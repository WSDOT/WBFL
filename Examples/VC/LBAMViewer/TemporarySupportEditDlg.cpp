// TemporarySupportEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LBAMViewer.h"
#include "TemporarySupportEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupportEditDlg dialog


CTemporarySupportEditDlg::CTemporarySupportEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTemporarySupportEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTemporarySupportEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTemporarySupportEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemporarySupportEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTemporarySupportEditDlg, CDialog)
	//{{AFX_MSG_MAP(CTemporarySupportEditDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupportEditDlg message handlers
