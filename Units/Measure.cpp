///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#include <Units\UnitsLib.h>
#include <Units\Measure.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Units;

const Mass Measure::Kilogram   ( 1.000,         _T("kg")   );
const Mass Measure::Gram       ( 0.001,         _T("g")    ); 
const Mass Measure::MetricTon  ( 1.0e03,        _T("MT") );
const Mass Measure::Slug       ( 14.5939029372, _T("slug") );
const Mass Measure::PoundMass  ( 0.45359237,    _T("lbm")  );
const Mass Measure::KSlug      ( 14593.9029372, _T("kslug") );
const Mass Measure::_12Slug    ( 175.126835246, _T("12slug") );
const Mass Measure::_12KSlug   ( 175126.835246, _T("12kslug") );

const MassPerLength Measure::KgPerMeter ( 1.000,           _T("kg/m") );
const MassPerLength Measure::LbmPerFeet ( 0.671968975139,  _T("lbm/ft") );
const MassPerLength Measure::SlugPerFeet( 0.0208854342115, _T("slug/ft") );
const MassPerLength Measure::LbfPerFeet ( 1.48816394357,   _T("lbf/ft") );

const Length Measure::Meter       ( 1.0,      _T("m")    );
const Length Measure::Millimeter  ( 1.0e-03,  _T("mm")   );
const Length Measure::Centimeter  ( 1.0e-02,  _T("cm")   );
const Length Measure::Kilometer   ( 1.0e03,   _T("km")   );
const Length Measure::Feet        ( 0.3048,   _T("ft")   );
const Length Measure::USSurveyFoot( 1200./3937., _T("ft")   );
const Length Measure::Inch        ( 0.0254,   _T("in")   );
const Length Measure::Mile        ( 1609.344, _T("mile") );
const Length Measure::Yard        ( 0.9144,   _T("yd" )  );
const Length Measure::USSurveyYard( 3600./3937., _T("yd")  );

const AreaPerLength Measure::Meter2PerMeter           ( 1.0,      _T("m^2/m")  );
const AreaPerLength Measure::Millimeter2PerMillimeter ( 1.0e-03,  _T("mm^2/mm"));
const AreaPerLength Measure::Millimeter2PerMeter      ( 1.0e-06,  _T("mm^2/m"));
const AreaPerLength Measure::Feet2PerFoot             ( 0.3048,   _T("ft^2/ft"));
const AreaPerLength Measure::Inch2PerInch             ( 0.0254,   _T("in^2/in"));
const AreaPerLength Measure::Inch2PerFoot             ( 0.0021166666666667, _T("in^2/ft"));

const Length2 Measure::Meter2       ( 1.0,           _T("m^2")    );
const Length2 Measure::Millimeter2  ( 1.0e-06,       _T("mm^2")   );
const Length2 Measure::Centimeter2  ( 1.0e-04,       _T("cm^2")   );
const Length2 Measure::Kilometer2   ( 1.0e06,        _T("km^2")   );
const Length2 Measure::Feet2        ( 0.09290304,    _T("ft^2")   );
const Length2 Measure::Inch2        ( 0.00064516,    _T("in^2")   );
const Length2 Measure::Mile2        ( 2589988.11034, _T("mile^2") );
const Length2 Measure::Yard2        ( 0.83612736,    _T("yd^2")   );

const Length3 Measure::Meter3       ( 1.0,            _T("m^3")    );
const Length3 Measure::Millimeter3  ( 1.0e-09,        _T("mm^3")   );
const Length3 Measure::Centimeter3  ( 1.0e-06,        _T("cm^3")   );
const Length3 Measure::Kilometer3   ( 1.0e09,         _T("km^3")   );
const Length3 Measure::Feet3        ( 0.028316846592, _T("ft^3")   );
const Length3 Measure::Inch3        ( 0.000016387064, _T("in^3")   );
const Length3 Measure::Mile3        ( 4168181825.44,  _T("mile^3") );
const Length3 Measure::Yard3        ( 0.764554857984, _T("yd^3")   );

const Length4 Measure::Meter4       ( 1.0,               _T("m^4")    );
const Length4 Measure::Millimeter4  ( 1.0e-12,           _T("mm^4")   );
const Length4 Measure::Centimeter4  ( 1.0e-08,           _T("cm^4")   );
const Length4 Measure::Kilometer4   ( 1.0e12,            _T("km^4")   );
const Length4 Measure::Feet4        ( 8.63097484124e-03, _T("ft^4")   );
const Length4 Measure::Inch4        ( 4.162314256e-07,   _T("in^4")   );
const Length4 Measure::Mile4        ( 6.70803841168e12,  _T("mile^4") );
const Length4 Measure::Yard4        ( 0.699108962141,    _T("yd^4")   );

const Time Measure::Second (     1.0, _T("sec") );
const Time Measure::Minute (    60.0, _T("min") );
const Time Measure::Hour   (  3600.0, _T("hr")  );
const Time Measure::Day    ( 86400.0, _T("day") );

const Temperature Measure::Celsius    ( 0.0, 1.0,  0.0, _T("C") );
const Temperature Measure::Fahrenheit (-32.0, 5./9., 0.0, _T("F") );

const Angle Measure::Radian ( 1.0,               _T("rad") );
const Angle Measure::Degree ( 1.74532925199e-02, _T("deg") );

const Pressure Measure::Pa  ( 1.0,                _T("Pa")  );
const Pressure Measure::kPa ( 1.0e03,             _T("kPa") );
const Pressure Measure::MPa ( 1.0e06,             _T("MPa") );
const Pressure Measure::PSI ( 6.89475729317e03,   _T("PSI") );
const Pressure Measure::PSF ( 4.78802589803e01,   _T("PSF") );
const Pressure Measure::KSI ( 6.89475729317e06,   _T("KSI") );
const Pressure Measure::KSF ( 4.78802589803e04,   _T("KSF") );

const UnitWeight Measure::NewtonPerMeter3 ( 1.0,                _T("N/m^3") );
const UnitWeight Measure::PCI             ( 271447.1375263134,  _T("PCI")   );
const UnitWeight Measure::PCF             ( 157.08746384624618, _T("PCF")   );

const Density Measure::KgPerMeter3  ( 1.0,                   _T("kg/m^3")    );
const Density Measure::LbmPerFeet3  ( 16.01846337396013800,  _T("lbm/ft^3")  );
const Density Measure::SlugPerFeet3 ( 515.37881839319730000, _T("slug/ft^3") );
const Density Measure::LbfPerFeet3  ( 16.01846337396013800,  _T("lbf/ft^3")  );
const Density Measure::KipPerFeet3  ( 16018.46337396013800,  _T("kip/ft^3")  );

const Force Measure::Newton     ( 1.0,             _T("N")          );
const Force Measure::Kilonewton ( 1.0e03,          _T("kN")          );
const Force Measure::Pound      ( 4.4482216152605, _T("lbf")        );
const Force Measure::Kip        ( 4448.2216152605, _T("kip")        );
const Force Measure::Ton        ( 8896.44323052,   _T("ton")        );

const ForcePerLength Measure::NewtonPerMeter      ( 1.0,           _T("N/m")    );
const ForcePerLength Measure::KilonewtonPerMeter  ( 1.0e03,        _T("kN/m")   );
const ForcePerLength Measure::NewtonPerMillimeter ( 1.0e03,        _T("N/mm")   );
const ForcePerLength Measure::LbfPerFoot          ( 14.593902937206362, _T("lbf/ft") );
const ForcePerLength Measure::LbfPerInch          ( 175.126835246, _T("lbf/in") );
const ForcePerLength Measure::KipPerFoot          ( 14593.902937206362, _T("kip/ft") );
const ForcePerLength Measure::KipPerInch          ( 175126.835246, _T("kip/in") );

const Moment Measure::NewtonMeter     ( 1.0,            _T("N-m")    );
const Moment Measure::KilonewtonMeter ( 1.0e03,         _T("kN-m")   );
const Moment Measure::NewtonMillimeter( 1.0e-03,        _T("N-mm")   );
const Moment Measure::InchLbf         ( 0.112984829028, _T("in-lbf") );
const Moment Measure::KipFeet         ( 1355.8179483314004,  _T("kip-ft") );
const Moment Measure::KipInch         ( 112.984829028, _T("kip-in") );

const MomentPerAngle Measure::NewtonMeterPerRadian     ( 1.0,           _T("N-m/rad") );
const MomentPerAngle Measure::KiloNewtonMeterPerRadian ( 1.0e03,        _T("kN-m/rad"));
const MomentPerAngle Measure::KipInchPerRadian         ( 112.984829028, _T("kip-in/rad") );
const MomentPerAngle Measure::KipFeetPerRadian         ( 1355.81794833, _T("kip-ft/rad") );

const SqrtPressure Measure::SqrtPa( 1.0, _T("Pa^0.5") );
const SqrtPressure Measure::SqrtMPa( 1000.0, _T("MPa^0.5") );
const SqrtPressure Measure::SqrtKSI( 2625.78698679, _T("KSI^0.5") );

const Acceleration Measure::MeterPerSec2( 1.0, _T("m/s^2") );
const Acceleration Measure::FeetPerSec2(  0.3048, _T("ft/s^2") );

const PerLength Measure::PerMeter(1.0, _T("m^-1"));
const PerLength Measure::PerMillimeter(1.0e3, _T("mm^-1"));
const PerLength Measure::PerInch(39.3700787402, _T("in^-1"));
const PerLength Measure::PerFeet(3.28083989501, _T("ft^-1"));;

const ForceLength2 Measure::NewtonMeter2     ( 1.0,         _T("N-m^2")    );
const ForceLength2 Measure::NewtonMillimeter2( 1.0e09,      _T("N-mm^2")   );
const ForceLength2 Measure::KilonewtonMeter2 ( 1.0e03,      _T("kN-m^2")   );
const ForceLength2 Measure::KipFoot2         ( 413.253311,  _T("kip-ft^2") );
const ForceLength2 Measure::KipInch2         ( 2.869815,    _T("kip-in^2") );
const ForceLength2 Measure::LbfInch2         ( 2.869815e-03,_T("lbf-in^2") );
const ForceLength2 Measure::LbfFoot2         ( 0.413253,    _T("lbf-ft^2") );

const Velocity Measure::KilometerPerHour(0.2777777777777777, _T("Km/h"));
const Velocity Measure::MeterPerSecond(  1.0,                _T("m/s"));
const Velocity Measure::MilePerHour(     0.44704,            _T("MPH"));
const Velocity Measure::FeetPerSecond(   0.3048,             _T("ft/s"));
