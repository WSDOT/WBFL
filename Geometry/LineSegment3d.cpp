///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 2999-2022  Washington State Department of Transportation
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

// LineSegment3d.cpp : Implementation of CLineSegment3d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "LineSegment3d.h"
#include "Point3d.h"
#include "Helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineSegment3d

STDMETHODIMP CLineSegment3d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILineSegment3d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLineSegment3d::FinalConstruct()
{
   return S_OK;
}

void CLineSegment3d::FinalRelease()
{
}

void CLineSegment3d::SetLineSegment(WBFL::Geometry::LineSegment3d& ls)
{
   m_LineSegment = ls;
}

STDMETHODIMP CLineSegment3d::get_StartPoint(IPoint3d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_LineSegment.GetStartPoint(), pVal);
}

STDMETHODIMP CLineSegment3d::put_StartPoint(IPoint3d *newVal)
{
   CHECK_IN(newVal);
   m_LineSegment.SetStartPoint(*GetInnerPoint(newVal));
   return S_OK;
}

STDMETHODIMP CLineSegment3d::get_EndPoint(IPoint3d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_LineSegment.GetEndPoint(), pVal);
}

STDMETHODIMP CLineSegment3d::put_EndPoint(IPoint3d *newVal)
{
   CHECK_IN(newVal);
   m_LineSegment.SetEndPoint(*GetInnerPoint(newVal));
   return S_OK;
}

STDMETHODIMP CLineSegment3d::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LineSegment.GetLength();
   return S_OK;
}

STDMETHODIMP CLineSegment3d::Offset(Float64 dx, Float64 dy,Float64 dz)
{
   m_LineSegment.Offset(dx, dy, dz);
	return S_OK;
}

STDMETHODIMP CLineSegment3d::OffsetEx(ISize3d *pSize)
{
   CHECK_IN(pSize);
   Float64 dx, dy, dz;
   pSize->Dimensions(&dx, &dy, &dz);
   return Offset(dx, dy, dz);
   return S_OK;
}

STDMETHODIMP CLineSegment3d::ThroughPoints(IPoint3d* p1, IPoint3d* p2)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   m_LineSegment.ThroughPoints(*GetInnerPoint(p1),*GetInnerPoint(p2));
   return S_OK;
}

STDMETHODIMP CLineSegment3d::Clone(ILineSegment3d** ppClone)
{
   CHECK_RETOBJ(ppClone);
   CComObject<CLineSegment3d>* pClone;
   CComObject<CLineSegment3d>::CreateInstance(&pClone);
   pClone->m_LineSegment = m_LineSegment;

   (*ppClone) = pClone;
   (*ppClone)->AddRef();

   return S_OK;
}
