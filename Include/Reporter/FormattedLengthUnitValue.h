///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\RcUnitValueT.h>


/// Unit value formating class that reports length values as feet, inches and fractions e.g. 125.27083333 ft = 125'-3 1/4".
class REPORTERCLASS rptFormattedLengthUnitValue : public rptLengthUnitValue
{
public:
   /// Specifies how values are rounded
   enum Rounding
   {
      RoundOff, ///< rounds to the nearest value
      RoundUp,  ///< rounds up
      RoundDown ///< rounds down
   };

   rptFormattedLengthUnitValue(Float64 value,               ///< unit value in system units
                                 const unitLength* pUnitOfMeasure, ///< Unit of measure
                                 Float64 zeroTolerance,  ///< tolerance for zeroness
                                 bool bShowUnitTag, ///< Indicates if the unit tag is shown
                                 bool bEnglish,               ///< true if this is an english unit (if not, just use base class formatting)
                                 Uint16 fraPrecision,         ///< precision of fraction (denominator for fraction of an inch, e.g. use 8 for a precision of 1/8")
                                 bool bFractionOnly, ///< if true, reports the number as a fraction only
                                 Rounding rounding ///< indicates how the value is to be rounded to the specified precision
                                 ) :  
   rptLengthUnitValue( value, pUnitOfMeasure, zeroTolerance, bShowUnitTag )
   {
      m_bEnglish = bEnglish;
      m_Denominator = fraPrecision;
      m_bFractionOnly = bFractionOnly;
      m_Rounding = rounding;
   }

   rptFormattedLengthUnitValue(  const unitLength* pUnitOfMeasure, ///< Unit of measure
                                 Float64 zeroTolerance,  ///< tolerance for zeroness
                                 bool bShowUnitTag, ///< Indicates if the unit tag is shown
                                 bool bEnglish,///< true if this is an english unit (if not, just use base class formatting)
                                 Uint16 fraPrecision,  ///< precision of fraction (denominator for fraction of an inch, e.g. use 8 for a precision of 1/8")
                                 bool bFractionOnly,///< if true, reports the number as a fraction only
                                 Rounding rounding///< indicates how the value is to be rounded to the specified precision
                               ) :  
   rptLengthUnitValue( pUnitOfMeasure, zeroTolerance, bShowUnitTag )
   {
      m_bEnglish = bEnglish;
      m_Denominator = fraPrecision;
      m_bFractionOnly = bFractionOnly;
      m_Rounding = rounding;
   }

   rptFormattedLengthUnitValue(const rptFormattedLengthUnitValue& rOther) :
   rptLengthUnitValue( rOther )
   {
      MakeCopy( rOther );
   }

   virtual ~rptFormattedLengthUnitValue()
   {
   }

   rptFormattedLengthUnitValue& operator = (const rptFormattedLengthUnitValue& rOther)
   {
      if ( this != &rOther )
         MakeAssignment( rOther );

      return *this;
   }

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Copies object data from rOther
   void MakeCopy(const rptFormattedLengthUnitValue& rOther)
   {
      m_bEnglish    = rOther.m_bEnglish;
      m_Denominator = rOther.m_Denominator;
      m_bFractionOnly = rOther.m_bFractionOnly;
      m_Rounding = rOther.m_Rounding;
   }

   /// Assigns object data from rOther to this object
   virtual void MakeAssignment(const rptFormattedLengthUnitValue& rOther)
   {
      rptLengthUnitValue::MakeAssignment( rOther );
      MakeCopy( rOther );
   }

   /// Returns the value as a formatted string
   virtual std::_tstring AsString() const override;

private:
   bool m_bEnglish;
   Uint16 m_Denominator;
   bool m_bFractionOnly; // if true and if m_bEnglish is true, show only the fraction equivalent
   Rounding m_Rounding;
};
