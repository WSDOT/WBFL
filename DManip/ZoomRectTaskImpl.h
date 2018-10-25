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

// RectSelectTaskImpl.h: interface for the CZoomRectTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZOOMRECTTASKIMPL_H__5D499BF8_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
#define AFX_ZOOMRECTTASKIMPL_H__5D499BF8_CF77_11D4_8B66_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "ZoomRectFSM.h"

class ATL_NO_VTABLE CZoomRectTaskImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CZoomRectTaskImpl, &CLSID_ZoomRectTask>,
   public CZoomRectFSM,
   public iTask
{
public:
	CZoomRectTaskImpl();
	virtual ~CZoomRectTaskImpl();

   void Init(CDisplayView* pView,HCURSOR hCursor,COLORREF color);


DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_ZOOMRECTTASK)

BEGIN_COM_MAP(CZoomRectTaskImpl)
   COM_INTERFACE_ENTRY(iTask)
	COM_INTERFACE_ENTRY(iZoomRectTask)
END_COM_MAP()

   // CZoomRectTask methods (from CZoomRectFSM)
	STDMETHOD_(void,FSMError)(LPCTSTR t,LPCTSTR s);
	STDMETHOD_(void,ZoomRect)();
	STDMETHOD_(void,RecordFirstPoint)();
   STDMETHOD_(void,ClearRect)();
	STDMETHOD_(void,TrackRect)();
	STDMETHOD_(void,InitTask)();
   STDMETHOD_(void,Cancel)();


   // CTask methods
   STDMETHOD_(void,Start)();

   STDMETHOD_(void,OnLButtonDown)(UINT nFlags, const CPoint& point);
	STDMETHOD_(void,OnLButtonUp)(UINT nFlags,const CPoint& point);
   STDMETHOD_(void,OnLButtonDblClk)(UINT nFlags,const CPoint& point);

   STDMETHOD_(void,OnRButtonDown)(UINT nFlags, const CPoint& point);
	STDMETHOD_(void,OnRButtonUp)(UINT nFlags,const CPoint& point);
   STDMETHOD_(void,OnRButtonDblClk)(UINT nFlags,const CPoint& point);

   STDMETHOD_(void,OnMouseMove)(UINT nFlags, const CPoint& point);
   STDMETHOD_(void,OnMouseWheel)(UINT nFlags, short zDelta, const CPoint& point);

   STDMETHOD_(void,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags);
   STDMETHOD_(void,OnContextMenu)(CWnd* pWnd,const CPoint& point);

   STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
   STDMETHOD_(void,OnDragLeave)();
   STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
   STDMETHOD_(DROPEFFECT,OnDragScroll)(DWORD dwKeyState,CPoint point);
   STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point);
   STDMETHOD_(DROPEFFECT,OnDropEx)(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point);

private:
   CDisplayView* m_pView;
   CPen* m_pTrackPen;
   CPoint m_FirstPoint;
   CPoint m_SecondPoint;
   CPoint m_TempPoint;
   HCURSOR m_Cursor;
   HCURSOR m_OldCursor;

   void DrawRect(CPoint& from,CPoint& to);
};

#endif // !defined(AFX_ZOOMRECTTASKIMPL_H__5D499BF8_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
