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

// Triangle.cpp : Implementation of CTriangle
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Triangle.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTriangle
HRESULT CTriangle::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Triangle.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CTriangle::FinalRelease()
{
}

void CTriangle::SetShape(const WBFL::Geometry::Triangle& shape)
{
   m_Triangle = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Triangle.GetHookPoint());
}

STDMETHODIMP CTriangle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITriangle,
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

STDMETHODIMP CTriangle::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Triangle.GetWidth();
	return S_OK;
}

STDMETHODIMP CTriangle::put_Width(Float64 newVal)
{
   m_Triangle.SetWidth(newVal);
   return S_OK;
}

STDMETHODIMP CTriangle::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Triangle.GetHeight();
	return S_OK;
}

STDMETHODIMP CTriangle::put_Height(Float64 newVal)
{
   m_Triangle.SetHeight(newVal);
   return S_OK;
}

STDMETHODIMP CTriangle::get_Offset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Triangle.GetOffset();
	return S_OK;
}

STDMETHODIMP CTriangle::put_Offset(Float64 newVal)
{
   m_Triangle.SetOffset(newVal);
   return S_OK;
}

STDMETHODIMP CTriangle::get_HookPoint(IPoint2d** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CTriangle::putref_HookPoint(IPoint2d* hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Triangle.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CTriangle::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CTriangle::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
