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
#include <Materials/ConcreteShrinkageTemplateModel.h>
#include <Materials/XConcrete.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

ConcreteShrinkageTemplateModel::ConcreteShrinkageTemplateModel(Float64 ecu) :
   ConcreteShrinkageModel(), m_ecu(ecu)
{
}

void ConcreteShrinkageTemplateModel::SetUltimateShrinkageStrain(Float64 ecu)
{
   m_ecu = ecu;
}

Float64 ConcreteShrinkageTemplateModel::GetUltimateShrinkageStrain() const
{
   return m_ecu;
}

void ConcreteShrinkageTemplateModel::SetVSRatioCorrectionFactor(const std::shared_ptr<const VSRatioCorrectionFactorModel>& model)
{
   m_VSRatioModel = model;
}

const std::shared_ptr<const VSRatioCorrectionFactorModel>& ConcreteShrinkageTemplateModel::GetVSRatioCorrectionFactor() const
{
   return m_VSRatioModel;
}

void ConcreteShrinkageTemplateModel::SetHumidityCorrectionFactor(const std::shared_ptr<const HumidityCorrectionFactorModel>& model)
{
   m_HumidityModel = model;
}

const std::shared_ptr<const HumidityCorrectionFactorModel>& ConcreteShrinkageTemplateModel::GetHumidityCorrectionFactor() const
{
   return m_HumidityModel;
}

void ConcreteShrinkageTemplateModel::SetConcreteStrengthCorrectionFactor(const std::shared_ptr<const ConcreteStrengthCorrectionFactorModel>& model)
{
   m_ConcreteStrengthModel = model;
}

const std::shared_ptr<const ConcreteStrengthCorrectionFactorModel>& ConcreteShrinkageTemplateModel::GetConcreteStrengthCorrectionFactor() const
{
   return m_ConcreteStrengthModel;
}

void ConcreteShrinkageTemplateModel::SetConcreteTimeDevelopmentCorrectionFactor(const std::shared_ptr<const ConcreteTimeDevelopmentCorrectionFactorModel>& model)
{
   m_TimeDevelopmentModel = model;
}

const std::shared_ptr<const ConcreteTimeDevelopmentCorrectionFactorModel>& ConcreteShrinkageTemplateModel::GetConcreteTimeDevelopmentCorrectionFactor() const
{
   return m_TimeDevelopmentModel;
}

void ConcreteShrinkageTemplateModel::SetConcretePhysicalTestingCorrectionFactor(const std::shared_ptr<const ConcretePhysicalTestingCorrectionFactorModel>& model)
{
   m_PhysicalTestingModel = model;
}

const std::shared_ptr<const ConcretePhysicalTestingCorrectionFactorModel>& ConcreteShrinkageTemplateModel::GetConcretePhysicalTestingCorrectionFactor() const
{
   return m_PhysicalTestingModel;
}

Float64 ConcreteShrinkageTemplateModel::GetShrinkageStrain(Float64 t) const
{
   Float64 ks = m_VSRatioModel ? m_VSRatioModel->GetCorrectionFactor(t) : 1.0;
   Float64 khs = m_HumidityModel ? m_HumidityModel->GetCorrectionFactor() : 1.0;
   Float64 kf = m_ConcreteStrengthModel ? m_ConcreteStrengthModel->GetCorrectionFactor() : 1.0;
   Float64 ktd = m_TimeDevelopmentModel ? m_TimeDevelopmentModel->GetCorrectionFactor(t) : 1.0;
   Float64 K = m_PhysicalTestingModel ? m_PhysicalTestingModel->GetCorrectionFactor() : 1.0;
   Float64 esh = GetUltimateShrinkageStrain();

   Float64 e_sh = esh * ks * khs * kf * ktd * K;
   return e_sh;
}


#if defined _DEBUG
bool ConcreteShrinkageTemplateModel::AssertValid() const
{
   return __super::AssertValid();
}

void ConcreteShrinkageTemplateModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConcreteShrinkageModel") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <Materials\FHWAUHPCConcrete.h>
#include <Units\Units.h>
bool ConcreteShrinkageTemplateModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteShrinkageTemplateModel");

   ConcreteShrinkageTemplateModel model(0.6e-3);

   Float64 fci = WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI);

   model.SetVSRatioCorrectionFactor(std::make_shared<FHWAUHPCVSRatioCorrectionFactorModel>(4.5));
   model.SetHumidityCorrectionFactor(std::make_shared<FHWAUHPCShrinkageHumidityCorrectionFactorModel>(73));
   model.SetConcreteStrengthCorrectionFactor(std::make_shared<FHWAUHPCConcreteStrengthCorrectionFactorModel>(fci));
   model.SetConcreteTimeDevelopmentCorrectionFactor(std::make_shared<FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel>(fci));
   model.SetConcretePhysicalTestingCorrectionFactor(std::make_shared<ConcretePhysicalTestingCorrectionFactorModel>(0.41));

   TRY_TESTME(IsEqual(model.GetShrinkageStrain(89), 0.000234 ));

   TESTME_EPILOG("ConcreteShrinkageTemplateModel");
}
#endif // _UNITTEST
