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

#ifndef INCLUDED_REPORTER_RCUNITVALUET_H_
#define INCLUDED_REPORTER_RCUNITVALUET_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\RcUnitValue.h>
#include <Units\PhysicalT.h>
#include <Units\SysUnits.h>
#include <MathEx.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcUnitValueT

   Template class the implements the rptUnitValue abstract interface.


DESCRIPTION
   Template class the implements the rptUnitValue abstract interface.

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

template <class T>
class rptRcUnitValueT : public rptRcUnitValue
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcUnitValueT(Float64 value,               // unit value in system units
                   const T* pUnitOfMeasure,     // pointer to unit of measure
                   Float64 zeroTolerance = 0.,  // tolerance for zeroness
                   bool bShowUnitTag = true) :  // Show the unit tag?
   rptRcUnitValue( bShowUnitTag ),
   m_Value( value ),
   m_pUnitOfMeasure( pUnitOfMeasure ),
   m_ZeroTolerance( zeroTolerance )
   {
   }

   rptRcUnitValueT(const T* pUnitOfMeasure = 0,     // pointer to unit of measure
                   Float64 zeroTolerance = 0.,  // tolerance for zeroness
                   bool bShowUnitTag = true) :  // Show the unit tag?
   rptRcUnitValue( bShowUnitTag ),
   m_Value( 0.00 ),
   m_pUnitOfMeasure( pUnitOfMeasure ),
   m_ZeroTolerance( zeroTolerance )
   {
   }

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcUnitValueT(const rptRcUnitValueT& rOther) :
   rptRcUnitValue( rOther )
   {
      MakeCopy( rOther );
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcUnitValueT()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptRcUnitValueT& operator = (const rptRcUnitValueT& rOther)
   {
      if ( this != &rOther )
         MakeAssignment( rOther );

      return *this;
   }

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // virtual way to make a copy.
   virtual rptReportContent* CreateClone() const
   {
#if defined _DEBUG
      // this is the same as DEBUG_NEW... we just can't use DEBUG_NEW in a header file
      return new(__FILE__,__LINE__) rptRcUnitValueT( *this );
#else
      return new rptRcUnitValueT( *this );
#endif
   }

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the value for this piece of report content. <i>value</i> is in
   // system units.
   virtual rptReportContent& SetValue(Float64 value)
   {
      m_Value = value;
      return *this;
   }

   //------------------------------------------------------------------------
   // Returns the value for this piece of report content.  If bConvert is
   // <b>true</b>,  the value is converted to output units, otherwise it is in
   // system units.
   virtual Float64 GetValue(bool bConvert = false) const
   {
      Float64 value;
      if ( bConvert )
         value = ::ConvertFromSysUnits( m_Value, *m_pUnitOfMeasure );
      else
         value = m_Value;

      if ( IsZero( value, m_ZeroTolerance ) )
         value = 0.;

      return value;
   }

   //------------------------------------------------------------------------
   void SetUnitOfMeasure(const T* pUnitOfMeasure)
   {
      m_pUnitOfMeasure = pUnitOfMeasure;

      ASSERTVALID;
   }

   //------------------------------------------------------------------------
   // Returns the unit tag for the output unit of measure.
   virtual std::_tstring GetUnitTag() const
   {
      return m_pUnitOfMeasure->UnitTag();
   }

   void SetZeroTolerance(Float64 z)
   {
      m_ZeroTolerance = z;
   }

   Float64 GetZeroTolerance() const
   {
      return m_ZeroTolerance;
   }

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const
   {
      return rptRcUnitValue::AssertValid() && (m_pUnitOfMeasure != 0);
   }

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const
   {
      rptRcUnitValue::Dump( os );
   }

#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const rptRcUnitValueT& rOther)
   {
      m_Value          = rOther.m_Value;
      m_pUnitOfMeasure = rOther.m_pUnitOfMeasure;
      m_ZeroTolerance  = rOther.m_ZeroTolerance;
   }

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rptRcUnitValueT& rOther)
   {
      rptRcUnitValue::MakeAssignment( rOther );
      MakeCopy( rOther );
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Value;
   const T* m_pUnitOfMeasure;
   Float64 m_ZeroTolerance;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#define DECLARE_RC_UNIT_VALUE(u,t) \
   REPORTERTPL rptRcUnitValueT<u>; \
   typedef rptRcUnitValueT<u> t;

//#pragma warning( disable : 4231 ) 
DECLARE_RC_UNIT_VALUE( unitMass,           rptMassUnitValue           );
DECLARE_RC_UNIT_VALUE( unitMassPerLength,  rptMassPerLengthUnitValue  );
DECLARE_RC_UNIT_VALUE( unitLength,         rptLengthUnitValue         );
DECLARE_RC_UNIT_VALUE( unitTime,           rptTimeUnitValue           );
DECLARE_RC_UNIT_VALUE( unitTemperature,    rptTemperatureUnitValue    );
DECLARE_RC_UNIT_VALUE( unitAngle,          rptAngleUnitValue          );
DECLARE_RC_UNIT_VALUE( unitLength2,        rptLength2UnitValue        );
DECLARE_RC_UNIT_VALUE( unitLength3,        rptLength3UnitValue        );
DECLARE_RC_UNIT_VALUE( unitLength4,        rptLength4UnitValue        );
DECLARE_RC_UNIT_VALUE( unitPressure,       rptPressureUnitValue       );
DECLARE_RC_UNIT_VALUE( unitDensity,        rptDensityUnitValue        );
DECLARE_RC_UNIT_VALUE( unitUnitWeight,     rptUnitWeightUnitValue     );
DECLARE_RC_UNIT_VALUE( unitForce,          rptForceUnitValue          );
DECLARE_RC_UNIT_VALUE( unitForcePerLength, rptForcePerLengthUnitValue );
DECLARE_RC_UNIT_VALUE( unitMomentPerAngle, rptMomentPerAngleUnitValue );
DECLARE_RC_UNIT_VALUE( unitMoment,         rptMomentUnitValue         );
DECLARE_RC_UNIT_VALUE( unitPerLength,      rptPerLengthUnitValue      );
DECLARE_RC_UNIT_VALUE( unitForceLength2,   rptForceLength2UnitValue   );
DECLARE_RC_UNIT_VALUE( unitVelocity,       rptVelocityUnitValue       );

typedef rptPressureUnitValue rptStressUnitValue;
typedef rptLength2UnitValue  rptAreaUnitValue;
typedef rptLength3UnitValue  rptVolumeUnitValue;
typedef rptLengthUnitValue   rptAreaPerLengthValue;

#endif // INCLUDED_REPORTER_RCUNITVALUET_H_
