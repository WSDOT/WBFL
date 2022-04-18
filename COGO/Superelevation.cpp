///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2022  Washington State Department of Transportation
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

// Superelevation.cpp : Implementation of CSuperelevation
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Superelevation.h"
#include "Station.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperelevation

HRESULT CSuperelevation::FinalConstruct()
{
   m_pSurface = nullptr;

   CComObject<CStation>* pBeginTransition;
   CComObject<CStation>::CreateInstance(&pBeginTransition);
   m_BeginTransition = pBeginTransition;

   CComObject<CStation>* pBeginFullSuper;
   CComObject<CStation>::CreateInstance(&pBeginFullSuper);
   m_BeginFullSuper = pBeginFullSuper;

   CComObject<CStation>* pEndFullSuper;
   CComObject<CStation>::CreateInstance(&pEndFullSuper);
   m_EndFullSuper = pEndFullSuper;

   CComObject<CStation>* pEndTransition;
   CComObject<CStation>::CreateInstance(&pEndTransition);
   m_EndTransition = pEndTransition;

   m_Rate = 0;
   m_PivotPoint = 0;

   m_BeginTransitionType      = stLinear;
   m_BeginTransitionLength[0] = 0;
   m_BeginTransitionLength[1] = 0;

   m_EndTransitionType      = stLinear;
   m_EndTransitionLength[0] = 0;
   m_EndTransitionLength[1] = 0;

   return S_OK;
}

void CSuperelevation::FinalRelease()
{
}

STDMETHODIMP CSuperelevation::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_ISuperelevation,
      &IID_IStructuredStorage2
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

// ISuperelevation
STDMETHODIMP CSuperelevation::Init(ISurface* pSurface,VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 rate,IndexType pivotPoint,SuperTransitionType beginType,Float64 beginL1,Float64 beginL2,SuperTransitionType endType,Float64 endL1,Float64 endL2)
{
   if ( FAILED(putref_Surface(pSurface)) )
      return E_FAIL;

   if ( FAILED(put_BeginTransition(varBeginStation)) )
      return E_FAIL;

   if ( FAILED(put_BeginFullSuper(varBeginFullStation)) )
      return E_FAIL;

   if ( FAILED(put_EndFullSuper(varEndFullStation)) )
      return E_FAIL;

   if ( FAILED(put_EndTransition(varEndStation)) )
      return E_FAIL;

   if ( FAILED(put_Rate(rate)) )
      return E_FAIL;

   if ( FAILED(put_PivotPoint(pivotPoint)) )
      return E_FAIL;

   if ( FAILED(put_BeginTransitionType(beginType)) )
      return E_FAIL;

   if ( FAILED(SetBeginTransitionParameters(beginL1,beginL2)) )
      return E_FAIL;

   if ( FAILED(put_EndTransitionType(endType)) )
      return E_FAIL;

   if ( FAILED(SetEndTransitionParameters(endL1,endL2)) )
      return E_FAIL;

   return S_OK;
}

STDMETHODIMP CSuperelevation::get_Surface(ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pSurface )
   {
      (*pVal) = m_pSurface;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::putref_Surface(ISurface* newVal)
{
   CHECK_IN(newVal);
   m_pSurface = newVal;
   return S_OK;
}

STDMETHODIMP CSuperelevation::put_BeginTransition(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( !cogoUtil::IsEqual(profile,objStation,m_BeginTransition) )
   {
      m_BeginTransition.Release();
      objStation->Clone(&m_BeginTransition);
      Fire_OnSuperelevationChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::get_BeginTransition(IStation** station)
{
   return m_BeginTransition->Clone(station);
}

STDMETHODIMP CSuperelevation::put_BeginFullSuper(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( !cogoUtil::IsEqual(profile,objStation,m_BeginFullSuper) )
   {
      m_BeginFullSuper.Release();
      objStation->Clone(&m_BeginFullSuper);
      Fire_OnSuperelevationChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::get_BeginFullSuper(IStation** station)
{
   return m_BeginFullSuper->Clone(station);
}

STDMETHODIMP CSuperelevation::put_EndFullSuper(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( !cogoUtil::IsEqual(profile,objStation,m_EndFullSuper) )
   {
      m_EndFullSuper.Release();
      objStation->Clone(&m_EndFullSuper);
      Fire_OnSuperelevationChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::get_EndFullSuper(IStation** station)
{
   return m_EndFullSuper->Clone(station);
}

STDMETHODIMP CSuperelevation::put_EndTransition(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( !cogoUtil::IsEqual(profile,objStation,m_EndTransition) )
   {
      m_EndTransition.Release();
      objStation->Clone(&m_EndTransition);
      Fire_OnSuperelevationChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::get_EndTransition(IStation** station)
{
   return m_EndTransition->Clone(station);
}

STDMETHODIMP CSuperelevation::put_Rate(Float64 value)
{
   if (!IsEqual(m_Rate, value))
   {
      m_Rate = value;
      Fire_OnSuperelevationChanged(this);
   }
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_Rate(Float64* value)
{
   CHECK_RETVAL(value);
   *value = m_Rate;
   return S_OK;
}

STDMETHODIMP CSuperelevation::put_PivotPoint(IndexType pntIdx)
{
   ATLASSERT(pntIdx != INVALID_INDEX);
   if ( pntIdx == INVALID_INDEX )
      return E_INVALIDARG;

   if (m_PivotPoint != pntIdx)
   {
      
      m_PivotPoint = pntIdx;
      Fire_OnSuperelevationChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::get_PivotPoint(IndexType* pntIdx)
{
   CHECK_RETVAL(pntIdx);

   *pntIdx = m_PivotPoint;
   return S_OK;
}

STDMETHODIMP CSuperelevation::put_BeginTransitionType(SuperTransitionType type)
{
   if ( m_BeginTransitionType != type )
   { 
      m_BeginTransitionType = type;
      Fire_OnSuperelevationChanged(this);
   }
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_BeginTransitionType(SuperTransitionType* type)
{
   CHECK_RETVAL(type);
   *type = m_BeginTransitionType;
   return S_OK;
}

STDMETHODIMP CSuperelevation::SetBeginTransitionParameters(Float64 L1,Float64 L2)
{
   if ( L1 < 0 || L2 < 0 )
      return E_INVALIDARG;

   if ( !IsEqual(L1,m_BeginTransitionLength[0]) || !IsEqual(L2,m_BeginTransitionLength[1]) )
   {
      m_BeginTransitionLength[0] = L1;
      m_BeginTransitionLength[1] = L2;
      Fire_OnSuperelevationChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::GetBeginTransitionParameters(Float64* L1,Float64* L2)
{
   CHECK_RETVAL(L1);
   CHECK_RETVAL(L2);
   *L1 = m_BeginTransitionLength[0];
   *L2 = m_BeginTransitionLength[1];
   return S_OK;
}

STDMETHODIMP CSuperelevation::put_EndTransitionType(SuperTransitionType type)
{
   if ( m_EndTransitionType != type )
   { 
      m_EndTransitionType = type;
      Fire_OnSuperelevationChanged(this);
   }
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_EndTransitionType(SuperTransitionType* type)
{
   CHECK_RETVAL(type);
   *type = m_EndTransitionType;
   return S_OK;
}

STDMETHODIMP CSuperelevation::SetEndTransitionParameters(Float64 L1,Float64 L2)
{
   if ( L1 < 0 || L2 < 0 )
      return E_INVALIDARG;

   if ( !IsEqual(L1,m_EndTransitionLength[0]) || !IsEqual(L2,m_EndTransitionLength[1]) )
   {
      m_EndTransitionLength[0] = L1;
      m_EndTransitionLength[1] = L2;
      Fire_OnSuperelevationChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::GetEndTransitionParameters(Float64* L1,Float64* L2)
{
   CHECK_RETVAL(L1);
   CHECK_RETVAL(L2);
   *L1 = m_EndTransitionLength[0];
   *L2 = m_EndTransitionLength[1];
   return S_OK;
}

STDMETHODIMP CSuperelevation::GetSlope(VARIANT varStation,Float64 templateSlope,Float64* pSlope)
{
   // adjusts the specified template slope with the superelevation
   CHECK_RETVAL(pSlope);

   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( 0 < cogoUtil::Compare(profile,objStation,m_BeginTransition) ||
        0 < cogoUtil::Compare(profile,m_EndTransition,objStation) )
   {
      // station is not in the supertransition area
      *pSlope = templateSlope;
      return S_OK;
   }

   if ( 0 <= cogoUtil::Compare(profile,m_BeginTransition,objStation) &&
        0 <= cogoUtil::Compare(profile,objStation,m_BeginFullSuper) )
   {
      // In begin transition
      hr = ComputeSlopeInBeginTransition(objStation,templateSlope,pSlope);
      if ( FAILED(hr) )
         return hr;
   }
   else if ( 0 <= cogoUtil::Compare(profile,m_EndFullSuper,objStation) &&
             0 <= cogoUtil::Compare(profile,objStation,m_EndTransition) )
   {
      // In end transition
      hr = ComputeSlopeInEndTransition(objStation,templateSlope,pSlope);
      if ( FAILED(hr) )
         return hr;
   }
   else
   {
      // In full super
      *pSlope = m_Rate;
   }

   return S_OK;
}

STDMETHODIMP CSuperelevation::Clone(ISuperelevation** ppClone)
{
   CHECK_RETOBJ(ppClone);

   CComObject<CSuperelevation>* pClone;
   CComObject<CSuperelevation>::CreateInstance(&pClone);

   pClone->Init(m_pSurface,CComVariant(m_BeginTransition),CComVariant(m_BeginFullSuper),CComVariant(m_EndFullSuper),CComVariant(m_EndTransition),m_Rate,m_PivotPoint,m_BeginTransitionType,m_BeginTransitionLength[0],m_BeginTransitionLength[1],m_EndTransitionType,m_EndTransitionLength[0],m_EndTransitionLength[1]);

   (*ppClone) = pClone;
   (*ppClone)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CSuperelevation::Save(IStructuredSave2* pSave)
{
#pragma Reminder("IMPLEMENT CSuperelevation:Save")
   pSave->BeginUnit(CComBSTR("Superelevation"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CSuperelevation::Load(IStructuredLoad2* pLoad)
{
#pragma Reminder("IMPLEMENT CSuperelevation::Load")

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Superelevation"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}


HRESULT CSuperelevation::ValidateStation(IStation* station)
{
   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   if ( profile == nullptr )
   {
      // if not associated with a profile, station must be normalized
      ZoneIndexType staEqnZoneIdx;
      station->get_StationZoneIndex(&staEqnZoneIdx);
      if ( staEqnZoneIdx != INVALID_INDEX )
      {
         return E_INVALIDARG; // station must be normalized
      }
   }

   return S_OK;
}

HRESULT CSuperelevation::ComputeSlopeInBeginTransition(IStation* pStation,Float64 templateSlope,Float64* pSlope)
{
   return ComputeSlopeInTransition(pStation,m_BeginTransition,m_BeginFullSuper,m_BeginTransitionType,m_BeginTransitionLength[0],m_BeginTransitionLength[1],templateSlope,m_Rate,pSlope);
}

HRESULT CSuperelevation::ComputeSlopeInEndTransition(IStation* pStation,Float64 templateSlope,Float64* pSlope)
{
   return ComputeSlopeInTransition(pStation,m_EndFullSuper,m_EndTransition,m_EndTransitionType,m_EndTransitionLength[0],m_EndTransitionLength[1],m_Rate,templateSlope,pSlope);
}

HRESULT CSuperelevation::ComputeSlopeInTransition(IStation* pStation,IStation* pStartTransition,IStation* pEndTransition,SuperTransitionType transitionType,Float64 L1,Float64 L2,Float64 startSlope,Float64 endSlope,Float64* pSlope)
{
   CComPtr<IProfile> profile;
   if ( m_pSurface )
   {
      m_pSurface->get_Profile(&profile); 
   }
   Float64 station = cogoUtil::GetNormalizedStationValue(profile,pStation);
   Float64 start   = cogoUtil::GetNormalizedStationValue(profile,pStartTransition);
   Float64 end     = cogoUtil::GetNormalizedStationValue(profile,pEndTransition);
   Float64 slope = 0.0;
   if ( IsEqual(start,end) )
   {
      slope = endSlope;
   }
   else if (transitionType == stLinear )
   {
      slope = ::LinInterp(station-start,startSlope,endSlope,end-start);
   }
   else if (transitionType == stParabolic)
   {
      Float64 L3 = end - start - L1 - L2;
      L3 = IsZero(L3) ? 0 : L3;
      if ( L3 < 0 )
      {
         return SuperelevationError(IDS_E_SUPERTRANSITIONERROR,COGO_E_SUPERTRANSITIONERROR);
      }

      Float64 x = station - start; // distance into transition zone
      Float64 K = IsZero(L1) && IsZero(L2) ? 0 : (endSlope-startSlope)/(L1*L1 + 2*L1*L3 + L1*L2);
      if ( x < L1 )
      {
         // first parabola
         slope = K*x*x + startSlope;
      }
      else if ( x < (L1+L3) )
      {
         // linear section
         Float64 Ya = K*L1*L1 + startSlope; // slope at end of first parabola
         Float64 Yb = -L1*L2*K + endSlope;  // slope at start of second parabola
         slope = ::LinInterp(x-L1,Ya,Yb,L3);
      }
      else
      {
         // second parabola
         Float64 x2 = x - L1 - L3;
         slope = -L1*K*x2*x2/L2 + 2*L1*K*x2 - L1*L2*K + endSlope;
      }
   }
   else
   {
      ATLASSERT(false); // is there a new transition type?
   }

   *pSlope = slope;
   return S_OK;
}

HRESULT CSuperelevation::SuperelevationError(UINT nHelpString,HRESULT hRes)
{
   USES_CONVERSION;

   TCHAR str[256];
   ::LoadString( _Module.GetModuleInstance(), nHelpString, str, 256);
   CComBSTR oleMsg(str);
   return Error(oleMsg, IID_ISuperelevation, hRes);
}
