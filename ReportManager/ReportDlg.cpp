///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2024  Washington State Department of Transportation
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

// ReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportManager.h"
#include "ReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog


CReportDlg::CReportDlg(const std::shared_ptr<const ReportBuilderManager>& rptMgr, const std::shared_ptr<ReportSpecification>& pRptSpec, const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder,CWnd* pParent /*=nullptr*/)
	: CDialog(CReportDlg::IDD, pParent), m_pRptMgr(rptMgr), m_pRptSpec(pRptSpec), m_pRptSpecBuilder(pRptSpecBuilder)
{
	//{{AFX_DATA_INIT(CReportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDlg)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_PRINT, m_Print);
	DDX_Control(pDX, IDC_BROWSER, m_Browser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDlg, CDialog)
	//{{AFX_MSG_MAP(CReportDlg)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDlg message handlers

BOOL CReportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
   m_pBrowser = m_pRptMgr->CreateReportBrowser(m_Browser.GetSafeHwnd(),0,m_pRptSpec,m_pRptSpecBuilder);

   CRect rect;
   m_Browser.GetClientRect(&rect);
   m_pBrowser->Size(rect.Size());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportDlg::OnPrint() 
{
   m_pBrowser->Print(true);
}

void CReportDlg::OnClose() 
{
	CDialog::OnClose();
}
