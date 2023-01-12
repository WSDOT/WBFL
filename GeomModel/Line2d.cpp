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
#include <MathEx.h>

#include <iostream>
#include <math.h>
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// Line2d encapsulates the notion of a line with infinite length. The 
/// implementation for this is taken from Chapter 1 of the original
/// Graphics Gems book by Brett Glassner.
/// 
using namespace WBFL::Geometry;

Point2d PointOnExplicitNearest(Float64 C, const Vector2d& N, const Point2d& point);
void ExplicitToImplicit(const Point2d& U, const Vector2d& rV, Float64* C, Vector2d* N);
void ImplicitToExplicit(Float64 C, const Vector2d& rN, Point2d* U, Vector2d* V);
void PointToImplicit(const Point2d& rp1, const Point2d& rp2, Float64* c, Vector2d* v);


Line2d::Line2d():
m_N(Size2d(0.,1.)),
m_c(0)
{
   ASSERTVALID;
}

Line2d::Line2d(const Point2d& p1,const Point2d& p2)
{
   PointToImplicit(p1,p2,&m_c,&m_N);

   ASSERTVALID;
}

Line2d::Line2d(const LineSegment2d& ls)
{
   Line2d t(*ls.GetStartPoint(), *ls.GetEndPoint());
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
   ExplicitToImplicit(ru,rv,&m_c,&m_N);
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

bool Line2d::ContainsPoint(const Point2d& p) const
{
   ASSERTVALID;

   Vector2d pv(p);
   return IsZero( m_N.Dot(pv) - m_c);

}

Float64 Line2d::GetSlope() const
{
   ASSERTVALID;

   Vector2d t = m_N.Normal(Vector2d::Side::Right);
   if (t.X() == 0)
   {
	  Float64 infinity = std::numeric_limits<Float64>::infinity();

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

   Point2d U;
   Vector2d V;
   ImplicitToExplicit(m_c, m_N, &U, &V);
   U.Rotate(centerPoint, angle);
   V.Rotate(angle);
   ExplicitToImplicit(U,V,&m_c,&m_N);

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

   Point2d U;
   Vector2d V;
   ImplicitToExplicit(m_c, m_N, &U, &V);
   // create a new point with explicit U at point
   Line2d t;
   U = point;
   ExplicitToImplicit(U,V,&t.m_c,&t.m_N);
   return t;
}

Line2d Line2d::Normal(const Point2d& point) const
{
   ASSERTVALID;

   Point2d q = PointOnLineNearest(point);
   if (q != point)
      return Line2d(point, q);
   else
   {
      Point2d u;
      Vector2d v;
      ImplicitToExplicit(m_c,m_N,&u,&v);
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
   if (n.IsZero()) THROW_GEOMETRY(_T("Line2d::SetImplicit - normal vector has zero magnitude"));

   m_c = c;
   m_N = n;
   m_N.Normalize();

   ASSERTVALID;
}

void Line2d::GetImplicit(Float64* c, Vector2d* n) const
{
   *c = m_c;
   *n = m_N;
}

void Line2d::SetExplicit(const Point2d& u, const Vector2d& v)
{
   if(v.IsZero()) THROW_GEOMETRY(_T("Line2d::SetExplicit - direction vector has zero magnitude"));

   ExplicitToImplicit(u, v, &m_c, &m_N);

   ASSERTVALID;
}

void Line2d::GetExplicit(Point2d* u, Vector2d* v) const
{
   ASSERTVALID;
   
   ImplicitToExplicit(m_c, m_N, u, v);
}

void Line2d::ThroughPoints(const Point2d& p1,const Point2d& p2)
{
   if(p1 == p2) THROW_GEOMETRY(_T("Line2d::ThroughPoints - points are coincident"));

   PointToImplicit(p1,p2,&m_c,&m_N);

   ASSERTVALID;
}


#if defined _DEBUG
bool Line2d::AssertValid() const
{
   return IsEqual( m_N.GetRelMagnitude(), 1. );
}

void Line2d::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for Line2d") << WBFL::Debug::endl;
   os << _T("  m_c =") << m_c << WBFL::Debug::endl;
   os << _T("m_N = ");
   m_N.Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool Line2d::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Line2d");

   const Point2d p0_0(0,0), p1_1(1,1), p0_1(0,1), p1_4(1,4), pn3_0(-3,0);
   const Point2d p4_1(4,1), pn1_2(-1,2), pn1_0(-1,0);
   const Line2d up(p0_0, p0_1);
   const Line2d down(p0_1, p0_0), left(p0_1,p1_1);
   const Line2d at45(pn3_0,p1_4);
   const Line2d atn45(p1_4,pn3_0);
   Line2d ltemp1, ltemp2;

   Float64 infinity = std::numeric_limits<Float64>::infinity();

   // getslope
   Float64 val = up.GetSlope();
   TRY_TESTME (val == infinity);
   val = down.GetSlope();
   TRY_TESTME (val == -infinity);
   val = at45.GetSlope();
   TRY_TESTME ( IsEqual(val,1.) );
   val = atn45.GetSlope();
   TRY_TESTME ( IsEqual(val,1.) );
   ltemp1 = Line2d(p1_4, p4_1);
   val = ltemp1.GetSlope();
   TRY_TESTME ( IsEqual(val,-1.) );
   ltemp1 = Line2d(p0_0, pn1_0);
   val = ltemp1.GetSlope();
   TRY_TESTME ( IsEqual(val,0.) );

   // contains
   TRY_TESTME (at45.ContainsPoint(p1_4));
   TRY_TESTME (atn45.ContainsPoint(p1_4));
   TRY_TESTME (at45.ContainsPoint(pn1_2));
   TRY_TESTME (atn45.ContainsPoint(pn1_2));
   TRY_TESTME (up.ContainsPoint(Point2d(0,456)));
   TRY_TESTME (up.ContainsPoint(Point2d(0,-456)));
   TRY_TESTME (left.ContainsPoint(Point2d(110,1)));
   TRY_TESTME (left.ContainsPoint(Point2d(-110,1)));
         
   // point nearest on line
   Point2d ptest = at45.PointOnLineNearest(p4_1);
   TRY_TESTME (ptest == p1_4);
   ptest = at45.PointOnLineNearest(pn1_2);
   TRY_TESTME (ptest == pn1_2);
   ptest = atn45.PointOnLineNearest(p4_1);
   TRY_TESTME (ptest == p1_4);
   ptest = up.PointOnLineNearest(p4_1);
   TRY_TESTME (ptest == Point2d(0,1));

   // offset - offsetby
   ltemp1 = at45.OffsetBy(-1,0);
   ptest = ltemp1.PointOnLineNearest(p1_1);
   TRY_TESTME (ptest == Point2d(-1,3));
   ltemp1 = at45.OffsetBy(1,0);
   ptest = ltemp1.PointOnLineNearest(p1_1);
   TRY_TESTME (ptest == Point2d(0,2));
   ltemp1 = at45.OffsetBy(1,1);  // offset in direction of line
   TRY_TESTME (ltemp1 == at45);
   ltemp1 = up.OffsetBy(1,1);
   TRY_TESTME (ltemp1 == Line2d(Point2d(1,0), Point2d(1,1)));

   // Normal
   Line2d at315(p4_1, p1_4);
   ltemp1 = at45.Normal(p4_1);
   TRY_TESTME (ltemp1 == at315);
   ptest = ltemp1.PointOnLineNearest(pn3_0);
   TRY_TESTME (ptest == p1_4);
   ltemp2 = at45.Normal(p1_4);  // point on line
   TRY_TESTME (ltemp1 == at315);
   ltemp1 = up.Normal(p4_1);
   ptest = ltemp1.PointOnLineNearest(pn3_0);
   TRY_TESTME (ptest == Point2d(-3,1));
   ltemp1 = left.Normal(pn1_2);
   ptest = ltemp1.PointOnLineNearest(pn3_0);
   TRY_TESTME (ptest == Point2d(-1,0));

   // parallel
   ltemp1 = at45.Parallel(sqrt(2.), Side::Left);
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-3,2)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-5,0)));
   ltemp2 = atn45.Parallel(sqrt(2.), Side::Right);
   TRY_TESTME (ltemp2.ContainsPoint(Point2d(-3,2)));
   TRY_TESTME (ltemp2.ContainsPoint(Point2d(-5,0)));
   // lines are collinear but have different direction and are hence not equal
   TRY_TESTME (ltemp2 != ltemp1); 
   ltemp1 = at45.Parallel(1.5*sqrt(2.), Side::Right);
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(0,0)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(2,2)));
   ltemp1 = up.Parallel(1, Side::Left);
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-1,0)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-1,2)));
   ltemp1 = left.Parallel(2, Side::Left);
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(0,3)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-1,3)));
   ltemp1 = at45.Parallel(Point2d(-3,2));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-3,2)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-5,0)));
   ltemp1 = at45.Parallel(Point2d(0,0));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(2,2)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-5,-5)));
   ltemp1 = down.Parallel(Point2d(5,5));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(5,2)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(5,-5)));
   ltemp1 = left.Parallel(Point2d(0,122));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(2,122)));
   TRY_TESTME (ltemp1.ContainsPoint(Point2d(-5,122)));

   // rotate
   ltemp1 = left.RotateBy(Point2d(-2,1),atan(1.));
   TRY_TESTME (ltemp1 == at45);
   ltemp1 = up.RotateBy(Point2d(0,3),-atan(1.));
   TRY_TESTME (ltemp1 == at45);
   ltemp1 = left.RotateBy(Point2d(-2,1),5*atan(1.));
   TRY_TESTME (ltemp1 == atn45);

   // explicit/implicit reps
   Vector2d ve(Size2d(1,1)), ve2;
   Point2d  pe(0,3), pe2;
   Line2d ex45(pe, ve);
   TRY_TESTME (ex45 == at45);
   ex45.GetExplicit(&pe, &ve);
   at45.GetExplicit(&pe2, &ve2);
   TRY_TESTME (ve == ve2 && pe == pe2);

   Float64 c1,c2;
   Vector2d vi, vi2;
   ex45.GetImplicit(&c1, &vi);
   at45.GetImplicit(&c2, &vi2);
   TRY_TESTME (c1 == c2 && vi == vi2);

   // collinearity
   TRY_TESTME (at45.IsColinear(at45));
   TRY_TESTME (atn45.IsColinear(at45));
   TRY_TESTME (!at45.IsColinear(up));

   // line segment constructor
   Line2d lsat45(pn3_0, p1_4);
   LineSegment2d sat45(pn3_0,p1_4);
   Line2d ssat45(sat45);
   TRY_TESTME (lsat45 == ssat45);

   ltemp1.ThroughPoints(pn3_0, p1_4);
   TRY_TESTME (ltemp1 == at45);
   

   //
   // DoesLineContainPoint
   //
   Point2d p1(-10, -10);
   Point2d p2(-50, 20);
   Line2d l1(p1, p2);
   Point2d p3(-30, 5);
   Point2d p4(0, 0);
   TRY_TESTME(l1.ContainsPoint(p3));
   TRY_TESTME(!l1.ContainsPoint(p4));



   //
   // AreLinesColinear
   //
   p1.Move(5, 5);
   p2.Move(15, 15);
   p3.Move(25, 25);
   p4.Move(35, 35);

   Line2d line(p1, p2);
   Line2d line2(p3, p4);
   TRY_TESTME(line.IsColinear(line));
   TRY_TESTME(line.IsColinear(line2));
   TRY_TESTME(line2.IsColinear(line));

   line2.ThroughPoints(p4, p3); // Reverse l2
   TRY_TESTME(line.IsColinear(line2));

   p4.Move(3, 4);
   line2.ThroughPoints(p3, p4);
   TRY_TESTME(!line.IsColinear(line2));


#if defined _DEBUG
   at45.Dump(rlog.GetLogContext());
#endif

   TESTME_EPILOG("Line2d");
}

#endif // _UNITTEST


void ExplicitToImplicit(const Point2d& U, const Vector2d& V, Float64* C, Vector2d* N)
{
   Vector2d n = V.NormalizeBy();
   *N = n.Normal();
   Vector2d uv(U);
   *C = N->Dot(uv);
}

void ImplicitToExplicit(Float64 C, const Vector2d& N, Point2d* U, Vector2d* V)
{
   Point2d origin(0,0);
   *U = PointOnExplicitNearest(C, N, origin);
   *V = N.Normal(Vector2d::Side::Right);
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

void PointToImplicit(const Point2d& p1, const Point2d& p2, Float64* c, Vector2d* n)
{
   Size2d size = p2 - p1;
   if (size.Dx() == 0.0 && size.Dy() == 0.0)
   {
      // Not using IsZero() or p1 == p2 (becauses it uses IsZero/IsEqual)... 
      // we need to be forgiving about creating a line... the two points must
      // be exactly equal to throw this exception, not just close enough
      THROW_GEOMETRY(_T("Line2d - points are coincident"));
   }
   else
   {
      Point2d  lu(p1);
      Vector2d lv(size);
      ExplicitToImplicit(lu, lv, c, n);
   }
}



