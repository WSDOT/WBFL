///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// PolyLineDisplayObject.h : Declaration of the CPolyLineDisplayObjectImpl

#ifndef __POLYLINEDISPLAYOBJECT_H_
#define __POLYLINEDISPLAYOBJECT_H_
#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CPolyLineDisplayObjectImpl
class ATL_NO_VTABLE CPolyLineDisplayObjectImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPolyLineDisplayObjectImpl,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPolyLineDisplayObjectImpl, &CLSID_PolyLineDisplayObject>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPolyLineDisplayObjectImpl>,
	public iPolyLineDisplayObject
{
public:
   CPolyLineDisplayObjectImpl();

DECLARE_REGISTRY_RESOURCEID(IDR_POLYLINEDISPLAYOBJECT)

DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CPolyLineDisplayObjectImpl)
	COM_INTERFACE_ENTRY(iPolyLineDisplayObject)
   COM_INTERFACE_ENTRY(iDisplayObject)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP() 

BEGIN_CONNECTION_POINT_MAP(CPolyLineDisplayObjectImpl)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// iDisplayObject Implementation
   STDMETHOD_(void,SetID)(long id) { m_pDisplayObject->SetID(id); }
   STDMETHOD_(long,GetID)() { return m_pDisplayObject->GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) { m_pDisplayObject->SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) { m_pDisplayObject->GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL) { m_pDisplayObject->SetDisplayList(pDL); }
   STDMETHOD_(void,GetDisplayList)(iDisplayList** list) { m_pDisplayObject->GetDisplayList(list); }

   STDMETHOD_(void,Visible)(BOOL bVisible) { m_pDisplayObject->Visible(bVisible); }
   STDMETHOD_(BOOL,IsVisible)() { return m_pDisplayObject->IsVisible(); }

   // Drawing
   STDMETHOD_(void,Draw)(CDC* pDC) { m_pDisplayObject->Draw(pDC); }
   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite) { m_pDisplayObject->Highlite(pDC,bHighlite); }
#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWell)(CDC* pDC) { m_pDisplayObject->DrawGravityWell(pDC); }
#endif 

   // Size and Hit Testing
   STDMETHOD_(void,SetGravityWellStrategy)(iGravityWellStrategy* pStrategy) { m_pDisplayObject->SetGravityWellStrategy(pStrategy); }
   STDMETHOD_(void,GetGravityWellStrategy)(iGravityWellStrategy** pStrategy){ m_pDisplayObject->GetGravityWellStrategy(pStrategy); }
   STDMETHOD_(BOOL,HitTest)(CPoint point) { return m_pDisplayObject->HitTest(point); }
   STDMETHOD_(CRect,GetBoundingBox)(){ return m_pDisplayObject->GetBoundingBox(); }
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect) { m_pDisplayObject->GetBoundingBox(rect); }
   STDMETHOD_(BOOL,TouchesRect)(CRect r) { return m_pDisplayObject->TouchesRect(r); }

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) {m_pDisplayObject->Select(bSelect);}
   STDMETHOD_(BOOL,IsSelected)() {return m_pDisplayObject->IsSelected();}
   STDMETHOD_(void,SetSelectionType)(SelectionType st) { m_pDisplayObject->SetSelectionType(st); }
   STDMETHOD_(SelectionType,GetSelectionType)() { return m_pDisplayObject->GetSelectionType(); }

   // Interface Events
   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point) { return m_pDisplayObject->OnLButtonDown(nFlags,point); }
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point)   { return m_pDisplayObject->OnLButtonUp(nFlags,point); }
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point) { return m_pDisplayObject->OnLButtonDblClk(nFlags,point); }
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point) { return m_pDisplayObject->OnRButtonDown(nFlags,point); }
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point) { return m_pDisplayObject->OnRButtonUp(nFlags,point); }
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point) { return m_pDisplayObject->OnRButtonDblClk(nFlags,point); }
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags,CPoint point) { return m_pDisplayObject->OnMouseMove(nFlags,point); }
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags,short zDelta,CPoint point) { return m_pDisplayObject->OnMouseWheel(nFlags,zDelta,point); }
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) { return m_pDisplayObject->OnKeyDown(nChar, nRepCnt, nFlags); }
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point) { return m_pDisplayObject->OnContextMenu(pWnd,point); }

   // Tool Tips
   STDMETHOD_(void,SetToolTipText)(LPCSTR lpszToolTipText) {m_pDisplayObject->SetToolTipText(lpszToolTipText);}
   STDMETHOD_(CString,GetToolTipText)() { return m_pDisplayObject->GetToolTipText(); }
   STDMETHOD_(void,SetMaxTipWidth)(long maxWidth) { m_pDisplayObject->SetMaxTipWidth(maxWidth); }
   STDMETHOD_(long,GetMaxTipWidth)() { return m_pDisplayObject->GetMaxTipWidth(); }

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink)
   { m_pDisplayObject->RegisterEventSink(pEventSink); }
   STDMETHOD_(void,UnregisterEventSink)()
   { m_pDisplayObject->UnregisterEventSink(); }
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink)
   { m_pDisplayObject->GetEventSink(pEventSink); }

   // Drag Drop
   STDMETHOD_(void,SetDropSite)(iDropSite* pDropSite) { m_pDisplayObject->SetDropSite(pDropSite); }
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) { m_pDisplayObject->GetDropSite(dropSite); }

// IPolyLineDisplayObject
public:
   STDMETHOD_(void,Commit)();
   STDMETHOD_(long,get_NumberOfPoints)();
   STDMETHOD_(void,AddPoint)(IPoint2d* point);
   STDMETHOD_(HRESULT,InsertPoint)(long idx, IPoint2d* point);
   STDMETHOD_(HRESULT,GetPoint)(long idx, IPoint2d* *point);
   STDMETHOD_(HRESULT,RemovePoint)(long idx);
   STDMETHOD_(void,ClearPoints)();
   STDMETHOD_(void,put_Color)(COLORREF color);
   STDMETHOD_(void,get_Color)(COLORREF* color);
   STDMETHOD_(void,put_Width)(long width);
   STDMETHOD_(void,get_Width)(long* width);
   STDMETHOD_(void,put_PointType)(PolyLinePointType ptType);
   STDMETHOD_(void,get_PointType)(PolyLinePointType* ptType);

   HRESULT FinalConstruct();
   void FinalRelease();

   CComPtr<iCompositeDisplayObject> m_pDisplayObject;

   COLORREF m_Color;
   long     m_Width;
   PolyLinePointType m_PtType;

   typedef CAdapt<CComPtr<IPoint2d> > ContainerItem;
   typedef std::vector<ContainerItem> ContainerType;
   typedef ContainerType::iterator    ContainerIterator;
   ContainerType m_Container;

private:
   long                                 m_NumDos; // number of display objects
   long                                 m_CurrId;

private:
   HRESULT RebuildDisplayObjects();
   void AddMyDisplayObject(iDisplayObject* pdo);
   void ClearDisplayObjects();
   void BuildLine(iCompositeDisplayObject* pCdo, IPoint2d* fromPoint,IPoint2d* toPoint);
};

#endif //__PolyLineDISPLAYOBJECT_H_
