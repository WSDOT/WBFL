///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRESSMONITORDLG_H__E1D69FE4_ED1E_49ED_A71F_BCE26EA1FD84__INCLUDED_)
#define AFX_PROGRESSMONITORDLG_H__E1D69FE4_ED1E_49ED_A71F_BCE26EA1FD84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressMonitorDlg.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CProgressMonitorDlg dialog

class CProgressMonitorDlg : public CDialog
{
// Construction
public:
	CProgressMonitorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressMonitorDlg)
	enum { IDD = IDD_PROGRESSMONITORDLG };
	CProgressCtrl	m_ProgressCtrl;
	CButton	m_MessageCtl;
	CButton	m_CancelBtn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressMonitorDlg)
public:
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
   void SetMessage(BSTR msg);
   void SetProgressValue(long val);
   void PumpMessage();
   void Close();

   VARIANT_BOOL m_WasCancelled;
   VARIANT_BOOL m_HasCancel;
   VARIANT_BOOL m_HasGauge;

protected:
   HCURSOR m_Cursor;

	// Generated message map functions
	//{{AFX_MSG(CProgressMonitorDlg)
	afx_msg void OnCancelProgress();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSMONITORDLG_H__E1D69FE4_ED1E_49ED_A71F_BCE26EA1FD84__INCLUDED_)
