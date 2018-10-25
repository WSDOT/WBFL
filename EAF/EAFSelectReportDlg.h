///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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


#pragma once

// EAFSelectReportDlg.h : header file
//
#include "resource.h"
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CEAFSelectReportDlg dialog
// Standard dialog for selecting a report

class CEAFSelectReportDlg : public CDialog
{
// Construction
public:
   CEAFSelectReportDlg(std::vector<std::_tstring>& rptNames,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEAFSelectReportDlg)
	enum { IDD = IDD_SELECTREPORT };
	//}}AFX_DATA
	std::_tstring	m_ReportName;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFSelectReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   std::vector<std::_tstring> m_RptNames;

	// Generated message map functions
	//{{AFX_MSG(CEAFSelectReportDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnLbnDblclkList();
};
