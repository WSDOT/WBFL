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
#include <Materials/ACI209Concrete.h>
#include <Materials/XConcrete.h>

#include <MathEx.h>
#include <Units/Units.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

void ACI209Concrete::GetModelParameters(CuringType cure,CementType cement,Float64* pA,Float64* pB)
{
   Float64 a[2][2] = { {WBFL::Units::ConvertToSysUnits(4.0,WBFL::Units::Measure::Day),    // Moist, Type I
                        WBFL::Units::ConvertToSysUnits(2.3,WBFL::Units::Measure::Day)} ,  // Moist, Type III
                       {WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Day),    // Steam, Type I
                        WBFL::Units::ConvertToSysUnits(0.7,WBFL::Units::Measure::Day)} }; // Steam, Type III
   Float64 b[2][2] = { {0.85,  // Moist, Type I
                        0.92}, // Moist, Type III
                        {0.95, // Steam, Type I
                        0.98} }; // Steam, Type III

   auto cure_idx = std::underlying_type<CuringType>::type(cure);
   auto cement_idx = std::underlying_type<CementType>::type(cement);
   *pA = a[cure_idx][cement_idx];
   *pB = b[cure_idx][cement_idx];
}

ACI209Concrete::ACI209Concrete(LPCTSTR name) :
ConcreteBase(name),
m_A(WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Day)),
m_Beta(0.95),
m_Fc28(0),
m_Ec28(0),
m_bUserEc(false),
m_bIsValid(false),
m_bCorrectionFactorsValidated(false),
m_Eshu(-780E-6),
m_Cu(2.35)
{
}

void ACI209Concrete::SetA(Float64 a)
{
   if ( !IsEqual(m_A,a) )
   {
      m_A = a;
      m_bIsValid = false;
   }
}

Float64 ACI209Concrete::GetA() const
{
   return m_A;
}

void ACI209Concrete::SetBeta(Float64 b)
{
   if ( !IsEqual(m_Beta,b) )
   {
      m_Beta = b;
      m_bIsValid = false;
   }
}

Float64 ACI209Concrete::GetBeta() const
{
   return m_Beta;
}

void ACI209Concrete::SetFc28(Float64 fc)
{
   if ( !IsEqual(m_Fc28,fc) )
   {
      m_Fc28 = fc;
      m_bIsValid = false;
   }
}

Float64 ACI209Concrete::ComputeFc28(Float64 fc,Float64 age,Float64 a,Float64 b)
{
   // solving ACI209 equation 2-1 for (f'c)28
   Float64 fc28 = (WBFL::Units::ConvertFromSysUnits(a,WBFL::Units::Measure::Day) + b*age)*fc/age;
   return fc28;
}

Float64 ACI209Concrete::ComputeEc28(Float64 Ec,Float64 age,Float64 a,Float64 b)
{
   // solving ACI209 equation 2-2 for (Ec)28
   Float64 Ec28 = sqrt((WBFL::Units::ConvertFromSysUnits(a,WBFL::Units::Measure::Day) + b*age)/age)*Ec;
   return Ec28;
}

void ACI209Concrete::ComputeParameters(Float64 fc1,Float64 t1,Float64 fc2,Float64 t2,Float64* pA,Float64* pB)
{
   // solving ACI209 equation 2-1 for Alpha and Beta
   *pB = (t1*fc2 - t2*fc1)/(fc1*(t1-t2));
   *pA = t2*(1.0 - (*pB));
}

void ACI209Concrete::SetFc28(Float64 fc,Float64 t)
{
   Float64 age = GetAge(t);
   ASSERT(!IsZero(age));
   m_Fc28 = ComputeFc28(fc,age,m_A,m_Beta);
   m_bIsValid = false;
}

Float64 ACI209Concrete::GetFc28() const
{
   return m_Fc28;
}

void ACI209Concrete::UserEc28(bool bUserEc)
{
   if ( m_bUserEc != bUserEc )
   {
      m_bUserEc = bUserEc;
      m_bIsValid = false;
   }
}

bool ACI209Concrete::UserEc28() const
{
   return m_bUserEc;
}

void ACI209Concrete::SetEc28(Float64 Ec)
{
   if ( !IsEqual(m_Ec28,Ec) )
   {
      m_Ec28 = Ec;
      m_bIsValid = false;
   }
}

Float64 ACI209Concrete::GetEc28() const
{
   return m_Ec28;
}

void ACI209Concrete::SetEc28(Float64 Ec,Float64 t)
{
   Float64 age = GetAge(t);
   ASSERT(!IsZero(age));
   m_Ec28 = ComputeEc28(Ec,age,m_A,m_Beta);
   m_bIsValid = false;
}

Float64 ACI209Concrete::GetFc(Float64 t) const
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

Float64 ACI209Concrete::GetEc(Float64 t) const
{
   Validate();

   Float64 age = GetAge(t);
   if ( age < 0 )
   {
      return 0;
   }

   // Eqn 2-5
   Float64 Ec = m_Ec*sqrt(age/(m_Alpha + m_Beta*age));
   return Ec;
}

Float64 ACI209Concrete::GetFlexureFr(Float64 t) const
{
   return GetFr(t);
}

Float64 ACI209Concrete::GetShearFr(Float64 t) const
{
   return GetFr(t);
}

Float64 ACI209Concrete::GetFreeShrinkageStrain(Float64 t) const
{
   return GetFreeShrinkageStrainDetails(t)->esh;
}

std::unique_ptr<ConcreteBaseShrinkageDetails> ACI209Concrete::GetFreeShrinkageStrainDetails(Float64 t) const
{
   std::unique_ptr<ACI209ConcreteShrinkageDetails> pDetails(std::make_unique<ACI209ConcreteShrinkageDetails>());

   ConcreteBase::InitializeShrinkageDetails(t, pDetails.get());

   ValidateCorrectionFactors();

   Float64 shrinkage_time = pDetails->shrinkage_duration;
   if ( shrinkage_time < 0 )
   {
      return pDetails;
   }

   Float64 f = (m_CuringType == CuringType::Moist ? 35 : 55); // Eqn 2-1, 2-9, 2-10
   Float64 time_factor = shrinkage_time/(f+shrinkage_time);

   // Adjustments
   Float64 correction_factor = 1.0;

   // Initial moist curing (2.5.3)
   correction_factor *= m_CP;

   // Relative humidity (2.5.4)
   correction_factor *= m_RHS;

   // Volume-Surface Ratio (2.5.5b)
   correction_factor *= m_VSS;

   // Limits (see paragraph between 2.5.5b and 2.5.6
   correction_factor = Max(correction_factor,0.2);

   // Shrinakge strain
   Float64 sh = time_factor * correction_factor * m_Eshu;

   pDetails->f = f;
   pDetails->time_factor = time_factor;
   pDetails->curing_factor = m_CP;
   pDetails->humidity_factor = m_RHS;
   pDetails->vs_factor = m_VSS;
   pDetails->esh = sh;
   return pDetails;
}

Float64 ACI209Concrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   return GetCreepCoefficientDetails(t,tla)->Ct;
}

std::unique_ptr<ConcreteBaseCreepDetails> ACI209Concrete::GetCreepCoefficientDetails(Float64 t,Float64 tla) const
{
   std::unique_ptr<ACI209ConcreteCreepDetails> pDetails(std::make_unique<ACI209ConcreteCreepDetails>());
   InitializeCreepDetails(t,tla, pDetails.get());

   ValidateCorrectionFactors();

   Float64 age = pDetails->age;
   Float64 age_at_loading = pDetails->age_at_loading;
   Float64 maturity = age - age_at_loading;
   if ( ::IsLE(age,0.0) || ::IsLE(age_at_loading,0.0) || ::IsLE(maturity,0.0) )
   {
      return pDetails;
   }

   Float64 tx = pow(maturity,0.6);
   Float64 time_factor = tx/(10+tx);

   // Adjustments
   Float64 correction_factor = 1.0;

   // Load Age Factor (2.5.1)
   Float64 LA = 1.0;
   if (m_CuringType == CuringType::Moist)
   {
      if ( 7 < age_at_loading )
      {
         LA = 1.25*pow(age_at_loading,-0.118);
      }
   }
   else
   {
      if ( 3 < age_at_loading )
      {
         LA = 1.13*pow(age_at_loading,-0.094);
      }
   }
   correction_factor *= LA;

   // Relative humidity (2.5.4)
   correction_factor *= m_RHC;

   // Volume-Surface Ratio (2.5.5b)
   correction_factor *= m_VSC;

   // Creep coefficent
   Float64 c = time_factor * correction_factor * m_Cu;

   pDetails->time_factor = time_factor;
   pDetails->loading_age_factor = LA;
   pDetails->humidity_factor = m_RHC;
   pDetails->vs_factor = m_VSC;
   pDetails->Ct = c;
   
   return pDetails;
}

std::unique_ptr<ConcreteBase> ACI209Concrete::CreateClone() const
{
   return std::make_unique<ACI209Concrete>(*this);
}

void ACI209Concrete::SetUltimateShrinkageStrain(Float64 eu)
{
   if ( m_Eshu != eu )
   {
      m_Eshu = eu;
      m_bCorrectionFactorsValidated = false;
   }
}

Float64 ACI209Concrete::GetUltimateShrinkageStrain() const
{
   return m_Eshu;
}

void ACI209Concrete::SetUltimateCreepCoefficient(Float64 cu)
{
   if ( m_Cu != cu )
   {
      m_Cu = cu;
      m_bCorrectionFactorsValidated = false;
   }
}

Float64 ACI209Concrete::GetUltimateCreepCoefficient() const
{
   return m_Cu;
}

Float64 ACI209Concrete::GetRelativeHumidityFactorCreep() const
{
   ValidateCorrectionFactors();
   return m_RHC;
}

Float64 ACI209Concrete::GetRelativeHumidityFactorShrinkage() const
{
   ValidateCorrectionFactors();
   return m_RHS;
}

Float64 ACI209Concrete::GetInitialMoistCureFactor() const
{
   ValidateCorrectionFactors();
   return m_CP;
}

Float64 ACI209Concrete::GetSizeFactorCreep() const
{
   ValidateCorrectionFactors();
   return m_VSC;
}

Float64 ACI209Concrete::GetSizeFactorShrinkage() const
{
   ValidateCorrectionFactors();
   return m_VSS;
}

void ACI209Concrete::OnChanged()
{
   m_bIsValid = false;
   m_bCorrectionFactorsValidated = false;
}

void ACI209Concrete::Validate() const
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

   m_bIsValid = true;
}

void ACI209Concrete::ValidateCorrectionFactors() const
{
   Validate();

   if ( m_bCorrectionFactorsValidated )
   {
      return;
   }

   // Initial Moist Cure (2.5.3)
   m_CP = 1.0;
   if ( m_CuringType == CuringType::Moist )
   {
      // linear interpolate values from table 2.5.3
      if ( m_CureTime < 1 )
      {
         m_CP = 1.2;
      }
      else if ( 1 <= m_CureTime && m_CureTime < 3 )
      {
         m_CP = LinInterp(m_CureTime-1.,1.2,1.1,3.-1.);
      }
      else if ( 3 <= m_CureTime && m_CureTime < 7 )
      {
         m_CP = LinInterp(m_CureTime-3.,1.1,1.0,7.-3.);
      }
      else if ( 7 <= m_CureTime && m_CureTime < 14 )
      {
         m_CP = LinInterp(m_CureTime-7.,1.0,0.93,14.-7.);
      }
      else if ( 14 <= m_CureTime && m_CureTime < 28 )
      {
         m_CP = LinInterp(m_CureTime-14.,0.93,0.86,28.-14.);
      }
      else if ( 28 <= m_CureTime && m_CureTime < 90 )
      {
         m_CP = LinInterp(m_CureTime-28.,0.86,0.75,90.-28.);
      }
      else
      {
         m_CP = 0.75;
      }
   }

   // Relative Humidity correction factors (2.5.4)
   m_RHC = 1.0;
   if ( 40.0 < m_RelativeHumidity )
   {
      m_RHC = 1.27 - 0.0067*m_RelativeHumidity;
   }

   m_RHS = 1.0;
   if ( 40.0 <= m_RelativeHumidity && m_RelativeHumidity <= 80.0 )
   {
      m_RHS = 1.40 - 0.0102*m_RelativeHumidity;
   }
   else if ( 80.0 < m_RelativeHumidity )
   {
      m_RHS = 3.00 - 0.030*m_RelativeHumidity;
   }

   // V/S ratio correction factor (2.5.5b)
   ASSERT(0 < m_VS); // did you forget to set V/S ratio?
   Float64 vs = WBFL::Units::ConvertFromSysUnits(m_VS,WBFL::Units::Measure::Inch);
   m_VSC = (2.0/3.0)*(1.0 + 1.13*exp(-0.54*vs)); // creep (2-21)
   m_VSS = 1.2*exp(-0.12*vs);                    // shrinkage (2-22)


   m_bCorrectionFactorsValidated = true;
}

Float64 ACI209Concrete::GetFr(Float64 t) const
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
Float64 ACI209Concrete::ModE(Float64 fc,Float64 density) const
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


//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

void ACI209ConcreteStrengthModel::GetModelParameters(CuringType cure, CementType cement, Float64* pA, Float64* pBeta)
{
   static const Float64 a[2][2] = { {WBFL::Units::ConvertToSysUnits(4.0,WBFL::Units::Measure::Day),    // Moist, Type I
                                     WBFL::Units::ConvertToSysUnits(2.3,WBFL::Units::Measure::Day)} ,  // Moist, Type III
                                    {WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Day),    // Steam, Type I
                                     WBFL::Units::ConvertToSysUnits(0.7,WBFL::Units::Measure::Day)} }; // Steam, Type III
   static const Float64 beta[2][2] = { {0.85,  // Moist, Type I
                                        0.92}, // Moist, Type III
                                       {0.95, // Steam, Type I
                                        0.98} }; // Steam, Type III

   auto cure_idx = std::underlying_type<CuringType>::type(cure);
   auto cement_idx = std::underlying_type<CementType>::type(cement);
   *pA = a[cure_idx][cement_idx];
   *pBeta = beta[cure_idx][cement_idx];
}

Float64 ACI209ConcreteStrengthModel::ComputeFc28(Float64 fc, Float64 age, Float64 a, Float64 b)
{
   PRECONDITION(0 < age);

   // solving ACI209 equation 2-1 for (f'c)28
   Float64 fc28 = (WBFL::Units::ConvertFromSysUnits(a, WBFL::Units::Measure::Day) + b * age) * fc / age;
   return fc28;
}

void ACI209ConcreteStrengthModel::ComputeParameters(Float64 fc1, Float64 t1, Float64 fc2, Float64 t2, Float64* pA, Float64* pB)
{
   PRECONDITION(!IsZero(t2 - t1));

   // solving ACI209 equation 2-1 for Alpha and Beta
   *pB = (t1 * fc2 - t2 * fc1) / (fc1 * (t1 - t2));
   *pA = t2 * (1.0 - (*pB));
}

void ACI209ConcreteStrengthModel::SetA(Float64 a)
{
   if (!IsEqual(m_A, a))
   {
      m_A = a;
      m_bIsValid = false;
   }
}

Float64 ACI209ConcreteStrengthModel::GetA() const
{
   return m_A;
}

void ACI209ConcreteStrengthModel::SetBeta(Float64 b)
{
   if (!IsEqual(m_Beta, b))
   {
      m_Beta = b;
      m_bIsValid = false;
   }
}

Float64 ACI209ConcreteStrengthModel::GetBeta() const
{
   return m_Beta;
}

void ACI209ConcreteStrengthModel::SetFc28(Float64 fc)
{
   if (!IsEqual(m_Fc28, fc))
   {
      m_Fc28 = fc;
      m_bIsValid = false;
   }
}

void ACI209ConcreteStrengthModel::SetFc28(Float64 fc, Float64 age)
{
   ASSERT(!IsZero(age));
   m_Fc28 = ACI209Concrete::ComputeFc28(fc, age, m_A, m_Beta);
   m_bIsValid = false;
}

Float64 ACI209ConcreteStrengthModel::GetFc28() const
{
   return m_Fc28;
}

Float64 ACI209ConcreteStrengthModel::GetFc(Float64 age) const
{
   Validate();

   // ACI209 Eqn 2-1
   Float64 fc = age * m_Fc28 / (m_Alpha + m_Beta * age);
   return fc;
}

void ACI209ConcreteStrengthModel::Validate() const
{
   if (m_bIsValid)
   {
      return;
   }

   m_Alpha = WBFL::Units::ConvertFromSysUnits(m_A, WBFL::Units::Measure::Day);

   m_bIsValid = true;
}

#if defined _DEBUG
bool ACI209ConcreteStrengthModel::AssertValid() const
{
   return true;
}

void ACI209ConcreteStrengthModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ACI209ConcreteStrengthModel") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool ACI209ConcreteStrengthModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209ConcreteStrengthModel");

   ACI209ConcreteStrengthModel model;
   model.SetFc28(7);

   Float64 a, b;
   ACI209ConcreteStrengthModel::GetModelParameters(CuringType::Moist, CementType::TypeI, &a, &b);
   model.SetA(a);
   model.SetBeta(b);
   TRY_TESTME(IsEqual(model.GetFc(10), 5.6));
   TRY_TESTME(IsEqual(model.GetFc(56), 7.596899));

   ACI209ConcreteStrengthModel::GetModelParameters(CuringType::Moist, CementType::TypeII, &a, &b);
   model.SetA(a);
   model.SetBeta(b);
   TRY_TESTME(IsEqual(model.GetFc(10), 6.08696));
   TRY_TESTME(IsEqual(model.GetFc(56), 7.28354));

   ACI209ConcreteStrengthModel::GetModelParameters(CuringType::Steam, CementType::TypeI, &a, &b);
   model.SetA(a);
   model.SetBeta(b);
   TRY_TESTME(IsEqual(model.GetFc(10), 6.66667));
   TRY_TESTME(IsEqual(model.GetFc(56), 7.23247));

   ACI209ConcreteStrengthModel::GetModelParameters(CuringType::Steam, CementType::TypeII, &a, &b);
   model.SetA(a);
   model.SetBeta(b);
   TRY_TESTME(IsEqual(model.GetFc(10), 6.66667));
   TRY_TESTME(IsEqual(model.GetFc(56), 7.05290));

   TESTME_EPILOG("ACI209ConcreteStrengthModel");
}
#endif // _UNITTEST

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
ACI209ConcreteSecantModulusModel::ACI209ConcreteSecantModulusModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel, Float64 density) :
   ConcreteSecantModulusModel(), m_FcModel(fcModel), m_Density(density)
{
}

Float64 ACI209ConcreteSecantModulusModel::ComputeEc28(Float64 Ec, Float64 age, Float64 a, Float64 b)
{
   PRECONDITION(0 < age);

   // solving ACI209 equation 2-2 for (Ec)28
   Float64 Ec28 = sqrt((WBFL::Units::ConvertFromSysUnits(a, WBFL::Units::Measure::Day) + b * age) / age) * Ec;
   return Ec28;
}

void ACI209ConcreteSecantModulusModel::SetConcreteStrengthModel(const std::shared_ptr<ConcreteStrengthModel>& fcModel)
{
   m_FcModel = fcModel;
}

const std::shared_ptr<ConcreteStrengthModel>& ACI209ConcreteSecantModulusModel::GetConcreteStrengthModel() const
{
   return m_FcModel;
}

void ACI209ConcreteSecantModulusModel::SetDensity(Float64 density)
{
   PRECONDITION(0 < density);
   m_Density = density;
}

Float64 ACI209ConcreteSecantModulusModel::GetDensity() const
{
   return m_Density;
}

Float64 ACI209ConcreteSecantModulusModel::GetEc(Float64 age) const
{
   if (age < 0) return 0;

   if (m_FcModel == nullptr) THROW_CONCRETE(_T("ACI209ConcreteSecantModulusModel - Concrete strength model not defined"));

   Float64 fc = m_FcModel->GetFc(age);

   Float64 Fc;          // fc in spec units
   Float64 Density;     // density in spec units
   Float64 E;           // Modulus of elasticity in spec units
   Float64 e;           // modulus of elasticity in System Units

   // Convert input to required units
   Fc = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::PSI);
   Density = WBFL::Units::ConvertFromSysUnits(m_Density, WBFL::Units::Measure::LbmPerFeet3);

   // Perform the calculation
   E = 33.0 * sqrt(pow(Density, 3.0) * Fc); // ACI209 Eq 2-5.

   // Convert output to system units.
   e = WBFL::Units::ConvertToSysUnits(E, WBFL::Units::Measure::PSI);
   
   return e;
}

#if defined _DEBUG
bool ACI209ConcreteSecantModulusModel::AssertValid() const
{
   return true;
}

void ACI209ConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ACI209ConcreteSecantModulusModel") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool ACI209ConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209ConcreteSecantModulusModel");

   // want to work is KSI units
   WBFL::Units::AutoSystem auto_restore_units_system;
   WBFL::Units::System::SetMassUnit(WBFL::Units::Measure::_12KSlug);
   WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Inch);
   WBFL::Units::System::SetTimeUnit(WBFL::Units::Measure::Second);
   WBFL::Units::System::SetTemperatureUnit(WBFL::Units::Measure::Fahrenheit);
   WBFL::Units::System::SetAngleUnit(WBFL::Units::Measure::Radian);

   ACI209ConcreteSecantModulusModel model;
   try
   {
      model.GetEc(28.0);
   }
   catch (XConcrete&)
   {
      TRY_TESTME(true);
   }

   std::shared_ptr<ACI209ConcreteStrengthModel> fcModel(std::make_shared<ACI209ConcreteStrengthModel>());
   Float64 a, b;
   ACI209ConcreteStrengthModel::GetModelParameters(CuringType::Moist, CementType::TypeI, &a, &b);

   fcModel->SetFc28(7.0);
   fcModel->SetA(a);
   fcModel->SetBeta(b);

   model.SetConcreteStrengthModel(fcModel);
   model.SetDensity(WBFL::Units::ConvertToSysUnits(150.0, WBFL::Units::Measure::LbmPerFeet3));

   TRY_TESTME(IsEqual(model.GetEc(10), 4536.74994));
   TRY_TESTME(IsEqual(model.GetEc(56), 5284.07546));


   TESTME_EPILOG("ACI209ConcreteSecantModulusModel");
}
#endif // _UNITTEST


////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////
ACI209CreepVSRatioCorrectionFactorModel::ACI209CreepVSRatioCorrectionFactorModel(Float64 vsRatio) :
   VSRatioCorrectionFactorModel(vsRatio)
{
}

Float64 ACI209CreepVSRatioCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   Float64 vsRatio = GetVSRatio();
   Float64 vs = WBFL::Units::ConvertFromSysUnits(vsRatio, WBFL::Units::Measure::Inch);
   return (2.0 / 3.0) * (1.0 + 1.13 * exp(-0.54 * vs)); // creep (2-21)
}

#if defined _DEBUG
bool ACI209CreepVSRatioCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void ACI209CreepVSRatioCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}

#endif // _DEBUG

#if defined _UNITTEST
bool ACI209CreepVSRatioCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209CreepVSRatioCorrectionFactorModel");
   ACI209CreepVSRatioCorrectionFactorModel model(WBFL::Units::ConvertToSysUnits(4.5, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(10), 0.73299));
   TESTME_EPILOG("ACI209CreepVSRatioCorrectionFactorModel");
}
#endif // _UNITTEST

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

ACI209ShrinkageVSRatioCorrectionFactorModel::ACI209ShrinkageVSRatioCorrectionFactorModel(Float64 vsRatio) :
   VSRatioCorrectionFactorModel(vsRatio)
{
}

Float64 ACI209ShrinkageVSRatioCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   Float64 vsRatio = GetVSRatio();
   Float64 vs = WBFL::Units::ConvertFromSysUnits(vsRatio, WBFL::Units::Measure::Inch);
   return 1.2 * exp(-0.12 * vs); // shrinkage (2-22)
}

#if defined _DEBUG
bool ACI209ShrinkageVSRatioCorrectionFactorModel::AssertValid() const 
{
   return __super::AssertValid();
}

void ACI209ShrinkageVSRatioCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool ACI209ShrinkageVSRatioCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209ShrinkageVSRatioCorrectionFactorModel");
   ACI209ShrinkageVSRatioCorrectionFactorModel model(WBFL::Units::ConvertToSysUnits(4.5, WBFL::Units::Measure::Inch));
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(10), 0.69930));
   TESTME_EPILOG("ACI209ShrinkageVSRatioCorrectionFactorModel");
}
#endif // _UNITTEST

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

ACI209ShrinkageHumidityCorrectionFactorModel::ACI209ShrinkageHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 ACI209ShrinkageHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   Float64 H = GetH();
   Float64 RH = 1.0;
   if (40.0 <= H && H <= 80.0)
   {
      RH = 1.40 - 0.0102 * H;
   }
   else if (80.0 < H)
   {
      RH = 3.00 - 0.030 * H;
   }

   return RH;
}

#if defined _DEBUG
bool ACI209ShrinkageHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void ACI209ShrinkageHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool ACI209ShrinkageHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209ShrinkageHumidityCorrectionFactorModel");
   ACI209ShrinkageHumidityCorrectionFactorModel model(30);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.0));

   model.SetH(50);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.89));

   model.SetH(90);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.30));
   TESTME_EPILOG("ACI209ShrinkageHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

ACI209CreepHumidityCorrectionFactorModel::ACI209CreepHumidityCorrectionFactorModel(Float64 h) :
   HumidityCorrectionFactorModel(h)
{
}

Float64 ACI209CreepHumidityCorrectionFactorModel::GetCorrectionFactor() const
{
   Float64 H = GetH();
   Float64 RH = 1.0;
   if (40.0 < H)
   {
      RH = 1.27 - 0.0067 * H;
   }
   return RH;
}

#if defined _DEBUG
bool ACI209CreepHumidityCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void ACI209CreepHumidityCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool ACI209CreepHumidityCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209CreepHumidityCorrectionFactorModel");
   ACI209CreepHumidityCorrectionFactorModel model(30);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.0));

   model.SetH(50);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.935));
   TESTME_EPILOG("ACI209CreepHumidityCorrectionFactorModel");
}
#endif // _UNITTEST

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::ACI209ShrinkageTimeDevelopmentCorrectionFactorModel(CuringType curingType) :
   m_CuringType(curingType)
{
}

void ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::SetCuringType(CuringType curingType)
{
   m_CuringType = curingType;
}

CuringType ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::GetCuringType() const
{
   return m_CuringType;
}

Float64 ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::GetCorrectionFactor(Float64 t) const
{
   Float64 f = (m_CuringType == CuringType::Moist ? 35 : 55); // Eqn 2-1, 2-9, 2-10
   Float64 time_factor = t / (f + t);
   return time_factor;
}

#if defined _DEBUG
bool ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::AssertValid() const
{
   return __super::AssertValid();
}

void ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209ShrinkageTimeDevelopmentCorrectionFactorModel");
   ACI209ShrinkageTimeDevelopmentCorrectionFactorModel model;
   
   model.SetCuringType(CuringType::Moist);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(89), 0.71774));
   
   model.SetCuringType(CuringType::Steam);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(89), 0.61806));
   
   TESTME_EPILOG("ACI209ShrinkageTimeDevelopmentCorrectionFactorModel");
}
#endif // _UNITTEST

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

ACI209CuringCorrectionFactorModel::ACI209CuringCorrectionFactorModel(CuringType curingType,Float64 curingDuration) :
   m_CuringType(curingType), m_CuringDuration(curingDuration)
{
}

void ACI209CuringCorrectionFactorModel::SetCuringType(CuringType curingType)
{
   m_CuringType = curingType;
}

CuringType ACI209CuringCorrectionFactorModel::GetCuringType() const
{
   return m_CuringType;
}

void ACI209CuringCorrectionFactorModel::SetCuringDuration(Float64 curingDuration)
{
   m_CuringDuration = curingDuration;
}

Float64 ACI209CuringCorrectionFactorModel::GetCuringDuration() const
{
   return m_CuringDuration;
}

Float64 ACI209CuringCorrectionFactorModel::GetCorrectionFactor() const
{
   // Initial Moist Cure (2.5.3)
   Float64 CP = 1.0;
   if (m_CuringType == CuringType::Moist)
   {
      // linear interpolate values from table 2.5.3
      if (m_CuringDuration < 1)
      {
         CP = 1.2;
      }
      else if (1 <= m_CuringDuration && m_CuringDuration < 3)
      {
         CP = LinInterp(m_CuringDuration - 1., 1.2, 1.1, 3. - 1.);
      }
      else if (3 <= m_CuringDuration && m_CuringDuration < 7)
      {
         CP = LinInterp(m_CuringDuration - 3., 1.1, 1.0, 7. - 3.);
      }
      else if (7 <= m_CuringDuration && m_CuringDuration < 14)
      {
         CP = LinInterp(m_CuringDuration - 7., 1.0, 0.93, 14. - 7.);
      }
      else if (14 <= m_CuringDuration && m_CuringDuration < 28)
      {
         CP = LinInterp(m_CuringDuration - 14., 0.93, 0.86, 28. - 14.);
      }
      else if (28 <= m_CuringDuration && m_CuringDuration < 90)
      {
         CP = LinInterp(m_CuringDuration - 28., 0.86, 0.75, 90. - 28.);
      }
      else
      {
         CP = 0.75;
      }
   }

   return CP;
}

#if defined _DEBUG
bool ACI209CuringCorrectionFactorModel::AssertValid() const
{
   return true;
}

void ACI209CuringCorrectionFactorModel::Dump(WBFL::Debug::LogContext& os) const
{
}
#endif // _DEBUG

#if defined _UNITTEST
bool ACI209CuringCorrectionFactorModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209CuringCorrectionFactorModel");

   ACI209CuringCorrectionFactorModel model(CuringType::Steam, 7);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.0));

   model.SetCuringType(CuringType::Moist);

   model.SetCuringDuration(0);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.2));

   model.SetCuringDuration(2);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.15));

   model.SetCuringDuration(5);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 1.05));

   model.SetCuringDuration(10);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.97));

   model.SetCuringDuration(20);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.90));

   model.SetCuringDuration(56);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.81033));

   model.SetCuringDuration(180);
   TRY_TESTME(IsEqual(model.GetCorrectionFactor(), 0.75));

   TESTME_EPILOG("ACI209CuringCorrectionFactorModel");
}
#endif // _UNITTEST

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
ACI209ConcreteShrinkageModel::ACI209ConcreteShrinkageModel() :
   ConcreteShrinkageTemplateModel()
{
   SetUltimateShrinkageStrain(-780E-6); // negative for shrinkage
}

ACI209ConcreteShrinkageModel::ACI209ConcreteShrinkageModel(Float64 ecu) :
   ConcreteShrinkageTemplateModel(ecu)
{
}

void ACI209ConcreteShrinkageModel::SetCuringCorrectionFactorModel(const std::shared_ptr<const ACI209CuringCorrectionFactorModel>& model)
{
   m_CuringModel = model;
}

const std::shared_ptr<const ACI209CuringCorrectionFactorModel>& ACI209ConcreteShrinkageModel::GetCuringCorrectionFactorModel() const
{
   return m_CuringModel;
}

Float64 ACI209ConcreteShrinkageModel::GetShrinkageStrain(Float64 t) const
{
   Float64 esh = __super::GetShrinkageStrain(t);
   Float64 cp = m_CuringModel ? m_CuringModel->GetCorrectionFactor() : 1.0;
   esh *= cp;
   return esh;
}

#if defined _DEBUG
bool ACI209ConcreteShrinkageModel::AssertValid() const
{
   return __super::AssertValid();
}

void ACI209ConcreteShrinkageModel::Dump(WBFL::Debug::LogContext& os) const
{
   __super::Dump(os);
}

#endif // _DEBUG

#if defined _UNITTEST
bool ACI209ConcreteShrinkageModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ACI209ConcreteShrinkageModel");

   CuringType curingType{ CuringType::Moist };

   ACI209ConcreteShrinkageModel model;
   model.SetVSRatioCorrectionFactor(std::make_shared<ACI209ShrinkageVSRatioCorrectionFactorModel>(WBFL::Units::ConvertToSysUnits(4.5,WBFL::Units::Measure::Inch)));
   model.SetHumidityCorrectionFactor(std::make_shared<ACI209ShrinkageHumidityCorrectionFactorModel>(73));
   model.SetConcreteTimeDevelopmentCorrectionFactor(std::make_shared<ACI209ShrinkageTimeDevelopmentCorrectionFactorModel>(curingType));
   model.SetCuringCorrectionFactorModel(std::make_shared<ACI209CuringCorrectionFactorModel>(curingType,7.0));

   TRY_TESTME(IsEqual(model.GetShrinkageStrain(89), -0.000257));

   TESTME_EPILOG("ACI209ConcreteShrinkageModel");
}
#endif // _UNITTEST
