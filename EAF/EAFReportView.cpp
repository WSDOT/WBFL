// EAFReportView.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFReportView.h>
#include <EAF\EAFBrokerDocument.h>
#include <EAF\EAFMainFrame.h>
#include <ReportManager\ReportManager.h>
#include <AgentTools.h>
#include <IReportManager.h>
#include <Reporter\Report.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView

IMPLEMENT_DYNAMIC(CEAFReportView, CView)

CEAFReportView::CEAFReportView()
{
   m_bInitialUpdate = false;
}

CEAFReportView::~CEAFReportView()
{
}


BEGIN_MESSAGE_MAP(CEAFReportView, CView)
	//{{AFX_MSG_MAP(CEAFReportView)
	ON_WM_SIZE()
	ON_WM_CREATE()
   ON_COMMAND(ID_FILE_PRINT,&CEAFReportView::OnFilePrint)
   ON_UPDATE_COMMAND_UI(ID_FILE_PRINT,&CEAFReportView::OnUpdateFilePrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEAFReportView::OnInitialUpdate()
{
   m_bInitialUpdate = true;
   CView::OnInitialUpdate();
   m_bInitialUpdate = false;
}

void CEAFReportView::OnUpdate(CView* pSender,LPARAM lHint,CObject* pHint)
{
   CView::OnUpdate(pSender,lHint,pHint);

   // the report browser (IE) throws an exception if this is called during
   // OnInitialUpdate. If this call comes from OnInitialUpdate(), just leave
   if ( m_bInitialUpdate )
      return;

   if ( m_pReportSpec && m_pReportBrowser )
   {
      RefreshReport();
   }
}

void CEAFReportView::RefreshReport()
{
   CEAFBrokerDocument* pDoc = (CEAFBrokerDocument*)GetDocument();

   _COM_SMARTPTR_TYPEDEF(IBroker,IID_IBroker);
   IBrokerPtr pBroker;
   pDoc->GetBroker(&pBroker);
   ASSERT( pBroker != NULL );

   // get the IReportManager interface
   GET_IFACE2(pBroker,IReportManager,pRptMgr);
   ASSERT( pRptMgr != NULL ); // The ReportManagerAgent isn't in your project... and it must be!

   // refresh the report
   boost::shared_ptr<CReportBuilder> pBuilder = pRptMgr->GetReportBuilder( m_pReportSpec->GetReportName() );
   boost::shared_ptr<rptReport> pReport = pBuilder->CreateReport( m_pReportSpec );
   m_pReportBrowser->UpdateReport( pReport, true );
}

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView drawing

void CEAFReportView::OnDraw(CDC* pDC)
{
   if ( !m_pReportBrowser )
   {
      OnDrawNoBrowser(pDC);
   }
}

void CEAFReportView::OnDrawNoBrowser(CDC* pDC)
{
   pDC->TextOut(0,0,"No report to display");
}

/////////////////////////////////////////////////////////////////////////////
// CEAFReportView diagnostics

#ifdef _DEBUG
void CEAFReportView::AssertValid() const
{
   // Make sure the module state is that for the CWinApp class
   // before diving down into MFC (if the module state isn't
   // correct, all sorts of asserts will fire)
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

void CEAFReportView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
   if ( m_pReportBrowser )
   {
      m_pReportBrowser->Size( GetBrowserSize(nType,cx,cy) );
   }
}

CSize CEAFReportView::GetBrowserSize(UINT nType, int cx, int cy)
{
   return CSize(cx,cy);
}


int CEAFReportView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   int result = CView::OnCreate(lpCreateStruct);
	if (result != 0)
		return result;
	

   // sub-classes implement CreateReportSpecification
   m_pReportSpec = CreateReportSpecification();

   if ( !m_pReportSpec )
   {
      CEAFMainFrame* pMainFrame = (CEAFMainFrame*)AfxGetMainWnd();
      ASSERT( pMainFrame->IsKindOf(RUNTIME_CLASS(CEAFMainFrame)) );
      pMainFrame->DisableFailCreateMessage();
      return -1;
   }

   m_pReportBrowser = CreateReportBrowser();

   return 0;
}

boost::shared_ptr<CReportBrowser> CEAFReportView::CreateReportBrowser()
{
   if ( m_pReportSpec == NULL )
      return boost::shared_ptr<CReportBrowser>();

   CEAFBrokerDocument* pDoc = (CEAFBrokerDocument*)GetDocument();
   ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CEAFBrokerDocument)) );

   _COM_SMARTPTR_TYPEDEF(IBroker,IID_IBroker);
   IBrokerPtr pBroker;
   pDoc->GetBroker(&pBroker);
   ASSERT( pBroker != NULL );

   // get the IReportManager interface
   GET_IFACE2(pBroker,IReportManager,pRptMgr);
   ASSERT( pRptMgr != NULL ); // The ReportManagerAgent isn't in your project... and it must be!

   // create the report and browser
   return pRptMgr->CreateReportBrowser(GetSafeHwnd(),m_pReportSpec);
}

void CEAFReportView::OnFilePrint()
{
   ASSERT(m_pReportBrowser);
	if (LOWORD(GetCurrentMessage()->wParam) == ID_FILE_PRINT_DIRECT)
      m_pReportBrowser->Print(FALSE);
   else
      m_pReportBrowser->Print(TRUE);
}

void CEAFReportView::OnUpdateFilePrint(CCmdUI* pUpdate)
{
   pUpdate->Enable( m_pReportBrowser == NULL ? FALSE : TRUE );
}
