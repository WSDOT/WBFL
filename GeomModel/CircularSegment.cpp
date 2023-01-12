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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
   Float64 hx, hy;
   GetHookPoint()->GetLocation(&hx, &hy);
   Float64 cx = hx - (m_Radius - m_MidOrdinate) * cos(m_Rotation);
   Float64 cy = hy - (m_Radius - m_MidOrdinate) * sin(m_Rotation);
   return Point2d(cx, cy);
}

void CircularSegment::SetRadius(Float64 r)
{
   if (r < 0) THROW_GEOMETRY(_T("CircularSegment::SetRadius - invalid radius"));

   Point2d center = GetCenter();

   m_Radius = r;

   // If the radius got so small that MO is beyond the boundries
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
   if (!InRange(0.0, mo, 2*m_Radius)) THROW_GEOMETRY(_T("CircularSegment::SetMidOrdinate - midordinte cannot be greater than twice the radius"));

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

   Float64 cx, cy;
   center.GetLocation(&cx, &cy);

   Float64 x1, y1;
   Float64 x2, y2;

   x1 = cx + m_Radius * cos(m_Rotation - angle / 2);
   y1 = cy + m_Radius * sin(m_Rotation - angle / 2);

   x2 = cx + m_Radius * cos(m_Rotation + angle / 2);
   y2 = cy + m_Radius * sin(m_Rotation + angle / 2);

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
   ASSERTVALID;

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
   mohrCircle.ComputeState(m_Rotation,ixx,iyy,ixy);

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
   auto& p1 = chord.GetStartPoint();
   auto& p2 = chord.GetEndPoint();

   Float64 p1x = p1->X();
   Float64 p1y = p1->Y();
   Float64 p2x = p2->X();
   Float64 p2y = p2->Y();

   // Get boundary line
   Line2d line(chord);

   Float64 c;
   Vector2d n;
   line.GetImplicit(&c, &n); // normal to line
   Float64 nx,ny;
   nx = n.X();
   ny = n.Y();
   // drown out any noice in the vector
   nx = IsZero(nx) ? 0.00 : nx;
   ny = IsZero(ny) ? 0.00 : ny;

   // Center of circle
   Float64 cx, cy;
   Point2d center(GetCenter());
   center.GetLocation(&cx, &cy);

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
   Line2d line(*chord.GetStartPoint(), *chord.GetEndPoint());
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
   if (*chord.GetStartPoint() == *chord.GetEndPoint())
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
      Float64 c;
      Vector2d v1;
      clipLine.GetImplicit(&c, &v1); // v1 is normal to line
      Point2d p;
      Vector2d v2;
      normal_line.GetExplicit(&p, &v2); // v2 is in the direction of normal_line

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
      Float64 c;
      Vector2d n1,n2;
      chord_line.GetImplicit(&c, &n1); // normal to chord line
      clipLine.GetImplicit(&c, &n2); // normal to clipping line

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
         // Check the interesction point
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
            Float64 nx, ny;
            n2.GetDimensions(&nx, &ny);
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
   if (clip_top == nullptr) return std::unique_ptr<Shape>(); // entier shape clipped away

   // Clip using Right edge
   line.ThroughPoints(r.TopRight(), r.BottomRight());
   std::unique_ptr<Shape> clip_right = clip_top->CreateClippedShape(line, Line2d::Side::Left);
   if (clip_right == nullptr) return std::unique_ptr<Shape>(); // entier shape clipped away

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

Float64 CircularSegment::GetFurthestDistance(const Line2d& line, Line2d::Side side) const
{
   Point2d fp;
   Float64 fd;
   GetFurthestPoint(line, side, fp, fd);
   return fd;
}

void CircularSegment::GetFurthestPoint(const Line2d& line, Line2d::Side side, Point2d& furthestPoint, Float64& furthestDistance) const
{
   Line2d bndLine(GetChord());

   Float64 temp;
   Vector2d n1; // normal of boundary line
   Vector2d n2; // normal of input line

   bndLine.GetImplicit(&temp, &n1);
   line.GetImplicit(&temp, &n2);

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
      auto& p1 = chord.GetStartPoint();
      auto& p2 = chord.GetEndPoint();
      Float64 d1 = -1.0 * line.DistanceToPoint(*p1);
      Float64 d2 = -1.0 * line.DistanceToPoint(*p2);
      if (d1 < d2)
      {
         furthestDistance = d2;
         furthestPoint = *p2;
      }
      else
      {
         furthestDistance = d1;
         furthestPoint = *p1;
      }
   }
   else
   {
      // Lines are in the same direction. The furthest distance is the
      // shortest distance from the line to the center of the circle plus
      // the radius
      Circle circle(GetCenter(), m_Radius);
      circle.GetFurthestPoint(line, side, furthestPoint, furthestDistance);

#if defined _DEBUG
      Float64 distToCenter; // Shortest distance from line to center of circle
                           // if < 0, circle is to the left of the line
      distToCenter = -1.0 * line.DistanceToPoint(GetCenter());

      ASSERT(IsEqual(furthestDistance, m_Radius + distToCenter));
#endif
   }
}

#if defined _DEBUG
bool CircularSegment::AssertValid() const
{
   if ( m_Radius < 0 )
      return false;

   if ( m_MidOrdinate < 0 || (2*m_Radius) < m_MidOrdinate )
      return false;

   return ShapeImpl::AssertValid();
}

void CircularSegment::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("*** Dump for CircularSegment ***")<< WBFL::Debug::endl;
   ShapeImpl::Dump( os );
   os << _T("  Hook Point      = (") << GetHookPoint()->X()<<_T(", ")<< GetHookPoint()->Y()<<_T(")")<< WBFL::Debug::endl;
   os << _T("  Center Point    = (") << GetCenter().X() << _T(", ") << GetCenter().Y() <<_T(")") << WBFL::Debug::endl;
   os << _T("  Radius          = ") << m_Radius      << WBFL::Debug::endl;
   os << _T("  Mid-ordinate    = ") << m_MidOrdinate << WBFL::Debug::endl;
}
#endif // _DEBUG

void CircularSegment::OnUpdatePolygon(std::unique_ptr<Polygon>& polygon) const
{
   ASSERTVALID;

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

   Float64 cx, cy; GetCenter().GetLocation(&cx, &cy);

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

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
#include <GeomModel/Polygon.h>
#include <GeomModel/UnitTest.h>
bool CircularSegment::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CircularSegment");

   Float64 radius = 50;
   Float64 mo = radius;
   CircularSegment circseg(Point2d(0,0),radius,mo,0);
   ShapeProperties props = circseg.GetProperties();

   TRY_TESTME( IsEqual(props.GetArea(),M_PI*radius*radius/2) );
   TRY_TESTME( IsEqual(props.GetIxx(),M_PI*radius*radius*radius*radius/8) );
   TRY_TESTME( IsEqual(props.GetIyy(),pow(radius,4)*(9*M_PI*M_PI-64)/(72*M_PI)) );
   TRY_TESTME( IsEqual(props.GetIxy(),0.0) );
   TRY_TESTME( IsEqual(props.GetCentroid().X(),4*radius/(3*M_PI)) );
   TRY_TESTME( IsEqual(props.GetCentroid().Y(),0.0) );
   TRY_TESTME( props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal );

   // rotate 90 deg and check results
   circseg.SetRotation(PI_OVER_2);
   props = circseg.GetProperties();
   TRY_TESTME( IsEqual(props.GetArea(),M_PI*radius*radius/2) );
   TRY_TESTME( IsEqual(props.GetIxx(),pow(radius,4)*(9*M_PI*M_PI-64)/(72*M_PI)) );
   TRY_TESTME( IsEqual(props.GetIyy(),M_PI*radius*radius*radius*radius/8) );
   TRY_TESTME( IsEqual(props.GetIxy(),0.0) );
   TRY_TESTME( IsEqual(props.GetCentroid().X(),0.0) );
   TRY_TESTME( IsEqual(props.GetCentroid().Y(),4*radius/(3*M_PI)) );
   TRY_TESTME( props.GetCoordinateSystem() == ShapeProperties::CoordSystemType::Centroidal );

   circseg.SetRotation(0.0);
   circseg.SetCenter(Point2d(10, 10));
   circseg.SetRadius(10);
   circseg.SetMidOrdinate(5);
   TRY_TESTME(circseg.PointInShape(Point2d(1, 1)) == false);
   TRY_TESTME(circseg.PointInShape(Point2d(10, 10)) == false);
   TRY_TESTME(circseg.PointInShape(Point2d(17, 10)) == true);

   ////////////////////////////
   // Test Polygon
   //
   // PolyPoints are tested by CircularSegment.xls. This
   // spreadsheet plots the polypoints so I can visually verify
   // the shape
   // The following are points reported from the spreadsheet and
   // verified visually. They are coded here for regression testing purposes
   // If the implementation changes, these points should not change
   Float64 px[] = {
      51.7356,
      53.7115,
      55.4346,
      56.8948,
      58.0837,
      58.9944,
      59.6217,
      59.9619,
      60.013,
      59.7748,
      59.2487,
      58.4376,
      57.3463,
      55.981,
      54.3498,
      52.462,
      50.3285,
      47.9617,
      45.3753,
      42.5842,
      39.6046,
      36.4537,
      33.1498,
      29.712,
      26.1601,
      22.5147,
      18.7969,
      15.0283,
      11.2305,
      7.42564,
      3.63566,
      -0.117501,
      -3.81213,
      -7.42685,
      -10.9408,
      -14.3335,
      -17.5855
   };

   Float64 py[] = {
      -17.5855,
      -14.3335,
      -10.9408,
      -7.42685,
      -3.81213,
      -0.117501,
      3.63566,
      7.42564,
      11.2305,
      15.0283,
      18.7969,
      22.5147,
      26.1601,
      29.712,
      33.1498,
      36.4537,
      39.6046,
      42.5842,
      45.3753,
      47.9617,
      50.3285,
      52.462,
      54.3498,
      55.981,
      57.3463,
      58.4376,
      59.2487,
      59.7748,
      60.013,
      59.9619,
      59.6217,
      58.9944,
      58.0837,
      56.8948,
      55.4346,
      53.7115,
      51.7356
   };

   circseg.SetRotation(M_PI/4);
   circseg.SetRadius(50);
   circseg.SetMidOrdinate(40);
   circseg.SetCenter(Point2d(10,10));

   const std::vector<Point2d>& vPoints = circseg.GetPolyPoints();
   int i = 0;
   for(const auto& point : vPoints)
   {
      TRY_TESTME(IsEqual(point.X(),px[i], 0.0001));
      TRY_TESTME(IsEqual(point.Y(),py[i], 0.0001));
      i++;
   }

   ////////////////////////////
   // Test ClipWithLine
   circseg.SetRotation(0.0);
   radius = 50;
   mo = radius;
   circseg.SetRadius(radius);
   circseg.SetMidOrdinate(mo);
   circseg.SetCenter(Point2d(10,10));

   // clipping line well below shape (shape on right of line)
   Line2d line(Point2d(100,-70),Point2d(-100,-70));
   std::unique_ptr<Shape> clipShape(circseg.CreateClippedShape(line,Line2d::Side::Left));
   props = clipShape->GetProperties();
   TRY_TESTME(IsEqual(props.GetArea(),M_PI*radius*radius/2));

   // reverse clipping line (shape on left of line)
   // entire shape clipped away
   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Right));
   TRY_TESTME(clipShape.get() == nullptr);

   // clip shape in such a way that we are left with a quarter circle
   circseg.SetCenter(Point2d(100,100));
   circseg.SetRotation(PI_OVER_2);
   radius = 50;
   mo = radius;
   circseg.SetRadius(radius);
   circseg.SetMidOrdinate(mo);

   line.ThroughPoints(Point2d(100,-500),Point2d(100,500));

   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Left));
   props = clipShape->GetProperties();
   Float64 val1 = props.GetArea();
   Float64 val2 = M_PI*radius*radius/4;
   TRY_TESTME(IsEqual(val1,val2,0.01));

   // Test relative correctness of centroid.
   // Should be left and above center of circle
   // and x and y should be equal.
   TRY_TESTME(props.GetCentroid().X() > 100);
   TRY_TESTME(props.GetCentroid().Y() > 100);
   TRY_TESTME(IsEqual(props.GetCentroid().X(),props.GetCentroid().Y(),0.0001));

   // clip in such a way the the result is still a circular segment
   circseg.SetCenter(Point2d(0,0));
   radius = 50;
   mo = 60;
   circseg.SetRadius(radius);
   circseg.SetMidOrdinate(mo);
   circseg.SetRotation(0);
   line.ThroughPoints(Point2d(40,-100),Point2d(40,100));
   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Left));
   CircularSegment* clip = dynamic_cast<CircularSegment*>(clipShape.get());
   TRY_TESTME(clip != nullptr);
   // center and radius should be the same
   TRY_TESTME(IsEqual(circseg.GetRadius(),clip->GetRadius()));
   TRY_TESTME(IsEqual(circseg.GetCenter().X(),clip->GetCenter().X()));
   TRY_TESTME(IsEqual(circseg.GetCenter().Y(),clip->GetCenter().Y()));
   // mid-ordinate should be the radius less the original mid-ordinate
   TRY_TESTME(IsEqual(clip->GetMidOrdinate(),mo-radius));

   // reverse the direction of the clipping line
   // result should be a polygon.
   // area clip = area shape - area clip from above
   //
   // get area of source shape and the clip shape from above
   Float64 area1, area2, area3;
   props = circseg.GetProperties();
   area1 = props.GetArea();

   props = clip->GetProperties();
   area2 = props.GetArea();

   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Right));

   props = clipShape->GetProperties();
   area3 = props.GetArea();
   val1 = area1 - area2;
   TRY_TESTME( IsEqual(area3,val1,0.35) );

   // run a clipping line through the straight edge of the shape
   // Clip with line going both direction. Sum of clipped shape areas
   // must be equal to the area of the original shape
   circseg.SetCenter(Point2d(0,0));
   circseg.SetRadius(100);
   circseg.SetMidOrdinate(70);
   circseg.SetRotation(0);
   props = circseg.GetProperties();
   area1 = props.GetArea();

   line.ThroughPoints(Point2d(90,90),Point2d(20,-60));
   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Left));
   props = clipShape->GetProperties();
   area2 = props.GetArea();

   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Right));
   props = clipShape->GetProperties();
   area3 = props.GetArea();

   val1 = area2 + area3;
   TRY_TESTME(IsEqual(area1,val1));

   // same as above, but this time shape is a full circle (interior angle = 360)
   circseg.SetCenter(Point2d(0,0));
   circseg.SetRadius(50);
   circseg.SetMidOrdinate(100);
   circseg.SetRotation(0);
   props = circseg.GetProperties();
   area1 = props.GetArea();
   TRY_TESTME(IsEqual(50.0, props.GetXleft()));
   TRY_TESTME(IsEqual(50.0, props.GetYbottom()));
   TRY_TESTME(IsEqual(50.0, props.GetXright()));
   TRY_TESTME(IsEqual(50.0, props.GetYtop()));

   line.ThroughPoints(Point2d(-50,-50),Point2d(50,50));

   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Left));
   props = clipShape->GetProperties();
   area2 = props.GetArea();
   TRY_TESTME(IsEqual(area2*2,area1,0.001)); // clip shape half circle

   Float64 cgx1,cgy1;
   cgx1 = props.GetCentroid().X();
   cgy1 = props.GetCentroid().Y();

   clipShape = std::unique_ptr<Shape>(circseg.CreateClippedShape(line,Line2d::Side::Right));
   props = clipShape->GetProperties();
   area3 = props.GetArea();
   TRY_TESTME(IsEqual(area3*2,area1,0.5)); // clip shape half circle

   Float64 cgx2,cgy2;
   cgx2 = props.GetCentroid().X();
   cgy2 = props.GetCentroid().Y();

   val1 = area2 + area3;
   TRY_TESTME(IsEqual(area1,val1,0.2));

   TRY_TESTME(IsEqual(cgx1,-cgx2,0.001));
   TRY_TESTME(IsEqual(cgy1,-cgy2,0.001));


   // Test hook point behavior
   TRY_TESTME(UnitTest::TestHookPoint(circseg) == true);

   TESTME_EPILOG("CircularSegment");
}

#endif // _UNITTEST



