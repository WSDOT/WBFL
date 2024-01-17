///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/UBeam2.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include <memory>

using namespace WBFL::Geometry;

UBeam2::UBeam2()
{
}

UBeam2::UBeam2(Float64 w1, Float64 w2, Float64 w3,Float64 w4,Float64 w5,Float64 w6,Float64 w7,
                 Float64 d1, Float64 d2, Float64 d3,Float64 d4,Float64 d5,Float64 d6,
                 Float64 c1,
   std::shared_ptr<Point2d>& hookPnt) :
   FlangedBeam(hookPnt),
m_W1(w1),
m_W2(w2),
m_W3(w3),
m_W4(w4),
m_W5(w5),
m_W6(w6),
m_W7(w7),
m_D1(d1),
m_D2(d2),
m_D3(d3),
m_D4(d4),
m_D5(d5),
m_D6(d6),
m_C1(c1)
{
   PRECONDITION(w1 >= 0);
   PRECONDITION(w2 >= 0);
   PRECONDITION(w3 >= 0);
   PRECONDITION(w4 >= 0);
   PRECONDITION(w5 >= 0);
   PRECONDITION(w6 >= 0);
   PRECONDITION(w7 >= 0);
   PRECONDITION(d1 >= 0);
   PRECONDITION(d2 >= 0);
   PRECONDITION(d3 >= 0);
   PRECONDITION(d4 >= 0);
   PRECONDITION(d5 >= 0);
   PRECONDITION(d6 >= 0);
   PRECONDITION(c1 >= 0);
}

UBeam2::~UBeam2()
{
}

void UBeam2::SetW1(Float64 w1)
{
   PRECONDITION(w1>0);
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 UBeam2::GetW1() const
{
   return m_W1;
}

void UBeam2::SetW2(Float64 w2)
{
   PRECONDITION(w2>0);
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 UBeam2::GetW2() const
{
   return m_W2;
}

void UBeam2::SetW3(Float64 w3)
{
   PRECONDITION(w3>=0);
   m_W3 = w3;
   SetDirtyFlag();
}

Float64 UBeam2::GetW3() const
{
   return m_W3;
}

void UBeam2::SetW4(Float64 w4)
{
   PRECONDITION(w4>=0);
   m_W4 = w4;
   SetDirtyFlag();
}

Float64 UBeam2::GetW4() const
{
   return m_W4;
}

void UBeam2::SetW5(Float64 w5)
{
   PRECONDITION(w5>0);
   m_W5 = w5;
   SetDirtyFlag();
}

Float64 UBeam2::GetW5() const
{
   return m_W5;
}

void UBeam2::SetW6(Float64 w6)
{
   PRECONDITION(w6 > 0);
   m_W6 = w6;
   SetDirtyFlag();
}

Float64 UBeam2::GetW6() const
{
   return m_W6;
}

void UBeam2::SetW7(Float64 w7)
{
   PRECONDITION(w7 > 0);
   m_W7 = w7;
   SetDirtyFlag();
}

Float64 UBeam2::GetW7() const
{
   return m_W7;
}

void UBeam2::SetD1(Float64 d1)
{
   PRECONDITION(d1>0);
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 UBeam2::GetD1() const
{
   return m_D1;
}

void UBeam2::SetD2(Float64 d2)
{
   PRECONDITION(d2>0);
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 UBeam2::GetD2() const
{
   return m_D2;
}

void UBeam2::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 UBeam2::GetD3() const
{
   return m_D3;
}

void UBeam2::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 UBeam2::GetD4() const
{
   return m_D4;
}

void UBeam2::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 UBeam2::GetD5() const
{
   return m_D5;
}

void UBeam2::SetD6(Float64 d6)
{
   PRECONDITION(d6>=0);
   m_D6 = d6;
   SetDirtyFlag();
}

Float64 UBeam2::GetD6() const
{
   return m_D6;
}

void UBeam2::SetC1(Float64 c1)
{
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 UBeam2::GetC1() const
{
   return m_C1;
}

void UBeam2::UseOutlineOnly(bool bOutline)
{
   m_bUseOutlineOnly = bOutline;
   SetDirtyFlag();
}

bool UBeam2::UseOutlineOnly() const
{
   return m_bUseOutlineOnly;
}

Float64 UBeam2::GetT() const
{
   GetPolygon(); // causes the same to be updated, including T
   return m_T;
}

Float64 UBeam2::GetWebLocation(WebIndexType webIdx) const
{
   if (2 <= webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes the shape to be updated, including m_Slope and m_T

   Float64 sign = (webIdx == 0) ? -1 : 1;
   return sign * (m_D1 / m_Slope - 0.5 * m_T * sqrt(m_Slope * m_Slope + 1) / m_Slope + m_W1 / 2);
}

Float64 UBeam2::GetWebSpacing() const
{
   Float64 t = GetT();

   return m_W1 - t * sqrt(m_Slope * m_Slope + 1) / m_Slope + 2 * m_D1 / m_Slope;
}

Float64 UBeam2::GetSlope(WebIndexType webIdx) const
{
   if (2 <= webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes the slope to be updated
   return (webIdx == 0 ? -1.0 : 1.0) * m_Slope;
}

Float64 UBeam2::GetHeight() const
{
   return m_D1;
}

void UBeam2::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void UBeam2::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

IndexType UBeam2::GetTopFlangeCount() const
{
   return 2;
}

Float64 UBeam2::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (1 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   Float64 sign = (flangeIdx == 0 ? -1 : 1);
   if (m_bUseOutlineOnly) 
   {
      return sign * m_W2 / 2;
   }
   else
   {
      return sign * (m_W2 - m_W6) / 2;
   }
}

Float64 UBeam2::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if(m_bUseOutlineOnly)
   {
      // if the shape is just the outline of the U-beam,
      // then the top flange is half the width of the beam
      return m_W2 / 2;
   }
   else
   {
      // otherwise it is the normal input value
      return m_W6;
   }
}

IndexType UBeam2::GetBottomFlangeCount() const
{
   return 1;
}

Float64 UBeam2::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 UBeam2::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetBottomWidth();
}

Float64 UBeam2::GetTopWidth() const
{
   return m_W2;
}

Float64 UBeam2::GetBottomWidth() const
{
   return m_W1;
}

MatingSurfaceIndexType UBeam2::GetMatingSurfaceCount() const
{
   return 2;
}

Float64 UBeam2::GetMatingSurfaceWidth(MatingSurfaceIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopFlangeWidth(webIdx);
}

Float64 UBeam2::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopFlangeLocation(webIdx);
}

IndexType UBeam2::GetWebCount() const
{
   return 2;
}

Plane3d UBeam2::GetWebPlane(WebIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes the shape to be updated, including m_Slope and m_T

   Float64 slope = GetSlope(webIdx);

   Float64 sign = (webIdx == 0 ? -1.0 : 1.0);

   Float64 x, y, z;
   Float64 t = fabs((m_T/2)*(sqrt(slope*slope+1)/slope));
   x = 0;
   y = 0;
   z = sign*(m_W1/2 - t);

   Point3d p1(x, y, z);

   x = 100;
   y = 0;
   z = sign*(m_W1/2 - t);

   Point3d p2(x, y, z);

   x = 0;
   y = 100;
   z = sign*(m_W1/2 - t - y/slope);
   Point3d p3(x, y, z);
   
   return Plane3d(p1, p2, p3);
}

Float64 UBeam2::GetShearWidth() const
{
   return GetMinWebWidth() * 2;
}

Float64 UBeam2::GetAvgWebWidth() const
{
   GetPolygon(); // causes the shape, including m_T to be updated
   return m_T;
}

Float64 UBeam2::GetMinWebWidth() const
{
   return GetAvgWebWidth();
}

Float64 UBeam2::GetMinBottomFlangeThickness() const
{
   return m_D2;
}

Float64 UBeam2::GetMinTopFlangeThickness() const
{
   return m_D5;
}

std::unique_ptr<Shape> UBeam2::CreateClone() const
{
   return std::make_unique<UBeam2>(*this);
}

void UBeam2::UpdateSlope() const
{
   Float64 rise = m_D1 - m_D4 - m_D5;
   Float64 run = (m_W2 - m_W1) / 2 - m_W4 - m_W5;

   m_Slope = IsZero(run) ? DBL_MAX : rise / run;
}

void UBeam2::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   UpdateSlope();

   // start at the bottom center and go around clockwise
   // Hook point is at bottom center (0,0)
   // Compute left side points, mirror for right side
   Float64 p1_x = 0.;
   Float64 p1_y = 0.;

   Float64 p2_x = -m_W1 / 2;
   Float64 p2_y = 0.;

   Float64 p3_x = p2_x - (IsZero(m_Slope) ? 0 : (m_D1 - m_D4 - m_D5) / m_Slope);
   Float64 p3_y = m_D1 - m_D4 - m_D5;

   Float64 p4_x = -m_W2 / 2 + m_W4;
   Float64 p4_y = m_D1 - m_D5;

   Float64 p5_x = -m_W2 / 2;
   Float64 p5_y = m_D1;

   Float64 p6_x = -m_W2 / 2 + m_W6;
   Float64 p6_y = p5_y;

   Float64 p7_x = p6_x + m_W7;
   Float64 p7_y = p6_y - m_D6;

   Float64 p8_x = p7_x + (IsZero(m_Slope) ? 0 : (m_D1 - m_D6 - m_D2 - m_D3) / m_Slope);
   Float64 p8_y = m_D2 + m_D3;

   Float64 p9_x = p8_x + m_W3;
   Float64 p9_y = m_D2;

   // next build chamfer points if needed
   Point2d p2a, p2b, p4a, p4b;

   bool is_chamfer = 0.0 < m_C1 ? true : false;
   if (is_chamfer)
   {
      p2a = GeometricOperations::PointOnLine(Point2d(p2_x, p2_y), Point2d(p1_x, p1_y), m_C1);
      p2b = GeometricOperations::PointOnLine(Point2d(p2_x, p2_y), Point2d(p3_x, p3_y), m_C1);

      p4a = GeometricOperations::PointOnLine(Point2d(p4_x, p4_y), Point2d(p3_x, p3_y), m_C1);
      p4b = GeometricOperations::PointOnLine(Point2d(p4_x, p4_y), Point2d(p5_x, p5_y), m_C1);
   }

   polygon->AddPoint(p1_x, p1_y);  // 1 (bottom center)

   if (is_chamfer)
   {
      polygon->AddPoint(p2a);
      polygon->AddPoint(p2b);
   }
   else
   {
      polygon->AddPoint(p2_x, p2_y);
   }

   polygon->AddPoint(p3_x, p3_y);

   if (is_chamfer)
   {
      polygon->AddPoint(p4a);
      polygon->AddPoint(p4b);
   }
   else
   {
      polygon->AddPoint(p4_x, p4_y);
   }

   polygon->AddPoint(p5_x, p5_y); // top left

   if (m_bUseOutlineOnly)
   {
      // Using the outline of the shape only
      // place the inner points along the top edge of the shape
      polygon->AddPoint(p6_x, p6_y);
      polygon->AddPoint(p7_x, p6_y);
      polygon->AddPoint(p8_x, p6_y);
      polygon->AddPoint(p9_x, p6_y);
      polygon->AddPoint(0, p6_y);
   }
   else
   {
      // points inside the U
      polygon->AddPoint(p6_x, p6_y);
      polygon->AddPoint(p7_x, p7_y);
      polygon->AddPoint(p8_x, p8_y);
      polygon->AddPoint(p9_x, p9_y);
      polygon->AddPoint(0, p9_y);
   }

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   //// mirror points
   //if (m_bUseOutlineOnly)
   //{
   //   // mirror points
   //   polygon->AddPoint(-p9_x, p6_y);
   //   polygon->AddPoint(-p8_x, p6_y);
   //   polygon->AddPoint(-p7_x, p6_y);
   //   polygon->AddPoint(-p6_x, p6_y);
   //}
   //else
   //{
   //   // mirror points
   //   polygon->AddPoint(-p9_x, p9_y);
   //   polygon->AddPoint(-p8_x, p8_y);
   //   polygon->AddPoint(-p7_x, p7_y);
   //   polygon->AddPoint(-p6_x, p6_y);
   //}


   //polygon->AddPoint(-p5_x, p5_y);

   //if (is_chamfer)
   //{
   //   polygon->AddPoint(-p4b.X(), p4b.Y());
   //   polygon->AddPoint(-p4a.X(), p4a.Y());
   //}
   //else
   //{
   //   polygon->AddPoint(-p4_x, p4_y);
   //}

   //polygon->AddPoint(-p3_x, p3_y);

   //if (is_chamfer)
   //{
   //   polygon->AddPoint(-p2b.X(), p2b.Y());
   //   polygon->AddPoint(-p2a.X(), p2a.Y());
   //}
   //else
   //{
   //   polygon->AddPoint(-p2_x, p2_y);
   //}

   Point2d p2(p2_x, p2_y);
   Point2d p3(p3_x, p3_y);
   if (p2 == p3)
   {
      m_T = 0;
   }
   else
   {
      Point2d p8(p8_x, p8_y);
      Line2d line(p2, p3);
      m_T = fabs(line.DistanceToPoint(p8));
   }

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0, 0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}
