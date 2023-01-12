///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
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


#include <Reporter\ReporterExp.h>
#include <Reporter\RcUnitValue.h>
#include <Units\PhysicalT.h>
#include <Units\SysUnits.h>
#include <MathEx.h>

/// Template class the implements the rptUnitValue abstract interface.
template <class T>
class rptRcUnitValueT : public rptRcUnitValue
{
public:
   rptRcUnitValueT(Float64 value,               ///< unit value in system units
                   const T* pUnitOfMeasure,     ///< pointer to unit of measure
                   Float64 zeroTolerance = 0.,  ///< tolerance for zeroness
                   bool bShowUnitTag = true) :  ///< indicates if the unit tag is to be included in with the output string
   rptRcUnitValue( bShowUnitTag ),
   m_Value( value ),
   m_pUnitOfMeasure( pUnitOfMeasure ),
   m_ZeroTolerance( zeroTolerance )
   {
   }

   rptRcUnitValueT(const T* pUnitOfMeasure = nullptr, ///< pointer to unit of measure
                   Float64 zeroTolerance = 0.,  ///< tolerance for zeroness
                   bool bShowUnitTag = true) :  ///< indicates if the unit tag is to be included in with the output string
   rptRcUnitValue( bShowUnitTag ),
   m_Value( 0.00 ),
   m_pUnitOfMeasure( pUnitOfMeasure ),
   m_ZeroTolerance( zeroTolerance )
   {
   }

   rptRcUnitValueT(const rptRcUnitValueT& rOther) :
   rptRcUnitValue( rOther )
   {
      MakeCopy( rOther );
   }

   virtual ~rptRcUnitValueT()
   {
   }

   rptRcUnitValueT& operator=(const rptRcUnitValueT& rOther)
   {
      if ( this != &rOther )
         MakeAssignment( rOther );

      return *this;
   }

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override
   {
#if defined _DEBUG
      // this is the same as DEBUG_NEW... we just can't use DEBUG_NEW in a header file
      return new(__FILE__,__LINE__) rptRcUnitValueT( *this );
#else
      return new rptRcUnitValueT( *this );
#endif
   }

   /// Assigns a new value and returns a reference to this
   virtual rptReportContent& SetValue(Float64 value) override
   {
      m_Value = value;
      return *this;
   }

   /// Returns the value.
   ///
   /// \param bConvert If true, the returned value is converted into the specifed unit of measure

   virtual Float64 GetValue(bool bConvert = false) const
   {
      Float64 value = bConvert ? ::ConvertFromSysUnits( m_Value, *m_pUnitOfMeasure ) : m_Value;

      if ( IsZero( value, m_ZeroTolerance ) )
         value = 0.;

      return value;
   }

   /// Sets the unit of measure
   void SetUnitOfMeasure(const T* pUnitOfMeasure)
   {
      m_pUnitOfMeasure = pUnitOfMeasure;
   }

   /// Returns the unit tag for the output unit of measure.
   virtual const std::_tstring& GetUnitTag() const override
   {
      return m_pUnitOfMeasure->UnitTag();
   }

   /// Sets the zero-tolerance value.
   ///
   /// Any value with absolute value of less than this tolerance will be returned through GetValue as zero and AsString will also return a zero value.
   void SetZeroTolerance(Float64 z)
   {
      m_ZeroTolerance = z;
   }

   /// Returns the zero-tolerance.
   Float64 GetZeroTolerance() const
   {
      return m_ZeroTolerance;
   }

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcUnitValueT& rOther)
   {
      m_Value          = rOther.m_Value;
      m_pUnitOfMeasure = rOther.m_pUnitOfMeasure;
      m_ZeroTolerance  = rOther.m_ZeroTolerance;
   }

   /// Assigns the content from oOther to this object
   virtual void MakeAssignment(const rptRcUnitValueT& rOther)
   {
      rptRcUnitValue::MakeAssignment( rOther );
      MakeCopy( rOther );
   }

private:
   Float64 m_Value;
   const T* m_pUnitOfMeasure;
   Float64 m_ZeroTolerance;
};

#define DECLARE_RC_UNIT_VALUE(u,t) \
   REPORTERTPL rptRcUnitValueT<u>; \
   typedef rptRcUnitValueT<u> t;

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
