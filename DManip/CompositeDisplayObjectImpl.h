///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#if !defined(AFX_COMPOSITEDISPLAYOBJECT_H__9E3A6AF5_E734_11D4_8B83_006097C68A9C__INCLUDED_)
#define AFX_COMPOSITEDISPLAYOBJECT_H__9E3A6AF5_E734_11D4_8B83_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#include <DManip\CompositeDisplayObject.h>
#include <DManip\DisplayObjectDefaultImpl.h>

class CCompositeDisplayObjectImpl :
   public CComObjectRootEx<CComSingleThreadModel>,
   public CComCoClass<CCompositeDisplayObjectImpl, &CLSID_CompositeDisplayObject>,
   public CDisplayObjectDefaultImpl,
   public iCompositeDisplayObject
{
public:
   CCompositeDisplayObjectImpl();
   virtual ~CCompositeDisplayObjectImpl();
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

   DECLARE_REGISTRY_RESOURCEID(IDR_COMPOSITEDISPLAYOBJECT)

   BEGIN_COM_MAP(CCompositeDisplayObjectImpl)
      COM_INTERFACE_ENTRY(iDisplayObject)
      COM_INTERFACE_ENTRY(iCompositeDisplayObject)
   END_COM_MAP()

private:
   CComPtr<iDisplayList> m_CompositeItems;
   CComPtr<IRect2d> m_BoundingBox;

   // iCompositeDisplayObject
public:
   STDMETHOD_(void, AddDisplayObject)(iDisplayObject* pDO) override;
   STDMETHOD_(void, RemoveDisplayObject)(IDType key, AccessType access) override;
   STDMETHOD_(IndexType, GetDisplayObjectCount)() override;
   STDMETHOD_(void, GetDisplayObject)(IDType key, AccessType access, iDisplayObject* *ppDO) override;
   STDMETHOD_(void, ClearDisplayObjects)() override;
   STDMETHOD_(void, GetDisplayObjects)(iDisplayList** dispList) override;

   // iDisplayObject Implementation
public:
   STDMETHOD_(void, SetID)(IDType id) override { Do_SetID(id); }
   STDMETHOD_(IDType, GetID)() override { return Do_GetID(); }

   STDMETHOD_(void, SetItemData)(void* pItemData, bool bDelete) override { Do_SetItemData(pItemData, bDelete); }
   STDMETHOD_(void, GetItemData)(void** ppItemData) override { Do_GetItemData(ppItemData); }

   STDMETHOD_(void, SetDisplayList)(iDisplayList * pDL) override;
   STDMETHOD_(void, GetDisplayList)(iDisplayList** dispList) override { Do_GetDisplayList(dispList); }

   STDMETHOD_(void, Visible)(BOOL bVisible) override;
   STDMETHOD_(BOOL, IsVisible)() override { return Do_IsVisible(); }

   // Drawing
   STDMETHOD_(void, Draw)(CDC* pDC) override;
   STDMETHOD_(void, Highlite)(CDC* pDC, BOOL bHighlite) override;
#if defined(_DEBUG)
   STDMETHOD_(void, DrawGravityWell)(CDC* pDC) override;
#endif

   // Size and Hit Testing
   STDMETHOD_(void, SetGravityWellStrategy)(iGravityWellStrategy* pStrategy) override { Do_SetGravityWellStrategy(pStrategy); }
   STDMETHOD_(void, GetGravityWellStrategy)(iGravityWellStrategy** pStrategy) override { Do_GetGravityWellStrategy(pStrategy); }
   STDMETHOD_(BOOL, HitTest)(CPoint point) override;
   STDMETHOD_(CRect, GetBoundingBox)() override;
   STDMETHOD_(void, GetBoundingBox)(IRect2d** rect) override;
   STDMETHOD_(BOOL, TouchesRect)(CRect r) override;

   // Selection
   STDMETHOD_(void, Select)(BOOL bSelect) override;
   STDMETHOD_(BOOL, IsSelected)() override { return Do_IsSelected(); }
   STDMETHOD_(void, SetSelectionType)(SelectionType st) override;
   STDMETHOD_(SelectionType, GetSelectionType)() override { return Do_GetSelectionType(); }
   STDMETHOD_(void, RetainSelection)(BOOL bRetain);
   STDMETHOD_(BOOL, RetainSelection)() { return Do_RetainSelection(); }

   // Tool Tips
   STDMETHOD_(void, SetToolTipText)(LPCTSTR lpszToolTipText) override { Do_SetToolTipText(lpszToolTipText); }
   STDMETHOD_(CString, GetToolTipText)() override { return Do_GetToolTipText(); }
   STDMETHOD_(void, SetMaxTipWidth)(INT maxWidth) override { Do_SetMaxTipWidth(maxWidth); }
   STDMETHOD_(INT, GetMaxTipWidth)() override { return Do_GetMaxTipWidth(); }
   STDMETHOD_(void, SetTipDisplayTime)(INT iTime) override { Do_SetTipDisplayTime(iTime); }
   STDMETHOD_(INT, GetTipDisplayTime)() override { return Do_GetTipDisplayTime(); }

   // Interface Events
   STDMETHOD_(bool, OnLButtonDown)(UINT nFlags, CPoint point) override
   {
      return Do_OnLButtonDown(nFlags, point);
   }
   STDMETHOD_(bool, OnLButtonUp)(UINT nFlags, CPoint point) override
   {
      return Do_OnLButtonUp(nFlags, point);
   }
   STDMETHOD_(bool, OnLButtonDblClk)(UINT nFlags, CPoint point) override
   {
      return Do_OnLButtonDblClk(nFlags, point);
   }
   STDMETHOD_(bool, OnRButtonDown)(UINT nFlags, CPoint point) override
   {
      return Do_OnRButtonDown(nFlags, point);
   }
   STDMETHOD_(bool, OnRButtonUp)(UINT nFlags, CPoint point) override
   {
      return Do_OnRButtonUp(nFlags, point);
   }
   STDMETHOD_(bool, OnRButtonDblClk)(UINT nFlags, CPoint point) override
   {
      return Do_OnRButtonDblClk(nFlags, point);
   }
   STDMETHOD_(bool, OnMouseMove)(UINT nFlags, CPoint point) override
   {
      return Do_OnMouseMove(nFlags, point);
   }
   STDMETHOD_(bool, OnMouseWheel)(UINT nFlags, short zDelta, CPoint point) override
   {
      return Do_OnMouseWheel(nFlags, zDelta, point);
   }
   STDMETHOD_(bool, OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) override
   {
      return Do_OnKeyDown(nChar, nRepCnt, nFlags);
   }
   STDMETHOD_(bool, OnContextMenu)(CWnd* pWnd, CPoint point) override
   {
      return Do_OnContextMenu(pWnd, point);
   }

   // Event Sink
   STDMETHOD_(void, RegisterEventSink)(iDisplayObjectEvents* pEventSink) override
   {
      Do_RegisterEventSink(pEventSink);
   }
   STDMETHOD_(void, UnregisterEventSink)() override
   {
      Do_UnregisterEventSink();
   }
   STDMETHOD_(void, GetEventSink)(iDisplayObjectEvents** pEventSink) override
   {
      Do_GetEventSink(pEventSink);
   }

   // Drag Drop
   STDMETHOD_(void, RegisterDropSite)(iDropSite* pDropSite) override { Do_RegisterDropSite(pDropSite); }
   STDMETHOD_(void, UnregisterDropSite)() override { Do_UnregisterDropSite(); }
   STDMETHOD_(void, GetDropSite)(iDropSite** dropSite) override { Do_GetDropSite(dropSite); }

   // Composite
   STDMETHOD_(void, SetParent)(iDisplayObject* pParent) override { Do_SetParent(pParent); }
   STDMETHOD_(void, GetParent)(iDisplayObject** ppParent) override { Do_GetParent(ppParent); }
};

#endif // !defined(AFX_COMPOSITEDISPLAYOBJECT_H__9E3A6AF5_E734_11D4_8B83_006097C68A9C__INCLUDED_)
