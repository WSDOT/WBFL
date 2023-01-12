///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <memory>

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
   HRESULT FinalConstruct();
   void FinalRelease();

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
   STDMETHOD_(void,SetID)(IDType id) override { Do_SetID(id); }
   STDMETHOD_(IDType,GetID)() override { return Do_GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) override { Do_SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) override { Do_GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL) override { Do_SetDisplayList(pDL); }
   STDMETHOD_(void,GetDisplayList)(iDisplayList** list) override { Do_GetDisplayList(list); }

   STDMETHOD_(void,Visible)(BOOL bVisible) override { Do_Visible(bVisible); }
   STDMETHOD_(BOOL,IsVisible)() override { return Do_IsVisible(); }

   // Drawing
   STDMETHOD_(void,Draw)(CDC* pDC) override;
   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite) override;
#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWell)(CDC* pDC) override { Do_DrawGravityWell(pDC); }
#endif 

   // Size and Hit Testing
   STDMETHOD_(void,SetGravityWellStrategy)(iGravityWellStrategy* pStrategy) override { Do_SetGravityWellStrategy(pStrategy); }
   STDMETHOD_(void,GetGravityWellStrategy)(iGravityWellStrategy** pStrategy) override { Do_GetGravityWellStrategy(pStrategy); }
   STDMETHOD_(BOOL,HitTest)(CPoint point) override { return Do_HitTest(point); }
   STDMETHOD_(CRect,GetBoundingBox)() override  { return Do_GetBoundingBox(); }
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect) override;
   STDMETHOD_(BOOL,TouchesRect)(CRect r) override { return Do_TouchesRect(r); }

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) override {Do_Select(bSelect);}
   STDMETHOD_(BOOL,IsSelected)() override {return Do_IsSelected();}
   STDMETHOD_(void,SetSelectionType)(SelectionType st) override { Do_SetSelectionType(st); }
   STDMETHOD_(SelectionType,GetSelectionType)() override { return Do_GetSelectionType(); }
   STDMETHOD_(void, RetainSelection)(BOOL bRetain) { Do_RetainSelection(bRetain); }
   STDMETHOD_(BOOL, RetainSelection)() { return Do_RetainSelection(); }

   // Interface Events
   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags,short zDelta,CPoint point) override;
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) override;
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point) override;

   // Tool Tips
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText) override {Do_SetToolTipText(lpszToolTipText);}
   STDMETHOD_(CString,GetToolTipText)() override;
   STDMETHOD_(void,SetMaxTipWidth)(INT maxWidth) override { Do_SetMaxTipWidth(maxWidth); }
   STDMETHOD_(INT,GetMaxTipWidth)() override { return Do_GetMaxTipWidth(); }
   STDMETHOD_(void,SetTipDisplayTime)(INT iTime) override { Do_SetTipDisplayTime(iTime); }
   STDMETHOD_(INT,GetTipDisplayTime)() override { return Do_GetTipDisplayTime(); }

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink) override
   { Do_RegisterEventSink(pEventSink); }
   STDMETHOD_(void,UnregisterEventSink)() override
   { Do_UnregisterEventSink(); }
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink) override
   { Do_GetEventSink(pEventSink); }

   // Drag Drop
   STDMETHOD_(void,RegisterDropSite)(iDropSite* pDropSite) override { Do_RegisterDropSite(pDropSite); }
   STDMETHOD_(void,UnregisterDropSite)() override { Do_UnregisterDropSite(); }
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) override { Do_GetDropSite(dropSite); }

   // Composite
   STDMETHOD_(void, SetParent)(iDisplayObject* pParent) override { Do_SetParent(pParent); }
   STDMETHOD_(void, GetParent)(iDisplayObject** ppParent) override { Do_GetParent(ppParent); }

   // iDraggable Implementation
   STDMETHOD_(void,SetDragData)(iDragData* dd) override;
   STDMETHOD_(void,GetDragData)(iDragData** dd) override;
   STDMETHOD_(UINT,Format)() override;
   STDMETHOD_(void,PrepareDrag)(iDragDataSink* pSink) override;
   STDMETHOD_(void,OnDrop)(iDragDataSource* pSource) override;
   STDMETHOD_(void,DrawDragImage)(CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint) override;
   STDMETHOD_(void,OnDragMoved)(ISize2d* offset) override;
   STDMETHOD_(void,OnMoved)() override;
   STDMETHOD_(void,OnCopied)() override;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILegendDisplayObject
   STDMETHOD_(void,put_Position)(IPoint2d* pos,BOOL bRedraw,BOOL bFireEvent) override;
   STDMETHOD_(void,get_Position)(IPoint2d* *pos) override;
   STDMETHOD_(void,get_Title)(BSTR *pVal) override;
   STDMETHOD_(void,put_Title)(BSTR newVal) override;
   STDMETHOD_(void,put_Font)(const LOGFONT& Font) override;
   STDMETHOD_(void,get_Font)(LOGFONT* pFont) override;
   STDMETHOD_(void,get_NumEntries)(CollectionIndexType* count) override;
   STDMETHOD_(void,AddEntry)(iLegendEntry* entry) override;
   STDMETHOD_(HRESULT,InsertEntry)(CollectionIndexType index, iLegendEntry* entry) override;
   STDMETHOD_(HRESULT,get_Entry)(CollectionIndexType index, iLegendEntry* *entry) override;
   STDMETHOD_(HRESULT,RemoveEntry)(CollectionIndexType index) override;
   STDMETHOD_(void,ClearEntries)() override;
   STDMETHOD_(void,get_NumRows)(CollectionIndexType* count) override;
   STDMETHOD_(void,put_NumRows)(CollectionIndexType count) override;
   STDMETHOD_(void,get_CellSize)(CSize* size) override;
   STDMETHOD_(void,put_CellSize)(CSize size) override;
   STDMETHOD_(void,GetMinCellSize)(CSize* size) override;
   STDMETHOD_(void,get_DoDrawBorder)(BOOL* doDraw) override;
   STDMETHOD_(void,put_DoDrawBorder)(BOOL doDraw) override;
   STDMETHOD_(void,get_DoFill)(BOOL* doDraw) override;
   STDMETHOD_(void,put_DoFill)(BOOL doDraw) override;
   STDMETHOD_(COLORREF,get_FillColor)() override;
   STDMETHOD_(void,put_FillColor)(COLORREF color) override;
   STDMETHOD_(void,get_IsDraggable)(BOOL* doDraw) override;
   STDMETHOD_(void,put_IsDraggable)(BOOL doDraw) override;

   // iMessageListener
   virtual void OnCaughtMessage(int msg) override;

private:
   void Draw(CDC* pDC, iCoordinateMap* map, const CPoint& location, BOOL hiLite, BOOL beingDragged=FALSE);
   void GetBoundingBoxEx(IRect2d** rect, bool includeTitle); 

   CComPtr<IPoint2d> m_Position;
   CComBSTR m_Title;
   LOGFONT  m_Font;
   RowIndexType m_NumRows;
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

   std::unique_ptr<CLegendMessageCatcher> m_pMessageCatcher;
};

#endif //__LEGENDDISPLAYOBJECT_H_
