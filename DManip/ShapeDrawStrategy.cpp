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
#include <DManip/ShapeDrawStrategy.h>
#include <DManip/PointDisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>
#include <DManip/CoordinateMap.h>

#include "Helpers.h"

using namespace WBFL::DManip;


ShapeDrawStrategy::ShapeDrawStrategy(std::shared_ptr<const WBFL::Geometry::Shape> shape)
{
   SetShape(shape);
}


void ShapeDrawStrategy::SetShape(std::shared_ptr<const WBFL::Geometry::Shape> shape)
{
   m_Shape = shape;
   m_CompositeShape = std::dynamic_pointer_cast<const WBFL::Geometry::CompositeShape>(m_Shape);
   m_BoundingBox.reset();
}

std::shared_ptr<const WBFL::Geometry::Shape> ShapeDrawStrategy::GetShape() const
{
   return m_Shape;
}

void ShapeDrawStrategy::SetSolidLineStyle(LineStyleType lineStyle)
{
   m_SolidLineStyle = lineStyle;
}

LineStyleType ShapeDrawStrategy::GetSolidLineStyle() const
{
   return m_SolidLineStyle;
}

void ShapeDrawStrategy::SetSolidLineColor(COLORREF crColor)
{
   m_SolidLineColor = crColor;
}

COLORREF ShapeDrawStrategy::GetSolidLineColor() const
{
   return m_SolidLineColor;
}

void ShapeDrawStrategy::SetSolidFillColor(COLORREF crColor)
{
   m_SolidFillColor = crColor;
}

COLORREF ShapeDrawStrategy::GetSolidFillColor() const
{
   return m_SolidFillColor;
}

void ShapeDrawStrategy::SetSolidLineWidth(UINT nPixels)
{
   m_SolidLineWidth = nPixels;
}

UINT ShapeDrawStrategy::GetSolidLineWidth() const
{
   return m_SolidLineWidth;
}

void ShapeDrawStrategy::SetVoidLineStyle(LineStyleType lineStyle)
{
   m_VoidLineStyle = lineStyle;
}

LineStyleType ShapeDrawStrategy::GetVoidLineStyle() const
{
   return m_VoidLineStyle;
}

void ShapeDrawStrategy::SetVoidLineColor(COLORREF crColor)
{
   m_VoidLineColor = crColor;
}

COLORREF ShapeDrawStrategy::GetVoidLineColor() const
{
   return m_VoidLineColor;
}

void ShapeDrawStrategy::SetVoidFillColor(COLORREF crColor)
{
   m_VoidFillColor = crColor;
}

COLORREF ShapeDrawStrategy::GetVoidFillColor() const
{
   return m_VoidFillColor;
}

void ShapeDrawStrategy::SetVoidLineWidth(UINT nPixels)
{
   m_VoidLineWidth = nPixels;
}

UINT ShapeDrawStrategy::GetVoidLineWidth() const
{
   return m_VoidLineWidth;
}

void ShapeDrawStrategy::Fill(bool bFill)
{
   m_bFill = bFill;
}

bool ShapeDrawStrategy::Fill() const
{
   return m_bFill;
}

void ShapeDrawStrategy::HasBoundingShape(bool bHasBoundingShape)
{
   m_bHasBoundingShape = bHasBoundingShape;
}

bool ShapeDrawStrategy::HasBoundingShape() const
{
   return m_bHasBoundingShape;
}

void ShapeDrawStrategy::Draw(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC) const
{
   DrawMe(pDO, pDC, false);
}

void ShapeDrawStrategy::DrawHighlight(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const
{
   DrawMe(pDO, pDC, bHighlight);
}

void ShapeDrawStrategy::DrawDragImage(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, const std::shared_ptr < const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) const
{
   ATLASSERT(false); // not implemented
//   map->LPtoWP(dragPoint.x, dragPoint.y, &m_CachePoint);
//
//   CRect r = pDO->GetBoundingBox();
//
//   COLORREF color;
//   color = RGB(0,0,255);
//
//   CPen pen(PS_SOLID,1,color);
//   CPen* pOldPen = pDC->SelectObject(&pen);
//   DrawMe(r,pDC);
//   pDC->SelectObject(pOldPen);
}

WBFL::Geometry::Rect2d ShapeDrawStrategy::GetBoundingBox(std::shared_ptr<const iPointDisplayObject> pDO) const
{
   if (m_BoundingBox.has_value())
   {
      return m_BoundingBox.value();
   }

   if (m_Shape == nullptr)
   {
      auto point = pDO->GetPosition();
      auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

      // map the point to world space
      auto p = map->MPtoWP(point);
      m_BoundingBox.emplace(WBFL::Geometry::Rect2d(p,WBFL::Geometry::Size2d()));
      return m_BoundingBox.value();
   }


   if (m_bHasBoundingShape)
   {
      auto points = GetPointsInWorldSpace(pDO, m_Shape);

      Float64 left = DBL_MAX;
      Float64 right = -DBL_MAX;
      Float64 top = -DBL_MAX;
      Float64 bottom = DBL_MAX;
      for(auto& point : points)
      {
         auto [x, y] = point.GetLocation();

         left = Min(left, x);
         right = Max(right, x);

         top = Max(top, y);
         bottom = Min(bottom, y);
      }

      m_BoundingBox.emplace(WBFL::Geometry::Rect2d( left,bottom,right,top ));
   }
   else
   {
      auto bbox = m_Shape->GetBoundingBox();
      m_BoundingBox.emplace(bbox);
   }
   return m_BoundingBox.value();
}

/////////////////////////////////////////////////////////
// iGravityWellStrategy Implementation
void ShapeDrawStrategy::GetGravityWell(std::shared_ptr<const iDisplayObject> pDO, CRgn* pRgn)
{
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();
   std::shared_ptr<const WBFL::Geometry::Shape> shape;
   if (m_CompositeShape)
   {
      shape = m_CompositeShape->GetShape(0);
   }
   else
   {
      shape = m_Shape;
   }

   auto polypoints = GetPointsInWorldSpace(pDO, shape);

   CPoint* points = new CPoint[polypoints.size()];
   IndexType i = 0;
   for(auto& point : polypoints)
   {
      map->WPtoLP(point, &points[i].x, &points[i].y);
      i++;
   }

   VERIFY(pRgn->CreatePolygonRgn(points, (int)polypoints.size(), ALTERNATE));

   delete[] points;
}

void ShapeDrawStrategy::DrawMe(std::shared_ptr<const iPointDisplayObject> pDO, CDC* pDC, bool bHighlight) const
{
   COLORREF line_color;
   COLORREF fill_color;

   auto bIsSelected = pDO->IsSelected();

   if (bIsSelected || bHighlight)
   {
      auto disp_mgr = pDO->GetDisplayList()->GetDisplayMgr();
      line_color = disp_mgr->GetSelectionLineColor();
      fill_color = disp_mgr->GetSelectionFillColor();
   }
   else
   {
      line_color = m_SolidLineColor;
      fill_color = m_SolidFillColor;
   }

   CPen solid_pen;
   CreatePen(m_SolidLineStyle, m_SolidLineWidth, line_color, solid_pen);

   CBrush solid_brush;
   if (bIsSelected)
   {
      solid_brush.CreateHatchBrush(HS_DIAGCROSS, fill_color);
   }
   else
   {
      solid_brush.CreateSolidBrush(fill_color);
   }

   CPen void_pen;
   CreatePen(m_VoidLineStyle, m_VoidLineWidth, m_VoidLineColor, void_pen);

   CBrush void_brush(m_VoidFillColor);

   CPen* pOldPen = pDC->SelectObject(&solid_pen);
   CBrush* pOldBrush;

   if (bHighlight)
   {
      // Highlightd always uses nullptr brush (not filled)
      pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
   }
   else
   {
      if (m_bFill)
      {
         pOldBrush = pDC->SelectObject(&solid_brush);
      }
      else
      {
         pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
      }
   }


   if (m_CompositeShape)
   {
      DrawShape(pDO, pDC, m_CompositeShape, solid_pen, solid_brush, void_pen, void_brush);
   }
   else
   {
      DrawShape(pDO, pDC, m_Shape);
   }


   pDC->SelectObject(pOldPen);
   pDC->SelectObject(pOldBrush);
}

void ShapeDrawStrategy::DrawShape(std::shared_ptr<const iDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::Geometry::CompositeShape> compositeShape, CPen& solidPen, CBrush& solidBrush, CPen& voidPen, CBrush& voidBrush) const
{
   IndexType nShapes = compositeShape->GetShapeCount();
   for (IndexType idx = 0; idx < nShapes; idx++)
   {
      const auto& shape = compositeShape->GetShape(idx);

      if (compositeShape->IsVoid(idx))
      {
         pDC->SelectObject(&voidPen);

         if (m_bFill)
            pDC->SelectObject(&voidBrush);
         else
            pDC->SelectStockObject(NULL_BRUSH);
      }
      else
      {
         pDC->SelectObject(&solidPen);

         if (m_bFill)
            pDC->SelectObject(&solidBrush);
         else
            pDC->SelectStockObject(NULL_BRUSH);
      }

      std::shared_ptr<const WBFL::Geometry::CompositeShape> composite = std::dynamic_pointer_cast<const WBFL::Geometry::CompositeShape>(shape);
      if (composite)
      {
         DrawShape(pDO, pDC, composite, solidPen, solidBrush, voidPen, voidBrush);
      }
      else
      {
         DrawShape(pDO, pDC, shape);
      }
   }
}

void ShapeDrawStrategy::DrawShape(std::shared_ptr<const iDisplayObject> pDO, CDC* pDC, std::shared_ptr<const WBFL::Geometry::Shape> shape) const
{
   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   auto polypoints = GetPointsInWorldSpace(pDO, shape);

   CPoint* points = new CPoint[polypoints.size()];
   IndexType i = 0;
   for(auto& point : polypoints)
   {
      map->WPtoLP(point, &points[i].x, &points[i].y);
      i++;
   }

   pDC->Polygon(points, (int)polypoints.size());

   delete[] points;
}

std::vector<WBFL::Geometry::Point2d> ShapeDrawStrategy::GetPointsInWorldSpace(std::shared_ptr<const iDisplayObject> pDO, std::shared_ptr<const WBFL::Geometry::Shape> shape) const
{
   std::vector<WBFL::Geometry::Point2d> points;

   auto map = pDO->GetDisplayList()->GetDisplayMgr()->GetCoordinateMap();

   auto poly_points = shape->GetPolyPoints();
   for(const auto& point : poly_points)
   {
      Float64 wx, wy;
      map->MPtoWP(point.X(),point.Y(), &wx, &wy);
      points.push_back({ wx,wy });
   }
   return points;
}
