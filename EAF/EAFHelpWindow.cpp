///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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



#include "stdafx.h"
#include "resource.h"
#include "EAFHelpWindow.h"
#include "EAFHelpWindowThread.h"
#include "WebBrowser.h"

#include <EAF\EAFApp.h>
#include <EAF\EAFCustSiteVars.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] = 
{
   ID_SEPARATOR,
};

#define ID_NAVIGATION_TIMER 1000
static const UINT gs_NavigationTimeout = 10000; // timeout in milliseconds (10,000 = 10 sec)

BEGIN_MESSAGE_MAP(CEAFHelpStatusBar, CStatusBar)
   ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CEAFHelpStatusBar::SetHelpWindow(CEAFHelpWindow* pHelpWnd)
{
   m_pHelpWnd = pHelpWnd;
}

void CEAFHelpStatusBar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
   CString strURL = m_pHelpWnd->GetURL();

   if (OpenClipboard() && EmptyClipboard())
   {
      size_t size = (strURL.GetLength() + 1) * sizeof(TCHAR);
      HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, size);
      memcpy_s(GlobalLock(hData), size, strURL.LockBuffer(), size);
      GlobalUnlock(hData);
      strURL.UnlockBuffer();
      UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
      SetClipboardData(uiFormat, hData);
      CloseClipboard();
   }
}

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
   ON_WM_SHOWWINDOW()
   ON_COMMAND(ID_FILE_CLOSE,OnFileClose)
   ON_COMMAND(ID_FILE_PRINT,OnFilePrint)
   ON_COMMAND(EAFID_HELPWND_BACK,OnBack)
   ON_COMMAND(EAFID_HELPWND_FORWARD,OnForward)
   ON_NOTIFY(CWebBrowser::BeforeNavigate2, AFX_IDW_PANE_FIRST, OnBeforeNavigate)
   ON_NOTIFY(CWebBrowser::DocumentComplete, AFX_IDW_PANE_FIRST, OnAfterNavigate)
   ON_COMMAND_RANGE(CCS_CMENU_BASE, CCS_CMENU_MAX, OnCmenuSelected)
   ON_WM_TIMER()
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
   m_StatusBar.SetHelpWindow(this);
	
   CRect rect(0,0,0,0);
   BOOL bCreated = m_WebBrowser.Create(TEXT("Browser Control"),
                                         WS_CHILD | WS_VISIBLE, rect, this, IDC_HELP_WEB_BROWSER);
   if ( !bCreated )
   {
      TRACE( TEXT("Failed to create browser") );
      return -1;
   }

   SetIcon(AfxGetApp()->LoadIcon(IDI_HELP),FALSE);
   SetWindowText(_T("Help"));

   return 0;
}

void CEAFHelpWindow::OnClose()
{
   if ( m_bCanClose )
   {
      SaveWindowPosition();
      CFrameWnd::OnClose();
   }
   else
   {
      ShowWindow(SW_HIDE);
   }
}

void CEAFHelpWindow::OnShowWindow(BOOL bShow, UINT nStatus)
{
   CFrameWnd::OnShowWindow(bShow, nStatus);

   if (bShow)
   {
      RestoreWindowPosition();
   }
   else
   {
      SaveWindowPosition();
   }
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
   m_WebBrowser.Navigate(lpszURL);

   if (!IsWindowVisible())
   {
      ShowWindow(SW_SHOW);
   }
   // force the help window to the top
   SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void CEAFHelpWindow::OnBack()
{
   m_WebBrowser.GoBack();
}

void CEAFHelpWindow::OnForward()
{
   m_WebBrowser.GoForward();
}

void CEAFHelpWindow::OnBeforeNavigate(NMHDR* pNotifyStruct,LRESULT* result)
{
   CWebBrowser::Notification* pNotification = (CWebBrowser::Notification*)(pNotifyStruct);
   CString strMsg;
   strMsg.Format(_T("%s (double click to copy URL)"),pNotification->URL);
   m_StatusBar.SetPaneText(0,strMsg);
   SetTimer(ID_NAVIGATION_TIMER, gs_NavigationTimeout,nullptr);
}

void CEAFHelpWindow::OnAfterNavigate(NMHDR* pNotifyStruct, LRESULT* result)
{
   // navigation was successful so kill the timer
   KillTimer(ID_NAVIGATION_TIMER);
}

CString CEAFHelpWindow::GetURL()
{
   return m_WebBrowser.GetLocationURL();
}

void CEAFHelpWindow::OnTimer(UINT_PTR nIDEvent)
{
   if (nIDEvent == ID_NAVIGATION_TIMER)
   {
      // the timer went off and we aren't dont navigating... kill the navigation
      m_WebBrowser.Stop();
      CEAFApp* pApp = EAFGetApp();
      if (pApp->UseOnlineDocumentation())
      {
         if (AfxMessageBox(_T("Unable to access online documentation, would you like to use the local documentation?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
         {
            pApp->UseOnlineDocumentation(FALSE);
            AfxMessageBox(_T("Documentation has been switch to the local source."));
         }
      }
   }
}

void CEAFHelpWindow::OnCmenuSelected(UINT id)
{
   UINT cmd = id-CCS_CMENU_BASE;

   switch(cmd)
   {
   //case CCS_RB_EDIT:
   //  //EditReport();
   //  break;

   case CCS_RB_FIND:
     m_WebBrowser.Find();
     break;

   case CCS_RB_SELECT_ALL:
     m_WebBrowser.SelectAll();
     break;

   case CCS_RB_PRINT:
      m_WebBrowser.Print();
     break;

   case CCS_RB_REFRESH:
     m_WebBrowser.Refresh();
     break;

   case CCS_RB_VIEW_SOURCE:
      m_WebBrowser.ViewSource();
     break;

   case CCS_RB_VIEW_BACK:
      m_WebBrowser.GoBack();
     break;

   case CCS_RB_VIEW_FORWARD:
      m_WebBrowser.GoForward();
     break;
   }
}

void CEAFHelpWindow::SaveWindowPosition()
{
   WINDOWPLACEMENT wp;
   if (GetWindowPlacement(&wp))
   {
      EAFGetApp()->WriteWindowPlacement(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("Help"), &wp);
   }
}

void CEAFHelpWindow::RestoreWindowPosition()
{
   WINDOWPLACEMENT wp;
   if (EAFGetApp()->ReadWindowPlacement(CString((LPCTSTR)IDS_WINDOW_POSITIONS), _T("Help"), &wp))
   {
      HMONITOR hMonitor = MonitorFromRect(&wp.rcNormalPosition, MONITOR_DEFAULTTONULL); // get the monitor that has maximum overlap with the dialog rectangle (returns null if none)
      if (hMonitor != NULL)
      {
         // if dialog is within a monitor, set its position... otherwise the default position will be sued
         SetWindowPos(NULL, wp.rcNormalPosition.left, wp.rcNormalPosition.top, wp.rcNormalPosition.right - wp.rcNormalPosition.left, wp.rcNormalPosition.bottom - wp.rcNormalPosition.top, 0);
         if (wp.flags == WPF_RESTORETOMAXIMIZED)
         {
            ShowWindow(SW_MAXIMIZE);
         }
      }
   }
}

