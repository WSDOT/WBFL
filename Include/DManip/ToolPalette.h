///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#if !defined(AFX_TOOLPALETTE_H__961A70E3_F6D1_11D4_8B99_006097C68A9C__INCLUDED_)
#define AFX_TOOLPALETTE_H__961A70E3_F6D1_11D4_8B99_006097C68A9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolPalette.h : header file
//

#include <DManip\DManipExp.h>
#include <vector>
#include <afxcmn.h>

struct iTool;

/////////////////////////////////////////////////////////////////////////////
// CToolPalette dialog

class DMANIPCLASS CToolPalette : public CDialogBar
{
// Construction
public:
	CToolPalette();   // standard constructor


// Dialog Data
	//{{AFX_DATA(CToolPalette)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolPalette)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
	virtual void PreSubclassWindow() override;
	//}}AFX_VIRTUAL

public:
   void AddTool(iTool* tool);
   void GetTool(IndexType idx,iTool** pTool);
   void FindTool(IDType id,iTool** pTool);
   void RemoveTool(IndexType idx);
   void RemoveTool(IDType id);

   void AddTooltip(CWnd* pWnd);

// Implementation
protected:
   using ToolContainer = std::vector<CAdapt<CComPtr<iTool>>>;
   ToolContainer m_Tools;

   CToolTipCtrl m_ctrlToolTip;

	// Generated message map functions
	//{{AFX_MSG(CToolPalette)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLPALETTE_H__961A70E3_F6D1_11D4_8B99_006097C68A9C__INCLUDED_)
