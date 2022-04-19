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
   CComObject<CPoint3d>* pStart;
   CComObject<CPoint3d>::CreateInstance(&pStart);
   pStart->SetPoint(m_LineSegment.GetStartPoint());
   pStart->QueryInterface(&m_Start);

   CComObject<CPoint3d>* pEnd;
   CComObject<CPoint3d>::CreateInstance(&pEnd);
   pEnd->SetPoint(m_LineSegment.GetEndPoint());
   pEnd->QueryInterface(&m_End);

   return S_OK;
}

void CLineSegment3d::FinalRelease()
{
}

void CLineSegment3d::SetLineSegment(WBFL::Geometry::LineSegment3d& ls)
{
   m_LineSegment = ls;
   dynamic_cast<CPoint3d*>(m_Start.p)->SetPoint(m_LineSegment.GetStartPoint());
   dynamic_cast<CPoint3d*>(m_End.p)->SetPoint(m_LineSegment.GetEndPoint());
}

STDMETHODIMP CLineSegment3d::get_StartPoint(IPoint3d **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_Start.QueryInterface(pVal);
}

STDMETHODIMP CLineSegment3d::putref_StartPoint(IPoint3d *newVal)
{
   CHECK_IN(newVal);
   m_Start = newVal;
   m_LineSegment.SetStartPoint(GetInnerPoint(m_Start));
   return S_OK;
}

STDMETHODIMP CLineSegment3d::get_EndPoint(IPoint3d **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_End.QueryInterface(pVal);
}  

STDMETHODIMP CLineSegment3d::putref_EndPoint(IPoint3d *newVal)
{
   CHECK_IN(newVal);
   m_End = newVal;
   m_LineSegment.SetEndPoint(GetInnerPoint(m_End));
   return S_OK;
}

STDMETHODIMP CLineSegment3d::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_LineSegment.GetLength();
   return S_OK;
}

//STDMETHODIMP CLineSegment3d::Rotate(Float64 cx, Float64 cy, Float64 angle)
//{
//   EventsOff();
//   m_pStart->Rotate( cx, cy, angle );
//   m_pEnd->Rotate( cx, cy, angle );
//   EventsOn();
//
//   return S_OK;
//}
//
//STDMETHODIMP CLineSegment3d::RotateEx(IPoint2d *pCenter, Float64 angle)
//{
//   CHECK_IN(pCenter);
//
//   Float64 x,y;
//   pCenter->get_X(&x);
//   pCenter->get_Y(&y);
//
//   return Rotate(x,y,angle);
//}

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

   m_Start = p1;
   m_End = p2;
   m_LineSegment.ThroughPoints(GetInnerPoint(m_Start),GetInnerPoint(m_End));
   return S_OK;
}

STDMETHODIMP CLineSegment3d::Clone(ILineSegment3d** ppClone)
{
   CHECK_RETOBJ(ppClone);
   CComObject<CLineSegment3d>* pClone;
   CComObject<CLineSegment3d>::CreateInstance(&pClone);

   pClone->m_Start.Release();
   m_Start->Clone(&pClone->m_Start);
   pClone->m_End.Release();
   m_End->Clone(&pClone->m_End);
   pClone->m_LineSegment.ThroughPoints(GetInnerPoint(m_Start), GetInnerPoint(m_End));

   (*ppClone) = pClone;
   (*ppClone)->AddRef();

   return S_OK;
}
