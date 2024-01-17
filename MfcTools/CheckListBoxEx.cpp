///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2024  Washington State Department of Transportation
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

// StaticSplitter.cpp : implementation file
//

#include "stdafx.h"
#include <MfcTools\CheckListBoxEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// https://www.codeproject.com/Articles/1715/ListBox-With-ToolTip-Support 

//IMPLEMENT_DYNCREATE(CCheckListBoxEx, CCheckListBox)

/////////////////////////////////////////////////////////////////////////////
// CCheckListBoxEx

CCheckListBoxEx::CCheckListBoxEx()
{
}

CCheckListBoxEx::~CCheckListBoxEx()
{
}


BEGIN_MESSAGE_MAP(CCheckListBoxEx, CCheckListBox)
	//{{AFX_MSG_MAP(CCheckListBoxEx)
		// NOTE - the ClassWizard will add and remove mapping macros here.

	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckListBoxEx message handlers

void CCheckListBoxEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	

	CCheckListBox::PreSubclassWindow();
	EnableToolTips(TRUE);

}

INT_PTR CCheckListBoxEx::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	int row;
	RECT cellrect;   // cellrect		- to hold the bounding rect
	BOOL tmp = FALSE;
	row  = ItemFromPoint(point,tmp);  //we call the ItemFromPoint function to determine the row,
	//note that in NT this function may fail  use the ItemFromPointNT member function

	if ( row == -1 ) 
		return -1;

	//set up the TOOLINFO structure. GetItemRect(row,&cellrect);
	GetItemRect(row,&cellrect);
	pTI->rect = cellrect;
	pTI->hwnd = m_hWnd;
	pTI->uId = (UINT)((row));   //The ‘uId’ is assigned a value according to the row value.
	pTI->lpszText = LPSTR_TEXTCALLBACK;
	return pTI->uId;
}


//Define OnToolTipText(). This is the handler for the TTN_NEEDTEXT notification from 
//support ansi and unicode 
BOOL CCheckListBoxEx::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	CString strTipText;
	UINT_PTR nID = pNMHDR->idFrom;
	
	GetText( (int)nID ,strTipText);

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, 80);
	else
		_mbstowcsz(pTTTW->szText, strTipText, 80);
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, 80);
	else
		lstrcpyn(pTTTW->szText, strTipText, 80);
#endif
	*pResult = 0;

	return TRUE;    
}

UINT CCheckListBoxEx::ItemFromPoint2(CPoint pt, BOOL& bOutside) const

// CListBox::ItemFromPoint does not work on NT.

{
	int nFirstIndex, nLastIndex;
	//GetFirstAndLastIndex(nFirstIndex, nLastIndex);
	nFirstIndex = GetTopIndex();
	nLastIndex = nFirstIndex  + GetCount(); 
	
	bOutside = TRUE;
	
	CRect Rect;
	int nResult = -1;
	
	for (int i = nFirstIndex; nResult == -1 && i <= nLastIndex; i++)
	{
		if (GetItemRect(i, &Rect) != LB_ERR)
		{
			if (Rect.PtInRect(pt))
			{
				nResult  = i;
				bOutside = FALSE;
			}
		}
		
	}
	
	return nResult;
}

void CCheckListBoxEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   // set item height once:    
   if ((GetStyle() & (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS)) ==
                     (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS)  && m_cyText == 0)
   {
      SetItemHeight(0, CalcMinimumItemHeight() + 2);
   }

   // add some space between box and string: 
   lpDrawItemStruct->rcItem.left += 2;

   CCheckListBox::DrawItem(lpDrawItemStruct);
}

