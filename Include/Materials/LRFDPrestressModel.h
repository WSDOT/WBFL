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
#include <Materials/StressStrainModel.h>
#include <Materials/MaterialTypes.h>
#include <Units/Convert.h>
#include <Units/Measure.h>

namespace WBFL
{
   namespace Materials
   {
      /// Material model for prestress reinforcement based on AASHTO LRFD 5.6.3.1.1
      ///
      /// \f$ f_{ps} = f_{pu}\left(1-k\left(\frac{c}{d}\right)\right) \f$ where \f$k\f$ = 0.28 for low relaxation strand and 0.38 for stress relieved strand
      ///
      /// \f$ d = \frac{0.003}{0.003+\epsilon} \f$
      class MATCLASS LRFDPrestressModel : public StressStrainModel
      {
      public:
         LRFDPrestressModel() = default;
         LRFDPrestressModel(const std::_tstring& strName);
         LRFDPrestressModel(const LRFDPrestressModel&) = default;
         virtual ~LRFDPrestressModel() = default;

         LRFDPrestressModel& operator=(const LRFDPrestressModel&) = delete;

         /// Set ultimate strength
         void SetFpu(Float64 fpu);
         Float64 GetFpu() const;

         /// Set modulus of elasticity
         void SetEps(Float64 Eps);
         Float64 GetEps() const;

         /// Set production type
         void SetStrandType(StrandType type);
         StrandType GetStrandType() const;

         /// Set the strain limits
         void SetStrainLimits(Float64 minStrain, Float64 maxStrain);

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
         StrandType m_Type{ StrandType::LowRelaxation };
         Float64 m_MinStrain{ -10 }; // assumes material doesn't fracture in compression
         Float64 m_MaxStrain{ 0.035 }; // per ASTM A416 material specification
         Float64 m_fpu{ WBFL::Units::ConvertToSysUnits(270.0, WBFL::Units::Measure::KSI) };
         Float64 m_Eps{ WBFL::Units::ConvertToSysUnits(28500.0, WBFL::Units::Measure::KSI) }; 
      };
   };
};
