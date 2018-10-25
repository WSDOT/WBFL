///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Cogo\CogoLib.h>

/****************************************************************************
CLASS
   cogoEngine
****************************************************************************/

#include <Cogo\Engine.h>
#include <GeometricPrimitives\Line2d.h>
#include <GeometricPrimitives\GeomOp2d.h>
#include <MathEx.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void cogoEngine::Inverse(Float64* pDistance,
                         cogoDirection* pDirection,
                         const gpPoint2d& fromPoint,
                         const gpPoint2d& toPoint)
{
   PRECONDITION( pDistance  != 0 );
   PRECONDITION( pDirection != 0 );

   gpSize2d size = toPoint - fromPoint;
   *pDistance = size.Magnitude();

   Float64 angle = atan2( size.Dx(), size.Dy() );
   if (IsZero(angle))
      angle=0;
   else if ( angle < 0 )
      angle += TWO_PI;

   *pDirection = angle;
}

cogoAngle cogoEngine::ComputeAngle(const gpPoint2d& fromPnt,
                                   const gpPoint2d& vertex,
                                   const gpPoint2d& toPnt )
{
   Float64 dist;
   cogoDirection d1, d2;
   cogoEngine::Inverse( &dist, &d1, vertex, fromPnt );
   cogoEngine::Inverse( &dist, &d2, vertex, toPnt );

   return ( d2 - d1 );
}

Float64 cogoEngine::ComputeArea(const std::vector<gpPoint2d>& vPoints)
{
   Float64 area = 0;

   std::vector<gpPoint2d>::const_iterator begin = vPoints.begin();
   std::vector<gpPoint2d>::const_iterator end   = vPoints.end();

   const gpPoint2d* pPrevPoint = &(*begin++);
   do
   {
      Float64 At, Ar;

      const gpPoint2d* pPoint = &(*begin++);

      gpSize2d size = *pPoint - *pPrevPoint;

      Ar = size.Dx() * pPrevPoint->Y();
      At = 0.5 * size.Dx() * size.Dy();

      area += (Ar + At);

      pPrevPoint = pPoint;

   } while ( begin != end );

   if ( area < 0 )
      area *= -1;

   return area;
}


gpPoint2d cogoEngine::LocateByDistDir(const gpPoint2d& fromPoint,
                                      Float64 distance,
                                      const cogoDirection& direction)
{
   Float64 dx;
   Float64 dy;
   Float64 x;
   Float64 y;

   x = fromPoint.X();
   y = fromPoint.Y();

   dx = distance * sin( direction.AsFloat64() );
   dy = distance * cos( direction.AsFloat64() );

   return gpPoint2d( x + dx, y + dy );
} // LocatePoint

gpPoint2d cogoEngine::LocatePointOnLine(const gpPoint2d& fromPoint,
                                        const gpPoint2d& toPoint,
                                        Float64 distance)
{
   Float64 inverse_distance;
   cogoDirection direction;
   Float64 dx,dy;

   cogoEngine::Inverse( &inverse_distance, &direction, fromPoint, toPoint );

   dx = distance * sin( direction.AsFloat64() );
   dy = distance * cos( direction.AsFloat64() );


   return gpPoint2d( fromPoint.X() + dx, fromPoint.Y() + dy );
} // LocatePointOnLine

  
gpPoint2d cogoEngine::LocateByDistAngle(const gpPoint2d& fromPoint,
                                        const gpPoint2d& toPoint,
                                        Float64 distance,
                                        const cogoAngle& angle)
{
   cogoDirection direction;
   Float64 temp;
   cogoEngine::Inverse( &temp, &direction, toPoint, fromPoint );
   direction += angle;

   return cogoEngine::LocateByDistDir( toPoint, distance, direction );
}

gpPoint2d cogoEngine::LocateByDistDefAngle(const gpPoint2d& fromPoint,
                                           const gpPoint2d& toPoint,
                                           Float64 distance,
                                           const cogoAngle& angle)
{
   Float64 d;
   cogoDirection azimuth;
   cogoEngine::Inverse( &d, &azimuth, toPoint, fromPoint );

   azimuth += angle;

   Float64 x,y;
   x = toPoint.X() - distance * sin( azimuth.AsFloat64() );
   y = toPoint.Y() - distance * cos( azimuth.AsFloat64() );

   return gpPoint2d( x, y );
}

void cogoEngine::LocateParallelLine(gpPoint2d* pStart,
                                    gpPoint2d* pEnd,
                                    const gpPoint2d& p1,
                                    const gpPoint2d& p2,
                                    Float64 distance)
{
   PRECONDITION( pStart != 0 );
   PRECONDITION( pEnd   != 0 );

   Float64 temp;
   cogoDirection dir;
   cogoEngine::Inverse( &temp, &dir, p1, p2 );

   dir += cogoAngle( PI_OVER_2 );
   *pStart = cogoEngine::LocateByDistDir( p1, distance, dir );
   *pEnd   = cogoEngine::LocateByDistDir( p2, distance, dir );
}

gpPoint2d cogoEngine::ProjectPointOnLine(const gpPoint2d& fromPoint,
                                         const gpPoint2d& toPoint,
                                         Float64 offset,
                                         const gpPoint2d& projPoint)
{
   gpPoint2d p1, p2, p3;

   // Locate the offset line onto which the point will be projected.
   cogoEngine::LocateParallelLine( &p1, &p2, fromPoint, toPoint, offset );

   // Create a local coordinate system with (0,0) at p1 and the X-axis
   // running through p2. Let p3 be projPoint in that coordinate system
   Float64 dist;
   cogoDirection dir;
   cogoEngine::Inverse( &dist, &dir, p1, p2 );
   gpSize2d size = projPoint - p1;
   Float64 angle = PI_OVER_2 - dir.AsFloat64();

   p3.X() = ( size.Dx() ) * cos( -angle ) - ( size.Dy() ) * sin( -angle );
   p3.Y() = ( size.Dy() ) * cos( -angle ) + ( size.Dx() ) * sin( -angle );

   // In the transformed coordinate system, the project point p4 is at (p3.x,0)
   gpPoint2d p4(p3.X(), 0.00);

   // Transform p4 to the original coordinate system
   gpPoint2d p5;
   size = p4;
   p5.X() = ( size.Dx() ) * cos( angle ) - ( size.Dy() ) * sin( angle ) + p1.X();
   p5.Y() = ( size.Dy() ) * cos( angle ) + ( size.Dx() ) * sin( angle ) + p1.Y();

   // :TODO: Re-implement this method using the general purpose coordinate transforms
   //

   return p5;
}

bool cogoEngine::LineLineIntersect(gpPoint2d* pPoint,
                                   const gpPoint2d& pnt1a,const gpPoint2d& pnt1b,
                                   const gpPoint2d& pnt2a,const gpPoint2d& pnt2b)
{
   // use geometry routines to find intersection
   gpLine2d l1(pnt1a, pnt1b);
   gpLine2d l2(pnt2a, pnt2b);

   return gpGeomOp2d::Intersect(pPoint, l1, l2) == 1;
}

bool cogoEngine::LineLineIntersect(gpPoint2d* pNewPoint,
                                   const gpPoint2d& pnt1,const cogoDirection& d1,Float64 offset1,
                                   const gpPoint2d& pnt2,const cogoDirection& d2,Float64 offset2)
{
   PRECONDITION( pNewPoint != 0 );

   // If lines are parallel, then there is no one intersection point
   if ( d1 == d2 )
      return false;

   // Make adjustments for offsets
   gpPoint2d p1, p2; // Point on offset lines
   cogoDirection pd1, pd2; // direction of lines perpendicular to d1 an d2
   pd1 = d1.AsFloat64() - PI_OVER_2;
   pd2 = d2.AsFloat64() - PI_OVER_2;
   p1 = cogoEngine::LocateByDistDir( pnt1, offset1,  pd1 );
   p2 = cogoEngine::LocateByDistDir( pnt2, offset2,  pd2 );

   Float64 d1d = d1.AsFloat64();
   // Is the first line vertical
   if ( IsZero(d1d) || IsEqual(d1d, M_PI) || IsEqual(d1d, TWO_PI))
   {
      pNewPoint->X() = p1.X();

      // If this check fires, then the parallel line test above failed.
      CHECKX( d2 != 0. && d2 != M_PI, "d2 is parallel to d1");

      pNewPoint->Y() = (pNewPoint->X() - p2.X())/tan( d2.AsFloat64() ) + p2.Y();
      return true;
   }

   Float64 d2d = d2.AsFloat64();
   // Is the second line vertical
   if ( IsZero(d2d) || IsEqual(d2d, M_PI) || IsEqual(d2d, TWO_PI))
      {
      pNewPoint->X() = p2.X();
      pNewPoint->Y() = (pNewPoint->X() - p1.X())/tan( d1.AsFloat64() ) + p1.Y();
      return true;
      }

   // Neither line is vertical.
   Float64 m1, m2;
   Float64 b1, b2;
   if ( IsZero( d1.AsFloat64() ) )
      m1 = 0;
   else
      m1 = 1./tan( d1.AsFloat64() );

   if ( IsZero( d2.AsFloat64() ) )
      m2 = 0;
   else
      m2 = 1./tan( d2.AsFloat64() );

   b1 = p1.Y() - m1 * p1.X();
   b2 = p2.Y() - m2 * p2.X();
   pNewPoint->X() = ( b1 - b2 ) / ( m2 - m1 );
   pNewPoint->Y() = m1 * pNewPoint->X() + b1;

   CHECK( IsEqual( pNewPoint->Y(), m2 * pNewPoint->X() + b2 ) );

   return true;
}

std::vector<gpPoint2d> cogoEngine::DivideLine(const gpPoint2d& p1, const gpPoint2d& p2,Uint16 nParts)
{
   gpSize2d step_size = p2 - p1;
   step_size.Dx() /= nParts;
   step_size.Dy() /= nParts;

   std::vector<gpPoint2d> points;
   for ( Uint16 i = 1; i < nParts; i++ )
   {
      gpPoint2d pnt( p1.X() + step_size.Dx() * i,
                     p1.Y() + step_size.Dy() * i );
      points.push_back( pnt );
   }

   CHECK( points.size() == nParts-1 );

   return points;
}

std::vector<gpPoint2d> cogoEngine::DivideArc(const gpPoint2d& fromPnt, const gpPoint2d& vertex,const gpPoint2d& toPnt,Uint16 nParts)
{
   cogoAngle sweep_angle = cogoEngine::ComputeAngle( fromPnt, vertex, toPnt );
   sweep_angle.Normalize();
   sweep_angle /= nParts;

   Float64 radius;
   cogoDirection dir;
   cogoEngine::Inverse( &radius, &dir, vertex, fromPnt );
   
   cogoAngle angle( dir.AsFloat64() );
   std::vector<gpPoint2d> points;
   for ( Uint16 i = 1; i < nParts; i++ )
   {
      angle += sweep_angle;
      gpPoint2d p( vertex.X() + radius * sin( angle.AsFloat64() ),
                   vertex.Y() + radius * cos( angle.AsFloat64() ) );
      points.push_back( p );
   }

   CHECK( points.size() == nParts-1 );

   return points;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _UNITTEST
bool cogoEngine::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoEngine");
   TESTME_EPILOG("cogoEngine");
}
#endif // _UNITTEST
