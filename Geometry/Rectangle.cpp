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

// Rectangle.cpp : Implementation of CRectangle
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Rectangle.h"
#include "Helper.h"
#include "Point2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectangle
STDMETHODIMP CRectangle::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
      &IID_IRectangle,
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

HRESULT CRectangle::FinalConstruct()
{
   CComObject<CPoint2d>* pHookPt;
   CComObject<CPoint2d>::CreateInstance(&pHookPt);

   pHookPt->SetPoint(m_Rectangle.GetHookPoint());

   pHookPt->QueryInterface(&m_HookPoint);

   return S_OK;
}

void CRectangle::FinalRelease()
{
}

void CRectangle::SetShape(const WBFL::Geometry::Rectangle& shape)
{
   m_Rectangle = shape;
   dynamic_cast<CPoint2d*>(m_HookPoint.p)->SetPoint(m_Rectangle.GetHookPoint());
}

STDMETHODIMP CRectangle::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Rectangle.GetHeight();
	return S_OK;
}

STDMETHODIMP CRectangle::put_Height(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IRectangle,GEOMETRY_E_DIMENSION);

   m_Rectangle.SetHeight(newVal);

   return S_OK;
}

STDMETHODIMP CRectangle::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Rectangle.GetWidth();
	return S_OK;
}

STDMETHODIMP CRectangle::put_Width(Float64 newVal)
{
   if ( newVal < 0 )
      return Error(IDS_E_DIMENSION,IID_IRectangle,GEOMETRY_E_DIMENSION);

   m_Rectangle.SetWidth(newVal);

	return S_OK;
}

STDMETHODIMP CRectangle::get_HookPoint(IPoint2d ** hookPnt)
{
   CHECK_RETOBJ(hookPnt);
   return m_HookPoint.CopyTo(hookPnt);
}

STDMETHODIMP CRectangle::putref_HookPoint(IPoint2d *hookPnt)
{
   CHECK_IN(hookPnt);
   m_HookPoint = hookPnt;
   m_Rectangle.SetHookPoint(GetInnerPoint(m_HookPoint));
   return S_OK;
}

STDMETHODIMP CRectangle::get_Shape(IShape **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IShape, (void**)pVal );
}

STDMETHODIMP CRectangle::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return QueryInterface( IID_IXYPosition, (void**)pVal );
}
