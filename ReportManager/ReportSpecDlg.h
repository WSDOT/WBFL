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


#include <ReportManager\ReportDescription.h>
#include <ReportManager\ReportSpecification.h>


using namespace WBFL::Reporting;

/////////////////////////////////////////////////////////////////////////////
// CReportSpecDlg dialog

class CReportSpecDlg : public CDialog
{
// Construction
public:
	CReportSpecDlg(const ReportDescription& rptDesc, std::shared_ptr<ReportSpecification>& pRptSpec,CWnd* pParent = nullptr);

// Dialog Data
	//{{AFX_DATA(CReportSpecDlg)
	enum { IDD = IDD_REPORTSPEC };
	CString	m_ReportName;
	CCheckListBox	m_clbChapterList;
	//}}AFX_DATA

   const ReportDescription& m_RptDesc;
   std::vector<ChapterInfo> m_ChapterInfo;
   std::vector<std::_tstring> m_ChapterList;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportSpecDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   void UpdateChapterList();
   void ClearChapterCheckMarks();
   void InitChapterListFromSpec();

   std::shared_ptr<ReportSpecification> m_pInitRptSpec;

	// Generated message map functions
	//{{AFX_MSG(CReportSpecDlg)
	virtual BOOL OnInitDialog() override;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
