///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RCSECTIONVALUET_H_
#define INCLUDED_REPORTER_RCSECTIONVALUET_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\RcSectionValue.h>
#include <System\SectionValue.h>
#include <Units\PhysicalT.h>
#include <Units\SysUnits.h>
#include <MathEx.h>


#if defined BUILDREPORTERLIB
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif // BUILDREPORTERLIB


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcSectionValueT

   Template class the implements the rptSectionValue abstract interface.


DESCRIPTION
   Template class the implements the rptSectionValue abstract interface.

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

template <class T>
class rptRcSectionValueT : public rptRcSectionValue
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcSectionValueT(const sysSectionValue& value,  // unit value in system units
                      const T* pUnitOfMeasure,       // pointer to unit of measure
                      Float64 zeroTolerance = 0.,    // tolerance for zeroness
                      bool bShowUnitTag = true) :    // Show the unit tag?
   rptRcSectionValue( bShowUnitTag ),
   m_Value( value ),
   m_pUnitOfMeasure( pUnitOfMeasure ),
   m_ZeroTolerance( zeroTolerance )
   {
   }

   //------------------------------------------------------------------------
   rptRcSectionValueT(const T* pUnitOfMeasure,       // pointer to unit of measure
                      Float64 zeroTolerance = 0.,    // tolerance for zeroness
                      bool bShowUnitTag = true) :    // Show the unit tag?
   rptRcSectionValue( bShowUnitTag ),
   m_Value( 0.00 ),
   m_pUnitOfMeasure( pUnitOfMeasure ),
   m_ZeroTolerance( zeroTolerance )
   {
   }

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcSectionValueT(const rptRcSectionValueT& rOther) :
   rptRcSectionValue( rOther )
   {
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcSectionValueT()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptRcSectionValueT& operator = (const rptRcSectionValueT& rOther)
   {
      if ( this != &rOther )
         MakeAssignment( rOther );

      return *this;
   }

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   rptReportContent* CreateClone() const
   {
      return new rptRcSectionValueT( *this );
   }


   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Assings a new section value to this object
   virtual rptReportContent& SetValue(const sysSectionValue& value)
   {
      m_Value = value;
      return *this;
   }

   //------------------------------------------------------------------------
   // Returns the section value.
   // If bConvert is <b>true</b>,  the value is converted to output units,
   // otherwise it is in system units.
   virtual sysSectionValue GetValue(bool bConvert = false ) const
   {
      return sysSectionValue( GetLeftValue(bConvert), GetRightValue(bConvert) );
   }

   //------------------------------------------------------------------------
   // Returns the left value for this piece of report content.  If bConvert is
   // <b>true</b>,  the value is converted to output units, otherwise it is in
   // system units.
   virtual Float64 GetLeftValue(bool bConvert = false) const
   {
      return GetValue( m_Value.Left(), bConvert );
   }

   //------------------------------------------------------------------------
   // Returns the right value for this piece of report content.  If bConvert is
   // <b>true</b>,  the value is converted to output units, otherwise it is in
   // system units.
   virtual Float64 GetRightValue(bool bConvert = false) const
   {
      return GetValue( m_Value.Right(), bConvert );
   }

   //------------------------------------------------------------------------
   // Returns the unit tag for the output unit of measure.
   virtual std::_tstring GetUnitTag() const
   {
      return m_pUnitOfMeasure->UnitTag();
   }

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const
   {
      return rptRcSectionValue::AssertValid() && (m_pUnitOfMeasure != 0);
   }

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const
   {
      rptRcSectionValue::Dump( os );
   }

#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const rptRcSectionValueT& rOther)
   {
      m_Value          = rOther.m_Value;
      m_pUnitOfMeasure = rOther.m_pUnitOfMeasure;
      m_ZeroTolerance  = rOther.m_ZeroTolerance;
   }

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rptRcSectionValueT& rOther)
   {
      rptRcSectionValue::MakeAssignment( rOther );
      MakeCopy( rOther );
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   sysSectionValue m_Value;
   const T* m_pUnitOfMeasure;
   Float64 m_ZeroTolerance;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   Float64 GetValue(Float64 v,bool bConvert = false) const
   {
      Float64 value;
      if ( bConvert )
         value = ::ConvertFromSysUnits( v, *m_pUnitOfMeasure );
      else
         value = v;

      if ( IsZero( value, m_ZeroTolerance ) )
         value = 0.;

      return value;
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

//#pragma warning( disable : 4231 ) 
#define DECLARE_RC_SECTION_VALUE(u,t) \
   REPORTERTPL rptRcSectionValueT<u>; \
   typedef rptRcSectionValueT<u> t;

DECLARE_RC_SECTION_VALUE( unitMass,           rptMassSectionValue           );
DECLARE_RC_SECTION_VALUE( unitMassPerLength,  rptMassPerLEngthSectionValue  );
DECLARE_RC_SECTION_VALUE( unitLength,         rptLengthSectionValue         );
DECLARE_RC_SECTION_VALUE( unitTime,           rptTimeSectionValue           );
DECLARE_RC_SECTION_VALUE( unitTemperature,    rptTemperatureSectionValue    );
DECLARE_RC_SECTION_VALUE( unitAngle,          rptAngleSectionValue          );
DECLARE_RC_SECTION_VALUE( unitLength2,        rptLength2SectionValue        );
DECLARE_RC_SECTION_VALUE( unitLength3,        rptLength3SectionValue        );
DECLARE_RC_SECTION_VALUE( unitLength4,        rptLength4SectionValue        );
DECLARE_RC_SECTION_VALUE( unitPressure,       rptPressureSectionValue       );
DECLARE_RC_SECTION_VALUE( unitDensity,        rptDensitySectionValue        );
DECLARE_RC_SECTION_VALUE( unitForce,          rptForceSectionValue          );
DECLARE_RC_SECTION_VALUE( unitForcePerLength, rptForcePerLengthSectionValue );
DECLARE_RC_SECTION_VALUE( unitMomentPerAngle, rptMomentPerAngleSectionValue );
DECLARE_RC_SECTION_VALUE( unitMoment,         rptMomentSectionValue         );
DECLARE_RC_SECTION_VALUE( unitSqrtPressure,   rptSqrtPressureValue          );

typedef rptPressureSectionValue rptStressSectionValue;
typedef rptLength2SectionValue  rptAreaSectionValue;
typedef rptLength3SectionValue  rptVolumeSectionValue;

#endif // INCLUDED_REPORTER_RCSECTIONVALUET_H_
