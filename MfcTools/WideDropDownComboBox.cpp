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
