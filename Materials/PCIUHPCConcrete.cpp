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
#include <Materials/PCIUHPCConcrete.h>
#include <Materials/XConcrete.h>

#include <MathEx.h>
#include <Units/Units.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

void PCIUHPCConcreteSecantModulusModel::SetConcreteStrengthModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel)
{
   m_FcModel = fcModel;
}

const std::shared_ptr<ConcreteStrengthModel>& PCIUHPCConcreteSecantModulusModel::GetConcreteStrengthModel() const
{
   return m_FcModel;
}

Float64 PCIUHPCConcreteSecantModulusModel::GetEc(Float64 age) const
{
   if (age < 0) return 0;

   if (m_FcModel == nullptr) THROW_CONCRETE(_T("PCIUHPCConcreteSecantModulusModel - Concrete strength model not defined"));

   Float64 fc = m_FcModel->GetFc(age);
   Float64 Fc = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::KSI);
   Float64 Ec = 2500 * pow(Fc, 0.33); // Fc in KSI, Ec in KSI (This is LRFD Equation C5.4.2.4-1)
   Float64 e = WBFL::Units::ConvertToSysUnits(Ec, WBFL::Units::Measure::KSI);
   return e;
}

#if defined _DEBUG
bool PCIUHPCConcreteSecantModulusModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void PCIUHPCConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for PCIUHPCConcreteSecantModulusModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool PCIUHPCConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIUHPCConcreteSecantModulusModel");
   
   // want to work is KSI units
   WBFL::Units::AutoSystem auto_restore_units_system;
   WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
   WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
   WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);
   WBFL::Units::System::SetTemperatureUnit(WBFL::Units::Measure::Fahrenheit);
   WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

   PCIUHPCConcreteSecantModulusModel model;
   try
   {
      TRY_TESTME(IsEqual(model.GetEc(28), 6827.66770));
   }
   catch (XConcrete&)
   {
      TRY_TESTME(true);
   }

   std::shared_ptr<ConstantConcreteStrengthModel> fc_model(std::make_shared<ConstantConcreteStrengthModel>(21.0));
   model.SetConcreteStrengthModel(fc_model);
   TRY_TESTME(IsEqual(model.GetEc(28), 6827.66770));

   TESTME_EPILOG("PCIUHPCConcreteSecantModulusModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
PCIUHPCVSRatioCorrectionFactorModel::PCIUHPCVSRatioCorrectionFactorModel(Float64 vsRatio) :
   VSRatioCorrectionFactorModel(vsRatio)
{
}

Float64 PCIUHPCVSRatioCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   return 1.0; // GS E.4.3.2-2
}

#if defined _DEBUG
bool PCIUHPCVSRatioCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void PCIUHPCVSRatioCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool PCIUHPCVSRatioCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIUHPCVSRatioCorrectionFactorModel");
   PCIUHPCVSRatioCorrectionFactorModel model;
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.0));
   TESTME_EPILOG("PCIUHPCVSRatioCorrectionFactorModel");
}
#endif // _UNITTEST


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
PCIUHPCShrinkageHumidityCorrectionFactorModel::PCIUHPCShrinkageHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 PCIUHPCShrinkageHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   return 1.0; // GS E4.3.3-2
}

#if defined _DEBUG
bool PCIUHPCShrinkageHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void PCIUHPCShrinkageHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool PCIUHPCShrinkageHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIUHPCShrinkageHumidityCorrectionFactorModel");
   PCIUHPCShrinkageHumidityCorrectionFactorModel model;
   model.SetH(73);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.0));
   TESTME_EPILOG("PCIUHPCShrinkageHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
PCIUHPCCreepHumidityCorrectionFactorModel::PCIUHPCCreepHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 PCIUHPCCreepHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   return 1.0; // GS E.4.3.2-4
}

#if defined _DEBUG
bool PCIUHPCCreepHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void PCIUHPCCreepHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool PCIUHPCCreepHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIUHPCCreepHumidityCorrectionFactorModel");
   PCIUHPCCreepHumidityCorrectionFactorModel model;
   model.SetH(73);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.0));
   TESTME_EPILOG("PCIUHPCCreepHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
PCIUHPCConcreteStrengthCorrectionFactorModel::PCIUHPCConcreteStrengthCorrectionFactorModel(Float64 fci) :
   ConcreteStrengthCorrectionFactorModel(fci)
{
}

Float64 PCIUHPCConcreteStrengthCorrectionFactorModel::GetCorrectionFactor() const
{
   return 1.0; // GS E4.3.2-5
}

#if defined _DEBUG
bool PCIUHPCConcreteStrengthCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void PCIUHPCConcreteStrengthCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool PCIUHPCConcreteStrengthCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIUHPCConcreteStrengthCorrectionFactorModel");
   PCIUHPCConcreteStrengthCorrectionFactorModel model;
   model.SetFci(WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.0));
   TESTME_EPILOG("PCIUHPCConcreteStrengthCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel::PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci) :
   ConcreteTimeDevelopmentCorrectionFactorModel(fci)
{
}

Float64 PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   Float64 Fci = GetFci();
   Float64 fci = WBFL::Units::ConvertFromSysUnits(Fci, WBFL::Units::Measure::KSI);
   Float64 ktd = t / (12.0*((100. - 4.*fci) / (20. + fci)) + t);
   return ktd;
}

#if defined _DEBUG
bool PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel");
   PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel model;
   model.SetFci(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::KSI));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(89), 0.78761));
   TESTME_EPILOG("PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel");
}
#endif // _UNITTEST
