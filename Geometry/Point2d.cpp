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

// Point2d.cpp : Implementation of CPoint2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Point2d.h"

#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPoint2d

STDMETHODIMP CPoint2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPoint2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CPoint2d::FinalConstruct()
{
   return S_OK;
}

void CPoint2d::FinalRelease()
{
}

STDMETHODIMP CPoint2d::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_pPoint->X();

	return S_OK;
}

STDMETHODIMP CPoint2d::put_X(Float64 newVal)
{
   m_pPoint->X() = newVal;
	return S_OK;
}

STDMETHODIMP CPoint2d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_pPoint->Y();

	return S_OK;
}

STDMETHODIMP CPoint2d::put_Y(Float64 newVal)
{
   m_pPoint->Y() = newVal;
	return S_OK;
}

STDMETHODIMP CPoint2d::Move(Float64 x, Float64 y)
{
   m_pPoint->Move(x, y);
	return S_OK;
}

STDMETHODIMP CPoint2d::MoveEx(IPoint2d *pPoint)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->Location(&x,&y);

   return Move(x,y);
}

STDMETHODIMP CPoint2d::Offset(Float64 dx, Float64 dy)
{
   m_pPoint->Offset(dx, dy);
	return S_OK;
}

STDMETHODIMP CPoint2d::OffsetEx(ISize2d *pSize)
{
   CHECK_IN(pSize);

   Float64 dx, dy;
   pSize->Dimensions(&dx,&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CPoint2d::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   m_pPoint->Rotate(WBFL::Geometry::Point2d(cx, cy), angle);
	return S_OK;
}

STDMETHODIMP CPoint2d::RotateEx(IPoint2d *pCenter, Float64 angle)
{
   CHECK_IN(pCenter);

   Float64 cx,cy;
   pCenter->Location(&cx,&cy);

   return Rotate(cx,cy,angle);
}

STDMETHODIMP CPoint2d::Distance(Float64 x,Float64 y,Float64* pDistance)
{
   CHECK_RETVAL(pDistance);
   *pDistance = m_pPoint->Distance(WBFL::Geometry::Point2d(x, y));
   return S_OK;
}

STDMETHODIMP CPoint2d::DistanceEx(IPoint2d* pOther,Float64* pDistance)
{
   CHECK_IN(pOther);
   Float64 x,y;
   pOther->Location(&x,&y);
   return Distance(x,y,pDistance);
}

STDMETHODIMP CPoint2d::Size(Float64 x, Float64 y, ISize2d** ppSize)
{
   CHECK_RETOBJ(ppSize);
   Float64 dx = m_pPoint->X() - x;
   Float64 dy = m_pPoint->Y() - y;
   CComPtr<ISize2d> size;
   size.CoCreateInstance(CLSID_Size2d);
   size->put_Dx(dx);
   size->put_Dy(dy);
   size.CopyTo(ppSize);
   return S_OK;
}

STDMETHODIMP CPoint2d::SizeEx(IPoint2d* pPoint, ISize2d** ppSize)
{
   CHECK_IN(pPoint);
   Float64 x, y;
   pPoint->Location(&x, &y);
   return Size(x, y, ppSize);
}

STDMETHODIMP CPoint2d::SameLocation(IPoint2d* pOther)
{
   CHECK_IN(pOther);

   Float64 x,y;
   pOther->Location(&x,&y);

   if ( IsEqual(m_pPoint->X(),x) && IsEqual(m_pPoint->Y(),y) )
      return S_OK;
   else
      return S_FALSE;
}

STDMETHODIMP CPoint2d::Location(Float64* pX,Float64* pY)
{
   CHECK_RETVAL(pX);
   CHECK_RETVAL(pY);

   std::tie(*pX, *pY) = m_pPoint->GetLocation();
   return S_OK;
}

STDMETHODIMP CPoint2d::Clone(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   CComObject<CPoint2d>* pPoint;
   HRESULT hr = CComObject<CPoint2d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   pPoint->m_pPoint = std::make_shared<WBFL::Geometry::Point2d>(*m_pPoint);

   (*ppPoint) = pPoint;
   (*ppPoint)->AddRef();

   return S_OK;
}
