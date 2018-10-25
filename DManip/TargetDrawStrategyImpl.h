///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

//TargetDrawStrategyImpl.h: interface for the CTargetDrawStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARGETDRAWSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
#define AFX_TARGETDRAWSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CTargetDrawStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTargetDrawStrategyImpl, &CLSID_TargetDrawStrategy>,
   public iTargetDrawStrategy
{
public:
	CTargetDrawStrategyImpl();
	virtual ~CTargetDrawStrategyImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_TARGETDRAWSTRATEGY)

BEGIN_COM_MAP(CTargetDrawStrategyImpl)
   COM_INTERFACE_ENTRY(iTargetDrawStrategy)
	COM_INTERFACE_ENTRY(iDrawPointStrategy)
END_COM_MAP()

   // iTargetDrawStrategy Implementation
   STDMETHOD_(void,SetRadius)(LONG radius);
   STDMETHOD_(LONG,GetRadius)();
   STDMETHOD_(void,SetFgColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetFgColor)();
   STDMETHOD_(void,SetBgColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetBgColor)();

   // iDrawPointStrategy Implementation
   STDMETHOD_(void,Draw)(iPointDisplayObject* pDO,CDC* pDC);
   STDMETHOD_(void,DrawHighlite)(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   STDMETHOD_(void,DrawDragImage)(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,GetBoundingBox)(iPointDisplayObject* pDO, IRect2d** box);

private:
   void DrawMe(iPointDisplayObject* pDO,CDC* pDC);

   COLORREF m_FgColor;
   COLORREF m_BgColor;
   COLORREF m_Color; // color used for drawing foreground (changes based on object's state)
   LONG m_Radius;

   CComPtr<IPoint2d> m_CachePoint;
};

#endif // !defined(AFX_TARGETDRAWSTRATEGYIMPL_H__9E3A6AF6_E734_11D4_8B83_006097C68A9C__INCLUDED_)
