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
#include <GeomModel/Line2d.h>

#include <GeomModel/LineSegment2d.h>
#include <GeomModel/Primitives.h>

#include <iostream>
#include <math.h>
#include <limits>

/// Line2d encapsulates the notion of a line with infinite length. The 
/// implementation for this is taken from Chapter 1 of the original
/// Graphics Gems book by Brett Glassner.
/// 
using namespace WBFL::Geometry;

Point2d PointOnExplicitNearest(Float64 C, const Vector2d& N, const Point2d& point);
std::pair<Float64,Vector2d> ExplicitToImplicit(const Point2d& U, const Vector2d& rV);
std::pair<Point2d,Vector2d> ImplicitToExplicit(Float64 C, const Vector2d& rN);
std::pair<Float64,Vector2d> PointToImplicit(const Point2d& rp1, const Point2d& rp2);


Line2d::Line2d():
m_N(Size2d(0.,1.)),
m_c(0)
{
   ASSERTVALID;
}

Line2d::Line2d(const Point2d& p1,const Point2d& p2)
{
   std::tie(m_c,m_N) = PointToImplicit(p1,p2);

   ASSERTVALID;
}

Line2d::Line2d(const LineSegment2d& ls)
{
   Line2d t(ls.GetStartPoint(), ls.GetEndPoint());
   *this = t;

   ASSERTVALID;
}

Line2d::Line2d(Float64 c, const Vector2d& rn):
m_c(c),
m_N(rn)
{
   m_N.Normalize();

   ASSERTVALID;
}

Line2d::Line2d(const Point2d& ru, const Vector2d& rv)
{
   std::tie(m_c,m_N) = ExplicitToImplicit(ru,rv);
   m_N.Normalize();

   ASSERTVALID;
}

Line2d::~Line2d()
{
   ASSERTVALID;
}

bool Line2d::operator==(const Line2d& other) const
{
   return (IsEqual(m_c, other.m_c) && (m_N == other.m_N));
}

bool Line2d::operator!=(const Line2d& other) const
{
   return !(*this == other);
}

bool Line2d::ContainsPoint(const Point2d& p,Float64 tolerance) const
{
   ASSERTVALID;

   Vector2d pv(p);
   return IsZero( m_N.Dot(pv) - m_c, tolerance);

}

Float64 Line2d::GetSlope() const
{
   ASSERTVALID;

   Vector2d t = m_N.Normal(Vector2d::Side::Right);
   if (t.X() == 0)
   {
	  constexpr Float64 infinity = std::numeric_limits<Float64>::infinity();

      if (t.Y() > 0)
         return infinity;
      else if (t.Y() < 0)
         return -infinity;
      else
         return 0;
   }
   else
      return tan(t.GetDirection());
}


bool Line2d::IsColinear(const Line2d& rOther) const
{
   if (m_N == rOther.m_N)
   {
      if (IsEqual(m_c, rOther.m_c))
         return true;
      else
         return false;
   }
   else
   {
      // check if N is reflected
      Vector2d r = -m_N;
      if (r == rOther.m_N)
      {
         if (IsEqual(m_c, -rOther.m_c))
            return true;
         else
            return false;
      }
      else
         return false;
   }
}

Line2d& Line2d::Offset(Float64 dx,Float64 dy)
{
   ASSERTVALID;

   Vector2d v(Size2d(dx,dy));
   Float64 pr = v.Projection(m_N);
   m_c += pr;

   ASSERTVALID;

   return *this;
}

Line2d& Line2d::Offset(const Size2d& size)
{
   Offset(size.Dx(), size.Dy());
   return *this;
}

Line2d& Line2d::Offset(Float64 offset)
{
   m_c += offset;
   return *this;
}

Line2d Line2d::OffsetBy(Float64 dx, Float64 dy) const
{
   Line2d t(*this);
   return t.Offset(dx, dy);
}

Line2d Line2d::OffsetBy(const Size2d& size) const
{
   return OffsetBy(size.Dx(), size.Dy());
}

Line2d Line2d::OffsetBy(Float64 offset) const
{
   Line2d t(*this);
   return t.Offset(offset);
}

Point2d Line2d::PointOnLineNearest(const Point2d& point) const
{
   ASSERTVALID;

   return PointOnExplicitNearest(m_c, m_N, point);
}

Float64 Line2d::DistanceToPoint(const Point2d& rPnt) const
{
   // this implementation may not be optimal, but it's the best
   // I can come up with for now.
   Point2d pl = PointOnLineNearest(rPnt);
   Float64 distance = pl.Distance(rPnt);
   Vector2d l2pvec(pl, rPnt);
   Float64 dot = m_N.Dot(l2pvec);

   if (dot < 0.)
      distance *= -1.0;

   return distance;
}


Line2d& Line2d::Rotate(const Point2d& centerPoint, Float64 angle)
{
   ASSERTVALID;

   auto [U,V] = ImplicitToExplicit(m_c, m_N);
   U.Rotate(centerPoint, angle);
   V.Rotate(angle);
   std::tie(m_c,m_N) = ExplicitToImplicit(U,V);

   ASSERTVALID;

   return *this;
}

Line2d Line2d::RotateBy(const Point2d& centerPoint, Float64 angle) const
{
   Line2d t(*this);
   return t.Rotate(centerPoint, angle);
}

Line2d Line2d::Parallel(Float64 offset, Line2d::Side side) const
{
   ASSERTVALID;

   Line2d t(*this);
   if (side==Side::Left)
      t.m_c += offset;
   else
      t.m_c -= offset;

   return t;
}

Line2d Line2d::Parallel(const Point2d& point) const
{
   ASSERTVALID;

   auto [U,V] = ImplicitToExplicit(m_c, m_N);
   // create a new point with explicit U at point
   Line2d t;
   U = point;
   std::tie(t.m_c,t.m_N) = ExplicitToImplicit(U,V);
   return t;
}

Line2d Line2d::Normal(const Point2d& point) const
{
   ASSERTVALID;

   Point2d q = PointOnLineNearest(point);
   if (q != point)
   {
      return Line2d(point, q);
   }
   else
   {
      auto [u,v] = ImplicitToExplicit(m_c,m_N);
      Vector2d direction = v.Normal(); // direct of line is normal to this line 
      return Line2d(point,direction);
   }
}

Line2d::Side Line2d::GetSide(const Point2d& point) const
{
   return DistanceToPoint(point) < 0 ? Side::Right : Side::Left;
}

void Line2d::Reverse()
{
   m_N.Reflect();
   m_c *= -1;
}

void Line2d::SetImplicit(Float64 c, const Vector2d& n)
{
   if (n.IsZero()) THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   m_c = c;
   m_N = n;
   m_N.Normalize();

   ASSERTVALID;
}

std::pair<Float64,Vector2d> Line2d::GetImplicit() const
{
   return std::make_pair(m_c, m_N);
}

void Line2d::SetExplicit(const Point2d& u, const Vector2d& v)
{
   if(v.IsZero()) THROW_GEOMETRY(WBFL_GEOMETRY_E_ZEROMAGNITUDE);

   std::tie(m_c,m_N) = ExplicitToImplicit(u, v);

   ASSERTVALID;
}

std::pair<Point2d,Vector2d> Line2d::GetExplicit() const
{
   ASSERTVALID;
   
   return ImplicitToExplicit(m_c, m_N);
}

void Line2d::ThroughPoints(const Point2d& p1,const Point2d& p2)
{
   std::tie(m_c,m_N) = PointToImplicit(p1,p2);

   ASSERTVALID;
}

std::pair<Float64, Vector2d> ExplicitToImplicit(const Point2d& U, const Vector2d& V)
{
   Vector2d n = V.NormalizeBy();
   auto N = n.Normal();
   Vector2d uv(U);
   auto C = N.Dot(uv);
   return std::make_pair(C, N);
}

std::pair<Point2d, Vector2d> ImplicitToExplicit(Float64 C, const Vector2d& N)
{
   Point2d origin(0, 0);
   auto U = PointOnExplicitNearest(C, N, origin);
   auto V = N.Normal(Vector2d::Side::Right);
   return std::make_pair(U, V);
}

Point2d PointOnExplicitNearest(Float64 C, const Vector2d& N, const Point2d& point)
{
   // don't need to normalize N since it already should be
   Vector2d vp(point);
   Float64 q = -C + N.Dot(vp);

   vp = N.ScaleBy(q);            // convert vector to a point
   Size2d tp(vp.X(), vp.Y());
   return point - tp;
}

std::pair<Float64, Vector2d> PointToImplicit(const Point2d& p1, const Point2d& p2)
{
   Size2d size = p2 - p1;
   if (size.Dx() == 0.0 && size.Dy() == 0.0)
   {
      // Not using IsZero() or p1 == p2 (becauses it uses IsZero/IsEqual)... 
      // we need to be forgiving about creating a line... the two points must
      // be exactly equal to throw this exception, not just close enough
      THROW_GEOMETRY(WBFL_GEOMETRY_E_COINCIDENTPOINTS);
   }
   else
   {
      Point2d  lu(p1);
      Vector2d lv(size);
      return ExplicitToImplicit(lu, lv);
   }
}

#if defined _DEBUG
bool Line2d::AssertValid() const
{
   return IsEqual(m_N.GetRelMagnitude(), 1.);
}
#endif // _DEBUG
