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

// DrawPointStrategyImpl.h: interface for the CDrawPointStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEDRAWPOINTSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
#define AFX_SIMPLEDRAWPOINTSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CSimpleDrawPointStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleDrawPointStrategyImpl, &CLSID_SimpleDrawPointStrategy>,
   public iSimpleDrawPointStrategy
{
public:
	CSimpleDrawPointStrategyImpl();
	virtual ~CSimpleDrawPointStrategyImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLEDRAWPOINTSTRATEGY)

BEGIN_COM_MAP(CSimpleDrawPointStrategyImpl)
   COM_INTERFACE_ENTRY(iSimpleDrawPointStrategy)
	COM_INTERFACE_ENTRY(iDrawPointStrategy)
END_COM_MAP()

   // iSimpleDrawPointStrategy Implementation
   STDMETHOD_(void,SetColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetColor)();
   STDMETHOD_(void,SetPointType)(PointType type);
   STDMETHOD_(PointType,GetPointType)();
   STDMETHOD_(void,SetPointSize)(Float64 size);
   STDMETHOD_(Float64,GetPointSize)();
   STDMETHOD_(void, SetLogicalPointSize)(int size);
   STDMETHOD_(int, GetLogicalPointSize)();

   // iDrawPointStrategy Implementation
   STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
   STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO, IRect2d** box);

private:
   void DrawMe(const CRect& rect,CDC* pDC);
   void GetPointInWorldSpace(iPointDisplayObject* pDO,Float64* wx,Float64* wy);
   CRect GetPointBox(iPointDisplayObject* pDO);

   bool m_bIsLogicalPoint; // if true, SetLogicalPointSize was called so use m_LogicalSize for the point size
   COLORREF m_Color;
   PointType m_Type;
   Float64 m_Size;
   int m_LogicalSize;

   CComPtr<IPoint2d> m_CachePoint;
};

#endif // !defined(AFX_SIMPLEDRAWPOINTSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
