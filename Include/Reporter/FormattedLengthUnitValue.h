///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright � 1999-2021  Washington State Department of Transportation
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


/*****************************************************************************
CLASS 
   rptRcFormattedLengthUnitValue

   Unit value formating class that reports length values as feet, inches and fractions
   e.g. 125.27083333 ft = 125'-3 1/4".

LOG
   rab : 06.09.2009 : Created file
*****************************************************************************/

class REPORTERCLASS rptFormattedLengthUnitValue : public rptLengthUnitValue
{
public:
   enum Rounding{RoundOff,RoundUp,RoundDown};
   rptFormattedLengthUnitValue(Float64 value,               // unit value in system units
                                 const unitLength* pUnitOfMeasure,
                                 Float64 zeroTolerance,  // tolerance for zeroness
                                 bool bShowUnitTag,// Show the unit tag?
                                 bool bEnglish,               // true if this is an english unit (if not, just use base class formatting)
                                 Uint16 fraPrecision,         // precision of fraction (denominator for fraction of an inch)
                                 bool bFractionOnly,
                                 Rounding rounding
                                 ) :  
   rptLengthUnitValue( value, pUnitOfMeasure, zeroTolerance, bShowUnitTag )
   {
      m_bEnglish = bEnglish;
      m_Denominator = fraPrecision;
      m_bFractionOnly = bFractionOnly;
      m_Rounding = rounding;
   }

   rptFormattedLengthUnitValue(  const unitLength* pUnitOfMeasure,
                                 Float64 zeroTolerance,  // tolerance for zeroness
                                 bool bShowUnitTag, // Show the unit tag?
                                 bool bEnglish,
                                 Uint16 fraPrecision,
                                 bool bFractionOnly,
                                 Rounding rounding
                               ) :  
   rptLengthUnitValue( pUnitOfMeasure, zeroTolerance, bShowUnitTag )
   {
      m_bEnglish = bEnglish;
      m_Denominator = fraPrecision;
      m_bFractionOnly = bFractionOnly;
      m_Rounding = rounding;
   }

   //------------------------------------------------------------------------
   // Copy constructor
   rptFormattedLengthUnitValue(const rptFormattedLengthUnitValue& rOther) :
   rptLengthUnitValue( rOther )
   {
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptFormattedLengthUnitValue()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptFormattedLengthUnitValue& operator = (const rptFormattedLengthUnitValue& rOther)
   {
      if ( this != &rOther )
         MakeAssignment( rOther );

      return *this;
   }

   //------------------------------------------------------------------------
   // virtual way to make a copy.
   virtual rptReportContent* CreateClone() const override;

   //------------------------------------------------------------------------
   void MakeCopy(const rptFormattedLengthUnitValue& rOther)
   {
      m_bEnglish    = rOther.m_bEnglish;
      m_Denominator = rOther.m_Denominator;
      m_bFractionOnly = rOther.m_bFractionOnly;
      m_Rounding = rOther.m_Rounding;
   }

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rptFormattedLengthUnitValue& rOther)
   {
      rptLengthUnitValue::MakeAssignment( rOther );
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Override base class method
   virtual std::_tstring AsString() const override;

private:
   bool m_bEnglish;
   Uint16 m_Denominator;
   bool m_bFractionOnly; // if true and if m_bEnglish is true, show only the fraction equivalent
   Rounding m_Rounding;
};
