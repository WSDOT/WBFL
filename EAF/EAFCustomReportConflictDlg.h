///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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
// CEAFCustomReportConflictDlg dialog
#pragma once

#include <EAF\EAFCustomReport.h>

class CEAFCustomReportConflictDlg : public CDialog
{
	DECLARE_DYNAMIC(CEAFCustomReportConflictDlg)

public:
	CEAFCustomReportConflictDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEAFCustomReportConflictDlg();

// Dialog Data
	enum { IDD = IDD_CUSTOM_REPORT_CONFLICT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
   const std::set<std::_tstring>* m_pReservedNames;
   CEAFCustomReport* m_pReport; 
   CString m_OrigReportName;

   afx_msg void OnBnClickedRename();
   afx_msg void OnBnClickedSkip();
   afx_msg void OnBnClickedCancel();
   virtual BOOL OnInitDialog();
};
