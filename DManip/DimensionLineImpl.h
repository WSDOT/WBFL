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

DECLARE_REGISTRY_RESOURCEID(IDR_DIMENSIONLINEDISPLAYOBJECT)

BEGIN_COM_MAP(CDimensionLineImpl)
   COM_INTERFACE_ENTRY(iDisplayObject)
	COM_INTERFACE_ENTRY(iDimensionLine)
   COM_INTERFACE_ENTRY(iConnector)
   COM_INTERFACE_ENTRY(iDisplayObjectEvents)
END_COM_MAP()

   // iDisplayObject Implementation
   STDMETHOD_(void,SetID)(long id) { Do_SetID(id); }
   STDMETHOD_(long,GetID)() { return Do_GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) { Do_SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) { Do_GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL);
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
   STDMETHOD_(BOOL,HitTest)(CPoint point);
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
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText) {Do_SetToolTipText(lpszToolTipText);}
   STDMETHOD_(CString,GetToolTipText)();
   STDMETHOD_(void,SetMaxTipWidth)(long maxWidth);
   STDMETHOD_(long,GetMaxTipWidth)();
   STDMETHOD_(void,SetTipDisplayTime)(long iTime);
   STDMETHOD_(long,GetTipDisplayTime)();

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

   // IDimensionLine Implementation
   STDMETHOD_(void,SetAngle)(Float64 angle);
   STDMETHOD_(Float64,GetAngle)();
   STDMETHOD_(void,SetWitnessLength)(long l);
   STDMETHOD_(long,GetWitnessLength)();
   STDMETHOD_(void,SetWitnessOffset)(long wOffset);
   STDMETHOD_(long,GetWitnessOffset)();
   STDMETHOD_(void,SetArrowHeadSize)(CSize size);
   STDMETHOD_(CSize,GetArrowHeadSize)();
   STDMETHOD_(void,SetArrowHeadStyle)(DManip::ArrowHeadStyleType style);
   STDMETHOD_(DManip::ArrowHeadStyleType,GetArrowHeadStyle)();
   STDMETHOD_(void,EnableAutoText)(BOOL bEnable);
   STDMETHOD_(BOOL,IsAutoTextEnabled)();
   STDMETHOD_(void,SetTextBlock)(iTextBlock* pTextBlock);
   STDMETHOD_(void,GetTextBlock)(iTextBlock** textBlock);

   // iDisplayObjectEvents Implementation
   STDMETHOD_(void,OnChanged)(iDisplayObject* pDO);
   STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offest);
   STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags);
   STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point);
   STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point);
   STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point);
   STDMETHOD_(void,OnMoved)(iDisplayObject* pDO);
   STDMETHOD_(void,OnCopied)(iDisplayObject* pDO);
   STDMETHOD_(void,OnSelect)(iDisplayObject* pDO);
   STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO);

private:
   CComPtr<iTextBlock> m_pTextBlock;

   Float64 m_Angle;
   BOOL   m_bAlignWithPlugs;
   long   m_LenWitness;
   long   m_DimOffset;
   long   m_WitnessOffset;
   long   m_ArrowHeight;
   long   m_ArrowWidth;

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
