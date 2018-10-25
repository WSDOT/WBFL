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

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTipDlg dialog

class CTipDlg : public CDialog
{
// Construction
public:
	CTipDlg(LPCTSTR lpszTipFile,CWnd* pParent = NULL);	 // standard constructor

// Dialog Data
	//{{AFX_DATA(CTipDlg)
	// enum { IDD = IDD_TIP };
	BOOL	m_bStartup;
	CString	m_strTip;
	//}}AFX_DATA

	FILE* m_pStream;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTipDlg();

protected:
	// Generated message map functions
	//{{AFX_MSG(CTipDlg)
	afx_msg void OnNextTip();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void GetNextTipString(CString& strNext);
};
