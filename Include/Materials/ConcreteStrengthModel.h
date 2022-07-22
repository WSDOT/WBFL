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
      /// Abstract base class for a concrete strength model. The purpose of this model is to 
      /// provide the concrete strength at a specified age.
      class MATCLASS ConcreteStrengthModel
      {
      public:
         ConcreteStrengthModel() = default;
         ConcreteStrengthModel(const ConcreteStrengthModel& rOther) = default;

         virtual ~ConcreteStrengthModel() = default;

         ConcreteStrengthModel& operator=(const ConcreteStrengthModel& rOther) = default;

         virtual Float64 GetFc(Float64 age) const = 0;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };

      /// Models concrete strength as constant with age
      class MATCLASS ConstantConcreteStrengthModel : public ConcreteStrengthModel
      {
      public:
         ConstantConcreteStrengthModel() = default;
         ConstantConcreteStrengthModel(Float64 fc);
         ConstantConcreteStrengthModel(const ConstantConcreteStrengthModel& rOther) = default;

         ConstantConcreteStrengthModel& operator=(const ConstantConcreteStrengthModel& rOther) = default;

         void SetFc28(Float64 fc);
         Float64 GetFc28() const;

         virtual Float64 GetFc(Float64 age) const override;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         Float64 m_Fc{ 0.0 };
      };

      /// Models concrete strength as a step function. At the step age, the concrete strength changes from fci to fc
      class MATCLASS SteppedConcreteStrengthModel : public ConcreteStrengthModel
      {
      public:
         SteppedConcreteStrengthModel() = default;
         SteppedConcreteStrengthModel(Float64 fci,Float64 age,Float64 fc);
         SteppedConcreteStrengthModel(const SteppedConcreteStrengthModel& rOther) = default;

         SteppedConcreteStrengthModel& operator=(const SteppedConcreteStrengthModel& rOther) = default;

         void SetFc(Float64 fci, Float64 age, Float64 fc);
         void GetFc(Float64* pfci, Float64* page, Float64* pfc) const;

         virtual Float64 GetFc(Float64 age) const override;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         Float64 m_Fci{ 0.0 };
         Float64 m_Fc{ 0.0 };
         Float64 m_Age{ 0.0 };
      };
   };
};
