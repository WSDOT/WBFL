// TestProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestProgress.h"
#include "TestProgressDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



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

/////////////////////////////////////////////////////////////////////////////
// CTestProgressDlg dialog

CTestProgressDlg::CTestProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestProgressDlg::IDD, pParent),
     m_IsLogFileOpen(false)
{
	//{{AFX_DATA_INIT(CTestProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestProgressDlg)
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_FileNameEdit);
	DDX_Control(pDX, IDC_CHECK_FILENAME, m_CheckFileNameCtrl);
	DDX_Control(pDX, IDC_ENABLE_GAUGE, m_EnableGaugeCtrl);
	DDX_Control(pDX, IDC_ENABLE_CANCEL, m_EnableCancelCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CTestProgressDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST1, OnTest1)
	ON_BN_CLICKED(IDC_CHECK_FILENAME, OnCheckFilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestProgressDlg message handlers

BOOL CTestProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
   m_ProgressMon.CoCreateInstance(CLSID_ProgressMonitorWindow);

   m_EnableGaugeCtrl.SetCheck(1);
   m_EnableCancelCtrl.SetCheck(1);

   m_FileNameEdit.SetWindowText("ProgressLog.txt");
   UpdateLogFile();
   
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestProgressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestProgressDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestProgressDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestProgressDlg::OnTest1() 
{
   HRESULT hr;
   CComQIPtr<IProgressMonitor> ipm(m_ProgressMon);

   // create our test process
   CComPtr<IBogusProgressTester> tester;
   tester.CoCreateInstance(CLSID_BogusProgressTester);
   CComQIPtr<ISupportProgressMonitor> ispm(tester);
   ispm->InitializeProgressMonitor(ipm, 2);

   // set some settings
   m_ProgressMon->put_HasGauge( m_EnableGaugeCtrl.GetCheck()==0 ? VARIANT_FALSE : VARIANT_TRUE );
   m_ProgressMon->put_HasCancel( m_EnableCancelCtrl.GetCheck()==0 ? VARIANT_FALSE : VARIANT_TRUE );

   // deal with opening our log file
   CComQIPtr<ILogProgressToFile> progress_log(m_ProgressMon);
   if (m_CheckFileNameCtrl.GetCheck()!=0)
   {
      CString file_name;
      m_FileNameEdit.GetWindowText(file_name);
      if (file_name.GetLength()>0)
      {
         CComBSTR bfn(file_name);
         hr = progress_log->OpenLogFile(bfn);
         if (FAILED(hr))
         {
            AfxMessageBox("Failed to Open Log File - Aborted");
            return;
         }
      }
      else
      {
         AfxMessageBox("Log File Name May Not Be Blank - Aborted");
         return;
      }
   }

   // show our dialog and run test
   m_ProgressMon->Show(CComBSTR("Test Start Message"));
   tester->RunTest();
   m_ProgressMon->Hide();

   // close log file
   if (m_CheckFileNameCtrl.GetCheck()!=0)
   {
      hr = progress_log->CloseLogFile();
      if (FAILED(hr))
      {
         AfxMessageBox("Failed to Close Log File");
      }
   }
}

void CTestProgressDlg::OnCheckFilename() 
{
	UpdateLogFile();
}

void CTestProgressDlg::UpdateLogFile() 
{
   if (m_CheckFileNameCtrl.GetCheck()!=0)
   {
      m_FileNameEdit.EnableWindow(TRUE);
   }
   else
   {
      m_FileNameEdit.EnableWindow(FALSE);
   }
}