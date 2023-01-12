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
// EAFExportCustomReports.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EAFExportCustomReports.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CEAFExportCustomReports dialog

IMPLEMENT_DYNAMIC(CEAFExportCustomReports, CDialog)

CEAFExportCustomReports::CEAFExportCustomReports(CWnd* pParent /*=nullptr*/)
	: CDialog(CEAFExportCustomReports::IDD, pParent),
   m_pCustomReports(nullptr)
{
}

CEAFExportCustomReports::~CEAFExportCustomReports()
{
}

void CEAFExportCustomReports::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST1, m_CheckListBox);

   if (pDX->m_bSaveAndValidate)
   {
      m_SelectedReports.clear();
      for (int cnt = 0; cnt <m_CheckListBox.GetCount(); cnt++)
      {
         int chk = m_CheckListBox.GetCheck(cnt);
         if (chk !=0)
         {
            TCHAR str[256];
            m_CheckListBox.GetText(cnt, str);
            m_SelectedReports.push_back(str);
         }
      }

      if (m_SelectedReports.empty())
      {
         ::AfxMessageBox(_T("You must select at least one report to export."),MB_ICONEXCLAMATION);
         pDX->Fail();
      }
   }
   else
   {
      m_CheckListBox.ResetContent();

      int cnt = 0;
      CEAFCustomReports::ReportConstIterator it = m_pCustomReports->m_Reports.begin();
      while(it != m_pCustomReports->m_Reports.end())
      {
         int cnt = m_CheckListBox.AddString(it->m_ReportName.c_str());
         m_CheckListBox.SetCheck( cnt, 0 );
         it++;
      }
   }
}

BEGIN_MESSAGE_MAP(CEAFExportCustomReports, CDialog)
END_MESSAGE_MAP()

// CEAFExportCustomReports message handlers
