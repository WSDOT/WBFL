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

// GirderLine.cpp : Implementation of CGirder

#include "stdafx.h"
#include "WBFLCogo.h"
#include "GirderLine.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CGirderLine
STDMETHODIMP CGirderLine::get_ID(IDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_GirderLine->GetID();
   return S_OK;
}

STDMETHODIMP CGirderLine::get_StartPier(IPierLine** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePierLine(WBFL::COGO::PierLine::Create(*m_GirderLine->GetPierLine(WBFL::COGO::EndType::Start)), pVal);
}

STDMETHODIMP CGirderLine::get_EndPier(IPierLine** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePierLine(WBFL::COGO::PierLine::Create(*m_GirderLine->GetPierLine(WBFL::COGO::EndType::End)), pVal);
}

STDMETHODIMP CGirderLine::get_GirderLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_GirderLine->GetGirderLength();
   return S_OK;
}

STDMETHODIMP CGirderLine::get_SpanLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_GirderLine->GetSpanLength();
   return S_OK;
}

STDMETHODIMP CGirderLine::get_LayoutLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_GirderLine->GetLayoutLength();
   return S_OK;
}

STDMETHODIMP CGirderLine::get_PierPoint(EndType endType, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_GirderLine->GetPierPoint(WBFL::COGO::EndType(endType)), ppPoint);
}

STDMETHODIMP CGirderLine::get_BearingPoint(EndType endType, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_GirderLine->GetBearingPoint(WBFL::COGO::EndType(endType)), ppPoint);
}

STDMETHODIMP CGirderLine::get_EndPoint(EndType endType, IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreatePoint(m_GirderLine->GetEndPoint(WBFL::COGO::EndType(endType)), ppPoint);
}

STDMETHODIMP CGirderLine::GetEndPoints(IPoint2d** pntPier1, IPoint2d** pntEnd1, IPoint2d** pntBrg1, IPoint2d** pntBrg2, IPoint2d** pntEnd2, IPoint2d** pntPier2)
{
   CHECK_RETOBJ(pntPier1);
   CHECK_RETOBJ(pntEnd1);
   CHECK_RETOBJ(pntBrg1);
   CHECK_RETOBJ(pntBrg2);
   CHECK_RETOBJ(pntEnd2);
   CHECK_RETOBJ(pntPier2);

   cogoUtil::CreatePoint(m_GirderLine->GetPierPoint(WBFL::COGO::EndType::Start), pntPier1);
   cogoUtil::CreatePoint(m_GirderLine->GetEndPoint(WBFL::COGO::EndType::Start), pntEnd1);
   cogoUtil::CreatePoint(m_GirderLine->GetBearingPoint(WBFL::COGO::EndType::Start), pntBrg1);

   cogoUtil::CreatePoint(m_GirderLine->GetBearingPoint(WBFL::COGO::EndType::End), pntBrg2);
   cogoUtil::CreatePoint(m_GirderLine->GetEndPoint(WBFL::COGO::EndType::End), pntEnd2);
   cogoUtil::CreatePoint(m_GirderLine->GetPierPoint(WBFL::COGO::EndType::End), pntPier2);

   return S_OK;
}

STDMETHODIMP CGirderLine::get_Path(IPath** pVal)
{
   CHECK_RETOBJ(pVal);
   return cogoUtil::CreatePath(WBFL::COGO::Path::Create(*m_GirderLine->GetPath()), pVal);
}

STDMETHODIMP CGirderLine::get_Direction(IDirection** ppDirection)
{
   CHECK_RETOBJ(ppDirection);
   return cogoUtil::CreateDirection(m_GirderLine->GetDirection(), ppDirection);
}

STDMETHODIMP CGirderLine::get_BearingOffset(EndType endType, Float64* pBrgOffset)
{
   CHECK_RETVAL(pBrgOffset);
   *pBrgOffset = m_GirderLine->GetBearingOffset(WBFL::COGO::EndType(endType));
   return S_OK;
}

STDMETHODIMP CGirderLine::get_EndDistance(EndType endType, Float64* pEndDist)
{
   CHECK_RETVAL(pEndDist);
   *pEndDist = m_GirderLine->GetEndDistance(WBFL::COGO::EndType(endType));
   return S_OK;
}


