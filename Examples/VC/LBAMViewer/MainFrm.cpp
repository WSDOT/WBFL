// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LBAMViewer.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "LBAMViewerDoc.h"
#include "ReactionReportDlg.h"
#include "ReactionReportBuilder.h"
#include "DataSetBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_STAGE_COMBO, OnSelchangeStageCombo)
	ON_CBN_SELCHANGE(IDC_RESPONSETYPE_COMBO, OnSelchangeResponseTypeCombo)
   ON_BN_CLICKED( IDC_CUMMULATIVE, OnCummulativeClicked )
   ON_BN_CLICKED( IDC_GRID, OnGridClicked )
	ON_COMMAND(IDM_REACTION_REPORT, OnReactionReport)
	ON_UPDATE_COMMAND_UI(IDM_REACTION_REPORT, OnUpdateReactionReport)
	ON_COMMAND(IDM_IG_POIS, OnInternallyGeneratedPoisClicked)
	ON_UPDATE_COMMAND_UI(IDM_IG_POIS, OnUpdateInternallyGeneratedPois)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this, IDD_LOAD_TOOLBAR, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this)         ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnSelchangeStageCombo() 
{
	CString strText;
	CString strItem;
	CComboBox* pCBox = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_STAGE_COMBO);
	int nIndex = pCBox->GetCurSel();
	if (nIndex == CB_ERR)
		return;
	pCBox->GetLBText(nIndex, strItem);

   CMDIChildWnd *pChild = this->MDIGetActive();
   CDocument *pDoc = pChild->GetActiveDocument();
   CLBAMViewerDoc* pVdoc = dynamic_cast<CLBAMViewerDoc*>(pDoc);
   ATLASSERT(pVdoc);

   pVdoc->SetStage(strItem);
}

void CMainFrame::OnCummulativeClicked() 
{
	CButton* pCB = (CButton*)m_wndDlgBar.GetDlgItem(IDC_CUMMULATIVE);
   BOOL do_accum = pCB->GetCheck()==0 ? FALSE : TRUE;

   CMDIChildWnd *pChild = this->MDIGetActive();
   CDocument *pDoc = pChild->GetActiveDocument();
   CLBAMViewerDoc* pVdoc = dynamic_cast<CLBAMViewerDoc*>(pDoc);
   ATLASSERT(pVdoc);

   pVdoc->SetAccumulateResults(do_accum);
}

void CMainFrame::OnGridClicked() 
{
	CButton* pCB = (CButton*)m_wndDlgBar.GetDlgItem(IDC_GRID);
   BOOL do_show_grid = pCB->GetCheck()==0 ? FALSE : TRUE;

   CMDIChildWnd *pChild = this->MDIGetActive();
   CDocument *pDoc = pChild->GetActiveDocument();
   CLBAMViewerDoc* pVdoc = dynamic_cast<CLBAMViewerDoc*>(pDoc);
   ATLASSERT(pVdoc);

   pVdoc->SetShowGrid(do_show_grid);
}


void CMainFrame::OnSelchangeResponseTypeCombo() 
{
	CString strText;
	CString strItem;
	CComboBox* pCBox = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_RESPONSETYPE_COMBO);
	int nIndex = pCBox->GetCurSel();
	if (nIndex == CB_ERR)
		return;


   CMDIChildWnd *pChild = this->MDIGetActive();
   CDocument *pDoc = pChild->GetActiveDocument();
   CLBAMViewerDoc* pVdoc = dynamic_cast<CLBAMViewerDoc*>(pDoc);
   ATLASSERT(pVdoc);

   _ASSERT(nIndex>-1 && nIndex<=CLBAMViewerDoc::rtStress); // new index value?

   pVdoc->SetResponseType((CLBAMViewerDoc::ResponseType)nIndex);
}

void CMainFrame::UpdateToolBar()
{
   HRESULT hr;
   CMDIChildWnd *pChild = this->MDIGetActive();
   CDocument *pDoc = pChild->GetActiveDocument();
   CLBAMViewerDoc* pVdoc = dynamic_cast<CLBAMViewerDoc*>(pDoc);
   ATLASSERT(pVdoc);

   // view got switched - updated lists in toolbars
   // stages
   CString curr_stage = pVdoc->GetStage();                // current stage
   CComPtr<IStages> stages;
   hr = pVdoc->m_pModel->get_Stages(&stages); // list of stages in document

	CComboBox* pStgCBox = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_STAGE_COMBO);
   pStgCBox->ResetContent();

   StageIndexType nstages;
   hr = stages->get_Count(&nstages);
   if (nstages != 0)
   {
      pStgCBox->EnableWindow(TRUE);

      for (StageIndexType istg=0; istg<nstages; istg++)
      {
         CComBSTR bstg;
         CComPtr<IStage> stage;
         hr = stages->get_Item(istg,&stage);
         hr = stage->get_Name(&bstg);
         CString stg( bstg );
         pStgCBox->AddString( stg );
      }

      if (curr_stage.GetLength() != 0)
      {
         int st = pStgCBox->SelectString(0, curr_stage);
         if (st==CB_ERR)
         {
            ATLASSERT(0); // should not happen, unless stage editing capabilities have been added to app
         }
      }
      else
      {
         // no stage is selected - should not happen
         ATLASSERT(0);
      }
   }
   else
   {
      pStgCBox->EnableWindow(FALSE);
   }

   /// response type
	CComboBox* pRtCBox = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_RESPONSETYPE_COMBO);
   pRtCBox->EnableWindow(TRUE);

   CLBAMViewerDoc::ResponseType rt = pVdoc->GetResponseType();
   int st = pRtCBox->SetCurSel((int)rt);
   if (st==CB_ERR)
   {
      ATLASSERT(0); // should not happen, unless LoadGroup editing capabilities have been added to app
   }

   // accumulate results
	CButton* pAcChkBox = (CButton*)m_wndDlgBar.GetDlgItem(IDC_CUMMULATIVE);
   pAcChkBox->EnableWindow(TRUE);
   BOOL acc = pVdoc->GetAccumulateResults();
   if (acc)
      pAcChkBox->SetCheck(BST_CHECKED);
   else
      pAcChkBox->SetCheck(BST_UNCHECKED);

   // show grid
	CButton* pSgChkBox = (CButton*)m_wndDlgBar.GetDlgItem(IDC_GRID);
   pSgChkBox->EnableWindow(TRUE);
   BOOL sg = pVdoc->GetShowGrid();
   if (sg)
      pSgChkBox->SetCheck(BST_CHECKED);
   else
      pSgChkBox->SetCheck(BST_UNCHECKED);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
   return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnReactionReport() 
{
   HRESULT hr;
   char cr[] = "\\par ";
   CReactionReportDlg dlg;
   dlg.m_Stream<<"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fmodern\\fprq1\\fcharset0 Courier New;}}\\viewkind4\\uc1\\pard\\f0\\fs20 ";
   dlg.m_Stream <<"REACTION REPORT FOR SELECTED LOADINGS"<<cr;

   // get some needed information
   CChildFrame* pChild = (CChildFrame*)this->MDIGetActive();
   CDocument *pVDoc = pChild->GetActiveDocument();
   CLBAMViewerDoc* pDoc = dynamic_cast<CLBAMViewerDoc*>(pVDoc);
   ATLASSERT(pDoc);

   CComBSTR curr_stg = pDoc->GetStage();
   if (curr_stg.Length()==0)
      return;

   BOOL is_cumm = pDoc->GetAccumulateResults();
   ResultsSummationType summ_type = is_cumm ? rsCumulative : rsIncremental;

   CLBAMViewerDoc::ResponseType curr_rt = pDoc->GetResponseType();

   // get list of all supports in model
   CComPtr<ILongArray> support_ids;
   CComPtr<ILBAMFactory> gen_util;
   hr = gen_util.CoCreateInstance(CLSID_LRFDFactory);
   ATLASSERT(SUCCEEDED(hr));
   hr = gen_util->GetSupportIDsForStage(pDoc->m_pModel, curr_stg, &support_ids);
   ATLASSERT(SUCCEEDED(hr));

   CollectionIndexType supsiz;
   support_ids->get_Count(&supsiz);
   if (supsiz==0)
   {
      ATLASSERT(0);
      return;
   }

   // see how many data builders we have and loop over them to create report;
   long num_ds = pChild->GetNumDataSetBuilders();
   for (long ids=0; ids<num_ds; ids++)
   {
      iDataSetBuilder* pbld = pChild->GetDataSetBuilder(ids);

      // Cross cast data set builder to reaction report builder
      iReactionReportBuilder* prb = dynamic_cast<iReactionReportBuilder*>(pbld);

      if (prb!=NULL)
      {
         prb->BuildReactionReport(support_ids, curr_stg, curr_rt, summ_type, dlg.m_Stream);
      }
      else
      {
         dlg.m_Stream <<"Reactions not supported for selected loading"<<cr;
      }
   }

   dlg.m_Stream<<"}";

   dlg.DoModal();

}

void CMainFrame::OnUpdateReactionReport(CCmdUI* pCmdUI) 
{
   CChildFrame* pChild = (CChildFrame*)this->MDIGetActive();
   if (pChild==NULL)
   {
      pCmdUI->Enable(FALSE);
   }
   else
   {
      pCmdUI->Enable(pChild->GetNumDataSetBuilders()>0);
   }
}

void CMainFrame::OnInternallyGeneratedPoisClicked() 
{
   // get some needed information
   CChildFrame* pChild = (CChildFrame*)this->MDIGetActive();
   CDocument *pVDoc = pChild->GetActiveDocument();
   CLBAMViewerDoc* pDoc = dynamic_cast<CLBAMViewerDoc*>(pVDoc);
   ATLASSERT(pDoc);

   // toggle 
   BOOL sip = pDoc->GetShowInternalPOIs() ? FALSE : TRUE;
   pDoc->SetShowInternalPOIs(sip);

}

void CMainFrame::OnUpdateInternallyGeneratedPois(CCmdUI* pCmdUI) 
{
   CChildFrame* pChild = (CChildFrame*)this->MDIGetActive();
   if (pChild==NULL)
   {
      pCmdUI->Enable(FALSE);
   }
   else
   {
      CDocument *pVDoc = pChild->GetActiveDocument();
      CLBAMViewerDoc* pDoc = dynamic_cast<CLBAMViewerDoc*>(pVDoc);
      ATLASSERT(pDoc);

      pCmdUI->Enable(TRUE);

      BOOL sip = pDoc->GetShowInternalPOIs();
      pCmdUI->SetCheck(sip);
   }
}
