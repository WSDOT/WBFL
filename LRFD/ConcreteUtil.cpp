///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include <Units\SysUnits.h>
#include <System\XProgrammingError.h>
#include <MathEx.h>

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
static const Float64 g_p210_KSI  = ::ConvertToSysUnits(0.210,unitMeasure::KSI);
static const Float64 g_p280_KSI  = ::ConvertToSysUnits(0.280,unitMeasure::KSI);
static const Float64 g_p075_KSI  = ::ConvertToSysUnits(0.075,unitMeasure::KSI);
static const Float64 g_p8_KSI    = ::ConvertToSysUnits(0.8,unitMeasure::KSI);
static const Float64 g_1p3_KSI   = ::ConvertToSysUnits(1.3,unitMeasure::KSI);
static const Float64 g_1p8_KSI   = ::ConvertToSysUnits(1.8,unitMeasure::KSI);

static const Float64 g_0p6_M = ::ConvertToSysUnits(0.6, unitMeasure::Meter);
static const Float64 g_0p9_M = ::ConvertToSysUnits(0.9, unitMeasure::Meter);

static const Float64 g_36_IN = ::ConvertToSysUnits(36.0, unitMeasure::Inch);

static const Float64 g_2_FT = ::ConvertToSysUnits(2.0, unitMeasure::Feet);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdConcreteUtil::~lrfdConcreteUtil()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
Float64 lrfdConcreteUtil::ModE(Float64 fc,Float64 density,bool bCheckRange)
{
   PRECONDITION( fc > 0 );
   PRECONDITION( density > 0 );

   Float64 Fc;          // fc in spec units
   Float64 Density;     // density in spec units
   Float64 E;           // Modulus of elasticity in spec units
   Float64 e;           // modulus of elasticity in System Units
   Float64 k;           // coefficient in equation
   Float64 min_density; // minimum density in System Units
   Float64 max_density; // maximum density in System Units

   // Input units
   const unitStress*  p_fc_unit;
   const unitDensity* p_density_unit;
   const unitStress*  p_E_unit;

   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      p_fc_unit      = &unitMeasure::MPa;
      p_density_unit = &unitMeasure::KgPerMeter3;
      p_E_unit       = &unitMeasure::MPa;

      k = 0.043;

      min_density = 1440.; // kg/m^3
      max_density = 2500.; // kg/m^3
   }
   else
   {
      // :NOTE: 1 lbm = 1 lbf
      p_fc_unit      = &unitMeasure::PSI;
      p_density_unit = &unitMeasure::LbmPerFeet3;
      p_E_unit       = &unitMeasure::PSI;

      k = 33.;

      min_density =  90.; // pcf
      max_density = 155.; // pcf
   }

   // Convert input to required units
   Fc      = ::ConvertFromSysUnits( fc,      *p_fc_unit      );
   Density = ::ConvertFromSysUnits( density, *p_density_unit );


   // Make sure the density range hasn't been violated.
   min_density = ::ConvertToSysUnits( min_density, *p_density_unit );
   max_density = ::ConvertToSysUnits( max_density, *p_density_unit );
   if ( bCheckRange && !InRange( min_density, density, max_density ) )
      THROW(sysXProgrammingError,ValueOutOfRange);

   E = k * pow( Density, 1.5 ) * sqrt( Fc );

   // Convert output to system units.
   e = ::ConvertToSysUnits( E, *p_E_unit );

   return e;
}

Float64 lrfdConcreteUtil::FcFromEc(Float64 ec,Float64 density)
{
   PRECONDITION( ec > 0 );
   PRECONDITION( density > 0 );

   Float64 Fc;          // fc in spec units
   Float64 fc;          // fc in system units
   Float64 Density;     // density in spec units
   Float64 Ec;          // Modulus of elasticity in spec units
   Float64 k;           // coefficient in equation

   // Input units
   const unitStress*  p_fc_unit;
   const unitDensity* p_density_unit;
   const unitStress*  p_E_unit;

   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      p_fc_unit      = &unitMeasure::MPa;
      p_density_unit = &unitMeasure::KgPerMeter3;
      p_E_unit       = &unitMeasure::MPa;

      k = 0.043;
   }
   else
   {
      // :NOTE: 1 lbm = 1 lbf
      p_fc_unit      = &unitMeasure::PSI;
      p_density_unit = &unitMeasure::LbmPerFeet3;
      p_E_unit       = &unitMeasure::PSI;

      k = 33.;
   }

   // Convert input to required units
   Ec      = ::ConvertFromSysUnits( ec,      *p_E_unit      );
   Density = ::ConvertFromSysUnits( density, *p_density_unit );

   Fc = pow(Ec/(k*pow(Density,1.5)),2);

   // Convert output to system units.
   fc = ::ConvertToSysUnits( Fc, *p_fc_unit );

   return fc;
}

Float64 lrfdConcreteUtil::ModRupture(Float64 fc, DensityType densityType,Float64 k)
{
   PRECONDITION( fc > 0 );

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
      switch( densityType )
      {
      case NormalDensity:
         if ( bAfter2004 )
            k = (is_si) ? 0.97 : 0.37;
         else
            k = (is_si) ? 0.63 : 0.24;
         break;

      case SandLowDensity:
         k = (is_si) ? 0.52 : 0.20;
         break;

      case AllLowDensity:
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
   PRECONDITION( fc > 0 );

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

Float64 lrfdConcreteUtil::ShearFrictionFactor(bool isRoughened)
{
   // friction factor, MU
   if (isRoughened)
      return 1.0; // from 5.8.4.3 - first bullet
   else
      return 0.6; // from 5.8.4.3 - 5th bullet
}

Float64 lrfdConcreteUtil::ShearCohesionFactor(bool isRoughened,lrfdConcreteUtil::DensityType girderDensityType,lrfdConcreteUtil::DensityType slabDensityType)
{
   // LRFD 5.8.4.2
   if ( lrfdVersionMgr::GetVersion() <= lrfdVersionMgr::ThirdEditionWith2006Interims )
   {
      Float64 Lamda[3] = { 1.0, 0.85, 0.75 };
      Float64 lamda = min(Lamda[girderDensityType],Lamda[slabDensityType]);

      Float64 c;
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         if (isRoughened)
            c = g_p7_MPA;
         else
            c =g_p52_MPA;
      }
      else
      {
         if (isRoughened)
            c = g_p1_KSI;
         else
            c = g_p075_KSI;
      }

      return c*lamda;
   }
   else
   {
      // LRFD 2007 or later
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US )
      {
         if (isRoughened)
         {
            return g_p280_KSI;
         }
         else
         {
            return g_p075_KSI;
         }
      }
      else
      {
         if (isRoughened)
         {
            return g_1p9_MPA;
         }
         else
         {
            return g_p52_MPA;
         }
      }
   }
}

Float64 lrfdConcreteUtil::HorizShearK1(bool isRoughened)
{
   Float64 K1;
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007 )
   {
      K1 = 0.2;
   }
   else
   {
      if ( isRoughened )
      {
         K1 = 0.3;
      }
      else
      {
         K1 = 0.2;
      }
   }

   return K1;
}

Float64 lrfdConcreteUtil::HorizShearK2(bool isRoughened,lrfdConcreteUtil::DensityType girderDensityType,lrfdConcreteUtil::DensityType slabDensityType)
{
   Float64 K2;

   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007 )
   {
      K2 = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI) ? g_5p5_MPA : g_p8_KSI;
   }
   else
   {
      bool bIsNWC = ( girderDensityType == lrfdConcreteUtil::NormalDensity && slabDensityType == lrfdConcreteUtil::NormalDensity );
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US )
      {
         if ( isRoughened )
         {
            K2 = (bIsNWC ? g_1p8_KSI : g_1p3_KSI );
         }
         else
         {
            K2 = g_p8_KSI;
         }
      }
      else
      {
         if ( isRoughened )
         {
            K2 = (bIsNWC ? g_12p4_MPA : g_9p0_MPA );
         }
         else
         {
            K2 = g_5p5_MPA;
         }
      }
   }

   return K2;
}

void lrfdConcreteUtil::HorizontalShearResistances(Float64 c, Float64 u, Float64 K1, Float64 K2,
                                                  Float64 Acv, Float64 Avf, Float64 Pc,
                                                  Float64 fc, Float64 fy,
                                                  Float64* penqn1, Float64* penqn2, Float64* penqn3)
{
   // nominal shear capacity 5.8.4.1-1,2
   Float64 Vn1 = c*Acv + u*(Avf * fy + Pc);
   Float64 Vn2 = K1 * fc * Acv;

   *penqn1= Vn1;
   *penqn2= Vn2;

   // nominal shear capacity 5.8.4.1-3
   *penqn3 = K2*Acv;
}

Float64 lrfdConcreteUtil::LowerLimitOfShearStrength(bool isRoughened)
{
   if ( lrfdVersionMgr::FourthEdition2007 <= lrfdVersionMgr::GetVersion() )
   {
      // 4th edition or later
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         return isRoughened ? g_14p0_MPA : 0.0;
      }
      else
      {
         return isRoughened ? g_p210_KSI : 0.0;
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
      return 4;
   else
      return 1;
}

Float64 lrfdConcreteUtil::AvfOverSMin(Float64 bv, Float64 fy,const sysSectionValue& Vuh,Float64 phi,Float64 c,Float64 u,Float64 pc)
{
   CHECK(fy>0.0);

   Float64 avf_min;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      Float64 bv_used = ::ConvertFromSysUnits(bv, unitMeasure::Millimeter);
      Float64 fy_used = ::ConvertFromSysUnits(fy, unitMeasure::MPa);
      if (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994)
         bv_used = min(bv_used, 900.0);

      Float64 avf = 0.35 * bv_used / fy_used;

      avf_min = ::ConvertToSysUnits(avf, unitMeasure::Millimeter);
   }
   else
   {
      Float64 bv_used = ::ConvertFromSysUnits(bv, unitMeasure::Inch);
      Float64 fy_used = ::ConvertFromSysUnits(fy, unitMeasure::KSI);
      if (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994)
         bv_used = min(bv_used, 36.0);

      Float64 avf = 0.05 * bv_used / fy_used;

      avf_min = ::ConvertToSysUnits(avf, unitMeasure::Inch);
   }

   if ( lrfdVersionMgr::FourthEdition2007 <= lrfdVersionMgr::GetVersion() )
   {
      // addition requirements added in 4th edition

      Float64 avf_min_max; // maximum value of avf_min

      Float64 vuh = max(Vuh.Left(),Vuh.Right());

      // this is a unit consistent equation... no unit conversions needed
      avf_min_max = (1.33*vuh - phi*(c*bv + u*pc))/(phi*u*fy);

      // less than zero means the reinforcement isn't needed to satify strength
      // requirements
      if ( avf_min_max < 0 )
         avf_min_max = 0;

      avf_min = min(avf_min, avf_min_max);
   }

   return avf_min;
}

Float64 lrfdConcreteUtil::MaxStirrupSpacingForHoriz()
{
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      return g_0p6_M;
   else
      return g_2_FT;
}

Float64 lrfdConcreteUtil::AvfRequiredForHoriz(const sysSectionValue& Vuh, Float64 phi, Float64 AvfOverSMin,
                                              Float64 c, Float64 u, Float64 K1, Float64 K2,
                                              Float64 bv, Float64 Acv, Float64 Avf, Float64 Pc, 
                                              Float64 fc, Float64 fy)
{
   Float64 vuh = max(Vuh.Left(),Vuh.Right());

   // Use existing function to get non-rebar related resistance values
   Float64 VnEnqn1, VnEnqn2, VnEnqn3; // Note that equation numbers have changed in most recent spec version 2009
   HorizontalShearResistances(c, u, K1, K2, Acv, Avf, Pc, fc, fy, &VnEnqn1, &VnEnqn2, &VnEnqn3);

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
   TRY_TESTME (  IsEqual(ModRupture( fc, NormalDensity ), 4.45477272148e6, 0.1 ) );
   TRY_TESTME (  IsEqual(ModRupture( fc, SandLowDensity ), 3.67695526217e6, 0.1 ) );
   TRY_TESTME (  IsEqual(ModRupture( fc, AllLowDensity ), 3.18198051534e6, 0.1 ) );

   //
   // Test ModE
   //
   lrfdVersionMgr::SetUnits( lrfdVersionMgr::SI );
   Float64 density = 2450.; // kg/m^3
   try
   {
      TRY_TESTME (  IsEqual( ModE(fc,density), 36872.5e6, 1. ) );
   }
   catch (...)
   {
      // An exception should not be thrown
      TRY_TESTME(false);
   }

   density = 2560.; // this will cause an exception to be thrown
   try 
   {
      ModE(fc,density);
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


