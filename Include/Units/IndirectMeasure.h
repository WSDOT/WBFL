///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright � 1999-2026  Washington State Department of Transportation
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

#include <Units\UnitsExp.h>
#include <Units\PhysicalT.h>
#include <Units\Measure.h>
#include <Units\StationFormat.h>
#include <System\System.h>

namespace WBFL
{
   namespace Units
   {
      /// Template class that defines an indirect unit of measure along with its display attributes.
      ///
      /// The display attributes includes a tolerance, field width, precision, and a format type.
      /// A value less than the tolerance is taken as zero. The field width, precision, and format type
      /// are used by a formatting tool to format the value when represented as a text string.
      template <class T>
      class IndirectMeasureDataT
      {
      public:
         /// Constructs a display profile for unit-of-measure type T: display in um, treating magnitudes
         /// below t as zero, with the given field width, precision, and numeric format.
         IndirectMeasureDataT(const T& um,Float64 t = 0.001,Uint16 w = 6,Uint16 p = 3, WBFL::System::NumericFormatTool::Format f=WBFL::System::NumericFormatTool::Format::Automatic) :
            UnitOfMeasure(um), Tol(t), Width(w), Precision(p), Format( f )
            {
            }

         IndirectMeasureDataT(const IndirectMeasureDataT&) = default;
         IndirectMeasureDataT& operator=(const IndirectMeasureDataT& rOther) = default;

         /// Updates all of this profile's fields at once.
         void Update(const T& um,Float64 t,Int16 w,Int16 p,WBFL::System::NumericFormatTool::Format f)
         {
            UnitOfMeasure = um;
            Tol           = t;
            Width         = w;
            Precision     = p;
            Format        = f;
         }

         T UnitOfMeasure;                             ///< The unit of measure values are displayed in
         Float64 Tol;                                 ///< The largest magnitude, in system units, that is displayed as zero
         Uint16 Width;                                 ///< The minimum field width of the formatted text
         Uint16 Precision;                             ///< The number of digits of precision in the formatted text
         WBFL::System::NumericFormatTool::Format Format; ///< The numeric notation (fixed, scientific, etc.) used to format the value
      };

      /// Formatting data for scalar (dimensionless) values.
      struct ScalarData
      {
         Uint16 Width{ 8 };                                                                        ///< The minimum field width of the formatted text
         Uint16 Precision{ 4 };                                                                     ///< The number of digits of precision in the formatted text
         WBFL::System::NumericFormatTool::Format Format{ WBFL::System::NumericFormatTool::Format::Automatic }; ///< The numeric notation used to format the value
      };

      /// Explicitly instantiates and exports IndirectMeasureDataT<u>, and declares t as an alias for it.
      /// These templates must be pre-instantiated so that they can be exported from the DLL.
      #define DECLARE_INDIRECT_MEASURE_DATA(u,t) \
         UNITSTPL IndirectMeasureDataT<u>; \
         using t = IndirectMeasureDataT<u>;

      DECLARE_INDIRECT_MEASURE_DATA( Mass,           MassData           ); ///< Display profile for Mass values
      DECLARE_INDIRECT_MEASURE_DATA( MassPerLength,  MassPerLengthData  ); ///< Display profile for MassPerLength values
      DECLARE_INDIRECT_MEASURE_DATA( Length,         LengthData         ); ///< Display profile for Length values
      DECLARE_INDIRECT_MEASURE_DATA( Time,           TimeData           ); ///< Display profile for Time values
      DECLARE_INDIRECT_MEASURE_DATA( Temperature,    TemperatureData    ); ///< Display profile for Temperature values
      DECLARE_INDIRECT_MEASURE_DATA( Angle,          AngleData          ); ///< Display profile for Angle values
      DECLARE_INDIRECT_MEASURE_DATA( Length2,        Length2Data        ); ///< Display profile for Length2 (area) values
      DECLARE_INDIRECT_MEASURE_DATA( Length3,        Length3Data        ); ///< Display profile for Length3 (volume) values
      DECLARE_INDIRECT_MEASURE_DATA( Length4,        Length4Data        ); ///< Display profile for Length4 (moment of inertia) values
      DECLARE_INDIRECT_MEASURE_DATA( Pressure,       PressureData       ); ///< Display profile for Pressure/Stress values
      DECLARE_INDIRECT_MEASURE_DATA( Density,        DensityData        ); ///< Display profile for Density values
      DECLARE_INDIRECT_MEASURE_DATA( UnitWeight,     UnitWeightData     ); ///< Display profile for UnitWeight values
      DECLARE_INDIRECT_MEASURE_DATA( Force,          ForceData          ); ///< Display profile for Force values
      DECLARE_INDIRECT_MEASURE_DATA( ForcePerLength, ForcePerLengthData ); ///< Display profile for ForcePerLength values
      DECLARE_INDIRECT_MEASURE_DATA( MomentPerAngle, MomentPerAngleData ); ///< Display profile for MomentPerAngle values
      DECLARE_INDIRECT_MEASURE_DATA( Moment,         MomentData         ); ///< Display profile for Moment values
      DECLARE_INDIRECT_MEASURE_DATA( PerLength,      PerLengthData      ); ///< Display profile for PerLength (curvature) values
      DECLARE_INDIRECT_MEASURE_DATA( ForceLength2,   ForceLength2Data   ); ///< Display profile for ForceLength2 (flexural rigidity) values
      DECLARE_INDIRECT_MEASURE_DATA( SqrtPressure,   SqrtPressureData   ); ///< Display profile for SqrtPressure values
      DECLARE_INDIRECT_MEASURE_DATA( Velocity,       VelocityData       ); ///< Display profile for Velocity values

      using StressData = PressureData;      ///< Alias for PressureData
      using AreaPerLengthData = LengthData;  ///< Alias for LengthData


      /// An object that defines a complete, named set of indirect units of measure (a "display profile"),
      /// one entry per kind of quantity an application typically needs to show a user (component
      /// dimensions, stress, force, angle, etc.), each with its own unit of measure, zero-tolerance, field
      /// width, precision, and numeric format.
      ///
      /// This class is intended to be used as the value type of a Library (e.g. one entry named "US units"
      /// and another named "SI units"), so that switching an application's display profile is a matter of
      /// looking up a different named IndirectMeasure rather than reconfiguring every quantity by hand. All
      /// members are public data (no accessors) since this is a plain, mutable settings object; every
      /// member defaults to a reasonable SI value.
      class UNITSCLASS IndirectMeasure
      {
      public:
         IndirectMeasure() = default;
         IndirectMeasure(const IndirectMeasure&) = default;
         ~IndirectMeasure();
         IndirectMeasure& operator= (const IndirectMeasure&) = default;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext & os) const;
#endif // _DEBUG

         std::_tstring               Name{ _T("Default") }; ///< The name of this display profile (e.g. "US units", "SI units")

         StationFormat         StationFormat; ///< The stationing display format for this profile

         ScalarData             Scalar{ 8,3, WBFL::System::NumericFormatTool::Format::Fixed };     ///< Display format for generic dimensionless scalar values
         ScalarData             Percentage{ 6,2, WBFL::System::NumericFormatTool::Format::Fixed }; ///< Display format for percentage values

         LengthData         ComponentDim{ Measure::Millimeter };                     ///< Display unit for the dimensions of a structural component (e.g. girder depth, flange width)
         LengthData         XSectionDim{ Measure::Millimeter };                      ///< Display unit for cross-section dimensions
         LengthData         SpanLength{ Measure::Meter };                            ///< Display unit for span lengths
         LengthData         AlignmentLength{ Measure::Meter };                       ///< Display unit for roadway alignment/station lengths
         LengthData         Deflection{ Measure::Millimeter };                       ///< Display unit for deflection values
         Length2Data        Area{ Measure::Millimeter2 };                            ///< Display unit for cross-sectional area
         Length4Data        MomentOfInertia{ Measure::Millimeter4 };                 ///< Display unit for moment of inertia
         Length3Data        SectModulus{ Measure::Millimeter3 };                     ///< Display unit for section modulus
         AreaPerLengthData  AvOverS{ Measure::Meter2PerMeter};                       ///< Display unit for shear-reinforcement area per unit spacing (Av/S)
         PressureData       Stress{Measure::MPa};                                    ///< Display unit for general stress values
         PressureData       SmallStress{ Measure::MPa };                             ///< Display unit for stress values that are typically small in magnitude, so a finer display format is appropriate
         PressureData       WindPressure{ Measure::Pa };                             ///< Display unit for wind pressure
         PressureData       ModE{ Measure::MPa };                                    ///< Display unit for modulus of elasticity
         ForceData          GeneralForce{ Measure::Kilonewton};                      ///< Display unit for general force values
         ForceData          Tonnage{ Measure::Kilonewton };                          ///< Display unit for tonnage (large force/weight) values
         ForceData          Shear{ Measure::Kilonewton };                            ///< Display unit for shear force
         MomentData         Moment{ Measure::KilonewtonMeter };                      ///< Display unit for general moment values
         MomentData         SmallMoment{ Measure::NewtonMillimeter };                ///< Display unit for moment values that are typically small in magnitude
         AngleData          Angle{ Measure::Degree };                                ///< Display unit for angles, in degrees
         AngleData          RadAngle{ Measure::Radian };                             ///< Display unit for angles that are conventionally shown in radians (e.g. rotational stiffness)
         DensityData        Density{ Measure::KgPerMeter3 };                         ///< Display unit for material density
         MassPerLengthData  MassPerLength{ Measure::KgPerMeter };                    ///< Display unit for mass per unit length
         ForcePerLengthData ForcePerLength{ Measure::KilonewtonPerMeter };           ///< Display unit for force per unit length (e.g. distributed load)
         MomentPerAngleData MomentPerAngle{ Measure::KiloNewtonMeterPerRadian };     ///< Display unit for rotational stiffness (moment per unit angle)
         TimeData           Time{ Measure::Hour };                                   ///< Display unit for general time durations
         TimeData           Time2{ Measure::Day };                                   ///< Display unit for a second class of (typically longer) time durations
         TimeData           Time3{ Measure::Day };                                   ///< Display unit for a third class of time durations
         PerLengthData      PerLength{ Measure::PerMillimeter };                     ///< Display unit for inverse-length values
         PerLengthData      Curvature{ Measure::PerMillimeter };                     ///< Display unit for curvature (1/radius)
         ForceLength2Data   ForceLength2{ Measure::KilonewtonMeter2 };               ///< Display unit for flexural rigidity (E*I) values
         SqrtPressureData   SqrtPressure{ Measure::SqrtMPa };                        ///< Display unit for sqrt(pressure) values (e.g. concrete cracking/rupture modulus)
         TemperatureData    Temperature{ Measure::Celsius };                         ///< Display unit for temperature
         VelocityData       Velocity{ Measure::KilometerPerHour };                   ///< Display unit for velocity
      };
   };
};
