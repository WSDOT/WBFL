///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// CircularSegment.cpp : Implementation of CCircularSegment
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "CircularSegment.h"
#include "Point2d.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCircularSegment
HRESULT CCircularSegment::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_CircularSegment.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CCircularSegment::FinalRelease()
{
}

void CCircularSegment::SetShape(const WBFL::Geometry::CircularSegment& shape)
{ 
   m_CircularSegment = shape; 
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_CircularSegment.GetHookPoint());
}

STDMETHODIMP CCircularSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICircularSegment,
      &IID_IShape,
      &IID_IXYPosition
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCircularSegment::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CCircularSegment::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}

STDMETHODIMP CCircularSegment::get_HookPoint(IPoint2d ** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CCircularSegment::putref_HookPoint(IPoint2d * hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_CircularSegment.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CCircularSegment::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_CircularSegment.GetRadius();
	return S_OK;
}

STDMETHODIMP CCircularSegment::put_Radius(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_RADIUS,IID_ICircularSegment,GEOMETRY_E_RADIUS);

   m_CircularSegment.SetRadius(newVal);

	return S_OK;
}

STDMETHODIMP CCircularSegment::get_Center(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_CircularSegment.GetCenter(), pVal);
}

STDMETHODIMP CCircularSegment::put_Center(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_CircularSegment.SetCenter(GetPoint(newVal));
   return S_OK;
}

STDMETHODIMP CCircularSegment::get_MidOrdinate(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_CircularSegment.GetMidOrdinate();
	return S_OK;
}

STDMETHODIMP CCircularSegment::put_MidOrdinate(Float64 newVal)
{
   try { m_CircularSegment.SetMidOrdinate(newVal); }
   catch(...) { return Error(IDS_E_MIDORDINATE, IID_ICircularSegment, GEOMETRY_E_MIDORDINATE); }

   return S_OK;
}

STDMETHODIMP CCircularSegment::get_Chord(ILineSegment2d** ppChord)
{
   CHECK_RETOBJ(ppChord);
   return CreateLineSegment(m_CircularSegment.GetChord(), ppChord);
}

STDMETHODIMP CCircularSegment::get_InteriorAngle(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_CircularSegment.GetInteriorAngle();
	return S_OK;
}

STDMETHODIMP CCircularSegment::put_InteriorAngle(Float64 newVal)
{
   if ( newVal < 0 || TWO_PI < newVal)
      return Error(IDS_E_ANGLE,IID_ICircularSegment,GEOMETRY_E_ANGLE);

   m_CircularSegment.SetInteriorAngle(newVal);

	return S_OK;
}

STDMETHODIMP CCircularSegment::get_Rotation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_CircularSegment.GetRotation();
   return S_OK;
}

STDMETHODIMP CCircularSegment::put_Rotation(Float64 newVal)
{
   m_CircularSegment.SetRotation(newVal);
   return S_OK;
}
