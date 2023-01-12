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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
      if ( ls2.ContainsPoint( *ls1.GetStartPoint() ) )
      {
         *point = *ls1.GetStartPoint();
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
      if ( ls1.ContainsPoint( *ls2.GetStartPoint() ) )
      {
         *point = *ls2.GetStartPoint();
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
      if ( *ls1.GetStartPoint() == *ls2.GetStartPoint() )
      {
         *point = *ls1.GetStartPoint();
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
      Point2d ls1s = *ls1.GetStartPoint();
      Point2d ls1e = *ls1.GetEndPoint();
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
   Float64    lc;
   Vector2d ln;
   Point2d  mu;
   Vector2d mv;

   l.GetImplicit(&lc, &ln);
   m.GetExplicit(&mu, &mv);

   Float64 d = ln.Dot(mv);
   if (d!=0)
   {
      Vector2d muv(Size2d(mu.X(),mu.Y()));      // must convert point to vector for Dot()
      Float64 f = ln.Dot(muv);
      f = (f - lc)/d;

      mv.SetMagnitude(fabs(f));
      if (f < 0) mv.Reflect();

      Float64 x1, y1;
      muv.GetDimensions(&x1, &y1);
      Float64 x2, y2;
      mv.GetDimensions(&x2, &y2);
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
      if ( l.ContainsPoint( *ls.GetStartPoint() ) )
      {
         *point = *ls.GetStartPoint();
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
      *point = *ls.GetStartPoint();
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
   Point2d center = *c.GetCenter();
   Point2d poln = l.PointOnLineNearest( center );
   Float64 radius = c.GetRadius();
   if ( radius < poln.Distance(center) )
      return 0; // Shorted dist to line is > radius.  They can't intersect

   Point2d p;
   Vector2d v;
   l.GetExplicit(&p, &v);
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
      CHECK( D >= 0 );
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
   auto center1 = c1.GetCenter();
   auto r1 = c1.GetRadius();
   auto center2 = c2.GetCenter();
   auto r2 = c2.GetRadius();

   // If the circles have the same center and the same radius, all points along the
   // circle intersect. Return the special value of 3. If the radii are different, there
   // are no intersection points
   if (*center1 == *center2)
   {
      // Center is the same
      nIntersect = IsEqual(r1, r2) ? 3 : 0;
      return nIntersect;
   }


   // OK... do the regular intersection calculations

   // Compute some constants used in the solution of the quadratic equation
   Float64 cx1, cy1; center1->GetLocation(&cx1, &cy1);
   Float64 cx2, cy2; center2->GetLocation(&cx2, &cy2);

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
   if (p1 == p2) THROW_GEOMETRY(_T("GeometricOperations::ProjectPointAlongLine - p1 and p2 cannot be coincident"));

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
   Float64 c1, c2;
   Vector2d n1, n2;
   l1.GetImplicit(&c1, &n1);
   l2.GetImplicit(&c2, &n2);
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
   Float64 c1, c2;
   Vector2d n1, n2;
   l1.GetImplicit(&c1, &n1);
   l2.GetImplicit(&c2, &n2);
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
   if (radius < 0) THROW_GEOMETRY(_T("GeometricOperations::GenerateCircle - invalid radius"));

   // Design note: lots of points can be used to general a circle - to avoid copying a large container on return
   // a container is provided by the caller that is filled up. We intentionally do not clear the container because
   // the caller might want to append points to the end of the container.
   Float64 cum_angle = 0;
   while ( -TWO_PI < cum_angle && cum_angle < TWO_PI )
   {
      vPoints->emplace_back(center.X() + radius * cos(initAngle + cum_angle), center.Y() + radius * sin(initAngle + cum_angle));
      cum_angle += deltaAngle;
   }
}

Float64 GeometricOperations::Angle(const Point2d& start, const Point2d& center, const Point2d& end)
{
   Float64 sx, sy; // Start Point
   Float64 cx, cy; // Center Point
   Float64 ex, ey; // End Points
   Float64 dx1, dy1; // Delta x and y center to start point
   Float64 dx2, dy2; // Delta x and y center to end point

   start.GetLocation(&sx, &sy);
   center.GetLocation(&cx, &cy);
   end.GetLocation(&ex, &ey);
   
   dx1 = sx - cx;
   dy1 = sy - cy;

   dx2 = ex - cx;
   dy2 = ey - cy;

   if (IsZero(dx1) && IsZero(dy1) || IsZero(dx2) && IsZero(dy2))
      THROW_GEOMETRY(_T("GeometricOperations::Angle - start, center, and end cannot be coincident points"));

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

   Float64 c;
   Vector2d n;
   line.GetImplicit(&c, &n);

   Float64 dot = n.Dot(v);
   if (dot < 0) distance *= -1.0;

   return distance;
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
      THROW_GEOMETRY(_T("GeometricOperations::GlobalToLocal - invalid unit vector"));

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

   if (!IsEqual(unitVector.GetMagnitude(), 1.0))
      THROW_GEOMETRY(_T("GeometricOperations::GlobalToLocal - invalid unit vector"));

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
   Float64 c;  Vector2d n;  line.GetImplicit(&c, &n);
   c -= dist;
   return Line2d(c, n);
}

LineSegment2d GeometricOperations::CreateParallelLineSegment(const LineSegment2d& segment, Float64 dist)
{
   Size2d size = (*segment.GetEndPoint()) - (*segment.GetStartPoint());
   Float64 dir = atan2(size.Dy(), size.Dx());
   LineSegment2d new_segment(segment);
   new_segment.Offset(dist * sin(dir), -dist * cos(dir));
   return new_segment;
}

Line2d GeometricOperations::CreateParallelLineThroughPoint(const Line2d& line, const Point2d& point)
{
   Point2d u; Vector2d v; line.GetExplicit(&u, &v);
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
      Point2d u;
      Vector2d v;
      line.GetExplicit(&u, &v);

      Vector2d n = v.Normal();

      return Line2d(point, n);
   }
}

Point2d GeometricOperations::PointOnLineNearest(const Line2d& line, const Point2d& point)
{
   Float64 c; Vector2d n; line.GetImplicit(&c, &n);

   n.Normalize(); // N must be normalized for this calculation

   Vector2d v(point); // Turn point int a vector

   Float64 dot = n.Dot(v);

   Float64 q = dot - c;

   n.Scale(q);

   Float64 xn, yn; n.GetDimensions(&xn, &yn);
   Float64 x, y; point.GetLocation(&x, &y);

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
      THROW_GEOMETRY(_T("GeometricOperations::InPointInTriangle - invalid points"));
   }

   Float64 u = (dot11 * dot02 - dot01 * dot12) / denom;
   Float64 v = (dot00 * dot12 - dot01 * dot02) / denom;

   return (0 <= u && 0 <= v && (u + v <= 1)) ? true : false;
}

#if defined _DEBUG
bool GeometricOperations::AssertValid() const
{
   return true;
}

void GeometricOperations::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for GeometricOperations" << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool GeometricOperations::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("GeometricOperations");

   //
   // Angle
   //
   Point2d p1(3, 8);
   Point2d p2(0, 0);
   Point2d p3(5, 7);

   Float64 angle = GeometricOperations::Angle(p1, p2, p3);
   TRY_TESTME(IsEqual(angle, 6.02170649147));
   angle = GeometricOperations::Angle(p3, p2, p1);
   TRY_TESTME(IsEqual(angle, 0.2614788157));

   try
   {
      angle = GeometricOperations::Angle(p1, p1, p3);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   try
   {
      angle = GeometricOperations::Angle(p1, p3, p3);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   p1.Move(10, 0);
   p3.Move(0, 10);
   angle = GeometricOperations::Angle(p1, p2, p3);
   TRY_TESTME(IsEqual(angle, PI_OVER_2));
   angle = GeometricOperations::Angle(p3, p2, p1);
   TRY_TESTME(IsEqual(angle, 3 * PI_OVER_2));

   p1.Move(-3, -8);
   p3.Move(-5, -7);
   angle = GeometricOperations::Angle(p1, p2, p3);
   TRY_TESTME(IsEqual(angle, 6.02170649147));
   angle = GeometricOperations::Angle(p3, p2, p1);
   TRY_TESTME(IsEqual(angle, 0.2614788157));

   //
   // ShortestOffsetToPoint
   //
   p1.Move(10, 10);
   p2.Move(20, 20);
   Line2d line(p1, p2);

   p3.Move(10, 20);
   Float64 dist = GeometricOperations::ShortestOffsetToPoint(line, p3);
   TRY_TESTME(IsEqual(dist, -7.07106)); // Point on left side (-)

   p3.Move(20, 10);
   dist = GeometricOperations::ShortestOffsetToPoint(line, p3);
   TRY_TESTME(IsEqual(dist, 7.07106)); // Point on right side (+)

   //
   // PointOnLineNearest
   //
   p1.Move(0, 10);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);
   p3.Move(5, 5);

   Point2d poln = GeometricOperations::PointOnLineNearest(line, p3);
   TRY_TESTME(poln == Point2d(5.0, 10.0));

   p3.Move(20, 10);
   poln = GeometricOperations::PointOnLineNearest(line, p3);
   TRY_TESTME(poln == Point2d(20.0, 10.0));

   p1.Move(0, 0);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);
   p3.Move(0, 10);
   poln = GeometricOperations::PointOnLineNearest(line, p3);
   TRY_TESTME(poln == Point2d(5.0, 5.0));

   p1.Move(0, 0);
   p2.Move(-10, 10);
   line.ThroughPoints(p1, p2);
   p3.Move(0, 10);
   poln = GeometricOperations::PointOnLineNearest(line, p3);
   TRY_TESTME(poln == Point2d(-5.0, 5.0));

   p1.Move(0, 0);
   p2.Move(-10, -10);
   line.ThroughPoints(p1, p2);
   p3.Move(0, -10);
   poln = GeometricOperations::PointOnLineNearest(line, p3);
   TRY_TESTME(poln == Point2d(-5.0, -5.0));

   p1.Move(0, 0);
   p2.Move(10, -10);
   line.ThroughPoints(p1, p2);
   p3.Move(0, -10);
   poln = GeometricOperations::PointOnLineNearest(line, p3);
   TRY_TESTME(poln == Point2d(5.0, -5.0));


   //
   // CreateParallelLine
   //
   p1.Move(0, 0);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);
   Line2d line2 = GeometricOperations::CreateParallelLine(line, 10.0);
   TRY_TESTME(GeometricOperations::IsParallel(line, line2));

   p1.Move(0, 0);
   p2.Move(10, 0);
   line.ThroughPoints(p1, p2);
   line2 = GeometricOperations::CreateParallelLine(line, 10.0);
   TRY_TESTME(GeometricOperations::IsParallel(line, line2));

   p1.Move(0, 0);
   p2.Move(0, 10);
   line.ThroughPoints(p1, p2);
   line2 = GeometricOperations::CreateParallelLine(line, 10.0);
   TRY_TESTME(GeometricOperations::IsParallel(line, line2));
   
   //
   // CreateParallelLineSegment
   //
   p1.Move(0, 0);
   p2.Move(10, 10);
   LineSegment2d seg1(p1,p2);
   LineSegment2d seg2 = GeometricOperations::CreateParallelLineSegment(seg1, 10.0);
   TRY_TESTME(GeometricOperations::IsParallel(seg1, seg2));

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(10, 0);
   seg2 = GeometricOperations::CreateParallelLineSegment(seg1, 10.0);
   TRY_TESTME(GeometricOperations::IsParallel(seg1, seg2));

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(0, 10);
   seg2 = GeometricOperations::CreateParallelLineSegment(seg1, 10.0);
   TRY_TESTME(GeometricOperations::IsParallel(seg1, seg2));


   //
   // CreateParallelLineThroughPoint
   //
   p1.Move(10, 10);
   p2.Move(20, 30);
   line.ThroughPoints(p1, p2);
   p3.Move(-10, 15);
   line2 = GeometricOperations::CreateParallelLineThroughPoint(line, p3);
   TRY_TESTME(GeometricOperations::IsParallel(line, line2));

   //
   // CreateNormalLineThroughPoint
   //
   p1.Move(40, 34);
   p2.Move(0, 4);
   line.ThroughPoints(p1, p2);
   p3.Move(-3, 8);
   line2 = GeometricOperations::CreateNormalLineThroughPoint(line, p3);

   Float64 c; Vector2d v;
   line2.GetImplicit(&c, &v);
   TRY_TESTME(IsEqual(c, 2.4));
   TRY_TESTME(v == Vector2d(Size2d(0.8, 0.6)));

   p3.Move(0, 4);
   line2 = GeometricOperations::CreateNormalLineThroughPoint(line, p3);
   line2.GetImplicit(&c, &v);
   TRY_TESTME(IsEqual(c, 2.4));
   TRY_TESTME(v == Vector2d(Size2d(0.8, 0.6)));

   //
   // LineCircleIntersect
   //
   p1.Move(0, 0);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);

   p3.Move(5, 5);
   Circle circle1(p3,5.0);
   Point2d intersect1, intersect2;

   auto nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME(intersect1 == Point2d(1.464466, 1.464466));
   TRY_TESTME(intersect2 == Point2d(8.535534, 8.535534));

   p1.Move(0, 100);
   p2.Move(10, 110);
   line.ThroughPoints(p1, p2);
   nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
   TRY_TESTME(nIntersect == 0);

   p1.Move(0, 10);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);
   nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
   TRY_TESTME(nIntersect == 1);
   TRY_TESTME(intersect1 == Point2d(5, 10));

   p1.Move(5, 0);
   p2.Move(5, 10);
   line.ThroughPoints(p1, p2);
   nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME(intersect1 == Point2d(5, 10));
   TRY_TESTME(intersect2 == Point2d(5, 0));

   p1.Move(10, 0);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);
   nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
   TRY_TESTME(nIntersect == 1);
   TRY_TESTME(intersect1 == Point2d(10, 5));

   p1.Move(-50, -210);
   p2.Move(90, 90);
   line.ThroughPoints(p1, p2);
   circle1.GetHookPoint()->Move(0, 0);
   circle1.SetRadius(100.);
   nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME(intersect1 == Point2d(1.337507, -99.991055));
   TRY_TESTME(intersect2 == Point2d(77.49461, 63.202734));

   //
   // LineLineIntersect
   // 
   p1.Move(10, 0);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);

   p3.Move(20, 0);
   Point2d p4(20, 10);
   line2.ThroughPoints(p3, p4);

   Int16 result = GeometricOperations::Intersect(line, line2, &intersect1);
   TRY_TESTME(result == 0);

   p1.Move(0, 0);
   p2.Move(10, 10);
   line.ThroughPoints(p1, p2);

   p3.Move(10, 0);
   p4.Move(0, 10);
   line2.ThroughPoints(p3, p4);

   result = GeometricOperations::Intersect(line, line2, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(5, 5));

   //
   // SegSegIntersect
   //
   p1.Move(10, 0);
   p2.Move(10, 10);
   seg1.ThroughPoints(p1,p2);

   p3.Move(20, 0);
   p4.Move(20, 10);
   seg2.ThroughPoints(p3,p4);

   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 0);

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(10, 10);
   seg2.GetStartPoint()->Move(10, 0);
   seg2.GetEndPoint()->Move(0, 10);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(5, 5));

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(0, 0);
   seg2.GetStartPoint()->Move(10, 0);
   seg2.GetEndPoint()->Move(0, 10);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 0);

   seg1.GetStartPoint()->Move(5, 5);
   seg1.GetEndPoint()->Move(5, 5);
   seg2.GetStartPoint()->Move(10, 0);
   seg2.GetEndPoint()->Move(0, 10);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(5, 5));

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(10, 10);
   seg2.GetStartPoint()->Move(0, 10);
   seg2.GetEndPoint()->Move(0, 10);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 0);

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(10, 10);
   seg2.GetStartPoint()->Move(5, 5);
   seg2.GetEndPoint()->Move(5, 5);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(5, 5));

   seg1.GetStartPoint()->Move(5, 5);
   seg1.GetEndPoint()->Move(5, 5);
   seg2.GetStartPoint()->Move(10, 10);
   seg2.GetEndPoint()->Move(10, 10);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 0);

   seg1.GetStartPoint()->Move(10, 10);
   seg1.GetEndPoint()->Move(10, 10);
   seg2.GetStartPoint()->Move(10, 10);
   seg2.GetEndPoint()->Move(10, 10);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(10, 10));

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(4, 4);
   seg2.GetStartPoint()->Move(0, 10);
   seg2.GetEndPoint()->Move(10, 0);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 0);

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(4, 4);
   seg2.GetStartPoint()->Move(0, 10);
   seg2.GetEndPoint()->Move(5, 4);
   result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
   TRY_TESTME(result == 0);


   //
   // IntersectLineWithLineSegment
   //
   p1.Move(0, 0);
   p2.Move(10, 10);
   p3.Move(10, 0);
   p4.Move(0, 10);
   line.ThroughPoints(p1, p2);
   seg1.ThroughPoints(p3, p4);

   result = GeometricOperations::Intersect(line, seg1, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(5, 5));

   seg1.GetEndPoint()->Move(100, 100);
   result = GeometricOperations::Intersect(line, seg1, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(100, 100));

   seg1.GetStartPoint()->Move(0, 0);
   seg1.GetEndPoint()->Move(10, 10);
   result = GeometricOperations::Intersect(line, seg1, &intersect1);
   TRY_TESTME(result == -1);

   seg1.GetStartPoint()->Move(10, 15);
   seg1.GetEndPoint()->Move(10, 15);
   result = GeometricOperations::Intersect(line, seg1, &intersect1);
   TRY_TESTME(result == 0);

   seg1.GetStartPoint()->Move(5, 5);
   seg1.GetEndPoint()->Move(5, 5);
   result = GeometricOperations::Intersect(line, seg1, &intersect1);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(5, 5));

   //
   // CircleCircleIntersect
   //
   circle1 = Circle(Point2d(0, 0), 5);
   Circle circle2(Point2d(5, 5), 5);
   
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(0, 5));
   TRY_TESTME(intersect2 == Point2d(5, 0));

   circle2.GetHookPoint()->Move(0, 0); // same center and radius - infinite number of results
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 3);

   circle2.SetRadius(10.0); // same center, bigger radius, no intersections
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 0);

   circle2.GetHookPoint()->Move(100, 100); // circles don't overlap
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 0);

   circle2.GetHookPoint()->Move(10, 0);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 1);
   TRY_TESTME(intersect1 == Point2d(5, 0));

   circle2.GetHookPoint()->Move(5, 5);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(0, 5));
   TRY_TESTME(intersect2 == Point2d(5, 0));

   circle2.GetHookPoint()->Move(-5, 5);
   circle2.SetRadius(5);

   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(-5, 0));
   TRY_TESTME(intersect2 == Point2d(0, 5));

   circle2.GetHookPoint()->Move(-5, -5);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(-5, 0));
   TRY_TESTME(intersect2 == Point2d(0, -5));

   circle2.GetHookPoint()->Move(5, -5);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(0, -5));
   TRY_TESTME(intersect2 == Point2d(5, 0));

   circle2.GetHookPoint()->Move(0, 5);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(-4.330127, 2.5));
   TRY_TESTME(intersect2 == Point2d(4.330127, 2.5));

   circle2.GetHookPoint()->Move(0, -5);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(-4.330127, -2.5));
   TRY_TESTME(intersect2 == Point2d(4.330127, -2.5));

   circle2.GetHookPoint()->Move(5,0);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(2.5, 4.330127));
   TRY_TESTME(intersect2 == Point2d(2.5,-4.330127));


   circle2.GetHookPoint()->Move(-5, 0);
   circle2.SetRadius(5);
   result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
   TRY_TESTME(result == 2);
   TRY_TESTME(intersect1 == Point2d(-2.5, 4.330127));
   TRY_TESTME(intersect2 == Point2d(-2.5, -4.330127));


   //
   // IsLineParallelToLineSegment
   //
   p1.Move(0, 0);
   p2.Move(10, 10);
   p3.Move(10, 0);
   p4.Move(0, 10);
   line.ThroughPoints(p1, p2);
   seg1.ThroughPoints(p3, p4);
   TRY_TESTME(!GeometricOperations::IsParallel(line, seg1));

   seg1.GetStartPoint()->Move(0, 10);
   seg1.GetEndPoint()->Move(10, 20);
   TRY_TESTME(GeometricOperations::IsParallel(line, seg1));
   TRY_TESTME(GeometricOperations::IsParallel(seg1, line));

   //
   // AreLineSegmentsParallel
   //
   p1.Move(-10, -10);
   p2.Move(-20, -20);
   seg1.ThroughPoints(p1, p2);

   p3.Move(0, -20);
   p4.Move(-20, -40);
   seg2.ThroughPoints(p3, p4);
   TRY_TESTME(GeometricOperations::IsParallel(seg1, seg2));

   seg2.GetEndPoint()->Offset(3, 5);
   TRY_TESTME(!GeometricOperations::IsParallel(seg1, seg2));

   //
   // AreLinesParallel
   //
   p1.Move(-10, -10);
   p2.Move(-20, -20);
   line.ThroughPoints(p1, p2);

   p3.Move(0, -20);
   p4.Move(-20, -40);
   line2.ThroughPoints(p3, p4);
   TRY_TESTME(GeometricOperations::IsParallel(line, line2));
   TRY_TESTME(GeometricOperations::IsParallel(line2, line));
   TRY_TESTME(GeometricOperations::IsParallel(line, line));

   p4.Offset(3, 5);
   line2.ThroughPoints(p3, p4);
   TRY_TESTME(!GeometricOperations::IsParallel(line, line2));


   //
   // Test PointInTriangle
   //
   p1.Move(5, 5);
   p2.Move(0, 0);
   p3.Move(20, 0);
   p4.Move(0, 20);
   TRY_TESTME(GeometricOperations::IsPointInTriangle(p1, p2, p3, p4));
   p1.Move(30, 30);
   TRY_TESTME(!GeometricOperations::IsPointInTriangle(p1, p2, p3, p4));


   ////////////////////////////////////////
   Point2d p1_7(1,7), pn3_3(-3,3), p0_4(0,4), p3_5(3,5),p6_6(6,6);
   Point2d p8_0(8,0), p9_n1(9,-1), p5_n5(5,-5), p12_2(12,2);

   Line2d l1(pn3_3,p0_4), l2(p1_7,p8_0), l3(p5_n5,p12_2);
   Line2d ln2(p8_0,p1_7);

   LineSegment2d ls0(p1_7,p1_7), ls1(pn3_3,p0_4), ls2(p1_7,p9_n1),  ls3(p5_n5,p12_2);
   LineSegment2d ls4(p0_4,p6_6), ls5(pn3_3,p6_6), ls6(p3_5,p1_7);

   Point2d pt;

   // intersect
   TRY_TESTME (1  == Intersect(l1,l2,&pt));
   TRY_TESTME (pt == p3_5);
   TRY_TESTME (1  == Intersect(l3,l2,&pt));
   TRY_TESTME (pt == p9_n1);
   TRY_TESTME (-1 == Intersect(l2,ln2,&pt));

   TRY_TESTME (1  == Intersect(ls4,ls2,&pt));
   TRY_TESTME (pt == p3_5);
   TRY_TESTME (1  == Intersect(ls2,ls3,&pt));
   TRY_TESTME (pt == p9_n1);
   TRY_TESTME (-1 == Intersect(ls1,ls4,&pt));
   TRY_TESTME (pt == p0_4);
   TRY_TESTME (0  == Intersect(ls4,ls3,&pt));
   TRY_TESTME (0  == Intersect(ls2,ls1,&pt));
   TRY_TESTME (0  == Intersect(ls0,ls1,&pt));

   // zero length line segment tests
   LineSegment2d ls7( 10, 50, 10, 100 );
   Line2d l4(ls7);
   LineSegment2d zls1( 10,10,10,10 );
   LineSegment2d zls2( 10,60,10,60 );
   LineSegment2d zls3( 10,10,10,10 );
   TRY_TESTME ( Intersect(ls7,zls1,&pt)  == 0 );
   TRY_TESTME ( Intersect(ls7,zls2,&pt)  == 1 && pt == Point2d(10,60) );
   TRY_TESTME ( Intersect(zls1,zls3,&pt) == 1 && pt == Point2d(10,10) );
   TRY_TESTME ( Intersect(l4,zls2,&pt)   == 1 && pt == Point2d(10,60) );
   TRY_TESTME ( Intersect(zls2,l4,&pt)   == 1 && pt == Point2d(10,60) );

   LineSegment2d ls8(25.6792,0.000,25.6792,-.0001);
   LineSegment2d ls9(25.6792,-0.000007,25.6792,-0.000007);
   TRY_TESTME ( Intersect(ls8,ls9,&pt) == 1 );

   // parallel
   TRY_TESTME (IsParallel(ls2,ls6));
   TRY_TESTME(!SameDirection(ls2, ls6)); // parallel, but not in the same direction
   TRY_TESTME (IsParallel(ls1,ls4));
   TRY_TESTME (!IsParallel(ls1,ls3));

   try
   {
      // ls0 - end points are coincident so it isn't a valid line
      TRY_TESTME(!IsParallel(ls1, ls0));
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // circle generation
   std::vector<Point2d> points;
   GenerateCircle(0, Point2d(0, 0), 10, M_PI / 4, &points);
   TRY_TESTME(points.empty());

   GenerateCircle( 4, Point2d(0,0), 10., 0., &points );
   TRY_TESTME( points.size() == 4 );
   TRY_TESTME( points[0] == Point2d(10,0) );
   TRY_TESTME( points[1] == Point2d(0,10) );
   TRY_TESTME( points[2] == Point2d(-10,0) );
   TRY_TESTME( points[3] == Point2d(0,-10) );

   points.clear();
   GenerateCircle(4, Point2d(0, 0), 10., M_PI/4, &points);
   TRY_TESTME(points.size() == 4);
   TRY_TESTME(points[0] == Point2d(7.071067, 7.071067));
   TRY_TESTME(points[1] == Point2d(-7.071067, 7.071067));
   TRY_TESTME(points[2] == Point2d(-7.071067, -7.071067));
   TRY_TESTME(points[3] == Point2d(7.071067, -7.071067));

   // Normalize angle
   angle = 3*M_PI/4;
   TRY_TESTME( IsEqual( NormalizeAngle(    angle), angle ) );
   TRY_TESTME( IsEqual( NormalizeAngle(  5*TWO_PI + angle), angle ) );
   TRY_TESTME( IsEqual( NormalizeAngle( -5*TWO_PI + angle), angle ) );

   // Test Line Circle Intersection
   Circle2d circle(Point2d(0,0),Point2d(10,0));

   // Line on horizontal diameter
   l1.ThroughPoints (Point2d(0,0),Point2d(10,0));
   nIntersect = Intersect(l1,circle,&p1,&p2);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME( p1 == Point2d(0,0) );
   TRY_TESTME( p2 == Point2d(10,0) );

   // Horizonal line at top of circle
   l1.ThroughPoints( Point2d(0,5), Point2d(5,5) );
   nIntersect = Intersect(l1,circle,&p1,&p2);
   TRY_TESTME(nIntersect == 1);
   TRY_TESTME( p1 == Point2d(5,5) );

   // Vertical line on diameter
   l1.ThroughPoints( Point2d(5,-5), Point2d(5,5) );
   nIntersect = Intersect(l1,circle,&p1,&p2);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME( p1 == Point2d(5,5) );
   TRY_TESTME( p2 == Point2d(5,-5) );

   // Vertical line on right edge of circle
   l1.ThroughPoints( Point2d(10,0), Point2d(10,5) );
   nIntersect = Intersect(l1,circle,&p1,&p2);
   TRY_TESTME(nIntersect == 1);
   TRY_TESTME( p1 == Point2d(10,0) );

   // 45 degree line through the origin
   l1.ThroughPoints( Point2d(0,0), Point2d(5,5) );
   nIntersect = Intersect(l1,circle,&p1,&p2);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME( p1 == Point2d(0,0) );
   TRY_TESTME( p2 == Point2d(5,5) );

   // Line that doesn't intersect
   l1.ThroughPoints( Point2d(100,100), Point2d(100,200) );
   nIntersect = Intersect(l1,circle,&p1,&p2);
   TRY_TESTME( nIntersect == 0 );



   TESTME_EPILOG("GeometricOperations");
}

#endif // _UNITTEST
