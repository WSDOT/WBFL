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

// DimensionLineImpl.h: interface for the CDimensionLineImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMENSIONLINEIMPL_H__80AD65CB_E7E0_11D4_8B84_006097C68A9C__INCLUDED_)
#define AFX_DIMENSIONLINEIMPL_H__80AD65CB_E7E0_11D4_8B84_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include <DManip\DisplayObjectDefaultImpl.h>
#include "ConnectorImpl.h"

class ATL_NO_VTABLE CDimensionLineImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDimensionLineImpl, &CLSID_DimensionLineDisplayObject>,
   public CDisplayObjectDefaultImpl,
   public CConnectorImpl,
   public iDisplayObjectEvents,
   public iDimensionLine
{
public:
	CDimensionLineImpl();
	virtual ~CDimensionLineImpl();
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
      if ( m_dwRef == 1 && m_TextBlock )
      {
         InternalAddRef();
         m_TextBlock->UnregisterEventSink();
      }
      ULONG ulReturn = CComObjectRootEx<CComSingleThreadModel>::InternalRelease();
      return ulReturn;
   }

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_DIMENSIONLINEDISPLAYOBJECT)

BEGIN_COM_MAP(CDimensionLineImpl)
   COM_INTERFACE_ENTRY(iDisplayObject)
	COM_INTERFACE_ENTRY(iDimensionLine)
   COM_INTERFACE_ENTRY(iConnector)
   COM_INTERFACE_ENTRY(iDisplayObjectEvents)
END_COM_MAP()

   // iDisplayObject Implementation
   STDMETHOD_(void,SetID)(IDType id) override { Do_SetID(id); }
   STDMETHOD_(IDType,GetID)() override { return Do_GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) override { Do_SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) override { Do_GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL) override;
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
   STDMETHOD_(BOOL,HitTest)(CPoint point) override;
   STDMETHOD_(CRect,GetBoundingBox)() override { return Do_GetBoundingBox(); }
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
   STDMETHOD_(void,SetMaxTipWidth)(INT maxWidth) override;
   STDMETHOD_(INT,GetMaxTipWidth)() override;
   STDMETHOD_(void,SetTipDisplayTime)(INT iTime) override;
   STDMETHOD_(INT,GetTipDisplayTime)() override;

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

   // IDimensionLine Implementation
   STDMETHOD_(void,SetAngle)(Float64 angle) override;
   STDMETHOD_(Float64,GetAngle)() override;
   STDMETHOD_(void,SetWitnessLength)(LONG l) override;
   STDMETHOD_(LONG,GetWitnessLength)() override;
   STDMETHOD_(void,SetHiddenWitnessLength)(LONG l) override;
   STDMETHOD_(LONG,GetHiddenWitnessLength)() override;
   STDMETHOD_(void,SetWitnessOffset)(LONG wOffset) override;
   STDMETHOD_(LONG,GetWitnessOffset)() override;
   STDMETHOD_(void,SetArrowHeadSize)(CSize size) override;
   STDMETHOD_(CSize,GetArrowHeadSize)() override;
   STDMETHOD_(void,SetArrowHeadStyle)(DManip::ArrowHeadStyleType style) override;
   STDMETHOD_(DManip::ArrowHeadStyleType,GetArrowHeadStyle)() override;
   STDMETHOD_(void,EnableAutoText)(BOOL bEnable) override;
   STDMETHOD_(BOOL,IsAutoTextEnabled)() override;
   STDMETHOD_(void,SetTextBlock)(iTextBlock* pTextBlock) override;
   STDMETHOD_(void,GetTextBlock)(iTextBlock** textBlock) override;

   // iDisplayObjectEvents Implementation
   STDMETHOD_(void,OnChanged)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offest) override;
   STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags) override;
   STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point) override;
   STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point) override;
   STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point) override;
   STDMETHOD_(void,OnMoved)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnCopied)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnSelect)(iDisplayObject* pDO) override;
   STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO) override;

private:
   CComPtr<iTextBlock> m_TextBlock;

   Float64 m_Angle;
   BOOL   m_bAlignWithPlugs;
   LONG   m_HiddenWitnessLength;
   LONG   m_LenWitness;
   LONG   m_DimOffset;
   LONG   m_WitnessOffset;
   int   m_ArrowHeight;
   int   m_ArrowWidth;

   struct ARROWHEAD
   {
      CPoint tip,left,right;
   };

   ARROWHEAD m_StartArrow;
   ARROWHEAD m_EndArrow;

   DManip::ArrowHeadStyleType m_Style;

   BOOL m_bAutoText; // If TRUE, the text is equal to the distance between plugs

   // Working points
   CPoint m_ptA, m_ptB, m_ptC, m_ptD, m_ptE, m_ptF, m_ptZ, m_ptStart, m_ptEnd;
   virtual void UpdateWorkPoints();
   void UpdateArrowHeads(Float64 stx, Float64 sty);
   void UpdateTextBlock();
   void IncludePointInRect(CPoint p,CRect* pRect);

   void GetStartPoint(IPoint2d* *point);
   void GetEndPoint(IPoint2d* *point);
};

#endif // !defined(AFX_DIMENSIONLINEIMPL_H__80AD65CB_E7E0_11D4_8B84_006097C68A9C__INCLUDED_)
