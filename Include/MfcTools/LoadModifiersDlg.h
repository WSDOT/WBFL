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

#if !defined(AFX_LOADMODIFIERSDLG_H__FF2BC883_D470_11D1_8B1C_0000F8776D5D__INCLUDED_)
#define AFX_LOADMODIFIERSDLG_H__FF2BC883_D470_11D1_8B1C_0000F8776D5D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LoadModifiersDlg.h : header file
//
#include <MfcTools\MfcToolsExp.h>
#include <MFCTools\HelpHandler.h>
#include <memory>

class CLoadModifierPage;

/////////////////////////////////////////////////////////////////////////////
// CLoadModifiersDlg

class MFCTOOLSCLASS CLoadModifiersDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CLoadModifiersDlg)

// Construction
public:
	CLoadModifiersDlg(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CLoadModifiersDlg(LPCTSTR pszCaption = _T("Load Modifiers"), CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);

   void SetHelpData(CHelpHandler* pHelpHandlerND,CHelpHandler* pHelpHandlerNR,CHelpHandler* pHelpHandlerNI);

   // levels on modifers are as follows:
   //  0 == High
   //  1 == Normal
   //  2 == Low
   void SetLoadModifiers(Float64 nd,Int16 ndl,Float64 nr,Int16 nrl,Float64 ni,Int16 nil);
   void GetLoadModifiers(Float64* nd,Int16* ndl,Float64* nr,Int16* nrl,Float64* ni,Int16* nil) const;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadModifiersDlg)
	public:
	virtual BOOL OnInitDialog() override;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLoadModifiersDlg();

	// Generated message map functions
protected:
   CHelpHandler* m_pHelpHandler[3];

   void Init();

   std::unique_ptr<CLoadModifierPage> m_pDuctilityPage;
   std::unique_ptr<CLoadModifierPage> m_pRedundancyPage;
   std::unique_ptr<CLoadModifierPage> m_pImportancePage;

	//{{AFX_MSG(CLoadModifiersDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADMODIFIERSDLG_H__FF2BC883_D470_11D1_8B1C_0000F8776D5D__INCLUDED_)
