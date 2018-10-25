///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright (C) 1999  Washington State Department of Transportation
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

// WatermarkMainFrm.h
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WATERMARKMAINFRM_H__59D503EE_265C_11D2_8EB0_006097DF3C68__INCLUDED_)
#define AFX_WATERMARKMAINFRM_H__59D503EE_265C_11D2_8EB0_006097DF3C68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <MfcTools\MfcToolsExp.h>
#include <MfcTools\Watermark.h>

class MFCTOOLSCLASS CWatermarkMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CWatermarkMainFrame)
public:
   CWatermarkMainFrame( UINT nIDResource );
   CWatermarkMainFrame( LPCTSTR lpszResourceName );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatermarkMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWatermarkMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    LPTSTR m_lpszResourceName;
    UINT m_nIDResource;
    CWatermark m_Watermark;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATERMARKMAINFRM_H__59D503EE_265C_11D2_8EB0_006097DF3C68__INCLUDED_)
