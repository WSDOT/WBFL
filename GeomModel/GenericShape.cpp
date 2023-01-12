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
#include <GeomModel/GenericShape.h>
#include <GeomModel/Primitives.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include "MohrCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

GenericShape::GenericShape(Float64 area,
   std::shared_ptr<Point2d>& centroid,
   Float64 ixx, Float64 iyy, Float64 ixy,
   Float64 xLeft, Float64 yBottom,
   Float64 xRight, Float64 yTop,
   Float64 perimeter)
{
   SetProperties(area, centroid, ixx, iyy, ixy, xLeft, yBottom, xRight, yTop, perimeter);
}

GenericShape::GenericShape(Float64 area,
   const Point2d& centroid,
   Float64 ixx, Float64 iyy, Float64 ixy,
   Float64 xLeft, Float64 yBottom,
   Float64 xRight, Float64 yTop,
   Float64 perimeter)
{
   SetProperties(area, centroid, ixx, iyy, ixy, xLeft, yBottom, xRight, yTop, perimeter);
}

void GenericShape::SetProperties(Float64 area, std::shared_ptr<Point2d>& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop, Float64 perimeter)
{
   m_Area = area;
   m_pCentroid = centroid;
   m_Ixx = ixx;
   m_Iyy = iyy;
   m_Ixy = ixy;
   m_Xleft = xLeft;
   m_Ybottom = yBottom;
   m_Xright = xRight;
   m_Ytop = yTop;
   m_Perimeter = perimeter;
}

void GenericShape::SetProperties(Float64 area, const Point2d& centroid, Float64 ixx, Float64 iyy, Float64 ixy, Float64 xLeft, Float64 yBottom, Float64 xRight, Float64 yTop, Float64 perimeter)
{
   m_Area = area;
   m_pCentroid->Move(centroid);
   m_Ixx = ixx;
   m_Iyy = iyy;
   m_Ixy = ixy;
   m_Xleft = xLeft;
   m_Ybottom = yBottom;
   m_Xright = xRight;
   m_Ytop = yTop;
   m_Perimeter = perimeter;
}

void GenericShape::GetProperties(Float64* area, std::shared_ptr<Point2d>* centroid, Float64* ixx, Float64* iyy, Float64* ixy, Float64* xLeft, Float64* yBottom, Float64* xRight, Float64* yTop, Float64* perimeter) const
{
   *area = m_Area;
   *centroid = m_pCentroid;
   *ixx = m_Ixx;
   *iyy = m_Iyy;
   *ixy = m_Ixy;
   *yTop = m_Ytop;
   *yBottom = m_Ybottom;
   *xLeft = m_Xleft;
   *xRight = m_Xright;
   *perimeter = m_Perimeter;
}

void GenericShape::SetArea(Float64 area)
{
   m_Area = area;
}

Float64 GenericShape::GetArea() const
{
   return m_Area;
}

void GenericShape::SetCentroid(const Point2d& centroid)
{
   m_pCentroid->Move(centroid);
}

void GenericShape::SetCentroid(std::shared_ptr<Point2d>& centroid)
{
   m_pCentroid = centroid;
}

const std::shared_ptr<Point2d>& GenericShape::GetCentroid() const
{
   return m_pCentroid;
}

std::shared_ptr<Point2d>& GenericShape::GetCentroid()
{
   return m_pCentroid;
}

void GenericShape::SetIxx(Float64 ixx)
{
   m_Ixx = ixx;
}

Float64 GenericShape::GetIxx() const
{
   return m_Ixx;
}

void GenericShape::SetIyy(Float64 iyy)
{
   m_Iyy = iyy;
}

Float64 GenericShape::GetIyy() const
{
   return m_Iyy;
}

void GenericShape::SetIxy(Float64 ixy)
{
   m_Ixy = ixy;
}

Float64 GenericShape::GetIxy() const
{
   return m_Ixy;
}

void GenericShape::SetYtop(Float64 ytop)
{
   m_Ytop = ytop;
}

Float64 GenericShape::GetYtop() const
{
   return m_Ytop;
}

void GenericShape::SetYbottom(Float64 ybot)
{
   m_Ybottom = ybot;
}

Float64 GenericShape::GetYbottom() const
{
   return m_Ybottom;
}

void GenericShape::SetXleft(Float64 xleft)
{
   m_Xleft = xleft;
}

Float64 GenericShape::GetXleft() const
{
   return m_Xleft;
}

void GenericShape::SetXright(Float64 xright)
{
   m_Xright = xright;

}

Float64 GenericShape::GetXright() const
{
   return m_Xright;
}

void GenericShape::SetPerimeter(Float64 p)
{
   m_Perimeter = p;
}

Float64 GenericShape::GetPerimeter() const
{
   return m_Perimeter;
}

void GenericShape::Offset(Float64 dx, Float64 dy)
{
   Offset(Size2d(dx, dy));
}

void GenericShape::Offset(const Size2d& delta)
{
   m_pCentroid->Offset(delta);
}

void GenericShape::Move(LocatorPoint lp, const Point2d& to)
{
   Offset(to - GetLocatorPoint(lp));
}

void GenericShape::Move(const Point2d& from, const Point2d& to)
{
   Offset(to - from);
}

void GenericShape::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   Rotate(Point2d(cx, cy), angle);
}

void GenericShape::Rotate(const Point2d& center, Float64 angle)
{
   m_pCentroid->Rotate(center, angle);
   m_Rotation += angle;
}

void GenericShape::SetHookPoint(std::shared_ptr<Point2d>& hookPnt)
{
   SetCentroid(hookPnt);
}

void GenericShape::SetHookPoint(const Point2d& hookPnt)
{
   SetCentroid(hookPnt);
}

std::shared_ptr<Point2d>& GenericShape::GetHookPoint()
{
   return GetCentroid();
}

const std::shared_ptr<Point2d>& GenericShape::GetHookPoint() const
{
   return GetCentroid();
}

Point2d GenericShape::GetLocatorPoint(LocatorPoint lp) const
{
   Point2d p(*m_pCentroid);
   switch (lp)
   {
   case Shape::LocatorPoint::HookPoint:
      break;

   case Shape::LocatorPoint::TopLeft:
      p.Offset(-m_Xleft,m_Ytop);
      break;

   case Shape::LocatorPoint::TopCenter:
      p.Offset(0, m_Ytop);
      break;

   case Shape::LocatorPoint::TopRight:
      p.Offset(m_Xright,m_Ytop);
      break;

   case Shape::LocatorPoint::CenterLeft:
       p.Offset(-m_Xleft, 0);
      break;

   case Shape::LocatorPoint::CenterCenter:
      break;

   case Shape::LocatorPoint::CenterRight:
      p.Offset(m_Xright, 0);
      break;

   case Shape::LocatorPoint::BottomLeft:
      p.Offset(-m_Xleft, -m_Ybottom);
      break;

   case Shape::LocatorPoint::BottomCenter:
      p.Offset(0, -m_Ybottom);
      break;

   case Shape::LocatorPoint::BottomRight:
      p.Offset(m_Xright,-m_Ybottom);
      break;
   }

   return p;
}

void GenericShape::SetLocatorPoint(LocatorPoint lp, Point2d& position)
{
   Move(GetLocatorPoint(lp), position);
}

ShapeProperties GenericShape::GetProperties() const
{
   // rotate properties into correct orientation.
   Float64 ixx(m_Ixx), ixy(m_Ixy), iyy(m_Iyy);
   if (!IsZero(m_Rotation))
   {
      MohrCircle mc(m_Ixx, m_Iyy, m_Ixy);
      mc.ComputeState(m_Rotation, ixx, iyy, ixy);
   }

   ShapeProperties props(m_Area, *m_pCentroid, ixx, iyy, ixy, m_Xleft, m_Ybottom, m_Xright, m_Ytop);
   return props;
}

Rect2d GenericShape::GetBoundingBox() const
{
   Float64 cx, cy;
   m_pCentroid->GetLocation(&cx, &cy);
   return Rect2d(cx - m_Xleft, cy - m_Ybottom, cx + m_Xright, cy + m_Ytop);
}

std::vector<Point2d> GenericShape::GetPolyPoints() const
{
   return std::vector<Point2d>{*m_pCentroid};
}

bool GenericShape::PointInShape(const Point2d& p) const
{
   Float64 x,y;
   p.GetLocation(&x,&y);

   Float64 cx,cy;
   m_pCentroid->GetLocation(&cx, &cy);

   if ( (cx-m_Xleft <= x && x <= cx+m_Xright) &&
        (cy-m_Ybottom <= y && y <= cy+m_Ytop) )
   {
      return true;
   }
   else
   {
      return false;
   }
}

std::unique_ptr<Shape> GenericShape::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   // if CG is on the right of the line, create a clone, otherwise
   // consider the shape to be clipped away

   Float64 d = -1.0*line.DistanceToPoint(*m_pCentroid);
   if ( d <= 0 )
   {
      // CG is on the left side of the line
      return nullptr;
   }
   else
   {
      // CG is on the right side of the line
      return CreateClone();
   }
}

std::unique_ptr<Shape> GenericShape::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   if (r.Contains(*m_pCentroid))
   {
      return CreateClone();
   }
   return nullptr;
}

Float64 GenericShape::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   Point2d p;
   Float64 fd;
   GetFurthestPoint(line, side, p, fd);
   return fd;
}

void GenericShape::GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const
{
   furthestPoint = *m_pCentroid;

   // get distance from left side of line to center
   furthestDistance = line.DistanceToPoint(*m_pCentroid);
   if (side == Line2d::Side::Right)
      furthestDistance = -furthestDistance;
}

std::unique_ptr<Shape> GenericShape::CreateClone() const
{
    auto clone = std::make_unique<GenericShape>(*this); // this copies a shared pointer so clone has the same centroid object as this
    clone->SetCentroid(std::make_shared<WBFL::Geometry::Point2d>(*GetCentroid())); // setting the centroid by reference creates a new shared pointer inside of clone
    return clone;
}

#if defined _DEBUG
bool GenericShape::AssertValid() const
{
   return true;
}

void GenericShape::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for GenericShape") << WBFL::Debug::endl;
   //os << _T("   m_Area         = ")<< m_Area << WBFL::Debug::endl;
   //os << _T("   m_Centroid     = (")<< m_Centroid.X()<<_T(", ")<<m_Centroid.Y()<<_T(")")<< WBFL::Debug::endl;
   //os << _T("   m_Ixx          = ")<< m_Ixx << WBFL::Debug::endl;         
   //os << _T("   m_Iyy          = ")<< m_Iyy << WBFL::Debug::endl;          
   //os << _T("   m_Ixy          = ")<< m_Ixy << WBFL::Debug::endl;         
   //os << _T("   m_Edges.Top    = ") << m_Edges.Top() << WBFL::Debug::endl;
   //os << _T("   m_Edges.Bottom = ") << m_Edges.Bottom() << WBFL::Debug::endl;
   //os << _T("   m_Edges.Left   = ") << m_Edges.Left() << WBFL::Debug::endl;
   //os << _T("   m_Edges.Right  = ") << m_Edges.Right() << WBFL::Debug::endl;
   //os << _T("   m_BoundingBox.Top    = ")<< m_BoundingBox.Top() << WBFL::Debug::endl;
   //os << _T("   m_BoundingBox.Bottom = ")<< m_BoundingBox.Bottom() << WBFL::Debug::endl;
   //os << _T("   m_BoundingBox.Left   = ")<< m_BoundingBox.Left() << WBFL::Debug::endl;
   //os << _T("   m_BoundingBox.Right  = ")<< m_BoundingBox.Right() << WBFL::Debug::endl;
   //os << _T("   m_CoordType    = ")<< (int)m_CoordType << WBFL::Debug::endl;   
   //os << _T("   m_Origin       = (")<<m_Origin.X()<<_T(", ")<<m_Origin.Y()<<_T(")") << WBFL::Debug::endl;
   //os << _T("   m_Orientation  = ")<< m_Orientation << WBFL::Debug::endl;
   //os << _T("   m_CurrCentroid = (")<< m_CurrCentroid.X()<<_T(", ")<<m_CurrCentroid.Y()<<_T(")")<< WBFL::Debug::endl;
   //os << _T("   m_CurrIxx      = ")<< m_CurrIxx << WBFL::Debug::endl;
   //os << _T("   m_CurrIyy      = ")<< m_CurrIyy << WBFL::Debug::endl;
   //os << _T("   m_CurrIxy      = ")<< m_CurrIxy << WBFL::Debug::endl;
}

#endif // _DEBUG


#if defined _UNITTEST
#include <MathEx.h>
#include <GeomModel/UnitTest.h>
bool GenericShape::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("GenericShape");

   GenericShape shape;
   TRY_TESTME(IsZero(shape.GetArea()));
   TRY_TESTME(IsZero(shape.GetIxx()));
   TRY_TESTME(IsZero(shape.GetIyy()));
   TRY_TESTME(IsZero(shape.GetIxy()));
   TRY_TESTME(IsZero(shape.GetPerimeter()));
   TRY_TESTME(*shape.GetCentroid() == Point2d(0, 0));

   shape.SetProperties(5, Point2d(10, 20), 1, 2, 0, 0, 0, 0, 0, 10);

   TRY_TESTME(IsEqual(shape.GetArea(), 5.0));
   TRY_TESTME(IsEqual(shape.GetIxx(), 1.0));
   TRY_TESTME(IsEqual(shape.GetIyy(), 2.0));
   TRY_TESTME(IsEqual(shape.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(shape.GetPerimeter(), 10.0));
   TRY_TESTME(*shape.GetCentroid() == Point2d(10, 20));

   auto hookPnt = shape.GetHookPoint();
   auto new_hookPnt = std::make_shared<Point2d>(-50, -60);
   shape.SetCentroid(new_hookPnt);
   TRY_TESTME(*hookPnt == Point2d(10, 20)); // the hook point object was replaced so this old hook point doesn't change
   hookPnt = shape.GetHookPoint(); // get the new hook point
   TRY_TESTME(*hookPnt == Point2d(-50, -60));

   shape = GenericShape(5,Point2d(10,20),1,2,0,0,0,0,0,10); // start with a new shape
   hookPnt = shape.GetHookPoint();

   //
   // ShapeProperties
   //
   auto props = shape.GetProperties();
   TRY_TESTME(IsEqual(shape.GetArea(), 5.0));
   TRY_TESTME(IsEqual(shape.GetIxx(), 1.0));
   TRY_TESTME(IsEqual(shape.GetIyy(), 2.0));
   TRY_TESTME(IsEqual(shape.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(shape.GetPerimeter(), 10.0));
   TRY_TESTME(*shape.GetCentroid() == Point2d(10, 20));
   TRY_TESTME(*shape.GetHookPoint() == Point2d(10, 20));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), 0.0));
   TRY_TESTME(IsEqual(props.GetXright(), 0.0));
   TRY_TESTME(IsEqual(props.GetYtop(), 0.0));
   TRY_TESTME(IsEqual(props.GetYbottom(), 0.0));

   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(shape) == true);


   //
   // BoundingBox
   //
   auto box = shape.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), 10.0));
   TRY_TESTME(IsEqual(box.Right(), 10.0));
   TRY_TESTME(IsEqual(box.Top(), 20.0));
   TRY_TESTME(IsEqual(box.Bottom(), 20.0));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(shape.GetPerimeter(), 10.0));

   //
   // FurthestDistance
   //

   // Shape on right
   Point2d p1(0, 50);
   Point2d p2(100, 50);
   Line2d line(p1, p2);
   TRY_TESTME(IsEqual(shape.GetFurthestDistance(line, Line2d::Side::Right), 30.000));

   // shape on left
   p1.Move(0, -50);
   p2.Move(100, -50);
   line.ThroughPoints(p1, p2);
   TRY_TESTME(IsEqual(shape.GetFurthestDistance(line, Line2d::Side::Right), -70.000));

   //
   // PointInShape
   //
   Point2d pnt(-10, -10);
   TRY_TESTME(shape.PointInShape(pnt) == false);

   pnt.Move(10, 20);
   TRY_TESTME(shape.PointInShape(pnt) == true);

   pnt.Move(15, 20);
   TRY_TESTME(shape.PointInShape(pnt) == false);

   //
   // PolyPoints
   //
   auto points = shape.GetPolyPoints();
   TRY_TESTME(points.size() == 1);
   TRY_TESTME(points[0] == Point2d(10, 20));

   //
   // ClipWithLine
   //

   // line to left of shape... clipping result is null
   p1.Move(0, 0);
   p2.Move(20, 20);
   Line2d clipLine(p1, p2);

   auto clip = shape.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip == nullptr);

   // line to right of shape
   p1.Move(0, 20);
   p2.Move(20, 40);
   clipLine.ThroughPoints(p1, p2);
   clip = shape.CreateClippedShape(clipLine, Line2d::Side::Left);
   TRY_TESTME(clip != nullptr);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 1);
   TRY_TESTME(points[0] == Point2d(10, 20));
   
   //
   // ClipIn
   //

   Rect2d clipRect(100, 15, 200, 25);
   clip = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip == nullptr);

   // in rect
   clipRect.Set(-100, 15, 100, 25);
   clip = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip != nullptr);
   points = clip->GetPolyPoints();
   TRY_TESTME(points.size() == 1);
   TRY_TESTME(points[0] == Point2d(10, 20));

   //
   // MoveEx
   //
   hookPnt->Move(10, 20);
   Point2d from(0, 0);
   Point2d to(110, 110);
   shape.Move(from, to);
   TRY_TESTME(*hookPnt == Point2d(120, 130));

   //
   // OffsetEx and Offset
   //
   Size2d size(10, 20);
   shape.Offset(size);
   TRY_TESTME(*hookPnt == Point2d(130, 150));

   //
   // LocatorPoint property
   //

   // BottomLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // BottomCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // BottomRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // CenterLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // CenterCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // CenterRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0,100.0));

   // TopLeft
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // TopCenter
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // TopRight
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   // HookPoint
   hookPnt->Move(0, 0);
   to.Move(100, 100);
   shape.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
   from = shape.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*hookPnt == Point2d(100.0, 100.0));

   //
   // Rotate and RotateEx
   //
   hookPnt->Move(10, 20);
   Point2d c(0, 0);

   shape.Rotate(c, PI_OVER_2);
   points = shape.GetPolyPoints();

   TRY_TESTME(points.size() == 1);
   TRY_TESTME(points[0] == Point2d(-20, 10));

   // Test section properties of the rectangle rotated 45 deg.
   hookPnt->Move(0, 0);
   c.Move(0, 0);
   shape.Rotate(c,M_PI / 4);

   props = shape.GetProperties();

   TRY_TESTME(IsEqual(props.GetArea(), 5.));
   TRY_TESTME(IsEqual(props.GetIxx(), 1.5));
   TRY_TESTME(IsEqual(props.GetIyy(), 1.5));
   TRY_TESTME(IsEqual(props.GetIxy(), -0.5));

   TESTME_EPILOG("GenericShape");
}

#endif // _UNITTEST


