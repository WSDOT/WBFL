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
#include <GeomModel/Plane3d.h>
#include <GeomModel/Primitives3d.h>
#include <GeomModel/Vector2d.h>
#include <GeomModel/Vector3d.h>
#include <GeomModel/Line2d.h>
#include <GeomModel/LineSegment3d.h>
#include <GeomModel/GeomOp2d.h>
#include <MathEx.h>
#include <stdexcept>
#include <array>

using namespace WBFL::Geometry;

Plane3d::Plane3d()
{
}

Plane3d::Plane3d(const Point3d& p, const Vector3d& n)
{
   Init(p, n);
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

void Plane3d::Init(const Point3d& p, const Vector3d& n)
{
   std::tie(m_A,m_B,m_C) = n.GetDimensions();
   m_D = -1*(m_A * p.X() + m_B * p.Y() + m_C * p.Z());
}

void Plane3d::Init(Float64 a, Float64 b, Float64 c, Float64 d)
{
   m_A = a;
   m_B = b;
   m_C = c;
   m_D = d;
}

std::tuple<Float64, Float64, Float64, Float64> Plane3d::GetConstants() const
{
   return std::make_tuple(m_A, m_B, m_C, m_D);
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
      
      if(line.ContainsPoint(pnt2d)) THROW_GEOMETRY(WBFL_GEOMETRY_E_COLINEARLINES);
   }

   // get two points on the line
   auto [p1,v] = line.GetExplicit();

   auto [x,y] = p1.GetLocation();

   Point3d p1_3d(x, y, 0.0);

   auto [dx,dy] = v.GetDimensions();

   Point3d p2_3d(x, y, 0.0);
   p2_3d.Offset(dx, dy, 0.0);

   return ThroughPoints(p1_3d, p2_3d, point);
}

void Plane3d::ThroughPoints(const Point3d& p1, const Point3d& p2, const Point3d& p3)
{
   if (p1 == p2 || p2 == p3 || p1 == p3 || IsZero(LineSegment3d(p1,p2).DistanceToPoint(p3)))
      THROW_GEOMETRY(WBFL_GEOMETRY_E_COLINEARLINES);

   // if they are, throw an exception
   const int x = 0;
   const int y = 1;
   const int z = 2;
   std::array<Float64, 3> v1;
   std::array<Float64, 3> v2;

   auto [x1,y1,z1] = p1.GetLocation();
   auto [x2,y2,z2] = p2.GetLocation();
   auto [x3,y3,z3] = p3.GetLocation();

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
         THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS); // infinite number of solutions
      else
         THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);
   }
   else if (IsZero(m_A))
   {
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);
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
         THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS); // infinite number of solutions
      else
         THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);
   }
   else if (IsZero(m_B))
   {
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);
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
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);
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

   const auto& size = end - start;

   Float64 Dx = size.Dx();
   Float64 Dy = size.Dy();
   Float64 Dz = size.Dz();

   Float64 Q = -m_D - m_A * start.X() - m_B * start.Y() - m_C * start.Z();
   Float64 R = m_A * Dx + m_B * Dy + m_C * Dz;

   if (IsZero(R)) // Line is parallel to plane, no solutions
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);

   if (IsZero(Q) && IsZero(R)) // Line is on plane, infinite solutions
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);

   Float64 t = Q / R;

   if (t < 0 || 1 < t) // Line segment does not intersect plane, however projected line segment intersects plane
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS);

   Float64 x = start.X() + t * Dx;
   Float64 y = start.Y() + t * Dy;
   Float64 z = start.Z() + t * Dz;

   return Point3d(x, y, z);
}

Float64 Plane3d::ShortestDistance(const Point3d& point) const
{
   // REFERENCE: http://en.wikipedia.org/wiki/Plane_(geometry)#Distance_from_a_point_to_a_plane
   Float64 K = m_A * m_A + m_B * m_B + m_C * m_C;
   if (IsZero(K))
   {
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS); // invalid plane
   }

   auto [x,y,z] = point.GetLocation();

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
      THROW_GEOMETRY(WBFL_GEOMETRY_E_NOSOLUTIONS); // invalid plane
   }

   Float64 d = m_D - m_A * point.X() - m_B * point.Y() - m_C * point.Z();

   Float64 x = m_A * d / K;
   Float64 y = m_B * d / K;
   Float64 z = m_C * d / K;

   return point + Point3d(x, y, z);
}

Vector3d Plane3d::NormalVector() const
{
   // REFERENCE: https://tutorial.math.lamar.edu/classes/calcIII/EqnsOfPlanes.aspx
   // the coefficients A, B, and C define the normal vector
   Vector3d v(m_A, m_B, m_C);
   return v;
}
