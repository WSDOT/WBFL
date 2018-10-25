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

#ifndef INCLUDED_DISPLAYOBJECT_H_
#define INCLUDED_DISPLAYOBJECT_H_
#pragma once

interface iCoordinateMap;
interface iDisplayList;
interface iDisplayObjectEvents;
interface iDropSite;
interface iGravityWellStrategy;
interface IRect2d;

typedef enum SelectionType
{
   stNone  = 1, // cannot be selected
   stNotUI = 2, // cannot be selected via the user interface (but can be selected through code)
   stAll   = 3  // can be selected by any means
} SelectionType;

interface iDisplayObject : public IUnknown
{
   STDMETHOD_(void,SetID)(IDType id) PURE;
   STDMETHOD_(IDType,GetID)() PURE;

   STDMETHOD_(void,SetItemData)(void* pVoid,bool bDelete) PURE;
   STDMETHOD_(void,GetItemData)(void** ppVoid) PURE;

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL) PURE;
   STDMETHOD_(void,GetDisplayList)(iDisplayList** list) PURE;

   STDMETHOD_(void,Visible)(BOOL bVisible) PURE;
   STDMETHOD_(BOOL,IsVisible)() PURE;

   // Drawing
   STDMETHOD_(void,Draw)(CDC* pDC) PURE;
   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite) PURE;
#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWell)(CDC* pDC) PURE;
#endif

   // Size and Hit Testing
   STDMETHOD_(void,SetGravityWellStrategy)(iGravityWellStrategy* pStrategy) PURE;
   STDMETHOD_(void,GetGravityWellStrategy)(iGravityWellStrategy** pStrategy) PURE;
   STDMETHOD_(BOOL,HitTest)(CPoint point) PURE;
   STDMETHOD_(CRect,GetBoundingBox)() PURE;
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect) PURE;
   STDMETHOD_(BOOL,TouchesRect)(CRect r) PURE;

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) PURE;
   STDMETHOD_(BOOL,IsSelected)() PURE;
   STDMETHOD_(void,SetSelectionType)(SelectionType st) PURE;
   STDMETHOD_(SelectionType,GetSelectionType)() PURE;

   // Tool Tips
//   virtual BOOL ToolTipHitTest(CPoint point) = 0;
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText) PURE;
   STDMETHOD_(CString,GetToolTipText)() PURE;
   STDMETHOD_(void,SetMaxTipWidth)(INT maxWidth) PURE;
   STDMETHOD_(INT,GetMaxTipWidth)() PURE;
   STDMETHOD_(void,SetTipDisplayTime)(INT iTime) PURE;
   STDMETHOD_(INT,GetTipDisplayTime)() PURE;

   // Interface Events
   // Called by the framework when UI events occur that are directed
   // towards this display object.
   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags,CPoint point) PURE;
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags,short zDelta,CPoint point) PURE;
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) PURE;
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point) PURE;

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink) PURE;
   STDMETHOD_(void,UnregisterEventSink)() PURE;
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink) PURE;

   // Drag Drop
   STDMETHOD_(void,SetDropSite)(iDropSite* pDropSite) PURE;
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) PURE;
};

#endif // INCLUDED_DISPLAYOBJECT_H_