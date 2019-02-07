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

#if !defined(AFX_STATUSMESSAGEDIALOG_H__E371357F_A5AF_4D06_AEEF_60EDC174B783__INCLUDED_)
#define AFX_STATUSMESSAGEDIALOG_H__E371357F_A5AF_4D06_AEEF_60EDC174B783__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusMessageDialog.h : header file
//
#include <EAF\EAFTypes.h>

#include "resource.h"

class CEAFStatusItem;

/////////////////////////////////////////////////////////////////////////////
// CStatusMessageDialog dialog

class CStatusMessageDialog : public CDialog
{
// Construction
public:
	CStatusMessageDialog(CEAFStatusItem* pStatusItem,eafTypes::StatusSeverityType severity,BOOL bRemoveableOnError,BOOL bEnableEdit,LPCTSTR lpszDocSetName,UINT helpID,CWnd* pParent = nullptr);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatusMessageDialog)
	enum { IDD = IDD_STATUS_DIALOG };
	//}}AFX_DATA

// Data
   // Return value from dialog closure
   eafTypes::StatusItemDisplayReturn GetReturnValue() const;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusMessageDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CString m_strDocSetName;
   UINT m_HelpID;

   eafTypes::StatusSeverityType m_Severity;
   BOOL m_bRemoveableOnError;
   BOOL m_bEnableEdit;
	CString	m_Message;
   eafTypes::StatusItemDisplayReturn m_StatusItemDisplayReturn;

	// Generated message map functions
	//{{AFX_MSG(CStatusMessageDialog)
	afx_msg void OnHelp();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedEdit();
   afx_msg void OnBnClickedRemove();
   afx_msg void OnBnClickedClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSMESSAGEDIALOG_H__E371357F_A5AF_4D06_AEEF_60EDC174B783__INCLUDED_)
