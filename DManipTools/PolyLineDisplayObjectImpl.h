///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2019  Washington State Department of Transportation
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

   HRESULT FinalConstruct();
   void FinalRelease();

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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// iDisplayObject Implementation
   STDMETHOD_(void,SetID)(IDType id) override { m_pDisplayObject->SetID(id); }
   STDMETHOD_(IDType,GetID)() override { return m_pDisplayObject->GetID(); }

   STDMETHOD_(void,SetItemData)(void* pItemData,bool bDelete) override { m_pDisplayObject->SetItemData(pItemData,bDelete); }
   STDMETHOD_(void,GetItemData)(void** ppItemData) override { m_pDisplayObject->GetItemData(ppItemData); }

   STDMETHOD_(void,SetDisplayList)(iDisplayList * pDL) override { m_pDisplayObject->SetDisplayList(pDL); }
   STDMETHOD_(void,GetDisplayList)(iDisplayList** list)  override { m_pDisplayObject->GetDisplayList(list); }

   STDMETHOD_(void,Visible)(BOOL bVisible) override { m_pDisplayObject->Visible(bVisible); }
   STDMETHOD_(BOOL,IsVisible)()  override { return m_pDisplayObject->IsVisible(); }

   // Drawing
   STDMETHOD_(void,Draw)(CDC* pDC) override { m_pDisplayObject->Draw(pDC); }
   STDMETHOD_(void,Highlite)(CDC* pDC,BOOL bHighlite) override { m_pDisplayObject->Highlite(pDC,bHighlite); }
#if defined(_DEBUG)
   STDMETHOD_(void,DrawGravityWell)(CDC* pDC) override { m_pDisplayObject->DrawGravityWell(pDC); }
#endif 

   // Size and Hit Testing
   STDMETHOD_(void,SetGravityWellStrategy)(iGravityWellStrategy* pStrategy) override { m_pDisplayObject->SetGravityWellStrategy(pStrategy); }
   STDMETHOD_(void,GetGravityWellStrategy)(iGravityWellStrategy** pStrategy) override { m_pDisplayObject->GetGravityWellStrategy(pStrategy); }
   STDMETHOD_(BOOL,HitTest)(CPoint point) override { return m_pDisplayObject->HitTest(point); }
   STDMETHOD_(CRect,GetBoundingBox)() override { return m_pDisplayObject->GetBoundingBox(); }
   STDMETHOD_(void,GetBoundingBox)(IRect2d** rect) override { m_pDisplayObject->GetBoundingBox(rect); }
   STDMETHOD_(BOOL,TouchesRect)(CRect r) override { return m_pDisplayObject->TouchesRect(r); }

   // Selection
   STDMETHOD_(void,Select)(BOOL bSelect) override {m_pDisplayObject->Select(bSelect);}
   STDMETHOD_(BOOL,IsSelected)() override {return m_pDisplayObject->IsSelected();}
   STDMETHOD_(void,SetSelectionType)(SelectionType st)  override { m_pDisplayObject->SetSelectionType(st); }
   STDMETHOD_(SelectionType,GetSelectionType)() override { return m_pDisplayObject->GetSelectionType(); }

   // Interface Events
   STDMETHOD_(bool,OnLButtonDown)(UINT nFlags,CPoint point) override { return m_pDisplayObject->OnLButtonDown(nFlags,point); }
   STDMETHOD_(bool,OnLButtonUp)(UINT nFlags,CPoint point)  override { return m_pDisplayObject->OnLButtonUp(nFlags,point); }
   STDMETHOD_(bool,OnLButtonDblClk)(UINT nFlags,CPoint point) override { return m_pDisplayObject->OnLButtonDblClk(nFlags,point); }
   STDMETHOD_(bool,OnRButtonDown)(UINT nFlags,CPoint point) override { return m_pDisplayObject->OnRButtonDown(nFlags,point); }
   STDMETHOD_(bool,OnRButtonUp)(UINT nFlags,CPoint point)  override { return m_pDisplayObject->OnRButtonUp(nFlags,point); }
   STDMETHOD_(bool,OnRButtonDblClk)(UINT nFlags,CPoint point)  override { return m_pDisplayObject->OnRButtonDblClk(nFlags,point); }
   STDMETHOD_(bool,OnMouseMove)(UINT nFlags,CPoint point) override { return m_pDisplayObject->OnMouseMove(nFlags,point); }
   STDMETHOD_(bool,OnMouseWheel)(UINT nFlags,short zDelta,CPoint point) override { return m_pDisplayObject->OnMouseWheel(nFlags,zDelta,point); }
   STDMETHOD_(bool,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) override { return m_pDisplayObject->OnKeyDown(nChar, nRepCnt, nFlags); }
   STDMETHOD_(bool,OnContextMenu)(CWnd* pWnd,CPoint point) override { return m_pDisplayObject->OnContextMenu(pWnd,point); }

   // Tool Tips
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszToolTipText) override {m_pDisplayObject->SetToolTipText(lpszToolTipText);}
   STDMETHOD_(CString,GetToolTipText)()  override { return m_pDisplayObject->GetToolTipText(); }
   STDMETHOD_(void,SetMaxTipWidth)(INT maxWidth) override { m_pDisplayObject->SetMaxTipWidth(maxWidth); }
   STDMETHOD_(INT,GetMaxTipWidth)()  override { return m_pDisplayObject->GetMaxTipWidth(); }
   STDMETHOD_(void,SetTipDisplayTime)(INT iTime)  override { m_pDisplayObject->SetTipDisplayTime(iTime); }
   STDMETHOD_(INT,GetTipDisplayTime)()  override { return m_pDisplayObject->GetTipDisplayTime(); }

   // Event Sink
   STDMETHOD_(void,RegisterEventSink)(iDisplayObjectEvents* pEventSink) override
   { m_pDisplayObject->RegisterEventSink(pEventSink); }
   STDMETHOD_(void,UnregisterEventSink)() override
   { m_pDisplayObject->UnregisterEventSink(); }
   STDMETHOD_(void,GetEventSink)(iDisplayObjectEvents** pEventSink) override
   { m_pDisplayObject->GetEventSink(pEventSink); }

   // Drag Drop
   STDMETHOD_(void,RegisterDropSite)(iDropSite* pDropSite) override { m_pDisplayObject->RegisterDropSite(pDropSite); }
   STDMETHOD_(void,UnregisterDropSite)() override { m_pDisplayObject->UnregisterDropSite(); }
   STDMETHOD_(void,GetDropSite)(iDropSite** dropSite) override { m_pDisplayObject->GetDropSite(dropSite); }

   // Composite
   STDMETHOD_(void, SetParent)(iDisplayObject* pParent) override { m_pDisplayObject->SetParent(pParent); }
   STDMETHOD_(void, GetParent)(iDisplayObject** ppParent) override { m_pDisplayObject->GetParent(ppParent); }

// IPolyLineDisplayObject
public:
   STDMETHOD_(void,Commit)() override;
   STDMETHOD_(CollectionIndexType,get_NumberOfPoints)() override;
   STDMETHOD_(void,AddPoints)(IPoint2dCollection* points) override;
   STDMETHOD_(void,AddPoint)(IPoint2d* point) override;
   STDMETHOD_(HRESULT,InsertPoint)(CollectionIndexType idx, IPoint2d* point) override;
   STDMETHOD_(HRESULT,GetPoint)(CollectionIndexType idx, IPoint2d* *point) override;
   STDMETHOD_(HRESULT,RemovePoint)(CollectionIndexType idx) override;
   STDMETHOD_(void,ClearPoints)() override;
   STDMETHOD_(void,put_Color)(COLORREF color) override;
   STDMETHOD_(void,get_Color)(COLORREF* color) override;
   STDMETHOD_(void,put_Width)(long width) override;
   STDMETHOD_(void,get_Width)(long* width) override;
   STDMETHOD_(void,put_PointType)(PolyLinePointType ptType) override;
   STDMETHOD_(void,get_PointType)(PolyLinePointType* ptType) override;

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
   void BuildLine(IPoint2d* fromPoint,IPoint2d* toPoint);
};

#endif //__PolyLineDISPLAYOBJECT_H_
