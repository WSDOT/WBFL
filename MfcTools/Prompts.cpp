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

#include "StdAfx.h"
#include <MfcTools\Prompts.h>
#include "QuestionDlg.h"
#include "ChoiceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString AfxQuestion(LPCTSTR lpszTitle,LPCTSTR lpszQuestion,LPCTSTR lpszDefault)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   CQuestionDlg dlg;
   dlg.m_Title = lpszTitle;
   dlg.m_Question = lpszQuestion;
   dlg.m_Answer = lpszDefault;
   dlg.DoModal();

   return dlg.m_Answer;
}

int AfxChoose(LPCTSTR lpszTitle,LPCTSTR lpszQuestion,LPCTSTR lpszResponses,BOOL bCancelButton,int defChoice,LPCTSTR lpszHelpFile,UINT helpID)
{
   AFX_MANAGE_STATE(AfxGetAppModuleState());

   CChoiceDlg dlg;
   dlg.m_bCancel = bCancelButton;
   dlg.m_Title = lpszTitle;
   dlg.m_Question = lpszQuestion;
   dlg.m_Responses = lpszResponses;
   dlg.m_Choice = defChoice;
   dlg.m_HelpFile = lpszHelpFile;
   dlg.m_HelpID = helpID;

   if ( dlg.DoModal() == IDOK )
      return dlg.m_Choice;
   else
      return -1;
}