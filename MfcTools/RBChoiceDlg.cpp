///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
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

// RBChoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RBChoiceDlg.h"


// CRBChoiceDlg dialog

IMPLEMENT_DYNAMIC(CRBChoiceDlg, CDialog)

CRBChoiceDlg::CRBChoiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRBChoiceDlg::IDD, pParent)
{
   m_Choice = 0;
   m_pHelpHandler = NULL;
}

CRBChoiceDlg::~CRBChoiceDlg()
{
}

void CRBChoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_QUESTIONMARK, m_Icon);
   DDX_Text(pDX,IDC_QUESTION,m_Question);

   DDX_Radio(pDX,IDC_RADIO1,m_Choice);
}


BEGIN_MESSAGE_MAP(CRBChoiceDlg, CDialog)
   ON_BN_CLICKED(IDHELP,OnHelp)
END_MESSAGE_MAP()


// CRBChoiceDlg message handlers

BOOL CRBChoiceDlg::OnInitDialog()
{
   SetWindowText(m_Title);

   int nRadioButtons = 4;
   int rbIdx = 0;
   CString resToken;
   int curPos = 0;
   resToken = m_Responses.Tokenize( _T("\n") ,curPos);
   while ( resToken != "" && rbIdx < nRadioButtons )
   {
      int nIDC = (rbIdx + IDC_RADIO1);
      CWnd* pWnd = GetDlgItem(nIDC);
      pWnd->SetWindowText(resToken);
      resToken = m_Responses.Tokenize(_T("\n"),curPos);
      rbIdx++;
   }

   // hide all the left overs
   for ( int i = rbIdx; i < nRadioButtons; i++ )
   {
      int nIDC = (i + IDC_RADIO1);
      CWnd* pWnd = GetDlgItem(nIDC);
      pWnd->ShowWindow(SW_HIDE);
   }

   CDialog::OnInitDialog();

   m_Icon.SetIcon(::LoadIcon(NULL,IDI_QUESTION));

   if ( !m_bCancel )
   {
      CWnd* pCancel = GetDlgItem(IDCANCEL);
      CWnd* pOK     = GetDlgItem(IDOK);

      CRect rCancel;
      pCancel->GetWindowRect(&rCancel);

      ScreenToClient(&rCancel);

      pOK->MoveWindow(rCancel);
      pCancel->ShowWindow(SW_HIDE);

      ModifyStyle(WS_SYSMENU,0);
   }

   if ( m_pHelpHandler == NULL )
   {
      GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
   }

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CRBChoiceDlg::OnHelp()
{
   if ( m_pHelpHandler )
   {
      m_pHelpHandler->OnHelp();
   }
}