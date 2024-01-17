///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MaterialsExp.h>
#include <Materials/StressStrainModel.h>

namespace WBFL
{
   namespace Materials
   {
      /// Material model for Ultra High Performance Concrete (UHPC)
      ///
      /// Mechanical Behavior and Design Properties of Ultra-High Performance Concrete
      /// El-Helou, Rafic, Haber, Z., Graybeal, B.
      /// (Unpublished as of 2020)
      /// /todo - Update reference after publication
      class MATCLASS UHPCModel : public StressStrainModel
      {
      public:
         UHPCModel() = default;
         UHPCModel(const std::_tstring& strName);
         UHPCModel(const UHPCModel&) = default;
         virtual ~UHPCModel() = default;

         UHPCModel& operator=(const UHPCModel&) = delete;

         /// Sets the concrete strength
         void SetFc(Float64 fc);

         /// Returns the concrete strength
         Float64 GetFc() const;

         /// Set the compressive strain limit
         void SetCompressiveStrainLimit(Float64 ecu);
         Float64 GetCompressiveStrainLimit() const;

         /// Set the modulus of elasticity correction factor
         /// \todo When models from the Generalized_Concrete_Models branch are implemented, replace this with a pointer to the modulus of elasticity model
         void SetK1(Float64 k1);
         Float64 GetK1() const;

         /// Set reduction factor to account for the non-linearity of the compressive stress-strain response
         void SetAlpha(Float64 alpha);
         Float64 GetAlpha() const;

         /// Set the cracking stress
         void SetFtcr(Float64 ftcr);
         Float64 GetFtcr() const;

         /// Set crack localization stress
         void SetFtloc(Float64 ftloc);
         Float64 GetFtloc() const;

         /// Set crack localization strain
         void Set_etloc(Float64 etloc);
         Float64 Get_etloc() const;

         /// Set reduction factor to account for the variability in tensile stress parameters.
         void SetGamma(Float64 gamma);
         Float64 GetGamma() const;

         /// Creates a clone of the stress-strain model
         virtual std::unique_ptr<StressStrainModel> Clone() const override;

         /// Returns the strain associated with yielding of the material
         virtual Float64 GetYieldStrain() const override;

         /// Returns the modulus of elasticity
         virtual Float64 GetModulusOfElasticity() const override;

         /// Returns the stress at a given level of strain
         virtual std::pair<Float64, bool> ComputeStress(Float64 strain) const override;

         /// Returns the range of strain values applicable to the model
         virtual void GetStrainLimits(Float64* pMinStrain, Float64* pMaxStrain) const override;

         /// Returns the strain that corresponds to the peak stress
         virtual Float64 GetStrainAtPeakStress() const override;

      private:
         Float64 m_fc{ 18.0 }; // in KSI units
         Float64 m_ecu{ -0.0035};
         Float64 m_K1{ 1.0 };
         Float64 m_alpha{ 0.85 };
         Float64 m_ftcr{ 0.75 }; // KSI
         Float64 m_ftloc{ 1.0 }; // KSI
         Float64 m_etloc{ 0.0025 };
         Float64 m_gamma_u{ 1.0 };

         Float64 GetEc() const; // returns Ec in KSI
      };
   };
};
