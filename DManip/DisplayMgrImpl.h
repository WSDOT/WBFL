///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2011  Washington State Department of Transportation
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
   STDMETHOD_(void,SetView)(CDisplayView* pView);
   STDMETHOD_(CDisplayView*,GetView)();

   STDMETHOD_(void,GetCoordinateMap)(iCoordinateMap** map);

   // Display List Management
   STDMETHOD_(void,AddDisplayList)(iDisplayList* pDL);
   STDMETHOD_(void,GetDisplayList)(long idx,iDisplayList** list);
   STDMETHOD_(void,FindDisplayList)(long id,iDisplayList** list);
   STDMETHOD_(long,GetDisplayListCount)();
   STDMETHOD_(void,RemoveDisplayList)(long key,AccessType access);
   STDMETHOD_(void,ClearDisplayLists)();

   // Display Object Management
   STDMETHOD_(void,AddDisplayObject)(iDisplayObject* pDO,long key,AccessType access);
   STDMETHOD_(void,FindDisplayObject)(long id,long listKey,AccessType access,iDisplayObject** dispObj);
   STDMETHOD_(void,FindDisplayObjects)(CPoint point,DisplayObjectContainer* dispObjs);
   STDMETHOD_(void,FindDisplayObjects)(IPoint2d* point,DisplayObjectContainer* dispObjs);
   STDMETHOD_(void,FindDisplayObjects)(CRect rect,DisplayObjectContainer* dispObjs);
   STDMETHOD_(void,RemoveDisplayObject)(long doKey,AccessType doAccess,long dlKey,AccessType dlAccess);
   STDMETHOD_(void,ClearDisplayObjects)();
   STDMETHOD_(void,ClearDisplayObjects)(long key,AccessType access);
   STDMETHOD_(long,GetDisplayObjectCount)();
   STDMETHOD_(long,GetDisplayObjectFactoryCount)();
   STDMETHOD_(void,AddDisplayObjectFactory)(iDisplayObjectFactory* factory);
   STDMETHOD_(void,GetDisplayObjectFactory)(long idx, iDisplayObjectFactory** factory);

   STDMETHOD_(void,SelectObject)(iDisplayObject* pDO,BOOL bClearSelection);
   STDMETHOD_(void,SelectObjects)(CRect r);
   STDMETHOD_(void,ClearSelectedObjects)();
   STDMETHOD_(void,ClearSelectedObjectsByList)(long key,AccessType access,BOOL bInclusive);
   STDMETHOD_(void,GetSelectedObjects)(DisplayObjectContainer* selObjs);
   STDMETHOD_(void,SelectAll)(BOOL bSelect);

   STDMETHOD_(void,EnableLBtnMultiSelect)(BOOL bEnable,DWORD dwKey);
   STDMETHOD_(BOOL,IsLBtnMultiSelectEnabled)();
   STDMETHOD_(DWORD,GetLBtnMultiSelectKey)();
   STDMETHOD_(void,EnableLBtnSelectRect)(BOOL bEnable);
   STDMETHOD_(BOOL,IsLBtnSelectRectEnabled)();
   STDMETHOD_(void,EnableLBtnSelect)(BOOL bEnable);
   STDMETHOD_(BOOL,IsLBtnSelectEnabled)();
   STDMETHOD_(void,EnableRBtnSelect)(BOOL bEnable);
   STDMETHOD_(BOOL,IsRBtnSelectEnabled)();

   STDMETHOD_(void,DrawDisplayObjects)(CDC* pDC);
   STDMETHOD_(void,SetSelectionFillColor)(COLORREF color);
   STDMETHOD_(void,SetSelectionLineColor)(COLORREF color);
   STDMETHOD_(COLORREF,GetSelectionFillColor)();
   STDMETHOD_(COLORREF,GetSelectionLineColor)();
   STDMETHOD_(void,GetBoundingBox)(iCoordinateMap* pMap, bool boundOrigin, IRect2d** ppRect);
   STDMETHOD_(void,InvalidateRect)(LPCRECT lpRect);
   STDMETHOD_(void,InvalidateRgn)(CRgn* pRgn);

#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWells)(CDC* pDC);
#endif

   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags, CPoint point);
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags, short zDelta, CPoint point);
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags);
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point);
   STDMETHOD_(BOOL,OnNeedToolTipText)(UINT id,NMHDR* pNMHDR,LRESULT* pResult);
   STDMETHOD_(int,OnToolHitTest)(CPoint point,TOOLINFO* pTI);

  	STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	STDMETHOD_(void,OnDragLeave)();
	STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
   STDMETHOD_(DROPEFFECT,OnDragScroll)( DWORD dwKeyState, CPoint point );

   // Drag and Drop
   STDMETHOD_(void,PrepareDragData)(iDragDataSink* pSink);
   STDMETHOD_(void,CreateDragObjects)(COleDataObject* pDataObject);
   STDMETHOD_(void,DrawDragObjects)(const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,DestroyDragObjects)();
   STDMETHOD_(void,SetDropSite)(iDropSite* pDropSite);
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite);
   STDMETHOD_(void,HighliteDropSite)(BOOL bHighlite);
   STDMETHOD_(void,OnDragFinished)(DROPEFFECT de);

   STDMETHOD_(void,SetTaskFactory)(iTaskFactory* pFactory);
   STDMETHOD_(void,GetTaskFactory)(iTaskFactory** factory);
   STDMETHOD_(void,SetTask)(iTask* pTask);

   // iDisplayListEvents
   STDMETHOD_(void,OnDisplayObjectAdded)(long listID,iDisplayObject* pDO);
   STDMETHOD_(void,OnDisplayObjectRemoved)(long listID,long doID);
   STDMETHOD_(void,OnDisplayObjectsCleared)(long listID);

   // Event Sink - This gives the canvas a pluggable event handling strategy for events 
   //              that are not handled by display objects
   STDMETHOD_(void,RegisterEventSink)(iDisplayMgrEvents* pEventSink);
   STDMETHOD_(void,UnregisterEventSink)();
   STDMETHOD_(void,GetEventSink)(iDisplayMgrEvents** pEventSink);

private:
   CDisplayView* m_pView;

   typedef CAdapt< CComPtr<iDisplayObjectFactory> > DisplayObjectFactoriesItem; 
   typedef std::vector<DisplayObjectFactoriesItem> DisplayObjectFactoriesContainer; 
   typedef DisplayObjectFactoriesContainer::iterator DisplayObjectFactoriesIterator; 
   DisplayObjectFactoriesContainer m_pDisplayObjectFactories;

   CComPtr<iTaskFactory> m_pTaskFactory;
   CComPtr<iTask> m_pCurrTask;

   typedef CAdapt<CComPtr<iDraggable> > DragMember;
   typedef std::vector<DragMember> DragList;
   DragList m_DragList;

   COleDropTarget m_DropTarget; // This view is an OLE drop target

   CComPtr<iDisplayObject> m_ToolTipObject; // Current object for which tool tip text will be requested
   CString m_strToolTipText;

   iDropSite* m_pDropSite; // Object that a drag/drop payload is about to be dropped on

   typedef CAdapt<CComPtr<iDisplayList> > DisplayListItem;
   typedef std::vector<DisplayListItem> DisplayListContainer;
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
