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
#include <DManip/SimpleDrawPointStrategy.h>
#include <DManip/PointDisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <MathEx.h>
#include <Colors.h>
#include "Helpers.h"

using namespace WBFL::DManip;

void SimpleDrawPointStrategy::SetColor(COLORREF crColor)
{
   m_Color = crColor;
}

COLORREF SimpleDrawPointStrategy::GetColor() const
{
   return m_Color;
}

void SimpleDrawPointStrategy::SetPointType(PointType type)
{
   m_Type = type;
}

PointType SimpleDrawPointStrategy::GetPointType() const
{
   return m_Type;
}

void SimpleDrawPointStrategy::SetPointSize(Float64 size)
{
   m_bIsLogicalPoint = false;
   m_Size = size;
}

Float64 SimpleDrawPointStrategy::GetPointSize() const
{
   return m_Size;
}

void SimpleDrawPointStrategy::SetLogicalPointSize(int size)
{
   m_bIsLogicalPoint = true;
   m_LogicalSize = size;
}

int SimpleDrawPointStrategy::GetLogicalPointSize() const
{
   return m_LogicalSize;
}

bool SimpleDrawPointStrategy::UsesLogicalPointSize() const
{
   return m_bIsLogicalPoint;
}

void SimpleDrawPointStrategy::Draw(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC) const
{
   CRect r = GetPointBox(pDO);
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();

   COLORREF line_color, fill_color;
   if ( pDO->IsSelected() )
   {
      line_color = pDispMgr->GetSelectionLineColor();
      fill_color = pDispMgr->GetSelectionFillColor();
   }
   else
   {
      line_color = m_Color;
      fill_color = m_Color;
   }

   CPen pen(PS_SOLID,1,line_color);
   CPen* pOldPen = pDC->SelectObject(&pen);

   CBrush brush(fill_color);
   CBrush* pOldBrush = pDC->SelectObject(&brush);

   DrawMe(r,pDC);

   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}

void SimpleDrawPointStrategy::DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC,bool bHighlight) const
{
   CRect r = GetPointBox(pDO);

   COLORREF color = LIME;

   UINT nWidth = bHighlight ? 2 : 1;
   CPen pen(PS_SOLID,nWidth,color);
   CPen* pOldPen = pDC->SelectObject(&pen);
   DrawMe(r,pDC);
   pDC->SelectObject(pOldPen);
}

void SimpleDrawPointStrategy::DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO,CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
   m_CachePoint = map->LPtoWP(dragPoint.x, dragPoint.y);

   CRect r = GetPointBox(pDO);

   COLORREF color = BLUE;

   CPen pen(PS_SOLID,1,color);
   CPen* pOldPen = pDC->SelectObject(&pen);
   DrawMe(r,pDC);
   pDC->SelectObject(pOldPen);
}

WBFL::Geometry::Rect2d SimpleDrawPointStrategy::GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   auto point = GetPointInWorldSpace(pDO);

   WBFL::Geometry::Rect2d bounding_box;

   if ( IsZero(m_Size) )
   {
      // make 4x4 logical size
      auto pDL = pDO->GetDisplayList();
      auto pDispMgr = pDL->GetDisplayMgr();
      auto pMap = pDispMgr->GetCoordinateMap();

      Float64 xo,yo;
      pMap->LPtoWP(0,0,&xo,&yo);
      Float64 x2,y2;
      pMap->LPtoWP(2,2,&x2,&y2);

      Float64 wid = fabs(x2-xo);
      Float64 hgt = fabs(y2-yo);
      bounding_box.Left() = point.X() - wid;
      bounding_box.Bottom() = point.Y() - hgt;
      bounding_box.Right() = point.X() + wid;
      bounding_box.Top() = point.Y() + hgt;
   }
   else
   {
      Float64 left   = point.X() - m_Size / 2;
      Float64 right  = point.X() + m_Size / 2;
      Float64 top    = point.Y() + m_Size / 2;
      Float64 bottom = point.Y() - m_Size / 2;

      bounding_box.Left() = left;
      bounding_box.Bottom() = bottom;
      bounding_box.Right() = right;
      bounding_box.Top() = top;
   }

   return bounding_box;
}


void SimpleDrawPointStrategy::DrawMe(const CRect& rect,CDC* pDC) const
{
   // sometimes mapping skews the shape... clean that up here
   int width = rect.Width();
   int height = rect.Height();

   CRect r(rect);

   if ( width < height )
   {
      int cx = r.CenterPoint().x;
      r.left  = cx - height/2;      
      r.right = cx + height/2;      
   }
   else if ( height < width )
   {
      int cy = r.CenterPoint().y;
      r.top    = cy - width/2;
      r.bottom = cy + width/2;
   }

   DrawPointSymbol(pDC, r, m_Type);
}

WBFL::Geometry::Point2d SimpleDrawPointStrategy::GetPointInWorldSpace(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   // this is the point in Model Space
   const auto& point = pDO->GetPosition();

   // get the coordinate map
   auto pDL = pDO->GetDisplayList();
   auto pDispMgr = pDL->GetDisplayMgr();
   auto pMap = pDispMgr->GetCoordinateMap();

   // map the point to world space
   return pMap->MPtoWP(point);
}

CRect SimpleDrawPointStrategy::GetPointBox(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   CRect rect;
   if (m_bIsLogicalPoint)
   {
      auto point = GetPointInWorldSpace(pDO);

      auto pDL = pDO->GetDisplayList();
      auto pDispMgr = pDL->GetDisplayMgr();
      auto pMap = pDispMgr->GetCoordinateMap();

      LONG x, y;
      pMap->WPtoLP(point, &x, &y);

      rect.left = x - m_LogicalSize / 2;
      rect.right = rect.left + m_LogicalSize;
      rect.top = y - m_LogicalSize / 2;
      rect.bottom = rect.top + m_LogicalSize;
   }
   else
   {
      rect = pDO->GetLogicalBoundingBox();
   }

   return rect;
}