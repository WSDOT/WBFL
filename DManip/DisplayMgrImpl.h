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

// DisplayMgrImpl.h: interface for the CDisplayMgrImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYMGRIMPL_H__BCB8A10C_E659_11D4_8B81_006097C68A9C__INCLUDED_)
#define AFX_DISPLAYMGRIMPL_H__BCB8A10C_E659_11D4_8B81_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <afxole.h> // For drag and drop
#include <vector>
#include <DManip\DisplayListEvents.h>
#include <DManip\DisplayMgrEvents.h>
 
class ATL_NO_VTABLE CDisplayMgrImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDisplayMgrImpl,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CDisplayMgrImpl, &CLSID_DisplayMgr>,
   public iDisplayMgr,
   public iDisplayListEvents
{
public:
	CDisplayMgrImpl();
	virtual ~CDisplayMgrImpl();

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_DISPLAYMGR)

BEGIN_COM_MAP(CDisplayMgrImpl)
	COM_INTERFACE_ENTRY(iDisplayMgr)
   COM_INTERFACE_ENTRY(iDisplayListEvents)
END_COM_MAP()

   // iDisplayMgr Implementation
public:
   STDMETHOD_(void,SetView)(CDisplayView* pView) override;
   STDMETHOD_(CDisplayView*,GetView)() override;

   STDMETHOD_(void,GetCoordinateMap)(iCoordinateMap** map) override;

   // Display List Management
   STDMETHOD_(void,AddDisplayList)(iDisplayList* pDL) override;
   STDMETHOD_(void,GetDisplayList)(IndexType idx,iDisplayList** list) override;
   STDMETHOD_(void,FindDisplayList)(IDType id,iDisplayList** list) override;
   STDMETHOD_(IndexType,GetDisplayListCount)() override;
   STDMETHOD_(void,RemoveDisplayList)(IDType key,AccessType access) override;
   STDMETHOD_(void,ClearDisplayLists)() override;

   // Display Object Management
   STDMETHOD_(void,AddDisplayObject)(iDisplayObject* pDO,IDType key,AccessType access) override;
   STDMETHOD_(void,FindDisplayObject)(IDType id,IDType listKey,AccessType access,iDisplayObject** dispObj) override;
   STDMETHOD_(void,FindDisplayObjects)(CPoint point,DisplayObjectContainer* dispObjs) override;
   STDMETHOD_(void,FindDisplayObjects)(IPoint2d* point,DisplayObjectContainer* dispObjs) override;
   STDMETHOD_(void,FindDisplayObjects)(CRect rect,DisplayObjectContainer* dispObjs) override;
   STDMETHOD_(void,RemoveDisplayObject)(IDType doKey,AccessType doAccess,IDType dlKey,AccessType dlAccess) override;
   STDMETHOD_(void,ClearDisplayObjects)() override;
   STDMETHOD_(void,ClearDisplayObjects)(IDType key,AccessType access) override;
   STDMETHOD_(IndexType,GetDisplayObjectCount)() override;
   STDMETHOD_(IndexType,GetDisplayObjectFactoryCount)() override;
   STDMETHOD_(void,AddDisplayObjectFactory)(iDisplayObjectFactory* factory) override;
   STDMETHOD_(void,GetDisplayObjectFactory)(IndexType idx, iDisplayObjectFactory** factory) override;

   STDMETHOD_(void,SelectObject)(iDisplayObject* pDO,BOOL bClearSelection) override;
   STDMETHOD_(void,SelectObjects)(CRect r) override;
   STDMETHOD_(void,ClearSelectedObjects)() override;
   STDMETHOD_(void,ClearSelectedObjectsByList)(IDType key,AccessType access,BOOL bInclusive) override;
   STDMETHOD_(void,GetSelectedObjects)(DisplayObjectContainer* selObjs) override;
   STDMETHOD_(void,SelectAll)(BOOL bSelect) override;

   STDMETHOD_(void,EnableLBtnMultiSelect)(BOOL bEnable,DWORD dwKey) override;
   STDMETHOD_(BOOL,IsLBtnMultiSelectEnabled)() override;
   STDMETHOD_(DWORD,GetLBtnMultiSelectKey)() override;
   STDMETHOD_(void,EnableLBtnSelectRect)(BOOL bEnable) override;
   STDMETHOD_(BOOL,IsLBtnSelectRectEnabled)() override;
   STDMETHOD_(void,EnableLBtnSelect)(BOOL bEnable) override;
   STDMETHOD_(BOOL,IsLBtnSelectEnabled)() override;
   STDMETHOD_(void,EnableRBtnSelect)(BOOL bEnable) override;
   STDMETHOD_(BOOL,IsRBtnSelectEnabled)() override;

   STDMETHOD_(void,DrawDisplayObjects)(CDC* pDC) override;
   STDMETHOD_(void,SetSelectionFillColor)(COLORREF color) override;
   STDMETHOD_(void,SetSelectionLineColor)(COLORREF color) override;
   STDMETHOD_(COLORREF,GetSelectionFillColor)() override;
   STDMETHOD_(COLORREF,GetSelectionLineColor)() override;
   STDMETHOD_(void,GetBoundingBox)(bool boundOrigin, IRect2d** ppRect) override;
   STDMETHOD_(void,InvalidateRect)(LPCRECT lpRect) override;
   STDMETHOD_(void,InvalidateRgn)(CRgn* pRgn) override;

#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWells)(CDC* pDC) override;
#endif

   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags, CPoint point) override;
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags, short zDelta, CPoint point) override;
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) override;
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point) override;
   STDMETHOD_(BOOL,OnNeedToolTipText)(UINT id,NMHDR* pNMHDR,LRESULT* pResult) override;
   STDMETHOD_(INT_PTR,OnToolHitTest)(CPoint point,TOOLINFO* pTI) override;

  	STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) override;
	STDMETHOD_(void,OnDragLeave)() override;
	STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) override;
	STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) override;
   STDMETHOD_(DROPEFFECT,OnDragScroll)( DWORD dwKeyState, CPoint point ) override;

   // Drag and Drop
   STDMETHOD_(void,PrepareDragData)(iDragDataSink* pSink) override;
   STDMETHOD_(void,CreateDragObjects)(COleDataObject* pDataObject) override;
   STDMETHOD_(void,DrawDragObjects)(const CPoint& dragStart, const CPoint& dragPoint) override;
   STDMETHOD_(void,DestroyDragObjects)() override;
   STDMETHOD_(void,RegisterDropSite)(iDropSite* pDropSite) override;
   STDMETHOD_(void,UnregisterDropSite)() override;
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) override;
   STDMETHOD_(void,HighliteDropSite)(BOOL bHighlite) override;
   STDMETHOD_(void,OnDragFinished)(DROPEFFECT de) override;

   STDMETHOD_(void,SetTaskFactory)(iTaskFactory* pFactory) override;
   STDMETHOD_(void,GetTaskFactory)(iTaskFactory** factory) override;
   STDMETHOD_(void,SetTask)(iTask* pTask) override;

   // iDisplayListEvents
   STDMETHOD_(void,OnDisplayObjectAdded)(IDType listID,iDisplayObject* pDO) override;
   STDMETHOD_(void,OnDisplayObjectRemoved)(IDType listID,SIZE_T doID) override;
   STDMETHOD_(void,OnDisplayObjectsCleared)(IDType listID) override;

   // Event Sink - This gives the canvas a pluggable event handling strategy for events 
   //              that are not handled by display objects
   STDMETHOD_(void,RegisterEventSink)(iDisplayMgrEvents* pEventSink) override;
   STDMETHOD_(void,UnregisterEventSink)() override;
   STDMETHOD_(void,GetEventSink)(iDisplayMgrEvents** pEventSink) override;

private:
   CDisplayView* m_pView;

   using DisplayObjectFactoriesItem = CAdapt< CComPtr<iDisplayObjectFactory>>;
   using DisplayObjectFactoriesContainer = std::vector<DisplayObjectFactoriesItem>;
   using DisplayObjectFactoriesIterator = DisplayObjectFactoriesContainer::iterator;
   DisplayObjectFactoriesContainer m_pDisplayObjectFactories;

   CComPtr<iTaskFactory> m_pTaskFactory;
   CComPtr<iTask> m_pCurrTask;

   using DragMember = CAdapt<CComPtr<iDraggable> >;
   using DragList = std::vector<DragMember>;
   DragList m_DragList;

   COleDropTarget m_DropTarget; // This view is an OLE drop target

   CComPtr<iDisplayObject> m_ToolTipObject; // Current object for which tool tip text will be requested
   CString m_strToolTipText;

   iDropSite* m_pDropSite; // Object that a drag/drop payload is about to be dropped on

   using DisplayListItem = CAdapt<CComPtr<iDisplayList> >;
   using DisplayListContainer = std::vector<DisplayListItem> ;
   DisplayListContainer m_DisplayLists;

   BOOL m_bLBtnMultiSelectEnabled;
   DWORD m_dwLBtnMultiSelectKey;
   BOOL m_bLBtnRectSelectEnabled;
   BOOL m_bLBtnSelectEnabled;
   BOOL m_bRBtnSelectEnabled;

   COLORREF m_crSelectionFill;
   COLORREF m_crSelectionLine;

   DisplayObjectContainer m_SelectedObjects;  // The display objects that are currently selected

   std::vector<CComPtr<iDisplayObject> > FindAllDisplayObjects(CPoint point);
   std::vector<CComPtr<iDisplayObject> > FindAllSelectableDisplayObjects(CPoint point);
   void FindNextSelectableDisplayObject(CPoint point,iDisplayObject* *pDispObj);

   CComPtr<iDisplayMgrEvents> m_EventSink;
};

#endif // !defined(AFX_DISPLAYMGRIMPL_H__BCB8A10C_E659_11D4_8B81_006097C68A9C__INCLUDED_)
