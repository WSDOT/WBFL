///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2011  Washington State Department of Transportation
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

// ChoiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChoiceDlg.h"


// CChoiceDlg dialog

IMPLEMENT_DYNAMIC(CChoiceDlg, CDialog)

CChoiceDlg::CChoiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoiceDlg::IDD, pParent)
{
   m_Choice = 0;
}

CChoiceDlg::~CChoiceDlg()
{
}

void CChoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_QUESTIONMARK, m_Icon);
   DDX_Text(pDX,IDC_QUESTION,m_Question);

   DDX_CBIndex(pDX,IDC_RESPONSE_CHOICES,m_Choice);
}


BEGIN_MESSAGE_MAP(CChoiceDlg, CDialog)
   ON_BN_CLICKED(IDHELP,OnHelp)
END_MESSAGE_MAP()


// CChoiceDlg message handlers

BOOL CChoiceDlg::OnInitDialog()
{
   SetWindowText(m_Title);

   CComboBox* pcbResponses = (CComboBox*)GetDlgItem(IDC_RESPONSE_CHOICES);

   CString resToken;
   int curPos = 0;
   resToken = m_Responses.Tokenize( _T("\n") ,curPos);
   while ( resToken != "" )
   {
      pcbResponses->AddString(resToken);
      resToken = m_Responses.Tokenize(_T("\n"),curPos);
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
   }

   if ( m_HelpFile.GetLength() == 0 )
   {
      GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
   }

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoiceDlg::OnHelp()
{
   ::HtmlHelp(*this,m_HelpFile,HH_HELP_CONTEXT,m_HelpID);
}