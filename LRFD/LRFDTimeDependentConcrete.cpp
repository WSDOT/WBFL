///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <LRFD\XCreepCoefficient.h>
#include <System\XProgrammingError.h>

using namespace WBFL::LRFD;

void LRFDTimeDependentConcrete::GetModelParameters(WBFL::Materials::CuringType cure,WBFL::Materials::CementType cement,Float64* pA,Float64* pB)
{
   static Float64 a[2][2] = { {WBFL::Units::ConvertToSysUnits(4.0,WBFL::Units::Measure::Day),    // Moist, Type I
                               WBFL::Units::ConvertToSysUnits(2.3,WBFL::Units::Measure::Day)} ,  // Moist, Type III
                              {WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Day),    // Steam, Type I
                               WBFL::Units::ConvertToSysUnits(0.7,WBFL::Units::Measure::Day)} }; // Steam, Type III
   static Float64 b[2][2] = { {0.85,  // Moist, Type I
                               0.92}, // Moist, Type III
                              {0.95, // Steam, Type I
                               0.98} }; // Steam, Type III

   *pA = a[+cure][+cement];
   *pB = b[+cure][+cement];
}

LRFDTimeDependentConcrete::LRFDTimeDependentConcrete(LPCTSTR name) :
   LRFDConcreteBase(name),
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
m_AutogenousShrinkage(0),
m_alpha_u(0.85),
m_ecu(0),
m_bExperimental_ecu(false),
m_etcr(0),
m_ftcri(0),
m_ftcr(0),
m_ftloc(0),
m_etloc(0),
m_gamma_u(1.0)
{
   Float64 fcMin, fpeak;
   ConcreteUtil::GetPCIUHPCMinProperties(&fcMin, &m_ffc, &fpeak, &m_frr);
}

void LRFDTimeDependentConcrete::SetA(Float64 a)
{
   if ( !IsEqual(m_A,a) )
   {
      m_A = a;
      m_bIsValid = false;
   }
}

Float64 LRFDTimeDependentConcrete::GetA() const
{
   return m_A;
}

void LRFDTimeDependentConcrete::SetBeta(Float64 b)
{
   if ( !IsEqual(m_Beta,b) )
   {
      m_Beta = b;
      m_bIsValid = false;
   }
}

Float64 LRFDTimeDependentConcrete::GetBeta() const
{
   return m_Beta;
}

void LRFDTimeDependentConcrete::SetFc28(Float64 fc)
{
   if ( !IsEqual(m_Fc28,fc) )
   {
      m_Fc28 = fc;
      m_bIsValid = false;
   }
}

Float64 LRFDTimeDependentConcrete::ComputeFc28(Float64 fc,Float64 age,Float64 a,Float64 b)
{
   // solving ACI209 equation 2-1 for (f'c)28
   Float64 fc28 = (WBFL::Units::ConvertFromSysUnits(a,WBFL::Units::Measure::Day) + b*age)*fc/age;
   return fc28;
}

Float64 LRFDTimeDependentConcrete::ComputeEc28(Float64 Ec,Float64 age,Float64 a,Float64 b)
{
   // solving ACI209 equation 2-2 for (Ec)28
   Float64 Ec28 = sqrt((WBFL::Units::ConvertFromSysUnits(a,WBFL::Units::Measure::Day) + b*age)/age)*Ec;
   return Ec28;
}

void LRFDTimeDependentConcrete::ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pA,Float64* pB)
{
   // solving ACI209 equation 2-1 for Alpha and Beta
   *pB = (t1*fc2 - t2*fc1)/(fc1*(t1-t2));
   *pA = t2*(1.0 - (*pB));
}

void LRFDTimeDependentConcrete::SetFc28(Float64 fc,Float64 t)
{
   Float64 age = GetAge(t);
   CHECK(!IsZero(age));
   m_Fc28 = ComputeFc28(fc,age,m_A,m_Beta);
   m_bIsValid = false;
}

Float64 LRFDTimeDependentConcrete::GetFc28() const
{
   return m_Fc28;
}

void LRFDTimeDependentConcrete::UserEc28(bool bUserEc)
{
   if ( m_bUserEc != bUserEc )
   {
      m_bUserEc = bUserEc;
      m_bIsValid = false;
   }
}

bool LRFDTimeDependentConcrete::UserEc28() const
{
   return m_bUserEc;
}

void LRFDTimeDependentConcrete::SetEc28(Float64 Ec)
{
   if ( !IsEqual(m_Ec28,Ec) )
   {
      m_Ec28 = Ec;
      m_bIsValid = false;
   }
}

Float64 LRFDTimeDependentConcrete::GetEc28() const
{
   return m_Ec28;
}

void LRFDTimeDependentConcrete::SetEc28(Float64 Ec,Float64 t)
{
   Float64 age = GetAge(t);
   CHECK(!IsZero(age));
   m_Ec28 = ComputeEc28(Ec,age,m_A,m_Beta);
   m_bIsValid = false;
}

Float64 LRFDTimeDependentConcrete::GetFc(Float64 t) const
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

Float64 LRFDTimeDependentConcrete::GetEc(Float64 t) const
{
   Validate();

   Float64 age = GetAge(t);
   if ( age < 0 )
   {
      return 0;
   }

   Float64 Ec;
   if ( LRFDVersionMgr::Version::SeventhEditionWith2015Interims <= LRFDVersionMgr::GetVersion() )
   {
      Ec = m_Ec*pow(age/(m_Alpha + m_Beta*age),0.33);
   }
   else
   {
      Ec = m_Ec*sqrt(age/(m_Alpha + m_Beta*age));
   }

   if ( LRFDVersionMgr::Version::ThirdEditionWith2005Interims <= LRFDVersionMgr::GetVersion() )
   {
      Float64 k1, k2;
      GetEcCorrectionFactors(&k1, &k2);
      Ec *= k1*k2;
   }

   return Ec;
}

Float64 LRFDTimeDependentConcrete::GetFlexureFr(Float64 t) const
{
   Float64 fc = GetFc(t);
   Float64 fr = ConcreteUtil::ModRupture(fc,m_FlexureFrCoefficient);
   fr *= GetLambda();
   return fr;
}

Float64 LRFDTimeDependentConcrete::GetShearFr(Float64 t) const
{
   Float64 fc = GetFc(t);
   Float64 fr = ConcreteUtil::ModRupture(fc,m_ShearFrCoefficient);
   fr *= GetLambda();
   return fr;
}

Float64 LRFDTimeDependentConcrete::GetFreeShrinkageStrain(Float64 t) const
{
   return GetFreeShrinkageStrainDetails(t)->esh;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDTimeDependentConcrete::GetFreeShrinkageStrainDetails(Float64 t) const
{
   if ( LRFDVersionMgr::GetVersion() < LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
   {
      return GetFreeShrinkageStrainBefore2005(t);
   }
   else if ( LRFDVersionMgr::Version::SeventhEditionWith2015Interims <= LRFDVersionMgr::GetVersion() )
   {
      return GetFreeShrinkageStrain2015(t);
   }
   else
   {
      return GetFreeShrinkageStrain2005(t);
   }
}

Float64 LRFDTimeDependentConcrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   return GetCreepCoefficientDetails(t,tla)->Ct;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDTimeDependentConcrete::GetCreepCoefficientDetails(Float64 t,Float64 tla) const
{
   if ( LRFDVersionMgr::GetVersion() < LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
   {
      return GetCreepCoefficientBefore2005(t,tla);
   }
   else if ( LRFDVersionMgr::Version::SeventhEditionWith2015Interims <= LRFDVersionMgr::GetVersion() )
   {
      return GetCreepCoefficient2015(t,tla);
   }
   else
   {
      return GetCreepCoefficient2005(t,tla);
   }
}

std::unique_ptr<WBFL::Materials::ConcreteBase> LRFDTimeDependentConcrete::CreateClone() const
{
   return std::make_unique<LRFDTimeDependentConcrete>(*this);
}

void LRFDTimeDependentConcrete::SetUltimateShrinkageStrain(Float64 eu)
{
   if ( m_Eshu != eu )
   {
      m_Eshu = eu;
      m_bIsValid = false;
   }
}

Float64 LRFDTimeDependentConcrete::GetUltimateShrinkageStrain() const
{
   return m_Eshu;
}

void LRFDTimeDependentConcrete::SetUltimateCreepCoefficient(Float64 cu)
{
   if ( m_Cu != cu )
   {
      m_Cu = cu;
      m_bIsValid = false;
   }
}

Float64 LRFDTimeDependentConcrete::GetUltimateCreepCoefficient() const
{
   return m_Cu;
}

void LRFDTimeDependentConcrete::SetShearModulusOfRuptureCoefficient(Float64 k)
{
   m_ShearFrCoefficient = k;
}

Float64 LRFDTimeDependentConcrete::GetShearModulusOfRuptureCoefficient() const
{
   return m_ShearFrCoefficient;
}

void LRFDTimeDependentConcrete::SetFlexureModulusOfRuptureCoefficient(Float64 k)
{
   m_FlexureFrCoefficient = k;
}

Float64 LRFDTimeDependentConcrete::GetFlexureModulusOfRuptureCoefficient() const
{
   return m_FlexureFrCoefficient;
}

Float64 LRFDTimeDependentConcrete::GetRelativeHumidityFactorCreep() const
{
   Validate();
   return m_khc;
}

Float64 LRFDTimeDependentConcrete::GetRelativeHumidityFactorShrinkage() const
{
   Validate();
   return m_khs;
}

Float64 LRFDTimeDependentConcrete::GetSizeFactorCreep(Float64 t,Float64 tla) const
{
   Validate();

   Float64 ks;
   CHECK(0 < m_VS); // did you forget to set V/S ratio?
   if ( LRFDVersionMgr::GetVersion() < LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
   {
      // LRFD 5.4.2.3.2-1
      Float64 maturity = GetAge(t) - GetAge(tla);
      Float64 a,b,c;
      Float64 x1, x2;
      Float64 vs;
      if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
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

Float64 LRFDTimeDependentConcrete::GetSizeFactorShrinkage(Float64 t) const
{
   Validate();

   Float64 ks;
   CHECK(0 < m_VS); // did you forget to set V/S ratio?
   if ( LRFDVersionMgr::GetVersion() < LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
   {
      // LRFD C5.4.2.3.3-1
      Float64 maturity = t - (m_CureTime + m_TimeAtCasting);
      if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::US )
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
      if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
      {
         Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Millimeter);
         ks = 1.45 - 0.0051*vs; // LRFD 5.4.2.3.2-2
      }
      else
      {
         Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
         ks = 1.45 - 0.13*vs; // LRFD 5.4.2.3.2-2
      }

      if ( LRFDVersionMgr::GetVersion() == LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
      {
         ks = Max(ks,1.0);
      }
      else if ( LRFDVersionMgr::GetVersion() == LRFDVersionMgr::Version::ThirdEditionWith2006Interims )
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

Float64 LRFDTimeDependentConcrete::GetConcreteStrengthFactor() const
{
   // this method is only valid for pre-2005 loss methods
   // 2005 and later, kf is a function of the concrete strength at time of loading
   if (LRFDVersionMgr::Version::ThirdEditionWith2005Interims <= LRFDVersionMgr::GetVersion())
   {
      WBFL_LRFD_THROW(XCreepCoefficient, Specification);
   }

   Validate();
   return m_kf;
}

void LRFDTimeDependentConcrete::SetFirstCrackingStrength(Float64 ffc)
{
   m_ffc = ffc;
}

Float64 LRFDTimeDependentConcrete::GetFirstCrackingStrength() const
{
   return m_ffc;
}

void LRFDTimeDependentConcrete::SetPostCrackingTensileStrength(Float64 frr)
{
   m_frr = frr;
}

Float64 LRFDTimeDependentConcrete::GetPostCrackingTensileStrength() const
{
   return m_frr;
}

void LRFDTimeDependentConcrete::SetAutogenousShrinkage(Float64 as)
{
   m_AutogenousShrinkage = as;
}

Float64 LRFDTimeDependentConcrete::GetAutogenousShrinkage() const
{
   return m_AutogenousShrinkage;
}

void LRFDTimeDependentConcrete::SetCompressionResponseReductionFactor(Float64 alpha_u)
{
   m_alpha_u = alpha_u;
}

Float64 LRFDTimeDependentConcrete::GetCompressionResponseReductionFactor() const
{
   return m_alpha_u;
}

void LRFDTimeDependentConcrete::SetCompressiveStrainLimit(Float64 ecu)
{
   // if this value is explicitly set, assume it is an experimentally derived value
   // from ASTM C1856 per GS 1.4.2.4.2
   m_ecu = ecu;
   m_bExperimental_ecu = true; 
}

void LRFDTimeDependentConcrete::SetElasticTensileStrainLimit(Float64 etcr)
{
   m_etcr = etcr;
}

Float64 LRFDTimeDependentConcrete::GetElasticTensileStrainLimit() const
{
   return m_etcr;
}

void LRFDTimeDependentConcrete::SetInitialEffectiveCrackingStrength(Float64 ft_cri)
{
   m_ftcri = ft_cri;
}

Float64 LRFDTimeDependentConcrete::GetInitialEffectiveCrackingStrength() const
{
   return m_ftcri;
}

void LRFDTimeDependentConcrete::SetDesignEffectiveCrackingStrength(Float64 ft_cr)
{
   m_ftcr = ft_cr;
}

Float64 LRFDTimeDependentConcrete::GetDesignEffectiveCrackingStrength() const
{
   return m_ftcr;
}

void LRFDTimeDependentConcrete::SetCrackLocalizationStrength(Float64 ft_loc)
{
   m_ftloc = ft_loc;
}

Float64 LRFDTimeDependentConcrete::GetCrackLocalizationStrength() const
{
   return m_ftloc;
}

void LRFDTimeDependentConcrete::SetCrackLocalizationStrain(Float64 et_loc)
{
   m_etloc = et_loc;
}

Float64 LRFDTimeDependentConcrete::GetCrackLocalizationStrain() const
{
   return m_etloc;
}

void LRFDTimeDependentConcrete::SetFiberOrientationReductionFactor(Float64 gamma_u)
{
   m_gamma_u = gamma_u;
}

Float64 LRFDTimeDependentConcrete::GetFiberOrientationReductionFactor() const
{
   return m_gamma_u;
}

Float64 LRFDTimeDependentConcrete::GetElasticCompressiveStrainLimit() const
{
   Float64 fc = GetFc28();
   Float64 Ec = GetEc28();
   Float64 ecp = -1.0 * m_alpha_u * fc / Ec;
   return ecp;
}

Float64 LRFDTimeDependentConcrete::GetCompressiveStrainLimit(bool* pbIsExperimental) const
{
   if (pbIsExperimental)
   {
      *pbIsExperimental = m_bExperimental_ecu;
   }

   if (m_bExperimental_ecu)
   {
      return m_ecu;
   }
   else
   {
      Float64 ecp = GetElasticCompressiveStrainLimit();
      return Min(ecp, -0.0035); // See GS 1.4.2.4.2
   }
}

void LRFDTimeDependentConcrete::Validate() const
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
   if ( LRFDVersionMgr::GetVersion() < LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
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
      CHECK(0 <= m_khs);
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

   if ( LRFDVersionMgr::GetVersion() < LRFDVersionMgr::Version::ThirdEditionWith2005Interims )
   {
      Float64 fc = GetFc(m_TimeAtCasting + 28);
      if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
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

// Could be using WBFL::LRFD::ConcreteUtil::ModE, except that creates a circular
// dependency between WBFLMaterial and WBFLLrfd. Neither will link
// without the other first being linked.
//
// For now, the easiest solution is to have a localized ModE method here
Float64 LRFDTimeDependentConcrete::ModE(Float64 fc,Float64 density) const
{
   Float64 Fc;          // fc in spec units
   Float64 Density;     // density in spec units
   Float64 E;           // Modulus of elasticity in spec units
   Float64 e;           // modulus of elasticity in System Units

   // Convert input to required units
   if ( LRFDVersionMgr::Version::SeventhEditionWith2015Interims <= LRFDVersionMgr::GetVersion() )
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

Float64 LRFDTimeDependentConcrete::ComputeConcreteStrengthFactor() const
{
   Float64 fci = GetFc(m_TimeAtCasting + m_CureTime);
   fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI);
   Float64 kf = 5.0 / (1.0 + fci);
   return kf;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDTimeDependentConcrete::GetFreeShrinkageStrainBefore2005(Float64 t) const
{
   std::unique_ptr<LRFDTimeDependentConcreteShrinkageDetails> pDetails(std::make_unique<LRFDTimeDependentConcreteShrinkageDetails>());
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
   Float64 K = (GetCuringType() == WBFL::Materials::CuringType::Moist ? 35.0 : 55.0);
   Float64 eshu = (GetCuringType() == WBFL::Materials::CuringType::Moist ? 0.51e-3 : 0.56e-3);
   Float64 esh = -ks*m_khs*eshu*(shrinkage_time)/(K + shrinkage_time);

   pDetails->esh = esh;
   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDTimeDependentConcrete::GetFreeShrinkageStrain2005(Float64 t) const
{
   Validate();

   std::unique_ptr<LRFDTimeDependentConcreteShrinkageDetails> pDetails(std::make_unique<LRFDTimeDependentConcreteShrinkageDetails>());
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
   if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
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

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDTimeDependentConcrete::GetFreeShrinkageStrain2015(Float64 t) const
{
   std::unique_ptr<LRFDTimeDependentConcreteShrinkageDetails> pDetails(std::make_unique<LRFDTimeDependentConcreteShrinkageDetails>());
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

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDTimeDependentConcrete::GetCreepCoefficientBefore2005(Float64 t,Float64 tla) const
{
   std::unique_ptr<LRFDTimeDependentConcreteCreepDetails> pDetails(std::make_unique<LRFDTimeDependentConcreteCreepDetails>());
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

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDTimeDependentConcrete::GetCreepCoefficient2005(Float64 t,Float64 tla) const
{
   Validate();

   std::unique_ptr<LRFDTimeDependentConcreteCreepDetails> pDetails(std::make_unique<LRFDTimeDependentConcreteCreepDetails>());
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
   if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
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

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDTimeDependentConcrete::GetCreepCoefficient2015(Float64 t,Float64 tla) const
{
   std::unique_ptr<LRFDTimeDependentConcreteCreepDetails> pDetails(std::make_unique<LRFDTimeDependentConcreteCreepDetails>());
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
