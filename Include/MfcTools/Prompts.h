///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2015  Washington State Department of Transportation
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

#pragma once

#include <MfcTools\MfcToolsExp.h>

// Use this function to ask the user a question. The return value is the user's answer
BOOL MFCTOOLSFUNC AfxQuestion(LPCTSTR lpszTitle,LPCTSTR lpszQuestion,LPCTSTR lpszDefault,CString& strAnswer);

// This function prompts the user with a question. The user has to select from a list of
// responses. lpszResponses is a \n separated list of responses. defChoice is the index of the
// default choice. The return value is the index of the selected choice or -1 if the Cancel button was pressed
int MFCTOOLSFUNC AfxChoose(LPCTSTR lpszTitle,LPCTSTR lpszQuestion,LPCTSTR lpszResponses,int defChoice=0,BOOL bCancelButton=FALSE,LPCTSTR lpszHelpFile=NULL,UINT helpID=0);

// A validator object for the AfxMultiChoice method
// The select list of options is passed to the IsValid method to validate the
// choices. Over-ride IsValid in a sub-class to provide context specific validation
class MFCTOOLSCLASS CMultiChoiceValidator
{
public:
   virtual BOOL IsValid(const std::vector<int>& options) {return TRUE;}
   virtual void DisplayValidationErrorMessage() {};
};

// This function prompts the user with a question. The use has to select one or more items from a list
// of options. lpszOptions is a \n separated list of options.  defChoice is the index of the
// default choice. The return value is the index of the selected choice or -1 if the Cancel button was pressed
std::vector<int> MFCTOOLSFUNC AfxMultiChoice(LPCTSTR lpszTitle,LPCTSTR lpszQuestion,LPCTSTR lpszOptions,CMultiChoiceValidator* pValidator=NULL,const std::vector<int>& defOptions=std::vector<int>(),BOOL bCancelButton=FALSE,LPCTSTR lpszHelpFile=NULL,UINT helpID=0);