///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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


#pragma once

// EAFHelpWindow.h : header file
//

#include <EAF\EAFExp.h>
#include <afxext.h>
#include "webbrowser.h"


/////////////////////////////////////////////////////////////////////////////
// CEAFHelpWindow
class CEAFHelpWindow : public CFrameWnd
{
public:
	CEAFHelpWindow();           // protected constructor used by dynamic creation
	virtual ~CEAFHelpWindow();

// Attributes
public:
   void CanClose(BOOL bCanClose);
   void Navigate(LPCTSTR lpszURL);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEAFHelpWindow)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   // Generated message map functions
protected:
	//{{AFX_MSG(CEAFReportView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnClose();
   afx_msg void OnDestroy();

   afx_msg void OnFileClose();
   afx_msg void OnFilePrint();
   afx_msg void OnBack();
   afx_msg void OnForward();

   afx_msg void OnNavigate(NMHDR* pNotifyStruct,LRESULT* result);
   afx_msg void OnCmenuSelected(UINT id);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
   BOOL m_bCanClose;
   CWebBrowser m_WebBrowser;
   CToolBar m_Toolbar;
   CStatusBar m_StatusBar;
};
