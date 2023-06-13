///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// DirectionDisplayUnitFormatter.cpp : Implementation of CDirectionDisplayUnitFormatter
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "DirectionDisplayUnitFormatter.h"
#include <CoordGeom/Direction.h>
#include <WBFLCogo/CogoHelpers.h>
#include <sstream>
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectionDisplayUnitFormatter

HRESULT CDirectionDisplayUnitFormatter::FinalConstruct()
{
   m_bBearingFormat = VARIANT_TRUE;
   m_bUsesTag = VARIANT_TRUE;
   m_bCondensedFormat = VARIANT_FALSE;
   m_Width = 5;
   m_Precision = 2;
   m_Justification = tjLeft;
   m_Notation = nftFixed;
   m_ZeroTolerance = 0.0001;
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDirectionDisplayUnitFormatter,
      &IID_IDisplayUnitFormatter
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::FormatSpecifiers( Uint32 width, Uint32 precision, TextJustificationType justify, NumericFormatType notation, Float64 zeroTol)
{
   if ( width < 0 || precision < 0 || zeroTol < 0)
      return E_INVALIDARG;

   m_Width         = width;
   m_Precision     = precision;
   m_Notation      = notation;
   m_Justification = justify;
   m_ZeroTolerance = zeroTol;

   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_Width(Uint32* val)
{
   CHECK_RETVAL(val);
   *val = m_Width;
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_Precision(Uint32* val)
{
   CHECK_RETVAL(val);
   *val = m_Precision;
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_Notation(NumericFormatType* notation)
{
   CHECK_RETVAL(notation);
   *notation = m_Notation;
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_Justification(TextJustificationType* justify)
{
   CHECK_RETVAL(justify);
   *justify = m_Justification;
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_ZeroTolerance(Float64* zeroTol)
{
   CHECK_RETVAL(zeroTol);
   *zeroTol = m_ZeroTolerance;
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::Format(Float64 val, BSTR tag, BSTR* fmtString)
{
   USES_CONVERSION;
   CHECK_RETSTRING(fmtString);

   if ( IsZero(val,m_ZeroTolerance) )
      val = 0.0;

   val = WBFL::COGO::COGO::NormalizeAngle(val);

   bool bShowTag = (tag == nullptr ? false : true);
   std::_tstring strDegTag, strMinTag, strSecTag;
   if ( bShowTag )
   {
      std::_tstring strTag = OLE2T(tag);
      if ( FAILED(cogoUtil::ParseAngleTags(strTag,&strDegTag,&strMinTag,&strSecTag)) )
         return E_INVALIDARG; // bad format tag
   }

   std::_tostringstream s;

   if ( m_bBearingFormat )
   {
      WBFL::COGO::Direction direction(val);
      WBFL::COGO::Direction::NSDirection ns;
      WBFL::COGO::Direction::EWDirection ew;
      unsigned short deg;
      unsigned short min;
      Float64 sec;
      std::tie(ns, deg, min, sec, ew) = direction.GetDMS();
      NSDirectionType n = NSDirectionType(ns);
      EWDirectionType e = EWDirectionType(ew);

      sec = IsZero(sec,m_ZeroTolerance) ? 0 : sec;
      s << std::setw(1) << (n == nsNorth ? _T('N') : _T('S') ) << _T(" ") 
        << deg;

      if ( bShowTag )
         s << strDegTag;

      if ( m_bCondensedFormat == VARIANT_FALSE || ( min != 0 || sec != 0 ) )
      {
         s << _T(" ") << std::setw(2) << std::setfill( _T('0') ) << min;
         if ( bShowTag )
            s << strMinTag;

         s << _T(" ") << std::setw(m_Width) << std::setfill( _T('0') ) << std::showpoint << std::fixed << std::setprecision(m_Precision) << sec;

         if ( bShowTag )
            s << strSecTag;
      }

      s << _T(" ") << std::setw(1) << (e == ewEast ? _T('E') : _T('W') ) << std::ends;
   }
   else
   {
      // azimuth
      val = WBFL::COGO::COGO::NormalizeAngle(PI_OVER_2 - val);
      short deg;
      unsigned short min;
      Float64 sec;
      std::tie(deg, min, sec) = WBFL::COGO::COGO::ToDMS(val);

      sec = IsZero(sec,m_ZeroTolerance) ? 0 : sec;
      s << deg;

      if ( bShowTag )
         s << strDegTag;

      if ( m_bCondensedFormat == VARIANT_FALSE || ( min != 0 || sec != 0 ) )
      {
         s << _T(" ") << std::setw(2) << std::setfill( _T('0') ) << min;
         if ( bShowTag )
            s << strMinTag;

         s << _T(" ") << std::setw(m_Width) << std::setfill( _T('0') ) << std::showpoint << std::fixed << std::setprecision(m_Precision) << sec;

         if ( bShowTag )
            s << strSecTag;
      }

      s << std::ends;
   }

   CComBSTR bstrFormattedValue(s.str().c_str());
   *fmtString = bstrFormattedValue.Copy();
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_UsesTag(VARIANT_BOOL *bUsesTag)
{
   CHECK_RETVAL(bUsesTag);
   *bUsesTag = VARIANT_TRUE;
   return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_CondensedFormat(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = m_bCondensedFormat;

	return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::put_CondensedFormat(VARIANT_BOOL newVal)
{
   m_bCondensedFormat = newVal;
	return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::get_BearingFormat(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = m_bBearingFormat;

	return S_OK;
}

STDMETHODIMP CDirectionDisplayUnitFormatter::put_BearingFormat(VARIANT_BOOL newVal)
{
   m_bBearingFormat = newVal;
	return S_OK;
}
