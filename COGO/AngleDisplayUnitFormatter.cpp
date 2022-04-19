///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// AngleDisplayUnitFormatter.cpp : Implementation of CAngleDisplayUnitFormatter
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "AngleDisplayUnitFormatter.h"
#include <WBFLCogo\CogoHelpers.h>
#include <sstream>
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAngleDisplayUnitFormatter
HRESULT CAngleDisplayUnitFormatter::FinalConstruct()
{
   m_bSigned  = VARIANT_FALSE;
   m_bCondensedFormat = VARIANT_FALSE;
   m_Width = 5;
   m_Precision = 2;
   m_Justification = tjLeft;
   m_Notation = nftFixed;
   m_ZeroTolerance = 0.0001;
   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAngleDisplayUnitFormatter,
      &IID_IDisplayUnitFormatter
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAngleDisplayUnitFormatter::FormatSpecifiers( Uint32 width, Uint32 precision, TextJustificationType justify, NumericFormatType notation, Float64 zeroTol)
{
   if ( width < 0 || precision < 0 || zeroTol < 0)
      return E_INVALIDARG;

   if ( m_Width != width || m_Precision != precision || m_Notation != notation || m_Justification != justify || !IsEqual(m_ZeroTolerance,zeroTol))
   {
      m_Width         = width;
      m_Precision     = precision;
      m_Notation      = notation;
      m_Justification = justify;
      m_ZeroTolerance = zeroTol;
   }

   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_Width(Uint32* val)
{
   CHECK_RETVAL(val);
   *val = m_Width;
   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_Precision(Uint32* val)
{
   CHECK_RETVAL(val);
   *val = m_Precision;
   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_Notation(NumericFormatType* notation)
{
   CHECK_RETVAL(notation);
   *notation = m_Notation;
   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_Justification(TextJustificationType* justify)
{
   CHECK_RETVAL(justify);
   *justify = m_Justification;
   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_ZeroTolerance(Float64* zeroTol)
{
   CHECK_RETVAL(zeroTol);
   *zeroTol = m_ZeroTolerance;
   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::Format(Float64 val, BSTR tag, BSTR* fmtString)
{
   USES_CONVERSION;
   CHECK_RETSTRING(fmtString);

   if ( IsZero(val,m_ZeroTolerance) )
      val = 0.0;

   bool bShowTag = (tag == nullptr ? false : true);
   std::_tstring strDegTag, strMinTag, strSecTag;
   if ( bShowTag )
   {
      std::_tstring strTag = OLE2T(tag);
      if ( FAILED(cogoUtil::ParseAngleTags(strTag,&strDegTag,&strMinTag,&strSecTag)) )
         return Error(IDS_E_BADFORMATTAG,IID_IAngleDisplayUnitFormatter,COGO_E_BADFORMATTAG);
   }

   long deg;
   long min;
   Float64 sec;
   TCHAR dir;

   dir = (val < 0) ? 'R' : 'L';
   cogoUtil::ToDMS( val, &deg, &min, &sec );

   std::_tostringstream s;
   s << (m_bSigned == VARIANT_TRUE ? deg : abs(deg));

   if ( bShowTag )
      s << strDegTag;

   if ( m_bCondensedFormat == VARIANT_FALSE || (min != 0 || sec != 0 ) )
   {
      s << _T(" ") << std::setw(2) << std::setfill( _T('0') ) << min;
      if ( bShowTag )
         s << strMinTag;
      s << _T(" ") << std::setw(m_Width) << std::setfill( _T('0') ) << std::showpoint << std::fixed << std::setprecision(m_Precision) << (IsZero(sec) ? 0. : sec );
      if ( bShowTag ) 
         s << strSecTag;
   }

   if ( m_bSigned == VARIANT_FALSE )
     s << _T(" ") << dir;

   CComBSTR bstrFormattedValue(s.str().c_str());
   *fmtString = bstrFormattedValue.Copy();

   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_UsesTag(VARIANT_BOOL *bUsesTag)
{
   CHECK_RETVAL(bUsesTag);
   *bUsesTag = VARIANT_TRUE;
   return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_CondensedFormat(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = m_bCondensedFormat;

	return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::put_CondensedFormat(VARIANT_BOOL newVal)
{
   m_bCondensedFormat = newVal;
	return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::get_Signed(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   (*pVal) = m_bSigned;
	return S_OK;
}

STDMETHODIMP CAngleDisplayUnitFormatter::put_Signed(VARIANT_BOOL newVal)
{
   m_bSigned = newVal;
	return S_OK;
}
