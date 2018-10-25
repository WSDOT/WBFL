///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2018  Washington State Department of Transportation
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
		&IID_IPoint2d,
      &IID_IStructuredStorage2
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
   m_X = 0.0;
   m_Y = 0.0;
}

STDMETHODIMP CPoint2d::get_X(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_X;

	return S_OK;
}

STDMETHODIMP CPoint2d::put_X(Float64 newVal)
{
   m_X = newVal;
   Fire_OnPointChanged(this);
	return S_OK;
}

STDMETHODIMP CPoint2d::get_Y(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Y;

	return S_OK;
}

STDMETHODIMP CPoint2d::put_Y(Float64 newVal)
{
   m_Y = newVal;
   Fire_OnPointChanged(this);
	return S_OK;
}

STDMETHODIMP CPoint2d::Move(Float64 x, Float64 y)
{
   m_X = x;
   m_Y = y;

   Fire_OnPointChanged(this);
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
   m_X += dx;
   m_Y += dy;

   Fire_OnPointChanged(this);
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
   Float64 x,y;
   x = (m_X - cx)*cos(angle) - (m_Y - cy)*sin(angle) + cx;
   y = (m_Y - cy)*cos(angle) + (m_X - cx)*sin(angle) + cy;

   m_X = x;
   m_Y = y;

   Fire_OnPointChanged(this);
	return S_OK;
}

STDMETHODIMP CPoint2d::RotateEx(IPoint2d *pCenter, Float64 angle)
{
   CHECK_IN(pCenter);

   Float64 cx,cy;
   pCenter->Location(&cx,&cy);

   return Rotate(cx,cy,angle);
}

STDMETHODIMP CPoint2d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CPoint2d::Distance(Float64 x,Float64 y,Float64* pDistance)
{
   CHECK_RETVAL(pDistance);
   *pDistance = sqrt( (m_X-x)*(m_X-x) + (m_Y-y)*(m_Y-y) );
   return S_OK;
}

STDMETHODIMP CPoint2d::DistanceEx(IPoint2d* pOther,Float64* pDistance)
{
   CHECK_IN(pOther);
   Float64 x,y;
   pOther->Location(&x,&y);
   return Distance(x,y,pDistance);
}

STDMETHODIMP CPoint2d::SameLocation(IPoint2d* pOther)
{
   CHECK_IN(pOther);

   Float64 x,y;
   pOther->Location(&x,&y);

   if ( IsEqual(m_X,x) && IsEqual(m_Y,y) )
      return S_OK;
   else
      return S_FALSE;
}

STDMETHODIMP CPoint2d::Location(Float64* pX,Float64* pY)
{
   CHECK_RETVAL(pX);
   CHECK_RETVAL(pY);

   *pX = m_X;
   *pY = m_Y;
   return S_OK;
}

STDMETHODIMP CPoint2d::Clone(IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   CComObject<CPoint2d>* pPoint;
   HRESULT hr = CComObject<CPoint2d>::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   (*ppPoint) = pPoint;
   (*ppPoint)->AddRef();

   (*ppPoint)->Move(m_X,m_Y);

   return S_OK;
}

// IPersist
STDMETHODIMP CPoint2d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CPoint2d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Point2d"),1.0);
   pSave->put_Property(CComBSTR("X"),CComVariant(m_X));
   pSave->put_Property(CComBSTR("Y"),CComVariant(m_Y));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPoint2d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Point2d"));
   
   pLoad->get_Property(CComBSTR("X"),&var);
   m_X = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Y"),&var);
   m_Y = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
