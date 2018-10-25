///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// LineSegment2d.cpp : Implementation of CLineSegment2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "LineSegment2d.h"
#include "Point2d.h"
#include "Helper.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineSegment2d

STDMETHODIMP CLineSegment2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILineSegment2d,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLineSegment2d::FinalConstruct()
{
   HRESULT hr = S_OK;

   hr = CreatePoint(0.00,0.00,NULL,&m_pStart );
   if ( FAILED(hr) )
      return hr;

   hr = CrAdvise(m_pStart, this, IID_IPoint2dEvents, &m_dwStartCookie);
   if ( FAILED(hr) )
      return hr;

   hr = CreatePoint(1.00,0.00,NULL,&m_pEnd );
   if ( FAILED(hr) )
      return hr;

   hr = CrAdvise(m_pEnd, this, IID_IPoint2dEvents, &m_dwEndCookie);
   if ( FAILED(hr) )
      return hr;

   m_bEventsOn = true;

   return S_OK;
}

void CLineSegment2d::FinalRelease()
{
   CrUnadvise(m_pStart, this, IID_IPoint2dEvents, m_dwStartCookie);
   CrUnadvise(m_pEnd,   this, IID_IPoint2dEvents, m_dwEndCookie  );
}

STDMETHODIMP CLineSegment2d::get_StartPoint(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   m_pStart->QueryInterface( pVal );

   return S_OK;
}

STDMETHODIMP CLineSegment2d::putref_StartPoint(IPoint2d *newVal)
{
   CHECK_IN(newVal);

   HRESULT hr = CrAssignPointer(m_pStart, newVal, this, IID_IPoint2dEvents, &m_dwStartCookie);
   if ( SUCCEEDED(hr) )
      Fire_OnLineSegmentChanged(this);

   return S_OK;
}

STDMETHODIMP CLineSegment2d::get_EndPoint(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   m_pEnd->QueryInterface( pVal );

   return S_OK;
}  

STDMETHODIMP CLineSegment2d::putref_EndPoint(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   HRESULT hr = CrAssignPointer(m_pEnd, newVal, this, IID_IPoint2dEvents, &m_dwEndCookie);
   if ( SUCCEEDED(hr) )
      Fire_OnLineSegmentChanged(this);

   return S_OK;
}

STDMETHODIMP CLineSegment2d::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   CComPtr<IGeomUtil2d> pUtil;
   CreateGeomUtil(&pUtil);
   return pUtil->Distance(m_pStart,m_pEnd,pVal);
}

STDMETHODIMP CLineSegment2d::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   EventsOff();
   m_pStart->Rotate( cx, cy, angle );
   m_pEnd->Rotate( cx, cy, angle );
   EventsOn();

   return S_OK;
}

STDMETHODIMP CLineSegment2d::RotateEx(IPoint2d *pCenter, Float64 angle)
{
   CHECK_IN(pCenter);

   Float64 x,y;
   pCenter->get_X(&x);
   pCenter->get_Y(&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CLineSegment2d::Offset2(Float64 distance)
{
   Float64 sx,sy;
   m_pStart->Location(&sx,&sy);

   Float64 ex,ey;
   m_pEnd->Location(&ex,&ey);

   Float64 dx = ex - sx;
   Float64 dy = ey - sy;
   Float64 length = sqrt(dx*dx + dy*dy);

   Float64 x = 0;
   Float64 y = 0;
   if ( !IsZero(length) )
   {
      x = -distance*dy/length;
      y =  distance*dx/length;
   }

   return Offset(x,y);
}

STDMETHODIMP CLineSegment2d::Offset(Float64 dx, Float64 dy)
{
   EventsOff();
   m_pStart->Offset(dx,dy);
   m_pEnd->Offset(dx,dy);
   EventsOn();
	return S_OK;
}

STDMETHODIMP CLineSegment2d::OffsetEx(ISize2d *pSize)
{
   CHECK_IN(pSize);

   EventsOff();
   m_pStart->OffsetEx( pSize );
   m_pEnd->OffsetEx( pSize );
   EventsOn();

   return S_OK;
}

STDMETHODIMP CLineSegment2d::ThroughPoints(IPoint2d* p1, IPoint2d* p2)
{
   CHECK_IN(p1);
   CHECK_IN(p2);

   HRESULT hr = CrAssignPointer(m_pStart, p1, this, IID_IPoint2dEvents, &m_dwStartCookie);
   if ( FAILED(hr) )
      return hr;

   hr = CrAssignPointer(m_pEnd, p2, this, IID_IPoint2dEvents, &m_dwEndCookie);
   if ( FAILED(hr) )
      return hr;

   Fire_OnLineSegmentChanged(this);
   return S_OK;
}

STDMETHODIMP CLineSegment2d::Clone(ILineSegment2d** ppClone)
{
   CHECK_RETOBJ(ppClone);
   CComObject<CLineSegment2d>* pClone;
   CComObject<CLineSegment2d>::CreateInstance(&pClone);
   (*ppClone) = pClone;
   (*ppClone)->AddRef();

   CComPtr<IPoint2d> start,end;
   m_pStart->Clone(&start);
   m_pEnd->Clone(&end);

   pClone->ThroughPoints(start,end);

   return S_OK;
}

STDMETHODIMP CLineSegment2d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CLineSegment2d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CLineSegment2d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("LineSegment2d"),1.0);
   pSave->put_Property(CComBSTR("Start"),CComVariant(m_pStart));
   pSave->put_Property(CComBSTR("End"),  CComVariant(m_pEnd));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CLineSegment2d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("LineSegment2d"));
   
   CrUnadvise(m_pStart, this, IID_IPoint2dEvents, m_dwStartCookie);
   m_pStart.Release();

   pLoad->get_Property(CComBSTR("Start"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pStart,&var)) )
      return STRLOAD_E_INVALIDFORMAT;
   
   CrUnadvise(m_pEnd,   this, IID_IPoint2dEvents, m_dwEndCookie  );
   m_pEnd.Release();

   pLoad->get_Property(CComBSTR("End"),&var);
   if ( FAILED( _CopyVariantToInterface<IPoint2d>::copy(&m_pEnd,&var)) )
      return STRLOAD_E_INVALIDFORMAT;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}


void CLineSegment2d::EventsOff()
{
   m_bEventsOn = false;
}

void CLineSegment2d::EventsOn(bool bFire)
{
   m_bEventsOn = true;

   if ( bFire )
      Fire_OnLineSegmentChanged(this);
}
