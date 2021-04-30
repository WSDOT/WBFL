///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2021  Washington State Department of Transportation
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

// HorzCurve.cpp : Implementation of CHorzCurve
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "HorzCurve.h"
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

/////////////////////////////////////////////////////////////////////////////
// CHorzCurve
HRESULT CHorzCurve::FinalConstruct()
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

   m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   m_Xform.CoCreateInstance(CLSID_CoordinateXform2d);

   m_bHoldEvents = false;
   m_bPendingEvents = false;

   return S_OK;
}

void CHorzCurve::FinalRelease()
{
   Unadvise(m_PBT, &m_dwPBT);
   Unadvise(m_PI, &m_dwPI);
   Unadvise(m_PFT, &m_dwPFT);
}

void CHorzCurve::Advise(IPoint2d* pnt,DWORD* pdwCookie)
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

void CHorzCurve::Unadvise(IPoint2d* pnt,DWORD* pdwCookie)
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

STDMETHODIMP CHorzCurve::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IHorzCurve,
		&IID_IStructuredStorage2,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CHorzCurve::get_PBT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_PBT;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CHorzCurve::putref_PBT(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Unadvise(m_PBT,&m_dwPBT);
   m_PBT = newVal;
   OnPointChanged(m_PBT);
   Advise(m_PBT,&m_dwPBT);

   Fire_OnHorzCurveChanged(this);

	return S_OK;
}

STDMETHODIMP CHorzCurve::get_PI(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_PI;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CHorzCurve::putref_PI(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Unadvise(m_PI,&m_dwPI);
   m_PI = newVal;
   OnPointChanged(m_PI);
   Advise(m_PI,&m_dwPI);

   Fire_OnHorzCurveChanged(this);

	return S_OK;
}

STDMETHODIMP CHorzCurve::get_PFT(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_PFT;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CHorzCurve::putref_PFT(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   Unadvise(m_PFT,&m_dwPFT);
   m_PFT = newVal;
   OnPointChanged(m_PFT);
   Advise(m_PFT,&m_dwPFT);

   Fire_OnHorzCurveChanged(this);

	return S_OK;
}

STDMETHODIMP CHorzCurve::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Radius;
   return S_OK;
}

STDMETHODIMP CHorzCurve::put_Radius(Float64 newVal)
{
   if ( newVal <= 0 )
      return E_INVALIDARG;

   m_Radius = newVal;
   Fire_OnHorzCurveChanged(this);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_SpiralLength(SpiralType spType,Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   if ( spType == spEntry )
      *pVal = m_Ls1;
   else
      *pVal = m_Ls2;

	return S_OK;
}

STDMETHODIMP CHorzCurve::put_SpiralLength(SpiralType spType,Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   if ( spType == spEntry )
      m_Ls1 = newVal;
   else
      m_Ls2 = newVal;

   Fire_OnHorzCurveChanged(this);

	return S_OK;
}

STDMETHODIMP CHorzCurve::get_SpiralAngle(SpiralType spType,IAngle **pVal)
{
   CHECK_RETOBJ(pVal);
   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);

   Float64 Ls;
   get_SpiralLength(spType,&Ls);

   Float64 angle;
   angle = Ls / (2*m_Radius);

   pAngle->put_Value(angle);

   (*pVal) = pAngle;
   (*pVal)->AddRef();
   return S_OK;
}

STDMETHODIMP CHorzCurve::get_X(SpiralType spType,Float64* x)
{
   CHECK_RETVAL(x);

   CComPtr<IAngle> spAngle;
   get_SpiralAngle(spType,&spAngle);
   Float64 angle;
   spAngle->get_Value(&angle);

   Float64 Ls;
   get_SpiralLength(spType,&Ls);

   *x = SpiralX(Ls,angle);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_Y(SpiralType spType,Float64* y)
{
   CHECK_RETVAL(y);

   CComPtr<IAngle> spAngle;
   get_SpiralAngle(spType,&spAngle);
   Float64 angle;
   spAngle->get_Value(&angle);

   Float64 Ls;
   get_SpiralLength(spType,&Ls);

   *y = SpiralY(Ls,angle);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_Q(SpiralType spType,Float64* q)
{
   CHECK_RETVAL(q);
   
   CComPtr<IAngle> a;
   get_SpiralAngle(spType,&a);
   Float64 angle;
   a->get_Value(&angle);

   Float64 Y;
   get_Y(spType,&Y);

   *q = Y - m_Radius*(1.0 - cos(angle));

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_T(SpiralType spType,Float64* t)
{
   CHECK_RETVAL(t);

   CComPtr<IAngle> a;
   get_SpiralAngle(spType,&a);
   Float64 angle;
   a->get_Value(&angle);

   Float64 X;
   get_X(spType,&X);

   *t = X - m_Radius*sin(angle);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_FwdTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   Float64 dist;
   cogoUtil::Inverse(m_PI,m_PFT,&dist,pVal);
	return S_OK;
}

STDMETHODIMP CHorzCurve::get_BkTangentBrg(IDirection **pVal)
{
   CHECK_RETOBJ(pVal);
   Float64 dist;
   cogoUtil::Inverse(m_PBT,m_PI,&dist,pVal);
	return S_OK;
}

STDMETHODIMP CHorzCurve::get_CurveAngle(IAngle* *pVal)
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

STDMETHODIMP CHorzCurve::get_BkTangentLength(Float64* t)
{
   CHECK_RETVAL(t);

   if ( IsZero(m_Ls1) && IsZero(m_Ls2) )
   {
      //  No spirals
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      *t = m_Radius * tan(angle/2);
   }
   else if ( !IsZero(m_Ls1) && IsZero(m_Ls2) )
   {
      // Entry Spiral Only
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      Float64 K1, Q1;

      get_T(spEntry,&K1);
      get_Q(spEntry,&Q1);

      *t = (m_Radius - (m_Radius + Q1)*cos(angle))/sin(angle) + K1;
   }
   else if ( IsZero(m_Ls1) && !IsZero(m_Ls2) )
   {
      // Exit Spiral Only
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      Float64 Q2;
      get_Q(spExit,&Q2);

      *t = (m_Radius + Q2 - m_Radius*cos(angle))/sin(angle);
   }
   else
   {
      // Entry and Exit Spirals
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      Float64 K1, Q1, Q2;

      get_T(spEntry,&K1);
      get_Q(spEntry,&Q1);
      get_Q(spExit,&Q2);

      Float64 M = fabs((Q1-Q2))/sin(angle);

      Float64 sign = (Q2 < Q1) ? -1 : 1;

      *t = K1 + (m_Radius + Q1)*tan(angle/2) + sign*M;
   }

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_FwdTangentLength(Float64* t)
{
   CHECK_RETVAL(t);

   if ( IsZero(m_Ls1) && IsZero(m_Ls2) )
   {
      //  No spirals
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      *t = m_Radius * tan(angle/2);
   }
   else if ( !IsZero(m_Ls1) && IsZero(m_Ls2) )
   {
      // Entry Spiral Only
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      Float64 Q1;
      get_Q(spEntry,&Q1);

      *t = (m_Radius + Q1 - m_Radius*cos(angle))/sin(angle);
   }
   else if ( IsZero(m_Ls1) && !IsZero(m_Ls2) )
   {
      // Exit Spiral Only
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      Float64 K2, Q2;

      get_T(spExit,&K2);
      get_Q(spExit,&Q2);

      *t = (m_Radius - (m_Radius + Q2)*cos(angle))/sin(angle) + K2;
   }
   else
   {
      // Entry and Exit Spirals
      CComPtr<IAngle> a;
      get_CurveAngle(&a);
      Float64 angle;
      a->get_Value(&angle);

      Float64 K2, Q1, Q2;

      get_T(spExit,&K2);
      get_Q(spEntry,&Q1);
      get_Q(spExit,&Q2);

      Float64 M = fabs((Q1-Q2))/sin(angle);

      Float64 sign = (Q2 < Q1) ? 1 : -1;

      *t = K2 + (m_Radius + Q2)*tan(angle/2) + sign*M;
   }

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_TS(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( m_TS == nullptr )
   {
      m_PointFactory->CreatePoint(&m_TS);

      CComPtr<IDirection> bkTanBrg;
      get_BkTangentBrg(&bkTanBrg);
      bkTanBrg->IncrementBy(CComVariant(M_PI)); // reverse the bearing (PI to PBT)

      Float64 T;
      get_BkTangentLength(&T);

      CComPtr<IPoint2d> pnt;
      cogoUtil::LocateByDistDir(m_PI,T,bkTanBrg,0.0,m_PointFactory,&pnt);

      Float64 x,y;
      pnt->Location(&x,&y);
      m_TS->Move(x,y);
   }

   m_TS->Clone(pVal);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_ST(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   if ( m_ST == nullptr )
   {
      m_PointFactory->CreatePoint(&m_ST);

      CComPtr<IDirection> fwdTanBrg;
      get_FwdTangentBrg(&fwdTanBrg);

      Float64 T;
      get_FwdTangentLength(&T);

      CComPtr<IPoint2d> pnt;
      cogoUtil::LocateByDistDir(m_PI,T,fwdTanBrg,0.0,m_PointFactory,&pnt);

      Float64 x,y;
      pnt->Location(&x,&y);
      m_ST->Move(x,y);
   }

   m_ST->Clone(pVal);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_SC(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 X, Y;
   get_X(spEntry,&X);
   get_Y(spEntry,&Y);

   PointOnEntrySpiral(X,Y,pVal);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_CS(IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 X, Y;
   get_X(spExit,&X);
   get_Y(spExit,&Y);

   PointOnExitSpiral(X,Y,pVal);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_Chord(Float64* chord)
{
   CHECK_RETVAL(chord);
   CComPtr<IPoint2d> sc, cs;
   get_SC(&sc);
   get_CS(&cs);
   CComPtr<IDirection> dir;
   cogoUtil::Inverse(sc,cs,chord,&dir);
   return S_OK;
}

STDMETHODIMP CHorzCurve::get_CircularCurveAngle(IAngle* *pVal)
{
   CHECK_RETOBJ(pVal);

   CComPtr<IAngle> totalAngle;
   CComPtr<IAngle> entryAngle;
   CComPtr<IAngle> exitAngle;

   get_CurveAngle(&totalAngle);
   get_SpiralAngle(spEntry,&entryAngle);
   get_SpiralAngle(spExit,&exitAngle);

   Float64 total, entry, exit;
   totalAngle->get_Value(&total);
   entryAngle->get_Value(&entry);
   exitAngle->get_Value(&exit);

   Float64 angle = total - entry - exit;
   if ( angle < 0 )
      return Error(IDS_E_SPIRALSOVERLAP,IID_IHorzCurve,COGO_E_SPIRALSOVERLAP);

   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);
   pAngle->put_Value(angle);

   (*pVal) = pAngle;
   (*pVal)->AddRef();

#if defined _DEBUG
   // Back check angle by alternative means
   Float64 chord;
   get_Chord(&chord);
   Float64 val = 2.0*asin(chord/(2*m_Radius));
   ATLASSERT( IsEqual(val,angle,0.001) );
#endif // _DEBUG

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_Tangent(Float64* tangent)
{
   CHECK_RETVAL(tangent);
   CComPtr<IAngle> angle;
   HRESULT hr = get_CircularCurveAngle(&angle);
   if ( FAILED(hr) )
      return hr;

   Float64 val;
   angle->get_Value(&val);
   *tangent = m_Radius * tan(val/2);
   return S_OK;
}

STDMETHODIMP CHorzCurve::get_MidOrdinate(Float64* mo)
{
   CHECK_RETVAL(mo);
   CComPtr<IAngle> angle;
   HRESULT hr = get_CircularCurveAngle(&angle);
   if ( FAILED(hr) )
      return hr;

   Float64 val;
   angle->get_Value(&val);
   *mo = m_Radius * (1 - cos(val/2));

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_External(Float64* external)
{
   CHECK_RETVAL(external);
   CComPtr<IAngle> angle;
   HRESULT hr = get_CircularCurveAngle(&angle);
   if ( FAILED(hr) )
      return hr;

   Float64 val;
   angle->get_Value(&val);
   *external = m_Radius * (1/cos(val/2) - 1);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_DE(SpiralType spType,IAngle** pDE)
{
   // Deviation angle of spiral measured from back tangent (or forward tangent)
   // to tangent through the spiral at its maximum degree
   CHECK_RETOBJ(pDE);

   return get_SpiralAngle(spType,pDE);
}

STDMETHODIMP CHorzCurve::get_LongTangent(SpiralType spType,Float64* u)
{
   CHECK_RETVAL(u);

   // If the length is zero, U is zero
   Float64 Ls;
   get_SpiralLength(spType,&Ls);
   if ( IsZero(Ls) )
   {
      *u = 0.0;
      return S_OK;
   }

   Float64 X,Y;
   get_X(spType,&X);
   get_Y(spType,&Y);

   CComPtr<IAngle> deObj;
   get_DE(spType,&deObj);
   Float64 DE;
   deObj->get_Value(&DE);

   *u = X - Y/tan(DE);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_ShortTangent(SpiralType spType,Float64* v)
{
   CHECK_RETVAL(v);

   // If the length is zero, V is zero
   Float64 Ls;
   get_SpiralLength(spType,&Ls);
   if ( IsZero(Ls) )
   {
      *v = 0.0;
      return S_OK;
   }

   Float64 X,Y;
   get_X(spType,&X);
   get_Y(spType,&Y);

   CComPtr<IAngle> deObj;
   get_DE(spType,&deObj);
   Float64 DE;
   deObj->get_Value(&DE);

   *v = Y/sin(DE);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_CC(IPoint2d** pVal)
{
   CHECK_RETOBJ(pVal);

   CComPtr<IPoint2d> TS;
   CComPtr<IPoint2d> ST;
   get_TS(&TS);
   get_ST(&ST);
   
   CComPtr<ILine2d> t1, t2;
   t1.CoCreateInstance(CLSID_Line2d); // bk tangent (reversed)
   t2.CoCreateInstance(CLSID_Line2d); // fwd tangent (reversed)

   HRESULT hr;
   hr = t1->ThroughPoints(m_PI,TS);
   ATLASSERT(SUCCEEDED(hr));
   hr = t2->ThroughPoints(m_PI,ST);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<ILine2d> n1, n2;
   hr = m_GeomUtil->CreateNormalLineThroughPoint(t1,TS,&n1);
   ATLASSERT(SUCCEEDED(hr));
   hr = m_GeomUtil->CreateNormalLineThroughPoint(t2,ST,&n2);
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IPoint2d> p;
   hr = m_GeomUtil->LineLineIntersect(n1,n2,&p);
   ATLASSERT(SUCCEEDED(hr));

#if defined _DEBUG
   // intersect tangents... should intersect at PI
   CComPtr<IPoint2d> testPoint;
   m_GeomUtil->LineLineIntersect(t1,t2,&testPoint);
   Float64 x1,y1, x2,y2;
   m_PI->Location(&x1,&y1);
   testPoint->Location(&x2,&y2);
   ATLASSERT( IsEqual(x1,x2) && IsEqual(y1,y2) );

   // intersect forward tangent and its normal
   // should intersect at TS
   testPoint.Release();
   m_GeomUtil->LineLineIntersect(t1,n1,&testPoint);
   TS->Location(&x1,&y1);
   testPoint->Location(&x2,&y2);
   ATLASSERT( IsEqual(x1,x2) && IsEqual(y1,y2) );

   // intersect back tangent and its normal
   // should intersect at ST
   testPoint.Release();
   m_GeomUtil->LineLineIntersect(t2,n2,&testPoint);
   ST->Location(&x1,&y1);
   testPoint->Location(&x2,&y2);
   ATLASSERT( IsEqual(x1,x2) && IsEqual(y1,y2) );
#endif // _DEBUG

   p.QueryInterface(pVal);
   ATLASSERT( *pVal != nullptr );

	return S_OK;
}

STDMETHODIMP CHorzCurve::get_SPI(SpiralType spType,IPoint2d** pSPI)
{
   CHECK_RETOBJ(pSPI);

   Float64 U;
   get_LongTangent(spType,&U);

   Float64 X, Y;
   X = U;
   Y = 0;

   if ( spType == spEntry )
   {
      // Setup a coordinate system at TS, with positive X going from TS to PI.
      // SC will be at point (X,-Y) in this coordinate system
      // Transform SC into the global coordinate system
      CComPtr<IPoint2d> TS;
      get_TS(&TS);

      m_Xform->putref_NewOrigin(TS);

      CComPtr<IDirection> dir;
      Float64 dist;
      cogoUtil::Inverse(TS,m_PI,&dist,&dir);
      Float64 rotAngle;
      dir->get_Value(&rotAngle);
      m_Xform->put_RotationAngle(rotAngle);

      m_PointFactory->CreatePoint(pSPI);
      (*pSPI)->put_X(X);
      (*pSPI)->put_Y(-Y);
      CComQIPtr<IPoint2d> spi(*pSPI);
      m_Xform->Xform(&spi.p,xfrmNewToOld);
   }
   else
   {
      // Setup a coordinate system at ST, with positive X going from ST to PI
      // CS will be at point (X,Y) in this coordinate system
      // Transform CS into the global coordinate system
      CComPtr<IPoint2d> ST;
      get_ST(&ST);

      m_Xform->putref_NewOrigin(ST);

      CComPtr<IDirection> dir;
      Float64 dist;
      cogoUtil::Inverse(ST,m_PI,&dist,&dir);
      Float64 rotAngle;
      dir->get_Value(&rotAngle);
      m_Xform->put_RotationAngle(rotAngle);

      m_PointFactory->CreatePoint(pSPI);
      (*pSPI)->put_X(X);
      (*pSPI)->put_Y(Y);
      CComQIPtr<IPoint2d> spi(*pSPI);
      m_Xform->Xform(&spi.p,xfrmNewToOld);
   }

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_CurveBkTangentBrg(IDirection* *brg)
{
   CHECK_RETOBJ(brg);
   if ( IsZero(m_Ls1) )
   {
      // No Entry Spiral
      get_BkTangentBrg(brg);
   }
   else
   {
      // Entry Spiral
      CComPtr<IPoint2d> spi;
      CComPtr<IPoint2d> sc;

      get_SPI(spEntry,&spi);
      get_SC(&sc);

      Float64 dist;
      cogoUtil::Inverse(spi,sc,&dist,brg);
   }
   
   return S_OK;
}

STDMETHODIMP CHorzCurve::get_CurveFwdTangentBrg(IDirection* *brg)
{
   CHECK_RETOBJ(brg);

   if ( IsZero(m_Ls2) )
   {
      // No Exit Spiral
      get_FwdTangentBrg(brg);
   }
   else
   {
      // Exit Spiral
      CComPtr<IPoint2d> cs;
      CComPtr<IPoint2d> spi;

      get_CS(&cs);
      get_SPI(spExit,&spi);

      Float64 dist;
      cogoUtil::Inverse(cs,spi,&dist,brg);
   }

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_PCI(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   // Get Bk and Fwd Tangent Bearings
   CComPtr<IDirection> bkBrg, fwdBrg;
   get_CurveBkTangentBrg(&bkBrg);
   get_CurveFwdTangentBrg(&fwdBrg);

   // Create a line in the direction of the bk tangent brg
   
   // vector in the direction of the line
   CComPtr<IVector2d> v1;
   v1.CoCreateInstance(CLSID_Vector2d);

   Float64 brg;
   bkBrg->get_Value(&brg);
   v1->put_X(cos(brg));
   v1->put_Y(sin(brg));

   // point on the line
   CComPtr<IPoint2d> spi1;
   get_SPI(spEntry,&spi1);

   CComPtr<ILine2d> l1;
   l1.CoCreateInstance(CLSID_Line2d);
   l1->SetExplicit(spi1,v1);

   // Create a line in the direction of the fwd tangent brg

   // vector in the direction of the line
   CComPtr<IVector2d> v2;
   v2.CoCreateInstance(CLSID_Vector2d);

   fwdBrg->get_Value(&brg);
   v2->put_X(cos(brg));
   v2->put_Y(sin(brg));

   // point on the line
   CComPtr<IPoint2d> spi2;
   get_SPI(spExit,&spi2);

   CComPtr<ILine2d> l2;
   l2.CoCreateInstance(CLSID_Line2d);
   l2->SetExplicit(spi2,v2);

   // Intersect the 2 lines
   CComPtr<IPoint2d> p;
   m_GeomUtil->LineLineIntersect(l1,l2,&p);

   p.QueryInterface(pVal);
   ATLASSERT( *pVal != nullptr );

	return S_OK;
}

STDMETHODIMP CHorzCurve::get_CCC(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   // Get Bk and Fwd Tangent Bearings
   CComPtr<IDirection> bkBrg, fwdBrg;
   get_CurveBkTangentBrg(&bkBrg);
   get_CurveFwdTangentBrg(&fwdBrg);

   // Create a line normal to the bk tangent brg
   
   // vector in the direction of the line
   CComPtr<IVector2d> v1;
   v1.CoCreateInstance(CLSID_Vector2d);

   Float64 brg;
   bkBrg->get_Value(&brg);
   brg += PI_OVER_2; // add 90 deg to get the normal
   v1->put_X(cos(brg));
   v1->put_Y(sin(brg));

   // point on the line
   CComPtr<IPoint2d> sc;
   get_SC(&sc);

   CComPtr<ILine2d> l1;
   l1.CoCreateInstance(CLSID_Line2d);
   l1->SetExplicit(sc,v1);

   // Create a line normal to the fwd tangent brg

   // vector in the direction of the line
   CComPtr<IVector2d> v2;
   v2.CoCreateInstance(CLSID_Vector2d);

   fwdBrg->get_Value(&brg);
   brg += PI_OVER_2; // add 90 deg to get the normal
   v2->put_X(cos(brg));
   v2->put_Y(sin(brg));

   // point on the line
   CComPtr<IPoint2d> cs;
   get_CS(&cs);

   CComPtr<ILine2d> l2;
   l2.CoCreateInstance(CLSID_Line2d);
   l2->SetExplicit(cs,v2);

   // Intersect the 2 lines
   CComPtr<IPoint2d> p;
   m_GeomUtil->LineLineIntersect(l1,l2,&p);

   p.QueryInterface(pVal);
   ATLASSERT( *pVal != nullptr );

	return S_OK;
}

STDMETHODIMP CHorzCurve::get_SpiralChord(SpiralType spType,Float64* cs)
{
   CHECK_RETVAL(cs);

   CComPtr<IPoint2d> start;
   CComPtr<IPoint2d> end;

   if ( spType == spEntry )
   {
      get_TS(&start);
      get_SC(&end);
   }
   else
   {
      get_ST(&start);
      get_CS(&end);
   }

   CComPtr<IDirection> dir;
   cogoUtil::Inverse(start,end,cs,&dir);

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_DF(SpiralType spType,IAngle** pDF)
{
   CHECK_RETOBJ(pDF);

   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> vertex;
   CComPtr<IPoint2d> to;
   Float64 angle;

   CurveDirectionType dir;
   get_Direction(&dir);

   if ( spType == spEntry )
   {
      if ( dir == cdRight )
      {
         get_SC(&from);
         get_TS(&vertex);
         get_SPI(spEntry,&to);
      }
      else
      {
         get_SPI(spEntry,&from);
         get_TS(&vertex);
         get_SC(&to);
      }
   }
   else
   {
      if ( dir == cdRight )
      {
         get_SPI(spExit,&from);
         get_ST(&vertex);
         get_CS(&to);
      }
      else
      {
         get_CS(&from);
         get_ST(&vertex);
         get_SPI(spExit,&to);
      }
   }

   HRESULT hr = m_GeomUtil->Angle(from,vertex,to,&angle);
   if ( hr == GEOMETRY_E_SAMEPOINTS )
   {
      // 3 points are the same. This occurs when the spiral lengths are zero
      angle = 0.0;
   }

   CComObject<CAngle>* pDFObj;
   CComObject<CAngle>::CreateInstance(&pDFObj);
   pDFObj->put_Value(angle);
   (*pDF) = pDFObj;
   (*pDF)->AddRef();

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_DH(SpiralType spType,IAngle** pDH)
{
   CHECK_RETOBJ(pDH);

   CComPtr<IPoint2d> from;
   CComPtr<IPoint2d> vertex;
   CComPtr<IPoint2d> to;
   Float64 angle;

   CurveDirectionType dir;
   get_Direction(&dir);

   if ( spType == spEntry )
   {
      if ( dir == cdRight )
      {
         get_SPI(spEntry,&from);
         get_SC(&vertex);
         get_TS(&to);
      }
      else
      {
         get_TS(&from);
         get_SC(&vertex);
         get_SPI(spEntry,&to);
      }
   }
   else
   {
      if ( dir == cdRight )
      {
         get_ST(&from);
         get_CS(&vertex);
         get_SPI(spExit,&to);
      }
      else
      {
         get_SPI(spExit,&from);
         get_CS(&vertex);
         get_ST(&to);
      }
   }

   HRESULT hr = m_GeomUtil->Angle(from,vertex,to,&angle);
   if ( hr == GEOMETRY_E_SAMEPOINTS )
   {
      // 3 points are the same. This occurs when the spiral lengths are zero
      angle = 0.0;
   }

   CComObject<CAngle>* pDHObj;
   CComObject<CAngle>::CreateInstance(&pDHObj);
   pDHObj->put_Value(angle);
   (*pDH) = pDHObj;
   (*pDH)->AddRef();

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_Direction(CurveDirectionType* dir)
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

STDMETHODIMP CHorzCurve::get_CurveLength(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IAngle> objAngle;
   HRESULT hr = get_CircularCurveAngle(&objAngle);
   if ( FAILED(hr) )
      return hr;

   Float64 angle;
   objAngle->get_Value(&angle);

   *pVal = m_Radius*angle;

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_TotalLength(Float64* pVal)
{
   CHECK_RETVAL(pVal);

   Float64 L;
   HRESULT hr = get_CurveLength(&L);
   if ( FAILED(hr) )
      return hr;

   *pVal = m_Ls1 + L + m_Ls2;

   return S_OK;
}

STDMETHODIMP CHorzCurve::get_DegreeCurvature(Float64 D,DegreeCurvatureType dcMethod,IAngle** pDC)
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

STDMETHODIMP CHorzCurve::Bearing(Float64 distance,IDirection* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 Lc; // Length of cicular curve
   HRESULT hr = get_CurveLength(&Lc);
   if ( FAILED(hr) )
      return hr;

   Float64 Lt; // Total length of curve
   hr = get_TotalLength(&Lt);
   if ( FAILED(hr) )
      return hr;

   if ( distance <= 0 )
   {
      // Before curve
      get_BkTangentBrg(pVal);
   }
   else if ( Lt <= distance )
   {
      // After curve
      get_FwdTangentBrg(pVal);
   }
   else
   {
      CurveDirectionType dir;
      get_Direction(&dir);

      Float64 sign = (dir == cdLeft ? 1 : -1);

      // On curve
      if ( distance <= m_Ls1 )
      {
         // On entry spiral
         Float64 La; // arc length
         La = distance;

         CComPtr<IAngle> objAngle;
         get_SpiralAngle(spEntry,&objAngle);
         Float64 angle;
         objAngle->get_Value(&angle);


         Float64 sweepAngle = pow(La/m_Ls1,2) * sign*angle;

         get_BkTangentBrg(pVal);
         (*pVal)->IncrementBy(CComVariant(sweepAngle));
      }
      else if ( m_Ls1 < distance && distance <= m_Ls1+Lc )
      {
         // On circular curve
         Float64 La; // arc length
         La = distance - m_Ls1;

         Float64 sweepAngle = sign*La/m_Radius;

         get_CurveBkTangentBrg(pVal);
         (*pVal)->IncrementBy(CComVariant(sweepAngle));
      }
      else
      {
         // On exit spiral
         Float64 La; // arc length measured from the end of the curve
         La = Lt - distance;

         CComPtr<IAngle> objAngle;
         get_SpiralAngle(spExit,&objAngle);
         Float64 angle;
         objAngle->get_Value(&angle);

         Float64 sweepAngle; // sweep angle measured from the end of the curve
         sweepAngle = sign * pow(La/m_Ls2,2) * angle;

         get_FwdTangentBrg(pVal);
         (*pVal)->IncrementBy(CComVariant(-sweepAngle));
      }
   }

   return S_OK;
}

STDMETHODIMP CHorzCurve::Normal(Float64 distance,IDirection* *pVal)
{
   // CHECK_RETOBJ(pVal); // check in Bearing

   HRESULT hr = Bearing(distance,pVal);
   if ( FAILED(hr) )
      return hr;

   (*pVal)->IncrementBy(CComVariant(-PI_OVER_2));
   return S_OK;
}

STDMETHODIMP CHorzCurve::PointOnCurve(Float64 distance,IPoint2d* *pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 Lc; // Length of cicular curve
   HRESULT hr = get_CurveLength(&Lc);
   if ( FAILED(hr) )
      return hr;

   Float64 Lt; // Total length of curve
   hr = get_TotalLength(&Lt);
   if ( FAILED(hr) )
      return hr;

   if ( distance <= 0 )
   {
      // Before curve
      CComPtr<IDirection> bkTanBrg;
      get_BkTangentBrg(&bkTanBrg);
      CComPtr<IPoint2d> ts;
      get_TS(&ts);
      cogoUtil::LocateByDistDir(ts,distance,bkTanBrg,0.0,m_PointFactory,pVal);
   }
   else if ( Lt <= distance )
   {
      // After curve
      CComPtr<IDirection> fwdTanBrg;
      get_FwdTangentBrg(&fwdTanBrg);
      CComPtr<IPoint2d> st;
      get_ST(&st);
      cogoUtil::LocateByDistDir(st,distance - Lt, fwdTanBrg, 0.0, m_PointFactory,pVal);
   }
   else
   {
      CurveDirectionType dir;
      get_Direction(&dir);

      Float64 sign = (dir == cdLeft ? 1 : -1);

      // On curve
      if ( distance <= m_Ls1 )
      {
         // On entry spiral
         PointOnEntrySpiral(distance,pVal);
      }
      else if ( m_Ls1 < distance && distance <= m_Ls1+Lc )
      {
         // On circular curve
         Float64 ls; // arc length from start of circular curve
         ls = distance - m_Ls1;

         Float64 sweepAngle = sign*ls/m_Radius;

         CComPtr<IPoint2d> sc; // start of circular curve
         get_SC(&sc);

         CComPtr<IPoint2d> ccc; // center of circular curve
         get_CCC(&ccc);

         sc->RotateEx(ccc,sweepAngle);

         (*pVal) = sc;
         (*pVal)->AddRef();
      }
      else
      {
         // On exit spiral
         Float64 ls; // arc length measured from the end of the curve
         ls = Lt - distance;
         PointOnExitSpiral(ls,pVal);
      }
   }

   return S_OK;
}

STDMETHODIMP CHorzCurve::ProjectPoint( IPoint2d* point, IPoint2d* *pNewPoint)
{
   CHECK_IN(point);
   CHECK_RETVAL(pNewPoint);

   Float64 dist;
   ProjectPoint(point,&dist,pNewPoint);

   return S_OK;
}

STDMETHODIMP CHorzCurve::DistanceFromStart(IPoint2d* point, Float64* dist)
{
   CHECK_IN(point);
   CHECK_RETVAL(dist);

   CComPtr<IPoint2d> prjPoint;
   ProjectPoint(point,dist,&prjPoint);

   return S_OK;
}

STDMETHODIMP CHorzCurve::Intersect(ILine2d* line,VARIANT_BOOL bProjectBack,VARIANT_BOOL bProjectAhead,IPoint2d** p1,IPoint2d** p2)
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
   CComPtr<IPoint2d> SC, CS, CCC, PI, TS, ST;
   get_CS(&CS);
   get_SC(&SC);
   get_CCC(&CCC);
   get_PI(&PI);
   get_TS(&TS);
   get_ST(&ST);

   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->putref_Center(CCC);
   circle->put_Radius(m_Radius);

   CComPtr<IPoint2d> pnt1, pnt2;
   short nIntersect;
   m_GeomUtil->LineCircleIntersect(line,circle,&pnt1,&pnt2,&nIntersect);

   Float64 delta;
   CurveDirectionType direction;
   get_Direction(&direction);
   if ( direction == cdLeft )
      m_GeomUtil->Angle(SC,CCC,CS,&delta);
   else
      m_GeomUtil->Angle(CS,CCC,SC,&delta);

#if defined _DEBUG
   CComPtr<IAngle> angle;
   get_CircularCurveAngle(&angle);
   Float64 value;
   angle->get_Value(&value);
   ATLASSERT(IsEqual(delta, value));
#endif

   CComPtr<IPoint2d> pntCurve1, pntCurve2;
   if ( pnt1 )
   {
      Float64 angle;
      if ( direction == cdLeft )
         m_GeomUtil->Angle(SC,CCC,pnt1,&angle);
      else
         m_GeomUtil->Angle(pnt1,CCC,SC,&angle);

      if ( 0 <= angle && angle <= delta )
         pnt1.CopyTo(&pntCurve1);
   }

   if ( pnt2 )
   {
      Float64 angle;
      if ( direction == cdLeft )
         m_GeomUtil->Angle(SC,CCC,pnt2,&angle);
      else
         m_GeomUtil->Angle(pnt2,CCC,SC,&angle);

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
      TS->DistanceEx(pntCurve1,&dist1);
      TS->DistanceEx(pntCurve2,&dist2);
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
   
   // Check if it intersects the entry spiral
   CComPtr<IPoint2d> pntEntrySpiral;
   if ( 0 < m_Ls1 )
   {
      // when evaluated, this function returns the distance from the line to the curve
      // if the curve is to the left of the line the distance is negative
      CLineIntersectFunction function(this,line,m_GeomUtil);
      mathBrentsRootFinder2d rootFinder;
      Float64 ya = function.Evaluate(0);
      Float64 yb = function.Evaluate(m_Ls1);
      if ( 0 < ya*yb )
      {
         // The end points don't bracket the solution....
         // Either the line doesn't intersect the spiral, it intersects it in two places
         // or it is tangent to the spiral

         // If the line intersects both the lines that are tangent to the spiral
         // then there is at least one intersection point
         CComPtr<IPoint2d> SPI;
         get_SPI(spEntry,&SPI);
         CComPtr<ILineSegment2d> seg1;
         seg1.CoCreateInstance(CLSID_LineSegment2d);
         seg1->ThroughPoints(TS,SPI);
         CComPtr<IPoint2d> pnt1;
         m_GeomUtil->IntersectLineWithLineSegment(line,seg1,&pnt1);

         CComPtr<ILineSegment2d> seg2;
         seg2.CoCreateInstance(CLSID_LineSegment2d);
         seg2->ThroughPoints(SPI,SC);
         CComPtr<IPoint2d> pnt2;
         m_GeomUtil->IntersectLineWithLineSegment(line,seg2,&pnt2);

         if ( pnt1 && pnt2 )
         {
            // there are at least 1 intersection point... 
            // need to find a disntace along the curve that is between the two intersection points
            // so we have a brack that works... to do this, search for a point on the spiral where
            // the tangent to the spiral is parallel to the line
            CParallelLineFunction parallel_function(this,line,m_GeomUtil);
            Float64 limit;
            try
            {
               limit = rootFinder.FindRootInRange(parallel_function,0,m_Ls1,0.0000001);
            }
            catch(mathXRootFinder2dFailed& /*e*/)
            {
               ATLASSERT(false);
            }

            // if this location is on the intersecting line, the intersecting line
            // is tangent to the spiral
            CComPtr<IPoint2d> POC;
            PointOnCurve(limit,&POC);
            VARIANT_BOOL bContainsPoint;
            m_GeomUtil->DoesLineContainPoint(line,POC,0.001,&bContainsPoint);
            if ( bContainsPoint == VARIANT_TRUE )
            {
               // Line is tangent
               POC.CopyTo(p1);
               return S_OK; // with tangency, there is only one solution so just leave now
            }
            else
            {
               // Line is not tangent
               try
               {
                  // get first insersection in first segment
                  Float64 dist1 = rootFinder.FindRootInRange(function,0,limit,0.0001);
                  PointOnCurve(dist1,p1);
                  ATLASSERT(TestIntersection(line,*p1));

                  // get second interection in second segment
                  Float64 dist2 = rootFinder.FindRootInRange(function,limit,m_Ls1,0.0001);
                  PointOnCurve(dist2,p2);
                  ATLASSERT(TestIntersection(line,*p2));

                  return S_OK; // we got both intersection points... leave now
               }
               catch (mathXRootFinder2dFailed& /*mx*/)
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
            Float64 dist1 = rootFinder.FindRootInRange(function,0,m_Ls1,0.0001);
            PointOnCurve(dist1,&pntEntrySpiral);
            ATLASSERT(TestIntersection(line,pntEntrySpiral));
         }
         catch (mathXRootFinder2dFailed& /*mx*/)
         {
            ATLASSERT(false); 
         }
      }
   }

   
   // Check if it intersects the exit spiral
   CComPtr<IPoint2d> pntExitSpiral;
   if ( 0 < m_Ls2 )
   {
      // when evaluated, this function returns the distance from the line to the curve
      // if the curve is to the left of the line the distance is negative
      CLineIntersectFunction function(this,line,m_GeomUtil);
      mathBrentsRootFinder2d rootFinder;
      Float64 length;
      get_TotalLength(&length);
      Float64 ya = function.Evaluate(length-m_Ls2);
      Float64 yb = function.Evaluate(length);
      if ( 0 < ya*yb )
      {
         // The end points don't bracket the solution....
         // Either the line doesn't intersect the spiral, it intersects it in two places
         // or it is tangent to the spiral

         // If the line intersects both the lines that are tangent to the spiral
         // then there is at least one intersection point
         CComPtr<IPoint2d> SPI;
         get_SPI(spExit,&SPI);
         CComPtr<ILineSegment2d> seg1;
         seg1.CoCreateInstance(CLSID_LineSegment2d);
         seg1->ThroughPoints(ST,SPI);
         CComPtr<IPoint2d> pnt1;
         m_GeomUtil->IntersectLineWithLineSegment(line,seg1,&pnt1);

         CComPtr<ILineSegment2d> seg2;
         seg2.CoCreateInstance(CLSID_LineSegment2d);
         seg2->ThroughPoints(SPI,CS);
         CComPtr<IPoint2d> pnt2;
         m_GeomUtil->IntersectLineWithLineSegment(line,seg2,&pnt2);

         if ( pnt1 && pnt2 )
         {
            // there are at least 1 intersection point... 
            // need to find a disntace along the curve that is between the two intersection points
            // so we have a brack that works... to do this, search for a point on the spiral where
            // the tangent to the spiral is parallel to the line
            CParallelLineFunction parallel_function(this,line,m_GeomUtil);
            Float64 limit;
            try
            {
               limit = rootFinder.FindRootInRange(parallel_function,length-m_Ls2,length,0.0000001);
            }
            catch(mathXRootFinder2dFailed& /*e*/)
            {
               ATLASSERT(false);
            }

            // if this location is on the intersecting line, the intersecting line
            // is tangent to the spiral
            CComPtr<IPoint2d> POC;
            PointOnCurve(limit,&POC);
            VARIANT_BOOL bContainsPoint;
            m_GeomUtil->DoesLineContainPoint(line,POC,0.001,&bContainsPoint);
            if ( bContainsPoint == VARIANT_TRUE )
            {
               // Line is tangent
               POC.CopyTo(p1);
               return S_OK; // with tangency, there is only one solution so just leave now
            }
            else
            {
               // Line is not tangent
               try
               {
                  // get first insersection in first segment
                  Float64 dist1 = rootFinder.FindRootInRange(function,length-m_Ls2,limit,0.0001);
                  PointOnCurve(dist1,p1);
                  ATLASSERT(TestIntersection(line,*p1));

                  // get second interection in second segment
                  Float64 dist2 = rootFinder.FindRootInRange(function,limit,length,0.0001);
                  PointOnCurve(dist2,p2);
                  ATLASSERT(TestIntersection(line,*p2));

                  return S_OK; // we got both intersection points... leave now
               }
               catch (mathXRootFinder2dFailed& /*mx*/)
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
            Float64 dist1 = rootFinder.FindRootInRange(function,length-m_Ls2,length,0.0001);
            PointOnCurve(dist1,&pntExitSpiral);
            ATLASSERT(TestIntersection(line,pntExitSpiral));
         }
         catch (mathXRootFinder2dFailed& /*mx*/)
         {
            ATLASSERT(false); 
         }
      }
   }

   // check intersection with back tangent
   CComPtr<IPoint2d> bkTangentPoint;
   if ( bProjectBack == VARIANT_TRUE )
   {
      CComPtr<ILine2d> bkTangentLine;
      GetBkTangentLine(&bkTangentLine);
      m_GeomUtil->LineLineIntersect(line,bkTangentLine, &bkTangentPoint);

      // if there was an intersection point and the point is not before the start of the TS-PI line
      // then this isn't an intersection on the back tangent projection 
      if ( bkTangentPoint && !cogoUtil::IsPointBeforeStart(TS,PI,bkTangentPoint) )
         bkTangentPoint.Release();
   }

   // check intersection with forward tangent
   CComPtr<IPoint2d> fwdTangentPoint;
   if ( bProjectAhead == VARIANT_TRUE )
   {
      CComPtr<ILine2d> fwdTangentLine;
      GetFwdTangentLine(&fwdTangentLine);
      m_GeomUtil->LineLineIntersect(line,fwdTangentLine, &fwdTangentPoint);

      // if there was an intersection point and the point is not after the end of the PI-ST line
      // then this isn't an intersection on the forward tangent projection 
      if ( fwdTangentPoint && !cogoUtil::IsPointAfterEnd(PI,ST,fwdTangentPoint) )
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

   if ( pntEntrySpiral )
      nPoints++;

   if ( pntExitSpiral )
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

   if ( pntEntrySpiral )
   {
      if ( *p1 == nullptr )
         pntEntrySpiral.CopyTo(p1);
      else
         pntEntrySpiral.CopyTo(p2);
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

   if ( pntExitSpiral )
   {
      if ( *p1 == nullptr )
         pntExitSpiral.CopyTo(p1);
      else
         pntExitSpiral.CopyTo(p2);
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

STDMETHODIMP CHorzCurve::get_PointFactory(IPoint2dFactory* *factory)
{
   CHECK_RETOBJ(factory);
   (*factory) = m_PointFactory;
   (*factory)->AddRef();

   return S_OK;
}

STDMETHODIMP CHorzCurve::putref_PointFactory(IPoint2dFactory *factory)
{
   CHECK_IN(factory);
   m_PointFactory = factory;
   return S_OK;
}

STDMETHODIMP CHorzCurve::Offset(Float64 dx,Float64 dy)
{
   m_bHoldEvents = true;
   m_bPendingEvents = false;

   m_PBT->Offset(dx,dy);
   m_PI->Offset(dx,dy);
   m_PFT->Offset(dx,dy);

   m_bHoldEvents = false;
   if ( m_bPendingEvents )
   {
      Fire_OnHorzCurveChanged(this);
   }

   return S_OK;
}

///////////////////////////////////////////
// IPointEvents
STDMETHODIMP CHorzCurve::OnPointChanged(IPoint2d* point)
{
   if ( m_TS.IsEqualObject(point) || m_ST.IsEqualObject(point) )
   {
      return S_OK;
   }

   ATLASSERT( m_PBT.IsEqualObject(point) || 
               m_PI.IsEqualObject(point) ||
              m_PFT.IsEqualObject(point) );

   m_TS.Release();
   m_ST.Release();

#ifdef _DEBUG
   // Better be listening only to IPoint2d objects
   CComQIPtr<IPoint2d> pointEx(point);
   ATLASSERT( pointEx != nullptr );
#endif // _DEBUG

   if ( m_bHoldEvents )
      m_bPendingEvents = true;
   else
      Fire_OnHorzCurveChanged(this);

   return S_OK;
}

STDMETHODIMP CHorzCurve::Clone(IHorzCurve* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CHorzCurve>* pClone;
   CComObject<CHorzCurve>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_SpiralLength(spEntry,m_Ls1);
   (*clone)->put_SpiralLength(spExit, m_Ls2);
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

STDMETHODIMP CHorzCurve::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CHorzCurve::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("HorzCurve"),1.0);
   pSave->put_Property(CComBSTR("PBT"),CComVariant(m_PBT));
   pSave->put_Property(CComBSTR("PI"),CComVariant(m_PI));
   pSave->put_Property(CComBSTR("PFT"),CComVariant(m_PFT));
   pSave->put_Property(CComBSTR("Radius"),CComVariant(m_Radius));
   pSave->put_Property(CComBSTR("Ls1"),CComVariant(m_Ls1));
   pSave->put_Property(CComBSTR("Ls2"),CComVariant(m_Ls2));
   pSave->put_Property(CComBSTR("PointFactory"),CComVariant(m_PointFactory));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CHorzCurve::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("HorzCurve"));

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

   pLoad->get_Property(CComBSTR("Ls1"),&var);
   put_SpiralLength(spEntry,var.dblVal);

   pLoad->get_Property(CComBSTR("Ls2"),&var);
   put_SpiralLength(spExit,var.dblVal);

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
Float64 CHorzCurve::SpiralX(Float64 ls,Float64 angle)
{
   return ls*(1 -  pow(angle,2)/10 + pow(angle,4)/216 - pow(angle,6)/9360);
}

Float64 CHorzCurve::SpiralY(Float64 ls,Float64 angle)
{
   return ls*(angle/3 - pow(angle,3)/42 + pow(angle,5)/1320 - pow(angle,7)/75600);
}

void CHorzCurve::PointOnEntrySpiral(Float64 distFromTS,IPoint2d** pVal)
{
   CComPtr<IAngle> objAngle;
   get_SpiralAngle(spEntry,&objAngle);
   Float64 angle;
   objAngle->get_Value(&angle);


   Float64 sweepAngle = pow(distFromTS/m_Ls1,2) * angle;

   Float64 x = SpiralX(distFromTS,sweepAngle);
   Float64 y = SpiralY(distFromTS,sweepAngle);

   PointOnEntrySpiral(x,y,pVal);
}

void CHorzCurve::PointOnExitSpiral(Float64 distFromST,IPoint2d** pVal)
{
   CComPtr<IAngle> objAngle;
   get_SpiralAngle(spExit,&objAngle);
   Float64 angle;
   objAngle->get_Value(&angle);

   Float64 sweepAngle; // sweep angle measured from the end of the curve
   sweepAngle = pow(distFromST/m_Ls2,2) * angle;

   Float64 x = SpiralX(distFromST,sweepAngle);
   Float64 y = SpiralY(distFromST,sweepAngle);

   PointOnExitSpiral(x,y,pVal);
}

void CHorzCurve::PointOnEntrySpiral(Float64 x,Float64 y,IPoint2d** pVal)
{
   // Setup a coordinate system at TS, with positive X going from TS to PI.
   // SC will be at point (X,kY) in this coordinate system.
   // k = 1 for left curves and -1 for right curves
   // Transform SC into the global coordinate system
   CComPtr<IPoint2d> TS;
   get_TS(&TS);

   m_Xform->putref_NewOrigin(TS);

   CComPtr<IDirection> dir;
   Float64 dist;
   cogoUtil::Inverse(TS,m_PI,&dist,&dir);
   Float64 rotAngle;
   dir->get_Value(&rotAngle);
   m_Xform->put_RotationAngle(rotAngle);

   CurveDirectionType cd;
   get_Direction(&cd);
   Float64 k = (cd == cdLeft ? 1 : -1);

   m_PointFactory->CreatePoint(pVal);
   (*pVal)->put_X(x);
   (*pVal)->put_Y(k*y);
   CComQIPtr<IPoint2d> pnt(*pVal);
   m_Xform->Xform(&pnt.p,xfrmNewToOld);
}

void CHorzCurve::PointOnExitSpiral(Float64 x,Float64 y,IPoint2d** pVal)
{
   // Setup a coordinate system at ST, with positive X going from ST to PI
   // CS will be at point (X,kY) in this coordinate system
   // k = -1 for left curves and 1 for right curves
   // Transform CS into the global coordinate system
   CComPtr<IPoint2d> ST;
   get_ST(&ST);

   m_Xform->putref_NewOrigin(ST);

   CComPtr<IDirection> dir;
   Float64 dist;
   cogoUtil::Inverse(ST,m_PI,&dist,&dir);
   Float64 rotAngle;
   dir->get_Value(&rotAngle);
   m_Xform->put_RotationAngle(rotAngle);

   CurveDirectionType cd;
   get_Direction(&cd);
   Float64 k = (cd == cdLeft ? -1 : 1);

   m_PointFactory->CreatePoint(pVal);
   (*pVal)->put_X(x);
   (*pVal)->put_Y(k*y);
   CComQIPtr<IPoint2d> pnt(*pVal);
   m_Xform->Xform(&pnt.p,xfrmNewToOld);
}

void CHorzCurve::ProjectPointOnEntrySpiral(IPoint2d* point,Float64* pDistFromStart,IPoint2d** newPoint)
{
   CEntrySpiralFunction function(this,point,m_GeomUtil);

   Float64 Ls;
   get_SpiralLength(spEntry,&Ls);

   mathBrentsRootFinder2d rootFinder;
   Float64 dist = rootFinder.FindRootInRange(function,0,Ls,0.00001);

   PointOnEntrySpiral(dist,newPoint);

   *pDistFromStart = dist;
}

void CHorzCurve::ProjectPointOnExitSpiral(IPoint2d* point,Float64* pDistFromStart,IPoint2d** newPoint)
{
   CExitSpiralFunction function(this,point,m_GeomUtil);

   Float64 Ls;
   get_SpiralLength(spExit,&Ls);

   mathBrentsRootFinder2d rootFinder;
   Float64 dist = rootFinder.FindRootInRange(function,0,Ls,0.00001); // dist from end

   PointOnExitSpiral(dist,newPoint);

   Float64 Lt;
   get_TotalLength(&Lt);

   *pDistFromStart = Lt - dist;
}

void CHorzCurve::ProjectPoint(IPoint2d* point,Float64* pDistFromStart, IPoint2d* *pNewPoint)
{
   // The first thing we have to do is determine if the point is before the curve,
   // within the bounds of the curve, or after the curve.

   // We will do this by setting up a coordinate system at each end of the curve and transform
   // the point into those systems.

   // Setup the first coordinate system, with origin at TS and X towards PI
   CComPtr<IPoint2d> origin;
   get_TS(&origin);
   
   CComPtr<IDirection> brg;
   get_BkTangentBrg(&brg);
   Float64 dir;
   brg->get_Value(&dir);

   m_Xform->putref_NewOrigin(origin);
   m_Xform->put_RotationAngle(dir);

   CComPtr<IPoint2d> xfrmPoint;
   m_Xform->XformEx(point,xfrmOldToNew,&xfrmPoint);
   Float64 x1; // X ordinate in coordinate system 1
   xfrmPoint->get_X(&x1);
//   x1 = IsZero(x1) ? 0.00 : x1;

#if defined _DEBUG
   // X coordinate of CC should be zero
   CComPtr<IPoint2d> cc;
   get_CC(&cc);
   CComQIPtr<IPoint2d> cc2(cc);
   m_Xform->Xform(&cc2.p,xfrmOldToNew);
   Float64 ccx, ccy;
   cc->get_X(&ccx);
   ATLASSERT( IsZero(ccx) );

   cc->get_Y(&ccy);
   CurveDirectionType dirType;
   get_Direction(&dirType);
   if ( dirType == cdRight )
      ATLASSERT( ccy < 0 );
   else
      ATLASSERT( ccy > 0 );
#endif // _DEBUG

   // Setup the second coordinate system, with origin at ST and X towards PI
   origin.Release();
   brg.Release();
   xfrmPoint.Release();

   get_ST(&origin);
   get_FwdTangentBrg(&brg);
   brg->get_Value(&dir);

   m_Xform->putref_NewOrigin(origin);
   m_Xform->put_RotationAngle(dir + M_PI);
   m_Xform->XformEx(point,xfrmOldToNew,&xfrmPoint);
   Float64 x2;
   xfrmPoint->get_X(&x2);
//   x2 = IsZero(x2) ? 0.00 : x2;

#if defined _DEBUG
   // X coordinate of CC should be zero
   cc.Release();
   get_CC(&cc);
   cc2.Release();
   cc.QueryInterface(&cc2);
   m_Xform->Xform(&cc2.p,xfrmOldToNew);
   cc->get_X(&ccx);
   ATLASSERT( IsZero(ccx) );

   cc->get_Y(&ccy);
   get_Direction(&dirType);
   if ( dirType == cdRight )
      ATLASSERT( ccy > 0 );
   else
      ATLASSERT( ccy < 0 );
#endif // _DEBUG
   
   if ( x1 < 0 && x2 < 0 )
   {
      // Point projects onto both the foward and back tangents
      // Find the point nearest the curve. If equal distance, take the
      // point on the foward tangent

      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IPoint2d> pbt, pi;
      get_PBT(&pbt);
      get_PI(&pi);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pbt,pi);

      CComPtr<IPoint2d> p1;
      m_GeomUtil->PointOnLineNearest(line,point,&p1);

      // Create a line object along the foward tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IPoint2d> pft;
      get_PFT(&pft);

      line->ThroughPoints(pi,pft);

      CComPtr<IPoint2d> p2;
      m_GeomUtil->PointOnLineNearest(line,point,&p2);

      Float64 d1, d2;
      m_GeomUtil->Distance(point,p1,&d1);
      m_GeomUtil->Distance(point,p2,&d2);

      if ( d1 < d2 )
      {
         // Point projects onto the back tangent bearing (it is before the curve)
         p1.QueryInterface(pNewPoint);
         ATLASSERT( *pNewPoint != nullptr );

         CComPtr<IPoint2d> ts;
         get_TS(&ts);
         m_GeomUtil->Distance(ts,p1,pDistFromStart);
         (*pDistFromStart) *= -1;

         ATLASSERT( (*pDistFromStart) <= 0 ); // must be negative because it is before the curve
      }
      else
      {
         // Point projects onto the forward tangent bearing (it is after the curve)
         p2.QueryInterface(pNewPoint);
         ATLASSERT( *pNewPoint != nullptr );

         Float64 Lt; // Total length of curve
         get_TotalLength(&Lt);

         CComPtr<IPoint2d> st;
         get_ST(&st);
         m_GeomUtil->Distance(st,p2,pDistFromStart);
         (*pDistFromStart) += Lt;

         ATLASSERT( (*pDistFromStart) >= 0 && (*pDistFromStart) >= Lt );
      }
   }
   else if ( x1 < 0 )
   {
      // Point is before the curve
      // Create a line object along the back tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IPoint2d> pbt, pi;
      get_PBT(&pbt);
      get_PI(&pi);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pbt,pi);

      CComPtr<IPoint2d> p;
      m_GeomUtil->PointOnLineNearest(line,point,&p);
      p.QueryInterface(pNewPoint);
      ATLASSERT( *pNewPoint != nullptr );

      CComPtr<IPoint2d> ts;
      get_TS(&ts);
      m_GeomUtil->Distance(ts,*pNewPoint,pDistFromStart);
      (*pDistFromStart) *= -1;

      ATLASSERT( (*pDistFromStart) <= 0 ); // must be negative because it is before the curve
   }
   else if ( 0 <= x1 && 0 <= x2 )
   {
      // Point is within bounds of curve
      // Need to determine if it is within the bounds of the entry spiral,
      // the circular curve, or the exit spiral

      // Create coordinate system at SC towards PCI
      CComPtr<IPoint2d> sc;
      get_SC(&sc);

      brg.Release();
      get_CurveBkTangentBrg(&brg);
      brg->get_Value(&dir);
      m_Xform->putref_NewOrigin(sc);
      m_Xform->put_RotationAngle(dir);
      
      CComPtr<IPoint2d> point1;
      m_Xform->XformEx(point,xfrmOldToNew,&point1);
      point1->get_X(&x1);
//      x1 = IsZero(x1) ? 0.00 : x1;

      // Create coordinate system at CS toward PCI
      CComPtr<IPoint2d> cs;
      get_CS(&cs);
      brg.Release();
      get_CurveFwdTangentBrg(&brg);
      brg->get_Value(&dir);
      m_Xform->putref_NewOrigin(cs);
      m_Xform->put_RotationAngle(dir + M_PI);
      
      CComPtr<IPoint2d> point2;
      m_Xform->XformEx(point,xfrmOldToNew,&point2);
      point2->get_X(&x2);
//      x2 = IsZero(x2) ? 0.00 : x2;

      if ( x1 < 0 && x2 < 0 )
      {
         // Point projects onto both the entry and exit spirals. Find the point
         // that is nearest.
         CComPtr<IPoint2d> prjPoint1, prjPoint2;
         Float64 dist1, dist2;
         ProjectPointOnEntrySpiral(point,&dist1,&prjPoint1);
         ProjectPointOnExitSpiral(point,&dist2,&prjPoint2);

         Float64 d1, d2;
         m_GeomUtil->Distance(point,prjPoint1,&d1);
         m_GeomUtil->Distance(point,prjPoint2,&d2);


         if ( d1 < d2 )
         {
            // Point is projected onto the entry spiral
            (*pNewPoint) = prjPoint1;
            (*pNewPoint)->AddRef();

            (*pDistFromStart) = dist1;
         }
         else
         {
            // Point is projected onto the exit spiral
            (*pNewPoint) = prjPoint2;
            (*pNewPoint)->AddRef();

            (*pDistFromStart) = dist2;
         }
      }
      else if ( x1 < 0 )
      {
         // Entry spiral
         ProjectPointOnEntrySpiral(point,pDistFromStart,pNewPoint);
         ATLASSERT(pNewPoint != nullptr);
      }
      else if ( 0 <= x1 && 0 <= x2 )
      {
         // Circular curve

         // Create a line from CCC through the projected point
         // Intersect this line with the circular arc, finding the
         // point that is nearest SC.
         CComPtr<IPoint2d> ccc;
         get_CCC(&ccc);

         CComPtr<ILine2d> line;
         line.CoCreateInstance(CLSID_Line2d);
         line->ThroughPoints(ccc,point);

         CComPtr<ICircle> circle;
         circle.CoCreateInstance(CLSID_Circle);
         circle->putref_Center(ccc);
         circle->put_Radius(m_Radius);

         CComPtr<IPoint2d> sc;
         get_SC(&sc);

         cogoUtil::LineCircleIntersect(line,circle,point,m_PointFactory,pNewPoint);
         ATLASSERT(pNewPoint != nullptr);

         CurveDirectionType dir;
         get_Direction(&dir);
         Float64 angle;
         if ( dir == cdRight )
            m_GeomUtil->Angle(*pNewPoint,ccc,sc,&angle);
         else
            m_GeomUtil->Angle(sc,ccc,*pNewPoint,&angle);

#if defined _DEBUG
         // The subtended angle must be less than or equal to the
         // circular curve angle (or the point isn't on the circular
         // part of the curve)
         CComPtr<IAngle> cca;
         Float64 delta;
         get_CircularCurveAngle(&cca);
         cca->get_Value(&delta);
         ATLASSERT( IsLE(angle,delta) );
#endif // _DEBUG

         ATLASSERT(angle >= 0);
         Float64 dist = m_Radius * angle;
         Float64 Ls;
         get_SpiralLength(spEntry,&Ls);
         *pDistFromStart = Ls + dist;
      }
      else if ( x2 < 0 )
      {
         // Exit spiral
         ProjectPointOnExitSpiral(point,pDistFromStart,pNewPoint);
         ATLASSERT(pNewPoint != nullptr);
      }
      else
      {
         ATLASSERT(false); // Shouldn't get here
      }

   }
   else if ( x2 < 0 )
   {
      // Point is after the curve
      // Create a line object along the foward tangent bearing. Locate the point on
      // that line that is nearest the input point
      CComPtr<IPoint2d> pft, pi;
      get_PFT(&pft);
      get_PI(&pi);

      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pi,pft);

      CComPtr<IPoint2d> p;
      m_GeomUtil->PointOnLineNearest(line,point,&p);
      p.QueryInterface(pNewPoint);
      ATLASSERT( *pNewPoint != nullptr );

      Float64 Lt;
      get_TotalLength(&Lt);
      CComPtr<IPoint2d> st;
      get_ST(&st);
      m_GeomUtil->Distance(st,*pNewPoint,pDistFromStart);
      (*pDistFromStart) += Lt;

      ATLASSERT( (*pDistFromStart) >= 0 && (*pDistFromStart) >= Lt );
   }
}

void CHorzCurve::GetBkTangentLine(ILine2d** line)
{
   CComPtr<ILine2d> pLine;
   pLine.CoCreateInstance(CLSID_Line2d);
   pLine->ThroughPoints(m_PBT,m_PI);

   (*line) = pLine;
   (*line)->AddRef();
}

void CHorzCurve::GetFwdTangentLine(ILine2d** line)
{
   CComPtr<ILine2d> pLine;
   pLine.CoCreateInstance(CLSID_Line2d);
   pLine->ThroughPoints(m_PI,m_PFT);

   (*line) = pLine;
   (*line)->AddRef();
}

bool CHorzCurve::LineParallelToTangent(ILine2d* pTangentLine,ILine2d* pLine,IPoint2d* pTangentPoint)
{
   CComPtr<IPoint2d> CC;
   get_CC(&CC);

   VARIANT_BOOL bParallel;
   m_GeomUtil->AreLinesParallel(pTangentLine,pLine,&bParallel);
   if ( bParallel == VARIANT_FALSE ) // not parallel means there can be an intersection
      return false;

   Float64 dist1;
   m_GeomUtil->Distance(pTangentPoint,CC,&dist1);

   CComPtr<IPoint2d> poln;
   m_GeomUtil->PointOnLineNearest(pLine,CC,&poln);

   Float64 dist2;
   m_GeomUtil->Distance(CC,poln,&dist2);

   if ( dist1 < dist2 && cogoUtil::IsPointBeforeStart(pTangentPoint,CC,poln) )
      return true; // line is parallel to tangent and on the outside of the curve... no intersections

   // lines are parallel, but line is on the inside of the curve so an intersection is possible
   return false;
}

void CHorzCurve::GetCurveCenterNormalIntersectPoints(IPoint2d** pPOBT,IPoint2d** pPOFT)
{
   // get length of curve
   Float64 length;
   get_TotalLength(&length);

   // get point on curve at half length
   CComPtr<IPoint2d> POC;
   PointOnCurve(length/2,&POC);

   // get bearing at POC
   CComPtr<IDirection> bearing;
   Bearing(length/2,&bearing);

   // convert bearing to a vector
   Float64 angle;
   bearing->get_Value(&angle);

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_X(cos(angle));
   v->put_Y(sin(angle));

   // create a line parallel to curve at POC
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(POC,v);

   // intersect line with back tangent
   CComPtr<ILine2d> bkTangentLine;
   GetBkTangentLine(&bkTangentLine);

   m_GeomUtil->LineLineIntersect(line,bkTangentLine,pPOBT);
   ATLASSERT(pPOBT != nullptr);

   // intersect line with forward tangent
   CComPtr<ILine2d> fwdTangentLine;
   GetFwdTangentLine(&fwdTangentLine);

   m_GeomUtil->LineLineIntersect(line,fwdTangentLine,pPOFT);
   ATLASSERT(pPOFT != nullptr);
}

bool CHorzCurve::IsPointOnCurve(IPoint2d* pPoint)
{
   Float64 dist;
   HRESULT hr = DistanceFromStart(pPoint,&dist);
   ATLASSERT( SUCCEEDED(hr) );

   CComPtr<IPoint2d> pntOnCurve;
   hr = PointOnCurve(dist,&pntOnCurve);

   ATLASSERT( SUCCEEDED(hr) );

   m_GeomUtil->Distance(pPoint,pntOnCurve,&dist);
   return IsZero(dist,tolerance);
}

bool CHorzCurve::IsPointOnLine(ILine2d* pLine,IPoint2d* pPoint)
{
   Float64 dist;
   m_GeomUtil->ShortestDistanceToPoint(pLine,pPoint,&dist);
   return IsZero(dist,tolerance);
}

bool CHorzCurve::TestIntersection(ILine2d* pLine,IPoint2d* pPoint)
{
   return IsPointOnCurve(pPoint) && IsPointOnLine(pLine,pPoint);
}