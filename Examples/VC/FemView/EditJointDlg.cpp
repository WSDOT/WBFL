// EditJointDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "EditJointDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditJointDlg dialog


CEditJointDlg::CEditJointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditJointDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditJointDlg)
	m_bSupportMz = FALSE;
	m_bSupportFx = FALSE;
	m_bSupportFy = FALSE;
	m_X = 0.0;
	m_Y = 0.0;
	m_JntID = 0;
	//}}AFX_DATA_INIT
}


void CEditJointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditJointDlg)
	DDX_Check(pDX, IDC_SUPPORT_MZ, m_bSupportMz);
	DDX_Check(pDX, IDC_SUPPORT_FX, m_bSupportFx);
	DDX_Check(pDX, IDC_SUPPORT_FY, m_bSupportFy);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_JNTID, m_JntID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditJointDlg, CDialog)
	//{{AFX_MSG_MAP(CEditJointDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditJointDlg message handlers
