///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2018  Washington State Department of Transportation
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

// LegalWizStep1.cpp : implementation file
//

#include "stdafx.h"
#include "LegalWizStep1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLegalWizStep1 property page

IMPLEMENT_DYNCREATE(CLegalWizStep1, CPropertyPage)

CLegalWizStep1::CLegalWizStep1() : CPropertyPage(CLegalWizStep1::IDD)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//{{AFX_DATA_INIT(CLegalWizStep1)
	m_Text = _T("");
	//}}AFX_DATA_INIT
}

CLegalWizStep1::~CLegalWizStep1()
{
}

void CLegalWizStep1::SetLicense(UINT license)
{
   m_License = license;
}

void CLegalWizStep1::DoDataExchange(CDataExchange* pDX)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLegalWizStep1)
	DDX_Text(pDX, IDC_LIC_TEXT, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLegalWizStep1, CPropertyPage)
	//{{AFX_MSG_MAP(CLegalWizStep1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLegalWizStep1 message handlers

BOOL CLegalWizStep1::OnSetActive() 
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your specialized code here and/or call the base class
   CPropertySheet* pWiz = (CPropertySheet*)GetParent();
   pWiz->SetWizardButtons( PSWIZB_NEXT );
	
	return CPropertyPage::OnSetActive();
}

BOOL CLegalWizStep1::OnInitDialog() 
{
   USES_CONVERSION;

   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   HMODULE hMod = AfxGetResourceHandle();
   HRSRC hResInfo;
   if ( m_License == IDR_AROSL )
      hResInfo = FindResource( hMod, MAKEINTRESOURCE(IDR_AROSL), _T("TEXT") );
   else
      hResInfo = FindResource( hMod, MAKEINTRESOURCE(IDR_ARLOSL), _T("TEXT") );

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
}
