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

#ifndef INCLUDED_DISPLAYMGR_H_
#define INCLUDED_DISPLAYMGR_H_
#pragma once

#include <DManip\DisplayObjectContainer.h>
#include <DManip\DManipTypes.h>

class CDisplayView;
interface iCoordinateMap;
interface iDisplayObject;
interface iDisplayObjectFactory;
interface iDisplayList;
interface iDropSite;
interface iDraggable;
interface iDragDataSink;
interface iTaskFactory;
interface iTask;
interface iDisplayMgrEvents;

interface iDisplayMgr : public IUnknown
{
   STDMETHOD_(void,SetView)(CDisplayView* pView) PURE;

   // Be very careful using the View!!!
   // Do not use the view unless you are ABSOLUTELY SURE that the method you are 
   // calling it from has nothing to do with printing or print preview. If all you 
   // need is scaling, use GetCoordinateMap from below. 
   // If all you want is to call InvalidateRect, or InvalidateRgn, call the methods below
   STDMETHOD_(CDisplayView*,GetView)() PURE;

   STDMETHOD_(void,GetCoordinateMap)(iCoordinateMap** map) PURE;

   // Display List Management
   STDMETHOD_(void,AddDisplayList)(iDisplayList* pDL) PURE;
   STDMETHOD_(void,GetDisplayList)(CollectionIndexType idx,iDisplayList** list) PURE;
   STDMETHOD_(void,FindDisplayList)(IDType id,iDisplayList** list) PURE;
   STDMETHOD_(CollectionIndexType,GetDisplayListCount)() PURE;
   STDMETHOD_(void,RemoveDisplayList)(IDType key,AccessType access) PURE;
   STDMETHOD_(void,ClearDisplayLists)() PURE;

   // Display Object Management
   STDMETHOD_(void,AddDisplayObject)(iDisplayObject* pDO,IDType key,AccessType access) PURE;
   STDMETHOD_(void,FindDisplayObject)(IDType id,IDType listKey,AccessType access,iDisplayObject** dispObj) PURE;
   STDMETHOD_(void,FindDisplayObjects)(CPoint point,DisplayObjectContainer* dispObjs) PURE;
   STDMETHOD_(void,FindDisplayObjects)(IPoint2d* point,DisplayObjectContainer* dispObjs) PURE;
   STDMETHOD_(void,FindDisplayObjects)(CRect rect,DisplayObjectContainer* dispObjs) PURE;
   STDMETHOD_(void,RemoveDisplayObject)(IDType doKey,AccessType doAccess,IDType dlKey,AccessType dlAccess) PURE;
   STDMETHOD_(void,ClearDisplayObjects)() PURE;
   STDMETHOD_(void,ClearDisplayObjects)(IDType key,AccessType access) PURE;
   STDMETHOD_(CollectionIndexType,GetDisplayObjectCount)() PURE;
   STDMETHOD_(CollectionIndexType,GetDisplayObjectFactoryCount)() PURE;
   STDMETHOD_(void,AddDisplayObjectFactory)(iDisplayObjectFactory* factory) PURE;
   STDMETHOD_(void,GetDisplayObjectFactory)(CollectionIndexType idx, iDisplayObjectFactory** factory) PURE;

   // Selecting and Selections
   STDMETHOD_(void,SelectObject)(iDisplayObject* pDO,BOOL bClearSelection) PURE;
   STDMETHOD_(void,SelectObjects)(CRect r) PURE;
   STDMETHOD_(void,ClearSelectedObjects)() PURE;
   STDMETHOD_(void,ClearSelectedObjectsByList)(IDType key,AccessType access,BOOL bInclusive) PURE;
   STDMETHOD_(void,GetSelectedObjects)(DisplayObjectContainer* selObjs) PURE;
   STDMETHOD_(void,SelectAll)(BOOL bSelect) PURE;

   // Selection Methods
   STDMETHOD_(void,EnableLBtnMultiSelect)(BOOL bEnable,DWORD dwKey) PURE;
   STDMETHOD_(BOOL,IsLBtnMultiSelectEnabled)() PURE;
   STDMETHOD_(DWORD,GetLBtnMultiSelectKey)() PURE;
   STDMETHOD_(void,EnableLBtnSelectRect)(BOOL bEnable) PURE;
   STDMETHOD_(BOOL,IsLBtnSelectRectEnabled)() PURE;
   STDMETHOD_(void,EnableLBtnSelect)(BOOL bEnable) PURE;
   STDMETHOD_(BOOL,IsLBtnSelectEnabled)() PURE;
   STDMETHOD_(void,EnableRBtnSelect)(BOOL bEnable) PURE;
   STDMETHOD_(BOOL,IsRBtnSelectEnabled)() PURE;

   // Drawing
   STDMETHOD_(void,DrawDisplayObjects)(CDC* pDC) PURE;
   STDMETHOD_(void,SetSelectionFillColor)(COLORREF color) PURE;
   STDMETHOD_(void,SetSelectionLineColor)(COLORREF color) PURE;
   STDMETHOD_(COLORREF,GetSelectionFillColor)() PURE;
   STDMETHOD_(COLORREF,GetSelectionLineColor)() PURE;
   STDMETHOD_(void,GetBoundingBox)(iCoordinateMap* pMap, bool boundOrigin, IRect2d** ppRect) PURE;
   STDMETHOD_(void,InvalidateRect)(LPCRECT lpRect) PURE;
   STDMETHOD_(void,InvalidateRgn)(CRgn* pRgn) PURE;

#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWells)(CDC* pDC) PURE;
#endif

   // Input Events
   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags, CPoint point) PURE;
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags, short zDelta, CPoint point) PURE;
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) PURE;
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point) PURE;

   // Tool Tips
   STDMETHOD_(BOOL,OnNeedToolTipText)(UINT id,NMHDR* pNMHDR,LRESULT* pResult) PURE;
   STDMETHOD_(INT_PTR,OnToolHitTest)(CPoint point,TOOLINFO* pTI) PURE;

   // OLE Drag/Drop Events
 	STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) PURE;
	STDMETHOD_(void,OnDragLeave)() PURE;
	STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) PURE;
	STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) PURE;
   STDMETHOD_(DROPEFFECT,OnDragScroll)( DWORD dwKeyState, CPoint point ) PURE;

   // Drag and Drop
   STDMETHOD_(void,PrepareDragData)(iDragDataSink* pSink) PURE;
   STDMETHOD_(void,CreateDragObjects)(COleDataObject* pDataObject) PURE;
   STDMETHOD_(void,DrawDragObjects)(const CPoint& dragStart, const CPoint& dragPoint) PURE;
   STDMETHOD_(void,DestroyDragObjects)() PURE;
   STDMETHOD_(void,SetDropSite)(iDropSite* pDropSite) PURE;
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) PURE;
   STDMETHOD_(void,HighliteDropSite)(BOOL bHighlite) PURE;
   STDMETHOD_(void,OnDragFinished)(DROPEFFECT de) PURE;

   // Tasks
   STDMETHOD_(void,SetTaskFactory)(iTaskFactory* pFactory) PURE;
   STDMETHOD_(void,GetTaskFactory)(iTaskFactory** factory) PURE;
   STDMETHOD_(void,SetTask)(iTask* pTask) PURE;

   // Event Sink - This gives the canvas a pluggable event handling strategy for events 
   //              that are not handled by display objects
   STDMETHOD_(void,RegisterEventSink)(iDisplayMgrEvents* pEventSink) PURE;
   STDMETHOD_(void,UnregisterEventSink)() PURE;
   STDMETHOD_(void,GetEventSink)(iDisplayMgrEvents** pEventSink) PURE;

};

#endif // INCLUDED_DISPLAYMGR_H_