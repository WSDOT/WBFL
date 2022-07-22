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
#include <Materials/CEBFIPConcrete.h>
#include <Materials/XConcrete.h>

#include <MathEx.h>
#include <Units/Units.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

LPCTSTR CEBFIPConcrete::GetCementType(CementType type)
{
   if ( type == CementType::RS )
   {
      return _T("RS");
   }
   else if ( type == CementType::N )
   {
      return _T("N");
   }
   else if ( type == CementType::R )
   {
      return _T("R");
   }
   else if ( type == CementType::SL )
   {
      return _T("SL");
   }

   ASSERT(false); // is there a new cement type?
   return _T("UNKNOWN");
}

void CEBFIPConcrete::GetModelParameters(CementType cementType,Float64* pS,Float64* pBetaSC)
{
   // See CEBFIP 2.1.6.1 and 2.1.6.4.4
   if ( cementType == CementType::RS )
   {
      *pS = 0.20;
      *pBetaSC = 8;
   }
   else if ( cementType == CementType::N || cementType == CementType::R )
   {
      *pS = 0.25;
      *pBetaSC = 5;
   }
   else if ( cementType == CementType::SL )
   {
      *pS = 0.38;
      *pBetaSC = 4;
   }
   else
   {
      ASSERT(false); // is there a new cement type?
   }
}

Float64 CEBFIPConcrete::ComputeFc28(Float64 fc,Float64 age,CementType type)
{
   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   Float64 s, betaSc;
   GetModelParameters(type,&s,&betaSc);
   Float64 beta = exp(s*(1.0 - sqrt(28./age)));
   Float64 fc28 = fc/beta;
   return fc28;
}

Float64 CEBFIPConcrete::ComputeEc28(Float64 Ec,Float64 age,CementType type)
{
   // CEB-FIP Eqn. 2.1-57, solved for Ec at 28 days
   Float64 s, betaSc;
   GetModelParameters(type,&s,&betaSc);
   Float64 beta = exp(s*(1.0 - sqrt(28./age)));
   Float64 Ec28 = Ec/sqrt(beta);
   return Ec28;
}

CEBFIPConcrete::CEBFIPConcrete(LPCTSTR name) :
ConcreteBase(name),
m_Fc28(0),
m_Ec28(0),
m_bUserEc(false),
m_bIsValid(false)
{
   GetModelParameters(CEBFIPConcrete::CementType::N,&m_S,&m_BetaSc);
}

void CEBFIPConcrete::SetS(Float64 s)
{
   if ( !IsEqual(m_S,s) )
   {
      m_S = s;
      m_bIsValid = false;
   }
}

Float64 CEBFIPConcrete::GetS() const
{
   return m_S;
}

void CEBFIPConcrete::SetBetaSc(Float64 betaSc)
{
   if ( !IsEqual(m_BetaSc,betaSc) )
   {
      m_BetaSc = betaSc;
      m_bIsValid = false;
   }
}

Float64 CEBFIPConcrete::GetBetaSc() const
{
   return m_BetaSc;
}

void CEBFIPConcrete::SetFc28(Float64 fc)
{
   if ( !IsEqual(m_Fc28,fc) )
   {
      m_Fc28 = fc;
      m_bIsValid = false;
   }
}

void CEBFIPConcrete::SetFc28(Float64 fc,Float64 t)
{
   Float64 age = GetAge(t);
   ASSERT(!IsZero(age));

   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   // age is in days
   m_Fc28 = fc/exp(m_S*(1.0 - sqrt(28./age)));

   m_bIsValid = false;
}

Float64 CEBFIPConcrete::GetFc28() const
{
   return m_Fc28;
}

void CEBFIPConcrete::UserEc28(bool bUserEc)
{
   if ( m_bUserEc != bUserEc )
   {
      m_bUserEc = bUserEc;
      m_bIsValid = false;
   }
}

bool CEBFIPConcrete::UserEc28() const
{
   return m_bUserEc;
}

void CEBFIPConcrete::SetEc28(Float64 Ec)
{
   if ( !IsEqual(m_Ec28,Ec) )
   {
      m_Ec28 = Ec;
      m_bIsValid = false;
   }
}

Float64 CEBFIPConcrete::GetEc28() const
{
   return m_Ec28;
}

void CEBFIPConcrete::SetEc28(Float64 Ec,Float64 t)
{
   Float64 age = GetAge(t);
   ASSERT(!IsZero(age));

   // CEB-FIP Equation 2.1-57, rearranged to solve for Ec28
   // age must be in days
   m_Ec28 = Ec/sqrt(exp(m_S*(1 - sqrt(28/age))));

   m_bIsValid = false;
}

Float64 CEBFIPConcrete::ComputeFc28(Float64 fc,Float64 age,Float64 s)
{
   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   // age is in days
   Float64 fc28 = fc/exp(s*(1.0 - sqrt(28./age)));
   return fc28;
}

Float64 CEBFIPConcrete::ComputeEc28(Float64 ec,Float64 age,Float64 s)
{
   // CEB-FIP Equation 2.1-57, rearranged to solve for Ec28
   // age must be in days
   Float64 Ec28 = ec/sqrt(exp(s*(1 - sqrt(28/age))));
   return Ec28;
}

void CEBFIPConcrete::ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pS)
{
   // Solving CEB-FIP Equation 2.1-54 for S
   // t1 and t2 in days
   *pS = log(fc1/fc2)/(sqrt(28/t2) - sqrt(28/t1));
}

Float64 CEBFIPConcrete::GetFc(Float64 t) const
{
   Validate();

   Float64 age = GetAge(t);
   if ( age < 0 )
   {
      return 0;
   }

   // age must be in days
   Float64 beta = exp(m_S*(1 - sqrt(28/age))); // CEB-FIP Eqn. 2.1-54
   Float64 fc = beta*m_Fc28; // CEB-FIP Eqn. 2.1-53
   return fc;
}

Float64 CEBFIPConcrete::GetEc(Float64 t) const
{
   Validate();

   Float64 age = GetAge(t);
   if ( age < 0 )
   {
      return 0;
   }

   // age must be in days
   Float64 beta = sqrt(exp(m_S*(1 - sqrt(28/age)))); // CEB-FIP Eqn. 2.1-58
   Float64 Ec = beta*m_Ec; // CEB-FIP Eqn. 2.1-57
   return Ec;
}

Float64 CEBFIPConcrete::GetFlexureFr(Float64 t) const
{
   return GetFr(t);
}

Float64 CEBFIPConcrete::GetShearFr(Float64 t) const
{
   return GetFr(t);
}

Float64 CEBFIPConcrete::GetFreeShrinkageStrain(Float64 t) const
{
   return GetFreeShrinkageStrainDetails(t)->esh;
}

std::unique_ptr<ConcreteBaseShrinkageDetails> CEBFIPConcrete::GetFreeShrinkageStrainDetails(Float64 t) const
{
   std::unique_ptr<CEBFIPConcreteShrinkageDetails> pDetails(std::make_unique<CEBFIPConcreteShrinkageDetails>());

   ConcreteBase::InitializeShrinkageDetails(t,pDetails.get());

   Float64 shrinkage_time = pDetails->shrinkage_duration;
   if ( shrinkage_time < 0 )
   {
      return pDetails;
   }

   // Notional shrinkage coefficient... CEB-FIP Eqn. 2.1-75
   Float64 ecso = GetNotionalShrinkageCoefficient(); // CEB-FIP Eqn. 2.1-75

   // Time development factor CEB-FIP Eqn. 2.1-79
   Float64 h = GetH();
   h = WBFL::Units::ConvertFromSysUnits(h,WBFL::Units::Measure::Millimeter); // need h in millimeter
   Float64 ho = 100; // 100 millimieter
   Float64 betaS = sqrt( shrinkage_time/(350*pow(h/ho,2) + shrinkage_time) );

   Float64 esh = ecso * betaS;

   pDetails->h = GetH();
   pDetails->BetaSC = m_BetaSc;
   pDetails->BetaSRH = GetBetaSRH();
   pDetails->BetaRH = GetBetaRH();
   pDetails->BetaS = betaS;
   pDetails->es = GetEpsilonS();
   pDetails->ecso = ecso;
   pDetails->esh = esh;
   return pDetails;
}

Float64 CEBFIPConcrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   return GetCreepCoefficientDetails(t,tla)->Ct;
}

std::unique_ptr<ConcreteBaseCreepDetails> CEBFIPConcrete::GetCreepCoefficientDetails(Float64 t,Float64 tla) const
{
   std::unique_ptr<CEBFIPConcreteCreepDetails> pDetails(std::make_unique<CEBFIPConcreteCreepDetails>());
   InitializeCreepDetails(t,tla, pDetails.get());

   Float64 age = pDetails->age;
   Float64 age_at_loading = pDetails->age_at_loading;
   Float64 maturity = age - age_at_loading;
   if ( ::IsLE(age,0.0) || ::IsLE(age_at_loading,0.0) || ::IsLE(maturity,0.0) )
   {
      return pDetails;
   }

   Float64 phiRH = GetPhiRH();
   Float64 beta_fcm = GetBetaFcm();


   Float64 beta_to = 1/(0.1 + pow(age_at_loading,0.2)); // CEB-FIP Eqn. 2.1-68

   Float64 co = phiRH * beta_fcm * beta_to; // CEB-FIP Eqn. 2.1-65

   // Time Development
   Float64 beta_H = GetBetaH();

   Float64 beta_c = pow(maturity/(beta_H + maturity),0.3); // CEB-FIP Eqn. 2.1-70

   Float64 c = co * beta_c; // CEB-FIP Eqn. 2.1-64

   pDetails->Yo = co;
   pDetails->Bc = beta_c;
   pDetails->Yrh = phiRH;
   pDetails->Bfc = beta_fcm;
   pDetails->Bt = beta_to;
   pDetails->Bh = beta_H;
   pDetails->h = GetH();
   pDetails->Ct = c;

   return pDetails;
}

Float64 CEBFIPConcrete::GetH() const
{
   Float64 h = 2*m_VS; // Eqn 2.1-69. Note that V/S ratio = Area/Perimeter
   return h;
}

Float64 CEBFIPConcrete::GetBetaSRH() const
{
   if ( m_RelativeHumidity < 40 )
   {
      return -1; // not applicable
   }
   else if ( 40 <= m_RelativeHumidity && m_RelativeHumidity < 99 )
   {
      return 1 - pow(m_RelativeHumidity/100,3); // CEB-FIP Eqn. 2.1-78
   }
   else
   {
      return -1; // not applicable
   }
}

Float64 CEBFIPConcrete::GetBetaRH() const
{
   // returns Beta-RH for use in CEB-FIP Eqn. 2.1-75
   Float64 beta;
   if ( m_RelativeHumidity < 40 )
   {
      beta = -1.4508; // Assume constant value for RH = 40%
   }
   else if ( 40 <= m_RelativeHumidity && m_RelativeHumidity < 99 )
   {
      Float64 beta_sRH = GetBetaSRH();
      ASSERT(0 < beta_sRH);
      beta = -1.55*beta_sRH; // CEB-FIP Eqn. 2.1-77
   }
   else
   {
      beta = 0.25; // CEB-FIP Eqn. 2.1-77
   }

   return beta;
}

Float64 CEBFIPConcrete::GetEpsilonS() const
{
   Float64 fc28 = WBFL::Units::ConvertFromSysUnits(m_Fc28,WBFL::Units::Measure::MPa); // must be in MPa for CEB-FIP equations
   Float64 es_fcm = (160 + 10*m_BetaSc*(9 - fc28/10))*1E-6; // CEB-FIP Eqn 2.1-76
   return es_fcm;
}

Float64 CEBFIPConcrete::GetNotionalShrinkageCoefficient() const
{
   Float64 es_fcm = GetEpsilonS();
   Float64 beta_RH = GetBetaRH();
   Float64 ecso = es_fcm * beta_RH; // CEB-FIP Eqn. 2.1-75
   return ecso;
}

Float64 CEBFIPConcrete::GetPhiRH() const
{
   Float64 h = GetH();
   h = WBFL::Units::ConvertFromSysUnits(h,WBFL::Units::Measure::Millimeter); // need h in millimeter
   Float64 ho = 100; // 100 millimieter

   Float64 phiRH = 1 + (1-m_RelativeHumidity/100)/(0.46*(pow(h/ho,1./3.))); // CEB-FIP Eqn. 2.1-66
   return phiRH;
}

Float64 CEBFIPConcrete::GetBetaFcm() const
{
   Float64 fc28 = WBFL::Units::ConvertFromSysUnits(m_Fc28,WBFL::Units::Measure::MPa); // must be in MPa for CEB-FIP equations
   Float64 beta_fcm = 5.3/sqrt(fc28/10); // CEB-FIP Eqn. 2.1-67
   return beta_fcm;
}

Float64 CEBFIPConcrete::GetBetaH() const
{
   Float64 h = GetH();
   h = WBFL::Units::ConvertFromSysUnits(h,WBFL::Units::Measure::Millimeter); // need h in millimeter
   Float64 ho = 100; // 100 millimieter

   Float64 beta_H = 150*(1 + pow(1.2*m_RelativeHumidity/100,18))*(h/ho) + 250; // CEB-FIP Eqn. 2.1-71
   beta_H = Min(beta_H,1500.0);
   return beta_H;
}

std::unique_ptr<ConcreteBase> CEBFIPConcrete::CreateClone() const
{
   return std::make_unique<CEBFIPConcrete>(*this);
}

void CEBFIPConcrete::OnChanged()
{
   m_bIsValid = false;
}

void CEBFIPConcrete::Validate() const
{
   if ( m_bIsValid )
   {
      return;
   }

   if ( m_bUserEc )
   {
      m_Ec = m_Ec28;
   }
   else
   {
      m_Ec = ModE(m_Fc28,GetStrengthDensity());
   }

   m_bIsValid = true;
}

Float64 CEBFIPConcrete::GetFr(Float64 t) const
{
   Validate();

   Float64 age = GetAge(t);
   if ( age < 0 )
   {
      return 0;
   }

   Float64 fc = GetFc(t);

   // Convert input to required units
   Float64 Fc      = WBFL::Units::ConvertFromSysUnits( fc,      WBFL::Units::Measure::PSI         );
   Float64 Density = WBFL::Units::ConvertFromSysUnits( m_StrengthDensity, WBFL::Units::Measure::LbmPerFeet3 );

   // Eqn 2-3
   Float64 gr = 0.6;
   Float64 fr = gr*sqrt(Density*Fc);
   fr = WBFL::Units::ConvertToSysUnits( fr, WBFL::Units::Measure::PSI );
   return fr;
}

// Could be using lrfdConcreteUtil::ModE, except that creates a circular
// dependency between WBFLMaterial and WBFLLrfd. Neither will link
// without the other first being linked.
//
// For now, the easiest solution is to have a localized ModE method here
Float64 CEBFIPConcrete::ModE(Float64 fc,Float64 density) const
{
#pragma Reminder("WORKING HERE - Need to update this - it's not the right model - see SecantModel below")
   Float64 Fc;          // fc in spec units
   Float64 Density;     // density in spec units
   Float64 E;           // Modulus of elasticity in spec units
   Float64 e;           // modulus of elasticity in System Units

   // Convert input to required units
   Fc      = WBFL::Units::ConvertFromSysUnits( fc,      WBFL::Units::Measure::PSI         );
   Density = WBFL::Units::ConvertFromSysUnits( density, WBFL::Units::Measure::LbmPerFeet3 );


   E = 33.0 * pow( Density, 1.5 ) * sqrt( Fc );

   // Convert output to system units.
   e = WBFL::Units::ConvertToSysUnits( E, WBFL::Units::Measure::PSI );

   return e;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

void CEBFIPConcreteStrengthModel::GetModelParameters(CementType cementType, Float64* pS)
{
   // See CEBFIP 2.1.6.1 and 2.1.6.4.4
   if (cementType == CementType::RS)
   {
      *pS = 0.20;
   }
   else if (cementType == CementType::N || cementType == CementType::R)
   {
      *pS = 0.25;
   }
   else if (cementType == CementType::SL)
   {
      *pS = 0.38;
   }
   else
   {
      ASSERT(false); // is there a new cement type?
   }
}

Float64 CEBFIPConcreteStrengthModel::ComputeFc28(Float64 fc, Float64 age, CementType type)
{
   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   Float64 s;
   GetModelParameters(type, &s);
   Float64 beta = exp(s * (1.0 - sqrt(28. / age)));
   Float64 fc28 = fc / beta;
   return fc28;
}

void CEBFIPConcreteStrengthModel::SetS(Float64 s)
{
   m_S = s;
}

Float64 CEBFIPConcreteStrengthModel::GetS() const
{
   return m_S;
}

void CEBFIPConcreteStrengthModel::SetFc28(Float64 fc)
{
   m_Fc28 = fc;
}

void CEBFIPConcreteStrengthModel::SetFc28(Float64 fc, Float64 age)
{
   PRECONDITION(0 < age);

   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   // age is in days
   Float64 beta_cc = GetBetaCC(age);
   m_Fc28 = fc / beta_cc;
}

Float64 CEBFIPConcreteStrengthModel::GetFc28() const
{
   return m_Fc28;
}

Float64 CEBFIPConcreteStrengthModel::ComputeFc28(Float64 fc, Float64 age, Float64 s)
{
   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   // age is in days
   Float64 fc28 = fc / exp(s * (1.0 - sqrt(28. / age)));
   return fc28;
}

void CEBFIPConcreteStrengthModel::ComputeParameters(Float64 fc1, Float64 t1, Float64 fc2, Float64 t2, Float64* pS)
{
   // Solving CEB-FIP Equation 2.1-54 for S
   // t1 and t2 in days
   *pS = log(fc1 / fc2) / (sqrt(28 / t2) - sqrt(28 / t1));
}

Float64 CEBFIPConcreteStrengthModel::GetBetaCC(Float64 age) const
{
   if (age < 0) return 0;

   Float64 beta_cc = exp(m_S * (1.0 - sqrt(28. / age))); // CEB-FIB Eq'n 2.1-54
   return beta_cc;
}

Float64 CEBFIPConcreteStrengthModel::GetFc(Float64 age) const
{
   if (age < 0)
   {
      return 0;
   }

   // age must be in days
   Float64 beta_cc = GetBetaCC(age);
   Float64 fc = beta_cc * m_Fc28; // CEB-FIP Eqn. 2.1-53
   return fc;
}

#if defined _DEBUG
bool CEBFIPConcreteStrengthModel::AssertValid() const
{
   return true;
}

void CEBFIPConcreteStrengthModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for CEBFIPConcreteStrengthModel") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool CEBFIPConcreteStrengthModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CEBFIPConcreteStrengthModel");

   CEBFIPConcreteStrengthModel model;
   Float64 s;
   CEBFIPConcreteStrengthModel::GetModelParameters(CementType::RS, &s);

   model.SetFc28(7);
   model.SetS(s);

   TRY_TESTME(IsEqual(model.GetFc(10), 6.11807));
   TRY_TESTME(IsEqual(model.GetFc(56), 7.42229));


   TESTME_EPILOG("CEBFIPConcreteStrengthModel");
}
#endif // _UNITTEST


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

CEBFIPConcreteSecantModulusModel::CEBFIPConcreteSecantModulusModel(const std::shared_ptr<CEBFIPConcreteStrengthModel>& fcModel) :
   ConcreteSecantModulusModel(), m_FcModel(fcModel)
{
}

Float64 CEBFIPConcreteSecantModulusModel::ComputeEc28(Float64 Ec, Float64 age, CEBFIPConcreteStrengthModel::CementType type)
{
   // CEB-FIP Eqn. 2.1-57, solved for Ec at 28 days
   Float64 s;
   CEBFIPConcreteStrengthModel::GetModelParameters(type, &s);
   Float64 beta = exp(s * (1.0 - sqrt(28. / age)));
   Float64 Ec28 = Ec / sqrt(beta);
   return Ec28;
}

Float64 CEBFIPConcreteSecantModulusModel::ComputeEc28(Float64 ec, Float64 age, Float64 s)
{
   // CEB-FIP Equation 2.1-57, rearranged to solve for Ec28
   // age must be in days
   Float64 Ec28 = ec / sqrt(exp(s * (1 - sqrt(28 / age))));
   return Ec28;
}

void CEBFIPConcreteSecantModulusModel::SetConcreteStrengthModel(const std::shared_ptr<CEBFIPConcreteStrengthModel>& fcModel)
{
   m_FcModel = fcModel;
}

const std::shared_ptr<CEBFIPConcreteStrengthModel>& CEBFIPConcreteSecantModulusModel::GetConcreteStrengthModel() const
{
   return m_FcModel;
}

Float64 CEBFIPConcreteSecantModulusModel::GetEc(Float64 age) const
{
   if (age < 0) return 0;

   if (m_FcModel == nullptr) THROW_CONCRETE(_T("CEBFIPConcreteSecantModulusModel - Concrete strength model not defined"));

   Float64 fcm = m_FcModel->GetFc(28.0); // fc at 28 days
   Float64 fcmo = WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::MPa);
   Float64 Eco = WBFL::Units::ConvertToSysUnits(2.15e4, WBFL::Units::Measure::MPa);
   Float64 Eci = Eco * pow(fcm / fcmo, 1.0 / 3.0); // CEB-FIP Eqn 2.1-16 (28 day Ec)

   if (IsEqual(age, 28.0)) return Eci;

   Float64 beta_cc = m_FcModel->GetBetaCC(age);

   Float64 beta_E = sqrt(beta_cc); // CEB-FIP Eqn 2.1-58
   Float64 E = beta_E * Eci; // CEB-FIP Eqn 2.1-57

   return E;
}

#if defined _DEBUG
bool CEBFIPConcreteSecantModulusModel::AssertValid() const
{
   return true;
}

void CEBFIPConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for CEBFIPConcreteSecantModulusModel") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool CEBFIPConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CEBFIPConcreteSecantModulusModel");

   // want to work is KSI units
   WBFL::Units::AutoSystem auto_restore_units_system;
   WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
   WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
   WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);
   WBFL::Units::System::SetTemperatureUnit(WBFL::Units::Measure::Fahrenheit);
   WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

   CEBFIPConcreteSecantModulusModel model;
   try
   {
      model.GetEc(28.0);
   }
   catch (XConcrete&)
   {
      TRY_TESTME(true);
   }

   std::shared_ptr<CEBFIPConcreteStrengthModel> fcModel(std::make_shared<CEBFIPConcreteStrengthModel>());
   
   Float64 s;
   CEBFIPConcreteStrengthModel::GetModelParameters(CEBFIPConcreteStrengthModel::CementType::RS, &s);

   fcModel->SetFc28(7);
   fcModel->SetS(s);

   model.SetConcreteStrengthModel(fcModel);

   TRY_TESTME(IsEqual(model.GetEc(10), 4926.62946));
   TRY_TESTME(IsEqual(model.GetEc(28), 5269.77191));
   TRY_TESTME(IsEqual(model.GetEc(56), 5426.40256));


   TESTME_EPILOG("CEBFIPConcreteSecantModulusModel");
}
#endif // _UNITTEST

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

CEBFIPConcreteShrinkageModel::CEBFIPConcreteShrinkageModel(Float64 vsRatio, Float64 rh, CEBFIPConcrete::CementType cementType, Float64 fc28) :
   ConcreteShrinkageModel(), m_VSRatio(vsRatio), m_RH(rh), m_CementType(cementType), m_Fc28(fc28)
{
}

void CEBFIPConcreteShrinkageModel::SetVSRatio(Float64 vsRatio) 
{
   m_VSRatio = vsRatio;
}

Float64 CEBFIPConcreteShrinkageModel::GetVSRatio() const
{
   return m_VSRatio;
}

void CEBFIPConcreteShrinkageModel::SetHumidity(Float64 rh)
{
   m_RH = rh;
}

Float64 CEBFIPConcreteShrinkageModel::GetHumidity() const
{
   return m_RH;
}

void CEBFIPConcreteShrinkageModel::SetCementType(CEBFIPConcrete::CementType cementType)
{
   m_CementType = cementType;
}

CEBFIPConcrete::CementType CEBFIPConcreteShrinkageModel::GetCementType() const
{
   return m_CementType;
}

void CEBFIPConcreteShrinkageModel::SetFc28(Float64 fc28)
{
   m_Fc28 = fc28;
}

Float64 CEBFIPConcreteShrinkageModel::GetFc28() const
{
   return m_Fc28;
}

Float64 CEBFIPConcreteShrinkageModel::GetShrinkageStrain(Float64 age) const
{
   // Notional shrinkage coefficient... CEB-FIP Eqn. 2.1-75
   Float64 ecso = GetNotionalShrinkageCoefficient(); // CEB-FIP Eqn. 2.1-75

   // Time development factor CEB-FIP Eqn. 2.1-79
   Float64 h = GetH();
   h = WBFL::Units::ConvertFromSysUnits(h, WBFL::Units::Measure::Millimeter); // need h in millimeter
   Float64 ho = 100; // 100 millimieter
   Float64 betaS = sqrt(age / (350 * pow(h / ho, 2) + age));

   Float64 esh = ecso * betaS;

   return esh;
}

Float64 CEBFIPConcreteShrinkageModel::GetH() const
{
   // See Eqn 2.1-69
   // VS ratio is basically the same as Ac/u and h = 2Ac/u
   return 2 * m_VSRatio;
}

Float64 CEBFIPConcreteShrinkageModel::GetNotionalShrinkageCoefficient() const
{
   Float64 es_fcm = GetEpsilonS();
   Float64 beta_RH = GetBetaRH();
   Float64 ecso = es_fcm * beta_RH; // CEB-FIP Eqn. 2.1-75
   return ecso;
}

Float64 CEBFIPConcreteShrinkageModel::GetEpsilonS() const
{
   Float64 fcm = WBFL::Units::ConvertFromSysUnits(m_Fc28, WBFL::Units::Measure::MPa); // must be in MPa for CEB-FIP equations
   Float64 fcmo = 10.0; // MPa
   Float64 betaSC = GetBetaSC();
   Float64 es_fcm = (160 + 10 * betaSC * (9 - fcm / fcmo)) * 1E-6; // CEB-FIP Eqn 2.1-76
   return es_fcm;
}

Float64 CEBFIPConcreteShrinkageModel::GetBetaRH() const
{
   // returns Beta-RH for use in CEB-FIP Eqn. 2.1-75
   Float64 beta;
   if (m_RH < 40)
   {
      beta = -1.4508; // Assume constant value for RH = 40%
   }
   else if (40 <= m_RH && m_RH < 99)
   {
      Float64 beta_sRH = GetBetaSRH();
      ASSERT(0 < beta_sRH);
      beta = -1.55 * beta_sRH; // CEB-FIP Eqn. 2.1-77
   }
   else
   {
      beta = 0.25; // CEB-FIP Eqn. 2.1-77
   }

   return beta;
}

Float64 CEBFIPConcreteShrinkageModel::GetBetaSRH() const
{
   Float64 betaSRH = 1.0 - pow(m_RH / 100.0, 3);
   return betaSRH;
}

Float64 CEBFIPConcreteShrinkageModel::GetBetaSC() const
{
   // See CEBFIP 2.1.6.1 and 2.1.6.4.4
   Float64 betaSC = 0;
   switch (m_CementType)
   {
   case CEBFIPConcrete::CementType::RS:
      betaSC = 8; break;

   case CEBFIPConcrete::CementType::N:
   case CEBFIPConcrete::CementType::R:
      betaSC = 5;
      break;

   case CEBFIPConcrete::CementType::SL:
      betaSC = 4;
      break;

   default:
      ASSERT(false);
      betaSC = 0;
      break;
   }
   return betaSC;
}

#if defined _DEBUG
bool CEBFIPConcreteShrinkageModel::AssertValid() const
{
   return __super::AssertValid();
}

void CEBFIPConcreteShrinkageModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}

#endif // _DEBUG

#if defined _UNITTEST
bool CEBFIPConcreteShrinkageModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CEBFIPConcreteShrinkageModel");

   CuringType curingType{ CuringType::Moist };

   CEBFIPConcreteShrinkageModel model(
      WBFL::Units::ConvertToSysUnits(4.5, WBFL::Units::Measure::Inch),
      75,
      CEBFIPConcrete::CementType::N,
      WBFL::Units::ConvertToSysUnits(7.0, WBFL::Units::Measure::KSI)
   );

   TRY_TESTME(IsEqual(model.GetShrinkageStrain(89), -7.1166336160217504e-05));

   TESTME_EPILOG("CEBFIPConcreteShrinkageModel");
}
#endif // _UNITTEST
