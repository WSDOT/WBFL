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

#include <Units\UnitsLib.h>
#include <Units\System.h>
#include <Units\Convert.h>
#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Units;

Mass         System::ms_Mass        = Measure::Kilogram;
Length       System::ms_Length      = Measure::Meter;
Time         System::ms_Time        = Measure::Second;
Temperature  System::ms_Temperature = Measure::Celsius;
Angle        System::ms_Angle       = Measure::Radian;
Float64      System::ms_Gravity     = 9.80665; //; // m/s^2, not 9.81 as we're taught in school
Acceleration System::ms_GravityUnit = Measure::MeterPerSec2;

void System::SetSystemUnits(const Mass& mass, const Length& length, const Time& time, const Temperature& temp, const Angle& angle)
{
   SetMassUnit(mass);
   SetLengthUnit(length);
   SetTimeUnit(time);
   SetTemperatureUnit(temp);
   SetAngleUnit(angle);
}

Mass System::SetMassUnit(const Mass& u)
{
   Mass temp = ms_Mass;
   ms_Mass = u;
   return temp;
}

Mass System::GetMassUnit()
{
   return  ms_Mass;
}

Length System::SetLengthUnit(const Length& u)
{
   Length temp = ms_Length;
   ms_Length = u;
   return temp;
}

Length System::GetLengthUnit()
{
   return ms_Length;
}

Time System::SetTimeUnit(const Time& u)
{
   Time temp = ms_Time;
   ms_Time = u;
   return temp;
}

Time System::GetTimeUnit() 
{
   return ms_Time;
}

Temperature System::SetTemperatureUnit(const Temperature& u)
{
   Temperature temp = ms_Temperature;
   ms_Temperature = u;
   return temp;
}

Temperature System::GetTemperatureUnit() 
{
   return ms_Temperature;
}

Angle System::SetAngleUnit(const Angle& u)
{
   Angle temp = ms_Angle;
   ms_Angle = u;
   return temp;
}

Angle System::GetAngleUnit() 
{
   return ms_Angle;
}

void System::SetGravitationalAcceleration(Float64 gravity)
{
   // Gravity is always stored in m/s^2.
   // the inbound value is in system units. Convert it now.
   gravity = WBFL::Units::ConvertFromSysUnits( gravity, ms_GravityUnit );
   if ( !IsEqual( ms_Gravity, gravity ) )
   {
      ms_Gravity = gravity;
   }
}

Float64 System::GetGravitationalAcceleration()
{
   // Gravity is always stored in m/s^2.
   // Convert the outbound value to system units.
   return WBFL::Units::ConvertToSysUnits(ms_Gravity,ms_GravityUnit);
}
