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
#include <Lrfd\ApproximateLosses2005.h>
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
   lrfdApproximateLosses2005
****************************************************************************/

// precompute conversions
static const Float64 g_17_MPA  = ::ConvertToSysUnits(17.0,unitMeasure::MPa);
static const Float64 g_70_MPA  = ::ConvertToSysUnits(70.0,unitMeasure::MPa);
static const Float64 g_27p95_MPA  = ::ConvertToSysUnits(27.95,unitMeasure::MPa);
static const Float64 g_69p05_MPA  = ::ConvertToSysUnits(69.05,unitMeasure::MPa);
static const Float64 g_105p05_MPA  = ::ConvertToSysUnits(105.05,unitMeasure::MPa);

static const Float64 g_2p4_KSI    = ::ConvertToSysUnits(2.4,unitMeasure::KSI);
static const Float64 g_2p5_KSI    = ::ConvertToSysUnits(2.5,unitMeasure::KSI);
static const Float64 g_3p95_KSI   = ::ConvertToSysUnits(3.95,unitMeasure::KSI);
static const Float64 g_10_KSI     = ::ConvertToSysUnits(10.0,unitMeasure::KSI);
static const Float64 g_10p05_KSI  = ::ConvertToSysUnits(10.05,unitMeasure::KSI);
static const Float64 g_15p05_KSI  = ::ConvertToSysUnits(15.05,unitMeasure::KSI);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdApproximateLosses2005::lrfdApproximateLosses2005()
{
}

lrfdApproximateLosses2005::lrfdApproximateLosses2005(Float64 x, // location along girder where losses are computed
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
                         const gpPoint2d& epermRelease, // eccentricty of permanent ps strands with respect to CG of girder
                         const gpPoint2d& epermFinal,
                         const gpPoint2d& etemp, // eccentricty of temporary strands with respect to CG of girder
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

                         Float64 An,    // Area of girder
                         Float64 Ixxn,    // Moment of inertia of girder
                         Float64 Iyyn,
                         Float64 Ixyn,
                         Float64 Ybn,   // Centroid of girder measured from bottom
                         Float64 Acn,    // Area of the composite girder and deck
                         Float64 Icn,    // Moment of inertia of composite
                         Float64 Ybcn,   // Centroid of composite measured from bottom

                         Float64 rh,      // relative humidity
                         Float64 ti,   // Time until prestress transfer
                         bool bIgnoreInitialRelaxation,
                         bool bValidateParameters
                         ) :
lrfdLosses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl1,Msidl2, Ag,Ixx,Iyy,Ixy,Ybg,Ac1,Ic1,Ybc1,Ac2,Ic2,Ybc2,An,Ixxn,Iyyn,Ixyn,Ybn,Acn,Icn,Ybcn,rh,ti,bIgnoreInitialRelaxation,bValidateParameters)
{
}

lrfdApproximateLosses2005::lrfdApproximateLosses2005(const lrfdApproximateLosses2005& rOther)
{
   MakeCopy( rOther );
}

lrfdApproximateLosses2005::~lrfdApproximateLosses2005()
{
}

//======================== OPERATORS  =======================================
lrfdApproximateLosses2005& lrfdApproximateLosses2005::operator=(const lrfdApproximateLosses2005& rOther)
{
   if ( this != &rOther )
   {
      MakeAssignment( rOther );
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdApproximateLosses2005::TemporaryStrand_RelaxationLossesAtXfer() const
{
   if ( IsZero(m_ApsTemp) || IsZero(m_FpjTemp) )
   {
      return 0;
   }
   else
   {
      return RelaxationLossesAtXfer(false);
   }
}

Float64 lrfdApproximateLosses2005::PermanentStrand_RelaxationLossesAtXfer() const
{
   if ( IsZero(m_ApsPerm) || IsZero(m_FpjPerm) )
   {
      return 0;
   }
   else
   {
      return RelaxationLossesAtXfer(true);
   }
}

Float64 lrfdApproximateLosses2005::RelaxationLossesAtXfer(bool bPerm) const
{
   Float64 loss = 0;
   bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
   matPsStrand::Type type = (bPerm ? m_TypePerm : m_TypeTemp);
   if ( type == matPsStrand::LowRelaxation )
   {
      if (is_si)
      {
         loss = g_17_MPA;
      }
      else
      {
         if ( lrfdVersionMgr::FourthEdition2007 <= lrfdVersionMgr::GetVersion() )
         {
            loss = g_2p4_KSI;
         }
         else
         {
            loss = g_2p5_KSI;
         }
      }
   }
   else
   {
      if (is_si)
      {
         loss = g_70_MPA;
      }
      else
      {
         loss = g_10_KSI;
      }
   }

   // See PCI Guidelines for the use of epoxy-coated strand
   // PCI Journal July-August 1993. Section 5.3
   matPsStrand::Coating coating = (bPerm ? m_CoatingPerm : m_CoatingTemp);
   if ( coating != matPsStrand::None )
   {
      loss *= 2;
   }

   return loss;
}

Float64 lrfdApproximateLosses2005::TemporaryStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[0];
}

Float64 lrfdApproximateLosses2005::PermanentStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[1];
}

Float64 lrfdApproximateLosses2005::TemporaryStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[0] + TemporaryStrand_ImmediatelyBeforeXferLosses();
}

Float64 lrfdApproximateLosses2005::PermanentStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[1] + PermanentStrand_ImmediatelyBeforeXferLosses();
}

Float64 lrfdApproximateLosses2005::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   UpdateLongTermLosses();
   return m_dfpTH;
}

Float64 lrfdApproximateLosses2005::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   UpdateLongTermLosses();
   return m_dfpTH;
}

Float64 lrfdApproximateLosses2005::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpLT;
}

Float64 lrfdApproximateLosses2005::TimeDependentLossesBeforeDeck() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return TimeDependentLosses();
}

Float64 lrfdApproximateLosses2005::TimeDependentLossesAfterDeck() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return 0;
}

Float64 lrfdApproximateLosses2005::PermanentStrand_Final() const
{
   // need to over ride this method because shipping losses could be a lump sum and it
   // doesn't have to be consistent with the other losses

   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterTransfer() // initial relaxation
                + TimeDependentLosses(); // total lump sum time dependent losses

   return loss;
}

Float64 lrfdApproximateLosses2005::PermanentStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AtShipping();
   return loss;
}

Float64 lrfdApproximateLosses2005::PermanentStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_BeforeTemporaryStrandRemoval();
   return loss;
}

Float64 lrfdApproximateLosses2005::GetFpi() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_FpjPerm - m_dfpR0[1];
}

Float64 lrfdApproximateLosses2005::GetHumidityFactor() const
{
   return 1.7 - 0.01*m_H;
}

Float64 lrfdApproximateLosses2005::GetStrengthFactor() const
{
   bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
   if ( is_si )
   {
      return 35/(7 + ::ConvertFromSysUnits(m_Fci,unitMeasure::MPa));
   }
   else
   {
      return 5/(1 + ::ConvertFromSysUnits(m_Fci,unitMeasure::KSI));
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdApproximateLosses2005::MakeAssignment( const lrfdApproximateLosses2005& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdApproximateLosses2005::MakeCopy( const lrfdApproximateLosses2005& rOther )
{
   lrfdLosses::MakeCopy(rOther);

   m_dfpTH = rOther.m_dfpTH;
   m_dfpLT = rOther.m_dfpLT;
}

void lrfdApproximateLosses2005::ValidateParameters() const
{
   // need to make sure spec version is ok
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      throw lrfdXPsLosses(lrfdXPsLosses::Specification,_T(__FILE__),__LINE__);
   }

   bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
   // Use a values that are just out of spec to avoid throwing for boundry values
   // that have a little round-off error in them.
   // 5.4.2.1 - Sets limits between 4 and 10KSI, but allows greater than 10 KSI when specific articles permit it
   // 5.9.5.1 permits up to 15KSI for loss calculations
   Float64 fcMin = (is_si ? g_27p95_MPA : g_3p95_KSI );
   Float64 fcMax = (is_si ? g_105p05_MPA : g_15p05_KSI );

   // LRFD 2009 limits approximate stresses per 5.9.5.3 to 10 KSI
   if ( lrfdVersionMgr::FourthEditionWith2009Interims <= lrfdVersionMgr::GetVersion() )
   {
      fcMax = (is_si ? g_69p05_MPA : g_10p05_KSI );
   }

   if ( m_Fc < fcMin || fcMax < m_Fc )
   {
      THROW(lrfdXPsLosses,fcOutOfRange);
   }
}

void lrfdApproximateLosses2005::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfpLT = 0.0;
      m_dfpTH = 0.0;
      m_dfpED[WITH_ELASTIC_GAIN_REDUCTION] = 0.0;
      m_dfpED[WITHOUT_ELASTIC_GAIN_REDUCTION] = 0.0;
   }
   else
   {
      Float64 gamma_H = GetHumidityFactor();
      Float64 gamma_ST = GetStrengthFactor();

      bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
      Float64 fpj = (m_ApsPerm*m_FpjPerm+m_ApsTemp*m_FpjTemp)/(m_ApsPerm+m_ApsTemp);
      Float64 dfpR0 = (m_ApsTemp*m_dfpR0[TEMPORARY_STRAND] + m_ApsPerm*m_dfpR0[PERMANENT_STRAND])/(m_ApsPerm+m_ApsTemp);
      if ( is_si )
      {
         fpj = ::ConvertFromSysUnits( fpj,unitMeasure::MPa);
         Float64 delta_fpR = ::ConvertFromSysUnits(PermanentStrand_RelaxationLossesAtXfer(),unitMeasure::MPa);
         Float64 fpi = fpj - ::ConvertFromSysUnits(dfpR0,unitMeasure::MPa);
         _ASSERTE(0 <= fpi);

         m_dfpLT = 10.*fpi*m_ApsPerm/m_Ag*gamma_H*gamma_ST + 83.*gamma_H*gamma_ST + delta_fpR;
         m_dfpLT = ::ConvertToSysUnits( m_dfpLT, unitMeasure::MPa );

         m_dfpTH = 3.*fpi*m_ApsPerm/m_Ag*gamma_H*gamma_ST + 21*gamma_H*gamma_ST + delta_fpR/4;
         m_dfpTH = ::ConvertToSysUnits( m_dfpTH, unitMeasure::MPa );
      }
      else
      {
         fpj = ::ConvertFromSysUnits( fpj ,unitMeasure::KSI);
         Float64 delta_fpR = ::ConvertFromSysUnits(PermanentStrand_RelaxationLossesAtXfer(),unitMeasure::KSI);

         Float64 fpi = fpj - ::ConvertFromSysUnits(dfpR0,unitMeasure::KSI);
         _ASSERTE(0 <= fpi);

         m_dfpLT = 10.*fpi*m_ApsPerm/m_Ag*gamma_H*gamma_ST + 12.*gamma_H*gamma_ST + delta_fpR;
         m_dfpLT = ::ConvertToSysUnits( m_dfpLT, unitMeasure::KSI );

         m_dfpTH = 3.*fpi*(m_ApsPerm+m_ApsTemp)/m_Ag*gamma_H*gamma_ST + 3*gamma_H*gamma_ST + delta_fpR/4;
         m_dfpTH = ::ConvertToSysUnits( m_dfpTH, unitMeasure::KSI );
      }

      // Elastic gain due to deck placement
      Float64 D = m_Ixx*m_Iyy - m_Ixy*m_Ixy;
      m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION] = (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Ixx/* + my*m_Ixy*/)*m_epermFinal.X() / D + (m_Madlg[WITH_ELASTIC_GAIN_REDUCTION] *m_Iyy/* + my*m_Ixy*/)*m_epermFinal.Y() / D; // biaxial on non-composite section
      m_dfpED[WITH_ELASTIC_GAIN_REDUCTION] = (m_Ep/m_Ec)*m_DeltaFcd1[WITH_ELASTIC_GAIN_REDUCTION];

      m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION] = (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Ixx/* + my*m_Ixy*/) * m_epermFinal.X() / D + (m_Madlg[WITHOUT_ELASTIC_GAIN_REDUCTION] * m_Iyy/* + my*m_Ixy*/) * m_epermFinal.Y() / D; // biaxial on non-composite section
      m_dfpED[WITHOUT_ELASTIC_GAIN_REDUCTION] = (m_Ep / m_Ec) * m_DeltaFcd1[WITHOUT_ELASTIC_GAIN_REDUCTION];

      // Elastic gain due to superimposed dead loads
      m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION] = m_Msidl1[WITH_ELASTIC_GAIN_REDUCTION] *(m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITH_ELASTIC_GAIN_REDUCTION] *( m_Ybc2 - m_Ybg + m_epermFinal.Y() )/m_Ic2; // uniaxial on composite section
      m_dfpSIDL[WITH_ELASTIC_GAIN_REDUCTION] = (m_Ep/m_Ec)*m_DeltaFcd2[WITH_ELASTIC_GAIN_REDUCTION];

      m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION] = m_Msidl1[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc1 - m_Ybg + m_epermFinal.Y()) / m_Ic1 + m_Msidl2[WITHOUT_ELASTIC_GAIN_REDUCTION] * (m_Ybc2 - m_Ybg + m_epermFinal.Y()) / m_Ic2; // uniaxial on composite section
      m_dfpSIDL[WITHOUT_ELASTIC_GAIN_REDUCTION] = (m_Ep / m_Ec) * m_DeltaFcd2[WITHOUT_ELASTIC_GAIN_REDUCTION];
   }
}

void lrfdApproximateLosses2005::UpdateHaulingLosses() const
{
   // don't really need to do anything here because it is handled in UpdateLongTermLosses
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdApproximateLosses2005::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdApproximateLosses2005");
//
//   lrfdAutoVersion av;
//
//   Float64 Fpj   = ::ConvertToSysUnits( 0.80*1860, unitMeasure::MPa );
//   Float64 Ag    = ::ConvertToSysUnits( 486051, unitMeasure::Millimeter2 );
//   Float64 Ig    = ::ConvertToSysUnits( 126011e6, unitMeasure::Millimeter4 );
//   Float64 Ybg   = ::ConvertToSysUnits( 608, unitMeasure::Millimeter );
//   Float64 e     = ::ConvertToSysUnits( 489, unitMeasure::Millimeter );
//   Float64 Aps   = ::ConvertToSysUnits( 5133, unitMeasure::Millimeter2 );
//   Float64 Mdlg  = ::ConvertToSysUnits( 1328, unitMeasure::KilonewtonMeter );
//   Float64 Eci   = ::ConvertToSysUnits( 30360, unitMeasure::MPa );
//   Float64 Fc    = ::ConvertToSysUnits( 48, unitMeasure::MPa );
//   Float64 t     = ::ConvertToSysUnits( 4.0, unitMeasure::Day );
//   Float64 PPR   = 1.0;
//
//   lrfdApproximateLosses2005 loss( matPsStrand::Gr1860,
//                               matPsStrand::LowRelaxation,
//                               lrfdApproximateLosses2005::IBeam,
//                               Fpj, Ag, Ig, Ybg, e, Aps, Mdlg, 1.0, Eci, Fc, PPR, t );
//
//   lrfdVersionMgr::RegisterListener( &loss );
//
//   lrfdVersionMgr::SetVersion( lrfdVersionMgr::FirstEdition );
//   Float64 loss1 = loss.ImmediatelyAfterXferLosses();
//   TRY_TEST (  IsEqual( ::ConvertFromSysUnits(loss1,unitMeasure::MPa),165.7,0.1) );
//
//   Float64 loss2 = loss.FinalLosses();
//   TRY_TEST (  IsEqual(::ConvertFromSysUnits(loss2,unitMeasure::MPa),339.8,0.1) );
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
//
   TESTME_EPILOG("lrfdApproximateLosses2005");
}

#endif // _UNITTEST


