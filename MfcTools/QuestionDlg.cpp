///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2021  Washington State Department of Transportation
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

// QuestionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuestionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// CQuestionDlg dialog

IMPLEMENT_DYNAMIC(CQuestionDlg, CDialog)

CQuestionDlg::CQuestionDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CQuestionDlg::IDD, pParent)
   , m_Answer(_T(""))
{

}

CQuestionDlg::~CQuestionDlg()
{
}

void CQuestionDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_QUESTIONMARK, m_Icon);
   DDX_Text(pDX,IDC_QUESTION,m_Question);
   DDX_Text(pDX,IDC_ANSWER,m_Answer);
}


BEGIN_MESSAGE_MAP(CQuestionDlg, CDialog)
END_MESSAGE_MAP()


// CQuestionDlg message handlers

BOOL CQuestionDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   SetWindowText(m_Title);

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

      CWnd* pAnswer = GetDlgItem(IDC_ANSWER);
      CWnd* pOK = GetDlgItem(IDOK);
      CWnd* pCancel = GetDlgItem(IDCANCEL);

      CRect rAnswer;
      pAnswer->GetWindowRect(&rAnswer);
      rAnswer.top += diff;
      rAnswer.bottom += diff;
      ScreenToClient(&rAnswer);
      pAnswer->MoveWindow(rAnswer);

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
   }
   dc.SelectObject(pOldFont);

   m_Icon.SetIcon(::LoadIcon(nullptr,IDI_QUESTION));

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
