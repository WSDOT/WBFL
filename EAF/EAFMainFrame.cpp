///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFResources.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFToolBar.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFSplashScreen.h>
#include <EAF\EAFApp.h>
#include <EAF\EAFPluginCommandManager.h>
#include <EAF\EAFChildFrame.h>
#include "ToolBarDlg.h"

#include "MFCToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CEAFMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CEAFMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CEAFMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
   ON_WM_SIZE()
	ON_WM_CREATE()
   ON_WM_CLOSE()
   ON_WM_DESTROY()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnToolTipText)
   ON_NOTIFY_EX_RANGE(TBN_DROPDOWN, 0, 0xFFFF, OnToolbarDropDown)

	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
   ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
   ON_COMMAND(ID_HELP, OnHelp)
   ON_COMMAND(ID_DEFAULT_HELP, OnHelp)
	ON_WM_DROPFILES()

   ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolBar)
   ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolBar)
   ON_COMMAND_RANGE(EAF_TOOLBAR_MENU_BASE, EAF_TOOLBAR_MENU_BASE+EAF_TOOLBAR_MENU_COUNT, OnToolbarMenuSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFMainFrame construction/destruction

CEAFMainFrame::CEAFMainFrame()
{
   m_pWndCurrentChild = NULL;

   m_bDisableFailCreateMsg = FALSE;
   m_bCreateCanceled = FALSE;

   m_bDisableHideMainToolBar = FALSE;

   m_pStatusBar = NULL;
   m_pMainFrameToolBar = NULL;
   m_pMainMenu = NULL;
   m_pStartPageWnd = NULL;

   m_bShowToolTips = TRUE;

   m_ToolBarIDs.push_back(ID_MAINFRAME_TOOLBAR+1);
}

CEAFMainFrame::~CEAFMainFrame()
{
   if ( m_pStatusBar )
   {
      delete m_pStatusBar;
   }

   if (m_pMainFrameToolBar)
   {
      delete m_pMainFrameToolBar;
   }

   if (m_pMainMenu)
   {
      delete m_pMainMenu;
   }

   m_wndMDIClient.Detach();
}

CEAFStatusBar* CEAFMainFrame::CreateStatusBar()
{
   CEAFStatusBar* pStatusBar = new CEAFStatusBar();
	if (!pStatusBar->Create(this) )
	{
      delete pStatusBar;
      return NULL;
	}

   return pStatusBar;
}

CToolBar* CEAFMainFrame::CreateMainFrameToolBar()
{
   CToolBar* pToolBar = new CMyToolBar();
   
   DWORD dwToolBarStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER;
   if ( m_bShowToolTips )
   {
      dwToolBarStyle |= CBRS_TOOLTIPS | CBRS_FLYBY;
   }

   if ( !pToolBar->CreateEx(this,TBSTYLE_FLAT | TBSTYLE_TRANSPARENT,dwToolBarStyle,CRect(0,0,0,0), ID_MAINFRAME_TOOLBAR) ||
        !pToolBar->LoadToolBar(IDR_MAINFRAME) )
   {
      delete pToolBar;
      return NULL;
   }

   pToolBar->GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
   int idx = pToolBar->CommandToIndex(ID_FILE_OPEN);
   DWORD dwStyle = pToolBar->GetButtonStyle(idx);
   dwStyle |= BTNS_DROPDOWN;
   pToolBar->SetButtonStyle(idx,dwStyle);

   pToolBar->EnableDocking(CBRS_ALIGN_ANY);
   pToolBar->SetWindowText(AfxGetAppName());

   return pToolBar;
}

CEAFStartPageWnd* CEAFMainFrame::CreateStartPage()
{
   return NULL;
}

void CEAFMainFrame::OnSize(UINT nType, int cx, int cy)
{
   CMDIFrameWnd::OnSize(nType,cx,cy);
   if ( m_pStartPageWnd )
   {
      // get the range of control bar IDs
      UINT minID = UINT_MAX;
      UINT maxID = 0;

	   POSITION pos = m_listControlBars.GetHeadPosition();
	   while (pos != NULL)
	   {
		   CControlBar* pBar = (CControlBar*)m_listControlBars.GetNext(pos);
         UINT id = pBar->GetDlgCtrlID();
         minID = Min(id,minID);
         maxID = Max(id,maxID);
	   }

      CRect rect;
      UINT bkID = m_pStartPageWnd->GetDlgCtrlID();
      RepositionBars(minID,maxID,bkID,CWnd::reposQuery,&rect);
      m_pStartPageWnd->SetWindowPos(NULL,0/*rect.left*/,0/*rect.top*/,rect.Size().cx,rect.Size().cy,SWP_NOZORDER);
   }
}

int CEAFMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
   {
		return -1;
   }

   if ( m_wndMDIClient.Attach(m_hWndMDIClient) == 0 )
   {
      TRACE0("Failed to attach to MDIClient.\n");
      return -1;
   }
	
   // Restore tool tips mode
   m_bShowToolTips = (EAFGetApp()->GetProfileInt(CString((LPCTSTR)IDS_REG_SETTINGS),
                                                 CString((LPCTSTR)IDS_TOOLTIP_STATE),
                                                 1) !=0 );

   // Restore the layout of the application window
   WINDOWPLACEMENT wp;
   if ( EAFGetApp()->ReadWindowPlacement(CString((LPCTSTR)IDS_REG_SETTINGS),CString((LPCTSTR)IDS_REG_WNDPOS),&wp) )
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

   // Status Bar
   m_pStatusBar = CreateStatusBar();
   if ( !m_pStatusBar )
   {
      return -1;
   }
   m_pStatusBar->EnableModifiedFlag(FALSE);


   // Tool Bars
   EnableDocking(CBRS_ALIGN_ANY);
   m_pMainFrameToolBar = CreateMainFrameToolBar();
   if ( !m_pMainFrameToolBar )
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

   DockControlBar( m_pMainFrameToolBar );

   // Load the state of the application toolbar
   LoadBarState( CString("Toolbars\\") + CString((LPCTSTR)IDS_TOOLBAR_STATE) );

   // Main Menu
   m_pMainMenu = CreateMainMenu();

   // Start Page Window
   m_pStartPageWnd = CreateStartPage();
   if ( m_pStartPageWnd )
   {
      m_pStartPageWnd->Create(NULL,_T("Start Page"),WS_CHILD | WS_VISIBLE,rectDefault,this);
   }

	return 0;
}

void CEAFMainFrame::OnClose()
{
   CEAFApp* pApp = EAFGetApp();

   // Save the layout of the application window
   WINDOWPLACEMENT wp;
   wp.length = sizeof wp;
   if (GetWindowPlacement(&wp))
   {
      wp.flags = 0;
      wp.showCmd = SW_SHOWNORMAL;
      pApp->WriteWindowPlacement(CString((LPCTSTR)IDS_REG_SETTINGS),CString((LPCTSTR)IDS_REG_WNDPOS),&wp);
   }

   // Save the ToolTips state
   pApp->WriteProfileInt(CString((LPCTSTR)IDS_REG_SETTINGS),
                         CString((LPCTSTR)IDS_TOOLTIP_STATE),
                        (m_bShowToolTips != 0) );

   pApp->OnMainFrameClosing();

   CMDIFrameWnd::OnClose();
}

void CEAFMainFrame::OnDestroy()
{
   // Save the state of the application toolbar
   SaveBarState( CString("Toolbars\\") + CString((LPCTSTR)IDS_TOOLBAR_STATE) );

   CMDIFrameWnd::OnDestroy();
}

BOOL CEAFMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.style &= ~WS_VISIBLE;

   return CMDIFrameWnd::PreCreateWindow(cs);
}

BOOL CEAFMainFrame::PreTranslateMessage(MSG* pMsg)
{
   if ( CMDIFrameWnd::PreTranslateMessage(pMsg) )
   {
      return TRUE;
   }

   // Add a toolbar popup menu if a right click happens in the docking space
   if (pMsg->message == WM_RBUTTONDOWN)
   {
      CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);
      CControlBar* pBar = DYNAMIC_DOWNCAST(CControlBar, pWnd);

      if (pBar != NULL)
      {
         CMenu menu;
         menu.CreatePopupMenu();

         int offset = 0;
         std::vector<CString> vNames  = GetToolBarNames();
         std::vector<BOOL>    vStates = GetToolBarStates();
         std::vector<CString>::iterator nameIter  = vNames.begin();
         std::vector<BOOL>::iterator    stateIter = vStates.begin();

         for ( ; nameIter != vNames.end(); nameIter++, stateIter++, offset++ )
         {
            ASSERT( offset <= EAF_TOOLBAR_MENU_COUNT );

            CString strName = *nameIter;
            BOOL bVisible = *stateIter;
            UINT iFlags = MF_STRING | MF_ENABLED;
            if ( bVisible )
            {
               iFlags |= MF_CHECKED;
            }

            CString strToolBarName;
            menu.AppendMenu( iFlags, EAF_TOOLBAR_MENU_BASE + offset, strName );
         }

         CPoint pt;
         pt.x = LOWORD(pMsg->lParam);
         pt.y = HIWORD(pMsg->lParam);
         pBar->ClientToScreen(&pt);

         menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this );

         return TRUE;
      }
   }
   
	if ( WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST )
   {
      // this is a little hack to get the accelerator keys translated when the shift, alt (menu), or control key is pressed
      if ( pMsg->message == WM_KEYUP && (::GetKeyState(VK_SHIFT) || ::GetKeyState(VK_MENU) || ::GetKeyState(VK_CONTROL)) )
      {
         pMsg->message = WM_KEYDOWN;
      }

      if ( GetAcceleratorTable()->TranslateMessage(this,pMsg) )
      {
         return TRUE;
      }

      CEAFDocument* pDoc = GetDocument();
      if ( pDoc )
      {
         if ( ((CEAFDocTemplate*)pDoc->GetDocTemplate())->GetAcceleratorTable()->TranslateMessage(this,pMsg) )
         {
            return TRUE;
         }

         if ( pDoc->GetDocPluginManager()->GetAcceleratorTable()->TranslateMessage(this,pMsg) )
         {
            return TRUE;
         }
      }
   }

   return FALSE; // message needs further processing
}

void CEAFMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
   BOOL bHandledByPlugin = FALSE;

   CDocument* pActiveDoc = NULL;
   CMDIChildWnd* pChildWnd = MDIGetActive();
   if ( pChildWnd )
   {
      pActiveDoc = pChildWnd->GetActiveDocument();
   }

   if ( pActiveDoc && pActiveDoc->IsKindOf(RUNTIME_CLASS(CEAFDocument)) )
   {
      CEAFDocument* pDoc = (CEAFDocument*)pActiveDoc;
      UINT nPluginCmdID;
      CComPtr<IEAFCommandCallback> pCallback;
      if ( pDoc->GetPluginCommandManager()->GetCommandCallback(nID,&nPluginCmdID,&pCallback) )
      {
         // this command belogs to one of the plug-ins
         bHandledByPlugin = TRUE;
         if ( pCallback )
         {
            pCallback->GetStatusBarMessageString(nPluginCmdID,rMessage);
         }
         else
         {
            pDoc->GetStatusBarMessageString(nID,rMessage);
         }
      }
   }

   if ( !bHandledByPlugin )
   {
      CEAFApp* pApp = EAFGetApp();
      UINT nPluginCmdID;
      CComPtr<IEAFCommandCallback> pCallback;
      if ( pApp->GetPluginCommandManager()->GetCommandCallback(nID,&nPluginCmdID,&pCallback) && pCallback )
      {
         // this command belogs to one application of the plug-ins
         bHandledByPlugin = TRUE;
         pCallback->GetStatusBarMessageString(nPluginCmdID,rMessage);
      }
   }

   if ( !bHandledByPlugin && pActiveDoc )
   {
      CEAFDocument* pDoc = (CEAFDocument*)pActiveDoc;
      CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDoc->GetDocTemplate();
      if ( pTemplate->GetCommandCallback() )
      {
         bHandledByPlugin = pTemplate->GetCommandCallback()->GetStatusBarMessageString(nID,rMessage);
      }
      else
      {
         bHandledByPlugin = pDoc->GetStatusBarMessageString(nID,rMessage);
      }
   }

   if ( !bHandledByPlugin )
   {
      CMDIFrameWnd::GetMessageString(nID,rMessage);
   }
}

BOOL CEAFMainFrame::OnToolTipText(UINT ,NMHDR* pTTTStruct,LRESULT* pResult)
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pTTTStruct;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pTTTStruct;

	UINT_PTR nID = pTTTStruct->idFrom;
	if (pTTTStruct->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
	 	 pTTTStruct->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
      nID = ::GetDlgCtrlID((HWND)nID);
	}

   CEAFDocument* pDoc = GetDocument();
   BOOL bHandledByPlugin = FALSE;
   CString strTipText;

   if ( nID != 0 && pDoc )
   {
      UINT nPluginCmdID;
      IEAFCommandCallback* pCallback;
      if ( pDoc->GetPluginCommandManager()->GetCommandCallback((UINT)nID,&nPluginCmdID,&pCallback) )
      {
         // this command belogs to one of the plug-ins
         if ( pCallback )
         {
            bHandledByPlugin = pCallback->GetToolTipMessageString(nPluginCmdID,strTipText);
         }
         else
         {
            bHandledByPlugin = pDoc->GetToolTipMessageString((UINT)nID,strTipText);
         }
      }
   }

   if ( !bHandledByPlugin )
   {
      CEAFApp* pApp = EAFGetApp();
      UINT nPluginCmdID;
      IEAFCommandCallback* pCallback;
      if ( pApp->GetPluginCommandManager()->GetCommandCallback((UINT)nID,&nPluginCmdID,&pCallback) && pCallback )
      {
         // this command belogs to one of the application plug-ins
         bHandledByPlugin = pCallback->GetToolTipMessageString(nPluginCmdID,strTipText);
      }
   }

   if (!bHandledByPlugin && pDoc )
   {
      CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDoc->GetDocTemplate();
      if ( pTemplate->GetCommandCallback() )
      {
         bHandledByPlugin = pTemplate->GetCommandCallback()->GetToolTipMessageString((UINT)nID,strTipText);
      }
      else
      {
         bHandledByPlugin = pDoc->GetToolTipMessageString((UINT)nID,strTipText);
      }
   }

   if ( bHandledByPlugin )
   {
#ifndef _UNICODE
	   if (pTTTStruct->code == TTN_NEEDTEXTA)
      {
		   lstrcpyn(pTTTA->szText, strTipText, strTipText.GetLength()+1);
      }
	   else
      {
		   _mbstowcsz(pTTTW->szText, strTipText, strTipText.GetLength()+1);
      }
#else
	   if (pTTTStruct->code == TTN_NEEDTEXTA)
      {
		   _wcstombsz(pTTTA->szText, strTipText, strTipText.GetLength()+1);
      }
	   else
      {
		   lstrcpyn(pTTTW->szText, strTipText, strTipText.GetLength()+1);
      }
#endif

      *pResult = 0;

      return TRUE;
   }

   return FALSE; // not handled here
}

BOOL CEAFMainFrame::OnToolbarDropDown(UINT nToolbarID,NMHDR* pnmhdr,LRESULT* plr)
{
   NMTOOLBAR* pnmtb = (NMTOOLBAR*)(pnmhdr);
   UINT nID;

   switch(pnmtb->iItem)
   {
   case ID_FILE_OPEN:
      nID = IDR_RECENT_FILE;
      break;

   default:
      return FALSE;
   }

   CMenu menu;
   menu.LoadMenu(nID);
   CMenu* pPopup = menu.GetSubMenu(0);
   ASSERT(pPopup);

   CRect rc;
   ::SendMessage(pnmtb->hdr.hwndFrom,TB_GETRECT,pnmtb->iItem,(LPARAM)&rc);

   CPoint pntBottomLeft(rc.left,rc.bottom);
   ::ClientToScreen(pnmtb->hdr.hwndFrom,&pntBottomLeft);

   pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL, pntBottomLeft.x, pntBottomLeft.y, this, &rc);

   return TRUE;
}

void CEAFMainFrame::UpdateFrameTitle(LPCTSTR lpszDocName)
{
   UpdateFrameTitleForDocument(lpszDocName);
}

void CEAFMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
   // Copied from CMDIFrameWnd
   // Modified to not check if the window is maximized.
   // The filename is always displayed.

   if ((GetStyle() & FWS_ADDTOTITLE) == 0)
   {
      return;     // leave it alone!
   }

   CEAFDocument* pDoc = GetDocument();

   if (bAddToTitle && pDoc)
   {
      if (pDoc->GetPathName().GetLength() == 0)
      {
         UpdateFrameTitleForDocument(pDoc->GetTitle());
      }
      else
      {
         TCHAR title[_MAX_PATH];
         WORD cbBuf = _MAX_PATH;

         ::GetFileTitle(pDoc->GetPathName(),title,cbBuf);

         UpdateFrameTitleForDocument(title);
      }
   }
   else
   {
      UpdateFrameTitleForDocument(NULL);
   }
}

void CEAFMainFrame::UpdateFrameTitleForDocument(LPCTSTR lpszDocName)
{
   // Copied from CFrameWnd.
   // Modified to remove the :n

   // copy first part of title loaded at time of frame creation
   TCHAR szText[256+_MAX_PATH];

   if (GetStyle() & FWS_PREFIXTITLE)
   {
      szText[0] = '\0';   // start with nothing

      // get name of currently active view
      if (lpszDocName != NULL)
      {
         lstrcpy(szText, lpszDocName);
         lstrcat(szText, _T(" - "));
      }
      lstrcat(szText, m_strTitle);
   }
   else
   {
      // get name of currently active view
      lstrcpy(szText, m_strTitle);
      if (lpszDocName != NULL)
      {
         lstrcat(szText, _T(" - "));
         lstrcat(szText, lpszDocName);
      }
   }

   // set title if changed, but don't remove completely
   // Note: will be excessive for MDI Frame with maximized child
   AfxSetWindowText(m_hWnd, szText);
}

/////////////////////////////////////////////////////////////////////////////
// CEAFMainFrame diagnostics

#ifdef _DEBUG
void CEAFMainFrame::AssertValid() const
{
   // Make sure the module state is that for the CWinApp class
   // before diving down into MFC (if the module state isn't
   // correct, all sorts of asserts will fire)
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CMDIFrameWnd::AssertValid();
}

void CEAFMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFMainFrame message handlers
BOOL CEAFMainFrame::DisableFailCreateMessage() const
{
   return m_bDisableFailCreateMsg;
}

void CEAFMainFrame::DisableFailCreateMessage(BOOL bDisable)
{
   m_bDisableFailCreateMsg = bDisable;
}

void CEAFMainFrame::CreateCanceled()
{
   m_bCreateCanceled = TRUE;
}

CEAFDocument* CEAFMainFrame::GetDocument()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   CMDIChildWnd* pActiveChild = MDIGetActive();
   CDocument* pDoc = GetActiveDocument();
   CView* pView = GetActiveView();
   if ( pDoc == NULL && pActiveChild != NULL )
   {
      pDoc = pActiveChild->GetActiveDocument();
   }
   else if ( pDoc == NULL && pView != NULL )
   {
      pDoc = pView->GetDocument();
   }

   if ( pDoc != NULL && pDoc->IsKindOf(RUNTIME_CLASS(CEAFDocument)) )
   {
      return (CEAFDocument*)pDoc;
   }
   else
   {
      return NULL;
   }
}

CView* CEAFMainFrame::CreateOrActivateFrame(CEAFDocTemplate* pTemplate)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   // If a view (specified by pTemplate->GetViewClass()) already exists, 
   // then activate the MDI child window containing
   // the view.  Otherwise, create a new view for the document.
   m_bCreateCanceled = false;
   m_bDisableFailCreateMsg = false;

   CMDIChildWnd* pMDIActive = MDIGetActive();
   ASSERT(pMDIActive != NULL);

   CDocument* pDoc = pMDIActive->GetActiveDocument();
   ASSERT(pDoc != NULL);

   // How many of this type of view can we create?
   int max_view_count = pTemplate->GetMaxViewCount();

   if (1 <= max_view_count)
   {
      // Scan all views attached to the document, counting the number
      // of views that are the same type as pViewClass.  Retain a pointer
      // to the last view of this type for activation if necessary
      int view_count = 0;
      CView* pView;
      CView* pLastView = NULL;
      POSITION pos = pDoc->GetFirstViewPosition();
      while (pos != NULL && view_count <= max_view_count)
      {
         pView = pDoc->GetNextView(pos);
         if (pView->IsKindOf(pTemplate->GetViewClass()))
         {
            pLastView = pView;
            view_count++;
         }
      }

      if (max_view_count <= view_count)
      {
         // This attempt would cause the maximim view count to be
         // exceeded. Activate the last view of this type.
         CFrameWnd* pFrame = pLastView->GetParentFrame();
         if (pFrame->IsKindOf(RUNTIME_CLASS(CEAFChildFrame)))
         {
            CEAFChildFrame* pEAFFrame = (CEAFChildFrame*)(pFrame);
            pEAFFrame->OnBeforeMaxViewActivate(pTemplate->GetViewCreationData());
         }
         pFrame->ActivateFrame();
         return pLastView;
      }
   }
   

   // If we get this far, the view count is less than the maximum or the
   // maximum is unlimited (-1). Create a new view
   CView* pNewView = 0;
   CMDIChildWnd* pNewFrame = (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, pMDIActive));
   BOOL bCreated = (pNewFrame == NULL ? FALSE : TRUE);
   if ( !bCreated )
   {
      // Child frame was not created
      if ( !m_bDisableFailCreateMsg )
      {
         // We aren't disabling the message.
         CString msg;
         CString msg1;
         msg1.LoadString( IDS_E_CREATEWND );
         CString msg2;
         msg2.LoadString( IDS_E_LOWRESOURCES );
         AfxFormatString2( msg, IDS_E_FORMAT, msg1, msg2 );
         AfxMessageBox( msg );
      }

      pNewView = 0;
   }
   else
   {
      ASSERT_KINDOF(CMDIChildWnd, pNewFrame);

      pNewFrame->ActivateFrame();
      pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
      pNewFrame->RecalcLayout();
      pNewView = pNewFrame->GetActiveView();
   }

   if ( m_bCreateCanceled )
   {
      // During the initial update process, the user canceled the creation of this
      // view (most likely the OnInitialUpdate() method (or one it calls) displayed
      // a progress window and ther user pressed the cancel button).

      // We need to destroy the view, but lets do it by destroying its frame window.
      pNewFrame->MDIDestroy();

      m_bCreateCanceled = false;
   }

   m_bCreateCanceled = false;
   m_bDisableFailCreateMsg = false;

   return pNewView;
}

CEAFMenu* CEAFMainFrame::GetMainMenu()
{
   return m_pMainMenu;
}

CEAFAcceleratorTable* CEAFMainFrame::GetAcceleratorTable()
{
   CEAFApp* pApp = EAFGetApp();
   return pApp->GetAppPluginManager()->GetAcceleratorTable();
}

CEAFStatusBar* CEAFMainFrame::GetStatusBar()
{
   return m_pStatusBar;
}

void CEAFMainFrame::SetStatusBar(CEAFStatusBar* pStatusBar)
{
   m_pStatusBar->DestroyWindow();
   delete m_pStatusBar;
   if ( pStatusBar )
   {
      m_pStatusBar = pStatusBar;
      m_pStatusBar->Reset();
   }
   else
   {
      m_pStatusBar = CreateStatusBar();
   }
}

void CEAFMainFrame::HideMainFrameToolBar()
{
   if ( m_bDisableHideMainToolBar )
   {
      return;
   }

   ShowControlBar(m_pMainFrameToolBar,FALSE,FALSE);
}

void CEAFMainFrame::ShowMainFrameToolBar()
{
   if ( m_bDisableHideMainToolBar )
   {
      return;
   }

   ShowControlBar(m_pMainFrameToolBar,TRUE,FALSE);
}

void CEAFMainFrame::HideStartPage()
{
   if ( m_pStartPageWnd )
   {
      m_pStartPageWnd->ShowWindow(SW_HIDE);
   }
}

void CEAFMainFrame::ShowStartPage()
{
   if ( m_pStartPageWnd )
   {
      m_pStartPageWnd->ShowWindow(SW_SHOW);
   }
}

UINT CEAFMainFrame::GetNextToolBarID()
{
   // If this assert fires, you probably didn't get the main window from the correct module state
   ASSERT(m_ToolBarIDs.size() != 0);
  
   std::vector<UINT>::iterator iter;
   for ( iter = m_ToolBarIDs.begin(); iter != m_ToolBarIDs.end(); iter++ )
   {
      UINT id = *iter;
      if ( id == -1 )
      {
         iter--;     // back up one
         id = *iter; // get the id
         iter++;     // advance the iter
         id++;       // increment the id
         *iter = id; // assign id to this place in the vector
         return id;  // done
      }
   }

   // if we got this far, then all of the spots in the vector are used... add one at the end
   UINT id = m_ToolBarIDs.back();
   id++;
   m_ToolBarIDs.push_back(id);
   return id;
}

void CEAFMainFrame::RecycleToolBarID(UINT id)
{
   std::vector<UINT>::iterator iter;
   for ( iter = m_ToolBarIDs.begin(); iter != m_ToolBarIDs.end(); iter++ )
   {
      if ( *iter == id )
      {
         *iter = -1;
         return;
      }
   }

   ATLASSERT(false); // should never get here... id wasn't in the vector
}

UINT CEAFMainFrame::CreateToolBar(LPCTSTR lpszName,CEAFPluginCommandManager* pCmdMgr)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   if ( EAF_TOOLBAR_MENU_COUNT <= m_ToolBarInfo.size() )
   {
      ATLASSERT(false); // can't load any more toolbars as the maximum has been reached
      return -1;
   }

   ATLASSERT(pCmdMgr != NULL);
   if ( pCmdMgr == NULL )
   {
      return -1; // must have a command manager
   }

   CEAFToolBar* pEAFToolBar = new CEAFToolBar();

   UINT tbID = GetNextToolBarID(); // this is a unique child window ID

   CEAFToolBarInfo tbInfo;
   tbInfo.m_pEAFToolBar  = pEAFToolBar;
   tbInfo.m_ToolBarID    = tbID;

   CToolBar* pToolBar = new CMyToolBar;

   DWORD dwToolBarStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER;
   if ( m_bShowToolTips )
   {
      dwToolBarStyle |= CBRS_TOOLTIPS | CBRS_FLYBY;
   }

   pToolBar->CreateEx(this,TBSTYLE_FLAT | TBSTYLE_TRANSPARENT,dwToolBarStyle,CRect(0,0,0,0),tbID);
   pToolBar->EnableDocking(CBRS_ALIGN_ANY);
   pToolBar->SetWindowText(lpszName);

   pEAFToolBar->m_ToolBarID  = tbID;
   pEAFToolBar->m_pCmdMgr    = pCmdMgr;
   pEAFToolBar->m_pToolBar   = pToolBar;
   pEAFToolBar->bOwnsToolBar = true;

   tbInfo.m_pMFCToolBar = pToolBar;

   if ( m_ToolBarInfo.size() == 0 )
   {
      DockControlBar(pToolBar);
   }
   else
   {
      CToolBar* pPrevToolBar = m_ToolBarInfo.back().m_pMFCToolBar;
      DockControlBarLeftOf(pToolBar,pPrevToolBar);
   }

   m_ToolBarInfo.push_back(tbInfo);

   return tbID;
}

CEAFToolBar* CEAFMainFrame::GetToolBar(UINT toolbarID)
{
   if ( m_ToolBarInfo.size() == 0 )
   {
      return NULL;
   }

   CEAFToolBarInfo key;
   key.m_ToolBarID = toolbarID;
   ToolBarInfo::iterator found = std::find(m_ToolBarInfo.begin(),m_ToolBarInfo.end(),key);
   if ( found == m_ToolBarInfo.end() )
   {
      ATLASSERT(false); // not found? why?
      return NULL;
   }

   CEAFToolBarInfo tbInfo = *found;
   return tbInfo.m_pEAFToolBar;
}

void CEAFMainFrame::DestroyToolBar(UINT tbID)
{
   CEAFToolBarInfo key;
   key.m_ToolBarID = tbID;
   ToolBarInfo::iterator found = std::find(m_ToolBarInfo.begin(),m_ToolBarInfo.end(),key);
   if ( found == m_ToolBarInfo.end() )
   {
      ATLASSERT(false); // not found? why?
      return;
   }

   CEAFToolBarInfo tbInfo = *found;

   tbInfo.m_pMFCToolBar->DestroyWindow();
   delete tbInfo.m_pEAFToolBar;

   m_ToolBarInfo.erase(found);

   RecycleToolBarID(tbID);

   RecalcLayout();
}

void CEAFMainFrame::DestroyToolBar(CEAFToolBar* pToolBar)
{
   DestroyToolBar(pToolBar->GetToolBarID());
   pToolBar = NULL;
}

void CEAFMainFrame::EnableModifiedFlag(BOOL bEnable)
{
   if ( m_pStatusBar && m_pStatusBar->GetSafeHwnd() )
   {
      m_pStatusBar->EnableModifiedFlag(bEnable);
   }
}

void CEAFMainFrame::OnStatusChanged()
{
   if ( m_pStatusBar && m_pStatusBar->GetSafeHwnd() )
   {
      m_pStatusBar->OnStatusChanged();
   }
}

void CEAFMainFrame::OnHelp()
{
   ::HtmlHelp( *this, EAFGetApp()->m_pszHelpFilePath, HH_DISPLAY_TOPIC, 0 );
}

void CEAFMainFrame::OnHelpFinder()
{
   ::HtmlHelp( *this, EAFGetApp()->m_pszHelpFilePath, HH_HELP_FINDER, 0 );
}

void CEAFMainFrame::OnDropFiles(HDROP hDropInfo) 
{
   // Don't allow multiple files to be dropped
	UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);
   if (1 < nFiles)
   {
      ::AfxMessageBox(_T("Error - Multiple file drop not allowed. Please drop one file at a time."),MB_ICONEXCLAMATION|MB_OK);
   }
   else
   {
      CMDIFrameWnd::OnDropFiles(hDropInfo);
   }
}

void CEAFMainFrame::OnViewToolBar() 
{
   CToolBarDlg dlg;
   dlg.m_strToolBarNames = GetToolBarNames();
   dlg.m_ToolBarStates   = GetToolBarStates();
   dlg.m_bShowToolTips   = m_bShowToolTips;
   
   if ( dlg.DoModal() == IDOK )
   {
      m_bShowToolTips = dlg.m_bShowToolTips;
      SetToolBarStates( dlg.m_ToolBarStates );
   }
}

void CEAFMainFrame::OnUpdateViewToolBar(CCmdUI* pCmdUI) 
{
   // Does nothing... Gobble up this message so the MFC
   // framework wont put a check mark next to the menu item.
}

void CEAFMainFrame::OnToolbarMenuSelected(UINT id)
{
   ATLASSERT(EAF_TOOLBAR_MENU_BASE <= id && id < EAF_TOOLBAR_MENU_BASE + EAF_TOOLBAR_MENU_COUNT);
   UINT base = EAF_TOOLBAR_MENU_BASE;
   UINT idx = id - base;
   ATLASSERT(idx < EAF_TOOLBAR_MENU_COUNT);
   ToggleToolBarState( idx );
}

void CEAFMainFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf)
{
   CRect rect;
   DWORD dw;
   UINT n;

   // get MFC to adjust the dimensions of all docked ToolBars
   // so that GetWindowRect will be accurate
   RecalcLayout();
   LeftOf->GetWindowRect(&rect);
   rect.OffsetRect(1,0);
   dw=LeftOf->GetBarStyle();
   n = 0;
   n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
   n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
   n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
   n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

   // When we take the default parameters on rect, DockControlBar will dock
   // each Toolbar on a seperate line.  By calculating a rectangle, we in effect
   // are simulating a Toolbar being dragged to that location and docked.
   DockControlBar(Bar,n,&rect);
}

std::vector<CString> CEAFMainFrame::GetToolBarNames()
{
   std::vector<CString> vNames;

   // Resource ID's of the toolbars.
   for ( ToolBarInfo::iterator iter = m_ToolBarInfo.begin(); iter != m_ToolBarInfo.end(); iter++ )
   {
      CEAFToolBarInfo& info = *iter;
      CString strName;
      info.m_pMFCToolBar->GetWindowText(strName);
      vNames.push_back( strName );
   }

   if ( vNames.size() == 0 )
   {
      ASSERT(GetActiveDocument() == NULL); // there shouldn't be a document open (unless the current document does not have toolbars)
      if ( GetActiveDocument() == NULL )
      {
         CString strName;
         m_pMainFrameToolBar->GetWindowText(strName);
         vNames.push_back(strName);
      }
   }

   return vNames;
}

std::vector<BOOL> CEAFMainFrame::GetToolBarStates()
{
   std::vector<BOOL> vStates;

   ToolBarInfo::iterator iter;
   for ( iter = m_ToolBarInfo.begin(); iter < m_ToolBarInfo.end(); iter++ )
   {
      CEAFToolBarInfo& tbInfo = *iter;
      vStates.push_back( tbInfo.m_pMFCToolBar->IsWindowVisible() ? TRUE : FALSE );
   }


   if ( vStates.size() == 0 )
   {
      ASSERT(GetActiveDocument() == NULL); // there shouldn't be a document open (unless the current document does not have toolbars)
      if ( GetActiveDocument() == NULL )
      {
         CString strName;
         vStates.push_back(m_pMainFrameToolBar->IsWindowVisible() ? TRUE : FALSE);
      }
   }

   return vStates;
}

void CEAFMainFrame::SetToolBarStates(const std::vector<BOOL>& vStates)
{
   if ( m_ToolBarInfo.size() == 0 )
   {
      ATLASSERT(vStates.size() == 1 );
      // this is the main frame toolbar state
      SetToolBarState(m_pMainFrameToolBar,vStates.front());
   }
   else
   {
      ATLASSERT( vStates.size() == m_ToolBarInfo.size() );

      ToolBarInfo::iterator tb_iter = m_ToolBarInfo.begin();
      std::vector<BOOL>::const_iterator state_iter = vStates.begin();
      for ( ; tb_iter < m_ToolBarInfo.end() && state_iter < vStates.end(); tb_iter++, state_iter++ )
      {
         CEAFToolBarInfo& tbInfo = *tb_iter;
         BOOL bShow = *state_iter;
         SetToolBarState(tbInfo.m_pMFCToolBar,bShow);
      }
   }
}

void CEAFMainFrame::SetToolBarState(CToolBar* pToolBar,BOOL bShow)
{
   BOOL bIsVisible = pToolBar->IsWindowVisible();

   if ( bIsVisible && !bShow || !bIsVisible && bShow )
   {
     ShowControlBar( pToolBar, bShow, FALSE );
   }

   DWORD dwStyle = pToolBar->GetBarStyle();
   BOOL bToolTipsEnabled = sysFlags<DWORD>::IsSet( dwStyle, CBRS_TOOLTIPS );
   if ( bToolTipsEnabled && !m_bShowToolTips || !bToolTipsEnabled && m_bShowToolTips )
   {
      if ( m_bShowToolTips )
      {
         sysFlags<DWORD>::Set( &dwStyle, CBRS_TOOLTIPS | CBRS_FLYBY );
      }
      else
      {
         sysFlags<DWORD>::Clear( &dwStyle, CBRS_TOOLTIPS | CBRS_FLYBY );
      }

      pToolBar->SetBarStyle( dwStyle );
   }
}

void CEAFMainFrame::ToggleToolBarState(UINT idx)
{
   if ( m_ToolBarInfo.size() == 0 )
   {
      BOOL bIsVisible = m_pMainFrameToolBar->IsWindowVisible();
      ShowControlBar( m_pMainFrameToolBar, !bIsVisible, FALSE );
   }
   else
   {
      CEAFToolBarInfo& tbInfo = m_ToolBarInfo[idx];
      BOOL bIsVisible = tbInfo.m_pMFCToolBar->IsWindowVisible();
      ShowControlBar( tbInfo.m_pMFCToolBar, !bIsVisible, FALSE );
   }
}

void CEAFMainFrame::LoadBarState(LPCTSTR lpszProfileName)
{
	CDockState state;
	state.LoadState(lpszProfileName);
   {
      AFX_MANAGE_STATE(AfxGetAppModuleState());
   	SetDockState(state);
   }
}

void CEAFMainFrame::SaveBarState(LPCTSTR lpszProfileName) const
{
	CDockState state;
   {
      AFX_MANAGE_STATE(AfxGetAppModuleState());
	   GetDockState(state);
   }
	state.SaveState(lpszProfileName);
}

CEAFMenu* CEAFMainFrame::CreateMainMenu()
{
   CEAFApp* pApp = EAFGetApp();
   return new CEAFMenu(this,pApp->GetPluginCommandManager());
}

//----------------------------------------------------------------
// This function finds the CMDIChildWnd in the list of windows
// maintained by the application's MDIClient window following the
// one pointed to by the member variable m_pWndCurrentChild. If no
// further CMDIChildWnds are in the list, NULL is returned.
//----------------------------------------------------------------
void CEAFMainFrame::InitMDIChildWndEnum()
{
   m_pWndCurrentChild = NULL;
}

CMDIChildWnd* CEAFMainFrame::GetNextMDIChildWnd()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   if (!m_pWndCurrentChild)
     {
      // Get the first child window.
      m_pWndCurrentChild = m_wndMDIClient.GetWindow(GW_CHILD);
     }
   else
     {
      // Get the next child window in the list.
        m_pWndCurrentChild=
           (CMDIChildWnd*)m_pWndCurrentChild->GetWindow(GW_HWNDNEXT);
     }

   if (!m_pWndCurrentChild)
     {
      // No child windows exist in the MDIClient,
      // or you are at the end of the list. This check
      // will terminate any recursion.
      return NULL;
     }

  // Check the kind of window
    if (!m_pWndCurrentChild->GetWindow(GW_OWNER))
      {
        if (m_pWndCurrentChild->
                           IsKindOf(RUNTIME_CLASS(CMDIChildWnd)))
          {
                 // CMDIChildWnd or a derived class.
                 return (CMDIChildWnd*)m_pWndCurrentChild;
          }
        else
          {
                 // Window is foreign to the MFC framework.
                 // Check the next window in the list recursively.
                 return GetNextMDIChildWnd();
          }
      }
    else
      {
          // Title window associated with an iconized child window.
          // Recurse over the window manager's list of windows.
          return GetNextMDIChildWnd();
      }
}

//-----------------------------------------------------------------
// This function counts the number of CMDIChildWnd objects
// currently maintained by the MDIClient.
//-----------------------------------------------------------------

int CEAFMainFrame::GetCountMDIChildWnds()
{
 int count = 0;

 CMDIChildWnd* pChild = GetNextMDIChildWnd();
 while (pChild)
  {
    count++;
    pChild = GetNextMDIChildWnd();
  }
 return count;
}
				