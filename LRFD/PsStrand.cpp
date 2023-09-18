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
#include <Lrfd\PsStrand.h>
#include <Lrfd/BDSManager.h>
#include <Lrfd\XCodeVersion.h>
#include <Math\QuadraticSolver.h>

using namespace WBFL::LRFD;

Float64 PsStrand::GetUltimateStrength(WBFL::Materials::PsStrand::Grade gr)
{
   Float64 fpu;
   bool is_si = ( BDSManager::GetUnits() == BDSManager::Units::SI );
   if ( gr == WBFL::Materials::PsStrand::Grade::Gr1725 )
   {
      fpu = is_si ? WBFL::Units::ConvertToSysUnits(1725, WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(250, WBFL::Units::Measure::KSI);
   }
   else if (gr == WBFL::Materials::PsStrand::Grade::Gr1860)
   {
      fpu = is_si ? WBFL::Units::ConvertToSysUnits(1860, WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(270, WBFL::Units::Measure::KSI);
   }
   else if (gr == WBFL::Materials::PsStrand::Grade::Gr2070)
   {
      fpu = is_si ? WBFL::Units::ConvertToSysUnits(2070, WBFL::Units::Measure::MPa) : WBFL::Units::ConvertToSysUnits(300, WBFL::Units::Measure::KSI);
   }
   else
   {
      CHECK(false); // is there a new grade?
   }

   return fpu;
}

Float64 PsStrand::GetYieldStrength(WBFL::Materials::PsStrand::Grade gr,WBFL::Materials::PsStrand::Type type)
{
   Float64 fpu = GetUltimateStrength( gr );
   Float64 fpy = fpu * ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.90 : 0.85 );
   return fpy;
}

Float64 PsStrand::GetStressLimit(WBFL::Materials::PsStrand::Grade gr,WBFL::Materials::PsStrand::Type type,Stage stage)
{
   Float64 fpu = GetUltimateStrength( gr );
   Float64 fpy = GetYieldStrength( gr, type );
   Float64 f_limit;

   bool is_first_edition = ( BDSManager::GetEdition() == BDSManager::Edition::FirstEdition1994 );
   switch( stage )
   {
   case Stage::Jacking:
        if ( !is_first_edition )
           WBFL_LRFD_THROW( XCodeVersion, BadVersion );

        f_limit = ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.78 : 0.72 ) * fpu;
        break;

   case Stage::BeforeTransfer:
        if ( is_first_edition )
           WBFL_LRFD_THROW( XCodeVersion, BadVersion );

        f_limit = ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.75 : 0.70 ) * fpu;
        break;

   case Stage::AfterTransfer:
        if ( !is_first_edition )
           WBFL_LRFD_THROW( XCodeVersion, BadVersion );

        f_limit = ( type == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.74 : 0.70 ) * fpu;
        break;

   case Stage::AfterAllLosses:
        f_limit = 0.80 * fpy;
        break;
   }

   return f_limit;
}

Float64 PsStrand::GetModE()
{
   Float64 e;

   if ( BDSManager::GetUnits() == BDSManager::Units::SI )
   {
      e = WBFL::Units::ConvertToSysUnits(197000., WBFL::Units::Measure::MPa);
   }
   else
   {
      e = WBFL::Units::ConvertToSysUnits(28500., WBFL::Units::Measure::KSI);
   }

   return e;
}

Float64 PsStrand::GetPjack(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer)
{
   Float64 fpj = PsStrand::GetFpj( strand, timeToXfer );
   Float64 Pjack = fpj * nStrands * strand.GetNominalArea();

   return Pjack;
}

Float64 PsStrand::GetPjack(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands,Float64 timeToXfer,Float64 coeff)
{
   Float64 fpj = PsStrand::GetFpj( strand, timeToXfer, coeff );
   Float64 Pjack = fpj * nStrands * strand.GetNominalArea();

   return Pjack;
}

Float64 PsStrand::GetFpj(const WBFL::Materials::PsStrand& strand,Float64 timeToXfer)
{
   Float64 fpj;
   Float64 coeff; // coefficient on fpu
   if ( BDSManager::GetEdition() == BDSManager::Edition::FirstEdition1994 )
   {
      coeff = ( strand.GetType() == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.78 : 0.72 );
   }
   else
   {
      coeff = ( strand.GetType() == WBFL::Materials::PsStrand::Type::LowRelaxation ? 0.75 : 0.70 ); 
   }

   fpj = PsStrand::GetFpj( strand, timeToXfer, coeff );
   return fpj;
}

Float64 PsStrand::GetFpj(const WBFL::Materials::PsStrand& strand,Float64 timeToXfer,Float64 coeff)
{
   Float64 fpj;

   if ( BDSManager::GetEdition() == BDSManager::Edition::FirstEdition1994 || BDSManager::Edition::ThirdEdition2004 < BDSManager::GetEdition())
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

      WBFL::Math::QuadraticSolver solver(a,b,c);
      auto [fpj1, fpj2] = solver.Solve();
      CHECK(fpj1.has_value() and fpj2.has_value());
      CHECK(fpj1.value() < fpj2.value());
      fpj = fpj2.value(); // we want the larger value
      fpj = WBFL::Units::ConvertToSysUnits( fpj, WBFL::Units::Measure::MPa );
   }

   return fpj;
}

Float64 PsStrand::GetXferLength(const WBFL::Materials::PsStrand& strand,bool bEpoxyCoated)
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

Float64 PsStrand::GetDevLengthFactor(Float64 mbrDepth,bool bDebonded)
{
   Float64 k;
   Float64 d;
   Float64 d_limit;
   if ( BDSManager::GetUnits() == BDSManager::Units::SI )
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
   else if ( d <= d_limit && BDSManager::Edition::ThirdEditionWith2005Interims <= BDSManager::GetEdition() )
   {
      k = 1.0;
   }
   else
   {
      k = 1.6;
   }

   return k;
}

Float64 PsStrand::GetDevLength(const WBFL::Materials::PsStrand& strand, Float64 fps, Float64 fpe, Float64 mbrDepth, bool bDebonded)
{
   Float64 db = strand.GetNominalDiameter();
   return GetDevLength(db, fps, fpe, mbrDepth, bDebonded);
}

Float64 PsStrand::GetDevLength(Float64 db, Float64 fps, Float64 fpe, Float64 mbrDepth, bool bDebonded)
{
   Float64 ld;
   Float64 k = GetDevLengthFactor(mbrDepth,bDebonded);
   if ( BDSManager::GetUnits() == BDSManager::Units::SI)
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

Float64 PsStrand::GetFpjPT(const WBFL::Materials::PsStrand& strand)
{
   Float64 fpy = strand.GetYieldStrength();
   return 0.90*fpy;
}

Float64 PsStrand::GetPjackPT(const WBFL::Materials::PsStrand& strand,StrandIndexType nStrands)
{
   Float64 fpj = GetFpjPT(strand);
   Float64 Apt = nStrands*strand.GetNominalArea();
   return Apt*fpj;
}
