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

   *pA = a[+cure][+cement];
   *pB = b[+cure][+cement];
}

ACI209Concrete::ACI209Concrete(const std::_tstring& name) :
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
