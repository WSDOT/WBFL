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
#include <GeomModel/CircularSegment.h>
#include <GeomModel/Circle.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/ShapeProperties.h>
#include <GeomModel/GeomOp2d.h>
#include <GeomModel/LineSegment2d.h>
#include <GeomModel/Circle2d.h>
#include <MathEx.h>
#include "MohrCircle.h"

using namespace WBFL::Geometry;

CircularSegment::CircularSegment() : ShapeOnAlternativePolygonImpl()
{
}

CircularSegment::CircularSegment(const Point2d& center,Float64 radius,Float64 midOrdinate,Float64 rotation) :
   ShapeOnAlternativePolygonImpl(), m_Radius(radius), m_MidOrdinate(midOrdinate),m_Rotation(rotation)
{
   PRECONDITION(0<=radius);
   UpdateHookPoint(center);
}

CircularSegment::CircularSegment(const CircularSegment& other) : ShapeOnAlternativePolygonImpl(other)
{
   Copy(other);
}

CircularSegment& CircularSegment::operator=(const CircularSegment& other)
{
   if (this != &other)
   {
      __super::operator=(other);
      Copy(other);
   }
   return *this;
}

CircularSegment::~CircularSegment()
{
}

void CircularSegment::SetCenter(const Point2d& center)
{
   UpdateHookPoint(center);
   SetDirtyFlag();
}

Point2d CircularSegment::GetCenter() const
{
   auto [hx,hy] = GetHookPoint()->GetLocation();
   auto cx = hx - (m_Radius - m_MidOrdinate) * cos(m_Rotation);
   auto cy = hy - (m_Radius - m_MidOrdinate) * sin(m_Rotation);
   return Point2d(cx, cy);
}

void CircularSegment::SetRadius(Float64 r)
{
   if (r < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_RADIUS);

   Point2d center = GetCenter();

   m_Radius = r;

   // If the radius got so small that MO is beyond the boundaries
   // of the circle, move MO to the edge of the circle
   if (2.0*m_Radius < m_MidOrdinate)
      m_MidOrdinate = 2*m_Radius;

   UpdateHookPoint(center);
   SetDirtyFlag();
}

Float64 CircularSegment::GetRadius() const
{
   return m_Radius;
}

void CircularSegment::SetMidOrdinate(Float64 mo)
{
   if (!InRange(0.0, mo, 2*m_Radius)) THROW_GEOMETRY(WBFL_GEOMETRY_E_MIDORDINATE);

   Point2d center = GetCenter();

   m_MidOrdinate = mo;
   UpdateHookPoint(center);
   SetDirtyFlag();
}

Float64 CircularSegment::GetMidOrdinate() const
{
   return m_MidOrdinate;
}

LineSegment2d CircularSegment::GetChord() const
{
   Point2d p1, p2;
   Point2d center(GetCenter());
   Float64 angle = GetInteriorAngle();
   if (IsEqual(angle, TWO_PI))
   {
      // special case - this is really a full circle
      CHECK(IsEqual(2 * m_Radius, m_MidOrdinate));
      p1 = center; p1.Offset(0, m_Radius);
      p2 = center; p2.Offset(0, -m_Radius);
   }

   auto [cx, cy] = center.GetLocation();

   auto x1 = cx + m_Radius * cos(m_Rotation - angle / 2);
   auto y1 = cy + m_Radius * sin(m_Rotation - angle / 2);

   auto x2 = cx + m_Radius * cos(m_Rotation + angle / 2);
   auto y2 = cy + m_Radius * sin(m_Rotation + angle / 2);

   p1.Move(x1, y1);
   p2.Move(x2, y2);

   return LineSegment2d(p1, p2);
}

void CircularSegment::SetRotation(Float64 rotation)
{
   Point2d center(GetCenter());
   m_Rotation = rotation;
   UpdateHookPoint(center);
   SetDirtyFlag();
}

Float64 CircularSegment::GetRotation() const
{
   return m_Rotation;
}

void CircularSegment::SetInteriorAngle(Float64 ia)
{
   PRECONDITION( 0 <= ia && ia <= TWO_PI );

   Point2d center(GetCenter());

   m_MidOrdinate = m_Radius*(1.0 - cos(ia/2));
   UpdateHookPoint(center);
   SetDirtyFlag();
}

Float64 CircularSegment::GetInteriorAngle() const
{
   if (IsZero(m_Radius)) return 0.0;

   if (IsZero(m_MidOrdinate)) return M_PI;

   Float64 x = (m_Radius - m_MidOrdinate)/m_Radius;
   if ( IsZero(x-1.0) )
      x = 1.0;

   Float64 angle = acos(x);
	return 2.0*angle;
}

void CircularSegment::DoOffset(const Size2d& delta)
{
   GetHookPoint()->Offset(delta);
   SetDirtyFlag();
}

void CircularSegment::DoRotate(const Point2d& center, Float64 angle)
{
   GetHookPoint()->Rotate(center, angle);
   m_Rotation += angle;
   m_Rotation = GeometricOperations::NormalizeAngle(m_Rotation);
   SetDirtyFlag();
}

ShapeProperties CircularSegment::GetProperties() const
{
   // Compute properties for non-rotated shape, about global axes (0,0)
   Float64 angle = GetInteriorAngle()/2.0;
   Float64 area, ixx, iyy, ixy, cgx, cgy;

   if ( IsZero(angle) || IsZero(m_MidOrdinate) )
   {
      area = 0;
      ixx = 0;
      iyy = 0;
      ixy = 0;
      cgx = m_Radius;
      cgy = 0;
   }
   else
   {
      area = m_Radius*m_Radius*(angle - sin(2*angle)/2);
      ixx = (area*m_Radius*m_Radius/4)*(1 - (4*pow(sin(angle),3)*cos(angle))/(3*(2*angle - sin(2*angle))));
      iyy = (area*m_Radius*m_Radius/4)*(1 + (4*pow(sin(angle),3)*cos(angle))/(2*angle - sin(2*angle)));
      ixy = 0.00;

      cgx = (4*m_Radius/3) * pow(sin(angle),3)/(2*angle-sin(2*angle));
      cgx = IsZero(cgx) ? 0 : cgx;
      cgy = 0.00;
   }

   Point2d cg(cgx,cgy);

   // Transform properties to centroidal coordinates
   iyy = iyy - area*cgx*cgx;

   // Transform properties into rotated coordinate system
   MohrCircle mohrCircle(ixx,iyy,ixy);
   std::tie(ixx,iyy,ixy) = mohrCircle.ComputeState(m_Rotation);

   // next need to translate and rotate CG to proper position
   Point2d center(GetCenter());
   cg.Offset(center.X(),center.Y());
   cg.Rotate(center,m_Rotation);

   // Get bounded box in centroidal coordinates
   Rect2d bb = GetBoundingBox();

   return ShapeProperties(area, cg, ixx, iyy, ixy, cg.X() - bb.Left(), cg.Y() - bb.Bottom(), bb.Right() - cg.X(), bb.Top() - cg.Y());
}

Rect2d CircularSegment::GetBoundingBox() const
{
   if (IsEqual(2 * m_Radius, m_MidOrdinate))
   {
      // Special case, full circle
      Point2d center(GetCenter());
      return Rect2d(center.X() - m_Radius, center.Y() - m_Radius, center.X() + m_Radius, center.Y() + m_Radius);
   }

   LineSegment2d chord = GetChord();
   const auto& p1 = chord.GetStartPoint();
   const auto& p2 = chord.GetEndPoint();

   Float64 p1x = p1.X();
   Float64 p1y = p1.Y();
   Float64 p2x = p2.X();
   Float64 p2y = p2.Y();

   // Get boundary line
   Line2d line(chord);

   auto [c,n] = line.GetImplicit(); // normal to line
   Float64 nx,ny;
   nx = n.X();
   ny = n.Y();
   // drown out any noise in the vector
   nx = IsZero(nx) ? 0.00 : nx;
   ny = IsZero(ny) ? 0.00 : ny;

   // Center of circle
   Point2d center(GetCenter());
   auto [cx,cy] = center.GetLocation();

   // Find sides
   Float64 left, right, top, bottom;

   // left
   if ( (IsZero(nx) && m_Radius < m_MidOrdinate) || 0.0 < nx )
      left = cx - m_Radius;
   else
      left = Min(p1x,p2x);

   // right
   if ( (IsZero(nx) && m_Radius < m_MidOrdinate) || nx < 0.0 )
      right = cx + m_Radius;
   else
      right = Max(p1x,p2x);

   // top
   if ( (IsZero(ny) && m_MidOrdinate < m_Radius) || 0.0 < ny )
      top = Max(p1y,p2y);
   else
      top = cy + m_Radius;

   // bottom
   if ( (IsZero(ny) && m_MidOrdinate < m_Radius) || ny < 0.0 )
      bottom = Min(p1y,p2y);
   else
      bottom = cy - m_Radius;

   return Rect2d(left, bottom, right, top);
}

bool CircularSegment::PointInShape(const Point2d& p) const
{
   // Point must be in the circle and to the right of the line
   Circle circle(GetCenter(), m_Radius);
   if (!circle.PointInShape(p)) return false;

   LineSegment2d chord = GetChord();
   Line2d line(chord.GetStartPoint(), chord.GetEndPoint());
   if (line.GetSide(p) == Line2d::Side::Left) return false;

   return true;
}

Float64 CircularSegment::GetPerimeter() const
{
   Float64 angle = GetInteriorAngle();
   angle /= 2.0;

   Float64 arc_length = IsZero(m_MidOrdinate) ? 0 : 2.0 * angle * m_Radius;
   Float64 chord_length = IsZero(m_MidOrdinate) ? 0 : 2 * m_Radius * sin(angle);

   return arc_length + chord_length;
}

std::unique_ptr<Shape> CircularSegment::CreateClone() const
{
   return std::make_unique<CircularSegment>( *this );
}

std::unique_ptr<Shape> CircularSegment::CreateClippedShape(const Line2d& line, Line2d::Side side) const
{
   // boundary case: if radius is zero - return zero
   if (m_Radius<=0)
      return nullptr;

   LineSegment2d chord(GetChord());
   if (chord.GetStartPoint() == chord.GetEndPoint())
   {
      CHECK(IsEqual(GetMidOrdinate(), 2.0 * GetRadius()));
      // this "circular segment" is actually a full circle
      return Circle(GetCenter(), m_Radius).CreateClippedShape(line, side);
   }

   // This routine always clips away the left side of the line, leaving
   // the portion of the shape on the right side.
   // If the right side clipping is requested, reverse the direction of
   // the clipping line
   Line2d clipLine = line;
   if (side == Line2d::Side::Right)
      clipLine.Reverse();

   // Find the intersection of the circle and the clipping line.
   // If either of the intersection points are in the shape, then
   // a clip is required.
   //
   // NOTE:
   // LineCircleIntersect will return points on the boundary of the circle
   // PointInShape cannot be used because points on the boundary are considered
   // out of the shape.
   Circle2d circle(GetCenter(), m_Radius);

   Point2d p1, p2;
   IndexType nIntersections = GeometricOperations::Intersect(clipLine, circle, &p1, &p2);

   bool bPoint1InShape = false;
   bool bPoint2InShape = false;

   Line2d chord_line(chord);

   if (1 <= nIntersections)
   {
      Float64 offset1 = chord_line.DistanceToPoint(p1);
      bPoint1InShape = (offset1 < 0) ? true : false;
   }

   if (nIntersections == 2)
   {
      Float64 offset2 = chord_line.DistanceToPoint(p2);
      bPoint2InShape = (offset2 < 0) ? true : false;
   }

   if (nIntersections == 0 || bPoint1InShape == false && bPoint2InShape == false)
   {
      // Clipping line does not intersect shape. If shape is
      // on the right side of the line, it remains
      // Determine if the shape is on the left or right of the line.
      Line2d normal_line = GeometricOperations::CreateNormalLineThroughPoint(line, GetCenter());
      auto [c,v1] = clipLine.GetImplicit(); // v1 is normal to line
      auto [p,v2] = normal_line.GetExplicit(); // v2 is in the direction of normal_line

      // If v2 and v1 have the same direction their dot product will be > 0
      Float64 dot = v1.Dot(v2);
      CHECK(!IsZero(dot)); // dot is only zero if v1 and v2 are at right
                                 // angles from one another. This should never
                                 // happen in this case.

      // The clipping line does not intersect shape
      if (0 < dot)
      {
         // Circle in on the right
         // circle is entirely within clipping region
         return CreateClone();
      }
      else
      {
         // circle is entirely outside of clipping region
         return nullptr;
      }
   }
   else
   {
      // Clipping line intersects the shape
      // If the clipping line is in the same direction as the edge line,
      // the resulting shape is a circular segment, unless the clipping line and
      // edge line intersect on the shape boundary
      auto [c1,n1] = chord_line.GetImplicit(); // normal to chord line
      auto [c2,n2] = clipLine.GetImplicit(); // normal to clipping line

      Float64 dot = n1.Dot(n2);

      if (dot < 0)
      {
         // Lines are in opposite direct

         // Make shape into a Polygon and use its clip
         return GetPolygon()->CreateClippedShape(line, side);
      }
      else
      {
         // Lines are same direction
         // Check the intersection point
         Point2d is;
         if (GeometricOperations::Intersect(clipLine, chord, &is) == 1)
         {
            // Clipping line intersects straight edge of shape
            // Make shape into a Polygon and use its clip
            return GetPolygon()->CreateClippedShape(line, side);
         }
         else
         {
            // resulting shape is a circular segment
            auto clone = std::make_unique<CircularSegment>(*this);
            auto [nx,ny] = n2.GetDimensions();
            Float64 rotation = atan2(-ny, -nx);
            clone->Rotate(GetCenter(),rotation);

            Float64 offset = clipLine.DistanceToPoint(GetCenter());
            clone->SetMidOrdinate(m_Radius - offset);
            return clone;
         }
         CHECK(false); // should never get here
      }
   }

   CHECK(false); // should never get here
   return nullptr;
}

std::unique_ptr<Shape> CircularSegment::CreateClippedShape(const Rect2d& r, Shape::ClipRegion region) const
{
   // Clip using top edge
   Line2d line(r.TopLeft(), r.TopRight());

   std::unique_ptr<Shape> clip_top = CreateClippedShape(line, Line2d::Side::Left);
   if (clip_top == nullptr) return std::unique_ptr<Shape>(); // entire shape clipped away

   // Clip using Right edge
   line.ThroughPoints(r.TopRight(), r.BottomRight());
   std::unique_ptr<Shape> clip_right = clip_top->CreateClippedShape(line, Line2d::Side::Left);
   if (clip_right == nullptr) return std::unique_ptr<Shape>(); // entire shape clipped away

   // Clip using Bottom edge
   line.ThroughPoints(r.BottomRight(), r.BottomLeft());
   std::unique_ptr<Shape> clip_bottom = clip_right->CreateClippedShape(line, Line2d::Side::Left);
   if (clip_bottom == nullptr) return std::unique_ptr<Shape>(); // entire shape clipped away

   // Clip using Left edge
   line.ThroughPoints(r.BottomLeft(), r.TopLeft());
   std::unique_ptr<Shape> clip_left = clip_bottom->CreateClippedShape(line, Line2d::Side::Left);
   if (clip_left == nullptr) return std::unique_ptr<Shape>(); // entire shape clipped away

   return clip_left;
}

Float64 CircularSegment::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   auto [fp,fd] = GetFurthestPoint(line, side);
   return fd;
}

std::pair<Point2d,Float64> CircularSegment::GetFurthestPoint(const Line2d& line, Line2d::Side side) const
{
   Point2d furthestPoint;
   Float64 furthestDistance = -99999;

   Line2d bndLine(GetChord());

   auto [temp1,n1] = bndLine.GetImplicit(); // n1, normal of boundary line
   auto [temp2,n2] = line.GetImplicit(); // n2, normal of input line

   Float64 dot;
   dot = n1.Dot(n2);

   // if dot < 0, the line in question and the straight edge of the shape
   // are in opposite directions

   if (dot < 0)
   {
      // Lines are in opposite direction.
      // The furthest distance is the greater of the shorter distance from the line
      // to the edge points of the shape.
      //
      // Distance to point returns a negative value if the point is on the right side of the line.
      LineSegment2d chord(GetChord());
      const auto& p1 = chord.GetStartPoint();
      const auto& p2 = chord.GetEndPoint();
      Float64 d1 = -1.0 * line.DistanceToPoint(p1);
      Float64 d2 = -1.0 * line.DistanceToPoint(p2);
      if (d1 < d2)
      {
         furthestDistance = d2;
         furthestPoint = p2;
      }
      else
      {
         furthestDistance = d1;
         furthestPoint = p1;
      }
   }
   else
   {
      // Lines are in the same direction. The furthest distance is the
      // shortest distance from the line to the center of the circle plus
      // the radius
      Circle circle(GetCenter(), m_Radius);
      std::tie(furthestPoint,furthestDistance) = circle.GetFurthestPoint(line, side);

#if defined _DEBUG
      Float64 distToCenter; // Shortest distance from line to center of circle
                           // if < 0, circle is to the left of the line
      distToCenter = -1.0 * line.DistanceToPoint(GetCenter());

      CHECK(IsEqual(furthestDistance, m_Radius + distToCenter));
#endif
   }

   return std::make_pair(furthestPoint, furthestDistance);
}

void CircularSegment::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   // number of vertex points used to describe a polyline version of a circle
   const short NUM_POINTS = 37; // 36 segments.

   Float64 angle = GetInteriorAngle()/2.0;
   Float64 angle_inc = 2*angle / (NUM_POINTS-1);

   // determine radius of circle to make an "Area Perfect" polygon.
   Float64 cfArea = m_Radius*m_Radius*(angle - sin(2*angle)/2); // closed form area

   Float64 rad = sqrt( cfArea/(((NUM_POINTS-1)*sin(angle_inc/2)*cos(angle_inc/2) - sin(angle)*cos(angle))) );

#if defined _DEBUG
   Float64 polyArea = (NUM_POINTS-1)*(rad*rad*sin(angle_inc/2)*cos(angle_inc/2))-rad*rad*sin(angle)*cos(angle);
   CHECK( IsEqual(cfArea,polyArea) );
#endif // _DEBUG

   auto [cx,cy] = GetCenter().GetLocation();

   Float64 startAngle = m_Rotation - angle;

   for (short i = 0; i < NUM_POINTS; i++)
   {
      Float64 a = startAngle + i * angle_inc;

      Float64 x = cx + rad * cos(a);
      Float64 y = cy + rad * sin(a);

      polygon->AddPoint(x,y);
   }
}

void CircularSegment::UpdateHookPoint(const Point2d& center)
{
   Float64 x,y;
   x = center.X() + (m_Radius-m_MidOrdinate)*cos(m_Rotation);
   y = center.Y() + (m_Radius-m_MidOrdinate)*sin(m_Rotation);

   GetHookPoint()->Move(x,y);
}

void CircularSegment::Copy(const CircularSegment& other)
{
   m_Radius = other.m_Radius;
   m_MidOrdinate = other.m_MidOrdinate;
   m_Rotation = other.m_Rotation;
}


