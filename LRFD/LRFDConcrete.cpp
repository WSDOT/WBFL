///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Lrfd\LRFDConcrete.h>
#include <Lrfd/BDSManager.h>

using namespace WBFL::LRFD;



LRFDConcrete::LRFDConcrete(LPCTSTR name) :
   LRFDConcreteBase(name),
m_StartTime(0),
m_StepTime(0),
m_bUse90DayConcrete(false)
{
}

LRFDConcrete::LRFDConcrete(const WBFL::Materials::SimpleConcrete& initial, const WBFL::Materials::SimpleConcrete & final, Float64 startTime, Float64 stepTime, LPCTSTR name) :
   LRFDConcreteBase(name),
   m_StartTime(startTime), m_StepTime(stepTime)
{
   SetConcreteModels(initial, final);
}

void LRFDConcrete::SetConcreteModels(const WBFL::Materials::SimpleConcrete& initial,const WBFL::Materials::SimpleConcrete & final)
{
   m_InitialConcrete = initial;
   m_FinalConcrete   = final;
   m_90DayConcrete = final;

   CHECK(IsEqual(m_InitialConcrete.GetLambda(),m_FinalConcrete.GetLambda()));

   SetType(m_FinalConcrete.GetType());
   SetStrengthDensity(m_FinalConcrete.GetDensity());
   SetWeightDensity(m_FinalConcrete.GetDensityForWeight());
   HasAggSplittingStrength(m_FinalConcrete.HasAggSplittingStrength());
   SetAggSplittingStrength(m_FinalConcrete.GetAggSplittingStrength());
   SetMaxAggregateSize(m_FinalConcrete.GetMaxAggregateSize());
   SetLambda(m_FinalConcrete.GetLambda());
}

const WBFL::Materials::SimpleConcrete& LRFDConcrete::GetInitialConcreteModel() const
{
   return m_InitialConcrete;
}

const WBFL::Materials::SimpleConcrete& LRFDConcrete::GetFinalConcreteModel() const
{
   return m_FinalConcrete;
}

void LRFDConcrete::SetLambda(Float64 lambda)
{
   __super::SetLambda(lambda);
   m_InitialConcrete.SetLambda(lambda);
   m_FinalConcrete.SetLambda(lambda);
}

Float64 LRFDConcrete::GetLambda() const
{
   CHECK(IsEqual(m_InitialConcrete.GetLambda(),m_FinalConcrete.GetLambda()));
   CHECK(IsEqual(m_InitialConcrete.GetLambda(), __super::GetLambda()));
   return __super::GetLambda();
}

void LRFDConcrete::SetFirstCrackingStrength(Float64 ffc)
{
   m_InitialConcrete.SetFirstCrackingStrength(ffc);
   m_FinalConcrete.SetFirstCrackingStrength(ffc);
}

Float64 LRFDConcrete::GetFirstCrackingStrength() const
{
   CHECK(IsEqual(m_InitialConcrete.GetFirstCrackingStrength(), m_FinalConcrete.GetFirstCrackingStrength()));
   return m_FinalConcrete.GetFirstCrackingStrength();
}

void LRFDConcrete::SetPostCrackingTensileStrength(Float64 frr)
{
   m_InitialConcrete.SetPostCrackingTensileStrength(frr);
   m_FinalConcrete.SetPostCrackingTensileStrength(frr);
}

Float64 LRFDConcrete::GetPostCrackingTensileStrength() const
{
   CHECK(IsEqual(m_InitialConcrete.GetPostCrackingTensileStrength(), m_FinalConcrete.GetPostCrackingTensileStrength()));
   return m_FinalConcrete.GetPostCrackingTensileStrength();
}

void LRFDConcrete::SetAutogenousShrinkage(Float64 as)
{
   m_InitialConcrete.SetAutogenousShrinkage(as);
   m_FinalConcrete.SetAutogenousShrinkage(as);
}

Float64 LRFDConcrete::GetAutogenousShrinkage() const
{
   CHECK(IsEqual(m_InitialConcrete.GetPostCrackingTensileStrength(), m_FinalConcrete.GetPostCrackingTensileStrength()));
   return m_FinalConcrete.GetAutogenousShrinkage();
}

void LRFDConcrete::SetCompressionResponseReductionFactor(Float64 alpha_u)
{
   m_InitialConcrete.SetCompressionResponseReductionFactor(alpha_u);
   m_FinalConcrete.SetCompressionResponseReductionFactor(alpha_u);
}

Float64 LRFDConcrete::GetCompressionResponseReductionFactor() const
{
   CHECK(IsEqual(m_InitialConcrete.GetCompressionResponseReductionFactor(), m_FinalConcrete.GetCompressionResponseReductionFactor()));
   return m_FinalConcrete.GetCompressionResponseReductionFactor();
}

void LRFDConcrete::SetCompressiveStrainLimit(Float64 ecu)
{
   m_InitialConcrete.SetCompressiveStrainLimit(ecu);
   m_FinalConcrete.SetCompressiveStrainLimit(ecu);
}

Float64 LRFDConcrete::GetCompressiveStrainLimit(bool* pbIsExperimental) const
{
   CHECK(IsEqual(m_InitialConcrete.GetCompressiveStrainLimit(pbIsExperimental), m_FinalConcrete.GetCompressiveStrainLimit(pbIsExperimental)));
   return m_FinalConcrete.GetCompressiveStrainLimit(pbIsExperimental);
}

void LRFDConcrete::SetElasticTensileStrainLimit(Float64 etcr)
{
   m_InitialConcrete.SetElasticTensileStrainLimit(etcr);
   m_FinalConcrete.SetElasticTensileStrainLimit(etcr);
}

Float64 LRFDConcrete::GetElasticTensileStrainLimit() const
{
   CHECK(IsEqual(m_InitialConcrete.GetElasticTensileStrainLimit(), m_FinalConcrete.GetElasticTensileStrainLimit()));
   return m_FinalConcrete.GetElasticTensileStrainLimit();
}

void LRFDConcrete::SetInitialEffectiveCrackingStrength(Float64 ft_cri)
{
   m_InitialConcrete.SetInitialEffectiveCrackingStrength(ft_cri);
   m_FinalConcrete.SetInitialEffectiveCrackingStrength(ft_cri);
}

Float64 LRFDConcrete::GetInitialEffectiveCrackingStrength() const
{
   CHECK(IsEqual(m_InitialConcrete.GetInitialEffectiveCrackingStrength(), m_FinalConcrete.GetInitialEffectiveCrackingStrength()));
   return m_FinalConcrete.GetInitialEffectiveCrackingStrength();
}

void LRFDConcrete::SetDesignEffectiveCrackingStrength(Float64 ft_cr)
{
   m_InitialConcrete.SetDesignEffectiveCrackingStrength(ft_cr);
   m_FinalConcrete.SetDesignEffectiveCrackingStrength(ft_cr);
}

Float64 LRFDConcrete::GetDesignEffectiveCrackingStrength() const
{
   CHECK(IsEqual(m_InitialConcrete.GetDesignEffectiveCrackingStrength(), m_FinalConcrete.GetDesignEffectiveCrackingStrength()));
   return m_FinalConcrete.GetDesignEffectiveCrackingStrength();
}

void LRFDConcrete::SetCrackLocalizationStrength(Float64 ft_loc)
{
   m_InitialConcrete.SetCrackLocalizationStrength(ft_loc);
   m_FinalConcrete.SetCrackLocalizationStrength(ft_loc);
}

Float64 LRFDConcrete::GetCrackLocalizationStrength() const
{
   CHECK(IsEqual(m_InitialConcrete.GetCrackLocalizationStrength(), m_FinalConcrete.GetCrackLocalizationStrength()));
   return m_FinalConcrete.GetCrackLocalizationStrength();
}

void LRFDConcrete::SetCrackLocalizationStrain(Float64 et_loc)
{
   m_InitialConcrete.SetCrackLocalizationStrain(et_loc);
   m_FinalConcrete.SetCrackLocalizationStrain(et_loc);
}

Float64 LRFDConcrete::GetCrackLocalizationStrain() const
{
   CHECK(IsEqual(m_InitialConcrete.GetCrackLocalizationStrain(), m_FinalConcrete.GetCrackLocalizationStrain()));
   return m_FinalConcrete.GetCrackLocalizationStrain();
}

void LRFDConcrete::SetFiberOrientationReductionFactor(Float64 gamma_u)
{
   m_InitialConcrete.SetFiberOrientationReductionFactor(gamma_u);
   m_FinalConcrete.SetFiberOrientationReductionFactor(gamma_u);
}

Float64 LRFDConcrete::GetFiberOrientationReductionFactor() const
{
   CHECK(IsEqual(m_InitialConcrete.GetFiberOrientationReductionFactor(), m_FinalConcrete.GetFiberOrientationReductionFactor()));
   return m_FinalConcrete.GetFiberOrientationReductionFactor();
}

Float64 LRFDConcrete::GetElasticCompressiveStrainLimit() const
{
   return m_FinalConcrete.GetElasticCompressiveStrainLimit();
}

void LRFDConcrete::SetStartTime(Float64 t)
{
   m_StartTime = t;
}

Float64 LRFDConcrete::GetStartTime() const
{
   return m_StartTime;
}

void LRFDConcrete::SetStepTime(Float64 t)
{
   m_StepTime = t;
}

Float64 LRFDConcrete::GetStepTime() const
{
   return m_StepTime;
}

void LRFDConcrete::Use90DayStrength(const WBFL::Materials::SimpleConcrete& concrete90)
{
   m_bUse90DayConcrete = true;
   m_90DayConcrete = concrete90;
}

bool LRFDConcrete::Use90DayStrength() const
{
   return m_bUse90DayConcrete;
}

const WBFL::Materials::SimpleConcrete& LRFDConcrete::Get90DayConcreteModel() const
{
   return m_90DayConcrete;
}

Float64 LRFDConcrete::GetFc(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   if ( t < m_StepTime )
   {
      return m_InitialConcrete.GetFc();
   }
   else
   {
      if (Use90DayConcrete(t))
      {
         return m_90DayConcrete.GetFc();
      }
      else
      {
         return m_FinalConcrete.GetFc();
      }
   }
}

Float64 LRFDConcrete::GetEc(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   Float64 Ec;
   if ( t < m_StepTime )
   {
      Ec = m_InitialConcrete.GetE();
   }
   else
   {
      if (Use90DayConcrete(t))
      {
         Ec = m_90DayConcrete.GetE();
      }
      else
      {
         Ec = m_FinalConcrete.GetE();
      }
   }

   if ( BDSManager::GetEdition() < BDSManager::Edition::ThirdEditionWith2005Interims )
   {
      Float64 k1, k2;
      GetEcCorrectionFactors(&k1, &k2);
      Ec *= k1*k2;
   }

   return Ec;
}

Float64 LRFDConcrete::GetShearFr(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   if ( t < m_StepTime )
   {
      return m_InitialConcrete.GetShearFr();
   }
   else
   {
      if (Use90DayConcrete(t))
      {
         return m_90DayConcrete.GetShearFr();
      }
      else
      {
         return m_FinalConcrete.GetShearFr();
      }
   }
}

Float64 LRFDConcrete::GetFlexureFr(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   if ( t < m_StepTime )
   {
      return m_InitialConcrete.GetFlexureFr();
   }
   else
   {
      if (Use90DayConcrete(t))
      {
         return m_90DayConcrete.GetFlexureFr();
      }
      else
      {
         return m_FinalConcrete.GetFlexureFr();
      }
   }
}


Float64 LRFDConcrete::GetFreeShrinkageStrain(Float64 t) const
{
   return GetFreeShrinkageStrainDetails(t)->esh;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDConcrete::GetFreeShrinkageStrainDetails(Float64 t) const
{
   if ( BDSManager::GetEdition() < BDSManager::Edition::ThirdEditionWith2005Interims )
   {
      return GetFreeShrinkageStrainBefore2005(t);
   }
   else if ( BDSManager::Edition::SeventhEditionWith2015Interims <= BDSManager::GetEdition() )
   {
      return GetFreeShrinkageStrain2015(t);
   }
   else
   {
      return GetFreeShrinkageStrain2005(t);
   }
}

Float64 LRFDConcrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   return GetCreepCoefficientDetails(t, tla)->Ct;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDConcrete::GetCreepCoefficientDetails(Float64 t,Float64 tla) const
{
   if ( BDSManager::GetEdition() < BDSManager::Edition::ThirdEditionWith2005Interims )
   {
      return GetCreepCoefficientBefore2005(t,tla);
   }
   else if ( BDSManager::Edition::SeventhEditionWith2015Interims <= BDSManager::GetEdition() )
   {
      return GetCreepCoefficient2015(t,tla);
   }
   else
   {
      return GetCreepCoefficient2005(t,tla);
   }
}

std::unique_ptr<WBFL::Materials::ConcreteBase> LRFDConcrete::CreateClone() const
{
   return std::make_unique<LRFDConcrete>(*this);
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDConcrete::GetFreeShrinkageStrainBefore2005(Float64 t) const
{
   std::unique_ptr<LRFDConcreteShrinkageDetails> pDetails(std::make_unique<LRFDConcreteShrinkageDetails>());
   InitializeShrinkageDetails(t,pDetails.get());

   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age <= 0 )
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

   Float64 ks = 1.0;
   if ( BDSManager::GetUnits() == BDSManager::Units::SI )
   {
      Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Millimeter);
      Float64 k1 = shrinkage_time/(26.0*exp(0.36*vs) + shrinkage_time);
      Float64 k2 = shrinkage_time/(45.0 + shrinkage_time);
      Float64 k3 = (1064 - 94*vs)/923;
      ks = (k1/k2)*k3;
   }
   else
   {
      Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
      Float64 k1 = shrinkage_time/(26.0*exp(0.0142*vs) + shrinkage_time);
      Float64 k2 = shrinkage_time/(45.0 + shrinkage_time);
      Float64 k3 = (1064 - 3.7*vs)/923;
      ks = (k1/k2)*k3;
   }

   Float64 kh = 1.0;
   if ( m_RelativeHumidity < 80.0 )
   {
      kh = (140. - m_RelativeHumidity)/70.;
   }
   else
   {
      kh = 3*(100.0 - m_RelativeHumidity)/70.;
   }
   if ( kh < 0 )
   {
      kh = 0;
   }

   Float64 K = (GetCuringType() == WBFL::Materials::CuringType::Moist ? 35.0 : 55.0);
   Float64 eshu = (GetCuringType() == WBFL::Materials::CuringType::Moist ? 0.51e-3 : 0.56e-3);
   Float64 esh = -ks*kh*eshu*(shrinkage_time)/(K + shrinkage_time);

   pDetails->kvs = ks;
   pDetails->khs = kh;
   pDetails->esh = esh;
   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDConcrete::GetFreeShrinkageStrain2005(Float64 t) const
{
   std::unique_ptr<LRFDConcreteShrinkageDetails> pDetails(std::make_unique<LRFDConcreteShrinkageDetails>());
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
   
   Float64 fc = WBFL::Units::ConvertFromSysUnits(m_InitialConcrete.GetFc(),WBFL::Units::Measure::KSI);
   Float64 kf = 5.0/(1.0 + fc);

   Float64 ktd = (shrinkage_time)/(61.0 - 4.0*fc + shrinkage_time);

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

std::unique_ptr<WBFL::Materials::ConcreteBaseShrinkageDetails> LRFDConcrete::GetFreeShrinkageStrain2015(Float64 t) const
{
   std::unique_ptr<LRFDConcreteShrinkageDetails> pDetails(std::make_unique<LRFDConcreteShrinkageDetails>());
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
   
   Float64 fc = WBFL::Units::ConvertFromSysUnits(m_InitialConcrete.GetFc(),WBFL::Units::Measure::KSI);
   Float64 kf = 5.0/(1.0 + fc);

   Float64 ktd = (shrinkage_time)/(12*(100.0 - 4.0*fc)/(fc + 20) + shrinkage_time);

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

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDConcrete::GetCreepCoefficientBefore2005(Float64 t,Float64 tla) const
{
   std::unique_ptr<LRFDConcreteCreepDetails> pDetails(std::make_unique<LRFDConcreteCreepDetails>());
   InitializeCreepDetails(t,tla,pDetails.get());

   Float64 age = pDetails->age;
   Float64 age_at_loading = pDetails->age_at_loading;
   Float64 maturity = age - age_at_loading;
   if ( ::IsLE(age,0.0) || ::IsLE(age_at_loading,0.0) || ::IsLE(maturity,0.0) )
   {
      return pDetails;
   }

   bool bSI = BDSManager::GetUnits() == BDSManager::Units::SI;
   
   // Check volume to surface ratio
   Float64 vs, fc;
   if ( bSI )
   {
      vs = WBFL::Units::ConvertFromSysUnits( m_VS, WBFL::Units::Measure::Millimeter );
      fc = WBFL::Units::ConvertFromSysUnits( m_FinalConcrete.GetFc(), WBFL::Units::Measure::MPa);
   }
   else
   {
      vs = WBFL::Units::ConvertFromSysUnits( m_VS, WBFL::Units::Measure::Inch );
      fc = WBFL::Units::ConvertFromSysUnits( m_FinalConcrete.GetFc(), WBFL::Units::Measure::KSI);
   }


   // Compute Kf
   Float64 kf;
   if ( bSI )
   {
      kf = 62.0 / ( 42.0 + fc );
   }
   else
   {
      kf = 1.0 / ( 0.67 + (fc/9.0) );
   }

   // Compute Kc
   Float64 a,b,c;
   Float64 x1, x2;
   Float64 e = pow(10.,1./log(10.));
   if ( bSI )
   {
      x1 = 0.0142;
      x2 = -0.0213;
   }
   else
   {
      x1 = 0.36;
      x2 = -0.54;
   }

   a = maturity/(26.0*pow(e,x1*vs)+maturity);
   b = maturity/(45.0 + maturity);
   c = 1.80 + 1.77*pow(e,x2*vs);

   Float64 kc = (a/b)*(c/2.587);

   Float64 Y = 3.5*kc*kf*(1.58 - m_RelativeHumidity/120.)*pow(age_at_loading,-0.118) * (  pow(maturity,0.6)/(10.0 + pow(maturity,0.6) ) );

   pDetails->fci = fc;
   pDetails->kc = kc;
   pDetails->kf = kf;
   pDetails->Ct = Y;

   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDConcrete::GetCreepCoefficient2005(Float64 t,Float64 tla) const
{
   std::unique_ptr<LRFDConcreteCreepDetails> pDetails(std::make_unique<LRFDConcreteCreepDetails>());
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
   
   Float64 fc = WBFL::Units::ConvertFromSysUnits(m_InitialConcrete.GetFc(),WBFL::Units::Measure::KSI);
   Float64 kf = 5.0/(1.0 + fc);

   Float64 ktd = (maturity)/(61.0 - 4.0*fc + maturity);

   Float64 ti = age_at_loading;
   Float64 k1, k2;
   GetCreepCorrectionFactors(&k1, &k2);
   Float64 Y = 1.9*k1*k2*ks*khc*kf*ktd*pow(ti,-0.118);

   pDetails->fci = m_InitialConcrete.GetFc();
   pDetails->kvs = ks;
   pDetails->khc = khc;
   pDetails->kf = kf;
   pDetails->ktd = ktd;
   pDetails->Ct = Y;

   return pDetails;
}

std::unique_ptr<WBFL::Materials::ConcreteBaseCreepDetails> LRFDConcrete::GetCreepCoefficient2015(Float64 t,Float64 tla) const
{
   std::unique_ptr<LRFDConcreteCreepDetails> pDetails(std::make_unique<LRFDConcreteCreepDetails>());
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
   
   Float64 fc = WBFL::Units::ConvertFromSysUnits(m_InitialConcrete.GetFc(),WBFL::Units::Measure::KSI);
   Float64 kf = 5.0/(1.0 + fc);

   Float64 ktd = (maturity)/(12*(100.0 - 4.0*fc)/(fc + 20) + maturity);

   Float64 ti = age_at_loading;
   Float64 k1, k2;
   GetCreepCorrectionFactors(&k1, &k2);
   Float64 Y = 1.9*k1*k2*ks*khc*kf*ktd*pow(ti,-0.118);

   pDetails->fci = fc;
   pDetails->kvs = ks;
   pDetails->khc = khc;
   pDetails->kf = kf;
   pDetails->ktd = ktd;
   pDetails->Ct = Y;

   return pDetails;
}

bool LRFDConcrete::Use90DayConcrete(Float64 t) const
{
   // if 90 concrete is enabled
   // and we have normal strength concrete (LRFD only gives 115%f'c for normal weight and is silent on LWC), and age is more than 90 days
   Float64 age = GetAge(t);

   // Starting with LRFD 10th Edition, 2024, the slow curing increase applies to NWC and LWC.
   bool bApplicableType = false;
   if (WBFL::LRFD::BDSManager::GetEdition() < WBFL::LRFD::BDSManager::Edition::TenthEdition2024)
      bApplicableType = m_Type == WBFL::Materials::ConcreteType::Normal ? true : false;
   else
      bApplicableType = m_Type == WBFL::Materials::ConcreteType::Normal || m_Type == WBFL::Materials::ConcreteType::AllLightweight || m_Type == WBFL::Materials::ConcreteType::SandLightweight ? true : false;

   return (m_bUse90DayConcrete && bApplicableType && 90 < age) ? true : false;
}
