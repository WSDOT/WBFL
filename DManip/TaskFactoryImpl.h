///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TaskFactoryImpl.h: interface for the CTaskFactoryImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKFACTORYIMPL_H__FC76B7E4_E710_11D4_8B82_006097C68A9C__INCLUDED_)
#define AFX_TASKFACTORYIMPL_H__FC76B7E4_E710_11D4_8B82_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CTaskFactoryImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTaskFactoryImpl, &CLSID_TaskFactory>,
   public iTaskFactory
{
public:
	CTaskFactoryImpl();
	virtual ~CTaskFactoryImpl();


DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_TASKFACTORY)

BEGIN_COM_MAP(CTaskFactoryImpl)
	COM_INTERFACE_ENTRY(iTaskFactory)
END_COM_MAP()

   // iTaskFactory Implementation
public:
   STDMETHOD_(void,CreateInplaceEditTask)(CDisplayView* pView,iInplaceEditable* pEditable,iTask** task);
   STDMETHOD_(void,CreateRectSelectTask)(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task);
   STDMETHOD_(void,CreateLocalDragDropTask)(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task);
   STDMETHOD_(void,CreateForeignDragDropTask)(iDisplayMgr* pDispMgr,const CPoint& startPoint,iTask** task);
   STDMETHOD_(void,CreateCenterOnPointTask)(CDisplayView* pView,iTask** task);
   STDMETHOD_(void,CreateZoomTask)(CDisplayView* pView,HCURSOR hCursor,COLORREF color,iTask** task);
};

#endif // !defined(AFX_TASKFACTORYIMPL_H__FC76B7E4_E710_11D4_8B82_006097C68A9C__INCLUDED_)
