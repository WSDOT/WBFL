///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include <Lrfd\VersionMgr.h>
#include <System\XProgrammingError.h>
#include <array>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
static const Float64 g_p7_MPA    = ::ConvertToSysUnits(0.7,unitMeasure::MPa);
static const Float64 g_p52_MPA   = ::ConvertToSysUnits(0.52,unitMeasure::MPa);
static const Float64 g_1p9_MPA   = ::ConvertToSysUnits(1.9,unitMeasure::MPa);
static const Float64 g_5p5_MPA   = ::ConvertToSysUnits(5.5,unitMeasure::MPa);
static const Float64 g_9p0_MPA   = ::ConvertToSysUnits(9.0,unitMeasure::MPa);
static const Float64 g_12p4_MPA  = ::ConvertToSysUnits(12.4,unitMeasure::MPa);
static const Float64 g_14p0_MPA  = ::ConvertToSysUnits(14.0,unitMeasure::MPa);

static const Float64 g_p1_KSI    = ::ConvertToSysUnits(0.100,unitMeasure::KSI);
static const Float64 g_p2_KSI = ::ConvertToSysUnits(0.200, unitMeasure::KSI);
static const Float64 g_p5_KSI = ::ConvertToSysUnits(0.500, unitMeasure::KSI);
static const Float64 g_p210_KSI  = ::ConvertToSysUnits(0.210,unitMeasure::KSI);
static const Float64 g_p240_KSI = ::ConvertToSysUnits(0.240, unitMeasure::KSI);
static const Float64 g_p280_KSI  = ::ConvertToSysUnits(0.280,unitMeasure::KSI);
static const Float64 g_p025_KSI = ::ConvertToSysUnits(0.025, unitMeasure::KSI);
static const Float64 g_p075_KSI = ::ConvertToSysUnits(0.075, unitMeasure::KSI);
static const Float64 g_p8_KSI    = ::ConvertToSysUnits(0.8,unitMeasure::KSI);
static const Float64 g_1p3_KSI = ::ConvertToSysUnits(1.3, unitMeasure::KSI);
static const Float64 g_1p5_KSI = ::ConvertToSysUnits(1.5, unitMeasure::KSI);
static const Float64 g_1p8_KSI   = ::ConvertToSysUnits(1.8,unitMeasure::KSI);
static const Float64 g_3p6_KSI = ::ConvertToSysUnits(3.6, unitMeasure::KSI);
static const Float64 g_60_KSI    = ::ConvertToSysUnits(60.0,unitMeasure::KSI);

static const Float64 g_0p6_M = ::ConvertToSysUnits(0.6, unitMeasure::Meter);
static const Float64 g_0p9_M = ::ConvertToSysUnits(0.9, unitMeasure::Meter);

static const Float64 g_48_IN = ::ConvertToSysUnits(48.0, unitMeasure::Inch);
static const Float64 g_36_IN = ::ConvertToSysUnits(36.0, unitMeasure::Inch);
static const Float64 g_24_IN = ::ConvertToSysUnits(24.0, unitMeasure::Inch);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdConcreteUtil::~lrfdConcreteUtil()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
Float64 lrfdConcreteUtil::GetNWCDensityLimit()
{
   Float64 limit;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US )
   {
      limit = ::ConvertToSysUnits(135.0,unitMeasure::LbfPerFeet3);
   }
   else
   {
      limit = ::ConvertToSysUnits(2150.0,unitMeasure::KgPerMeter3);
   }

   return limit;
}

Float64 lrfdConcreteUtil::GetLWCDensityLimit()
{
   Float64 limit;
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2016Interims )
   {
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US )
      {
         limit = ::ConvertToSysUnits(120.0,unitMeasure::LbfPerFeet3);
      }
      else
      {
         limit = ::ConvertToSysUnits(1925.0,unitMeasure::KgPerMeter3);
      }
   }
   else
   {
      limit = lrfdConcreteUtil::GetNWCDensityLimit();
   }

   return limit;
}

void lrfdConcreteUtil::GetPCIUHPCStrengthRange(Float64* pFcMin, Float64* pFcMax)
{
   // See "Compression Response of a Rapid-Strengthening Ultra-High Performance Concrete Formulation"
   // FHWA Publication FHWA-HRT-12-964
   // Graybeal
   //*pFcMin = ::ConvertToSysUnits(14.0, unitMeasure::KSI);
   //*pFcMax = ::ConvertToSysUnits(26.0, unitMeasure::KSI);

   // PCI-UHPC Structural Guidance, min f'c = 17.4 ksi, no max provided so use a really high value that wont be exceeded
   *pFcMin = ::ConvertToSysUnits(17.4, unitMeasure::KSI);
   *pFcMax = ::ConvertToSysUnits(99999.0, unitMeasure::KSI);
}

void lrfdConcreteUtil::GetPCIUHPCMinProperties(Float64* pfcMin, Float64* pffc, Float64* pfpeak, Float64* pfrr)
{
   Float64 fcMax;
   GetPCIUHPCStrengthRange(pfcMin, &fcMax);
   *pffc = ::ConvertToSysUnits(1.5, unitMeasure::KSI);
   *pfpeak = ::ConvertToSysUnits(2.0, unitMeasure::KSI);
   *pfrr = ::ConvertToSysUnits(0.75, unitMeasure::KSI);
}

Float64 lrfdConcreteUtil::ModE(matConcrete::Type type,Float64 fc,Float64 density,bool bCheckRange)
{
   Float64 e;  // modulus of elasticity in System Units
   if (type == matConcrete::PCI_UHPC)
   {
      Float64 Fc = ::ConvertFromSysUnits(fc, unitMeasure::KSI);
      Float64 Ec = 2500 * pow(Fc,0.33); // Fc in KSI, Ec in KSI (This is LRFD Equation C5.4.2.4-1)
      e = ::ConvertToSysUnits(Ec, unitMeasure::KSI);
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
      const unitStress*  p_fc_unit;
      const unitDensity* p_density_unit;
      const unitStress*  p_E_unit;

      if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
      {
         p_fc_unit = &unitMeasure::MPa;
         p_density_unit = &unitMeasure::KgPerMeter3;
         p_E_unit = &unitMeasure::MPa;

         k = 0.043;

         min_density = 1440.; // kg/m^3
         max_density = 2500.; // kg/m^3
      }
      else
      {
         // :NOTE: 1 lbm = 1 lbf
         p_fc_unit = &unitMeasure::KSI;
         p_density_unit = &unitMeasure::KipPerFeet3;
         p_E_unit = &unitMeasure::KSI;

         if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims)
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
      Fc = ::ConvertFromSysUnits(fc, *p_fc_unit);
      Density = ::ConvertFromSysUnits(density, *p_density_unit);


      // Make sure the density range hasn't been violated.
      if (bCheckRange)
      {
         min_density = ::ConvertToSysUnits(min_density, *p_density_unit);
         max_density = ::ConvertToSysUnits(max_density, *p_density_unit);
         if (!InRange(min_density, density, max_density))
         {
            THROW(sysXProgrammingError, ValueOutOfRange);
         }
      }

      if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims)
      {
         E = k * pow(Density, 1.5) * sqrt(Fc);
      }
      else
      {
         E = k*pow(Density, 2.0)*pow(Fc, 0.33);
      }

      // Convert output to system units.
      e = ::ConvertToSysUnits(E, *p_E_unit);
   }

   return e;
}

Float64 lrfdConcreteUtil::FcFromEc(matConcrete::Type type, Float64 ec,Float64 density)
{
   Float64 fc;          // fc in system units

   if (type == matConcrete::PCI_UHPC)
   {
      Float64 Ec = ::ConvertFromSysUnits(ec, unitMeasure::KSI);
      Float64 Fc = pow(Ec / 2500., 2);
      fc = ::ConvertToSysUnits(Fc, unitMeasure::KSI);
   }
   else
   {
      Float64 Fc;          // fc in spec units
      Float64 Density;     // density in spec units
      Float64 Ec;          // Modulus of elasticity in spec units
      Float64 k;           // coefficient in equation

      // Input units
      const unitStress*  p_fc_unit;
      const unitDensity* p_density_unit;
      const unitStress*  p_E_unit;

      if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
      {
         p_fc_unit = &unitMeasure::MPa;
         p_density_unit = &unitMeasure::KgPerMeter3;
         p_E_unit = &unitMeasure::MPa;

         k = 0.043;
      }
      else
      {
         // :NOTE: 1 lbm = 1 lbf
         p_fc_unit = &unitMeasure::KSI;
         p_density_unit = &unitMeasure::KipPerFeet3;
         p_E_unit = &unitMeasure::KSI;

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
      Ec = ::ConvertFromSysUnits(ec, *p_E_unit);
      Density = ::ConvertFromSysUnits(density, *p_density_unit);

      if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims)
      {
         Fc = pow(Ec / (k*pow(Density, 1.5)), 2);
      }
      else
      {
         Fc = pow(Ec / (k*pow(Density, 2)), 1 / 0.33);
      }

      // Convert output to system units.
      fc = ::ConvertToSysUnits(Fc, *p_fc_unit);
   }

   return fc;
}

Float64 lrfdConcreteUtil::ModRupture(Float64 fc, Float64 k)
{
   return lrfdConcreteUtil::ModRupture(fc,matConcrete::Normal,k);
}

Float64 lrfdConcreteUtil::ModRupture(Float64 fc, matConcrete::Type concType)
{
   return lrfdConcreteUtil::ModRupture(fc,concType,-1);
}

Float64 lrfdConcreteUtil::ModRupture(Float64 fc, matConcrete::Type concType,Float64 k)
{
   const unitStress* p_fc_unit;
   const unitStress* p_fr_unit;
   const unitSqrtPressure* p_coefficient_unit;

   bool is_si = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   if ( is_si )
   {
      p_fc_unit = &unitMeasure::MPa;
      p_fr_unit = &unitMeasure::MPa;
      p_coefficient_unit = &unitMeasure::SqrtMPa;
   }
   else
   {
      p_fc_unit = &unitMeasure::KSI;
      p_fr_unit = &unitMeasure::KSI;
      p_coefficient_unit = &unitMeasure::SqrtKSI;
   }
      

   bool bAfter2004 = (lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion());
   if ( k <= 0 )
   {
      switch( concType )
      {
      case matConcrete::Normal:
         if ( bAfter2004 )
         {
            k = (is_si) ? 0.97 : 0.37;
         }
         else
         {
            k = (is_si) ? 0.63 : 0.24;
         }
         break;

      case matConcrete::SandLightweight:
         k = (is_si) ? 0.52 : 0.20;
         break;

      case matConcrete::Type::AllLightweight:
         k = (is_si) ? 0.45 : 0.17;
         break;

      default:
         CHECK(false);
      }
   }
   else
   {
      k = ::ConvertFromSysUnits(k,*p_coefficient_unit);
   }

   // Convert fc to the proper units
   fc = ::ConvertFromSysUnits( fc, *p_fc_unit );

   Float64 fr = k * sqrt( fc );

   // Convert fr to system units
   fr = ::ConvertToSysUnits( fr, *p_fr_unit );

   return fr;
}

Float64 lrfdConcreteUtil::Beta1(Float64 fc)
{
   const unitStress* p_fc_unit;
   Float64 fc_limit;
   Float64 fc_step;

   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      p_fc_unit = &unitMeasure::MPa;
      fc_limit = 28.; // MPa
      fc_step  =  7.; // MPa
   }
   else
   {
      p_fc_unit = &unitMeasure::PSI;
      fc_limit = 4000.; // psi
      fc_step  = 1000.; // psi
   }

   // Convert fc to the required units
   fc = ::ConvertFromSysUnits( fc, *p_fc_unit );

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

void lrfdConcreteUtil::InterfaceShearParameters(bool isRoughened, matConcrete::Type girderConcType, matConcrete::Type deckConcType, Float64* pC, Float64* pU, Float64* pK1, Float64* pK2)
{
   if (girderConcType == matConcrete::PCI_UHPC)
   {
      if (deckConcType == matConcrete::PCI_UHPC)
      {
         // UHPC deck on UHPC girder, PCI SDG Table 7.4.3-1 Case 8 and 9
         *pC = (isRoughened ? g_p5_KSI : g_p2_KSI);
         *pU = (isRoughened ? 1.4 : 0.6);
         *pK1 = (isRoughened ? 0.3 : 0.2);
         *pK2 = (isRoughened ? g_3p6_KSI : g_3p6_KSI);
      }
      else
      {
         // conventional deck concrete on UHPC girder, PCI SDG Table 7.4.3-1 Case 4 and 6
         *pC = (isRoughened ? g_p240_KSI : g_p025_KSI);
         *pU = (isRoughened ? 1.0 : 0.7);
         *pK1 = (isRoughened ? 0.25 : 0.20);
         *pK2 = (isRoughened ? g_1p5_KSI : g_p8_KSI);
      }
   }
   else
   {
      // conventional concrete girder

      // C
      if (lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::ThirdEditionWith2006Interims)
      {
         if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI)
         {
            *pC = (isRoughened ? g_p7_MPA : g_p52_MPA);
         }
         else
         {
            *pC = (isRoughened ? g_p1_KSI : g_p075_KSI);
         }
      }
      else
      {
         // LRFD 2007 or later
         if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US)
         {
            *pC = (isRoughened ? g_p280_KSI : g_p075_KSI);
         }
         else
         {
            *pC = (isRoughened ? g_1p9_MPA : g_p52_MPA);
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

      if (lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::ThirdEditionWith2006Interims)
      {
         std::array<Float64, 4> Lamda{ 1.0, 0.85, 0.75, 1.0 };
         Float64 lambda = min(Lamda[girderConcType], Lamda[deckConcType]);
         *pU *= lambda;
      }

      // K1
      if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007)
      {
         *pK1 = 0.2;
      }
      else
      {
         *pK1 = (isRoughened ? 0.3 : 0.2);
      }

      // K2
      if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007)
      {
         *pK2 = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI) ? g_5p5_MPA : g_p8_KSI;
      }
      else
      {
         bool bIsNWC = (girderConcType == matConcrete::Normal && deckConcType == matConcrete::Normal);
         if (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US)
         {
            if (isRoughened)
            {
               *pK2 = (bIsNWC ? g_1p8_KSI : g_1p3_KSI);
            }
            else
            {
               *pK2 = g_p8_KSI;
            }
         }
         else
         {
            if (isRoughened)
            {
               *pK2 = (bIsNWC ? g_12p4_MPA : g_9p0_MPA);
            }
            else
            {
               *pK2 = g_5p5_MPA;
            }
         }
      }
   }
}

void lrfdConcreteUtil::InterfaceShearResistances(Float64 c, Float64 u, Float64 K1, Float64 K2,
                                                  Float64 Acv, Float64 Avf, Float64 Pc,
                                                  Float64 fc, Float64 fy,
                                                  Float64* penqn1, Float64* penqn2, Float64* penqn3)
{
   // nominal shear capacity 5.8.4.1-1,2
   if ( lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::SixthEditionWith2013Interims )
   {
      fy = min(fy,g_60_KSI);
   }

   Float64 Vn1 = c*Acv + u*(Avf * fy + Pc);
   Float64 Vn2 = K1 * fc * Acv;

   *penqn1= Vn1;
   *penqn2= Vn2;

   // nominal shear capacity 5.8.4.1-3
   *penqn3 = K2*Acv;
}

Float64 lrfdConcreteUtil::LowerLimitOfShearStrength(bool isRoughened, bool doAllStirrupsEngageDeck)
{
   if ( lrfdVersionMgr::FourthEdition2007 <= lrfdVersionMgr::GetVersion() )
   {
      // 4th edition or later
      if (isRoughened && doAllStirrupsEngageDeck)
      {
         if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
         {
            return g_14p0_MPA;
         }
         else
         {
            return g_p210_KSI;
         }
      }
      else
      {
         return 0.0;
      }
   }
   else if (lrfdVersionMgr::SecondEdition1998 <= lrfdVersionMgr::GetVersion())
   {
      // 2nd edition or later (but not 4th or later)

      // 2nd to 4th it didn't matter if surface was roughened
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         return g_p7_MPA;
      }
      else
      {
         return g_p1_KSI;
      }
   }
   else
   {
      // all other versions have no such limit
      return 0.0;
   }
}

Float64 lrfdConcreteUtil::UpperLimitForBv()
{
   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SecondEdition1998)
   {
      // This requirement was removed in the 1998 Section Edition
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         return g_0p9_M;
      }
      else
      {
         return g_36_IN;
      }
   }
   else
   {
      // all other versions have no such limit
      return Float64_Max;
   }
}

Uint16 lrfdConcreteUtil::MinLegsForBv(Float64 bv)
{
   Float64 upper_bv = UpperLimitForBv();
   if (bv >= upper_bv)
   {
      return 4;
   }
   else
   {
      return 1;
   }
}

lrfdConcreteUtil::HsAvfOverSMinType lrfdConcreteUtil::AvfOverSMin(Float64 bv, Float64 fy,const sysSectionValue& Vuh,Float64 phi,Float64 c,Float64 u,Float64 pc)
{
   CHECK(fy>0.0);

   HsAvfOverSMinType hsAvfOverSMin;

   // All spec versions evalulate 5.8.4.4-1
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      Float64 bv_used = ::ConvertFromSysUnits(bv, unitMeasure::Millimeter);
      Float64 fy_used = ::ConvertFromSysUnits(fy, unitMeasure::MPa);
      if (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994)
      {
         bv_used = min(bv_used, 900.0);
      }

      Float64 avf = 0.35 * bv_used / fy_used;

      Float64 avf_min = ::ConvertToSysUnits(avf, unitMeasure::Millimeter);

      hsAvfOverSMin.res5_7_4_2_1 = avf_min;
      hsAvfOverSMin.AvfOverSMin  = avf_min;
   }
   else
   {
      Float64 bv_used = ::ConvertFromSysUnits(bv, unitMeasure::Inch);
      Float64 fy_used = ::ConvertFromSysUnits(fy, unitMeasure::KSI);
      if (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994)
      {
         bv_used = min(bv_used, 36.0);
      }

      Float64 avf = 0.05 * bv_used / fy_used;

      Float64 avf_min = ::ConvertToSysUnits(avf, unitMeasure::Inch);

      hsAvfOverSMin.res5_7_4_2_1 = avf_min;
      hsAvfOverSMin.AvfOverSMin  = avf_min;
   }

   if ( lrfdVersionMgr::FourthEdition2007 <= lrfdVersionMgr::GetVersion() )
   {
      // Addition requirements added in 4th edition
      hsAvfOverSMin.ValidEqns = HsAvfOverSMinType::eqBoth;

      Float64 vuh = max(Vuh.Left(),Vuh.Right());

      // Equation 5.7.4.1-3 (pre 2017: 5.8.4.1-3)
      // this is a unit consistent equation... no unit conversions needed
      Float64 avf_min = (1.33*vuh - phi*(c*bv + u*pc))/(phi*u*fy);

      hsAvfOverSMin.res5_7_4_2_3 = avf_min;

      // Final is min of two equations
      hsAvfOverSMin.AvfOverSMin = min(hsAvfOverSMin.res5_7_4_2_3, hsAvfOverSMin.res5_7_4_2_1);

      // But, less than zero means the reinforcement isn't needed to satify strength
      // requirements. Set to zero if so
      if ( hsAvfOverSMin.AvfOverSMin  < 0.0 )
      {
         hsAvfOverSMin.AvfOverSMin  = 0.0;
      }
   }

   return hsAvfOverSMin;
}

Float64 lrfdConcreteUtil::MaxStirrupSpacingForHoriz(Float64 Hg)
{
   if ( lrfdVersionMgr::SeventhEdition2014 <= lrfdVersionMgr::GetVersion() )
   {
      ATLASSERT(lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US);
      return min(Hg,g_48_IN);
   }
   else
   {
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         return g_0p6_M;
      }
      else
      {
         return g_24_IN;
      }
   }
}

Float64 lrfdConcreteUtil::AvfRequiredForHoriz(const sysSectionValue& Vuh, Float64 phi, Float64 AvfOverSMin,
                                              Float64 c, Float64 u, Float64 K1, Float64 K2,
                                              Float64 bv, Float64 Acv, Float64 Avf, Float64 Pc, 
                                              Float64 fc, Float64 fy)
{
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
      // solve eqn 1 for Av
      Float64 Avs_reqd = ( (vuh/phi - c*bv)/u - Pc )/fy;
      Avs_reqd = max(Avs_reqd, AvfOverSMin);

      return Avs_reqd;
   }
}

Float64 lrfdConcreteUtil::ComputeConcreteDensityModificationFactor(matConcrete::Type type,Float64 density,bool bHasFct,Float64 fct,Float64 fc)
{
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2016Interims || type == matConcrete::Normal || type == matConcrete::PCI_UHPC)
   {
      return 1.0;
   }

   Float64 lambda;
   if ( bHasFct )
   {
      fct = ::ConvertFromSysUnits(fct,unitMeasure::KSI);
      fc  = ::ConvertFromSysUnits(fc,unitMeasure::KSI);
      lambda = 4.7*fct/sqrt(fc);
      lambda = ::ForceIntoRange(0.0,lambda,1.0);
   }
   else
   {
      density = ::ConvertFromSysUnits(density,unitMeasure::KipPerFeet3);
      lambda = 7.5*density;
      lambda = ::ForceIntoRange(0.75,lambda,1.0);
   }
   return lambda;
}


std::_tstring lrfdConcreteUtil::GetTypeName(matConcrete::Type type,bool bFull)
{
   switch(type)
   {
   case matConcrete::Normal:
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");

   case matConcrete::AllLightweight:
      if ( bFull )
      {
         if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2016Interims )
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

   case matConcrete::SandLightweight:
      if ( bFull )
      {
         if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2016Interims )
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

   case matConcrete::PCI_UHPC:
      return bFull ? _T("PCI Ultra High Performance Concrete (PCI-UHPC)") : _T("PCI-UHPC");

   default:
      ATLASSERT(false); // is there a new type?
      return bFull ? _T("Normal Weight Concrete") : _T("Normal");
   }
}

matConcrete::Type lrfdConcreteUtil::GetTypeFromTypeName(LPCTSTR strName)
{
   matConcrete::Type type;
   if ( std::_tstring(strName) == _T("Normal") )
   {
      type = matConcrete::Normal;
   }
   else if ( std::_tstring(strName) == _T("AllLightweight") )
   {
      type = matConcrete::AllLightweight;
   }
   else if ( std::_tstring(strName) == _T("SandLightweight") )
   {
      type = matConcrete::SandLightweight;
   }
   else if (std::_tstring(strName) == _T("PCI-UHPC"))
   {
      type = matConcrete::PCI_UHPC;
   }
   else
   {
      ATLASSERT(false); // invalid name
      type = matConcrete::Normal;
   }

   if ( lrfdVersionMgr::SeventhEditionWith2016Interims <= lrfdVersionMgr::GetVersion() && type == matConcrete::AllLightweight )
   {
      // LRFD 2016 removed the distinction between Sand and All lightweight concrete. For a consistent application of the
      // concrete type, we will use SandLightweight to mean "Lightweight" for all lightweight cases
      type = matConcrete::SandLightweight;
   }

   return type;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================
#if defined _UNITTEST
#include <Lrfd\AutoVersion.h>
#include <Units\AutoSysUnits.h>
bool lrfdConcreteUtil::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdConcreteUtil");

   // Before we do any testing, get the current code version and units
   lrfdAutoVersion av;
   unitAutoSysUnits au;

   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);

   // We want to work in kg,m,s,C,rad
   unitSysUnitsMgr::SetMassUnit( unitMeasure::Kilogram );
   unitSysUnitsMgr::SetLengthUnit( unitMeasure::Meter );
   unitSysUnitsMgr::SetTimeUnit( unitMeasure::Second );
   unitSysUnitsMgr::SetTemperatureUnit( unitMeasure::Celcius );
   unitSysUnitsMgr::SetAngleUnit( unitMeasure::Radian );

   //
   // Test Beta1
   //
   TRY_TESTME (  IsEqual( Beta1(0.1), 0.85 ) );

   lrfdVersionMgr::SetUnits( lrfdVersionMgr::SI );
   TRY_TESTME (  IsEqual( Beta1(60e6), 0.65 ) );

   lrfdVersionMgr::SetUnits( lrfdVersionMgr::US );
   TRY_TESTME (  IsEqual( Beta1(60e6), 0.65 ) );

   //
   // Test ModRupture
   //
   Float64 fc = 50e6; // 50 MPa
   lrfdVersionMgr::SetUnits( lrfdVersionMgr::SI );
   TRY_TESTME (  IsEqual(ModRupture( fc, matConcrete::Normal ), 4.45477272148e6, 0.1 ) );
   TRY_TESTME (  IsEqual(ModRupture( fc, matConcrete::SandLightweight ), 3.67695526217e6, 0.1 ) );
   TRY_TESTME (  IsEqual(ModRupture( fc, matConcrete::AllLightweight ), 3.18198051534e6, 0.1 ) );

   //
   // Test ModE
   //
   lrfdVersionMgr::SetUnits( lrfdVersionMgr::SI );
   Float64 density = 2450.; // kg/m^3
   try
   {
      TRY_TESTME (  IsEqual( ModE(matConcrete::Normal, fc,density), 36872.5e6, 1. ) );
   }
   catch (...)
   {
      // An exception should not be thrown
      TRY_TESTME(false);
   }

   density = 2560.; // this will cause an exception to be thrown
   try 
   {
      ModE(matConcrete::Normal, fc,density);
      ; // We shouldn't hit this code
   }
   catch(const sysXProgrammingError& e)
   {
      // Do nothing
      TRY_TESTME(e.GetReasonCode() == sysXProgrammingError::ValueOutOfRange);
   }
   
   TESTME_EPILOG("lrfdConcreteUtil");
}
#endif // _UNITTEST


