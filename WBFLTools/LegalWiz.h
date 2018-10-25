///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2017  Washington State Department of Transportation
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

#if !defined(AFX_LEGALWIZ_H__5897AA6B_703A_11D3_89BA_006097C68A9C__INCLUDED_)
#define AFX_LEGALWIZ_H__5897AA6B_703A_11D3_89BA_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LegalWiz.h : header file
//

#include "LegalWizStep1.h"
#include "LegalWizStep2.h"

/////////////////////////////////////////////////////////////////////////////
// CLegalWiz

class CLegalWiz : public CPropertySheet
{
	DECLARE_DYNAMIC(CLegalWiz)

// Construction
public:
	CLegalWiz(CWnd* pParent,UINT nLicense = IDR_AROSL);

// Attributes
public:

// Operations
public:
   void GiveChoice(VARIANT_BOOL bGiveChoice);
   void ShowLegalNoticeAgain(VARIANT_BOOL bShow);
   VARIANT_BOOL ShowLegalNoticeAgain();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLegalWiz)
	public:
	virtual BOOL OnInitDialog() override;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLegalWiz();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLegalWiz)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
   CLegalWizStep1 m_Page1;
   CLegalWizStep2 m_Page2;
   UINT m_License;

   VARIANT_BOOL m_bGiveChoice;

   void Init();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEGALWIZ_H__5897AA6B_703A_11D3_89BA_006097C68A9C__INCLUDED_)
