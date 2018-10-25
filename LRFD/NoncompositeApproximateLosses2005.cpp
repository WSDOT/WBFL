///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <Lrfd\NoncompositeApproximateLosses2005.h>
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
   lrfdNoncompositeApproximateLosses2005
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdNoncompositeApproximateLosses2005::lrfdNoncompositeApproximateLosses2005()
{
   Init();

   m_BeamType = SingleT;
   m_Level = Average;
   m_Grade = matPsStrand::Gr1860;
   m_Type  = matPsStrand::LowRelaxation;
   m_Eci   = ::ConvertToSysUnits(  25000, unitMeasure::MPa );
   m_Ep    = lrfdPsStrand::GetModE();
   m_Fpu   = lrfdPsStrand::GetUltimateStrength( m_Grade );
   m_Fpj   = 0.80*m_Fpu;
   m_Fpy   = lrfdPsStrand::GetYieldStrength( m_Grade, m_Type );
   m_Aps   = ::ConvertToSysUnits( 1, unitMeasure::Millimeter2 );
   m_Ag    = ::ConvertToSysUnits( 1, unitMeasure::Millimeter2 );
   m_Ig    = ::ConvertToSysUnits( 1, unitMeasure::Millimeter4 );
   m_Ybg   = 0;
   m_e     = 0;
   m_eperm = 0;
   m_Mdlg  = 0;
   m_Fc    = ::ConvertToSysUnits(  48, unitMeasure::MPa );;
   m_PPR   = 1.0;
   m_K = 1;
}

lrfdNoncompositeApproximateLosses2005::lrfdNoncompositeApproximateLosses2005(matPsStrand::Grade gr,
                           matPsStrand::Type type,
                           BeamType beamType,
                           Level level,
                           Float64 fpj,
                           Float64 Ag,   // area of girder
                           Float64 Ig,   // moment of inertia of girder
                           Float64 Ybg,  // Centroid of girder measured from bottom
                           Float64 e,   // eccentricity of ps strands
                           Float64 eperm,
                           Float64 aps,
                           Float64 Mdlg,  // Dead load moment of girder only
                           Float64 K,
                           Float64 Eci, // Modulus of elasticity of concrete at transfer
                           Float64 Fc,
                           Float64 PPR,
                           Float64 t )   // Time until prestress transfer
{
   Init();

   m_Grade = gr;
   m_Type  = type;
   m_BeamType = beamType;
   m_Level = level;
   m_Fpj   = fpj;
   m_Eci   = Eci;
   m_Ep    = lrfdPsStrand::GetModE();
   m_Fpu   = lrfdPsStrand::GetUltimateStrength( m_Grade );
   m_Fpy   = lrfdPsStrand::GetYieldStrength( m_Grade, m_Type );
   m_Time  = t;
   m_Ag    = Ag;
   m_Ig    = Ig;
   m_Ybg   = Ybg;
   m_e     = e;
   m_eperm = eperm;
   m_Aps   = aps;
   m_Mdlg  = Mdlg;
   m_Fc    = Fc;
   m_PPR   = PPR;
   m_K     = K;
}

lrfdNoncompositeApproximateLosses2005::lrfdNoncompositeApproximateLosses2005(const lrfdNoncompositeApproximateLosses2005& rOther)
{
   Init();
   MakeCopy( rOther );
}

lrfdNoncompositeApproximateLosses2005::~lrfdNoncompositeApproximateLosses2005()
{
}

//======================== OPERATORS  =======================================
lrfdNoncompositeApproximateLosses2005& lrfdNoncompositeApproximateLosses2005::operator=(const lrfdNoncompositeApproximateLosses2005& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
void lrfdNoncompositeApproximateLosses2005::OnUpdate()
{
   lrfdVersionMgrListener::OnUpdate();

   // Nothing actually changes.
}

Float64 lrfdNoncompositeApproximateLosses2005::ElasticShorteningLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfES;
}

Float64 lrfdNoncompositeApproximateLosses2005::RelaxationLossesAtXfer() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfR1;
}

Float64 lrfdNoncompositeApproximateLosses2005::ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfR1;
}

Float64 lrfdNoncompositeApproximateLosses2005::ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfES + m_dfR1;
}

Float64 lrfdNoncompositeApproximateLosses2005::ApproxLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfApprox;
}

Float64 lrfdNoncompositeApproximateLosses2005::FinalLosses() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_dfES + m_dfApprox - m_dfR1;
}

Float64 lrfdNoncompositeApproximateLosses2005::GetFcgp() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fcgp;
}

Float64 lrfdNoncompositeApproximateLosses2005::GetFpy() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_Fpy;
}

Float64 lrfdNoncompositeApproximateLosses2005::GetP() const
{
   if ( m_IsDirty )
      UpdateLosses();

   return m_P;
}

Float64 lrfdNoncompositeApproximateLosses2005::GetEp() const
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
void lrfdNoncompositeApproximateLosses2005::MakeAssignment( const lrfdNoncompositeApproximateLosses2005& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdNoncompositeApproximateLosses2005::Init()
{
   m_IsDirty = true;
   m_Fcgp = 0;
}

void lrfdNoncompositeApproximateLosses2005::MakeCopy( const lrfdNoncompositeApproximateLosses2005& rOther )
{
   m_BeamType = rOther.m_BeamType;
   m_Level = rOther.m_Level;
   m_Grade = rOther.m_Grade;
   m_Type  = rOther.m_Type;
   m_Ag    = rOther.m_Ag;
   m_Ig    = rOther.m_Ig;
   m_Ybg   = rOther.m_Ybg;
   m_e     = rOther.m_e;
   m_eperm = rOther.m_eperm;
   m_Aps   = rOther.m_Aps;
   m_Mdlg  = rOther.m_Mdlg;
   m_Ep    = rOther.m_Ep;
   m_Eci   = rOther.m_Eci;
   m_Fpu   = rOther.m_Fpu;
   m_Fpy   = rOther.m_Fpy;
   m_Fpj   = rOther.m_Fpj;
   m_Time  = rOther.m_Time;
   m_Fc    = rOther.m_Fc;
   m_PPR   = rOther.m_PPR;

   m_K     = rOther.m_K;

   m_Fcgp = rOther.m_Fcgp;
   m_P = rOther.m_P;

   m_dfES = rOther.m_dfES;
   m_dfR1 = rOther.m_dfR1;
   m_dfApprox = rOther.m_dfApprox;

   m_IsDirty = rOther.m_IsDirty;
}

void lrfdNoncompositeApproximateLosses2005::UpdateLosses() const
{
   if ( !IsZero( m_Fpj ) && !(0.5*m_Fpu < m_Fpj) )
      THROW(lrfdXPsLosses,fpjOutOfRange);

   bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
   // Use a values that are just out of spec to avoid throwing for boundry values
   // that have a little round-off error in them.
   Float64 fcMin = (is_si ? ::ConvertToSysUnits( 27.95, unitMeasure::MPa ) : ::ConvertToSysUnits( 3.95, unitMeasure::KSI ) );
   Float64 fcMax = (is_si ? ::ConvertToSysUnits( 70.05, unitMeasure::MPa ) : ::ConvertToSysUnits( 10.05, unitMeasure::KSI ) );
   if ( m_Fc < fcMin || fcMax < m_Fc )
      THROW(lrfdXPsLosses,fcOutOfRange);

   UpdateInitialLosses();
   UpdateLongTermLosses();

   m_IsDirty = false;
}

void lrfdNoncompositeApproximateLosses2005::UpdateInitialLosses() const
{
   // Losses from jacking to release
   Float64 t_days = ::ConvertFromSysUnits( m_Time, unitMeasure::Day );
   Float64 A = (m_Type == matPsStrand::LowRelaxation ? 40. : 10. );

   if ( t_days*24. < 1 )
      m_dfR1 = 0; // log10(<1) = < 0... t_days < 1/24 is less than one hour
   else
      m_dfR1 = (log10(24.*t_days)/A) * (m_Fpj/m_Fpy - 0.55) * m_Fpj;

   // Elastic shortening
   lrfdElasticShortening es(m_Fpj,
                            0,
                            m_dfR1,
                            0,
                            m_Aps,
                            0,
                            m_Ag,
                            m_Ig,
                            m_eperm,
                            0,
                            m_Mdlg,
                            1.0,
                            m_Eci,
                            m_Ep);

   m_Fcgp = es.PermanentStrand_Fcgp();
   m_dfES = es.PermanentStrand_ElasticShorteningLosses();
   m_P    = es.P();
}

void lrfdNoncompositeApproximateLosses2005::UpdateLongTermLosses() const
{
   if ( IsZero( m_Fpj ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfApprox = 0.0;
   }
   else
   {
      Float64 losses;
      const unitStress* p_unit;

      bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);

      if ( is_si )
         p_unit = &unitMeasure::MPa;
      else
         p_unit = &unitMeasure::KSI;

      Float64 lowRelaxReduction = 0.0;
      Float64 fc = ::ConvertFromSysUnits( m_Fc, *p_unit );

      switch (m_BeamType )
      {
      case SolidSlab:
          if ( m_Level == UpperBound )
              losses = (is_si ? 200 : 29) + (is_si ? 28 : 4)*m_PPR;
          else
              losses = (is_si ? 180 : 26) + (is_si ? 28 : 4)*m_PPR;

          lowRelaxReduction = is_si ? 41 : 6;
          break;

      case BoxBeam:
          if ( m_Level == UpperBound )
              losses = (is_si ? 145 : 21) + (is_si ? 28 : 4)*m_PPR;
          else
              losses = (is_si ? 130 : 19) + (is_si ? 28 : 4)*m_PPR;


          lowRelaxReduction = is_si ? 28 : 4;
          break;

      case SingleT:
      case Float64T:
      case TripleT:
      case HollowCore:
      case VoidedSlab:
          if ( m_Level == UpperBound )
              losses = (is_si ? 270 : 39)*(1.0 - 0.15*(fc-(is_si?41:6))/(is_si?41:6)) + (is_si?41:6)*m_PPR;
          else
              losses = (is_si ? 230 : 33)*(1.0 - 0.15*(fc-(is_si?41:6))/(is_si?41:6)) + (is_si?41:6)*m_PPR;

          lowRelaxReduction = is_si ? 55 : 8;
          break;
      }

      if ( m_Type == matPsStrand::LowRelaxation )
         losses -= lowRelaxReduction;

      m_dfApprox = ::ConvertToSysUnits( losses, *p_unit );
   }
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdNoncompositeApproximateLosses2005::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdNoncompositeApproximateLosses2005");

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
//   lrfdNoncompositeApproximateLosses2005 loss( matPsStrand::Gr1860,
//                               matPsStrand::LowRelaxation,
//                               lrfdNoncompositeApproximateLosses2005::IBeam,
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

   TESTME_EPILOG("lrfdNoncompositeApproximateLosses2005");
}

#endif // _UNITTEST


