///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <Lrfd\LRFDConcreteBase.h>
#include <Materials/SimpleConcrete.h>

namespace WBFL
{
   namespace LRFD
   {
      struct LRFDCLASS LRFDConcreteShrinkageDetails : public WBFL::Materials::ConcreteBaseShrinkageDetails
      {
         LRFDConcreteShrinkageDetails() = default;
         Float64 kvs{ 0 };
         Float64 khs{ 0 };
         Float64 kf{ 0 };
         Float64 ktd{ 0 };
      };

      struct LRFDCLASS LRFDConcreteCreepDetails : public WBFL::Materials::ConcreteBaseCreepDetails
      {
         LRFDConcreteCreepDetails() = default;
         Float64 kf{ 0 };
         Float64 kc{ 0 };
         Float64 kvs{ 0 };
         Float64 khc{ 0 };
         Float64 ktd{ 0 };
      };


      /// @brief Pseudo Time-dependent concrete model based on AASHTO LRFD. This is a
      /// step function that uses f'ci and Eci until a specified time and then
      /// f'c and Ec. This class is an adaptor for matConcreteEx
      class LRFDCLASS LRFDConcrete : public LRFDConcreteBase
      {
      public:
         LRFDConcrete(LPCTSTR name = _T("Unknown"));
         LRFDConcrete(const WBFL::Materials::SimpleConcrete& initial, const WBFL::Materials::SimpleConcrete & final,Float64 startTime,Float64 stepTime, LPCTSTR name = _T("Unknown"));
         LRFDConcrete(const LRFDConcrete&) = default;
         virtual ~LRFDConcrete() override = default;

         LRFDConcrete& operator=(const LRFDConcrete&) = default;

         void SetConcreteModels(const WBFL::Materials::SimpleConcrete& initial,const WBFL::Materials::SimpleConcrete & final);
         const WBFL::Materials::SimpleConcrete& GetInitialConcreteModel() const;
         const WBFL::Materials::SimpleConcrete& GetFinalConcreteModel() const;

         void SetStartTime(Float64 t);
         Float64 GetStartTime() const;

         void SetStepTime(Float64 t);
         Float64 GetStepTime() const;

         void Use90DayStrength(const WBFL::Materials::SimpleConcrete& concrete90);
         bool Use90DayStrength() const;
         const WBFL::Materials::SimpleConcrete& Get90DayConcreteModel() const;

         // PCI UHPC parameters
         virtual void SetFirstCrackingStrength(Float64 ffc) override;
         virtual Float64 GetFirstCrackingStrength() const override;
         virtual void SetPostCrackingTensileStrength(Float64 frr) override;
         virtual Float64 GetPostCrackingTensileStrength() const override;
         virtual void SetAutogenousShrinkage(Float64 as) override;
         virtual Float64 GetAutogenousShrinkage() const override;

         // UHPC Parameters
         virtual void SetCompressionResponseReductionFactor(Float64 alpha_u) override;
         virtual Float64 GetCompressionResponseReductionFactor() const override;
         virtual void SetCompressiveStrainLimit(Float64 ecu) override;
         virtual void SetElasticTensileStrainLimit(Float64 etcr) override;
         virtual Float64 GetElasticTensileStrainLimit() const override;
         virtual void SetInitialEffectiveCrackingStrength(Float64 ft_cri) override;
         virtual Float64 GetInitialEffectiveCrackingStrength() const override;
         virtual void SetDesignEffectiveCrackingStrength(Float64 ft_cr) override;
         virtual Float64 GetDesignEffectiveCrackingStrength() const override;
         virtual void SetCrackLocalizationStrength(Float64 ft_loc) override;
         virtual Float64 GetCrackLocalizationStrength() const override;
         virtual void SetCrackLocalizationStrain(Float64 et_loc) override;
         virtual Float64 GetCrackLocalizationStrain() const override;
         virtual void SetFiberOrientationReductionFactor(Float64 gamma_u) override;
         virtual Float64 GetFiberOrientationReductionFactor() const override;

         // e.cu per GS 1.4.2.4.2 Max(e.cu,e.cp)
         virtual Float64 GetElasticCompressiveStrainLimit() const override;
         virtual Float64 GetCompressiveStrainLimit(bool* pbIsExperimental = nullptr) const override;

         // Returns the compressive strength of the concrete at time t. If
         // t occurs before the time at casting, zero is returned.
         virtual Float64 GetFc(Float64 t) const override;

         // Returns the secant modulus of the concrete at time t. If
         // t occurs before the time at casting, zero is returned.
         virtual Float64 GetEc(Float64 t) const override;

         // Returns the modulus of rupture for shear calculations at time t. If
         // t occurs before the time at casting, zero is returned.
         virtual Float64 GetShearFr(Float64 t) const override;

         // Returns the modulus of rupture for flexure calculations at time t. If
         // t occurs before the time at casting, zero is returned.
         virtual Float64 GetFlexureFr(Float64 t) const override;

         virtual Float64 GetFreeShrinkageStrain(Float64 t) const override;
         virtual std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> GetFreeShrinkageStrainDetails(Float64 t) const override;

         virtual Float64 GetCreepCoefficient(Float64 t,Float64 tla) const override;
         virtual std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> GetCreepCoefficientDetails(Float64 t,Float64 tla) const override;

         // Creates a clone of this object
         virtual std::unique_ptr<WBFL::Materials::ConcreteBase> CreateClone() const override;

         // Concrete density modification factor (LRFD2016 5.2.4.8)
         virtual void SetLambda(Float64 lambda) override;
         virtual Float64 GetLambda() const override;


      protected:
         std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> GetFreeShrinkageStrainBefore2005(Float64 t) const;
         std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> GetFreeShrinkageStrain2005(Float64 t) const;
         std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> GetFreeShrinkageStrain2015(Float64 t) const;
         std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> GetCreepCoefficientBefore2005(Float64 t,Float64 tla) const;
         std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> GetCreepCoefficient2005(Float64 t,Float64 tla) const;
         std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> GetCreepCoefficient2015(Float64 t,Float64 tla) const;

         bool Use90DayConcrete(Float64 t) const;

      private:
         WBFL::Materials::SimpleConcrete m_InitialConcrete, m_FinalConcrete, m_90DayConcrete;
         bool m_bUse90DayConcrete = false;
         Float64 m_StartTime = 0;
         Float64 m_StepTime = 28;
      };

   };
};
