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

namespace WBFL
{
   namespace Materials
   {
      /// Material model for pretensioning strands based on the modified Ramberg-Osgood model
      ///
      /// \f$ f_{ps} = E_p \epsilon_p \left[ A + \frac{1-A}{\left[1+(B \epsilon_p)^C \right]^\frac{1}{C}} \right] \f$
      ///
      /// \todo - Add reference to publication
      class MATCLASS RambergOsgoodModel : public StressStrainModel
      {
      public:
         RambergOsgoodModel() = default;
         RambergOsgoodModel(const std::_tstring& strName);
         RambergOsgoodModel(const RambergOsgoodModel&) = default;
         virtual ~RambergOsgoodModel() = default;

         RambergOsgoodModel& operator=(const RambergOsgoodModel&) = delete;

         /// Model parameters
         void SetModelParameters(Float64 A, Float64 B, Float64 C, Float64 Eps, Float64 fpu, Float64 minStrain, Float64 maxStrain);
         void GetModelParameters(Float64* pA, Float64* pB, Float64* pC, Float64* pEps, Float64* pfpu, Float64* pminStrain, Float64* pmaxStrain) const;

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

      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         Float64 m_A{ 0.0 };
         Float64 m_B{ 0.0 };
         Float64 m_C{ 0.0 };
         Float64 m_Eps{ 0.0 };
         Float64 m_fpu{ 0.0 };
         Float64 m_MinStrain{ 0.0 };
         Float64 m_MaxStrain{ 0.0 };
      };
   };
};
