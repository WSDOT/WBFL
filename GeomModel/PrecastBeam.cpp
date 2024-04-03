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
#include <GeomModel/PrecastBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include <memory>

using namespace WBFL::Geometry;

PrecastBeam::PrecastBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 w5,
   Float64 d1, Float64 d2, Float64 d3, Float64 d4,
   Float64 d5, Float64 d6, Float64 h,
   Float64 t1, Float64 t2, Float64 c1,
   std::shared_ptr<Point2d>& hookPnt) : FlangedBeam(hookPnt),
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
m_H(h),
m_T1(t1),
m_T2(t2),
m_C1(c1)
{
   PRECONDITION(w1>=0);
   PRECONDITION(w2>=0);
   PRECONDITION(w3>=0);
   PRECONDITION(w4>=0);
   PRECONDITION(w5>=0);
   PRECONDITION(d1>=0);
   PRECONDITION(d2>=0);
   PRECONDITION(d3>=0);
   PRECONDITION(d4>=0);
   PRECONDITION(d5>=0);
   PRECONDITION(d6>=0);
   PRECONDITION(h>=0);
   PRECONDITION(c1>=0);
   PRECONDITION(t1>=0);
   PRECONDITION(t2>=0);
}

PrecastBeam::PrecastBeam(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 w5,
   Float64 d1, Float64 d2, Float64 d3, Float64 d4,
   Float64 d5, Float64 d6, Float64 h,
   Float64 t1, Float64 t2, Float64 c1,
   const Point2d& hookPnt) : FlangedBeam(hookPnt),
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
   m_H(h),
   m_T1(t1),
   m_T2(t2),
   m_C1(c1)
{
   PRECONDITION(w1 >= 0);
   PRECONDITION(w2 >= 0);
   PRECONDITION(w3 >= 0);
   PRECONDITION(w4 >= 0);
   PRECONDITION(w5 >= 0);
   PRECONDITION(d1 >= 0);
   PRECONDITION(d2 >= 0);
   PRECONDITION(d3 >= 0);
   PRECONDITION(d4 >= 0);
   PRECONDITION(d5 >= 0);
   PRECONDITION(d6 >= 0);
   PRECONDITION(h >= 0);
   PRECONDITION(c1 >= 0);
   PRECONDITION(t1 >= 0);
   PRECONDITION(t2 >= 0);
}

PrecastBeam::~PrecastBeam()
{
}

void PrecastBeam::SetW1(Float64 w1)
{
   PRECONDITION(w1>=0);
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetW1() const
{
   return m_W1;
}

void PrecastBeam::SetW2(Float64 w2)
{
   PRECONDITION(w2>=0);
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetW2() const
{
   return m_W2;
}

void PrecastBeam::SetW3(Float64 w3)
{
   PRECONDITION(w3>=0);
   m_W3 = w3;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetW3() const
{
   return m_W3;
}

void PrecastBeam::SetW4(Float64 w4)
{
   PRECONDITION(w4>=0);
   m_W4 = w4;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetW4() const
{
   return m_W4;
}

void PrecastBeam::SetW5(Float64 w5)
{
   PRECONDITION(w5 >= 0);
   m_W5 = w5;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetW5() const
{
   return m_W5;
}

void PrecastBeam::SetD1(Float64 d1)
{
   PRECONDITION(d1>=0);
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetD1() const
{
   return m_D1;
}

void PrecastBeam::SetD2(Float64 d2)
{
   PRECONDITION(d2>=0);
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetD2() const
{
   return m_D2;
}

void PrecastBeam::SetD3(Float64 d3)
{
   PRECONDITION(d3>=0);
   m_D3 = d3;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetD3() const
{
   return m_D3;
}

void PrecastBeam::SetD4(Float64 d4)
{
   PRECONDITION(d4>=0);
   m_D4 = d4;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetD4() const
{
   return m_D4;
}

void PrecastBeam::SetD5(Float64 d5)
{
   PRECONDITION(d5>=0);
   m_D5 = d5;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetD5() const
{
   return m_D5;
}

void PrecastBeam::SetD6(Float64 d6)
{
   PRECONDITION(d6>=0);
   m_D6 = d6;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetD6() const
{
   return m_D6;
}

void PrecastBeam::SetHeight(Float64 h)
{
   PRECONDITION(h>=0);
   m_H = h;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetHeight() const
{
   return m_H;
}

void PrecastBeam::SetT1(Float64 t1)
{
   PRECONDITION(t1>=0);
   m_T1 = t1;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetT1() const
{
   return m_T1;
}

void PrecastBeam::SetT2(Float64 t2)
{
   PRECONDITION(t2>=0);
   m_T2 = t2;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetT2() const
{
   return m_T2;
}

void PrecastBeam::SetC1(Float64 c1)
{
   PRECONDITION(c1 >= 0);
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 PrecastBeam::GetC1() const
{
   return m_C1;
}

void PrecastBeam::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void PrecastBeam::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

IndexType PrecastBeam::GetTopFlangeCount() const
{
   return 1;
}

Float64 PrecastBeam::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 PrecastBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

IndexType PrecastBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 PrecastBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 PrecastBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetBottomWidth();
}

Float64 PrecastBeam::GetTopWidth() const
{
   return  m_T1 + 2. * (m_W1 + m_W2 + m_W3);
}

Float64 PrecastBeam::GetBottomWidth() const
{
   return m_T2 + 2. * (m_W4 + m_W5);
}

MatingSurfaceIndexType PrecastBeam::GetMatingSurfaceCount() const
{
   return 1;
}

Float64 PrecastBeam::GetMatingSurfaceWidth(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

Float64 PrecastBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0;
}

IndexType PrecastBeam::GetWebCount() const
{
   return 1;
}

Plane3d PrecastBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return Plane3d(0, 0, -1, 0); // vertical plane
}

Float64 PrecastBeam::GetShearWidth() const
{
   return GetMinWebWidth();
}

Float64 PrecastBeam::GetAvgWebWidth() const
{
   return 0.5 * (m_T1 + m_T2);
}

Float64 PrecastBeam::GetMinWebWidth() const
{
   return Min(m_T1,m_T2);
}

Float64 PrecastBeam::GetMinBottomFlangeThickness() const
{
   return m_D6;
}

Float64 PrecastBeam::GetMinTopFlangeThickness() const
{
   return m_D1;
}

std::unique_ptr<Shape> PrecastBeam::CreateClone() const
{
   return std::make_unique<PrecastBeam>(*this);
}

void PrecastBeam::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   // start at top center and go around counter-clockwise
   // there are 22 points total. point 1 is top center. point 12 is bottom center. 
   Float64 p1_x = 0.;
   Float64 p1_y = 0.;

   Float64 p2_x = -m_T1 / 2 - m_W3 - m_W2 - m_W1;
   Float64 p2_y = 0.;

   Float64 p3_x = p2_x;
   Float64 p3_y = -m_D1;

   Float64 p4_x = p3_x + m_W1;
   Float64 p4_y = p3_y;

   Float64 p5_x = -m_T1 / 2 - m_W3;
   Float64 p5_y = -m_D1 - m_D2;

   Float64 p6_x = -m_T1 / 2;
   Float64 p6_y = -m_D1 - m_D2 - m_D3;

   Float64 p7_x = -m_T2 / 2;
   Float64 p7_y = -m_H + m_D4 + m_D5 + m_D6;

   Float64 p8_x = -m_T2 / 2 - m_W4;
   Float64 p8_y = -m_H + m_D5 + m_D6;

   Float64 p9_x = -m_T2 / 2 - m_W4 - m_W5;
   Float64 p9_y = -m_H + m_D6;

   Float64 p10_x = p9_x;
   Float64 p10_y = -m_H + m_C1;

   Float64 p11_x = p10_x + m_C1;
   Float64 p11_y = -m_H;

   polygon->AddPoint(p1_x, p1_y);  // 1 (top center)
   polygon->AddPoint(p2_x, p2_y);
   polygon->AddPoint(p3_x, p3_y);
   if (0.0 < m_W1)
   {
      polygon->AddPoint(p4_x, p4_y);
   }
   polygon->AddPoint(p5_x, p5_y);
   polygon->AddPoint(p6_x, p6_y);
   polygon->AddPoint(p7_x, p7_y);
   polygon->AddPoint(p8_x, p8_y);
   polygon->AddPoint(p9_x, p9_y);
   polygon->AddPoint(p10_x, p10_y); // top of chamfer (or bottom corner if no chamfer)
   if (0.0 < m_C1)
   {
      polygon->AddPoint(p11_x, p11_y); // bottom of chamfer
   }
   polygon->AddPoint(0, p11_y);  // 12 (bottom center)

   // this shape is symmetric about the Y-axis
   polygon->SetSymmetry(Polygon::Symmetry::Y);

   //if (0.0 < m_C1)
   //{
   //   polygon->AddPoint(-p11_x, p11_y); // bottom of chamfer
   //}
   //polygon->AddPoint(-p10_x, p10_y);// top of chamfer (or bottom corner if no chamfer)
   //polygon->AddPoint(-p9_x, p9_y);
   //polygon->AddPoint(-p8_x, p8_y);
   //polygon->AddPoint(-p7_x, p7_y);
   //polygon->AddPoint(-p6_x, p6_y);
   //polygon->AddPoint(-p5_x, p5_y);
   //polygon->AddPoint(-p4_x, p4_y);
   //polygon->AddPoint(-p3_x, p3_y);
   //polygon->AddPoint(-p2_x, p2_y);
   //polygon->AddPoint(-p1_x, p1_y);  // 22


   // polygon hook point is the first point, which is the top center of the precast beam as defined above
   // however, the hookpoint of the precast beam is at the bottom center
   // adjust the polygon so that it's first point is at the same point as the hookpoint
   polygon->Offset(GetHookPoint()->X(),GetHookPoint()->Y()+m_H);

   if (!IsZero(m_Rotation))
      polygon->Rotate(*GetHookPoint(), m_Rotation);
}
