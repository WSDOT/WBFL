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
#include <GeomModel/Circle.h>
#include <GeomModel/CircularSegment.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

// number of vertex points used to describe a polyline version of a circle
const int NUM_POINTS=36;

Circle::Circle() : ShapeOnAlternativePolygonImpl()
{
}

Circle::Circle(std::shared_ptr<Point2d>& hookPnt,Float64 radius) :
   ShapeOnAlternativePolygonImpl(hookPnt),
   m_Radius(radius)
{
   PRECONDITION(0 <= radius);
}

Circle::Circle(const Point2d& hookPnt, Float64 radius) :
   ShapeOnAlternativePolygonImpl(hookPnt),
   m_Radius(radius)
{
   PRECONDITION(0 <= radius);
}

Circle::Circle(const Circle& other) :
   ShapeOnAlternativePolygonImpl(other)
{
   Copy(other);
}

Circle& Circle::operator=(const Circle& other)
{
   if (this != &other)
   {
      __super::operator=(other);
      Copy(other);
   }
   return *this;
}

Circle::~Circle()
{
}

void Circle::SetRadius(Float64 r)
{
   PRECONDITION(0 <= r);
   m_Radius = r;
   SetDirtyFlag();
}

Float64 Circle::GetRadius() const
{
   return m_Radius;
}

void Circle::SetParameters(std::shared_ptr<Point2d>& center, Float64 radius)
{
   SetHookPoint(center);
   m_Radius = radius;
   SetDirtyFlag();
}

void Circle::SetParameters(const Point2d& center, Float64 radius)
{
   SetHookPoint(center);
   m_Radius = radius;
   SetDirtyFlag();
}

void Circle::GetParameters(std::shared_ptr<Point2d>* pCenter, Float64* radius) const
{
   *pCenter = GetHookPoint();
   *radius = m_Radius;
}

void Circle::ThroughTwoPoints(const Point2d& p1, const Point2d& p2)
{
   Float64 diameter = p1.Distance(p2);
   if (IsZero(diameter)) THROW_GEOMETRY(_T("Circle::ThroughtTwoPoints - points are coincident"));

   m_Radius = diameter / 2;
   SetHookPoint((p1+p2)/2);

   SetDirtyFlag();
}

void Circle::ThroughThreePoints(const Point2d& p1, const Point2d& p2, const Point2d& p3)
{
   // Create lines that go between the poinst
   Line2d line1(p1, p2);
   Line2d line2(p2, p3);

   // Determine if the lines are colinear
   if (line1.IsColinear(line2)) THROW_GEOMETRY(_T("Circle::ThroughThreePoints - lines are colinear."));

   // Create lines that are normal to line1 and line2, passing through the midpoint
   Float64 x1, y1; p1.GetLocation(&x1, &y1);
   Float64 x2, y2; p2.GetLocation(&x2, &y2);
   Float64 x3, y3; p3.GetLocation(&x3, &y3);

   Float64 mx1 = (x1 + x2) / 2;
   Float64 my1 = (y1 + y2) / 2;
   Float64 mx2 = (x2 + x3) / 2;
   Float64 my2 = (y2 + y3) / 2;

   // Line mid-points
   Point2d mp1(mx1, my1);
   Point2d mp2(mx2, my2);

   // Create lines normal to L1 and L2 at their mid-points
   Line2d normal1 = GeometricOperations::CreateNormalLineThroughPoint(line1, mp1);
   Line2d normal2 = GeometricOperations::CreateNormalLineThroughPoint(line2, mp2);

   // The intersection of the normal lines is the center of the circle
   Point2d center;
   GeometricOperations::Intersect(normal1, normal2, &center);

   Float64 radius = center.Distance(p1);

#if defined _DEBUG
   Float64 r2 = center.Distance(p2);
   Float64 r3 = center.Distance(p3);
   CHECK(IsEqual(radius, r2));
   CHECK(IsEqual(radius, r3));
   CHECK(IsEqual(r2, r3));
#endif

   SetHookPoint(center);
   m_Radius = radius;
}

void Circle::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void Circle::DoRotate(const Point2d& center, Float64 angle)
{
   GetHookPoint()->Rotate(center, angle);
   SetDirtyFlag();
}

ShapeProperties Circle::GetProperties() const
{
   ASSERTVALID;
   // get non-rotated properties
   Float64 area = M_PI * m_Radius * m_Radius;
   Float64 ixx  = M_PI * pow(m_Radius,4.)/4.;
   Float64 iyy  = ixx;
   Float64 ixy  = 0;

   return ShapeProperties(area , *GetHookPoint(), ixx, iyy, ixy, m_Radius,m_Radius,m_Radius,m_Radius);
}

Rect2d Circle::GetBoundingBox() const
{
   // use a point to determine box height and width
   auto pCenter = GetHookPoint();
   Float64 top   = pCenter->Y() + m_Radius;
   Float64 right = pCenter->X() + m_Radius;
   Float64 bottom= pCenter->Y() - m_Radius;
   Float64 left  = pCenter->X() - m_Radius;

   return Rect2d(left,bottom,right,top);
}

bool Circle::PointInShape(const Point2d& p) const
{
   Float64 dist = p.Distance(*GetHookPoint());
   return ::IsLE(dist,m_Radius) ? true : false;
}

Float64 Circle::GetPerimeter() const
{
   return TWO_PI * m_Radius;
}

bool Circle::PointOnCircle(const Point2d& p)
{
   Float64 dist = p.Distance(*GetHookPoint());
   return IsEqual(dist, m_Radius);
}

std::unique_ptr<Shape> Circle::CreateClone() const
{
   return std::make_unique<Circle>(*this);
}

std::unique_ptr<Shape> Circle::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   // since clipping a circle is very expensive
   // first determine if circle really needs to be clipped.
   Float64 distance = -1*line.DistanceToPoint(*GetHookPoint());
   distance = IsZero(distance) ? 0.0 : distance;

   if (fabs(distance) <= m_Radius)
   {
      // circle touches line, must clip
      return GetPolygon()->CreateClippedShape(line, side);
   }
   else
   {
      // now need to find out which side of line circle is on.
      if (side==Line2d::Side::Right) distance = -distance;

      if (0 < distance)
      {
         // circle is entirely within clipping region
         return std::make_unique<Circle>(*this);
      }
      else
      {
         // circle is entirely outside of clipping region
         return nullptr;
      }
   }
}

std::unique_ptr<Shape> Circle::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   // Clip using top edge
   Line2d line(r.TopLeft(), r.TopRight());

   std::unique_ptr<Shape> clip_top = CreateClippedShape(line, Line2d::Side::Left);
   if (clip_top == nullptr) return std::unique_ptr<Shape>(); // entier shape clipped away

   // Clip using Right edge
   line.ThroughPoints(r.TopRight(), r.BottomRight());
   std::unique_ptr<Shape> clip_right = clip_top->CreateClippedShape(line, Line2d::Side::Left);
   if(clip_right == nullptr) return std::unique_ptr<Shape>(); // entier shape clipped away

   // Clip using Bottom edge
   line.ThroughPoints(r.BottomRight(), r.BottomLeft());
   std::unique_ptr<Shape> clip_bottom = clip_right->CreateClippedShape(line, Line2d::Side::Left);
   if (clip_bottom == nullptr) return std::unique_ptr<Shape>(); // entier shape clipped away

   // Clip using Left edge
   line.ThroughPoints(r.BottomLeft(), r.TopLeft());
   std::unique_ptr<Shape> clip_left = clip_bottom->CreateClippedShape(line, Line2d::Side::Left);
   if (clip_left == nullptr) return std::unique_ptr<Shape>(); // entier shape clipped away

   return clip_left;
}

Float64 Circle::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   Point2d fp;
   Float64 fd;
   GetFurthestPoint(line, side, fp, fd);
   return fd;
}

void Circle::GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const
{
   Float64 c;
   Vector2d n;
   line.GetImplicit(&c, &n);
   Float64 angle = n.GetDirection();
   if (side == Line2d::Side::Right)
      angle += M_PI;

   Float64 x = cos(angle) * m_Radius + GetHookPoint()->X();
   Float64 y = sin(angle) * m_Radius + GetHookPoint()->Y();
   furthestPoint.Move(x, y);
      
   ASSERT(IsEqual(m_Radius, furthestPoint.Distance(*GetHookPoint())));

   furthestDistance = line.DistanceToPoint(furthestPoint);
   if (side == Line2d::Side::Right)
      furthestDistance *= -1;

   // check distance from line to center
   ASSERT(IsEqual(furthestDistance, (side == Line2d::Side::Right ? -1 : 1) * line.DistanceToPoint(*GetHookPoint()) + m_Radius));

   // check point is on correct side of line. if furhtestDistance < 0, the correct side is the opposite side than the request
   ASSERT(line.GetSide(furthestPoint) == (furthestDistance < 0 ? (side == Line2d::Side::Right ? Line2d::Side::Left : Line2d::Side::Right) : side));
}

#if defined _DEBUG
bool Circle::AssertValid() const
{
   if (m_Radius<0) return false;
   return __super::AssertValid();
}

void Circle::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for Circle ***")<< WBFL::Debug::endl;
   ShapeImpl::Dump( os );
   os << _T("  Hook Point      = (")<< GetHookPoint()->X()<<_T(", ")<< GetHookPoint()->Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("  Radius          =  ")<<m_Radius  << WBFL::Debug::endl;
}
#endif // _DEBUG

void Circle::Copy(const Circle& other)
{
   m_Radius = other.m_Radius;
}

void Circle::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   Float64 angle_inc = 2 * M_PI / NUM_POINTS;

   // determine radius of circle to make an "Area Perfect" polycircle.
   Float64 rad = sqrt(M_PI * m_Radius * m_Radius /
      (NUM_POINTS * sin(M_PI / NUM_POINTS) * cos(M_PI / NUM_POINTS)));

   Float64 cx, cy;
   GetHookPoint()->GetLocation(&cx, &cy);
   for (Int32 i = 0; i <= NUM_POINTS; i++)
   {
      Float64 a = i * angle_inc;
      Float64 x = cx + rad * cos(a);
      Float64 y = cy + rad * sin(a);
      polygon->AddPoint(x, y);
   }
}

#if defined _UNITTEST
#include <GeomModel/UnitTest.h>
bool Circle::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Circle");

   Circle rt(Point2d(2,2),2);
   TRY_TESTME( IsEqual(2., rt.GetRadius())) 
   TRY_TESTME(Point2d(2,2) == *rt.GetHookPoint()) 
   ShapeProperties aprops = rt.GetProperties();
   TRY_TESTME (IsEqual(aprops.GetArea(), 12.566, .01)) 
   TRY_TESTME (IsEqual(aprops.GetIxx(),  12.56, .1)) 
   TRY_TESTME (IsEqual(aprops.GetIyy(),  12.56, .1)) 
   TRY_TESTME (IsEqual(aprops.GetIxy(),   0.00, .001)) 
   TRY_TESTME (rt.GetBoundingBox() == Rect2d(0,0,4,4)) 

   rt.SetHookPoint(Point2d(0,0));
   TRY_TESTME (rt.GetBoundingBox() == Rect2d(-2,-2,2,2)) 
   rt.Move(Shape::LocatorPoint::CenterCenter, Point2d(2,2));
   TRY_TESTME (rt.GetBoundingBox() == Rect2d(0,0,4,4)) 

   Float64 ang = atan(1.);
   Float64 dis = 2/cos(ang);
   rt.Rotate(Point2d(0,0),ang);
   TRY_TESTME (rt.GetBoundingBox() == Rect2d(-2,dis-2,2,dis+2)) 

   // Resize circle and clip it into a hemi
   rt.SetRadius(40);
   rt.SetHookPoint(Point2d(0,40));
   Line2d at45(Point2d(0,40), Vector2d(Size2d(1,1)));
   std::unique_ptr<Shape> phemi(rt.CreateClippedShape(at45, Line2d::Side::Right));
   aprops = phemi->GetProperties();
   TRY_TESTME (IsEqual(aprops.GetArea(), 2513.2,.1)) 

   // clip should return entire circle
   rt.SetHookPoint(Point2d(60,0));
   std::unique_ptr<Shape> prt(rt.CreateClippedShape(at45, Line2d::Side::Left));
   aprops = prt->GetProperties();
   TRY_TESTME (IsEqual(aprops.GetArea(), 5026.55,.1)) 

#if defined _DEBUG
   rt.Dump(rlog.GetLogContext());
#endif


   // Center
   std::shared_ptr<Point2d> center = std::make_shared<Point2d>(0, 0);
   Circle circle(center, 100);
   auto hookPnt = circle.GetHookPoint();
   center->Move(15, 20);
   TRY_TESTME(*hookPnt == Point2d(15, 20));
   TRY_TESTME(hookPnt == center);
   TRY_TESTME(*hookPnt == *center);

   // ThroughTwoPoints
   Point2d p1(15, 10);
   Point2d p2(15, 10);
   try {
      circle.ThroughTwoPoints(p1, p2);
      TRY_TESTME(false);
   }
   catch (...) { TRY_TESTME(true); }
   
   p1.Move(10, 10);
   circle.ThroughTwoPoints(p1, p2);
   TRY_TESTME(*center == Point2d(12.5, 10));
   TRY_TESTME(IsEqual(circle.GetRadius(), 2.5));

   // ThroughThreePoints
   p1.Move(15, 10);
   p2.Move(15, 10);
   Point2d p3(15, 10);
   try {
      circle.ThroughThreePoints(p1, p2, p3);
      TRY_TESTME(false);
   }
   catch (...) { TRY_TESTME(true); }
   
   p1.Move(15, 10);
   p2.Move(15, 20);
   p3.Move(15, 30);
   try {
      circle.ThroughThreePoints(p1, p2, p3);
      TRY_TESTME(false);
   }
   catch (...) { TRY_TESTME(true); }

   p1.Move(10, 10);
   p2.Move(20, 10);
   p3.Move(15, 15);
   circle.ThroughThreePoints(p1, p2, p3);
   TRY_TESTME(*center == Point2d(15, 10));
   TRY_TESTME(IsEqual(circle.GetRadius(), 5.0));

   // ContainsPoint
   center->Move(10, 10);
   circle.SetRadius(10);
   p1.Move(0, 0);   TRY_TESTME(circle.PointInShape(p1) == false);
   p1.Move(20, 10); TRY_TESTME(circle.PointInShape(p1) == true);
   p1.Move(30, 5);  TRY_TESTME(circle.PointInShape(p1) == false);
   p1.Move(9, 9);   TRY_TESTME(circle.PointInShape(p1) == true);
   TRY_TESTME(circle.PointInShape(*center) == true);
   TRY_TESTME(circle.PointInShape(*hookPnt) == true);

   // PointOnCircle
   center->Move(10, 10);
   circle.SetRadius(10);
   p1.Move(0, 0);   TRY_TESTME(circle.PointOnCircle(p1) == false);
   p1.Move(20, 10); TRY_TESTME(circle.PointOnCircle(p1) == true);
   p1.Move(30, 5);  TRY_TESTME(circle.PointOnCircle(p1) == false);
   p1.Move(9, 9);   TRY_TESTME(circle.PointOnCircle(p1) == false);
   TRY_TESTME(circle.PointOnCircle(*center) == false);
   TRY_TESTME(circle.PointOnCircle(*hookPnt) == false);


   //
   // ShapeProperties
   //
   center->Move(3, 5);
   Float64 radius = 10;
   circle.SetRadius(radius);
   ShapeProperties props = circle.GetProperties();

   TRY_TESTME(IsEqual(props.GetArea(), M_PI * radius * radius));
   TRY_TESTME(IsEqual(props.GetIxx(), M_PI * radius * radius * radius * radius / 4));
   TRY_TESTME(IsEqual(props.GetIyy(), M_PI * radius * radius * radius * radius / 4));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 3.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 5.0));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), radius));
   TRY_TESTME(IsEqual(props.GetXright(), radius));
   TRY_TESTME(IsEqual(props.GetYtop(), radius));
   TRY_TESTME(IsEqual(props.GetYbottom(), radius));

   //
   // BoundingBox
   //
   Rect2d box = circle.GetBoundingBox();
   TRY_TESTME(IsEqual(box.Left(), 3 - radius));
   TRY_TESTME(IsEqual(box.Right(), 3 + radius));
   TRY_TESTME(IsEqual(box.Top(), 5 + radius));
   TRY_TESTME(IsEqual(box.Bottom(), 5 - radius));

   //
   // Perimeter
   //
   TRY_TESTME(IsEqual(circle.GetPerimeter(), TWO_PI * radius));

   //
   // FurthestDistance
   //
   p1.Move(0, 0);
   p2.Move(100, 0);
   Line2d line(p1, p2);

   // Shape on right
   center->Move(50, -100);
   circle.SetRadius(10);

   Point2d furthestPoint;
   Float64 furthestDistance;
   circle.GetFurthestPoint(line, Line2d::Side::Right, furthestPoint, furthestDistance);
   TRY_TESTME(furthestPoint == Point2d(50,-110));
   TRY_TESTME(IsEqual(furthestDistance, 110.0));

   // shape on left
   center->Move(50, 100);
   circle.GetFurthestPoint(line, Line2d::Side::Right, furthestPoint, furthestDistance);
   TRY_TESTME(furthestPoint == Point2d(50, 90));
   TRY_TESTME(IsEqual(furthestDistance, -90.0));

   // center of circle on line
   center->Move(50, 0);
   circle.GetFurthestPoint(line, Line2d::Side::Right, furthestPoint, furthestDistance);
   TRY_TESTME(furthestPoint == Point2d(50, -10));
   TRY_TESTME(IsEqual(furthestDistance, 10.0));

   circle.GetFurthestPoint(line, Line2d::Side::Left, furthestPoint, furthestDistance);
   TRY_TESTME(furthestPoint == Point2d(50, 10));
   TRY_TESTME(IsEqual(furthestDistance, 10.0));

   // make line vertical - center of circle on line
   p2.Move(0, 100);
   line.ThroughPoints(p1, p2);

   center->Move(0, 50);
   circle.GetFurthestPoint(line, Line2d::Side::Right, furthestPoint, furthestDistance);
   TRY_TESTME(furthestPoint == Point2d(10, 50));
   TRY_TESTME(IsEqual(furthestDistance, 10.0));

   circle.GetFurthestPoint(line, Line2d::Side::Left, furthestPoint, furthestDistance);
   TRY_TESTME(furthestPoint == Point2d(-10, 50));
   TRY_TESTME(IsEqual(furthestDistance, 10.0));

   //
   // PointInShape
   //
   center->Move(3, 5);
   Point2d pnt(-10, -10);
   TRY_TESTME(circle.PointInShape(pnt) == false);

   pnt.Move(3, 5);
   TRY_TESTME(circle.PointInShape(pnt) == true);

   pnt.Move(3, 15);
   TRY_TESTME(circle.PointInShape(pnt) == true);

   //
   // PolyPoints
   //
   auto points = circle.GetPolyPoints();
   TRY_TESTME(points.size() == 37);
   
   // Create a PolyShape and check its section properties
   Polygon polyShape;
   polyShape.AddPoints(points);
   props = polyShape.GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(), M_PI* radius* radius, 0.01));
   TRY_TESTME(IsEqual(props.GetIxx(), M_PI* radius* radius* radius* radius / 4, 0.1));
   TRY_TESTME(IsEqual(props.GetIyy(), M_PI* radius* radius* radius* radius / 4, 0.1));
   TRY_TESTME(IsEqual(props.GetIxy(), 0.0));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 3.0));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 5.0));
   TRY_TESTME(props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal);

   TRY_TESTME(IsEqual(props.GetXleft(), radius, 0.1));
   TRY_TESTME(IsEqual(props.GetXright(), radius, 0.1));
   TRY_TESTME(IsEqual(props.GetYtop(), radius, 0.1));
   TRY_TESTME(IsEqual(props.GetYbottom(), radius, 0.1));

   //
   // ClipWithLine
   //
   center->Move(0, 0);

   p1.Move(0, 0);
   p2.Move(20, 20);
   line.ThroughPoints(p1, p2);

   // Clip with a simple line through the center of the circle
   // Verify by checking area.
   auto clip = circle.CreateClippedShape(line, Line2d::Side::Left);
   TRY_TESTME(IsEqual(circle.GetProperties().GetArea()/2, clip->GetProperties().GetArea()));

   // Clip against line such that the entire circle remains
   p1.Move(0, 50);
   p2.Move(20, 70);
   line.ThroughPoints(p1, p2);
   clip = circle.CreateClippedShape(line, Line2d::Side::Left);
   TRY_TESTME(IsEqual(circle.GetProperties().GetArea(), clip->GetProperties().GetArea()));

   // Clip against line such that the entire circle is removed
   p1.Move(0, -50);
   p2.Move(20, -70);
   line.ThroughPoints(p1, p2);
   clip = circle.CreateClippedShape(line, Line2d::Side::Left);
   TRY_TESTME(clip == nullptr);

   //
   // ClipIn
   //

   // Clip out a square the is entirely contained within the circle

   center->Move(0, 0);
   circle.SetRadius(10.0);
   Rect2d clipRect(-5, -5, 5, 5);

   clip = circle.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(IsEqual(clip->GetProperties().GetArea(), 100.0, 0.001));

   // Clip with a rectange that is larger than the circle.
   // A clone of the circle should be returned
   clipRect.Set(-500, -500, 500, 500);
   clip = circle.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   Circle* clone_circle = dynamic_cast<Circle*>(clip.get());
   TRY_TESTME(clone_circle != nullptr);
   clone_circle = nullptr;

   // Clip away the top half of the circle
   // Verify by checking the area (should be half the area of the circle)
   clipRect.Set(-500, -500, 500, 0);
   clip = circle.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(IsEqual(circle.GetProperties().GetArea() / 2, clip->GetProperties().GetArea(), 0.001));

   // Entire clipping rectangle is above the circle
   clipRect.Set(-500, 2*radius, 500, 3*radius);
   clip = circle.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip == nullptr);

   // Entire clipping rectangle is below the circle
   clipRect.Set(-500, -2 * radius, 500, -3 * radius);
   clip = circle.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip == nullptr);

   // Entire clipping rectangle is left of the circle
   clipRect.Set(-500, -2 * radius, -400, 2 * radius);
   clip = circle.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip == nullptr);

   // Entire clipping rectangle is right of the circle
   clipRect.Set(400, -2 * radius, 500, 2 * radius);
   clip = circle.CreateClippedShape(clipRect, Shape::ClipRegion::In);
   TRY_TESTME(clip == nullptr);

   //
   // MoveEx (Provides full coverage of Offset)
   //
   circle.SetRadius(10);
   center->Move(3, 5);

   Point2d from(10, 10);
   Point2d to(110, 110);
   circle.Move(from, to);
   TRY_TESTME(*center == Point2d(103, 105));

   //
   // OffsetEx
   //
   circle.SetRadius(10);
   center->Move(3, 5);
   Size2d size(100, 100);
   circle.Offset(size);
   TRY_TESTME(*center == Point2d(103, 105));


   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(circle) == true);

   //
   // LocatorPoint property
   //
   circle.SetRadius(10);
   center->Move(3, 5);

   // BottomLeft
   to.Move(90, 90);
   circle.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
   TRY_TESTME(from == Point2d(90, 90));
   TRY_TESTME(*center == Point2d(100, 100));

   // BottomCenter
   to.Move(100, 90);
   circle.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
   TRY_TESTME(from == Point2d(100, 90));
   TRY_TESTME(*center == Point2d(100, 100));

   // BottomRight
   to.Move(110, 90);
   circle.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
   TRY_TESTME(from == Point2d(110, 90));
   TRY_TESTME(*center == Point2d(100, 100));

   // CenterLeft
   to.Move(90, 100);
   circle.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
   TRY_TESTME(from == Point2d(90, 100));
   TRY_TESTME(*center == Point2d(100, 100));

   // CenterCenter
   to.Move(100, 100);
   circle.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*center == Point2d(100, 100));

   // CenterRight
   to.Move(110, 100);
   circle.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
   TRY_TESTME(from == Point2d(110, 100));
   TRY_TESTME(*center == Point2d(100, 100));

   // TopLeft
   to.Move(90, 110);
   circle.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
   TRY_TESTME(from == Point2d(90, 110));
   TRY_TESTME(*center == Point2d(100, 100));

   // TopCenter
   to.Move(100, 110);
   circle.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
   TRY_TESTME(from == Point2d(100, 110));
   TRY_TESTME(*center == Point2d(100, 100));

   // TopRight
   to.Move(110, 110);
   circle.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::TopRight);
   TRY_TESTME(from == Point2d(110, 110));
   TRY_TESTME(*center == Point2d(100, 100));

   // HookPoint
   to.Move(100, 100);
   circle.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
   from = circle.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
   TRY_TESTME(from == Point2d(100, 100));
   TRY_TESTME(*center == Point2d(100, 100));

   //
   // RotateEx (Provides coverage of Rotate)
   //
   center->Move(10, 0);
   Point2d c(0, 0);
   circle.Rotate(c, PI_OVER_2);
   TRY_TESTME(*center == Point2d(0, 10));

   TESTME_EPILOG("Circle");
}

#endif // _UNITTEST



