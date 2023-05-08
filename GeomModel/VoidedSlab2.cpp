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
#include <GeomModel/VoidedSlab2.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Circle.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

VoidedSlab2::VoidedSlab2() :
   ShapeOnCompositeImpl()
{
}

VoidedSlab2::VoidedSlab2(Float64 h, Float64 w, Float64 d1, Float64 d2, Float64 h1, Float64 h2, Float64 s1, Float64 s2, Float64 c1, Float64 c2, Float64 c3, IndexType nVoids, bool bLeftBlockout, bool bRightBlockout, std::shared_ptr<Point2d>& hookPnt) :
   ShapeOnCompositeImpl(hookPnt), m_H(h),m_W(w),m_D1(d1), m_D2(d2), m_H1(h1), m_H2(h2), m_S1(s1), m_S2(s2), m_C1(c1), m_C2(c2), m_C3(c3), m_nVoids(nVoids), m_bLeftBlockout(bLeftBlockout), m_bRightBlockout(bRightBlockout)
{
}

VoidedSlab2::~VoidedSlab2()
{
}

void VoidedSlab2::SetHeight(Float64 h)
{
   m_H = h;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetHeight() const
{
   return m_H;
}

void VoidedSlab2::SetWidth(Float64 width)
{
   m_W = width;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetWidth() const
{
   return m_W;
}

void VoidedSlab2::SetExteriorVoidDiameter(Float64 d1)
{
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetExteriorVoidDiameter() const
{
   return m_D1;
}

void VoidedSlab2::SetInteriorVoidDiameter(Float64 d2)
{
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetInteriorVoidDiameter() const
{
   return m_D2;
}

void VoidedSlab2::SetExteriorVoidElevation(Float64 h1)
{
   m_H1 = h1;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetExteriorVoidElevation() const
{
   return m_H1;
}

void VoidedSlab2::SetInteriorVoidElevation(Float64 h2)
{
   m_H2 = h2;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetInteriorVoidElevation() const
{
   return m_H2;
}

void VoidedSlab2::SetExteriorVoidSpacing(Float64 s1)
{
   m_S1 = s1;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetExteriorVoidSpacing() const
{
   return m_S1;
}

void VoidedSlab2::SetInteriorVoidSpacing(Float64 s2)
{
   m_S2 = s2;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetInteriorVoidSpacing() const
{
   return m_S2;
}

void VoidedSlab2::SetVoidCount(IndexType nVoids)
{
   m_nVoids = nVoids;
   SetDirtyFlag();
}

IndexType VoidedSlab2::GetVoidCount() const
{
   return m_nVoids;
}

void VoidedSlab2::SetC1(Float64 c1)
{
   m_C1 = c1;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetC1() const
{
   return m_C1;
}

void VoidedSlab2::SetC2(Float64 c2)
{
   m_C2 = c2;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetC2() const
{
   return m_C2;
}

void VoidedSlab2::SetC3(Float64 c3)
{
   m_C3 = c3;
   SetDirtyFlag();
}

Float64 VoidedSlab2::GetC3() const
{
   return m_C3;
}

void VoidedSlab2::SetLeftBlockout(bool bBlockout)
{
   m_bLeftBlockout = bBlockout;
   SetDirtyFlag();
}

bool VoidedSlab2::GetLeftBlockout() const
{
   return m_bLeftBlockout;
}

void VoidedSlab2::SetRightBlockout(bool bBlockout)
{
   m_bRightBlockout = bBlockout;
   SetDirtyFlag();
}

bool VoidedSlab2::GetRightBlockout() const
{
   return m_bRightBlockout;
}

void VoidedSlab2::Offset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void VoidedSlab2::Rotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> VoidedSlab2::CreateClone() const
{
   return std::make_unique<VoidedSlab2>(*this);
}

std::shared_ptr<Shape> VoidedSlab2::GetSlabShape() const
{
   return GetComposite()->GetShape(0);
}

std::shared_ptr<Shape> VoidedSlab2::GetVoidShape(IndexType voidIdx) const
{
   if (m_nVoids <= voidIdx)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   return GetComposite()->GetShape(voidIdx + 1);
}

#if defined _DEBUG
bool VoidedSlab2::AssertValid() const
{
   return __super::AssertValid();
}

void VoidedSlab2::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for VoidedSlab2 ***")<< WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

void VoidedSlab2::OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const
{
   // Create the main slab "rectangle" using a polygon, since it has clipped corners
   std::unique_ptr<Polygon> slab = std::make_unique<Polygon>();

   // bottom right corner
   slab->AddPoint(m_W / 2 - m_C3, 0);
   slab->AddPoint(m_W / 2, m_C3);

   if (m_bRightBlockout)
   {
      slab->AddPoint(m_W / 2, m_H - m_C1 - m_C2);
      slab->AddPoint(m_W / 2 - m_C1, m_H - m_C2);
      slab->AddPoint(m_W / 2 - m_C1, m_H);
   }
   else
   {
      slab->AddPoint(m_W / 2, m_H);
   }

   if (m_bLeftBlockout)
   {
      slab->AddPoint(-m_W / 2 + m_C1, m_H);
      slab->AddPoint(-m_W / 2 + m_C1, m_H - m_C2);
      slab->AddPoint(-m_W / 2, m_H - m_C1 - m_C2);
   }
   else
   {
      slab->AddPoint(-m_W / 2, m_H);
   }

   // bottom left corner
   slab->AddPoint(-m_W / 2, m_C3);
   slab->AddPoint(-m_W / 2 + m_C3, 0);

   slab->RemoveDuplicatePoints();

   composite->AddShape(std::move(slab));

   if (m_nVoids == 0)
   {
      // do nothing
   }
   else if (m_nVoids == 1)
   {
      // put an exterior void in the center of the beam
      std::unique_ptr<Circle> center_void = std::make_unique<Circle>(Point2d(0, m_H1), m_D1 / 2);
      composite->AddShape(std::move(center_void),CompositeShape::ShapeType::Void);
   }
   else if (m_nVoids == 2)
   {
      // left exterior void
      std::unique_ptr<Circle> left_exterior_void = std::make_unique<Circle>(Point2d(-m_S1 / 2, m_H1), m_D1 / 2);
      composite->AddShape(std::move(left_exterior_void), CompositeShape::ShapeType::Void);

      // right exterior void
      std::unique_ptr<Circle> right_exterior_void = std::make_unique<Circle>(Point2d(m_S1 / 2, m_H1), m_D1 / 2);
      composite->AddShape(std::move(right_exterior_void), CompositeShape::ShapeType::Void);
   }
   else
   {
      // center the two exterior voids
      IndexType nIntVoids = m_nVoids - 2;

      Float64 x = m_S1 + m_S2 * (nIntVoids - 1) / 2;

      // left exterior void
      std::unique_ptr<Circle> left_exterior_void = std::make_unique<Circle>(Point2d(-x, m_H1), m_D1 / 2);
      composite->AddShape(std::move(left_exterior_void), CompositeShape::ShapeType::Void);

      // right exterior void
      std::unique_ptr<Circle> right_exterior_void = std::make_unique<Circle>(Point2d(x,m_H1), m_D1 / 2);
      composite->AddShape(std::move(right_exterior_void), CompositeShape::ShapeType::Void);

      // interior voids
      x = -m_S2 * (nIntVoids - 1) / 2;
      for (IndexType voidIdx = 0; voidIdx < nIntVoids; voidIdx++)
      {
         std::unique_ptr<Circle> interior_void = std::make_unique<Circle>(Point2d(x, m_H2), m_D2 / 2);
         composite->AddShape(std::move(interior_void), CompositeShape::ShapeType::Void);
         x += m_S2;
      }
   }

   if (!IsZero(m_Rotation))
      composite->Rotate(Point2d(0, 0), m_Rotation);

   composite->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool VoidedSlab2::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("VoidedSlab2");

   VoidedSlab2 beam;

   beam.SetHeight(36);
   beam.SetWidth(260);
   beam.SetExteriorVoidDiameter(20);
   beam.SetInteriorVoidDiameter(30);
   beam.SetExteriorVoidElevation(12);
   beam.SetInteriorVoidElevation(18);
   beam.SetInteriorVoidSpacing(45);
   beam.SetExteriorVoidSpacing(45);
   beam.SetVoidCount(5);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -130.0));
   TRY_TESTME(IsEqual(box.Right(), 130.0));
   TRY_TESTME(IsEqual(box.Top(), 36.0));
   TRY_TESTME(IsEqual(box.Bottom(), 0.0));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 6611.1064281089311));
   TRY_TESTME(IsEqual(props.GetIxx(), 851120.47291073855));
   TRY_TESTME(IsEqual(props.GetIyy(), 44640853.286266908));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 18.570239070464662));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
   TRY_TESTME(IsEqual(props.GetXleft(), 130.0));
   TRY_TESTME(IsEqual(props.GetXright(), 130.0));
   TRY_TESTME(IsEqual(props.GetYtop(), 17.429760929535338));
   TRY_TESTME(IsEqual(props.GetYbottom(), 18.570239070464662));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 592.));

   //
   // FurthestDistance
   //
    
   // Shape on right
   Point2d p1(0, 50);
   Point2d p2(100, 50);
   Line2d line(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 50.000));

   // shape on left
   p1.Move(0, -50);
   p2.Move(100, -50);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -50.000));

   // 
   // PolyPoints
   //
   auto points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   int i = 0;
   TRY_TESTME(points[i++] == Point2d(130.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(130.000000, 36.000000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 36.000000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // PointInShape
   //
   Point2d pnt(0.0, 1.0);
   TRY_TESTME(beam.PointInShape(pnt) == true);

   pnt.Move(500, 500);
   TRY_TESTME(beam.PointInShape(pnt) == false);

   pnt.Move(0, 0); // Point on perimeter
   TRY_TESTME(beam.PointInShape(pnt) == false);

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   //
   // ClipWithLine
   //

   // setup clipping line
   // setup clipping line
   p1.Move(-50, 0.50);
   p2.Move(50, 0.50);
   Line2d clipLine(p1, p2);

   auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 5);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(130.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(130.000000, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 0.500000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(130.000000, 0.000000));
   TRY_TESTME(i == points.size());

   // clip in other direction
   p1.Move(50, 0.50);
   p2.Move(-50, 0.50);

   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(130.000000, 0.500000));
   TRY_TESTME(points[i++] == Point2d(130.000000, 36.000000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 36.000000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 0.500000));
   TRY_TESTME(i == points.size());

   //
   // ClipIn
   //
   Rect2d clipRect(-100, 1.5, 100, 16.5);
   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   points = clip->GetPolyPoints();

   TRY_TESTME(points.size() == 5);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(100.000000, 16.500000));
   TRY_TESTME(points[i++] == Point2d(-100.000000, 16.500000));
   TRY_TESTME(points[i++] == Point2d(-100.000000, 1.500000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 1.500000));
   TRY_TESTME(points[i++] == Point2d(100.000000, 16.500000));
   TRY_TESTME(i == points.size());

   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);

   beam.Move(from, to);

   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(230.000000, 100.000000));
   TRY_TESTME(points[i++] == Point2d(230.000000, 136.000000));
   TRY_TESTME(points[i++] == Point2d(-30.000000, 136.000000));
   TRY_TESTME(points[i++] == Point2d(-30.000000, 100.000000));
   TRY_TESTME(i == points.size());

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(130.000000, 0.000000));
   TRY_TESTME(points[i++] == Point2d(130.000000, 36.000000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 36.000000));
   TRY_TESTME(points[i++] == Point2d(-130.000000, 0.000000));
   TRY_TESTME(i == points.size());

   //
   // LocatorPoint property
   //
   auto hookPnt = beam.GetHookPoint();
   hookPnt->Move(0, 0);

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(230.0, 100.0));

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
   TRY_TESTME(*hookPnt == Point2d(-30.0, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(230.0, 82.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 82.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(-30.0, 82.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(230.0, 64.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 64.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(-30.0, 64.0));

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
   Point2d c(-24, 0);

   beam.Rotate(c, PI_OVER_2);

   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-24.000000, 154.000000));
   TRY_TESTME(points[i++] == Point2d(-60.000000, 154.000000));
   TRY_TESTME(points[i++] == Point2d(-60.000000, -106.000000));
   TRY_TESTME(points[i++] == Point2d(-24.000000, -106.000000));
   TRY_TESTME(i == points.size());

   TESTME_EPILOG("VoidedSlab");
}

#endif // _UNITTEST



