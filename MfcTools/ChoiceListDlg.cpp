///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2014  Washington State Department of Transportation
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

// ChoiceListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChoiceListDlg.h"


// CChoiceListDlg dialog

IMPLEMENT_DYNAMIC(CChoiceListDlg, CDialog)

CChoiceListDlg::CChoiceListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoiceListDlg::IDD, pParent)
{
}

CChoiceListDlg::~CChoiceListDlg()
{
}

void CChoiceListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_QUESTIONMARK, m_Icon);
   DDX_Control(pDX, IDC_LIST, m_List);

   DDX_Text(pDX,IDC_QUESTION,m_Question);

   if ( pDX->m_bSaveAndValidate )
   {
      m_Choices.clear();
      int nOptions = m_List.GetSelCount();
      CArray<int,int> options;
      options.SetSize(nOptions);
      m_List.GetSelItems(nOptions,options.GetData());
      for ( int i = 0; i < nOptions; i++ )
      {
         m_Choices.push_back(options[i]);
      }

      if ( m_pValidator && !m_pValidator->IsValid(m_Choices) )
      {
         m_pValidator->DisplayValidationErrorMessage();
         pDX->PrepareCtrl(IDC_LIST);
         pDX->Fail();
      }
   }
   else
   {
      // Put choices into the check box list
      std::vector<int>::iterator iter(m_Choices.begin());
      std::vector<int>::iterator end(m_Choices.end());
      for ( ; iter != end; iter++ )
      {
         m_List.SetSel(*iter);
      }
   }
}


BEGIN_MESSAGE_MAP(CChoiceListDlg, CDialog)
   ON_BN_CLICKED(IDHELP,OnHelp)
END_MESSAGE_MAP()


// CChoiceListDlg message handlers

BOOL CChoiceListDlg::OnInitDialog()
{
   SetWindowText(m_Title);

   CListBox* pcbList = (CListBox*)GetDlgItem(IDC_LIST);

   CString resToken;
   int curPos = 0;
   resToken = m_Options.Tokenize( _T("\n") ,curPos);
   while ( resToken != "" )
   {
      pcbList->AddString(resToken);
      resToken = m_Options.Tokenize(_T("\n"),curPos);
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

   if ( m_HelpFile.GetLength() == 0 )
   {
      GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
   }

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoiceListDlg::OnHelp()
{
   ::HtmlHelp(*this,m_HelpFile,HH_HELP_CONTEXT,m_HelpID);
}