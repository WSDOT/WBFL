///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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
#include <DManip/PolyLineDisplayObjectImpl.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>

#include "Helpers.h"

using namespace WBFL::DManip;

PolyLineDisplayObject::PolyLineDisplayObject(IDType id) : iPolyLineDisplayObject(id)
{
}

void PolyLineDisplayObject::Draw(CDC* pDC)
{
   if (!IsVisible()) return; // don't draw if not visible

   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   CPen pen(PS_SOLID, m_Width, m_Color);
   CPen* pOldPen = pDC->SelectObject(&pen);

   auto iter = m_Points.begin();
   auto end = m_Points.end();
   auto& point(*iter);
   LONG lx, ly;
   map->WPtoLP(map->MPtoWP(point), &lx, &ly);
   pDC->MoveTo(lx, ly);
   DrawPoint(pDC, lx, ly);
   iter++;
   for (; iter != end; iter++)
   {
      map->WPtoLP(map->MPtoWP(*iter), &lx, &ly);
      pDC->LineTo(lx, ly);
      DrawPoint(pDC, lx, ly);
   }

   pDC->SelectObject(pOldPen);
}

void PolyLineDisplayObject::Highlight(CDC* pDC, bool bHighlight)
{
   Draw(pDC);
}

WBFL::Geometry::Rect2d PolyLineDisplayObject::GetBoundingBox() const
{
   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   Float64 xmin = DBL_MAX;
   Float64 xmax = -DBL_MAX;
   Float64 ymin = DBL_MAX;
   Float64 ymax = -DBL_MAX;
   std::for_each(m_Points.cbegin(), m_Points.cend(), [map,&xmin, &xmax, &ymin, &ymax](const auto& p)
      {
         auto wp = map->MPtoWP(p); // convert from model space to world space
         xmin = Min(xmin, wp.X());
         xmax = Max(xmax, wp.X());
         ymin = Min(ymin, wp.Y());
         ymax = Max(ymax, wp.Y());
      });

   return { xmin,ymin,xmax,ymax };
}

void PolyLineDisplayObject::SetPoints(const std::vector<WBFL::Geometry::Point2d>& points)
{
   m_Points = points;
}

void PolyLineDisplayObject::AddPoints(const std::vector<WBFL::Geometry::Point2d>& points)
{
   m_Points.insert(m_Points.end(), points.begin(), points.end());
}

void PolyLineDisplayObject::AddPoint(const WBFL::Geometry::Point2d& point)
{
   m_Points.push_back(point);
}

void PolyLineDisplayObject::InsertPoint(IndexType idx, const WBFL::Geometry::Point2d& point)
{
   m_Points.insert(m_Points.begin() + idx, point);
}

const WBFL::Geometry::Point2d& PolyLineDisplayObject::GetPoint(IndexType idx) const
{
   return m_Points[idx];
}

void PolyLineDisplayObject::RemovePoint(IndexType idx)
{
   m_Points.erase(m_Points.begin() + idx);
}

IndexType PolyLineDisplayObject::GetPointCout() const
{
   return m_Points.size();
}

void PolyLineDisplayObject::ClearPoints()
{
   m_Points.clear();
}

void PolyLineDisplayObject::SetColor(COLORREF color)
{
   m_Color = color;
}

COLORREF PolyLineDisplayObject::GetColor() const
{
   return m_Color;
}

void PolyLineDisplayObject::SetWidth(unsigned width)
{
   m_Width = width;
}

unsigned PolyLineDisplayObject::GetWidth() const
{
   return m_Width;
}

void PolyLineDisplayObject::SetPointType(PointType ptType)
{
   m_PointType = ptType;
}

PointType PolyLineDisplayObject::GetPointType() const
{
   return m_PointType;
}

void PolyLineDisplayObject::SetPointSize(UINT size)
{
   m_Size = size;
}

UINT PolyLineDisplayObject::GetPointSize() const
{
   return m_Size;
}

void PolyLineDisplayObject::DrawPoint(CDC* pDC, LONG lx, LONG ly)
{
   CRect rect(lx, ly, lx, ly);
   rect.InflateRect(m_Size, m_Size);
   DrawPointSymbol(pDC, rect, m_PointType);
}
