///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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

// ViewTitleImpl.h: interface for the CViewTitleImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWTITLEIMPL_H__BCB8A108_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_VIEWTITLEIMPL_H__BCB8A108_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#include <DManip\DisplayObjectDefaultImpl.h>

class ATL_NO_VTABLE CViewTitleImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CViewTitleImpl, &CLSID_ViewTitle>,
   public CDisplayObjectDefaultImpl,
   public iViewTitle
{
public:
	CViewTitleImpl();
	virtual ~CViewTitleImpl();
   HRESULT FinalConstruct();
   void FinalRelease();

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

DECLARE_REGISTRY_RESOURCEID(IDR_VIEWTITLE)

BEGIN_COM_MAP(CViewTitleImpl)
	COM_INTERFACE_ENTRY(iViewTitle)
END_COM_MAP()

   // iDisplayObject Implementation
   STDMETHOD_(void,SetID)(IDType id) { Do_SetID(id); }
   STDMETHOD_(IDType,GetID)() { return Do_GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) { Do_SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) { Do_GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pList) { Do_SetDisplayList(pList); }
   STDMETHOD_(void,GetDisplayList)(iDisplayList** list) { Do_GetDisplayList(list); }

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
   STDMETHOD_(CRect,GetBoundingBox)();
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect); 
   STDMETHOD_(BOOL,TouchesRect)(CRect r) {return Do_TouchesRect(r); }

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) {Do_Select(bSelect);}
   STDMETHOD_(BOOL,IsSelected)() {return Do_IsSelected();}
   STDMETHOD_(void,SetSelectionType)(SelectionType st) { Do_SetSelectionType(st); }
   STDMETHOD_(SelectionType,GetSelectionType)() { return Do_GetSelectionType(); }
   STDMETHOD_(void, RetainSelection)(BOOL bRetain) { Do_RetainSelection(bRetain); }
   STDMETHOD_(BOOL, RetainSelection)() { return Do_RetainSelection(); }

   // Tool Tips
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText) {Do_SetToolTipText(lpszToolTipText);}
   STDMETHOD_(CString,GetToolTipText)() {return Do_GetToolTipText();}
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
   STDMETHOD_(void,RegisterDropSite)(iDropSite* pDropSite) { Do_RegisterDropSite(pDropSite); }
   STDMETHOD_(void,UnregisterDropSite)() { Do_UnregisterDropSite(); }
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) { Do_GetDropSite(dropSite); }

   // Composite
   STDMETHOD_(void, SetParent)(iDisplayObject* pParent) override { Do_SetParent(pParent); }
   STDMETHOD_(void, GetParent)(iDisplayObject** ppParent) override { Do_GetParent(ppParent); }

   // iViewTitle Implemention
   STDMETHOD_(void,SetText)(LPCTSTR lpszText);
   STDMETHOD_(CString,GetText)();

   STDMETHOD_(void,SetFont)(const LOGFONT& Font);
   STDMETHOD_(void,GetFont)(LOGFONT* pFont);

private:
   CString m_strText;
   LOGFONT m_Font;

   void GetTextLines(CStringArray& strings);
};

#endif // !defined(AFX_VIEWTITLEIMPL_H__BCB8A108_E659_11D4_8B81_006097C68A9C__INCLUDED_)
