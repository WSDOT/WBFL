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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\LRFDTimeDependentConcrete.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\ConcreteUtil.h>

#include <MathEx.h>
#include <Units\Units.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void lrfdLRFDTimeDependentConcrete::GetModelParameters(WBFL::Materials::ConcreteBase::CureMethod cure,lrfdLRFDTimeDependentConcrete::CementType cement,Float64* pA,Float64* pB)
{
   Float64 a[2][2] = { {WBFL::Units::ConvertToSysUnits(4.0,WBFL::Units::Measure::Day),    // Moist, Type I
                        WBFL::Units::ConvertToSysUnits(2.3,WBFL::Units::Measure::Day)} ,  // Moist, Type III
                       {WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Day),    // Steam, Type I
                        WBFL::Units::ConvertToSysUnits(0.7,WBFL::Units::Measure::Day)} }; // Steam, Type III
   Float64 b[2][2] = { {0.85,  // Moist, Type I
                        0.92}, // Moist, Type III
                        {0.95, // Steam, Type I
                        0.98} }; // Steam, Type III

   auto cure_idx = std::underlying_type<ConcreteBase::CureMethod>::type(cure);
   auto cement_idx = std::underlying_type<lrfdLRFDTimeDependentConcrete::CementType>::type(cement);
   *pA = a[cure_idx][cement_idx];
   *pB = b[cure_idx][cement_idx];
}

lrfdLRFDTimeDependentConcrete::lrfdLRFDTimeDependentConcrete(LPCTSTR name) :
   lrfdLRFDConcreteBase(name),
m_A(WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Day)),
m_Beta(0.95),
m_Fc28(0),
m_Ec28(0),
m_bUserEc(false),
m_bIsValid(false),
m_Eshu(-0.48E-3),
m_Cu(1.9),
m_ShearFrCoefficient(WBFL::Units::ConvertToSysUnits(0.24,WBFL::Units::Measure::SqrtKSI)),
m_FlexureFrCoefficient(WBFL::Units::ConvertToSysUnits(0.24,WBFL::Units::Measure::SqrtKSI)),
m_AutogenousShrinkage(0)
{
   Float64 fcMin, fpeak;
   lrfdConcreteUtil::GetPCIUHPCMinProperties(&fcMin, &m_ffc, &fpeak, &m_frr);
}

void lrfdLRFDTimeDependentConcrete::SetA(Float64 a)
{
   if ( !IsEqual(m_A,a) )
   {
      m_A = a;
      m_bIsValid = false;
   }
}

Float64 lrfdLRFDTimeDependentConcrete::GetA() const
{
   return m_A;
}

void lrfdLRFDTimeDependentConcrete::SetBeta(Float64 b)
{
   if ( !IsEqual(m_Beta,b) )
   {
      m_Beta = b;
      m_bIsValid = false;
   }
}

Float64 lrfdLRFDTimeDependentConcrete::GetBeta() const
{
   return m_Beta;
}

void lrfdLRFDTimeDependentConcrete::SetFc28(Float64 fc)
{
   if ( !IsEqual(m_Fc28,fc) )
   {
      m_Fc28 = fc;
      m_bIsValid = false;
   }
}

Float64 lrfdLRFDTimeDependentConcrete::ComputeFc28(Float64 fc,Float64 age,Float64 a,Float64 b)
{
   // solving ACI209 equation 2-1 for (f'c)28
   Float64 fc28 = (WBFL::Units::ConvertFromSysUnits(a,WBFL::Units::Measure::Day) + b*age)*fc/age;
   return fc28;
}

Float64 lrfdLRFDTimeDependentConcrete::ComputeEc28(Float64 Ec,Float64 age,Float64 a,Float64 b)
{
   // solving ACI209 equation 2-2 for (Ec)28
   Float64 Ec28 = sqrt((WBFL::Units::ConvertFromSysUnits(a,WBFL::Units::Measure::Day) + b*age)/age)*Ec;
   return Ec28;
}

void lrfdLRFDTimeDependentConcrete::ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pA,Float64* pB)
{
   // solving ACI209 equation 2-1 for Alpha and Beta
   *pB = (t1*fc2 - t2*fc1)/(fc1*(t1-t2));
   *pA = t2*(1.0 - (*pB));
}

void lrfdLRFDTimeDependentConcrete::SetFc28(Float64 fc,Float64 t)
{
   Float64 age = GetAge(t);
   ATLASSERT(!IsZero(age));
   m_Fc28 = ComputeFc28(fc,age,m_A,m_Beta);
   m_bIsValid = false;
}

Float64 lrfdLRFDTimeDependentConcrete::GetFc28() const
{
   return m_Fc28;
}

void lrfdLRFDTimeDependentConcrete::UserEc28(bool bUserEc)
{
   if ( m_bUserEc != bUserEc )
   {
      m_bUserEc = bUserEc;
      m_bIsValid = false;
   }
}

bool lrfdLRFDTimeDependentConcrete::UserEc28() const
{
   return m_bUserEc;
}

void lrfdLRFDTimeDependentConcrete::SetEc28(Float64 Ec)
{
   if ( !IsEqual(m_Ec28,Ec) )
   {
      m_Ec28 = Ec;
      m_bIsValid = false;
   }
}

Float64 lrfdLRFDTimeDependentConcrete::GetEc28() const
{
   return m_Ec28;
}

void lrfdLRFDTimeDependentConcrete::SetEc28(Float64 Ec,Float64 t)
{
   Float64 age = GetAge(t);
   ATLASSERT(!IsZero(age));
   m_Ec28 = ComputeEc28(Ec,age,m_A,m_Beta);
   m_bIsValid = false;
}

Float64 lrfdLRFDTimeDependentConcrete::GetFc(Float64 t) const
{
   Validate();

   // ACI209 Eqn 2-1
   Float64 age = GetAge(t);
   if ( age < 0 )
   {
      return 0;
   }

   Float64 fc = age*m_Fc28/(m_Alpha + m_Beta*age);
   return fc;
}

Float64 lrfdLRFDTimeDependentConcrete::GetEc(Float64 t) const
{
   Validate();

   Float64 age = GetAge(t);
   if ( age < 0 )
   {
      return 0;
   }

   Float64 Ec;
   if ( lrfdVersionMgr::SeventhEditionWith2015Interims <= lrfdVersionMgr::GetVersion() )
   {
      Ec = m_Ec*pow(age/(m_Alpha + m_Beta*age),0.33);
   }
   else
   {
      Ec = m_Ec*sqrt(age/(m_Alpha + m_Beta*age));
   }

   if ( lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
   {
      Float64 k1, k2;
      GetEcCorrectionFactors(&k1, &k2);
      Ec *= k1*k2;
   }

   return Ec;
}

Float64 lrfdLRFDTimeDependentConcrete::GetFlexureFr(Float64 t) const
{
   Float64 fc = GetFc(t);
   Float64 fr = lrfdConcreteUtil::ModRupture(fc,m_FlexureFrCoefficient);
   fr *= GetLambda();
   return fr;
}

Float64 lrfdLRFDTimeDependentConcrete::GetShearFr(Float64 t) const
{
   Float64 fc = GetFc(t);
   Float64 fr = lrfdConcreteUtil::ModRupture(fc,m_ShearFrCoefficient);
   fr *= GetLambda();
   return fr;
}

Float64 lrfdLRFDTimeDependentConcrete::GetFreeShrinkageStrain(Float64 t) const
{
   return GetFreeShrinkageStrainDetails(t)->esh;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> lrfdLRFDTimeDependentConcrete::GetFreeShrinkageStrainDetails(Float64 t) const
{
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      return GetFreeShrinkageStrainBefore2005(t);
   }
   else if ( lrfdVersionMgr::SeventhEditionWith2015Interims <= lrfdVersionMgr::GetVersion() )
   {
      return GetFreeShrinkageStrain2015(t);
   }
   else
   {
      return GetFreeShrinkageStrain2005(t);
   }
}

Float64 lrfdLRFDTimeDependentConcrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   return GetCreepCoefficientDetails(t,tla)->Ct;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> lrfdLRFDTimeDependentConcrete::GetCreepCoefficientDetails(Float64 t,Float64 tla) const
{
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      return GetCreepCoefficientBefore2005(t,tla);
   }
   else if ( lrfdVersionMgr::SeventhEditionWith2015Interims <= lrfdVersionMgr::GetVersion() )
   {
      return GetCreepCoefficient2015(t,tla);
   }
   else
   {
      return GetCreepCoefficient2005(t,tla);
   }
}

std::unique_ptr<WBFL::Materials::ConcreteBase> lrfdLRFDTimeDependentConcrete::CreateClone() const
{
   return std::make_unique<lrfdLRFDTimeDependentConcrete>(*this);
}

void lrfdLRFDTimeDependentConcrete::SetUltimateShrinkageStrain(Float64 eu)
{
   if ( m_Eshu != eu )
   {
      m_Eshu = eu;
      m_bIsValid = false;
   }
}

Float64 lrfdLRFDTimeDependentConcrete::GetUltimateShrinkageStrain() const
{
   return m_Eshu;
}

void lrfdLRFDTimeDependentConcrete::SetUltimateCreepCoefficient(Float64 cu)
{
   if ( m_Cu != cu )
   {
      m_Cu = cu;
      m_bIsValid = false;
   }
}

Float64 lrfdLRFDTimeDependentConcrete::GetUltimateCreepCoefficient() const
{
   return m_Cu;
}

void lrfdLRFDTimeDependentConcrete::SetShearModulusOfRuptureCoefficient(Float64 k)
{
   m_ShearFrCoefficient = k;
}

Float64 lrfdLRFDTimeDependentConcrete::GetShearModulusOfRuptureCoefficient() const
{
   return m_ShearFrCoefficient;
}

void lrfdLRFDTimeDependentConcrete::SetFlexureModulusOfRuptureCoefficient(Float64 k)
{
   m_FlexureFrCoefficient = k;
}

Float64 lrfdLRFDTimeDependentConcrete::GetFlexureModulusOfRuptureCoefficient() const
{
   return m_FlexureFrCoefficient;
}

Float64 lrfdLRFDTimeDependentConcrete::GetRelativeHumidityFactorCreep() const
{
   Validate();
   return m_khc;
}

Float64 lrfdLRFDTimeDependentConcrete::GetRelativeHumidityFactorShrinkage() const
{
   Validate();
   return m_khs;
}

Float64 lrfdLRFDTimeDependentConcrete::GetSizeFactorCreep(Float64 t,Float64 tla) const
{
   Validate();

   Float64 ks;
   ATLASSERT(0 < m_VS); // did you forget to set V/S ratio?
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      // LRFD 5.4.2.3.2-1
      Float64 maturity = GetAge(t) - GetAge(tla);
      Float64 a,b,c;
      Float64 x1, x2;
      Float64 vs;
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         x1 = 0.0142;
         x2 = -0.0213;
         vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Millimeter);
      }
      else
      {
         x1 = 0.36;
         x2 = -0.54;
         vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
      }

      a = maturity/(26.0*exp(x1*vs)+maturity);
      b = maturity/(45.0 + maturity);
      c = 1.80 + 1.77*exp(x2*vs);

      ks = (a/b)*(c/2.587);
   }
   else
   {
      // LRFD 2005 and later, size factor for creep and shrinkage are the same
      ks = GetSizeFactorShrinkage(-99999); // doesn't rely on time for 2005 and later
   }

   return ks;
}

Float64 lrfdLRFDTimeDependentConcrete::GetSizeFactorShrinkage(Float64 t) const
{
   Validate();

   Float64 ks;
   ATLASSERT(0 < m_VS); // did you forget to set V/S ratio?
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      // LRFD C5.4.2.3.3-1
      Float64 maturity = t - (m_CureTime + m_TimeAtCasting);
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US )
      {
         Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
         Float64 k1 = maturity/(26.0*exp(0.36*vs) + maturity);
         Float64 k2 = maturity/(45.0 + maturity);
         Float64 k3 = (1064 - 94*vs)/923;
         ks = (k1/k2)*k3;
      }
      else
      {
         Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Millimeter);
         Float64 k1 = maturity/(26.0*exp(0.0142*vs) + maturity);
         Float64 k2 = maturity/(45.0 + maturity);
         Float64 k3 = (1064 - 3.7*vs)/923;
         ks = (k1/k2)*k3;
      }
   }
   else
   {
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Millimeter);
         ks = 1.45 - 0.0051*vs; // LRFD 5.4.2.3.2-2
      }
      else
      {
         Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
         ks = 1.45 - 0.13*vs; // LRFD 5.4.2.3.2-2
      }

      if ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::ThirdEditionWith2005Interims )
      {
         ks = Max(ks,1.0);
      }
      else if ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::ThirdEditionWith2006Interims )
      {
         ks = Max(ks,0.0);
      }
      else
      {
         ks = Max(ks,1.0);
      }
   }

   return ks;
}

Float64 lrfdLRFDTimeDependentConcrete::GetConcreteStrengthFactor() const
{
   // this method is only valide for pre-2005 loss methods
   // 2005 and later, kf is a function of the concrete strength at time of loading
   ATLASSERT(lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims);
   Validate();
   return m_kf;
}

void lrfdLRFDTimeDependentConcrete::SetFirstCrackingStrength(Float64 ffc)
{
   m_ffc = ffc;
}

Float64 lrfdLRFDTimeDependentConcrete::GetFirstCrackingStrength() const
{
   return m_ffc;
}

void lrfdLRFDTimeDependentConcrete::SetPostCrackingTensileStrength(Float64 frr)
{
   m_frr = frr;
}

Float64 lrfdLRFDTimeDependentConcrete::GetPostCrackingTensileStrength() const
{
   return m_frr;
}

void lrfdLRFDTimeDependentConcrete::SetAutogenousShrinkage(Float64 as)
{
   m_AutogenousShrinkage = as;
}

Float64 lrfdLRFDTimeDependentConcrete::GetAutogenousShrinkage() const
{
   return m_AutogenousShrinkage;
}

void lrfdLRFDTimeDependentConcrete::Validate() const
{
   if ( m_bIsValid )
   {
      return;
   }

   m_Alpha = WBFL::Units::ConvertFromSysUnits(m_A,WBFL::Units::Measure::Day);

   if ( m_bUserEc )
   {
      m_Ec = m_Ec28;
   }
   else
   {
      m_Ec = ModE(m_Fc28,GetStrengthDensity());
   }

   // Relative Humidity correction factors
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      m_khc = 1.58 - m_RelativeHumidity/120;
      if ( m_RelativeHumidity < 80 )
      {
         m_khs = (140 - m_RelativeHumidity)/70;
      }
      else
      {
         m_khs = 3*(100 - m_RelativeHumidity)/70;
      }
      ATLASSERT(0 <= m_khs);
   }
   else
   {
      m_khc = 1.56 - 0.008*m_RelativeHumidity; // LRFD 5.4.2.3.2-3
      m_khs = 2.00 - 0.014*m_RelativeHumidity; // LRFD 5.4.2.3.3-2
   }

   // Size correction factor
   // ks is a function of time for some versions of the LRFD so
   // it is computed in its own methods

   m_bIsValid = true; // the call to GetFc below is going to call Validate
   // and we'll get into a recursive loop. Mark validation complete here so that doesn't
   // happen. When GetFc returns we will finish the validation.

   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      Float64 fc = GetFc(m_TimeAtCasting + 28);
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         fc = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::MPa);
         m_kf = 62.0/(42 + fc);
      }
      else
      {
         fc = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::KSI);
         m_kf = 1/(0.67 + (fc/9.0));
      }
   }
}

// Could be using lrfdConcreteUtil::ModE, except that creates a circular
// dependency between WBFLMaterial and WBFLLrfd. Neither will link
// without the other first being linked.
//
// For now, the easiest solution is to have a localized ModE method here
Float64 lrfdLRFDTimeDependentConcrete::ModE(Float64 fc,Float64 density) const
{
   Float64 Fc;          // fc in spec units
   Float64 Density;     // density in spec units
   Float64 E;           // Modulus of elasticity in spec units
   Float64 e;           // modulus of elasticity in System Units

   // Convert input to required units
   if ( lrfdVersionMgr::SeventhEditionWith2015Interims <= lrfdVersionMgr::GetVersion() )
   {
      Fc      = WBFL::Units::ConvertFromSysUnits( fc,      WBFL::Units::Measure::KSI         );
      Density = WBFL::Units::ConvertFromSysUnits( density, WBFL::Units::Measure::KipPerFeet3 );

      E = 120000.0 * Density*Density * pow( Fc, 0.33 );

      // Convert output to system units.
      e = WBFL::Units::ConvertToSysUnits( E, WBFL::Units::Measure::KSI );
   }
   else
   {
      Fc      = WBFL::Units::ConvertFromSysUnits( fc,      WBFL::Units::Measure::PSI         );
      Density = WBFL::Units::ConvertFromSysUnits( density, WBFL::Units::Measure::LbmPerFeet3 );

      // This is the same in LRFD and ACI 209
      E = 33.0 * pow( Density, 1.5 ) * sqrt( Fc );

      // Convert output to system units.
      e = WBFL::Units::ConvertToSysUnits( E, WBFL::Units::Measure::PSI );
   }

   return e;
}

Float64 lrfdLRFDTimeDependentConcrete::ComputeConcreteStrengthFactor() const
{
   Float64 fci = GetFc(m_TimeAtCasting + m_CureTime);
   fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI);
   Float64 kf = 5.0 / (1.0 + fci);
   return kf;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> lrfdLRFDTimeDependentConcrete::GetFreeShrinkageStrainBefore2005(Float64 t) const
{
   std::unique_ptr<lrfdLRFDTimeDependentConcreteShrinkageDetails> pDetails(std::make_unique<lrfdLRFDTimeDependentConcreteShrinkageDetails>());
   InitializeShrinkageDetails(t,pDetails.get());

   pDetails->khs = m_khs;

   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age < 0 )
   {
      return pDetails;
   }

   // duration of time after initial curing (time since curing stopped, this is when shrinkage begins)
   Float64 shrinkage_time = concrete_age - m_CureTime; // same as drying time
   if ( shrinkage_time <= 0 )
   {
      // if this occurs, t is in the curing period so no shrinkage occurs
      return pDetails;
   }

   Float64 ks = GetSizeFactorShrinkage(t);
   pDetails->kvs = ks;
   Float64 K = (GetCureMethod() == WBFL::Materials::ConcreteBase::CureMethod::Moist ? 35.0 : 55.0);
   Float64 eshu = (GetCureMethod() == WBFL::Materials::ConcreteBase::CureMethod::Moist ? 0.51e-3 : 0.56e-3);
   Float64 esh = -ks*m_khs*eshu*(shrinkage_time)/(K + shrinkage_time);

   pDetails->esh = esh;
   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> lrfdLRFDTimeDependentConcrete::GetFreeShrinkageStrain2005(Float64 t) const
{
   Validate();

   std::unique_ptr<lrfdLRFDTimeDependentConcreteShrinkageDetails> pDetails(std::make_unique<lrfdLRFDTimeDependentConcreteShrinkageDetails>());
   InitializeShrinkageDetails(t,pDetails.get());

   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age < 0 )
   {
      return pDetails;
   }

   // duration of time after initial curing (time since curing stopped, this is when shrinkage begins)
   Float64 shrinkage_time = concrete_age - m_CureTime;
   if ( shrinkage_time < 0 )
   {
      // if this occurs, t is in the curing period so no shrinkage occurs
      return pDetails;
   }


   //Float64 kf = ComputeConcreteStrengthFactor(m_AgeAtInitialLoading);
   Float64 kf = ComputeConcreteStrengthFactor();

   Float64 ktd;
   Float64 fci = GetFc(m_TimeAtCasting + m_AgeAtInitialLoading);
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      fci = WBFL::Units::ConvertFromSysUnits(fci,WBFL::Units::Measure::MPa);
      ktd = (shrinkage_time)/(61.0 - 0.58*fci + shrinkage_time);
   }
   else
   {
      fci = WBFL::Units::ConvertFromSysUnits(fci,WBFL::Units::Measure::KSI);
      ktd = (shrinkage_time)/(61.0 - 4.0*fci + shrinkage_time);
   }

   Float64 ks = GetSizeFactorShrinkage(t);

   Float64 k1, k2;
   GetShrinkageCorrectionFactors(&k1, &k2);
   Float64 esh = k1*k2*ks*m_khs*kf*ktd*m_Eshu;

   pDetails->kvs = ks;
   pDetails->khs = m_khs;
   pDetails->kf = kf;
   pDetails->ktd = ktd;
   pDetails->esh = esh;
   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> lrfdLRFDTimeDependentConcrete::GetFreeShrinkageStrain2015(Float64 t) const
{
   std::unique_ptr<lrfdLRFDTimeDependentConcreteShrinkageDetails> pDetails(std::make_unique<lrfdLRFDTimeDependentConcreteShrinkageDetails>());
   InitializeShrinkageDetails(t,pDetails.get());

   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age < 0 )
   {
      return pDetails;
   }

   // duration of time after initial curing (time since curing stopped, this is when shrinkage begins)
   Float64 shrinkage_time = concrete_age - m_CureTime;
   if ( shrinkage_time < 0 )
   {
      // if this occurs, t is in the curing period so no shrinkage occurs
      return pDetails;
   }

   Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
   Float64 ks = Max(1.0,1.45 - 0.13*vs);

   Float64 khs = (2.0 - 0.014*m_RelativeHumidity);
   
   Float64 kf = ComputeConcreteStrengthFactor();

   Float64 fci = GetFc(m_TimeAtCasting + m_AgeAtInitialLoading);
   fci = WBFL::Units::ConvertFromSysUnits(fci,WBFL::Units::Measure::KSI);
   Float64 ktd = (shrinkage_time)/(12*(100.0 - 4.0*fci)/(fci + 20) + shrinkage_time);

   Float64 k1, k2;
   GetShrinkageCorrectionFactors(&k1, &k2);
   Float64 esh = -k1*k2*ks*khs*kf*ktd*0.48E-3;

   pDetails->kvs = ks;
   pDetails->khs = khs;
   pDetails->kf = kf;
   pDetails->ktd = ktd;
   pDetails->esh = esh;
   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> lrfdLRFDTimeDependentConcrete::GetCreepCoefficientBefore2005(Float64 t,Float64 tla) const
{
   std::unique_ptr<lrfdLRFDTimeDependentConcreteCreepDetails> pDetails(std::make_unique<lrfdLRFDTimeDependentConcreteCreepDetails>());
   InitializeCreepDetails(t,tla,pDetails.get());

   Float64 age = pDetails->age;
   Float64 age_at_loading = pDetails->age_at_loading;
   Float64 maturity = age - age_at_loading;
   if ( ::IsLE(age,0.0) || ::IsLE(age_at_loading,0.0) || ::IsLE(maturity,0.0) )
   {
      return pDetails;
   }

   Float64 kc = GetSizeFactorCreep(t,tla);

   Float64 kla = pow(age_at_loading,-0.118);

   Float64 tx = pow(maturity,0.6);
   Float64 kt = tx/(10 + tx);

   Float64 Y = 3.5*kc*m_kf*m_khc*kla*kt;

   //pDetails->fci = GetFc(m_TimeAtCasting + 28);
   pDetails->fci = GetFc(m_TimeAtCasting + m_CureTime);
   pDetails->kc = kc;
   pDetails->kf = m_kf;
   pDetails->Ct = Y;

   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> lrfdLRFDTimeDependentConcrete::GetCreepCoefficient2005(Float64 t,Float64 tla) const
{
   Validate();

   std::unique_ptr<lrfdLRFDTimeDependentConcreteCreepDetails> pDetails(std::make_unique<lrfdLRFDTimeDependentConcreteCreepDetails>());
   InitializeCreepDetails(t,tla,pDetails.get());

   Float64 age = pDetails->age;
   Float64 age_at_loading = pDetails->age_at_loading;
   Float64 maturity = age - age_at_loading;
   if ( ::IsLE(age,0.0) || ::IsLE(age_at_loading,0.0) || ::IsLT(maturity,0.0) )
   {
      return pDetails;
   }

   //Float64 kf = ComputeConcreteStrengthFactor(age_at_loading);
   Float64 kf = ComputeConcreteStrengthFactor();

   //Float64 fci = GetFc(m_TimeAtCasting + age_at_loading);
   Float64 fci = GetFc(m_TimeAtCasting + m_CureTime);
   pDetails->fci = fci;

   Float64 ktd;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::MPa);
      ktd = (maturity)/(61.0 - 0.58*fci + maturity);
   }
   else
   {
      fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI);
      ktd = (maturity)/(61.0 - 4.0*fci + maturity);
   }

   
   Float64 ks = GetSizeFactorCreep(t,tla);
   Float64 ti = age_at_loading;
   Float64 k1, k2;
   GetCreepCorrectionFactors(&k1, &k2);
   Float64 Y = k1*k2*m_Cu*ks*m_khc*kf*ktd*pow(ti,-0.118);

   pDetails->kvs = ks;
   pDetails->khc = m_khc;
   pDetails->kf = kf;
   pDetails->ktd = ktd;
   pDetails->Ct = Y;

   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> lrfdLRFDTimeDependentConcrete::GetCreepCoefficient2015(Float64 t,Float64 tla) const
{
   std::unique_ptr<lrfdLRFDTimeDependentConcreteCreepDetails> pDetails(std::make_unique<lrfdLRFDTimeDependentConcreteCreepDetails>());
   InitializeCreepDetails(t,tla,pDetails.get());

   Float64 age = pDetails->age;
   Float64 age_at_loading = pDetails->age_at_loading;
   Float64 maturity = age - age_at_loading;
   if ( ::IsLE(age,0.0) || ::IsLE(age_at_loading,0.0) || ::IsLT(maturity,0.0) )
   {
      return pDetails;
   }

   Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
   Float64 ks = Max(1.0,1.45 - 0.13*vs);

   Float64 khc = (1.56 - 0.008*m_RelativeHumidity);
   
   //Float64 kf = ComputeConcreteStrengthFactor(age_at_loading);
   Float64 kf = ComputeConcreteStrengthFactor();

   //Float64 fci = GetFc(m_TimeAtCasting + age_at_loading);
   Float64 fci = GetFc(m_TimeAtCasting + m_CureTime);
   pDetails->fci = fci;
   fci = WBFL::Units::ConvertFromSysUnits(fci,WBFL::Units::Measure::KSI);

   Float64 ktd = (maturity)/(12*(100.0 - 4.0*fci)/(fci + 20) + maturity);

   Float64 ti = age_at_loading;
   Float64 k1, k2;
   GetCreepCorrectionFactors(&k1, &k2);
   Float64 Y = 1.9*k1*k2*ks*khc*kf*ktd*pow(ti,-0.118);

   pDetails->kvs = ks;
   pDetails->khc = m_khc;
   pDetails->kf = kf;
   pDetails->ktd = ktd;
   pDetails->Ct = Y;

   return pDetails;
}
