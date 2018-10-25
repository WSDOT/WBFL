///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <EAF\EAFReportView.h>
#include <EAF\EAFUtilities.h>
#include <EAF\EAFAutoProgress.h>
#include <EAF\EAFStatusCenter.h>
#include "AgentTools.h"
#include "EAFSelectReportDlg.h"

#include <EAF\EAFDocument.h>
#include <EAF\EAFMainFrame.h>
#include <EAF\EAFHints.h>
#include <EAF\EAFCustSiteVars.h>

#include <ReportManager\ReportBuilderManager.h>
#include <IReportManager.h>

#include <MfcTools\XUnwind.h>
#include <MfcTools\Text.h>
#include "ReportButton.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView


IMPLEMENT_DYNCREATE(CEAFReportView, CView)
bool CEAFReportView::ms_bIsUpdatingReport = false;

CEAFReportView::CEAFReportView()
{
   m_bNoBrowser   = false;
   m_bUpdateError = false;
   m_bIsNewReport = true;
   m_bUpdateInProgress = false;
   m_bInvalidReport = true;

   m_pReportBuilderMgr = NULL;
   m_pRptMgr = NULL;

   // Create report edit button and register to listen to messages
   m_pBtnEdit = new CReportButton();
   m_pBtnEdit->Register(this);

}

CEAFReportView::~CEAFReportView()
{
   delete(m_pBtnEdit);
}

BEGIN_MESSAGE_MAP(CEAFReportView, CView)
	//{{AFX_MSG_MAP(CEAFReportView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnToolbarPrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_DIRECT, OnUpdateFilePrint)
	//}}AFX_MSG_MAP
    ON_COMMAND_RANGE(CCS_CMENU_BASE, CCS_CMENU_MAX, OnCmenuSelected)
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView drawing

void CEAFReportView::OnDraw(CDC* pDC)
{
  CString msg;
  if ( m_bNoBrowser )
  {
     msg.LoadString(IDS_E_NOBROWSER);
  }
  else if ( m_bUpdateError )
  {
     AfxFormatString1(msg,IDS_E_UPDATE,m_ErrorMsg.c_str());
  }
  else if ( m_bUpdateInProgress )
  {
     msg.LoadString(IDS_UPDATE_IN_PROGRESS);
  }
  else
  {
     msg.LoadString(IDS_RESULTS_NOT_AVAILABLE);
  }

  CFont font;
  CFont* pOldFont = NULL;
  if ( font.CreatePointFont(100,_T("Arial"),pDC) )
     pOldFont = pDC->SelectObject(&font);

  COLORREF oldColor = pDC->SetBkColor( GetSysColor(COLOR_BTNFACE) );
  MultiLineTextOut(pDC,0,0,msg);
  pDC->SetBkColor( oldColor );

  if ( pOldFont )
     pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView diagnostics

#ifdef _DEBUG
void CEAFReportView::AssertValid() const
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
	CView::AssertValid();
}

void CEAFReportView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView message handlers

int CEAFReportView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   return 0;
}

bool CEAFReportView::InitReport(boost::shared_ptr<CReportSpecification>& pSpec,boost::shared_ptr<CReportSpecificationBuilder>& pSpecBuilder)
{
   m_pReportSpec = pSpec;
   if ( !m_pReportSpec )
      return false;

   m_pRptSpecBuilder = pSpecBuilder;

   UpdateViewTitle();
   return true;
}

bool CEAFReportView::CreateReport(CollectionIndexType rptIdx,bool bPromptForSpec)
{
   CreateReportSpecification(rptIdx,bPromptForSpec);
   return CreateReport(rptIdx,m_pReportSpec,m_pRptSpecBuilder);
}

bool CEAFReportView::CreateReport(CollectionIndexType rptIdx,boost::shared_ptr<CReportSpecification>& pSpec,boost::shared_ptr<CReportSpecificationBuilder>& pSpecBuilder)
{
   if ( !InitReport(pSpec,pSpecBuilder) )
      return false;

   if ( SUCCEEDED(UpdateReportBrowser(NULL)) )
      return true;

   return false;
}

void CEAFReportView::CreateReportSpecification(CollectionIndexType rptIdx,bool bPromptForSpec)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());
   std::vector<std::_tstring> rptNames = GetReportNames();
   if ( rptNames.size() == 0 )
   {
      // can't create reports if there aren't any defined.

      // The view creation must fail and this is intentional
      // Turn off the error message so the user doesn't see it
      CEAFMainFrame* pFrame = EAFGetMainFrame();
      pFrame->DisableFailCreateMessage();
      pFrame->CreateCanceled();

      AFX_MANAGE_STATE(AfxGetAppModuleState());
      AfxMessageBox(_T("There must be at least one report defined to create the report view."),MB_OK | MB_ICONEXCLAMATION);
   }

   std::_tstring rptName;
   if ( rptIdx == INVALID_INDEX )
   {
      // creating report with invalid index, this means we have to prompt for the
      // report
      if ( rptNames.size() == 1 )
      {
         rptName = rptNames[0];
      }
      else
      {
         CEAFSelectReportDlg dlg(rptNames);
         if ( dlg.DoModal() == IDOK )
         {
            rptName = dlg.m_ReportName;
         }
         else
         {
            // the user cancelled the report creation because he failed to
            // select a report (ie. the Cancel buttow was pressed)

            // The view creation must fail and this is intentional
            // Turn off the error message so the user doesn't see it
            CEAFMainFrame* pFrame = EAFGetMainFrame();
            pFrame->DisableFailCreateMessage();
            m_pReportSpec = boost::shared_ptr<CReportSpecification>();
            m_pRptSpecBuilder = boost::shared_ptr<CReportSpecificationBuilder>();
            return;
         }
      }
   }
   else
   {
      ATLASSERT( 0 <= rptIdx && rptIdx < (CollectionIndexType)rptNames.size() );
      rptName = rptNames[rptIdx];
   }

   boost::shared_ptr<CReportBuilder> pRptBuilder = GetReportBuilder(rptName);
   CReportDescription rptDesc = pRptBuilder->GetReportDescription();

   m_pRptSpecBuilder = pRptBuilder->GetReportSpecificationBuilder();
   if ( bPromptForSpec )
   {
      m_pReportSpec = m_pRptSpecBuilder->CreateReportSpec(rptDesc,m_pReportSpec);
   }
   else
   {
      m_pReportSpec = m_pRptSpecBuilder->CreateDefaultReportSpec(rptDesc);
   }

   if ( m_pReportSpec == NULL )
   {
      // the user probably cancelled the report creation because he pressed the Cancel button
      // in the report specification dialog

      // The view creation must fail and this is intentional
      // Turn off the error message so the user doesn't see it
      CEAFMainFrame* pFrame = EAFGetMainFrame();
      pFrame->DisableFailCreateMessage();
      pFrame->CreateCanceled();
   }
}

HRESULT CEAFReportView::UpdateReportBrowser(CReportHint* pHint)
{
   if ( m_pReportSpec == NULL )
      return S_OK;

   HRESULT hr = m_pReportSpec->Validate();
   if ( FAILED(hr) )
      return hr;

   try
   {
      m_bUpdateInProgress = true;
      m_bUpdateError = false;
      m_bNoBrowser = false;

      Invalidate();
      UpdateWindow();


      // All the chapter builders get called from here... this is where all the
      // work related to generating the content of the report happens

      // if we already have a report browser, just refresh the report
      if ( m_pReportBrowser )
      {
         boost::shared_ptr<CReportBuilder> pBuilder = GetReportBuilder( m_pReportSpec->GetReportName() );

         // It is possible for the report builder to be deleted dynamically (e.g., if it is a custom report)
         if (!pBuilder)
         {
            m_ErrorMsg = _T("The report specified when creating this window no longer exists. Please close this window.");
            m_bUpdateError = true;

            if ( m_pBtnEdit->GetSafeHwnd() )
               m_pBtnEdit->ShowWindow(SW_HIDE);

            // delete the report browser because what ever it is displaying is totally invalid
            // also need to elimintate it so that we can draw the error message on the view window itself
            m_pReportBrowser = boost::shared_ptr<CReportBrowser>();
            return E_FAIL;
         }

         if ( pBuilder->NeedsUpdate(pHint,m_pReportSpec) )
         {
            boost::shared_ptr<rptReport> pReport = pBuilder->CreateReport( m_pReportSpec );

            if ( m_pBtnEdit->GetSafeHwnd() )
               m_pBtnEdit->ShowWindow(SW_SHOW);

            m_pReportBrowser->UpdateReport( pReport, true );
         }
      }
      else
      {
         // create the report and browser
         m_pReportBrowser = CreateReportBrowser(GetSafeHwnd(),m_pReportSpec,m_pRptSpecBuilder);

        CreateEditButton();
      }
   }
   catch(...)
   {
      if ( m_pReportBrowser )
      {
         // delete the report browser because what ever it is displaying is totally invalid
         // also need to elimintate it so that we can draw the error message on the view window itself
         m_pReportBrowser = boost::shared_ptr<CReportBrowser>();
      }

      m_bUpdateInProgress = false;
      throw; // keep the exception moving
   }

   m_bUpdateInProgress = false;

   if ( m_pReportBrowser )
   {
      Invalidate();

      if ( m_pBtnEdit->GetSafeHwnd() )
         m_pBtnEdit->ShowWindow(SW_SHOW);

      // size the browser window to fill the view
      CRect rect;
      GetClientRect(&rect);
      OnSize(0,rect.Width(),rect.Height());
   }
   else
   {
      if ( m_pBtnEdit->GetSafeHwnd() ) 
         m_pBtnEdit->ShowWindow(SW_HIDE);

      m_bNoBrowser = true;
   }


   return S_OK;
}

void CEAFReportView::EditReport()
{
   if ( m_pReportBrowser->Edit(false) ) // just edit, don't update... we need to wrap a progress window around the updating
   {
      // returning false means the user cancelled the edit
      RefreshReport();
   }
}

void CEAFReportView::RefreshReport()
{
   m_pReportSpec = m_pReportBrowser->GetReportSpecification();

   boost::shared_ptr<CReportBuilder> pRptBuilder = GetReportBuilder(m_pReportSpec->GetReportName());

   boost::shared_ptr<rptReport> pReport = pRptBuilder->CreateReport( m_pReportSpec );
   m_pReportBrowser->UpdateReport(pReport,true);

   UpdateViewTitle();
}

void CEAFReportView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

   if ( m_pReportBrowser )
   {
      m_pReportBrowser->Size( CSize(cx,cy) );
   }

   if ( m_pBtnEdit->GetSafeHwnd() )
      m_pBtnEdit->SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
}

void CEAFReportView::OnFilePrint() 
{
   ASSERT(m_pReportBrowser);
   m_pReportBrowser->Print(TRUE);
}

void CEAFReportView::OnToolbarPrint() 
{
   ASSERT(m_pReportBrowser);
   m_pReportBrowser->Print(FALSE);
}

void CEAFReportView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable( m_pReportBrowser == NULL ? FALSE : TRUE );
}

void CEAFReportView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   if ( m_bIsNewReport )
      return; // this the OnUpdate that comes from OnInitialUpdate() ... nothing to do here

   CView::OnUpdate( pSender, lHint, pHint ); // base class

   if ( lHint == EAF_HINT_UPDATEERROR )
   {
      CString* pmsg = (CString*)pHint;
      m_ErrorMsg = *pmsg;
      m_bUpdateError = true;

      if ( m_pBtnEdit->GetSafeHwnd() )
         m_pBtnEdit->ShowWindow(SW_HIDE);

      // delete the report browser because what ever it is displaying is totally invalid
      // also need to elimintate it so that we can draw the error message on the view window itself
      m_pReportBrowser = boost::shared_ptr<CReportBrowser>();

      Invalidate();
      UpdateWindow();
      return;
   }

   CEAFDocument* pDoc = (CEAFDocument*)GetDocument();
   CEAFStatusCenter& statusCenter = pDoc->GetStatusCenter();

   if ( statusCenter.GetSeverity() == eafTypes::statusError )
   {
      m_bUpdateError = true;
      m_ErrorMsg = _T("Errors exist that prevent analysis. Review the errors posted in the status center for more information");

      if ( m_pBtnEdit->GetSafeHwnd() )
         m_pBtnEdit->ShowWindow(SW_HIDE);

      // delete the report browser because what ever it is displaying is totally invalid
      // also need to elimintate it so that we can draw the error message on the view window itself
      m_pReportBrowser = boost::shared_ptr<CReportBrowser>();

      Invalidate();
      UpdateWindow();

      return;
   }

   // Something has changed to invalidate the report
   m_bInvalidReport = true;

   std::auto_ptr<CReportHint> pRptHint( TranslateHint(pSender,lHint,pHint) );
   UpdateNow(pRptHint.get());
}

CReportHint* CEAFReportView::TranslateHint(CView* pSender, LPARAM lHint, CObject* pHint)
{
   return NULL;
}

void CEAFReportView::UpdateNow(CReportHint* pHint)
{
   if ( CEAFReportView::ms_bIsUpdatingReport )
      return;

   CEAFReportView::ms_bIsUpdatingReport = true;

   if ( m_bInvalidReport )
   {
      try
      {
         HRESULT hr = UpdateReportBrowser(pHint);
         if ( FAILED(hr)  )
         {
            if ( m_bNoBrowser )
            {
               AfxMessageBox( IDS_E_NOBROWSER );
            }
         }
         else
         {
            m_bInvalidReport = false;
         }

         UpdateViewTitle();
      }
      catch(...)
      {
         CEAFReportView::ms_bIsUpdatingReport = false;
         throw;
      }
   }

   CEAFReportView::ms_bIsUpdatingReport = false;
}

void CEAFReportView::OnInitialUpdate() 
{
   m_bIsNewReport = true;

   try
   {
      CDocument* pDoc = GetDocument();
      CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();
      ASSERT( pDocTemplate->IsKindOf(RUNTIME_CLASS(CEAFDocTemplate)) );

      CEAFDocTemplate* pTemplate = (CEAFDocTemplate*)pDocTemplate;
      CEAFReportViewCreationData* pCreateData = (CEAFReportViewCreationData*)pTemplate->GetViewCreationData();
      ASSERT(pCreateData != NULL);

      m_pReportBuilderMgr = pCreateData->m_pReportBuilderMgr;
      m_pRptMgr = pCreateData->m_pRptMgr;
      ATLASSERT(m_pReportBuilderMgr != NULL || m_pRptMgr != NULL); // one of these should not be NULL

      CollectionIndexType rptIdx = pCreateData->m_RptIdx;
      if ( pCreateData->m_pRptSpecification )
      {
         if ( pCreateData->m_bInitializeOnly )
            InitReport(pCreateData->m_pRptSpecification,pCreateData->m_pRptSpecificationBuilder);
         else
            CreateReport(rptIdx,pCreateData->m_pRptSpecification,pCreateData->m_pRptSpecificationBuilder);
      }
      else
      {
         bool bPromptForSpec = pCreateData->m_bPromptForSpec;
         CreateReport(rptIdx,bPromptForSpec);
      }

      CView::OnInitialUpdate();
   }
   catch(...)
   {
      m_bIsNewReport = false; // no longer creating a new report
      throw; // keep the exception moving
   }

   m_bIsNewReport = false;
}

void CEAFReportView::UpdateViewTitle()
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   if ( m_pReportSpec == NULL )
   {
      SetWindowText(_T("Report View"));
   }
   else
   {
      CString strTitle( m_pReportSpec->GetReportTitle().c_str() );
	   SetWindowText(strTitle);
   }

   CFrameWnd* pFrame = GetParentFrame();
   pFrame->OnUpdateFrameTitle(TRUE);

   CDocument* pDoc = GetDocument();
   pDoc->UpdateFrameCounts();
}

void CEAFReportView::OnCmenuSelected(UINT id)
{
  UINT cmd = id-CCS_CMENU_BASE ;

  switch(cmd)
  {
  case CCS_RB_EDIT:
     EditReport();
     break;

  case CCS_RB_FIND:
     m_pReportBrowser->Find();
     break;

  case CCS_RB_SELECT_ALL:
     m_pReportBrowser->SelectAll();
     break;
  case CCS_RB_PRINT:
     m_pReportBrowser->Print(true);
     break;

  case CCS_RB_REFRESH:
     m_pReportBrowser->Refresh();
     break;

  case CCS_RB_VIEW_SOURCE:
     m_pReportBrowser->ViewSource();
     break;

  case CCS_RB_VIEW_BACK:
     m_pReportBrowser->Back();
     break;

  case CCS_RB_VIEW_FORWARD:
     m_pReportBrowser->Forward();
     break;

  default:
     // must be a toc anchor
     CHECK(cmd>=CCS_RB_TOC);
     m_pReportBrowser->NavigateAnchor(cmd-CCS_RB_TOC);
  }
}


BOOL CEAFReportView::PreTranslateMessage(MSG* pMsg) 
{
   if (pMsg->message == WM_KEYDOWN) 
   {
      if (pMsg->wParam =='f' || pMsg->wParam =='F')
      {
         // ctrl - F = Find
         if (::GetKeyState(VK_CONTROL))
         {
            m_pReportBrowser->Find();
            return TRUE;
         }
      }
   }

	return CView::PreTranslateMessage(pMsg);
}

BOOL CEAFReportView::OnEraseBkgnd(CDC* pDC)
{
   CRect rect;
   GetClientRect(&rect);

   CBrush brush;
   brush.Attach( GetSysColorBrush(COLOR_BTNFACE) ); // dialog background color
   brush.UnrealizeObject();
   CBrush* pOldBrush = pDC->SelectObject(&brush);

   CPen pen(PS_SOLID,1, GetSysColor(COLOR_BTNFACE) );
   CPen* pOldPen = pDC->SelectObject(&pen);

   pDC->Rectangle(rect);
   
   pDC->SelectObject(pOldBrush);
   pDC->SelectObject(pOldPen);

   return TRUE;
}

BOOL CEAFReportView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.style |= WS_CLIPCHILDREN;

   return CView::PreCreateWindow(cs);
}

void CEAFReportView::CreateEditButton()
{
   CWnd* pWeb = m_pReportBrowser->GetBrowserWnd();

   CRect rect(0,0,50,21);
   m_pBtnEdit->Create(_T("Edit"),WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON | BS_TEXT, rect, pWeb, IDC_EDIT);
   m_btnFont.Attach( GetStockObject(DEFAULT_GUI_FONT) );
   m_pBtnEdit->SetFont(&m_btnFont);
}

std::vector<std::_tstring> CEAFReportView::GetReportNames()
{
   if ( m_pReportBuilderMgr )
      return m_pReportBuilderMgr->GetReportNames();
   else
      return m_pRptMgr->GetReportNames();
}

boost::shared_ptr<CReportBuilder> CEAFReportView::GetReportBuilder(const std::_tstring& strRptName)
{
   if ( m_pReportBuilderMgr )
      return m_pReportBuilderMgr->GetReportBuilder(strRptName);
   else
      return m_pRptMgr->GetReportBuilder(strRptName);
}

boost::shared_ptr<CReportBrowser> CEAFReportView::CreateReportBrowser(HWND hwndParent,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder)
{
   if ( m_pReportBuilderMgr )
      return m_pReportBuilderMgr->CreateReportBrowser(hwndParent,pRptSpec,pRptSpecBuilder);
   else
      return m_pRptMgr->CreateReportBrowser(hwndParent,pRptSpec,pRptSpecBuilder);
}

void CEAFReportView::NotifyReportButtonWasClicked()
{
   EditReport();
}

boost::shared_ptr<CReportSpecification> CEAFReportView::GetReportSpecification()
{
   return m_pReportSpec;
}
