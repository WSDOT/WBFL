///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2018  Washington State Department of Transportation
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

#if !defined(AFX_STATICSPLITTER_H__78208B73_C328_11D1_8B10_0000F8776D5D__INCLUDED_)
#define AFX_STATICSPLITTER_H__78208B73_C328_11D1_8B10_0000F8776D5D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StaticSplitter.h : header file
//
#include <MfcTools\MfcToolsExp.h>
#include <afxsplitterwndex.h>

class MFCTOOLSCLASS CUsefulSplitterWnd : public CSplitterWndEx
{
// Construction
	DECLARE_DYNCREATE(CUsefulSplitterWnd)
	CUsefulSplitterWnd();

// Attributes
public:

private:
	BOOL m_bBarLocked;

// Operations
public:
	BOOL IsBarLocked(){return m_bBarLocked;}
	void LockBar(BOOL bState=TRUE){m_bBarLocked=bState;}
	BOOL ReplaceView(int row, int col,CRuntimeClass * pViewClass/*,SIZE size*/);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsefulSplitterWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUsefulSplitterWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUsefulSplitterWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class MFCTOOLSCLASS CDynamicSplitter : public CUsefulSplitterWnd
{
	DECLARE_DYNCREATE(CDynamicSplitter)
	CDynamicSplitter();           // protected constructor used by dynamic creation

// Attributes
protected:

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynamicSplitter)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDynamicSplitter();

	// Generated message map functions
	//{{AFX_MSG(CDynamicSplitter)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
      void SetFirstPaneFraction(Float64 frac);
      Float64  GetFirstPaneFraction() const;

private:
   Float64 m_FirstPaneFraction; // % height for first pane
};

class MFCTOOLSCLASS CStaticSplitter : public CDynamicSplitter
{
	DECLARE_DYNCREATE(CStaticSplitter)
	CStaticSplitter();           // protected constructor used by dynamic creation

// Attributes
protected:

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticSplitter)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticSplitter();

	// Generated message map functions
	//{{AFX_MSG(CStaticSplitter)
   afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICSPLITTER_H__78208B73_C328_11D1_8B10_0000F8776D5D__INCLUDED_)
