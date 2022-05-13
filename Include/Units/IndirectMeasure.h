///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2022  Washington State Department of Transportation
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
         IndirectMeasureDataT(const T& um,Float64 t = 0.001,Int16 w = 6,Int16 p = 3, sysNumericFormatTool::Format f=sysNumericFormatTool::Automatic) :
            UnitOfMeasure(um), Tol(t), Width(w), Precision(p), Format( f )
            {
            }

         IndirectMeasureDataT(const IndirectMeasureDataT&) = default;
         IndirectMeasureDataT& operator=(const IndirectMeasureDataT& rOther) = default;

         void Update(const T& um,Float64 t,Int16 w,Int16 p,sysNumericFormatTool::Format f)
         {
            UnitOfMeasure = um;
            Tol           = t;
            Width         = w;
            Precision     = p;
            Format        = f;
         }

         T UnitOfMeasure;
         Float64 Tol;
         Uint16 Width;
         Uint16 Precision;
         sysNumericFormatTool::Format Format;
      };

      /// Formatting data for scalar values
      struct ScalarData
      {
         Uint16 Width{ 8 };
         Uint16 Precision{ 4 };
         sysNumericFormatTool::Format Format{ sysNumericFormatTool::Automatic };
      };

      // These templates must be pre-instantiated so that they 
      // can be exported
      #define DECLARE_INDIRECT_MEASURE_DATA(u,t) \
         UNITSTPL IndirectMeasureDataT<u>; \
         typedef IndirectMeasureDataT<u> t;

      DECLARE_INDIRECT_MEASURE_DATA( Mass,           MassData           );
      DECLARE_INDIRECT_MEASURE_DATA( MassPerLength,  MassPerLengthData  );
      DECLARE_INDIRECT_MEASURE_DATA( Length,         LengthData         );
      DECLARE_INDIRECT_MEASURE_DATA( Time,           TimeData           );
      DECLARE_INDIRECT_MEASURE_DATA( Temperature,    TemperatureData    );
      DECLARE_INDIRECT_MEASURE_DATA( Angle,          AngleData          );
      DECLARE_INDIRECT_MEASURE_DATA( Length2,        Length2Data        );
      DECLARE_INDIRECT_MEASURE_DATA( Length3,        Length3Data        );
      DECLARE_INDIRECT_MEASURE_DATA( Length4,        Length4Data        );
      DECLARE_INDIRECT_MEASURE_DATA( Pressure,       PressureData       );
      DECLARE_INDIRECT_MEASURE_DATA( Density,        DensityData        );
      DECLARE_INDIRECT_MEASURE_DATA( UnitWeight,     UnitWeightData     );
      DECLARE_INDIRECT_MEASURE_DATA( Force,          ForceData          );
      DECLARE_INDIRECT_MEASURE_DATA( ForcePerLength, ForcePerLengthData );
      DECLARE_INDIRECT_MEASURE_DATA( MomentPerAngle, MomentPerAngleData );
      DECLARE_INDIRECT_MEASURE_DATA( Moment,         MomentData         );
      DECLARE_INDIRECT_MEASURE_DATA( PerLength,      PerLengthData      );
      DECLARE_INDIRECT_MEASURE_DATA( ForceLength2,   ForceLength2Data   );
      DECLARE_INDIRECT_MEASURE_DATA( SqrtPressure,   SqrtPressureData   );
      DECLARE_INDIRECT_MEASURE_DATA( Velocity,       VelocityData       );

      typedef PressureData StressData;
      typedef LengthData   AreaPerLengthData;


      /// An object that defines various indirect units of measure.
      /// This class is intended to be used as a value for LibraryT.
      class UNITSCLASS IndirectMeasure
      {
      public:
         IndirectMeasure() = default;
         IndirectMeasure(const IndirectMeasure&) = default;
         ~IndirectMeasure();
         IndirectMeasure& operator= (const IndirectMeasure&) = default;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(dbgDumpContext & os) const;
#endif // _DEBUG

         std::_tstring               Name{ _T("Default") };

         StationFormat         StationFormat; 

         ScalarData             Scalar{ 8,3, sysNumericFormatTool::Fixed };
         ScalarData             Percentage{ 6,2, sysNumericFormatTool::Fixed };

         LengthData         ComponentDim{ Measure::Millimeter };
         LengthData         XSectionDim{ Measure::Millimeter };
         LengthData         SpanLength{ Measure::Meter };
         LengthData         AlignmentLength{ Measure::Meter };
         LengthData         Deflection{ Measure::Millimeter };
         Length2Data        Area{ Measure::Millimeter2 };
         Length4Data        MomentOfInertia{ Measure::Millimeter4 };
         Length3Data        SectModulus{ Measure::Millimeter3 };
         AreaPerLengthData  AvOverS{ Measure::Meter2PerMeter};
         PressureData       Stress{Measure::MPa};
         PressureData       SmallStress{ Measure::MPa };
         PressureData       WindPressure{ Measure::Pa };
         PressureData       ModE{ Measure::MPa };
         ForceData          GeneralForce{ Measure::Kilonewton};
         ForceData          Tonnage{ Measure::Kilonewton };
         ForceData          Shear{ Measure::Kilonewton };
         MomentData         Moment{ Measure::KilonewtonMeter };
         MomentData         SmallMoment{ Measure::NewtonMillimeter };
         AngleData          Angle{ Measure::Degree };
         AngleData          RadAngle{ Measure::Radian };
         DensityData        Density{ Measure::KgPerMeter3 };
         MassPerLengthData  MassPerLength{ Measure::KgPerMeter };
         ForcePerLengthData ForcePerLength{ Measure::KilonewtonPerMeter };
         MomentPerAngleData MomentPerAngle{ Measure::KiloNewtonMeterPerRadian };
         TimeData           Time{ Measure::Hour };
         TimeData           Time2{ Measure::Day };
         TimeData           Time3{ Measure::Day };
         PerLengthData      PerLength{ Measure::PerMillimeter };
         PerLengthData      Curvature{ Measure::PerMillimeter };
         ForceLength2Data   ForceLength2{ Measure::KilonewtonMeter2 };
         SqrtPressureData   SqrtPressure{ Measure::SqrtMPa };
         VelocityData       Velocity{ Measure::KilometerPerHour };
      };
   };
};
