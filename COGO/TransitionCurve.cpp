///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TransitionCurve.cpp : Implementation of CTransitionCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "TransitionCurve.h"
#include "Angle.h"
#include "Direction.h"
#include <WBFLCogo\CogoHelpers.h>
#include <WBFLGeometry\GeomHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static Float64 tolerance = 0.1;

#define BACK_TANGENT    0x0001
#define TRANSITION_CURVE  0x0002
#define FORWARD_TANGENT 0x0004

// References
// 1) "Calculating coordinates along a clothoid between 2 curves", https://math.stackexchange.com/questions/1785816/calculating-coordinates-along-a-clothoid-betwen-2-curves
// 2) "How to calculate the length of a clothoid segment?", https://math.stackexchange.com/questions/3287710/how-to-calculate-length-of-clothoid-segment



/////////////////////////////////////////////////////////////////////////////
// CTransitionCurve
HRESULT CTransitionCurve::FinalConstruct()
{
   return S_OK;
}

void CTransitionCurve::FinalRelease()
{
}

void CTransitionCurve::Advise(IPoint2d* pnt,DWORD* pdwCookie)
{
   //CComPtr<IConnectionPointContainer> pCPC;
   //CComPtr<IConnectionPoint> pCP;
   //HRESULT hr;
   //hr = pnt->QueryInterface(&pCPC);
   //if ( FAILED(hr) )
   //{
   //   *pdwCookie = 0;
   //   return;
   //}

   //hr = pCPC->FindConnectionPoint(IID_IPoint2dEvents,&pCP);
   //if ( FAILED(hr) )
   //{
   //   *pdwCookie = 0;
   //   return;
   //}

   //pCP->Advise(GetUnknown(),pdwCookie);
   //
   //InternalRelease();
}

void CTransitionCurve::Unadvise(IPoint2d* pnt,DWORD* pdwCookie)
{
   //InternalAddRef();

   //CComPtr<IConnectionPointContainer> pCPC;
   //CComPtr<IConnectionPoint> pCP;
   //HRESULT hr;
   //hr = pnt->QueryInterface(&pCPC);
   //if ( FAILED(hr) )
   //{
   //   *pdwCookie = 0;
   //   return;
   //}

   //hr = pCPC->FindConnectionPoint(IID_IPoint2dEvents,&pCP);
   //if ( FAILED(hr) )
   //{
   //   *pdwCookie = 0;
   //   return;
   //}

   //pCP->Unadvise(*pdwCookie);
}

STDMETHODIMP CTransitionCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITransitionCurve,
		&IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// Determinate of
// | a b |
// | c d |
Float64 Det(Float64 a, Float64 b, Float64 c, Float64 d)
{
   return a*d - b*c;
}

HRESULT CTransitionCurve::Init(IPoint2d* pStartPoint, IDirection* pStartDirection, Float64 R1, Float64 R2, Float64 L,TransitionCurveType type)
{
   ATLASSERT(!IsEqual(R1,R2)); // both can't same number
   ATLASSERT(!IsZero(L)); // curve must have a length

   m_Type = type;

   // capture input values before we adjust them
   m_r1 = R1;
   m_r2 = R2;

   // zero means infinite radius.... set value to maximum possible vale
   R1 = IsZero(R1) ? Float64_Max : R1; 
   R2 = IsZero(R2) ? Float64_Max : R2;

   if (pStartPoint == nullptr)
   {
      if (m_StartPoint)
         m_StartPoint->Move(0, 0);
      else
         m_StartPoint.CoCreateInstance(CLSID_Point2d);
   }
   else
   {
      m_StartPoint = pStartPoint;
   }

   if (pStartDirection == nullptr)
   {
      if (m_StartDirection)
         m_StartDirection->put_Value(0.0);
      else
         m_StartDirection.CoCreateInstance(CLSID_Direction);
   }
   else
   {
      m_StartDirection = pStartDirection;
   }

   m_StartDirection->get_Value(&m_StartDirectionValue);

   m_R1 = fabs(R1);
   m_R2 = fabs(R2);

   m_Rs = Max(m_R1, m_R2);
   m_Re = Min(m_R1, m_R2);
   m_Sign = IsEqual(fabs(R1), m_Re) ? ::BinarySign(R1) : ::BinarySign(R2);

   m_L = L;

   Float64 a, b, delta;
   ATLASSERT(!IsZero(m_R1) && !IsZero(m_R2));

   m_SignY = (m_R1 < m_R2) ? -1.0 : 1.0;
   m_A = sqrt(L / (1 / m_Re - 1 / m_Rs)); // from reference 2

   Float64 t1 = m_A*m_A / (2 * pow(Min(m_Rs,m_Re),2));
   Float64 l1 = 2 * t1 * Min(m_Rs, m_Re);
   ATLASSERT(IsEqual(l1, sqrt(2 * m_A*m_A*t1)));

   Float64 t2 = m_A*m_A / (2 * pow(Max(m_Rs, m_Re), 2));
   Float64 l2 = 2 * t2 * Max(m_Rs, m_Re);
   ATLASSERT(IsEqual(l2, sqrt(2 * m_A*m_A*t2)));

   Float64 x_ = (m_R1 < m_R2) ? SpiralX(l1,t1) : SpiralX(l2, t2);
   Float64 y_ = (m_R1 < m_R2) ? SpiralY(l1,t1) : SpiralY(l2, t2);
   y_ *= m_Sign*m_SignY;

   // start of transition curve in global coordinates
   Float64 x, y;
   m_StartPoint->Location(&x, &y);

   delta = m_StartDirectionValue;
   if (m_R1 < m_R2)
   {
      Float64 angle = m_Sign * l1 / (2 * m_Re);
      delta += angle + M_PI;
   }


   // Find origin of curve coordinates in global space
   // Solve for a and b using Cramer's Rule
   // The coordinate transformation equations given in the source document (reference #1) is:
   // x_ = (x - a)cos(delta) - (y - b)sin(delta)
   // y_ = (x - a)sin(delta) + (y - b)cos(delta)
   // These equations are incorrect!!!
   // The correct coordinate transformation equations are:
   // x_ =  (x - a)cos(delta) + (y - b)sin(delta)
   // y_ = -(x - a)sin(delta) + (y - b)cos(delta)
   Float64 cos_delta = cos(delta);
   Float64 sin_delta = sin(delta);
   Float64 a1 = -cos_delta;
   Float64 a2 = sin_delta;
   Float64 b1 = -sin_delta;
   Float64 b2 = -cos_delta;
   Float64 c1 = x_ - ( x*cos_delta + y*sin_delta);
   Float64 c2 = y_ - (-x*sin_delta + y*cos_delta);


   Float64 Dx = Det(c1, b1, 
                    c2, b2);
   Float64 Dy = Det(a1, c1, 
                    a2, c2);
   Float64 D  = Det(a1, b1, 
                    a2, b2);
   a = Dx / D;
   b = Dy / D;

   m_StartDist = l2;
   m_Ls = L + m_StartDist;

   m_SpiralAngle = m_Ls / (2 * m_Re);

   // set up the local spiral coordiante system
   if(!m_SpiralOrigin)  m_SpiralOrigin.CoCreateInstance(CLSID_Point2d);
   m_SpiralOrigin->Move(a, b);
   m_SpiralRotation = delta;

   // Get the point and end direction
   m_EndPoint.Release();
   m_EndDirection.Release();
   PointOnCurve(m_L, &m_EndPoint);
   Bearing(m_L, &m_EndDirection);

   m_PI.Release();
   cogoUtil::IntersectBearings(m_StartPoint, CComVariant(m_StartDirection), 0.0, m_EndPoint, CComVariant(m_EndDirection), 0.0, &m_PI);

   Float64 d1, d2;
   m_StartPoint->DistanceEx(m_PI, &d1);
   m_EndPoint->DistanceEx(m_PI, &d2);
   m_U = Max(d1, d2); // long tangent
   m_V = Min(d1, d2); // short tangent

   return S_OK;
}

/////////////////////////////////////////////////////////////////
// ITransitionCurve
STDMETHODIMP CTransitionCurve::get_Type(TransitionCurveType* pType)
{
   CHECK_RETVAL(pType);
   *pType = m_Type;
   return S_OK;
}
STDMETHODIMP CTransitionCurve::get_R1(Float64* pR1)
{
   CHECK_RETVAL(pR1);
   *pR1 = m_r1;
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_R2(Float64* pR2)
{
   CHECK_RETVAL(pR2);
   *pR2 = m_r2;
   return S_OK;
}

STDMETHODIMP CTransitionCurve::GetRadius(Float64 distance, Float64* pRadius)
{
   CHECK_RETOBJ(pRadius);

   if (IsZero(distance))
   {
      // at start of curve, use original radius
      *pRadius = m_r1;
   }
   else if (IsEqual(distance, m_L))
   {
      // at end of curve, use original radius
      *pRadius = m_r2;
   }
   else
   {
      // Compute radius at distance from start
      // R*L = A^2  --> R = A^2/L
      *pRadius = m_A*m_A / distance;
   }

   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_X(Float64* x)
{
   CHECK_RETVAL(x);
   *x = SpiralX(m_L,m_SpiralAngle);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_Y(Float64* y)
{
   CHECK_RETVAL(y);
   *y = SpiralY(m_L,m_SpiralAngle);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_LongTangent(Float64* u)
{
    CHECK_RETVAL(u);
    *u = m_U;
    return S_OK;
}

STDMETHODIMP CTransitionCurve::get_ShortTangent(Float64* v)
{
    CHECK_RETVAL(v);
    *v = m_V;
    return S_OK;
}

STDMETHODIMP CTransitionCurve::get_PI(IPoint2d** pPI)
{
   CHECK_RETOBJ(pPI);
   return m_PI.CopyTo(pPI);
}

STDMETHODIMP CTransitionCurve::get_Angle(/*[out, retval]*/IAngle** ppAngle)
{
   return m_StartDirection->AngleBetween(m_EndDirection, ppAngle);
}

STDMETHODIMP CTransitionCurve::get_Direction(CurveDirectionType* dir)
{
   CHECK_RETVAL(dir);

   CComPtr<IAngle> angle;
   m_StartDirection->AngleBetween(m_EndDirection, &angle);

   Float64 delta;
   angle->get_Value(&delta);

   *dir = (delta > M_PI) ? cdRight : cdLeft;

   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_Start(/*[out, retval]*/IPoint2d** pStart)
{
   CHECK_RETOBJ(pStart);
   m_StartPoint.CopyTo(pStart);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_StartDirection(/*[out, retval]*/IDirection** pStartDirection)
{
   CHECK_RETOBJ(pStartDirection);
   m_StartDirection.CopyTo(pStartDirection);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_End(/*[out, retval]*/IPoint2d** pEnd)
{
   CHECK_RETOBJ(pEnd);
   m_EndPoint.CopyTo(pEnd);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_EndDirection(/*[out, retval]*/IDirection** pEndDirection)
{
   CHECK_RETOBJ(pEndDirection);
   m_EndDirection.CopyTo(pEndDirection);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_Length(/*[out, retval]*/Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_L;
   return S_OK;
}

STDMETHODIMP CTransitionCurve::PointOnCurve(Float64 distanceFromStart, IPoint2d** point)
{
   CHECK_RETOBJ(point);

   Float64 s = DistanceFromStartOfSpiral(distanceFromStart);

   Float64 sweepAngle = pow(s / m_Ls, 2) * m_SpiralAngle;

   Float64 x_ = SpiralX(s, sweepAngle);
   Float64 y_ = m_Sign*m_SignY*SpiralY(s, sweepAngle);

   CComPtr<IPoint2d> pnt;
    pnt.CoCreateInstance(CLSID_Point2d);
   pnt->Move(x_, y_);

   geomUtil::XformToOriginal(m_SpiralOrigin, m_SpiralRotation, pnt);

   pnt.CopyTo(point);
   return S_OK;
}

STDMETHODIMP CTransitionCurve::Bearing(Float64 distance, IDirection* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 s = DistanceFromStartOfSpiral(distance);
   Float64 sweepAngle = pow(s / m_Ls, 2) * m_SpiralAngle;
   if (m_R1 < m_R2)
   {
      sweepAngle -= m_SpiralAngle;
   }
   Float64 bearing = m_StartDirectionValue + m_Sign * m_SignY * sweepAngle;

   CComPtr<IDirection> direction;
   direction.CoCreateInstance(CLSID_Direction);
   direction->put_Value(bearing);

   direction.CopyTo(pVal);

   return S_OK;
}

STDMETHODIMP CTransitionCurve::Normal(Float64 distance, IDirection* *pVal)
{
   HRESULT hr = Bearing(distance, pVal);
   if (FAILED(hr))
      return hr;

   (*pVal)->IncrementBy(CComVariant(-PI_OVER_2));
   return S_OK;
}

STDMETHODIMP CTransitionCurve::ProjectPoint(IPoint2d* point, IPoint2d** pNewPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
{
   CHECK_IN(point);
   CHECK_RETVAL(pDistFromStart);
   CHECK_RETVAL(pvbOnProjection);
   CHECK_RETOBJ(pNewPoint);

   // determine if the point projects onto the entry spiral, circular curve, or exit spiral
   int projection_region = ProjectionRegion(point);

   *pNewPoint = nullptr;

   CComPtr<IPoint2d> bkTangentPoint;
   Float64 bkTangentOffset;
   Float64 bkTangentDistance;
   if (projection_region & BACK_TANGENT)
   {
      // point projects onto the back tangent

      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IPoint2d> pi;
      get_PI(&pi);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(m_StartPoint, pi);

      // compute offset from "point" to the back tangent (used to determine if it is closer to the back tangent than other points on the curve)
      geomUtil::PointOnLineNearest(line, point, &bkTangentPoint);
      point->DistanceEx(bkTangentPoint, &bkTangentOffset); // distance from the point to where it projects onto the back tangent

                                                           // compute distance along the back tangent to the projection point
      geomUtil::Distance(m_StartPoint, bkTangentPoint, &bkTangentDistance);
      bkTangentDistance *= -1;

      // deal with the case when the point is exactly at the start of the curve
      bkTangentDistance = IsZero(bkTangentDistance, 1e-9) ? 0.0 : bkTangentDistance;
   }


   CComPtr<IPoint2d> curvePoint;
   Float64 curveOffset;
   Float64 curveDistance;
   if (projection_region & TRANSITION_CURVE)
   {
      ProjectPoint(point, &curveDistance, &curvePoint);
      point->DistanceEx(curvePoint, &curveOffset);
   }

   CComPtr<IPoint2d> fwdTangentPoint;
   Float64 fwdTangentOffset;
   Float64 fwdTangentDistance;
   if (projection_region & FORWARD_TANGENT)
   {
      // point projects onto the forward tangent

      // Create a line object along the foward tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IPoint2d> pi;
      get_PI(&pi);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pi, m_EndPoint);

      geomUtil::PointOnLineNearest(line, point, &fwdTangentPoint);
      point->DistanceEx(fwdTangentPoint, &fwdTangentOffset); // distance from the point to where it projects onto the foward tangent

                                                             // compute distance along the forard tangent to the projection point
      geomUtil::Distance(m_EndPoint, fwdTangentPoint, &fwdTangentDistance);

      Float64 L; // length of curve
      get_Length(&L);

      // deal with case when point is exactly at the end of the curve
      if (IsZero(fwdTangentDistance))
         fwdTangentDistance = L;
      else
         fwdTangentDistance += L;
   }

   // find the projected point that is closest to the curve
   Float64 min_offset = Float64_Max;
   if (bkTangentPoint && bkTangentOffset < min_offset)
   {
      min_offset = bkTangentOffset;
      if (*pNewPoint) (*pNewPoint)->Release();
      bkTangentPoint.CopyTo(pNewPoint);
      *pDistFromStart = bkTangentDistance;
      *pvbOnProjection = VARIANT_TRUE;
   }

   if (curvePoint && curveOffset < min_offset)
   {
      min_offset = curveOffset;
      if (*pNewPoint) (*pNewPoint)->Release();
      curvePoint.CopyTo(pNewPoint);
      *pDistFromStart = curveDistance;
      *pvbOnProjection = VARIANT_FALSE;
   }

   if (fwdTangentPoint && fwdTangentOffset < min_offset)
   {
      min_offset = fwdTangentOffset;
      if (*pNewPoint) (*pNewPoint)->Release();
      fwdTangentPoint.CopyTo(pNewPoint);
      *pDistFromStart = fwdTangentDistance;
      *pvbOnProjection = VARIANT_TRUE;
   }

   return S_OK;
}

STDMETHODIMP CTransitionCurve::DistanceFromStart(IPoint2d* point, Float64* dist)
{
   CHECK_IN(point);
   CHECK_RETVAL(dist);

   CComPtr<IPoint2d> prjPoint;
   ProjectPoint(point, dist, &prjPoint);

   return S_OK;
}

STDMETHODIMP CTransitionCurve::Intersect(ILine2d* line, VARIANT_BOOL bProjectBack, VARIANT_BOOL bProjectAhead, IPoint2dCollection** points)
{
   CHECK_IN(line);
   CHECK_RETOBJ(points);

   if (*points == nullptr)
   {
      // if a point collection wasn't supplied, create one
      CComPtr<IPoint2dCollection> pntCollection;
      pntCollection.CoCreateInstance(CLSID_Point2dCollection);
      pntCollection.CopyTo(points);
   }

   CComPtr<IPoint2d> pntOnCurve;

   // when evaluated, this function returns the distance from the line to the curve
   // if the curve is to the left of the line the distance is negative
   CLineIntersectFunction function(this, line);
   WBFL::Math::BrentsRootFinder rootFinder;
   Float64 ya = function.Evaluate(m_StartDist);
   Float64 yb = function.Evaluate(m_Ls);
   if (0 < ya*yb)
   {
      // The end points don't bracket the solution....
      // Either the line doesn't intersect the spiral, it intersects it in two places
      // or it is tangent to the spiral

      // If the line intersects both the lines that are tangent to the spiral
      // then there is at least one intersection point
      CComPtr<IPoint2d> SPI;
      get_PI(&SPI);
      CComPtr<ILineSegment2d> seg1;
      seg1.CoCreateInstance(CLSID_LineSegment2d);
      seg1->ThroughPoints(m_StartPoint, SPI);
      CComPtr<IPoint2d> pnt1;
      geomUtil::IntersectLineWithLineSegment(line, seg1, &pnt1);

      CComPtr<ILineSegment2d> seg2;
      seg2.CoCreateInstance(CLSID_LineSegment2d);
      seg2->ThroughPoints(SPI, m_EndPoint);
      CComPtr<IPoint2d> pnt2;
      geomUtil::IntersectLineWithLineSegment(line, seg2, &pnt2);

      if (pnt1 && pnt2)
      {
         // there are at least 1 intersection point... 
         // need to find a disntace along the curve that is between the two intersection points
         // so we have a brack that works... to do this, search for a point on the spiral where
         // the tangent to the spiral is parallel to the line
         CParallelLineFunction parallel_function(this, line);
         Float64 limit;
         try
         {
            limit = rootFinder.FindRootInRange(parallel_function, m_StartDist, m_Ls, 0.0000001);
         }
         catch (WBFL::Math::XRootFinder& /*e*/)
         {
            ATLASSERT(false);
         }

         // if this location is on the intersecting line, the intersecting line
         // is tangent to the spiral
         CComPtr<IPoint2d> POC;
         PointOnCurve(limit, &POC);
         VARIANT_BOOL bContainsPoint;
         geomUtil::DoesLineContainPoint(line, POC, 0.001, &bContainsPoint);
         if (bContainsPoint == VARIANT_TRUE)
         {
            // Line is tangent
            (*points)->Add(POC);
            return S_OK; // with tangency, there is only one solution so just leave now
         }
         else
         {
            // Line is not tangent
            try
            {
               // get first insersection in first segment
               Float64 dist1 = rootFinder.FindRootInRange(function, m_StartDist, limit, 0.0001);
               CComPtr<IPoint2d> pnt;
               PointOnCurve(dist1, &pnt);
               ATLASSERT(TestIntersection(line, pnt));
               (*points)->Add(pnt);

               // get second interection in second segment
               pnt.Release();
               Float64 dist2 = rootFinder.FindRootInRange(function, limit, m_Ls, 0.0001);
               PointOnCurve(dist2, &pnt);
               ATLASSERT(TestIntersection(line, pnt));
               (*points)->Add(pnt);

               return S_OK; // we got both intersection points... leave now
            }
            catch (WBFL::Math::XRootFinder& /*mx*/)
            {
               ATLASSERT(false); // should never fire
            }
         }
      }
   }
   else
   {
      // find the single intersection point
      try
      {
         Float64 dist1 = rootFinder.FindRootInRange(function, m_StartDist, m_Ls, 0.0001);
         PointOnCurve(dist1, &pntOnCurve);
         ATLASSERT(TestIntersection(line, pntOnCurve));
         (*points)->Add(pntOnCurve);
      }
      catch (WBFL::Math::XRootFinder& /*mx*/)
      {
         ATLASSERT(false);
      }
   }

   // check intersection with back tangent
   CComPtr<IPoint2d> bkTangentPoint;
   if (bProjectBack == VARIANT_TRUE)
   {
       CComPtr<ILine2d> bkTangentLine;
       GetBkTangentLine(&bkTangentLine);
       geomUtil::LineLineIntersect(line, bkTangentLine, &bkTangentPoint);

       // if there was an intersection point and the point is before the start of the Start-SPI line
       // then this is an intersection on the back tangent projection 
       if (bkTangentPoint && cogoUtil::IsPointBeforeStart(m_StartPoint, m_PI, bkTangentPoint))
           (*points)->Add(bkTangentPoint);
   }

   // check intersection with forward tangent
   CComPtr<IPoint2d> fwdTangentPoint;
   if (bProjectAhead == VARIANT_TRUE)
   {
       CComPtr<ILine2d> fwdTangentLine;
       GetFwdTangentLine(&fwdTangentLine);
       geomUtil::LineLineIntersect(line, fwdTangentLine, &fwdTangentPoint);

       // if there was an intersection point and the point is after the end of the SPI-End line
       // then this is an intersection on the forward tangent projection 
       if (fwdTangentPoint && cogoUtil::IsPointAfterEnd(m_PI, m_EndPoint, fwdTangentPoint))
           (*points)->Add(fwdTangentPoint);
   }

   IndexType nPoints;
   (*points)->get_Count(&nPoints);
   if (nPoints == 0)
      return S_FALSE;

   return S_OK;
}

STDMETHODIMP CTransitionCurve::Move(Float64 dist, IDirection* direction)
{
   Float64 angle;
   direction->get_Value(&angle);
   Float64 dx, dy;
   dx = dist*cos(angle);
   dy = dist*sin(angle);
   return Offset(dx, dy);
}

STDMETHODIMP CTransitionCurve::Offset(Float64 dx,Float64 dy)
{
   m_StartPoint->Offset(dx, dy);
   m_EndPoint->Offset(dx, dy);

   m_PI->Offset(dx, dy);
   m_SpiralOrigin->Offset(dx, dy);

   return S_OK;
}

STDMETHODIMP CTransitionCurve::Clone(ITransitionCurve* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CTransitionCurve>* pClone;
   CComObject<CTransitionCurve>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->Init(m_StartPoint, m_StartDirection, m_r1, m_r2, m_L, m_Type);

   return S_OK;
}

STDMETHODIMP CTransitionCurve::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CTransitionCurve::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("TransitionCurve"),1.0);

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CTransitionCurve::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("TransitionCurve"));

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////////
// Helpers
Float64 CTransitionCurve::SpiralX(Float64 ls,Float64 angle)
{
   return ls*(1 -  pow(angle,2)/10 + pow(angle,4)/216 - pow(angle,6)/9360);
}

Float64 CTransitionCurve::SpiralY(Float64 ls,Float64 angle)
{
   return ls*(angle/3 - pow(angle,3)/42 + pow(angle,5)/1320 - pow(angle,7)/75600);
}

void CTransitionCurve::ProjectPoint(IPoint2d* point,Float64* pDistFromStart, IPoint2d* *pNewPoint)
{
   CSpiralFunction function(this,point);
   WBFL::Math::BrentsRootFinder rootFinder;
   Float64 dist = rootFinder.FindRootInRange(function, m_StartDist,m_Ls,0.00001); // dist from end
   PointOnCurve(dist,pNewPoint);
   *pDistFromStart = dist;
}

void CTransitionCurve::GetBkTangentLine(ILine2d** line)
{
   CComPtr<ILine2d> pLine;
   pLine.CoCreateInstance(CLSID_Line2d);

   Float64 direction;
   m_StartDirection->get_Value(&direction);
   CComPtr<IVector2d> vector;
   vector.CoCreateInstance(CLSID_Vector2d);
   vector->put_X(cos(direction));
   vector->put_Y(sin(direction));
   pLine->SetExplicit(m_StartPoint, vector);

   (*line) = pLine;
   (*line)->AddRef();
}

void CTransitionCurve::GetFwdTangentLine(ILine2d** line)
{
    CComPtr<ILine2d> pLine;
    pLine.CoCreateInstance(CLSID_Line2d);

    Float64 direction;
    m_EndDirection->get_Value(&direction);
    CComPtr<IVector2d> vector;
    vector.CoCreateInstance(CLSID_Vector2d);
    vector->put_X(cos(direction));
    vector->put_Y(sin(direction));
    pLine->SetExplicit(m_EndPoint, vector);

    (*line) = pLine;
    (*line)->AddRef();
}

bool CTransitionCurve::IsPointOnCurve(IPoint2d* pPoint)
{
   Float64 dist;
   HRESULT hr = DistanceFromStart(pPoint,&dist);
   ATLASSERT( SUCCEEDED(hr) );

   CComPtr<IPoint2d> pntOnCurve;
   hr = PointOnCurve(dist,&pntOnCurve);

   ATLASSERT( SUCCEEDED(hr) );

   pPoint->DistanceEx(pntOnCurve,&dist);
   return IsZero(dist,tolerance);
}

bool CTransitionCurve::IsPointOnLine(ILine2d* pLine,IPoint2d* pPoint)
{
   Float64 dist;
   geomUtil::ShortestDistanceToPoint(pLine,pPoint,&dist);
   return IsZero(dist,tolerance);
}

bool CTransitionCurve::TestIntersection(ILine2d* pLine,IPoint2d* pPoint)
{
   return IsPointOnCurve(pPoint) && IsPointOnLine(pLine,pPoint);
}

Float64 CTransitionCurve::DistanceFromStartOfSpiral(Float64 distance)
{
   // Adjust distance into distance from start (point of infinite radius) of spiral
   if (m_R1 < m_R2)
   {
      // infinite radius is towards the end of the spiral so
      // change distance to be from that end
      distance = m_Ls - distance;
   }
   else
   {
      distance += m_StartDist;
   }

   return distance;
}

int CTransitionCurve::ProjectionRegion(IPoint2d* pPoint)
{
   int result = 0;

   // check circular curve

   // put coordinate system at Start with X tangent to the curve
   Float64 startDir;
   m_StartDirection->get_Value(&startDir);

   CComPtr<IPoint2d> xfrmPoint;
   geomUtil::XformToNew(m_StartPoint, startDir, pPoint, &xfrmPoint);
   Float64 x1; // X ordinate in coordinate system 1
   xfrmPoint->get_X(&x1);

   // put coordinate system at End with X tangent to the curve
   Float64 endDir;
   m_EndDirection->get_Value(&endDir);

   xfrmPoint.Release();
   geomUtil::XformToNew(m_EndPoint, endDir, pPoint, &xfrmPoint);
   Float64 x2; // X ordinate in coordinate system 2
   xfrmPoint->get_X(&x2);

   if (x1 < 0)
      result |= BACK_TANGENT;

   if (0 < x2)
      result |= FORWARD_TANGENT;

   if (0 <= x1 && x2 <= 0)
      result |= TRANSITION_CURVE;

   return result;
}
