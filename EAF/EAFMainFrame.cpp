// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFToolBar.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFSplashScreen.h>
#include "PluginCommandManager.h"

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
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFMainFrame construction/destruction

CEAFMainFrame::CEAFMainFrame()
{
   m_bDisableFailCreateMsg = FALSE;
   m_bCreateCanceled = FALSE;

   m_ToolBarID = 1;
}

CEAFMainFrame::~CEAFMainFrame()
{
}

CEAFStatusBar* CEAFMainFrame::CreateStatusBar()
{
   std::auto_ptr<CEAFStatusBar> pStatusBar(new CEAFStatusBar());
	if (!pStatusBar->Create(this) )
	{
      return NULL;
	}

   return pStatusBar.release();
}

int CEAFMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndReBar.Create(this) ||
		 !m_wndReBar.AddBar(&m_wndToolBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

   m_pStatusBar = std::auto_ptr<CEAFStatusBar>(CreateStatusBar());
   if ( !m_pStatusBar.get() )
   {
      return -1;
   }
   m_pStatusBar->EnableModifiedFlag(FALSE);

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

   CEAFSplashScreen::ShowSplashScreen(this,TRUE);

	return 0;
}

BOOL CEAFMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CEAFMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
   return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CEAFMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
   BOOL bHandledByPlugin = FALSE;

   CDocument* pActiveDoc = NULL;
   CMDIChildWnd* pChildWnd = MDIGetActive();
   if ( pChildWnd )
      pActiveDoc = pChildWnd->GetActiveDocument();

   if ( pActiveDoc && pActiveDoc->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
   {
      CEAFBrokerDocument* pDoc = (CEAFBrokerDocument*)pActiveDoc;
      UINT nPluginCmdID;
      ICommandCallback* pCallback;
      if ( pDoc->m_pPluginCommandMgr->GetCommandCallback(nID,&nPluginCmdID,&pCallback) )
      {
         // this command belogs to one of the plug-ins
         bHandledByPlugin = TRUE;
         pCallback->GetStatusBarMessageString(nPluginCmdID,rMessage);
      }
   }

   if ( !bHandledByPlugin )
      CMDIFrameWnd::GetMessageString(nID,rMessage);
}

BOOL CEAFMainFrame::OnToolTipText(UINT ,NMHDR* pTTTStruct,LRESULT* pResult)
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pTTTStruct;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pTTTStruct;

	UINT nID = pTTTStruct->idFrom;
	if (pTTTStruct->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
	 	 pTTTStruct->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
      nID = ::GetDlgCtrlID((HWND)nID);
	}

   CDocument* pActiveDoc = NULL;
   CMDIChildWnd* pChildWnd = MDIGetActive();
   if ( pChildWnd )
      pActiveDoc = pChildWnd->GetActiveDocument();

   if ( nID != 0 && pActiveDoc && pActiveDoc->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) )
   {
      CEAFBrokerDocument* pDoc = (CEAFBrokerDocument*)pActiveDoc;
      UINT nPluginCmdID;
      ICommandCallback* pCallback;
      if ( pDoc->m_pPluginCommandMgr->GetCommandCallback(nID,&nPluginCmdID,&pCallback) )
      {
         // this command belogs to one of the plug-ins
         CString strTipText;
         pCallback->GetToolTipMessageString(nPluginCmdID,strTipText);


#ifndef _UNICODE
	   if (pTTTStruct->code == TTN_NEEDTEXTA)
		   lstrcpyn(pTTTA->szText, strTipText, strTipText.GetLength()+1);
	   else
		   _mbstowcsz(pTTTW->szText, strTipText, strTipText.GetLength()+1);
#else
	   if (pTTTStruct->code == TTN_NEEDTEXTA)
		   _wcstombsz(pTTTA->szText, strTipText, strTipText.GetLength()+1);
	   else
		   lstrcpyn(pTTTW->szText, strTipText, strTipText.GetLength()+1);
#endif

         *pResult = 0;

         return TRUE;
      }
   }

   return FALSE; // not handled here
}

void CEAFMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
   // Copied from CMDIFrameWnd
   // Modified to not check if the window is maximized.
   // The filename is always displayed.

   if ((GetStyle() & FWS_ADDTOTITLE) == 0)
      return;     // leave it alone!

   CMDIChildWnd* pActiveChild = MDIGetActive();
   CDocument* pDocument = GetActiveDocument();

   if (pDocument == NULL && pActiveChild != NULL)
      pDocument = pActiveChild->GetActiveDocument();

   if (bAddToTitle &&
       (pActiveChild != NULL) &&
       (pDocument != NULL) )
   {
      if (pDocument->GetPathName().GetLength() == 0)
         UpdateFrameTitleForDocument(pDocument->GetTitle());
      else
      {
         char title[_MAX_PATH];
         WORD cbBuf = _MAX_PATH;

         ::GetFileTitle(pDocument->GetPathName(),title,cbBuf);

         UpdateFrameTitle(title);
      }
   }
   else
      UpdateFrameTitle(NULL);
}

void CEAFMainFrame::UpdateFrameTitle(LPCTSTR lpszDocName)
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


CView* CEAFMainFrame::CreateOrActivateFrame(CEAFDocTemplate* pTemplate)
{
   // If a view (specified by pViewClass) already exists, 
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
         pLastView->GetParentFrame()->ActivateFrame();
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

CEAFToolBar* CEAFMainFrame::GetMainToolBar()
{
   return &m_ToolBar;
}

CEAFToolBar* CEAFMainFrame::CreateToolBar(LPCTSTR lpszName,CPluginCommandManager* pCmdMgr)
{
   CEAFToolBar* pNewToolBar = new CEAFToolBar();

   CToolBar* pToolBar = new CToolBar;
   pToolBar->CreateEx(this);

	// TODO: Remove this if you don't want tool tips
	pToolBar->SetBarStyle(pToolBar->GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

   pNewToolBar->m_pCmdMgr = pCmdMgr;
   pNewToolBar->m_pToolBar = pToolBar;
   pNewToolBar->bOwnsToolBar = true;

   m_wndReBar.AddBar(pToolBar,lpszName);

   CReBarCtrl& rb = m_wndReBar.GetReBarCtrl();
   UINT nBands = rb.GetBandCount();
   REBARBANDINFO rbInfo;
   rb.GetBandInfo(nBands-1,&rbInfo);
   rbInfo.fMask |= RBBIM_ID;
   rbInfo.wID = m_ToolBarID++;
   rb.SetBandInfo(nBands-1,&rbInfo);

   pNewToolBar->m_ID = rbInfo.wID;

   for ( UINT i = 0; i < nBands; i++ )
      rb.MinimizeBand(i);


   return pNewToolBar;
}

void CEAFMainFrame::DestroyToolBar(CEAFToolBar* pToolBar)
{
   CReBarCtrl& rb = m_wndReBar.GetReBarCtrl();
   int idx = rb.IDToIndex(pToolBar->GetID());
   rb.DeleteBand(idx);
   delete pToolBar;
   pToolBar = NULL;

   RecalcLayout();
}

void CEAFMainFrame::EnableModifiedFlag(BOOL bEnable)
{
   if ( m_pStatusBar.get() )
   {
      m_pStatusBar->EnableModifiedFlag(bEnable);
   }
}
