///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <list>

namespace WBFL
{
   namespace Units
   {
      /// Class that defines an application wide units system such as KMS (kilogram-meter-seconds)
      class UNITSCLASS System
      {
      public:
         System() = delete;
         System(const System&) = delete;
         System& operator=(const System&) = delete;

         /// Initializes the unit system
         static void SetSystemUnits(const Mass& mass, const Length& length, const Time& time, const Temperature& temp, const Angle& angle);

         /// Sets the system unit for mass
         static Mass SetMassUnit(const Mass& u);

         /// Returns the current system unit for mass
         static Mass GetMassUnit();

         /// Sets the system unit for length
         static Length SetLengthUnit(const Length& u);

         /// Returns the current system unit for length
         static Length GetLengthUnit();

         /// Sets the system unit for time
         static Time SetTimeUnit(const Time& u);

         /// Returns the current system unit for time
         static Time GetTimeUnit();

         /// Sets the system unit for temperature
         static Temperature SetTemperatureUnit(const Temperature& u);

         /// Returns the current system unit for temperature
         static Temperature GetTemperatureUnit();

         /// Sets the system unit for angle
         static Angle SetAngleUnit(const Angle& u);

         /// Returns the current system unit for angle
         static Angle GetAngleUnit();

         /// Sets the gravitational acceleration for this unit system
         static void SetGravitationalAcceleration(Float64 gravity);

         /// Returns the gravitational acceleration for this unit system
         static Float64 GetGravitationalAcceleration();

      private:
         static Mass        ms_Mass;
         static Length      ms_Length;
         static Time        ms_Time;
         static Temperature ms_Temperature;
         static Angle       ms_Angle;

         static Float64 ms_Gravity;
         static Acceleration ms_GravityUnit;
      };

   };
};
