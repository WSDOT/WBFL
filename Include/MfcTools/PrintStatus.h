///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright � 1999-2025  Washington State Department of Transportation
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
#if !defined(AFX_PRINTSTATUS_H__7EADD892_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
#define AFX_PRINTSTATUS_H__7EADD892_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrintStatus.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPrintStatus dialog

class CPrintStatus : public CDialog
{
// Construction
public:
	CPrintStatus(CWnd* pParent = nullptr);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintStatus)
	enum { IDD = IDD_PRINT_STATUS };
	CProgressCtrl	wndProg;
	CAnimateCtrl	wndAnima;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintStatus)
	protected:
      virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintStatus)
	virtual BOOL OnInitDialog() override;
	virtual void OnCancel() override;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTSTATUS_H__7EADD892_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
