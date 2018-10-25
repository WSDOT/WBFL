///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2011  Washington State Department of Transportation
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

#if !defined(AFX_LOADMODIFIERPAGE_H__FF2BC889_D470_11D1_8B1C_0000F8776D5D__INCLUDED_)
#define AFX_LOADMODIFIERPAGE_H__FF2BC889_D470_11D1_8B1C_0000F8776D5D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LoadModifierPage.h : header file
//
#include <MfcTools\MfcToolsExp.h>

/////////////////////////////////////////////////////////////////////////////
// CLoadModifierPage dialog

class MFCTOOLSCLASS CLoadModifierPage : public CPropertyPage
{

// Construction
public:
	CLoadModifierPage(const CString& t1,const CString& t2,const CString& t3,char ss);
	~CLoadModifierPage();

   CString m_Text1;
   CString m_Text2;
   CString m_Text3;
   char    m_Subscript;

// Dialog Data
	//{{AFX_DATA(CLoadModifierPage)
	enum { IDD = IDD_LOAD_MODIFIER };
	Float64	m_LimitStateFactor;
	int		m_Flag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLoadModifierPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLoadModifierPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioButtonChanged();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADMODIFIERPAGE_H__FF2BC889_D470_11D1_8B1C_0000F8776D5D__INCLUDED_)
