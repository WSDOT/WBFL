///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_RECTANGLEDRAWELINESTRATEGYIMPL_H_
#define INCLUDED_RECTANGLEDRAWELINESTRATEGYIMPL_H_
// RectangleDrawLineStrategyImpl.h: interface for the CRectangleDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CRectangleDrawLineStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRectangleDrawLineStrategyImpl, &CLSID_RectangleDrawLineStrategy>,
   public iRectangleDrawLineStrategy,
   public iGravityWellStrategy
{
public:
	CRectangleDrawLineStrategyImpl();
	virtual ~CRectangleDrawLineStrategyImpl();
   HRESULT FinalConstruct();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_RECTANGLEDRAWLINESTRATEGY)

BEGIN_COM_MAP(CRectangleDrawLineStrategyImpl)
   COM_INTERFACE_ENTRY(iDrawLineStrategy)
   COM_INTERFACE_ENTRY(iRectangleDrawLineStrategy)
   COM_INTERFACE_ENTRY(iGravityWellStrategy)
END_COM_MAP()

// iLineDrawStrategy
public:
   STDMETHOD_(void,Draw)(iLineDisplayObject* pDO,CDC* pDC);
   STDMETHOD_(void,DrawDragImage)(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,DrawHighlite)(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   STDMETHOD_(void,GetBoundingBox)(iLineDisplayObject* pDO,IRect2d** box);

// iRectangleLineDrawStrategy
public:
   STDMETHOD_(void,SetWidth)(Float64 width);
   STDMETHOD_(Float64,GetWidth)();
   STDMETHOD_(void,SetLineWidth)(UINT nPixels);
   STDMETHOD_(UINT,GetLineWidth)();
   STDMETHOD_(void,SetColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetColor)();
   STDMETHOD_(void,SetLineStyle)(LineStyleType style);
   STDMETHOD_(LineStyleType,GetLineStyle)();
   STDMETHOD_(void,PerimeterGravityWell)(BOOL bPerimeterGravityWell);
   STDMETHOD_(void,SetFillColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetFillColor)();
   STDMETHOD_(void,SetDoFill)(BOOL doFill);
   STDMETHOD_(BOOL,GetDoFill)();

// iGravityWellStrategy
public:
   STDMETHOD_(void,GetGravityWell)(iDisplayObject* pDO,CRgn* pRgn);

private:
   BOOL m_bPerimeterGravityWell;
   BOOL m_bDoFill;
   Float64 m_RectWidth;
   UINT m_nWidth;
   COLORREF m_crColor;
   COLORREF m_crFillColor;

   LineStyleType m_Style;

   void GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetPoints(iLineDisplayObject* pDO,IPoint2d** pntTopLeft,IPoint2d** pntBottomLeft,IPoint2d** pntBottomRight,IPoint2d** pntTopRight);
   void GetDrawRect(iLineDisplayObject* pDO,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4);
   void DrawPerimeter(CDC* pDC,COLORREF color, int penStyle, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4);
};

#endif // INCLUDED_RECTANGLEDRAWELINESTRATEGYIMPL_H_