// ArpNotice.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ArpNotice.h"
#include "MainFrm.h"
#include "ArpNoticeDoc.h"
#include "ArpNoticeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeApp

BEGIN_MESSAGE_MAP(CArpNoticeApp, CWinApp)
	//{{AFX_MSG_MAP(CArpNoticeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_HELP_LEGAL, OnHelpLegal)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeApp construction

CArpNoticeApp::CArpNoticeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CArpNoticeApp object

CArpNoticeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeApp initialization

BOOL CArpNoticeApp::InitInstance()
{
   ::CoInitialize( NULL ); // Must initalize the COM DLL's
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


   //////////////////////////////////////////////////////////
   // Read Registry Settings
	SetRegistryKey(_T("ARP Notice Example"));
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
   CString strLegalNotice = GetProfileString(_T("Settings"),_T("LegalNotice"),_T("On"));
   if ( strLegalNotice.CompareNoCase(_T("On")) == 0 )
      m_bShowLegalNotice = VARIANT_TRUE;
   else
      m_bShowLegalNotice = VARIANT_FALSE;

   //////////////////////////////////////////////////////////
   // Display Legal Notice
   if ( ShowLegalNoticeAtStartup() == atReject )
      return FALSE; // License as not accepted
   



	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CArpNoticeDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CArpNoticeView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CArpNoticeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CArpNoticeApp message handlers

AcceptanceType CArpNoticeApp::ShowLegalNoticeAtStartup(void)
{
   if ( m_bShowLegalNotice == VARIANT_TRUE )
   {
      return ShowLegalNotice(VARIANT_TRUE);
   }

   return atAccept;
}

AcceptanceType CArpNoticeApp::ShowLegalNotice(VARIANT_BOOL bGiveChoice)
{
   CComPtr<IARPNotice> pNotice;
   pNotice.CoCreateInstance(CLSID_ARPNotice);
   pNotice->put_ShowAgain( m_bShowLegalNotice );
   AcceptanceType accept;
   pNotice->Show(bGiveChoice,ltAROSL,&accept);

   pNotice->get_ShowAgain(&m_bShowLegalNotice);

   return accept;
}

int CArpNoticeApp::ExitInstance() 
{
   // Save the current state of the Legal Notice
   VERIFY(WriteProfileString( _T("Settings"),_T("LegalNotice"),m_bShowLegalNotice == VARIANT_TRUE ? _T("On") : _T("Off") ));
	
	return CWinApp::ExitInstance();
}

void CArpNoticeApp::OnHelpLegal() 
{
   ShowLegalNotice(VARIANT_FALSE);
   ::CoUninitialize(); // Done using COM
}
