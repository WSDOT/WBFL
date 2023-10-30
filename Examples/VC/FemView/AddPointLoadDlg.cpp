// AddPointLoadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FEA2D.h"
#include "AddPointLoadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddPointLoadDlg dialog


CAddPointLoadDlg::CAddPointLoadDlg(IFem2dModel* pModel,BOOL bMbrIDReadOnly,CWnd* pParent /*=NULL*/)
	: CDialog(CAddPointLoadDlg::IDD, pParent)
{
   m_Model = pModel;
   m_bMbrIDReadOnly = bMbrIDReadOnly;

	//{{AFX_DATA_INIT(CAddPointLoadDlg)
	m_Fx = 0.0;
	m_Fy = 0.0;
	m_LoadingID = -1;
	m_Location = 0.0;
	m_MbrID = 0;
	m_Mz = 0.0;
	//}}AFX_DATA_INIT
}


void CAddPointLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddPointLoadDlg)
	DDX_Text(pDX, IDC_FX, m_Fx);
	DDX_Text(pDX, IDC_FY, m_Fy);
	DDX_CBIndex(pDX, IDC_LOADINGS, (int&)m_LoadingID);
	DDX_Text(pDX, IDC_LOCATION, m_Location);
	DDX_Text(pDX, IDC_MBRID, m_MbrID);
	DDX_Text(pDX, IDC_MZ, m_Mz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddPointLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CAddPointLoadDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddPointLoadDlg message handlers

BOOL CAddPointLoadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   // Populate the loading combobox
   CComboBox* pLoadings = (CComboBox*)GetDlgItem(IDC_LOADINGS);
   CComPtr<IFem2dLoadingCollection> loadings;
   m_Model->get_Loadings(&loadings);
   IndexType count;
   loadings->get_Count(&count);
   for ( IndexType i = 0; i < count; i++ )
   {
      CComPtr<IFem2dLoading> loading;
      loadings->get_Item(i,&loading);

      CString strID;
      LoadCaseIDType ID;
      loading->get_ID(&ID);
      strID.Format(_T("%d"),ID);
      pLoadings->AddString(strID);
   }

   if ( pLoadings->SetCurSel((int)m_LoadingID) == CB_ERR )
      pLoadings->SetCurSel(0);

   // Make the member id edit control read only
   CEdit* pEdit = (CEdit*)GetDlgItem(IDC_MBRID);
   pEdit->SetReadOnly(m_bMbrIDReadOnly);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
