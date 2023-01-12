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

// CircularCurve.cpp : Implementation of CCircularCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CircularCurve.h"
#include "Angle.h"
#include "Direction.h"
#include <WBFLCogo\CogoHelpers.h>
#include "PointFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static Float64 tolerance = 0.1;

#define BACK_TANGENT    0x0001
#define CIRCULAR_CURVE  0x0002
#define FORWARD_TANGENT 0x0004

/////////////////////////////////////////////////////////////////////////////
// CCircularCurve
HRESULT CCircularCurve::FinalConstruct()
{
   CComObject<CPointFactory>* pPF;
   CComObject<CPointFactory>::CreateInstance(&pPF);

   m_PointFactory = pPF;

   m_PointFactory->CreatePoint(&m_PBT);
   m_PointFactory->CreatePoint(&m_PI);
   m_PointFactory->CreatePoint(&m_PFT);

   m_PBT->Move(-1000,0);
   m_PI->Move(0,0);
   m_PFT->Move(1000,1000);

   Advise(m_PBT,&m_dwPBT);
   Advise(m_PI,&m_dwPI);
   Advise(m_PFT,&m_dwPFT);

   m_bHoldEvents = false;
   m_bPendingEvents = false;

   return S_OK;
}

void CCircularCurve::FinalRelease()
{
   Unadvise(m_PBT, &m_dwPBT);
   Unadvise(m_PI, &m_dwPI);
   Unadvise(m_PFT, &m_dwPFT);
}

void CCircularCurve::Advise(IPoint2d* pnt,DWORD* pdwCookie)
{
   CComPtr<IConnectionPointContainer> pCPC;
   CComPtr<IConnectionPoint> pCP;
   HRESULT hr;
   hr = pnt->QueryInterface(&pCPC);
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      return;
   }

   hr = pCPC->FindConnectionPoint(IID_IPoint2dEvents,&pCP);
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      return;
   }

   pCP->Advise(GetUnknown(),pdwCookie);
   
   InternalRelease();
}

void CCircularCurve::Unadvise(IPoint2d* pnt,DWORD* pdwCookie)
{
   InternalAddRef();

   CComPtr<IConnectionPointContainer> pCPC;
   CComPtr<IConnectionPoint> pCP;
   HRESULT hr;
   hr = pnt->QueryInterface(&pCPC);
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      return;
   }

   hr = pCPC->FindConnectionPoint(IID_IPoint2dEvents,&pCP);
   if ( FAILED(hr) )
   {
      *pdwCookie = 0;
      return;
   }

   pCP->Unadvise(*pdwCookie);
}

STDMETHODIMP CCircularCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICircularCurve,
		&IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCircularCurve::get_PBT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_PBT;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CCircularCurve::putref_PBT(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Unadvise(m_PBT,&m_dwPBT);
   m_PBT = newVal;
   OnPointChanged(m_PBT);
   Advise(m_PBT,&m_dwPBT);

   Fire_OnCircularCurveChanged(this);

	return S_OK;
}

STDMETHODIMP CCircularCurve::get_PI(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_PI;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CCircularCurve::putref_PI(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Unadvise(m_PI,&m_dwPI);
   m_PI = newVal;
   OnPointChanged(m_PI);
   Advise(m_PI,&m_dwPI);

   Fire_OnCircularCurveChanged(this);

	return S_OK;
}

STDMETHODIMP CCircularCurve::get_PFT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_PFT;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CCircularCurve::putref_PFT(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Unadvise(m_PFT,&m_dwPFT);
   m_PFT = newVal;
   OnPointChanged(m_PFT);
   Advise(m_PFT,&m_dwPFT);

   Fire_OnCircularCurveChanged(this);

	return S_OK;
}

STDMETHODIMP CCircularCurve::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Radius;
   return S_OK;
}

STDMETHODIMP CCircularCurve::put_Radius(Float64 newVal)
{
   if ( newVal <= 0 )
      return E_INVALIDARG;

   m_Radius = newVal;
   Fire_OnCircularCurveChanged(this);

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_PC(IPoint2d** pVal)
{
    CHECK_RETOBJ(pVal);
    if (m_PC == nullptr)
    {
        CComPtr<IDirection> bkTanBrg;
        get_BkTangentBrg(&bkTanBrg);
        bkTanBrg->IncrementBy(CComVariant(M_PI)); // reverse the bearing (PI to PBT)

        Float64 T;
        get_TangentLength(&T);

        cogoUtil::LocateByDistDir(m_PI, T, bkTanBrg, 0.0, m_PointFactory, &m_PC);
    }

    m_PC->Clone(pVal);
    return S_OK;
}

STDMETHODIMP CCircularCurve::get_PT(IPoint2d** pVal)
{
    CHECK_RETOBJ(pVal);

    if (m_PT == nullptr)
    {
        CComPtr<IDirection> fwdTanBrg;
        get_FwdTangentBrg(&fwdTanBrg);

        Float64 T;
        get_TangentLength(&T);

        cogoUtil::LocateByDistDir(m_PI, T, fwdTanBrg, 0.0, m_PointFactory, &m_PT);
    }

    m_PT->Clone(pVal);
    return S_OK;
}

STDMETHODIMP CCircularCurve::get_FwdTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   Float64 dist;
   cogoUtil::Inverse(m_PI,m_PFT,&dist,pVal);
	return S_OK;
}

STDMETHODIMP CCircularCurve::get_BkTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   Float64 dist;
   cogoUtil::Inverse(m_PBT,m_PI,&dist,pVal);
	return S_OK;
}

STDMETHODIMP CCircularCurve::get_Angle(IAngle* *pVal)
{
   // Total curve angle
   CHECK_RETOBJ(pVal);

   CComPtr<IDirection> fwdTangent;
   CComPtr<IDirection> bkTangent;
   get_FwdTangentBrg(&fwdTangent);
   get_BkTangentBrg(&bkTangent);

   Float64 dirFwd, dirBk;
   fwdTangent->get_Value(&dirFwd);
   bkTangent->get_Value(&dirBk);

   CurveDirectionType dir;
   get_Direction(&dir);

   Float64 angle;
   if ( dir == cdLeft )
      angle = dirFwd - dirBk;
   else
      angle = dirBk - dirFwd;

   if ( angle < 0 )
      angle += TWO_PI;

   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);
   pAngle->put_Value(angle);
   (*pVal) = pAngle;
   (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_TangentLength(Float64* t)
{
   CHECK_RETVAL(t);

    CComPtr<IAngle> a;
    get_Angle(&a);
    Float64 angle;
    a->get_Value(&angle);

    *t = m_Radius * tan(angle/2);

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_Chord(Float64* chord)
{
   CHECK_RETVAL(chord);
   CComPtr<IPoint2d> pc, pt;
   get_PC(&pc);
   get_PT(&pt);
   CComPtr<IDirection> dir;
   cogoUtil::Inverse(pc,pt,chord,&dir);
   return S_OK;
}


STDMETHODIMP CCircularCurve::get_Tangent(Float64* tangent)
{
   CHECK_RETVAL(tangent);
   CComPtr<IAngle> angle;
   HRESULT hr = get_Angle(&angle);
   if ( FAILED(hr) )
      return hr;

   Float64 val;
   angle->get_Value(&val);
   *tangent = m_Radius * tan(val/2);
   return S_OK;
}

STDMETHODIMP CCircularCurve::get_MidOrdinate(Float64* mo)
{
   CHECK_RETVAL(mo);
   CComPtr<IAngle> angle;
   HRESULT hr = get_Angle(&angle);
   if ( FAILED(hr) )
      return hr;

   Float64 val;
   angle->get_Value(&val);
   *mo = m_Radius * (1 - cos(val/2));

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_External(Float64* external)
{
   CHECK_RETVAL(external);
   CComPtr<IAngle> angle;
   HRESULT hr = get_Angle(&angle);
   if ( FAILED(hr) )
      return hr;

   Float64 val;
   angle->get_Value(&val);
   *external = m_Radius * (1/cos(val/2) - 1);

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_Center(IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);

   CComPtr<IPoint2d> PC;
   CComPtr<IPoint2d> PT;
   get_PC(&PC);
   get_PT(&PT);

   if (m_PI->SameLocation(PC) == S_OK || m_PI->SameLocation(PT) == S_OK)
   {
      // this curve is really just a point... CC is going to be at the same location
      // creating lines t1 and t2 will fail below.... just you the PI and the CC and return
      return m_PI->Clone(pVal);
   }

   CComPtr<ILine2d> t1, t2;
   t1.CoCreateInstance(CLSID_Line2d); // bk tangent (reversed)
   t2.CoCreateInstance(CLSID_Line2d); // fwd tangent (reversed)

   HRESULT hr;
   hr = t1->ThroughPoints(m_PI,PC);
   ATLASSERT(SUCCEEDED(hr));
   hr = t2->ThroughPoints(m_PI,PT);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<ILine2d> n1, n2;
   hr = geomUtil::CreateNormalLineThroughPoint(t1,PC,nullptr,&n1);
   ATLASSERT(SUCCEEDED(hr));
   hr = geomUtil::CreateNormalLineThroughPoint(t2,PT,nullptr,&n2);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IPoint2d> p;
   hr = geomUtil::LineLineIntersect(n1,n2,m_PointFactory,&p);
   ATLASSERT(SUCCEEDED(hr));

#if defined _DEBUG
   // intersect tangents... should intersect at PI
   CComPtr<IPoint2d> testPoint;
   hr = geomUtil::LineLineIntersect(t1,t2,m_PointFactory,&testPoint);
   ATLASSERT(SUCCEEDED(hr));
   Float64 x1,y1, x2,y2;
   m_PI->Location(&x1,&y1);
   testPoint->Location(&x2,&y2);
   ATLASSERT( IsEqual(x1,x2) && IsEqual(y1,y2) );

   // intersect forward tangent and its normal
   // should intersect at PC
   testPoint.Release();
   hr = geomUtil::LineLineIntersect(t1,n1,m_PointFactory,&testPoint);
   ATLASSERT(SUCCEEDED(hr));
   PC->Location(&x1,&y1);
   testPoint->Location(&x2,&y2);
   ATLASSERT( IsEqual(x1,x2) && IsEqual(y1,y2) );

   // intersect back tangent and its normal
   // should intersect at PT
   testPoint.Release();
   hr = geomUtil::LineLineIntersect(t2,n2,m_PointFactory,&testPoint);
   ATLASSERT(SUCCEEDED(hr));
   PT->Location(&x1,&y1);
   testPoint->Location(&x2,&y2);
   ATLASSERT( IsEqual(x1,x2) && IsEqual(y1,y2) );
#endif // _DEBUG

   p.QueryInterface(pVal);
   ATLASSERT( *pVal != nullptr );

	return S_OK;
}

STDMETHODIMP CCircularCurve::get_Direction(CurveDirectionType* dir)
{
   CHECK_RETVAL(dir);

   // Get Bk and Fwd Tangent Bearings
   CComPtr<IDirection> bkBrg, fwdBrg;
   get_BkTangentBrg(&bkBrg);
   get_FwdTangentBrg(&fwdBrg);

   CComPtr<IAngle> angle;
   fwdBrg->AngleBetween(bkBrg,&angle);

   Float64 delta;
   angle->get_Value(&delta);

   *dir = (delta > M_PI) ? cdRight : cdLeft;

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_Length(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IAngle> objAngle;
   HRESULT hr = get_Angle(&objAngle);
   if ( FAILED(hr) )
      return hr;

   Float64 angle;
   objAngle->get_Value(&angle);

   *pVal = m_Radius*angle;

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_DegreeCurvature(Float64 D,DegreeCurvatureType dcMethod,IAngle** pDC)
{
   CHECK_RETVAL(pDC);
   Float64 dc = 0;
   Float64 R;
   get_Radius(&R);
   if ( dcMethod == dcArc || dcMethod == dcHighway )
   {
      // degree of curvature = D/R
      dc = D/R;
   }
   else
   {
      // degree of curvature = 2*arcSin(D/2R)
      dc = 2*asin(D/(2*R));
   }

   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);
   pAngle->put_Value(dc);

   (*pDC) = pAngle;
   (*pDC)->AddRef();
   return S_OK;
}

STDMETHODIMP CCircularCurve::Bearing(Float64 distance,IDirection* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 L;
   HRESULT hr = get_Length(&L);
   if (FAILED(hr))
       return hr;

   if (distance <= 0)
   {
       // Before curve
       get_BkTangentBrg(pVal);
   }
   else if (L <= distance)
   {
       // After curve
       get_FwdTangentBrg(pVal);
   }
   else
   {
       // On curve
       CurveDirectionType dir;
       get_Direction(&dir);

       Float64 sign = (dir == cdLeft ? 1 : -1);

       Float64 sweepAngle = sign * distance / m_Radius;
       get_BkTangentBrg(pVal);
       (*pVal)->IncrementBy(CComVariant(sweepAngle));
   }

   return S_OK;
}

STDMETHODIMP CCircularCurve::Normal(Float64 distance,IDirection* *pVal)
{
   // CHECK_RETOBJ(pVal); // check in Bearing

   HRESULT hr = Bearing(distance,pVal);
   if ( FAILED(hr) )
      return hr;

   (*pVal)->IncrementBy(CComVariant(-PI_OVER_2));
   return S_OK;
}

STDMETHODIMP CCircularCurve::PointOnCurve(Float64 distance,IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 L;
   HRESULT hr = get_Length(&L);
   if (FAILED(hr))
       return hr;

   if (distance <= 0)
   {
       // Before curve
       CComPtr<IDirection> bkTanBrg;
       get_BkTangentBrg(&bkTanBrg);
       CComPtr<IPoint2d> pc;
       get_PC(&pc);
       cogoUtil::LocateByDistDir(pc, distance, bkTanBrg, 0.0, m_PointFactory, pVal);
   }
   else if (L <= distance)
   {
       // After curve
       CComPtr<IDirection> fwdTanBrg;
       get_FwdTangentBrg(&fwdTanBrg);
       CComPtr<IPoint2d> pt;
       get_PT(&pt);
       cogoUtil::LocateByDistDir(pt, distance - L, fwdTanBrg, 0.0, m_PointFactory, pVal);
   }
   else
   {
       // On curve

       CurveDirectionType dir;
       get_Direction(&dir);

       Float64 sign = (dir == cdLeft ? 1 : -1);

       // On curve
       Float64 sweepAngle = sign * distance / m_Radius;

       CComPtr<IPoint2d> pc; // start of circular curve
       get_PC(&pc);

       CComPtr<IPoint2d> center; // center of circular curve
       get_Center(&center);

       pc->RotateEx(center, sweepAngle);

       (*pVal) = pc;
       (*pVal)->AddRef();
   }

   return S_OK;
}

STDMETHODIMP CCircularCurve::ProjectPoint( IPoint2d* point, IPoint2d* *pNewPoint, Float64* pDistFromStart, VARIANT_BOOL* pvbOnProjection)
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
      CComPtr<IPoint2d> pbt, pi;
      get_PBT(&pbt);
      get_PI(&pi);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pbt, pi);

      // compute offset from "point" to the back tangent (used to determine if it is closer to the back tangent than other points on the curve)
      geomUtil::PointOnLineNearest(line, point, m_PointFactory, &bkTangentPoint);
      point->DistanceEx(bkTangentPoint, &bkTangentOffset); // distance from the point to where it projects onto the back tangent

                                                           // compute distance along the back tangent to the projection point
      CComPtr<IPoint2d> pc;
      get_PC(&pc);
      geomUtil::Distance(pc, bkTangentPoint, &bkTangentDistance);
      bkTangentDistance *= -1;

      // deal with the case when the point is exactly at the start of the curve
      bkTangentDistance = IsZero(bkTangentDistance, 1e-9) ? 0.0 : bkTangentDistance;
   }


   CComPtr<IPoint2d> curvePoint;
   Float64 curveOffset;
   Float64 curveDistance;
   if (projection_region & CIRCULAR_CURVE)
   {
      // Create a line from center through the projected point
      // Intersect this line with the circular arc, finding the
      // point that is nearest PC.
      CComPtr<IPoint2d> center;
      get_Center(&center);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(center, point);

      CComPtr<ICircle> circle;
      circle.CoCreateInstance(CLSID_Circle);
      circle->putref_Center(center);
      circle->put_Radius(m_Radius);

      CComPtr<IPoint2d> pc;
      get_PC(&pc);

      cogoUtil::LineCircleIntersect(line, circle, point, m_PointFactory, &curvePoint);
      ATLASSERT(curvePoint != nullptr);

      CurveDirectionType dir;
      get_Direction(&dir);
      Float64 angle;
      if (dir == cdRight)
         geomUtil::Angle(curvePoint, center, pc, &angle);
      else
         geomUtil::Angle(pc, center, curvePoint, &angle);

#if defined _DEBUG
      // The subtended angle must be less than or equal to the
      // circular curve angle (or the point isn't on the circular part of the curve)
      CComPtr<IAngle> cca;
      Float64 delta;
      get_Angle(&cca);
      cca->get_Value(&delta);
      ATLASSERT(IsLE(angle, delta));
#endif // _DEBUG

      ATLASSERT(0 <= angle);
      curveDistance = m_Radius * angle; // distance along circular curve to projected point
      point->DistanceEx(curvePoint, &curveOffset); // distance from the point to where it projects onto the circular curve
   }

   CComPtr<IPoint2d> fwdTangentPoint;
   Float64 fwdTangentOffset;
   Float64 fwdTangentDistance;
   if (projection_region & FORWARD_TANGENT)
   {
      // point projects onto the forward tangent

      // Create a line object along the foward tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IPoint2d> pi, pft;
      get_PI(&pi);
      get_PFT(&pft);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pi, pft);

      geomUtil::PointOnLineNearest(line, point, m_PointFactory, &fwdTangentPoint);
      point->DistanceEx(fwdTangentPoint, &fwdTangentOffset); // distance from the point to where it projects onto the foward tangent

                                                             // compute distance along the forard tangent to the projection point
      CComPtr<IPoint2d> pt;
      get_PT(&pt);
      geomUtil::Distance(pt, fwdTangentPoint, &fwdTangentDistance);

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

STDMETHODIMP CCircularCurve::Intersect(ILine2d* line,VARIANT_BOOL bProjectBack,VARIANT_BOOL bProjectAhead,IPoint2d** p1,IPoint2d** p2)
{
   CHECK_IN(line);
   CHECK_RETOBJ(p1);
   CHECK_RETOBJ(p2);

   // make this equal to nullptr to indicate intersections not found
   (*p1) = nullptr;
   (*p2) = nullptr;

   //
   // First check to see if the line intersects the circular curve
   ///

   // get the key circular curve points
   CComPtr<IPoint2d> pc, center, pt, pi;
   get_PC(&pc);
   get_Center(&center);
   get_PI(&pi);
   get_PT(&pt);

   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->putref_Center(center);
   circle->put_Radius(m_Radius);

   CComPtr<IPoint2d> pnt1, pnt2;
   short nIntersect;
   geomUtil::LineCircleIntersect(line,circle,m_PointFactory,&pnt1,&pnt2,&nIntersect);

   Float64 delta;
   CurveDirectionType direction;
   get_Direction(&direction);
   if ( direction == cdLeft )
      geomUtil::Angle(pc,center,pt,&delta);
   else
      geomUtil::Angle(pt,center,pc,&delta);

#if defined _DEBUG
   CComPtr<IAngle> angle;
   get_Angle(&angle);
   Float64 value;
   angle->get_Value(&value);
   ATLASSERT(IsEqual(delta, value));
#endif

   CComPtr<IPoint2d> pntCurve1, pntCurve2;
   if ( pnt1 )
   {
      Float64 angle;
      if ( direction == cdLeft )
         geomUtil::Angle(pc,center,pnt1,&angle);
      else
         geomUtil::Angle(pnt1,center,pc,&angle);

      if ( 0 <= angle && angle <= delta )
         pnt1.CopyTo(&pntCurve1);
   }

   if ( pnt2 )
   {
      Float64 angle;
      if ( direction == cdLeft )
         geomUtil::Angle(pc,center,pnt2,&angle);
      else
         geomUtil::Angle(pnt2,center,pc,&angle);

      if ( 0 <= angle && angle <= delta )
         pnt2.CopyTo(&pntCurve2);
   }

   if ( pntCurve1 == nullptr && pntCurve2 != nullptr )
   {
      pntCurve1 = pntCurve2;
      pntCurve2.Release();
   }

   // both intersection points are in the circular curve, we are done
   if ( pntCurve1 && pntCurve2 )
   {
      // make *p1 the point that is nearest the beginning of the curve
      Float64 dist1, dist2;
      pc->DistanceEx(pntCurve1,&dist1);
      pc->DistanceEx(pntCurve2,&dist2);
      if ( dist1 < dist2 )
      {
         pntCurve1.CopyTo(p1);
         pntCurve2.CopyTo(p2);
      }
      else
      {
         pntCurve1.CopyTo(p2);
         pntCurve2.CopyTo(p1);
      }

      return S_OK;
   }

   // If we get this far, the line doesn't intersect the circular curve 
   // or it only intersects it in one place
   
   // check intersection with back tangent
   CComPtr<IPoint2d> bkTangentPoint;
   if ( bProjectBack == VARIANT_TRUE )
   {
      CComPtr<ILine2d> bkTangentLine;
      GetBkTangentLine(&bkTangentLine);
      geomUtil::LineLineIntersect(line,bkTangentLine,m_PointFactory, &bkTangentPoint);

      // if there was an intersection point and the point is not before the start of the TS-PI line
      // then this isn't an intersection on the back tangent projection 
      if ( bkTangentPoint && !cogoUtil::IsPointBeforeStart(pc,pi,bkTangentPoint) )
         bkTangentPoint.Release();
   }

   // check intersection with forward tangent
   CComPtr<IPoint2d> fwdTangentPoint;
   if ( bProjectAhead == VARIANT_TRUE )
   {
      CComPtr<ILine2d> fwdTangentLine;
      GetFwdTangentLine(&fwdTangentLine);
      geomUtil::LineLineIntersect(line,fwdTangentLine,m_PointFactory, &fwdTangentPoint);

      // if there was an intersection point and the point is not after the end of the PI-ST line
      // then this isn't an intersection on the forward tangent projection 
      if ( fwdTangentPoint && !cogoUtil::IsPointAfterEnd(pi,pt,fwdTangentPoint) )
         fwdTangentPoint.Release();
   }

#if defined _DEBUG
   int nPoints = 0;

   if ( bkTangentPoint )
      nPoints++;

   if ( pntCurve1 )
      nPoints++;

   if ( pntCurve2 )
      nPoints++;

   if ( fwdTangentPoint )
      nPoints++;

   // This method assumes there is never more than 2 intersection points
   ATLASSERT( nPoints <= 2 );
#endif

   if ( bkTangentPoint )
   {
      if ( *p1 == nullptr )
         bkTangentPoint.CopyTo(p1);
      else
         bkTangentPoint.CopyTo(p2);
   }

   if ( pntCurve1 )
   {
      if ( *p1 == nullptr )
         pntCurve1.CopyTo(p1);
      else
         pntCurve1.CopyTo(p2);
   }

   if ( pntCurve2 )
   {
      if ( *p1 == nullptr )
         pntCurve2.CopyTo(p1);
      else
         pntCurve2.CopyTo(p2);
   }

   if ( fwdTangentPoint )
   {
      if ( *p1 == nullptr )
         fwdTangentPoint.CopyTo(p1);
      else
         fwdTangentPoint.CopyTo(p2);
   }

   if ( *p1 == nullptr && *p2 == nullptr )
      return S_FALSE;

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_PointFactory(IPoint2dFactory* *factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_PointFactory;
   (*factory)->AddRef();

   return S_OK;
}

STDMETHODIMP CCircularCurve::putref_PointFactory(IPoint2dFactory *factory)
{
   CHECK_IN(factory);
   m_PointFactory = factory;
   return S_OK;
}

STDMETHODIMP CCircularCurve::Offset(Float64 dx,Float64 dy)
{
   m_bHoldEvents = true;
   m_bPendingEvents = false;

   m_PBT->Offset(dx,dy);
   m_PI->Offset(dx,dy);
   m_PFT->Offset(dx,dy);

   m_bHoldEvents = false;
   if ( m_bPendingEvents )
   {
      Fire_OnCircularCurveChanged(this);
   }

   return S_OK;
}

///////////////////////////////////////////
// IPointEvents
STDMETHODIMP CCircularCurve::OnPointChanged(IPoint2d* point)
{
   if ( m_PC.IsEqualObject(point) || m_PT.IsEqualObject(point) )
   {
      return S_OK;
   }

   ATLASSERT( m_PBT.IsEqualObject(point) || 
               m_PI.IsEqualObject(point) ||
              m_PFT.IsEqualObject(point) );

   m_PC.Release();
   m_PT.Release();

#ifdef _DEBUG
   // Better be listening only to IPoint2d objects
   CComQIPtr<IPoint2d> pointEx(point);
   ATLASSERT( pointEx != nullptr );
#endif // _DEBUG

   if ( m_bHoldEvents )
      m_bPendingEvents = true;
   else
      Fire_OnCircularCurveChanged(this);

   return S_OK;
}

STDMETHODIMP CCircularCurve::Clone(ICircularCurve* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCircularCurve>* pClone;
   CComObject<CCircularCurve>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_Radius(m_Radius);

   CComPtr<IPoint2d> clonePBT;
   m_PointFactory->CreatePoint(&clonePBT);
   clonePBT->MoveEx(m_PBT);
   (*clone)->putref_PBT(clonePBT);

   CComPtr<IPoint2d> clonePI;
   m_PointFactory->CreatePoint(&clonePI);
   clonePI->MoveEx(m_PI);
   (*clone)->putref_PI(clonePI);
   
   CComPtr<IPoint2d> clonePFT;
   m_PointFactory->CreatePoint(&clonePFT);
   clonePFT->MoveEx(m_PFT);
   (*clone)->putref_PFT(clonePFT);

   (*clone)->putref_PointFactory(m_PointFactory);

   return S_OK;
}

STDMETHODIMP CCircularCurve::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CCircularCurve::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("CircularCurve"),1.0);
   pSave->put_Property(CComBSTR("PBT"),CComVariant(m_PBT));
   pSave->put_Property(CComBSTR("PI"),CComVariant(m_PI));
   pSave->put_Property(CComBSTR("PFT"),CComVariant(m_PFT));
   pSave->put_Property(CComBSTR("Radius"),CComVariant(m_Radius));
   pSave->put_Property(CComBSTR("PointFactory"),CComVariant(m_PointFactory));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCircularCurve::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("CircularCurve"));

   pLoad->get_Property(CComBSTR("PBT"),&var);
   CComPtr<IPoint2d> pbt;
   _CopyVariantToInterface<IPoint2d>::copy(&pbt,&var);
   putref_PBT(pbt);

   pLoad->get_Property(CComBSTR("PI"),&var);
   CComPtr<IPoint2d> pi;
   _CopyVariantToInterface<IPoint2d>::copy(&pi,&var);
   putref_PI(pi);

   pLoad->get_Property(CComBSTR("PFT"),&var);
   CComPtr<IPoint2d> pft;
   _CopyVariantToInterface<IPoint2d>::copy(&pft,&var);
   putref_PFT(pft);

   pLoad->get_Property(CComBSTR("Radius"),&var);
   put_Radius(var.dblVal);

   pLoad->get_Property(CComBSTR("PointFactory"),&var);
   CComPtr<IPoint2dFactory> factory;
   _CopyVariantToInterface<IPoint2dFactory>::copy(&factory,&var);
   putref_PointFactory(factory);


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

//////////////////////////////////////////////
// Helpers

int CCircularCurve::ProjectionRegion(IPoint2d* pPoint)
{
   int result = 0;

   // check circular curve

   // put coordinate system at PC with X tangent to the curve
   CComPtr<IPoint2d> origin;
   CComPtr<IDirection> brg;

   get_PC(&origin);
   get_BkTangentBrg(&brg);
   Float64 dir;
   brg->get_Value(&dir);

   CComPtr<IPoint2d> xfrmPoint;
   geomUtil::XformToNew(origin, dir, pPoint, &xfrmPoint);
   Float64 x1; // X ordinate in coordinate system 1
   xfrmPoint->get_X(&x1);

   // put coordinate system at PT with X tangent to the curve
   origin.Release();
   get_PT(&origin);

   brg.Release();
   get_FwdTangentBrg(&brg);
   brg->get_Value(&dir);

   xfrmPoint.Release();
   geomUtil::XformToNew(origin, dir, pPoint, &xfrmPoint);
   Float64 x2; // X ordinate in coordinate system 2
   xfrmPoint->get_X(&x2);

   if (x1 < 0)
      result |= BACK_TANGENT;

   if (0 < x2)
      result |= FORWARD_TANGENT;

   if (0 <= x1 && x2 <= 0)
      result |= CIRCULAR_CURVE;

   return result;
}

void CCircularCurve::GetBkTangentLine(ILine2d** line)
{
   CComPtr<ILine2d> pLine;
   pLine.CoCreateInstance(CLSID_Line2d);
   pLine->ThroughPoints(m_PBT,m_PI);

   (*line) = pLine;
   (*line)->AddRef();
}

void CCircularCurve::GetFwdTangentLine(ILine2d** line)
{
   CComPtr<ILine2d> pLine;
   pLine.CoCreateInstance(CLSID_Line2d);
   pLine->ThroughPoints(m_PI,m_PFT);

   (*line) = pLine;
   (*line)->AddRef();
}

bool CCircularCurve::LineParallelToTangent(ILine2d* pTangentLine,ILine2d* pLine,IPoint2d* pTangentPoint)
{
   CComPtr<IPoint2d> center;
   get_Center(&center);

   VARIANT_BOOL bParallel;
   geomUtil::AreLinesParallel(pTangentLine,pLine,&bParallel);
   if ( bParallel == VARIANT_FALSE ) // not parallel means there can be an intersection
      return false;

   Float64 dist1;
   geomUtil::Distance(pTangentPoint, center,&dist1);

   CComPtr<IPoint2d> poln;
   geomUtil::PointOnLineNearest(pLine, center, m_PointFactory,&poln);

   Float64 dist2;
   geomUtil::Distance(center,poln,&dist2);

   if ( dist1 < dist2 && cogoUtil::IsPointBeforeStart(pTangentPoint, center,poln) )
      return true; // line is parallel to tangent and on the outside of the curve... no intersections

   // lines are parallel, but line is on the inside of the curve so an intersection is possible
   return false;
}

bool CCircularCurve::IsPointOnCurve(IPoint2d* pPoint)
{
   CComPtr<IPoint2d> prjPoint;
   Float64 dist;
   VARIANT_BOOL vbOnProjection;
   HRESULT hr = ProjectPoint(pPoint, &prjPoint, &dist, &vbOnProjection);
   ATLASSERT( SUCCEEDED(hr) );

   CComPtr<IPoint2d> pntOnCurve;
   hr = PointOnCurve(dist,&pntOnCurve);

   ATLASSERT( SUCCEEDED(hr) );

   geomUtil::Distance(pPoint,pntOnCurve,&dist);
   return IsZero(dist,tolerance);
}

bool CCircularCurve::IsPointOnLine(ILine2d* pLine,IPoint2d* pPoint)
{
   Float64 offset;
   geomUtil::ShortestDistanceToPoint(pLine,pPoint,&offset);
   return IsZero(offset,tolerance);
}

bool CCircularCurve::TestIntersection(ILine2d* pLine,IPoint2d* pPoint)
{
   return IsPointOnCurve(pPoint) && IsPointOnLine(pLine,pPoint);
}