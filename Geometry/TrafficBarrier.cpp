///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TrafficBarrier.cpp : Implementation of CTrafficBarrier
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "TrafficBarrier.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrafficBarrier
STDMETHODIMP CTrafficBarrier::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITrafficBarrier,
		&IID_IShape,
		&IID_IXYPosition
	};
	for (int i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTrafficBarrier::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Barrier.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CTrafficBarrier::FinalRelease()
{
}

void CTrafficBarrier::SetShape(const WBFL::Geometry::TrafficBarrier& shape)
{
   m_Barrier = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Barrier.GetHookPoint());
}

STDMETHODIMP CTrafficBarrier::get_X1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetX1();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X1(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetX1(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   
   *pVal = m_Barrier.GetX2();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X2(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetX2(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetX3();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X3(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetX3(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetX4();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X4(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetX4(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_X5(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetX5();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_X5(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetX5(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y1(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetY1();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y1(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetY1(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y2(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetY2();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y2(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetY2(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y3(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetY3();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y3(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetY3(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Y4(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Barrier.GetSlabDepth();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Y4(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_ITrafficBarrier,GEOMETRY_E_DIMENSION);

   m_Barrier.SetSlabDepth(newVal);
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Orientation(TrafficBarrierOrientation* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = (TrafficBarrierOrientation)m_Barrier.GetOrientation();
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::put_Orientation(TrafficBarrierOrientation newVal)
{
   m_Barrier.SetOrientation(WBFL::Geometry::TrafficBarrier::Orientation(newVal));
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_HookPoint(IPoint2d ** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CTrafficBarrier::putref_HookPoint(IPoint2d *hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Barrier.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CTrafficBarrier::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CTrafficBarrier::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
