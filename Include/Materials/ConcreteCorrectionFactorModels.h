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

namespace WBFL
{
   namespace Materials
   {
      /// Abstract base class for a correction factor related to the volume to surface area ratio of a concrete element
      class MATCLASS VSRatioCorrectionFactorModel
      {
      public:
         VSRatioCorrectionFactorModel() = default;
         VSRatioCorrectionFactorModel(Float64 vsRatio);
         VSRatioCorrectionFactorModel(const VSRatioCorrectionFactorModel& rOther) = default;

         virtual ~VSRatioCorrectionFactorModel() = default;

         VSRatioCorrectionFactorModel& operator=(const VSRatioCorrectionFactorModel& rOther) = default;

         void SetVSRatio(Float64 vs);
         Float64 GetVSRatio() const;

         /// \param t Maturity of concrete in days
         virtual Float64 GetCorrectionFactor(Float64 t) const = 0;

      private:
         Float64 m_VSRatio{ 0.0 };

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

      /// Abstract base class for a correction factor related to relative humidity
      class MATCLASS HumidityCorrectionFactorModel
      {
      public:
         HumidityCorrectionFactorModel() = default;
         HumidityCorrectionFactorModel(Float64 h);
         HumidityCorrectionFactorModel(const HumidityCorrectionFactorModel& rOther) = default;

         virtual ~HumidityCorrectionFactorModel() = default;

         HumidityCorrectionFactorModel& operator=(const HumidityCorrectionFactorModel& rOther) = default;

         /// \param h Humidity in percent, %
         void SetH(Float64 h);
         Float64 GetH() const;

         virtual Float64 GetCorrectionFactor() const = 0;

      private:
         Float64 m_H{ 0.0 };

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


      /// Abstract base class for a correction factor related to concrete strength
      class MATCLASS ConcreteStrengthCorrectionFactorModel
      {
      public:
         ConcreteStrengthCorrectionFactorModel() = default;
         ConcreteStrengthCorrectionFactorModel(Float64 fci);
         ConcreteStrengthCorrectionFactorModel(const ConcreteStrengthCorrectionFactorModel& rOther) = default;

         virtual ~ConcreteStrengthCorrectionFactorModel() = default;

         ConcreteStrengthCorrectionFactorModel& operator=(const ConcreteStrengthCorrectionFactorModel& rOther) = default;

         /// \param fci concrete strength at time of initial loading
         void SetFci(Float64 fci);
         Float64 GetFci() const;

         virtual Float64 GetCorrectionFactor() const = 0;

      private:
         Float64 m_fci{ 0.0 };

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

      /// Abstract base class for a correction factor related to time development and maturity of concrete
      class MATCLASS ConcreteTimeDevelopmentCorrectionFactorModel
      {
      public:
         ConcreteTimeDevelopmentCorrectionFactorModel() = default;
         ConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci);
         ConcreteTimeDevelopmentCorrectionFactorModel(const ConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

         virtual ~ConcreteTimeDevelopmentCorrectionFactorModel() = default;

         ConcreteTimeDevelopmentCorrectionFactorModel& operator=(const ConcreteTimeDevelopmentCorrectionFactorModel& rOther) = default;

         /// \param fci concrete strength at time of initial loading
         void SetFci(Float64 fci);
         Float64 GetFci() const;

         /// \param t concrete maturity in days
         virtual Float64 GetCorrectionFactor(Float64 t) const = 0;

      private:
         Float64 m_fci{ 0.0 };

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


      /// Abstract base class for factor related to effect of loading age
      class MATCLASS ConcreteLoadingAgeCorrectionFactorModel
      {
      public:
         ConcreteLoadingAgeCorrectionFactorModel() = default;
         ConcreteLoadingAgeCorrectionFactorModel(const ConcreteLoadingAgeCorrectionFactorModel& rOther) = default;

         virtual ~ConcreteLoadingAgeCorrectionFactorModel() = default;

         ConcreteLoadingAgeCorrectionFactorModel& operator=(const ConcreteLoadingAgeCorrectionFactorModel& rOther) = default;

         virtual Float64 GetCorrectionFactor(Float64 ti) const = 0;

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

      /// Correction factor related to physical testing of concrete
      class MATCLASS ConcretePhysicalTestingCorrectionFactorModel
      {
      public:
         ConcretePhysicalTestingCorrectionFactorModel() = default;
         ConcretePhysicalTestingCorrectionFactorModel(Float64 k);
         ConcretePhysicalTestingCorrectionFactorModel(const ConcretePhysicalTestingCorrectionFactorModel& rOther) = default;

         virtual ~ConcretePhysicalTestingCorrectionFactorModel() = default;

         ConcretePhysicalTestingCorrectionFactorModel& operator=(const ConcretePhysicalTestingCorrectionFactorModel& rOther) = default;

         void SetK(Float64 k);
         Float64 GetK() const;

         virtual Float64 GetCorrectionFactor() const;

      private:
         Float64 m_K{ 1.0 };

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
