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

#include <Lrfd/LrfdExp.h>
#include <Materials/ConcreteSecantModulusModel.h>
#include <Materials/ConcreteStrengthModel.h>
#include <Materials/ConcreteCorrectionFactorModels.h>
#include <Units/Units.h>

namespace WBFL
{
   namespace LRFD
   {
      /// Secant modulus model for concrete based on AASHTO LRFD Bridge Design Specifications
      class LRFDCLASS LRFDConcreteSecantModulusModel : public WBFL::Materials::ConcreteSecantModulusModel
      {
      public:
         LRFDConcreteSecantModulusModel() = default;
         LRFDConcreteSecantModulusModel(const std::shared_ptr<WBFL::Materials::ConcreteStrengthModel>& fcModel, Float64 density);
         LRFDConcreteSecantModulusModel(const LRFDConcreteSecantModulusModel&) = default;
         ~LRFDConcreteSecantModulusModel() = default;
         LRFDConcreteSecantModulusModel& operator=(const LRFDConcreteSecantModulusModel&) = default;

         void SetConcreteStrengthModel(const std::shared_ptr<WBFL::Materials::ConcreteStrengthModel>& fcModel);
         const std::shared_ptr<WBFL::Materials::ConcreteStrengthModel>& GetConcreteStrengthModel() const;

         void SetDensity(Float64 density);
         Float64 GetDensity() const;

         virtual Float64 GetEc(Float64 age) const override;

      private:
         std::shared_ptr<WBFL::Materials::ConcreteStrengthModel> m_FcModel;
         Float64 m_Density{ WBFL::Units::ConvertToSysUnits(0.155,WBFL::Units::Measure::KipPerFeet3) };

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


      class LRFDCLASS LRFDVSRatioCorrectionFactorModel : public WBFL::Materials::VSRatioCorrectionFactorModel
      {
      public:
         LRFDVSRatioCorrectionFactorModel() = default;
         LRFDVSRatioCorrectionFactorModel(Float64 vsRatio);
         LRFDVSRatioCorrectionFactorModel(const LRFDVSRatioCorrectionFactorModel& rOther) = default;

         virtual ~LRFDVSRatioCorrectionFactorModel() = default;

         LRFDVSRatioCorrectionFactorModel& operator=(const LRFDVSRatioCorrectionFactorModel& rOther) = default;

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

      class LRFDCLASS LRFDShrinkageHumidityCorrectionFactorModel : public WBFL::Materials::HumidityCorrectionFactorModel
      {
      public:
         LRFDShrinkageHumidityCorrectionFactorModel() = default;
         LRFDShrinkageHumidityCorrectionFactorModel(Float64 h);
         LRFDShrinkageHumidityCorrectionFactorModel(const LRFDShrinkageHumidityCorrectionFactorModel& rOther) = default;

         virtual ~LRFDShrinkageHumidityCorrectionFactorModel() = default;

         LRFDShrinkageHumidityCorrectionFactorModel& operator=(const LRFDShrinkageHumidityCorrectionFactorModel& rOther) = default;

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

      class LRFDCLASS LRFDCreepHumidityCorrectionFactorModel : public WBFL::Materials::HumidityCorrectionFactorModel
      {
      public:
         LRFDCreepHumidityCorrectionFactorModel() = default;
         LRFDCreepHumidityCorrectionFactorModel(Float64 h);
         LRFDCreepHumidityCorrectionFactorModel(const LRFDCreepHumidityCorrectionFactorModel& rOther) = default;

         virtual ~LRFDCreepHumidityCorrectionFactorModel() = default;

         LRFDCreepHumidityCorrectionFactorModel& operator=(const LRFDCreepHumidityCorrectionFactorModel& rOther) = default;

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


      class LRFDCLASS LRFDConcreteStrengthCorrectionFactorModel : public WBFL::Materials::ConcreteStrengthCorrectionFactorModel
      {
      public:
         LRFDConcreteStrengthCorrectionFactorModel() = default;
         LRFDConcreteStrengthCorrectionFactorModel(Float64 fci);
         LRFDConcreteStrengthCorrectionFactorModel(const LRFDConcreteStrengthCorrectionFactorModel& rOther) = default;

         virtual ~LRFDConcreteStrengthCorrectionFactorModel() = default;

         LRFDConcreteStrengthCorrectionFactorModel& operator=(const LRFDConcreteStrengthCorrectionFactorModel& rOther) = default;

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

      class LRFDCLASS LRFDConcreteTimeDevelopmentCorrectionFactorModel : public WBFL::Materials::ConcreteTimeDevelopmentCorrectionFactorModel
      {
      public:
         LRFDConcreteTimeDevelopmentCorrectionFactorModel() = default;
         LRFDConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci);
         LRFDConcreteTimeDevelopmentCorrectionFactorModel(const LRFDConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

         virtual ~LRFDConcreteTimeDevelopmentCorrectionFactorModel() = default;

         LRFDConcreteTimeDevelopmentCorrectionFactorModel& operator=(const LRFDConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

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

      class LRFDCLASS LRFDConcreteLoadingAgeCorrectionFactorModel : public WBFL::Materials::ConcreteLoadingAgeCorrectionFactorModel
      {
      public:
         LRFDConcreteLoadingAgeCorrectionFactorModel() = default;
         LRFDConcreteLoadingAgeCorrectionFactorModel(const LRFDConcreteLoadingAgeCorrectionFactorModel& rOther) = default;

         virtual ~LRFDConcreteLoadingAgeCorrectionFactorModel() = default;

         LRFDConcreteLoadingAgeCorrectionFactorModel& operator=(const LRFDConcreteLoadingAgeCorrectionFactorModel& rOther) = default;

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
