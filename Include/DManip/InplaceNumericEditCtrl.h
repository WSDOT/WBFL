///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#if !defined(AFX_FLOATEDIT_H__DC21B442_DE85_11D4_8CE4_0080C7380027__INCLUDED_)
#define AFX_FLOATEDIT_H__DC21B442_DE85_11D4_8CE4_0080C7380027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InplaceNumericEditCtrl.h : header file
//

#define WM_EDITERROR WM_USER + 100

#include <DManip\DManipExp.h>
#include <DManip\InplaceEditCtrl.h>

/////////////////////////////////////////////////////////////////////////////
// CInplaceNumericEdit window

class DMANIPCLASS CInplaceNumericEdit : public CInplaceEdit
{
// Construction
public:
	CInplaceNumericEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInplaceNumericEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInplaceNumericEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFloatEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOATEDIT_H__DC21B442_DE85_11D4_8CE4_0080C7380027__INCLUDED_)
