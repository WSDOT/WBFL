///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#include <Reporter\ReporterLib.h>
#include <Reporter\FormattedLengthUnitValue.h>
#include <Reporter\RcVisitor.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptFormattedLengthUnitValue
****************************************************************************/
rptReportContent* rptFormattedLengthUnitValue::CreateClone() const
{
   return new rptFormattedLengthUnitValue( *this );
}

std::_tstring rptFormattedLengthUnitValue::AsString() const
{
   std::_tstring strBase = rptLengthUnitValue::AsString();
   if ( !m_bEnglish )
      return strBase;

   // English formatted output  ft'-inn/d"

   // get value in feet
   Float64 value = ::ConvertFromSysUnits( GetValue(), unitMeasure::Feet );
   if ( IsZero( value, GetZeroTolerance() ) )
      value = 0.;

   Int16 sign = ::BinarySign(value);
   value = fabs(value); // make a positive number
   Int16 ft = Int16(value); // integer part
   value -= ft; // remove the feet part
   value *= 12; // value now in inches
   Uint16 in = Uint16(value);

   value -= in; // value is now fractions of an inch

   Uint16 denominator = m_Denominator;
   Uint16 numerator = Uint16(::RoundOff(value*m_Denominator,1));

   // reduce the fraction
   while ( numerator % 2 == 0 && denominator % 2 == 0 )
   {
      numerator   /= 2;
      denominator /= 2;
   }

   if ( numerator == denominator )
   {
      in++;
      numerator = 0;
   }

   if ( in == 12 )
   {
      ft++;
      in = 0;
   }

   std::_tostringstream os;
   if ( m_bFractionOnly )
   {
      if ( numerator == 0 ) // whole number of inches
      {
         if ( ft == 0 ) // 1"
            os << sign*in << _T("\"");
         else // 1'-3"
            os << sign*ft << _T("'-") << in << _T("\"");
      }
      else // fractional number of inches
      {
         if ( ft == 0 && in == 0 )  // 1/2"
         {
            if ( sign < 0 )
               os << __T("-");

            os << _T("^") << numerator << _T("_/_") << denominator << _T("^") << _T("\"");
         }
         else if ( ft == 0 ) // 1 1/2"
            os << sign*in << _T("^") << numerator << _T("_/_") << denominator << _T("^") << _T("\"");
         else // 3'-1 1/2"
            os << sign*ft << _T("'-") << in << _T("^") << numerator << _T("_/_") << denominator << _T("^") << _T("\"");
      }
   }
   else
   {
      if ( numerator == 0 ) // whole number of inches
      {
         if ( ft == 0 ) // 1"
            os << strBase << _T(" (") << sign*in << _T("\")");
         else // 1'-3"
            os << strBase << _T(" (") << sign*ft << _T("'-") << in << _T("\")");
      }
      else // fractional number of inches
      {
         if ( ft == 0 && in == 0 )  // 1/2"
         {
            if ( sign < 0 )
               os << strBase << _T(" (") << _T("-^") << numerator << _T("_/_") << denominator << _T("^") << _T("\")");
            else
               os << strBase << _T(" (") << _T("^") << numerator << _T("_/_") << denominator << _T("^") << _T("\")");
         }
         else if ( ft == 0 ) // 1 1/2"
            os << strBase << _T(" (") << sign*in << _T("^") << numerator << _T("_/_") << denominator << _T("^") << _T("\")");
         else // 3'-1 1/2"
            os << strBase << _T(" (") << sign*ft << _T("'-") << in << _T("^") << numerator << _T("_/_") << denominator << _T("^") << _T("\")");
      }
   }

   return os.str();
}
