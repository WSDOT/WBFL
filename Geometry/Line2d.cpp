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

// Line2d.cpp : Implementation of CLine2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Line2d.h"
#include "Helper.h"
#include <GeomModel/Primitives.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLine2d

HRESULT CLine2d::FinalConstruct()
{
   return S_OK;
}

STDMETHODIMP CLine2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILine2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLine2d::GetExplicit(IPoint2d** p,IVector2d** d)
{
   CHECK_RETOBJ(p);
   CHECK_RETOBJ(d);

   auto [pu,pv] = m_Line.GetExplicit();

   CreatePoint(pu, p);
   CreateVector(pv, d);

   return S_OK;
}

STDMETHODIMP CLine2d::SetExplicit(IPoint2d *p,IVector2d* d)
{
   CHECK_IN(p);
   CHECK_IN(d);

   try
   {
      m_Line.SetExplicit(GetPoint(p), GetVector(d));
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_ILine2d, GEOMETRY_E_ZEROMAGNITUDE);
   }

   return S_OK;
}

STDMETHODIMP CLine2d::SetImplicit(Float64 c, IVector2d *pN)
{
   CHECK_IN(pN);
   
   try
   {
      m_Line.SetImplicit(c, GetVector(pN));
   }
   catch (...)
   {
      return Error(IDS_E_ZEROMAGNITUDE, IID_ILine2d, GEOMETRY_E_ZEROMAGNITUDE);
   }

   return S_OK;
}

STDMETHODIMP CLine2d::GetImplicit(Float64 *pC, IVector2d** pN)
{
   CHECK_RETVAL(pC);
   CHECK_RETOBJ(pN);

   WBFL::Geometry::Vector2d n;
   std::tie(*pC,n) = m_Line.GetImplicit();
   return CreateVector(n, pN);
}

STDMETHODIMP CLine2d::ThroughPoints(IPoint2d* p1, IPoint2d* p2)
{
   CHECK_IN(p1);
   CHECK_IN(p2);

   try
   {
      m_Line.ThroughPoints(GetPoint(p1), GetPoint(p2));
   }
   catch (...)
   {
      return Error(IDS_E_SAMEPOINTS, IID_ILine2d, GEOMETRY_E_SAMEPOINTS);
   }
   return S_OK;
}

STDMETHODIMP CLine2d::Offset(Float64 offset)
{
   m_Line.Offset(offset);
   return S_OK;
}

STDMETHODIMP CLine2d::Rotate(Float64 cx,Float64 cy, Float64 angle)
{
   m_Line.Rotate(WBFL::Geometry::Point2d(cx, cy), angle);
   return S_OK;
}

STDMETHODIMP CLine2d::RotateEx(IPoint2d *pCenter, Float64 angle)
{
   CHECK_IN(pCenter);
   Float64 x, y; pCenter->Location(&x, &y);
   return Rotate(x,y,angle);
}

STDMETHODIMP CLine2d::Reverse()
{
   m_Line.Reverse();
   return S_OK;
}

STDMETHODIMP CLine2d::ContainsPoint(IPoint2d* pPoint, VARIANT_BOOL* pbResult)
{
   CHECK_RETVAL(pbResult);
   *pbResult = MakeBool(m_Line.ContainsPoint(GetPoint(pPoint)));
   return S_OK;
}

STDMETHODIMP CLine2d::IsColinear(ILine2d* pLine, VARIANT_BOOL* pbResult)
{
   CHECK_RETVAL(pbResult);
   *pbResult = MakeBool(m_Line.IsColinear(GetLine(pLine)));
   return S_OK;
}

STDMETHODIMP CLine2d::Clone(ILine2d** ppLine)
{
   CHECK_RETVAL(ppLine);
   CComObject<CLine2d>* pLine;
   CComObject<CLine2d>::CreateInstance(&pLine);

   pLine->m_Line = m_Line;

   (*ppLine) = pLine;
   (*ppLine)->AddRef();

   return S_OK;
}
