///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2023  Washington State Department of Transportation
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
   m_Superelevation = WBFL::COGO::Superelevation::Create();
   m_pSurface = nullptr;
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
   };
   for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
   {
      if (InlineIsEqualGUID(*arr[i],riid))
         return S_OK;
   }
   return S_FALSE;
}

// ISuperelevation
STDMETHODIMP CSuperelevation::Init(VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 rate,IndexType pivotPoint,SuperTransitionType beginType,Float64 beginL1,Float64 beginL2,SuperTransitionType endType,Float64 endL1,Float64 endL2)
{
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
   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;

   m_Superelevation->SetBeginTransition(station);
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_BeginTransition(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Superelevation->GetBeginTransition(), station);
}

STDMETHODIMP CSuperelevation::put_BeginFullSuper(VARIANT varStation)
{
   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;

   m_Superelevation->SetBeginFullSuperelevation(station);
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_BeginFullSuper(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Superelevation->GetBeginFullSuperelevation(), station);
}

STDMETHODIMP CSuperelevation::put_EndFullSuper(VARIANT varStation)
{
   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;

   m_Superelevation->SetEndFullSuperelevation(station);
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_EndFullSuper(IStation** station)
{
   CHECK_RETVAL(station);
   return cogoUtil::CreateStation(m_Superelevation->GetEndFullSuperelevation(), station);
}

STDMETHODIMP CSuperelevation::put_EndTransition(VARIANT varStation)
{
   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   hr = ValidateStation(station);
   if (FAILED(hr)) return hr;

   m_Superelevation->SetEndTransition(station);
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_EndTransition(IStation** station)
{
   CHECK_RETOBJ(station);
   return cogoUtil::CreateStation(m_Superelevation->GetEndTransition(), station);
}

STDMETHODIMP CSuperelevation::put_Rate(Float64 value)
{
   m_Superelevation->SetRate(value);
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_Rate(Float64* value)
{
   CHECK_RETVAL(value);
   *value = m_Superelevation->GetRate();
   return S_OK;
}

STDMETHODIMP CSuperelevation::put_PivotPoint(IndexType pntIdx)
{
   ATLASSERT(pntIdx != INVALID_INDEX);
   if ( pntIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_Superelevation->SetPivotPoint(pntIdx);

   return S_OK;
}

STDMETHODIMP CSuperelevation::get_PivotPoint(IndexType* pntIdx)
{
   CHECK_RETVAL(pntIdx);

   *pntIdx = m_Superelevation->GetPivotPoint();
  
   return S_OK;
}

STDMETHODIMP CSuperelevation::put_BeginTransitionType(SuperTransitionType type)
{
   m_Superelevation->SetBeginTransitionType(WBFL::COGO::Superelevation::TransitionType(type));
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_BeginTransitionType(SuperTransitionType* type)
{
   CHECK_RETVAL(type);
   *type = SuperTransitionType(m_Superelevation->GetBeginTransitionType());
   return S_OK;
}

STDMETHODIMP CSuperelevation::SetBeginTransitionParameters(Float64 L1,Float64 L2)
{
   if ( L1 < 0 || L2 < 0 )
      return E_INVALIDARG;

   m_Superelevation->SetBeginTransitionParameters(L1, L2);

   return S_OK;
}

STDMETHODIMP CSuperelevation::GetBeginTransitionParameters(Float64* L1,Float64* L2)
{
   CHECK_RETVAL(L1);
   CHECK_RETVAL(L2);
   std::tie(*L1, *L2) = m_Superelevation->GetBeginTransitionParameters();
   return S_OK;
}

STDMETHODIMP CSuperelevation::put_EndTransitionType(SuperTransitionType type)
{
   m_Superelevation->SetEndTransitionType(WBFL::COGO::Superelevation::TransitionType(type));
   return S_OK;
}

STDMETHODIMP CSuperelevation::get_EndTransitionType(SuperTransitionType* type)
{
   CHECK_RETVAL(type);
   *type = SuperTransitionType(m_Superelevation->GetEndTransitionType());
   return S_OK;
}

STDMETHODIMP CSuperelevation::SetEndTransitionParameters(Float64 L1,Float64 L2)
{
   if ( L1 < 0 || L2 < 0 )
      return E_INVALIDARG;

   m_Superelevation->SetEndTransitionParameters(L1, L2);

   return S_OK;
}

STDMETHODIMP CSuperelevation::GetEndTransitionParameters(Float64* L1,Float64* L2)
{
   CHECK_RETVAL(L1);
   CHECK_RETVAL(L2);
   std::tie(*L1, *L2) = m_Superelevation->GetEndTransitionParameters();
   return S_OK;
}

STDMETHODIMP CSuperelevation::GetSlope(VARIANT varStation,Float64 templateSlope,Float64* pSlope)
{
   // adjusts the specified template slope with the superelevation
   CHECK_RETVAL(pSlope);

   HRESULT hr;
   WBFL::COGO::Station station;
   std::tie(hr, station) = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   *pSlope = m_Superelevation->GetSlope(station, templateSlope);
   return S_OK;
}

HRESULT CSuperelevation::ValidateStation(const WBFL::COGO::Station& station)
{
   auto surface = m_Superelevation->GetSurface();
   auto profile = (surface ? surface->GetProfile() : nullptr);
   auto alignment = (profile ? profile->GetAlignment() : nullptr);
   return (alignment == nullptr && !station.IsNormalized() ? E_INVALIDARG : S_OK);
}
