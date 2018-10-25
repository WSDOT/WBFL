///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_LEGALWIZSTEP1_H__5897AA6D_703A_11D3_89BA_006097C68A9C__INCLUDED_)
#define AFX_LEGALWIZSTEP1_H__5897AA6D_703A_11D3_89BA_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LegalWizStep1.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CLegalWizStep1 dialog

class CLegalWizStep1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CLegalWizStep1)

// Construction
public:
	CLegalWizStep1();
	~CLegalWizStep1();

   void SetLicense(UINT license);

// Dialog Data
	//{{AFX_DATA(CLegalWizStep1)
	enum { IDD = IDD_LICENSEWIZ_1 };
	CString	m_Text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLegalWizStep1)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLegalWizStep1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

   UINT m_License;

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEGALWIZSTEP1_H__5897AA6D_703A_11D3_89BA_006097C68A9C__INCLUDED_)
