///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <Units\UnitsLib.h>
#include <Units\Measure.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/****************************************************************************
CLASS
   unitMeasure
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== DATA MEMBERS =======================================
const unitMass unitMeasure::Kilogram   ( 0.0, 1.000,         0.0 ,"kg"   );
const unitMass unitMeasure::Gram       ( 0.0, 0.001,         0.0, "g"    ); 
const unitMass unitMeasure::MetricTon  ( 0.0, 1.0e03,        0.0, "MT" );
const unitMass unitMeasure::Slug       ( 0.0, 14.5939029372, 0.0, "slug" );
const unitMass unitMeasure::PoundMass  ( 0.0, 0.45359237,    0.0, "lbm"  );

const unitMassPerLength unitMeasure::KgPerMeter ( 0.0, 1.000,         0.0, "kg/m" );
const unitMassPerLength unitMeasure::LbmPerFeet ( 0.0, 0.671968975139, 0.0, "lbm/ft" );
const unitMassPerLength unitMeasure::SlugPerFeet( 0.0, 0.0208854342115,  0.0, "slug/ft" );
const unitMassPerLength unitMeasure::LbfPerFeet ( 0.0, 1.48816394357,  0.0, "lbf/ft" );

const unitLength unitMeasure::Meter       ( 0.0, 1.0,      0.0, "m"    );
const unitLength unitMeasure::Millimeter  ( 0.0, 1.0e-03,  0.0, "mm"   );
const unitLength unitMeasure::Centimeter  ( 0.0, 1.0e-02,  0.0, "cm"   );
const unitLength unitMeasure::Kilometer   ( 0.0, 1.0e03,   0.0, "km"   );
const unitLength unitMeasure::Feet        ( 0.0, 0.3048,   0.0, "ft"   );
const unitLength unitMeasure::Inch        ( 0.0, 0.0254,   0.0, "in"   );
const unitLength unitMeasure::Mile        ( 0.0, 1609.344, 0.0, "mile" );
const unitLength unitMeasure::Yard        ( 0.0, 0.9144,   0.0, "yd"   );

const unitAreaPerLength unitMeasure::Meter2PerMeter           ( 0.0, 1.0,      0.0, "m^2/m"  );
const unitAreaPerLength unitMeasure::Millimeter2PerMillimeter ( 0.0, 1.0e-03,  0.0, "mm^2/mm");
const unitAreaPerLength unitMeasure::Millimeter2PerMeter      ( 0.0, 1.0e-06,  0.0, "mm^2/m");
const unitAreaPerLength unitMeasure::Feet2PerFoot             ( 0.0, 0.3048,   0.0, "ft^2/ft");
const unitAreaPerLength unitMeasure::Inch2PerInch             ( 0.0, 0.0254,   0.0, "in^2/in");
const unitAreaPerLength unitMeasure::Inch2PerFoot             ( 0.0, 0.0021166666666667, 0.0, "in^2/ft");

const unitLength2 unitMeasure::Meter2       ( 0.0, 1.0,           0.0, "m^2"    );
const unitLength2 unitMeasure::Millimeter2  ( 0.0, 1.0e-06,       0.0, "mm^2"   );
const unitLength2 unitMeasure::Centimeter2  ( 0.0, 1.0e-04,       0.0, "cm^2"   );
const unitLength2 unitMeasure::Kilometer2   ( 0.0, 1.0e06,        0.0, "km^2"   );
const unitLength2 unitMeasure::Feet2        ( 0.0, 0.09290304,    0.0, "ft^2"   );
const unitLength2 unitMeasure::Inch2        ( 0.0, 0.00064516,    0.0, "in^2"   );
const unitLength2 unitMeasure::Mile2        ( 0.0, 2589988.11034, 0.0, "mile^2" );
const unitLength2 unitMeasure::Yard2        ( 0.0, 0.83612736,    0.0, "yd^2"   );

const unitLength3 unitMeasure::Meter3       ( 0.0, 1.0,            0.0, "m^3"    );
const unitLength3 unitMeasure::Millimeter3  ( 0.0, 1.0e-09,        0.0, "mm^3"   );
const unitLength3 unitMeasure::Centimeter3  ( 0.0, 1.0e-06,        0.0, "cm^3"   );
const unitLength3 unitMeasure::Kilometer3   ( 0.0, 1.0e09,         0.0, "km^3"   );
const unitLength3 unitMeasure::Feet3        ( 0.0, 0.028316846592, 0.0, "ft^3"   );
const unitLength3 unitMeasure::Inch3        ( 0.0, 0.000016387064, 0.0, "in^3"   );
const unitLength3 unitMeasure::Mile3        ( 0.0, 4168181825.44,  0.0, "mile^3" );
const unitLength3 unitMeasure::Yard3        ( 0.0, 0.764554857984, 0.0, "yd^3"   );

const unitLength4 unitMeasure::Meter4       ( 0.0, 1.0,               0.0, "m^4"    );
const unitLength4 unitMeasure::Millimeter4  ( 0.0, 1.0e-12,           0.0, "mm^4"   );
const unitLength4 unitMeasure::Centimeter4  ( 0.0, 1.0e-08,           0.0, "cm^4"   );
const unitLength4 unitMeasure::Kilometer4   ( 0.0, 1.0e12,            0.0, "km^4"   );
const unitLength4 unitMeasure::Feet4        ( 0.0, 8.63097484124e-03, 0.0, "ft^4"   );
const unitLength4 unitMeasure::Inch4        ( 0.0, 4.162314256e-07,   0.0, "in^4"   );
const unitLength4 unitMeasure::Mile4        ( 0.0, 6.70803841168e12,  0.0, "mile^4" );
const unitLength4 unitMeasure::Yard4        ( 0.0, 0.699108962141,    0.0, "yd^4"   );

const unitTime unitMeasure::Second ( 0.0,     1.0, 0.0, "sec" );
const unitTime unitMeasure::Minute ( 0.0,    60.0, 0.0, "min" );
const unitTime unitMeasure::Hour   ( 0.0,  3600.0, 0.0, "hr"  );
const unitTime unitMeasure::Day    ( 0.0, 86400.0, 0.0, "day" );

const unitTemperature unitMeasure::Celcius    ( 0.0, 1.0,  0.0, "C" );
const unitTemperature unitMeasure::Fahrenheit (-32.0, 5./9., 0.0, "F" );

const unitAngle unitMeasure::Radian ( 0.0, 1.0,               0.0, "rad" );
const unitAngle unitMeasure::Degree ( 0.0, 1.74532925199e-02, 0.0, "deg" );

const unitPressure unitMeasure::Pa  ( 0.0, 1.0,                0.0, "Pa"  );
const unitPressure unitMeasure::kPa ( 0.0, 1.0e03,             0.0, "kPa" );
const unitPressure unitMeasure::MPa ( 0.0, 1.0e06,             0.0, "MPa" );
const unitPressure unitMeasure::PSI ( 0.0, 6.89475729317e03,   0.0, "PSI" );
const unitPressure unitMeasure::PSF ( 0.0, 4.78802589803e01,   0.0, "PSF" );
const unitPressure unitMeasure::KSI ( 0.0, 6.89475729317e06,   0.0, "KSI" );
const unitPressure unitMeasure::KSF ( 0.0, 4.78802589803e04,   0.0, "KSF" );

const unitUnitWeight unitMeasure::NewtonPerMeter3 ( 0.0, 1.0,           0.0, "N/m^3" );
const unitUnitWeight unitMeasure::PCI             ( 0.0, 271447.1375263134, 0.0, "PCI"   );
const unitUnitWeight unitMeasure::PCF             ( 0.0, 157.08746384624618, 0.0, "PCF"   );

const unitDensity unitMeasure::KgPerMeter3  ( 0.0, 1.0,           0.0, "kg/m^3"    );
const unitDensity unitMeasure::LbmPerFeet3  ( 0.0,  16.01846337396013800,  0.0, "lbm/ft^3"  );
const unitDensity unitMeasure::SlugPerFeet3 ( 0.0, 515.37881839319730000, 0.0, "slug/ft^3" );
const unitDensity unitMeasure::LbfPerFeet3  ( 0.0,  16.01846337396013800,  0.0, "lbf/ft^3"  );

const unitForce unitMeasure::Newton     ( 0.0, 1.0,           0.0, "N"          );
const unitForce unitMeasure::Kilonewton ( 0.0, 1.0e03,       0.0, "kN"          );
const unitForce unitMeasure::Pound      ( 0.0, 4.4482216152605, 0.0, "lbf"        );
const unitForce unitMeasure::Kip        ( 0.0, 4448.2216152605, 0.0, "kip"        );
const unitForce unitMeasure::Ton        ( 0.0, 8896.44323052, 0.0, "ton"        );

const unitForcePerLength unitMeasure::NewtonPerMeter      ( 0.0, 1.0,           0.0, "N/m"    );
const unitForcePerLength unitMeasure::KilonewtonPerMeter  ( 0.0, 1.0e03,        0.0, "kN/m"   );
const unitForcePerLength unitMeasure::NewtonPerMillimeter ( 0.0, 1.0e03,        0.0, "N/mm"   );
const unitForcePerLength unitMeasure::LbfPerFoot          ( 0.0, 14.593902937206362, 0.0, "lbf/ft" );
const unitForcePerLength unitMeasure::LbfPerInch          ( 0.0, 175.126835246, 0.0, "lbf/in" );
const unitForcePerLength unitMeasure::KipPerFoot          ( 0.0, 14593.902937206362, 0.0, "kip/ft" );
const unitForcePerLength unitMeasure::KipPerInch          ( 0.0, 175126.835246, 0.0, "kip/in" );

const unitMoment unitMeasure::NewtonMeter     ( 0.0, 1.0,            0.0, "N-m"    );
const unitMoment unitMeasure::KilonewtonMeter ( 0.0, 1.0e03,         0.0, "kN-m"   );
const unitMoment unitMeasure::NewtonMillimeter( 0.0, 1.0e-03,        0.0, "N-mm"   );
const unitMoment unitMeasure::InchLbf         ( 0.0, 0.112984829028, 0.0, "in-lbf" );
const unitMoment unitMeasure::KipFeet         ( 0.0, 1355.8179483314004,  0.0, "kip-ft" );
const unitMoment unitMeasure::KipInch         ( 0.0, 112.984829028, 0.0, "kip-in" );

const unitMomentPerAngle unitMeasure::NewtonMeterPerRadian     ( 0.0, 1.0,            0.0, "N-m/rad" );
const unitMomentPerAngle unitMeasure::KiloNewtonMeterPerRadian ( 0.0, 1.0e03,         0.0, "kN-m/rad");
const unitMomentPerAngle unitMeasure::KipInchPerRadian         ( 0.0, 112.984829028, 0.0,  "kip-in/rad" );
const unitMomentPerAngle unitMeasure::KipFeetPerRadian         ( 0.0, 1355.81794833,  0.0, "kip-ft/rad" );

const unitSqrtPressure unitMeasure::SqrtPa( 0.0, 1.0, 0.0, "Pa^0.5" );
const unitSqrtPressure unitMeasure::SqrtMPa( 0.0, 1000.0, 0.0, "MPa^0.5" );
const unitSqrtPressure unitMeasure::SqrtKSI( 0.0, 2625.78698679, 0.0, "KSI^0.5" );

const unitAcceleration unitMeasure::MeterPerSec2( 0.0, 1.0, 0.0, "m/s^2" );
const unitAcceleration unitMeasure::FeetPerSec2( 0.0, 0.3048, 0.0, "ft/s^2" );

const unitPerLength unitMeasure::PerMeter(0.0, 1.0, 0.0, "1/m");
const unitPerLength unitMeasure::PerMillimeter(0.0,1.0e3, 0.0, "1/mm");
const unitPerLength unitMeasure::PerInch(0.0, 39.3700787402, 0.0, "1/in");
const unitPerLength unitMeasure::PerFeet(0.0, 3.28083989501, 0.0, "1/ft");;

const unitForceLength2 unitMeasure::NewtonMeter2     ( 0.0, 1.0,         0.0, "N-m^2"    );
const unitForceLength2 unitMeasure::NewtonMillimeter2( 0.0, 1.0e09,      0.0, "N-mm^2"   );
const unitForceLength2 unitMeasure::KilonewtonMeter2 ( 0.0, 1.0e03,      0.0, "kN-m^2"   );
const unitForceLength2 unitMeasure::KipFoot2         ( 0.0, 413.253311,  0.0, "kip-ft^2" );
const unitForceLength2 unitMeasure::KipInch2         ( 0.0, 2.869815,    0.0, "kip-in^2" );
const unitForceLength2 unitMeasure::LbfInch2         ( 0.0, 2.869815e-03,0.0, "lbf-in^2" );
const unitForceLength2 unitMeasure::LbfFoot2         ( 0.0, 0.413253,    0.0, "lbf-ft^2" );

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _UNITTEST
#include <Units\Convert.h>

#define TEST(a,ua,b,ub) ( IsEqual( ::Convert((a),(ua), (ub)), (b) ) )

bool unitMeasure::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("unitMeasure");

   TRY_TESTME( TEST( 1.0, Inch,        25.4,      Millimeter ));
   TRY_TESTME( TEST( 1.0, Feet,        304.8,     Millimeter ));
   TRY_TESTME( TEST( 1.0, Inch2,       645.16,    Millimeter2 ));
   TRY_TESTME( TEST( 1.0, Pound,       4.4482216, Newton ));
   TRY_TESTME( TEST( 1.0, KSI,         6.8947573, MPa ));
   TRY_TESTME( TEST( 1.0, KgPerMeter,  0.6719689, LbfPerFeet ));
   TRY_TESTME( TEST( 1.0, LbfPerFeet,  1.4881639, KgPerMeter ));
   TRY_TESTME( TEST( 1.0, LbfPerFeet3, 16.018463, KgPerMeter3 ));
   TRY_TESTME( TEST( 0.0948, SqrtKSI,  0.2489246, SqrtMPa));

   TRY_TESTME( TEST( 1.0, NewtonMeter2,  2.419823, LbfFoot2));
   TRY_TESTME( TEST( 1.0, NewtonMeter2,  348.45452, LbfInch2));
   TRY_TESTME( TEST( 1.0, NewtonMeter2,  0.348455, KipInch2));
   TRY_TESTME( TEST( 1.0, NewtonMeter2,  2.419823e-03, KipFoot2));
   TRY_TESTME( TEST( 1.0, NewtonMeter2,  1.0e-03, KilonewtonMeter2));
   TRY_TESTME( TEST( 1.0, NewtonMeter2,  1.0e-09, NewtonMillimeter2));
   
   TESTME_EPILOG("unitMeasure");
}
#endif


