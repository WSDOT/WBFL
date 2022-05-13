///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\CEBFIPConcrete.h>

#include <MathEx.h>
#include <Units\Units.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR matCEBFIPConcrete::GetCementType(CementType type)
{
   if ( type == RS )
   {
      return _T("RS");
   }
   else if ( type == N )
   {
      return _T("N");
   }
   else if ( type == R )
   {
      return _T("R");
   }
   else if ( type == SL )
   {
      return _T("SL");
   }

   ATLASSERT(false); // is there a new cement type?
   return _T("UNKNOWN");
}

void matCEBFIPConcrete::GetModelParameters(CementType cementType,Float64* pS,Float64* pBetaSC)
{
   // See CEBFIP 2.1.6.1 and 2.1.6.4.4
   if ( cementType == RS )
   {
      *pS = 0.20;
      *pBetaSC = 8;
   }
   else if ( cementType == N || cementType == R )
   {
      *pS = 0.25;
      *pBetaSC = 5;
   }
   else if ( cementType == SL )
   {
      *pS = 0.38;
      *pBetaSC = 4;
   }
   else
   {
      ATLASSERT(false); // is there a new cement type?
   }
}

Float64 matCEBFIPConcrete::ComputeFc28(Float64 fc,Float64 age,CementType type)
{
   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   Float64 s, betaSc;
   GetModelParameters(type,&s,&betaSc);
   Float64 beta = exp(s*(1.0 - sqrt(28./age)));
   Float64 fc28 = fc/beta;
   return fc28;
}

Float64 matCEBFIPConcrete::ComputeEc28(Float64 Ec,Float64 age,CementType type)
{
   // CEB-FIP Eqn. 2.1-57, solved for Ec at 28 days
   Float64 s, betaSc;
   GetModelParameters(type,&s,&betaSc);
   Float64 beta = exp(s*(1.0 - sqrt(28./age)));
   Float64 Ec28 = Ec/sqrt(beta);
   return Ec28;
}

matCEBFIPConcrete::matCEBFIPConcrete(LPCTSTR name) :
matConcreteBase(name),
m_Fc28(0),
m_Ec28(0),
m_bUserEc(false),
m_bIsValid(false)
{
   GetModelParameters(matCEBFIPConcrete::N,&m_S,&m_BetaSc);
}

matCEBFIPConcrete::matCEBFIPConcrete(const matCEBFIPConcrete& rOther) :
matConcreteBase(rOther)
{
   m_bIsValid = false;
   m_Fc28     = rOther.m_Fc28;
   m_Ec28     = rOther.m_Ec28;
   m_bUserEc  = rOther.m_bUserEc;
   m_S        = rOther.m_S;
   m_BetaSc   = rOther.m_BetaSc;
}

void matCEBFIPConcrete::SetS(Float64 s)
{
   if ( !IsEqual(m_S,s) )
   {
      m_S = s;
      m_bIsValid = false;
   }
}

Float64 matCEBFIPConcrete::GetS() const
{
   return m_S;
}

void matCEBFIPConcrete::SetBetaSc(Float64 betaSc)
{
   if ( !IsEqual(m_BetaSc,betaSc) )
   {
      m_BetaSc = betaSc;
      m_bIsValid = false;
   }
}

Float64 matCEBFIPConcrete::GetBetaSc() const
{
   return m_BetaSc;
}

void matCEBFIPConcrete::SetFc28(Float64 fc)
{
   if ( !IsEqual(m_Fc28,fc) )
   {
      m_Fc28 = fc;
      m_bIsValid = false;
   }
}

void matCEBFIPConcrete::SetFc28(Float64 fc,Float64 t)
{
   Float64 age = GetAge(t);
   ATLASSERT(!IsZero(age));

   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   // age is in days
   m_Fc28 = fc/exp(m_S*(1.0 - sqrt(28./age)));

   m_bIsValid = false;
}

Float64 matCEBFIPConcrete::GetFc28() const
{
   return m_Fc28;
}

void matCEBFIPConcrete::UserEc28(bool bUserEc)
{
   if ( m_bUserEc != bUserEc )
   {
      m_bUserEc = bUserEc;
      m_bIsValid = false;
   }
}

bool matCEBFIPConcrete::UserEc28() const
{
   return m_bUserEc;
}

void matCEBFIPConcrete::SetEc28(Float64 Ec)
{
   if ( !IsEqual(m_Ec28,Ec) )
   {
      m_Ec28 = Ec;
      m_bIsValid = false;
   }
}

Float64 matCEBFIPConcrete::GetEc28() const
{
   return m_Ec28;
}

void matCEBFIPConcrete::SetEc28(Float64 Ec,Float64 t)
{
   Float64 age = GetAge(t);
   ATLASSERT(!IsZero(age));

   // CEB-FIP Equation 2.1-57, rearranged to solve for Ec28
   // age must be in days
   m_Ec28 = Ec/sqrt(exp(m_S*(1 - sqrt(28/age))));

   m_bIsValid = false;
}

Float64 matCEBFIPConcrete::ComputeFc28(Float64 fc,Float64 age,Float64 s)
{
   // CEB-FIP Eqn. 2.1-54, solved for f'c at 28 days
   // age is in days
   Float64 fc28 = fc/exp(s*(1.0 - sqrt(28./age)));
   return fc28;
}

Float64 matCEBFIPConcrete::ComputeEc28(Float64 ec,Float64 age,Float64 s)
{
   // CEB-FIP Equation 2.1-57, rearranged to solve for Ec28
   // age must be in days
   Float64 Ec28 = ec/sqrt(exp(s*(1 - sqrt(28/age))));
   return Ec28;
}

void matCEBFIPConcrete::ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pS)
{
   // Solving CEB-FIP Equation 2.1-54 for S
   // t1 and t2 in days
   *pS = log(fc1/fc2)/(sqrt(28/t2) - sqrt(28/t1));
}

Float64 matCEBFIPConcrete::GetFc(Float64 t) const
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

Float64 matCEBFIPConcrete::GetEc(Float64 t) const
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

Float64 matCEBFIPConcrete::GetFlexureFr(Float64 t) const
{
   return GetFr(t);
}

Float64 matCEBFIPConcrete::GetShearFr(Float64 t) const
{
   return GetFr(t);
}

Float64 matCEBFIPConcrete::GetFreeShrinkageStrain(Float64 t) const
{
   std::shared_ptr<matConcreteBaseShrinkageDetails> pDetails = GetFreeShrinkageStrainDetails(t);
   return pDetails->esh;
}

std::shared_ptr<matConcreteBaseShrinkageDetails> matCEBFIPConcrete::GetFreeShrinkageStrainDetails(Float64 t) const
{
   std::shared_ptr<matCEBFIPConcreteShrinkageDetails> pDetails(std::make_shared<matCEBFIPConcreteShrinkageDetails>());

   matConcreteBase::InitializeShrinkageDetails(t,std::dynamic_pointer_cast<matConcreteBaseShrinkageDetails>(pDetails));

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

Float64 matCEBFIPConcrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   return GetCreepCoefficientDetails(t,tla)->Ct;
}

std::shared_ptr<matConcreteBaseCreepDetails> matCEBFIPConcrete::GetCreepCoefficientDetails(Float64 t,Float64 tla) const
{
   std::shared_ptr<matCEBFIPConcreteCreepDetails> pDetails(std::make_shared<matCEBFIPConcreteCreepDetails>());
   InitializeCreepDetails(t,tla, std::dynamic_pointer_cast<matConcreteBaseCreepDetails>(pDetails));

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

Float64 matCEBFIPConcrete::GetH() const
{
   Float64 h = 2*m_VS; // Eqn 2.1-69. Note that V/S ratio = Area/Perimeter
   return h;
}

Float64 matCEBFIPConcrete::GetBetaSRH() const
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

Float64 matCEBFIPConcrete::GetBetaRH() const
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
      ATLASSERT(0 < beta_sRH);
      beta = -1.55*beta_sRH; // CEB-FIP Eqn. 2.1-77
   }
   else
   {
      beta = 0.25; // CEB-FIP Eqn. 2.1-77
   }

   return beta;
}

Float64 matCEBFIPConcrete::GetEpsilonS() const
{
   Float64 fc28 = WBFL::Units::ConvertFromSysUnits(m_Fc28,WBFL::Units::Measure::MPa); // must be in MPa for CEB-FIP equations
   Float64 es_fcm = (160 + 10*m_BetaSc*(9 - fc28/10))*1E-6; // CEB-FIP Eqn 2.1-76
   return es_fcm;
}

Float64 matCEBFIPConcrete::GetNotionalShrinkageCoefficient() const
{
   Float64 es_fcm = GetEpsilonS();
   Float64 beta_RH = GetBetaRH();
   Float64 ecso = es_fcm * beta_RH; // CEB-FIP Eqn. 2.1-75
   return ecso;
}

Float64 matCEBFIPConcrete::GetPhiRH() const
{
   Float64 h = GetH();
   h = WBFL::Units::ConvertFromSysUnits(h,WBFL::Units::Measure::Millimeter); // need h in millimeter
   Float64 ho = 100; // 100 millimieter

   Float64 phiRH = 1 + (1-m_RelativeHumidity/100)/(0.46*(pow(h/ho,1./3.))); // CEB-FIP Eqn. 2.1-66
   return phiRH;
}

Float64 matCEBFIPConcrete::GetBetaFcm() const
{
   Float64 fc28 = WBFL::Units::ConvertFromSysUnits(m_Fc28,WBFL::Units::Measure::MPa); // must be in MPa for CEB-FIP equations
   Float64 beta_fcm = 5.3/sqrt(fc28/10); // CEB-FIP Eqn. 2.1-67
   return beta_fcm;
}

Float64 matCEBFIPConcrete::GetBetaH() const
{
   Float64 h = GetH();
   h = WBFL::Units::ConvertFromSysUnits(h,WBFL::Units::Measure::Millimeter); // need h in millimeter
   Float64 ho = 100; // 100 millimieter

   Float64 beta_H = 150*(1 + pow(1.2*m_RelativeHumidity/100,18))*(h/ho) + 250; // CEB-FIP Eqn. 2.1-71
   beta_H = Min(beta_H,1500.0);
   return beta_H;
}

matConcreteBase* matCEBFIPConcrete::CreateClone() const
{
   return new matCEBFIPConcrete(*this);
}

void matCEBFIPConcrete::OnChanged()
{
   m_bIsValid = false;
}

void matCEBFIPConcrete::Validate() const
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

Float64 matCEBFIPConcrete::GetFr(Float64 t) const
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
Float64 matCEBFIPConcrete::ModE(Float64 fc,Float64 density) const
{
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
