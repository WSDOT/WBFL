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

// LineSegment2d.cpp : Implementation of CLineSegment2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "LineSegment2d.h"
#include "Point2d.h"
#include "Helper.h"

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
		&IID_ILineSegment2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CLineSegment2d::FinalConstruct()
{
   return S_OK;
}

void CLineSegment2d::FinalRelease()
{
}

void CLineSegment2d::SetLineSegment(const WBFL::Geometry::LineSegment2d& ls)
{
   m_LineSegment = ls;
}

STDMETHODIMP CLineSegment2d::get_StartPoint(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_LineSegment.GetStartPoint(), pVal);
}

STDMETHODIMP CLineSegment2d::put_StartPoint(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_LineSegment.SetStartPoint(*GetInnerPoint(newVal));
   return S_OK;
}

STDMETHODIMP CLineSegment2d::get_EndPoint(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_LineSegment.GetEndPoint(), pVal);
}

STDMETHODIMP CLineSegment2d::put_EndPoint(IPoint2d *newVal)
{
   CHECK_IN(newVal);
   m_LineSegment.SetEndPoint(*GetInnerPoint(newVal));
   return S_OK;
}

STDMETHODIMP CLineSegment2d::get_Length(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_LineSegment.Length();
   return S_OK;
}

STDMETHODIMP CLineSegment2d::Rotate(Float64 cx, Float64 cy, Float64 angle)
{
   m_LineSegment.Rotate(WBFL::Geometry::Point2d(cx, cy), angle);
   return S_OK;
}

STDMETHODIMP CLineSegment2d::RotateEx(IPoint2d *pCenter, Float64 angle)
{
   CHECK_IN(pCenter);

   Float64 x,y;
   pCenter->Location(&x,&y);

   return Rotate(x,y,angle);
}

STDMETHODIMP CLineSegment2d::Offset2(Float64 distance)
{
   m_LineSegment.Offset(distance);
   return S_OK;
}

STDMETHODIMP CLineSegment2d::Offset(Float64 dx, Float64 dy)
{
   m_LineSegment.Offset(dx, dy);
	return S_OK;
}

STDMETHODIMP CLineSegment2d::OffsetEx(ISize2d *pSize)
{
   CHECK_IN(pSize);

   Float64 dx, dy;
   pSize->Dimensions(&dx, &dy);
   return Offset(dx, dy);

   return S_OK;
}

STDMETHODIMP CLineSegment2d::ThroughPoints(IPoint2d* p1, IPoint2d* p2)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   m_LineSegment.ThroughPoints(*GetInnerPoint(p1), *GetInnerPoint(p2));
   return S_OK;
}

STDMETHODIMP CLineSegment2d::ContainsPoint(IPoint2d* pPoint, Float64 tolerance, VARIANT_BOOL* pbResult)
{
   CHECK_RETVAL(pbResult);
   *pbResult = MakeBool(m_LineSegment.ContainsPoint(GetPoint(pPoint), tolerance));
   return S_OK;
}

STDMETHODIMP CLineSegment2d::Divide(IndexType nSpaces, IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   std::vector<WBFL::Geometry::Point2d> points;
   try
   {
      points = m_LineSegment.Divide(nSpaces);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }

   return CreatePointCollection(points, ppPoints);
}

STDMETHODIMP CLineSegment2d::Clone(ILineSegment2d** ppClone)
{
   CHECK_RETOBJ(ppClone);
   CComObject<CLineSegment2d>* pClone;
   CComObject<CLineSegment2d>::CreateInstance(&pClone);
   pClone->m_LineSegment = m_LineSegment;

   (*ppClone) = pClone;
   (*ppClone)->AddRef();

   return S_OK;
}
