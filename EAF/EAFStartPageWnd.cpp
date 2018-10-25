///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// EAFStartPageWnd.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFStartPageWnd.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFStartPageWnd

IMPLEMENT_DYNCREATE(CEAFStartPageWnd, CMDIChildWnd)

CEAFStartPageWnd::CEAFStartPageWnd()
{
}

CEAFStartPageWnd::~CEAFStartPageWnd()
{
}
#ifdef _DEBUG
void CEAFStartPageWnd::AssertValid() const
{
   // Make sure the module state is that for the CWinApp class
   // before diving down into MFC (if the module state isn't
   // correct, all sorts of asserts will fire)   
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CMDIChildWnd::AssertValid();
}

void CEAFStartPageWnd::Dump(CDumpContext& dc) const
{
   CMDIChildWnd::Dump(dc);
}
#endif


BEGIN_MESSAGE_MAP(CEAFStartPageWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CEAFStartPageWnd)
	//}}AFX_MSG_MAP
   ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFStartPageWnd message handlers

BOOL CEAFStartPageWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	return CMDIChildWnd::PreCreateWindow(cs);
}

BOOL CEAFStartPageWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	return CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}
