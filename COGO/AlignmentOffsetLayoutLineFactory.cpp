///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// SinglePierLineFactory.cpp : Implementation of CSinglePierLineFactory

#include "stdafx.h"
#include "WBFLCogo.h"
#include "AlignmentOffsetLayoutLineFactory.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_AlignmentID(IDType id)
{
   m_Factory->SetAlignmentID(id);
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_AlignmentID(IDType* pID)
{
   CHECK_RETVAL(pID);
   *pID = m_Factory->GetAlignmentID();
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_LayoutLineID(IDType id)
{
   m_Factory->SetLayoutLineID(id);
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_LayoutLineID(IDType* pID)
{
   CHECK_RETVAL(pID);
   *pID = m_Factory->GetLayoutLineID();
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_LayoutLineIDIncrement(IDType idInc)
{
   m_Factory->SetLayoutLineIDIncrement(idInc);
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_LayoutLineIDIncrement(IDType* pIDInc)
{
   CHECK_RETVAL(pIDInc);
   *pIDInc = m_Factory->GetLayoutLineIDIncrement();
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_LayoutLineCount(IndexType nLayoutLines)
{
   m_Factory->SetLayoutLineCount(nLayoutLines);
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_LayoutLineCount(IndexType* pnLayoutLines)
{
   CHECK_RETVAL(pnLayoutLines);
   *pnLayoutLines = m_Factory->GetLayoutLineCount();
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_Offset(Float64 offset)
{
   m_Factory->SetOffset(offset);
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_Offset(Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   *pOffset = m_Factory->GetOffset();
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::put_OffsetIncrement(Float64 offsetInc)
{
   m_Factory->SetOffsetIncrement(offsetInc);
   return S_OK;
}

STDMETHODIMP CAlignmentOffsetLayoutLineFactory::get_OffsetIncrement(Float64* pOffsetInc)
{
   CHECK_RETVAL(pOffsetInc);
   *pOffsetInc = m_Factory->GetOffsetIncrement();
   return S_OK;
}


