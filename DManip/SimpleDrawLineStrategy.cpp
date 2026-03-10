///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <DManip/SimpleDrawLineStrategy.h>
#include <DManip/LineDisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>
#include <DManip/Connections.h>

#include "Helpers.h"

using namespace WBFL::DManip;

void SimpleDrawLineStrategy::Draw(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC) const
{
   Float64 sx,sy, ex,ey;
   GetPointsInWorldSpace(pDO,&sx,&sy,&ex,&ey);

   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   CPoint start, end;
   map->WPtoLP(sx,sy,&start.x,&start.y);
   map->WPtoLP(ex,ey,&end.x,&end.y);

   COLORREF color = m_crColor;
   if ( pDO->IsSelected() )
      color = pDO->GetDisplayList()->GetDisplayMgr()->GetSelectionLineColor();

   CPen pen;
   CreatePen(m_Style, m_nWidth, color, pen);

   CPen* oldPen = pDC->SelectObject(&pen);

   // Draw the main line
   pDC->MoveTo(start);
   pDC->LineTo(end);

   // Draw the beginning end
   {   
      CRect rect(start, start);
      rect.InflateRect(m_BeginSize,m_BeginSize);
      DrawPointSymbol(pDC, rect, m_BeginType);
   }

   // Draw the terminus end
   {
      CRect rect(end,end);
      rect.InflateRect(m_BeginSize, m_BeginSize);
      DrawPointSymbol(pDC, rect, m_EndType);
   }

   // Cleanup
   pDC->SelectObject(oldPen);
}

void SimpleDrawLineStrategy::DrawDragImage(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
}

void SimpleDrawLineStrategy::DrawHighlight(std::shared_ptr<const iLineDisplayObject> pDO,CDC* pDC,bool bHighlight) const
{
}

WBFL::Geometry::Rect2d SimpleDrawLineStrategy::GetBoundingBox(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   // the end points of this line are in Model Space
   // the need to be converted to World Space for the bounding box
   Float64 sx,sy, ex,ey;
   GetPointsInWorldSpace(pDO,&sx,&sy,&ex,&ey);

   return { Min(sx, ex), Min(sy, ey), Max(sx, ex), Max(sy, ey) };
}

/////////////////////////////////////////////////////////
// iSimpleLineDrawStrategy Implementation
void SimpleDrawLineStrategy::SetWidth(UINT nWidth)
{
   m_nWidth = nWidth;
}

UINT SimpleDrawLineStrategy::GetWidth() const
{
   return m_nWidth;
}

void SimpleDrawLineStrategy::SetColor(COLORREF crColor)
{
   m_crColor = crColor;
}

COLORREF SimpleDrawLineStrategy::GetColor() const
{
   return m_crColor;
}

void SimpleDrawLineStrategy::SetBeginType(PointType type)
{
   m_BeginType = type;
}

PointType SimpleDrawLineStrategy::GetBeginType() const
{
   return m_BeginType;
}

UINT SimpleDrawLineStrategy::GetBeginSize() const
{
   return m_BeginSize;
}

void SimpleDrawLineStrategy::SetBeginSize(UINT size)
{
   m_BeginSize = size;
}

void SimpleDrawLineStrategy::SetEndType(PointType type)
{
   m_EndType = type;
}

PointType SimpleDrawLineStrategy::GetEndType() const
{
   return m_EndType;
}

UINT SimpleDrawLineStrategy::GetEndSize() const
{
   return m_EndSize;
}

void SimpleDrawLineStrategy::SetEndSize(UINT size)
{
   m_EndSize = size;
}

void SimpleDrawLineStrategy::SetLineStyle(LineStyleType style)
{
   m_Style = style;
}

LineStyleType SimpleDrawLineStrategy::GetLineStyle() const
{
   return m_Style;
}

/////////////////////////////////

WBFL::Geometry::Point2d SimpleDrawLineStrategy::GetStartPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetStartPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}

WBFL::Geometry::Point2d SimpleDrawLineStrategy::GetEndPoint(std::shared_ptr<const iLineDisplayObject> pDO) const
{
   auto connector = std::dynamic_pointer_cast<const iConnector>(pDO);
   auto plug = connector->GetEndPlug();
   auto socket = plug->GetSocket();
   return socket->GetPosition();
}

void SimpleDrawLineStrategy::GetPointsInWorldSpace(std::shared_ptr<const iLineDisplayObject> pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey) const
{
   // the end points of this line are in Model Space
   // the need to be converted to World Space for the bounding box


   // start by getting the coordinate mapper
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   // get the points
   auto [start, end] = pDO->GetEndPoints();

   // convert them to world space
   map->MPtoWP(start.X(),start.Y(), sx, sy);
   map->MPtoWP(end.X(),end.Y(), ex, ey);
}
