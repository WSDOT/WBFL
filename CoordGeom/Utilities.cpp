///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright � 1999-2023  Washington State Department of Transportation
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/Utilities.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/XCoordGeom.h>
#include <CoordGeom/Alignment.h>

#include <GeomModel/GeomOp2d.h>
#include <GeomModel/Polygon.h>
#include <GeomModel/Circle2d.h>
#include <GeomModel/Arc.h>

using namespace WBFL::COGO;


std::tuple<std::_tstring, std::_tstring, std::_tstring> Utilities::ParseAngleTags(const std::_tstring& strFormat)
{
   std::_tstring::size_type posFirst = strFormat.find(_T(","));
   std::_tstring::size_type posSecond = strFormat.find(_T(","), posFirst + 1);

   if (posFirst == std::_tstring::npos || posSecond == std::_tstring::npos)
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }

   std::_tstring strDegTag, strMinTag, strSecTag;
   strDegTag.assign(strFormat, 0, posFirst);
   strMinTag.assign(strFormat, posFirst + 1, posSecond - posFirst - 1);
   strSecTag.assign(strFormat, posSecond + 1, strFormat.size() - posFirst - 1);

   return std::make_tuple(strDegTag, strMinTag, strSecTag);;
}


std::tuple<short,unsigned short,Float64> Utilities::ToDMS(Float64 value)
{
   value = ToDegrees(value);

   short sign = BinarySign(value);
   value = fabs(value);

   short deg = (short)floor(value);
   value -= deg;
   value *= 60;
   unsigned short min = (unsigned short)floor(value);
   value -= min;
   Float64 sec = value * 60;

   if (IsZero(60. - sec, 0.051)) // 59.95 ==> 60.0, 59.94 ==> 59.9
   {
      sec = 0.;
      min += 1;
   }

   if (min == 60)
   {
      min = 0;
      deg += 1;
   }

   deg *= sign;

   return std::make_tuple(deg, min, sec);
}

Float64 Utilities::FromDMS(short deg, unsigned short min, Float64 sec)
{
   if ((min < 0 || 60 <= min) || (sec < 0.0 || 60.0 <= sec))
      THROW_COGO(WBFL_COGO_E_ANGLE);


   Float64 angle;
   angle = BinarySign(deg) * (abs(deg) + (Float64)min / 60. + sec / 3600.);

   angle = ToRadians(angle);

   return angle;
}

Float64 Utilities::NormalizeAngle(Float64 angle)
{
   return WBFL::Geometry::GeometricOperations::NormalizeAngle(angle);
}

bool Utilities::IsPointBeforeStart(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end, const WBFL::Geometry::Point2d& point)
{
   Float64 distance;
   Direction direction;
   std::tie(distance,direction) = ComputeInverse(start, end);

   auto newPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(start, direction.GetValue(), point);

   return newPoint.X() < 0 ? true : false;
}

bool Utilities::IsPointAfterEnd(const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end, const WBFL::Geometry::Point2d& point)
{
   Float64 distance;
   Direction direction;
   std::tie(distance,direction) = ComputeInverse(start, end);

   auto newPoint = WBFL::Geometry::GeometricOperations::GlobalToLocal(end, direction.GetValue(), point);

   return 0 < newPoint.X() ? true : false;
}

WBFL::Geometry::Line2d Utilities::CreateParallelLine(const WBFL::Geometry::Point2d& p, const Direction& direction, Float64 offset)
{
   Float64 dir = direction.GetValue();
   Float64 normal = dir - PI_OVER_2; // normal to the line, in the direction of offset
   auto offset_point = LocateByDistanceAndDirection(p, offset, normal, 0.0); // point the line passes through

   WBFL::Geometry::Vector2d v(1.0,dir); // direction of the line

   return WBFL::Geometry::Line2d(offset_point, v);
}


WBFL::COGO::Angle Utilities::MeasureAngle(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& vertex, const WBFL::Geometry::Point2d& to)
{
   return WBFL::Geometry::GeometricOperations::Angle(from, vertex, to);
}

Float64 Utilities::MeasureArea(std::vector<WBFL::Geometry::Point2d>& vPoints)
{
   WBFL::Geometry::Polygon shape;
   shape.AddPoints(vPoints);
   return shape.GetProperties().GetArea();
}

Float64 Utilities::MeasureDistance(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2)
{
   return p1.Distance(p2);
}

WBFL::COGO::Direction Utilities::MeasureDirection(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2)
{
   Float64 distance;
   WBFL::COGO::Direction direction;
   std::tie(distance,direction) = ComputeInverse(p1, p2);
   return direction;
}

std::pair<Float64,WBFL::COGO::Direction> Utilities::ComputeInverse(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2)
{
   auto size = p2 - p1;

   Float64 dir = atan2(size.Dy(), size.Dx());
   if (IsZero(dir))
   {
      dir = 0.0;
   }
   else if (dir < 0)
   {
      dir += TWO_PI;
   }

   return std::make_pair(size.Magnitude(), dir);
}

WBFL::Geometry::Point2d Utilities::LocateByDistanceAndAngle(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 distance, const WBFL::COGO::Angle& angle, Float64 offset)
{
   // Get the back sight direction
   auto back_sight = MeasureDirection(to, from);
   auto normal = back_sight.IncrementBy(PI_OVER_2); // normal to the back sight

   // Locate a point at the desired offset. This will be the reference point from which we located the desired point
   auto ref_point = LocateByDistanceAndDirection(to, offset, normal, 0.00);

   // Locate the new point. Direction of line is the back sight plus the angle
   back_sight.Increment(angle);
   auto point = LocateByDistanceAndDirection(ref_point, distance, back_sight, 0.00);
   return point;
}

WBFL::Geometry::Point2d Utilities::LocateByDistanceAndDeflectionAngle(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 distance, const Angle& defAngle, Float64 offset)
{
   // Get the back sight direction
   auto back_sight = MeasureDirection(to, from);
   auto normal = back_sight.IncrementBy(PI_OVER_2); // normal to the back sight

   // Locate a point at the desired offset. This will be the reference point from which we located the desired point
   auto ref_point = LocateByDistanceAndDirection(to, offset, normal, 0.00);

   // Locate the new point. Direction of line is the back sight plus the angle + 180def
   Float64 dir = defAngle.GetValue();
   dir += M_PI;
   back_sight.Increment(dir);
   auto point = LocateByDistanceAndDirection(ref_point, distance, back_sight, 0.00);
   return point;
}

WBFL::Geometry::Point2d Utilities::LocateByDistanceAndDirection(const WBFL::Geometry::Point2d& from, Float64 distance, const Direction& direction, Float64 offset)
{
   Float64 x, y; std::tie(x,y) = from.GetLocation();
   Float64 dir = direction.GetValue();

   Float64 sindir = sin(dir);
   Float64 cosdir = cos(dir);

   Float64 dx = distance * cosdir;
   Float64 dy = distance * sindir;

   // Point on line
   x += dx;
   y += dy;

   // Apply offset
   x += offset * sindir;
   y -= offset * cosdir;

   return WBFL::Geometry::Point2d(x, y);
}

WBFL::Geometry::Point2d Utilities::LocatePointOnLine(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 distance, Float64 offset)
{
   // Get the direction of the line going from "from" to "to"
   auto line_direction = MeasureDirection(from, to);
   auto normal = line_direction.IncrementBy(-PI_OVER_2); // subtract 90deg to get the direction of the right normal line

   // Locate the offset "from" point
   auto pnt_offset = LocateByDistanceAndDirection(from, offset, normal, 0.0);

   // Locate the point
   auto point = LocateByDistanceAndDirection(pnt_offset, distance, line_direction, 0.00);
   return point;
}

std::pair<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d>  Utilities::LocateParallelLineByPoints(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, Float64 offset)
{
   WBFL::Geometry::LineSegment2d ls(from, to);
   auto newLS = WBFL::Geometry::GeometricOperations::CreateParallelLineSegment(ls, offset);
   return std::make_pair(newLS.GetStartPoint(), newLS.GetEndPoint());
}

WBFL::Geometry::LineSegment2d Utilities::LocateParallelLineSegment(const WBFL::Geometry::LineSegment2d& ls, Float64 offset)
{
   return WBFL::Geometry::GeometricOperations::CreateParallelLineSegment(ls, offset);
}

WBFL::Geometry::Point2d Utilities::IntersectBearings(const WBFL::Geometry::Point2d& p1, const Direction& dir1, Float64 offset1, const WBFL::Geometry::Point2d& p2, const Direction& dir2, Float64 offset2)
{
   auto line1 = CreateParallelLine(p1, dir1, offset1);
   auto line2 = CreateParallelLine(p2, dir2, offset2);

   WBFL::Geometry::Point2d point;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line1, line2, &point);
   if (nIntersections != 1)
   {
      THROW_COGO(WBFL_COGO_E_NOINTERSECTION);
   }

   return point;
}

WBFL::Geometry::Point2d Utilities::IntersectBearingAndCircle(const WBFL::Geometry::Point2d& p1, const Direction& dir1, Float64 offset1, const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& nearest)
{
   PRECONDITION(0.0 < radius);

   auto line = CreateParallelLine(p1, dir1, offset1);

   WBFL::Geometry::Circle2d circle(center, radius);

   WBFL::Geometry::Point2d i1, i2;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, circle, &i1, &i2);

   WBFL::Geometry::Point2d point;
   if (nIntersections == 1)
   {
      point = i1;
   }
   else if(nIntersections == 2)
   {
      Float64 d1 = nearest.Distance(i1);
      Float64 d2 = nearest.Distance(i2);
      if (d2 < d1)
      {
         point = i2;
      }
      else
      {
         point = i1;
      }
   }
   else
   {
      THROW_COGO(WBFL_COGO_E_NOINTERSECTION);
   }

   return point;
}

WBFL::Geometry::Point2d Utilities::IntersectCircles(const WBFL::Geometry::Point2d& center1, Float64 radius1, const WBFL::Geometry::Point2d& center2, Float64 radius2, const WBFL::Geometry::Point2d& nearest)
{
   PRECONDITION(0.0 < radius1);
   PRECONDITION(0.0 < radius2);

   WBFL::Geometry::Circle2d circle1(center1, radius1);
   WBFL::Geometry::Circle2d circle2(center2, radius2);

   WBFL::Geometry::Point2d i1, i2;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(circle1, circle2, &i1, &i2);

   WBFL::Geometry::Point2d point;
   if (nIntersections == 1)
   {
      point = i1;
   }
   else if (nIntersections == 2)
   {
      Float64 d1 = nearest.Distance(i1);
      Float64 d2 = nearest.Distance(i2);
      if (d2 < d1)
      {
         point = i2;
      }
      else
      {
         point = i1;
      }
   }
   else
   {
      THROW_COGO(WBFL_COGO_E_NOINTERSECTION);
   }

   return point;
}

WBFL::Geometry::Point2d Utilities::IntersectLineByPointsAndCircle(const WBFL::Geometry::Point2d& p1, const WBFL::Geometry::Point2d& p2, Float64 offset, const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& nearest)
{
   PRECONDITION(0.0 < radius);

   WBFL::Geometry::Line2d line(p1, p2);
   auto offset_line = WBFL::Geometry::GeometricOperations::CreateParallelLine(line, offset);

   WBFL::Geometry::Circle2d circle(center, radius);

   WBFL::Geometry::Point2d i1, i2;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(offset_line, circle, &i1, &i2);

   WBFL::Geometry::Point2d point;
   if (nIntersections == 1)
   {
      point = i1;
   }
   else if (nIntersections == 2)
   {
      Float64 d1 = nearest.Distance(i1);
      Float64 d2 = nearest.Distance(i2);
      if (d2 < d1)
      {
         point = i2;
      }
      else
      {
         point = i1;
      }
   }
   else
   {
      THROW_COGO(WBFL_COGO_E_NOINTERSECTION);
   }

   return point;
}

WBFL::Geometry::Point2d Utilities::IntersectLinesByPoints(const WBFL::Geometry::Point2d& p11, const WBFL::Geometry::Point2d& p12, Float64 offset1, const WBFL::Geometry::Point2d& p21, const WBFL::Geometry::Point2d& p22, Float64 offset2)
{
   WBFL::Geometry::Line2d l1(p11, p12);
   auto offset_line_1 = WBFL::Geometry::GeometricOperations::CreateParallelLine(l1, offset1);

   WBFL::Geometry::Line2d l2(p21, p22);
   auto offset_line_2 = WBFL::Geometry::GeometricOperations::CreateParallelLine(l2, offset2);

   WBFL::Geometry::Point2d point;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(offset_line_1, offset_line_2, &point);
   if (nIntersections != 1)
   {
      THROW_COGO(WBFL_COGO_E_NOINTERSECTION);
   }

   return point;
}

WBFL::Geometry::Point2d Utilities::IntersectLineSegments(const WBFL::Geometry::LineSegment2d& ls1, Float64 offset1, const WBFL::Geometry::LineSegment2d& ls2, Float64 offset2)
{
   return IntersectLinesByPoints(ls1.GetStartPoint(), ls1.GetEndPoint(), offset1, ls2.GetStartPoint(), ls2.GetEndPoint(), offset2);
}

WBFL::Geometry::Point2d Utilities::IntersectLineSegmentAndCircle(const WBFL::Geometry::LineSegment2d& ls, Float64 offset, const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& nearest)
{
   PRECONDITION(0 < radius);

   WBFL::Geometry::Line2d line(ls.GetStartPoint(),ls.GetEndPoint());
   auto offset_line = WBFL::Geometry::GeometricOperations::CreateParallelLine(line,offset);

   WBFL::Geometry::Circle2d circle(center, radius);

   WBFL::Geometry::Point2d i1, i2;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(offset_line, circle, &i1, &i2);

   WBFL::Geometry::Point2d point;
   if (nIntersections == 1)
   {
      point = i1;
   }
   else if (nIntersections == 2)
   {
      Float64 d1 = nearest.Distance(i1);
      Float64 d2 = nearest.Distance(i2);
      if (d2 < d1)
      {
         point = i2;
      }
      else
      {
         point = i1;
      }
   }
   else
   {
      THROW_COGO(WBFL_COGO_E_NOINTERSECTION);
   }

   return point;
}

WBFL::Geometry::Point2d Utilities::IntersectLineAndCircle(const WBFL::Geometry::Line2d& line, const WBFL::Geometry::Circle2d& circle, const WBFL::Geometry::Point2d& nearest)
{
   WBFL::Geometry::Point2d p1, p2;
   auto nIntersections = WBFL::Geometry::GeometricOperations::Intersect(line, circle, &p1, &p2);
   if (nIntersections == 0)
   {
      THROW_COGO(WBFL_COGO_E_NOINTERSECTION);
   }
   else if (nIntersections == 1)
   {
      return p1;
   }
   else
   {
      CHECK(nIntersections == 2);

      auto d1 = nearest.Distance(p1);
      auto d2 = nearest.Distance(p2);

      if (d2 < d1)
      {
         return p2;
      }
      else
      {
         return p1;
      }
   }
}

WBFL::Geometry::Point2d Utilities::ProjectPointOnLineByPoints(const WBFL::Geometry::Point2d& point, const WBFL::Geometry::Point2d& start, const WBFL::Geometry::Point2d& end, Float64 offset)
{
   WBFL::Geometry::Line2d line(start, end);
   auto offset_line = WBFL::Geometry::GeometricOperations::CreateParallelLine(line, offset);
   return WBFL::Geometry::GeometricOperations::PointOnLineNearest(offset_line, point);
}

WBFL::Geometry::Point2d Utilities::ProjectPointOnLineSegment(const WBFL::Geometry::Point2d& point, const WBFL::Geometry::LineSegment2d& segment, Float64 offset)
{
   WBFL::Geometry::Line2d line(segment.GetStartPoint(), segment.GetEndPoint());
   auto offset_line = WBFL::Geometry::GeometricOperations::CreateParallelLine(line, offset);
   return WBFL::Geometry::GeometricOperations::PointOnLineNearest(offset_line, point);
}

std::vector<WBFL::Geometry::Point2d> Utilities::DivideArc(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& vertex, const WBFL::Geometry::Point2d& to, IndexType nParts)
{
   WBFL::Geometry::Arc arc(from, vertex, to);
   return arc.Divide(nParts);
}

std::vector<WBFL::Geometry::Point2d> Utilities::DivideBetweenPoints(const WBFL::Geometry::Point2d& from, const WBFL::Geometry::Point2d& to, IndexType nParts)
{
   WBFL::Geometry::LineSegment2d segment(from, to);
   return segment.Divide(nParts);
}

std::pair<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d> Utilities::CrossingTangents(const WBFL::Geometry::Point2d& center1, Float64 radius1, const WBFL::Geometry::Point2d& center2, Float64 radius2, TangentSign sign)
{
   PRECONDITION(0 < radius1);
   PRECONDITION(0 < radius2);

   // Compute "delta". The angle of the line connecting the centers of the circle
   Float64 Ax, Ay; std::tie(Ax,Ay) = center1.GetLocation();
   Float64 Bx, By; std::tie(Bx,By) = center2.GetLocation();

   Float64 delta;
   Float64 dx = Bx - Ax;
   Float64 dy = By - Ay;
   delta = atan2(dy, dx);
   delta = NormalizeAngle(delta);

   // Compute "theta". The angle formed by the line connecting the centers of the circles and
   // the line connection the center of one circle and the tangent point on that circle
   Float64 d = sqrt(dx * dx + dy * dy);
   if (IsZero(d)) THROW_COGO(WBFL_COGO_E_COINCIDENTPOINTS);

   Float64 x = radius1 / (d * radius1 / (radius1 + radius2));
   if (IsZero(x - 1.0))
      x = 1.0;

   Float64 theta = acos(x);

   Float64 sG, sH;
   if (sign == TangentSign::CCW)
   {
      sG = 1;
      sH = -1;
   }
   else
   {
      sG = -1;
      sH = 1;
   }

   Float64 Gx, Gy;
   Float64 Hx, Hy;

   Gx = Ax + radius1 * cos(sG * theta + delta);
   Gy = Ay + radius1 * sin(sG * theta + delta);

   Hx = Bx + radius2 * cos(sH * theta + delta);
   Hy = By + radius2 * sin(sH * theta + delta);

   // create the two new points
   return std::make_pair(WBFL::Geometry::Point2d(Gx, Gy), WBFL::Geometry::Point2d(Hx, Hy));
}

std::pair<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d> Utilities::ExternalTangents(const WBFL::Geometry::Point2d& center1, Float64 radius1, const WBFL::Geometry::Point2d& center2, Float64 radius2, TangentSign sign)
{
   PRECONDITION(0 < radius1);
   PRECONDITION(0 < radius2);

   WBFL::Geometry::Point2d A, B; // center points of circle A and B. Circle A is the one with the larger radius
   Float64 Ar, Br; // Radius of circle A and B
   if (radius2 <= radius1)
   {
      A = center1;
      Ar = radius1;

      B = center2;
      Br = radius2;
   }
   else
   {
      A = center2;
      Ar = radius2;

      B = center1;
      Br = radius1;
   }

   Float64 JG;
   JG = Ar - Br;

   // Compute "delta". The angle of the line connecting the centers of the circle
   Float64 Ax, Ay; std::tie(Ax, Ay) = A.GetLocation();
   Float64 Bx, By; std::tie(Bx, By) = B.GetLocation();

   Float64 delta;
   Float64 dx = Bx - Ax;
   Float64 dy = By - Ay;
   delta = atan2(dy, dx);
   delta = NormalizeAngle(delta);

   // Compute "theta". The angle formed by the line connecting the centers of the circles and
   // the line connection the center of one circle and the tangent point on that circle
   Float64 JH = sqrt(dx * dx + dy * dy);
   if (IsZero(JH)) THROW_COGO(WBFL_COGO_E_COINCIDENTPOINTS);

   Float64 JG_JH = JG / JH;
   if (IsZero(JG_JH - 1.0))
      JG_JH = 1.0;

   Float64 theta = acos(JG_JH);

   if (sign == TangentSign::CCW)
      theta *= 1;

   Float64 Gx, Gy;
   Float64 Hx, Hy;

   Gx = Ax + Ar * cos(theta + delta);
   Gy = Ay + Ar * sin(theta + delta);

   Hx = Bx + Br * cos(theta + delta);
   Hy = By + Br * sin(theta + delta);

   // create the two new points
   WBFL::Geometry::Point2d t1, t2;
   if (A == center1)
   {
      t1.Move(Gx, Gy);
      t2.Move(Hx, Hy);
   }
   else
   {
      t2.Move(Gx, Gy);
      t1.Move(Hx, Hy);
   }
   return std::make_pair(t1, t2);
}

WBFL::Geometry::Point2d Utilities::TangentPoint(const WBFL::Geometry::Point2d& center, Float64 radius, const WBFL::Geometry::Point2d& point, TangentSign sign)
{
   PRECONDITION(0 < radius);

   // Compute "delta". The angle of the line connecting the centers of the circle
   Float64 Ax, Ay; std::tie(Ax,Ay) = center.GetLocation();
   Float64 Bx, By; std::tie(Bx,By) = point.GetLocation();

   Float64 delta;
   Float64 dx = Bx - Ax;
   Float64 dy = By - Ay;
   delta = atan2(dy, dx);
   delta = NormalizeAngle(delta);

   // Compute "theta". The angle formed by the line connecting the center of the circle and
   // the tangent point
   Float64 d = sqrt(dx * dx + dy * dy);
   if (IsZero(d)) THROW_COGO(WBFL_COGO_E_COINCIDENTPOINTS);

   if (d <= radius) THROW_COGO(WBFL_COGO_E_POINTINCIRCLE);

   Float64 x = radius / d;
   if (IsZero(x - 1.0))
      x = 1.0;

   Float64 theta = acos(x);

   Float64 sG;
   if (sign == TangentSign::CCW)
   {
      sG = 1;
   }
   else
   {
      sG = -1;
   }

   Float64 Gx, Gy;

   Gx = Ax + radius * cos(sG * theta + delta);
   Gy = Ay + radius * sin(sG * theta + delta);

   return WBFL::Geometry::Point2d(Gx, Gy);
}

Int8 Utilities::CompareStations(std::shared_ptr<const Alignment> alignment, const Station& s1, const Station& s2)
{
   if (alignment)
   {
      return alignment->CompareStations(s1, s2);
   }
   else
   {
      return CompareNormalizedStations(s1, s2);
   }
}

Int8 Utilities::CompareNormalizedStations(const Station& s1, const Station& s2)
{
   if (s1.IsNormalized() && s2.IsNormalized())
      return ::Sign(s2.GetValue() - s1.GetValue()); // return 0, 1, or -1
   else
      THROW_COGO(WBFL_COGO_E_STATION);
}

Float64 Utilities::ConvertToNormalizedStation(std::shared_ptr<const Alignment> alignment, const Station& s)
{
   if (alignment)
      return alignment->ConvertToNormalizedStation(s).GetValue();
   else
   {
      if (s.IsNormalized())
         return s.GetValue();
      else
         THROW_COGO(WBFL_COGO_E_STATION);
   }
}

Station Utilities::ConvertFromNormalizedStation(std::shared_ptr<const Alignment> alignment, Float64 normalizedStation)
{
   if (alignment)
      return alignment->ConvertFromNormalizedStation(normalizedStation);
   else
      return normalizedStation;
}

Station Utilities::ConvertFromNormalizedStation(std::shared_ptr<const Alignment> alignment, const Station& station)
{
   if (station.IsNormalized())
      return ConvertFromNormalizedStation(alignment, station.GetValue());
   else
      THROW_COGO(WBFL_COGO_E_STATION);
}

Float64 Utilities::DistanceBetweenStations(std::shared_ptr<const Alignment> alignment, const Station& s1, const Station& s2)
{
   if (alignment)
      return alignment->DistanceBetweenStations(s1, s2);
   else
   {
      if(s1.IsNormalized() && s2.IsNormalized())
         return s2.GetValue() - s1.GetValue();
      else
         THROW_COGO(WBFL_COGO_E_STATION);
   }
}

Station& Utilities::IncrementStation(std::shared_ptr<const Alignment> alignment, Station& station, Float64 distance)
{
   if (alignment)
      return alignment->IncrementStation(station, distance);
   else
   {
      if (station.IsNormalized())
      {
         station.SetValue(station.GetValue() + distance);
         return station;
      }
      else
      {
         THROW_COGO(WBFL_COGO_E_STATION);
      }
   }
}

Station Utilities::IncrementStationBy(std::shared_ptr<const Alignment> alignment, const Station& station, Float64 distance)
{
   if (alignment)
      return alignment->IncrementStationBy(station, distance);
   else
   {
      if (station.IsNormalized())
      {
         Station s(station.GetValue() + distance);
         return s;
      }
      else
      {
         THROW_COGO(WBFL_COGO_E_STATION);
      }
   }
}

#if defined _UNITTEST
bool Utilities::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Utilities");
   TRY_TESTME(Measure(rlog));
   TRY_TESTME(Locate(rlog));
   TRY_TESTME(Intersect(rlog));
   TRY_TESTME(Project(rlog));
   TRY_TESTME(Divide(rlog));
   TRY_TESTME(Tangent(rlog));
   TESTME_EPILOG("Utilities");
}

bool Utilities::Measure(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Utilities::Measure");
   
   WBFL::Geometry::Point2d p1(10, 10);
   WBFL::Geometry::Point2d p2(20, 20);
   WBFL::Geometry::Point2d p3(30, 10);

   TRY_TESTME(MeasureAngle(p1, p2, p3) == Angle(PI_OVER_2));
   TRY_TESTME(MeasureAngle(p3, p2, p1) == Angle(3 * PI_OVER_2));

   TRY_TESTME(IsEqual(MeasureDistance(p1, p2), sqrt(200)));
   TRY_TESTME(IsEqual(MeasureDistance(p2, p3), sqrt(200)));
   TRY_TESTME(IsEqual(MeasureDistance(p1, p3), 20.0));

   TRY_TESTME(MeasureDirection(p1, p2) == Direction(M_PI / 4));
   TRY_TESTME(MeasureDirection(p2, p3) == Direction(7 * M_PI / 4));
   TRY_TESTME(MeasureDirection(p1, p3) == Direction(0.0));
   TRY_TESTME(MeasureDirection(p3, p1) == Direction(M_PI));

   std::vector<WBFL::Geometry::Point2d> points{ p1,p2,p3 };
   TRY_TESTME(IsEqual(MeasureArea(points), 100.0));

   TESTME_EPILOG("Utilities::Measure");
}

bool Utilities::Locate(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Utilities::Locate");

   WBFL::Geometry::Point2d p1(0, 0);
   WBFL::Geometry::Point2d p2(10, 0);

   TRY_TESTME(LocateByDistanceAndDirection(p2, 10.0, PI_OVER_2,  0.0) == WBFL::Geometry::Point2d(10., 10.));
   TRY_TESTME(LocateByDistanceAndDirection(p2, 10.0, PI_OVER_2,  5.0) == WBFL::Geometry::Point2d(15., 10.));
   TRY_TESTME(LocateByDistanceAndDirection(p2, 10.0, PI_OVER_2, -5.0) == WBFL::Geometry::Point2d( 5., 10.));
   
   Direction direction(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::West);
   TRY_TESTME(LocateByDistanceAndDirection(p2, 10.0, direction, 0.0) == WBFL::Geometry::Point2d(2.92893218813, 7.07106781187));
   TRY_TESTME(LocateByDistanceAndDirection(p2, 10.0, direction, 5.0) == WBFL::Geometry::Point2d(6.4644660940, 10.6066017178));
   TRY_TESTME(LocateByDistanceAndDirection(p2, 10.0, direction,-5.0) == WBFL::Geometry::Point2d(-0.60660171781, 3.53553390593));
   TRY_TESTME(LocateByDistanceAndDirection(p2,-10.0, direction, 0.0) == WBFL::Geometry::Point2d(17.07106781187, -7.07106781187));

   p1.Move(10, 10);
   p2.Move(0, 0);
   Angle angle(225, 0, 0);
   TRY_TESTME(LocateByDistanceAndAngle(p1, p2, 10.0, M_PI / 4, 0.0) == WBFL::Geometry::Point2d(0.0, 10.0));
   TRY_TESTME(LocateByDistanceAndAngle(p1, p2, 10.0, angle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, -13.53553390594));
   TRY_TESTME(LocateByDistanceAndAngle(p1, p2, -10.0, angle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

   Angle defAngle(45, 0, 0);
   TRY_TESTME(LocateByDistanceAndDeflectionAngle(p1, p2, 10.0, M_PI, 0.0) == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));
   TRY_TESTME(LocateByDistanceAndDeflectionAngle(p1, p2, 10.0, M_PI/4, 0.0) == WBFL::Geometry::Point2d(0.0, -10.0));
   TRY_TESTME(LocateByDistanceAndDeflectionAngle(p1, p2, 10.0, defAngle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, -13.53553390594));
   TRY_TESTME(LocateByDistanceAndDeflectionAngle(p1, p2,-10.0, defAngle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

   p1.Move(10, 10);
   p2.Move(20, 20);
   TRY_TESTME(LocatePointOnLine(p1, p2, 20.0, 0.0) == WBFL::Geometry::Point2d(24.1421356237, 24.1421356237));
   TRY_TESTME(LocatePointOnLine(p1, p2,-20.0, 0.0) == WBFL::Geometry::Point2d(-4.1421356237, -4.1421356237));
   TRY_TESTME(LocatePointOnLine(p1, p2, 10.0, 5.0) == WBFL::Geometry::Point2d(20.6066017178, 13.5355339059));
   TRY_TESTME(LocatePointOnLine(p1, p2, 10.0,-5.0) == WBFL::Geometry::Point2d(13.5355339059, 20.6066017178));

   // ParallelLineSegment and ParallelLineByPoints
   p1.Move(0, 0);
   p2.Move(20, 20);
   WBFL::Geometry::LineSegment2d segment(p1, p2);

   auto newSegment = LocateParallelLineSegment(segment, 5.0);
   TRY_TESTME(newSegment.GetStartPoint() == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
   TRY_TESTME(newSegment.GetEndPoint() == WBFL::Geometry::Point2d(23.5355339059, 16.4644660941));

   newSegment = LocateParallelLineSegment(segment, -5.0);
   TRY_TESTME(newSegment.GetStartPoint() == WBFL::Geometry::Point2d(-3.53553390594, 3.53553390594));
   TRY_TESTME(newSegment.GetEndPoint() == WBFL::Geometry::Point2d(16.4644660941, 23.5355339059));

   std::tie(p1,p2) = LocateParallelLineByPoints(p1, p2, 5.0);
   TRY_TESTME(p1 == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
   TRY_TESTME(p2 == WBFL::Geometry::Point2d(23.5355339059, 16.4644660940));

   TESTME_EPILOG("Utilities::Locate");
}

bool Utilities::Intersect(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Utilities::Intersect");

   WBFL::Geometry::Point2d p1(0, 0);
   WBFL::Geometry::Point2d p2(10, 0);

   TRY_TESTME(IntersectBearings(p1, M_PI / 4, 0.0, p2, 3 * M_PI / 4, 0.0) == WBFL::Geometry::Point2d(5.0, 5.0));
   TRY_TESTME(IntersectBearings(p1, M_PI / 4, 5.0, p2, 3 * M_PI / 4, 5.0) == WBFL::Geometry::Point2d(12.0710678119, 5.0));
   try { IntersectBearings(p1, M_PI / 4, 0.0, p2, M_PI / 4, 0.0); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }


   p1.Move(0, 0);
   WBFL::Geometry::Point2d center(10, 10);
   WBFL::Geometry::Point2d nearest(15, 15);
   TRY_TESTME(IntersectBearingAndCircle(p1, M_PI / 4, 0.0, center, 5.0, nearest) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));
   TRY_TESTME(IntersectBearingAndCircle(p1, M_PI / 4, 0.0, center, 5.0, p1) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));
   TRY_TESTME(IntersectBearingAndCircle(p1, PI_OVER_2, 5.0, center, 5.0, p1) == WBFL::Geometry::Point2d(5.0, 10.0));
   try { IntersectBearingAndCircle(p1, PI_OVER_2, 0.0, center, 5.0, p1); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }


   p1.Move(10, 10);
   p2.Move(20, 20);
   nearest.Move(20, 0);
   TRY_TESTME(IntersectCircles(p1, 10.0, p2, 10.0, nearest) == WBFL::Geometry::Point2d(20, 10));
   TRY_TESTME(IntersectCircles(p1, 20.0, WBFL::Geometry::Point2d(20, 10), 10.0, nearest) == WBFL::Geometry::Point2d(30, 10));
   TRY_TESTME(IntersectCircles(p1, 20.0, WBFL::Geometry::Point2d(20, 10), 20.0, WBFL::Geometry::Point2d(0, 20)) == WBFL::Geometry::Point2d(15.0, 29.3649167));
   try { IntersectCircles(p1, 2.0, p2, 2.0, nearest); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

   p1.Move(0, 0);
   p2.Move(15, 15);
   center.Move(10, 10);
   TRY_TESTME(IntersectLineByPointsAndCircle(p1, p2, 0.0, center, 5.0, p2) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));
   TRY_TESTME(IntersectLineByPointsAndCircle(p1, p2, 0.0, center, 5.0, p1) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));
   TRY_TESTME(IntersectLineByPointsAndCircle(p1, WBFL::Geometry::Point2d(0, 20), 5.0, center, 5.0, p1) == WBFL::Geometry::Point2d(5, 10));
   try { IntersectLineByPointsAndCircle(p1, WBFL::Geometry::Point2d(0, 20), 0.0, center, 5.0, p1); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

   p1.Move(0, 0);
   p2.Move(10, 0);
   WBFL::Geometry::Point2d p3(10, 10);
   WBFL::Geometry::Point2d p4(0, 10);

   TRY_TESTME(IntersectLinesByPoints(p1, p3, 0.0, p2, p4, 0.0) == WBFL::Geometry::Point2d(5, 5));
   TRY_TESTME(IntersectLinesByPoints(p1, p3, 5.0, p2, p4, 5.0) == WBFL::Geometry::Point2d(12.0710678119, 5));
   try { IntersectLinesByPoints(p1, p2, 0.0, p3, p4, 0.0); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

   TRY_TESTME(IntersectLineSegments(WBFL::Geometry::LineSegment2d(p1, p3), 0.0, WBFL::Geometry::LineSegment2d(p2, p4), 0.0) == WBFL::Geometry::Point2d(5, 5));
   TRY_TESTME(IntersectLineSegments(WBFL::Geometry::LineSegment2d(p1, p3), 5.0, WBFL::Geometry::LineSegment2d(p2, p4), 5.0) == WBFL::Geometry::Point2d(12.0710678119, 5));
   try { IntersectLineSegments(WBFL::Geometry::LineSegment2d(p1, p2), 0.0, WBFL::Geometry::LineSegment2d(p3, p4), 0.0); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

   p1.Move(0, 0);
   p2.Move(10, 10);
   p3.Move(15, 15);
   p4.Move(0, 20);
   TRY_TESTME(IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p3), 0.0, p2, 5.0, p3) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));
   TRY_TESTME(IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p3), 0.0, p2, 5.0, p1) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));
   TRY_TESTME(IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p4), 5.0, p2, 5.0, p1) == WBFL::Geometry::Point2d(5, 10));
   try { IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p4), 0.0, p2, 5.0, p1); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }


   TESTME_EPILOG("Utilities::Intersect");
}

bool Utilities::Project(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Utilities::Project");

   WBFL::Geometry::Point2d p1(0, 0);
   WBFL::Geometry::Point2d p2(5, 5);
   WBFL::Geometry::Point2d p3(6,12);
   WBFL::Geometry::Point2d p4(12,6);

   TRY_TESTME(ProjectPointOnLineByPoints(p3, p1, p2, 0.0) == WBFL::Geometry::Point2d(9, 9));
   TRY_TESTME(ProjectPointOnLineByPoints(p4, p1, p2, 0.0) == WBFL::Geometry::Point2d(9, 9));
   TRY_TESTME(ProjectPointOnLineByPoints(p3, p1, p2, 4.24264068712) == WBFL::Geometry::Point2d(12, 6));
   TRY_TESTME(ProjectPointOnLineByPoints(p3, p1, p2, -4.24264068712) == WBFL::Geometry::Point2d(6, 12));

   TRY_TESTME(ProjectPointOnLineSegment(p3, WBFL::Geometry::LineSegment2d(p1, p2), 0.0) == WBFL::Geometry::Point2d(9, 9));
   TRY_TESTME(ProjectPointOnLineSegment(p3, WBFL::Geometry::LineSegment2d(p1, p2), 4.24264068712) == WBFL::Geometry::Point2d(12, 6));

   TESTME_EPILOG("Utilities::Project");
}

bool Utilities::Divide(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Utilities::Divide");

   WBFL::Geometry::Point2d p1(0, 0);
   WBFL::Geometry::Point2d p2(10, 0);
   WBFL::Geometry::Point2d p3(-10, 0);

   auto points = DivideArc(p2, p1, p3, 4);
   TRY_TESTME(points.size() == 5); // divided the arc into 4 pieces, with 5 points
   TRY_TESTME(points[0] == p2);
   TRY_TESTME(points[1] == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));
   TRY_TESTME(points[2] == WBFL::Geometry::Point2d(0,10));
   TRY_TESTME(points[3] == WBFL::Geometry::Point2d(-7.07106781187, 7.07106781187));
   TRY_TESTME(points[4] == p3);

   p1.Move(10, 10);
   p2.Move(110, 110);
   points = DivideBetweenPoints(p1, p2, 10);
   TRY_TESTME(points.size() == 11);
   int i = 1;
   for (const auto& point : points)
   {
      TRY_TESTME(point == WBFL::Geometry::Point2d(p1.X() * i, p1.Y()*i));
      i++;
   }

   TESTME_EPILOG("Utilities::Divide");
}

bool Utilities::Tangent(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Utilities::Tangent");

   WBFL::Geometry::Point2d p1(10, 10);
   WBFL::Geometry::Point2d p2(40, 10);
   WBFL::Geometry::Point2d t1, t2;

   // ExternalTangents

   // define the big circle first
   std::tie(t1,t2) = ExternalTangents(p1, 20, p2, 5, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(20.0, 27.3205));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(42.5, 14.33013));

   std::tie(t1, t2) = ExternalTangents(p1, 20, p2, 5, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(20.0, 27.3205));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(42.5, 14.33013));

   // define the small circle first
   std::tie(t1, t2) = ExternalTangents(p2, 5, p1, 20, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(42.5, 14.33013));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(20.0, 27.3205));

   std::tie(t1, t2) = ExternalTangents(p2, 5, p1, 20, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(42.5, 14.33013));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(20.0, 27.3205));

   // rotate both circles 180 deg around (0,0) (make x = -x)
   p1.X() *= -1;
   p2.X() *= -1;

   // big circle first
   std::tie(t1, t2) = ExternalTangents(p1, 20, p2, 5, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-20.0, -7.3205));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-42.5, 5.66987));

   std::tie(t1, t2) = ExternalTangents(p1, 20, p2, 5, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-20.0, -7.3205));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-42.5, 5.66987));

   // small circle first
   std::tie(t1, t2) = ExternalTangents(p2, 5, p1, 20, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-42.5, 5.66987));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-20.0, -7.3205));

   std::tie(t1, t2) = ExternalTangents(p2, 5, p1, 20, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-42.5, 5.66987));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-20.0, -7.3205));

   // make Y = x and X = -Y
   p1.Move(-10, 10);
   p2.Move(-10, 40);

   // big circle first
   std::tie(t1, t2) = ExternalTangents(p1, 20, p2, 5, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-27.3205, 20));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-14.33013, 42.5));

   std::tie(t1, t2) = ExternalTangents(p1, 20, p2, 5, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-27.3205, 20));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-14.33013, 42.5));

   // small circle first
   std::tie(t1, t2) = ExternalTangents(p2, 5, p1, 20, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-14.33013, 42.5));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-27.3205 , 20.0));

   std::tie(t1, t2) = ExternalTangents(p2, 5, p1, 20, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-14.33013, 42.5));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-27.3205, 20.0));

   // Quadrants   ^
   //             |
   //       2     |     1
   //             |
   //   ----------+----------->
   //             |
   //       3     |     4
   //             |

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 1
   p1.Move(0, 0);
   p2.Move(10, 10);
   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-3.53553, 3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(6.46447, 13.53553));

   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-3.53553, 3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(6.46447, 13.53553));

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 2
   p1.Move(0, 0);
   p2.Move(-10, 10);
   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-3.53553, -3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-13.53553, 6.46447));

   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(-3.53553, -3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-13.53553, 6.46447));
   
   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 3
   p1.Move(0, 0);
   p2.Move(-10, -10);
   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d( 3.53553, -3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-6.46447, -13.53553));

   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(3.53553, -3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(-6.46447, -13.53553));

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 4
   p1.Move(0, 0);
   p2.Move( 10, -10);
   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(3.53553, 3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(13.53553, -6.46447));

   std::tie(t1, t2) = ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(3.53553, 3.53553));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(13.53553, -6.46447));

   // CrossingTangents
   p1.Move(10, 10);
   p2.Move(40, 10);
   std::tie(t1, t2) = CrossingTangents(p1, 20.0, p2, 5.0, TangentSign::CW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(26.66666, -1.05541));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(44.16667, 12.76385));

   std::tie(t1, t2) = CrossingTangents(p1, 20.0, p2, 5.0, TangentSign::CCW);
   TRY_TESTME(t1 == WBFL::Geometry::Point2d(26.66666, 21.055415));
   TRY_TESTME(t2 == WBFL::Geometry::Point2d(44.16667, 7.23615));

   // TangentPoint
   Float64 radius = 20.;
   p1.Move(10, 10);
   p2.Move(10 + radius * sqrt(2.), 10);

   TRY_TESTME(TangentPoint(p1, radius, p2, TangentSign::CW) == WBFL::Geometry::Point2d(24.14214, -4.14214));
   TRY_TESTME(TangentPoint(p1, radius, p2, TangentSign::CCW) == WBFL::Geometry::Point2d(24.14214, 24.14214));
   TRY_TESTME(TangentPoint(p1, radius, WBFL::Geometry::Point2d(10 + radius, 10 + radius), TangentSign::CW) == WBFL::Geometry::Point2d(30, 10));
   TRY_TESTME(TangentPoint(p1, radius, WBFL::Geometry::Point2d(10 + radius, 10 + radius), TangentSign::CCW) == WBFL::Geometry::Point2d(10, 30));

   TESTME_EPILOG("Utilities::Tangent");
}

#endif // _UNITTEST