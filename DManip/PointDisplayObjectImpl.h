///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// PointDisplayObject.h: interface for the CPointDisplayObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTDISPLAYOBJECT_H__9E3A6AF5_E734_11D4_8B83_006097C68A9C__INCLUDED_)
#define AFX_POINTDISPLAYOBJECT_H__9E3A6AF5_E734_11D4_8B83_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#include <DManip\DisplayObjectDefaultImpl.h>
#include "ConnectableImpl.h"

class CPointDisplayObjectImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPointDisplayObjectImpl, &CLSID_PointDisplayObject>,
   public CDisplayObjectDefaultImpl,
   public CConnectableImpl<CPointDisplayObjectImpl>,
   public iPointDisplayObject,
   public iDraggable
{
public:
	CPointDisplayObjectImpl();
	virtual ~CPointDisplayObjectImpl();
   HRESULT FinalConstruct();

   ULONG OuterAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterAddRef();
      return ulReturn;
   }

   ULONG OuterRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::OuterRelease();
      return ulReturn;
   }

   ULONG InternalAddRef()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalAddRef();
      return ulReturn;
   }

   ULONG InternalRelease()
   {
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalRelease();
      return ulReturn;
   }

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_POINTDISPLAYOBJECT)

BEGIN_COM_MAP(CPointDisplayObjectImpl)
   COM_INTERFACE_ENTRY(iDisplayObject)
	COM_INTERFACE_ENTRY(iPointDisplayObject)
   COM_INTERFACE_ENTRY(iDraggable)
	COM_INTERFACE_ENTRY(iConnectable)
END_COM_MAP()

   // iPointDisplayObject
   STDMETHOD_(void,SetPosition)(IPoint2d* pos,BOOL bRedraw,BOOL bFireEvent);
   STDMETHOD_(void,GetPosition)(IPoint2d* *pos);
   STDMETHOD_(CPoint,GetPosition)();
   STDMETHOD_(void,Offset)(ISize2d* offset,BOOL bRedraw,BOOL bFireEvent);
   STDMETHOD_(void,SetDrawingStrategy)(iDrawPointStrategy* pStrategy);
   STDMETHOD_(void,GetDrawingStrategy)(iDrawPointStrategy** pStrategy);
   STDMETHOD_(void,EnableAutoUpdate)(BOOL bEnable);
   STDMETHOD_(BOOL,IsAutoUpdateEnabled)();

   // iDisplayObject Implementation
   STDMETHOD_(void,SetID)(IDType id) { Do_SetID(id); }
   STDMETHOD_(IDType,GetID)() { return Do_GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) { Do_SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) { Do_GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL){ Do_SetDisplayList(pDL); }

   STDMETHOD_(void,GetDisplayList)(iDisplayList** dispList) { Do_GetDisplayList(dispList); }

   STDMETHOD_(void,Visible)(BOOL bVisible) { Do_Visible(bVisible); }
   STDMETHOD_(BOOL,IsVisible)() { return Do_IsVisible(); }

   // Drawing
   STDMETHOD_(void,Draw)(CDC* pDC);
   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite);
#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWell)(CDC* pDC) { Do_DrawGravityWell(pDC); }
#endif

   // Size and Hit Testing
   STDMETHOD_(void,SetGravityWellStrategy)(iGravityWellStrategy* pStrategy) { Do_SetGravityWellStrategy(pStrategy); }
   STDMETHOD_(void,GetGravityWellStrategy)(iGravityWellStrategy** pStrategy){ Do_GetGravityWellStrategy(pStrategy); }
   STDMETHOD_(BOOL,HitTest)(CPoint point) { return Do_HitTest(point); }
   STDMETHOD_(CRect,GetBoundingBox)(){ return Do_GetBoundingBox(); }
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect);
   STDMETHOD_(BOOL,TouchesRect)(CRect r) { return Do_TouchesRect(r); }

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) { Do_Select(bSelect); }
   STDMETHOD_(BOOL,IsSelected)() {return Do_IsSelected(); }
   STDMETHOD_(void,SetSelectionType)(SelectionType st) { Do_SetSelectionType(st); }
   STDMETHOD_(SelectionType,GetSelectionType)() { return Do_GetSelectionType(); }

   // Tool Tips
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText) {Do_SetToolTipText(lpszToolTipText); }
   STDMETHOD_(CString,GetToolTipText)() {return Do_GetToolTipText(); }
   STDMETHOD_(void,SetMaxTipWidth)(INT maxWidth) { Do_SetMaxTipWidth(maxWidth); }
   STDMETHOD_(INT,GetMaxTipWidth)() { return Do_GetMaxTipWidth(); }
   STDMETHOD_(void,SetTipDisplayTime)(INT iTime) { Do_SetTipDisplayTime(iTime); }
   STDMETHOD_(INT,GetTipDisplayTime)() { return Do_GetTipDisplayTime(); }

   // Interface Events
   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point)
   { return Do_OnLButtonDown(nFlags,point); }
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point)
   { return Do_OnLButtonUp(nFlags,point); }
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point)
   { return Do_OnLButtonDblClk(nFlags,point); }
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point)
   { return Do_OnRButtonDown(nFlags,point); }
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point)
   { return Do_OnRButtonUp(nFlags,point); }
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point)
   { return Do_OnRButtonDblClk(nFlags,point); }
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags,CPoint point)
   { return Do_OnMouseMove(nFlags,point); }
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags,short zDelta,CPoint point)
   { return Do_OnMouseWheel(nFlags,zDelta,point); }
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags)
   { return Do_OnKeyDown(nChar,nRepCnt,nFlags); }
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point)
   { return Do_OnContextMenu(pWnd,point); }

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink)
   { Do_RegisterEventSink(pEventSink); }
   STDMETHOD_(void,UnregisterEventSink)()
   { Do_UnregisterEventSink(); }
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink)
   { Do_GetEventSink(pEventSink); }

   // Drag Drop
   STDMETHOD_(void,SetDropSite)(iDropSite* pDropSite)
   { Do_SetDropSite(pDropSite); }
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite)
   { Do_GetDropSite(dropSite); }

   // iDraggable Implementation
   STDMETHOD_(void,SetDragData)(iDragData* dd);
   STDMETHOD_(void,GetDragData)(iDragData** dd);
   STDMETHOD_(UINT,Format)();
   STDMETHOD_(void,PrepareDrag)(iDragDataSink* pSink);
   STDMETHOD_(void,OnDrop)(iDragDataSource* pSource);
   STDMETHOD_(void,DrawDragImage)(CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,OnDragMoved)(ISize2d* offset);
   STDMETHOD_(void,OnMoved)();
   STDMETHOD_(void,OnCopied)();


private:
   BOOL m_bAutoUpdate;
   CComPtr<iDrawPointStrategy> m_pDrawStrategy;
   CComPtr<IPoint2d> m_Position;
   CComPtr<iDragData> m_pDragData;

   static UINT ms_cfFormat;
};

#endif // !defined(AFX_POINTDISPLAYOBJECT_H__9E3A6AF5_E734_11D4_8B83_006097C68A9C__INCLUDED_)
