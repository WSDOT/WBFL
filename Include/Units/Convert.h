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
#include <Units\System.h>

namespace WBFL
{
   namespace Units
   {
      /// Converts a value between units of measure
      template <class T>
      inline Float64 Convert(Float64 value,const T& from, const T& to)
      {
         return to.ConvertTo(from.ConvertFrom(value));
      }


      /// Converts a value. This method is not intended to be called by external users but must be exported to support the System Unit conversion functions.
      void UNITSFUNC convert_from(Float64* pValue, Float64 cf, Float64 dim);
      /// Converts a value. This method is not intended to be called by external users but must be exported to support the System Unit conversion functions.
      void UNITSFUNC convert_from(Float64* pValue, Float64 preTerm, Float64 cf, Float64 postTerm, Float64 dim);
      /// Converts a value. This method is not intended to be called by external users but must be exported to support the System Unit conversion functions.
      void UNITSFUNC convert_to(Float64* pValue, Float64 cf, Float64 dim);
      /// Converts a value. This method is not intended to be called by external users but must be exported to support the System Unit conversion functions.
      void UNITSFUNC convert_to(Float64* pValue, Float64 preTerm, Float64 cf, Float64 postTerm, Float64 dim);

      /// Converts a value from system units to a specified unit of measure
      template <class T>
      Float64 ConvertFromSysUnits(Float64 value, const T& to)
      {
         if (value == Float64_Max || value == Float64_Inf)
         {
            return value;
         }

         const Mass& um = System::GetMassUnit();
         convert_from(&value,
            um.GetConvFactor(),
            T::MassDim());

         const Length& ul = System::GetLengthUnit();
         convert_from(&value,
            ul.GetConvFactor(),
            T::LengthDim());

         const Time& ut = System::GetTimeUnit();
         convert_from(&value,
            ut.GetConvFactor(),
            T::TimeDim());

         const Temperature& uk = System::GetTemperatureUnit();
         convert_from(&value,
            uk.GetPreTerm(),
            uk.GetConvFactor(),
            uk.GetPostTerm(),
            T::TemperatureDim());

         const Angle& ua = System::GetAngleUnit();
         convert_from(&value,
            ua.GetConvFactor(),
            T::AngleDim());

         return to.ConvertTo(value);
      }

      /// Converts a value from a specified unit of measure to system units
      template <class T>
      Float64 ConvertToSysUnits(Float64 value, const T& from)
      {
         if (value == Float64_Max || value == Float64_Inf)
         {
            return value;
         }

         const Mass& um = System::GetMassUnit();
         convert_to(&value,
            um.GetConvFactor(),
            T::MassDim());

         const Length& ul = System::GetLengthUnit();
         convert_to(&value,
            ul.GetConvFactor(),
            T::LengthDim());

         const Time& ut = System::GetTimeUnit();
         convert_to(&value,
            ut.GetConvFactor(),
            T::TimeDim());

         const Temperature& uk = System::GetTemperatureUnit();
         convert_to(&value,
            uk.GetPreTerm(),
            uk.GetConvFactor(),
            uk.GetPostTerm(),
            T::TemperatureDim());

         const Angle& ua = System::GetAngleUnit();
         convert_to(&value,
            ua.GetConvFactor(),
            T::AngleDim());

         return from.ConvertFrom(value);
      }
   };
};
