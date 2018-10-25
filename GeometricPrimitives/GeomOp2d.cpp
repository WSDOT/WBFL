///////////////////////////////////////////////////////////////////////
// Geometry - Modeling of geometric primitives
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
#include <GeometricPrimitives\GeomOp2d.h>

#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\Primitives3d.h>
#include <GeometricPrimitives\Vector2d.h>
#include <GeometricPrimitives\Vector3d.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\LineSegment2d.h>
#include <GeometricPrimitives\Circle.h>
#include <GeometricPrimitives\Arc.h>

#include <MathEx.h>
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gpGeomOp2d
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gpGeomOp2d::gpGeomOp2d()
{
}

gpGeomOp2d::~gpGeomOp2d()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Int16 gpGeomOp2d::Intersect(gpPoint2d* pPoint,
              const gpLineSegment2d& ls1,
              const gpLineSegment2d& ls2)
{
   // Check if either line segment has zero length
   bool bSeg1ZeroLength = IsZero( ls1.Length() );
   bool bSeg2ZeroLength = IsZero( ls2.Length() );
   if ( bSeg1ZeroLength && !bSeg2ZeroLength )
   {
      // Segment 1 is zero length, but segment 2 is not.
      // See if start point of segment 1 is on segment 2.
      if ( ls2.Contains( ls1.GetStartPoint() ) )
      {
         *pPoint = ls1.GetStartPoint();
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
      if ( ls1.Contains( ls2.GetStartPoint() ) )
      {
         *pPoint = ls2.GetStartPoint();
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
         *pPoint = ls1.GetStartPoint();
         return 1;
      }
      else
      {
         return 0;
      }
   }

   // Neither line segments are zero length
   // Convert to lines and make sure intersection point is in segments
   gpLine2d l1(ls1), l2(ls2);
   Int16 it = Intersect(pPoint, l1, l2);
   if (it == 1)
   {
      if(ls1.Contains(*pPoint) && ls2.Contains(*pPoint))
         return 1;
      else
         return 0;
   }
   else if (it==-1)
   {
      // lines are collinear - do they share points?
      gpPoint2d ls1s = ls1.GetStartPoint();
      gpPoint2d ls1e = ls1.GetEndPoint();
      if (ls2.Contains(ls1s))
      {
         *pPoint = ls1s;
         return -1;
      }
      else if (ls2.Contains(ls1e))
      {
         *pPoint = ls1e;
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

Int16 gpGeomOp2d::Intersect(gpPoint2d* pPoint,
              const gpLine2d& l,
              const gpLine2d& m)
{
   // Use method as outlined in Graphics Gems, page 11. Get explicit form of
   // l1 and implicit form of l2
   Float64    lc;
   gpVector2d ln;
   gpPoint2d  mu;
   gpVector2d mv;

   l.GetImplicit(&lc, &ln);
   m.GetExplicit(&mu, &mv);

   Float64 d = ln.Dot(mv);
   if (d!=0)
   {
      gpVector2d muv(gpSize2d(mu.X(),mu.Y()));      // must convert point to vector for Dot()
      Float64 f = ln.Dot(muv);
      f = (f - lc)/d;
      gpVector2d pv = muv - mv.SetMagnitude(f); // use temp vector to convert back to point
      pPoint->X() = pv.X();
      pPoint->Y() = pv.Y();
      return 1;
   }
   else
      // lines are parallel, either collinear or do not intersect.
   {
      if (l.IsCollinear(m))
         return -1;
      else
         return 0;
   }
}


Int16 gpGeomOp2d::Intersect(gpPoint2d* pPoint,
              const gpLineSegment2d& ls,
              const gpLine2d& l)
{
   if ( IsZero( ls.Length() ) )
   {
      if ( l.Contains( ls.GetStartPoint() ) )
      {
         *pPoint = ls.GetStartPoint();
         return 1;
      }
      else
      {
         return 0;
      }
   }

   gpLine2d l1(ls);
   Int16 it = Intersect(pPoint, l1, l);
   if (it == 1)
   {
      if(ls.Contains(*pPoint))
         return 1;
      else
         return 0;
   }
   else if (it==-1)
   {
      *pPoint = ls.GetStartPoint();
      return -1;
   }
   else
      return 0;

}

Int16 gpGeomOp2d::Intersect(gpPoint2d* pPoint,
              const gpLine2d& l,
              const gpLineSegment2d& ls)
{
   return Intersect(pPoint, ls, l);
}


Int16 gpGeomOp2d::Intersect(gpPoint2d* p1,gpPoint2d* p2,
                            const gpLine2d& l,
                            const gpCircle& c)
{
   // Quick check to see if the line and the circle have a chance of intersecting
   gpPoint2d center = c.GetCenter();
   gpPoint2d poln = l.PointOnLineNearest( center );
   Float64 radius = c.GetRadius();
   if ( poln.Distance(center) > radius )
      return 0; // Shorted dist to line is > radius.  They can't intersect

   Float64 slope = l.GetSlope();
   if ( slope == std::numeric_limits<Float64>::infinity() )
   {
      // Special case of a vertical line.
      Float64 dy = sqrt(radius*radius - pow(poln.X()-center.X(),2));
      p1->X() = poln.X();
      p1->Y() = center.Y() + dy;

      // Does the vertical line just touch the circle
      // Is there only one intersection?
      if ( IsEqual(radius,poln.Distance(center)) )
         return 1; // yes

      // No... There is two intersections

      p2->X() = poln.X();
      p2->Y() = center.Y() - dy;

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
      gpPoint2d origin;
      poln = l.PointOnLineNearest( origin );
      Float64 x,y;
      x = poln.X();
      y = poln.Y();
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

Int16 gpGeomOp2d::Intersect(gpPoint2d* p1,gpPoint2d* p2,
                            const gpLine2d& l,
                            const gpArc& arc)
{
   gpPoint2d ip1, ip2;
   Int16 nIntersect = Intersect(&ip1,&ip2,l,gpCircle(arc));
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

bool gpGeomOp2d::IsParallel(const gpLineSegment2d& ls1,
                const gpLineSegment2d& ls2)
{
   gpLine2d l1(ls1), l2(ls2);
   return IsParallel(l1, l2);
}

bool gpGeomOp2d::IsParallel(const gpLine2d& l1,
                const gpLine2d& l2)
{
   return (IsEqual(l1.GetSlope(), l2.GetSlope(), 1.0e-10));
}

bool gpGeomOp2d::IsParallel(const gpLineSegment2d& ls,
                const gpLine2d& l)
{
   gpLine2d l1(ls);
   return IsParallel(l1, l);
}

bool gpGeomOp2d::IsParallel(const gpLine2d& l,
                const gpLineSegment2d& ls)
{
   gpLine2d l1(ls);
   return IsParallel(l1, l);
}


void gpGeomOp2d::GenerateCircle(Int16 numPoints,
                                const gpPoint2d& center,
                                Float64 radius,
                                Float64 initAngle,
                                std::vector<gpPoint2d>* ppoints)
{
   Float64 delta_angle = TWO_PI / numPoints;
   GenerateCircle( center, radius, initAngle, delta_angle, ppoints );
}

void gpGeomOp2d::GenerateCircle(const gpPoint2d& center,
                                Float64 radius,
                                Float64 initAngle,
                                Float64 deltaAngle,
                                std::vector<gpPoint2d>* ppoints)
{
   PRECONDITION( radius > 0 );
   PRECONDITION( deltaAngle > 0 );

   ppoints->clear();
   Float64 cum_angle = 0;
   while ( cum_angle < TWO_PI )
   {
      gpPoint2d point;
      point.X() = center.X() + radius*cos( initAngle + cum_angle );
      point.Y() = center.Y() + radius*sin( initAngle + cum_angle );
      ppoints->push_back(point);
      cum_angle += deltaAngle;
   }
}

Float64 gpGeomOp2d::NormalizeAngle(Float64 angle)
{
   while ( angle < 0 )
      angle += TWO_PI;

   while ( angle >= TWO_PI )
      angle -= TWO_PI;

   CHECK( InRange(0.0,angle,TWO_PI) );

   return angle;
}

gpPoint3d gpGeomOp2d::GlobalToLocal(const gpPoint3d& origin,
                                    const gpVector3d& unitVector,
                                    Float64 angle,
                                    const gpPoint3d& point)
{
   gpVector3d v1, v2, v3, v4;
   gpVector3d vKnownSubvOrigin;
   gpVector3d vKnown(point);
   gpVector3d vOrigin(origin);
   Float64 nDot;

   vKnownSubvOrigin = vKnown - vOrigin;
   nDot = vKnownSubvOrigin.Dot(unitVector);
   v4 = unitVector.ScaleBy(nDot);

   v1 = v4.ScaleBy(1 - cos(angle));
   v2 = vKnownSubvOrigin.ScaleBy(cos(angle));

   gpVector3d cross = vKnownSubvOrigin.Cross(unitVector);
   v3 = cross.ScaleBy(sin(angle));

   v4       = v1 + v2;
   gpVector3d result = v4 + v3;
   return gpPoint3d(result.X(),result.Y(),result.Z());
}

gpPoint3d gpGeomOp2d::LocalToGlobal(const gpPoint3d& origin,
                                    const gpVector3d& unitVector,
                                    Float64 angle,
                                    const gpPoint3d& point)
{
   gpVector3d v1, v2, v3, v4, v5;
   Float64 KnownDotUnit;
   gpVector3d KnownCrossUnit;
   gpVector3d vKnown(point);

   KnownDotUnit = vKnown.Dot(unitVector);
   KnownCrossUnit = vKnown.Cross(unitVector);

   v1 = unitVector.ScaleBy(KnownDotUnit);
   v1.Scale(1-cos(angle));

   v2 = vKnown.ScaleBy(cos(angle));

   v3 = KnownCrossUnit.ScaleBy(sin(-1*angle));

   v4 = v1 + v2;
   v5 = v4 + v3;

   gpPoint3d result( gpPoint3d(v5.X(),v5.Y(),v5.Z()) + origin );
   return result;
}

gpPoint2d gpGeomOp2d::LocalToGlobal(const gpPoint2d& origin,
                                    Float64 angle,
                                    const gpPoint2d& local)
{
   gpPoint3d origin3d(origin.X(),origin.Y(),0.0);
   gpVector3d uv(0,0,1);
   gpPoint3d local3d(local.X(),local.Y(),0.0);
   gpPoint3d global3d = LocalToGlobal(origin3d,uv,angle,local3d);
   return gpPoint2d(global3d.X(),global3d.Y());
}

gpPoint2d gpGeomOp2d::GlobalToLocal(const gpPoint2d& origin,
                                    Float64 angle,
                                    const gpPoint2d& global)
{
   gpPoint3d origin3d(origin.X(),origin.Y(),0.0);
   gpVector3d uv(0,0,1);
   gpPoint3d global3d(global.X(),global.Y(),0.0);
   gpPoint3d local3d = GlobalToLocal(origin3d,uv,angle,global3d);
   return gpPoint2d(local3d.X(),local3d.Y());
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gpGeomOp2d::AssertValid() const
{
   return true;
}

void gpGeomOp2d::Dump(dbgDumpContext& os) const
{
   os << "Dump for gpGeomOp2d" << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

#if defined _UNITTEST

bool gpGeomOp2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gpGeomOp2d");

   gpPoint2d p1_7(1,7), pn3_3(-3,3), p0_4(0,4), p3_5(3,5),p6_6(6,6);
   gpPoint2d p8_0(8,0), p9_n1(9,-1), p5_n5(5,-5), p12_2(12,2);

   gpLine2d l1(pn3_3,p0_4), l2(p1_7,p8_0), l3(p5_n5,p12_2);
   gpLine2d ln2(p8_0,p1_7);

   gpLineSegment2d ls0(p1_7,p1_7), ls1(pn3_3,p0_4), ls2(p1_7,p9_n1),  ls3(p5_n5,p12_2);
   gpLineSegment2d ls4(p0_4,p6_6), ls5(pn3_3,p6_6), ls6(p3_5,p1_7);

   gpPoint2d pt;

   // intersect
   TRY_TESTME (1  == Intersect(&pt,l1,l2));
   TRY_TESTME (pt == p3_5);
   TRY_TESTME (1  == Intersect(&pt,l3,l2));
   TRY_TESTME (pt == p9_n1);
   TRY_TESTME (-1 == Intersect(&pt,l2,ln2));

   TRY_TESTME (1  == Intersect(&pt, ls4,ls2));
   TRY_TESTME (pt == p3_5);
   TRY_TESTME (1  == Intersect(&pt, ls2,ls3));
   TRY_TESTME (pt == p9_n1);
   TRY_TESTME (-1 == Intersect(&pt, ls1,ls4));
   TRY_TESTME (pt == p0_4);
   TRY_TESTME (0  == Intersect(&pt, ls4,ls3));
   TRY_TESTME (0  == Intersect(&pt, ls2,ls1));
   TRY_TESTME (0  == Intersect(&pt, ls0,ls1));

   // zero length line segment tests
   gpLineSegment2d ls7( 10, 50, 10, 100 );
   gpLine2d l4(ls7);
   gpLineSegment2d zls1( 10,10,10,10 );
   gpLineSegment2d zls2( 10,60,10,60 );
   gpLineSegment2d zls3( 10,10,10,10 );
   TRY_TESTME ( Intersect(&pt,ls7,zls1)  == 0 );
   TRY_TESTME ( Intersect(&pt,ls7,zls2)  == 1 && pt == gpPoint2d(10,60) );
   TRY_TESTME ( Intersect(&pt,zls1,zls3) == 1 && pt == gpPoint2d(10,10) );
   TRY_TESTME ( Intersect(&pt,l4,zls2)   == 1 && pt == gpPoint2d(10,60) );
   TRY_TESTME ( Intersect(&pt,zls2,l4)   == 1 && pt == gpPoint2d(10,60) );

   gpLineSegment2d ls8(25.6792,0.000,25.6792,-.0001);
   gpLineSegment2d ls9(25.6792,-0.000007,25.6792,-0.000007);
   TRY_TESTME ( Intersect(&pt,ls8,ls9) == 1 );

   // parallel
   TRY_TESTME (IsParallel(ls2,ls6));
   TRY_TESTME (IsParallel(ls1,ls4));
   TRY_TESTME (!IsParallel(ls1,ls3));
   TRY_TESTME (!IsParallel(ls1,ls0));

   // circle generation
   std::vector<gpPoint2d> points;
   GenerateCircle( 4, gpPoint2d(0,0), 10., 0., &points );
   TRY_TESTME( points.size() == 4 );
   TRY_TESTME( points[0] == gpPoint2d(10,0) );
   TRY_TESTME( points[1] == gpPoint2d(0,10) );
   TRY_TESTME( points[2] == gpPoint2d(-10,0) );
   TRY_TESTME( points[3] == gpPoint2d(0,-10) );

   // Normalize angle
   Float64 angle = 3*M_PI/4;
   TRY_TESTME( IsEqual( NormalizeAngle(    angle), angle ) );
   TRY_TESTME( IsEqual( NormalizeAngle(  5*TWO_PI + angle), angle ) );
   TRY_TESTME( IsEqual( NormalizeAngle( -5*TWO_PI + angle), angle ) );

   // Test Line Circle Intersection
   gpCircle circle(gpPoint2d(0,0),gpPoint2d(10,0));
   gpPoint2d p1, p2;
   Int16 nIntersect;

   // Line on horizontal diameter
   l1.SetPoints (gpPoint2d(0,0),gpPoint2d(10,0));
   nIntersect = Intersect(&p1,&p2,l1,circle);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME( p1 == gpPoint2d(0,0) );
   TRY_TESTME( p2 == gpPoint2d(10,0) );

   // Horizonal line at top of circle
   l1.SetPoints( gpPoint2d(0,5), gpPoint2d(5,5) );
   nIntersect = Intersect(&p1,&p2,l1,circle);
   TRY_TESTME(nIntersect == 1);
   TRY_TESTME( p1 == gpPoint2d(5,5) );

   // Vertical line on diameter
   l1.SetPoints( gpPoint2d(5,-5), gpPoint2d(5,5) );
   nIntersect = Intersect(&p1,&p2,l1,circle);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME( p1 == gpPoint2d(5,5) );
   TRY_TESTME( p2 == gpPoint2d(5,-5) );

   // Vertical line on right edge of circle
   l1.SetPoints( gpPoint2d(10,0), gpPoint2d(10,5) );
   nIntersect = Intersect(&p1,&p2,l1,circle);
   TRY_TESTME(nIntersect == 1);
   TRY_TESTME( p1 == gpPoint2d(10,0) );

   // 45 degree line through the origin
   l1.SetPoints( gpPoint2d(0,0), gpPoint2d(5,5) );
   nIntersect = Intersect(&p1,&p2,l1,circle);
   TRY_TESTME(nIntersect == 2);
   TRY_TESTME( p1 == gpPoint2d(0,0) );
   TRY_TESTME( p2 == gpPoint2d(5,5) );

   // Line that doesn't intersect
   l1.SetPoints( gpPoint2d(100,100), gpPoint2d(100,200) );
   nIntersect = Intersect(&p1,&p2,l1,circle);
   TRY_TESTME( nIntersect == 0 );

   TESTME_EPILOG("gpGeomOp2d");
}

#endif // _UNITTEST

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


