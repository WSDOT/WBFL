///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
   if (0 < flangeIdx) THROW_GEOMETRY(_T("BulbTee::GetTopFlangeLocation - invalid flange index"));
   return 0.0;
}

Float64 BulbTee::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("BulbTee::GetTopFlangeWidth - invalid flange index"));
   return GetTopWidth();
}

IndexType BulbTee::GetBottomFlangeCount() const
{
   return 1;
}

Float64 BulbTee::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("BulbTee::GetBottomFlangeLocation - invalid flange index"));
   return 0.0;
}

Float64 BulbTee::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("BulbTee::GetBottomFlangeWidth - invalid flange index"));
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

void BulbTee::GetTopFlangePoints(Point2d* leftTop, Point2d* leftBottom, Point2d* topCentral, Point2d* rightTop, Point2d* rightBottom) const
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
   if (0 < webIdx) THROW_GEOMETRY(_T("BulbTee::GetMatingSurfaceWidth - index out of range"));

   return GetTopWidth();
}

Float64 BulbTee::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(_T("BulbTee::GetMatingSurfaceWidth - index out of range"));
   
   return 0.0;
}

IndexType BulbTee::GetWebCount() const
{
   return 1;
}

Plane3d BulbTee::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(_T("BulbTee::GetMatingSurfaceWidth - index out of range"));
   return Plane3d(0, 0, -1, 0); // vertical plane
}

std::unique_ptr<Shape> BulbTee::CreateClone() const
{
   return std::make_unique<BulbTee>(*this);
}

#if defined _DEBUG
bool BulbTee::AssertValid() const
{
   return __super::AssertValid();
}

void BulbTee::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for BulbTee ***") << WBFL::Debug::endl;
   __super::Dump( os );
   GetPolygon()->Dump(os);
}
#endif // _DEBUG

void BulbTee::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   ASSERTVALID;

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

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool BulbTee::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("BulbTee");

   BulbTee beam;

   // Try some real dimensions (WSDOT WF69G)
   beam.SetD1(6);
   beam.SetD2(3);
   beam.SetD3(3);
   beam.SetD4(5.125);
   beam.SetD5(4.5);
   beam.SetD6(3);
   beam.SetD7(44.375);
   beam.SetW1(18.4375);
   beam.SetW2(3);
   beam.SetW3(13.125);
   beam.SetW4(3);
   beam.SetW5(30);
   beam.SetW6(30);
   beam.SetT1(6.125);
   beam.SetT2(6.125);
   beam.SetC1(1);
   beam.SetC2(15);
   beam.SetN1(0.02);
   beam.SetN2(-0.02);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -30.0));
   TRY_TESTME(IsEqual(box.Right(), 30.0));
   TRY_TESTME(IsEqual(box.Top(), 69.9));
   TRY_TESTME(IsEqual(box.Bottom(), 0.0));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 1119.03125));
   TRY_TESTME(IsEqual(props.GetIxx(), 798071.07781859976));
   TRY_TESTME(IsEqual(props.GetIyy(), 158329.51421028795));
   TRY_TESTME(IsEqual(props.GetIxy(), -7399.6791562527796));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), -0.22117344801586084));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 39.565942803019738));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 29.778826551984139));
   TRY_TESTME(IsEqual(props.GetXright(), 30.221173448015861));
   TRY_TESTME(IsEqual(props.GetYtop(), 69.9 - 39.565942803019738));
   TRY_TESTME(IsEqual(props.GetYbottom(), 39.565942803019738));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 301.89593547481729));

   //
   // FurthestDistance
   //
   Point2d p1(0, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);

   // Shape on right
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line,Line2d::Side::Right), 20.000));

   // shape on left
   p1.Move(0, -20);
   p2.Move(100, -20);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.000));


   //
   // PointInShape
   //
   Point2d pnt(0, 1);
   TRY_TESTME(beam.PointInShape(pnt) == true);
   pnt.Move(500, 500);
   TRY_TESTME(beam.PointInShape(pnt) == false);
   pnt.Move(0, 0); // Point on perimeter
   TRY_TESTME(beam.PointInShape(pnt) == false);

   // Get moment of inertia about CG before move
   // These properties should be invariant
   props.SetCoordinateSystem(ShapeProperties::CoordSystemType::Centroidal);
   Float64 area = props.GetArea();
   Float64 Ixx = props.GetIxx();
   Float64 Iyy = props.GetIyy();

   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);
   beam.Move(from, to);

   props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetIxx(), Ixx));
   TRY_TESTME(IsEqual(props.GetIyy(), Iyy));

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);

   props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), area));
   TRY_TESTME(IsEqual(props.GetIxx(), Ixx));
   TRY_TESTME(IsEqual(props.GetIyy(), Iyy));

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   ///
   // LocatorPoint property
   //
   auto hookPnt = beam.GetHookPoint();

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(130, 100));

   // BottomCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 100));

   // BottomRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(70, 100));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(130, 65.05));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 65.05));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(70, 65.05));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(130, 30.1));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 30.1));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(70, 30.1));

   // HookPoint
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 100));

   TESTME_EPILOG("BulbTee");
}

#endif // _UNITTEST


