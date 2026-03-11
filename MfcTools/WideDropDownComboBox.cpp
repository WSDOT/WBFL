///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2026  Washington State Department of Transportation
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

// WideDropDownComboBox.cpp : implementation file
//

#include "stdafx.h"
#include <MfcTools\WideDropDownComboBox.h>


// CWideDropDownComboBox

IMPLEMENT_DYNAMIC(CWideDropDownComboBox, CComboBox)

CWideDropDownComboBox::CWideDropDownComboBox()
{

}

CWideDropDownComboBox::~CWideDropDownComboBox()
{
}


BEGIN_MESSAGE_MAP(CWideDropDownComboBox, CComboBox)
   ON_CONTROL_REFLECT(CBN_DROPDOWN, &CWideDropDownComboBox::OnDropdown)
END_MESSAGE_MAP()


// CWideDropDownComboBox message handlers
void CWideDropDownComboBox::OnDropdown()
{
   RecalcDropWidth();
}

void CWideDropDownComboBox::RecalcDropWidth()
{
   CString str;
   CSize sz;
   int dx = 0;
   TEXTMETRIC tm;
   CDC* pDC = GetDC();
   CFont* pFont = GetFont();

   // Select the listbox font, save the old font
   CFont* pOldFont = pDC->SelectObject(pFont);

   // Get the text metrics for avg char width
   pDC->GetTextMetrics(&tm);

   int nNumEntries = GetCount();
   for (int i = 0; i < nNumEntries; i++)
   {
      GetLBText(i, str);
      sz = pDC->GetTextExtent(str);

      // Add the avg width to prevent clipping
      sz.cx += tm.tmAveCharWidth;
      
      if (dx < sz.cx) dx = sz.cx;
   }

   // Select the old font back into the dc
   pDC->SelectObject(pOldFont);
   ReleaseDC(pDC);

   // Adjust the width for the vertical scroll bar and the left and right border
   dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2 * ::GetSystemMetrics(SM_CXEDGE);

   // Set the width of the list box so that every item is completely visible
   SetDroppedWidth(dx);
}
