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
#include <GeomModel/PrecastBeam.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <MathEx.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PrecastBeam::GetTopFlangeLocation - invalid flange index"));
   return 0.0;
}

Float64 PrecastBeam::GetTopFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PrecastBeam::GetTopFlangeWidth - invalid flange index"));
   return GetTopWidth();
}

IndexType PrecastBeam::GetBottomFlangeCount() const
{
   return 1;
}

Float64 PrecastBeam::GetBottomFlangeLocation(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PrecastBeam::GetBottomFlangeLocation - invalid flange index"));
   return 0.0;
}

Float64 PrecastBeam::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) THROW_GEOMETRY(_T("PrecastBeam::GetBottomFlangeWidth - invalid flange index"));
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
   if (0 < webIdx) THROW_GEOMETRY(_T("PrecastBeam::GetMatingSurfaceWidth - index out of range"));
   return GetTopWidth();
}

Float64 PrecastBeam::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(_T("PrecastBeam::GetMatingSurfaceLocation - index out of range"));
   return 0;
}

IndexType PrecastBeam::GetWebCount() const
{
   return 1;
}

Plane3d PrecastBeam::GetWebPlane(WebIndexType webIdx) const
{
   if (0 < webIdx) THROW_GEOMETRY(_T("PrecastBeam::GetWebPlane - index out of range"));
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

#if defined _DEBUG
bool PrecastBeam::AssertValid() const
{
   if ( m_W1<0 || m_W2<0 || m_W3<0 || m_W4<0 || m_D1<0 )return false;
   if ( m_D2<0 || m_D3<0 || m_D4<0 || m_D5<0 || m_D6<0 )return false;
   if ( m_H<0 || m_T1<0 || m_T2<0) return false;

   return __super::AssertValid();
}

void PrecastBeam::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for PrecastBeam ***")<< WBFL::Debug::endl;
   __super::Dump( os );
   os << _T("  Hook Point      = (")<<GetHookPoint()->X()<<_T(", ")<<GetHookPoint()->Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("  Rotation        =  ")<<m_Rotation<< WBFL::Debug::endl;
   os << _T("  D1              =  ")<<m_D1 << WBFL::Debug::endl;
   os << _T("  D2              =  ")<<m_D2 << WBFL::Debug::endl;
   os << _T("  D3              =  ")<<m_D3 << WBFL::Debug::endl;
   os << _T("  D4              =  ")<<m_D4 << WBFL::Debug::endl;
   os << _T("  D5              =  ")<<m_D5 << WBFL::Debug::endl;
   os << _T("  D6              =  ")<<m_D6 << WBFL::Debug::endl;
   os << _T("  H               =  ")<<m_H << WBFL::Debug::endl;
   os << _T("  W1              =  ")<<m_W1 << WBFL::Debug::endl;
   os << _T("  W2              =  ")<<m_W2 << WBFL::Debug::endl;
   os << _T("  W3              =  ")<<m_W3 << WBFL::Debug::endl;
   os << _T("  W4              =  ")<<m_W4 << WBFL::Debug::endl;
   os << _T("  T1              =  ")<<m_T1 << WBFL::Debug::endl;
   os << _T("  T2              =  ")<<m_T2 << WBFL::Debug::endl;
   os << _T("Polygon rep of beam") << WBFL::Debug::endl;
   
   GetPolygon()->Dump(os);
}
#endif // _DEBUG

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
   polygon->AddPoint(p4_x, p4_y);
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

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool PrecastBeam::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PrecastBeam");

   // Use some real dimensions (WSDOT Modified WF100G girder)
   PrecastBeam beam;
   beam.SetW1(6);
   beam.SetW2(18.4375);
   beam.SetW3(3);
   beam.SetW4(3);
   beam.SetW5(13.125);
   beam.SetD1(3);
   beam.SetD2(3);
   beam.SetD3(3);
   beam.SetD4(3);
   beam.SetD5(4.5);
   beam.SetD6(5.125);
   beam.SetHeight(100);
   beam.SetT1(6.125);
   beam.SetT2(6.125);
   beam.SetC1(1.0);

   TRY_TESTME(IsEqual(beam.GetHeight(), 100.0));

   TRY_TESTME(beam.GetWebCount() == 1);
   TRY_TESTME(beam.GetTopFlangeCount() == 1);
   TRY_TESTME(IsEqual(beam.GetTopFlangeLocation(0), 0.0));
   TRY_TESTME(IsEqual(beam.GetTopFlangeWidth(0), 61.0));
   TRY_TESTME(beam.GetBottomFlangeCount() == 1);
   TRY_TESTME(IsEqual(beam.GetBottomFlangeLocation(0), 0.0));
   TRY_TESTME(IsEqual(beam.GetBottomFlangeWidth(0), 38.375));
   TRY_TESTME(beam.GetMatingSurfaceCount() == 1);
   TRY_TESTME(IsEqual(beam.GetMatingSurfaceLocation(0), 0.0));
   TRY_TESTME(IsEqual(beam.GetMatingSurfaceWidth(0), 61.0));
   TRY_TESTME(IsEqual(beam.GetAvgWebWidth(), 6.125));

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -30.5));
   TRY_TESTME(IsEqual(box.Right(), 30.5));
   TRY_TESTME(IsEqual(box.Top(), 100.0));
   TRY_TESTME(IsEqual(box.Bottom(), 0.00));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 1118.78125));
   TRY_TESTME(IsEqual(props.GetIxx(), 1612833.8649339355));
   TRY_TESTME(IsEqual(props.GetIyy(), 99849.307047526003));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 49.889825586808556));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 30.5));
   TRY_TESTME(IsEqual(props.GetXright(), 30.5));
   TRY_TESTME(IsEqual(props.GetYtop(), 100.0 - props.GetCentroid().Y()));
   TRY_TESTME(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 365.28393667457732));

   //
   // FurthestDistance
   //
   Point2d p1(0, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);

   // Shape on right
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.000));

   // shape on left
   p1.Move(0, -20);
   p2.Move(100, -20);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.000));

   // 
   // PolyPoints
   //
   auto points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 23);
   int i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(-24.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, 94.000000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, 91.000000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, 12.625000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, 9.625000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 5.125000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(-18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(19.187500, 5.125000));
   TRY_TESTME(points[i++] == Point2d(6.062500, 9.625000));
   TRY_TESTME(points[i++] == Point2d(3.062500, 12.625000));
   TRY_TESTME(points[i++] == Point2d(3.062500, 91.000000));
   TRY_TESTME(points[i++] == Point2d(6.062500, 94.000000));
   TRY_TESTME(points[i++] == Point2d(24.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // PointInShape
   //
   Point2d pnt(0, 0.5);
   TRY_TESTME(beam.PointInShape(pnt) == true);

   pnt.Move(500, 500);
   TRY_TESTME(beam.PointInShape(pnt) == false);

   pnt.Move(0, 0); // Point on perimeter
   TRY_TESTME(beam.PointInShape(pnt) == false);

   //
   // ClipWithLine
   //

   // setup clipping line
   p1.Move(-50, 0.50);
   p2.Move(50, 0.50);
   Line2d clipLine(p1, p2);

   auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 5);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-18.687500, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(18.687500, 0.500000));
   TRY_TESTME(i == points.size());

   // clip in other direction
   p1.Move(50, 0.5);
   p2.Move(-50, 0.5);

   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 22);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(-24.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, 94.000000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, 91.000000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, 12.625000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, 9.625000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 5.125000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(-18.687500, 0.500000));
   TRY_TESTME(points[i++] == Point2d(18.687500, 0.500000));
   TRY_TESTME(points[i++] == Point2d(19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(19.187500, 5.125000));
   TRY_TESTME(points[i++] == Point2d(6.062500, 9.625000));
   TRY_TESTME(points[i++] == Point2d(3.062500, 12.625000));
   TRY_TESTME(points[i++] == Point2d(3.062500, 91.000000));
   TRY_TESTME(points[i++] == Point2d(6.062500, 94.000000));
   TRY_TESTME(points[i++] == Point2d(24.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // ClipIn
   //
   Rect2d clipRect(-100, 0.5, 100, 0.6);
   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 5);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-18.787500, 0.600000));
   TRY_TESTME(points[i++] == Point2d(-18.687500, 0.500000));
   TRY_TESTME(points[i++] == Point2d(18.687500, 0.500000));
   TRY_TESTME(points[i++] == Point2d(18.787500, 0.600000));
   TRY_TESTME(points[i++] == Point2d(-18.787500, 0.600000));
   TRY_TESTME(i == points.size());

   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);

   beam.Move(from, to);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 23);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(100.000000, 200.000000));
   TRY_TESTME(points[i++] == Point2d(69.500000, 200.000000));
   TRY_TESTME(points[i++] == Point2d(69.500000, 197.000000));
   TRY_TESTME(points[i++] == Point2d(75.500000, 197.000000));
   TRY_TESTME(points[i++] == Point2d(93.937500, 194.000000));
   TRY_TESTME(points[i++] == Point2d(96.937500, 191.000000));
   TRY_TESTME(points[i++] == Point2d(96.937500, 112.625000));
   TRY_TESTME(points[i++] == Point2d(93.937500, 109.625000));
   TRY_TESTME(points[i++] == Point2d(80.812500, 105.125000));
   TRY_TESTME(points[i++] == Point2d(80.812500, 101.000000));
   TRY_TESTME(points[i++] == Point2d(81.812500, 100.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(118.187500, 100.000000));
   TRY_TESTME(points[i++] == Point2d(119.187500, 101.000000));
   TRY_TESTME(points[i++] == Point2d(119.187500, 105.125000));
   TRY_TESTME(points[i++] == Point2d(106.062500, 109.625000));
   TRY_TESTME(points[i++] == Point2d(103.062500, 112.625000));
   TRY_TESTME(points[i++] == Point2d(103.062500, 191.000000));
   TRY_TESTME(points[i++] == Point2d(106.062500, 194.000000));
   TRY_TESTME(points[i++] == Point2d(124.500000, 197.000000));
   TRY_TESTME(points[i++] == Point2d(130.500000, 197.000000));
   TRY_TESTME(points[i++] == Point2d(130.500000, 200.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 200.000000));
   TRY_TESTME(i == points.size());

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 23);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(-24.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, 94.000000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, 91.000000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, 12.625000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, 9.625000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 5.125000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(-18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(19.187500, 1.000000));
   TRY_TESTME(points[i++] == Point2d(19.187500, 5.125000));
   TRY_TESTME(points[i++] == Point2d(6.062500, 9.625000));
   TRY_TESTME(points[i++] == Point2d(3.062500, 12.625000));
   TRY_TESTME(points[i++] == Point2d(3.062500, 91.000000));
   TRY_TESTME(points[i++] == Point2d(6.062500, 94.000000));
   TRY_TESTME(points[i++] == Point2d(24.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, 97.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // LocatorPoint property
   //
   auto hookPnt = beam.GetHookPoint();

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(130.5, 100.0));

   // BottomCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // BottomRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(69.5, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(130.5, 50.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 50.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(69.5, 50.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(130.5, 0.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 0.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(69.5, 0.0));

   // HookPoint
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0, 0);
   Point2d c(0, 0);

   beam.Rotate(c, M_PI);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 23);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-0.000000, -100.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, -100.000000));
   TRY_TESTME(points[i++] == Point2d(30.500000, -97.000000));
   TRY_TESTME(points[i++] == Point2d(24.500000, -97.000000));
   TRY_TESTME(points[i++] == Point2d(6.062500, -94.000000));
   TRY_TESTME(points[i++] == Point2d(3.062500, -91.000000));
   TRY_TESTME(points[i++] == Point2d(3.062500, -12.625000));
   TRY_TESTME(points[i++] == Point2d(6.062500, -9.625000));
   TRY_TESTME(points[i++] == Point2d(19.187500, -5.125000));
   TRY_TESTME(points[i++] == Point2d(19.187500, -1.000000));
   TRY_TESTME(points[i++] == Point2d(18.187500, -0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-18.187500, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, -1.000000));
   TRY_TESTME(points[i++] == Point2d(-19.187500, -5.125000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, -9.625000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, -12.625000));
   TRY_TESTME(points[i++] == Point2d(-3.062500, -91.000000));
   TRY_TESTME(points[i++] == Point2d(-6.062500, -94.000000));
   TRY_TESTME(points[i++] == Point2d(-24.500000, -97.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, -97.000000));
   TRY_TESTME(points[i++] == Point2d(-30.500000, -100.000000));
   TRY_TESTME(points[i++] == Point2d(-0.000000, -100.000000));
   TRY_TESTME(i == points.size());

   TESTME_EPILOG("PrecastBeam");
}

#endif // _UNITTEST


