///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2026  Washington State Department of Transportation
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

// EAFLegalNoticeWiz.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <EAF\EAFLegalNoticeWiz.h>

// The TEXT-type license/disclaimer resources are compiled into this DLL's own
// binary. Windows resource lookup must target this DLL's module handle
// explicitly rather than whatever module happens to be ambiently active on
// the calling thread (e.g. the host application), since FindResource/LoadResource
// (unlike MFC's own chain-searching dialog-template loader) only look in the
// exact module handle given to them.
extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace
{
   CString LoadEmbeddedResourceText(UINT nResId)
   {
      USES_CONVERSION;

      HMODULE hMod = (HMODULE)&__ImageBase;
      HRSRC hResInfo = FindResource( hMod, MAKEINTRESOURCE(nResId), _T("TEXT") );
      if ( hResInfo == 0 )
         return CString();

      DWORD dwSize = SizeofResource( hMod, hResInfo );
      HGLOBAL hResData = LoadResource( hMod, hResInfo );
      LPVOID pVoid = LockResource( hResData );

      if ( dwSize == 0 || pVoid == nullptr )
         return CString();

      LPSTR pText = new char[dwSize];
      memcpy((void*)pText,pVoid,dwSize);
      pText[dwSize-1] = 0;

      CString strText = A2T(pText);

      delete[] pText;

      return strText;
   }
}

CString EAFGetLicenseText(EAFLicenseType license)
{
   return LoadEmbeddedResourceText( license == EAFLicenseType::AROSL ? IDR_AROSL : IDR_ARLOSL );
}

CString EAFGetDisclaimerText()
{
   return LoadEmbeddedResourceText( IDR_DISCLAIMER );
}

// CEAFLegalNoticeWiz

IMPLEMENT_DYNAMIC(CEAFLegalNoticeWiz, CPropertySheet)

CEAFLegalNoticeWiz::CEAFLegalNoticeWiz(CWnd* pParent, EAFLicenseType license)
	:CPropertySheet(_T("Legal Notice"),pParent,0)
{
   m_License = license;
   m_bGiveChoice = TRUE;
   Init();
}

CEAFLegalNoticeWiz::~CEAFLegalNoticeWiz()
{
}


BEGIN_MESSAGE_MAP(CEAFLegalNoticeWiz, CPropertySheet)
END_MESSAGE_MAP()

// CEAFLegalNoticeWiz message handlers
void CEAFLegalNoticeWiz::Init()
{
   m_Page1.m_psp.dwFlags ^= PSP_HASHELP;
   m_Page2.m_psp.dwFlags ^= PSP_HASHELP;
   m_psh.dwFlags ^= PSH_HASHELP;

   m_Page1.SetLicense( m_License );

   AddPage( &m_Page1 );
   AddPage( &m_Page2 );
   SetWizardMode();
}

BOOL CEAFLegalNoticeWiz::OnInitDialog()
{
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

void CEAFLegalNoticeWiz::GiveChoice(BOOL bGiveChoice)
{
   m_bGiveChoice = bGiveChoice;
}

void CEAFLegalNoticeWiz::ShowLegalNoticeAgain(BOOL bShow)
{
   m_Page2.m_DontShowAgain = (bShow ? FALSE : TRUE);
}

BOOL CEAFLegalNoticeWiz::ShowLegalNoticeAgain()
{
   return (m_Page2.m_DontShowAgain == TRUE) ? FALSE : TRUE;
}
