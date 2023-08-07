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

// DiaphragmLine.cpp : Implementation of CDiaphragm

#include "stdafx.h"
#include "WBFLCogo.h"
#include "ThroughPointDiaphragmLineFactory.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_Point(IPoint2d* point)
{
   CHECK_IN(point);
   m_Factory->SetPoint(cogoUtil::GetPoint(point));
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_Point(IPoint2d** point)
{
   CHECK_RETOBJ(point);
   return cogoUtil::CreatePoint(m_Factory->GetPoint(), point);
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_Direction(VARIANT varDirection)
{
   auto [hr,direction] = cogoUtil::DirectionFromVariant(varDirection);
   if (FAILED(hr)) return hr;
   m_Factory->SetDirection(direction);
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_Direction(IDirection** direction)
{
   CHECK_RETOBJ(direction);
   return cogoUtil::CreateDirection(m_Factory->GetDireciton(), direction);
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_DiaphragmLineID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Factory->GetDiaphragmLineID();
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_DiaphragmLineID(IDType newVal)
{
   m_Factory->SetDiaphragmLineID(newVal);
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_Staggered(VARIANT_BOOL bStaggered)
{
   m_Factory->IsStaggered(bStaggered == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_Staggered(VARIANT_BOOL* bStaggered)
{
   CHECK_RETVAL(bStaggered);
   *bStaggered = m_Factory->IsStaggered() ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_LeftGirderLineID(IDType ID)
{
   m_Factory->SetGirderLineID(WBFL::COGO::SideType::Left, ID);
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_LeftGirderLineID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetGirderLineID(WBFL::COGO::SideType::Left);
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::put_RightGirderLineID(IDType ID)
{
   m_Factory->SetGirderLineID(WBFL::COGO::SideType::Right, ID);
   return S_OK;
}

STDMETHODIMP CThroughPointDiaphragmLineFactory::get_RightGirderLineID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetGirderLineID(WBFL::COGO::SideType::Right);
   return S_OK;
}

