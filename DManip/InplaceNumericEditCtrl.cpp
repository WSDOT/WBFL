///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// FloatEdit.cpp : implementation file
//

#include "stdafx.h"
#include <DManip\InplaceNumericEditCtrl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInplaceNumericEdit

CInplaceNumericEdit::CInplaceNumericEdit()
{
}

CInplaceNumericEdit::~CInplaceNumericEdit()
{
}


BEGIN_MESSAGE_MAP(CInplaceNumericEdit, CInplaceEdit)
	//{{AFX_MSG_MAP(CInplaceNumericEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit message handlers

void CInplaceNumericEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

  int              i, num_typed, start_char, end_char;
  int              nELoc        = -1;
  BOOL             nPeriodLoc   = -1;
  BOOL             bSignTyped   = FALSE;
  BOOL             bESignTyped  = FALSE;
  CString          temp_str;

    // this is the set of printing characters that we will NOT allow for
    // float edit fields. The reason we do it this way instead of specifying
    // what we DO want is because we need to allow all nonprinting characters
    // such as shift, control, arrows, etc., and we cannot mask all of those.
  CString          Holder = "`~!@#$%^&*()_=qwrtyuiop[]\\asdfghjkl;\'zxcvbnm,/QWRTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?/ ";

    // 1st pass on unwanted characters
  if (Holder.Find(nChar) != -1)
    return;

    // length, selection info
  num_typed = CEdit::GetWindowTextLength();
  GetSel(start_char, end_char);

    // current CEdit text
  GetWindowText(temp_str);

    // most of the work done in here..
  for (i = 0; i < temp_str.GetLength(); i++) {
        // selected chars don't count..
    if ((i >= start_char) && (i < end_char))
      continue;

    switch (temp_str[i]) {

      case '+':
      case '-':
        if (nELoc >= 0)
          bESignTyped = TRUE;
        else
          bSignTyped = TRUE;
        break;

      case '.':
        nPeriodLoc = i;
        break;

      case 'e':
      case 'E':
        nELoc = i;
        break;
    }
  }

    // determine if new character is valid
  switch (nChar) {

      // allow sign only once, and only on the first char
    case '+':
    case '-':
      if (start_char == 0) {
        if (bSignTyped)
          return;
      }
      else if ((start_char-1) == nELoc) {
        if (bESignTyped)
          return;
      }
      else {
        return;
      }
      break;

      // allow period only once
    case '.':
      if (nPeriodLoc != -1)
        return;
      break;

    case 'e':
    case 'E':
        // only allow one 'e'
      if (nELoc != -1)
        return;
        // don't allow 'e' before the period
      if (start_char <= nPeriodLoc)
        return;
      break;
  }

    // if we get here, the character is ok
	CInplaceEdit::OnChar(nChar, nRepCnt, nFlags);
}
