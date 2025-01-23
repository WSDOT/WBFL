///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/BulbTee.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include <memory>

// NOTE: This shape is based on the WBFL::Geometry BulbTee2

using namespace WBFL::Geometry;

BulbTee::BulbTee() : FlangedBeam()
{
}

BulbTee::BulbTee(Float64 w1, Float64 w2, Float64 w3, Float64 w4, Float64 w5, Float64 w6,
   Float64 d1, Float64 d2, Float64 d3, Float64 d4, Float64 d5, Float64 d6, Float64 d7,
   Float64 t1, Float64 t2, Float64 c1, Float64 c2, Float64 n1, Float64 n2, const Point2d& hookPnt) :
   FlangedBeam(hookPnt),
   m_W1(w1),m_W2(w2),m_W3(w3),m_W4(w4),m_W5(w5),m_W6(w6),
   m_D1(d1), m_D2(d2), m_D3(d3), m_D4(d4), m_D5(d5), m_D6(d6), m_D7(d7),
   m_T1(t1), m_T2(t2), m_C1(c1), m_C2(c2), m_N1(n1), m_N2(n2)
{
}

BulbTee::~BulbTee()
{
}

void BulbTee::SetW1(Float64 w1) { m_W1 = w1; SetDirtyFlag(); }
Float64 BulbTee::GetW1() const { return m_W1; }

void BulbTee::SetW2(Float64 w2) { m_W2 = w2; SetDirtyFlag(); }
Float64 BulbTee::GetW2() const { return m_W2; }

void BulbTee::SetW3(Float64 w3) { m_W3 = w3; SetDirtyFlag(); }
Float64 BulbTee::GetW3() const { return m_W3; }

void BulbTee::SetW4(Float64 w4) { m_W4 = w4; SetDirtyFlag(); }
Float64 BulbTee::GetW4() const { return m_W4; }

void BulbTee::SetW5(Float64 w5) { m_W5 = w5; SetDirtyFlag(); }
Float64 BulbTee::GetW5() const { return m_W5; }

void BulbTee::SetW6(Float64 w6) { m_W6 = w6; SetDirtyFlag(); }
Float64 BulbTee::GetW6() const { return m_W6; }

void BulbTee::SetD1(Float64 d1) { m_D1 = d1; SetDirtyFlag(); }
Float64 BulbTee::GetD1() const { return m_D1; }

void BulbTee::SetD2(Float64 d2) { m_D2 = d2; SetDirtyFlag(); }
Float64 BulbTee::GetD2() const { return m_D2; }

void BulbTee::SetD3(Float64 d3) { m_D3 = d3; SetDirtyFlag(); }
Float64 BulbTee::GetD3() const { return m_D3; }

void BulbTee::SetD4(Float64 d4) { m_D4 = d4; SetDirtyFlag(); }
Float64 BulbTee::GetD4() const { return m_D4; }

void BulbTee::SetD5(Float64 d5) { m_D5 = d5; SetDirtyFlag(); }
Float64 BulbTee::GetD5() const { return m_D5; }

void BulbTee::SetD6(Float64 d6) { m_D6 = d6; SetDirtyFlag(); }
Float64 BulbTee::GetD6() const { return m_D6; }

void BulbTee::SetD7(Float64 d7) { m_D7 = d7; SetDirtyFlag(); }
Float64 BulbTee::GetD7() const { return m_D7; }

void BulbTee::SetT1(Float64 f1) { m_T1 = f1; SetDirtyFlag(); }
Float64 BulbTee::GetT1() const { return m_T1; }

void BulbTee::SetT2(Float64 t2) { m_T2 = t2; SetDirtyFlag(); }
Float64 BulbTee::GetT2() const { return m_T2; }

void BulbTee::SetC1(Float64 c1) { m_C1 = c1;  SetDirtyFlag(); }
Float64 BulbTee::GetC1() const { return m_C1; }

void BulbTee::SetC2(Float64 c2) { m_C2 = c2; SetDirtyFlag(); }
Float64 BulbTee::GetC2() const { return m_C2; }

void BulbTee::SetN1(Float64 n1) { m_N1 = n1;  SetDirtyFlag(); }
Float64 BulbTee::GetN1() const { return m_N1; }

void BulbTee::SetN2(Float64 n2) { m_N2 = n2;  SetDirtyFlag(); }
Float64 BulbTee::GetN2() const { return m_N2; }

void BulbTee::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void BulbTee::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

Float64 BulbTee::GetAvgWebWidth() const
{
   return (m_T1 + m_T2) / 2.;
}

IndexType BulbTee::GetTopFlangeCount() const
{
   return 1;
}

Float64 BulbTee::GetTopFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 BulbTee::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetTopWidth();
}

IndexType BulbTee::GetBottomFlangeCount() const
{
   return 1;
}

Float64 BulbTee::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return 0.0;
}

Float64 BulbTee::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return GetBottomWidth();
}

Float64 BulbTee::GetTopWidth() const
{
   return m_W5 + m_W6;
}

Float64 BulbTee::GetBottomWidth() const
{
   return m_T2 + 2. * (m_W3 + m_W4);
}

Float64 BulbTee::GetMinHeight() const
{
   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);
   return Min(Hl, Hr, Hc);
}

Float64 BulbTee::GetMaxHeight() const
{
   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);
   return Max(Hl, Hr, Hc);
}

Float64 BulbTee::GetCLHeight() const
{
   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);
   Float64 Hcl;
   if (m_W5 < m_C2)
   {
      Hcl = Hl + m_N1 * m_W5;
   }
   else
   {
      Hcl = Hl + m_N1 * m_C2 + m_N2 * (m_W5 - m_C2);
   }
   return Hcl;
}

Float64 BulbTee::GetHeight() const
{
   return GetMaxHeight();
}

void BulbTee::GetTopFlangePoints(Point2d* leftTop, Point2d* leftBottom, Point2d* topCL, Point2d* topCentral, Point2d* rightTop, Point2d* rightBottom) const
{
   IndexType leftTopIdx(11), leftBottomIdx(12), topCentralIdx(10), rightTopIdx(9), rightBottomIdx(8); // index into the polygon points
   if (IsZero(m_C1))
   {
      // we don't have a chamfer in the bottom flange... reduce indicies by one
      leftTopIdx--;
      leftBottomIdx--;
      topCentralIdx--;
      rightTopIdx--;
      rightBottomIdx--;
   }

   if (IsZero(m_C2) || IsEqual(m_C2, m_W5 + m_W6))
   {
      // there isn't a crown point between flange tips
      // high point is at left or right flange tip... reduce one from left flange indicies
      leftTopIdx--;
      leftBottomIdx--;

      if (IsZero(m_C2))
      {
         // top flange is thicker on the right side
         topCentralIdx = rightTopIdx;
      }
      else
      {
         // top flange is thicker on the left side
         topCentralIdx = leftTopIdx;
      }
   }

   std::unique_ptr<Polygon>& polygon = GetPolygon();

   // get the points from our polygon implementation
   *leftTop = polygon->GetPoint(leftTopIdx);
   *leftBottom = polygon->GetPoint(leftBottomIdx);
   *topCentral = polygon->GetPoint(topCentralIdx);
   *rightTop = polygon->GetPoint(rightTopIdx);
   *rightBottom = polygon->GetPoint(rightBottomIdx);

   if (IsZero(m_C2))
   {
      auto [x,y] = leftTop->GetLocation();
      x += m_W5;
      y += m_W5 * m_N2;
      topCL->Move(x, y);
   }
   else if (IsEqual(m_C2, m_W5 + m_W6))
   {
      auto [x,y] = leftTop->GetLocation();
      x += m_W5;
      y += m_W5 * m_N1;
      topCL->Move(x, y);
   }
   else
   {
      auto [x,y] = leftTop->GetLocation();
      x += m_W5;
      if (m_C2 < m_W5)
      {
         y += m_C2 * m_N1 + (m_W5 - m_C2) * m_N2;
      }
      else
      {
         y += m_W5 * m_N1;
      }
      topCL->Move(x, y);
   }

#if defined _DEBUG
   Float64 Hl, Hc, Hr;
   GetTopFlangeThickness(&Hl, &Hc, &Hr);
   Float64 hl = leftTop->Distance(*leftBottom);
   Float64 hr = rightTop->Distance(*rightBottom);
   CHECK(IsEqual(hl, Hl));
   CHECK(IsEqual(hr, Hr));
#endif
}

void BulbTee::GetBottomFlangePoints(Point2d* leftTop, Point2d* leftBottom, Point2d* rightTop, Point2d* rightBottom) const
{
   std::unique_ptr<Polygon>& polygon = GetPolygon();
   IndexType nPoints = polygon->GetCount();

   // get the points from our polygon implementation
   if (IsZero(m_C1))
   {
      // no chamfer
      *rightBottom = polygon->GetPoint(0);
      *rightTop = polygon->GetPoint(0);

      *leftTop = polygon->GetPoint(nPoints - 1);
      *leftBottom = polygon->GetPoint(nPoints - 1);
   }
   else
   {
      *rightBottom = polygon->GetPoint(0);
      *rightTop = polygon->GetPoint(1);

      *leftTop = polygon->GetPoint(nPoints - 2);
      *leftBottom = polygon->GetPoint(nPoints-1);
   }
}

void BulbTee::GetTopFlangeThickness(Float64* Hl, Float64* Hc, Float64* Hr) const
{
   GetHeight(Hl, Hc, Hr);

   Float64 baseHeight = /*m_D1 +*/ m_D2 + m_D3 + m_D4 + m_D5 + m_D6 + m_D7; // basic height

   *Hl -= baseHeight;
   *Hc -= baseHeight;
   *Hr -= baseHeight;
}

Float64 BulbTee::GetShearWidth() const
{
   return GetAvgWebWidth();
}

Float64 BulbTee::GetMinWebWidth() const
{
   return Min(m_T1, m_T2);
}

Float64 BulbTee::GetMinBottomFlangeThickness() const
{
   return m_D4;
}

Float64 BulbTee::GetMinTopFlangeThickness() const
{
   return m_D1;
}

MatingSurfaceIndexType BulbTee::GetMatingSurfaceCount() const
{
   return 1;
}

Float64 BulbTee::GetMatingSurfaceWidth(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   return GetTopWidth();
}

Float64 BulbTee::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   
   return 0.0;
}

IndexType BulbTee::GetWebCount() const
{
   return 1;
}

Plane3d BulbTee::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);
   return Plane3d(0, 0, -1, 0); // vertical plane
}

std::unique_ptr<Shape> BulbTee::CreateClone() const
{
   return std::make_unique<BulbTee>(*this);
}

void BulbTee::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   Float64 Hl, Hc, Hr;
   GetHeight(&Hl, &Hc, &Hr);

   // start at bottom center (0,0)
   // and work counter-clockwise around shape
   Float64 p1_x = 0;
   Float64 p1_y = 0;

   // outside corner of bottom flange... intersection of vertical and horizontal
   // edges... no chamfer
   Float64 p2_x = p1_x + m_T2 / 2 + m_W3 + m_W4;
   Float64 p2_y = p1_y;

   Float64 p3_x = p2_x;
   Float64 p3_y = p2_y + m_D4;

   Float64 p4_x = p3_x - m_W3;
   Float64 p4_y = p3_y + m_D5;

   Float64 p5_x = p4_x - m_W4;
   Float64 p5_y = p4_y + m_D6;

   Float64 p6_x = p5_x - (m_T2 - m_T1) / 2;
   Float64 p6_y = p5_y + m_D7;

   Float64 p7_x = p6_x + m_W2;
   Float64 p7_y = p6_y + m_D3;

   Float64 p8_x = p7_x + m_W1;
   Float64 p8_y = p7_y + m_D2;

   //m_pShape->AddPoint(p1_x, p1_y); // skip 0,0... this is just an extra point we don't really need
   if (0 < m_C1)
   {
      // there is a chamfer
      polygon->AddPoint(p2_x - m_C1, p2_y);
      polygon->AddPoint(p2_x, p2_y + m_C1);
   }
   else
   {
      polygon->AddPoint(p2_x, p2_y);
   }
   polygon->AddPoint(p3_x, p3_y);
   polygon->AddPoint(p4_x, p4_y);
   polygon->AddPoint(p5_x, p5_y);
   polygon->AddPoint(p6_x, p6_y);
   polygon->AddPoint(p7_x, p7_y);
   polygon->AddPoint(p8_x, p8_y);

   // Right tip of top flange... on soffit below top surface
   polygon->AddPoint(m_W6, p8_y);

   // Top right corner
   polygon->AddPoint(m_W6, Hr);

   if (!IsZero(m_C2) && !IsEqual(m_C2, m_W5 + m_W6))
   {
      // there is a peak at C2
      polygon->AddPoint(m_C2 - m_W5, Hc);
   }

   // Top left corner
   polygon->AddPoint(-m_W5, Hl);

   // left tip of top flange... on soffet below top surface
   polygon->AddPoint(-m_W5, p8_y);

   // work down the left side of the soffit and web
   polygon->AddPoint(-p8_x, p8_y);
   polygon->AddPoint(-p7_x, p7_y);
   polygon->AddPoint(-p6_x, p6_y);
   polygon->AddPoint(-p5_x, p5_y);
   polygon->AddPoint(-p4_x, p4_y);
   polygon->AddPoint(-p3_x, p3_y);
   if (0 < m_C1)
   {
      // there is a chamfer
      polygon->AddPoint(-p2_x, p2_y + m_C1);
      polygon->AddPoint(-p2_x + m_C1, p2_y);
   }
   else
   {
      polygon->AddPoint(-p2_x, p2_y);
   }

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0, 0), m_Rotation);

   // The hook point is at the bottom centerline of the web (which may not be at the bottom CL of the bounding box)
   // The shape was built with bottom centerline of the web at (0,0)
   // Move the shape so that point (0,0) moves to the hook point
   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

void BulbTee::GetHeight(Float64* Hl, Float64* Hc, Float64* Hr) const
{
   // Hl = height at left edge
   // Hc = height at C2
   // Hr = height at right edge

   Float64 H = m_D1 + m_D2 + m_D3 + m_D4 + m_D5 + m_D6 + m_D7; // basic height

   Float64 dL = m_N1 * m_C2; // change in depth on left side of crown point
   Float64 dR = m_N2 * (m_W5 + m_W6 - m_C2); // change in depth on right side of crown point

   if (dL < 0 && 0 < dR)
   {
      // the top flange is a "V" shape... low point is at C
      *Hc = H;
      *Hl = H - dL;
      *Hr = H + dR;
   }
   else if (dL < -dR)
   {
      // low point is on the right side
      *Hr = H;
      *Hc = H - dR;
      *Hl = H - dR - dL;
   }
   else
   {
      // low point is on the left side
      *Hl = H;
      *Hc = H + dL;
      *Hr = H + dL + dR;
   }
}
