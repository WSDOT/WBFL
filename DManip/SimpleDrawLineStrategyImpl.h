///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_SIMPLEDRAWELINESTRATEGYIMPL_H_
#define INCLUDED_SIMPLEDRAWELINESTRATEGYIMPL_H_
// SimpleDrawLineStrategyImpl.h: interface for the CSimpleDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CSimpleDrawLineStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleDrawLineStrategyImpl, &CLSID_SimpleDrawLineStrategy>,
   public iSimpleDrawLineStrategy
{
public:
	CSimpleDrawLineStrategyImpl();
	virtual ~CSimpleDrawLineStrategyImpl();
   HRESULT FinalConstruct();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLEDRAWLINESTRATEGY)

BEGIN_COM_MAP(CSimpleDrawLineStrategyImpl)
   COM_INTERFACE_ENTRY(iDrawLineStrategy)
   COM_INTERFACE_ENTRY(iSimpleDrawLineStrategy)
END_COM_MAP()

// iLineDrawStrategy
public:
   STDMETHOD_(void,Draw)(iLineDisplayObject* pDO,CDC* pDC);
   STDMETHOD_(void,DrawDragImage)(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,DrawHighlite)(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   STDMETHOD_(void,GetBoundingBox)(iLineDisplayObject* pDO,IRect2d** box);

// iSimpleLineDrawStrategy
public:
   STDMETHOD_(void,SetWidth)(UINT nPixels);
   STDMETHOD_(UINT,GetWidth)();
   STDMETHOD_(void,SetColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetColor)();
   STDMETHOD_(void,SetBeginType)(LineEndType type);
   STDMETHOD_(LineEndType,GetBeginType)();
   STDMETHOD_(int,GetBeginSize)();
   STDMETHOD_(void,SetBeginSize)(int size);
   STDMETHOD_(void,SetEndType)(LineEndType type);
   STDMETHOD_(LineEndType,GetEndType)();
   STDMETHOD_(int,GetEndSize)();
   STDMETHOD_(void,SetEndSize)(int size);
   STDMETHOD_(void,SetLineStyle)(LineStyleType style);
   STDMETHOD_(LineStyleType,GetLineStyle)();

private:
   UINT m_nWidth;
   COLORREF m_crColor;

   LineEndType m_BeginType;
   int m_BeginSize;
   LineEndType m_EndType;
   int m_EndSize;
   LineStyleType m_Style;

   void GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetPointsInWorldSpace(iLineDisplayObject* pDO,Float64* sx,Float64* sy,Float64* ex,Float64* ey);
};

#endif // INCLUDED_SIMPLEDRAWELINESTRATEGYIMPL_H_