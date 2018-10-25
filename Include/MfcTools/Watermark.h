///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2013  Washington State Department of Transportation
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

#if !defined(AFX_WATERMARK_H__5429BD52_E13A_11D1_8E93_006097DF3C68__INCLUDED_)
#define AFX_WATERMARK_H__5429BD52_E13A_11D1_8E93_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Watermark.h : header file
//

#include <MfcTools\MfcToolsExp.h>

/////////////////////////////////////////////////////////////////////////////
// CWatermark window

class MFCTOOLSCLASS CWatermark : public CWnd
{
// Construction
public:
	CWatermark();

// Attributes
public:
   int MarkIt( UINT nIDResource, HWND hwnd );
   int MarkIt( LPCTSTR lpszResourceName, HWND hwnd );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatermark)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWatermark();

	// Generated message map functions
protected:
   int Subclass(HWND hwnd);
   CBitmap m_Bitmap;

	//{{AFX_MSG(CWatermark)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATERMARK_H__5429BD52_E13A_11D1_8E93_006097DF3C68__INCLUDED_)
