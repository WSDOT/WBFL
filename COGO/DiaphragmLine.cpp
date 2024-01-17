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
#include "DiaphragmLine.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CDiaphragmLine
STDMETHODIMP CDiaphragmLine::get_ID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_DiaphragmLine->GetID();
   return S_OK;
}

STDMETHODIMP CDiaphragmLine::get_Length(IDType gdrLineID, Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_DiaphragmLine->Length(gdrLineID);
   return S_OK;
}

STDMETHODIMP CDiaphragmLine::get_Point(IDType gdrLineID, EndType endType, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_DiaphragmLine->GetPoint(gdrLineID, WBFL::COGO::EndType(endType)), ppPoint);
}

