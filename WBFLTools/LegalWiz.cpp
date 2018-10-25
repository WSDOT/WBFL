///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2014  Washington State Department of Transportation
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

// LegalWiz.cpp : implementation file
//

#include "stdafx.h"
#include "LegalWiz.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLegalWiz

IMPLEMENT_DYNAMIC(CLegalWiz, CPropertySheet)

CLegalWiz::CLegalWiz(CWnd* pParent,UINT nLicense)
	:CPropertySheet(_T("Legal Notice"),pParent,0)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   m_License = nLicense;
   m_bGiveChoice = VARIANT_TRUE;
   Init();
}

CLegalWiz::~CLegalWiz()
{
}


BEGIN_MESSAGE_MAP(CLegalWiz, CPropertySheet)
	//{{AFX_MSG_MAP(CLegalWiz)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLegalWiz message handlers
void CLegalWiz::Init()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   m_Page1.m_psp.dwFlags ^= PSP_HASHELP;
   m_Page2.m_psp.dwFlags ^= PSP_HASHELP;
   m_psh.dwFlags ^= PSH_HASHELP;

   m_Page1.SetLicense( m_License );

   AddPage( &m_Page1 );
   AddPage( &m_Page2 );
   SetWizardMode();
}

BOOL CLegalWiz::OnInitDialog() 
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   BOOL bResult = CPropertySheet::OnInitDialog();

   if ( m_bGiveChoice )
   {
      // Change the text on the Finish button
      // If you use SetFinishText, the Back button will be hidden
      // This is not desired.
      // Change the text manually
      CWnd* pWnd = GetDlgItem(ID_WIZFINISH);
      if ( pWnd )
         pWnd->SetWindowText( _T("I Accept") );
      
      //SetFinishText(_T("I Accept"));
   }
   else
   {
     CWnd* pWnd = GetDlgItem(IDCANCEL);
     if ( pWnd )
        pWnd->ShowWindow( SW_HIDE );
   }
	

   CWnd* pWnd = GetDlgItem( IDHELP );
   if ( pWnd )
      pWnd->ShowWindow( SW_HIDE );
	
	return bResult;
}

void CLegalWiz::GiveChoice(VARIANT_BOOL bGiveChoice)
{
   m_bGiveChoice = bGiveChoice;
}

void CLegalWiz::ShowLegalNoticeAgain(VARIANT_BOOL bShow)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   m_Page2.m_DontShowAgain = (bShow == VARIANT_TRUE ? FALSE : TRUE);
}

VARIANT_BOOL CLegalWiz::ShowLegalNoticeAgain()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   return (m_Page2.m_DontShowAgain == TRUE) ? VARIANT_FALSE : VARIANT_TRUE;
}
