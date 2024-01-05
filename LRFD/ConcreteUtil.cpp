///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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
#include <Lrfd\ConcreteUtil.h>
#include <Lrfd/BDSManager.h>
#include <System\XProgrammingError.h>
#include <array>

using namespace WBFL::LRFD;

Float64 ConcreteUtil::GetNWCDensityLimit()
{
   Float64 limit;
   if ( BDSManager::GetUnits() == BDSManager::Units::US )
   {
      limit = WBFL::Units::ConvertToSysUnits(135.0,WBFL::Units::Measure::LbfPerFeet3);
   }
   else
   {
      limit = WBFL::Units::ConvertToSysUnits(2150.0,WBFL::Units::Measure::KgPerMeter3);
   }

   return limit;
}

Float64 ConcreteUtil::GetLWCDensityLimit()
{
   Float64 limit;
   if ( BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2016Interims )
   {
      if ( BDSManager::GetUnits() == BDSManager::Units::US )
      {
         limit = WBFL::Units::ConvertToSysUnits(120.0,WBFL::Units::Measure::LbfPerFeet3);
      }
      else
      {
         limit = WBFL::Units::ConvertToSysUnits(1925.0,WBFL::Units::Measure::KgPerMeter3);
      }
   }
   else
   {
      limit = ConcreteUtil::GetNWCDensityLimit();
   }

   return limit;
}

void ConcreteUtil::GetPCIUHPCStrengthRange(Float64* pFcMin, Float64* pFcMax)
{
   // See "Compression Response of a Rapid-Strengthening Ultra-High Performance Concrete Formulation"
   // FHWA Publication FHWA-HRT-12-964
   // Graybeal
   //*pFcMin = WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI);
   //*pFcMax = WBFL::Units::ConvertToSysUnits(26.0, WBFL::Units::Measure::KSI);

   // PCI-UHPC Structural Guidance, min f'c = 17.4 ksi, no max provided so use a really high value that wont be exceeded
   *pFcMin = WBFL::Units::ConvertToSysUnits(17.4, WBFL::Units::Measure::KSI);
   *pFcMax = WBFL::Units::ConvertToSysUnits(99999.0, WBFL::Units::Measure::KSI);
}

void ConcreteUtil::GetPCIUHPCMinProperties(Float64* pfcMin, Float64* pffc, Float64* pfpeak, Float64* pfrr)
{
   Float64 fcMax;
   GetPCIUHPCStrengthRange(pfcMin, &fcMax);
   *pffc = WBFL::Units::ConvertToSysUnits(1.5, WBFL::Units::Measure::KSI);
   *pfpeak = WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::KSI);
   *pfrr = WBFL::Units::ConvertToSysUnits(0.75, WBFL::Units::Measure::KSI);
}

Float64 ConcreteUtil::ModE(WBFL::Materials::ConcreteType type,Float64 fc,Float64 density,bool bCheckRange)
{
   Float64 e;  // modulus of elasticity in System Units
   if (type == WBFL::Materials::ConcreteType::PCI_UHPC || type == WBFL::Materials::ConcreteType::UHPC)
   {
      Float64 Fc = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::KSI);
      Float64 Ec = 2500 * pow(Fc,0.33); // Fc in KSI, Ec in KSI (This is LRFD Equation C5.4.2.4-1)
      e = WBFL::Units::ConvertToSysUnits(Ec, WBFL::Units::Measure::KSI);
   }
   else
   {
      Float64 Fc;          // fc in spec units
      Float64 Density;     // density in spec units
      Float64 E;           // Modulus of elasticity in spec units
      Float64 k;           // coefficient in equation
      Float64 min_density; // minimum density in System Units
      Float64 max_density; // maximum density in System Units

      // Input units
      const WBFL::Units::Stress*  p_fc_unit;
      const WBFL::Units::Density* p_density_unit;
      const WBFL::Units::Stress*  p_E_unit;

      if (BDSManager::GetUnits() == BDSManager::Units::SI)
      {
         p_fc_unit = &WBFL::Units::Measure::MPa;
         p_density_unit = &WBFL::Units::Measure::KgPerMeter3;
         p_E_unit = &WBFL::Units::Measure::MPa;

         k = 0.043;

         min_density = 1440.; // kg/m^3
         max_density = 2500.; // kg/m^3
      }
      else
      {
         // :NOTE: 1 lbm = 1 lbf
         p_fc_unit = &WBFL::Units::Measure::KSI;
         p_density_unit = &WBFL::Units::Measure::KipPerFeet3;
         p_E_unit = &WBFL::Units::Measure::KSI;

         if (BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2015Interims)
         {
            k = 33000.;
         }
         else
         {
            k = 120000.;
         }

         min_density = 0.090; // kcf
         max_density = 0.155; // kcf
      }

      // Convert input to required units
      Fc = WBFL::Units::ConvertFromSysUnits(fc, *p_fc_unit);
      Density = WBFL::Units::ConvertFromSysUnits(density, *p_density_unit);


      // Make sure the density range hasn't been violated.
      if (bCheckRange)
      {
         if (!InRange(min_density, Density, max_density))
         {
            THROW(WBFL::System::XProgrammingError, ValueOutOfRange);
         }
      }

      if (BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2015Interims)
      {
         E = k * pow(Density, 1.5) * sqrt(Fc);
      }
      else
      {
         E = k*pow(Density, 2.0)*pow(Fc, 0.33);
      }

      // Convert output to system units.
      e = WBFL::Units::ConvertToSysUnits(E, *p_E_unit);
   }

   return e;
}

Float64 ConcreteUtil::FcFromEc(WBFL::Materials::ConcreteType type, Float64 ec,Float64 density)
{
   Float64 fc;          // fc in system units

   if (type == WBFL::Materials::ConcreteType::PCI_UHPC || type == WBFL::Materials::ConcreteType::UHPC)
   {
      Float64 Ec = WBFL::Units::ConvertFromSysUnits(ec, WBFL::Units::Measure::KSI);
      Float64 Fc = pow(Ec / 2500., 1/0.33);
      fc = WBFL::Units::ConvertToSysUnits(Fc, WBFL::Units::Measure::KSI);
   }
   else
   {
      Float64 Fc;          // fc in spec units
      Float64 Density;     // density in spec units
      Float64 Ec;          // Modulus of elasticity in spec units
      Float64 k;           // coefficient in equation

      // Input units
      const WBFL::Units::Stress*  p_fc_unit;
      const WBFL::Units::Density* p_density_unit;
      const WBFL::Units::Stress*  p_E_unit;

      if (BDSManager::GetUnits() == BDSManager::Units::SI)
      {
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

         if (BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2015Interims)
         {
            k = 33000.;
         }
         else
         {
            k = 120000.;
         }
      }

      // Convert input to required units
      Ec = WBFL::Units::ConvertFromSysUnits(ec, *p_E_unit);
      Density = WBFL::Units::ConvertFromSysUnits(density, *p_density_unit);

      if (BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2015Interims)
      {
         Fc = pow(Ec / (k*pow(Density, 1.5)), 2);
      }
      else
      {
         Fc = pow(Ec / (k*pow(Density, 2)), 1 / 0.33);
      }

      // Convert output to system units.
      fc = WBFL::Units::ConvertToSysUnits(Fc, *p_fc_unit);
   }

   return fc;
}

Float64 ConcreteUtil::ModRupture(Float64 fc, Float64 k)
{
   return ConcreteUtil::ModRupture(fc, WBFL::Materials::ConcreteType::Normal,k);
}

Float64 ConcreteUtil::ModRupture(Float64 fc, WBFL::Materials::ConcreteType concType)
{
   return ConcreteUtil::ModRupture(fc,concType,-1);
}

Float64 ConcreteUtil::ModRupture(Float64 fc, WBFL::Materials::ConcreteType concType,Float64 k)
{
   const WBFL::Units::Stress* p_fc_unit;
   const WBFL::Units::Stress* p_fr_unit;
   const WBFL::Units::SqrtPressure* p_coefficient_unit;

   bool is_si = ( BDSManager::GetUnits() == BDSManager::Units::SI );

   if ( is_si )
   {
      p_fc_unit = &WBFL::Units::Measure::MPa;
      p_fr_unit = &WBFL::Units::Measure::MPa;
      p_coefficient_unit = &WBFL::Units::Measure::SqrtMPa;
   }
   else
   {
      p_fc_unit = &WBFL::Units::Measure::KSI;
      p_fr_unit = &WBFL::Units::Measure::KSI;
      p_coefficient_unit = &WBFL::Units::Measure::SqrtKSI;
   }
      

   bool bAfter2004 = (BDSManager::Edition::ThirdEditionWith2005Interims <= BDSManager::GetEdition());
   if ( k <= 0 )
   {
      switch( concType )
      {
      case WBFL::Materials::ConcreteType::Normal:
         if ( bAfter2004 )
         {
            k = (is_si) ? 0.97 : 0.37;
         }
         else
         {
            k = (is_si) ? 0.63 : 0.24;
         }
         break;

      case WBFL::Materials::ConcreteType::SandLightweight:
         k = (is_si) ? 0.52 : 0.20;
         break;

      case WBFL::Materials::ConcreteType::AllLightweight:
         k = (is_si) ? 0.45 : 0.17;
         break;

      default:
         CHECK(false);
      }
   }
   else
   {
      k = WBFL::Units::ConvertFromSysUnits(k,*p_coefficient_unit);
   }

   // Convert fc to the proper units
   fc = WBFL::Units::ConvertFromSysUnits( fc, *p_fc_unit );

   Float64 fr = k * sqrt( fc );

   // Convert fr to system units
   fr = WBFL::Units::ConvertToSysUnits( fr, *p_fr_unit );

   return fr;
}

Float64 ConcreteUtil::Alpha1(Float64 fc)
{
   if (BDSManager::GetEdition() <= BDSManager::Edition::SeventhEdition2014)
      return 0.85; // alpha1 was introduced in 7th Edition, 2015 interims, before that it was 0.85

   auto fc1 = WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::KSI);
   auto fc2 = WBFL::Units::ConvertToSysUnits(15.0, WBFL::Units::Measure::KSI);
   auto alpha1 = 0.85;
   auto alpha2 = 0.75;

   Float64 alpha = ::LinInterp(fc - fc1, alpha1, alpha2, fc2 - fc1);
   return ::ForceIntoRange(Min(alpha1, alpha2), alpha, Max(alpha1, alpha2));
}

Float64 ConcreteUtil::Beta1(Float64 fc)
{
   const WBFL::Units::Stress* p_fc_unit;
   Float64 fc_limit;
   Float64 fc_step;

   if ( BDSManager::GetUnits() == BDSManager::Units::SI )
   {
      p_fc_unit = &WBFL::Units::Measure::MPa;
      fc_limit = 28.; // MPa
      fc_step  =  7.; // MPa
   }
   else
   {
      p_fc_unit = &WBFL::Units::Measure::PSI;
      fc_limit = 4000.; // psi
      fc_step  = 1000.; // psi
   }

   // Convert fc to the required units
   fc = WBFL::Units::ConvertFromSysUnits( fc, *p_fc_unit );

   Float64 beta1;
   if ( fc < fc_limit )
   {
      beta1 = 0.85;
   }
   else
   {
      beta1 = 0.85 - 0.05*((fc - fc_limit) / fc_step );
      beta1 = ( beta1 < 0.65 ) ? 0.65 : beta1;
   }

   return beta1;
}

Float64 ConcreteUtil::GetFlexureCapacityResistanceFactor(Float64 et, Float64 ecl, Float64 etl, Float64 phiC,Float64 phiT)
{
   Float64 phi = phiC + (phiT - phiC)* (et - ecl) / (etl - ecl);
   phi = ::ForceIntoRange(phiC, phi, phiT);
   return phi;
}

void ConcreteUtil::InterfaceShearParameters(bool isRoughened, WBFL::Materials::ConcreteType girderConcType, WBFL::Materials::ConcreteType deckConcType, Float64* pC, Float64* pU, Float64* pK1, Float64* pK2)
{
   if (girderConcType == WBFL::Materials::ConcreteType::PCI_UHPC)
   {
      if (deckConcType == WBFL::Materials::ConcreteType::PCI_UHPC)
      {
         // UHPC deck on UHPC girder, PCI SDG Table 7.4.3-1 Case 8 and 9
         *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 0.5 : 0.2, WBFL::Units::Measure::KSI);
         *pU = (isRoughened ? 1.4 : 0.6);
         *pK1 = (isRoughened ? 0.3 : 0.2);
         *pK2 = WBFL::Units::ConvertToSysUnits(isRoughened ? 3.6 : 3.6, WBFL::Units::Measure::KSI);
      }
      else
      {
         // conventional deck concrete on UHPC girder, PCI SDG Table 7.4.3-1 Case 4 and 6
         *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 0.24 : 0.025, WBFL::Units::Measure::KSI);
         *pU = (isRoughened ? 1.0 : 0.7);
         *pK1 = (isRoughened ? 0.25 : 0.20);
         *pK2 = WBFL::Units::ConvertToSysUnits(isRoughened ? 1.5 : 0.8, WBFL::Units::Measure::KSI);
      }
   }
   else if (girderConcType == WBFL::Materials::ConcreteType::UHPC)
   {
      // GS 1.7.4.4
      if (deckConcType == WBFL::Materials::ConcreteType::UHPC)
      {
         // UHPC deck on UHPC girder, Case 3 and 4
         *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 0.5 : 0.025, WBFL::Units::Measure::KSI);
         *pU = (isRoughened ? 1.0 : 0.6);
         *pK1 = 99999999; // want this value super high so K1*f'c*Acf never controls
         *pK2 = WBFL::Units::ConvertToSysUnits(isRoughened ? 1.8 : 0.8, WBFL::Units::Measure::KSI);
      }
      else
      {
         // conventional deck concrete on UHPC girder, PCI SDG Table 7.4.3-1 Case 7 and 8
         *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 0.24 : 0.025, WBFL::Units::Measure::KSI);
         *pU = (isRoughened ? 1.0 : 0.6);
         *pK1 = 99999999; // want this value super high so K1*f'c*Acf never controls
         *pK2 = WBFL::Units::ConvertToSysUnits(isRoughened ? 1.8 : 0.8, WBFL::Units::Measure::KSI);
      }
   }
   else
   {
      // conventional concrete girder

      // C
      if (BDSManager::GetEdition() <= BDSManager::Edition::ThirdEditionWith2006Interims)
      {
         if (BDSManager::GetUnits() == BDSManager::Units::SI)
         {
            *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 0.7 : 0.52, WBFL::Units::Measure::MPa);
         }
         else
         {
            *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 0.1 : 0.075, WBFL::Units::Measure::KSI);
         }
      }
      else
      {
         // LRFD 2007 or later
         if (BDSManager::GetUnits() == BDSManager::Units::SI)
         {
            *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 1.9 : 0.52, WBFL::Units::Measure::MPa);
         }
         else
         {
            *pC = WBFL::Units::ConvertToSysUnits(isRoughened ? 0.28 : 0.075, WBFL::Units::Measure::KSI);
         }
      }

      // MU
      if (isRoughened)
      {
         *pU = 1.0; // concrete placed against clean, hardened concrete with surface intentionally roughened
      }
      else
      {
         *pU = 0.6; // concrete placed against clean, hardened concrete with surface NOT intentionally roughened
      }

      if (BDSManager::GetEdition() <= BDSManager::Edition::ThirdEditionWith2006Interims)
      {
         std::array<Float64, 4> Lambda{ 1.0, 0.85, 0.75, 1.0 };
         Float64 lambda = min(Lambda[+girderConcType], Lambda[+deckConcType]);
         *pU *= lambda;
      }

      // K1
      if (BDSManager::GetEdition() < BDSManager::Edition::FourthEdition2007)
      {
         *pK1 = 0.2;
      }
      else
      {
         *pK1 = (isRoughened ? 0.3 : 0.2);
      }

      // K2
      if (BDSManager::GetEdition() < BDSManager::Edition::FourthEdition2007)
      {
         if(BDSManager::GetUnits() == BDSManager::Units::SI)
            *pK2 = WBFL::Units::ConvertToSysUnits(5.5, WBFL::Units::Measure::MPa);
         else
            *pK2 = WBFL::Units::ConvertToSysUnits(0.8, WBFL::Units::Measure::KSI);
      }
      else
      {
         bool bIsNWC = (girderConcType == WBFL::Materials::ConcreteType::Normal && deckConcType == WBFL::Materials::ConcreteType::Normal);
         if (BDSManager::GetUnits() == BDSManager::Units::US)
         {
            if (isRoughened)
            {
               *pK2 = WBFL::Units::ConvertToSysUnits(bIsNWC ? 1.8 : 1.3, WBFL::Units::Measure::KSI);
            }
            else
            {
               *pK2 = WBFL::Units::ConvertToSysUnits(0.8, WBFL::Units::Measure::KSI);
            }
         }
         else
         {
            if (isRoughened)
            {
               *pK2 = WBFL::Units::ConvertToSysUnits(bIsNWC ? 12.4 : 9.0 , WBFL::Units::Measure::MPa);
            }
            else
            {
               *pK2 = WBFL::Units::ConvertToSysUnits(5.5, WBFL::Units::Measure::MPa);
            }
         }
      }
   }
}

void ConcreteUtil::InterfaceShearResistances(Float64 c, Float64 u, Float64 K1, Float64 K2,
                                                  Float64 Acv, Float64 Avf, Float64 Pc,
                                                  Float64 fc, Float64 fy,
                                                  Float64* penqn1, Float64* penqn2, Float64* penqn3)
{
   // nominal shear capacity 5.8.4.1-1,2
   if ( BDSManager::GetEdition() <= BDSManager::Edition::SixthEditionWith2013Interims )
   {
      fy = min(fy, WBFL::Units::ConvertToSysUnits(60.0, WBFL::Units::Measure::KSI));
   }

   Float64 Vn1 = c*Acv + u*(Avf * fy + Pc);
   Float64 Vn2 = K1 * fc * Acv;

   *penqn1= Vn1;
   *penqn2= Vn2;

   // nominal shear capacity 5.8.4.1-3
   *penqn3 = K2*Acv;
}

Float64 ConcreteUtil::LowerLimitOfShearStrength(bool isRoughened, bool doAllStirrupsEngageDeck)
{
   if ( BDSManager::Edition::FourthEdition2007 <= BDSManager::GetEdition() )
   {
      // 4th edition or later
      if (isRoughened && doAllStirrupsEngageDeck)
      {
         if ( BDSManager::GetUnits() == BDSManager::Units::SI )
         {
            return WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::MPa);
         }
         else
         {
            return WBFL::Units::ConvertToSysUnits(0.210, WBFL::Units::Measure::KSI);
         }
      }
      else
      {
         return 0.0;
      }
   }
   else if (BDSManager::Edition::SecondEdition1998 <= BDSManager::GetEdition())
   {
      // 2nd edition or later (but not 4th or later)

      // 2nd to 4th it didn't matter if surface was roughened
      if ( BDSManager::GetUnits() == BDSManager::Units::SI )
      {
         return WBFL::Units::ConvertToSysUnits(0.7, WBFL::Units::Measure::MPa);
      }
      else
      {
         return WBFL::Units::ConvertToSysUnits(0.100, WBFL::Units::Measure::KSI);
      }
   }
   else
   {
      // all other versions have no such limit
      return 0.0;
   }
}

Float64 ConcreteUtil::UpperLimitForBv()
{
   if (BDSManager::GetEdition() < BDSManager::Edition::SecondEdition1998)
   {
      // This requirement was removed in the 1998 Section Edition
      if ( BDSManager::GetUnits() == BDSManager::Units::SI )
      {
         return WBFL::Units::ConvertToSysUnits(0.9, WBFL::Units::Measure::Meter);
      }
      else
      {
         return WBFL::Units::ConvertToSysUnits(36.0, WBFL::Units::Measure::Inch);
      }
   }
   else
   {
      // all other versions have no such limit
      return Float64_Max;
   }
}

Uint16 ConcreteUtil::MinLegsForBv(Float64 bv)
{
   // This requirement was removed in the 1998 Section Edition so the minimum is 1
   if (BDSManager::Edition::SecondEdition1998 <= BDSManager::GetEdition())
      return 1;

   Float64 upper_bv = UpperLimitForBv();
   if (upper_bv <= bv)
   {
      return 4;
   }
   else
   {
      return 1;
   }
}

ConcreteUtil::HsAvfOverSMinType ConcreteUtil::AvfOverSMin(Float64 bv, Float64 fy,const WBFL::System::SectionValue& Vuh,Float64 phi,Float64 c,Float64 u,Float64 pc)
{
   PRECONDITION(0.0 < fy);

   HsAvfOverSMinType hsAvfOverSMin;

   // All spec versions evaluate 5.8.4.4-1
   if ( BDSManager::GetUnits() == BDSManager::Units::SI )
   {
      Float64 bv_used = WBFL::Units::ConvertFromSysUnits(bv, WBFL::Units::Measure::Millimeter);
      Float64 fy_used = WBFL::Units::ConvertFromSysUnits(fy, WBFL::Units::Measure::MPa);
      if (BDSManager::GetEdition() == BDSManager::Edition::FirstEdition1994)
      {
         bv_used = min(bv_used, 900.0);
      }

      Float64 avf = 0.35 * bv_used / fy_used;

      Float64 avf_min = WBFL::Units::ConvertToSysUnits(avf, WBFL::Units::Measure::Millimeter);

      hsAvfOverSMin.res5_7_4_2_1 = avf_min;
      hsAvfOverSMin.AvfOverSMin  = avf_min;
   }
   else
   {
      Float64 bv_used = WBFL::Units::ConvertFromSysUnits(bv, WBFL::Units::Measure::Inch);
      Float64 fy_used = WBFL::Units::ConvertFromSysUnits(fy, WBFL::Units::Measure::KSI);
      if (BDSManager::GetEdition() == BDSManager::Edition::FirstEdition1994)
      {
         bv_used = min(bv_used, 36.0);
      }

      Float64 avf = 0.05 * bv_used / fy_used;

      Float64 avf_min = WBFL::Units::ConvertToSysUnits(avf, WBFL::Units::Measure::Inch);

      hsAvfOverSMin.res5_7_4_2_1 = avf_min;
      hsAvfOverSMin.AvfOverSMin  = avf_min;
   }

   if ( BDSManager::Edition::FourthEdition2007 <= BDSManager::GetEdition() )
   {
      // Addition requirements added in 4th edition
      hsAvfOverSMin.ValidEqns = HsAvfOverSMinType::ValidEqnsType::eqBoth;

      Float64 vuh = max(Vuh.Left(),Vuh.Right());

      // Equation 5.7.4.1-3 (pre 2017: 5.8.4.1-3)
      // this is a unit consistent equation... no unit conversions needed
      Float64 avf_min = (1.33*vuh - phi*(c*bv + u*pc))/(phi*u*fy);

      hsAvfOverSMin.res5_7_4_2_3 = avf_min;

      // Final is min of two equations
      hsAvfOverSMin.AvfOverSMin = min(hsAvfOverSMin.res5_7_4_2_3, hsAvfOverSMin.res5_7_4_2_1);

      // But, less than zero means the reinforcement isn't needed to satisfy strength
      // requirements. Set to zero if so
      if ( hsAvfOverSMin.AvfOverSMin  < 0.0 )
      {
         hsAvfOverSMin.AvfOverSMin  = 0.0;
      }
   }

   return hsAvfOverSMin;
}

Float64 ConcreteUtil::MaxStirrupSpacingForHoriz(Float64 Hg)
{
   if ( BDSManager::Edition::SeventhEdition2014 <= BDSManager::GetEdition() )
   {
      CHECK(BDSManager::GetUnits() == BDSManager::Units::US);
      return min(Hg, WBFL::Units::ConvertToSysUnits(48.0, WBFL::Units::Measure::Inch));
   }
   else
   {
      if ( BDSManager::GetUnits() == BDSManager::Units::SI )
      {
         return WBFL::Units::ConvertToSysUnits(0.6, WBFL::Units::Measure::Meter);
      }
      else
      {
         return WBFL::Units::ConvertToSysUnits(24.0, WBFL::Units::Measure::Inch);
      }
   }
}

Float64 ConcreteUtil::AvfRequiredForHoriz(const WBFL::System::SectionValue& Vuh, Float64 phi, Float64 AvfOverSMin,
                                              Float64 c, Float64 u, Float64 K1, Float64 K2,
                                              Float64 bv, Float64 Acv, Float64 Avf, Float64 Pc, 
                                              Float64 fc, Float64 fy)
{
   PRECONDITION(0 < phi);
   PRECONDITION(0 < fc);
   PRECONDITION(0 < fy);
   PRECONDITION(0 < u);

   Float64 vuh = max(Vuh.Left(),Vuh.Right());

   // Use existing function to get non-rebar related resistance values
   Float64 VnEnqn1, VnEnqn2, VnEnqn3; // Note that equation numbers have changed in most recent spec version 2009
   InterfaceShearResistances(c, u, K1, K2, Acv, Avf, Pc, fc, fy, &VnEnqn1, &VnEnqn2, &VnEnqn3);

   Float64 VnMax = min(VnEnqn2, VnEnqn3);

   if (VnMax < vuh/phi)
   {
      return Float64_Max; // we can't add enough steel to satisfy
   }
   else
   {
      // solve equation 1 for Av
      Float64 Avs_reqd = ( (vuh/phi - c*bv)/u - Pc )/fy;
      Avs_reqd = max(Avs_reqd, AvfOverSMin);

      return Avs_reqd;
   }
}

Float64 ConcreteUtil::ComputeConcreteDensityModificationFactor(WBFL::Materials::ConcreteType type,Float64 density,bool bHasFct,Float64 fct,Float64 fc)
{
   if ( BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2016Interims || type == WBFL::Materials::ConcreteType::Normal || type == WBFL::Materials::ConcreteType::PCI_UHPC || type == WBFL::Materials::ConcreteType::UHPC)
   {
      return 1.0;
   }

   Float64 lambda;
   if ( bHasFct )
   {
      fct = WBFL::Units::ConvertFromSysUnits(fct,WBFL::Units::Measure::KSI);
      fc  = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);
      lambda = 4.7*fct/sqrt(fc);
      lambda = ::ForceIntoRange(0.0,lambda,1.0);
   }
   else
   {
      density = WBFL::Units::ConvertFromSysUnits(density,WBFL::Units::Measure::KipPerFeet3);
      lambda = 7.5*density;
      lambda = ::ForceIntoRange(0.75,lambda,1.0);
   }
   return lambda;
}


std::_tstring ConcreteUtil::GetTypeName(WBFL::Materials::ConcreteType type,bool bFull)
{
   switch(type)
   {
   case WBFL::Materials::ConcreteType::Normal:
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");

   case WBFL::Materials::ConcreteType::AllLightweight:
      if ( bFull )
      {
         if ( BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2016Interims )
         {
            return _T("All Lightweight Concrete");
         }
         else
         {
            return _T("Lightweight Concrete");
         }
      }
      else
      {
         return _T("AllLightweight");
      }

   case WBFL::Materials::ConcreteType::SandLightweight:
      if ( bFull )
      {
         if ( BDSManager::GetEdition() < BDSManager::Edition::SeventhEditionWith2016Interims )
         {
            return _T("Sand Lightweight Concrete");
         }
         else
         {
            return _T("Lightweight Concrete");
         }
      }
      else
      {
         return _T("SandLightweight");
      }

   case WBFL::Materials::ConcreteType::PCI_UHPC:
      return bFull ? _T("PCI Ultra High Performance Concrete (PCI-UHPC)") : _T("PCI-UHPC");

   case WBFL::Materials::ConcreteType::UHPC:
      return bFull ? _T("Ultra High Performance Concrete (UHPC)") : _T("UHPC");

   default:
      CHECK(false); // is there a new type?
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");
   }
}

WBFL::Materials::ConcreteType ConcreteUtil::GetTypeFromTypeName(LPCTSTR strName)
{
   WBFL::Materials::ConcreteType type;
   if ( std::_tstring(strName) == _T("Normal") )
   {
      type = WBFL::Materials::ConcreteType::Normal;
   }
   else if ( std::_tstring(strName) == _T("AllLightweight") )
   {
      type = WBFL::Materials::ConcreteType::AllLightweight;
   }
   else if ( std::_tstring(strName) == _T("SandLightweight") )
   {
      type = WBFL::Materials::ConcreteType::SandLightweight;
   }
   else if (std::_tstring(strName) == _T("PCI-UHPC"))
   {
      type = WBFL::Materials::ConcreteType::PCI_UHPC;
   }
   else if (std::_tstring(strName) == _T("UHPC") || std::_tstring(strName) == _T("FHWA-UHPC"))
   {
      type = WBFL::Materials::ConcreteType::UHPC;
   }
   else
   {
      CHECK(false); // invalid name
      type = WBFL::Materials::ConcreteType::Normal;
   }

   if ( BDSManager::Edition::SeventhEditionWith2016Interims <= BDSManager::GetEdition() && type == WBFL::Materials::ConcreteType::AllLightweight )
   {
      // LRFD 2016 removed the distinction between Sand and All lightweight concrete. For a consistent application of the
      // concrete type, we will use SandLightweight to mean "Lightweight" for all lightweight cases
      type = WBFL::Materials::ConcreteType::SandLightweight;
   }

   return type;
}
