///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// EditableTextBlock.h: interface for the CEditableTextBlockImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITABLEUNITVALUETEXTBLOCK_H__FC76B7E5_E710_11D4_8B82_006097C68A9C__INCLUDED_)
#define AFX_EDITABLEUNITVALUETEXTBLOCK_H__FC76B7E5_E710_11D4_8B82_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "InplaceEditDefaultImpl.h"
#include <WBFLCogo.h>

class CInplaceEdit;

class ATL_NO_VTABLE CEditableUnitValueTextBlockImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEditableUnitValueTextBlockImpl, &CLSID_EditableUnitValueTextBlock>,
   public CInplaceEditDefaultImpl,
   public iEditableUnitValueTextBlock,
   public iDisplayObjectEvents
{
public:
	CEditableUnitValueTextBlockImpl();
	virtual ~CEditableUnitValueTextBlockImpl();

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_EDITABLEUNITVALUETEXTBLOCK)

BEGIN_COM_MAP(CEditableUnitValueTextBlockImpl)
   COM_INTERFACE_ENTRY(iEditableUnitValueTextBlock)
   COM_INTERFACE_ENTRY(iTextBlock)
   COM_INTERFACE_ENTRY(iDisplayObject)
	COM_INTERFACE_ENTRY(iInplaceEditable)
   COM_INTERFACE_ENTRY(iDisplayObjectEvents)
END_COM_MAP()

   // iInplaceEdit Implementation
   // (not implemented by CInplaceEditDefaultImpl)
   STDMETHOD_(void,CreateEditControl)() override;
   STDMETHOD_(void,DestroyEditControl)() override;
   STDMETHOD_(BOOL,ValidateData)() override;
   STDMETHOD_(void,OnDataChanged)() override;

   // iDisplayObject overrides
   STDMETHOD_(void,SetID)(IDType id) override;
   STDMETHOD_(IDType,GetID)() override;

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) override;
   STDMETHOD_(void,GetItemData)(void** ppItemData) override;

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL) override;
   STDMETHOD_(void,GetDisplayList)(iDisplayList** list) override;

   STDMETHOD_(void,Visible)(BOOL bVisible) override;
   STDMETHOD_(BOOL,IsVisible)() override;

   // Drawing
   STDMETHOD_(void,Draw)(CDC* pDC) override;
   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite) override;
#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWell)(CDC* pDC) override;
#endif

   // Size and Hit Testing
   STDMETHOD_(void,SetGravityWellStrategy)(iGravityWellStrategy* pStrategy) override;
   STDMETHOD_(void,GetGravityWellStrategy)(iGravityWellStrategy** pStrategy) override;
   STDMETHOD_(BOOL,HitTest)(CPoint point) override;
   STDMETHOD_(CRect,GetBoundingBox)() override;
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect) override;
   STDMETHOD_(BOOL,TouchesRect)(CRect r) override;

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) override;
   STDMETHOD_(BOOL,IsSelected)() override;
   STDMETHOD_(void,SetSelectionType)(SelectionType st) override;
   STDMETHOD_(SelectionType,GetSelectionType)() override;

   // Tool Tips
//   virtual BOOL ToolTipHitTest(CPoint point) = 0;
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText) override;
   STDMETHOD_(CString,GetToolTipText)() override;
   STDMETHOD_(void,SetMaxTipWidth)(INT maxWidth) override;
   STDMETHOD_(INT,GetMaxTipWidth)() override;
   STDMETHOD_(void,SetTipDisplayTime)(INT iTime) override;
   STDMETHOD_(INT,GetTipDisplayTime)() override;

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

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink) override;
   STDMETHOD_(void,UnregisterEventSink)() override;
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink) override;

   // Drag Drop
   STDMETHOD_(void,RegisterDropSite)(iDropSite* pDropSite) override;
   STDMETHOD_(void,UnregisterDropSite)() override;
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) override;

   // Composite
   STDMETHOD_(void, SetParent)(iDisplayObject* pParent) override { Do_SetParent(pParent); }
   STDMETHOD_(void, GetParent)(iDisplayObject** ppParent) override { Do_GetParent(ppParent); }

   // iTextBlock overrides
   STDMETHOD_(void,SetPosition)(IPoint2d* pos) override;
   STDMETHOD_(void,GetPosition)(IPoint2d** pos) override;

   // Use CDC::SetTextAlign constants
   STDMETHOD_(void,SetTextAlign)(UINT nFlags) override;
   STDMETHOD_(UINT,GetTextAlign)() override;

   STDMETHOD_(void,SetAngle)(LONG angle) override;
   STDMETHOD_(LONG,GetAngle)() override;

   STDMETHOD_(void, SetPointSize)(LONG pointSize) override;
   STDMETHOD_(LONG, GetPointSize)() override;

   STDMETHOD_(void,SetText)(LPCTSTR lpszText) override;
   STDMETHOD_(CString,GetText)() override;

   STDMETHOD_(void,SetFont)(const LOGFONT& Font) override;
   STDMETHOD_(void,GetFont)(LOGFONT* pFont) override;

   STDMETHOD_(void,SetTextColor)(COLORREF color) override;
   STDMETHOD_(COLORREF,GetTextColor)() override;

   STDMETHOD_(void,SetBkColor)(COLORREF color) override;
   STDMETHOD_(COLORREF,GetBkColor)() override;

   STDMETHOD_(void,SetBkMode)(int bkMode) override;
   STDMETHOD_(int,GetBkMode)() override;

   // iEditableUnitValueTextBlock
   STDMETHOD_(void,EnableAutoUpdate)(BOOL bEnable) override;
   STDMETHOD_(BOOL,IsAutoUpdateEnabled)() override;
   STDMETHOD_(void,SetUnitSystem)(IDocUnitSystem* docUnitSystem) override;
   STDMETHOD_(void,SetDisplayUnitGroupName)(LPCTSTR strGroupName) override;
   STDMETHOD_(void,SetValue)(Float64 value) override;
   STDMETHOD_(Float64,GetValue)() override;
   STDMETHOD_(Float64,GetEditedValue)() override;
   STDMETHOD_(bool,IsStation)() override;
   STDMETHOD_(void,IsStation)(bool bIsStation) override;

   // iDisplayObjectEvents
   // Receive events from EditableTextBlock and forward to anyone listing to events on
   // this display object
   STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point) override;
   STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags) override;
   STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point) override;
   STDMETHOD_(void,OnChanged)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset) override;
   STDMETHOD_(void,OnMoved)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnCopied)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnSelect)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO) override;


protected:
   virtual CDisplayView* GetDisplayView() override;
   virtual CInplaceEdit* GetEditObject() override;

private:
   CComPtr<iEditableTextBlock> m_EditableTextBlock; // Most all of the implementation is delagated here
   CComPtr<iDisplayObjectEvents> m_EventSink;
   CComPtr<IDocUnitSystem> m_UnitSystem;
   CComBSTR m_bstrDisplayUnitGroup;
   CStatic* m_pctlUnitTag;
   Float64 m_Value; // Always in base units
   bool m_bIsStation; // are we going to edit stations instead of regular floating point numbers?
   CComPtr<IStation> m_Station;
};

#endif // !defined(AFX_EDITABLEUNITVALUETEXTBLOCK_H__FC76B7E5_E710_11D4_8B82_006097C68A9C__INCLUDED_)
