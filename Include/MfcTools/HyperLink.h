///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2015  Washington State Department of Transportation
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
#ifndef INCLUDED_MFCTOOLS_HYPERLINK_H_
#define INCLUDED_MFCTOOLS_HYPERLINK_H_
#pragma once

//
#include <MfcTools\MfcToolsExp.h>
#include <afxcmn.h>

// Structure used to get/set hyperlink colors
typedef struct MFCTOOLSCLASS tagHYPERLINKCOLORS {
	COLORREF	crLink;
	COLORREF	crActive;
	COLORREF	crVisited;
	COLORREF	crHover;
} HYPERLINKCOLORS;


/////////////////////////////////////////////////////////////////////////////
// CHyperLink window

class MFCTOOLSCLASS CHyperLink : public CStatic
{
	DECLARE_DYNAMIC(CHyperLink)

public:
// Link styles
	static const DWORD StyleUnderline;
	static const DWORD StyleUseHover;
	static const DWORD StyleAutoSize;
	static const DWORD StyleDownClick;
	static const DWORD StyleGetFocusOnClick;
	static const DWORD StyleNoHandCursor;
	static const DWORD StyleNoActiveColor;

// Construction/destruction
	CHyperLink();
	virtual ~CHyperLink();

// Attributes
public:

// Operations
public:	
	static void GetColors(HYPERLINKCOLORS& linkColors);

	static HCURSOR GetLinkCursor();
	static void SetLinkCursor(HCURSOR hCursor);
    
    static void SetColors(COLORREF crLinkColor, COLORREF crActiveColor, 
				   COLORREF crVisitedColor, COLORREF crHoverColor = -1);
    static void SetColors(HYPERLINKCOLORS& colors);

	void SetURL(CString strURL);
    CString GetURL() const;

	DWORD GetLinkStyle() const;
	BOOL ModifyLinkStyle(DWORD dwRemove, DWORD dwAdd, BOOL bApply=TRUE);	
    
	void SetWindowText(LPCTSTR lpszText);
	void SetFont(CFont *pFont);
	
	BOOL IsVisited() const;
	void SetVisited(BOOL bVisited = TRUE);
	
	// Use this if you want to subclass and also set different URL
	BOOL SubclassDlgItem(UINT nID, CWnd* pParent, LPCTSTR lpszURL=NULL) {
		m_strURL = lpszURL;
		return CStatic::SubclassDlgItem(nID, pParent);
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperLink)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	protected:
	virtual void PreSubclassWindow();	
	//}}AFX_VIRTUAL

// Implementation
protected:
	static void SetDefaultCursor();
	static LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	static void ReportError(int nError);	
	static HINSTANCE GotoURL(LPCTSTR url, int showcmd);

	void AdjustWindow();	
	virtual void FollowLink();
	inline void SwitchUnderline();
	
// Protected attributes
protected:
	static COLORREF g_crLinkColor;		// Link normal color
	static COLORREF g_crActiveColor;	// Link active color
	static COLORREF g_crVisitedColor;	// Link visited color
	static COLORREF g_crHoverColor;		// Hover color
	static HCURSOR  g_hLinkCursor;		// Hyperlink mouse cursor

	BOOL	 m_bLinkActive;				// Is the link active?
	BOOL     m_bOverControl;			// Is cursor over control?
	BOOL	 m_bVisited;				// Has link been visited?
	DWORD	 m_dwStyle;					// Link styles
	CString  m_strURL;					// Hyperlink URL string
	CFont    m_Font;					// Underlined font (if required)	
	CToolTipCtrl m_ToolTip;				// The link tooltip	

	// Generated message map functions
protected:
	//{{AFX_MSG(CHyperLink)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line

#endif // INCLUDED_MFCTOOLS_HYPERLINK_H_
