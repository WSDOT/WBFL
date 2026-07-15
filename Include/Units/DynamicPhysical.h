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
#include <System\LogContext.h>
#include <string>

namespace WBFL
{
   namespace Units
   {
      /// A physical unit of measure whose dimensionality is determined at run time.
      ///
      /// DynamicPhysical is the run-time counterpart of PhysicalT and PhysicalExT. PhysicalT fixes its
      /// dimensionality (the mass, length, time, temperature, and angle exponents that define a physical
      /// quantity such as length, force, or pressure) at compile time using template parameters. This makes
      /// PhysicalT fast and type-safe, but it means a distinct C++ type must exist for every dimensionality
      /// an application will ever use.
      ///
      /// Some applications need to define unit types whose dimensionality isn't known until run time, for
      /// example a unit type read from a configuration file or defined interactively by an end user.
      /// DynamicPhysical supports this case by storing its dimensionality as ordinary data members instead
      /// of template parameters, while using the same conversion equation, value*ConvFactor, or the full
      /// (value+PreTerm)*ConvFactor+PostTerm equation, that PhysicalT and PhysicalExT use.
      ///
      /// Because dimensionality is a run-time value with DynamicPhysical, two DynamicPhysical objects can be
      /// passed to a conversion function even if their dimensionality doesn't actually match. Call
      /// IsSameDimension() to test compatibility directly, or use the DynamicPhysical overload of Convert(),
      /// which performs this check and throws XUnit with reason XUnit::Reason::DimensionMismatch if the two
      /// units of measure aren't compatible.
      ///
      /// Prefer PhysicalT, PhysicalExT, and the Measure catalog whenever the dimensionality of a unit of
      /// measure is known when the application is written. Reach for DynamicPhysical only when it isn't; see
      /// DynamicUnitTypeManager for a way to organize a named catalog of DynamicPhysical units of measure.
      class UNITSCLASS DynamicPhysical
      {
      public:
         /// Constructs a unit of measure with dimensionality (m,l,t,k,a) and the conversion equation
         /// value*cf (equivalent to a PreTerm and PostTerm of 0).
         DynamicPhysical(Float64 m, Float64 l, Float64 t, Float64 k, Float64 a, Float64 cf, const std::_tstring& tag);

         /// Constructs a unit of measure with dimensionality (m,l,t,k,a) and the full conversion equation
         /// (value+preTerm)*cf+postTerm.
         DynamicPhysical(Float64 m, Float64 l, Float64 t, Float64 k, Float64 a, Float64 preTerm, Float64 cf, Float64 postTerm, const std::_tstring& tag);

         DynamicPhysical(const DynamicPhysical&) = default;
         DynamicPhysical& operator=(const DynamicPhysical&) = default;

         /// Returns true if other has the same dimensionality, conversion equation, and unit tag as this
         /// unit of measure.
         bool operator==(const DynamicPhysical& other) const;

         /// Converts value, expressed in this unit of measure, to the fundamental unit implied by its
         /// conversion equation.
         Float64 ConvertFrom(Float64 value) const;

         /// Converts value, expressed in the fundamental unit implied by this unit's conversion equation,
         /// to this unit of measure.
         Float64 ConvertTo(Float64 value) const;

         /// Returns true if other has the same mass, length, time, temperature, and angle dimensionality as
         /// this unit of measure. Converting a value between two DynamicPhysical units of measure only
         /// makes physical sense when this returns true.
         bool IsSameDimension(const DynamicPhysical& other) const;

         /// Returns the pre-addition term of the conversion equation.
         Float64 GetPreTerm() const;

         /// Returns the conversion factor of the conversion equation.
         Float64 GetConvFactor() const;

         /// Returns the post-addition term of the conversion equation.
         Float64 GetPostTerm() const;

         /// Returns the unit tag.
         const std::_tstring& UnitTag() const;

         /// Returns the mass dimensionality.
         Float64 MassDim() const;

         /// Returns the length dimensionality.
         Float64 LengthDim() const;

         /// Returns the time dimensionality.
         Float64 TimeDim() const;

         /// Returns the temperature dimensionality.
         Float64 TemperatureDim() const;

         /// Returns the angle dimensionality.
         Float64 AngleDim() const;

      #if defined _DEBUG
         bool AssertValid() const;
         void Dump(WBFL::Debug::LogContext& os) const;

         /// RAII helper that suppresses the constructor's "duplicates a compile-time dimension" diagnostic
         /// for the lifetime of the scope (nests correctly if more than one is alive at once). Intended for
         /// callers, such as a bulk-seeding routine that is known to be intentionally mirroring compile-time
         /// dimensions on purpose (e.g. populating a catalog meant to hold both built-in and run-time-defined
         /// unit types uniformly), not for general use - the diagnostic exists to catch accidental
         /// duplication, and constructing this scope around ordinary code defeats that purpose.
         ///
         /// \todo This exists only to accommodate WBFLUnitServer's facade over WBFLUnits (CUnitTypes::
         /// InitDefaultUnits() seeds a DynamicUnitTypeManager with a DynamicPhysical for every built-in unit,
         /// all of which necessarily duplicate a compile-time dimension by design). Remove this class, and
         /// g_SuppressDuplicateDimensionWarningCount in DynamicPhysical.cpp, once WBFLUnitServer is obsoleted
         /// and removed from WBFL.
         class UNITSCLASS SuppressDuplicateDimensionWarningScope
         {
         public:
            SuppressDuplicateDimensionWarningScope();
            ~SuppressDuplicateDimensionWarningScope();
         };
      #endif // _DEBUG

      private:
         Float64 m_Mass;
         Float64 m_Length;
         Float64 m_Time;
         Float64 m_Temperature;
         Float64 m_Angle;

         Float64 m_PreTerm;
         Float64 m_ConvFactor;
         Float64 m_PostTerm;
         std::_tstring m_UnitTag;
      };
   };
};
