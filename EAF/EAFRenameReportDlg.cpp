///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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
// EAFRenameReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EAFRenameReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CEAFRenameReportDlg dialog

IMPLEMENT_DYNAMIC(CEAFRenameReportDlg, CDialog)

CEAFRenameReportDlg::CEAFRenameReportDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CEAFRenameReportDlg::IDD, pParent)
   , m_ReportName(_T(""))
   , m_OriginalReportName(_T(""))
{
}

CEAFRenameReportDlg::~CEAFRenameReportDlg()
{
}

void CEAFRenameReportDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_NAME_STATIC, m_OriginalReportName);
   DDX_Text(pDX, IDC_REPORT_NAME_EDIT, m_ReportName);

   if (pDX->m_bSaveAndValidate)
   {
      m_ReportName.Trim();
      if(m_ReportName.IsEmpty())
      {
         ::AfxMessageBox(_T("Please enter a report name"));
         pDX->Fail();
      }
      else if (m_pReservedNames->find(std::_tstring(m_ReportName)) != m_pReservedNames->end())
      {
         ::AfxMessageBox(_T("The report name entered already exists. Please enter a new, unique name."));
         pDX->Fail();
      }
   }
}

BEGIN_MESSAGE_MAP(CEAFRenameReportDlg, CDialog)
END_MESSAGE_MAP()

// CEAFRenameReportDlg message handlers
