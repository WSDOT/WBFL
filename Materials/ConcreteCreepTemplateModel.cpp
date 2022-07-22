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

#include <Materials/MatLib.h>
#include <Materials/ConcreteCreepTemplateModel.h>
#include <Materials/XConcrete.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

ConcreteCreepTemplateModel::ConcreteCreepTemplateModel(Float64 ct) :
   ConcreteCreepModel(), m_Ct(ct)
{
}

void ConcreteCreepTemplateModel::SetUltimateCreep(Float64 ct)
{
   m_Ct = ct;
}

Float64 ConcreteCreepTemplateModel::GetUltimateCreep() const
{
   return m_Ct;
}

void ConcreteCreepTemplateModel::SetVSRatioCorrectionFactor(const std::shared_ptr<const VSRatioCorrectionFactorModel>& model)
{
   m_VSRatioModel = model;
}

const std::shared_ptr<const VSRatioCorrectionFactorModel>& ConcreteCreepTemplateModel::GetVSRatioCorrectionFactor() const
{
   return m_VSRatioModel;
}

void ConcreteCreepTemplateModel::SetHumidityCorrectionFactor(const std::shared_ptr<const HumidityCorrectionFactorModel>& model)
{
   m_HumidityModel = model;
}

const std::shared_ptr<const HumidityCorrectionFactorModel>& ConcreteCreepTemplateModel::GetHumidityCorrectionFactor() const
{
   return m_HumidityModel;
}

void ConcreteCreepTemplateModel::SetConcreteStrengthCorrectionFactor(const std::shared_ptr<const ConcreteStrengthCorrectionFactorModel>& model)
{
   m_ConcreteStrengthModel = model;
}

const std::shared_ptr<const ConcreteStrengthCorrectionFactorModel>& ConcreteCreepTemplateModel::GetConcreteStrengthCorrectionFactor() const
{
   return m_ConcreteStrengthModel;
}

void ConcreteCreepTemplateModel::SetConcreteTimeDevelopmentCorrectionFactor(const std::shared_ptr<const ConcreteTimeDevelopmentCorrectionFactorModel>& model)
{
   m_TimeDevelopmentModel = model;
}

const std::shared_ptr<const ConcreteTimeDevelopmentCorrectionFactorModel>& ConcreteCreepTemplateModel::GetConcreteTimeDevelopmentCorrectionFactor() const
{
   return m_TimeDevelopmentModel;
}

void ConcreteCreepTemplateModel::SetConcreteLoadingAgeCorrectionFactor(const std::shared_ptr<const ConcreteLoadingAgeCorrectionFactorModel>& model)
{
   m_LoadingAgeModel = model;
}

const std::shared_ptr<const ConcreteLoadingAgeCorrectionFactorModel>& ConcreteCreepTemplateModel::GetConcreteLoadingAgeCorrectionFactor() const
{
   return m_LoadingAgeModel;
}

void ConcreteCreepTemplateModel::SetConcretePhysicalTestingCorrectionFactor(const std::shared_ptr<const ConcretePhysicalTestingCorrectionFactorModel>& model)
{
   m_PhysicalTestingModel = model;
}

const std::shared_ptr<const ConcretePhysicalTestingCorrectionFactorModel>& ConcreteCreepTemplateModel::GetConcretePhysicalTestingCorrectionFactor() const
{
   return m_PhysicalTestingModel;
}

Float64 ConcreteCreepTemplateModel::GetCreep(Float64 t, Float64 ti) const
{
   Float64 ks = m_VSRatioModel ? m_VSRatioModel->GetCorrectionFactor(t) : 1.0;
   Float64 khc = m_HumidityModel ? m_HumidityModel->GetCorrectionFactor() : 1.0;
   Float64 kf = m_ConcreteStrengthModel ? m_ConcreteStrengthModel->GetCorrectionFactor() : 1.0;
   Float64 ktd = m_TimeDevelopmentModel ? m_TimeDevelopmentModel->GetCorrectionFactor(t) : 1.0;
   Float64 kl = m_LoadingAgeModel ? m_LoadingAgeModel->GetCorrectionFactor(ti) : 1.0;
   Float64 K = m_PhysicalTestingModel ? m_PhysicalTestingModel->GetCorrectionFactor() : 1.0;
   Float64 Ct = GetUltimateCreep();

   Float64 Y = Ct * ks * khc * kf * ktd * kl * K;
   return Y;
}


#if defined _DEBUG
bool ConcreteCreepTemplateModel::AssertValid() const
{
   return __super::AssertValid();
}

void ConcreteCreepTemplateModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConcreteCreepModel") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <Materials\FHWAUHPCConcrete.h>
#include <Units\Units.h>
bool ConcreteCreepTemplateModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteCreepTemplateModel");

   ConcreteCreepTemplateModel model(1.2);

   Float64 fci = WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI);

   model.SetVSRatioCorrectionFactor(std::make_shared<FHWAUHPCVSRatioCorrectionFactorModel>(4.5));
   model.SetHumidityCorrectionFactor(std::make_shared<FHWAUHPCCreepHumidityCorrectionFactorModel>(73));
   model.SetConcreteStrengthCorrectionFactor(std::make_shared<FHWAUHPCConcreteStrengthCorrectionFactorModel>(fci));
   model.SetConcreteTimeDevelopmentCorrectionFactor(std::make_shared<FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel>(fci));
   model.SetConcreteLoadingAgeCorrectionFactor(std::make_shared<FHWAUHPCConcreteLoadingAgeCorrectionFactorModel>());
   model.SetConcretePhysicalTestingCorrectionFactor(std::make_shared<ConcretePhysicalTestingCorrectionFactorModel>(0.62));

   TRY_TESTME(IsEqual(model.GetCreep(89,1), 0.87005));

   TESTME_EPILOG("ConcreteCreepTemplateModel");
}
#endif // _UNITTEST
