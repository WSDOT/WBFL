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
   STDMETHOD_(void,CreateEditControl)();
   STDMETHOD_(void,DestroyEditControl)();
   STDMETHOD_(BOOL,ValidateData)();
   STDMETHOD_(void,OnDataChanged)();

   // iDisplayObject overrides
   STDMETHOD_(void,SetID)(IDType id);
   STDMETHOD_(IDType,GetID)();

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete);
   STDMETHOD_(void,GetItemData)(void** ppItemData);

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL);
   STDMETHOD_(void,GetDisplayList)(iDisplayList** list);

   STDMETHOD_(void,Visible)(BOOL bVisible);
   STDMETHOD_(BOOL,IsVisible)();

   // Drawing
   STDMETHOD_(void,Draw)(CDC* pDC);
   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite);
#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWell)(CDC* pDC);
#endif

   // Size and Hit Testing
   STDMETHOD_(void,SetGravityWellStrategy)(iGravityWellStrategy* pStrategy);
   STDMETHOD_(void,GetGravityWellStrategy)(iGravityWellStrategy** pStrategy);
   STDMETHOD_(BOOL,HitTest)(CPoint point);
   STDMETHOD_(CRect,GetBoundingBox)();
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect);
   STDMETHOD_(BOOL,TouchesRect)(CRect r);

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect);
   STDMETHOD_(BOOL,IsSelected)();
   STDMETHOD_(void,SetSelectionType)(SelectionType st);
   STDMETHOD_(SelectionType,GetSelectionType)();

   // Tool Tips
//   virtual BOOL ToolTipHitTest(CPoint point) = 0;
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText);
   STDMETHOD_(CString,GetToolTipText)();
   STDMETHOD_(void,SetMaxTipWidth)(INT maxWidth);
   STDMETHOD_(INT,GetMaxTipWidth)();
   STDMETHOD_(void,SetTipDisplayTime)(INT iTime);
   STDMETHOD_(INT,GetTipDisplayTime)();

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

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink);
   STDMETHOD_(void,UnregisterEventSink)();
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink);

   // Drag Drop
   STDMETHOD_(void,RegisterDropSite)(iDropSite* pDropSite);
   STDMETHOD_(void,UnregisterDropSite)();
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite);

   // iTextBlock overrides
   STDMETHOD_(void,SetPosition)(IPoint2d* pos);
   STDMETHOD_(void,GetPosition)(IPoint2d** pos);

   // Use CDC::SetTextAlign constants
   STDMETHOD_(void,SetTextAlign)(UINT nFlags);
   STDMETHOD_(UINT,GetTextAlign)();

   STDMETHOD_(void,SetAngle)(LONG angle);
   STDMETHOD_(LONG,GetAngle)();

   STDMETHOD_(void,SetText)(LPCTSTR lpszText);
   STDMETHOD_(CString,GetText)();

   STDMETHOD_(void,SetFont)(const LOGFONT& Font);
   STDMETHOD_(void,GetFont)(LOGFONT* pFont);

   STDMETHOD_(void,SetTextColor)(COLORREF color);
   STDMETHOD_(COLORREF,GetTextColor)();

   STDMETHOD_(void,SetBkColor)(COLORREF color);
   STDMETHOD_(COLORREF,GetBkColor)();

   STDMETHOD_(void,SetBkMode)(int bkMode);
   STDMETHOD_(int,GetBkMode)();

   // iEditableUnitValueTextBlock
   STDMETHOD_(void,EnableAutoUpdate)(BOOL bEnable);
   STDMETHOD_(BOOL,IsAutoUpdateEnabled)();
   STDMETHOD_(void,SetUnitSystem)(IDocUnitSystem* docUnitSystem);
   STDMETHOD_(void,SetDisplayUnitGroupName)(LPCTSTR strGroupName);
   STDMETHOD_(void,SetValue)(Float64 value);
   STDMETHOD_(Float64,GetValue)();
   STDMETHOD_(Float64,GetEditedValue)();
   STDMETHOD_(bool,IsStation)();
   STDMETHOD_(void,IsStation)(bool bIsStation);

   // iDisplayObjectEvents
   // Receive events from EditableTextBlock and forward to anyone listing to events on
   // this display object
   STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point);
   STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags);
   STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point);
   STDMETHOD_(void,OnChanged)(iDisplayObject* pDO);
   STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset);
   STDMETHOD_(void,OnMoved)(iDisplayObject* pDO);
   STDMETHOD_(void,OnCopied)(iDisplayObject* pDO);
   STDMETHOD_(void,OnSelect)(iDisplayObject* pDO);
   STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO);


protected:
   virtual CDisplayView* GetDisplayView();
   virtual CInplaceEdit* GetEditObject();

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
