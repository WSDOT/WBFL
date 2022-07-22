///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <Materials/ConcreteSecantModulusModel.h>
#include <Materials/ConcreteStrengthModel.h>
#include <Materials/ConcreteCorrectionFactorModels.h>

namespace WBFL
{
   namespace Materials
   {
      /// Secant modulus model for PCI UHPC concrete based on "Implementation of Ultra-High Performance Concrete in Long-Span
      /// Precast Pretensioned Elements for COncrete Buildings and Bridges", Phase II Report, PCI
      /// 
      /// See Section E.4.4 of PCI Report. This implementation uses the alternative, which is the LRFD Eqn C5.4.2.4-1
      /// If you want to use the constant 6,500 KSI value PCI reports, use the ConstantConcreteSecantModulusModel object
      /// in your concrete model.
      class MATCLASS PCIUHPCConcreteSecantModulusModel : public ConcreteSecantModulusModel
      {
      public:
         PCIUHPCConcreteSecantModulusModel() = default;
         PCIUHPCConcreteSecantModulusModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel, Float64 density);
         PCIUHPCConcreteSecantModulusModel(const PCIUHPCConcreteSecantModulusModel&) = default;
         ~PCIUHPCConcreteSecantModulusModel() = default;
         PCIUHPCConcreteSecantModulusModel& operator=(const PCIUHPCConcreteSecantModulusModel&) = default;

         void SetConcreteStrengthModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel);
         const std::shared_ptr<ConcreteStrengthModel>& GetConcreteStrengthModel() const;

         virtual Float64 GetEc(Float64 age) const override;

      private:
         std::shared_ptr<ConcreteStrengthModel> m_FcModel;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };


      class MATCLASS PCIUHPCVSRatioCorrectionFactorModel : public VSRatioCorrectionFactorModel
      {
      public:
         PCIUHPCVSRatioCorrectionFactorModel() = default;
         PCIUHPCVSRatioCorrectionFactorModel(Float64 vsRatio);
         PCIUHPCVSRatioCorrectionFactorModel(const PCIUHPCVSRatioCorrectionFactorModel& rOther) = default;

         virtual ~PCIUHPCVSRatioCorrectionFactorModel() = default;

         PCIUHPCVSRatioCorrectionFactorModel& operator=(const PCIUHPCVSRatioCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor(Float64 t) const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      class MATCLASS PCIUHPCShrinkageHumidityCorrectionFactorModel : public HumidityCorrectionFactorModel
      {
      public:
         PCIUHPCShrinkageHumidityCorrectionFactorModel() = default;
         PCIUHPCShrinkageHumidityCorrectionFactorModel(Float64 h);
         PCIUHPCShrinkageHumidityCorrectionFactorModel(const PCIUHPCShrinkageHumidityCorrectionFactorModel& rOther) = default;

         virtual ~PCIUHPCShrinkageHumidityCorrectionFactorModel() = default;

         PCIUHPCShrinkageHumidityCorrectionFactorModel& operator=(const PCIUHPCShrinkageHumidityCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor() const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      class MATCLASS PCIUHPCCreepHumidityCorrectionFactorModel : public HumidityCorrectionFactorModel
      {
      public:
         PCIUHPCCreepHumidityCorrectionFactorModel() = default;
         PCIUHPCCreepHumidityCorrectionFactorModel(Float64 h);
         PCIUHPCCreepHumidityCorrectionFactorModel(const PCIUHPCCreepHumidityCorrectionFactorModel& rOther) = default;

         virtual ~PCIUHPCCreepHumidityCorrectionFactorModel() = default;

         PCIUHPCCreepHumidityCorrectionFactorModel& operator=(const PCIUHPCCreepHumidityCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor() const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };


      class MATCLASS PCIUHPCConcreteStrengthCorrectionFactorModel : public ConcreteStrengthCorrectionFactorModel
      {
      public:
         PCIUHPCConcreteStrengthCorrectionFactorModel() = default;
         PCIUHPCConcreteStrengthCorrectionFactorModel(Float64 fci);
         PCIUHPCConcreteStrengthCorrectionFactorModel(const PCIUHPCConcreteStrengthCorrectionFactorModel& rOther) = default;

         virtual ~PCIUHPCConcreteStrengthCorrectionFactorModel() = default;

         PCIUHPCConcreteStrengthCorrectionFactorModel& operator=(const PCIUHPCConcreteStrengthCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor() const override;

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      class MATCLASS PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel : public ConcreteTimeDevelopmentCorrectionFactorModel
      {
      public:
         PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel() = default;
         PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci);
         PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel(const PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

         virtual ~PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel() = default;

         PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel& operator=(const PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor(Float64 age) const override;

      private:

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};
