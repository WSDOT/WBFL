///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/BoxBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <array>
#include <MathEx.h>

using namespace WBFL::Geometry;

BoxBeam::BoxBeam() :
   ShapeOnCompositeImpl()
{
}

BoxBeam::BoxBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 h1, Float64 h2, Float64 h3, Float64 h4, Float64 h5, Float64 h6, Float64 h7, Float64 f1, Float64 f2, Float64 f3, Float64 c1, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, const Point2d& hookPnt) :
ShapeOnCompositeImpl(hookPnt), m_W1(w1),m_W2(w2),m_W3(w3),m_W4(w4), m_H1(h1), m_H2(h2), m_H3(h3), m_H4(h4), m_H5(h5), m_H6(h6), m_H7(h7), m_F1(f1),m_F2(f2),m_F3(f3),m_C1(c1), m_nVoids(nVoids), m_bLeftBlockout(bLeftBlockout),m_bRightBlockout(bRightBlockout)
{
}

BoxBeam::~BoxBeam()
{
}

void BoxBeam::SetW1(Float64 w1) { m_W1 = w1; SetDirtyFlag(); }
Float64 BoxBeam::GetW1() const { return m_W1; }

void BoxBeam::SetW2(Float64 w2) { m_W2 = w2; SetDirtyFlag(); }
Float64 BoxBeam::GetW2() const { return m_W2; }

void BoxBeam::SetW3(Float64 w3) { m_W3 = w3; SetDirtyFlag(); }
Float64 BoxBeam::GetW3() const { return m_W3; }

void BoxBeam::SetW4(Float64 w4) { m_W4 = w4; SetDirtyFlag(); }
Float64 BoxBeam::GetW4() const { return m_W4; }

void BoxBeam::SetH1(Float64 h1) { m_H1 = h1; SetDirtyFlag(); }
Float64 BoxBeam::GetH1() const { return m_H1; }

void BoxBeam::SetH2(Float64 h2) { m_H2 = h2; SetDirtyFlag(); }
Float64 BoxBeam::GetH2() const { return m_H2; }

void BoxBeam::SetH3(Float64 h3) { m_H3 = h3; SetDirtyFlag(); }
Float64 BoxBeam::GetH3() const { return m_H3; }

void BoxBeam::SetH4(Float64 h4) { m_H4 = h4;  SetDirtyFlag(); }
Float64 BoxBeam::GetH4() const { return m_H4; }

void BoxBeam::SetH5(Float64 h5) { m_H5 = h5;  SetDirtyFlag(); }
Float64 BoxBeam::GetH5() const { return m_H5; }

void BoxBeam::SetH6(Float64 h6) { m_H6 = h6;  SetDirtyFlag(); }
Float64 BoxBeam::GetH6() const { return m_H6; }

void BoxBeam::SetH7(Float64 h7) { m_H7 = h7;  SetDirtyFlag(); }
Float64 BoxBeam::GetH7() const { return m_H7; }

void BoxBeam::SetF1(Float64 f1) { m_F1 = f1;  SetDirtyFlag(); }
Float64 BoxBeam::GetF1() const { return m_F1; }

void BoxBeam::SetF2(Float64 f2) { m_F2 = f2;  SetDirtyFlag(); }
Float64 BoxBeam::GetF2() const { return m_F2; }

void BoxBeam::SetC1(Float64 c1) { m_C1 = c1;  SetDirtyFlag(); }
Float64 BoxBeam::GetC1() const { return m_C1; }

void BoxBeam::SetVoidCount(IndexType nVoids) { m_nVoids = nVoids;  SetDirtyFlag(); }
IndexType BoxBeam::GetVoidCount() const { return m_nVoids; }

void BoxBeam::SetLeftBlockout(bool bBlockout) { m_bLeftBlockout = bBlockout;  SetDirtyFlag(); }
bool BoxBeam::GetLeftBlockout() const { return m_bLeftBlockout; }

void BoxBeam::SetRightBlockout(bool bBlockout) { m_bRightBlockout = bBlockout;  SetDirtyFlag(); }
bool BoxBeam::GetRightBlockout() const { return m_bRightBlockout; }

Float64 BoxBeam::GetWebWidth() const
{
   bool bSmallShearKey = (m_W1 < m_W2 / 2 || m_W4 < m_W2 / 2) ? true : false;
   bool bShearKeyAtTop = (m_H4 < m_H1&& m_H2 + m_H3 - m_F1 < m_H7) ? true : false;
   bool bShearKeyAtBottom = (m_H7 < m_H3&& m_H1 + m_H2 - m_F2 < m_H4) ? true : false;

   Float64 wWeb = -99999;
   if (bSmallShearKey && bShearKeyAtTop)
      wWeb = 2.0 * (m_W2 + m_W4);
   else if (bSmallShearKey && bShearKeyAtBottom)
      wWeb = 2.0 * (m_W1 + m_W2);
   else
      wWeb = 2.0 * m_W2;

   return wWeb;
}

void BoxBeam::GetBottomFlangeWidth(Float64* left, Float64* right) const
{
   Float64 val = m_W4 + m_W2 + m_W3 / 2.0;
   *left = val;
   *right = val;
}

void BoxBeam::GetTopFlangeWidth(Float64* left, Float64* right) const
{
   Float64 Bot2 = m_W4 + m_W2 + m_W3 / 2.0;
   Float64 Top2 = m_W1 + m_W2 + m_W3 / 2.0;

   // if blockout, use top dimension
   *left = (m_bLeftBlockout ? Top2 : Bot2);
   *right = (m_bRightBlockout ? Top2 : Bot2);
}

Float64 BoxBeam::GetWidth() const
{
   Float64 top = m_W3 + 2 * m_W2; // middle part
   top += (m_bLeftBlockout ? m_W1 : m_W4); // left part
   top += (m_bRightBlockout ? m_W1 : m_W4); // right part

   Float64 bot = 2 * (m_W4 + m_W2) + m_W3;

   return Max(top, bot);
}

Float64 BoxBeam::GetHeight() const
{
   return m_H1 + m_H2 + m_H3;
}

void BoxBeam::GetBoundaryPoints(Point2d* leftTop, Point2d* leftBottom, Point2d* rightTop, Point2d* rightBottom) const
{
   auto& composite = GetComposite();
   
   // outer shape
   const auto& shape = composite->GetShape(0);
   const auto& outer = std::dynamic_pointer_cast<Polygon>(shape);

   *leftTop     = outer->GetPoint(m_LeftTopPointIdx);
   *rightTop    = outer->GetPoint(m_RightTopPointIdx);
   *leftBottom  = outer->GetPoint(m_LeftBottomPointIdx);
   *rightBottom = outer->GetPoint(m_RightBottomPointIdx);

   // bottom points aren't that simple it there is a chamfer. we need to create a point at the intersection.
   if (0.0 < m_C1)
   {
      //
      //            |                               |
      //            |                               |
      //            |                               |
      //            |                               |
      //            \                               / rB
      //             \                             /
      //           lB -----------------------------
      //

      // get points just before indexed points
      Point2d leftBottomM1  = outer->GetPoint(m_LeftBottomPointIdx - 1);
      Point2d rightBottomM1 = outer->GetPoint(m_RightBottomPointIdx - 1);
      
      // left bottom
      leftBottom->X() = leftBottomM1.X();

      // right bottom
      rightBottom->Y() = rightBottomM1.Y();
   }
}

void BoxBeam::Offset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void BoxBeam::Rotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetComposite()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> BoxBeam::CreateClone() const
{
   return std::make_unique<BoxBeam>(*this);
}

std::shared_ptr<Shape> BoxBeam::GetBoxShape() const
{
   return GetComposite()->GetShape(0);
}

std::shared_ptr<Shape> BoxBeam::GetVoidShape(IndexType voidIdx) const
{
   if (m_nVoids <= voidIdx)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   return GetComposite()->GetShape(voidIdx + 1);
}

void BoxBeam::OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const
{
   // Create the outer shape
   std::unique_ptr<Polygon> outer = std::make_unique<Polygon>();

   // Start at bottom center and work CCW around the perimeter. 
   // Number of points varies depending on chamfer

   // outside dimensions
   Float64 wtop = 2.0 * (m_W1 + m_W2) + m_W3;
   Float64 wbot = 2.0 * (m_W4 + m_W2) + m_W3;
   Float64 hgt = m_H1 + m_H2 + m_H3;

   std::vector<Point2d> points;
   points.reserve(16);

   // bottom center
   points.emplace_back(0, 0);

   if (m_C1 <= 0.0)
   {
      // bottom right
      points.emplace_back(wbot / 2, 0);
   }
   else
   {
      // deal with chamfer
      points.emplace_back(wbot / 2 - m_C1, 0);
      points.emplace_back(wbot / 2, m_C1);
   }

   m_RightBottomPointIdx = points.size()-1;

   if (m_bRightBlockout)
   {
      // up the right edge, H7
      points.emplace_back(points.back().X(), m_H7);

      // bottom of the right key way, H6
      points.emplace_back(points.back().X() - m_W4, m_H6 + m_H7);

      // top of the right key way
      if (0.0 < m_H5 || 0.0 < m_H4)
      {
         points.emplace_back(points.back().X(), hgt - m_H4 - m_H5);
      }

      // right edge near top, H4
      if (0.0 < m_H4)
      {
         points.emplace_back(wtop / 2, hgt - m_H4);
      }

      // top right corner
      points.emplace_back(wtop / 2, hgt);
   }
   else
   {
      // top right corner
      points.emplace_back(wbot / 2, hgt);
   }

   m_RightTopPointIdx = points.size() - 1;

   if (m_bLeftBlockout)
   {
      // top left corner
      points.emplace_back(-wtop / 2, hgt);

      m_LeftTopPointIdx = points.size() - 1;

      // left edge near top, H4
      if (0 < m_H4)
      {
         points.emplace_back(-wtop / 2, hgt - m_H4);
      }

      // top of the left key way
      if (0.0 < m_H5 || 0.0 < m_H4)
      {
         points.emplace_back(points.back().X() + m_W1, hgt - m_H4 - m_H5);
      }

      // bottom of the left key way, H6
      points.emplace_back(points.back().X(), m_H6 + m_H7);

      // left edge, H7
      points.emplace_back(points.back().X() - m_W4, m_H7);
   }
   else
   {
      // top left corner
      points.emplace_back(-wbot / 2, hgt);

      m_LeftTopPointIdx = points.size() - 1;
   }

   if (m_C1 <= 0.0)
   {
      // bottom left
      points.emplace_back(-wbot / 2, 0);
   }
   else
   {
      // deal with chamfer
      points.emplace_back(-wbot / 2, m_C1);
      points.emplace_back(-wbot / 2 + m_C1, 0);
   }

   m_LeftBottomPointIdx = points.size() - 1;

   outer->SetPoints(points);

   composite->AddShape(std::move(outer));

   // inner shape
   if (0 < m_nVoids)
   {
      std::unique_ptr<Polygon> inner = std::make_unique<Polygon>();

      Float64 x1 = 0;
      Float64 y1 = m_H3;

      Float64 x2 = m_W3 / 2 - m_F2;
      Float64 y2 = y1;

      Float64 x3 = x2 + m_F2;
      Float64 y3 = y2 + m_F2;

      Float64 x4 = x3;
      Float64 y4 = m_H3 + m_H2 - m_F1;

      Float64 x5 = x4 - m_F1;
      Float64 y5 = y4 + m_F1;

      Float64 x6 = 0;
      Float64 y6 = y5;

      // the void is always symmetric about the X=0 axis
      inner->SetSymmetry(Polygon::Symmetry::Y,0.0);
      inner->AddPoint(x1, y1);
      inner->AddPoint(x2, y2);
      inner->AddPoint(x3, y3);
      inner->AddPoint(x4, y4);
      inner->AddPoint(x5, y5);
      inner->AddPoint(x6, y6);

      composite->AddShape(std::move(inner),CompositeShape::ShapeType::Void);
   }

   if (!IsZero(m_Rotation))
      composite->Rotate(Point2d(0, 0), m_Rotation);

   composite->Move(Point2d(0, 0), *GetHookPoint());
}
