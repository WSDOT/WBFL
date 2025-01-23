///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <ReportManager\ReportBuilderManager.h>
#include <ReportManager\ReportSpecification.h>
#include <ReportManager\ReportBrowser.h>

using namespace WBFL::Reporting;

/// MFC Dialog that allows the user to configure a report
class CReportDlg : public CDialog
{
public:
	CReportDlg(const std::shared_ptr<const ReportBuilderManager>& rptMgr, const std::shared_ptr<ReportSpecification>& pRptSpec, const std::shared_ptr<const ReportSpecificationBuilder>& pRptSpecBuilder, CWnd* pParent = nullptr);

// Dialog Data
	//{{AFX_DATA(CReportDlg)
	enum { IDD = IDD_REPORT };
	CButton	m_OK;
	CButton	m_Cancel;
	CButton	m_Print;
	CStatic	m_Browser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CString m_strRptName;
	std::shared_ptr<const ReportBuilderManager> m_pRptMgr;
   std::shared_ptr<ReportSpecification> m_pRptSpec;
   std::shared_ptr<const ReportSpecificationBuilder> m_pRptSpecBuilder;
   std::shared_ptr<ReportBrowser> m_pBrowser;

	// Generated message map functions
	//{{AFX_MSG(CReportDlg)
	afx_msg void OnPrint();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
