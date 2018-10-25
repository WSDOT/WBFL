///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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
// CEditCustomReportDlg dialog
#pragma once

#include "EAF\EAFResources.h"
#include "Resource.h"
#include "afxwin.h"

#include <EAF\EAFCustomReport.h>

class CConfigureReportsDlg;

class CEditCustomReportDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditCustomReportDlg)

public:
	CEditCustomReportDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditCustomReportDlg();

// Dialog Data
	enum { IDD = IDD_EDIT_CUSTOM_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

   void FillChapterData(bool initial);
   void OnSelectAvailable(BOOL select);
   void OnSelectSelected(BOOL select);

public:
   CEAFCustomReport m_CustomReport;
   CConfigureReportsDlg* m_pConfigureReportsDlg;

   virtual BOOL OnInitDialog();
   afx_msg void OnCbnSelchangeParentCombo();
   CComboBox m_ParentReportCombo;
   CEdit m_ReportName;
   bool m_FromInit;
   CListBox m_AvailableChaptersList;
   CListBox m_SelectedChaptersList;
   CButton m_AddButton;
   CButton m_RemoveButton;
   CButton m_MoveUpButton;
   CButton m_MoveDownButton;
   afx_msg void OnBnClickedAddButton();
   afx_msg void OnBnClickedRemoveButton();
   afx_msg void OnBnClickedMoveUpButton();
   afx_msg void OnBnClickedMoveDownButton();
   afx_msg void OnLbnSelchangeAvailableList();
   afx_msg void OnLbnSelchangeSelectedList();
   BOOL m_bIsFavorite;
};
