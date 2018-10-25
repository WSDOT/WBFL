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

#include "StdAfx.h"
#include <MfcTools\Text.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void MultiLineTextOut(CDC* pDC,int x,int y,LPCTSTR lpszText)
{
   CString strText(lpszText);

   // force string to be null terminated
   if ( strText[strText.GetLength()-1] != '\n' )
   {
      strText += '\n';
   }

   // Parse the string for \n
   // Write each line on a new line in the dc
   TEXTMETRIC tm;
   pDC->GetTextMetrics(&tm);
   int pos = 0;
   int line = 0;
   do
   {
      pos = strText.Find('\n');

      CString strLine(strText.Left(pos));
      pDC->TextOut(x,y+line*tm.tmHeight,strLine);

      strText = strText.Mid(pos+1);
      line++;
   } while ( 0 < strText.GetLength() );
}

void ChangeComboBoxString(CComboBox* pCB,int idx,LPCTSTR lpszNewString)
{
   int cursel = pCB->GetCurSel();
   DWORD_PTR itemData = pCB->GetItemData(idx);
   void* pItemPtr = pCB->GetItemDataPtr(idx);
   pCB->DeleteString(idx);
   pCB->InsertString(idx,lpszNewString);
   pCB->SetItemData(idx,itemData);
   pCB->SetItemDataPtr(idx,pItemPtr);
   pCB->SetCurSel(cursel);
}
