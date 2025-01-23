///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#pragma once

#include <Units\PhysicalT.h>
#include <Units\UnitsExp.h>

namespace WBFL
{
   namespace Units
   {
      /// Encapsulates instances of the physical unit object for specific units of measure
      class UNITSCLASS Measure
      {
      public:
         Measure() = delete;
         Measure(const Measure&) = delete;
         Measure& operator=(const Measure&) = delete;

         static const Mass Kilogram;
         static const Mass Gram;
         static const Mass MetricTon;
         static const Mass Slug;
         static const Mass PoundMass;
         static const Mass KSlug;
         static const Mass _12Slug;
         static const Mass _12KSlug;

         static const MassPerLength KgPerMeter;
         static const MassPerLength LbmPerFeet;
         static const MassPerLength SlugPerFeet;
         static const MassPerLength LbfPerFeet;  // This is a minor hack to make the
                                                 // use of mass in SI mode the same
                                                 // as force in US mode

         static const Length Meter;
         static const Length Millimeter;
         static const Length Centimeter;
         static const Length Kilometer;
         static const Length Feet;
         static const Length USSurveyFoot;
         static const Length Inch;
         static const Length Mile;
         static const Length Yard;
         static const Length USSurveyYard;

         static const Length2 Meter2;
         static const Length2 Millimeter2;
         static const Length2 Centimeter2;
         static const Length2 Kilometer2;
         static const Length2 Feet2;
         static const Length2 Inch2;
         static const Length2 Mile2;
         static const Length2 Yard2;

         static const Length3 Meter3;
         static const Length3 Millimeter3;
         static const Length3 Centimeter3;
         static const Length3 Kilometer3;
         static const Length3 Feet3;
         static const Length3 Inch3;
         static const Length3 Mile3;
         static const Length3 Yard3;

         static const Length4 Meter4;
         static const Length4 Millimeter4;
         static const Length4 Centimeter4;
         static const Length4 Kilometer4;
         static const Length4 Feet4;
         static const Length4 Inch4;
         static const Length4 Mile4;
         static const Length4 Yard4;

         static const AreaPerLength Meter2PerMeter;
         static const AreaPerLength Millimeter2PerMillimeter;
         static const AreaPerLength Millimeter2PerMeter;
         static const AreaPerLength Feet2PerFoot;
         static const AreaPerLength Inch2PerInch;
         static const AreaPerLength Inch2PerFoot;

         static const PerLength PerMeter;
         static const PerLength PerMillimeter;
         static const PerLength PerInch;
         static const PerLength PerFeet;

         static const Time Second;
         static const Time Minute;
         static const Time Hour;
         static const Time Day;

         static const Temperature Celsius;
         static const Temperature Fahrenheit;

         static const Angle Radian;
         static const Angle Degree;

         static const Pressure Pa;
         static const Pressure kPa;
         static const Pressure MPa;
         static const Pressure PSI;
         static const Pressure PSF;
         static const Pressure KSI;
         static const Pressure KSF;

         static const UnitWeight NewtonPerMeter3;
         static const UnitWeight PCI;
         static const UnitWeight PCF;

         static const Density KgPerMeter3;
         static const Density LbmPerFeet3;
         static const Density SlugPerFeet3;
         static const Density LbfPerFeet3;
         static const Density KipPerFeet3;

         static const Force Newton;
         static const Force Kilonewton;
         static const Force Pound;
         static const Force Kip;
         static const Force Ton;

         static const ForcePerLength NewtonPerMeter;
         static const ForcePerLength KilonewtonPerMeter;
         static const ForcePerLength NewtonPerMillimeter;
         static const ForcePerLength LbfPerFoot;
         static const ForcePerLength LbfPerInch;
         static const ForcePerLength KipPerFoot;
         static const ForcePerLength KipPerInch;

         static const Moment NewtonMeter;
         static const Moment KilonewtonMeter;
         static const Moment NewtonMillimeter;
         static const Moment InchLbf;
         static const Moment KipFeet;
         static const Moment KipInch;

         static const MomentPerAngle NewtonMeterPerRadian;
         static const MomentPerAngle KiloNewtonMeterPerRadian;
         static const MomentPerAngle KipInchPerRadian;
         static const MomentPerAngle KipFeetPerRadian;

         static const SqrtPressure SqrtPa;
         static const SqrtPressure SqrtMPa;
         static const SqrtPressure SqrtKSI;

         static const Acceleration MeterPerSec2;
         static const Acceleration FeetPerSec2;

         static const ForceLength2 KipInch2;
         static const ForceLength2 KipFoot2;
         static const ForceLength2 LbfInch2;
         static const ForceLength2 LbfFoot2;
         static const ForceLength2 NewtonMeter2;
         static const ForceLength2 NewtonMillimeter2;
         static const ForceLength2 KilonewtonMeter2;

         static const Velocity KilometerPerHour;
         static const Velocity MeterPerSecond;
         static const Velocity MilePerHour;
         static const Velocity FeetPerSecond;
      };
   };
};

