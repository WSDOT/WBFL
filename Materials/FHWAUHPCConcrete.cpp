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
#include <Materials/FHWAUHPCConcrete.h>
#include <Materials/XConcrete.h>

#include <MathEx.h>
#include <Units/Units.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

FHWAUHPCConcreteSecantModulusModel::FHWAUHPCConcreteSecantModulusModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel) :
   m_FcModel(fcModel)
{
}

void FHWAUHPCConcreteSecantModulusModel::SetConcreteStrengthModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel)
{
   m_FcModel = fcModel;
}

const std::shared_ptr<ConcreteStrengthModel>& FHWAUHPCConcreteSecantModulusModel::GetConcreteStrengthModel() const
{
   return m_FcModel;
}

Float64 FHWAUHPCConcreteSecantModulusModel::GetEc(Float64 age) const
{
   if (age < 0) return 0;

   if (m_FcModel == nullptr) THROW_CONCRETE(_T("FHWAUHPCConcreteSecantModulusModel - Concrete strength model not defined"));

   Float64 fc = m_FcModel->GetFc(age);
   Float64 Fc = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::KSI);
   Float64 Ec = 2500 * pow(Fc, 0.33); // Fc in KSI, Ec in KSI (This is LRFD Equation C5.4.2.4-1)
   Float64 e = WBFL::Units::ConvertToSysUnits(Ec, WBFL::Units::Measure::KSI);
   return e;
}

#if defined _DEBUG
bool FHWAUHPCConcreteSecantModulusModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void FHWAUHPCConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for FHWAUHPCConcreteSecantModulusModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool FHWAUHPCConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FHWAUHPCConcreteSecantModulusModel");
   
   // want to work is KSI units
   WBFL::Units::AutoSystem auto_restore_units_system;
   WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
   WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
   WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);
   WBFL::Units::System::SetTemperatureUnit(WBFL::Units::Measure::Fahrenheit);
   WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

   FHWAUHPCConcreteSecantModulusModel model;
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

   TESTME_EPILOG("FHWAUHPCConcreteSecantModulusModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
FHWAUHPCVSRatioCorrectionFactorModel::FHWAUHPCVSRatioCorrectionFactorModel(Float64 vsRatio) :
   VSRatioCorrectionFactorModel(vsRatio)
{
}

Float64 FHWAUHPCVSRatioCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   return 1.0; // GS 1.4.2.8.2-2
}

#if defined _DEBUG
bool FHWAUHPCVSRatioCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void FHWAUHPCVSRatioCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool FHWAUHPCVSRatioCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FHWAUHPCVSRatioCorrectionFactorModel");
   FHWAUHPCVSRatioCorrectionFactorModel model;
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.0));
   TESTME_EPILOG("FHWAUHPCVSRatioCorrectionFactorModel");
}
#endif // _UNITTEST


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
FHWAUHPCShrinkageHumidityCorrectionFactorModel::FHWAUHPCShrinkageHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 FHWAUHPCShrinkageHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   Float64 H = GetH();
   return 1.5 - 0.01 * H; // GS 1.4.2.8.3-2
}

#if defined _DEBUG
bool FHWAUHPCShrinkageHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void FHWAUHPCShrinkageHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool FHWAUHPCShrinkageHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FHWAUHPCShrinkageHumidityCorrectionFactorModel");
   FHWAUHPCShrinkageHumidityCorrectionFactorModel model;
   model.SetH(73);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.77));
   TESTME_EPILOG("FHWAUHPCShrinkageHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
FHWAUHPCCreepHumidityCorrectionFactorModel::FHWAUHPCCreepHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 FHWAUHPCCreepHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   Float64 H = GetH();
   return 1.12 - 0.0024 * H; // GS 1.4.2.8.2-3
}

#if defined _DEBUG
bool FHWAUHPCCreepHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void FHWAUHPCCreepHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool FHWAUHPCCreepHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FHWAUHPCCreepHumidityCorrectionFactorModel");
   FHWAUHPCCreepHumidityCorrectionFactorModel model;
   model.SetH(73);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.9448));
   TESTME_EPILOG("FHWAUHPCCreepHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
FHWAUHPCConcreteStrengthCorrectionFactorModel::FHWAUHPCConcreteStrengthCorrectionFactorModel(Float64 fci) :
   ConcreteStrengthCorrectionFactorModel(fci)
{
}

Float64 FHWAUHPCConcreteStrengthCorrectionFactorModel::GetCorrectionFactor() const
{
   // see GS 1.4.2.8.2-4
   Float64 Fci = GetFci();
   Float64 fci = WBFL::Units::ConvertFromSysUnits(Fci, WBFL::Units::Measure::KSI);
   Float64 kf = 18.0 / (1.5 * fci - 3.0);
   return kf;
}

#if defined _DEBUG
bool FHWAUHPCConcreteStrengthCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void FHWAUHPCConcreteStrengthCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool FHWAUHPCConcreteStrengthCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FHWAUHPCConcreteStrengthCorrectionFactorModel");
   FHWAUHPCConcreteStrengthCorrectionFactorModel model;
   model.SetFci(WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.0));
   TESTME_EPILOG("FHWAUHPCConcreteStrengthCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel::FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci) :
   ConcreteTimeDevelopmentCorrectionFactorModel(fci)
{
}

Float64 FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   Float64 Fci = GetFci();
   Float64 fci = WBFL::Units::ConvertFromSysUnits(Fci, WBFL::Units::Measure::KSI);
   Float64 ktd = t / ((300 / (fci + 30)) + 0.8 * pow(t, 0.98));
   return ktd;
}

#if defined _DEBUG
bool FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel");
   FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel model;
   model.SetFci(WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(89), 1.23775));
   TESTME_EPILOG("FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

Float64 FHWAUHPCConcreteLoadingAgeCorrectionFactorModel::GetCorrectionFactor(Float64 ti) const
{
   return (ti < 7.0) ? 1.0 : pow(ti - 6, -0.15); // GS Eqns 1.4.2.8.2-6 and -7
}

#if defined _DEBUG
bool FHWAUHPCConcreteLoadingAgeCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void FHWAUHPCConcreteLoadingAgeCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool FHWAUHPCConcreteLoadingAgeCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("FHWAUHPCConcreteLoadingAgeCorrectionFactorModel");
   FHWAUHPCConcreteLoadingAgeCorrectionFactorModel model;
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(1), 1.0));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(7), 1.0));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(10), 0.81225));
   TESTME_EPILOG("FHWAUHPCConcreteLoadingAgeCorrectionFactorModel");
}
#endif // _UNITTEST
