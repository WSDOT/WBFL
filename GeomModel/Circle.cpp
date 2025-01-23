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
#include <GeomModel/Circle.h>
#include <GeomModel/CircularSegment.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include <numeric>

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

std::pair<std::shared_ptr<const Point2d>, Float64> Circle::GetParameters() const
{
   return std::make_pair(GetHookPoint(), m_Radius);
}

void Circle::ThroughTwoPoints(const Point2d& p1, const Point2d& p2)
{
   Float64 diameter = p1.Distance(p2);
   if (IsZero(diameter)) THROW_GEOMETRY(WBFL_GEOMETRY_E_COINCIDENTPOINTS);

   m_Radius = diameter / 2;
   SetHookPoint((p1+p2)/2);

   SetDirtyFlag();
}

void Circle::ThroughThreePoints(const Point2d& p1, const Point2d& p2, const Point2d& p3)
{
   // Create lines that go between the points
   Line2d line1(p1, p2);
   Line2d line2(p2, p3);

   // Determine if the lines are colinear
   if (line1.IsColinear(line2)) THROW_GEOMETRY(WBFL_GEOMETRY_E_COLINEARLINES);

   // Create lines that are normal to line1 and line2, passing through the midpoint
   auto [x1,y1] = p1.GetLocation();
   auto [x2,y2] = p2.GetLocation();
   auto [x3,y3] = p3.GetLocation();

   Float64 mx1 = std::midpoint(x1,x2);
   Float64 my1 = std::midpoint(y1,y2);
   Float64 mx2 = std::midpoint(x2,x3);
   Float64 my2 = std::midpoint(y2,y3);

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
   auto [fp,fd] = GetFurthestPoint(line, side);
   return fd;
}

std::pair<Point2d,Float64> Circle::GetFurthestPoint(const Line2d& line, Line2d::Side side) const
{
   auto [c,n] = line.GetImplicit();
   Float64 angle = n.GetDirection();
   if (side == Line2d::Side::Right)
      angle += M_PI;

   Float64 x = cos(angle) * m_Radius + GetHookPoint()->X();
   Float64 y = sin(angle) * m_Radius + GetHookPoint()->Y();
   Point2d furthestPoint(x, y);
      
   CHECK(IsEqual(m_Radius, furthestPoint.Distance(*GetHookPoint())));

   auto furthestDistance = line.DistanceToPoint(furthestPoint);
   if (side == Line2d::Side::Right)
      furthestDistance *= -1;

   // check distance from line to center
   CHECK(IsEqual(furthestDistance, (side == Line2d::Side::Right ? -1 : 1) * line.DistanceToPoint(*GetHookPoint()) + m_Radius));

   // check point is on correct side of line. if furthestDistance < 0, the correct side is the opposite side than the request
   CHECK(line.GetSide(furthestPoint) == (furthestDistance < 0 ? (side == Line2d::Side::Right ? Line2d::Side::Left : Line2d::Side::Right) : side));

   return std::make_pair(furthestPoint, furthestDistance);
}

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

   auto [cx,cy] = GetHookPoint()->GetLocation();
   for (Int32 i = 0; i <= NUM_POINTS; i++)
   {
      Float64 a = i * angle_inc;
      Float64 x = cx + rad * cos(a);
      Float64 y = cy + rad * sin(a);
      polygon->AddPoint(x, y);
   }
}
