// CreateLoadingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "CreateLoadingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateLoadingDlg dialog


CCreateLoadingDlg::CCreateLoadingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateLoadingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateLoadingDlg)
	m_ID = 0;
	//}}AFX_DATA_INIT
}


void CCreateLoadingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateLoadingDlg)
	DDX_Text(pDX, IDC_ID, m_ID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateLoadingDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateLoadingDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateLoadingDlg message handlers
