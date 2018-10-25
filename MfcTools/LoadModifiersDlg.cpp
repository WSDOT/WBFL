///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// LoadModifiersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include <HtmlHelp.h>
#include <MFCTools\LoadModifiersDlg.h>
#include <MFCTools\LoadModifierPage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadModifiersDlg

IMPLEMENT_DYNAMIC(CLoadModifiersDlg, CPropertySheet)

CLoadModifiersDlg::CLoadModifiersDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
   Init();
}

CLoadModifiersDlg::CLoadModifiersDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
   Init();
}

CLoadModifiersDlg::~CLoadModifiersDlg()
{
}

void CLoadModifiersDlg::SetHelpData(LPCTSTR pszHelpFile,DWORD nd,DWORD nr,DWORD ni)
{
   m_HelpFile = pszHelpFile;
   m_HelpID[0] = nd;
   m_HelpID[1] = nr;
   m_HelpID[2] = ni;
   m_bHelpInit = TRUE;
}

void CLoadModifiersDlg::SetLoadModifiers(Float64 nd,Int16 ndl,Float64 nr,Int16 nrl,Float64 ni,Int16 nil)
{
   m_pDuctilityPage->m_LimitStateFactor  = nd;
   m_pDuctilityPage->m_Flag = ndl;

   m_pRedundancyPage->m_LimitStateFactor = nr;
   m_pRedundancyPage->m_Flag = nrl;

   m_pImportancePage->m_LimitStateFactor = ni;
   m_pImportancePage->m_Flag = nil;
}

void CLoadModifiersDlg::GetLoadModifiers(Float64* nd,Int16* ndl,Float64* nr,Int16* nrl,Float64* ni,Int16* nil) const
{
   PRECONDITION( nd != 0 );
   PRECONDITION( nr != 0 );
   PRECONDITION( ni != 0 );

   PRECONDITION( ndl != 0 );
   PRECONDITION( nrl != 0 );
   PRECONDITION( nil != 0 );

   *nd  = m_pDuctilityPage->m_LimitStateFactor;
   *ndl = m_pDuctilityPage->m_Flag;

   *nr  = m_pRedundancyPage->m_LimitStateFactor;
   *nrl = m_pRedundancyPage->m_Flag;

   *ni  = m_pImportancePage->m_LimitStateFactor;
   *nil = m_pImportancePage->m_Flag;
}

BEGIN_MESSAGE_MAP(CLoadModifiersDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CLoadModifiersDlg)
	ON_WM_CREATE()
	ON_COMMAND(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadModifiersDlg message handlers

void CLoadModifiersDlg::Init()
{
   m_bHelpInit = FALSE;

   m_psh.dwFlags |= PSH_HASHELP | PSH_NOAPPLYNOW;

   m_pDuctilityPage = std::auto_ptr<CLoadModifierPage>( new CLoadModifierPage(_T("Non-ductile"),
                                                                              _T("Conventional design"),
                                                                              _T("Enhanced ductility"),
                                                                              _T('D')) );
   AddPage( m_pDuctilityPage.get() );

   m_pRedundancyPage = std::auto_ptr<CLoadModifierPage>( new CLoadModifierPage(_T("Non-redundant"),
                                                                               _T("Conventional levels of redundancy"),
                                                                               _T("Exceptional levels of redundancy"),
                                                                               _T('R')) );
   AddPage( m_pRedundancyPage.get() );

   m_pImportancePage = std::auto_ptr<CLoadModifierPage>( new CLoadModifierPage(_T("Important"),
                                                                               _T("Typical"),
                                                                               _T("Not important"),
                                                                               _T('I')) );
   AddPage( m_pImportancePage.get() );
}

int CLoadModifiersDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	
	return 0;
}

BOOL CLoadModifiersDlg::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	TC_ITEM tcItem;
   tcItem.mask = TCIF_TEXT;
   int idx;

   idx = GetPageIndex( m_pDuctilityPage.get() );
	tcItem.pszText = _T("Ductility");
	GetTabControl()->SetItem(idx, &tcItem );

   idx = GetPageIndex( m_pRedundancyPage.get() );
	tcItem.pszText = _T("Redundancy");
	GetTabControl()->SetItem(idx, &tcItem );
   
   idx = GetPageIndex( m_pImportancePage.get() );
	tcItem.pszText = _T("Importance");
	GetTabControl()->SetItem(idx, &tcItem );
	
	return bResult;
}

void CLoadModifiersDlg::OnHelp()
{
   if ( m_bHelpInit )
   {
      ::HtmlHelp( *this, m_HelpFile, HH_HELP_CONTEXT, m_HelpID[GetActiveIndex()] );
   }

}
