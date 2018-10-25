///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2012  Washington State Department of Transportation
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

#if !defined(AFX_REPORTDLG_H__0116CAC5_A624_4A3A_8A98_2D140B68DBF0__INCLUDED_)
#define AFX_REPORTDLG_H__0116CAC5_A624_4A3A_8A98_2D140B68DBF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDlg.h : header file
//

#include <ReportManager\ReportBuilderManager.h>
#include <ReportManager\ReportSpecification.h>
#include <ReportManager\ReportBrowser.h>

/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog

class CReportDlg : public CDialog
{
// Construction
public:
   CReportDlg(CReportBuilderManager& rptMgr,boost::shared_ptr<CReportSpecification>& pRptSpec,boost::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder,CWnd* pParent = NULL);   // standard constructor

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
   CReportBuilderManager& m_RptMgr;
   boost::shared_ptr<CReportSpecification> m_pRptSpec;
   boost::shared_ptr<CReportSpecificationBuilder> m_pRptSpecBuilder;
   boost::shared_ptr<CReportBrowser> m_pBrowser;

	// Generated message map functions
	//{{AFX_MSG(CReportDlg)
	afx_msg void OnPrint();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDLG_H__0116CAC5_A624_4A3A_8A98_2D140B68DBF0__INCLUDED_)
