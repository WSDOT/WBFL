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

#include <Lrfd/LrfdLib.h>
#include <Lrfd/LRFDConcrete2.h>
#include <Materials/XConcrete.h>
#include <Lrfd/VersionMgr.h>

#include <MathEx.h>
#include <Units/Units.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::LRFD;
using namespace WBFL::Materials;

LRFDConcreteSecantModulusModel::LRFDConcreteSecantModulusModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel, Float64 density) :
   m_FcModel(fcModel), m_Density(density)
{
}

void LRFDConcreteSecantModulusModel::SetConcreteStrengthModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel)
{
   m_FcModel = fcModel;
}

const std::shared_ptr<ConcreteStrengthModel>& LRFDConcreteSecantModulusModel::GetConcreteStrengthModel() const
{
   return m_FcModel;
}         

void LRFDConcreteSecantModulusModel::SetDensity(Float64 density) 
{
   m_Density = density;
}

Float64 LRFDConcreteSecantModulusModel::GetDensity() const
{
   return m_Density;
}

Float64 LRFDConcreteSecantModulusModel::GetEc(Float64 age) const
{
   if (age < 0) return 0;

   if (m_FcModel == nullptr) THROW_CONCRETE(_T("LRFDConcreteSecantModulusModel - Concrete strength model not defined"));

   Float64 Fc;          // fc in spec units
   Float64 Density;     // density in spec units
   Float64 E;           // Modulus of elasticity in spec units
   Float64 k;           // coefficient in equation

   // Input units
   const WBFL::Units::Stress* p_fc_unit;
   const WBFL::Units::Density* p_density_unit;
   const WBFL::Units::Stress* p_E_unit;

   if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
   {
      ASSERT(lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::GetLastSIVersion());

      p_fc_unit = &WBFL::Units::Measure::MPa;
      p_density_unit = &WBFL::Units::Measure::KgPerMeter3;
      p_E_unit = &WBFL::Units::Measure::MPa;

      k = 0.043;
   }
   else
   {
      // :NOTE: 1 lbm = 1 lbf
      p_fc_unit = &WBFL::Units::Measure::KSI;
      p_density_unit = &WBFL::Units::Measure::KipPerFeet3;
      p_E_unit = &WBFL::Units::Measure::KSI;

      if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims)
      {
         k = 33000.;
      }
      else
      {
         k = 120000.;
      }
   }

   // Convert input to required units
   Float64 fc = m_FcModel->GetFc(age);
   Fc = WBFL::Units::ConvertFromSysUnits(fc, *p_fc_unit);
   Density = WBFL::Units::ConvertFromSysUnits(m_Density, *p_density_unit);

   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims)
   {
      E = k * pow(Density, 1.5) * sqrt(Fc);
   }
   else
   {
      E = k * pow(Density, 2.0) * pow(Fc, 0.33);
   }

   Float64 k1 = GetK1Model()->GetCorrectionFactor();
   Float64 k2 = GetK2Model()->GetCorrectionFactor();
   E *= k1 * k2;

   // Convert output to system units.
   Float64 e = WBFL::Units::ConvertToSysUnits(E, *p_E_unit);

   return e;
}

#if defined _DEBUG
bool LRFDConcreteSecantModulusModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void LRFDConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for LRFDConcreteSecantModulusModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <LRFD/AutoVersion.h>
bool LRFDConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LRFDConcreteSecantModulusModel");
   
   LRFDConcreteSecantModulusModel model;
   try
   {
      TRY_TESTME(IsEqual(model.GetEc(28), 6827.66770));
   }
   catch (XConcrete&)
   {
      TRY_TESTME(true);
   }

   Float64 fc = WBFL::Units::ConvertToSysUnits(8.0, WBFL::Units::Measure::KSI);
   Float64 density = WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3);
   std::shared_ptr<ConstantConcreteStrengthModel> fc_model(std::make_shared<ConstantConcreteStrengthModel>(fc));
   model.SetConcreteStrengthModel(fc_model);
   model.SetDensity(density);

   Float64 Ec;
   lrfdAutoVersion auto_reset_version;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);
   Ec = WBFL::Units::ConvertFromSysUnits(model.GetEc(28), WBFL::Units::Measure::KSI);
   TRY_TESTME(IsEqual(Ec, 5455.34380));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   Ec = WBFL::Units::ConvertFromSysUnits(model.GetEc(28), WBFL::Units::Measure::KSI);
   TRY_TESTME(IsEqual(Ec, 5422.45332));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::SeventhEditionWith2015Interims);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   Ec = WBFL::Units::ConvertFromSysUnits(model.GetEc(28), WBFL::Units::Measure::KSI);
   TRY_TESTME(IsEqual(Ec, 5362.69948));

   TESTME_EPILOG("LRFDConcreteSecantModulusModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
LRFDVSRatioCorrectionFactorModel::LRFDVSRatioCorrectionFactorModel(Float64 vsRatio) :
   VSRatioCorrectionFactorModel(vsRatio)
{
}

Float64 LRFDVSRatioCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   Float64 ks;
   Float64 vs = GetVSRatio();
   ASSERT(0 < vs); // did you forget to set V/S ratio?
   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims)
   {
      // LRFD C5.4.2.3.3-1
      if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US)
      {
         ASSERT(lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::GetLastSIVersion());
         vs = WBFL::Units::ConvertFromSysUnits(vs, WBFL::Units::Measure::Inch);
         Float64 k1 = t / (26.0 * exp(0.36 * vs) + t);
         Float64 k2 = t / (45.0 + t);
         Float64 k3 = (1064 - 94 * vs) / 923;
         ks = (k1 / k2) * k3;
      }
      else
      {
         vs = WBFL::Units::ConvertFromSysUnits(vs, WBFL::Units::Measure::Millimeter);
         Float64 k1 = t / (26.0 * exp(0.0142 * vs) + t);
         Float64 k2 = t / (45.0 + t);
         Float64 k3 = (1064 - 3.7 * vs) / 923;
         ks = (k1 / k2) * k3;
      }
   }
   else
   {
      if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
      {
         ASSERT(lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::GetLastSIVersion());
         vs = WBFL::Units::ConvertFromSysUnits(vs, WBFL::Units::Measure::Millimeter);
         ks = 1.45 - 0.0051 * vs; // LRFD 5.4.2.3.2-2
      }
      else
      {
         vs = WBFL::Units::ConvertFromSysUnits(vs, WBFL::Units::Measure::Inch);
         ks = 1.45 - 0.13 * vs; // LRFD 5.4.2.3.2-2
      }

      if (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::ThirdEditionWith2005Interims)
      {
         ks = Max(ks, 1.0);
      }
      else if (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::ThirdEditionWith2006Interims)
      {
         ks = Max(ks, 0.0);
      }
      else
      {
         ks = Max(ks, 1.0);
      }
   }

   return ks;
}

#if defined _DEBUG
bool LRFDVSRatioCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void LRFDVSRatioCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool LRFDVSRatioCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LRFDVSRatioCorrectionFactorModel");
   LRFDVSRatioCorrectionFactorModel model;
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(4.5,WBFL::Units::Measure::Inch));

   lrfdAutoVersion auto_reset_version;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 0.31733));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 0.31809));


   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.0)); // 1.0 is min value
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Millimeter));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.44949));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(4.5, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.0)); // 1.0 is min value
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.43700));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2006Interims);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(4.5, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 0.86500));
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(600, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 0.0)); // 0.0 is min value


   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FourthEdition2007);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(4.5, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.0)); // 1.0 is min value
   model.SetVSRatio(WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(28.0), 1.43700));


   TESTME_EPILOG("LRFDVSRatioCorrectionFactorModel");
}
#endif // _UNITTEST


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
LRFDShrinkageHumidityCorrectionFactorModel::LRFDShrinkageHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 LRFDShrinkageHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   Float64 H = GetH();
   Float64 khs = 0;
   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims)
   {
      if (H < 80)
      {
         khs = (140 - H) / 70;
      }
      else
      {
         khs = 3 * (100 - H) / 70;
      }
      ASSERT(0 <= khs);
   }
   else
   {
      khs = 2.00 - 0.014 * H; // LRFD 5.4.2.3.3-2
   }

   return khs;
}

#if defined _DEBUG
bool LRFDShrinkageHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void LRFDShrinkageHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool LRFDShrinkageHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LRFDShrinkageHumidityCorrectionFactorModel");
   LRFDShrinkageHumidityCorrectionFactorModel model;

   lrfdAutoVersion auto_reset_version;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   model.SetH(75);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.92857));

   model.SetH(85);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.64286));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);
   model.SetH(75);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.95));

   TESTME_EPILOG("LRFDShrinkageHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
LRFDCreepHumidityCorrectionFactorModel::LRFDCreepHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 LRFDCreepHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   Float64 H = GetH();
   Float64 khc = 0;
   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims)
   {
      khc = 1.58 - H / 120;
   }
   else
   {
      khc = 1.56 - 0.008 * H; // LRFD 5.4.2.3.2-3
   }

   return khc;
}

#if defined _DEBUG
bool LRFDCreepHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void LRFDCreepHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool LRFDCreepHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LRFDCreepHumidityCorrectionFactorModel");
   LRFDCreepHumidityCorrectionFactorModel model;
   model.SetH(75);

   lrfdAutoVersion auto_reset_version;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.955));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.96));

   TESTME_EPILOG("LRFDCreepHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
LRFDConcreteStrengthCorrectionFactorModel::LRFDConcreteStrengthCorrectionFactorModel(Float64 fci) :
   ConcreteStrengthCorrectionFactorModel(fci)
{
}

Float64 LRFDConcreteStrengthCorrectionFactorModel::GetCorrectionFactor() const
{
   Float64 kf = 0;
   Float64 fci = GetFci();
   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims)
   {
      if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
      {
         fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::MPa);
         kf = 62.0 / (42.0 + fci);
         ASSERT(lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::GetLastSIVersion());
      }
      else
      {
         fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI);
         kf = 1.0 / (0.67 + (fci / 9.0));
      }
   }
   else
   {
      if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
      {
         fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::MPa);
         kf = 35.0 / (7.0 + fci);
         ASSERT(lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::GetLastSIVersion());
      }
      else
      {
         fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI);
         kf = 5 / (1 + fci);
      }
   }

   return kf;
}

#if defined _DEBUG
bool LRFDConcreteStrengthCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void LRFDConcreteStrengthCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool LRFDConcreteStrengthCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LRFDConcreteStrengthCorrectionFactorModel");
   LRFDConcreteStrengthCorrectionFactorModel model;
   model.SetFci(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));

   lrfdAutoVersion auto_reset_version;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.81074));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.81596));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.84391));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.83333));

   TESTME_EPILOG("LRFDConcreteStrengthCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
LRFDConcreteTimeDevelopmentCorrectionFactorModel::LRFDConcreteTimeDevelopmentCorrectionFactorModel(Float64 fci) :
   ConcreteTimeDevelopmentCorrectionFactorModel(fci)
{
}

Float64 LRFDConcreteTimeDevelopmentCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   Float64 ktd = 0;
   Float64 Fci = GetFci();

   if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
   {
      Float64 fci = WBFL::Units::ConvertFromSysUnits(Fci, WBFL::Units::Measure::MPa);
      ktd = t / (61.0 - 0.58 * fci + t);
      ASSERT(lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::GetLastSIVersion());
   }
   else
   {
      Float64 fci = WBFL::Units::ConvertFromSysUnits(Fci, WBFL::Units::Measure::KSI);
      if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims)
      {
         ktd = t / (12.0*((100. - 4.*fci)/(fci + 20.)) + t);
      }
      else
      {
         ktd = t / (61.0 - 4.0 * fci + t);
      }
   }

   return ktd;
}

#if defined _DEBUG
bool LRFDConcreteTimeDevelopmentCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void LRFDConcreteTimeDevelopmentCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool LRFDConcreteTimeDevelopmentCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LRFDConcreteTimeDevelopmentCorrectionFactorModel");
   LRFDConcreteTimeDevelopmentCorrectionFactorModel model;
   model.SetFci(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));

   lrfdAutoVersion auto_reset_version;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(89), 0.68459));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(89), 0.69859));

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::SeventhEditionWith2015Interims);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(89), 0.68462));

   TESTME_EPILOG("LRFDConcreteTimeDevelopmentCorrectionFactorModel");
}
#endif // _UNITTEST


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

Float64 LRFDConcreteLoadingAgeCorrectionFactorModel::GetCorrectionFactor(Float64 ti) const
{
   return pow(ti,-0.118); // 5.4.2.3.2-1
}

#if defined _DEBUG
bool LRFDConcreteLoadingAgeCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void LRFDConcreteLoadingAgeCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool LRFDConcreteLoadingAgeCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("LRFDConcreteLoadingAgeCorrectionFactorModel");
   LRFDConcreteLoadingAgeCorrectionFactorModel model;
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(1), 1.0));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(7), 0.79484));
   TESTME_EPILOG("LRFDConcreteLoadingAgeCorrectionFactorModel");
}
#endif // _UNITTEST
