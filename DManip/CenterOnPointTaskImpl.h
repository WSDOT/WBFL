///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// CenterOnPointTaskImpl.h: interface for the CCenterOnPointTaskImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTERONPOINTTASKIMPL_H__5D499BF8_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
#define AFX_CENTERONPOINTTASKIMPL_H__5D499BF8_CF77_11D4_8B66_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "CenterOnPointFSM.h"

class ATL_NO_VTABLE CCenterOnPointTaskImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCenterOnPointTaskImpl, &CLSID_CenterOnPointTask>,
   public CCenterOnPointFSM,
   public iTask
{
public:
	CCenterOnPointTaskImpl();
	virtual ~CCenterOnPointTaskImpl();

   void Init(CDisplayView* pView);

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_CENTERONPOINTTASK)

BEGIN_COM_MAP(CCenterOnPointTaskImpl)
   COM_INTERFACE_ENTRY(iTask)
	COM_INTERFACE_ENTRY(iCenterOnPointTask)
END_COM_MAP()

   // CCenterOnPointTask methods (from CCenterOnPointFSM)
	STDMETHOD_(void,FSMError)(LPCTSTR t,LPCTSTR s) override;
	STDMETHOD_(void,CenterOnPoint)() override;
   STDMETHOD_(void,Cancel)() override;
	STDMETHOD_(void,InitTask)() override;

   // CTask methods
   STDMETHOD_(void,Start)() override;

   STDMETHOD_(void,OnLButtonDown)(UINT nFlags, const CPoint& point) override;
	STDMETHOD_(void,OnLButtonUp)(UINT nFlags,const CPoint& point) override;
   STDMETHOD_(void,OnLButtonDblClk)(UINT nFlags,const CPoint& point) override;

   STDMETHOD_(void,OnRButtonDown)(UINT nFlags, const CPoint& point) override;
	STDMETHOD_(void,OnRButtonUp)(UINT nFlags,const CPoint& point) override;
   STDMETHOD_(void,OnRButtonDblClk)(UINT nFlags,const CPoint& point) override;

   STDMETHOD_(void,OnMouseMove)(UINT nFlags, const CPoint& point) override;
   STDMETHOD_(void,OnMouseWheel)(UINT nFlags, short zDelta, const CPoint& point) override;

   STDMETHOD_(void,OnKeyDown)(UINT nChar, UINT nRepCnt, UINT nFlags) override;
   STDMETHOD_(void,OnContextMenu)(CWnd* pWnd,const CPoint& point) override;

   STDMETHOD_(DROPEFFECT,OnDragEnter)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
   STDMETHOD_(void,OnDragLeave)() override;
   STDMETHOD_(DROPEFFECT,OnDragOver)(COleDataObject* pDataObject,DWORD dwKeyState,CPoint point) override;
   STDMETHOD_(DROPEFFECT,OnDragScroll)(DWORD dwKeyState,CPoint point) override;
   STDMETHOD_(BOOL,OnDrop)(COleDataObject* pDataObject,DROPEFFECT dropEffect,CPoint point) override;
   STDMETHOD_(DROPEFFECT,OnDropEx)(COleDataObject* pDataObject,DROPEFFECT dropEffect,DROPEFFECT dropList,CPoint point) override;

private:
   CDisplayView* m_pView;
   CPoint m_Point;
   HCURSOR m_OldCursor;
};

#endif // !defined(AFX_CENTERONPOINTTASKIMPL_H__5D499BF8_CF77_11D4_8B66_006097C68A9C__INCLUDED_)
