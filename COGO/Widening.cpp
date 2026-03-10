///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <WBFLCogo\CogoHelpers.h>


/////////////////////////////////////////////////////////////////////////////
// CWidening

HRESULT CWidening::FinalConstruct()
{
   m_Widening = WBFL::COGO::Widening::Create();
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
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

// IWidening
STDMETHODIMP CWidening::Init(VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 widening,IndexType seg1,IndexType seg2)
{
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

STDMETHODIMP CWidening::get_Surface(ISurface* *pVal)
{
   CHECK_RETOBJ(pVal);
   if ( m_pSurface )
   {
      (*pVal) = m_pSurface;
      (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CWidening::putref_Surface(ISurface* newVal)
{
   CHECK_IN(newVal);
   m_pSurface = newVal;
   return S_OK;
}

STDMETHODIMP CWidening::put_BeginTransition(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;
   
   m_Widening->SetBeginTransition(station);
   return S_OK;
}

STDMETHODIMP CWidening::get_BeginTransition(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Widening->GetBeginTransition(), station);
}

STDMETHODIMP CWidening::put_BeginFullWidening(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;

   m_Widening->SetBeginFullWidening(station);
   return S_OK;
}

STDMETHODIMP CWidening::get_BeginFullWidening(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Widening->GetBeginFullWidening(), station);
}

STDMETHODIMP CWidening::put_EndFullWidening(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;

   m_Widening->SetEndFullWidening(station);
   return S_OK;
}

STDMETHODIMP CWidening::get_EndFullWidening(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Widening->GetEndFullWidening(), station);
}

STDMETHODIMP CWidening::put_EndTransition(VARIANT varStation)
{
   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;

   m_Widening->SetEndTransition(station);
   return S_OK;
}

STDMETHODIMP CWidening::get_EndTransition(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Widening->GetEndTransition(), station);
}

STDMETHODIMP CWidening::put_Widening(Float64 value)
{
   m_Widening->SetWidening(value);
   return S_OK;
}

STDMETHODIMP CWidening::get_Widening(Float64* value)
{
   CHECK_RETVAL(value);
   *value = m_Widening->GetWidening();
   return S_OK;
}

STDMETHODIMP CWidening::put_Segment(IndexType pntIdx,IndexType segmentIdx)
{
   if (1 < pntIdx) return E_INVALIDARG;
   m_Widening->SetSegment(pntIdx, segmentIdx);
   return S_OK;
}

STDMETHODIMP CWidening::get_Segment(IndexType pntIdx,IndexType* segmentIdx)
{
   CHECK_RETVAL(segmentIdx);
   if (1 < pntIdx) return E_INVALIDARG;
   *segmentIdx = m_Widening->GetSegment(pntIdx);
   return S_OK;
}

STDMETHODIMP CWidening::GetWidening(VARIANT varStation,IndexType templateSegmentIdx,Float64* pWidening)
{
   CHECK_RETVAL(pWidening);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *pWidening = m_Widening->GetWidening(station, templateSegmentIdx);
   return S_OK;
}

HRESULT CWidening::ValidateStation(const WBFL::COGO::Station& station)
{
   auto surface = m_Widening->GetSurface();
   auto profile = (surface ? surface->GetProfile() : nullptr);
   auto alignment = (profile ? profile->GetAlignment() : nullptr);
   return (alignment == nullptr && !station.IsNormalized() ? E_INVALIDARG : S_OK);
}
