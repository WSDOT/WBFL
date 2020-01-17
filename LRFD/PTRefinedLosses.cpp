///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <Lrfd\PTRefinedLosses.h>
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
   lrfdPTRefinedLosses
****************************************************************************/


Float64 pt_shrinkage_losses(Float64 h);
Float64 pt_creep_losses(Float64 fcgp, Float64 dfcdp);
Float64 pt_relaxation_after_transfer(matPsStrand::Type type,Float64 fr,Float64 es,Float64 sr,Float64 cr);

bool pt_IsSI() 
{
   return (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdPTRefinedLosses::lrfdPTRefinedLosses()
{
   Init();

   m_Grade = matPsStrand::Gr1860;
   m_Type  = matPsStrand::LowRelaxation;
   m_Rh    = 70.;
   m_Eci   = ::ConvertToSysUnits(  25000, unitMeasure::MPa );
   m_Ep    = lrfdPsStrand::GetModE();
   m_Fpu   = lrfdPsStrand::GetUltimateStrength( m_Grade );
   m_Fpj   = 0.80*m_Fpu;
   m_Fpy   = lrfdPsStrand::GetYieldStrength( m_Grade, m_Type );
   m_Aps   = ::ConvertToSysUnits( 1, unitMeasure::Millimeter2 );
   m_Ag    = ::ConvertToSysUnits( 1, unitMeasure::Millimeter2 );
   m_Ig    = ::ConvertToSysUnits( 1, unitMeasure::Millimeter4 );
   m_Ybg   = 0;
   m_Ic    = ::ConvertToSysUnits( 1, unitMeasure::Millimeter4 );
   m_Ybc   = 0;
   m_e     = 0;
   m_Mdlg  = 0;
   m_Madlg = 0;
   m_Msidl = 0;
}

lrfdPTRefinedLosses::lrfdPTRefinedLosses(matPsStrand::Grade gr,
                           matPsStrand::Type type,
                           Float64 fpj,
                           Float64 Ag,   // area of girder
                           Float64 Ig,   // moment of inertia of girder
                           Float64 Ybg,  // Centroid of girder measured from bottom
                           Float64 Ic,   // moment of inertia of composite
                           Float64 Ybc,  // Centroid of composite measured from bottom
                           Float64 e,   // eccentricity of ps strands
                           Float64 Aps, // area of ps strands
                           Float64 Mdlg,  // Dead load moment of girder only
                           Float64 Madlg,  // Additional dead load on girder section
                           Float64 Msidl, // Superimposed dead loads
                           Float64 rh,  // Relative humidity [0,100]
                           Float64 Eci, // Modulus of elasticity of concrete at transfer
                           Float64 dfFR,  // Friction losses
                           Float64 Fcgp,
                           Float64 dfES)
{
   Init();

   m_Grade = gr;
   m_Type  = type;
   m_Fpj   = fpj;
   m_Rh    = rh;
   m_Eci   = Eci;
   m_Ep    = lrfdPsStrand::GetModE();
   m_Fpu   = lrfdPsStrand::GetUltimateStrength( m_Grade );
   m_Fpy   = lrfdPsStrand::GetYieldStrength( m_Grade, m_Type );
   m_Aps   = Aps;
   m_Ag    = Ag;
   m_Ig    = Ig;
   m_Ybg   = Ybg;
   m_Ic    = Ic;
   m_Ybc   = Ybc;
   m_e     = e;
   m_Mdlg  = Mdlg;
   m_Madlg = Madlg;
   m_Msidl = Msidl;
   m_dfFR  = dfFR;
   m_Fcgp  = Fcgp;
   m_dfES  = dfES;
}

lrfdPTRefinedLosses::lrfdPTRefinedLosses(const lrfdPTRefinedLosses& rOther)
{
   Init();
   MakeCopy( rOther );
}

lrfdPTRefinedLosses::~lrfdPTRefinedLosses()
{
}

//======================== OPERATORS  =======================================
lrfdPTRefinedLosses& lrfdPTRefinedLosses::operator=(const lrfdPTRefinedLosses& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
void lrfdPTRefinedLosses::OnUpdate()
{
   lrfdVersionMgrListener::OnUpdate();

   // Nothing actually changes.
}
 
Float64 lrfdPTRefinedLosses::ShrinkageLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfSR;
}

Float64 lrfdPTRefinedLosses::CreepLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfCR;
}

Float64 lrfdPTRefinedLosses::RelaxationLossesAfterXfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfR2;
}

Float64 lrfdPTRefinedLosses::FinalLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfCR + m_dfSR + m_dfR2;
}

Float64 lrfdPTRefinedLosses::GetDeltaFcdp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_DeltaFcdp;
}

Float64 lrfdPTRefinedLosses::GetFpy() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fpy;
}

Float64 lrfdPTRefinedLosses::GetEp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Ep;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdPTRefinedLosses::MakeAssignment( const lrfdPTRefinedLosses& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdPTRefinedLosses::Init()
{
   m_IsDirty = true;
   m_Fcgp = 0;
}

void lrfdPTRefinedLosses::MakeCopy( const lrfdPTRefinedLosses& rOther )
{
   m_Grade = rOther.m_Grade;
   m_Type  = rOther.m_Type;
   m_Ag    = rOther.m_Ag;
   m_Ig    = rOther.m_Ig;
   m_Ybg   = rOther.m_Ybg;
   m_Ic    = rOther.m_Ic;
   m_Ybc   = rOther.m_Ybc;
   m_e     = rOther.m_e;
   m_Aps   = rOther.m_Aps;
   m_Mdlg  = rOther.m_Mdlg;
   m_Madlg = rOther.m_Madlg;
   m_Msidl = rOther.m_Msidl;
   m_Rh    = rOther.m_Rh;
   m_Ep    = rOther.m_Ep;
   m_Eci   = rOther.m_Eci;
   m_Fpu   = rOther.m_Fpu;
   m_Fpy   = rOther.m_Fpy;
   m_Fpj   = rOther.m_Fpj;

   m_dfFR = rOther.m_dfFR;

   m_Fcgp = rOther.m_Fcgp;
   m_DeltaFcdp = rOther.m_DeltaFcdp;

   m_dfES = rOther.m_dfES;
   m_dfSR = rOther.m_dfSR;
   m_dfCR = rOther.m_dfCR;
   m_dfR2 = rOther.m_dfR2;

   m_IsDirty = rOther.m_IsDirty;
}

void lrfdPTRefinedLosses::UpdateLosses() const
{
   UpdateLongTermLosses();

   m_IsDirty = false;
}


void lrfdPTRefinedLosses::UpdateLongTermLosses() const
{
   if ( IsZero( m_Fpj ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfSR = 0.0;
      m_dfCR = 0.0;
      m_dfR2 = 0.0;
   }
   else
   {
      m_dfSR = pt_shrinkage_losses( m_Rh );

      m_DeltaFcdp = m_Madlg*m_e/m_Ig +
                    m_Msidl*( m_Ybc - m_Ybg + m_e )/m_Ic;

      m_dfCR = pt_creep_losses( m_Fcgp, m_DeltaFcdp );

      m_dfR2 = pt_relaxation_after_transfer( m_Type, m_dfFR, m_dfES, m_dfSR, m_dfCR );
   }
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


Float64 pt_shrinkage_losses(Float64 h)
{
   CHECK( InRange(0.,h,100.) );

   Float64 losses;
   Float64 A,B; // Coefficients in the loss equation
   const unitStress* p_unit;

   bool is_si = pt_IsSI();

   if ( is_si )
      p_unit = &unitMeasure::MPa;
   else
      p_unit = &unitMeasure::KSI;

   A = is_si ? 93.  : 13.5;
   B = is_si ? 0.85 : 0.123;

   losses = A - B*h;

   losses = ::ConvertToSysUnits(losses, *p_unit );
   CHECK( losses >= 0. );

   return losses;
}

Float64 pt_creep_losses(Float64 fcgp, Float64 dfcdp)
{
   Float64 loss = 12.0* fcgp - 7.0*dfcdp;
   loss = (loss < 0 ) ? 0 : loss;
   return loss;
}

Float64 pt_relaxation_after_transfer(matPsStrand::Type type,Float64 fr,Float64 es,Float64 sr,Float64 cr)
{
   bool is_si = pt_IsSI();
   const unitStress* p_unit;
   Float64 A;

   if ( is_si )
   {
      p_unit = &unitMeasure::MPa;
      A = 138.;
   }
   else
   {
      p_unit = &unitMeasure::KSI;
      A = 20.;
   }

   // Convert input values from system units to code units
   fr = ::ConvertFromSysUnits(fr,*p_unit);
   es = ::ConvertFromSysUnits(es,*p_unit);
   sr = ::ConvertFromSysUnits(sr,*p_unit);
   cr = ::ConvertFromSysUnits(cr,*p_unit);

   Float64 losses;
   losses = A - 0.3*fr - 0.4*es - 0.2*(sr+cr);

   losses = ::ConvertToSysUnits(losses,*p_unit);

   if ( losses < 0 )
   {
      WATCH(_T("Losses less than zero. Setting them to zero"));
      losses = 0; // Per Bijan Khaleghi 12/18/98
   }

   return losses;
}

#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdPTRefinedLosses::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdPTRefinedLosses");
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
//   lrfdPTRefinedLosses loss( matPsStrand::Gr1860,
//                      matPsStrand::LowRelaxation,
//                      Fpj, Ag, Ig, Ybg, Ic, Ybc, e, Aps, Mdlg, Madlg, Msidl,
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
//
   TESTME_EPILOG("lrfdPTRefinedLosses");
}

#endif // _UNITTEST


