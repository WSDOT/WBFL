///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <DManip/SimpleDrawDashedLineStrategy.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include <DManip/LineDisplayObject.h>
#include <DManip/Connections.h>

using namespace WBFL::DManip;

void SimpleDrawDashedLineStrategy::Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const
{
   Float64 sx,sy, ex,ey;
   GetPointsInWorldSpace(pDO,&sx,&sy,&ex,&ey);

   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   CPoint start, end;
   map->WPtoLP(sx,sy,&start.x,&start.y);
   map->WPtoLP(ex,ey,&end.x,&end.y);

   // Draw the dash color as a solid background line
   CPen bkPen(PS_SOLID,1,m_crColor2);
   CPen* oldPen = pDC->SelectObject(&bkPen);
   pDC->MoveTo(start);
   pDC->LineTo(end);

   // Setup the dash patter
   DWORD dashStyle[3];
   dashStyle[0] = m_dwDash;
   dashStyle[1] = m_dwDash;
   dashStyle[2] = m_dwDash;

   // Draw the primary color as a dashed line
   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = m_crColor1;
   lb.lbHatch = 0;
   CPen fgPen(PS_USERSTYLE | PS_GEOMETRIC,m_nWidth,&lb,sizeof(dashStyle)/sizeof(DWORD),dashStyle);

   pDC->SelectObject(&fgPen);

   // Draw the main line
   pDC->MoveTo(start);
   pDC->LineTo(end);

   // Cleanup
   pDC->SelectObject(oldPen);
}

void SimpleDrawDashedLineStrategy::DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
}

void SimpleDrawDashedLineStrategy::DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const
{
}

WBFL::Geometry::Rect2d SimpleDrawDashedLineStrategy::GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   // the end points of this line are in Model Space
   // the need to be converted to World Space for the bounding box
   Float64 sx,sy, ex,ey;
   GetPointsInWorldSpace(pDO,&sx,&sy,&ex,&ey);

   return { Min(sx, ex), Min(sy, ey), Max(sx, ex), Max(sy, ey) };
}

void SimpleDrawDashedLineStrategy::SetWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

UINT SimpleDrawDashedLineStrategy::GetWidth() const
{
   return m_nWidth;
}

void SimpleDrawDashedLineStrategy::SetColor1(COLORREF crColor)
{
   m_crColor1 = crColor;
}

COLORREF SimpleDrawDashedLineStrategy::GetColor1() const
{
   return m_crColor1;
}

void SimpleDrawDashedLineStrategy::SetColor2(COLORREF crColor)
{
   m_crColor2 = crColor;
}

COLORREF SimpleDrawDashedLineStrategy::GetColor2() const
{
   return m_crColor2;
}

void SimpleDrawDashedLineStrategy::SetDashLength(DWORD dwDash)
{
   m_dwDash = dwDash;
}

DWORD SimpleDrawDashedLineStrategy::GetDashLength() const
{
   return m_dwDash;
}

/////////////////////////////////

WBFL::Geometry::Point2d SimpleDrawDashedLineStrategy::GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetStartPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}

WBFL::Geometry::Point2d SimpleDrawDashedLineStrategy::GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetEndPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}

void SimpleDrawDashedLineStrategy::GetPointsInWorldSpace(std::shared_ptr<const iLineDisplayObject> pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey) const
{
   // the end points of this line are in Model Space
   // the need to be converted to World Space for the bounding box

   // start by getting the coordinate mapper
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   // get the points
   auto [start, end] = pDO->GetEndPoints();

   // convert them to world space
   map->MPtoWP(start.X(), start.Y(), sx, sy);
   map->MPtoWP(end.X(), end.Y(), ex, ey);
}
