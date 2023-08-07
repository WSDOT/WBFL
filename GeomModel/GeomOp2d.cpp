///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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
#include <GeomModel/GeomOp2d.h>

#include <GeomModel/Primitives.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/Vector2d.h>
#include <GeomModel/Vector3d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/LineSegment2d.h>
#include <GeomModel/Circle2d.h>
#include <GeomModel/Circle.h>
#include <GeomModel/Arc.h>

#include <MathEx.h>
#include <limits>

using namespace WBFL::Geometry;

Int16 GeometricOperations::Intersect(const LineSegment2d& ls1, const LineSegment2d& ls2, Point2d* point)
{
   // Check if either line segment has zero length
   bool bSeg1ZeroLength = IsZero( ls1.Length() );
   bool bSeg2ZeroLength = IsZero( ls2.Length() );
   if ( bSeg1ZeroLength && !bSeg2ZeroLength )
   {
      // Segment 1 is zero length, but segment 2 is not.
      // See if start point of segment 1 is on segment 2.
      if ( ls2.ContainsPoint( ls1.GetStartPoint() ) )
      {
         *point = ls1.GetStartPoint();
         return 1;
      }
      else
      {
         return 0;
      }
   }

   if ( !bSeg1ZeroLength && bSeg2ZeroLength )
   {
      // Segment 2 is zero length, but segment 1 is not.
      // See if start point of segment 2 is on segment 1.
      if ( ls1.ContainsPoint( ls2.GetStartPoint() ) )
      {
         *point = ls2.GetStartPoint();
         return 1;
      }
      else
      {
         return 0;
      }
   }

   if ( bSeg1ZeroLength && bSeg2ZeroLength )
   {
      // Both segment 1 and segment 2 are zero length.
      // See if their start points are the same
      if ( ls1.GetStartPoint() == ls2.GetStartPoint() )
      {
         *point = ls1.GetStartPoint();
         return 1;
      }
      else
      {
         return 0;
      }
   }

   // Neither line segments are zero length
   // Convert to lines and make sure intersection point is in segments
   Line2d l1(ls1), l2(ls2);
   Int16 it = Intersect(l1, l2,point);
   if (it == 1)
   {
      if(ls1.ContainsPoint(*point) && ls2.ContainsPoint(*point))
         return 1;
      else
         return 0;
   }
   else if (it==-1)
   {
      // lines are collinear - do they share points?
      Point2d ls1s = ls1.GetStartPoint();
      Point2d ls1e = ls1.GetEndPoint();
      if (ls2.ContainsPoint(ls1s))
      {
         *point = ls1s;
         return -1;
      }
      else if (ls2.ContainsPoint(ls1e))
      {
         *point = ls1e;
         return -1;
      }
      else
      {
         return 0;
      }
   }
   else
   {
      return 0;
   }
}

Int16 GeometricOperations::Intersect(const Line2d& l, const Line2d& m, Point2d* point)
{
   // Use method as outlined in Graphics Gems, page 11. Get explicit form of
   // l1 and implicit form of l2
   auto [lc,ln] = l.GetImplicit();
   auto [mu,mv] = m.GetExplicit();

   Float64 d = ln.Dot(mv);
   if (d!=0)
   {
      Vector2d muv(Size2d(mu.X(),mu.Y()));      // must convert point to vector for Dot()
      Float64 f = ln.Dot(muv);
      f = (f - lc)/d;

      mv.SetMagnitude(fabs(f));
      if (f < 0) mv.Reflect();

      auto [x1,y1] = muv.GetDimensions();
      auto [x2,y2] = mv.GetDimensions();
      point->Move(x1 - x2, y1 - y2);

      return 1;
   }
   else
   {
      // lines are parallel, either collinear or do not intersect.
      return l.IsColinear(m) ? -1 : 0;
   }
}


Int16 GeometricOperations::Intersect(const LineSegment2d& ls, const Line2d& l, Point2d* point)
{
   if ( IsZero( ls.Length() ) )
   {
      if ( l.ContainsPoint( ls.GetStartPoint() ) )
      {
         *point = ls.GetStartPoint();
         return 1;
      }
      else
      {
         return 0;
      }
   }

   Line2d l1(ls);
   Int16 it = Intersect(l1, l, point);
   if (it == 1)
   {
      if(ls.ContainsPoint(*point))
         return 1;
      else
         return 0;
   }
   else if (it==-1)
   {
      *point = ls.GetStartPoint();
      return -1;
   }
   else
      return 0;

}

Int16 GeometricOperations::Intersect(const Line2d& l,const LineSegment2d& ls,Point2d* point)
{
   return Intersect(ls, l, point);
}

Int16 GeometricOperations::Intersect(const Line2d& l,const Circle2d& c,Point2d* p1,Point2d* p2)
{
   // Quick check to see if the line and the circle have a chance of intersecting
   const auto& center = c.GetCenter();
   Point2d poln = l.PointOnLineNearest( center );
   Float64 radius = c.GetRadius();
   Float64 distance = poln.Distance(center);
   if ( radius < distance && !IsEqual(radius,distance) )
      return 0; // Shortest dist to line is > radius.  They can't intersect

   auto [p,v] = l.GetExplicit();
   Size2d size = v.GetSize();

   if ( IsZero(size.Dx()) )
   {
      // Special case of a vertical line.
      Float64 dy = sqrt(radius*radius - pow(poln.X()-center.X(),2));
      p1->Move(poln.X(), center.Y() + dy);

      // Does the vertical line just touch the circle
      // Is there only one intersection?
      if ( IsEqual(radius,poln.Distance(center)) )
         return 1; // yes

      // No... There is two intersections

      p2->Move(poln.X(), center.Y() - dy);

      return (*p1 == *p2) ? 1 : 2;
   }
   else
   {
      // General line.

      // determine the y-intercept of the line
      //
      // get any point on the line and solve y=mx+b
      // point on line nearest origin is just as good as the next point,
      // and it is easy to get.
      Point2d origin;
      poln = l.PointOnLineNearest( origin );
      Float64 x,y;
      x = poln.X();
      y = poln.Y();
      Float64 slope = l.GetSlope();
      Float64 b = y - slope*x;

      Float64 A = slope*slope + 1;
      Float64 B = 2*( slope*(b-center.Y()) - center.X());
      Float64 C = pow(center.X(),2) + pow((b-center.Y()),2) - pow(radius,2);

      Float64 D = B*B - 4*A*C;
      D = (IsZero(D) ? 0 : D);
      CHECK( 0 <= D );
      Float64 x1 = (-B - sqrt(D))/(2*A);
      Float64 x2 = (-B + sqrt(D))/(2*A);

      Float64 y1 = slope*x1 + b;
      Float64 y2 = slope*x2 + b;

      p1->Move(x1,y1);
      p2->Move(x2,y2);

      return (*p1 == *p2) ? 1 : 2;
   }

   return 0;
}

Int16 GeometricOperations::Intersect(const Line2d& l, const Circle& c, Point2d* p1, Point2d* p2)
{
   return Intersect(l, Circle2d(*c.GetHookPoint(), c.GetRadius()), p1, p2);
}

Int16 GeometricOperations::Intersect(const Line2d& l,const Arc& arc,Point2d* p1,Point2d* p2)
{
   Point2d ip1, ip2;
   Int16 nIntersect = Intersect(l,Circle2d(arc),&ip1,&ip2);
   Int16 ni = 0;
   if ( nIntersect != 0 )
   {
      if ( arc.IsPointOnArc(ip1) )
      {
         *p1 = ip1;
         ni++;
      }

      if ( nIntersect == 2 )
      {
         if ( arc.IsPointOnArc(ip2) )
         {
            if ( ni == 0 ) // ip1 is not on arc, so the second point found on the circle is the first intersection on the arc
               *p1 = ip2;
            else
               *p2 = ip2;

            ni++;
         }
      }
   }

   return ni;
}

Int16 GeometricOperations::Intersect(const Circle2d& c1, const Circle2d& c2, Point2d* p1, Point2d* p2)
{
   // Initialize
   Int16 nIntersect = 0;

   // Get center and radius of both circles
   const auto& center1 = c1.GetCenter();
   auto r1 = c1.GetRadius();
   const auto& center2 = c2.GetCenter();
   auto r2 = c2.GetRadius();

   // If the circles have the same center and the same radius, all points along the
   // circle intersect. Return the special value of 3. If the radii are different, there
   // are no intersection points
   if (center1 == center2)
   {
      // Center is the same
      nIntersect = IsEqual(r1, r2) ? 3 : 0;
      return nIntersect;
   }


   // OK... do the regular intersection calculations

   // Compute some constants used in the solution of the quadratic equation
   auto [cx1,cy1] = center1.GetLocation();
   auto [cx2,cy2] = center2.GetLocation();

   Float64 K = (r1 * r1 - r2 * r2) - cx1 * cx1 + cx2 * cx2 - (cy2 - cy1) * (cy2 - cy1);

   Float64 A = -4 * ((cx2 - cx1) * (cx2 - cx1) + (cy2 - cy1) * (cy2 - cy1));
   Float64 B = 8 * (cy2 - cy1) * (cy2 - cy1) * cx2 + 4 * K * (cx2 - cx1);
   Float64 C = 4 * (cy2 - cy1) * (cy2 - cy1) * (r2 * r2 - cx2 * cx2) - K * K;
   Float64 D = B * B - 4 * A * C; // Part of the Quadratic equation

   if (D < 0)
   {
      nIntersect = 0;
      return nIntersect;
   }

   //
   // Compute intersection points
   //
   Float64 x1, y1, y1a, y1b;
   Float64 x2, y2, y2a, y2b;
   Float64 d1, d2;

   x1 = (-B + sqrt(D)) / (2 * A);
   x2 = (-B - sqrt(D)) / (2 * A);

   y1a = cy1 + sqrt(r1 * r1 - (x1 - cx1) * (x1 - cx1));
   y1b = cy1 - sqrt(r1 * r1 - (x1 - cx1) * (x1 - cx1));

   if (IsEqual(x1, x2))
   {
      y1 = y1a;
      y2 = y1b;
   }
   else
   {
      // compute distance between center of circle2 and x1,y1a and
      // center of circle2 and x1,y1b. The one that equals the radius of circle2
      // is the correct Y
      d1 = (y1a - cy2) * (y1a - cy2) + (x1 - cx2) * (x1 - cx2);
      d2 = (y1b - cy2) * (y1b - cy2) + (x1 - cx2) * (x1 - cx2);
      y1 = IsEqual(r2 * r2, d1) ? y1a : y1b;

      y2a = cy2 - sqrt(r2 * r2 - (x2 - cx2) * (x2 - cx2));
      y2b = cy2 + sqrt(r2 * r2 - (x2 - cx2) * (x2 - cx2));

      // compute distance between center of circle1 and x2,y2a and
      // center of circle1 and x2,y2b. The one that equals the radius of circle1
      // is the correct Y
      d1 = (y2a - cy1) * (y2a - cy1) + (x2 - cx1) * (x2 - cx1);
      d2 = (y2b - cy1) * (y2b - cy1) + (x2 - cx1) * (x2 - cx1);
      y2 = IsEqual(r1 * r1, d1) ? y2a : y2b;
   }

   p1->Move(x1, y1);
   p2->Move(x2, y2);

   // Determine # of intersections
   nIntersect = (*p1 == *p2 ? 1 : 2);
   return nIntersect;
}

Int16 GeometricOperations::Intersect(const Circle& c1, const Circle& c2, Point2d* p1, Point2d* p2)
{
   return Intersect(Circle2d(*c1.GetHookPoint(), c1.GetRadius()), Circle2d(*c2.GetHookPoint(), c2.GetRadius()),p1,p2);
}

Point2d GeometricOperations::PointOnLine(const Point2d& p1, const Point2d& p2, Float64 distFromStart)
{
   if (p1 == p2) THROW_GEOMETRY(WBFL_GEOMETRY_E_COINCIDENTPOINTS);

   if (IsZero(distFromStart))
      return p1;

   Size2d delta = p2 - p1;
   Float64 direction = atan2(delta.Dy(), delta.Dx());
   if (IsZero(direction))
      direction = 0;
   else if (direction < 0)
      direction += TWO_PI;

   return Point2d(p1.X() + distFromStart * cos(direction), p1.Y() + distFromStart * sin(direction));
}

bool GeometricOperations::IsParallel(const Line2d& l1, const Line2d& l2)
{
   auto [c1,n1] = l1.GetImplicit();
   auto [c2,n2] = l2.GetImplicit();
   // test normal vectors. if they are in the same, or opposite directions, the lines are parallel
   return (n1 == n2 || n1 == -n2); 
}

bool GeometricOperations::IsParallel(const LineSegment2d& l1, const LineSegment2d& l2)
{
   return IsParallel(Line2d(l1), Line2d(l2));
}

bool GeometricOperations::IsParallel(const LineSegment2d& l1, const Line2d& l2)
{
   return IsParallel(Line2d(l1), l2);
}

bool GeometricOperations::IsParallel(const Line2d& l1, const LineSegment2d& l2)
{
   return IsParallel(l2, l1);
}

bool GeometricOperations::SameDirection(const Line2d& l1, const Line2d& l2)
{
   auto [c1,n1] = l1.GetImplicit();
   auto [c2,n2] = l2.GetImplicit();
   return (n1 == n2);
}

bool GeometricOperations::SameDirection(const LineSegment2d& l1, const LineSegment2d& l2)
{
   return SameDirection(Line2d(l1), Line2d(l2));
}

bool GeometricOperations::SameDirection(const LineSegment2d& l1, const Line2d& l2)
{
   return SameDirection(Line2d(l1), l2);
}

bool GeometricOperations::SameDirection(const Line2d& l1, const LineSegment2d& l2)
{
   return SameDirection(l2, l1);
}

void GeometricOperations::GenerateCircle(IndexType numPoints,
                                const Point2d& center,
                                Float64 radius,
                                Float64 initAngle,
                                std::vector<Point2d>* vPoints)
{
   if (numPoints == 0) return;
   Float64 delta_angle = TWO_PI / numPoints;
   GenerateCircle( center, radius, initAngle, delta_angle, vPoints );
}

void GeometricOperations::GenerateCircle(const Point2d& center,
                                Float64 radius,
                                Float64 initAngle,
                                Float64 deltaAngle,
                                std::vector<Point2d>* vPoints)
{
   if (radius < 0) THROW_GEOMETRY(WBFL_GEOMETRY_E_RADIUS);

   // Design note: lots of points can be used to general a circle - to avoid copying a large container on return
   // a container is provided by the caller that is filled up. We intentionally do not clear the container because
   // the caller might want to append points to the end of the container.
   Float64 cum_angle = 0;
   while ( ::IsGT(-TWO_PI,cum_angle) && ::IsGT(cum_angle, TWO_PI))
   {
      vPoints->emplace_back(center.X() + radius * cos(initAngle + cum_angle), center.Y() + radius * sin(initAngle + cum_angle));
      cum_angle += deltaAngle;
   }
}

Float64 GeometricOperations::Angle(const Point2d& start, const Point2d& center, const Point2d& end)
{
   auto [sx,sy] = start.GetLocation(); // Start Point
   auto [cx,cy] = center.GetLocation(); // Center Point
   auto [ex,ey] = end.GetLocation(); // End Points
   
   auto dx1 = sx - cx; // Delta x and y center to start point
   auto dy1 = sy - cy; // Delta x and y center to end point

   auto dx2 = ex - cx;
   auto dy2 = ey - cy;

   if (IsZero(dx1) && IsZero(dy1) || IsZero(dx2) && IsZero(dy2))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_COINCIDENTPOINTS);

   Float64 angle1 = atan2(dy1, dx1);
   if (IsZero(angle1))
      angle1 = 0.00;
   else if (angle1 < 0)
      angle1 += TWO_PI;

   Float64 angle2 = atan2(dy2, dx2);
   if (IsZero(angle2))
      angle2 = 0.00;
   else if (angle2 < 0)
      angle2 += TWO_PI;

   Float64 angle = angle2 - angle1;
   angle = IsZero(angle) ? 0.00 : angle;
   if (angle < 0.0)
      angle += TWO_PI;

   return angle;
}

Float64 GeometricOperations::NormalizeAngle(Float64 angle)
{
   while ( angle < 0 )
      angle += TWO_PI;

   while ( TWO_PI <= angle )
      angle -= TWO_PI;

   CHECK( InRange(0.0,angle,TWO_PI) );

   return angle;
}

Float64 GeometricOperations::ShortestOffsetToPoint(const Line2d& line, const Point2d& point)
{
   // this implementation may not be optimal, but it's the best
   // I can come up with for now.
   Point2d poln = PointOnLineNearest(line, point);
   Float64 distance = point.Distance(poln);

   Vector2d v(poln - point);

   auto [c,n] = line.GetImplicit();

   Float64 dot = n.Dot(v);
   if (dot < 0) distance *= -1.0;

   return distance;
}

Point2d GeometricOperations::ReflectPointAcrossLine(const Point2d& point, const Line2d& line)
{
   auto [c,n] = line.GetImplicit();

   Float64 dist = line.DistanceToPoint(point);

   Point2d reflected_point(point.X() - 2 * dist * n.X(), point.Y() - 2 * dist * n.Y());

   return reflected_point;
}

Point3d GeometricOperations::GlobalToLocal(const Point3d& origin,
                                    const Vector3d& unitVector,
                                    Float64 angle,
                                    const Point3d& point)
{
   Vector3d v1, v2, v3, v4;
   Vector3d vKnownSubvOrigin;
   Vector3d vKnown(point);
   Vector3d vOrigin(origin);
   Float64 nDot;

   if (!IsEqual(unitVector.GetMagnitude(), 1.0))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG); // must be a unit vector

   vKnownSubvOrigin = vKnown - vOrigin;
   nDot = vKnownSubvOrigin.Dot(unitVector);
   v4 = unitVector.ScaleBy(nDot);

   v1 = v4.ScaleBy(1 - cos(angle));
   v2 = vKnownSubvOrigin.ScaleBy(cos(angle));

   Vector3d cross = vKnownSubvOrigin.Cross(unitVector);
   v3 = cross.ScaleBy(sin(angle));

   v4       = v1 + v2;
   Vector3d result = v4 + v3;
   return Point3d(result.X(),result.Y(),result.Z());
}

Point3d GeometricOperations::LocalToGlobal(const Point3d& origin,
                                    const Vector3d& unitVector,
                                    Float64 angle,
                                    const Point3d& point)
{
   Vector3d v1, v2, v3, v4, v5;
   Float64 KnownDotUnit;
   Vector3d KnownCrossUnit;
   Vector3d vKnown(point);

   if (!IsEqual(unitVector.GetMagnitude(), 1.0)) // must be a unit vector
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);

   KnownDotUnit = vKnown.Dot(unitVector);
   KnownCrossUnit = vKnown.Cross(unitVector);

   v1 = unitVector.ScaleBy(KnownDotUnit);
   v1.Scale(1-cos(angle));

   v2 = vKnown.ScaleBy(cos(angle));

   v3 = KnownCrossUnit.ScaleBy(sin(-1*angle));

   v4 = v1 + v2;
   v5 = v4 + v3;

   Point3d result( Point3d(v5.X(),v5.Y(),v5.Z()) + origin );
   return result;
}

Point2d GeometricOperations::LocalToGlobal(const Point2d& origin,
                                    Float64 angle,
                                    const Point2d& local)
{
   Point3d origin3d(origin.X(),origin.Y(),0.0);
   Vector3d uv(0,0,1);
   Point3d local3d(local.X(),local.Y(),0.0);
   Point3d global3d = LocalToGlobal(origin3d,uv,angle,local3d);
   return Point2d(global3d.X(),global3d.Y());
}

Point2d GeometricOperations::GlobalToLocal(const Point2d& origin,
                                    Float64 angle,
                                    const Point2d& global)
{
   Point3d origin3d(origin.X(),origin.Y(),0.0);
   Vector3d uv(0,0,1);
   Point3d global3d(global.X(),global.Y(),0.0);
   Point3d local3d = GlobalToLocal(origin3d,uv,angle,global3d);
   return Point2d(local3d.X(),local3d.Y());
}

Line2d GeometricOperations::CreateParallelLine(const Line2d& line, Float64 dist)
{
   auto [c,n] = line.GetImplicit();
   c -= dist;
   return Line2d(c, n);
}

LineSegment2d GeometricOperations::CreateParallelLineSegment(const LineSegment2d& segment, Float64 dist)
{
   Size2d size = segment.GetEndPoint() - segment.GetStartPoint();
   Float64 dir = atan2(size.Dy(), size.Dx());
   LineSegment2d new_segment(segment);
   new_segment.Offset(dist * sin(dir), -dist * cos(dir));
   return new_segment;
}

Line2d GeometricOperations::CreateParallelLineThroughPoint(const Line2d& line, const Point2d& point)
{
   auto [u,v] = line.GetExplicit();
   return Line2d(point, v);
}

Line2d GeometricOperations::CreateNormalLineThroughPoint(const Line2d& line, const Point2d& point)
{
   Point2d poln = PointOnLineNearest(line, point);

   if (point != poln)
   {
      return Line2d(point, poln);
   }
   else
   {
      auto [u,v] = line.GetExplicit();

      Vector2d n = v.Normal();

      return Line2d(point, n);
   }
}

Point2d GeometricOperations::PointOnLineNearest(const Line2d& line, const Point2d& point)
{
   auto [c,n] = line.GetImplicit();

   n.Normalize(); // N must be normalized for this calculation

   Vector2d v(point); // Turn point int a vector

   Float64 dot = n.Dot(v);

   Float64 q = dot - c;

   n.Scale(q);

   auto [xn,yn] = n.GetDimensions();
   auto [x,y] = point.GetLocation();

   return Point2d(x - xn, y - yn);
}

bool GeometricOperations::IsPointInTriangle(const Point2d& p, const Point2d& A, const Point2d& B, const Point2d& C)
{
   // Use Barycentric Coordinate system
   // https://blogs.msdn.microsoft.com/rezanour/2011/08/07/barycentric-coordinates-and-point-in-triangle-tests/
   // http://blackpawn.com/texts/pointinpoly/default.html

   Vector2d v0(C - A);
   Vector2d v1(B - A);
   Vector2d v2(p - A);

   Float64 dot00 = v0.Dot(v0);
   Float64 dot01 = v0.Dot(v1);
   Float64 dot02 = v0.Dot(v2);
   Float64 dot11 = v1.Dot(v1);
   Float64 dot12 = v1.Dot(v2);

   Float64 denom = dot00 * dot11 - dot01 * dot01;
   if (IsZero(denom))
   {
      THROW_GEOMETRY(WBFL_GEOMETRY_E_INVALIDARG);
   }

   Float64 u = (dot11 * dot02 - dot01 * dot12) / denom;
   Float64 v = (dot00 * dot12 - dot01 * dot02) / denom;

   return (0 <= u && 0 <= v && (u + v <= 1)) ? true : false;
}
