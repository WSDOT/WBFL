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
#include <Materials/ConcreteShrinkageModel.h>
#include <Materials/ConcreteCorrectionFactorModels.h>

namespace WBFL
{
   namespace Materials
   {
      /// Model for concrete shrinkage based on the Template method pattern. This class implements
      /// the high level calculation of concrete shrinkage as the product of an ultimate shrinkage strain
      /// and correction factors for V/S ratio, humidity, strength, time, and physical testing.
      /// Calculation of correction factors is deligated to correction factor models.
      class MATCLASS ConcreteShrinkageTemplateModel : public ConcreteShrinkageModel
      {
      public:
         ConcreteShrinkageTemplateModel(Float64 ecu);
         ConcreteShrinkageTemplateModel() = default;
         ConcreteShrinkageTemplateModel(const ConcreteShrinkageTemplateModel& rOther) = default;

         virtual ~ConcreteShrinkageTemplateModel() = default;

         ConcreteShrinkageTemplateModel& operator=(const ConcreteShrinkageTemplateModel& rOther) = default;

         void SetUltimateShrinkageStrain(Float64 eu);
         Float64 GetUltimateShrinkageStrain() const;

         void SetVSRatioCorrectionFactor(const std::shared_ptr<const VSRatioCorrectionFactorModel>& model);
         const std::shared_ptr<const VSRatioCorrectionFactorModel>& GetVSRatioCorrectionFactor() const;

         void SetHumidityCorrectionFactor(const std::shared_ptr<const HumidityCorrectionFactorModel>& model);
         const std::shared_ptr<const HumidityCorrectionFactorModel>& GetHumidityCorrectionFactor() const;

         void SetConcreteStrengthCorrectionFactor(const std::shared_ptr<const ConcreteStrengthCorrectionFactorModel>& model);
         const std::shared_ptr<const ConcreteStrengthCorrectionFactorModel>& GetConcreteStrengthCorrectionFactor() const;

         void SetConcreteTimeDevelopmentCorrectionFactor(const std::shared_ptr<const ConcreteTimeDevelopmentCorrectionFactorModel>& model);
         const std::shared_ptr<const ConcreteTimeDevelopmentCorrectionFactorModel>& GetConcreteTimeDevelopmentCorrectionFactor() const;

         void SetConcretePhysicalTestingCorrectionFactor(const std::shared_ptr<const ConcretePhysicalTestingCorrectionFactorModel>& model);
         const std::shared_ptr<const ConcretePhysicalTestingCorrectionFactorModel>& GetConcretePhysicalTestingCorrectionFactor() const;

         virtual Float64 GetShrinkageStrain(Float64 t) const override;

      private:
         Float64 m_ecu{ 0.0 };
         std::shared_ptr<const VSRatioCorrectionFactorModel> m_VSRatioModel;
         std::shared_ptr<const HumidityCorrectionFactorModel> m_HumidityModel;
         std::shared_ptr<const ConcreteStrengthCorrectionFactorModel> m_ConcreteStrengthModel;
         std::shared_ptr<const ConcreteTimeDevelopmentCorrectionFactorModel> m_TimeDevelopmentModel;
         std::shared_ptr<const ConcretePhysicalTestingCorrectionFactorModel> m_PhysicalTestingModel{ std::make_shared<ConcretePhysicalTestingCorrectionFactorModel>() };

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
