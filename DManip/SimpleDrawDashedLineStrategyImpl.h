///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// SimpleDrawDashedLineStrategyImpl.h: interface for the CSimpleDrawDashedLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "resource.h"

class ATL_NO_VTABLE CSimpleDrawDashedLineStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleDrawDashedLineStrategyImpl, &CLSID_SimpleDrawDashedLineStrategy>,
   public iSimpleDrawDashedLineStrategy
{
public:
	CSimpleDrawDashedLineStrategyImpl();
	virtual ~CSimpleDrawDashedLineStrategyImpl();
   HRESULT FinalConstruct();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLEDRAWDASHEDLINESTRATEGY)

BEGIN_COM_MAP(CSimpleDrawDashedLineStrategyImpl)
   COM_INTERFACE_ENTRY(iDrawLineStrategy)
   COM_INTERFACE_ENTRY(iSimpleDrawDashedLineStrategy)
END_COM_MAP()

// iLineDrawStrategy
public:
   STDMETHOD_(void,Draw)(iLineDisplayObject* pDO,CDC* pDC);
   STDMETHOD_(void,DrawDragImage)(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,DrawHighlite)(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   STDMETHOD_(void,GetBoundingBox)(iLineDisplayObject* pDO,IRect2d** box);

// iSimpleLineDashedDrawStrategy
public:
   STDMETHOD_(void,SetWidth)(UINT nPixels);
   STDMETHOD_(UINT,GetWidth)();
   STDMETHOD_(void,SetColor1)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetColor1)();
   STDMETHOD_(void,SetColor2)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetColor2)();
   STDMETHOD_(void,SetDashLength)(DWORD dwDash);
   STDMETHOD_(DWORD,GetDashLength)();

private:
   UINT m_nWidth;
   COLORREF m_crColor1;
   COLORREF m_crColor2;
   DWORD m_dwDash;

   void GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetPointsInWorldSpace(iLineDisplayObject* pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey);
};
