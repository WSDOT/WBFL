///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <Lrfd\RefinedLossesTxDOT2013.h>
#include <Lrfd\ElasticShortening.h>
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
   lrfdRefinedLossesTxDOT2013
****************************************************************************/


static Float64 shrinkage_losses(Float64 h, Float64 fci, Float64 Ep);
static Float64 creep_losses(Float64 h, Float64 fci, Float64 Eci, Float64 Ep, Float64 fcgp, Float64 dfcdp);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdRefinedLossesTxDOT2013::lrfdRefinedLossesTxDOT2013()
{
   Init();

   m_FcgpMethod = lrfdElasticShortening::fcgpIterative;
}

lrfdRefinedLossesTxDOT2013::lrfdRefinedLossesTxDOT2013(Float64 x, // location along girder where losses are computed
                         Float64 Lg,    // girder length
                         lrfdLosses::SectionPropertiesType sectionProperties,
                         matPsStrand::Grade gr,
                         matPsStrand::Type type,
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp, // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,  // area of TTS 
                         Float64 aps,      // area of one strand
                         Float64 epermRelease, // eccentricty of permanent ps strands with respect to CG of girder at release
                         Float64 epermFinal, // eccentricty of permanent ps strands with respect to CG of girder at final
                         Float64 etemp, // eccentricty of temporary strands with respect to CG of girder
                         TempStrandUsage usage,
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

                         Float64 Mdlg,  // Dead load moment of girder only
                         Float64 Madlg,  // Additional dead load on girder section
                         Float64 Msidl, // Superimposed dead loads
                         Float64 Mllim, // live load

                         Float64 Ag,    // Area of girder
                         Float64 Ig,    // Moment of inertia of girder
                         Float64 Ybg,   // Centroid of girder measured from bottom
                         Float64 Ac,    // Area of the composite girder and deck
                         Float64 Ic,    // Moment of inertia of composite
                         Float64 Ybc,   // Centroid of composite measured from bottom

                         Float64 An,   // area of girder
                         Float64 In,   // moment of inertia of girder
                         Float64 Ybn,  // Centroid of girder measured from bottom
                         Float64 Acn,   // area of composite girder
                         Float64 Icn,   // moment of inertia of composite
                         Float64 Ybcn,  // Centroid of composite measured from bottom

                         Float64 rh, // relative humidity

                         Float64 ti,   // Time until prestress transfer
                         Float64 shipping,
                         lrfdElasticShortening::FcgpComputationMethod method,
                         bool bValidateParameters
                         ) :
lrfdLosses(x,Lg,sectionProperties,gr,type,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl,Mllim,Ag,Ig,Ybg,Ac,Ic,Ybc,An,In,Ybn,Acn,Icn,Ybcn,rh,ti,/* ignore initial relaxation */ true,bValidateParameters)
{
   Init();

   m_Shipping = shipping;
   m_FcgpMethod = method;
}

lrfdRefinedLossesTxDOT2013::lrfdRefinedLossesTxDOT2013(const lrfdRefinedLossesTxDOT2013& rOther)
{
   MakeCopy( rOther );
}

lrfdRefinedLossesTxDOT2013::~lrfdRefinedLossesTxDOT2013()
{
}

//======================== OPERATORS  =======================================
lrfdRefinedLossesTxDOT2013& lrfdRefinedLossesTxDOT2013::operator=(const lrfdRefinedLossesTxDOT2013& rOther)
{
   if ( this != &rOther )
   {
      MakeAssignment( rOther );
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdRefinedLossesTxDOT2013::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   return PermanentStrand_TimeDependentLossesAtShipping();
}

Float64 lrfdRefinedLossesTxDOT2013::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_Shipping < 0 )
   {
      return -m_Shipping*TimeDependentLosses();
   }
   else
   {
      return m_Shipping;
   }
}

Float64 lrfdRefinedLossesTxDOT2013::TimeDependentLossesBeforeDeck() const
{
   return TimeDependentLosses();
}

Float64 lrfdRefinedLossesTxDOT2013::TimeDependentLossesAfterDeck() const
{
   return 0;
}

Float64 lrfdRefinedLossesTxDOT2013::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR + m_dfpCR + m_dfpR1 + m_dfpR2;
}

Float64 lrfdRefinedLossesTxDOT2013::ShrinkageLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR;
}

Float64 lrfdRefinedLossesTxDOT2013::CreepLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpCR;
}

Float64 lrfdRefinedLossesTxDOT2013::RelaxationLossBeforeDeckPlacement() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }
   return m_dfpR1;
}

Float64 lrfdRefinedLossesTxDOT2013::RelaxationLossAfterDeckPlacement() const
{
   if ( m_IsDirty ) 
   {
      UpdateLosses();
   }
   return m_dfpR2;
}

Float64 lrfdRefinedLossesTxDOT2013::TemporaryStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[TEMPORARY_STRAND];
}

Float64 lrfdRefinedLossesTxDOT2013::PermanentStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[PERMANENT_STRAND];
}

Float64 lrfdRefinedLossesTxDOT2013::TemporaryStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[TEMPORARY_STRAND] + m_dfpR0[TEMPORARY_STRAND];
}

Float64 lrfdRefinedLossesTxDOT2013::PermanentStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[PERMANENT_STRAND] + m_dfpR0[PERMANENT_STRAND];
}

void lrfdRefinedLossesTxDOT2013::ValidateParameters() const
{
}

void lrfdRefinedLossesTxDOT2013::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      Init();
   }
   else
   {
      m_dfpSR = shrinkage_losses( m_H, m_Fci, m_Ep );

      m_Msd = m_Madlg + m_Msidl;

      m_DeltaFcd1 = -1 * m_Msd * m_epermFinal/m_Ig;

      m_dfpCR = creep_losses( m_H, m_Fci, m_Eci, m_Ep, m_ElasticShortening.PermanentStrand_Fcgp(), m_DeltaFcd1 );

      if (lrfdElasticShortening::fcgp07Fpu == m_ElasticShortening.GetFcgpComputationMethod())
      {
         m_fpt = 0.7 * this->m_Fpu;
      }
      else
      {
         m_fpt = m_FpjPerm - m_dfpR0[PERMANENT_STRAND] - m_dfpES[PERMANENT_STRAND];
      }

      m_KL = (m_Type == matPsStrand::LowRelaxation ? 30 : 7);

      m_dfpR1 = (m_fpt <= 0.0) ? 0 : (m_fpt/m_KL)*(m_fpt/m_Fpy - 0.55);
      m_dfpR1 = (m_dfpR1 < 0 ? 0 : m_dfpR1); // Fpt can't be less than 0.55Fpy

      m_dfpR2 = m_dfpR1; // Relaxation loss at deck placement is 1/2 of total
   }
}

void lrfdRefinedLossesTxDOT2013::UpdateHaulingLosses() const
{
   UpdateLongTermLosses();
}

void lrfdRefinedLossesTxDOT2013::UpdateElasticShortening() const
{
   // Elastic shortening
   lrfdElasticShortening es(m_FpjPerm,
                            (m_TempStrandUsage == tsPretensioned ? m_FpjTemp : 0),
                            m_dfpR0[PERMANENT_STRAND], // perm
                            m_dfpR0[TEMPORARY_STRAND], // temp
                            m_ApsPerm,
                            (m_TempStrandUsage == tsPretensioned ? m_ApsTemp : 0),
                            m_SectionProperties == sptGross ? true : false,
                            m_Ag,
                            m_Ig,
                            m_epermRelease,
                            m_etemp,
                            m_Mdlg,
                            1.0,
                            m_Eci,
                            m_Ep,
                            m_FcgpMethod);

   m_ElasticShortening = es;

   m_dfpES[TEMPORARY_STRAND] = m_ElasticShortening.TemporaryStrand_ElasticShorteningLosses();
   m_dfpES[PERMANENT_STRAND] = m_ElasticShortening.PermanentStrand_ElasticShorteningLosses();
}

//======================== ACCESS     =======================================
Float64 lrfdRefinedLossesTxDOT2013::GetKL() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_KL;
}

Float64 lrfdRefinedLossesTxDOT2013::Getfpt() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_fpt;
}

Float64 lrfdRefinedLossesTxDOT2013::GetSdMoment() const
{
    if ( m_IsDirty )
    {
        UpdateLosses();
    }

    return m_Msd;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdRefinedLossesTxDOT2013::MakeAssignment( const lrfdRefinedLossesTxDOT2013& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void lrfdRefinedLossesTxDOT2013::MakeCopy( const lrfdRefinedLossesTxDOT2013& rOther )
{
   lrfdLosses::MakeCopy(rOther);

   m_dfpSR = rOther.m_dfpSR;
   m_dfpCR = rOther.m_dfpCR;
   m_dfpR2 = rOther.m_dfpR2;
   m_dfpR1 = rOther.m_dfpR1;

   m_KL     = rOther.m_KL;
   m_fpt    = rOther.m_fpt;
   m_Msd    = rOther.m_Msd;

   m_Shipping = rOther.m_Shipping;
   m_FcgpMethod = rOther.m_FcgpMethod;
}

void lrfdRefinedLossesTxDOT2013::Init() const
{
   m_dfpSR = 0.0;
   m_dfpCR = 0.0;

   m_KL = 0.0;
   m_fpt = 0.0;
   m_Msd = 0.0;

   m_dfpR1 = 0.0;
   m_dfpR2 = 0.0;
   m_Shipping = 0.0;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


Float64 shrinkage_losses(Float64 H, Float64 fci, Float64 Ep)
{
   CHECK( InRange(0.,H,100.) );

   // No si unit conversion in Texas
   fci = ::ConvertFromSysUnits(fci, unitMeasure::KSI );
   Ep  = ::ConvertFromSysUnits(Ep, unitMeasure::KSI );

   Float64 losses = Ep*( (140-H)/(4.8+fci) )*4.4e-05;

   losses = ::ConvertToSysUnits(losses, unitMeasure::KSI );
   CHECK( losses >= 0. );

   return losses;
}

Float64 creep_losses(Float64 H, Float64 fci, Float64 Eci, Float64 Ep, Float64 fcgp, Float64 dfcdp)
{
   CHECK( InRange(0.,H,100.) );
   fci   = ::ConvertFromSysUnits(fci, unitMeasure::KSI );
   Eci   = ::ConvertFromSysUnits(Eci, unitMeasure::KSI );
   Ep    = ::ConvertFromSysUnits(Ep, unitMeasure::KSI );
   fcgp  = ::ConvertFromSysUnits(fcgp, unitMeasure::KSI );
   dfcdp = ::ConvertFromSysUnits(dfcdp, unitMeasure::KSI );
                                                     
   Float64 loss = 0.1*((195-H)/(4.8+fci))*(Ep/Eci)*(fcgp+0.6*dfcdp);

   loss = ::ConvertToSysUnits(loss, unitMeasure::KSI );
   loss = (loss < 0 ) ? 0 : loss;
   return loss;
}

#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdRefinedLossesTxDOT2013::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdRefinedLossesTxDOT2013");
//
//   lrfdAutoVersion av;
//
//   Float64 Fpj   = ::ConvertToSysUnits( 0.80*1860, unitMeasure::MPa );
//   Float64 Ag    = ::ConvertToSysUnits( 486051, unitMeasure::Millimeter2 );
//   Float64 Ig    = ::ConvertToSysUnits( 126011e6, unitMeasure::Millimeter4 );
//   Float64 Ybg   = ::ConvertToSysUnits( 608, unitMeasure::Millimeter );
//   Float64 Ic    = ::ConvertToSysUnits( 283.7e9, unitMeasure::Millimeter4 );
//   Float64 Ybc   = ::ConvertToSysUnits( 977, unitMeasure::Millimeter );
//   Float64 e     = ::ConvertToSysUnits( 489, unitMeasure::Millimeter );
//   Float64 Aps   = ::ConvertToSysUnits( 5133, unitMeasure::Millimeter2 );
//   Float64 Mdlg  = ::ConvertToSysUnits( 1328, unitMeasure::KilonewtonMeter );
//   Float64 Madlg = ::ConvertToSysUnits( 2900-1328, unitMeasure::KilonewtonMeter );
//   Float64 Msidl = ::ConvertToSysUnits( 540+353, unitMeasure::KilonewtonMeter );
//   Float64 Rh    = 70.;
//   Float64 Eci   = ::ConvertToSysUnits( 30360, unitMeasure::MPa );
//   Float64 t     = ::ConvertToSysUnits( 4.0, unitMeasure::Day );
//
//   lrfdRefinedLossesTxDOT2013 loss( matPsStrand::Gr1860,
//                      matPsStrand::LowRelaxation,
//                      Fpj, 0, Ag, Ig, Ybg, Ic, Ybc, e, e, e, Aps, 0, Mdlg, Madlg, Msidl, 1.0,
//                      Rh, Eci, t );
//
//   lrfdVersionMgr::RegisterListener( &loss );
//
//   lrfdVersionMgr::SetVersion( lrfdVersionMgr::FirstEdition );
//   Float64 loss1 = loss.ImmediatelyAfterXferLosses();
//   TRY_TEST (  IsEqual( ::ConvertFromSysUnits(loss1,unitMeasure::MPa),165.7,0.1) );
//
//   Float64 loss2 = loss.FinalLosses();
//   TRY_TEST (  IsEqual(::ConvertFromSysUnits(loss2,unitMeasure::MPa),394.2,0.1) );
//
//   loss.SetFpj(1);
//   bool bDidCatch = false;
//   try
//   {
//      Float64 loss3 = loss.FinalLosses();
//   }
//   catch( const lrfdXPsLosses& e )
//   {
//      bDidCatch = true;
//      TRY_TEST( bDidCatch );
//      TRY_TEST( e.GetReasonCode() == lrfdXPsLosses::fpjOutOfRange );
//   }
//   TRY_TEST( bDidCatch );
//
//   lrfdVersionMgr::UnregisterListener( &loss );

   TESTME_EPILOG("lrfdRefinedLossesTxDOT2013");
}

#endif // _UNITTEST


