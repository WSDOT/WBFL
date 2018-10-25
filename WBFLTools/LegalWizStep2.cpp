///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2011  Washington State Department of Transportation
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

// LegalWizStep2.cpp : implementation file
//

#include "stdafx.h"
#include "LegalWizStep2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLegalWizStep2 dialog


IMPLEMENT_DYNCREATE(CLegalWizStep2, CPropertyPage)

CLegalWizStep2::CLegalWizStep2() : CPropertyPage(CLegalWizStep2::IDD)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//{{AFX_DATA_INIT(CLegalWizStep2)
	m_DontShowAgain = FALSE;
	m_Text = _T("");
	//}}AFX_DATA_INIT
}

CLegalWizStep2::~CLegalWizStep2()
{
}

void CLegalWizStep2::DoDataExchange(CDataExchange* pDX)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLegalWizStep2)
	DDX_Check(pDX, IDC_CHECK, m_DontShowAgain);
	DDX_Text(pDX, IDC_DISCLAIMER, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLegalWizStep2, CPropertyPage)
	//{{AFX_MSG_MAP(CLegalWizStep2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLegalWizStep2 message handlers

BOOL CLegalWizStep2::OnSetActive() 
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   CPropertySheet* pWiz = (CPropertySheet*)GetParent();
   pWiz->SetWizardButtons( PSWIZB_BACK | PSWIZB_FINISH );
	
	return CPropertyPage::OnSetActive();
}

BOOL CLegalWizStep2::OnWizardFinish() 
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your specialized code here and/or call the base class
   UpdateData();
	
	return CPropertyPage::OnWizardFinish();
}

BOOL CLegalWizStep2::OnInitDialog() 
{
   USES_CONVERSION;

   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   HMODULE hMod = AfxGetResourceHandle();
   HRSRC hResInfo = FindResource( hMod, MAKEINTRESOURCE(IDR_DISCLAIMER), _T("TEXT") );
   if ( hResInfo == 0 )
      DWORD dwError = GetLastError();
   DWORD dwSize = SizeofResource( hMod, hResInfo );
   HGLOBAL hResData = LoadResource( hMod, hResInfo );
   LPVOID pVoid = LockResource( hResData );

   LPSTR pText = new char[dwSize];
   memcpy((void*)pText,pVoid,dwSize);
   pText[dwSize-1] = 0;

   m_Text = A2T(pText);

   delete[] pText;
	
	CPropertyPage::OnInitDialog();

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	              // EXCEPTION: OCX Property Pages should return FALSE
}
