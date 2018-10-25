// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FEA2D.h"

#include "MainFrm.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
   IDS_INDICATOR_POINT,
   IDS_INDICATOR_POINT,
   IDS_INDICATOR_POINT,
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
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

   if ( !m_wndToolPalette.Create(this,IDD_TOOLS,CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR) )
   {
		TRACE0("Failed to create tool palette\n");
		return -1;		// fail to create
   }

   if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndToolPalette))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

   CComPtr<iTool> tool;
   ::CoCreateInstance(CLSID_Tool,NULL,CLSCTX_ALL,IID_iTool,(void**)&tool);
   tool->SetID(IDC_CONCLOAD_TOOL);
   tool->SetToolTipText("Create Point Load");
   m_wndToolPalette.AddTool(tool);

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

void CMainFrame::UpdateWorldPoint(double x,double y)
{
   CString strMsg;
   CString strX;
   CString strY;
   strX.Format("%6.3f",x);
   strY.Format("%6.3f",y);
   AfxFormatString2(strMsg,IDS_INDICATOR_WORLDPOINT,strX,strY);

   m_wndStatusBar.GetStatusBarCtrl().SetText(strMsg,3,0);
}

void CMainFrame::UpdateDevicePoint(long x,long y)
{
   CString strMsg;
   CString strX;
   CString strY;
   strX.Format("%d",x);
   strY.Format("%d",y);
   AfxFormatString2(strMsg,IDS_INDICATOR_DEVICEPOINT,strX,strY);

   m_wndStatusBar.GetStatusBarCtrl().SetText(strMsg,2,0);
}

void CMainFrame::UpdateLogicalPoint(long x,long y)
{
   CString strMsg;
   CString strX;
   CString strY;
   strX.Format("%d",x);
   strY.Format("%d",y);
   AfxFormatString2(strMsg,IDS_INDICATOR_LOGICALPOINT,strX,strY);

   m_wndStatusBar.GetStatusBarCtrl().SetText(strMsg,1,0);
}
