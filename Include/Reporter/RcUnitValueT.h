///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Units\Convert.h>
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
      return new rptRcUnitValueT( *this );
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
      Float64 value = bConvert ? WBFL::Units::ConvertFromSysUnits( m_Value, *m_pUnitOfMeasure ) : m_Value;

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
   using t = rptRcUnitValueT<u>;

DECLARE_RC_UNIT_VALUE( WBFL::Units::Mass,           rptMassUnitValue           );
DECLARE_RC_UNIT_VALUE( WBFL::Units::MassPerLength,  rptMassPerLengthUnitValue  );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Length,         rptLengthUnitValue         );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Time,           rptTimeUnitValue           );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Temperature,    rptTemperatureUnitValue    );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Angle,          rptAngleUnitValue          );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Length2,        rptLength2UnitValue        );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Length3,        rptLength3UnitValue        );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Length4,        rptLength4UnitValue        );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Pressure,       rptPressureUnitValue       );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Density,        rptDensityUnitValue        );
DECLARE_RC_UNIT_VALUE( WBFL::Units::UnitWeight,     rptUnitWeightUnitValue     );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Force,          rptForceUnitValue          );
DECLARE_RC_UNIT_VALUE( WBFL::Units::ForcePerLength, rptForcePerLengthUnitValue );
DECLARE_RC_UNIT_VALUE( WBFL::Units::MomentPerAngle, rptMomentPerAngleUnitValue );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Moment,         rptMomentUnitValue         );
DECLARE_RC_UNIT_VALUE( WBFL::Units::PerLength,      rptPerLengthUnitValue      );
DECLARE_RC_UNIT_VALUE( WBFL::Units::ForceLength2,   rptForceLength2UnitValue   );
DECLARE_RC_UNIT_VALUE( WBFL::Units::Velocity,       rptVelocityUnitValue       );

using rptStressUnitValue = rptPressureUnitValue;
using rptAreaUnitValue = rptLength2UnitValue;
using rptVolumeUnitValue = rptLength3UnitValue;
using rptAreaPerLengthValue = rptLengthUnitValue;

#endif // INCLUDED_REPORTER_RCUNITVALUET_H_
