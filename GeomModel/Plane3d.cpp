///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
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
#include <GeomModel/Plane3d.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/Vector2d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/LineSegment3d.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include <stdexcept>
#include <array>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Geometry;

Plane3d::Plane3d()
{
}

Plane3d::Plane3d(Float64 a, Float64 b, Float64 c, Float64 d)
{
   Init(a, b, c, d);
}

Plane3d::Plane3d(Float64 altitude)
{
   ThroughAltitude(altitude);
}

Plane3d::Plane3d(const Line2d& line, const Point3d& point)
{
   ThroughLine(line, point);
}

Plane3d::Plane3d(const Point3d& p1, const Point3d& p2, const Point3d& p3)
{
   ThroughPoints(p1, p2, p3);
}

Plane3d::~Plane3d()
{
}

void Plane3d::Init(Float64 a, Float64 b, Float64 c, Float64 d)
{
   m_A = a;
   m_B = b;
   m_C = c;
   m_D = d;
}

void Plane3d::GetConstants(Float64* pA, Float64* pB, Float64* pC, Float64* pD) const
{
   *pA = m_A;
   *pB = m_B;
   *pC = m_C;
   *pD = m_D;
}

void Plane3d::ThroughAltitude(Float64 altitude)
{
   XY(altitude);
}

void Plane3d::ThroughLine(const Line2d& line, const Point3d& point)
{
   // If point is on the line, the plane is undefined
   Float64 z = point.Z();
   if (IsZero(z)) // Point is in XY plane
   {
      Point2d pnt2d(point.X(), point.Y());
      
      if(line.ContainsPoint(pnt2d)) THROW_GEOMETRY(_T("Plane3d::Init - point cannot be on the line"));
   }

   // get two points on the line
   Point2d p1;
   Vector2d v;
   line.GetExplicit(&p1, &v);

   Float64 x, y;
   p1.GetLocation(&x, &y);

   Point3d p1_3d(x, y, 0.0);

   Float64 dx, dy;
   v.GetDimensions(&dx, &dy);

   Point3d p2_3d(x, y, 0.0);
   p2_3d.Offset(dx, dy, 0.0);

   return ThroughPoints(p1_3d, p2_3d, point);
}

void Plane3d::ThroughPoints(const Point3d& p1, const Point3d& p2, const Point3d& p3)
{
   if (p1 == p2 || p2 == p3 || p1 == p3 || IsZero(LineSegment3d(p1,p2).DistanceToPoint(p3)))
      THROW_GEOMETRY(_T("Plane3d::ThroughPoints - points cannot be coincident or colinear"));

   // if they are, throw an exception
   const int x = 0;
   const int y = 1;
   const int z = 2;
   std::array<Float64, 3> v1;
   std::array<Float64, 3> v2;

   Float64 x1, x2, x3;
   Float64 y1, y2, y3;
   Float64 z1, z2, z3;
   p1.GetLocation(&x1, &y1, &z1);
   p2.GetLocation(&x2, &y2, &z2);
   p3.GetLocation(&x3, &y3, &z3);

   v1[x] = x2 - x1;
   v1[y] = y2 - y1;
   v1[z] = z2 - z1;

   v2[x] = x3 - x1;
   v2[y] = y3 - y1;
   v2[z] = z3 - z1;

   m_A = v1[y] * v2[z] - v1[z] * v2[y];
   m_B = v1[z] * v2[x] - v1[x] * v2[z];
   m_C = v1[x] * v2[y] - v1[y] * v2[x];

   m_D = -1 * (m_A * x1 + m_B * y1 + m_C * z1);

   // normalize coefficients
   Float64 d = Max(fabs(m_A), fabs(m_B), fabs(m_C), fabs(m_D));
   m_A /= d;
   m_B /= d;
   m_C /= d;
   m_D /= d;

#if defined _DEBUG
   if (!IsZero(m_D))
   {
      Float64 d2 = -1 * (m_A * x2 + m_B * y2 + m_C * z2);
      Float64 d3 = -1 * (m_A * x3 + m_B * y3 + m_C * z3);
      CHECK(IsEqual(d2/m_D, 1.0));
      CHECK(IsEqual(d3/m_D, 1.0));
   }
#endif
}

void Plane3d::XY(Float64 altitude)
{
   m_A = 0;
   m_B = 0;
   m_C = -1.0;
   m_D = altitude;
}

void Plane3d::XZ(Float64 altitude)
{
   m_A = 0;
   m_B = -1.0;
   m_C = 0;
   m_D = altitude;
}

void Plane3d::YZ(Float64 altitude)
{
   m_A = -1.0;
   m_B = 0;
   m_C = 0;
   m_D = altitude;
}

Float64 Plane3d::GetX(Float64 y, Float64 z) const
{
   Float64 X = 0;
   if (IsZero(m_A) && IsZero(m_B) && IsZero(m_C))
   {
      if (IsEqual(m_D, z) || IsZero(m_A))
         THROW_GEOMETRY(_T("Plane3d::GetX - there are an infinite number of solutions"));
      else
         THROW_GEOMETRY(_T("Plane3d::GetX - there are no solutions"));
   }
   else if (IsZero(m_A))
   {
      THROW_GEOMETRY(_T("Plane3d::GetX - there are no solutions"));
   }
   else
   {
      X = (m_B * y + m_C * z + m_D) / (-m_A);
   }

   return X;
}

Float64 Plane3d::GetY(Float64 x, Float64 z) const
{
   Float64 Y = 0;
   if (IsZero(m_A) && IsZero(m_B) && IsZero(m_C))
   {
      if (IsEqual(m_D, z) || IsZero(m_B))
         THROW_GEOMETRY(_T("Plane3d::GetY - there are an infinite number of solutions"));
      else
         THROW_GEOMETRY(_T("Plane3d::GetY - there are no solutions"));
   }
   else if (IsZero(m_B))
   {
      THROW_GEOMETRY(_T("Plane3d::GetY - there are no solutions"));
   }
   else
   {
      Y = (m_A * x + m_C * z + m_D) / (-m_B);
   }
   return Y;
}

Float64 Plane3d::GetZ(Float64 x, Float64 y) const
{
   Float64 Z = 0;
   if (IsZero(m_A) && IsZero(m_B) && IsZero(m_C))
   {
      Z = m_D;
   }
   else if (IsZero(m_C))
   {
      THROW_GEOMETRY(_T("Plane3d::GetZ - there are no solutions"));
   }
   else
   {
      Z = (m_A * x + m_B * y + m_D) / (-m_C);
   }

   return Z;
}

Point3d Plane3d::LineSegmentIntersect(const LineSegment3d& lineSegment) const
{
   // Reference: http://en.wikipedia.org/wiki/Line-plane_intersection
   const auto& start = lineSegment.GetStartPoint();
   const auto& end = lineSegment.GetEndPoint();

   const auto& size = *end - *start;

   Float64 Dx = size.Dx();
   Float64 Dy = size.Dy();
   Float64 Dz = size.Dz();

   Float64 Q = -m_D - m_A * start->X() - m_B * start->Y() - m_C * start->Z();
   Float64 R = m_A * Dx + m_B * Dy + m_C * Dz;

   if (IsZero(R)) // Line is parallel to plane
      THROW_GEOMETRY(_T("Plane3d::LineSegmentIntersect - line segment is parallel to the plane, there are no solutions"));

   if (IsZero(Q) && IsZero(R)) // Line is on plane
      THROW_GEOMETRY(_T("Plane3d::LineSegmentIntersect - line segment is in the plane - there are infinite solutions"));

   Float64 t = Q / R;

   if (t < 0 || 1 < t)
      THROW_GEOMETRY(_T("Plane3d::LineSegmentIntersect - the line segment does not intersects the plane, however projected line segment intersects the plane"));

   Float64 x = start->X() + t * Dx;
   Float64 y = start->Y() + t * Dy;
   Float64 z = start->Z() + t * Dz;

   return Point3d(x, y, z);
}

Float64 Plane3d::ShortestDistance(const Point3d& point) const
{
   // REFERENCE: http://en.wikipedia.org/wiki/Plane_(geometry)#Distance_from_a_point_to_a_plane
   Float64 K = m_A * m_A + m_B * m_B + m_C * m_C;
   if (IsZero(K))
   {
      THROW_GEOMETRY(_T("Plane3d::ShortestDistance - Invalid plane"));
   }

   Float64 x, y, z;
   point.GetLocation(&x, &y, &z);

   Float64 distance = (m_A * x + m_B * y + m_C * z + m_D) / sqrt(K);
   // distance > 0... point is above plane (on same side as normal)
   // distance < 0... point is below plane

   return distance;
}

Point3d Plane3d::PointOnPlaneNearest(const Point3d& point) const
{
   // REFERENCE: http://en.wikipedia.org/wiki/Point_on_plane_closest_to_origin

   Float64 K = m_A * m_A + m_B * m_B + m_C * m_C;
   if (IsZero(K))
   {
      THROW_GEOMETRY(_T("Plane3d::ShortestDistance - Invalid plane"));
   }

   Float64 d = m_D - m_A * point.X() - m_B * point.Y() - m_C * point.Z();

   Float64 x = m_A * d / K;
   Float64 y = m_B * d / K;
   Float64 z = m_C * d / K;

   return point + Point3d(x, y, z);
}


#if defined _DEBUG
bool Plane3d::AssertValid() const
{
   return true;
}

void Plane3d::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for Plane3d") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool Plane3d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Plane3d");

   Plane3d plane;

   // XY Plane at Altitude = 10.0
   plane.ThroughAltitude(10.0);
   TRY_TESTME(IsEqual(plane.GetZ(5, 5), 10.0));

   try
   {
      plane.GetX(5, 5);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   try
   {
      plane.GetY(5, 5);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // Plane through three points
   Point3d p1(0, 0, 0), p2(0, 0, 10), p3(10, 10, 0);
   plane.ThroughPoints(p1, p2, p3);

   TRY_TESTME(IsEqual(plane.GetX(5, 5), 5.0));
   TRY_TESTME(IsEqual(plane.GetY(5, 5), 5.0));
   try
   {
      plane.GetZ(5, 5);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // ThroughLineEx
   Line2d line; // Line on the X axis
   line.Rotate(Point2d(0, 0), PI_OVER_2); // Line is now in the pos Y direction
   p3.Move(10, 0, 10);
   plane.ThroughLine(line, p3);

   TRY_TESTME(IsEqual(plane.GetX(5, 5), 5.0));
   try
   {
      plane.GetY(5, 5);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }   
   TRY_TESTME(IsEqual(plane.GetZ(5, 5), 5.0));


   p3.Move(0, 10, 0); // point is now on the line
   try
   {
      plane.ThroughLine(line, p3);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // Arbitrary Plane
   p1.Move(10, 0, 0);
   p2.Move(0, 10, 0);
   p3.Move(0, 0, 10);
   plane.ThroughPoints(p1, p2, p3);

   TRY_TESTME(IsEqual(plane.GetX(5, 5), 0.0));
   TRY_TESTME(IsEqual(plane.GetY(5, 5), 0.0));
   TRY_TESTME(IsEqual(plane.GetZ(5, 5), 0.0));

   
   p1.Move(1, 0, 0);
   p2.Move(0, 1, 0);
   p3.Move(0, 0, 1);
   plane.ThroughPoints(p1, p2, p3);

   Point3d A(0, 0, 0);
   Point3d B(10, 10, 10);
   LineSegment3d seg(A, B);

   Point3d intersect = plane.LineSegmentIntersect(seg);
   TRY_TESTME(intersect == Point3d(1. / 3., 1. / 3., 1. / 3.));

   B.Move(10, 10, 0);
   seg.ThroughPoints(A, B);
   intersect = plane.LineSegmentIntersect(seg);
   TRY_TESTME(intersect == Point3d(0.5, 0.5, 0.0));

   B.Move(0, 10, 10);
   seg.ThroughPoints(A, B);
   intersect = plane.LineSegmentIntersect(seg);
   TRY_TESTME(intersect == Point3d(0.0,0.5,0.5));

   B.Move(10, 0, 10);
   seg.ThroughPoints(A, B);
   intersect = plane.LineSegmentIntersect(seg);
   TRY_TESTME(intersect == Point3d(0.5, 0.0, 0.5));

   // Parallel to YZ at X = 1
   p1.Move(1, 0, 0);
   p2.Move(1, 1, 0);
   p3.Move(1, 0, 1);
   plane.ThroughPoints(p1, p2, p3);

   B.Move(10, 0, 0);
   seg.ThroughPoints(A, B);
   intersect = plane.LineSegmentIntersect(seg);
   TRY_TESTME(intersect == Point3d(1.0, 0.0, 0.0));

   // parallel to the plane
   B.Move(0, 10, 10);
   seg.ThroughPoints(A, B);
   try
   {
      intersect = plane.LineSegmentIntersect(seg);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   // in the plane
   A.Move(1, 0, 0);
   B.Move(1, 10, 10);
   seg.ThroughPoints(A, B);
   try
   {
      intersect = plane.LineSegmentIntersect(seg);
      TRY_TESTME(false);
   }
   catch (...)
   {
      TRY_TESTME(true);
   }

   TESTME_EPILOG("Plane3d");
}
#endif // _UNITTEST


