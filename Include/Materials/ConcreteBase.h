///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#pragma once

#include <Materials/MaterialsExp.h>
#include <Materials/MaterialTypes.h>
#include <memory>

namespace WBFL
{
   namespace Materials
   {
      struct ConcreteBaseShrinkageDetails;
      struct ConcreteBaseCreepDetails;

      /// Abstract base class for time-dependent Portland Cement concrete material models.
      class MATCLASS ConcreteBase
      {
      public:
         ConcreteBase() = default;
         ConcreteBase(const std::_tstring& name);
         virtual ~ConcreteBase();

         ConcreteBase(const ConcreteBase&) = default;
         ConcreteBase& operator= (const ConcreteBase&) = default;

         /// Name of the material
         void SetName(const std::_tstring& name);
         std::_tstring GetName() const;

         void SetType(ConcreteType type);
         ConcreteType GetType() const;

         /// Returns a string name that represents the type of concrete. If bFull is true, the full name is returned, otherwise an abbreviated name
         static std::_tstring GetTypeName(ConcreteType type,bool bFull);
         static ConcreteType GetTypeFromTypeName(LPCTSTR strName);

         static std::_tstring GetCuringType(CuringType curingType);

         /// Indicates if the concrete defines an aggregate splitting strength
         bool HasAggSplittingStrength() const;
         void HasAggSplittingStrength(bool bHasFct);

         /// Aggregate splitting strength is a property of lightweight concrete
         void SetAggSplittingStrength(Float64 ft);
         Float64 GetAggSplittingStrength() const;

         /// Maximum aggregate size
         void SetMaxAggregateSize(Float64 size);
         Float64 GetMaxAggregateSize() const;

         // Fiber length for fiber reinforced materials
         void SetFiberLength(Float64 length);
         Float64 GetFiberLength() const;

         /// Density of the concrete used for computing secant modulus
         void SetStrengthDensity(Float64 d);
         Float64 GetStrengthDensity() const;

         /// Density of the concrete used for computing unit weight
         void SetWeightDensity(Float64 d);
         Float64 GetWeightDensity() const;

         /// Ambient relative humidity. A parameter typically used for time-dependent effects
         void SetRelativeHumidity(Float64 rh);
         Float64 GetRelativeHumidity() const;

         /// Volume to surface area (V/S) ratio
         void SetVSRatio(Float64 vs);
         Float64 GetVSRatio() const;

         /// The time when the concrete is cast. When getting properties
         /// such as Ec, this time is subtracted from the time provided to get
         /// the age of the concrete.
         void SetTimeAtCasting(Float64 time);
         Float64 GetTimeAtCasting() const;

         /// Age when the concrete first takes load (for creep)
         void SetAgeAtInitialLoading(Float64 age);
         Float64 GetAgeAtInitialLoading() const;

         /// Cure time
         void SetCureTime(Float64 t);
         Float64 GetCureTime() const;

         // Cure method
         void SetCuringType(CuringType method);
         CuringType GetCuringType() const;

         /// Returns the age of the concrete at time t. Return value is < 0
         /// if t is before casting
         Float64 GetAge(Float64 t) const;

         /// Returns the compressive strength of the concrete at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetFc(Float64 t) const = 0;

         /// Returns the secant modulus of the concrete at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetEc(Float64 t) const = 0;

         /// Returns the modulus of rupture for shear calculations at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetShearFr(Float64 t) const = 0;

         /// Returns the modulus of rupture for flexure calculations at time t. If
         /// t occurs before the time at casting, zero is returned.
         virtual Float64 GetFlexureFr(Float64 t) const = 0;

         /// Returns the total free shrinkage that has occured from time at casting
         /// to the time specified
         virtual Float64 GetFreeShrinkageStrain(Float64 t) const = 0;
         virtual std::unique_ptr<ConcreteBaseShrinkageDetails> GetFreeShrinkageStrainDetails(Float64 t) const = 0;

         /// Returns the creep coefficient at time t for a loading applied at time tla
         virtual Float64 GetCreepCoefficient(Float64 t,Float64 tla) const = 0;
         virtual std::unique_ptr<ConcreteBaseCreepDetails> GetCreepCoefficientDetails(Float64 t,Float64 tla) const = 0;

         /// Creates a clone of this object
         virtual std::unique_ptr<ConcreteBase> CreateClone() const = 0;

      protected:
         /// Called when the concrete is changed. The default implemention does nothing.
         virtual void OnChanged();

         /// Subclasses can call this to initialize the base class details for shrinkage. The parameters that get 
         /// initialized are CuringType and shrinkage_during
         void InitializeShrinkageDetails(Float64 t,ConcreteBaseShrinkageDetails* pDetails) const;

         /// Subclasses must call this to initialize the base class details for creep. The parameters that get
         /// initialized are age and age_at_loading
         void InitializeCreepDetails(Float64 t,Float64 tla,ConcreteBaseCreepDetails* pDetails) const;

      protected:
         ConcreteType   m_Type;
         std::_tstring m_Name{_T("Unknown")};
         bool        m_bHasFct; // has aggregate splitting strength
         Float64     m_Fct;     // aggregate splitting strength
         Float64     m_MaxAggregateSize;
         Float64     m_FiberLength;
         Float64     m_StrengthDensity;
         Float64     m_WeightDensity;
         Float64     m_RelativeHumidity;
         Float64     m_VS; // V/S ratio
         Float64     m_TimeAtCasting; // time at casting... days
         Float64     m_AgeAtInitialLoading; // days
         Float64     m_CureTime; // duration of time that the concrete is cured
         CuringType  m_CuringType;
      };

      /// Base class for shrinkage strain calculation details. Subclasses extend this to provide additional parameters.
      struct MATCLASS ConcreteBaseShrinkageDetails
      {
         ConcreteBaseShrinkageDetails() = default;
         virtual ~ConcreteBaseShrinkageDetails() {};
         Float64 shrinkage_duration{ 0 }; ///< duration of time overwhich shrinkage occurs
         CuringType curingType{ CuringType::Moist }; ///< Concrete curing method
         Float64 esh{ 0 }; ///< Shrinkage strain
      };

      /// Base class for creep calculation details. Subclasses extend this to provide additional parameters.
      struct MATCLASS ConcreteBaseCreepDetails
      {
         ConcreteBaseCreepDetails() = default;
         virtual ~ConcreteBaseCreepDetails() {};
         Float64 age{ 0 }; ///< Concrete age when creep coefficient is computed
         Float64 age_at_loading{ 0 }; ///< Concrete age at time of loading
         Float64 fci{ 0 }; ///< Concrete strength at time of loading 
         Float64 Ct{ 0 }; ///< Creep coefficient
      };

   };
};
