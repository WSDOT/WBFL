///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2013  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// StationEquationCollection.cpp : Implementation of CStationEquationCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "StationEquationCollection.h"
#include "StationEquation.h"
#include "Station.h"
#include "CogoHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationEquationCollection
HRESULT CStationEquationCollection::FinalConstruct()
{
   return S_OK;
}

void CStationEquationCollection::FinalRelease()
{
}

STDMETHODIMP CStationEquationCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStationEquationCollection,
		&IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStationEquationCollection::get_Alignment(IAlignment** ppAlignment)
{
   CHECK_RETVAL(ppAlignment);
   (*ppAlignment) = m_pAlignment;
   if ( m_pAlignment )
      (*ppAlignment)->AddRef();

   return S_OK;
}

STDMETHODIMP CStationEquationCollection::putref_Alignment(IAlignment* pAlignment)
{
   m_pAlignment = pAlignment;
   return S_OK;
}

STDMETHODIMP CStationEquationCollection::Add(Float64 back,Float64 ahead,IStationEquation* *ppEquation)
{
   if ( ppEquation != NULL )
   {
      CHECK_RETVAL(ppEquation);
   }

   CComObject<CStationEquation>* pEquation;
   CComObject<CStationEquation>::CreateInstance(&pEquation);
   CComPtr<IStationEquation> equation(pEquation);

   pEquation->m_Back = back;
   pEquation->m_Ahead = ahead;
   pEquation->m_NormalizedStation = ComputeNormalizedStation(back);

   if ( 0 < m_coll.size() )
   {
      PersistentStationEquationCollection::StoredType& item(m_coll.back());
      Float64 prevAhead;
      item.second.m_T->get_Ahead(&prevAhead);
      if ( back <= prevAhead )
      {
         return BackStationError();
      }
   }

   if ( ppEquation != NULL )
   {
      (*ppEquation) = pEquation;
      (*ppEquation)->AddRef();
   }

   return PersistentStationEquationCollection::Add(pEquation);
}

STDMETHODIMP CStationEquationCollection::Clear()
{
   m_coll.clear();
   Fire_OnEquationsCleared();
	return S_OK;
}

STDMETHODIMP CStationEquationCollection::get__EnumStationEquations(IEnumStationEquations** ppenum)
{
   CHECK_RETOBJ(ppenum);

   typedef CComEnumOnSTL<IEnumStationEquations, &IID_IEnumStationEquations, IStationEquation*, CustomCopyType, ContainerType> MyEnumType;
   CComObject<MyEnumType>* pEnum;
   HRESULT hr = CComObject<MyEnumType>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IEnumStationEquations> pHolder(pEnum); // memory leak avoidance

   hr = pEnum->Init( NULL, m_coll );
   if ( FAILED(hr) )
      return hr;

   *ppenum = pEnum;
   (*ppenum)->AddRef(); // for client

   return S_OK;
}

STDMETHODIMP CStationEquationCollection::get_StructuredStorage(IStructuredStorage2* *pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface(IID_IStructuredStorage2,(void**)pVal);
}

STDMETHODIMP CStationEquationCollection::Distance(VARIANT varStation1,VARIANT varStation2,Float64* pDist)
{
   CHECK_RETVAL(pDist);
   Float64 s1,s2;
   HRESULT hr;
   hr = ConvertToNormalizedStation(varStation1,&s1);
   if ( FAILED(hr) )
      return hr;

   hr = ConvertToNormalizedStation(varStation2,&s2);
   if ( FAILED(hr) )
      return hr;

   *pDist = s2 - s1;
   return S_OK;
}

STDMETHODIMP CStationEquationCollection::Increment(VARIANT varStation,Float64 value,IStation** station)
{
   CHECK_RETOBJ(station);

   Float64 n;
   
   HRESULT hr = ConvertToNormalizedStation(varStation,&n);
   if ( FAILED(hr) )
      return hr;

   n += value;

   return ConvertFromNormalizedStation(n,station);
}

STDMETHODIMP CStationEquationCollection::IncrementBy(IStation* station,Float64 value)
{
   CHECK_IN(station);
   Float64 n;
   
   HRESULT hr = ConvertToNormalizedStation(CComVariant(station),&n);
   if ( FAILED(hr) )
      return hr;

   n += value;

   return ConvertFromNormalizedStation(n,&station);
}

STDMETHODIMP CStationEquationCollection::ConvertToNormalizedStation(VARIANT varStation,Float64* stationValue)
{
   CComPtr<IStation> station;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&station);
   if ( FAILED(hr) )
   {
      return hr;
   }

   ZoneIndexType zoneIdx;
   Float64 value;
   station->GetStation(&zoneIdx,&value);
   if ( zoneIdx == INVALID_INDEX )
   {
      *stationValue = value;
      return S_OK;
   }

   IndexType nEquations = m_coll.size();
   if ( nEquations < zoneIdx )
      return E_INVALIDARG; // the zone index is invalid (must be between 0 and nEquations+1

   if ( zoneIdx == 0 )
   {
      // before the first equation
      if ( 0 < m_coll.size() )
      {
         // make sure the station is before the back station of the next equation
         Float64 nextBack;
         m_coll.front().second.m_T->get_Back(&nextBack);
         if ( nextBack < value )
         {
            return StationEquationError(IDS_E_STATIONRANGEERROR,COGO_E_STATIONRANGEERROR);
         }

         *stationValue = value;
         return S_OK;
      }
      else
      {
         *stationValue = value;
         return S_OK;
      }
   }

   if ( zoneIdx == nEquations )
   {
      // after the last equation
      // make sure the station is after the last ahead station
      Float64 nextAhead;
      m_coll.back().second.m_T->get_Ahead(&nextAhead);
      if ( value < nextAhead )
      {
         return StationEquationError(IDS_E_STATIONRANGEERROR,COGO_E_STATIONRANGEERROR);
      }

      Float64 normalizedStation;
      m_coll.back().second.m_T->get_NormalizedValue(&normalizedStation);
      *stationValue = normalizedStation + (value-nextAhead);
      return S_OK;
   }

   // zone is somewhere between two equations

   IndexType eqIdx = zoneIdx-1;
   Float64 prevAhead, nextBack;
   m_coll[eqIdx].second.m_T->get_Ahead(&prevAhead);
   m_coll[eqIdx+1].second.m_T->get_Back(&nextBack);
   if ( !InRange(prevAhead,value,nextBack) )
   {
      return StationEquationError(IDS_E_STATIONRANGEERROR,COGO_E_STATIONRANGEERROR);
   }
   
   Float64 normalizedStation;
   m_coll[eqIdx].second.m_T->get_NormalizedValue(&normalizedStation);

   *stationValue = normalizedStation + (value-prevAhead);

   return S_OK;
}

STDMETHODIMP CStationEquationCollection::ConvertToNormalizedStationEx(VARIANT varStation,IStation** station)
{
   if ( station == NULL )
      return E_POINTER;

   if ( *station == NULL )
   {
      CComObject<CStation>* pStation;
      CComObject<CStation>::CreateInstance(&pStation);
      (*station) = pStation;
      (*station)->AddRef();
   }

   Float64 normalizedStation;
   HRESULT hr = ConvertToNormalizedStation(varStation,&normalizedStation);
   if ( FAILED(hr) )
      return hr;

   (*station)->SetStation(INVALID_INDEX,normalizedStation);

   return S_OK;
}

STDMETHODIMP CStationEquationCollection::ConvertFromNormalizedStation(Float64 normalizedStation,IStation** station)
{
   if ( station == NULL )
      return E_POINTER;

   if ( *station == NULL )
   {
      CComObject<CStation>* pStation;
      CComObject<CStation>::CreateInstance(&pStation);
      (*station) = pStation;
      (*station)->AddRef();
   }

   if ( m_coll.size() == 0 )
   {
      // no station equations
      (*station)->SetStation(INVALID_INDEX,normalizedStation);
      return S_OK;
   }

   Float64 ns;
   m_coll.front().second.m_T->get_NormalizedValue(&ns);
   if (normalizedStation <= ns)
   {
      // before the start of the station equations
      (*station)->SetStation(0,normalizedStation);
      return S_OK;
   }

   m_coll.back().second.m_T->get_NormalizedValue(&ns);
   if (ns <= normalizedStation)
   {
      // after the end of the station equations
      Float64 ahead;
      m_coll.back().second.m_T->get_Ahead(&ahead);

      (*station)->SetStation(m_coll.size(),normalizedStation - ns + ahead);
      return S_OK;
   }

   // somewhere in the middle... find it
   PersistentStationEquationCollection::ContainerIteratorType iter(m_coll.begin());
   PersistentStationEquationCollection::ContainerIteratorType end(m_coll.end());
   iter++;
   for ( ; iter != end; iter++ )
   {
      Float64 ns1,ns2;
      (iter-1)->second.m_T->get_NormalizedValue(&ns1);
      iter->second.m_T->get_NormalizedValue(&ns2);

      if ( InRange(ns1,normalizedStation,ns2) )
      {
         Float64 ahead;
         (iter-1)->second.m_T->get_Ahead(&ahead);
         (*station)->SetStation(ZoneIndexType(iter-m_coll.begin()),normalizedStation - ns1 + ahead);
         return S_OK;
      }
   }

   ATLASSERT(false); // should not get here
   return E_FAIL;
}

STDMETHODIMP CStationEquationCollection::ConvertFromNormalizedStationEx(VARIANT varStation,IStation** station)
{
   CComPtr<IStation> objNormalizedStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objNormalizedStation);
   if ( FAILED(hr) )
   {
      return hr;
   }

   ZoneIndexType idx;
   Float64 normalizedStation;
   objNormalizedStation->GetStation(&idx,&normalizedStation);
   if ( idx != INVALID_INDEX )
   {
      return E_INVALIDARG;
   }

   return ConvertFromNormalizedStation(normalizedStation,station);
}

Float64 CStationEquationCollection::ComputeNormalizedStation(Float64 back)
{
   if ( m_coll.size() == 0 )
      return back;

   Float64 prevNormalizedStation;
   m_coll.back().second.m_T->get_NormalizedValue(&prevNormalizedStation);

   Float64 prevAhead;
   m_coll.back().second.m_T->get_Ahead(&prevAhead);

   Float64 dist = back - prevAhead;

   return prevNormalizedStation + dist;
}

HRESULT CStationEquationCollection::BackStationError()
{
   return StationEquationError(IDS_E_STATIONEQUATIONBACK,COGO_E_STATIONEQUATIONBACK);
}

HRESULT CStationEquationCollection::AheadStationError()
{
   return StationEquationError(IDS_E_STATIONEQUATIONAHEAD,COGO_E_STATIONEQUATIONAHEAD);
}

HRESULT CStationEquationCollection::StationEquationError(UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   CComBSTR oleMsg(str);
   return Error(oleMsg, IID_IStationEquationCollection, hRes);
}
