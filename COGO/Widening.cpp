///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2014  Washington State Department of Transportation
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

// Widening.cpp : Implementation of CWidening
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "Widening.h"
#include "Station.h"
#include "CogoHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWidening

HRESULT CWidening::FinalConstruct()
{
   m_pProfile = NULL;

   CComObject<CStation>* pBeginTransition;
   CComObject<CStation>::CreateInstance(&pBeginTransition);
   m_BeginTransition = pBeginTransition;

   CComObject<CStation>* pBeginFullWidening;
   CComObject<CStation>::CreateInstance(&pBeginFullWidening);
   m_BeginFullWidening = pBeginFullWidening;

   CComObject<CStation>* pEndFullWidening;
   CComObject<CStation>::CreateInstance(&pEndFullWidening);
   m_EndFullWidening = pEndFullWidening;

   CComObject<CStation>* pEndTransition;
   CComObject<CStation>::CreateInstance(&pEndTransition);
   m_EndTransition = pEndTransition;

   m_Widening = 0;
   m_SegmentIndex[0] = 0;
   m_SegmentIndex[1] = INVALID_INDEX;

   return S_OK;
}

void CWidening::FinalRelease()
{
}

STDMETHODIMP CWidening::InterfaceSupportsErrorInfo(REFIID riid)
{
   static const IID* arr[] = 
   {
      &IID_IWidening,
      &IID_IStructuredStorage2
   };
   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

// IWidening
STDMETHODIMP CWidening::Init(IProfile* pProfile,VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 widening,IndexType seg1,IndexType seg2)
{
   if ( FAILED(putref_Profile(pProfile)) )
      return E_FAIL;

   if ( FAILED(put_BeginTransition(varBeginStation)) )
      return E_FAIL;

   if ( FAILED(put_BeginFullWidening(varBeginFullStation)) )
      return E_FAIL;

   if ( FAILED(put_EndFullWidening(varEndFullStation)) )
      return E_FAIL;

   if ( FAILED(put_EndTransition(varEndStation)) )
      return E_FAIL;

   if ( FAILED(put_Widening(widening)) )
      return E_FAIL;

   if ( FAILED(put_Segment(0,seg1)) )
      return E_FAIL;

   if ( FAILED(put_Segment(1,seg2)) )
      return E_FAIL;

   return S_OK;
}

STDMETHODIMP CWidening::get_Profile(IProfile* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pProfile )
   {
      (*pVal) = m_pProfile;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CWidening::putref_Profile(IProfile* newVal)
{
   m_pProfile = newVal;
   return S_OK;
}

STDMETHODIMP CWidening::put_BeginTransition(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   if ( !cogoUtil::IsEqual(m_pProfile,objStation,m_BeginTransition) )
   {
      m_BeginTransition.Release();
      objStation->Clone(&m_BeginTransition);
      Fire_OnWideningChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CWidening::get_BeginTransition(IStation** station)
{
   return m_BeginTransition->Clone(station);
}

STDMETHODIMP CWidening::put_BeginFullWidening(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   if ( !cogoUtil::IsEqual(m_pProfile,objStation,m_BeginFullWidening) )
   {
      m_BeginFullWidening.Release();
      objStation->Clone(&m_BeginFullWidening);
      Fire_OnWideningChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CWidening::get_BeginFullWidening(IStation** station)
{
   return m_BeginFullWidening->Clone(station);
}

STDMETHODIMP CWidening::put_EndFullWidening(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   if ( !cogoUtil::IsEqual(m_pProfile,objStation,m_EndFullWidening) )
   {
      m_EndFullWidening.Release();
      objStation->Clone(&m_EndFullWidening);
      Fire_OnWideningChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CWidening::get_EndFullWidening(IStation** station)
{
   return m_EndFullWidening->Clone(station);
}

STDMETHODIMP CWidening::put_EndTransition(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   hr = ValidateStation(objStation);
   if ( FAILED(hr) )
      return hr;

   if ( !cogoUtil::IsEqual(m_pProfile,objStation,m_EndTransition) )
   {
      m_EndTransition.Release();
      objStation->Clone(&m_EndTransition);
      Fire_OnWideningChanged(this);
   }

   return S_OK;
}

STDMETHODIMP CWidening::get_EndTransition(IStation** station)
{
   return m_EndTransition->Clone(station);
}

STDMETHODIMP CWidening::put_Widening(Float64 value)
{
   if ( !IsEqual(m_Widening,value) )
   {
      m_Widening = value;
      Fire_OnWideningChanged(this);
   }
   return S_OK;
}

STDMETHODIMP CWidening::get_Widening(Float64* value)
{
   CHECK_RETVAL(value);
   *value = m_Widening;
   return S_OK;
}

STDMETHODIMP CWidening::put_Segment(IndexType pntIdx,IndexType segmentIdx)
{
   if ( 1 < pntIdx )
      return E_INVALIDARG;

   if ( m_SegmentIndex[pntIdx] != segmentIdx )
   {
      m_SegmentIndex[pntIdx] = segmentIdx;
      Fire_OnWideningChanged(this);
   }
   return S_OK;
}

STDMETHODIMP CWidening::get_Segment(IndexType pntIdx,IndexType* segmentIdx)
{
   CHECK_RETVAL(segmentIdx);

   if ( 1 < pntIdx )
      return E_INVALIDARG;

   *segmentIdx = m_SegmentIndex[pntIdx];
   return S_OK;
}

STDMETHODIMP CWidening::GetWidening(VARIANT varStation,IndexType templateSegmentIdx,Float64* pWidening)
{
   CHECK_RETVAL(pWidening);

   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   if ( templateSegmentIdx == INVALID_INDEX )
      return E_INVALIDARG;

   if ( m_SegmentIndex[0] != templateSegmentIdx && m_SegmentIndex[1] != templateSegmentIdx )
   {
      // the specified segment is not widened
      *pWidening = 0;
      return S_OK;
   }

   if ( 0 < cogoUtil::Compare(m_pProfile,objStation,m_BeginTransition) ||
        0 < cogoUtil::Compare(m_pProfile,m_EndTransition,objStation) )
   {
      // station is not in the widening area
      *pWidening = 0;
      return S_OK;
   }

   if ( 0 <= cogoUtil::Compare(m_pProfile,m_BeginTransition,objStation) &&
        0 <= cogoUtil::Compare(m_pProfile,objStation,m_BeginFullWidening) )
   {
      // In begin transition
      Float64 station = cogoUtil::GetNormalizedStationValue(m_pProfile,objStation);
      Float64 begin   = cogoUtil::GetNormalizedStationValue(m_pProfile,m_BeginTransition);
      Float64 full    = cogoUtil::GetNormalizedStationValue(m_pProfile,m_BeginFullWidening);
      if ( IsEqual(begin,full) )
      {
         *pWidening = m_Widening;
      }
      else
      {
         *pWidening = ::LinInterp(station-begin,0.0,m_Widening,full-begin);
      }
   }
   else if ( 0 <= cogoUtil::Compare(m_pProfile,m_EndFullWidening,objStation) &&
             0 <= cogoUtil::Compare(m_pProfile,objStation,m_EndTransition) )
   {
      // In end transition
      Float64 station = cogoUtil::GetNormalizedStationValue(m_pProfile,objStation);
      Float64 full    = cogoUtil::GetNormalizedStationValue(m_pProfile,m_EndFullWidening);
      Float64 end     = cogoUtil::GetNormalizedStationValue(m_pProfile,m_EndTransition);
      if ( IsEqual(full,end) )
      {
         *pWidening = m_Widening;
      }
      else
      {
         *pWidening = ::LinInterp(station-full,m_Widening,0.0,end-full);
      }
   }
   else
   {
      // In full widening
      *pWidening = m_Widening;
   }

   return S_OK;
}

STDMETHODIMP CWidening::Clone(IWidening** ppClone)
{
   CHECK_RETOBJ(ppClone);

   CComObject<CWidening>* pClone;
   CComObject<CWidening>::CreateInstance(&pClone);

   pClone->Init(m_pProfile,CComVariant(m_BeginTransition),CComVariant(m_BeginFullWidening),CComVariant(m_EndFullWidening),CComVariant(m_EndTransition),m_Widening,m_SegmentIndex[0],m_SegmentIndex[1]);

   (*ppClone) = pClone;
   (*ppClone)->AddRef();
   
   return S_OK;
}

STDMETHODIMP CWidening::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CWidening::Save(IStructuredSave2* pSave)
{
#pragma Reminder("IMPLEMENT CWidening:Save")
   pSave->BeginUnit(CComBSTR("Widening"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CWidening::Load(IStructuredLoad2* pLoad)
{
#pragma Reminder("IMPLEMENT CWidening::Load")

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Widening"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}


HRESULT CWidening::ValidateStation(IStation* station)
{
   if ( m_pProfile == NULL )
   {
      // if not associated with a profile, station must be normalized
      ZoneIndexType staEqnZoneIdx;
      station->get_StationZoneIndex(&staEqnZoneIdx);
      if ( staEqnZoneIdx != INVALID_INDEX )
         return E_INVALIDARG; // station must be normalized
   }

   return S_OK;
}
