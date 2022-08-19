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
#include <GeomModel/MultiWeb.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/Polygon.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

MultiWeb::MultiWeb() :
   ShapeOnPolygonImpl()
{
}

MultiWeb::MultiWeb(Float64 w1, Float64 w2, Float64 d1, Float64 d2, Float64 t1, Float64 t2, IndexType nWebs, std::shared_ptr<Point2d>& hookPnt) :
   ShapeOnPolygonImpl(hookPnt), m_W1(w1),m_W2(w2),m_D1(d1), m_D2(d2), m_T1(t1), m_T2(t2), m_WebCount(nWebs)
{
}

MultiWeb::~MultiWeb()
{
}

void MultiWeb::SetW1(Float64 w1)
{
   m_W1 = w1;
   SetDirtyFlag();
}

Float64 MultiWeb::GetW1() const
{
   return m_W1;
}

void MultiWeb::SetW2(Float64 w2)
{
   m_W2 = w2;
   SetDirtyFlag();
}

Float64 MultiWeb::GetW2() const
{
   return m_W2;
}

void MultiWeb::SetD1(Float64 d1)
{
   m_D1 = d1;
   SetDirtyFlag();
}

Float64 MultiWeb::GetD1() const
{
   return m_D1;
}

void MultiWeb::SetD2(Float64 d2)
{
   m_D2 = d2;
   SetDirtyFlag();
}

Float64 MultiWeb::GetD2() const
{
   return m_D2;
}

void MultiWeb::SetT1(Float64 t1)
{
   m_T1 = t1;
   SetDirtyFlag();
}

Float64 MultiWeb::GetT1() const
{
   return m_T1;
}

void MultiWeb::SetT2(Float64 t2)
{
   m_T2 = t2;
   SetDirtyFlag();
}

Float64 MultiWeb::GetT2() const
{
   return m_T2;
}

void MultiWeb::SetWebCount(WebIndexType nWebs)
{
   m_WebCount = nWebs;
   SetDirtyFlag();
}

WebIndexType MultiWeb::GetWebCount() const
{
   return m_WebCount;
}

Float64 MultiWeb::GetWebLocation(WebIndexType webIdx)
{
   if (m_WebCount <= webIdx) THROW_GEOMETRY(_T("MultiWeb::GetWebLocation - invalid web index"));

   Float64 W = GetTopFlangeWidth();

   return (m_W1 + webIdx * (m_W2 + m_T1) + m_T1 / 2) - W / 2;
}

Float64 MultiWeb::GetTopFlangeWidth() const
{
   return 2 * m_W1 + m_WebCount * m_T1 + (m_WebCount - 1) * m_W2;
}

Float64 MultiWeb::GetAvgWebWidth() const
{
   return m_WebCount * (m_T1 + m_T2) / 2.;
}

Float64 MultiWeb::GetHeight() const
{
   return m_D1 + m_D2;
}

void MultiWeb::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void MultiWeb::DoRotate(const Point2d& center, Float64 angle)
{
   m_Rotation += angle;

   // our shape uses symmetry - once the shape is rotated, symmetry with the Y axis is broken
   // rotating the polygon causes the full set of points to be modeled and the symmetry 
   // property set to None
   GetPolygon()->Rotate(center, angle);
   SetDirtyFlag();
}

std::unique_ptr<Shape> MultiWeb::CreateClone() const
{
   return std::make_unique<MultiWeb>(*this);
}

#if defined _DEBUG
bool MultiWeb::AssertValid() const
{
   return __super::AssertValid();
}

void MultiWeb::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for MultiWeb ***")<< WBFL::Debug::endl;
   __super::Dump( os );
}
#endif // _DEBUG

void MultiWeb::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   Float64 width = 2 * m_W1 + m_WebCount * m_T1 + (m_WebCount - 1) * m_W2;

   polygon->AddPoint(0, 0); // top center
   polygon->AddPoint(-width / 2, 0); // top left
   polygon->AddPoint(-width / 2, -m_D1);

   WebIndexType nFullWebs = (m_WebCount < 2 ? 0 : m_WebCount / 2);
   WebIndexType nHalfWebs = (nFullWebs == 0 ? 0 : m_WebCount / 2 - nFullWebs + IsOdd(m_WebCount) ? 1 : 0);
   for (WebIndexType i = 0; i < nFullWebs; i++)
   {
      Float64 web_x1 = -width/2 + m_W1 + i * (m_W2 + m_T1);
      Float64 web_y1 = -m_D1;

      Float64 web_x2 = web_x1 + m_T1 / 2 - m_T2 / 2;
      Float64 web_y2 = -m_D1 - m_D2;

      Float64 web_x3 = web_x2 + m_T2;
      Float64 web_y3 = -m_D1 - m_D2;

      Float64 web_x4 = web_x1 + m_T1;
      Float64 web_y4 = -m_D1;

      polygon->AddPoint(web_x1, web_y1);
      polygon->AddPoint(web_x2, web_y2);
      polygon->AddPoint(web_x3, web_y3);
      polygon->AddPoint(web_x4, web_y4);

      if (nHalfWebs == 0)
         polygon->AddPoint(web_x4 + m_W2 / 2, web_y4); // point half-way to the next web
   }

   if (nHalfWebs != 0)
   {
      Float64 web_x1 = -width / 2 + m_W1 + nFullWebs * (m_T1 + m_W2);
      Float64 web_y1 = -m_D1;

      Float64 web_x2 = web_x1 + m_T1 / 2 - m_T2 / 2;
      Float64 web_y2 = -m_D1 - m_D2;
      polygon->AddPoint(web_x1, web_y1);
      polygon->AddPoint(web_x2, web_y2);
      polygon->AddPoint(web_x2 + m_T2 / 2, web_y2); // point at bottom-CL of web
   }

   polygon->SetSymmetry(Polygon::Symmetry::Y);

   if (!IsZero(m_Rotation))
      polygon->Rotate(Point2d(0, 0), m_Rotation);

   polygon->Move(Point2d(0, 0), *GetHookPoint());
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool MultiWeb::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("MultiWeb");

   // Use some real dimensions (2'-3" by 6' with 3 webs)
   MultiWeb beam;
   beam.SetD1(6.00);
   beam.SetD2(21.00);
   beam.SetW1(13.125);
   beam.SetW2(12.0);
   beam.SetT1(7.25);
   beam.SetT2(5.25);
   beam.SetWebCount(3);

   //
   // Bounding Box
   //
   Rect2d box = beam.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), -36.));
   TRY_TESTME(IsEqual(box.Right(), 36.));
   TRY_TESTME(IsEqual(box.Top(), 0.));
   TRY_TESTME(IsEqual(box.Bottom(), -27.));

   //
   // ShapeProperties
   //
   ShapeProperties props = beam.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), 825.75));
   TRY_TESTME(IsEqual(props.GetIxx(), 50135.30160));
   TRY_TESTME(IsEqual(props.GetIyy(), 285211.20703));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), -9.1702997275204368));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 36.));
   TRY_TESTME(IsEqual(props.GetXright(), 36.));
   TRY_TESTME(IsEqual(props.GetYtop(), 9.17029972752044));
   TRY_TESTME(IsEqual(props.GetYbottom(), 17.8297002724796));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(beam.GetPerimeter(), 276.142776249772));

   //
   // FurthestDistance
   //

   // Shape on right of line
   Point2d p1(-100, 20);
   Point2d p2(100, 20);
   Line2d line(p1, p2);

   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 47.0));

   // shape on left of line
   p1.Move(100, 20);
   p2.Move(-100, 20);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.0));

   // 
   // PolyPoints
   //
   auto points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 19);

   int i = 0;
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(points[i++] == Point2d(-36, 0));
   TRY_TESTME(points[i++] == Point2d(-36, -6));
   TRY_TESTME(points[i++] == Point2d(-22.875, -6));
   TRY_TESTME(points[i++] == Point2d(-21.875, -27));
   TRY_TESTME(points[i++] == Point2d(-16.625, -27));
   TRY_TESTME(points[i++] == Point2d(-15.625, -6));
   TRY_TESTME(points[i++] == Point2d(-3.625, -6));
   TRY_TESTME(points[i++] == Point2d(-2.625, -27));
   TRY_TESTME(points[i++] == Point2d(0, -27));
   TRY_TESTME(points[i++] == Point2d(2.625, -27));
   TRY_TESTME(points[i++] == Point2d(3.625, -6));
   TRY_TESTME(points[i++] == Point2d(15.625, -6));
   TRY_TESTME(points[i++] == Point2d(16.625, -27));
   TRY_TESTME(points[i++] == Point2d(21.875, -27));
   TRY_TESTME(points[i++] == Point2d(22.875, -6));
   TRY_TESTME(points[i++] == Point2d(36, -6));
   TRY_TESTME(points[i++] == Point2d(36, 0));
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(i == points.size());

   //
   // PointInShape
   //
   Point2d pnt(0, -5);
   TRY_TESTME(beam.PointInShape(pnt) == true);

   pnt.Move(500, 500);
   TRY_TESTME(beam.PointInShape(pnt) == false);

   pnt.Move(0, 0); // Point on perimeter
   TRY_TESTME(beam.PointInShape(pnt) == false);

   //
   // ClipWithLine
   //

   // setup clipping line
   p1.Move(-100, -10.0);
   p2.Move(100, -10.0);

   Line2d clipLine(p1, p2);

   auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 13);
   
   i = 0;
   TRY_TESTME(points[i++] == Point2d(-22.68452, -10));
   TRY_TESTME(points[i++] == Point2d(-21.875, -27));
   TRY_TESTME(points[i++] == Point2d(-16.625, -27));
   TRY_TESTME(points[i++] == Point2d(-15.81548, -10));
   TRY_TESTME(points[i++] == Point2d(-3.43452, -10));
   TRY_TESTME(points[i++] == Point2d(-2.625, -27));
   TRY_TESTME(points[i++] == Point2d(0, -27));
   TRY_TESTME(points[i++] == Point2d(2.625, -27));
   TRY_TESTME(points[i++] == Point2d(3.43452, -10));
   TRY_TESTME(points[i++] == Point2d(15.81548, -10));
   TRY_TESTME(points[i++] == Point2d(16.625, -27));
   TRY_TESTME(points[i++] == Point2d(21.875, -27));
   TRY_TESTME(points[i++] == Point2d(22.68452, -10));
   TRY_TESTME(i == points.size());

   // clip in other direction
   p1.Move(100, -10.0);
   p2.Move(-100, -10.0);
   clipLine.ThroughPoints(p1, p2);

   clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 18);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(points[i++] == Point2d(-36, 0));
   TRY_TESTME(points[i++] == Point2d(-36, -6));
   TRY_TESTME(points[i++] == Point2d(-22.875, -6));
   TRY_TESTME(points[i++] == Point2d(-22.68452, -10));
   TRY_TESTME(points[i++] == Point2d(-15.815476, -10));
   TRY_TESTME(points[i++] == Point2d(-15.625, -6));
   TRY_TESTME(points[i++] == Point2d(-3.625, -6));
   TRY_TESTME(points[i++] == Point2d(-3.43452, -10));
   TRY_TESTME(points[i++] == Point2d(3.43452, -10));
   TRY_TESTME(points[i++] == Point2d(3.625, -6));
   TRY_TESTME(points[i++] == Point2d(15.625, -6));
   TRY_TESTME(points[i++] == Point2d(15.815476, -10));
   TRY_TESTME(points[i++] == Point2d(22.68452, -10));
   TRY_TESTME(points[i++] == Point2d(22.875, -6));
   TRY_TESTME(points[i++] == Point2d(36, -6));
   TRY_TESTME(points[i++] == Point2d(36, 0));
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(i == points.size());

   //
   // ClipIn
   //
   Rect2d clipRect(-100, -7, 100, 10);

   clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 18);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(points[i++] == Point2d(-36, 0));
   TRY_TESTME(points[i++] == Point2d(-36, -6));
   TRY_TESTME(points[i++] == Point2d(-22.875, -6));
   TRY_TESTME(points[i++] == Point2d(-22.82738, -7));
   TRY_TESTME(points[i++] == Point2d(-15.67262, -7));
   TRY_TESTME(points[i++] == Point2d(-15.625, -6));
   TRY_TESTME(points[i++] == Point2d(-3.625, -6));
   TRY_TESTME(points[i++] == Point2d(-3.57738, -7));
   TRY_TESTME(points[i++] == Point2d(3.57738, -7));
   TRY_TESTME(points[i++] == Point2d(3.625, -6));
   TRY_TESTME(points[i++] == Point2d(15.625, -6));
   TRY_TESTME(points[i++] == Point2d(15.67262, -7));
   TRY_TESTME(points[i++] == Point2d(22.82738, -7));
   TRY_TESTME(points[i++] == Point2d(22.875, -6));
   TRY_TESTME(points[i++] == Point2d(36, -6));
   TRY_TESTME(points[i++] == Point2d(36, 0));
   TRY_TESTME(points[i++] == Point2d(0, 0));
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
   TRY_TESTME(points[i++] == Point2d(100, 100));
   TRY_TESTME(points[i++] == Point2d(64, 100));
   TRY_TESTME(points[i++] == Point2d(64, 94));
   TRY_TESTME(points[i++] == Point2d(77.125, 94));
   TRY_TESTME(points[i++] == Point2d(78.125, 73));
   TRY_TESTME(points[i++] == Point2d(83.375, 73));
   TRY_TESTME(points[i++] == Point2d(84.375, 94));
   TRY_TESTME(points[i++] == Point2d(96.375, 94));
   TRY_TESTME(points[i++] == Point2d(97.375, 73));
   TRY_TESTME(points[i++] == Point2d(100, 73));
   TRY_TESTME(points[i++] == Point2d(102.625, 73));
   TRY_TESTME(points[i++] == Point2d(103.625, 94));
   TRY_TESTME(points[i++] == Point2d(115.625, 94));
   TRY_TESTME(points[i++] == Point2d(116.625, 73));
   TRY_TESTME(points[i++] == Point2d(121.875, 73));
   TRY_TESTME(points[i++] == Point2d(122.875, 94));
   TRY_TESTME(points[i++] == Point2d(136, 94));
   TRY_TESTME(points[i++] == Point2d(136, 100));
   TRY_TESTME(points[i++] == Point2d(100, 100));
   TRY_TESTME(i == points.size());


   //
   // OffsetEx
   //
   Size2d size(-100, -100);
   beam.Offset(size);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 19);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(points[i++] == Point2d(-36, 0));
   TRY_TESTME(points[i++] == Point2d(-36, -6));
   TRY_TESTME(points[i++] == Point2d(-22.875, -6));
   TRY_TESTME(points[i++] == Point2d(-21.875, -27));
   TRY_TESTME(points[i++] == Point2d(-16.625, -27));
   TRY_TESTME(points[i++] == Point2d(-15.625, -6));
   TRY_TESTME(points[i++] == Point2d(-3.625, -6));
   TRY_TESTME(points[i++] == Point2d(-2.625, -27));
   TRY_TESTME(points[i++] == Point2d(0, -27));
   TRY_TESTME(points[i++] == Point2d(2.625, -27));
   TRY_TESTME(points[i++] == Point2d(3.625, -6));
   TRY_TESTME(points[i++] == Point2d(15.625, -6));
   TRY_TESTME(points[i++] == Point2d(16.625, -27));
   TRY_TESTME(points[i++] == Point2d(21.875, -27));
   TRY_TESTME(points[i++] == Point2d(22.875, -6));
   TRY_TESTME(points[i++] == Point2d(36, -6));
   TRY_TESTME(points[i++] == Point2d(36, 0));
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(i == points.size());

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(beam) == true);

   //
   // LocatorPoint property
   //
   std::shared_ptr<Point2d> hookPnt = beam.GetHookPoint();

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(136, 127));

   // BottomCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 127));

   // BottomRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(64, 127));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(136, 113.5));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 113.5));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(64, 113.5));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(136, 100));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 100));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(64, 100));

   // HookPoint
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
   from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100, 100));

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0, 0);
   Point2d c(0, 0);

   beam.Rotate(c, M_PI);
   points = beam.GetPolyPoints();
   TRY_TESTME(points.size() == 19);

   i = 0;
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(points[i++] == Point2d(36, 0));
   TRY_TESTME(points[i++] == Point2d(36, 6));
   TRY_TESTME(points[i++] == Point2d(22.875, 6));
   TRY_TESTME(points[i++] == Point2d(21.875, 27));
   TRY_TESTME(points[i++] == Point2d(16.625, 27));
   TRY_TESTME(points[i++] == Point2d(15.625, 6));
   TRY_TESTME(points[i++] == Point2d(3.625, 6));
   TRY_TESTME(points[i++] == Point2d(2.625, 27));
   TRY_TESTME(points[i++] == Point2d(0, 27));
   TRY_TESTME(points[i++] == Point2d(-2.625, 27));
   TRY_TESTME(points[i++] == Point2d(-3.625, 6));
   TRY_TESTME(points[i++] == Point2d(-15.625, 6));
   TRY_TESTME(points[i++] == Point2d(-16.625, 27));
   TRY_TESTME(points[i++] == Point2d(-21.875, 27));
   TRY_TESTME(points[i++] == Point2d(-22.875, 6));
   TRY_TESTME(points[i++] == Point2d(-36, 6));
   TRY_TESTME(points[i++] == Point2d(-36, 0));
   TRY_TESTME(points[i++] == Point2d(0, 0));
   TRY_TESTME(i == points.size());

   TESTME_EPILOG("MultiWeb");
}

#endif // _UNITTEST



