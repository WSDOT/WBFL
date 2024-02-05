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

// ForeignDragDropTaskImpl.h: interface for the CForeignDragDropTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_FOREIGNDRAGDROPTASKIMPL_H_
#define INCLUDED_FOREIGNDRAGDROPTASKIMPL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "ForeignDragDropFSM.h"

class ATL_NO_VTABLE CForeignDragDropTaskImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CForeignDragDropTaskImpl, &CLSID_ForeignDragDropTask>,
   public CForeignDragDropFSM,
   public iTask
{
public:
	CForeignDragDropTaskImpl();
	virtual ~CForeignDragDropTaskImpl();

	void Init(iDisplayMgr* pDM,const CPoint& startPoint);

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_FOREIGNDRAGDROPTASK)

BEGIN_COM_MAP(CForeignDragDropTaskImpl)
   COM_INTERFACE_ENTRY(iTask)
	COM_INTERFACE_ENTRY(iForeignDragDropTask)
END_COM_MAP()

   // CForeignDragDropTask methods (from CForeignDragDropFSM)
	STDMETHOD_(void,FSMError)(LPCTSTR t,LPCTSTR s) override;
	STDMETHOD_(void,InitTask)() override;
   STDMETHOD_(void,CreateDragObjects)() override;
   STDMETHOD_(void,DestroyDragObjects)() override;
   STDMETHOD_(DROPEFFECT,DetermineDropEffect)() override;
   STDMETHOD_(void,TrackDragObjects)() override;
   STDMETHOD_(void,NotifyDropTarget)() override;

   // iTask methods
   STDMETHOD_(void,Start)() override;
	STDMETHOD_(void,OnLButtonUp)(UINT nFlags,const CPoint& point) override;
   STDMETHOD_(void,OnRButtonUp)(UINT nFlags,const CPoint& point) override;
   STDMETHOD_(void,OnMouseMove)(UINT nFlags, const CPoint& point) override;
   STDMETHOD_(void,OnMouseWheel)(UINT nFlags, short zDelta, const CPoint& point) override;
   STDMETHOD_(void,OnLButtonDown)(UINT nFlags, const CPoint& point) override;
   STDMETHOD_(void,OnRButtonDown)(UINT nFlags, const CPoint& point) override;
   STDMETHOD_(void,OnLButtonDblClk)(UINT nFlags,const CPoint& point) override;
   STDMETHOD_(void,OnRButtonDblClk)(UINT nFlags,const CPoint& point) override;
   STDMETHOD_(void,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) override;
   STDMETHOD_(void,OnContextMenu)(CWnd* pWnd,const CPoint& point) override;
   STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
   STDMETHOD_(void,OnDragLeave)() override;
   STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
   STDMETHOD_(DROPEFFECT,OnDragScroll)(DWORD dwKeyState,CPoint point) override;
   STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) override;
   STDMETHOD_(DROPEFFECT,OnDropEx)(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) override;

private:
   CComPtr<iDisplayMgr> m_pDispMgr;
   CComPtr<iCoordinateMap> m_pMap;
   CPoint m_DragStart; // This is the world point where drag and drop started
   CPoint m_LastPoint; // The is the last drag point
   CPoint m_DragPoint; // This is the world point corresponding to the current mouse position

   CComPtr<IPoint2d>  m_PointCache; // create once, use many

   COleDataObject* m_pDataObject;
   DWORD m_dwKeyState;
   DROPEFFECT m_dropEffect;
   DROPEFFECT m_dropList;
};

#endif // INCLUDED_FOREIGNDRAGDROPTASKIMPL_H_
