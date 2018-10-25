// EditMemberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "EditMemberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditMemberDlg dialog


CEditMemberDlg::CEditMemberDlg(IFem2dModel* pModel,BOOL bMbrIDReadOnly,CWnd* pParent /*=NULL*/)
	: CDialog(CEditMemberDlg::IDD, pParent)
{
   m_Model = pModel;
   m_bMbrIDReadOnly = bMbrIDReadOnly;

	//{{AFX_DATA_INIT(CEditMemberDlg)
	m_EA = 0.0;
	m_EI = 0.0;
	m_EndJoint = -1;
	m_MbrID = 0;
	m_bReleaseMzAtEnd = FALSE;
	m_bReleaseMzAtStart = FALSE;
	m_StartJoint = -1;
	//}}AFX_DATA_INIT
}


void CEditMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditMemberDlg)
	DDX_Text(pDX, IDC_EA, m_EA);
	DDX_Text(pDX, IDC_EI, m_EI);
	DDX_CBIndex(pDX, IDC_ENDJNT, m_EndJoint);
	DDX_Text(pDX, IDC_MBRID, m_MbrID);
	DDX_Check(pDX, IDC_RELEASE_MZ_END, m_bReleaseMzAtEnd);
	DDX_Check(pDX, IDC_RELEASE_MZ_START, m_bReleaseMzAtStart);
	DDX_CBIndex(pDX, IDC_STARTJNT, m_StartJoint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditMemberDlg, CDialog)
	//{{AFX_MSG_MAP(CEditMemberDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditMemberDlg message handlers

BOOL CEditMemberDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

   CComboBox* pStart = (CComboBox*)GetDlgItem(IDC_STARTJNT);
   CComboBox* pEnd = (CComboBox*)GetDlgItem(IDC_ENDJNT);

   CComPtr<IFem2dJointCollection> joints;
   m_Model->get_Joints(&joints);

   CollectionIndexType count;
   joints->get_Count(&count);
   for ( CollectionIndexType i = 0; i < count; i++ )
   {
      CComPtr<IFem2dJoint> jnt;
      joints->get_Item(i,&jnt);

      JointIDType ID;
      jnt->get_ID(&ID);

      CString strJntID;
      strJntID.Format(_T("%d"),ID);
      pStart->AddString(strJntID);
      pEnd->AddString(strJntID);
   }

   if ( pStart->SetCurSel(m_StartJoint) == CB_ERR )
      pStart->SetCurSel(0);

   if ( pEnd->SetCurSel(m_EndJoint) == CB_ERR )
      pEnd->SetCurSel(0);

   // Make the member id edit control read only
   CEdit* pEdit = (CEdit*)GetDlgItem(IDC_MBRID);
   pEdit->SetReadOnly(m_bMbrIDReadOnly);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
