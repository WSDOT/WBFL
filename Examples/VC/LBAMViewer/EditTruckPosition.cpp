// EditTruckPosition.cpp : implementation file
//
#include "stdafx.h"
#include "EditTruckPosition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditTruckPosition dialog


CEditTruckPosition::CEditTruckPosition(CWnd* pParent /*=NULL*/)
	: CDialog(CEditTruckPosition::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditTruckPosition)
	m_TruckPosition = 0.0;
	m_VariableAxleSpacing = 0.0;
	m_ApplyImpact = FALSE;
	m_PivotAxleIndex = -1;
	//}}AFX_DATA_INIT
}


void CEditTruckPosition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditTruckPosition)
	DDX_Text(pDX, IDC_TRUCK_POSITION, m_TruckPosition);
	DDV_MinMaxDouble(pDX, m_TruckPosition, -1.e+031, 1.e+031);
	DDX_Text(pDX, IDC_VARIABLE_AXLE, m_VariableAxleSpacing);
	DDX_Check(pDX, IDC_APPLY_IMPACT, m_ApplyImpact);
	DDX_CBIndex(pDX, IDC_PIVOT_AXLE, m_PivotAxleIndex);

	//}}AFX_DATA_MAP

   if (m_IsVar)
   {
	   DDV_MinMaxDouble(pDX, m_VariableAxleSpacing, m_MinVarspcg, m_MaxVarspcg);
   }
   else
   {
      CWnd* pedit = this->GetDlgItem(IDC_VARIABLE_AXLE);
      pedit->EnableWindow(FALSE);
      
      CWnd* pstat = this->GetDlgItem(IDC_VARSPCG_STATIC);
      pstat->EnableWindow(FALSE);
   }

   if (!pDX->m_bSaveAndValidate)
   {
      CButton* chk;
      if(m_Direction==ltdForward)
         chk = (CButton*)this->GetDlgItem(IDC_RADIO_FORWARD);
      else
         chk = (CButton*)this->GetDlgItem(IDC_RADIO_REVERSE);

      chk->SetCheck(1);
   }
}



BEGIN_MESSAGE_MAP(CEditTruckPosition, CDialog)
	//{{AFX_MSG_MAP(CEditTruckPosition)
	ON_BN_CLICKED(IDC_RADIO_FORWARD, OnRadioForward)
	ON_BN_CLICKED(IDC_RADIO_REVERSE, OnRadioReverse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTruckPosition message handlers

void CEditTruckPosition::OnRadioForward() 
{
	m_Direction = ltdForward;
	
}

void CEditTruckPosition::OnRadioReverse() 
{
	m_Direction = ltdReverse;
}

BOOL CEditTruckPosition::OnInitDialog() 
{
   CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_PIVOT_AXLE);
   for ( int i = 0; i < m_nAxles; i++ )
   {
      CString str;
      str.Format("%d",i);
      pCB->AddString(str);
   }


	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
