///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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
#include <Lrfd\RefinedLossesTxDOT2013.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\XPsLosses.h>
#include <System\XProgrammingError.h>

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
                         matPsStrand::Grade gradePerm, // strand grade
                         matPsStrand::Type typePerm, // strand type
                         matPsStrand::Coating coatingPerm, // strand coating (none, epoxy)
                         matPsStrand::Grade gradeTemp, // strand grade
                         matPsStrand::Type typeTemp, // strand type
                         matPsStrand::Coating coatingTemp, // strand coating (none, epoxy)
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp, // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,  // area of TTS 
                         Float64 aps,      // area of one strand
                         const WBFL::Geometry::Point2d& epermRelease, // eccentricty of permanent ps strands with respect to CG of girder at release
                         const WBFL::Geometry::Point2d& epermFinal, // eccentricty of permanent ps strands with respect to CG of girder at final
                         const WBFL::Geometry::Point2d& etemp, // eccentricty of temporary strands with respect to CG of girder
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
                         const std::vector<std::pair<Float64, Float64>>& Madlg,  // Additional dead load on girder section (first value is moment, second is elastic gain reduction factor)
                         const std::vector<std::pair<Float64, Float64>>& Msidl1, // Superimposed dead loads, stage 1
                         const std::vector<std::pair<Float64, Float64>>& Msidl2, // Superimposed dead loads, stage 2

                         Float64 Ag,    // Area of girder
                         Float64 Ixx,    // Moment of inertia of girder
                         Float64 Iyy,
                         Float64 Ixy,
                         Float64 Ybg,   // Centroid of girder measured from bottom
                         Float64 Ac1,    // Area of the composite girder and deck
                         Float64 Ic1,    // Moment of inertia of composite
                         Float64 Ybc1,   // Centroid of composite measured from bottom
                         Float64 Ac2,    // Area of the composite girder and deck
                         Float64 Ic2,    // Moment of inertia of composite
                         Float64 Ybc2,   // Centroid of composite measured from bottom

                         Float64 An,   // area of girder
                         Float64 Ixxn,   // moment of inertia of girder
                         Float64 Iyyn,
                         Float64 Ixyn,
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
lrfdLosses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl1,Msidl2, Ag,Ixx,Iyy,Ixy,Ybg,Ac1,Ic1,Ybc1,Ac2,Ic2,Ybc2,An,Ixxn,Iyyn,Ixyn,Ybn,Acn,Icn,Ybcn,rh,ti,/* ignore initial relaxation */ true,bValidateParameters)
{
   Init();

   m_Shipping = shipping;
   m_FcgpMethod = method;
}

lrfdRefinedLossesTxDOT2013::~lrfdRefinedLossesTxDOT2013()
{
}

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

      m_Msd = m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] + m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] + m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION];
      Float64 msd = m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] + m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] + m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION];

      m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = -1 * m_Msd * m_epermFinal.Y() / m_Ixx;
      m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = -1 * msd * m_epermFinal.Y() / m_Ixx;

      m_dfpCR = creep_losses( m_H, m_Fci, m_Eci, m_Ep, m_ElasticShortening.PermanentStrand_Fcgp(), m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION]);

      if (lrfdElasticShortening::fcgp07Fpu == m_ElasticShortening.GetFcgpComputationMethod())
      {
         m_fpt = 0.7 * this->m_FpuPerm;
      }
      else
      {
         m_fpt = m_FpjPerm - m_dfpR0[PERMANENT_STRAND] - m_dfpES[PERMANENT_STRAND];
      }

      m_KL = (m_TypePerm == matPsStrand::LowRelaxation ? 30 : 7);

      m_dfpR1 = (m_fpt <= 0.0) ? 0 : (m_fpt/m_KL)*(m_fpt/m_FpyPerm - 0.55);
      m_dfpR1 = (m_dfpR1 < 0 ? 0 : m_dfpR1); // Fpt can't be less than 0.55Fpy

      if ( m_CoatingPerm != matPsStrand::None )
      {
         // See PCI Guidelines for the use of epoxy-coated strand
         // PCI Journal July-August 1993. Section 5.3
         m_dfpR1 *= 2;
      }

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
                            m_Ixx,
                            m_Iyy,
                            m_Ixy,
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
   fci = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI );
   Ep  = WBFL::Units::ConvertFromSysUnits(Ep, WBFL::Units::Measure::KSI );

   Float64 losses = Ep*( (140-H)/(4.8+fci) )*4.4e-05;

   losses = WBFL::Units::ConvertToSysUnits(losses, WBFL::Units::Measure::KSI );
   CHECK( losses >= 0. );

   return losses;
}

Float64 creep_losses(Float64 H, Float64 fci, Float64 Eci, Float64 Ep, Float64 fcgp, Float64 dfcdp)
{
   CHECK( InRange(0.,H,100.) );
   fci   = WBFL::Units::ConvertFromSysUnits(fci, WBFL::Units::Measure::KSI );
   Eci   = WBFL::Units::ConvertFromSysUnits(Eci, WBFL::Units::Measure::KSI );
   Ep    = WBFL::Units::ConvertFromSysUnits(Ep, WBFL::Units::Measure::KSI );
   fcgp  = WBFL::Units::ConvertFromSysUnits(fcgp, WBFL::Units::Measure::KSI );
   dfcdp = WBFL::Units::ConvertFromSysUnits(dfcdp, WBFL::Units::Measure::KSI );
                                                     
   Float64 loss = 0.1*((195-H)/(4.8+fci))*(Ep/Eci)*(fcgp+0.6*dfcdp);

   loss = WBFL::Units::ConvertToSysUnits(loss, WBFL::Units::Measure::KSI );
   loss = (loss < 0 ) ? 0 : loss;
   return loss;
}

#if defined _UNITTEST
#include <Units\System.h>
#include <Lrfd\AutoVersion.h>
bool lrfdRefinedLossesTxDOT2013::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("lrfdRefinedLossesTxDOT2013");
//
//   lrfdAutoVersion av;
//
//   Float64 Fpj   = WBFL::Units::ConvertToSysUnits( 0.80*1860, WBFL::Units::Measure::MPa );
//   Float64 Ag    = WBFL::Units::ConvertToSysUnits( 486051, WBFL::Units::Measure::Millimeter2 );
//   Float64 Ig    = WBFL::Units::ConvertToSysUnits( 126011e6, WBFL::Units::Measure::Millimeter4 );
//   Float64 Ybg   = WBFL::Units::ConvertToSysUnits( 608, WBFL::Units::Measure::Millimeter );
//   Float64 Ic    = WBFL::Units::ConvertToSysUnits( 283.7e9, WBFL::Units::Measure::Millimeter4 );
//   Float64 Ybc   = WBFL::Units::ConvertToSysUnits( 977, WBFL::Units::Measure::Millimeter );
//   Float64 e     = WBFL::Units::ConvertToSysUnits( 489, WBFL::Units::Measure::Millimeter );
//   Float64 Aps   = WBFL::Units::ConvertToSysUnits( 5133, WBFL::Units::Measure::Millimeter2 );
//   Float64 Mdlg  = WBFL::Units::ConvertToSysUnits( 1328, WBFL::Units::Measure::KilonewtonMeter );
//   Float64 Madlg = WBFL::Units::ConvertToSysUnits( 2900-1328, WBFL::Units::Measure::KilonewtonMeter );
//   Float64 Msidl = WBFL::Units::ConvertToSysUnits( 540+353, WBFL::Units::Measure::KilonewtonMeter );
//   Float64 Rh    = 70.;
//   Float64 Eci   = WBFL::Units::ConvertToSysUnits( 30360, WBFL::Units::Measure::MPa );
//   Float64 t     = WBFL::Units::ConvertToSysUnits( 4.0, WBFL::Units::Measure::Day );
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
//   TRY_TEST (  IsEqual( WBFL::Units::ConvertFromSysUnits(loss1,WBFL::Units::Measure::MPa),165.7,0.1) );
//
//   Float64 loss2 = loss.FinalLosses();
//   TRY_TEST (  IsEqual(WBFL::Units::ConvertFromSysUnits(loss2,WBFL::Units::Measure::MPa),394.2,0.1) );
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


