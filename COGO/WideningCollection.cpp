///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// WideningCollection.cpp : Implementation of CWideningCollection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "WideningCollection.h"
#include "Widening.h"
#include "CogoHelpers.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class SortWidenings
{
public:
   SortWidenings(IProfile* pProfile) { m_pProfile = pProfile; }
   bool operator()(WideningType& pX,WideningType& pY)
   {
      CComVariant& varX = pX.second;
      CComVariant& varY = pY.second;
      CComPtr<IStation> staX, staY;
      
      CComQIPtr<IWidening> csX(varX.pdispVal);
      CComQIPtr<IWidening> csY(varY.pdispVal);

      csX->get_BeginTransition(&staX);
      csY->get_BeginTransition(&staY);
      return 0 < cogoUtil::Compare(m_pProfile,staX,staY);
   }
private:
   IProfile* m_pProfile; // weak reference
};

/////////////////////////////////////////////////////////////////////////////
// CWideningCollection
HRESULT CWideningCollection::FinalConstruct()
{
   m_pProfile = NULL;
   return S_OK;
}

void CWideningCollection::FinalRelease()
{
   UnadviseAll();
}

STDMETHODIMP CWideningCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWideningCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CWideningCollection::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CWideningCollection::putref_Profile(IProfile* pProfile)
{
   m_pProfile = pProfile;

   CComPtr<IEnumWidenings> enumWidenings;
   get__EnumWidenings(&enumWidenings);

   CComPtr<IWidening> widening;
   while ( enumWidenings->Next(1,&widening,NULL) != S_FALSE )
   {
      widening->putref_Profile(m_pProfile);
      widening.Release();
   };

   return S_OK;
}

//STDMETHODIMP CWideningCollection::get__NewEnum(IUnknown** retval)
//{
//}

STDMETHODIMP CWideningCollection::get_Item(CollectionIndexType idx, IWidening* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   WideningType& p = m_coll[idx];
   CComVariant& varItem = p.second;
   varItem.pdispVal->QueryInterface(pVal);
   return S_OK;
}

STDMETHODIMP CWideningCollection::putref_Item(CollectionIndexType idx,IWidening* pVal)
{
   CHECK_IN(pVal);

   HRESULT hr = S_OK;

   if ( !IsValidIndex(idx,m_coll) )
      return E_INVALIDARG;

   //hr = ValidateStation(pVal);
   //if ( FAILED(hr) )
   //   return hr;

   // Get the item
   WideningType& cst = m_coll[idx];
   CComVariant& var = cst.second; // Variant holding IDispatch to Widening
   pVal->putref_Profile(m_pProfile);

   UnadviseElement(idx); // Unadvise from the current element

   var = pVal; // Associate new Widening with this variant

   // Advise
   DWORD dwCookie;
   AdviseElement(pVal,&dwCookie);

   // Update the cookie
   cst.first = dwCookie;

   Fire_OnWideningChanged(pVal);

   return S_OK;
}

STDMETHODIMP CWideningCollection::GetWidening(VARIANT varStation,IWidening** widening)
{
   // searches for the Widening that contains the specified station
   CHECK_RETOBJ(widening);
   *widening = NULL;

   CComPtr<IStation> station;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&station);
   if ( FAILED(hr) )
      return hr;

   Widenings::iterator iter(m_coll.begin());
   Widenings::iterator end(m_coll.end());
   for ( ; iter != end; iter++ )
   {
      CComQIPtr<IWidening> thisWidening(iter->second.pdispVal);

      CComPtr<IStation> startStation,endStation;
      thisWidening->get_BeginTransition(&startStation);
      thisWidening->get_EndTransition(&endStation);

      if ( 0 <= cogoUtil::Compare(m_pProfile,startStation,station) &&
           0 <= cogoUtil::Compare(m_pProfile,station,endStation) )
      {
         return thisWidening.CopyTo(widening);
      }
   }

   return S_FALSE;
}

STDMETHODIMP CWideningCollection::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_coll.size();
   return S_OK;
}

STDMETHODIMP CWideningCollection::AddEx(IWidening* widening)
{
   CHECK_IN(widening);

   HRESULT hr = S_OK;
   //hr = ValidateStation(widening);
   //if ( FAILED(hr) )
   //   return hr;

   widening->putref_Profile(m_pProfile);

   DWORD dwCookie;
   AdviseElement(widening,&dwCookie);
   m_coll.push_back( std::make_pair(dwCookie,CComVariant(widening)));

   std::sort(m_coll.begin(),m_coll.end(),SortWidenings(m_pProfile));

   Fire_OnWideningAdded(widening);
   return S_OK;
}

STDMETHODIMP CWideningCollection::Add(VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 widening,IndexType pnt1,IndexType pnt2,IWidening* *pWidening)
{
   if ( pWidening != NULL )
   {
      CHECK_RETOBJ(pWidening);
   }

   CComObject<CWidening>* pNewWidening;
   CComObject<CWidening>::CreateInstance(&pNewWidening);
   CComPtr<IWidening> newWidening;
   newWidening = pNewWidening;

   HRESULT hr = newWidening->Init(m_pProfile,varBeginStation,varBeginFullStation,varEndFullStation,varEndStation,widening,pnt1,pnt2);
   if ( FAILED(hr) )
      return hr;

   if ( pWidening != NULL )
   {
      (*pWidening) = newWidening;
      (*pWidening)->AddRef();
   }

   return AddEx(newWidening);
}

STDMETHODIMP CWideningCollection::Remove(CollectionIndexType idx)
{
   if ( idx < 0 || m_coll.size() <= idx )
      return E_INVALIDARG;

   UnadviseElement(idx);
   m_coll.erase(m_coll.begin() + idx );
   Fire_OnWideningRemoved();
   return S_OK;
}

STDMETHODIMP CWideningCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   Fire_OnWideningsCleared();
   return S_OK;
}

STDMETHODIMP CWideningCollection::Clone(IWideningCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CWideningCollection>* pClone;
   CComObject<CWideningCollection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->putref_Profile(m_pProfile);

   CComPtr<IEnumWidenings> enumWidenings;
   get__EnumWidenings(&enumWidenings);

   CComPtr<IWidening> widening;
   while ( enumWidenings->Next(1,&widening,NULL) != S_FALSE )
   {
      CComPtr<IWidening> wideningClone;
      widening->Clone(&wideningClone);

      (*clone)->AddEx(wideningClone);

      widening.Release();
   };


   return S_OK;
}

STDMETHODIMP CWideningCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

/////////////////////////////////////////////////////////////////////////////
// IWideningEvents
STDMETHODIMP CWideningCollection::OnWideningChanged(IWidening * pWidening)
{
   Fire_OnWideningChanged(pWidening);
   return S_OK;
}

STDMETHODIMP CWideningCollection::get__EnumWidenings(IEnumWidenings** retval)
{
   CHECK_RETOBJ(retval);

   typedef CComEnumOnSTL<IEnumWidenings,
                         &IID_IEnumWidenings, 
                         IWidening*,
                         CopyFromPair2Interface<WideningType,IWidening*>, 
                         std::vector<WideningType>> Enum;
   CComObject<Enum>* pEnum;
   HRESULT hr = CComObject<Enum>::CreateInstance(&pEnum);
   if ( FAILED(hr) )
      return hr;

   hr = pEnum->Init( NULL, m_coll );
   if ( FAILED(hr) )
      return hr;

   pEnum->QueryInterface( retval );

   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CWideningCollection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Widenings"),1.0);
   CollectionIndexType count = m_coll.size();
   pSave->put_Property(CComBSTR("Count"),CComVariant(count));
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      pSave->put_Property(CComBSTR("Widening"),m_coll[i].second);
   }

   return S_OK;
}

STDMETHODIMP CWideningCollection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Widenings"));

   pLoad->get_Property(CComBSTR("Count"),&var);
   long count = var.lVal;

   for ( long i = 0; i < count; i++ )
   {
      pLoad->get_Property(CComBSTR("Widening"),&var);
      CComPtr<IWidening> widening;
      _CopyVariantToInterface<IWidening>::copy(&widening,&var);
      AddEx(widening);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////
// Helper methods

void CWideningCollection::AdviseElement(IWidening* widening,DWORD* pdwCookie)
{
   CComPtr<IWidening> pCP(widening);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_IWideningEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      ATLTRACE("Failed to establish connection point with Widening object\n");
      return;
   }

   InternalRelease(); // Break circular reference
}

void CWideningCollection::UnadviseElement(CollectionIndexType idx)
{
   //
   // Disconnection from connection Widening
   //
   WideningType& p = m_coll[idx];
   if ( p.first == 0 )
      return;

   DWORD dwCookie = p.first;
   CComVariant& var = p.second;

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( var.pdispVal );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_IWideningEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));

   p.first = 0;
}

void CWideningCollection::UnadviseAll()
{
   for ( CollectionIndexType i = 0; i < m_coll.size(); i++ )
   {
      UnadviseElement(i);
   }
}

HRESULT CWideningCollection::OnBeforeSave(IStructuredSave2* pSave)
{
   return S_OK;
}

HRESULT CWideningCollection::OnBeforeLoad(IStructuredLoad2* pLoad)
{
   return S_OK;
}
//
//HRESULT CWideningCollection::ValidateStation(IWidening* csect)
//{
//   CComPtr<IStation> station;
//   csect->get_Station(&station);
//   CComPtr<IStation> sta;
//   return ValidateStation(CComVariant(station),false,&sta);
//}
//
//HRESULT CWideningCollection::ValidateStation(VARIANT varStation,bool bClone,IStation** station)
//{
//   HRESULT hr = cogoUtil::StationFromVariant(varStation,bClone,station);
//   if ( FAILED(hr) )
//      return hr;
//
//   if ( m_pProfile == NULL )
//   {
//      ZoneIndexType staEqnZoneIdx;
//      (*station)->get_StationZoneIndex(&staEqnZoneIdx);
//      if ( staEqnZoneIdx != INVALID_INDEX )
//         return E_INVALIDARG; // station must be normalized
//   }
//
//   return S_OK;
//}