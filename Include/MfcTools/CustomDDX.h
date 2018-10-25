///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
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

#ifndef INCLUDED_MFCTOOLS_CUSTOMDDX_H_
#define INCLUDED_MFCTOOLS_CUSTOMDDX_H_
#pragma once

#include <MfcTools\MfcToolsExp.h>
#include <MfcTools\CacheEdit.h>
#include <Units\SysUnits.h>
#include <limits>

void MFCTOOLSFUNC DDX_String(CDataExchange* pDX,int nIDC, std::_tstring& str);
void MFCTOOLSFUNC DDX_LBString(CDataExchange* pDX, int nIDC, std::_tstring& value);
void MFCTOOLSFUNC DDX_LBStringExact(CDataExchange* pDX, int nIDC, std::_tstring& value);
void MFCTOOLSFUNC DDX_CBString(CDataExchange* pDX,int nIDC, std::_tstring& str);
void MFCTOOLSFUNC DDX_CBStringExact(CDataExchange* pDX, int nIDC, std::_tstring& str);
void MFCTOOLSFUNC DDX_CBStringExactCase(CDataExchange* pDX, int nIDC, std::_tstring& str);
void MFCTOOLSFUNC DDX_CBStringExactCase(CDataExchange* pDX, int nIDC, CString& str);
void MFCTOOLSFUNC DDX_CBIndex(CDataExchange* pDX, int nIDC, IndexType& index);
void MFCTOOLSFUNC DDX_CBItemData( CDataExchange* pDX, int nIDC, bool& itemdata );

void MFCTOOLSFUNC DDV_NonNegativeDouble(CDataExchange* pDX, int nIDC,Float64 value);
void MFCTOOLSFUNC DDV_GreaterThanZero(CDataExchange* pDX, int nIDC, Float64 value);
void MFCTOOLSFUNC DDV_LimitOrMore(CDataExchange* pDX,int nIDC,Float64 value,Float64 min);

void MFCTOOLSFUNC DDX_Check_Bool(CDataExchange* pDX, int nIDC, bool& value);
void MFCTOOLSFUNC DDX_Text(CDataExchange* pDX, int nIDC, Uint16& value);

void MFCTOOLSFUNC DDX_Percentage(CDataExchange* pDX,int nIDC,Float64& value);
void MFCTOOLSFUNC DDX_Fractional(CDataExchange* pDX,int nIDC,Float64& value);

class MFCTOOLSCLASS mfcDDV
{
public:
   enum LowerBound { LE, LT };
   enum UpperBound { GT, GE };
};

void MFCTOOLSFUNC DDV_Range(CDataExchange* pDX, mfcDDV::LowerBound lower,mfcDDV::UpperBound upper,Float64 value,Float64 min,Float64 max);

// Exchanges a value or keyword. When putting data into the control, if value is < 0, the
// control is filled with the keyword. When getting data from the control, if the keyword
// is used, value is set to -1, otherwise, a normal DDX_Text is done.
// Only the first three letters of the keyword need to be input.
template <class T>
void DDX_Keyword(CDataExchange* pDX,int nIDC,LPCTSTR lpszKeyword,T& value)
{
   if ( pDX->m_bSaveAndValidate )
   {
      CString strText;
      pDX->m_pDlgWnd->GetDlgItem(nIDC)->GetWindowText(strText);
      strText.Trim();
      CString strKeyword = CString(lpszKeyword).Left(3);
      if ( strText.GetLength() == 0 || strKeyword.CompareNoCase(strText.Left(3)) == 0 )
      {
         value = -1;
      }
      else
      {
         DDX_Text(pDX,nIDC,value);
      }
   }
   else
   {
      if ( value < 0 )
         DDX_Text(pDX,nIDC,CString(lpszKeyword));
      else
         DDX_Text(pDX,nIDC,value);
   }
}

template <class U>
void DDX_KeywordUnitValueAndTag(CDataExchange* pDX,int nIDC,int nIDCTag,LPCTSTR lpszKeyword,Float64& value, const U& umIndirectMeasure)
{
   if ( pDX->m_bSaveAndValidate )
   {
      CString strText;
      pDX->m_pDlgWnd->GetDlgItem(nIDC)->GetWindowText(strText);
      strText.Trim();
      CString strKeyword = CString(lpszKeyword).Left(3);
      if ( strText.GetLength() == 0 || strKeyword.CompareNoCase(strText.Left(3)) == 0 )
      {
         value = -1;
      }
      else
      {
         DDX_UnitValueAndTag(pDX,nIDC,nIDCTag,value, umIndirectMeasure );
      }
   }
   else
   {
      if ( value < 0 )
      {
         DDX_Text(pDX,nIDC,CString(lpszKeyword));
         DDX_Tag(pDX,nIDCTag,umIndirectMeasure);
      }
      else
      {
         DDX_UnitValueAndTag(pDX,nIDC,nIDCTag,value, umIndirectMeasure );
      }
   }
}

template <class T,class U>
void DDV_UnitValueGreaterThanLimit(CDataExchange* pDX, T& value, T limit, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if( !(limit < value) )
   {
      CString msg;
      msg.Format(_T("Please enter a number that is greater than %f %s"), 
                 ::ConvertFromSysUnits( limit, displayUnit ), 
                 displayUnit.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

template <class T,class U>
void DDV_UnitValueLimitOrMore(CDataExchange* pDX, T& value, T limit, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if( !IsEqual(value,limit) && value < limit )
   {
      CString msg;
      msg.Format(_T("Please enter a number that is at least %f %s"), 
                 ::ConvertFromSysUnits( limit, displayUnit ), 
                 displayUnit.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

template <class T,class U>
void DDV_UnitValueLessThanLimit(CDataExchange* pDX, T& value, T limit, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if( !(value < limit) )
   {
      CString msg;
      msg.Format(_T("Please enter a number that is less than %f %s"), 
                 ::ConvertFromSysUnits( limit, displayUnit ), 
                 displayUnit.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

template <class T,class U>
void DDV_UnitValueLimitOrLess(CDataExchange* pDX, T& value, T limit, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if( !IsEqual(limit,value) && limit < value )
   {
      CString msg;
      msg.Format(_T("Please enter a number that is not more than %f %s"), 
                 ::ConvertFromSysUnits( limit, displayUnit ), 
                 displayUnit.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

template <class T,class U>
void DDV_UnitValueRange(CDataExchange* pDX, T& value, T min, T max, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if(  value < min || max < value )
   {
      CString msg;
      msg.Format(_T("Please enter a number in the range %f to %f %s"), 
                 ::ConvertFromSysUnits( min, displayUnit ), 
                 ::ConvertFromSysUnits( max, displayUnit ), 
                 displayUnit.UnitTag().c_str() );
	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

template <class T,class U>
void DDV_UnitValueGreaterThanZero(CDataExchange* pDX, T& value, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   T zero = 0;
   DDV_UnitValueGreaterThanLimit( pDX, value, zero, bUnitModeSI, usDisplayUnit, siDisplayUnit );
}

template <class T,class U>
void DDV_UnitValueLessThanZero(CDataExchange* pDX, T& value, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   T zero = 0;
   DDV_UnitValueLessThanLimit( pDX, value, zero, bUnitModeSI, usDisplayUnit, siDisplayUnit );
}

template <class T,class U>
void DDV_UnitValueZeroOrMore(CDataExchange* pDX, T& value, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   T zero = 0;
   DDV_UnitValueLimitOrMore( pDX, value, zero, bUnitModeSI, usDisplayUnit, siDisplayUnit );
}

template <class T,class U>
void DDV_UnitValueZeroOrLess(CDataExchange* pDX, T& value, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   T zero = 0;
   DDV_UnitValueLimitOrLess( pDX, value, zero, bUnitModeSI, usDisplayUnit, siDisplayUnit );
}

template <class T,class U>
void DDX_UnitValue( CDataExchange* pDX, int nIDC, T& data, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if ( pDX->m_bSaveAndValidate )
	{
      Float64 f;
      DDX_Text( pDX, nIDC, f);
      data = ::ConvertToSysUnits( f, displayUnit );
	}
	else
	{
      Float64 f = ::ConvertFromSysUnits( data, displayUnit );
      DDX_Text( pDX, nIDC, f );
	}
}

template <class T,class U>
void DDX_UnitValueAndTag( CDataExchange* pDX, int nIDC, int nIDCTag, T& data, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if ( pDX->m_bSaveAndValidate )
	{
      Float64 f;
      DDX_Text( pDX, nIDC, f);
      data = ::ConvertToSysUnits( f, displayUnit );
	}
	else
	{
      Float64 f = ::ConvertFromSysUnits( data, displayUnit );
      DDX_Text( pDX, nIDC, f );

      std::_tstring tag = displayUnit.UnitTag();
      DDX_String( pDX, nIDCTag, tag );
	}
}

template <class U>
void DDX_Tag(CDataExchange* pDX, int nIDCTag, bool bUnitModeSI, const U& usDisplayUnit, const U& siDisplayUnit )
{
   const U& displayUnit = (bUnitModeSI ? siDisplayUnit : usDisplayUnit);
	if ( pDX->m_bSaveAndValidate )
	{
	}
	else
	{
      std::_tstring tag = displayUnit.UnitTag();
      DDX_String( pDX, nIDCTag, tag );
	}
}

template <class T>
void DDX_CBItemData( CDataExchange* pDX, int nIDC, T& itemdata )
{
   HWND hWnd = pDX->PrepareCtrl( nIDC );
   CComboBox* pCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

   if ( pDX->m_bSaveAndValidate )
   {
      int selidx = pCB->GetCurSel();
      if ( selidx != CB_ERR )
         itemdata = (T)(pCB->GetItemData(selidx));
   }
   else
   {
      int count = pCB->GetCount();
      for ( int i = 0; i < count; i++ )
      {
         if ( ((T)pCB->GetItemData(i)) == itemdata )
         {
            pCB->SetCurSel(i);
            return;
         }
      }
      ASSERT(0 == count || !::IsWindowEnabled(hWnd) ); // nothing was selected (doesn't assert if count == 0 or window is disabled)
   }
}

template <class T>
void DDX_CBItemData(CDataExchange* pDX,int nIDC, const T* vData,T& itemData)
{
   HWND hWnd = pDX->PrepareCtrl( nIDC );
   CComboBox* pCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

   if ( pDX->m_bSaveAndValidate )
   {
      int selidx = pCB->GetCurSel();
      if ( selidx != CB_ERR )
         itemdata = vData[pCB->GetItemData(selidx)];
   }
   else
   {
      int count = pCB->GetCount();
      for ( int i = 0; i < count; i++ )
      {
         if ( vData[pCB->GetItemData(i)] == itemdata )
         {
            pCB->SetCurSel(i);
            return;
         }
      }
      ASSERT(0 == count || !::IsWindowEnabled(hWnd) ); // nothing was selected (doesn't assert if count == 0 or window is disabled)
   }
}

template <class T>
void DDX_CBEnum(CDataExchange* pDX, int nIDC, T& value)
{
   if ( pDX->m_bSaveAndValidate )
   {
      int item;
      DDX_CBIndex(pDX, nIDC, item );
      value = (T)item;
   }
   else
   {
      int item = (int)value;
      DDX_CBIndex(pDX, nIDC, item );
   }
}

template <class T>
void MFCTOOLSFUNC DDX_RadioEnum(CDataExchange* pDX,int nIDC,T& value)
{
   if ( pDX->m_bSaveAndValidate )
   {
      int item;
      DDX_Radio(pDX, nIDC, item );
      value = (T)item;
   }
   else
   {
      int item = (int)value;
      DDX_Radio(pDX, nIDC, item );
   }
}


///////////////////////////////////////////////

template <class U>
void DDX_Tag(CDataExchange* pDX, int nIDCTag, const U& umIndirectMeasure )
{
	if ( pDX->m_bSaveAndValidate )
	{
	}
	else
	{
      std::_tstring tag = umIndirectMeasure.UnitOfMeasure.UnitTag();
      DDX_String( pDX, nIDCTag, tag );
	}
}


template <class U>
void DDX_UnitValue( CDataExchange* pDX, int nIDC, Float64& data, const U& umIndirectMeasure )
{
	if ( pDX->m_bSaveAndValidate )
	{
      Float64 f;
      DDX_Text( pDX, nIDC, f);
      data = ::ConvertToSysUnits( f, umIndirectMeasure.UnitOfMeasure );
	}
	else
	{
      CString strValue;
      if (data!=Float64_Inf) // Infinite values create a blank line
      {
         strValue.Format(_T("%*.*f"),umIndirectMeasure.Width,umIndirectMeasure.Precision,::ConvertFromSysUnits( data, umIndirectMeasure.UnitOfMeasure ) );
         strValue.TrimLeft();
      }
      DDX_Text( pDX, nIDC, strValue );
	}
}

template <class U>
void DDX_UnitValueAndTag( CDataExchange* pDX, int nIDC, int nIDCTag, Float64& data, const U& umIndirectMeasure )
{
	if ( pDX->m_bSaveAndValidate )
	{
      CWnd* pWnd = pDX->m_pDlgWnd->GetDlgItem(nIDC);
      if ( pWnd->IsKindOf( RUNTIME_CLASS(CCacheEdit) ) && pWnd->IsWindowEnabled() == FALSE )
      {
         data = ((CCacheEdit*)(pWnd))->GetDefaultValue();
         data = ::ConvertToSysUnits( data, umIndirectMeasure.UnitOfMeasure );
         return;
      }

      Float64 f;
      DDX_Text( pDX, nIDC, f);
      data = ::ConvertToSysUnits( f, umIndirectMeasure.UnitOfMeasure );
	}
	else
	{
      CString strValue;
      Float64 value = data; // make a copy because we are going to change it...
      if (value!=Float64_Inf) // Infinite values create a blank line
      {
         value = ::ConvertFromSysUnits( value, umIndirectMeasure.UnitOfMeasure );
         strValue.Format(_T("%*.*f"),umIndirectMeasure.Width,umIndirectMeasure.Precision,value );
         strValue.TrimLeft();
      }
      DDX_Text( pDX, nIDC, strValue );

      CString strTag = umIndirectMeasure.UnitOfMeasure.UnitTag().c_str();
      DDX_Text( pDX, nIDCTag, strTag );

      CWnd* pWnd = pDX->m_pDlgWnd->GetDlgItem(nIDC);
      if ( pWnd->IsKindOf( RUNTIME_CLASS(CCacheEdit) )  )
      {
         ((CCacheEdit*)(pWnd))->SetDefaultValue(value);
      }
	}
}

template <class U>
void DDX_OffsetAndTag( CDataExchange* pDX, int nIDC, int nIDCTag, Float64& data, const U& umIndirectMeasure )
{
   std::_tstring tag = umIndirectMeasure.UnitOfMeasure.UnitTag();
   DDX_String( pDX, nIDCTag, tag );

	if ( pDX->m_bSaveAndValidate )
	{
      CString strOffset;
      DDX_Text( pDX, nIDC, strOffset);
      strOffset.MakeUpper();
      strOffset.TrimLeft();
      strOffset.TrimRight();
      char cDir = (strOffset.GetLength() == 0 ? 'R' : strOffset.GetAt(strOffset.GetLength()-1));
      Float64 sign = 1;
      if ( cDir == 'L')
         sign = -1;
      
      data = _tstof(strOffset);
      data = ::ConvertToSysUnits( data, umIndirectMeasure.UnitOfMeasure);
      data *= sign;
	}
	else
	{
      CString strOffset;
      if ( data < 0 )
         strOffset.Format(_T("%*.*f L"),umIndirectMeasure.Width,umIndirectMeasure.Precision,::ConvertFromSysUnits( fabs(data), umIndirectMeasure.UnitOfMeasure ) );
      else if ( 0 < data )
         strOffset.Format(_T("%*.*f R"),umIndirectMeasure.Width,umIndirectMeasure.Precision,::ConvertFromSysUnits( fabs(data), umIndirectMeasure.UnitOfMeasure ) );
      else
         strOffset.Format(_T("%*.*f"),umIndirectMeasure.Width,umIndirectMeasure.Precision,::ConvertFromSysUnits( fabs(data), umIndirectMeasure.UnitOfMeasure ) );

      strOffset.TrimLeft();

      DDX_Text( pDX, nIDC, strOffset );
	}
}

template <class T,class U>
void DDV_UnitValueGreaterThanLimit(CDataExchange* pDX, int nIDC, T& value, T limit, const U& umIndirectMeasure, LPCTSTR message=_T("Please enter a number that is greater than %*.*f %s") )
{
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if( !(limit < value) )
   {
      pDX->PrepareEditCtrl(nIDC);
      CString msg;
      msg.Format(message, 
                 umIndirectMeasure.Width,umIndirectMeasure.Precision,
                 ::ConvertFromSysUnits( limit, umIndirectMeasure.UnitOfMeasure ), 
                 umIndirectMeasure.UnitOfMeasure.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

template <class T,class U>
void DDV_UnitValueLimitOrMore(CDataExchange* pDX, int nIDC, T& value, T limit, const U& umIndirectMeasure, LPCTSTR message=_T("Please enter a number that is at least %f %s") )
{
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if( !IsEqual(value,limit) && value < limit )
   {
      pDX->PrepareEditCtrl(nIDC);
      CString msg;
      msg.Format(message, 
                 ::ConvertFromSysUnits( limit, umIndirectMeasure.UnitOfMeasure ), 
                 umIndirectMeasure.UnitOfMeasure.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

template <class T,class U>
void DDV_UnitValueLessThanLimit(CDataExchange* pDX, int nIDC, T& value, T limit, const U& umIndirectMeasure, LPCTSTR message=_T("Please enter a number that is less than %f %s") )
{
	if (!pDX->m_bSaveAndValidate)
	{
		TRACE0("Warning: initial dialog data is out of range.\n");
		return;         // don't stop now
	}

   if( !(value < limit) )
   {
      pDX->PrepareEditCtrl(nIDC);
      CString msg;
      msg.Format(message, 
                 ::ConvertFromSysUnits( limit, umIndirectMeasure.UnitOfMeasure  ), 
                 umIndirectMeasure.UnitOfMeasure.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}


template <class T,class U>
void DDV_UnitValueLimitOrLess(CDataExchange* pDX, int nIDC, T& value, T limit, const U& umIndirectMeasure, LPCTSTR message=_T("Please enter a number that is not more than %f %s"))
{
	if (!pDX->m_bSaveAndValidate)
	{
		TRACE0("Warning: initial dialog data is out of range.\n");
		return;         // don't stop now
	}

   if( !IsEqual(limit,value) && limit < value )
   {
      pDX->PrepareEditCtrl(nIDC);
      CString msg;
      msg.Format(message, 
                 ::ConvertFromSysUnits( limit, umIndirectMeasure.UnitOfMeasure ), 
                 umIndirectMeasure.UnitOfMeasure.UnitTag().c_str() );

	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}


template <class T,class U>
void DDV_UnitValueGreaterThanZero(CDataExchange* pDX, int nIDC, T& value, const U& umIndirectMeasure )
{
   T zero = 0;
   DDV_UnitValueGreaterThanLimit( pDX, nIDC, value, zero, umIndirectMeasure );
}

template <class T,class U>
void DDV_UnitValueLessThanZero(CDataExchange* pDX, int nIDC, T& value, const U& umIndirectMeasure )
{
   T zero = 0;
   DDV_UnitValueLessThanLimit( pDX, nIDC, value, zero, umIndirectMeasure );
}

template <class T,class U>
void DDV_UnitValueZeroOrMore(CDataExchange* pDX, int nIDC, T& value, const U& umIndirectMeasure )
{
   T zero = 0;
   DDV_UnitValueLimitOrMore( pDX, nIDC, value, zero, umIndirectMeasure );
}

template <class T,class U>
void DDV_UnitValueZeroOrLess(CDataExchange* pDX, int nIDC, T& value, const U& umIndirectMeasure )
{
   T zero = 0;
   DDV_UnitValueLimitOrLess( pDX, nIDC, value, zero, umIndirectMeasure );
}

template <class T,class U>
void DDV_UnitValueRange(CDataExchange* pDX, int nIDC, T& value, T min, T max, const U& umIndirectMeasure )
{
	if (!pDX->m_bSaveAndValidate)
	{
		return;
	}

   if(  value < min || max < value )
   {
      pDX->PrepareEditCtrl(nIDC);
      CString msg;
      msg.Format(_T("Please enter a number in the range %f to %f %s"), 
                 ::ConvertFromSysUnits( min, umIndirectMeasure.UnitOfMeasure ), 
                 ::ConvertFromSysUnits( max, umIndirectMeasure.UnitOfMeasure ), 
                 umIndirectMeasure.UnitOfMeasure.UnitTag().c_str() );
	   AfxMessageBox( msg, MB_ICONEXCLAMATION);
	   pDX->Fail();
   }
}

#endif // INCLUDED_MFCTOOLS_CUSTOMDDX_H_