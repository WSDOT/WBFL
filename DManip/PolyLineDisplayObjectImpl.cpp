///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

   COLORREF line_color;
   if (IsSelected())
   {
      auto disp_mgr = GetDisplayList()->GetDisplayMgr();
      line_color = disp_mgr->GetSelectionLineColor();
   }
   else
   {
      line_color = m_Color;
   }

   CPen pen(PS_SOLID, m_Width, line_color);
   CPen* pOldPen = pDC->SelectObject(&pen);

   auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

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

bool PolyLineDisplayObject::HitTest(const POINT& point) const
{
   if (m_Points.empty())
   {
      return false;
   }

   if (m_pGravityWellStrategy)
   {
      // If there is a gravity well, use the default hit test implementation
      return __super::HitTest(point);
   }
   else
   {
      // Otherwise, use this strategy
      // Return true if the distance between the point and any line segment is less than the line width
      auto map = GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

      // Get line width threshold in model coords
      LONG lwid = max(4, m_Width);

      // Width in model space
      Float64 wxo, wyo;
      map->LPtoWP(0, 0, &wxo, &wyo);
      Float64 wx2, wy2;
      map->LPtoWP(lwid, lwid, &wx2, &wy2);
      Float64 mxo, myo;
      map->WPtoMP(wxo, wyo, &mxo, &myo);
      Float64 mx2, my2;
      map->WPtoMP(wx2, wy2, &mx2, &my2);

      Float64 threshold = abs(mx2 - mxo); // just use distance along x

      // Convert target point to model coords
      WBFL::Geometry::Point2d wpoint = map->LPtoWP(point.x, point.y);
      Float64 mx, my;
      map->WPtoMP(wpoint, &mx, &my);
      WBFL::Geometry::Point2d mpoint(mx, my);

      // Iterate over all segments to test for a hit
      std::vector<WBFL::Geometry::Point2d>::const_iterator startPointIter = m_Points.begin();
      std::vector<WBFL::Geometry::Point2d>::const_iterator endPointIter = startPointIter;
      while (++endPointIter != m_Points.end())
      {
         // First need to use a line to get nearest point along an infinite line
         const WBFL::Geometry::Point2d& startPoint(*startPointIter);
         const WBFL::Geometry::Point2d& endPoint(*endPointIter);

         if (startPoint != endPoint) // Line2d will throw below if we have equal points
         {
            WBFL::Geometry::Line2d line(startPoint, endPoint);

            WBFL::Geometry::Point2d closestPoint = WBFL::Geometry::GeometricOperations::PointOnLineNearest(line, mpoint);
            Float64 dist = mpoint.Distance(closestPoint);
            if (dist < threshold)
            {
               // Point is close enough to an infinite line. Now we need to see if it's along our segment
               WBFL::Geometry::LineSegment2d lineSeg(startPoint.X(), startPoint.Y(), endPoint.X(), endPoint.Y());
               if (WBFL::Geometry::GeometricOperations::DoesLineSegmentContainPoint(lineSeg, closestPoint, 0.01)) // assuming metric, and a mm is close enough
               {
                  return true;
               }
            }
         }

         startPointIter = endPointIter;
      }
   }

   return false;
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
