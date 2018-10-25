///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include <GeometricPrimitives\GeometryLib.h>
#include <GeometricPrimitives\Line2d.h>

#include <GeometricPrimitives\LineSegment2d.h>
#include <GeometricPrimitives\Primitives.h>
#include <MathEx.h>

#include <iostream>
#include <math.h>
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpLine2d
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////
gpPoint2d PointOnExplicitNearest(Float64 C, const gpVector2d& N, const gpPoint2d& point);
void ExplicitToImplicit(const gpPoint2d& U, const gpVector2d& rV, Float64* pC, gpVector2d* pN);
void ImplicitToExplicit(Float64 C, const gpVector2d& rN, gpPoint2d* U, gpVector2d* V);
void PointToImplicit(const gpPoint2d& rp1, const gpPoint2d& rp2, Float64* pc, gpVector2d* pv);


//======================== LIFECYCLE  =======================================
gpLine2d::gpLine2d():
m_N(gpSize2d(0.,1.)),
m_c(0)
{
   ASSERTVALID;
}

gpLine2d::gpLine2d(const gpPoint2d& p1,const gpPoint2d& p2)
{
   PointToImplicit(p1,p2,&m_c,&m_N);

   ASSERTVALID;
}

gpLine2d::gpLine2d(const gpLineSegment2d& ls)
{
   gpLine2d t(ls.GetStartPoint(), ls.GetEndPoint());
   *this = t;

   ASSERTVALID;
}

gpLine2d::gpLine2d(Float64 c, const gpVector2d& rn):
m_c(c),
m_N(rn)
{
   m_N.Normalize();

   ASSERTVALID;
}

gpLine2d::gpLine2d(const gpPoint2d& ru, const gpVector2d& rv)
{
   ExplicitToImplicit(ru,rv,&m_c,&m_N);
   m_N.Normalize();

   ASSERTVALID;
}

gpLine2d::gpLine2d(const gpLine2d& rOther)
{
   MakeCopy(rOther);

   ASSERTVALID;
}

gpLine2d::~gpLine2d()
{
   ASSERTVALID;
}

//======================== OPERATORS  =======================================
gpLine2d& gpLine2d::operator= (const gpLine2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   ASSERTVALID;

   return *this;
}

//======================== OPERATIONS =======================================

bool gpLine2d::Contains(const gpPoint2d& p) const
{
   ASSERTVALID;

   gpVector2d pv(p);
   return IsZero( m_N.Dot(pv) - m_c );

}

Float64 gpLine2d::GetSlope() const
{
   ASSERTVALID;

   gpVector2d t = m_N.Normal(gpVector2d::Right);
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


bool gpLine2d::IsCollinear(const gpLine2d& rOther) const
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
      gpVector2d r = -m_N;
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

gpLine2d& gpLine2d::Offset(Float64 dx,Float64 dy)
{
   ASSERTVALID;

   gpVector2d v(gpSize2d(dx,dy));
   Float64 pr = v.Projection(m_N);
   m_c += pr;

   ASSERTVALID;

   return *this;
}

gpLine2d& gpLine2d::Offset(const gpSize2d& size)
{
   Offset(size.Dx(), size.Dy());
   return *this;
}

gpLine2d gpLine2d::OffsetBy(Float64 dx, Float64 dy) const
{
   gpLine2d t(*this);
   return t.Offset(dx, dy);
}

gpLine2d gpLine2d::OffsetBy(const gpSize2d& size) const
{
   return OffsetBy(size.Dx(), size.Dy());
}


gpPoint2d gpLine2d::PointOnLineNearest(const gpPoint2d& point) const
{
   ASSERTVALID;

   return PointOnExplicitNearest(m_c, m_N, point);
}

Float64 gpLine2d::DistanceToPoint(const gpPoint2d& rPnt) const
{
   // this implementation may not be optimal, but it's the best
   // I can come up with for now.
   gpPoint2d pl = this->PointOnLineNearest(rPnt);
   Float64 distance = pl.Distance(rPnt);
   gpVector2d l2pvec(pl, rPnt);
   Float64 dir = m_N.Dot(l2pvec);

   if (dir<0.)
      distance = -distance;

   return distance;
}


gpLine2d& gpLine2d::Rotate(const gpPoint2d& centerPoint, Float64 angle)
{
   ASSERTVALID;

   gpPoint2d U;
   gpVector2d V;
   ImplicitToExplicit(m_c, m_N, &U, &V);
   U.Rotate(centerPoint, angle);
   V.Rotate(angle);
   ExplicitToImplicit(U,V,&m_c,&m_N);

   ASSERTVALID;

   return *this;
}

gpLine2d gpLine2d::RotateBy(const gpPoint2d& centerPoint, Float64 angle) const
{
   gpLine2d t(*this);
   return t.Rotate(centerPoint, angle);
}

gpLine2d gpLine2d::Parallel(Float64 offset, gpLine2d::Side side) const
{
   ASSERTVALID;

   gpLine2d t(*this);
   if (side==Left)
      t.m_c += offset;
   else
      t.m_c -= offset;

   return t;
}

gpLine2d gpLine2d::Parallel(const gpPoint2d& point) const
{
   ASSERTVALID;

   gpPoint2d U;
   gpVector2d V;
   ImplicitToExplicit(m_c, m_N, &U, &V);
   // create a new point with explicit U at point
   gpLine2d t;
   U = point;
   ExplicitToImplicit(U,V,&(t.m_c),&(t.m_N));
   return t;
}

gpLine2d gpLine2d::Normal(const gpPoint2d& point) const
{
   ASSERTVALID;

   gpPoint2d q = PointOnLineNearest(point);
   if (q != point)
      return gpLine2d(point, q);
   else
   {
      gpPoint2d u;
      gpVector2d v;
      ImplicitToExplicit(m_c,m_N,&u, &v);
      gpVector2d direction = v.Normal(); // direct of line is normal to this line 
      return gpLine2d(point,direction);
   }
}

gpLine2d::Side gpLine2d::GetSide(const gpPoint2d& point) const
{
   return DistanceToPoint(point) < 0 ? gpLine2d::Right : gpLine2d::Left;
}

void gpLine2d::Reverse()
{
   m_N.Reflect();
   m_c *= -1;
}

//======================== ACCESS     =======================================

void gpLine2d::SetImplicit(Float64 c, const gpVector2d& rn)
{
   m_c = c;
   m_N = rn;
   m_N.Normalize();

   ASSERTVALID;
}

void gpLine2d::GetImplicit(Float64* pc, gpVector2d* pn) const
{
   *pc = m_c;
   *pn = m_N;
}

void gpLine2d::SetExplicit(const gpPoint2d& ru, const gpVector2d& rv)
{
   ExplicitToImplicit(ru, rv, &m_c, &m_N);

   ASSERTVALID;
}

void gpLine2d::GetExplicit(gpPoint2d* pu, gpVector2d* pv) const
{
   ASSERTVALID;
   
   ImplicitToExplicit(m_c, m_N, pu, pv);
}

void gpLine2d::SetPoints(const gpPoint2d& p1,const gpPoint2d& p2)
{
   PointToImplicit(p1,p2,&m_c,&m_N);

   ASSERTVALID;
}


//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpLine2d::AssertValid() const
{
   return IsEqual( m_N.GetRelMagnitude(), 1. );
}

void gpLine2d::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for gpLine2d") << endl;
   os << _T("  m_c =") << m_c <<endl;
   os << _T("m_N = ");
   m_N.Dump(os);
}

#endif // _DEBUG

#if defined _UNITTEST

bool gpLine2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpLine2d");

   const gpPoint2d p0_0(0,0), p1_1(1,1), p0_1(0,1), p1_4(1,4), pn3_0(-3,0);
   const gpPoint2d p4_1(4,1), pn1_2(-1,2), pn1_0(-1,0);
   const gpLine2d up(p0_0, p0_1);
   const gpLine2d down(p0_1, p0_0), left(p0_1,p1_1);
   const gpLine2d at45(pn3_0,p1_4);
   const gpLine2d atn45(p1_4,pn3_0);
   gpLine2d ltemp1, ltemp2;

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
   ltemp1 = gpLine2d(p1_4, p4_1);
   val = ltemp1.GetSlope();
   TRY_TESTME ( IsEqual(val,-1.) );
   ltemp1 = gpLine2d(p0_0, pn1_0);
   val = ltemp1.GetSlope();
   TRY_TESTME ( IsEqual(val,0.) );

   // contains
   TRY_TESTME (at45.Contains(p1_4));
   TRY_TESTME (atn45.Contains(p1_4));
   TRY_TESTME (at45.Contains(pn1_2));
   TRY_TESTME (atn45.Contains(pn1_2));
   TRY_TESTME (up.Contains(gpPoint2d(0,456)));
   TRY_TESTME (up.Contains(gpPoint2d(0,-456)));
   TRY_TESTME (left.Contains(gpPoint2d(110,1)));
   TRY_TESTME (left.Contains(gpPoint2d(-110,1)));
         
   // point nearest on line
   gpPoint2d ptest = at45.PointOnLineNearest(p4_1);
   TRY_TESTME (ptest == p1_4);
   ptest = at45.PointOnLineNearest(pn1_2);
   TRY_TESTME (ptest == pn1_2);
   ptest = atn45.PointOnLineNearest(p4_1);
   TRY_TESTME (ptest == p1_4);
   ptest = up.PointOnLineNearest(p4_1);
   TRY_TESTME (ptest == gpPoint2d(0,1));

   // offset - offsetby
   ltemp1 = at45.OffsetBy(-1,0);
   ptest = ltemp1.PointOnLineNearest(p1_1);
   TRY_TESTME (ptest == gpPoint2d(-1,3));
   ltemp1 = at45.OffsetBy(1,0);
   ptest = ltemp1.PointOnLineNearest(p1_1);
   TRY_TESTME (ptest == gpPoint2d(0,2));
   ltemp1 = at45.OffsetBy(1,1);  // offset in direction of line
   TRY_TESTME (ltemp1 == at45);
   ltemp1 = up.OffsetBy(1,1);
   TRY_TESTME (ltemp1 == gpLine2d(gpPoint2d(1,0), gpPoint2d(1,1)));

   // Normal
   gpLine2d at315(p4_1, p1_4);
   ltemp1 = at45.Normal(p4_1);
   TRY_TESTME (ltemp1 == at315);
   ptest = ltemp1.PointOnLineNearest(pn3_0);
   TRY_TESTME (ptest == p1_4);
   ltemp2 = at45.Normal(p1_4);  // point on line
   TRY_TESTME (ltemp1 == at315);
   ltemp1 = up.Normal(p4_1);
   ptest = ltemp1.PointOnLineNearest(pn3_0);
   TRY_TESTME (ptest == gpPoint2d(-3,1));
   ltemp1 = left.Normal(pn1_2);
   ptest = ltemp1.PointOnLineNearest(pn3_0);
   TRY_TESTME (ptest == gpPoint2d(-1,0));

   // parallel
   ltemp1 = at45.Parallel(sqrt(2.), Left);
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-3,2)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-5,0)));
   ltemp2 = atn45.Parallel(sqrt(2.), Right);
   TRY_TESTME (ltemp2.Contains(gpPoint2d(-3,2)));
   TRY_TESTME (ltemp2.Contains(gpPoint2d(-5,0)));
   // lines are collinear but have different direction and are hence not equal
   TRY_TESTME (ltemp2 != ltemp1); 
   ltemp1 = at45.Parallel(1.5*sqrt(2.), Right);
   TRY_TESTME (ltemp1.Contains(gpPoint2d(0,0)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(2,2)));
   ltemp1 = up.Parallel(1, Left);
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-1,0)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-1,2)));
   ltemp1 = left.Parallel(2, Left);
   TRY_TESTME (ltemp1.Contains(gpPoint2d(0,3)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-1,3)));
   ltemp1 = at45.Parallel(gpPoint2d(-3,2));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-3,2)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-5,0)));
   ltemp1 = at45.Parallel(gpPoint2d(0,0));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(2,2)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-5,-5)));
   ltemp1 = down.Parallel(gpPoint2d(5,5));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(5,2)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(5,-5)));
   ltemp1 = left.Parallel(gpPoint2d(0,122));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(2,122)));
   TRY_TESTME (ltemp1.Contains(gpPoint2d(-5,122)));

   // rotate
   ltemp1 = left.RotateBy(gpPoint2d(-2,1),atan(1.));
   TRY_TESTME (ltemp1 == at45);
   ltemp1 = up.RotateBy(gpPoint2d(0,3),-atan(1.));
   TRY_TESTME (ltemp1 == at45);
   ltemp1 = left.RotateBy(gpPoint2d(-2,1),5*atan(1.));
   TRY_TESTME (ltemp1 == atn45);

   // explicit/implicit reps
   gpVector2d ve(gpSize2d(1,1)), ve2;
   gpPoint2d  pe(0,3), pe2;
   gpLine2d ex45(pe, ve);
   TRY_TESTME (ex45 == at45);
   ex45.GetExplicit(&pe,&ve);
   at45.GetExplicit(&pe2,&ve2);
   TRY_TESTME (ve == ve2 && pe == pe2);

   Float64 c1,c2;
   gpVector2d vi, vi2;
   ex45.GetImplicit(&c1,&vi);
   at45.GetImplicit(&c2,&vi2);
   TRY_TESTME (c1 == c2 && vi == vi2);

   // collinearity
   TRY_TESTME (at45.IsCollinear(at45));
   TRY_TESTME (atn45.IsCollinear(at45));
   TRY_TESTME (!at45.IsCollinear(up));

   // line segment constructor
   gpLineSegment2d sat45(pn3_0,p1_4);
   gpLine2d ssat45(sat45);
   TRY_TESTME (sat45 == at45);

   ltemp1.SetPoints(pn3_0, p1_4);
   TRY_TESTME (ltemp1 == at45);
   
#if defined _DEBUG
   at45.Dump(rlog.GetDumpCtx());
#endif

   TESTME_EPILOG("gpLine2d");
}

#endif // _UNITTEST


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gpLine2d::MakeCopy(const gpLine2d& rOther)
{
   m_c = rOther.m_c;
   m_N = rOther.m_N;
}

void gpLine2d::MakeAssignment(const gpLine2d& rOther)
{

   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void ExplicitToImplicit(const gpPoint2d& U, const gpVector2d& rV, Float64* pC, gpVector2d* pN)
{
   gpVector2d n = rV.NormalizeBy();
   *pN = n.Normal();
   gpVector2d uv(U);
   *pC = pN->Dot(uv);
}

void ImplicitToExplicit(Float64 C, const gpVector2d& rN, gpPoint2d* U, gpVector2d* V)
{
   gpPoint2d origin(0,0);
   *U = PointOnExplicitNearest(C, rN, origin);
   *V = rN.Normal(gpVector2d::Right);
}

gpPoint2d PointOnExplicitNearest(Float64 C, const gpVector2d& N, const gpPoint2d& point)
{
   // don't need to normalize N since it already should be
   gpVector2d vp(point);
   Float64 q = -C + N.Dot(vp);

   vp = N.ScaleBy(q);            // convert vector to a point
   gpSize2d tp(vp.X(), vp.Y());
   return point - tp;
}

void PointToImplicit(const gpPoint2d& rp1, const gpPoint2d& rp2, 
                     Float64* pc, gpVector2d* pn)
{
   if (rp1==rp2)
   {
      // can't make a line if endpoints are identical, but probably not
      // serious enough to throw an exception over.
      WARN(0,"Line endpoints are identical");
      pn->SetSize(gpSize2d(0, 1));
      *pc = 0;
   }
   else
   {
      gpPoint2d  lu(rp1);
      gpVector2d lv(gpSize2d(rp2.X()-rp1.X(),rp2.Y()-rp1.Y()));
      ExplicitToImplicit(lu, lv,pc, pn);
   }
}


//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

bool operator==(const gpLine2d& lhs, const gpLine2d& rhs)
{
   return (IsEqual(lhs.m_c,rhs.m_c) && (lhs.m_N==rhs.m_N));
}

bool operator!=(const gpLine2d& lhs, const gpLine2d& rhs)
{
   return !(lhs==rhs);
}




