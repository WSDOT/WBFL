///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// DisplayUnitFormatter.cpp : Implementation of CDisplayUnitFormatter
#include "stdafx.h"
#include "WBFLUnitServer.h"
#include "DisplayUnitFormatter.h"
#include "engnotation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// A macro called "max" is defined in this compilation unit
// It is interfering with std::numeric_limits<>::max()
// Undefining "max" to resolve conflict
#if defined max
#undef max
#endif

// Helper function prototypes
void apply_stream_manipulators( std::_tostream* pOS,TextJustificationType justify, NumericFormatType format,Uint32 width,Uint32 precision, Float64 value);
Uint32 get_width_demand(Float64 value, Uint32 precision);

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitFormatter
STDMETHODIMP CDisplayUnitFormatter::Format(/*[in]*/ Float64 cv,/*[in]*/ BSTR tag,/*[out,retval]*/ BSTR* fmtString)
{
   USES_CONVERSION;

   CHECK_RETSTRING(fmtString);

   if ( IsZero(cv,m_ZeroTolerance) )
   {
      cv = 0.00;
   }
 
   // If the number is greater than 95% of max Float64, take it to be infinity
   if ( 0.95*std::numeric_limits<Float64>::max() < fabs(cv) )
   {
      // Check if the number is +/- infinity
      CComBSTR bstrString( cv < 0 ? _T("-INF") : _T("INF") );
      if ( tag )
      {
         bstrString += CComBSTR(_T(" "));
         bstrString += tag;
      }
      *fmtString = bstrString.Detach();
      return S_OK;
   }



   // Setup stream for floating point format, width, and precision
   std::_tostringstream os;
   apply_stream_manipulators(&os,m_Justify,m_Notation,m_Width,m_Precision, cv);

   if ( m_Notation == nftEngineering )
   {
      os << eng_notation(cv,m_Width,m_Precision);
   }
   else
   {
      os << cv;
   }

   if ( tag != 0 )
   {
      os << _T(" ") << OLE2T(tag);
   }

   CComBSTR bstrString( os.str().c_str() );
   *fmtString = bstrString.Detach();
 
   return S_OK;
}

STDMETHODIMP CDisplayUnitFormatter::get_Width(/*[out, retval]*/ Uint32 *width)
{
   CHECK_RETVAL(width);
   *width = m_Width;
   return S_OK;
}

STDMETHODIMP CDisplayUnitFormatter::get_Precision(/*[out, retval]*/ Uint32 *precision)
{
   CHECK_RETVAL(precision);
   *precision = m_Precision;
   return S_OK;
}

STDMETHODIMP CDisplayUnitFormatter::FormatSpecifiers(/*[in]*/ Uint32 width,/*[in]*/Uint32 precision,/*[in]*/ TextJustificationType justify,/*[in]*/NumericFormatType notation,Float64 zeroTol)
{
   if ( width < 0 || precision < 0 || zeroTol < 0)
      return E_INVALIDARG;

   if ( m_Width != width || m_Precision != precision || m_Notation != notation || m_Justify != justify || !IsEqual(m_ZeroTolerance,zeroTol))
   {
      m_Width         = width;
      m_Precision     = precision;
      m_Notation      = notation;
      m_Justify       = justify;
      m_ZeroTolerance = zeroTol;

      Fire_OnFormatChanged();
   }

   return S_OK;
}

STDMETHODIMP CDisplayUnitFormatter::get_Notation(NumericFormatType* notation)
{
   CHECK_RETVAL(notation);
   *notation = m_Notation;
   return S_OK;
}

STDMETHODIMP CDisplayUnitFormatter::get_Justification(TextJustificationType* justify)
{
   CHECK_RETVAL(justify);
   *justify = m_Justify;
   return S_OK;
}

STDMETHODIMP CDisplayUnitFormatter::get_ZeroTolerance(Float64* zeroTol)
{
   CHECK_RETVAL(zeroTol);
   *zeroTol = m_ZeroTolerance;
   return S_OK;
}

STDMETHODIMP CDisplayUnitFormatter::get_UsesTag(VARIANT_BOOL *bUsesTag)
{
   CHECK_RETVAL(bUsesTag);
   *bUsesTag = VARIANT_TRUE;
   return S_OK;
}

void apply_stream_manipulators( std::_tostream* pOS, TextJustificationType justify, NumericFormatType format,Uint32 width,Uint32 precision, Float64 value)
{
   // Check if the specified width is adequate
   // Only applies to Automatic and Fixed formatting
   if ( (width > 0) &&
        (format == nftAutomatic || format == nftFixed ) &&
        (get_width_demand( value, precision ) > width) )
   {
      // The specified with is insufficient, use scientific notation
      format = nftScientific;
   }

   switch ( format )
   {
   case nftEngineering:
      // Do nothing.
      // std::ios does not support scientific notation so we
      // will have to roll our own with a custom manipulator

      //**************************************
      //*** DROP THROUGH to Automatic
      //**************************************

   case nftAutomatic:
      pOS->setf( !std::ios::scientific, std::ios::floatfield );
      pOS->setf( !std::ios::fixed,      std::ios::floatfield );
      break;

   case nftFixed:
      pOS->setf( std::ios::fixed,      std::ios::floatfield );
      break;

   case nftScientific:
      {
      pOS->setf( std::ios::scientific, std::ios::floatfield );

      long max_precision = width - 8;
      if ( pOS->precision() > max_precision )
      {
         pOS->precision( max_precision );
      } // end if
      } // end case
      break;

   default:
        ATLASSERT(false); // Should never get here
   }

   // Justification
   long flags = pOS->flags();
   flags |= (justify == tjLeft ? std::ios::left : std::ios::right );
   pOS->flags(flags);

   // Width
   pOS->width( width );

   // Precision
   pOS->precision( precision );
}

Uint32 get_width_demand(Float64 value,Uint32 precision)
{
   // number of digits to the left of the decimal place
   Float64 dLeft;
   if ( value != 0 )
      dLeft = log10(fabs(value))/log10(10.);
   else
      dLeft = 1;

   if ( dLeft > (LONG_MAX - 2 - precision))
      return LONG_MAX;

   // Number of digits to the left of the decimal place
   Uint32 left = Uint32( dLeft ) + 1;

   // Compute width demand
   Uint32 demand = left + 1 + precision; // +1 = Room for the decimal point
   if ( value < 0 )
      demand += 1; // Add 1 for - sign if negative

   return demand;
}
