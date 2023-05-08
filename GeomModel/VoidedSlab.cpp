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
#include <GeomModel/VoidedSlab.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Rectangle.h>
#include <GeomModel/Circle.h>
#include <MathEx.h>

using namespace WBFL::Geometry;

VoidedSlab::VoidedSlab() :
   ShapeOnCompositeImpl()
{
}

VoidedSlab::VoidedSlab(Float64 h, Float64 w, Float64 d, Float64 s, IndexType nVoids, std::shared_ptr<Point2d>& hookPnt) :
   ShapeOnCompositeImpl(hookPnt), m_H(h),m_W(w),m_D(d), m_S(s), m_nVoids(nVoids)
{
}

VoidedSlab::~VoidedSlab()
{
}

void VoidedSlab::SetHeight(Float64 h)
{
   m_H = h;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetHeight() const
{
   return m_H;
}

void VoidedSlab::SetWidth(Float64 width)
{
   m_W = width;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetWidth() const
{
   return m_W;
}

void VoidedSlab::SetVoidDiameter(Float64 d)
{
   m_D = d;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetVoidDiameter() const
{
   return m_D;
}

void VoidedSlab::SetVoidSpacing(Float64 s)
{
   m_S = s;
   SetDirtyFlag();
}

Float64 VoidedSlab::GetVoidSpacing() const
{
   return m_S;
}

void VoidedSlab::SetVoidCount(IndexType nVoids)
{
   m_nVoids = nVoids;
   SetDirtyFlag();
}

IndexType VoidedSlab::GetVoidCount() const
{
   return m_nVoids;
}

void VoidedSlab::Offset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void VoidedSlab::Rotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> VoidedSlab::CreateClone() const
{
   return std::make_unique<VoidedSlab>(*this);
}

std::shared_ptr<Shape> VoidedSlab::GetSlabShape() const
{
   return GetComposite()->GetShape(0);
}

std::shared_ptr<Shape> VoidedSlab::GetVoidShape(IndexType voidIdx) const
{
   if (m_nVoids <= voidIdx)
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDINDEX);

   return GetComposite()->GetShape(voidIdx + 1);
}

#if defined _DEBUG
bool VoidedSlab::AssertValid() const
{
   return __super::AssertValid();
}

void VoidedSlab::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for VoidedSlab ***")<< WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

void VoidedSlab::OnUpdateComposite(std::unique_ptr<CompositeShape>& composite) const
{
   Rectangle slab(Point2d(0,0), m_W, m_H);
   composite->AddShape(slab);

   if (0 < m_nVoids)
   {
      Float64 x = -m_S * (m_nVoids - 1) / 2;
      Float64 y = 0;
      Float64 r = m_D / 2;
      for (IndexType i = 0; i < m_nVoids; i++)
      {
         Circle hole(Point2d(x, y), r);
         composite->AddShape(hole, CompositeShape::ShapeType::Void);

         x += m_S;
      }
   }

   // move the shape so that the bottom center is at (0,0)
   // this is the hook point
   composite->Offset(Size2d(0.0, m_H / 2));

   if (!IsZero(m_Rotation))
      composite->Rotate(Point2d(0, 0), m_Rotation);

   composite->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool VoidedSlab::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("VoidedSlab");

   VoidedSlab beam;

   // Use some real dimensions (WSDOT 1'-6" Voided Slab)
   beam.SetHeight(18);
   beam.SetWidth(48);
   beam.SetVoidSpacing(12.5);
   beam.SetVoidDiameter(0.833);
   beam.SetVoidCount(3);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -24.0));
   TRY_TESTME(IsEqual(box.Right(), 24.0));
   TRY_TESTME(IsEqual(box.Top(), 18.0));
   TRY_TESTME(IsEqual(box.Bottom(), 0.0));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 862.365062561));
   TRY_TESTME(IsEqual(props.GetIxx(), 23327.929095931002));
   TRY_TESTME(IsEqual(props.GetIyy(), 165717.62311274296));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 9.0));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
   TRY_TESTME(IsEqual(props.GetXleft(), 24.0));
   TRY_TESTME(IsEqual(props.GetXright(), 24.0));
   TRY_TESTME(IsEqual(props.GetYtop(), 9.0));
   TRY_TESTME(IsEqual(props.GetYbottom(), 9.0));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 132.));

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
   TRY_TESTME(points.size() == 4);

   int i = 0;
   TRY_TESTME(points[i++] == Point2d(24, 0));
   TRY_TESTME(points[i++] == Point2d(-24, 0));
   TRY_TESTME(points[i++] == Point2d(-24, 18));
   TRY_TESTME(points[i++] == Point2d(24, 18));

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
   p1.Move(-50, 0.50);
   p2.Move(50, 0.50);
   Line2d clipLine(p1, p2);

   auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 5);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(24, 0));
   TRY_TESTME(points[i++] == Point2d(-24, 0));
   TRY_TESTME(points[i++] == Point2d(-24, 0.5));
   TRY_TESTME(points[i++] == Point2d(24, 0.5));
   TRY_TESTME(points[i++] == Point2d(24, 0));

   // clip in other direction
   p1.Move(50, 0.50);
   p2.Move(-50, 0.50);

   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 4);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(-24, 0.5));
   TRY_TESTME(points[i++] == Point2d(-24, 18));
   TRY_TESTME(points[i++] == Point2d(24, 18));
   TRY_TESTME(points[i++] == Point2d(24, 0.5));

   //
   // ClipIn
   //
   Rect2d clipRect(-100, 1.5, 100, 16.5);
   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   points = clip->GetPolyPoints();

   TRY_TESTME(points.size() == 4);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(-24, 1.5));
   TRY_TESTME(points[i++] == Point2d(-24, 16.5));
   TRY_TESTME(points[i++] == Point2d(24, 16.5));
   TRY_TESTME(points[i++] == Point2d(24, 1.5));

   //
   // MoveEx (tests Offset as well)
   //
   Point2d from(0, 0);
   Point2d to(100, 100);

   beam.Move(from, to);

   // Check the points
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(124, 100));
   TRY_TESTME(points[i++] == Point2d(76, 100));
   TRY_TESTME(points[i++] == Point2d(76, 118));
   TRY_TESTME(points[i++] == Point2d(124, 118));

   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 4);
   i = 0;
   TRY_TESTME(points[i++] == Point2d(24, 0));
   TRY_TESTME(points[i++] == Point2d(-24, 0));
   TRY_TESTME(points[i++] == Point2d(-24, 18));
   TRY_TESTME(points[i++] == Point2d(24, 18));

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

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
   TRY_TESTME(*hookPnt == Point2d(124.0, 100.0));

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
   TRY_TESTME(*hookPnt == Point2d(76.0, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(124.0, 91.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 91.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(76.0, 91.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(124.0, 82.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 82.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(76.0, 82.0));

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

   i = 0;
   TRY_TESTME(points[i++] == Point2d(-24, 48));
   TRY_TESTME(points[i++] == Point2d(-24, 0));
   TRY_TESTME(points[i++] == Point2d(-42, 0));
   TRY_TESTME(points[i++] == Point2d(-42, 48)); 

   TESTME_EPILOG("VoidedSlab");
}

#endif // _UNITTEST



