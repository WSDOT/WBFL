///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2020  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// GeomHelper.cpp : Implementation of geomUtil
#include "stdafx.h"
#include <WBFLGeometry\GeomHelpers.h>

#include "GeomUtil.h"
#include "Helper.h"
#include "Vector2d.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static Float64 ms_Tolerance = 1.0e-6;
HRESULT geomUtil::GenerateCircle(IndexType numPoints, IPoint2d *center, Float64 radius, Float64 initAngle, IPoint2dCollection **points)
{
   if ( numPoints < 0 || numPoints == INVALID_INDEX || center == 0 || radius < 0 )
      return E_INVALIDARG;

   CHECK_RETOBJ(points);

   ::CreatePointCollection( points );

   Float64 delta_angle = TWO_PI / numPoints;
   ATLASSERT( radius > 0 );

   Float64 cx, cy;
   GetCoordinates( center, &cx, &cy );

   IndexType cPoints = 0;
   (*points)->Clear();
   Float64 cum_angle = 0;
   while ( cPoints++ < numPoints )
   {
      CComPtr<IPoint2d> pPoint;
      Float64 x,y;
      x = cx + radius*cos( initAngle + cum_angle );
      y = cy + radius*sin( initAngle + cum_angle );
      ::CreatePoint( x,y, &pPoint );
      (*points)->Add( pPoint );
      cum_angle += delta_angle;
   }

   return S_OK;
}

HRESULT geomUtil::Distance(IPoint2d *p1, IPoint2d *p2, Float64 *dist)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   return p1->DistanceEx(p2,dist);
}

HRESULT geomUtil::Magnitude(IPoint2d* pPoint,Float64* pMag)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pMag);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);
   *pMag = sqrt( x*x + y*y );

	return S_OK;
}

HRESULT geomUtil::Angle(IPoint2d* pStart,IPoint2d* pCenter,IPoint2d* pEnd,Float64* angle)
{
   CHECK_IN(pStart);
   CHECK_IN(pCenter);
   CHECK_IN(pEnd);
   CHECK_RETVAL(angle);

   Float64 sx, sy; // Start Point
   Float64 cx, cy; // Center Point
   Float64 ex, ey; // End Points
   Float64 dx1,dy1; // Delta x and y center to start point
   Float64 dx2,dy2; // Delta x and y center to end point

   pStart->get_X(&sx);
   pStart->get_Y(&sy);

   pCenter->get_X(&cx);
   pCenter->get_Y(&cy);

   pEnd->get_X(&ex);
   pEnd->get_Y(&ey);

   dx1 = sx - cx;
   dy1 = sy - cy;

   dx2 = ex - cx;
   dy2 = ey - cy;

   *angle = 0;

   if ( IsZero(dx1) && IsZero(dy1) || IsZero(dx2) && IsZero(dy2) )
      return GEOMETRY_E_SAMEPOINTS;

   Float64 angle1;
   angle1 = atan2(dy1,dx1);
   if ( IsZero(angle1) )
      angle1 = 0.00;
   else if ( angle1 < 0 )
      angle1 += TWO_PI;

   Float64 angle2;
   angle2 = atan2(dy2,dx2);
   if ( IsZero(angle2) )
      angle2 = 0.00;
   else if ( angle2 < 0 )
      angle2 += TWO_PI;

   (*angle) = angle2 - angle1;
   (*angle) = IsZero(*angle) ? 0.00 : (*angle);
   if ( (*angle) < 0.0 )
      (*angle) += TWO_PI;

   return S_OK;
}

HRESULT geomUtil::DoesLineSegmentContainPoint(ILineSegment2d* pSeg,IPoint2d* pPoint,Float64 tolerance,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pSeg);
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   // adopted implementation from unidraw's LineObj class and added tolerance. We might
   // want to consider having a global geometric tolerance for the geom package.
   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);
   Float64 x1,y1;
   Float64 x2,y2;
   GetCoordinates( pStart, &x1, &y1 );
   GetCoordinates( pEnd,   &x2, &y2 );

   Float64 x,y;
   GetCoordinates( pPoint, &x, &y );

   
	if ((x >= Min(x1, x2)-tolerance) && 
       (x <= Max(x1, x2)+tolerance) &&
	    (y >= Min(y1, y2)-tolerance) && 
       (y <= Max(y1, y2)+tolerance))
   {
      Float64 prod = (y - y1)*(x2 - x1) - (y2 - y1)*(x - x1);

      *pbResult = MakeBool(IsZero(prod,tolerance));
   }
   else
   {
      *pbResult = VARIANT_FALSE;
   }

   return S_OK;
}

HRESULT geomUtil::DivideLineSegment(ILineSegment2d* pSeg,IndexType nSpaces,IPoint2dCollection** ppPoints)
{
   CHECK_IN(pSeg);
   CHECK_RETOBJ(ppPoints);

   if ( nSpaces < 1 || nSpaces == INVALID_INDEX )
      return E_INVALIDARG;

   ::CreatePointCollection( ppPoints );

   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);
   Float64 x1,y1;
   Float64 x2,y2;
   GetCoordinates( pStart, &x1, &y1 );
   GetCoordinates( pEnd,   &x2, &y2 );
   Float64 dx = (x2 - x1)/nSpaces;
   Float64 dy = (y2 - y1)/nSpaces;

   CComPtr<IPoint2d> newStart;
   ::CreatePoint(pStart,&newStart);
   (*ppPoints)->Add(newStart);
   
   for ( IndexType i = 0; i < nSpaces - 1; i++ )
   {
      Float64 x,y;
      x = x1 + (i+1)*dx;
      y = y1 + (i+1)*dy;

      CComPtr<IPoint2d> pPoint;
      ::CreatePoint(x,y, &pPoint);

      (*ppPoints)->Add(pPoint);
   }

   CComPtr<IPoint2d> newEnd;
   ::CreatePoint(pEnd,&newEnd);
   (*ppPoints)->Add(newEnd);

   return S_OK;
}

HRESULT geomUtil::DivideArc(IPoint2d* pStart,IPoint2d* pCenter,IPoint2d* pEnd,IndexType nSpaces, IPoint2dCollection** ppPoints)
{
   CHECK_IN(pStart);
   CHECK_IN(pCenter);
   CHECK_IN(pEnd);
   CHECK_RETOBJ(ppPoints);

   if ( nSpaces < 1 || nSpaces == INVALID_INDEX )
      return E_INVALIDARG;

   ::CreatePointCollection(ppPoints);

   Float64 sx, sy; // Start Point
   Float64 cx, cy; // Center Point
   Float64 ex, ey; // End point
   Float64 radius; // Radius (measured center to start)
   Float64 dir;    // Direction of start vector measured from Y = 0 (+X)
   Float64 sweep_angle = 0;
   Float64 delta_angle = 0;

   pStart->get_X(&sx);
   pStart->get_Y(&sy);

   pCenter->get_X(&cx);
   pCenter->get_Y(&cy);

   pEnd->get_X(&ex);
   pEnd->get_Y(&ey);

   radius = sqrt( pow(sx-cx,2) + pow(sy-cy,2) );

   dir = atan2( sy-cy, sx-cx );

   Angle(pStart,pCenter,pEnd,&sweep_angle);
   delta_angle = sweep_angle / nSpaces;

   CComPtr<IPoint2d> newStart;
   ::CreatePoint(pStart,&newStart);
   (*ppPoints)->Add( newStart );

   for ( IndexType i = 0; i < nSpaces-1; i++ )
   {
      Float64 angle = dir + (i+1)*delta_angle;
      Float64 dx = radius * cos(angle);
      Float64 dy = radius * sin(angle);
      Float64 x = cx + dx;
      Float64 y = cy + dy;

      CComPtr<IPoint2d> pPoint;
      ::CreatePoint(x,y,&pPoint);

      (*ppPoints)->Add( pPoint );
   }

   CComPtr<IPoint2d> newEnd;
   ::CreatePoint(pEnd,&newEnd);
   (*ppPoints)->Add( newEnd );

   return S_OK;
}

HRESULT geomUtil::SegSegIntersect(ILineSegment2d* pSeg1,ILineSegment2d* pSeg2, IPoint2d** ppPoint)
{
   CHECK_IN(pSeg1);
   CHECK_IN(pSeg2);
   CHECK_RETOBJ(ppPoint); // ppPoint is now Nothing

   /////////////////////////////////////////////////////////////////
   // Check if either line segment has zero length
   Float64 l1,l2;
   pSeg1->get_Length(&l1);
   pSeg2->get_Length(&l2);
   bool bSeg1ZeroLength = IsZero(l1);
   bool bSeg2ZeroLength = IsZero(l2);

   if ( bSeg1ZeroLength && !bSeg2ZeroLength )
   {
      // Segment 1 is zero length, but segment 2 is not.
      // See if start point of segment 1 is on segment 2.
      VARIANT_BOOL bContains;
      CComPtr<IPoint2d> pStart;
      pSeg1->get_StartPoint(&pStart);
      DoesLineSegmentContainPoint(pSeg2,pStart,ms_Tolerance,&bContains);
      if ( bContains == VARIANT_TRUE )
      {
         ::CreatePoint( pStart, ppPoint );
         return S_OK;
      }
      else
      {
         // No intersect found
         // Indicate with Nothing point (see above)
         return S_FALSE;
      }
   }

   if ( !bSeg1ZeroLength && bSeg2ZeroLength )
   {
      // Segment 2 is zero length, but segment 1 is not.
      // See if start point of segment 2 is on segment 1.
      VARIANT_BOOL bContains;
      CComPtr<IPoint2d> pStart;
      pSeg2->get_StartPoint(&pStart);
      DoesLineSegmentContainPoint(pSeg1,pStart,ms_Tolerance,&bContains);
      if ( bContains == VARIANT_TRUE )
      {
         ::CreatePoint( pStart, ppPoint );
         return S_OK;
      }
      else
      {
         // No intersect found
         // Indicate with Nothing point (see above)
         return S_FALSE;
      }
   }

   if ( bSeg1ZeroLength && bSeg2ZeroLength )
   {
      // Both segment 1 and segment 2 are zero length.
      // See if their start points are the same
      CComPtr<IPoint2d> pStart1;
      CComPtr<IPoint2d> pStart2;
      pSeg1->get_StartPoint(&pStart1);
      pSeg2->get_StartPoint(&pStart2);
      if ( IsEqualPoint(pStart1,pStart2) )
      {
         ::CreatePoint( pStart1, ppPoint );
         return S_OK;
      }
      else
      {
         // No intersect found
         // Indicate with Nothing point (see above)
         return S_FALSE;
      }
   }

   // Neither line segments are zero length
   // Convert to lines and make sure intersection point is in segments
   CComPtr<ILine2d> pLine1;
   CComPtr<ILine2d> pLine2;
   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;

   pSeg1->get_StartPoint(&pStart);
   pSeg1->get_EndPoint(&pEnd);
   CreateLine(pStart,pEnd,&pLine1);

   pStart.Release();
   pEnd.Release();

   pSeg2->get_StartPoint(&pStart);
   pSeg2->get_EndPoint(&pEnd);
   CreateLine(pStart,pEnd,&pLine2);

   CComPtr<IPoint2d> pIntersect;
   LineLineIntersect(pLine1,pLine2,&pIntersect);
   if ( pIntersect )
   {
      // If the line segments intersect, both segments must contain the intersection point
      VARIANT_BOOL bContains1, bContains2;
      DoesLineSegmentContainPoint( pSeg1, pIntersect, ms_Tolerance, &bContains1 );
      DoesLineSegmentContainPoint( pSeg2, pIntersect, ms_Tolerance, &bContains2 );
      if ( bContains1 == VARIANT_TRUE && bContains2 == VARIANT_TRUE)
      {
         pIntersect->QueryInterface( ppPoint );
         return S_OK;
      }

      // No intersect found
      // Indicate with Nothing point (see above)
      return S_FALSE;
   }

   // No intersect found
   // Indicate with Nothing point (see above)
   return S_FALSE;
}

HRESULT geomUtil::LineLineIntersect(ILine2d* l, ILine2d *m, IPoint2d **ppPoint)
{
   CHECK_IN(l);
   CHECK_IN(m);
   CHECK_RETOBJ(ppPoint);

   // Use method as outlined in Graphics Gems, page 11. Get explicit form of
   // l1 and implicit form of l2
   Float64    lc;
   CComPtr<IVector2d> ln;
   CComPtr<IPoint2d>  mu;
   CComPtr<IVector2d> mv;

   l->GetImplicit(&lc, &ln);
   m->GetExplicit(&mu, &mv);

   Float64 d;
   ln->Dot(mv,&d);
   if ( d != 0 )
   {
      CComPtr<IVector2d> muv;
      CreateVector(mu,&muv);  // must convert point to vector for Dot()
      Float64 f;
      ln->Dot(muv,&f);
      f = (f - lc)/d;

      mv->put_Magnitude( fabs(f) );
      if ( f < 0 )
         mv->Reflect();

      Float64 x1,y1;
      Float64 x2,y2;
      GetCoordinates(muv,&x1,&y1);
      GetCoordinates(mv,&x2,&y2);
      
      ::CreatePoint(x1-x2,y1-y2,ppPoint);

      return S_OK;
   }
   else
   {
      // lines are parallel, collinear or do not intersect.
      // Indicate this by have the returned point be (in VB terms) Nothing
      if ( *ppPoint )
         (*ppPoint)->Release();

      (*ppPoint) = 0;

      return S_OK;
   }
}

HRESULT geomUtil::IntersectLineWithLineSegment(ILine2d* pLine,ILineSegment2d* pSeg,IPoint2d** ppPoint)
{
   CHECK_IN(pLine);
   CHECK_IN(pSeg);
   CHECK_RETOBJ(ppPoint); // Point is Nothing

   // Check if the line segment is zero length, if it is, check if the start/end point
   // is contained by the line. If it is, then consider it an intersection
   Float64 length;
   pSeg->get_Length(&length);
   if ( IsZero(length) )
   {
      CComPtr<IPoint2d> pStart;
      pSeg->get_StartPoint(&pStart);
      VARIANT_BOOL bContains;
      DoesLineContainPoint(pLine,pStart,ms_Tolerance,&bContains);
      if ( bContains == VARIANT_TRUE )
      {
         ::CreatePoint(pStart,ppPoint);
         return S_OK;
      }
      else
      {
         return S_FALSE; // Point is "Nothing" (See above)
      }
   }

   // Line segment has finite length
   // Create a temporary line from the segment and intersect it with the line
   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);
   CComPtr<ILine2d> pLine2;
   CreateLine(pStart,pEnd,&pLine2);
   CComPtr<IPoint2d> pIntersect;
   LineLineIntersect(pLine,pLine2,&pIntersect);
   if (pIntersect)
   {
      // Lines intersect, does the line segment contain it?
      VARIANT_BOOL bContains;
      DoesLineSegmentContainPoint(pSeg,pIntersect,ms_Tolerance,&bContains);
      if( bContains == VARIANT_TRUE )
      {
         pIntersect->QueryInterface(ppPoint);
         return S_OK;
      }
   }

   return S_FALSE;
}

HRESULT geomUtil::ShortestDistanceToPoint( ILine2d* pLine, IPoint2d* pPoint, Float64* pDist)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETVAL(pDist);

   // this implementation may not be optimal, but it's the best
   // I can come up with for now.
   CComPtr<IPoint2d> pPOLN;
   PointOnLineNearest(pLine,pPoint,&pPOLN);
   Float64 distance;
   Distance(pPoint,pPOLN,&distance);

   Float64 x1,y1;
   Float64 x2,y2;
   GetCoordinates(pPoint,&x1,&y1);
   GetCoordinates(pPOLN,&x2,&y2);

   CComObject<CVector2d>* pVector;
   CComObject<CVector2d>::CreateInstance(&pVector);
   CComPtr<IVector2d> vector = pVector;
   vector->put_X(x2-x1);
   vector->put_Y(y2-y1);

   Float64 c;
   CComPtr<IVector2d> pNormal;
   pLine->GetImplicit(&c,&pNormal);

   Float64 dot;
   pNormal->Dot(vector,&dot);

   if ( dot < 0 )
      distance *= -1.;

   *pDist = distance;

   return S_OK;
}

HRESULT geomUtil::IsLineParallelToLineSegment(ILine2d* pLine,ILineSegment2d* pSeg,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pLine);
   CHECK_IN(pSeg);
   CHECK_RETVAL(pbResult);

   CComPtr<ILine2d> pLine2;
   CreateLine(pSeg,&pLine2);
   return AreLinesParallel(pLine,pLine2,pbResult);
}

HRESULT geomUtil::AreLinesParallel(ILine2d* pLine1,ILine2d* pLine2,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pLine1);
   CHECK_IN(pLine2);
   CHECK_RETVAL(pbResult);

   CComVariant varP;
   CComVariant varDir1;
   CComVariant varDir2;
   
   CComPtr<IVector2d> pDir1;
   CComPtr<IVector2d> pDir2;
   CComPtr<IPoint2d> p;
   pLine1->GetExplicit(&p, &pDir1);
   p.Release();
   pLine2->GetExplicit(&p, &pDir2);

   pDir1->Normalize();
   pDir2->Normalize();

   Float64 x1,y1;
   Float64 x2,y2;
   GetCoordinates(pDir1,&x1,&y1);
   GetCoordinates(pDir2,&x2,&y2);

   *pbResult = MakeBool(IsEqual(x1,x2) && IsEqual(y1,y2));

   return S_OK;
}

HRESULT geomUtil::AreLineSegmentsParallel(ILineSegment2d* pSeg1,ILineSegment2d* pSeg2,VARIANT_BOOL* pbResult)
{
   CHECK_IN(pSeg1);
   CHECK_IN(pSeg2);
   CHECK_RETVAL(pbResult);

   CComPtr<ILine2d> pLine1;
   CComPtr<ILine2d> pLine2;

   CreateLine(pSeg1,&pLine1);
   CreateLine(pSeg2,&pLine2);

   AreLinesParallel(pLine1,pLine2,pbResult);

   return S_OK;
}

HRESULT geomUtil::CreateParallelLine(ILine2d* pLine,Float64 dist, ILine2d** ppLine)
{
   CHECK_IN(pLine);
   CHECK_RETOBJ(ppLine);

   CComPtr<IVector2d> pNormal;
   Float64 c;
   pLine->GetImplicit(&c,&pNormal);

   c -= dist;

   ::CreateLine(ppLine);
   (*ppLine)->SetImplicit(c,pNormal);

   return S_OK;
}

HRESULT geomUtil::CreateParallelLineThroughPoint(ILine2d* pLine,IPoint2d* pPoint, ILine2d** ppLine)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETOBJ(ppLine);

   CComPtr<IPoint2d> pU;
   CComPtr<IVector2d> pDir;

   pLine->GetExplicit(&pU,&pDir);

   ::CreateLine(ppLine);
   (*ppLine)->SetExplicit(pPoint,pDir);

   return S_OK;
}

HRESULT geomUtil::PointOnLineNearest(ILine2d* pLine,IPoint2d* pPoint, IPoint2d** ppPOLN)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETOBJ(ppPOLN);

   CComPtr<IVector2d> pN;
   Float64 C;
   pLine->GetImplicit(&C,&pN);

   pN->Normalize(); // N must be normalized for this calculation

   CComPtr<IVector2d> pV; // Turn pPoint int a vector
   CreateVector(pPoint,&pV);
   
   Float64 dot;
   pN->Dot(pV,&dot);

   Float64 q = dot - C;

   pN->Scale(q);
   Float64 xn,yn;
   GetCoordinates(pN,&xn,&yn);

   Float64 x,y;
   GetCoordinates(pPoint,&x,&y);

   ::CreatePoint(x-xn,y-yn,ppPOLN);

   return S_OK;
}

HRESULT geomUtil::CreateNormalLineThroughPoint(ILine2d* pLine, IPoint2d* pPoint, ILine2d** ppLine)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETOBJ(ppLine);

   CComPtr<IPoint2d> pPOLN;
   PointOnLineNearest(pLine,pPoint,&pPOLN);

   if ( !IsEqualPoint(pPoint,pPOLN) )
   {
      CreateLine(pPoint,pPOLN,ppLine);
   }
   else
   {
      CComPtr<IPoint2d> pU;
      CComPtr<IVector2d> pV;
      pLine->GetExplicit(&pU,&pV);
      
      CComPtr<IVector2d> pN;
      pV->Normal(&pN);

      ::CreateLine(ppLine);
      (*ppLine)->SetExplicit(pPoint,pN);
   }

   return S_OK;
}

HRESULT geomUtil::DoesLineContainPoint(ILine2d* pLine, IPoint2d* pPoint, Float64 tolerance, VARIANT_BOOL* pbResult)
{
   CHECK_IN(pLine);
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   CComPtr<IVector2d> pN;
   Float64 C;
   pLine->GetImplicit(&C,&pN);

   CComPtr<IVector2d> pV;
   CreateVector(pPoint,&pV);

   Float64 dot;
   pN->Dot(pV,&dot);

   *pbResult = MakeBool(IsZero(dot-C,tolerance));

   return S_OK;
}

HRESULT geomUtil::AreLinesColinear( ILine2d* pLine1, ILine2d* pLine2, VARIANT_BOOL* pbResult)
{
   CHECK_IN(pLine1);
   CHECK_IN(pLine2);
   CHECK_RETVAL(pbResult);

   CComVariant varC, varN;

   Float64 C1;
   CComPtr<IVector2d> pN1;
   pLine1->GetImplicit(&C1,&pN1);

   Float64 C2;
   CComPtr<IVector2d> pN2;
   pLine2->GetImplicit(&C2,&pN2);

   if (IsEqualVector(pN1, pN2))
   {
      *pbResult = MakeBool(IsEqual(C1, C2));
   }
   else
   {
      // Check if one vector is a reflection of the other
      pN1->Reflect();
      if ( IsEqualVector(pN1,pN2) )
         *pbResult = MakeBool( IsEqual(C1,-C2) );
      else
         *pbResult = VARIANT_FALSE;
   }

   return S_OK;
}

HRESULT geomUtil::CreateParallelLineSegment(ILineSegment2d* pSeg,Float64 offset, ILineSegment2d** pNewSeg)
{
   CHECK_IN(pSeg);
   CHECK_RETOBJ(pNewSeg);

   CComPtr<IPoint2d> pStart;
   CComPtr<IPoint2d> pEnd;
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);

   Float64 sx,sy;
   Float64 ex,ey;
   GetCoordinates(pStart,&sx,&sy);
   GetCoordinates(pEnd,  &ex,&ey);

   Float64 dx,dy;
   dx = ex - sx;
   dy = ey - sy;

   Float64 dir = atan2(dy,dx);

   Float64 ox =  offset*sin(dir);
   Float64 oy = -offset*cos(dir);

   ::CreateLineSegment(pNewSeg);
   CopyLineSegment(*pNewSeg,pSeg);
   (*pNewSeg)->Offset(ox,oy);

   return S_OK;
}

HRESULT geomUtil::LineCircleIntersect(ILine2d *line, ICircle *circle, IPoint2d** p1, IPoint2d** p2, short *nIntersect)
{
   CHECK_IN(line);
   CHECK_IN(circle);
   CHECK_RETOBJ(p1);
   CHECK_RETOBJ(p2);
   CHECK_RETVAL(nIntersect);

   // Quick check to see if the line and the circle have a chance of intersecting
   CComPtr<IPoint2d> pCenter;
   circle->get_Center( &pCenter );

   CComPtr<IPoint2d> poln;
   PointOnLineNearest( line, pCenter, &poln );

   Float64 radius;
   circle->get_Radius( &radius );

   Float64 dist;
   Distance( pCenter, poln, &dist );

   if ( radius < dist && !IsEqual(radius,dist) )
   {
      *nIntersect = 0;
      return S_OK;
   }

   CComPtr<IPoint2d> pnt;
   CComPtr<IVector2d> vector;
   line->GetExplicit( &pnt, &vector );

   CComPtr<ISize2d> size;
   vector->get_Size( &size );
   Float64 xp;
   poln->get_X(&xp);
   Float64 xc,yc;
   pCenter->get_X(&xc);
   pCenter->get_Y(&yc);
   Float64 dx,dy;
   size->get_Dx(&dx);
   size->get_Dy(&dy);

   // Check if the line is vertical
   if ( IsZero(dx) )
   {
      // Line is vertical
      Float64 K = sqrt(pow(radius,2) - pow(xp-xc,2));
      ::CreatePoint( xp, yc+K, p1 );

      // Does the vertical line just touch the circle?
      // Is there only one intersection?

      if ( IsEqual(radius,dist) )
      {
         *nIntersect = 1;
         return S_OK;
      }

      // No... there are two intersections
      ::CreatePoint( xp, yc-K, p2 );

      *nIntersect = 2;
      return S_OK;
   }
   else
   {
      Float64 slope = dy/dx;

      // determine the y-intercept of the line
      //
      // get any point on the line and solve y=mx+b
      // point on line nearest origin is just as good as the next point,
      // and it is easy to get.
      CComPtr<IPoint2d> origin;
      ::CreatePoint(0,0,&origin);
      poln.Release();
      PointOnLineNearest( line, origin, &poln );
      Float64 x,y;
      poln->get_X(&x);
      poln->get_Y(&y);
      Float64 b = y - slope*x;

      Float64 A = slope*slope + 1;
      Float64 B = 2*( slope*(b-yc) - xc);
      Float64 C = pow(xc,2) + pow(b-yc,2) - pow(radius,2);

      Float64 D = B*B - 4*A*C;
      D = (IsZero(D) ? 0 : D);
      ATLASSERT( D >= 0 );
      Float64 x1 = (-B - sqrt(D))/(2*A);
      Float64 x2 = (-B + sqrt(D))/(2*A);

      Float64 y1 = slope*x1 + b;
      Float64 y2 = slope*x2 + b;

      if ( IsEqual(x1,x2) && IsEqual(y1,y2) )
      {
         *nIntersect = 1;
         ::CreatePoint( x1, y1, p1);
         return S_OK;
      }
      else
      {
         *nIntersect = 2;
         ::CreatePoint( x1, y1, p1);
         ::CreatePoint( x2, y2, p2);
         return S_OK;
      }
   }

	return S_OK;
}

// Finds the intersection of two circles. A return value of 3 indicates the circles
// are identical and intersect at all points along the circle
HRESULT geomUtil::CircleCircleIntersect(ICircle* circle1,ICircle* circle2,IPoint2d** p1,IPoint2d** p2,short* nIntersect)
{
   CHECK_IN(circle1);
   CHECK_IN(circle2);
   CHECK_RETOBJ(p1);
   CHECK_RETOBJ(p2);
   CHECK_RETVAL(nIntersect);

   HRESULT hr = S_OK;

   Float64 A, B, C, D, K;
   Float64 cx1,cy1,cx2,cy2;
   Float64 r1, r2;

   // Initialize
   *nIntersect = 0;

   //
   // Get center and radius of both circles
   //
   CComPtr<IPoint2d> center1;
   circle1->get_Center(&center1);
   center1->get_X(&cx1);
   center1->get_Y(&cy1);
   circle1->get_Radius(&r1);

   CComPtr<IPoint2d> center2;
   circle2->get_Center(&center2);
   center2->get_X(&cx2);
   center2->get_Y(&cy2);
   circle2->get_Radius(&r2);

   // If the circles have the same center and the same radius, all points along the
   // circle intersect. Return the special value of 3. If the radii are different, there
   // are no intersection points
   if ( IsEqual(cx1,cx2) && IsEqual(cy1,cy2) )
   {
      // Center is the same
      if ( IsEqual(r1,r2) )
      {
         *nIntersect = 3;
         return S_OK;
      }
      else
      {
         *nIntersect = 0;
         return S_OK;
      }
   }


   // OK... do the regular intersection calculations

   // Compute some constants used in the solution of the quadratic equation
   K = (r1*r1 - r2*r2) - cx1*cx1 + cx2*cx2 - (cy2-cy1)*(cy2-cy1);

   A = -4*( (cx2-cx1)*(cx2-cx1) + (cy2-cy1)*(cy2-cy1) );
   B = 8*(cy2-cy1)*(cy2-cy1)*cx2 + 4*K*(cx2-cx1);
   C = 4*(cy2-cy1)*(cy2-cy1)*(r2*r2 - cx2*cx2) - K*K;
   D = B*B - 4*A*C; // Part of the Quadratic equation

   if ( D < 0 )
   {
      *nIntersect = 0;
      return S_OK;
   }

   CComPtr<IPoint2d> pnt1;
   pnt1.CoCreateInstance(CLSID_Point2d);
   pnt1.CopyTo(p1);

   CComPtr<IPoint2d> pnt2;
   pnt2.CoCreateInstance(CLSID_Point2d);
   pnt2.CopyTo(p2);

   //
   // Compute intersection points
   //
   Float64 x1, y1, y1a, y1b;
   Float64 x2, y2, y2a, y2b;
   Float64 d1, d2;

   x1  = (-B + sqrt(D))/(2*A);
   x2  = (-B - sqrt(D))/(2*A);

   y1a = cy1 + sqrt(r1*r1 - (x1-cx1)*(x1-cx1));
   y1b = cy1 - sqrt(r1*r1 - (x1-cx1)*(x1-cx1));

   if ( IsEqual(x1,x2) )
   {
      y1 = y1a;
      y2 = y1b;
   }
   else
   {
      // compute distance between center of circle2 and x1,y1a and
      // center of circle2 and x1,y1b. The one that equals the radius of circle2
      // is the correct Y
      d1 = (y1a-cy2)*(y1a-cy2) + (x1-cx2)*(x1-cx2);
      d2 = (y1b-cy2)*(y1b-cy2) + (x1-cx2)*(x1-cx2);
      if ( IsEqual(r2*r2,d1) )
         y1 = y1a;
      else
         y1 = y1b;

      y2a = cy2 - sqrt(r2*r2 - (x2-cx2)*(x2-cx2));
      y2b = cy2 + sqrt(r2*r2 - (x2-cx2)*(x2-cx2));

      // compute distance between center of circle1 and x2,y2a and
      // center of circle1 and x2,y2b. The one that equals the radius of circle1
      // is the correct Y
      d1 = (y2a-cy1)*(y2a-cy1) + (x2-cx1)*(x2-cx1);
      d2 = (y2b-cy1)*(y2b-cy1) + (x2-cx1)*(x2-cx1);
      if ( IsEqual(r1*r1,d1) )
         y2 = y2a;
      else
         y2 = y2b;
   }

   (*p1)->Move(x1,y1);
   (*p2)->Move(x2,y2);

   // Determine # of intersections
   *nIntersect = IsEqualPoint(*p1,*p2) ? 1 : 2;

   return S_OK;
}

HRESULT geomUtil::PointInTriangle(IPoint2d* p,IPoint2d* pA,IPoint2d* pB,IPoint2d* pC,VARIANT_BOOL* pbResult)
{
   // Use Barycentric Coordinate system
   // https://blogs.msdn.microsoft.com/rezanour/2011/08/07/barycentric-coordinates-and-point-in-triangle-tests/
   // http://blackpawn.com/texts/pointinpoly/default.html

   CHECK_IN(p);
   CHECK_IN(pA);
   CHECK_IN(pB);
   CHECK_IN(pC);
   CHECK_RETVAL(pbResult);

   Float64 Xa,Ya;
   pA->Location(&Xa,&Ya);

   Float64 Xb,Yb;
   pB->Location(&Xb,&Yb);

   Float64 Xc,Yc;
   pC->Location(&Xc,&Yc);

   Float64 Xp,Yp;
   p->Location(&Xp,&Yp);

   CComPtr<IVector2d> v0,v1,v2;
   v0.CoCreateInstance(CLSID_Vector2d);
   v1.CoCreateInstance(CLSID_Vector2d);
   v2.CoCreateInstance(CLSID_Vector2d);
   
   v0->put_X(Xc-Xa);
   v0->put_Y(Yc-Ya);

   v1->put_X(Xb-Xa);
   v1->put_Y(Yb-Ya);

   v2->put_X(Xp-Xa);
   v2->put_Y(Yp-Ya);

   Float64 dot00, dot01, dot02, dot11, dot12;
   v0->Dot(v0,&dot00);
   v0->Dot(v1,&dot01);
   v0->Dot(v2,&dot02);
   v1->Dot(v1,&dot11);
   v1->Dot(v2,&dot12);

   Float64 denom = dot00*dot11 - dot01*dot01;
   if ( denom == 0.0 )
   {
      return E_FAIL;
   }

   Float64 u = (dot11*dot02 - dot01*dot12)/denom;
   Float64 v = (dot00*dot12 - dot01*dot02)/denom;

   *pbResult = (0 <= u && 0 <= v && (u + v <= 1)) ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

////////////////// 3D /////////////////////
HRESULT geomUtil::Distance(IPoint3d* p1,IPoint3d* p2,Float64* pDist)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_RETVAL(pDist);

   Float64 x1,y1,z1;
   Float64 x2,y2,z2;
   GetCoordinates(p1,&x1,&y1,&z1);
   GetCoordinates(p2,&x2,&y2,&z2);

   *pDist = sqrt(pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2));

   return S_OK;
}

HRESULT geomUtil::Magnitude(IPoint3d* p,Float64 *pMag)
{
   CHECK_IN(p);
   CHECK_RETVAL(pMag);

   Float64 x,y,z;
   GetCoordinates(p,&x,&y,&z);
   *pMag = sqrt(x*x + y*y + z*z);
   return S_OK;
}

HRESULT geomUtil::PointInTriangle(IPoint3d* p,IPoint3d* pA,IPoint3d* pB,IPoint3d* pC,VARIANT_BOOL* pbResult)
{
   CHECK_IN(p);
   CHECK_IN(pA);
   CHECK_IN(pB);
   CHECK_IN(pC);
   CHECK_RETVAL(pbResult);

   Float64 Xa,Ya,Za;
   pA->Location(&Xa,&Ya,&Za);

   Float64 Xb,Yb,Zb;
   pB->Location(&Xb,&Yb,&Zb);

   Float64 Xc,Yc,Zc;
   pC->Location(&Xc,&Yc,&Zc);

   Float64 Xp,Yp,Zp;
   p->Location(&Xp,&Yp,&Zp);

   CComPtr<IVector3d> v0,v1,v2;
   v0.CoCreateInstance(CLSID_Vector3d);
   v1.CoCreateInstance(CLSID_Vector3d);
   v2.CoCreateInstance(CLSID_Vector3d);
   
   v0->put_X(Xc-Xa);
   v0->put_Y(Yc-Ya);
   v0->put_Z(Zc-Za);

   v1->put_X(Xb-Xa);
   v1->put_Y(Yb-Ya);
   v1->put_Z(Zb-Za);

   v2->put_X(Xp-Xa);
   v2->put_Y(Yp-Ya);
   v2->put_Z(Zp-Za);

   Float64 dot00, dot01, dot02, dot11, dot12;
   v0->Dot(v0,&dot00);
   v0->Dot(v1,&dot01);
   v0->Dot(v2,&dot02);
   v1->Dot(v1,&dot11);
   v1->Dot(v2,&dot12);

   Float64 denom = dot00*dot11 - dot01*dot01;
   if ( denom == 0.0 )
   {
      return E_FAIL;
   }

   Float64 u = (dot11*dot02 - dot01*dot12)/denom;
   Float64 v = (dot00*dot12 - dot01*dot02)/denom;

   *pbResult = (0 <= u && 0 <= v && (u + v <= 1)) ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

void geomUtil::XformToNew(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint)
{
   Float64 xo, yo;
   pOrigin->Location(&xo, &yo);

   Float64 x, y;
   pPoint->Location(&x, &y);

   Float64 cos_angle = cos(angle);
   Float64 sin_angle = sin(angle);

   Float64 x_ =  (x - xo)*cos_angle + (y - yo)*sin_angle;
   Float64 y_ = -(x - xo)*sin_angle + (y - yo)*cos_angle;

   pPoint->Move(x_, y_);
}

void geomUtil::XformToNew(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint, IPoint2d** ppPoint)
{
   pPoint->Clone(ppPoint);
   geomUtil::XformToNew(pOrigin, angle, *ppPoint);
}

void geomUtil::XformToOriginal(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint)
{
   Float64 xo, yo;
   pOrigin->Location(&xo, &yo);

   Float64 x_, y_;
   pPoint->Location(&x_, &y_);

   Float64 cos_angle = cos(angle);
   Float64 sin_angle = sin(angle);

   Float64 x = x_*cos_angle - y_*sin_angle + xo;
   Float64 y = x_*sin_angle + y_*cos_angle + yo;

   pPoint->Move(x, y);
}


void geomUtil::XformToOriginal(IPoint2d* pOrigin, Float64 angle, IPoint2d* pPoint, IPoint2d** ppPoint)
{
   pPoint->Clone(ppPoint);
   geomUtil::XformToOriginal(pOrigin, angle, *ppPoint);
}


std::shared_ptr<WBFL::Geometry::Point2d> geomUtil::GetInnerPoint(IPoint2d* pPoint)
{
   return ::GetInnerPoint(pPoint);
}

std::shared_ptr<WBFL::Geometry::Point3d> geomUtil::GetInnerPoint(IPoint3d* pPoint)
{
   return ::GetInnerPoint(pPoint);
}

HRESULT geomUtil::CreatePoint(std::shared_ptr<WBFL::Geometry::Point2d>& point, IPoint2d** ppPoint)
{
   return ::CreatePoint(point, ppPoint);
}

HRESULT geomUtil::CreatePoint(std::shared_ptr<WBFL::Geometry::Point3d>& point, IPoint3d** ppPoint)
{
   return ::CreatePoint(point, ppPoint);
}

WBFL::Geometry::Point2d geomUtil::GetPoint(IPoint2d* pPoint)
{
   return ::GetPoint(pPoint);
}

WBFL::Geometry::Point3d geomUtil::GetPoint(IPoint3d* pPoint)
{
   return ::GetPoint(pPoint);
}

WBFL::Geometry::Line2d geomUtil::GetLine(ILine2d* pLine)
{
   return ::GetLine(pLine);
}

WBFL::Geometry::LineSegment2d geomUtil::GetLineSegment(ILineSegment2d* pLineSegment)
{
   return ::GetLineSegment(pLineSegment);
}

WBFL::Geometry::Circle geomUtil::GetCircle(ICircle* pCircle)
{
   return ::GetCircle(pCircle);
}

WBFL::Geometry::Circle2d geomUtil::GetCircle2d(ICircle* pCircle)
{
   return ::GetCircle2d(pCircle);
}

HRESULT geomUtil::CreateLineSegment(const WBFL::Geometry::LineSegment2d& ls, ILineSegment2d** ppLineSegment)
{
   return ::CreateLineSegment(ls, ppLineSegment);
}

HRESULT geomUtil::CreateLine(const WBFL::Geometry::Line2d& line, ILine2d** ppLine)
{
   return ::CreateLine(line, ppLine);
}

HRESULT geomUtil::CreateLine(IPoint2d* pStart, IPoint2d* pEnd, ILine2d** ppLine)
{
   return ::CreateLine(pStart, pEnd, ppLine);
}

HRESULT geomUtil::CreateLine(ILineSegment2d* pSeg, ILine2d** ppLine)
{
   return ::CreateLine(pSeg, ppLine);
}

HRESULT geomUtil::CreatePointCollection(const std::vector<WBFL::Geometry::Point2d>& vPoints, IPoint2dCollection** ppPoints)
{
   return ::CreatePointCollection(vPoints, ppPoints);
}
