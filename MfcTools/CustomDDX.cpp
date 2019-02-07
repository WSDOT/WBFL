///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include <MFCTools\CustomDDX.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void DDX_String( CDataExchange* pDX, int nIDC, std::_tstring& str )
{
	HWND hWndCtrl = pDX->PrepareEditCtrl( nIDC );
	if ( pDX->m_bSaveAndValidate )
	{
		int nLen = ::GetWindowTextLength( hWndCtrl ) + 1;
      LPTSTR text = new TCHAR[ nLen ];
		::GetWindowText( hWndCtrl, text, nLen );
      str.assign( text );
      delete[] text;
	}
	else
	{
		AfxSetWindowText( hWndCtrl, str.c_str() );
	}
}

void DDX_LBString(CDataExchange* pDX, int nIDC, std::_tstring& value)
{
   HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		int nIndex = (int)::SendMessage(hWndCtrl, LB_GETCURSEL, 0, 0L);
		if (nIndex != -1)
		{
			int nLen = (int)::SendMessage(hWndCtrl, LB_GETTEXTLEN, nIndex, 0L);
         CString string;
			::SendMessage(hWndCtrl, LB_GETTEXT, nIndex,
					(LPARAM)(LPVOID)string.GetBufferSetLength(nLen));
         value = string;
         string.ReleaseBuffer();
		}
		else
		{
			// no selection
         value = std::_tstring();
		}
	}
	else
	{
		// set current selection based on data string
		if (::SendMessage(hWndCtrl, LB_SELECTSTRING, (WPARAM)-1,
		  (LPARAM)(LPCTSTR)value.c_str()) == LB_ERR)
		{
			// no selection match
			TRACE0("Warning: no listbox item selected.\n");
		}
	}
}

void DDX_LBStringExact(CDataExchange* pDX, int nIDC, std::_tstring& value)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		DDX_LBString(pDX, nIDC, value);
	}
	else
	{
		// set current selection based on data string
		int i = (int)::SendMessage(hWndCtrl, LB_FINDSTRINGEXACT, (WPARAM)-1,
		  (LPARAM)(LPCTSTR)value.c_str());
		if (i < 0)
		{
			// no selection match
			TRACE0("Warning: no listbox item selected.\n");
		}
		else
		{
			// select it
			SendMessage(hWndCtrl, LB_SETCURSEL, i, 0L);
		}
	}
}

void DDX_CBString( CDataExchange* pDX, int nIDC, std::_tstring& str )
{
   HWND hWnd = pDX->PrepareCtrl( nIDC );
   if ( pDX->m_bSaveAndValidate )
   {
      // Just get current edit item text (or drop list static)
      int len = ::GetWindowTextLength( hWnd );
      if ( len < 0 )
         len = 255;

      // Get length
      LPTSTR buffer = new TCHAR[len+1];
      ::GetWindowText( hWnd, buffer, len+1 );
      str = buffer;
      delete[] buffer;
   }
   else
   {
		// set current selection based on model string
		if (::SendMessage(hWnd, CB_SELECTSTRING, (WPARAM)-1,
			(LPARAM)(LPCTSTR)str.c_str()) == CB_ERR)
		{
			// just set the edit text (will be ignored if DROPDOWNLIST)
			AfxSetWindowText(hWnd, str.c_str() );
		}
   }
}

void DDX_CBStringExact(CDataExchange* pDX, int nIDC, std::_tstring& str)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		DDX_CBString(pDX, nIDC, str);
	}
	else
	{
		// set current selection based on data string
		int i = (int)::SendMessage(hWndCtrl, CB_FINDSTRINGEXACT, (WPARAM)-1,
		  (LPARAM)(LPCTSTR)str.c_str());
		if (i < 0)
		{
			// just set the edit text (will be ignored if DROPDOWNLIST)
			AfxSetWindowText(hWndCtrl, str.c_str() );
		}
		else
		{
			// select it
			SendMessage(hWndCtrl, CB_SETCURSEL, i, 0L);
		}
	}
}

void DDX_CBStringExactCase(CDataExchange* pDX, int nIDC, std::_tstring& str)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		DDX_CBString(pDX, nIDC, str);
	}
	else
	{
		// set current selection based on data string
      int startSearch = -1;
      bool bDone = false;
      do 
      {
		   int i = (int)::SendMessage(hWndCtrl, CB_FINDSTRINGEXACT, (WPARAM)startSearch,(LPARAM)(LPCTSTR)str.c_str());

		   if (i < 0)
		   {
            // the text hasn't been found yet and nothing has been set
            // the string isn't in the combo box
			   // just set the edit text (will be ignored if DROPDOWNLIST)
			   AfxSetWindowText(hWndCtrl, str.c_str() );
            bDone = true;
		   }
		   else
		   {
            LRESULT len = ::SendMessage(hWndCtrl,CB_GETLBTEXTLEN,(WPARAM)i,(LPARAM)0);
            if ( len < 0 )
               len = 255;

            LPTSTR buffer = new TCHAR[len+1];
            ::SendMessage(hWndCtrl, CB_GETLBTEXT, (WPARAM)i, (LPARAM)buffer); 

            std::_tstring strText(buffer);
            if ( strText == str )
            {
			      // select it
			      SendMessage(hWndCtrl, CB_SETCURSEL, i, 0L);
               bDone = true;
            }
            startSearch = i;
            delete[] buffer;
		   }
      } while ( !bDone );
	}
}

void DDX_CBStringExactCase(CDataExchange* pDX, int nIDC, CString& str)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		DDX_CBString(pDX, nIDC, str);
	}
	else
	{
		// set current selection based on data string
      int startSearch = -1;
      bool bDone = false;
      do 
      {
		   int i = (int)::SendMessage(hWndCtrl, CB_FINDSTRINGEXACT, (WPARAM)startSearch,(LPARAM)(LPCTSTR)str);

		   if (i < 0)
		   {
            // the text hasn't been found yet and nothing has been set
            // the string isn't in the combo box
			   // just set the edit text (will be ignored if DROPDOWNLIST)
			   AfxSetWindowText(hWndCtrl, str );
            bDone = true;
		   }
		   else
		   {
            LRESULT len = ::SendMessage(hWndCtrl,CB_GETLBTEXTLEN,(WPARAM)i,(LPARAM)0);
            if ( len < 0 )
               len = 255;

            LPTSTR buffer = new TCHAR[len+1];
            ::SendMessage(hWndCtrl, CB_GETLBTEXT, (WPARAM)i, (LPARAM)buffer); 

            CString strText(buffer);
            if ( strText == str )
            {
			      // select it
			      SendMessage(hWndCtrl, CB_SETCURSEL, i, 0L);
               bDone = true;
            }
            startSearch = i;
            delete[] buffer;
		   }
      } while ( !bDone );
	}
}

void DDX_CBIndex(CDataExchange* pDX, int nIDC, IndexType& index)
{
	pDX->PrepareCtrl(nIDC);
	HWND hWndCtrl;
	pDX->m_pDlgWnd->GetDlgItem(nIDC, &hWndCtrl);
	if (pDX->m_bSaveAndValidate)
		index = (IndexType)::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);
	else
		::SendMessage(hWndCtrl, CB_SETCURSEL, (WPARAM)index, 0L);
}

void DDV_NonNegativeDouble(CDataExchange* pDX, int nIDC,Float64 value)
{
	if (!pDX->m_bSaveAndValidate)
	{
		TRACE0("Warning: initial dialog data is out of range.\n");
		return;         // don't stop now
	}

   if(value<0.0)
   {
      pDX->PrepareEditCtrl(nIDC);
	   AfxMessageBox(_T("Please enter non-negative number!"), MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

void DDV_GreaterThanZero(CDataExchange* pDX, int nIDC,Float64 value)
{
	if (!pDX->m_bSaveAndValidate)
	{
		TRACE0("Warning: initial dialog data is out of range.\n");
		return;         // don't stop now
	}

   if( !(value > 0.0) )
   {
      pDX->PrepareEditCtrl(nIDC);
	   AfxMessageBox(_T("Please enter a number that is greater than zero!"), MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

void DDX_Check_Bool(CDataExchange* pDX, int nIDC, bool& value)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		int val = (int)::SendMessage(hWndCtrl, BM_GETCHECK, 0, 0L);
		ASSERT(val >= 0 && val <= 2);
      value = (val == BST_CHECKED ? true : false);
	}
	else
	{
      int val = (value ? BST_CHECKED : BST_UNCHECKED);
		::SendMessage(hWndCtrl, BM_SETCHECK, (WPARAM)val, 0L);
	}
}

void DDX_Text(CDataExchange* pDX, int nIDC, Uint16& value)
{
   int val;
   if ( pDX->m_bSaveAndValidate )
   {
      DDX_Text( pDX, nIDC, val );
      ASSERT( val >= 0 );
      value = val;
   }
   else
   {
      val = value;
      DDX_Text( pDX, nIDC, val );
   }
}

void DDX_Percentage(CDataExchange* pDX,int nIDC,Float64& value)
{
   Float64 v;
   if ( pDX->m_bSaveAndValidate )
   {
      DDX_Text(pDX,nIDC,v);
      value = v/100;
   }
   else
   {
      v = 100*value;
      DDX_Text(pDX,nIDC,v);
   }
}

void DDX_Fractional(CDataExchange* pDX,int nIDC,Float64& value)
{
   Float64 v;
   if ( pDX->m_bSaveAndValidate )
   {
      DDX_Text(pDX,nIDC,v);
      value = -v/100;
   }
   else
   {
      v = -100*value;
      DDX_Text(pDX,nIDC,v);
   }
}


void DDV_LimitOrMore(CDataExchange* pDX,int nIDC,Float64 value,Float64 min)
{
	if (!pDX->m_bSaveAndValidate)
	{
		return;         // don't stop now
	}

   if( value < min )
   {
      pDX->PrepareEditCtrl(nIDC);
      CString msg;
      msg.Format(_T("Please enter a number that is equal to or greater than %f"),min);
      AfxMessageBox( msg, MB_ICONEXCLAMATION );
	   pDX->Fail();
   }
}

void DDV_Range(CDataExchange* pDX, mfcDDV::LowerBound lower,mfcDDV::UpperBound upper,Float64 value,Float64 min,Float64 max)
{
   if ( !pDX->m_bSaveAndValidate )
      return;

   std::_tstring strLower;
   std::_tstring strUpper;

   bool bPassedLower = false;
   if ( lower == mfcDDV::LT )
   {
      strLower = _T("greater than");
      if ( min < value )
         bPassedLower = true;
   }
   else
   {
      strLower = _T("greater than or equal to");
      if ( IsLE(min,value) )
         bPassedLower = true;
   }

   bool bPassedUpper = false;
   if ( upper == mfcDDV::GT )
   {
      strUpper = _T("less than");
      if ( value < max )
         bPassedUpper = true;
   }
   else
   {
      strUpper = _T("less than or equal to");
      if ( IsGE(value,max) )
         bPassedUpper = true;
   }

   if ( !bPassedLower || !bPassedUpper )
   {
      CString msg;
      msg.Format(_T("Please enter a number that is %s %f and %s %f"),min,strLower.c_str(),strUpper.c_str(),max);
      AfxMessageBox( msg, MB_ICONEXCLAMATION );
	   pDX->Fail();
   }
}

void DDX_CBItemData( CDataExchange* pDX, int nIDC, bool& itemdata )
{
   HWND hWnd = pDX->PrepareCtrl( nIDC );
   CComboBox* pCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

   if ( pDX->m_bSaveAndValidate )
   {
      int selidx = pCB->GetCurSel();
      if ( selidx != CB_ERR )
         itemdata = pCB->GetItemData(selidx) != 0 ? true : false;
   }
   else
   {
      int count = pCB->GetCount();
      for ( int i = 0; i < count; i++ )
      {
         bool bItemData = pCB->GetItemData(i) != 0 ? true : false;
         if ( bItemData == itemdata )
         {
            pCB->SetCurSel(i);
            return;
         }
      }
      ASSERT(0 == count || !::IsWindowEnabled(hWnd) ); // nothing was selected (doesn't assert if count == 0 or window is disabled)
   }
}
