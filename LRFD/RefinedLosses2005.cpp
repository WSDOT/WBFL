///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
#include <Lrfd\RefinedLosses2005.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\XPsLosses.h>
#include <Units\SysUnits.h>
#include <System\XProgrammingError.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   lrfdRefinedLosses2005
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdRefinedLosses2005::lrfdRefinedLosses2005()
{
   m_V                     = ::ConvertToSysUnits(747.7,unitMeasure::Inch3);
   m_S                     = ::ConvertToSysUnits(258.747,unitMeasure::Inch2);
   m_th                    = ::ConvertToSysUnits(10.0,unitMeasure::Day);
   m_td                    = ::ConvertToSysUnits(90.0,unitMeasure::Day);
   m_tf                    = ::ConvertToSysUnits(120.0,unitMeasure::Day);
   m_CuringMethod          = lrfdCreepCoefficient2005::Accelerated;
   m_Ad                    = ::ConvertToSysUnits(600.,unitMeasure::Inch2);
   m_ed                    = ::ConvertToSysUnits(-25.865,unitMeasure::Inch);
   m_CuringMethodTimeAdjustmentFactor = 7;

}

lrfdRefinedLosses2005::lrfdRefinedLosses2005(
                         Float64 x,
                         Float64 Lg,
                         matPsStrand::Grade gr,
                         matPsStrand::Type type,
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp,  // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,   // area of TTS 
                         Float64 aps,      // area of one temp strand
                         Float64 eperm, // eccentricty of permanent ps strands with respect to CG of girder
                         Float64 etemp, // eccentricty of temporary strands with respect to CG of girder
                         lrfdLosses::TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck
                         
                         Float64 V,    // Volumne of girder
                         Float64 S,    // Surface area of girder
                         Float64 VSlab,    // Volumne of slab
                         Float64 SSlab,    // Surface area of slab
                         Float64 Ag,   // area of girder
                         Float64 Ig,   // moment of inertia of girder
                         Float64 Ybg,  // Centroid of girder measured from bottom
                         Float64 Ac,   // area of composite girder
                         Float64 Ic,   // moment of inertia of composite
                         Float64 Ybc,  // Centroid of composite measured from bottom
                         Float64 Ad,   // area of deck
                         Float64 ed,   // eccentricity of deck CG with respect to CG of composite
                         
                         Float64 Mdlg,  // Dead load moment of girder only
                         Float64 Madlg,  // Additional dead load on girder section
                         Float64 Msidl, // Superimposed dead loads

                         Float64 rh,  // Relative humidity [0,100]
                         Float64 ti,   // Time until prestress transfer
                         Float64 th,   // Time at hauling
                         Float64 td,   // Time to deck placement
                         Float64 tf,   // Final time
                         lrfdCreepCoefficient2005::CuringMethod curingMethod,
                         Float64 curingMethodTimeFactor,
                         bool bIgnoreInitialRelaxation
                         ) :
lrfdLosses(x,Lg,gr,type,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,eperm,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl,Ag,Ig,Ybg,Ac,Ic,Ybc,rh,ti,bIgnoreInitialRelaxation)
{
   m_V                     = V;
   m_S                     = S;
   m_VSlab                 = VSlab;
   m_SSlab                 = SSlab;
   m_Ad                    = Ad;
   m_ed                    = ed;
   m_ti                    = ti;
   m_th                    = th;
   m_td                    = td;
   m_tf                    = tf;
   m_CuringMethod          = curingMethod;
   m_CuringMethodTimeAdjustmentFactor = curingMethodTimeFactor;
}

lrfdRefinedLosses2005::lrfdRefinedLosses2005(const lrfdRefinedLosses2005& rOther)
{
   MakeCopy( rOther );
}

lrfdRefinedLosses2005::~lrfdRefinedLosses2005()
{
}

//======================== OPERATORS  =======================================
lrfdRefinedLosses2005& lrfdRefinedLosses2005::operator=(const lrfdRefinedLosses2005& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================

Float64 lrfdRefinedLosses2005::TemporaryStrand_ShrinkageLossAtShipping() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpSRH[0];
}

Float64 lrfdRefinedLosses2005::TemporaryStrand_CreepLossAtShipping() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpCRH[0];
}

Float64 lrfdRefinedLosses2005::TemporaryStrand_RelaxationLossAtShipping() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpR1H[0];
}

Float64 lrfdRefinedLosses2005::PermanentStrand_ShrinkageLossAtShipping() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpSRH[1];
}

Float64 lrfdRefinedLosses2005::PermanentStrand_CreepLossAtShipping() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpCRH[1];
}

Float64 lrfdRefinedLosses2005::PermanentStrand_RelaxationLossAtShipping() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpR1H[1];
}

Float64 lrfdRefinedLosses2005::ShrinkageLossBeforeDeckPlacement() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpSR;
}

Float64 lrfdRefinedLosses2005::CreepLossBeforeDeckPlacement() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpCR;
}

Float64 lrfdRefinedLosses2005::RelaxationLossBeforeDeckPlacement() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpR1;
}

Float64 lrfdRefinedLosses2005::ShrinkageLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpSD;
}

Float64 lrfdRefinedLosses2005::CreepLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpCD;
}

Float64 lrfdRefinedLosses2005::RelaxationLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpR2;
}

Float64 lrfdRefinedLosses2005::DeckShrinkageLoss() const
{
   if ( m_IsDirty ) UpdateLosses();
   return m_dfpSS;
}

Float64 lrfdRefinedLosses2005::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpSRH[0] + m_dfpCRH[0] + m_dfpR1H[0];
}

Float64 lrfdRefinedLosses2005::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpSRH[1] + m_dfpCRH[1] + m_dfpR1H[1];
}

Float64 lrfdRefinedLosses2005::TimeDependentLossesBeforeDeck() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpSR + m_dfpCR + m_dfpR1;
}

Float64 lrfdRefinedLosses2005::TimeDependentLossesAfterDeck() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpSD + m_dfpCD + m_dfpR2 - m_dfpSS;
}

Float64 lrfdRefinedLosses2005::TimeDependentLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfpLT;
}

const lrfdCreepCoefficient2005& lrfdRefinedLosses2005::GetCreepInitialToFinal() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_CreepInitialToFinal;
}

const lrfdCreepCoefficient2005& lrfdRefinedLosses2005::GetCreepInitialToDeck() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_CreepInitialToDeck;
}

const lrfdCreepCoefficient2005& lrfdRefinedLosses2005::GetCreepInitialToShipping() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_CreepInitialToHauling;
}

const lrfdCreepCoefficient2005& lrfdRefinedLosses2005::GetCreepDeckToFinal() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_CreepDeckToFinal;
}

const lrfdCreepCoefficient2005& lrfdRefinedLosses2005::GetCreepDeck() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_CreepDeck;
}

Float64 lrfdRefinedLosses2005::GetTemporaryStrandFcgp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_ElasticShortening.TemporaryStrand_Fcgp();
}

Float64 lrfdRefinedLosses2005::GetPermanentStrandFcgp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_ElasticShortening.PermanentStrand_Fcgp();
}

Float64 lrfdRefinedLosses2005::GetTemporaryStrandFpt() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_FpjTemp - m_dfpR0[0] - m_dfpES[0];
}

Float64 lrfdRefinedLosses2005::GetPermanentStrandFpt() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_FpjPerm - m_dfpR0[1] - m_dfpES[1];
}

Float64 lrfdRefinedLosses2005::GetDeltaFcd() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_DeltaFcd;
}

Float64 lrfdRefinedLosses2005::GetDeltaFcdf() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_DeltaFcdf;
}

Float64 lrfdRefinedLosses2005::Getkhs() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_khs;
}

Float64 lrfdRefinedLosses2005::Get_ebid() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_ebid;
}

Float64 lrfdRefinedLosses2005::Get_ebih() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_ebih;
}

Float64 lrfdRefinedLosses2005::GetKid() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_Kid;
}

Float64 lrfdRefinedLosses2005::GetTemporaryStrandKih() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_Kih[0];
}

Float64 lrfdRefinedLosses2005::GetPermanentStrandKih() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_Kih[1];
}

Float64 lrfdRefinedLosses2005::GetKL() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_KL;
}

Float64 lrfdRefinedLosses2005::Get_ebdf() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_ebdf;
}

Float64 lrfdRefinedLosses2005::GetKdf() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_Kdf;
}

Float64 lrfdRefinedLosses2005::Get_eddf() const
{
    if ( m_IsDirty )
        UpdateLosses();

    return m_eddf;
}

//======================== ACCESS     =======================================

void lrfdRefinedLosses2005::SetVolume(Float64 V)
{
   if ( !IsEqual(m_V,V) )
   {
      m_V = V; 
      m_IsDirty = true;
   }
}

Float64 lrfdRefinedLosses2005::GetVolume() const
{
   return m_V;
}

void lrfdRefinedLosses2005::SetSurfaceArea(Float64 S)
{
   if ( !IsEqual(m_S,S) )
   {
      m_S = S; 
      m_IsDirty = true;
   }
}

Float64 lrfdRefinedLosses2005::GetSurfaceArea() const
{
   return m_S;
}


void lrfdRefinedLosses2005::SetVolumeSlab(Float64 V)
{
   if ( !IsEqual(m_VSlab,V) )
   {
      m_VSlab = V; 
      m_IsDirty = true;
   }
}

Float64 lrfdRefinedLosses2005::GetVolumeSlab() const
{
   return m_VSlab;
}

void lrfdRefinedLosses2005::SetSurfaceAreaSlab(Float64 S)
{
   if ( !IsEqual(m_SSlab,S) )
   {
      m_SSlab = S; 
      m_IsDirty = true;
   }
}

Float64 lrfdRefinedLosses2005::GetSurfaceAreaSlab() const
{
   return m_SSlab;
}

void lrfdRefinedLosses2005::SetCuringMethod(lrfdCreepCoefficient2005::CuringMethod method)
{
   if ( m_CuringMethod != method )
   {
      m_CuringMethod = method;
      m_IsDirty = true;
   }
}

lrfdCreepCoefficient2005::CuringMethod lrfdRefinedLosses2005::GetCuringMethod() const
{
   return m_CuringMethod;
}

void lrfdRefinedLosses2005::SetCuringMethodTimeAdjustmentFactor(Float64 f)
{
   m_CuringMethodTimeAdjustmentFactor = f;
}

Float64 lrfdRefinedLosses2005::GetCuringMethodTimeAdjustmentFactor() const
{
   return m_CuringMethodTimeAdjustmentFactor;
}

Float64 lrfdRefinedLosses2005::GetAdjustedInitialAge() const
{
   Float64 tiAdjusted = m_ti;

   if ( m_CuringMethod == lrfdCreepCoefficient2005::Accelerated )
      tiAdjusted *= m_CuringMethodTimeAdjustmentFactor;

   return tiAdjusted;
}

void lrfdRefinedLosses2005::SetAgeAtHauling(Float64 th)
{
   if ( !IsEqual(m_th,th) )
   {
      m_th = th;
      m_IsDirty = true;
   }
}

Float64 lrfdRefinedLosses2005::GetAgeAtHauling() const
{
   return m_th;
}

void lrfdRefinedLosses2005::SetAgeAtDeckPlacement(Float64 td)
{
   if ( !IsEqual(m_td,td) )
   {
      m_td = td;
      m_IsDirty = true;
   }
}

Float64 lrfdRefinedLosses2005::GetAgeAtDeckPlacement() const
{
   return m_td;
}

void lrfdRefinedLosses2005::SetFinalAge(Float64 tf)
{
   if ( !IsEqual(m_tf,tf) )
   {
      m_tf = tf;
      m_IsDirty = true;
   }
}

Float64 lrfdRefinedLosses2005::GetFinalAge() const
{
   return m_tf;
}


//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdRefinedLosses2005::MakeAssignment( const lrfdRefinedLosses2005& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void lrfdRefinedLosses2005::MakeCopy( const lrfdRefinedLosses2005& rOther )
{
   lrfdLosses::MakeCopy(rOther);

   m_V                     = rOther.m_V;
   m_S                     = rOther.m_S;
   m_VSlab                 = rOther.m_VSlab;
   m_SSlab                 = rOther.m_SSlab;
   m_th                    = rOther.m_th;
   m_td                    = rOther.m_td;
   m_tf                    = rOther.m_tf;
   m_CuringMethod          = rOther.m_CuringMethod;
   m_CreepInitialToHauling = rOther.m_CreepInitialToHauling;
   m_CreepInitialToFinal   = rOther.m_CreepInitialToFinal;
   m_CreepInitialToDeck    = rOther.m_CreepInitialToDeck;
   m_CreepDeckToFinal      = rOther.m_CreepDeckToFinal;
   m_CreepDeck             = rOther.m_CreepDeck;
   m_Ad                    = rOther.m_Ad;
   m_ed                    = rOther.m_ed;
   m_Fcgpt                 = rOther.m_Fcgpt;
   m_DeltaFcd              = rOther.m_DeltaFcd;
   m_DeltaFcdf             = rOther.m_DeltaFcdf;
   m_khs                   = rOther.m_khs;
   m_ebid                  = rOther.m_ebid;
   m_ebih                  = rOther.m_ebih;
   m_Kid                   = rOther.m_Kid;
   m_Kih[0]                = rOther.m_Kih[0];
   m_Kih[1]                = rOther.m_Kih[1];
   m_KL                    = rOther.m_KL;
   m_ebdf                  = rOther.m_ebdf;
   m_Kdf                   = rOther.m_Kdf;
   m_eddf                  = rOther.m_eddf;
   m_dfpSR                 = rOther.m_dfpSR;
   m_dfpCR                 = rOther.m_dfpCR;
   m_dfpR1                 = rOther.m_dfpR1;
   m_dfpSD                 = rOther.m_dfpSD;
   m_dfpCD                 = rOther.m_dfpCD;
   m_dfpR2                 = rOther.m_dfpR2;
   m_dfpSS                 = rOther.m_dfpSS;
   m_dfpLT                 = rOther.m_dfpLT;

   m_dfpSRH[0]             = rOther.m_dfpSRH[0];
   m_dfpCRH[0]             = rOther.m_dfpCRH[0];
   m_dfpR1H[0]             = rOther.m_dfpR1H[0];
   m_dfpTH[0]              = rOther.m_dfpTH[0];

   m_dfpSRH[1]             = rOther.m_dfpSRH[1];
   m_dfpCRH[1]             = rOther.m_dfpCRH[1];
   m_dfpR1H[1]             = rOther.m_dfpR1H[1];
   m_dfpTH[1]              = rOther.m_dfpTH[1];

   m_CuringMethodTimeAdjustmentFactor = rOther.m_CuringMethodTimeAdjustmentFactor;

}

void lrfdRefinedLosses2005::ValidateParameters() const
{
   // need to make sure spec version is ok
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
      throw lrfdXPsLosses(lrfdXPsLosses::Specification,__FILE__,__LINE__);

   bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
   // Use a values that are just out of spec to avoid throwing for boundry values
   // that have a little round-off error in them.
   // 5.4.2.1 - Sets limits between 4 and 10KSI, but allows greater than 10 KSI when specific articles permit it
   // 5.9.5.1 permits up to 15KSI for loss calculations
   Float64 fcMin = (is_si ? ::ConvertToSysUnits( 27.95, unitMeasure::MPa ) : ::ConvertToSysUnits( 3.95, unitMeasure::KSI ) );
   Float64 fcMax = (is_si ? ::ConvertToSysUnits( 105.05, unitMeasure::MPa ) : ::ConvertToSysUnits( 15.05, unitMeasure::KSI ) );
   if ( m_Fc < fcMin || fcMax < m_Fc )
      THROW(lrfdXPsLosses,fcOutOfRange);
}

void lrfdRefinedLosses2005::UpdateLongTermLosses() const
{
   //////////////////////////////////////////////////////////////////////////////////////
   // Losses: Time of Transfer to Time of Deck Placement [5.9.5.4.2]
   //////////////////////////////////////////////////////////////////////////////////////

   // Shrinkage of Girder Concrete [5.9.5.4.2a]

   // 1. Compute creep coefficient for use in computing Kid
   // Handled as part of Hauling losses

   // 2. Compute Kid
   Float64 Aps = m_ApsPerm;
   Float64 e   = m_eperm;
   if ( m_TempStrandUsage == lrfdRefinedLosses2005::tsPretensioned )
   {
      Aps += m_ApsTemp;
      e = GetEccpg();
   }

   m_Kid = 1 + (m_Ep/m_Eci)*(Aps/m_Ag)*(1 + m_Ag*e*m_eperm/m_Ig)*(1 + 0.7*m_CreepInitialToFinal.GetCreepCoefficient());
   m_Kid = 1/m_Kid;

   // 3. Compute creep parameters for ktd for deck placement
   m_CreepInitialToDeck.SetCuringMethod(m_CuringMethod);
   m_CreepInitialToDeck.SetCuringMethodTimeAdjustmentFactor(m_CuringMethodTimeAdjustmentFactor);
   m_CreepInitialToDeck.SetFc(m_Fci);
   m_CreepInitialToDeck.SetInitialAge(m_ti);
   m_CreepInitialToDeck.SetMaturity(m_td);
   m_CreepInitialToDeck.SetRelHumidity(m_H);
   m_CreepInitialToDeck.SetSurfaceArea(m_S);
   m_CreepInitialToDeck.SetVolume(m_V);

   // 4. Compute shrinkage strain
   Float64 kvs = m_CreepInitialToFinal.GetKvs();
   Float64 kf  = m_CreepInitialToFinal.GetKf();
   Float64 ktd = m_CreepInitialToDeck.GetKtd();
   Float64 khs = m_khs;
   m_ebid = kvs*khs*kf*ktd*0.48e-03;

   m_dfpSR = IsZero(m_ApsPerm) ? 0 : m_ebid * m_Ep * m_Kid;

   // Creep of Girder Concrete [5.9.5.4.2b]
   Float64 fcgp = m_ElasticShortening.PermanentStrand_Fcgp();
   m_dfpCR = (m_Ep/m_Eci)*(fcgp + m_dfpp)*m_CreepInitialToDeck.GetCreepCoefficient()*m_Kid;

   // Relaxation of Prestressing Strands [5.9.5.4.2c]
#pragma Reminder("NOTE") // do we have to consider effect of PT if used???
   Float64 fpt = m_FpjPerm - m_dfpR0[1] - m_dfpES[1];
   Float64 td  = ::ConvertFromSysUnits(m_td,unitMeasure::Day);
   Float64 ti  = ::ConvertFromSysUnits(m_ti,unitMeasure::Day);

   m_dfpR1 = IsZero(fpt) ? 0 : (fpt/m_KL)*(log10(24*td)/log10(24*ti))*(fpt/m_Fpy - 0.55)*(1 - 3*(m_dfpSR + m_dfpCR)/fpt)*m_Kid;
   m_dfpR1 = (m_dfpR1 < 0 ? 0 : m_dfpR1); // Fpt can't be less than 0.55Fpy

   //////////////////////////////////////////////////////////////////////////////////////
   // Losses: Time of Deck Placement to Final Time
   //////////////////////////////////////////////////////////////////////////////////////

   // Shrinkage of Girder Concrete [5.9.5.4.3a]

   // 1. Compute Kdf
   Float64 epc = GetEccpc();
   m_Kdf = 1 + (m_Ep/m_Eci)*(m_ApsPerm/m_Ac)*(1 + m_Ac*epc*epc/m_Ic)*(1 + 0.7*m_CreepInitialToFinal.GetCreepCoefficient());
   m_Kdf = 1/m_Kdf;

   // 2. Compute shrinkage strain
   ktd = m_CreepInitialToFinal.GetKtd();
   m_ebdf = kvs*khs*kf*ktd*0.48e-03;

   // if there aren't any strands then there can't be loss due to shrinkage
   m_dfpSD = IsZero(m_ApsPerm) ? 0.0 : m_ebdf*m_Ep*m_Kdf;

   // Creep of Girder Concrete [5.9.5.4.3b]

   // 1. Creep coefficient - initial to deck
   m_CreepInitialToDeck.SetCuringMethod(m_CuringMethod);
   m_CreepInitialToDeck.SetCuringMethodTimeAdjustmentFactor(m_CuringMethodTimeAdjustmentFactor);
   m_CreepInitialToDeck.SetFc(m_Fci);
   m_CreepInitialToDeck.SetInitialAge(m_ti);
   m_CreepInitialToDeck.SetMaturity(m_td);
   m_CreepInitialToDeck.SetRelHumidity(m_H);
   m_CreepInitialToDeck.SetSurfaceArea(m_S);
   m_CreepInitialToDeck.SetVolume(m_V);

   // 2. Creep coefficient - deck to final
   m_CreepDeckToFinal.SetCuringMethod(lrfdCreepCoefficient2005::Normal);
   m_CreepDeckToFinal.SetCuringMethodTimeAdjustmentFactor(m_CuringMethodTimeAdjustmentFactor);
   m_CreepDeckToFinal.SetFc(m_Fc);
   m_CreepDeckToFinal.SetInitialAge(m_td);
   m_CreepDeckToFinal.SetMaturity(m_tf);
   m_CreepDeckToFinal.SetRelHumidity(m_H);
   m_CreepDeckToFinal.SetSurfaceArea(m_S);
   m_CreepDeckToFinal.SetVolume(m_V);

   // 3. Compute Delta Fcd
   m_DeltaFcd1 = -1*(m_Madlg*m_eperm/m_Ig + m_Msidl*( m_Ybc - m_Ybg + m_eperm )/m_Ic);
   m_DeltaFcd2 = -1*((m_dfpCR + m_dfpSR + m_dfpR1)*m_ApsPerm/m_Ag + (m_dfpCR + m_dfpSR + m_dfpR1)*m_ApsPerm*m_eperm*m_eperm/m_Ig);
   // change sign because these moments cause tension at the level of
   // the strands which reduces creep

   m_DeltaFcd = m_DeltaFcd1 + m_DeltaFcd2;

   if ( IsZero(m_ApsPerm) )
   {
      m_dfpCD = 0;
   }
   else
   {
      m_dfpCD  = (m_Ep/m_Eci)*(fcgp+m_dfpp)*(m_CreepInitialToFinal.GetCreepCoefficient() - m_CreepInitialToDeck.GetCreepCoefficient())*m_Kdf;
      m_dfpCD += (m_Ep/m_Ec)*(m_DeltaFcd+m_dfptr)*m_CreepDeckToFinal.GetCreepCoefficient()*m_Kdf;
   }


   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007 && m_dfpCD < 0 )
   {
      // removed inequality forcing dfpCD >= 0 in 4th Edition, 2007
      m_dfpCD = 0;
   }

   // Elastic gain due to deck and superimposed dead loads
   m_dfpED = IsZero(m_ApsPerm) ? 0 : (m_Ep/m_Ec)*m_DeltaFcd1;

   // Relaxation of Prestressing Strands [5.9.5.4.3c]
   m_dfpR2 = m_dfpR1;

   // Shrinkage of Deck Concrete [5.9.5.4.3d]
   m_CreepDeck.SetCuringMethod(lrfdCreepCoefficient2005::Normal);
   m_CreepDeck.SetCuringMethodTimeAdjustmentFactor(m_CuringMethodTimeAdjustmentFactor);
   m_CreepDeck.SetFc(m_FcSlab);
   m_CreepDeck.SetInitialAge(0);
   m_CreepDeck.SetMaturity(m_tf-m_td);
   m_CreepDeck.SetRelHumidity(m_H);
   m_CreepDeck.SetSurfaceArea(m_SSlab);
   m_CreepDeck.SetVolume(m_VSlab);
   kvs = m_CreepDeck.GetKvs();
   kf  = m_CreepDeck.GetKf();
   ktd = m_CreepDeck.GetKtd();
   m_eddf = -kvs*khs*kf*ktd*0.48e-03;

   // LRFD 2007 has a "-" in 1/Ac - epc*ed/I
   // we use a "+" because ed is < 0 for typical construction per our sign convension
   m_DeltaFcdf = m_eddf*m_Ad*m_Ecd*(1/m_Ac + (epc*m_ed)/m_Ic)/(1 + 0.7*m_CreepDeckToFinal.GetCreepCoefficient());

   // if there aren't any strands, then there can't be losses due to deck shrinkage
   m_dfpSS = IsZero(m_ApsPerm) ? 0.0 : (m_Ep/m_Ec)*m_DeltaFcdf*m_Kdf*(1 + 0.7*m_CreepDeckToFinal.GetCreepCoefficient());


   m_dfpLT = m_dfpSR + m_dfpCR + m_dfpR1 + m_dfpSD + m_dfpCD + m_dfpR2 - m_dfpSS;
}


void lrfdRefinedLosses2005::UpdateHaulingLosses() const
{
   // Losses: Time of Transfer to Time of Lifting [5.9.5.4.2]
   m_KL = (m_Type == matPsStrand::LowRelaxation ? 45 : 10);
   m_khs = 2.0 - 0.014*m_H;

   // Shrinkage of Girder Concrete [5.9.5.4.2a]
   Float64 Aps = m_ApsPerm;
   Float64 e   = m_eperm;
   if ( m_TempStrandUsage == lrfdRefinedLosses2005::tsPretensioned )
   {
      Aps += m_ApsTemp;
      e = GetEccpg();
   }

   // Compute creep coefficient for use in computing Kid
   m_CreepInitialToFinal.SetCuringMethod(m_CuringMethod);
   m_CreepInitialToFinal.SetCuringMethodTimeAdjustmentFactor(m_CuringMethodTimeAdjustmentFactor);
   m_CreepInitialToFinal.SetFc(m_Fci);
   m_CreepInitialToFinal.SetInitialAge(m_ti);
   m_CreepInitialToFinal.SetMaturity(m_tf);
   m_CreepInitialToFinal.SetRelHumidity(m_H);
   m_CreepInitialToFinal.SetSurfaceArea(m_S);
   m_CreepInitialToFinal.SetVolume(m_V);

   m_Kih[0] = 1 + (m_Ep/m_Eci)*(Aps/m_Ag)*(1 + m_Ag*e*m_etemp/m_Ig)*(1 + 0.7*m_CreepInitialToFinal.GetCreepCoefficient());
   m_Kih[0] = 1/m_Kih[0];

   m_Kih[1] = 1 + (m_Ep/m_Eci)*(Aps/m_Ag)*(1 + m_Ag*e*m_eperm/m_Ig)*(1 + 0.7*m_CreepInitialToFinal.GetCreepCoefficient());
   m_Kih[1] = 1/m_Kih[1];

   // Compute creep parameters for ktd for shipping
   m_CreepInitialToHauling.SetCuringMethod(m_CuringMethod);
   m_CreepInitialToHauling.SetCuringMethodTimeAdjustmentFactor(m_CuringMethodTimeAdjustmentFactor);
   m_CreepInitialToHauling.SetFc(m_Fci);
   m_CreepInitialToHauling.SetInitialAge(m_ti);
   m_CreepInitialToHauling.SetMaturity(m_th);
   m_CreepInitialToHauling.SetRelHumidity(m_H);
   m_CreepInitialToHauling.SetSurfaceArea(m_S);
   m_CreepInitialToHauling.SetVolume(m_V);

   // Compute shrinkage strain
   Float64 ktd = m_CreepInitialToHauling.GetKtd();
   Float64 kvs = m_CreepInitialToHauling.GetKvs();
   Float64 kf  = m_CreepInitialToHauling.GetKf();
   Float64 khs = m_khs;
   m_ebih = kvs*khs*kf*ktd*0.48e-03;
   m_dfpSRH[0] = IsZero(m_ApsTemp*m_FpjTemp) ? 0 : m_ebih * m_Ep * m_Kih[0];
   m_dfpSRH[1] = IsZero(m_ApsPerm*m_FpjPerm) ? 0 : m_ebih * m_Ep * m_Kih[1];

   // Creep of Girder Concrete [5.9.5.4.2b]
   Float64 fcgp = m_ElasticShortening.TemporaryStrand_Fcgp();
   m_dfpCRH[0] = (m_Ep/m_Eci)*(fcgp+m_dfpp)*m_CreepInitialToHauling.GetCreepCoefficient()*m_Kih[0];
   
   fcgp = m_ElasticShortening.PermanentStrand_Fcgp();
   m_dfpCRH[1] = (m_Ep/m_Eci)*(fcgp+m_dfpp)*m_CreepInitialToHauling.GetCreepCoefficient()*m_Kih[1];

   // Relaxation of Prestressing Strands [5.9.5.4.2c]
#pragma Reminder("NOTE") // consider m_dfpp???
   Float64 th  = ::ConvertFromSysUnits(m_th,unitMeasure::Day);
   Float64 ti  = ::ConvertFromSysUnits(m_ti,unitMeasure::Day);

   Float64 fpj = IsZero(m_ApsTemp) ? 0 : m_FpjTemp;
   Float64 fpt = fpj - m_dfpR0[0] - m_dfpES[0];
   m_dfpR1H[0] = IsZero(fpt) ? 0 : (fpt/m_KL)*(log10(24*th)/log10(24*ti))*(fpt/m_Fpy - 0.55)*(1 - 3*(m_dfpSRH[0] + m_dfpCRH[0])/fpt)*m_Kih[0];
   m_dfpR1H[0] = (m_dfpR1H[0] < 0 ? 0 : m_dfpR1H[0]); // Fpt can't be less than 0.55Fpy

   fpj = IsZero(m_ApsPerm) ? 0 : m_FpjPerm;
   fpt = fpj - m_dfpR0[1] - m_dfpES[1];
   m_dfpR1H[1] = IsZero(fpt) ? 0 : (fpt/m_KL)*(log10(24*th)/log10(24*ti))*(fpt/m_Fpy - 0.55)*(1 - 3*(m_dfpSRH[1] + m_dfpCRH[1])/fpt)*m_Kih[1];
   m_dfpR1H[1] = (m_dfpR1H[1] < 0 ? 0 : m_dfpR1H[1]); // Fpt can't be less than 0.55Fpy

   // Total time dependent losses at shipping
   m_dfpTH[0] = m_dfpSRH[0] + m_dfpCRH[0] + m_dfpR1H[0];
   m_dfpTH[1] = m_dfpSRH[1] + m_dfpCRH[1] + m_dfpR1H[1];
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdRefinedLosses2005::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdRefinedLosses2005");

   lrfdAutoVersion av;

   lrfdRefinedLosses2005 loss(19.5072, // location along girder where losses are computed
                         39.0144,    // girder length
                         matPsStrand::Gr1860,
                         matPsStrand::LowRelaxation,
                         1396186227.0505831, // fpj permanent strands
                         1396188385.8038988, // fpj of temporary strands
                         0.0051799896399999995,  // area of permanent strand
                         0.00055999887999999998,  // area of TTS 
                         0.00013999972000000000,      // area of one strand
                         0.73344249937779116, // eccentricty of permanent ps strands with respect to CG of girder
                         -0.81870344656815441, // eccentricty of temporary strands with respect to CG of girder
                         
                         tsPretensioned, // temporary strand usage

                         0.0095250000000000005, // anchor set
                         0.00065616797900200005, // wobble
                         0.25000000000000000, // friction
                         0, // angle change

                         41368543.759020001,   // 28 day strength of girder concrete
                         35852736.609413415,  // Release strength
                         27579029.172680002,   
                         35668801112.349388,   // Modulus of elasticity of girder
                         33205846111.428368,  // Modulus of elasticity of girder at transfer
                         29123454154.024353,  // Modulus of elasticity of deck
                         
                         0.56485774124999988,    // Volumne of girder
                         6.9711699425657105,    // Surface area of girder
                         0.32516064001351508,    // Volumne of slab
                         1.8288000000760127,    // Surface area of slab
                         
                         0.56485774124999988,   // area of girder
                         0.23197765412628035,   // moment of inertia of girder
                         0.80689655343184530,  // Centroid of girder measured from bottom
                         0.83035029207347855,   // area of composite girder
                         0.39856959307884982,   // moment of inertia of composite
                         1.1133322567444859,  // Centroid of composite measured from bottom
                         0.34838640001448046,   // area of deck
                         -0.65196774325551399,   // eccentricity of deck CG with respect to CG of composite
                         
                         2701223.1744837998,  // Dead load moment of girder only
                         2144430.8154568151,  // Additional dead load on girder section
                         494526.00384487113, // Superimposed dead loads
                         
                         75,  // Relative humidity [0,100]
                         86400.000000000000,   // Time until prestress transfer
                         864000.00000000000,   // Time at hauling
                         10368000.000000000,   // Time to deck placement
                         172800000.00000000,   // Final time
                         lrfdCreepCoefficient2005::Accelerated,
                         7, // time scale factor for curing method
                         false
                         );

   lrfdVersionMgr::RegisterListener( &loss );
   lrfdVersionMgr::SetVersion( lrfdVersionMgr::ThirdEditionWith2005Interims );
   lrfdVersionMgr::SetUnits( lrfdVersionMgr::US );

   Float64 value;

   // permanent strands
   value = loss.PermanentStrand_BeforeTransfer();
   TRY_TESTME( IsEqual(value,13683947.729187824) );

   value = loss.PermanentStrand_AfterTransfer();
   TRY_TESTME( IsEqual(value,120602629.93431854) );

   value = loss.PermanentStrand_AfterTemporaryStrandInstallation();
   TRY_TESTME( IsEqual(value,120602629.93431854) );

   value = loss.PermanentStrand_AtLifting();
   TRY_TESTME( IsEqual(value,120602629.93431854) );

   value = loss.PermanentStrand_AtShipping();
   TRY_TESTME( IsEqual(value,161640424.74374515) );

   value = loss.PermanentStrand_BeforeTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value,161640424.74374515) );

   value = loss.PermanentStrand_AfterTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value,164929970.05799773) );

   value = loss.PermanentStrand_AfterDeckPlacement();
   TRY_TESTME( IsEqual(value,212991990.04773825) );

   value = loss.PermanentStrand_Final();
   TRY_TESTME( IsEqual(value,271762357.13140631) );

   // temporary strands
   value = loss.TemporaryStrand_BeforeTransfer();
   TRY_TESTME( IsEqual(value,13684031.013553569) );

   value = loss.TemporaryStrand_AfterTransfer();
   TRY_TESTME( IsEqual(value,57859070.448777609) );

   value = loss.TemporaryStrand_AfterTemporaryStrandInstallation();
   TRY_TESTME( IsEqual(value,57859070.448777609) );

   value = loss.TemporaryStrand_AtLifting();
   TRY_TESTME( IsEqual(value,57859070.448777609) );

   value = loss.TemporaryStrand_AtShipping();
   TRY_TESTME( IsEqual(value,96177231.626787215) );

   value = loss.TemporaryStrand_BeforeTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value,96177231.626787215) );

   value = loss.TemporaryStrand_AfterTemporaryStrandRemoval();
   TRY_TESTME( IsEqual(value,0.) );

   value = loss.TemporaryStrand_AfterDeckPlacement();
   TRY_TESTME( IsEqual(value,0.) );

   value = loss.TemporaryStrand_Final();
   TRY_TESTME( IsEqual(value,0.) );

   lrfdVersionMgr::UnregisterListener( &loss );

   TESTME_EPILOG("lrfdRefinedLosses2005");
}

#endif // _UNITTEST


