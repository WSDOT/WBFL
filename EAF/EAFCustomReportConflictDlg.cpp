///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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
// EAFCustomReportConflictDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EAFCustomReportConflictDlg.h"
#include "EAFRenameReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CEAFCustomReportConflictDlg dialog

IMPLEMENT_DYNAMIC(CEAFCustomReportConflictDlg, CDialog)

CEAFCustomReportConflictDlg::CEAFCustomReportConflictDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CEAFCustomReportConflictDlg::IDD, pParent)
   , m_OrigReportName(_T(""))
{

}

CEAFCustomReportConflictDlg::~CEAFCustomReportConflictDlg()
{
}

void CEAFCustomReportConflictDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);

   DDX_Text(pDX, IDC_REPORT_NAME_STATIC, m_OrigReportName);
}

BEGIN_MESSAGE_MAP(CEAFCustomReportConflictDlg, CDialog)
   ON_BN_CLICKED(ID_RENAME, &CEAFCustomReportConflictDlg::OnBnClickedRename)
   ON_BN_CLICKED(ID_SKIP, &CEAFCustomReportConflictDlg::OnBnClickedSkip)
   ON_BN_CLICKED(IDCANCEL, &CEAFCustomReportConflictDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// CEAFCustomReportConflictDlg message handlers

void CEAFCustomReportConflictDlg::OnBnClickedRename()
{
   CEAFRenameReportDlg dlg;
   dlg.m_pReservedNames = m_pReservedNames;
   dlg.m_OriginalReportName = m_pReport->m_ReportName.c_str();

   if (IDOK == dlg.DoModal())
   {
      // Rename report
      m_pReport->m_ReportName = dlg.m_ReportName;

      EndDialog(ID_RENAME);
   }
   else
   {
      EndDialog(IDCANCEL);
   }
}

void CEAFCustomReportConflictDlg::OnBnClickedSkip()
{
   EndDialog(ID_SKIP);
}

void CEAFCustomReportConflictDlg::OnBnClickedCancel()
{
   OnCancel();
}

BOOL CEAFCustomReportConflictDlg::OnInitDialog()
{
   m_OrigReportName = m_pReport->m_ReportName.c_str();

   CDialog::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
