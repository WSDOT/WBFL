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
#include <Materials/FiberConcrete.h>
#include <Materials/ConcreteSecantModulusModel.h>
#include <Materials/ConcreteStrengthModel.h>
#include <Materials/ConcreteCorrectionFactorModels.h>
#include <Materials/ConcreteCreepTemplateModel.h>

namespace WBFL
{
   namespace Materials
   {
      /// Secant modulus model for UHPC concrete based on "FHWA Proposed Draft Version of AASHTO Guide Specifications for Structural Design with Ultra-High Performance Concrete"
      /// 
      /// See Eqn 1.4.2.3-1
      class MATCLASS FHWAUHPCConcreteSecantModulusModel : public ConcreteSecantModulusModel
      {
      public:
         FHWAUHPCConcreteSecantModulusModel() = default;
         FHWAUHPCConcreteSecantModulusModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel);
         FHWAUHPCConcreteSecantModulusModel(const FHWAUHPCConcreteSecantModulusModel&) = default;
         ~FHWAUHPCConcreteSecantModulusModel() = default;
         FHWAUHPCConcreteSecantModulusModel& operator=(const FHWAUHPCConcreteSecantModulusModel&) = default;

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

      class MATCLASS FHWAUHPCVSRatioCorrectionFactorModel : public VSRatioCorrectionFactorModel
      {
      public:
         FHWAUHPCVSRatioCorrectionFactorModel() = default;
         FHWAUHPCVSRatioCorrectionFactorModel(Float64 vsRatio);
         FHWAUHPCVSRatioCorrectionFactorModel(const FHWAUHPCVSRatioCorrectionFactorModel& rOther) = default;

         virtual ~FHWAUHPCVSRatioCorrectionFactorModel() = default;

         FHWAUHPCVSRatioCorrectionFactorModel& operator=(const FHWAUHPCVSRatioCorrectionFactorModel& rOther) = default;

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

      class MATCLASS FHWAUHPCShrinkageHumidityCorrectionFactorModel : public HumidityCorrectionFactorModel
      {
      public:
         FHWAUHPCShrinkageHumidityCorrectionFactorModel() = default;
         FHWAUHPCShrinkageHumidityCorrectionFactorModel(Float64 h);
         FHWAUHPCShrinkageHumidityCorrectionFactorModel(const FHWAUHPCShrinkageHumidityCorrectionFactorModel& rOther) = default;

         virtual ~FHWAUHPCShrinkageHumidityCorrectionFactorModel() = default;

         FHWAUHPCShrinkageHumidityCorrectionFactorModel& operator=(const FHWAUHPCShrinkageHumidityCorrectionFactorModel& rOther) = default;

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

      class MATCLASS FHWAUHPCCreepHumidityCorrectionFactorModel : public HumidityCorrectionFactorModel
      {
      public:
         FHWAUHPCCreepHumidityCorrectionFactorModel() = default;
         FHWAUHPCCreepHumidityCorrectionFactorModel(Float64 h);
         FHWAUHPCCreepHumidityCorrectionFactorModel(const FHWAUHPCCreepHumidityCorrectionFactorModel& rOther) = default;

         virtual ~FHWAUHPCCreepHumidityCorrectionFactorModel() = default;

         FHWAUHPCCreepHumidityCorrectionFactorModel& operator=(const FHWAUHPCCreepHumidityCorrectionFactorModel& rOther) = default;

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


      class MATCLASS FHWAUHPCConcreteStrengthCorrectionFactorModel : public ConcreteStrengthCorrectionFactorModel
      {
      public:
         FHWAUHPCConcreteStrengthCorrectionFactorModel() = default;
         FHWAUHPCConcreteStrengthCorrectionFactorModel(Float64 fci);
         FHWAUHPCConcreteStrengthCorrectionFactorModel(const FHWAUHPCConcreteStrengthCorrectionFactorModel& rOther) = default;

         virtual ~FHWAUHPCConcreteStrengthCorrectionFactorModel() = default;

         FHWAUHPCConcreteStrengthCorrectionFactorModel& operator=(const FHWAUHPCConcreteStrengthCorrectionFactorModel& rOther) = default;

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

      class MATCLASS FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel : public ConcreteTimeDevelopmentCorrectionFactorModel
      {
      public:
         FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel() = default;
         FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci);
         FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel(const FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

         virtual ~FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel() = default;

         FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel& operator=(const FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

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
   

      class MATCLASS FHWAUHPCConcreteLoadingAgeCorrectionFactorModel : public ConcreteLoadingAgeCorrectionFactorModel
      {
      public:
         FHWAUHPCConcreteLoadingAgeCorrectionFactorModel() = default;
         FHWAUHPCConcreteLoadingAgeCorrectionFactorModel(const FHWAUHPCConcreteLoadingAgeCorrectionFactorModel& rOther) = default;

         virtual ~FHWAUHPCConcreteLoadingAgeCorrectionFactorModel() = default;

         FHWAUHPCConcreteLoadingAgeCorrectionFactorModel& operator=(const FHWAUHPCConcreteLoadingAgeCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor(Float64 ti) const override;

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
