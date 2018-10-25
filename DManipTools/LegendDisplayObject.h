///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

// LegendDisplayObject.h : Declaration of the CLegendDisplayObject

#ifndef __LEGENDDISPLAYOBJECT_H_
#define __LEGENDDISPLAYOBJECT_H_
#pragma once

#include "resource.h"       // main symbols
#include <DManip\DisplayObjectDefaultImpl.h>

#include "LegendMessageCatcher.h"

/////////////////////////////////////////////////////////////////////////////
// CLegendDisplayObject
class ATL_NO_VTABLE CLegendDisplayObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLegendDisplayObject, &CLSID_LegendDisplayObject>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLegendDisplayObject>,
	public iLegendDisplayObject,
   public CDisplayObjectDefaultImpl,
   public iDraggable,
   public iMessageListener
{
public:
	CLegendDisplayObject();

DECLARE_REGISTRY_RESOURCEID(IDR_LEGENDDISPLAYOBJECT)

DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLegendDisplayObject)
	COM_INTERFACE_ENTRY(iLegendDisplayObject)
	COM_INTERFACE_ENTRY(iDisplayObject)
	COM_INTERFACE_ENTRY(iDraggable)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLegendDisplayObject)
END_CONNECTION_POINT_MAP()

   // clipboard format
   static UINT ms_cfFormat;

   // iDisplayObject Implementation
   STDMETHOD_(void,SetID)(long id) { Do_SetID(id); }
   STDMETHOD_(long,GetID)() { return Do_GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) { Do_SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) { Do_GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL) { Do_SetDisplayList(pDL); }
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
   STDMETHOD_(CRect,GetBoundingBox)(){ return Do_GetBoundingBox(); }
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect); 
   STDMETHOD_(BOOL,TouchesRect)(CRect r) { return Do_TouchesRect(r); }

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) {Do_Select(bSelect);}
   STDMETHOD_(BOOL,IsSelected)() {return Do_IsSelected();}
   STDMETHOD_(void,SetSelectionType)(SelectionType st) { Do_SetSelectionType(st); }
   STDMETHOD_(SelectionType,GetSelectionType)() { return Do_GetSelectionType(); }

   // Interface Events
   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags,short zDelta,CPoint point);
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags);
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point);

   // Tool Tips
   STDMETHOD_(void,SetToolTipText)(LPCSTR lpszToolTipText) {Do_SetToolTipText(lpszToolTipText);}
   STDMETHOD_(CString,GetToolTipText)();
   STDMETHOD_(void,SetMaxTipWidth)(long maxWidth) { Do_SetMaxTipWidth(maxWidth); }
   STDMETHOD_(long,GetMaxTipWidth)() { return Do_GetMaxTipWidth(); }

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink)
   { Do_RegisterEventSink(pEventSink); }
   STDMETHOD_(void,UnregisterEventSink)()
   { Do_UnregisterEventSink(); }
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink)
   { Do_GetEventSink(pEventSink); }

   // Drag Drop
   STDMETHOD_(void,SetDropSite)(iDropSite* pDropSite) { Do_SetDropSite(pDropSite); }
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) { Do_GetDropSite(dropSite); }

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

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILegendDisplayObject
   STDMETHOD_(void,put_Position)(IPoint2d* pos,BOOL bRedraw,BOOL bFireEvent);
   STDMETHOD_(void,get_Position)(IPoint2d* *pos);
   STDMETHOD_(void,get_Title)(BSTR *pVal);
   STDMETHOD_(void,put_Title)(BSTR newVal);
   STDMETHOD_(void,put_Font)(const LOGFONT& Font);
   STDMETHOD_(void,get_Font)(LOGFONT* pFont);
   STDMETHOD_(void,get_NumEntries)(long* count);
   STDMETHOD_(void,AddEntry)(iLegendEntry* entry);
   STDMETHOD_(HRESULT,InsertEntry)(long index, iLegendEntry* entry);
   STDMETHOD_(HRESULT,get_Entry)(long index, iLegendEntry* *entry);
   STDMETHOD_(HRESULT,RemoveEntry)(long index);
   STDMETHOD_(void,ClearEntries)();
   STDMETHOD_(void,get_NumRows)(long* count);
   STDMETHOD_(void,put_NumRows)(long count);
   STDMETHOD_(void,get_CellSize)(CSize* size);
   STDMETHOD_(void,put_CellSize)(CSize size);
   STDMETHOD_(void,GetMinCellSize)(CSize* size);
   STDMETHOD_(void,get_DoDrawBorder)(BOOL* doDraw);
   STDMETHOD_(void,put_DoDrawBorder)(BOOL doDraw);
   STDMETHOD_(void,get_DoFill)(BOOL* doDraw);
   STDMETHOD_(void,put_DoFill)(BOOL doDraw);
   STDMETHOD_(COLORREF,get_FillColor)();
   STDMETHOD_(void,put_FillColor)(COLORREF color);
   STDMETHOD_(void,get_IsDraggable)(BOOL* doDraw);
   STDMETHOD_(void,put_IsDraggable)(BOOL doDraw);

   // iMessageListener
   virtual void OnCaughtMessage(int msg);

public:
   HRESULT FinalConstruct();
   void FinalRelease();

private:
   void Draw(CDC* pDC, iCoordinateMap* map, const CPoint& location, BOOL hiLite, BOOL beingDragged=FALSE);
   void GetBoundingBoxEx(IRect2d** rect, bool includeTitle); 

   CComPtr<IPoint2d> m_Position;
   CComBSTR m_Title;
   LOGFONT  m_Font;
   long     m_NumRows;
   BOOL     m_DoDrawBorder;
   BOOL     m_DoFill;
   COLORREF m_FillColor;
   CSize    m_CellSize;
   BOOL     m_IsDraggable;

   typedef CAdapt<CComPtr<iLegendEntry> > ContainerItem;
   typedef std::vector<ContainerItem>     Container;
   typedef Container::iterator            ContainerIterator;
   Container m_Container;

   CComPtr<iDragData> m_pDragData;

   CSize m_DragOffset; // only for dragging - used to make dragging smooth

   std::auto_ptr<CLegendMessageCatcher> m_pMessageCatcher;
};

#endif //__LEGENDDISPLAYOBJECT_H_
