///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2017  Washington State Department of Transportation
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

#if !defined(AFX_PROGRESSDLG_H__99C34AA6_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)
#define AFX_PROGRESSDLG_H__99C34AA6_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProgressDlg.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

class CProgressDlg : public CDialog
{
// Construction
public:
	CProgressDlg(CWnd* pParent = nullptr);   // standard constructor

   ~CProgressDlg();
// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESSDLG };
   DWORD m_dwMask;
	CAnimateCtrl	m_Animate;
	CStatic	m_MessageCtrl;
	CButton	m_Cancel;
	CProgressCtrl	m_ProgressBar;
	CString	m_Message;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   BOOL Continue();
   void ResetContinueState();
   void PumpMessage();
   void UpdateMessage(LPCTSTR msg);

   void GrabInput();
   void ReleaseInput();


// Implementation
protected:
   BOOL m_bContinue;

   CWnd* m_pwndFocus;
   CWnd* m_pwndCapture;

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	virtual BOOL OnInitDialog() override;
	//}}AFX_MSG
   virtual void OnCancel() override;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLG_H__99C34AA6_2BE4_11D2_8EB3_006097DF3C68__INCLUDED_)
