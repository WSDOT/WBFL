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
#include <GeomModel/DeckedSlabBeam.h>
#include <GeomModel/Polygon.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

DeckedSlabBeam::DeckedSlabBeam() :
   ShapeOnCompositeImpl()
{
}

DeckedSlabBeam::DeckedSlabBeam(Float64 a, Float64 b, Float64 c, Float64 w, Float64 tt, Float64 tb, Float64 f, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, std::shared_ptr<Point2d>& hookPnt) :
ShapeOnCompositeImpl(hookPnt),m_A(a),m_B(b),m_C(c),m_W(w), m_Tt(tt), m_Tb(tb), m_F(f), m_nVoids(nVoids), m_bLeftBlockout(bLeftBlockout),m_bRightBlockout(bRightBlockout)
{
}

DeckedSlabBeam::DeckedSlabBeam(Float64 a, Float64 b, Float64 c, Float64 w, Float64 tt, Float64 tb, Float64 f, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, const Point2d& hookPnt) :
ShapeOnCompositeImpl(hookPnt),m_A(a), m_B(b), m_C(c), m_W(w), m_Tt(tt), m_Tb(tb), m_F(f), m_nVoids(nVoids), m_bLeftBlockout(bLeftBlockout), m_bRightBlockout(bRightBlockout)
{
}

DeckedSlabBeam::~DeckedSlabBeam()
{
}

void DeckedSlabBeam::SetA(Float64 a) { m_A = a; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetA() const { return m_A; }

void DeckedSlabBeam::SetB(Float64 b) { m_B = b; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetB() const { return m_B; }

void DeckedSlabBeam::SetC(Float64 c) { m_C = c; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetC() const { return m_C; }

void DeckedSlabBeam::SetW(Float64 w) { m_W = w; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetW() const { return m_W; }

void DeckedSlabBeam::SetTt(Float64 tt) { m_Tt = tt; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetTt() const { return m_Tt; }

void DeckedSlabBeam::SetTb(Float64 tb) { m_Tb = tb; SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetTb() const { return m_Tb; }

void DeckedSlabBeam::SetF(Float64 f) { m_F = f;  SetDirtyFlag(); }
Float64 DeckedSlabBeam::GetF() const { return m_F; }

void DeckedSlabBeam::SetVoidCount(IndexType nVoids)
{
   if (1 < nVoids) THROW_GEOMETRY(_T("DeckedSlabBeam::SetVoidCount - number of voids can only be 0 or 1"));

   m_nVoids = nVoids;
   SetDirtyFlag();
}

IndexType DeckedSlabBeam::GetVoidCount() const { return m_nVoids; }

void DeckedSlabBeam::SetLeftBlockout(bool bBlockout) { m_bLeftBlockout = bBlockout;  SetDirtyFlag(); }
bool DeckedSlabBeam::GetLeftBlockout() const { return m_bLeftBlockout; }

void DeckedSlabBeam::SetRightBlockout(bool bBlockout) { m_bRightBlockout = bBlockout;  SetDirtyFlag(); }
bool DeckedSlabBeam::GetRightBlockout() const { return m_bRightBlockout; }

Float64 DeckedSlabBeam::GetHeight() const
{
   return m_Tt + m_C;
}

void DeckedSlabBeam::Offset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void DeckedSlabBeam::Rotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> DeckedSlabBeam::CreateClone() const
{
   return std::make_unique<DeckedSlabBeam>(*this);
}

std::shared_ptr<Shape> DeckedSlabBeam::GetSlabShape() const
{
   return GetComposite()->GetShape(0);
}

std::shared_ptr<Shape> DeckedSlabBeam::GetVoidShape(IndexType voidIdx) const
{
   if (m_nVoids <= voidIdx) THROW_GEOMETRY(_T("DeckedSlabBeam::GetVoidShape - invalid index"));

   return GetComposite()->GetShape(voidIdx + 1);
}
#if defined _DEBUG
bool DeckedSlabBeam::AssertValid() const
{
   return __super::AssertValid();
}

void DeckedSlabBeam::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for DeckedSlabBeam ***")<< WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

void DeckedSlabBeam::OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const
{
   // Create the outer shape
   std::unique_ptr<Polygon> slab = std::make_unique<Polygon>();
   Float64 Wb = m_A - 2 * m_B;

   slab->AddPoint(0, 0);
   slab->AddPoint(Wb / 2, 0.0);  // bottom right corner
   slab->AddPoint(Wb / 2, m_C);
   slab->AddPoint(m_A / 2, m_C);

   if (m_bRightBlockout)
   {
      slab->AddPoint(m_A / 2 - m_F, m_C + m_Tt);
   }
   else
   {
      slab->AddPoint(m_A / 2, m_C + m_Tt);
   }

   if (m_bRightBlockout == m_bLeftBlockout)
   {
      // the shape is symmetric about the X = 0 axis
      slab->AddPoint(0, m_C + m_Tt);
      slab->SetSymmetry(Polygon::Symmetry::Y, 0.0);
   }
   else
   {
      // the shape is not symmetric

      // top left corner
      if (m_bLeftBlockout)
      {
         slab->AddPoint(-(m_A / 2 - m_F), m_C + m_Tt);
      }
      else
      {
         slab->AddPoint(-m_A / 2, m_C + m_Tt);
      }

      slab->AddPoint(-m_A / 2, m_C);
      slab->AddPoint(-Wb / 2, m_C);
      slab->AddPoint(-Wb / 2, 0.0);
   }

   composite->AddShape(std::move(slab));

   // put an exterior void in the center of the beam
   if (0 < m_nVoids)
   {
      std::unique_ptr<Polygon> void_shape = std::make_unique<Polygon>();
      Float64 Wv2 = (Wb - 2 * m_W) / 2.0; // half width of void
      void_shape->AddPoint(0, m_Tb);
      void_shape->AddPoint(Wv2, m_Tb);
      void_shape->AddPoint(Wv2, m_C);
      void_shape->AddPoint(0, m_C);
      void_shape->SetSymmetry(Polygon::Symmetry::Y); // the void is always symmetric about the X=0 axis
      composite->AddShape(std::move(void_shape),CompositeShape::ShapeType::Void);
   }

   if (!IsZero(m_Rotation))
      composite->Rotate(Point2d(0, 0), m_Rotation);

   composite->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool DeckedSlabBeam::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("DeckedSlabBeam");

   // 6DS20
   DeckedSlabBeam beam;
   Float64 A = 77.75;
   beam.SetA(A);
   beam.SetB(9.0);
   beam.SetC(12.0);
   beam.SetW(6.0);
   beam.SetTt(8.0);
   beam.SetTb(7.0);
   beam.SetF(1.75);
   beam.SetLeftBlockout(true);
   beam.SetRightBlockout(true);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -A / 2.0));
   TRY_TESTME(IsEqual(box.Right(), A / 2.0));
   TRY_TESTME(IsEqual(box.Top(), 20.0));
   TRY_TESTME(IsEqual(box.Bottom(), 0.0));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();

   Float64 d_area = 1086.25;
   Float64 d_ixx = 43711.5237997;
   Float64 d_iyy = 460753.3242187;
   Float64 d_cgy = 10.81077867;

   // datum values
   TRY_TESTME(IsEqual(props.GetArea(), d_area));
   TRY_TESTME(IsEqual(props.GetIxx(), d_ixx));
   TRY_TESTME(IsEqual(props.GetIyy(), d_iyy));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), d_cgy));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), A / 2.0));
   TRY_TESTME(IsEqual(props.GetXright(), A / 2.0));
   TRY_TESTME(IsEqual(props.GetYtop(), 20 - d_cgy));
   TRY_TESTME(IsEqual(props.GetYbottom(), d_cgy));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 192.378339));

   //
   // FurthestDistance
   //
   Point2d p1(0, 50);
   Point2d p2(100, 50);
   Line2d line(p1, p2);

   // Shape on right
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 50.0));

   // shape on left
   p1.Move(0, -50);
   p2.Move(100, -50);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -50.0));

   // 
   // PolyPoints
   //
   auto points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 10);

   Float64 Wb2 = (A - 9 * 2) / 2.0;

   int i = 0;
   TRY_TESTME(points[i++] == Point2d(0.0, 0.0));
   TRY_TESTME(points[i++] == Point2d(Wb2,  0.0));
   TRY_TESTME(points[i++] == Point2d(Wb2, 12.0));
   TRY_TESTME(points[i++] == Point2d(A/2, 12.0));
   TRY_TESTME(points[i++] == Point2d(A / 2 - 1.75, 20.0));
   TRY_TESTME(points[i++] == Point2d(0.0, 20.0));
   TRY_TESTME(points[i++] == Point2d(-(A/2 - 1.75), 20.0));
   TRY_TESTME(points[i++] == Point2d(-A/2, 12.0));
   TRY_TESTME(points[i++] == Point2d(-Wb2, 12.0));
   TRY_TESTME(points[i++] == Point2d(-Wb2, 0.0));
   TRY_TESTME(i == points.size());

   //
   // PointInShape
   //
   Point2d pnt(0, 1);
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
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 6);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(29.875000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(29.875000, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(i == points.size());

   // clip in other direction
   p1.Move(50, 0.50);
   p2.Move(-50, 0.50);
   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   points = clip->GetPolyPoints();

   TRY_TESTME(points.size() == 9);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(29.875000, 0.500000));
   TRY_TESTME(points[i++] == Point2d(29.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(38.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(37.125000, 20.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 20.000000));
   TRY_TESTME(points[i++] == Point2d(-37.125000, 20.000000));
   TRY_TESTME(points[i++] == Point2d(-38.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 0.500000));
   TRY_TESTME(i == points.size());

   //
   // ClipIn
   //
   Rect2d clipRect(-100, 1.5, 100, 11.0);
   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   points = clip->GetPolyPoints();

   TRY_TESTME(points.size() == 4);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(29.875000, 1.500000));
   TRY_TESTME(points[i++] == Point2d(29.875000, 11.000000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 11.000000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 1.500000));
   TRY_TESTME(i == points.size());

   // Remove void
   beam.SetVoidCount(0);
   props = beam.GetProperties();

   d_area = 1325.0;
   d_ixx = 44545.211236897274;
   d_iyy = 506117.06770833326;
   d_cgy = 10.574591194968553;

   TRY_TESTME(IsEqual(props.GetArea(), d_area));
   TRY_TESTME(IsEqual(props.GetIxx(), d_ixx));
   TRY_TESTME(IsEqual(props.GetIyy(), d_iyy));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), d_cgy));
   

   std::shared_ptr<Point2d> hookPnt = std::make_shared<Point2d>(0, 0);

   // 6DS20
   beam.SetHookPoint(hookPnt);

   // Get moment of inertia about CG before move
   // These properties should be invariant
   props = beam.GetProperties();
   Float64 area = props.GetArea();
   Float64 Ixx = props.GetIxx();
   Float64 Iyy = props.GetIyy();

   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);

   beam.Move(from, to);

   // Check the points
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 10);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(100.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(129.875000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(129.875000, 112.000000));
   TRY_TESTME(points[i++] == Point2d(138.875000, 112.000000));
   TRY_TESTME(points[i++] == Point2d(137.125000, 120.000000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 120.000000));
   TRY_TESTME(points[i++] == Point2d(62.875000, 120.000000));
   TRY_TESTME(points[i++] == Point2d(61.125000, 112.000000));
   TRY_TESTME(points[i++] == Point2d(70.125000, 112.000000));
   TRY_TESTME(points[i++] == Point2d(70.125000, 100.000000));
   TRY_TESTME(i == points.size());

   props = beam.GetProperties();
   TRY_TESTME(IsEqual(area, props.GetArea()));
   TRY_TESTME(IsEqual(Ixx, props.GetIxx()));
   TRY_TESTME(IsEqual(Iyy, props.GetIyy()));

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);

   // Check the points
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 10);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(29.875000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(29.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(38.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(37.125000, 20.000000));
   TRY_TESTME(points[i++] == Point2d(0.000000, 20.000000));
   TRY_TESTME(points[i++] == Point2d(-37.125000, 20.000000));
   TRY_TESTME(points[i++] == Point2d(-38.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 12.000000));
   TRY_TESTME(points[i++] == Point2d(-29.875000, 0.000000));
   TRY_TESTME(i == points.size());

   props = beam.GetProperties();
   TRY_TESTME(IsEqual(area, props.GetArea()));
   TRY_TESTME(IsEqual(Ixx, props.GetIxx()));
   TRY_TESTME(IsEqual(Iyy, props.GetIyy()));


   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   //
   // LocatorPoint property
   //

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(138.875, 100.0));

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
   TRY_TESTME(*hookPnt == Point2d(61.125, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(138.875, 90.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 90.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(61.125, 90.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(138.875, 80.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 80.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(61.125, 80.0));

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
   Point2d c(-38.875, 0.0);

   beam.Rotate(c, PI_OVER_2);

   // Check the points
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 10);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(-38.875000, 38.875000));
   TRY_TESTME(points[i++] == Point2d(-38.875000, 68.750000));
   TRY_TESTME(points[i++] == Point2d(-50.875000, 68.750000));
   TRY_TESTME(points[i++] == Point2d(-50.875000, 77.750000));
   TRY_TESTME(points[i++] == Point2d(-58.875000, 76.000000));
   TRY_TESTME(points[i++] == Point2d(-58.875000, 38.875000));
   TRY_TESTME(points[i++] == Point2d(-58.875000, 1.750000));
   TRY_TESTME(points[i++] == Point2d(-50.875000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(-50.875000, 9.000000));
   TRY_TESTME(points[i++] == Point2d(-38.875000, 9.000000));
   TRY_TESTME(i == points.size());

   TESTME_EPILOG("DeckedSlabBeam");
}

#endif // _UNITTEST



