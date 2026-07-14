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

#include <Units\PhysicalT.h>
#include <Units\UnitsExp.h>

namespace WBFL
{
   namespace Units
   {
      /// Encapsulates instances of the physical unit object for specific units of measure.
      ///
      /// Each member is a named, ready-to-use instance of one of the dimension-type aliases declared in
      /// PhysicalT.h (Mass, Length, Force, Pressure, etc.). Use these directly with Convert(),
      /// ConvertToSysUnits(), and ConvertFromSysUnits() rather than constructing new PhysicalT instances by
      /// hand. This catalog is not exhaustive or closed: any application can define its own named instance
      /// of an existing dimension-type alias (e.g. a unit this catalog doesn't already have) simply by
      /// constructing one directly - see PhysicalT's constructor.
      class UNITSCLASS Measure
      {
      public:
         Measure() = delete;
         Measure(const Measure&) = delete;
         Measure& operator=(const Measure&) = delete;

         static const Mass Kilogram;   ///< Kilogram, the SI base unit of mass (tag "kg")
         static const Mass Gram;       ///< Gram (tag "g")
         static const Mass MetricTon;  ///< Metric ton/tonne, 1000 kg (tag "MT")
         static const Mass Megagram;   ///< Megagram, numerically equal to MetricTon, 1000 kg (tag "Mg")
         static const Mass Slug;       ///< Slug, the US customary mass unit consistent with force in pounds and length in feet (tag "slug")
         static const Mass PoundMass;  ///< Pound-mass (tag "lbm")
         static const Mass KSlug;      ///< Kip-slug, mass consistent with force in kips and length in feet (tag "kslug")
         static const Mass _12Slug;    ///< Mass consistent with force in pounds and length in inches (tag "12slug")
         static const Mass _12KSlug;   ///< Mass consistent with force in kips and length in inches (tag "12kslug")

         static const MassPerLength KgPerMeter;  ///< Kilograms per meter (tag "kg/m")
         static const MassPerLength LbmPerFeet;  ///< Pounds-mass per foot (tag "lbm/ft")
         static const MassPerLength SlugPerFeet; ///< Slugs per foot (tag "slug/ft")

         /// Pounds-force per foot (tag "lbf/ft"). This is a minor hack to make the use of mass in SI mode
         /// the same as the use of force in US mode.
         static const MassPerLength LbfPerFeet;

         static const Length Meter;        ///< Meter, the SI base unit of length (tag "m")
         static const Length Millimeter;   ///< Millimeter (tag "mm")
         static const Length Centimeter;   ///< Centimeter (tag "cm")
         static const Length Kilometer;    ///< Kilometer (tag "km")
         static const Length Feet;         ///< US customary foot (tag "ft")
         static const Length USSurveyFoot; ///< US survey foot, 1200/3937 m (tag "ft")
         static const Length Inch;         ///< Inch (tag "in")
         static const Length Mile;         ///< Mile (tag "mile")
         static const Length Yard;         ///< Yard (tag "yd")
         static const Length USSurveyYard; ///< US survey yard, 3600/3937 m (tag "yd")

         static const Length2 Meter2;      ///< Square meters (tag "m^2")
         static const Length2 Millimeter2; ///< Square millimeters (tag "mm^2")
         static const Length2 Centimeter2; ///< Square centimeters (tag "cm^2")
         static const Length2 Kilometer2;  ///< Square kilometers (tag "km^2")
         static const Length2 Feet2;       ///< Square feet (tag "ft^2")
         static const Length2 Inch2;       ///< Square inches (tag "in^2")
         static const Length2 Mile2;       ///< Square miles (tag "mile^2")
         static const Length2 Yard2;       ///< Square yards (tag "yd^2")

         static const Length3 Meter3;      ///< Cubic meters (tag "m^3")
         static const Length3 Millimeter3; ///< Cubic millimeters (tag "mm^3")
         static const Length3 Centimeter3; ///< Cubic centimeters (tag "cm^3")
         static const Length3 Kilometer3;  ///< Cubic kilometers (tag "km^3")
         static const Length3 Feet3;       ///< Cubic feet (tag "ft^3")
         static const Length3 Inch3;       ///< Cubic inches (tag "in^3")
         static const Length3 Mile3;       ///< Cubic miles (tag "mile^3")
         static const Length3 Yard3;       ///< Cubic yards (tag "yd^3")

         static const Length4 Meter4;      ///< Meters to the 4th power, used for moment of inertia (tag "m^4")
         static const Length4 Millimeter4; ///< Millimeters to the 4th power (tag "mm^4")
         static const Length4 Centimeter4; ///< Centimeters to the 4th power (tag "cm^4")
         static const Length4 Kilometer4;  ///< Kilometers to the 4th power (tag "km^4")
         static const Length4 Feet4;       ///< Feet to the 4th power (tag "ft^4")
         static const Length4 Inch4;       ///< Inches to the 4th power (tag "in^4")
         static const Length4 Mile4;       ///< Miles to the 4th power (tag "mile^4")
         static const Length4 Yard4;       ///< Yards to the 4th power (tag "yd^4")

         static const AreaPerLength Meter2PerMeter;           ///< Square meters per meter (tag "m^2/m")
         static const AreaPerLength Millimeter2PerMillimeter; ///< Square millimeters per millimeter (tag "mm^2/mm")
         static const AreaPerLength Millimeter2PerMeter;      ///< Square millimeters per meter (tag "mm^2/m")
         static const AreaPerLength Feet2PerFoot;             ///< Square feet per foot (tag "ft^2/ft")
         static const AreaPerLength Inch2PerInch;             ///< Square inches per inch (tag "in^2/in")
         static const AreaPerLength Inch2PerFoot;             ///< Square inches per foot (tag "in^2/ft")

         static const PerLength PerMeter;      ///< Inverse meters (tag "m^-1")
         static const PerLength PerMillimeter; ///< Inverse millimeters (tag "mm^-1")
         static const PerLength PerInch;       ///< Inverse inches (tag "in^-1")
         static const PerLength PerFeet;       ///< Inverse feet (tag "ft^-1")

         static const Time Second; ///< Second, the SI base unit of time (tag "sec")
         static const Time Minute; ///< Minute (tag "min")
         static const Time Hour;   ///< Hour (tag "hr")
         static const Time Day;    ///< Day (tag "day")

         static const Temperature Celsius;    ///< Degrees Celsius (tag "C")
         static const Temperature Fahrenheit; ///< Degrees Fahrenheit (tag "F")

         static const Angle Radian; ///< Radian (tag "rad")
         static const Angle Degree; ///< Degree (tag "deg")

         static const Pressure Pa;  ///< Pascal, N/m^2 (tag "Pa")
         static const Pressure kPa; ///< Kilopascal (tag "kPa")
         static const Pressure MPa; ///< Megapascal (tag "MPa")
         static const Pressure PSI; ///< Pounds per square inch (tag "PSI")
         static const Pressure PSF; ///< Pounds per square foot (tag "PSF")
         static const Pressure KSI; ///< Kips per square inch (tag "KSI")
         static const Pressure KSF; ///< Kips per square foot (tag "KSF")

         static const UnitWeight NewtonPerMeter3; ///< Newtons per cubic meter (tag "N/m^3")
         static const UnitWeight PCI;             ///< Pounds per cubic inch (tag "PCI")
         static const UnitWeight PCF;             ///< Pounds per cubic foot (tag "PCF")

         static const Density KgPerMeter3;  ///< Kilograms per cubic meter (tag "kg/m^3")
         static const Density LbmPerFeet3;  ///< Pounds-mass per cubic foot (tag "lbm/ft^3")
         static const Density SlugPerFeet3; ///< Slugs per cubic foot (tag "slug/ft^3")
         static const Density LbfPerFeet3;  ///< Pounds-force per cubic foot, numerically equal to LbmPerFeet3 (tag "lbf/ft^3")
         static const Density KipPerFeet3;  ///< Kips per cubic foot (tag "kip/ft^3")

         static const Force Newton;     ///< Newton (tag "N")
         static const Force Kilonewton; ///< Kilonewton (tag "kN")
         static const Force Pound;      ///< Pound-force (tag "lbf")
         static const Force Kip;        ///< Kip, 1000 lbf (tag "kip")
         static const Force Ton;        ///< Ton-force, 2000 lbf (tag "ton")

         static const ForcePerLength NewtonPerMeter;      ///< Newtons per meter (tag "N/m")
         static const ForcePerLength KilonewtonPerMeter;  ///< Kilonewtons per meter (tag "kN/m")
         static const ForcePerLength NewtonPerMillimeter; ///< Newtons per millimeter (tag "N/mm")
         static const ForcePerLength LbfPerFoot;          ///< Pounds-force per foot (tag "lbf/ft")
         static const ForcePerLength LbfPerInch;          ///< Pounds-force per inch (tag "lbf/in")
         static const ForcePerLength KipPerFoot;          ///< Kips per foot (tag "kip/ft")
         static const ForcePerLength KipPerInch;          ///< Kips per inch (tag "kip/in")

         static const Moment NewtonMeter;      ///< Newton-meters (tag "N-m")
         static const Moment KilonewtonMeter;  ///< Kilonewton-meters (tag "kN-m")
         static const Moment NewtonMillimeter; ///< Newton-millimeters (tag "N-mm")
         static const Moment InchLbf;          ///< Inch-pounds (tag "in-lbf")
         static const Moment PoundFeet;         ///< Pound-feet, 1/1000 of KipFeet (tag "lbf-ft")
         static const Moment KipFeet;          ///< Kip-feet (tag "kip-ft")
         static const Moment KipInch;          ///< Kip-inches (tag "kip-in")

         static const MomentPerAngle NewtonMeterPerRadian;     ///< Newton-meters per radian (tag "N-m/rad")
         static const MomentPerAngle KiloNewtonMeterPerRadian; ///< Kilonewton-meters per radian (tag "kN-m/rad")
         static const MomentPerAngle KipInchPerRadian;         ///< Kip-inches per radian (tag "kip-in/rad")
         static const MomentPerAngle KipFeetPerRadian;         ///< Kip-feet per radian (tag "kip-ft/rad")

         static const SqrtPressure SqrtPa;  ///< Square root of pascals (tag "Pa^0.5")
         static const SqrtPressure SqrtMPa; ///< Square root of megapascals, commonly used in concrete cracking/rupture-modulus formulas (tag "MPa^0.5")
         static const SqrtPressure SqrtKSI; ///< Square root of kips per square inch (tag "KSI^0.5")

         static const Acceleration MeterPerSec2; ///< Meters per second squared (tag "m/s^2")
         static const Acceleration FeetPerSec2;  ///< Feet per second squared (tag "ft/s^2")

         static const ForceLength2 KipInch2;          ///< Kip-inches^2, used for flexural rigidity (E*I) (tag "kip-in^2")
         static const ForceLength2 KipFoot2;          ///< Kip-feet^2 (tag "kip-ft^2")
         static const ForceLength2 LbfInch2;           ///< Pound-inches^2 (tag "lbf-in^2")
         static const ForceLength2 LbfFoot2;           ///< Pound-feet^2 (tag "lbf-ft^2")
         static const ForceLength2 NewtonMeter2;       ///< Newton-meters^2 (tag "N-m^2")
         static const ForceLength2 NewtonMillimeter2;  ///< Newton-millimeters^2 (tag "N-mm^2")
         static const ForceLength2 KilonewtonMeter2;   ///< Kilonewton-meters^2 (tag "kN-m^2")

         static const Velocity KilometerPerHour; ///< Kilometers per hour (tag "Km/h")
         static const Velocity MeterPerSecond;    ///< Meters per second (tag "m/s")
         static const Velocity MilePerHour;       ///< Miles per hour (tag "MPH")
         static const Velocity FeetPerSecond;     ///< Feet per second (tag "ft/s")

         static const ThermalExpansion PerCelsius;    ///< Inverse degrees Celsius, coefficient of thermal expansion (tag "1/C")
         static const ThermalExpansion PerFahrenheit; ///< Inverse degrees Fahrenheit (tag "1/F")
      };
   };
};

