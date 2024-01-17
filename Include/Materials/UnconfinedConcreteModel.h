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
      /// Unconfined concrete stress-strain model
      ///
      /// See Collins, M.P., and Mitchell, D., Prestressed Concrete Structures, Prentice-Hall, Inc., A Division of Simon & Schuster, Englewood Cliffs, New Jersey, 07632, 1991, pp. 61-65.
      ///
      /// \f$ f_c(\epsilon_{cf}) = \left[ \frac{n\left(\frac{\epsilon_{cf}}{\epsilon'_c}\right)}{n-1+\left(\frac{\epsilon_{cf}}{\epsilon'_c} \right)^{nk}} \right] \f$
      ///
      /// where
      ///
      /// \f[ n = 0.8 + \frac{f'_c}{2500} \f]
      /// \f[ k = 0.67 + \frac{f'_c}{9000}, if \left(\frac{\epsilon_{cf}}{\epsilon'_c} \right) < 1.0, k = 1.0 \f]
      /// \f[ E_c = 40,000\sqrt{f'_c}+1,000,000 \f]
      /// \f[ \epsilon'_c = \frac{f'_c}{E_c} \frac{n}{n-1} \f]
      class MATCLASS UnconfinedConcreteModel : public StressStrainModel
      {
      public:
         UnconfinedConcreteModel() = default;
         UnconfinedConcreteModel(const std::_tstring& strName,Float64 fc=0);
         UnconfinedConcreteModel(const UnconfinedConcreteModel&) = default;
         virtual ~UnconfinedConcreteModel() = default;

         UnconfinedConcreteModel& operator=(const UnconfinedConcreteModel&) = delete;

         /// Sets the concrete strength
         void SetFc(Float64 fc);

         /// Returns the concrete strength
         Float64 GetFc() const;

         /// Creates a clone of the stress-strain model
         virtual std::unique_ptr<StressStrainModel> Clone() const override;

         /// Returns the strain associated with yielding of the material
         virtual Float64 GetYieldStrain() const override;

         /// Returns the modulus of elasticity
         virtual Float64 GetModulusOfElasticity() const override;

         /// Returns the stress at a given level of strain
         virtual std::pair<Float64, bool> ComputeStress(Float64 strain) const override;

         /// Returns the range of strain values applicable to the model
         virtual std::pair<Float64, Float64> GetStrainLimits() const override;

         /// Returns the strain that corresponds to the peak stress
         virtual Float64 GetStrainAtPeakStress() const override;

      private:
         void UpdateParameters();

         Float64 GetEc() const; // returns Ec in KSI

         Float64 m_Fc{0.0}; // in KSI units
         Float64 m_MinStrain{-0.003};
         Float64 m_MaxStrain{1.0};

         // cached values - updated when f'c changes
         Float64 m_n{ 0.0 };
         Float64 m_k{ 0.0 };
         Float64 m_Ec{ 0.0 };
         Float64 m_ec{ 0.0 };
      };
   };
};
