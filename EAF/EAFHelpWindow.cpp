///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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



#include "stdafx.h"
#include "resource.h"
#include "EAFHelpWindow.h"
#include "EAFHelpWindowThread.h"
#include "WebBrowser.h"

#include <EAF\EAFApp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] = 
{
   ID_SEPARATOR,
};

/////////////////////////////////////////////////////////////////////////////
// CEAFHelpWindow

CEAFHelpWindow::CEAFHelpWindow()
{
   m_bCanClose = FALSE;
}

CEAFHelpWindow::~CEAFHelpWindow()
{
}

void CEAFHelpWindow::CanClose(BOOL bCanClose)
{
   m_bCanClose = bCanClose;
}

BEGIN_MESSAGE_MAP(CEAFHelpWindow, CFrameWnd)
	//{{AFX_MSG_MAP(CEAFHelpWindow)
	ON_WM_CREATE()
   ON_WM_CLOSE()
   ON_WM_DESTROY()
   ON_COMMAND(ID_FILE_CLOSE,OnFileClose)
   ON_COMMAND(ID_FILE_PRINT,OnFilePrint)
   ON_COMMAND(EAFID_HELPWND_BACK,OnBack)
   ON_COMMAND(EAFID_HELPWND_FORWARD,OnForward)
   ON_NOTIFY(CWebBrowser::BeforeNavigate2,AFX_IDW_PANE_FIRST,OnNavigate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFHelpWindow diagnostics

#ifdef _DEBUG
void CEAFHelpWindow::AssertValid() const
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CFrameWnd::AssertValid();
}

void CEAFHelpWindow::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFHelpWindow message handlers

int CEAFHelpWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

   DWORD dwToolBarStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY;
   if ( !m_Toolbar.CreateEx(this,TBSTYLE_FLAT | TBSTYLE_TRANSPARENT,dwToolBarStyle,CRect(0,0,0,0), 500) ||
        !m_Toolbar.LoadToolBar(IDR_HELP) )
   {
      return -1;
   }
   EnableDocking(CBRS_ALIGN_ANY);
   m_Toolbar.EnableDocking(CBRS_ALIGN_ANY);
   DockControlBar(&m_Toolbar);


   if ( !m_StatusBar.Create(this) )
   {
      return -1;
   }

   m_StatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));
	
   CRect rect(0,0,0,0);
   BOOL bCreated = m_WebBrowser.Create(TEXT("Browser Control"),
                                         WS_CHILD | WS_VISIBLE, rect, this, AFX_IDW_PANE_FIRST);
   if ( !bCreated )
   {
      TRACE( TEXT("Failed to create browser") );
      return -1;
   }


   WINDOWPLACEMENT wp;
   if ( EAFGetApp()->ReadWindowPlacement(CString((LPCTSTR)IDS_REG_SETTINGS),_T("HelpWindowPosition"),&wp) )
   {
      if ( sysFlags<LONG>::IsSet(lpCreateStruct->style,WS_VISIBLE) )
      {
         wp.showCmd = SW_SHOW;
      }
      else
      {
         wp.showCmd = SW_HIDE;
      }

      SetWindowPlacement(&wp);
   }

   SetIcon(AfxGetApp()->LoadIcon(IDI_HELP),FALSE);
   SetWindowText(_T("Help"));

   return 0;
}

void CEAFHelpWindow::OnClose()
{
   if ( m_bCanClose )
   {
      CFrameWnd::OnClose();
   }
   else
   {
      ShowWindow(SW_HIDE);
   }
}

void CEAFHelpWindow::OnDestroy()
{
   WINDOWPLACEMENT wp;
   wp.length = sizeof wp;
   if (GetWindowPlacement(&wp))
   {
      wp.flags = 0;
      wp.showCmd = SW_SHOWNORMAL;
      EAFGetApp()->WriteWindowPlacement(CString((LPCTSTR)IDS_REG_SETTINGS),_T("HelpWindowPosition"),&wp);
   }

   CFrameWnd::OnDestroy();
}

void CEAFHelpWindow::OnFileClose()
{
   PostMessage(WM_CLOSE);
}

void CEAFHelpWindow::OnFilePrint()
{
   m_WebBrowser.Print();
}

void CEAFHelpWindow::Navigate(LPCTSTR lpszURL)
{
   CWaitCursor wait;
   ShowWindow(SW_SHOW);
   m_WebBrowser.Navigate(lpszURL);
}

void CEAFHelpWindow::OnBack()
{
   m_WebBrowser.GoBack();
}

void CEAFHelpWindow::OnForward()
{
   m_WebBrowser.GoForward();
}

void CEAFHelpWindow::OnNavigate(NMHDR* pNotifyStruct,LRESULT* result)
{
   CWebBrowser::Notification* pNotification = (CWebBrowser::Notification*)(pNotifyStruct);
   m_StatusBar.SetPaneText(0,pNotification->URL);
}
