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

// EAFChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFChildFrame.h>
#include <EAF\EAFApp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFChildFrame

IMPLEMENT_DYNCREATE(CEAFChildFrame, CMDIChildWnd)

CEAFChildFrame::CEAFChildFrame()
{
   m_bIsSnapped = false;
   m_wndPlacement.length = sizeof(WINDOWPLACEMENT);
}

CEAFChildFrame::~CEAFChildFrame()
{
}
#ifdef _DEBUG
void CEAFChildFrame::AssertValid() const
{
   // Make sure the module state is that for the CWinApp class
   // before diving down into MFC (if the module state isn't
   // correct, all sorts of asserts will fire)   
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CMDIChildWnd::AssertValid();
}

void CEAFChildFrame::Dump(CDumpContext& dc) const
{
   CMDIChildWnd::Dump(dc);
}
#endif


BEGIN_MESSAGE_MAP(CEAFChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CEAFChildFrame)
	//}}AFX_MSG_MAP
   ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFChildFrame message handlers
void CEAFChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if (bAddToTitle && (GetStyle() & FWS_ADDTOTITLE) == 0)
   {
      // By turning off the default MFC-defined FWS_ADDTOTITLE style,
      // the framework will use first string in the document template
      // STRINGTABLE resource instead of the document name. We want
      // to append a view count to the end of the window title.  
		TCHAR szText[256+_MAX_PATH];
      CString window_text;
      CString window_title;
      GetWindowText(window_text);

      // Look for the last :
      // The text to the left of the last : is the window title
      int idx = window_text.ReverseFind(':');
      if (idx != -1) // -1 meams : was not found
         window_title = window_text.Left(idx);
      else
         window_title = window_text;

		lstrcpy(szText,window_title);
//		if (m_nWindow > 0)
//			wsprintf(szText + lstrlen(szText), _T(":%d"), m_nWindow);

		// set title if changed, but don't remove completely
		AfxSetWindowText(m_hWnd, szText);
   }
   else
   {
      CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
   }
}

void CEAFChildFrame::OnBeforeMaxViewActivate(void* pvCreateData)
{
   // Called by framework when a view cannot be created because it has reacted
   // its maximum view count. pvCreateData is a pointer to the view creation
   // data that would have been used to initialize the view if it had been created.

   // Does nothing be default.
   // Override this method if you want to modified the frame/view with the creation data
}

BOOL CEAFChildFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   // :TRICKY: rab 11.23.96 : Modifying default behavior
	// By turning off the default MFC-defined FWS_ADDTOTITLE style,
	// the framework will use first string in the document template
	// STRINGTABLE resource instead of the document name.
	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}

LRESULT CEAFChildFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
   CEAFApp* pApp = EAFGetApp();
   pApp->GetMDIWndSnapper().OnMessage(this, message, wParam, lParam);	
	return CMDIChildWnd::WindowProc(message, wParam, lParam);
}

void CEAFChildFrame::SnapToRect(LPCRECT lpRect)
{
   if ( lpRect )
   {
      GetWindowPlacement(&m_wndPlacement);
      m_bIsSnapped = true;
      MoveWindow(lpRect);
   }
   else
   {
      if ( m_bIsSnapped )
      {
         SetWindowPlacement(&m_wndPlacement);
      }
      m_bIsSnapped = false;
   }
}

void CEAFChildFrame::Unsnap()
{
   if ( m_bIsSnapped )
   {
      m_wndPlacement.rcNormalPosition;
      SetWindowPos(nullptr,m_wndPlacement.rcNormalPosition.left,m_wndPlacement.rcNormalPosition.top,m_wndPlacement.rcNormalPosition.right-m_wndPlacement.rcNormalPosition.left,m_wndPlacement.rcNormalPosition.bottom - m_wndPlacement.rcNormalPosition.top,SWP_NOZORDER | SWP_NOMOVE);
      m_bIsSnapped = false;
   }
}

bool CEAFChildFrame::IsSnapped()
{
   return m_bIsSnapped;
}

BOOL CEAFChildFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	return CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}

BOOL CEAFChildFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
   //AFX_MANAGE_STATE(AfxGetAppModuleState());
   // Don't set the module state for the EAF DLL Module. This function has been made pure-virtual
   // so that base classes must implement and set the module state for their DLL module.
   return CMDIChildWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}
