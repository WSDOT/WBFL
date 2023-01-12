///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// Circle.cpp : Implementation of CCircle
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Circle.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT CCircle::FinalConstruct()
{
   CComObject<CPoint2d>* pCenter;
   CComObject<CPoint2d>::CreateInstance(&pCenter);

   pCenter->SetPoint(m_Circle.GetHookPoint());

   pCenter->QueryInterface(&m_pCenter);

   return S_OK;
}

void CCircle::SetShape(const WBFL::Geometry::Circle& shape)
{
   m_Circle = shape;
   dynamic_cast<CPoint2d*>(m_pCenter.p)->SetPoint(m_Circle.GetHookPoint());
}

STDMETHODIMP CCircle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICircle,
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

/////////////////////////////////////////////////////////////////////////////
// CCircle
STDMETHODIMP CCircle::get_Radius(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Circle.GetRadius();
	return S_OK;
}

STDMETHODIMP CCircle::put_Radius(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_RADIUS,IID_ICircle,GEOMETRY_E_RADIUS);

   m_Circle.SetRadius(newVal);
	return S_OK;
}

STDMETHODIMP CCircle::get_Center(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_pCenter.CopyTo(pVal);
}

STDMETHODIMP CCircle::putref_Center(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_pCenter = newVal;
   m_Circle.SetHookPoint(GetInnerPoint(m_pCenter));
   return S_OK;
}

STDMETHODIMP CCircle::ThroughTwoPoints(IPoint2d* p1,IPoint2d* p2)
{
   CHECK_IN(p1);
   CHECK_IN(p2);

   try
   {
      m_Circle.ThroughTwoPoints(::GetPoint(p1), ::GetPoint(p2));
   }
   catch (...)
   {
      return Error(IDS_E_COINCIDENTPOINTS, IID_ICircle, GEOMETRY_E_COINCIDENTPOINTS);
   }

   return S_OK;
}

STDMETHODIMP CCircle::ThroughThreePoints(IPoint2d* p1,IPoint2d* p2,IPoint2d* p3)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_IN(p3);

   try
   {
      m_Circle.ThroughThreePoints(::GetPoint(p1), ::GetPoint(p2), ::GetPoint(p3));
   }
   catch (...)
   {
      return Error(IDS_E_COLINEAR, IID_ICircle, GEOMETRY_E_COLINEAR);
   }

   return S_OK;
}

STDMETHODIMP CCircle::ContainsPoint(IPoint2d* p,VARIANT_BOOL* pResult)
{
   CHECK_IN(p);
   CHECK_RETVAL(pResult);
   *pResult = MakeBool(m_Circle.PointInShape(::GetPoint(p)));
   return S_OK;
}

STDMETHODIMP CCircle::PointOnCircle(IPoint2d* p,VARIANT_BOOL* pResult)
{
   CHECK_IN(p);
   CHECK_RETVAL(pResult);
   *pResult = MakeBool(m_Circle.PointOnCircle(::GetPoint(p)));
   return S_OK;
}

STDMETHODIMP CCircle::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CCircle::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
