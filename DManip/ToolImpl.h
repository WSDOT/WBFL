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

#ifndef INCLUDED_TOOLIMPL_H_
#define INCLUDED_TOOLIMPL_H_
#pragma once

#include "resource.h"

class ATL_NO_VTABLE CToolImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CToolImpl, &CLSID_Tool>,
   public iTool,
   public iToolIcon,
   public iDraggable
{
public:
   CToolImpl();
   virtual ~CToolImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_TOOL)

BEGIN_COM_MAP(CToolImpl)
   COM_INTERFACE_ENTRY(iTool)
   COM_INTERFACE_ENTRY(iToolIcon)
	COM_INTERFACE_ENTRY(iDraggable)
END_COM_MAP()
   
// iTool Implementation
   STDMETHOD_(void,SetID)(UINT id);
   STDMETHOD_(UINT,GetID)();
   STDMETHOD_(void,SetToolTipText)(LPCTSTR lpszText);
   STDMETHOD_(CString,GetToolTipText)();

   // iToolIcon interace
   STDMETHOD_(HRESULT,SetIcon)(HINSTANCE hInstance, WORD IconResId);

   // iDraggable Implementation
   STDMETHOD_(void,SetDragData)(iDragData* dd);
   STDMETHOD_(void,GetDragData)(iDragData** dd);

   STDMETHOD_(UINT,Format)();
   STDMETHOD_(void,PrepareDrag)(iDragDataSink* pSink);
   STDMETHOD_(void,OnDrop)(iDragDataSource* pSource);
   STDMETHOD_(void,OnDragMoved)(ISize2d* offset);
   STDMETHOD_(void,OnMoved)();
   STDMETHOD_(void,OnCopied)();

   STDMETHOD_(void,DrawDragImage)(CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);

   static CLIPFORMAT ms_cfFormat;

private:
   UINT m_ID;
   CString m_strToolTipText;
   CComPtr<iDragData> m_pDragData;

   HINSTANCE m_hIconInstance;
   WORD      m_IconResId;
   HICON     m_Icon;
   CDC       m_MemDC; // memory dc and bitmap for animation
   CBitmap   m_Bitmap;
   bool      m_First;
   CPoint    m_OldPoint;
   bool      m_bDrawIcon;

   void LoadIcon();
};

#endif // INCLUDED_TOOLIMPL_H_