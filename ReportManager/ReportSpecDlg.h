///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#if !defined(AFX_REPORTSPECDLG_H__A3EE66C1_88D8_486F_8375_1258BEC7B39A__INCLUDED_)
#define AFX_REPORTSPECDLG_H__A3EE66C1_88D8_486F_8375_1258BEC7B39A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportSpecDlg.h : header file
//

#include <ReportManager\ReportDescription.h>
#include <ReportManager\ReportSpecification.h>
#include <boost\shared_ptr.hpp>

/////////////////////////////////////////////////////////////////////////////
// CReportSpecDlg dialog

class CReportSpecDlg : public CDialog
{
// Construction
public:
	CReportSpecDlg(const CReportDescription* pRptDesc,boost::shared_ptr<CReportSpecification>& pRptSpec,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportSpecDlg)
	enum { IDD = IDD_REPORTSPEC };
	CString	m_ReportName;
	CCheckListBox	m_ChapterList;
	//}}AFX_DATA

   const CReportDescription* m_pRptDesc;
   std::vector<CChapterInfo> m_ChapterInfo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportSpecDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   void UpdateChapterList();
   void ClearChapterCheckMarks();
   void InitChapterListFromSpec();

   boost::shared_ptr<CReportSpecification> m_pInitRptSpec;

	// Generated message map functions
	//{{AFX_MSG(CReportSpecDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTSPECDLG_H__A3EE66C1_88D8_486F_8375_1258BEC7B39A__INCLUDED_)
