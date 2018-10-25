// SysUnitsTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SysUnitsTest.h"
#include "SysUnitsTestDlg.h"

#include <Units\SysUnitsMgr.h>
#include <Units\Measure.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysUnitsTestDlg dialog

CSysUnitsTestDlg::CSysUnitsTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysUnitsTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysUnitsTestDlg)
	m_BaseLength = 1;
	m_UnitTagForCurrentBase = _T(unitSysUnitsMgr::GetLengthUnit().UnitTag().c_str());
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSysUnitsTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysUnitsTestDlg)
	DDX_Radio(pDX, IDC_BASE_LENGTH, m_BaseLength);
	DDX_Text(pDX, IDC_CURRENT_BASE, m_UnitTagForCurrentBase);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSysUnitsTestDlg, CDialog)
	//{{AFX_MSG_MAP(CSysUnitsTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BASE_LENGTH, OnBaseLengthChanged)
	ON_BN_CLICKED(IDC_RADIO2, OnBaseLengthChanged)
	ON_BN_CLICKED(IDC_BUTTON, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysUnitsTestDlg message handlers

BOOL CSysUnitsTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSysUnitsTestDlg::OnPaint() 
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
HCURSOR CSysUnitsTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSysUnitsTestDlg::OnBaseLengthChanged() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE );
   if ( m_BaseLength == 0 )
      unitSysUnitsMgr::SetLengthUnit( unitMeasure::Feet );
   else
      unitSysUnitsMgr::SetLengthUnit( unitMeasure::Meter );

   m_UnitTagForCurrentBase = unitSysUnitsMgr::GetLengthUnit().UnitTag().c_str();

   UpdateData( FALSE );
}

void CSysUnitsTestDlg::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	OnBaseLengthChanged();
}
