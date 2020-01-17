///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include "resource.h"
#include "ChoiceListDlg.h"
#include <MFCTools\Prompts.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// CChoiceListDlg dialog

IMPLEMENT_DYNAMIC(CChoiceListDlg, CDialog)

CChoiceListDlg::CChoiceListDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CChoiceListDlg::IDD, pParent)
{
   m_bCheckList = FALSE;
   m_pValidator = nullptr;
   m_pHelpHandler = nullptr;
}

CChoiceListDlg::~CChoiceListDlg()
{
}

void CChoiceListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_QUESTIONMARK, m_Icon);

   DDX_Control(pDX, IDC_LIST, m_List);
   DDX_Control(pDX, IDC_CHECKLIST, m_CheckList);

   DDX_Text(pDX,IDC_QUESTION,m_Question);

   if ( pDX->m_bSaveAndValidate )
   {
      m_Choices.clear();
      if ( m_bCheckList )
      {
         int nOptions = m_CheckList.GetCount();
         for ( int idx = 0; idx < nOptions; idx++ )
         {
            if ( m_CheckList.GetCheck(idx) == BST_CHECKED )
            {
               m_Choices.push_back(idx);
            }
         }
      }
      else
      {
         int nOptions = m_List.GetSelCount();
         CArray<int,int> options;
         options.SetSize(nOptions);
         m_List.GetSelItems(nOptions,options.GetData());
         for ( int idx = 0; idx < nOptions; idx++ )
         {
            m_Choices.push_back(options[idx]);
         }
      }

      if ( m_pValidator && !m_pValidator->IsValid(m_Choices) )
      {
         m_pValidator->DisplayValidationErrorMessage();
         pDX->PrepareCtrl(IDC_LIST);
         pDX->Fail();
      }
   }
}


BEGIN_MESSAGE_MAP(CChoiceListDlg, CDialog)
   ON_BN_CLICKED(IDHELP,OnHelp)
END_MESSAGE_MAP()


// CChoiceListDlg message handlers

BOOL CChoiceListDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   if ( m_bCheckList )
   {
      m_List.ShowWindow(SW_HIDE);
   }
   else
   {
      m_CheckList.ShowWindow(SW_HIDE);
   }

   SetWindowText(m_Title);

   CString resToken;
   int curPos = 0;
   resToken = m_Options.Tokenize( _T("\n") ,curPos);
   while ( resToken != "" )
   {
      if ( m_bCheckList )
      {
         m_CheckList.AddString(resToken);
      }
      else
      {
         m_List.AddString(resToken);
      }
      resToken = m_Options.Tokenize(_T("\n"),curPos);
   }

   for( const auto& idx : m_Choices)
   {
      if ( m_bCheckList )
      {
         m_CheckList.SetCheck(idx,BST_CHECKED);
      }
      else
      {
         m_List.SetSel(idx);
      }
   }

   // resize dialog to fit the question text
   CWnd* pwndQuestion = GetDlgItem(IDC_QUESTION);
   CClientDC dc(this);
   CFont* pOldFont = dc.SelectObject(pwndQuestion->GetFont());
   CRect rect;
   pwndQuestion->GetClientRect(&rect);
   CRect rWnd = rect;
   dc.DrawText(m_Question, &rect, DT_CALCRECT | DT_NOPREFIX | DT_EDITCONTROL | DT_WORDBREAK); // get the required size of the question static control
   pwndQuestion->SetWindowPos(nullptr, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE); // resize the question static control
   auto diff = rect.Height() - rWnd.Height();
   if (0 < diff)
   {
      // the height of the static control grew, so resize the dialog and move the buttons down
      CRect rDlg;
      GetWindowRect(&rDlg);
      rDlg.bottom += diff;
      MoveWindow(rDlg);

      CRect rList;
      m_List.GetWindowRect(&rList);
      rList.top += diff;
      rList.bottom += diff;
      ScreenToClient(&rList);
      m_List.MoveWindow(rList);

      CRect rCheckList;
      m_CheckList.GetWindowRect(&rCheckList);
      rCheckList.top += diff;
      rCheckList.bottom += diff;
      ScreenToClient(&rCheckList);
      m_CheckList.MoveWindow(rCheckList);

      CWnd* pOK = GetDlgItem(IDOK);
      CWnd* pCancel = GetDlgItem(IDCANCEL);
      CWnd* pHelp = GetDlgItem(IDHELP);

      CRect rOK;
      pOK->GetWindowRect(&rOK);
      rOK.top += diff;
      rOK.bottom += diff;
      ScreenToClient(&rOK);
      pOK->MoveWindow(rOK);

      CRect rCancel;
      pCancel->GetWindowRect(&rCancel);
      rCancel.top += diff;
      rCancel.bottom += diff;
      ScreenToClient(&rCancel);
      pCancel->MoveWindow(rCancel);

      CRect rHelp;
      pHelp->GetWindowRect(&rHelp);
      rHelp.top += diff;
      rHelp.bottom += diff;
      ScreenToClient(&rHelp);
      pHelp->MoveWindow(rHelp);
   }
   dc.SelectObject(pOldFont);

   m_Icon.SetIcon(::LoadIcon(nullptr,IDI_QUESTION));

   if ( m_bCancel && m_pHelpHandler == nullptr )
   {
      // [OK][Cancel]
      CWnd* pOK     = GetDlgItem(IDOK);
      CWnd* pCancel = GetDlgItem(IDCANCEL);
      CWnd* pHelp   = GetDlgItem(IDHELP);
      
      CRect rHelp;
      pHelp->GetWindowRect(&rHelp);
      
      CRect rCancel;
      pCancel->GetWindowRect(&rCancel);

      pHelp->ShowWindow(SW_HIDE);
      ScreenToClient(&rHelp);
      ScreenToClient(&rCancel);
      pCancel->MoveWindow(rHelp);
      pOK->MoveWindow(rCancel);
   }
   else if ( !m_bCancel && m_pHelpHandler != nullptr )
   {
      // [OK][Help]
      CWnd* pOK     = GetDlgItem(IDOK);
      CWnd* pCancel = GetDlgItem(IDCANCEL);
      
      CRect rCancel;
      pCancel->GetWindowRect(&rCancel);

      ScreenToClient(&rCancel);
      pCancel->ShowWindow(SW_HIDE);
      pOK->MoveWindow(rCancel);
      ModifyStyle(WS_SYSMENU,0);
   }
   else if ( !m_bCancel && m_pHelpHandler == nullptr )
   {
      // [OK]
      CWnd* pOK     = GetDlgItem(IDOK);
      CWnd* pCancel = GetDlgItem(IDCANCEL);
      CWnd* pHelp   = GetDlgItem(IDHELP);
      
      CRect rHelp;
      pHelp->GetWindowRect(&rHelp);

      pHelp->ShowWindow(SW_HIDE);
      pCancel->ShowWindow(SW_HIDE);

      ScreenToClient(&rHelp);
      pOK->MoveWindow(rHelp);
      ModifyStyle(WS_SYSMENU,0);
   }

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoiceListDlg::OnHelp()
{
   if ( m_pHelpHandler )
   {
      m_pHelpHandler->OnHelp();
   }
}