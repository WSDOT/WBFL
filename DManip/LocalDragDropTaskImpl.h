///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// LocalDragDropTaskImpl.h: interface for the CLocalDragDropTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_LOCALDRAGDROPTASKIMPL_H_
#define INCLUDED_LOCALDRAGDROPTASKIMPL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "LocalDragDropFSM.h"

class ATL_NO_VTABLE CLocalDragDropTaskImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLocalDragDropTaskImpl, &CLSID_LocalDragDropTask>,
   public CLocalDragDropFSM,
   public iTask
{
public:
	CLocalDragDropTaskImpl();
	virtual ~CLocalDragDropTaskImpl();
   
   void Init(iDisplayMgr* pDM,const CPoint& startPoint);

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_LOCALDRAGDROPTASK)

BEGIN_COM_MAP(CLocalDragDropTaskImpl)
   COM_INTERFACE_ENTRY(iTask)
	COM_INTERFACE_ENTRY(iLocalDragDropTask)
END_COM_MAP()

   // CLocalDragDropTask methods (from CLocalDragDropFSM)
	STDMETHOD_(void,FSMError)(LPCTSTR t,LPCTSTR s);
	STDMETHOD_(void,InitTask)();
   STDMETHOD_(void,CreateDragObjects)();
   STDMETHOD_(void,DestroyDragObjects)();
   STDMETHOD_(DROPEFFECT,DetermineDropEffect)();
   STDMETHOD_(void,TrackDragObjects)();
   STDMETHOD_(void,NotifyDropTarget)();

   // iTask methods
   STDMETHOD_(void,Start)();
	STDMETHOD_(void,OnLButtonUp)(UINT nFlags,const CPoint& point);
   STDMETHOD_(void,OnRButtonUp)(UINT nFlags,const CPoint& point);
   STDMETHOD_(void,OnMouseMove)(UINT nFlags, const CPoint& point);
   STDMETHOD_(void,OnMouseWheel)(UINT nFlags, short zDelta, const CPoint& point);
   STDMETHOD_(void,OnLButtonDown)(UINT nFlags, const CPoint& point);
   STDMETHOD_(void,OnRButtonDown)(UINT nFlags, const CPoint& point);
   STDMETHOD_(void,OnLButtonDblClk)(UINT nFlags,const CPoint& point);
   STDMETHOD_(void,OnRButtonDblClk)(UINT nFlags,const CPoint& point);
   STDMETHOD_(void,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags);
   STDMETHOD_(void,OnContextMenu)(CWnd* pWnd,const CPoint& point);
   STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
   STDMETHOD_(void,OnDragLeave)();
   STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point);
   STDMETHOD_(DROPEFFECT,OnDragScroll)(DWORD dwKeyState,CPoint point);
   STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point);
   STDMETHOD_(DROPEFFECT,OnDropEx)(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point);

private:
   CComPtr<iDisplayMgr> m_pDispMgr;
   CComPtr<iCoordinateMap> m_pMap;
   CPoint m_StartPoint;
   CPoint m_DragStart; // This is the world point where drag and drop started
   CPoint m_LastPoint; // The is the last drag point
   CPoint m_DragPoint; // This is the world point corresponding to the current mouse position

   CComPtr<IPoint2d>  m_PointCache; // create once, use many

   COleDataObject* m_pDataObject;
   DWORD m_dwKeyState;
   DROPEFFECT m_dropEffect;
   DROPEFFECT m_dropList;
};

#endif // INCLUDED_LOCALDRAGDROPTASKIMPL_H_
