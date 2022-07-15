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
#include <Lrfd\PsStrand.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\XCodeVersion.h>
#include <Math\QuadraticSolver.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdPsStrand
****************************************************************************/

// preconvert for performance
static const Float64 g_197000_MPA = WBFL::Units::ConvertToSysUnits( 197000., WBFL::Units::Measure::MPa );
static const Float64 g_1725_MPA   = WBFL::Units::ConvertToSysUnits( 1725, WBFL::Units::Measure::MPa );
static const Float64 g_1860_MPA   = WBFL::Units::ConvertToSysUnits( 1860, WBFL::Units::Measure::MPa );
static const Float64 g_2070_MPA   = WBFL::Units::ConvertToSysUnits( 2070, WBFL::Units::Measure::MPa);
static const Float64 g_28500_KSI  = WBFL::Units::ConvertToSysUnits( 28500., WBFL::Units::Measure::KSI );
static const Float64 g_250_KSI    = WBFL::Units::ConvertToSysUnits(  250, WBFL::Units::Measure::KSI );
static const Float64 g_270_KSI = WBFL::Units::ConvertToSysUnits(270, WBFL::Units::Measure::KSI);
static const Float64 g_300_KSI = WBFL::Units::ConvertToSysUnits(300, WBFL::Units::Measure::KSI);

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdPsStrand::~lrfdPsStrand()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
Float64 lrfdPsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade gr)
{
   Float64 fpu;
   bool is_si = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   if ( gr == WBFL::Materials::PsStrand::Grade::Gr1725 )
   {
      fpu = is_si ? g_1725_MPA : g_250_KSI;
   }
   else if (gr == WBFL::Materials::PsStrand::Grade::Gr1860)
   {
      fpu = is_si ? g_1860_MPA : g_270_KSI;
   }
   else if (gr == WBFL::Materials::PsStrand::Grade::Gr2070)
   {
      fpu = is_si ? g_2070_MPA : g_300_KSI;
   }
   else
   {
      ATLASSERT(false); // is there a new grade?
   }

   return fpu;
}

Float64 lrfdPsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade gr,WBFL::Materials::PsStrand::Type type)
{
   Float64 fpu = GetUltimateStrength( gr );
   Float64 fpy = fpu * ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.90 : 0.85 );
   return fpy;
}

Float64 lrfdPsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade gr,WBFL::Materials::PsStrand::Type type,Stage stage)
{
   Float64 fpu = GetUltimateStrength( gr );
   Float64 fpy = GetYieldStrength( gr, type );
   Float64 f_limit;

   bool is_first_edition = ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994 );
   switch( stage )
   {
   case Jacking:
        if ( !is_first_edition )
           THROW( lrfdXCodeVersion, BadVersion );

        f_limit = ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.78 : 0.72 ) * fpu;
        break;

   case BeforeTransfer:
        if ( is_first_edition )
           THROW( lrfdXCodeVersion, BadVersion );

        f_limit = ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.75 : 0.70 ) * fpu;
        break;

   case AfterTransfer:
        if ( !is_first_edition )
           THROW( lrfdXCodeVersion, BadVersion );

        f_limit = ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.74 : 0.70 ) * fpu;
        break;

   case AfterAllLosses:
        f_limit = 0.80 * fpy;
        break;
   }

   return f_limit;
}

Float64 lrfdPsStrand::GetModE()
{
   Float64 e;

   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      e = g_197000_MPA;
   }
   else
   {
      e = g_28500_KSI;
   }

   return e;
}

Float64 lrfdPsStrand::GetPjack(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer)
{
   Float64 fpj = lrfdPsStrand::GetFpj( strand, timeToXfer );
   Float64 Pjack = fpj * nStrands * strand.GetNominalArea();

   return Pjack;
}

Float64 lrfdPsStrand::GetPjack(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer,Float64 coeff)
{
   Float64 fpj = lrfdPsStrand::GetFpj( strand, timeToXfer, coeff );
   Float64 Pjack = fpj * nStrands * strand.GetNominalArea();

   return Pjack;
}

Float64 lrfdPsStrand::GetFpj(const WBFL::Materials::PsStrand& strand,Float64 timeToXfer)
{
   Float64 fpj;
   Float64 coeff; // coefficient on fpu
   if ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994 )
   {
      coeff = ( strand.GetType() == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.78 : 0.72 );
   }
   else
   {
      coeff = ( strand.GetType() == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.75 : 0.70 ); 
   }

   fpj = lrfdPsStrand::GetFpj( strand, timeToXfer, coeff );
   return fpj;
}

Float64 lrfdPsStrand::GetFpj(const WBFL::Materials::PsStrand& strand,Float64 timeToXfer,Float64 coeff)
{
   Float64 fpj;

   if ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994 || lrfdVersionMgr::ThirdEdition2004 < lrfdVersionMgr::GetVersion())
   {
      fpj = coeff * strand.GetUltimateStrength();
   }
   else
   {
      // Since the SI and US equations for DeltaFpR1 are the same in US and SI,
      // we will do our work in SI units.

      Float64 fbt; // stress before transfer
      fbt = coeff * strand.GetUltimateStrength();
      fbt = WBFL::Units::ConvertFromSysUnits( fbt, WBFL::Units::Measure::MPa );

      Float64 fpy = strand.GetYieldStrength();
      fpy = WBFL::Units::ConvertFromSysUnits( fpy, WBFL::Units::Measure::MPa );
      
      Float64 k; // Coefficient in denominator of equation 5.9.5.4.4b
      k = ( strand.GetType() == WBFL::Materials::PsStrand::Type::LowRelaxation ? 40.0 : 10.0 );

      Float64 t; // time in days
      t = WBFL::Units::ConvertFromSysUnits( timeToXfer, WBFL::Units::Measure::Day );

      Float64 K; // log(24t)/k from eqn 5.9.5.4.4b
      if ( t*24. < 1 )
         K = 0;
      else
         K = log10(24.0*t)/k;

      Float64 a,b,c; // coefficients for a quadratic equation
      a = K / fpy;
      b = -1*(1.0 + 0.55*K);
      c = fbt;

      Float64 fpj1, fpj2; // Solutions to a quadratic equation
      mathQuadraticSolver solver(a,b,c);
      bool bSolved = (solver.Solve( &fpj1, &fpj2 ) > 0);
      CHECK( bSolved );
      CHECK( fpj1 > fpj2 );

      fpj = fpj2;

      fpj = WBFL::Units::ConvertToSysUnits( fpj, WBFL::Units::Measure::MPa );
   }

   return fpj;
}

Float64 lrfdPsStrand::GetXferLength(const WBFL::Materials::PsStrand& strand,bool bEpoxyCoated)
{
   if ( bEpoxyCoated )
   {
      // see PCI "Guidelines for the use of Epoxy-Coated Strand"
      // PCI Journal, July-August 1993
      return 50.0 * strand.GetNominalDiameter();
   }
   else
   {
      // See LRFD
      return 60.0 * strand.GetNominalDiameter();
   }
}

Float64 lrfdPsStrand::GetDevLengthFactor(Float64 mbrDepth,bool bDebonded)
{
   Float64 k;
   Float64 d;
   Float64 d_limit;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
       d = WBFL::Units::ConvertFromSysUnits(mbrDepth,WBFL::Units::Measure::Millimeter);
       d_limit = 600;
   }
   else
   {
       d = WBFL::Units::ConvertFromSysUnits(mbrDepth,WBFL::Units::Measure::Inch);
       d_limit = 24;
   }


   if ( bDebonded )
   {
      k = 2.0;
   }
   else if ( d <= d_limit && lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
   {
      k = 1.0;
   }
   else
   {
      k = 1.6;
   }

   return k;
}

Float64 lrfdPsStrand::GetDevLength(const WBFL::Materials::PsStrand& strand, Float64 fps, Float64 fpe, Float64 mbrDepth, bool bDebonded)
{
   Float64 db = strand.GetNominalDiameter();
   return GetDevLength(db, fps, fpe, mbrDepth, bDebonded);
}

Float64 lrfdPsStrand::GetDevLength(Float64 db, Float64 fps, Float64 fpe, Float64 mbrDepth, bool bDebonded)
{
   Float64 ld;
   Float64 k = GetDevLengthFactor(mbrDepth,bDebonded);
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      db  = WBFL::Units::ConvertFromSysUnits(db,WBFL::Units::Measure::Millimeter);
      fps = WBFL::Units::ConvertFromSysUnits(fps,WBFL::Units::Measure::MPa);
      fpe = WBFL::Units::ConvertFromSysUnits(fpe,WBFL::Units::Measure::MPa);
      ld = k*db*(0.15*fps - 0.097*fpe);
      ld = WBFL::Units::ConvertToSysUnits(ld,WBFL::Units::Measure::Millimeter);
   }
   else
   {
      db  = WBFL::Units::ConvertFromSysUnits(db,WBFL::Units::Measure::Inch);
      fps = WBFL::Units::ConvertFromSysUnits(fps,WBFL::Units::Measure::KSI);
      fpe = WBFL::Units::ConvertFromSysUnits(fpe,WBFL::Units::Measure::KSI);
      ld = k*db*(fps - 2.*fpe/3.);
      ld = WBFL::Units::ConvertToSysUnits(ld,WBFL::Units::Measure::Inch);
   }

   return ld;
}

Float64 lrfdPsStrand::GetFpjPT(const WBFL::Materials::PsStrand& strand)
{
   Float64 fpy = strand.GetYieldStrength();
   return 0.90*fpy;
}

Float64 lrfdPsStrand::GetPjackPT(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands)
{
   Float64 fpj = GetFpjPT(strand);
   Float64 Apt = nStrands*strand.GetNominalArea();
   return Apt*fpj;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdPsStrand::AssertValid() const
{
   return true;
}

void lrfdPsStrand::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for lrfdPsStrand" << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <Lrfd\AutoVersion.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\StrandPool.h>
bool lrfdPsStrand::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("lrfdPsStrand");
   lrfdAutoVersion auto_ver;

   Uint16 nStrands = 10;
   Float64 Pjack;
   Float64 xferTime = WBFL::Units::ConvertToSysUnits( 24.0, WBFL::Units::Measure::Hour );
   const WBFL::Materials::PsStrand* pStrand = 0;
   lrfdStrandPool* pPool = lrfdStrandPool::GetInstance();

   // LRFD 1st Edition

   lrfdVersionMgr::SetVersion( lrfdVersionMgr::FirstEdition1994 );
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   // Grade 1725 SR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1153.82, 0.01 ) );

   // Grade 1725 LR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1249.97, 0.01 ) );

   // Grade 1860 SR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1321.92, 0.01 ) );

   // Grade 1860 LR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1432.08, 0.01 ) );


   // LRFD 1st Edition with 1996 and/or 1997 interim provisions

   lrfdVersionMgr::SetVersion( lrfdVersionMgr::FirstEditionWith1997Interims );

   // Grade 1725 SR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1171.98, 0.01 ) );

   // Grade 1725 LR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1725, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1214.12, 0.01 ) );

   // Grade 1860 SR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::StressRelieved, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1342.72, 0.01 ) );

   // Grade 1860 LR
   pStrand = pPool->GetStrand( WBFL::Materials::PsStrand::Grade::Gr1860, WBFL::Materials::PsStrand::Type::LowRelaxation, WBFL::Materials::PsStrand::Coating::None, WBFL::Materials::PsStrand::Size::D1270 );
   Pjack = lrfdPsStrand::GetPjack( *pStrand, nStrands, xferTime );
   Pjack = WBFL::Units::ConvertFromSysUnits( Pjack, WBFL::Units::Measure::Kilonewton );
   TRY_TESTME( IsEqual( Pjack, 1391.01, 0.01 ) );

   TESTME_EPILOG("lrfdPsStrand");
}
#endif // _UNITTEST


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


