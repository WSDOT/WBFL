///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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
// CCustomReportsPage 

#pragma once

#include "EAF\EAFResources.h"
#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"

#include <EAF\EAFCustomReport.h>

class CConfigureReportsDlg;

class CCustomReportsPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCustomReportsPage)

public:
	CCustomReportsPage();
	virtual ~CCustomReportsPage();

   void InsertData();

// Dialog Data
	enum { IDD = IDD_CUSTOM_REPORTS_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

   CListCtrl m_CustomReportsList;
   CButton m_EditButton;
   CButton m_DeleteButton;

   bool m_bInInit;

   afx_msg void OnBnClickedAddnew();
   afx_msg void OnBnClickedEdit();
   afx_msg void OnBnClickedDelete();
   afx_msg void OnLvnItemchangedCustomReportList(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnNMDblclkCustomReportList(NMHDR *pNMHDR, LRESULT *pResult);

   virtual BOOL OnInitDialog() override;

   void EditSelectedReport();
public:
   CConfigureReportsDlg* m_pParentDlg;


   afx_msg void OnBnClickedExport();
   afx_msg void OnBnClickedImport();
};
