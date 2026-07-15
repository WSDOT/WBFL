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
#include <Units\System.h>
#include <Units\DynamicPhysical.h>
#include <Units\XUnit.h>

namespace WBFL
{
   namespace Units
   {
      /// Returns true if a and b have the same mass, length, time, temperature, and angle dimensionality.
      /// Works for any pair of types exposing MassDim()/LengthDim()/TimeDim()/TemperatureDim()/AngleDim()
      /// accessors, so it can compare two compile-time-dimensioned units (PhysicalT/PhysicalExT aliases),
      /// two DynamicPhysical units, or one of each.
      template <class T1, class T2>
      inline bool IsSameDimension(const T1& a, const T2& b)
      {
         return a.MassDim() == b.MassDim()
             && a.LengthDim() == b.LengthDim()
             && a.TimeDim() == b.TimeDim()
             && a.TemperatureDim() == b.TemperatureDim()
             && a.AngleDim() == b.AngleDim();
      }

      /// Converts a value between units of measure
      template <class T>
      inline Float64 Convert(Float64 value,const T& from, const T& to)
      {
         return to.ConvertTo(from.ConvertFrom(value));
      }

      /// Converts a value between two dynamically-dimensioned units of measure. Unlike the templated
      /// Convert() overload above, from and to are not guaranteed by the compiler to have the same
      /// dimensionality (DynamicPhysical's dimensionality is a run-time value), so this overload checks
      /// dimensional compatibility itself and throws WBFL::Units::XUnit, with reason
      /// XUnit::Reason::DimensionMismatch, if from and to do not have the same dimensionality (see
      /// DynamicPhysical::IsSameDimension()).
      Float64 UNITSFUNC Convert(Float64 value, const DynamicPhysical& from, const DynamicPhysical& to);

      /// Converts a value from a compile-time-dimensioned unit of measure to a dynamically-dimensioned
      /// unit of measure. Since DynamicPhysical's dimensionality isn't known until run time, this overload
      /// checks dimensional compatibility itself and throws WBFL::Units::XUnit, with reason
      /// XUnit::Reason::DimensionMismatch, if from and to do not have the same dimensionality.
      template <class T>
      inline Float64 Convert(Float64 value, const T& from, const DynamicPhysical& to)
      {
         if (!IsSameDimension(from, to))
         {
            THROW(XUnit, Reason::DimensionMismatch);
         }

         return to.ConvertTo(from.ConvertFrom(value));
      }

      /// Converts a value from a dynamically-dimensioned unit of measure to a compile-time-dimensioned
      /// unit of measure. Since DynamicPhysical's dimensionality isn't known until run time, this overload
      /// checks dimensional compatibility itself and throws WBFL::Units::XUnit, with reason
      /// XUnit::Reason::DimensionMismatch, if from and to do not have the same dimensionality.
      template <class T>
      inline Float64 Convert(Float64 value, const DynamicPhysical& from, const T& to)
      {
         if (!IsSameDimension(from, to))
         {
            THROW(XUnit, Reason::DimensionMismatch);
         }

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
            to.MassDim());

         const Length& ul = System::GetLengthUnit();
         convert_from(&value,
            ul.GetConvFactor(),
            to.LengthDim());

         const Time& ut = System::GetTimeUnit();
         convert_from(&value,
            ut.GetConvFactor(),
            to.TimeDim());

         const Temperature& uk = System::GetTemperatureUnit();
         convert_from(&value,
            uk.GetPreTerm(),
            uk.GetConvFactor(),
            uk.GetPostTerm(),
            to.TemperatureDim());

         const Angle& ua = System::GetAngleUnit();
         convert_from(&value,
            ua.GetConvFactor(),
            to.AngleDim());

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
            from.MassDim());

         const Length& ul = System::GetLengthUnit();
         convert_to(&value,
            ul.GetConvFactor(),
            from.LengthDim());

         const Time& ut = System::GetTimeUnit();
         convert_to(&value,
            ut.GetConvFactor(),
            from.TimeDim());

         const Temperature& uk = System::GetTemperatureUnit();
         convert_to(&value,
            uk.GetPreTerm(),
            uk.GetConvFactor(),
            uk.GetPostTerm(),
            from.TemperatureDim());

         const Angle& ua = System::GetAngleUnit();
         convert_to(&value,
            ua.GetConvFactor(),
            from.AngleDim());

         return from.ConvertFrom(value);
      }
   };
};
