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

// DeckBoundary.cpp : Implementation of CDiaphragm

#include "stdafx.h"
#include "WBFLCogo.h"
#include "DeckBoundary.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CDeckBoundary
STDMETHODIMP CDeckBoundary::get_Perimeter(IndexType nMinPointsPerSide, IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);
   return cogoUtil::CreatePoints(m_DeckBoundary->GetPerimeter(nMinPointsPerSide), points);
}

STDMETHODIMP CDeckBoundary::get_PerimeterEx(IndexType nMinPointsPerSide, IDType startPierID, Float64 Xstart, IDType endPierID, Float64 Xend, VARIANT_BOOL bParallelToPiers, IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);
   return cogoUtil::CreatePoints(m_DeckBoundary->GetPerimeter(nMinPointsPerSide, startPierID, Xstart, endPierID, Xend, bParallelToPiers == VARIANT_TRUE), points);
}

STDMETHODIMP CDeckBoundary::get_TransverseEdgePoints(EndType endType, IPoint2d** ppLeft, IPoint2d** ppLeftBreak, IPoint2d** ppRightBreak, IPoint2d** ppRight)
{
   CHECK_RETOBJ(ppLeft);
   CHECK_RETOBJ(ppLeftBreak);
   CHECK_RETOBJ(ppRightBreak);
   CHECK_RETOBJ(ppRight);

   auto points = m_DeckBoundary->GetTransverseEdgePoints(WBFL::COGO::EndType(endType));
   cogoUtil::CreatePoint(points[0], ppLeft);
   cogoUtil::CreatePoint(points[1], ppLeftBreak);
   cogoUtil::CreatePoint(points[2], ppRightBreak);
   cogoUtil::CreatePoint(points[3], ppRight);

   return S_OK;
}

STDMETHODIMP CDeckBoundary::get_EdgePath(SideType side, VARIANT_BOOL vbLayoutPath, IPath** ppPath)
{
   CHECK_RETOBJ(ppPath);
   return cogoUtil::CreatePath(WBFL::COGO::Path::Create(*m_DeckBoundary->GetEdgePath(WBFL::COGO::SideType(side), vbLayoutPath == VARIANT_TRUE)), ppPath);
}

