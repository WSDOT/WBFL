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
#include <Materials/ConcreteCorrectionFactorModels.h>

namespace WBFL
{
   namespace Materials
   {
      /// Abstract base class for a concrete secant modulus model. The purpose of this model is to 
      /// provide the secant modulus of elasticity at a specified age.
      class MATCLASS ConcreteSecantModulusModel
      {
      public:
         ConcreteSecantModulusModel() = default;
         ConcreteSecantModulusModel(const ConcreteSecantModulusModel& rOther) = default;

         virtual ~ConcreteSecantModulusModel() = default;

         ConcreteSecantModulusModel& operator=(const ConcreteSecantModulusModel& rOther) = default;

         /// Model for averging factor
         void SetK1Model(const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& model);
         const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& GetK1Model() const;

         /// Model for bounding factor
         void SetK2Model(const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& model);
         const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& GetK2Model() const;

         virtual Float64 GetEc(Float64 age) const = 0;

      private:
         std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel> m_K1Model{ std::make_shared<ConcretePhysicalTestingCorrectionFactorModel>() };
         std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel> m_K2Model{ std::make_shared<ConcretePhysicalTestingCorrectionFactorModel>() };

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

      /// Models modulus of elasticity as constant with age
      class MATCLASS ConstantConcreteSecantModulusModel : public ConcreteSecantModulusModel
      {
      public:
         ConstantConcreteSecantModulusModel() = default;
         ConstantConcreteSecantModulusModel(Float64 Ec);
         ConstantConcreteSecantModulusModel(const ConstantConcreteSecantModulusModel& rOther) = default;

         ConstantConcreteSecantModulusModel& operator=(const ConstantConcreteSecantModulusModel& rOther) = default;

         void SetEc28(Float64 Ec);
         Float64 GetEc28() const;

         virtual Float64 GetEc(Float64 age) const override;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         Float64 m_Ec{ 0.0 };
      };

      /// Models modulus of elasticity as a step function. At the step age, the modulus of elasticity changes from Eci to Ec
      class MATCLASS SteppedConcreteSecantModulusModel : public ConcreteSecantModulusModel
      {
      public:
         SteppedConcreteSecantModulusModel() = default;
         SteppedConcreteSecantModulusModel(Float64 Eci,Float64 age,Float64 Ec);
         SteppedConcreteSecantModulusModel(const SteppedConcreteSecantModulusModel& rOther) = default;

         SteppedConcreteSecantModulusModel& operator=(const SteppedConcreteSecantModulusModel& rOther) = default;

         void SetEc(Float64 Eci, Float64 age, Float64 Ec);
         void GetEc(Float64* pEci, Float64* page, Float64* pEc) const;

         virtual Float64 GetEc(Float64 age) const override;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         Float64 m_Eci{ 0.0 };
         Float64 m_Ec{ 0.0 };
         Float64 m_Age{ 0.0 };
      };
   };
};
