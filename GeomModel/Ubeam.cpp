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
#include <GeomModel/UBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include <memory>

using namespace WBFL::Geometry;

UBeam::UBeam()
{
}

UBeam::UBeam(Float64 w1, Float64 w2, Float64 w3,Float64 w4,Float64 w5,
                 Float64 d1, Float64 d2, Float64 d3,Float64 d4,Float64 d5,Float64 d6,Float64 d7,
                 Float64 t,
   std::shared_ptr<Point2d>& hookPnt) :
   FlangedBeam(hookPnt),
m_W1(w1),
m_W2(w2),
m_W3(w3),
m_W4(w4),
m_W5(w5),
m_D1(d1),
m_D2(d2),
m_D3(d3),
m_D4(d4),
m_D5(d5),
m_D6(d6),
m_D7(d7),
m_T(t)
{
   PRECONDITION(w1    >  0);
   PRECONDITION(w2    >  0);
   PRECONDITION(w3    >= 0);
   PRECONDITION(w4    >= 0);
   PRECONDITION(d1    >  0);
   PRECONDITION(d2    >  0);
   PRECONDITION(d3    >= 0);
   PRECONDITION(d4    >= 0);
   PRECONDITION(d5    >= 0);
   PRECONDITION(d6    >= 0);
   PRECONDITION(t     >  0);
}

UBeam::UBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 w5,
   Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5, Float64 d6, Float64 d7,
   Float64 t,
   const Point2d& hookPnt) :
   FlangedBeam(hookPnt),
   m_W1(w1),
   m_W2(w2),
   m_W3(w3),
   m_W4(w4),
   m_W5(w5),
   m_D1(d1),
   m_D2(d2),
   m_D3(d3),
   m_D4(d4),
   m_D5(d5),
   m_D6(d6),
   m_D7(d7),
   m_T(t)
{
   PRECONDITION(w1 > 0);
   PRECONDITION(w2 > 0);
   PRECONDITION(w3 >= 0);
   PRECONDITION(w4 >= 0);
   PRECONDITION(d1 > 0);
   PRECONDITION(d2 > 0);
   PRECONDITION(d3 >= 0);
   PRECONDITION(d4 >= 0);
   PRECONDITION(d5 >= 0);
   PRECONDITION(d6 >= 0);
   PRECONDITION(t > 0);
}
UBeam::~UBeam()
{
}

void UBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>0);
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 UBeam::GetW1() const
{
   return m_W1;
}

void UBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>0);
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 UBeam::GetW2() const
{
   return m_W2;
}

void UBeam::SetW3(Float64 w3)
{
   PRECONDITION(w3>=0);
   m_W3 = w3;
   SetDirtyFlag();
}

Float64 UBeam::GetW3() const
{
   return m_W3;
}

void UBeam::SetW4(Float64 w4)
{
   PRECONDITION(w4>=0);
   m_W4 = w4;
   SetDirtyFlag();
}

Float64 UBeam::GetW4() const
{
   return m_W4;
}

void UBeam::SetW5(Float64 w5)
{
   PRECONDITION(w5>=0);
   m_W5 = w5;
   SetDirtyFlag();
}

Float64 UBeam::GetW5() const
{
   return m_W5;
}

void UBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>0);
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 UBeam::GetD1() const
{
   return m_D1;
}

void UBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>0);
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 UBeam::GetD2() const
{
   return m_D2;
}

void UBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 UBeam::GetD3() const
{
   return m_D3;
}

void UBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 UBeam::GetD4() const
{
   return m_D4;
}

void UBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 UBeam::GetD5() const
{
   return m_D5;
}

void UBeam::SetD6(Float64 d6)
{
   PRECONDITION(d6>=0);
   m_D6 = d6;
   SetDirtyFlag();
}

Float64 UBeam::GetD6() const
{
   return m_D6;
}

void UBeam::SetD7(Float64 d7)
{
   PRECONDITION(d7>=0);
   m_D7 = d7;
   SetDirtyFlag();
}

Float64 UBeam::GetD7() const
{
   return m_D7;
}

void UBeam::SetT(Float64 t)
{
   PRECONDITION(t>=0);
   m_T = t;
   SetDirtyFlag();
}

Float64 UBeam::GetT() const
{
   return m_T;
}

Float64 UBeam::GetSlope(WebIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes the slope to be updated
   return (webIdx == 0 ? -1.0 : 1.0) * m_Slope;
}

Float64 UBeam::GetHeight() const
{
   return m_D1;
}

Float64 UBeam::GetWebLocation(WebIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes the slope to be updated
   Float64 sign = (webIdx == 0) ? -1 : 1;

   return sign * (m_D1 / m_Slope - 0.5 * m_T * sqrt(m_Slope * m_Slope + 1) / m_Slope + m_W1 / 2);
}

Float64 UBeam::GetWebSpacing() const
{
   GetPolygon(); // causes the slope to be updated
   return m_W1 - m_T * sqrt(m_Slope * m_Slope + 1) / m_Slope + 2 * m_D1 / m_Slope;
}

void UBeam::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void UBeam::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

IndexType UBeam::GetTopFlangeCount() const
{
   return 2;
}

Float64 UBeam::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (1 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   Float64 sign = (flangeIdx == 0) ? -1 : 1;
   return sign * (GetTopWidth() - GetTopFlangeWidth(flangeIdx)) / 2;
}

Float64 UBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (1 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   GetPolygon(); // causes m_Slope to be updated
   Float64 t = m_T*sqrt(m_Slope * m_Slope + 1)/ m_Slope;
   return (m_W4 + (m_D6 + m_D7) / m_Slope) + (m_W5 - (m_D4 + m_D5) / m_Slope) + t;
}

IndexType UBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 UBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 UBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetBottomWidth();
}

Float64 UBeam::GetTopWidth() const
{
   return m_W2;
}

Float64 UBeam::GetBottomWidth() const
{
   return m_W1;
}

MatingSurfaceIndexType UBeam::GetMatingSurfaceCount() const
{
   return 2;
}

Float64 UBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopFlangeWidth(webIdx)/2;
}

Float64 UBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopFlangeLocation(webIdx);
}

IndexType UBeam::GetWebCount() const
{
   return 2;
}

Plane3d UBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (1 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

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

Float64 UBeam::GetShearWidth() const
{
   return GetMinWebWidth() * 2;
}

Float64 UBeam::GetAvgWebWidth() const
{
   return m_T;
}

Float64 UBeam::GetMinWebWidth() const
{
   return m_T;
}

Float64 UBeam::GetMinBottomFlangeThickness() const
{
   return m_D2;
}

Float64 UBeam::GetMinTopFlangeThickness() const
{
   return Min(m_D4,m_D6);
}

std::unique_ptr<Shape> UBeam::CreateClone() const
{
   return std::make_unique<UBeam>(*this);
}

void UBeam::UpdateSlope() const
{
   Float64 rise = m_D1 - m_D4 - m_D5;
   Float64 run = (m_W2 - m_W1)/2 - m_W5;

   m_Slope = IsZero(run) ? DBL_MAX : rise / run;
}

void UBeam::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   UpdateSlope();

   Float64 T = m_T;
   if (!IsZero(m_Slope))
      T = m_T * sqrt(m_Slope * m_Slope + 1) / m_Slope;

   Float64 D4(m_D4), D5(m_D5), D6(m_D6), D7(m_D7);
   if (IsZero(m_W4))
   {
      // D6 and D7 must be zero if W4 is zero
      CHECK(IsZero(m_D6));
      CHECK(IsZero(m_D7));
      D6 = 0;
      D7 = 0;
   }

   if (IsZero(m_W5))
   {
      // D4 and D5 must be zero if W5 is zero
      CHECK(IsZero(m_D4));
      CHECK(IsZero(m_D5));
      D4 = 0;
      D5 = 0;
   }

   // start at the bottom center and go around clockwise
   // Hook point is at bottom center (0,0)
   // Compute left side points, mirror for right side
   Float64 p1_x = 0.;
   Float64 p1_y = 0.;

   Float64 p2_x = -m_W1 / 2;
   Float64 p2_y = 0.;

   Float64 p3_x = p2_x - (IsZero(m_Slope) ? 0 : (m_D1 - D4 - D5) / m_Slope);
   Float64 p3_y = m_D1 - D4 - D5;

   Float64 p4_x = -m_W2 / 2;
   Float64 p4_y = m_D1 - D4;

   Float64 p5_x = -m_W2 / 2;
   Float64 p5_y = m_D1;

   Float64 p6_x;
   if (IsZero(D4) && IsZero(D5) && !IsZero(D6) & !IsZero(D7))
   {
      // Flange only on the inside
      p6_x = -m_W2 / 2 + m_W4 + T + (IsZero(m_Slope) ? 0 : (D6 + D7) / m_Slope);
   }
   else if (!IsZero(D4) && !IsZero(D5) && IsZero(D6) & IsZero(D7))
   {
      // Flange only on the outside
      p6_x = -m_W2 / 2 + m_W5 + T - (IsZero(m_Slope) ? 0 : (D4 + D5) / m_Slope);
   }
   else
   {
      // Flange on both sides or no flange
      p6_x = -m_W2 / 2 + m_W4 + m_W5 + T;
   }
   Float64 p6_y = m_D1;

   Float64 p7_x = p6_x;
   Float64 p7_y = m_D1 - D6;

   Float64 p8_x = p7_x - m_W4;
   Float64 p8_y = m_D1 - D6 - D7;

   Float64 p9_x = p8_x + (IsZero(m_Slope) ? 0 : (m_D1 - m_D2 - m_D3 - D6 - D7) / m_Slope);
   Float64 p9_y = m_D2 + m_D3;

   Float64 p10_x = p9_x + m_W3;
   Float64 p10_y = m_D2;

   polygon->AddPoint(Point2d( p1_x, p1_y));
   polygon->AddPoint(Point2d( p2_x, p2_y));
   polygon->AddPoint(Point2d( p3_x, p3_y));
   polygon->AddPoint(Point2d( p4_x, p4_y));
   polygon->AddPoint(Point2d( p5_x, p5_y));
   polygon->AddPoint(Point2d( p6_x, p6_y));
   polygon->AddPoint(Point2d( p7_x, p7_y));
   polygon->AddPoint(Point2d( p8_x, p8_y));
   polygon->AddPoint(Point2d( p9_x, p9_y));
   polygon->AddPoint(Point2d( p10_x, p10_y));
   polygon->AddPoint(Point2d( 0.0, p10_y));

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   //// mirror points
   //polygon->AddPoint(Point2d(-p10_x, p10_y));
   //polygon->AddPoint(Point2d(-p9_x, p9_y));
   //polygon->AddPoint(Point2d(-p8_x, p8_y));
   //polygon->AddPoint(Point2d(-p7_x, p7_y));
   //polygon->AddPoint(Point2d(-p6_x, p6_y)); 
   //polygon->AddPoint(Point2d(-p5_x, p5_y));
   //polygon->AddPoint(Point2d(-p4_x, p4_y));
   //polygon->AddPoint(Point2d(-p3_x, p3_y));
   //polygon->AddPoint(Point2d(-p2_x, p2_y));

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0,0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}
