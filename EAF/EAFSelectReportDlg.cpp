///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2011  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


// EAFSelectReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EAFSelectReportDlg.h"

#include <MFCTools\CustomDDX.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFSelectReportDlg dialog


CEAFSelectReportDlg::CEAFSelectReportDlg(std::vector<std::_tstring>& rptNames,CWnd* pParent /*=NULL*/)
	: CDialog(CEAFSelectReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEAFSelectReportDlg)
	m_ReportName = _T("");
	//}}AFX_DATA_INIT
   m_RptNames = rptNames;
}


void CEAFSelectReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEAFSelectReportDlg)
	DDX_LBString(pDX, IDC_LIST, m_ReportName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEAFSelectReportDlg, CDialog)
	//{{AFX_MSG_MAP(CEAFSelectReportDlg)
	//}}AFX_MSG_MAP
   ON_LBN_DBLCLK(IDC_LIST, &CEAFSelectReportDlg::OnLbnDblclkList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEAFSelectReportDlg message handlers

BOOL CEAFSelectReportDlg::OnInitDialog() 
{
   CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST);
   std::vector<std::_tstring>::iterator iter;
   for ( iter = m_RptNames.begin(); iter != m_RptNames.end(); iter++ )
   {
      pList->AddString( (*iter).c_str() );
   }

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEAFSelectReportDlg::OnLbnDblclkList()
{
   OnOK(); // close the dialog as if the OK button was pressed
}
