///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// DiaphragmLine.cpp : Implementation of CDiaphragm

#include "stdafx.h"
#include "WBFLCogo.h"
#include "EqualSpacingDiaphragmLineFactory.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::put_AlignmentID(IDType ID)
{
   m_Factory->SetAlignmentID(ID);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::get_AlignmentID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetAlignmentID();
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::SetStationRange(VARIANT varStartStation, VARIANT varEndStation)
{
   HRESULT hr;
   WBFL::COGO::Station startStation;
   std::tie(hr,startStation) = cogoUtil::StationFromVariant(varStartStation);
   if (FAILED(hr)) return hr;
   
   WBFL::COGO::Station endStation;
   std::tie(hr,endStation) = cogoUtil::StationFromVariant(varEndStation);
   if (FAILED(hr)) return hr;
   
   m_Factory->SetStationRange(startStation, endStation);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::GetStationRange(IStation** ppStartStation, IStation** ppEndStation)
{
   CHECK_RETOBJ(ppStartStation);
   CHECK_RETOBJ(ppEndStation);
   const auto& [startStation,endStation] = m_Factory->GetStationRange();
   HRESULT hr = S_OK;
   hr = cogoUtil::CreateStation(startStation, ppStartStation);
   if (FAILED(hr)) return hr;
   hr = cogoUtil::CreateStation(endStation, ppEndStation);
   if (FAILED(hr)) return hr;
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::get_DiaphragmLineID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetDiaphragmLineID();
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::put_DiaphragmLineID(IDType newVal)
{
   m_Factory->SetDiaphragmLineID(newVal);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::get_DiaphragmLineIDInc(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetDiaphragmLineIDIncrement();
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::put_DiaphragmLineIDInc(IDType newVal)
{
   m_Factory->SetDiaphragmLineIDIncrement(newVal);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::put_Divisor(Uint16 divisor)
{
   m_Factory->SetDivisor(divisor);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::get_Divisor(Uint16* divisor)
{
   CHECK_RETVAL(divisor);
   *divisor = m_Factory->GetDivisor();
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::put_Staggered(VARIANT_BOOL bStaggered)
{
   m_Factory->IsStaggered(bStaggered == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::get_Staggered(VARIANT_BOOL* bStaggered)
{
   CHECK_RETVAL(bStaggered);
   *bStaggered = m_Factory->IsStaggered() ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::put_LeftGirderLineID(IDType ID)
{
   m_Factory->SetGirderLineID(WBFL::COGO::SideType::Left, ID);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::get_LeftGirderLineID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetGirderLineID(WBFL::COGO::SideType::Left);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::put_RightGirderLineID(IDType ID)
{
   m_Factory->SetGirderLineID(WBFL::COGO::SideType::Right, ID);
   return S_OK;
}

STDMETHODIMP CEqualSpacingDiaphragmLineFactory::get_RightGirderLineID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetGirderLineID(WBFL::COGO::SideType::Right);
   return S_OK;
}

