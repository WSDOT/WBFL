///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include "SingleDiaphragmLineFactory.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CSingleDiaphragmLineFactory::put_AlignmentID(IDType ID)
{
   m_Factory->SetAlignmentID(ID);
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_AlignmentID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetAlignmentID();
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_Station(VARIANT varStation)
{
   auto [hr,station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;
   m_Factory->SetStation(station);
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_Station(IStation** ppStation)
{
   CHECK_RETOBJ(ppStation);
   return cogoUtil::CreateStation(m_Factory->GetStation(), ppStation);
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_Orientation(BSTR orientation)
{
   USES_CONVERSION;
   m_Factory->SetOrientation(OLE2T(orientation));
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_Orientation(BSTR* orientation)
{
   CHECK_RETVAL(orientation);
   USES_CONVERSION;
   CComBSTR bstr(m_Factory->GetOrientation().c_str());
   return bstr.CopyTo(orientation);
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_DiaphragmLineID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetDiaphragmLineID();
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_DiaphragmLineID(IDType newVal)
{
   m_Factory->SetDiaphragmLineID(newVal);
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_Staggered(VARIANT_BOOL bStaggered)
{
   m_Factory->IsStaggered(bStaggered == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_Staggered(VARIANT_BOOL* bStaggered)
{
   CHECK_RETVAL(bStaggered);
   *bStaggered = m_Factory->IsStaggered() ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_LeftGirderLineID(IDType ID)
{
   m_Factory->SetGirderLineID(WBFL::COGO::SideType::Left, ID);
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_LeftGirderLineID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetGirderLineID(WBFL::COGO::SideType::Left);
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::put_RightGirderLineID(IDType ID)
{
   m_Factory->SetGirderLineID(WBFL::COGO::SideType::Right, ID);
   return S_OK;
}

STDMETHODIMP CSingleDiaphragmLineFactory::get_RightGirderLineID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetGirderLineID(WBFL::COGO::SideType::Right);
   return S_OK;
}

