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

#include <Lrfd\LrfdExp.h>
#include <Materials/ConcreteBase.h>

namespace WBFL
{
   namespace LRFD
   {
      class LRFDCLASS LRFDConcreteBase : public WBFL::Materials::ConcreteBase
      {
      public:
         LRFDConcreteBase(LPCTSTR name = _T("Unknown"));
         LRFDConcreteBase(const LRFDConcreteBase&) = default;
         virtual ~LRFDConcreteBase() override = default;

         LRFDConcreteBase& operator=(const LRFDConcreteBase&) = default;

         // aggregate correction and bounding factors.
         // see NCHRP Report 496
         void SetEcCorrectionFactors(Float64 K1,Float64 K2);
         void GetEcCorrectionFactors(Float64* pK1,Float64* pK2) const;
         void SetCreepCorrectionFactors(Float64 K1,Float64 K2);
         void GetCreepCorrectionFactors(Float64* pK1,Float64* pK2) const;
         void SetShrinkageCorrectionFactors(Float64 K1,Float64 K2);
         void GetShrinkageCorrectionFactors(Float64* pK1,Float64* pK2) const;

         // Concrete density modification factor (LRFD2016 5.2.4.8)
         virtual void SetLambda(Float64 lambda);
         virtual Float64 GetLambda() const;

         // PCI UHPC parameters
         virtual void SetFirstCrackingStrength(Float64 ffc) = 0;
         virtual Float64 GetFirstCrackingStrength() const = 0;
         virtual void SetPostCrackingTensileStrength(Float64 frr) = 0;
         virtual Float64 GetPostCrackingTensileStrength() const = 0;
         virtual void SetAutogenousShrinkage(Float64 as) = 0;
         virtual Float64 GetAutogenousShrinkage() const = 0;

         // UHPC parameters
         virtual void SetCompressionResponseReductionFactor(Float64 alpha_u) = 0;
         virtual Float64 GetCompressionResponseReductionFactor() const = 0;

         /// Sets an experimentally derived value for ultimate compression strain per
         /// GS 1.4.2.4.2. Do not set this value if ultimate compression strain is to be determined
         /// as the greater of elastic compression strain (GS Eq 1.4.2.4.2-1) and 0.0035
         /// @param ecu 
         virtual void SetCompressiveStrainLimit(Float64 ecu) = 0;
         virtual void SetElasticTensileStrainLimit(Float64 etcr) = 0;
         virtual Float64 GetElasticTensileStrainLimit() const = 0;
         virtual void SetInitialEffectiveCrackingStrength(Float64 ft_cri) = 0;
         virtual Float64 GetInitialEffectiveCrackingStrength() const = 0;
         virtual void SetDesignEffectiveCrackingStrength(Float64 ft_cr) = 0;
         virtual Float64 GetDesignEffectiveCrackingStrength() const = 0;
         virtual void SetCrackLocalizationStrength(Float64 ft_loc) = 0;
         virtual Float64 GetCrackLocalizationStrength() const = 0;
         virtual void SetCrackLocalizationStrain(Float64 et_loc) = 0;
         virtual Float64 GetCrackLocalizationStrain() const = 0;
         virtual void SetFiberOrientationReductionFactor(Float64 gamma_u) = 0;
         virtual Float64 GetFiberOrientationReductionFactor() const = 0;

         virtual Float64 GetElasticCompressiveStrainLimit() const = 0;
         virtual Float64 GetCompressiveStrainLimit(bool* pbIsExperimental = nullptr) const = 0;

      private:
         Float64 m_EcK1{ 1.0 };
         Float64 m_EcK2{ 1.0 };
         Float64 m_CreepK1{ 1.0 };
         Float64 m_CreepK2{ 1.0 };
         Float64 m_ShrinkageK1{ 1.0 };
         Float64 m_ShrinkageK2{ 1.0 };
         Float64 m_Lambda{ 1.0 };
      };
   };
};
