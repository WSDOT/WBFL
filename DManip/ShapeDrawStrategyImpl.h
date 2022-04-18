///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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

// ShapeDrawStrategyImpl.h: interface for the CShapeDrawStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPEDRAWSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
#define AFX_SHAPEDRAWSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CShapeDrawStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShapeDrawStrategyImpl, &CLSID_ShapeDrawStrategy>,
   public iShapeDrawStrategy,
   public iGravityWellStrategy
{
public:
	CShapeDrawStrategyImpl();
	virtual ~CShapeDrawStrategyImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_SHAPEDRAWSTRATEGY)

BEGIN_COM_MAP(CShapeDrawStrategyImpl)
   COM_INTERFACE_ENTRY(iShapeDrawStrategy)
	COM_INTERFACE_ENTRY(iDrawPointStrategy)
   COM_INTERFACE_ENTRY(iGravityWellStrategy)
END_COM_MAP()

   // iShapeDrawStrategy Implementation
   STDMETHOD_(void,SetShape)(IShape* pShape);
   STDMETHOD_(void,GetShape)(IShape** ppShape);

   STDMETHOD_(void,SetSolidLineStyle)(LineStyleType lineStyle);
   STDMETHOD_(LineStyleType,GetSolidLineStyle)();
   STDMETHOD_(void,SetSolidLineColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetSolidLineColor)();
   STDMETHOD_(void,SetSolidFillColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetSolidFillColor)();
   STDMETHOD_(void,SetSolidLineWidth)(UINT nPixels);
   STDMETHOD_(UINT,GetSolidLineWidth)();

   STDMETHOD_(void,SetVoidLineStyle)(LineStyleType lineStyle);
   STDMETHOD_(LineStyleType,GetVoidLineStyle)();
   STDMETHOD_(void,SetVoidLineColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetVoidLineColor)();
   STDMETHOD_(void,SetVoidFillColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetVoidFillColor)();
   STDMETHOD_(void,SetVoidLineWidth)(UINT nPixels);
   STDMETHOD_(UINT,GetVoidLineWidth)();

   STDMETHOD_(void,DoFill)(bool doFill);
   STDMETHOD_(bool,DoFill)();

   STDMETHOD_(void,HasBoundingShape)(bool bHasBoundingShape);
   STDMETHOD_(bool,HasBoundingShape)();

   // iDrawPointStrategy Implementation
   STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
   STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO, IRect2d** box);

   // iGravityWellStrategy
   STDMETHOD_(void, GetGravityWell)(iDisplayObject* pDO, CRgn* pRgn) override;

private:
   LineStyleType m_SolidLineStyle;
   LineStyleType m_VoidLineStyle;
   COLORREF m_SolidLineColor;
   COLORREF m_SolidFillColor;
   COLORREF m_VoidLineColor;
   COLORREF m_VoidFillColor;
   UINT m_SolidLineWidth;
   UINT m_VoidLineWidth;
   bool m_bFill;
   bool m_bHasBoundingShape;

   CComPtr<IShape> m_Shape;
   CComPtr<ICompositeShape> m_CompositeShape;

   CComPtr<IRect2d> m_BoundingBox;

   void DrawMe(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   void DrawShape(iDisplayObject* pDO,CDC* pDC,ICompositeShape* pCompositeShape,CPen& solidPen,CBrush& solidBrush,CPen& voidPen,CBrush& voidBrush);
   void DrawShape(iDisplayObject* pDO,CDC* pDC,IShape* pShape);
   void GetPointsInWorldSpace(iDisplayObject* pDO,IShape* pShape,IPoint2dCollection** pPoints);
   void CreatePen(LineStyleType lineStyle,UINT width,COLORREF color,CPen& pen);
};

#endif // !defined(AFX_SHAPEDRAWSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
