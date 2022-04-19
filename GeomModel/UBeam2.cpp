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
#include <GeomModel/UBeam2.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
   //PRECONDITION(w1    >  0);
   //PRECONDITION(w2    >  0);
   //PRECONDITION(w3    >= 0);
   //PRECONDITION(w4    >= 0);
   //PRECONDITION(d1    >  0);
   //PRECONDITION(d2    >  0);
   //PRECONDITION(d3    >= 0);
   //PRECONDITION(d4    >= 0);
   //PRECONDITION(d5    >= 0);
   //PRECONDITION(d6    >= 0);
   //PRECONDITION(t     >  0);
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
   if (2 <= webIdx)
      throw std::invalid_argument("UBeam2::GetWebLocation - invalid web index");

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
   if (2 <= webIdx)
      throw std::invalid_argument("UBeam2::GetMatingSurfaceLocation - invalid web index");

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
   if (1 < flangeIdx) throw std::invalid_argument("UBeam2::GetTopFlangeLocation - invalid flange index");

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
   if (0 < flangeIdx) throw std::invalid_argument("UBeam2::GetBottomFlangeLocation - invalid flange index");
   return 0.0;
}

Float64 UBeam2::GetBottomFlangeWidth(IndexType flangeIdx) const
{
   if (0 < flangeIdx) throw std::invalid_argument("UBeam2::GetBottomFlangeWidth - invalid flange index");
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
   if (1 < webIdx) throw std::invalid_argument("UBeam2::GetMatingSurfaceWidth - invalid web index");
   return GetTopFlangeWidth(webIdx);
}

Float64 UBeam2::GetMatingSurfaceLocation(MatingSurfaceIndexType webIdx) const
{
   if (1 < webIdx) throw std::invalid_argument("UBeam2::GetMatingSurfaceLocation - invalid web index");
   return GetTopFlangeLocation(webIdx);
}

IndexType UBeam2::GetWebCount() const
{
   return 2;
}

Plane3d UBeam2::GetWebPlane(WebIndexType webIdx) const
{
   if (1 < webIdx)  throw std::invalid_argument("UBeam2::GetWebPlane - invalid web index");

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

#if defined _DEBUG
bool UBeam2::AssertValid() const
{
   if ( m_W1 < 0 || m_W2 < 0 || m_W3 < 0 || m_W4 < 0 ) return false;
   if ( m_D1 < 0 || m_D2 < 0 || m_D3 < 0 || m_D4 < 0 || m_D5 < 0 || m_D6 < 0 ) return false;
   if ( m_T  < 0)                          return false;

   return __super::AssertValid();
}

void UBeam2::Dump(dbgDumpContext& os) const
{
   os << _T("*** Dump for UBeam2 ***") <<endl;
   ShapeImpl::Dump( os );
   os << _T("  Hook Point      = (")<<GetHookPoint()->X()<<_T(", ")<<GetHookPoint()->Y()<<_T(")")<<endl;
   os << _T("  Rotation        =  ")<<m_Rotation<<endl;
   os << _T("  D1              =  ")<<m_D1 <<endl;
   os << _T("  D2              =  ")<<m_D2 <<endl;
   os << _T("  D3              =  ")<<m_D3 <<endl;
   os << _T("  D4              =  ")<<m_D4 <<endl;
   os << _T("  D5              =  ")<<m_D5 <<endl;
   os << _T("  D6              =  ")<<m_D6 <<endl;
   os << _T("  W1              =  ")<<m_W1 <<endl;
   os << _T("  W2              =  ")<<m_W2 <<endl;
   os << _T("  W3              =  ")<<m_W3 <<endl;
   os << _T("  W4              =  ")<<m_W4 <<endl;
   os << _T("  W5              =  ")<<m_W5 <<endl;
   os << _T("  T               =  ")<<m_T  <<endl;
   os << _T("Polygon rep of beam") << endl;
   GetPolygon()->Dump(os);
}
#endif // _DEBUG

void UBeam2::UpdateSlope() const
{
   Float64 rise = m_D1 - m_D4 - m_D5;
   Float64 run = (m_W2 - m_W1) / 2 - m_W4 - m_W5;

   m_Slope = IsZero(run) ? DBL_MAX : rise / run;
}

void UBeam2::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   ASSERTVALID;

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

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool UBeam2::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("UBeam2");

   // Use some real dimensions (TXDOT U40 girder)
   UBeam2 beam;
   beam.SetW1(55);
   beam.SetW2(89);
   beam.SetW3(3);
   beam.SetW4(0.375);
   beam.SetW5(8.25);
   beam.SetW6(15.75);
   beam.SetW7(1.75);
   beam.SetD1(40);
   beam.SetD2(8.25);
   beam.SetD3(3);
   beam.SetD4(0.875);
   beam.SetD5(5.875);
   beam.SetD6(21.625);
   beam.SetC1(0.0);

   TRY_TESTME(IsEqual(beam.GetHeight(), 40.0));

   TRY_TESTME(IsEqual(beam.GetSlope(0), -3.970149));
   TRY_TESTME(IsEqual(beam.GetSlope(1),  3.970149));

   TRY_TESTME(IsEqual(beam.GetTopWidth(), 89.0));

   TRY_TESTME(beam.GetTopFlangeCount() == 2);
   TRY_TESTME(IsEqual(beam.GetTopFlangeWidth(0), 15.75));
   TRY_TESTME(IsEqual(beam.GetTopFlangeWidth(1), 15.75));

   TRY_TESTME(IsEqual(beam.GetWebSpacing(), 70.022086466165405));

   TRY_TESTME(beam.GetWebCount() == 2);
   TRY_TESTME(IsEqual(beam.GetWebLocation(0), -35.011043233082702));
   TRY_TESTME(IsEqual(beam.GetWebLocation(1), 35.011043233082702));

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -44.5));
   TRY_TESTME(IsEqual(box.Right(), 44.5));
   TRY_TESTME(IsEqual(box.Top(), 40.00));
   TRY_TESTME(IsEqual(box.Bottom(), 0.00));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();

   TRY_TESTME(IsEqual(props.GetArea(), 978.1015625));
   TRY_TESTME(IsEqual(props.GetIxx(), 183371.372367286));
   TRY_TESTME(IsEqual(props.GetIyy(), 672244.006479706));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 16.3516905452245));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);
   TRY_TESTME(IsEqual(props.GetXleft(), 44.5));
   TRY_TESTME(IsEqual(props.GetXright(), 44.5));
   TRY_TESTME(IsEqual(props.GetYtop(), 23.6483094547755));
   TRY_TESTME(IsEqual(props.GetYbottom(), 16.3516905452245));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 294.425976857583));

   //
   // FurthestDistance
   //

   // Shape on right
   Point2d p1(0, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);

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
   TRY_TESTME(points.size() == 18);

   int i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-27.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-35.875000, 33.250000));
   TRY_TESTME(points[i++] == Point2d(-44.125000, 34.125000));
   TRY_TESTME(points[i++] == Point2d(-44.500000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(-28.750000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(-27.000000, 18.375000));
   TRY_TESTME(points[i++] == Point2d(-25.205357, 11.250000));
   TRY_TESTME(points[i++] == Point2d(-22.205357, 8.250000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 8.250000));
   TRY_TESTME(points[i++] == Point2d(22.205357, 8.250000));
   TRY_TESTME(points[i++] == Point2d(25.205357, 11.250000));
   TRY_TESTME(points[i++] == Point2d(27.000000, 18.375000));
   TRY_TESTME(points[i++] == Point2d(28.750000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(44.500000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(44.125000, 34.125000));
   TRY_TESTME(points[i++] == Point2d(35.875000, 33.250000));
   TRY_TESTME(points[i++] == Point2d(27.500000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // PointInShape
   //
   Point2d pnt(0.0, 0.5);
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
   TRY_TESTME(points.size() == 6);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-27.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-27.625940, 0.500000));
   TRY_TESTME(points[i++] == Point2d(27.625940, 0.500000));
   TRY_TESTME(points[i++] == Point2d(27.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   // clip in other direction
   p1.Move(50, 0.50);
   p2.Move(-50, 0.50);

   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 17);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(-27.625940, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-35.875000, 33.250000));
   TRY_TESTME(points[i++] == Point2d(-44.125000, 34.125000));
   TRY_TESTME(points[i++] == Point2d(-44.500000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(-28.750000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(-27.000000, 18.375000));
   TRY_TESTME(points[i++] == Point2d(-25.205357, 11.250000));
   TRY_TESTME(points[i++] == Point2d(-22.205357, 8.250000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 8.250000));
   TRY_TESTME(points[i++] == Point2d(22.205357, 8.250000));
   TRY_TESTME(points[i++] == Point2d(25.205357, 11.250000));
   TRY_TESTME(points[i++] == Point2d(27.000000, 18.375000));
   TRY_TESTME(points[i++] == Point2d(28.750000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(44.500000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(44.125000, 34.125000));
   TRY_TESTME(points[i++] == Point2d(35.875000, 33.250000));
   TRY_TESTME(points[i++] == Point2d(27.625940, 0.500000));
   TRY_TESTME(i == points.size());

   //
   // ClipIn
   //
   Rect2d clipRect(-100, 0.5, 100, 0.6);
   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip != nullptr);

   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 4);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(-27.625940, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-27.651128, 0.600000));
   TRY_TESTME(points[i++] == Point2d(27.651128, 0.600000));
   TRY_TESTME(points[i++] == Point2d(27.625940, 0.500000));
   TRY_TESTME(i == points.size());

   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);

   beam.Move(from, to);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 19);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(72.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(64.125000, 133.250000));
   TRY_TESTME(points[i++] == Point2d(55.875000, 134.125000));
   TRY_TESTME(points[i++] == Point2d(55.500000, 140.000000));
   TRY_TESTME(points[i++] == Point2d(71.250000, 140.000000));
   TRY_TESTME(points[i++] == Point2d(73.000000, 118.375000));
   TRY_TESTME(points[i++] == Point2d(74.794643, 111.250000));
   TRY_TESTME(points[i++] == Point2d(77.794643, 108.250000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 108.250000));
   TRY_TESTME(points[i++] == Point2d(122.205357, 108.250000));
   TRY_TESTME(points[i++] == Point2d(125.205357, 111.250000));
   TRY_TESTME(points[i++] == Point2d(127.000000, 118.375000));
   TRY_TESTME(points[i++] == Point2d(128.750000, 140.000000));
   TRY_TESTME(points[i++] == Point2d(144.500000, 140.000000));
   TRY_TESTME(points[i++] == Point2d(144.125000, 134.125000));
   TRY_TESTME(points[i++] == Point2d(135.875000, 133.250000));
   TRY_TESTME(points[i++] == Point2d(127.500000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 18);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-27.500000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-35.875000, 33.250000));
   TRY_TESTME(points[i++] == Point2d(-44.125000, 34.125000));
   TRY_TESTME(points[i++] == Point2d(-44.500000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(-28.750000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(-27.000000, 18.375000));
   TRY_TESTME(points[i++] == Point2d(-25.205357, 11.250000));
   TRY_TESTME(points[i++] == Point2d(-22.205357, 8.250000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 8.250000));
   TRY_TESTME(points[i++] == Point2d(22.205357, 8.250000));
   TRY_TESTME(points[i++] == Point2d(25.205357, 11.250000));
   TRY_TESTME(points[i++] == Point2d(27.000000, 18.375000));
   TRY_TESTME(points[i++] == Point2d(28.750000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(44.500000, 40.000000));
   TRY_TESTME(points[i++] == Point2d(44.125000, 34.125000));
   TRY_TESTME(points[i++] == Point2d(35.875000, 33.250000));
   TRY_TESTME(points[i++] == Point2d(27.500000, 0.000000));
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
   TRY_TESTME(*hookPnt == Point2d(144.5, 100.0));

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
   TRY_TESTME(*hookPnt == Point2d(55.5, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(144.5, 80.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 80.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(55.5, 80.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(144.5, 60.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 60.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(55.5, 60.0));

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
   TRY_TESTME(points.size() == 18);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(27.500000, -0.000000));
   TRY_TESTME(points[i++] == Point2d(35.875000, -33.250000));
   TRY_TESTME(points[i++] == Point2d(44.125000, -34.125000));
   TRY_TESTME(points[i++] == Point2d(44.500000, -40.000000));
   TRY_TESTME(points[i++] == Point2d(28.750000, -40.000000));
   TRY_TESTME(points[i++] == Point2d(27.000000, -18.375000));
   TRY_TESTME(points[i++] == Point2d(25.205357, -11.250000));
   TRY_TESTME(points[i++] == Point2d(22.205357, -8.250000));
   TRY_TESTME(points[i++] == Point2d(0.000000, -8.250000));
   TRY_TESTME(points[i++] == Point2d(-22.205357, -8.250000));
   TRY_TESTME(points[i++] == Point2d(-25.205357, -11.250000));
   TRY_TESTME(points[i++] == Point2d(-27.000000, -18.375000));
   TRY_TESTME(points[i++] == Point2d(-28.750000, -40.000000));
   TRY_TESTME(points[i++] == Point2d(-44.500000, -40.000000));
   TRY_TESTME(points[i++] == Point2d(-44.125000, -34.125000));
   TRY_TESTME(points[i++] == Point2d(-35.875000, -33.250000));
   TRY_TESTME(points[i++] == Point2d(-27.500000, 0.000000));
   TRY_TESTME(i == points.size());

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   TESTME_EPILOG("UBeam2");
}

#endif // _UNITTEST


