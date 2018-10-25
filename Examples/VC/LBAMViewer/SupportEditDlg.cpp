// SupportEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "SupportEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSupportEditDlg dialog


CSupportEditDlg::CSupportEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSupportEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSupportEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSupportEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSupportEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSupportEditDlg, CDialog)
	//{{AFX_MSG_MAP(CSupportEditDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSupportEditDlg message handlers
