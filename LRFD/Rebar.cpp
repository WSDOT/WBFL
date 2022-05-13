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
#include <Lrfd\Rebar.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\XCodeVersion.h>
#include <Lrfd\RebarPool.h>
#include <Lrfd\ConcreteUtil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// precompute conversions
static const Float64 g_140p0_MPA  = WBFL::Units::ConvertToSysUnits(140.0,WBFL::Units::Measure::MPa);

static const Float64 g_20p0_KSI   = WBFL::Units::ConvertToSysUnits(20.0,WBFL::Units::Measure::KSI);

static const Float64 g_150_MM = WBFL::Units::ConvertToSysUnits( 150, WBFL::Units::Measure::Millimeter );
static const Float64 g_300_MM = WBFL::Units::ConvertToSysUnits( 300, WBFL::Units::Measure::Millimeter );
static const Float64 g_600_MM = WBFL::Units::ConvertToSysUnits( 600, WBFL::Units::Measure::Millimeter );

static const Float64 g_6_IN =  WBFL::Units::ConvertToSysUnits( 6, WBFL::Units::Measure::Inch );
static const Float64 g_12_IN = WBFL::Units::ConvertToSysUnits(12, WBFL::Units::Measure::Inch );
static const Float64 g_24_IN = WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::Inch );


/****************************************************************************
CLASS
   lrfdRebar
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdRebar::~lrfdRebar()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Float64 lrfdRebar::GetMaxBurstingStress(Float64 fy)
{
   CHECK(fy>0.0);
   bool is_si = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   if( lrfdVersionMgr::GetVersion() >= lrfdVersionMgr::FirstEditionWith1996Interims )
   {
      Float64 fym = is_si ? g_140p0_MPA : g_20p0_KSI;

      fy = min(fy, fym);
   }

   return fy;
}

Float64 lrfdRebar::GetBurstingZoneLength(Float64 h)
{
   if( lrfdVersionMgr::GetVersion() >= lrfdVersionMgr::FirstEditionWith1996Interims )
      return h/5;
   else
      return h/4;
}

matRebar::Size lrfdRebar::GetMinConfinmentBarSize()
{
   return matRebar::bs3;
}

Float64 lrfdRebar::GetMaxConfinmentBarSpacing()
{
   bool is_si = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   Float64 bss = is_si ? g_150_MM : g_6_IN;
   return bss;
}

Float64 lrfdRebar::GetMinConfinmentAvS()
{
   // manufacture a bogus rebar to get properties from
   lrfdRebarPool* rp = lrfdRebarPool::GetInstance();
   CHECK(rp);
   const matRebar* pr = rp->GetRebar(matRebar::A615,matRebar::Grade60,matRebar::bs3);
   CHECK(pr);

   Float64 s  = lrfdRebar::GetMaxConfinmentBarSpacing();
   CHECK(s>0.0);
   Float64 av = pr->GetNominalArea();
   return av/s;
}

Float64 lrfdRebar::GetAvOverSMin(Float64 fc, Float64 bv, Float64 fy)
{
   CHECK(fy>0);
   Float64 avs;
   bool is_si = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   if (is_si)
   {
      Float64 bv_u = WBFL::Units::ConvertFromSysUnits(bv, WBFL::Units::Measure::Millimeter);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy, WBFL::Units::Measure::MPa);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::MPa);
      Float64 avs_u = 0.083*sqrt(fc_u)*bv_u/fy_u;
      avs = ConvertToSysUnits(avs_u, WBFL::Units::Measure::Millimeter2PerMillimeter);
   }
   else
   {
      Float64 bv_u = WBFL::Units::ConvertFromSysUnits(bv, WBFL::Units::Measure::Inch);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy, WBFL::Units::Measure::KSI);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc, WBFL::Units::Measure::KSI);
      Float64 avs_u = 0.0316*sqrt(fc_u)*bv_u/fy_u;
      avs = ConvertToSysUnits(avs_u, WBFL::Units::Measure::Inch2PerInch);
   }

   return avs;

}

void lrfdRebar::GetMaxStirrupSpacing(Float64* sUnderLimit, Float64* sOverLimit)
{
   bool is_si = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   if (is_si)
   {
      *sUnderLimit = g_600_MM;
      *sOverLimit  = g_300_MM;
   }
   else
   {
      *sUnderLimit = g_24_IN;
      *sOverLimit  = g_12_IN;
   }
}

Float64 lrfdRebar::GetTensileDevelopmentLength(const matRebar& rebar, Float64 fc)
{
   ATLASSERT(lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims);

   Float64 dl=0.0;

   Float64 ab = rebar.GetNominalArea();
   Float64 db = rebar.GetNominalDimension();
   Float64 fy = rebar.GetYieldStrength();

   // get size
   matRebar::Size size = rebar.GetSize();

   // Equations taken from 5.11.2.1.1
   bool is_si = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   if (is_si)
   {
      Float64 ab_u = WBFL::Units::ConvertFromSysUnits(ab,WBFL::Units::Measure::Millimeter2);
      Float64 db_u = WBFL::Units::ConvertFromSysUnits(db,WBFL::Units::Measure::Millimeter);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::MPa);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::MPa);
      ATLASSERT(0 < fc_u);

      Float64 dl_u = 0;

      if (size==matRebar::bs3 || size==matRebar::bs4 || size==matRebar::bs5  || size==matRebar::bs6 || size==matRebar::bs7 ||
          size==matRebar::bs8 || size==matRebar::bs9 || size==matRebar::bs10 || size==matRebar::bs11)
      {
         dl_u = 0.02*ab_u*fy_u / sqrt(fc_u);
         dl_u = max(dl_u, 0.06 * db_u * fy_u);
      }
      else if (size==matRebar::bs14)
      {
         dl_u = 25 * fy_u / sqrt(fc_u);
      }
      else if (size==matRebar::bs18)
      {
         dl_u = 34 * fy_u / sqrt(fc_u);
      }
      else
      {
         ATLASSERT(false); // an unknown bar snuck in.
      }

      dl_u = max(dl_u, 305);

      dl = ConvertToSysUnits(dl_u,WBFL::Units::Measure::Millimeter);
   }
   else
   {
      Float64 ab_u = WBFL::Units::ConvertFromSysUnits(ab,WBFL::Units::Measure::Inch2);
      Float64 db_u = WBFL::Units::ConvertFromSysUnits(db,WBFL::Units::Measure::Inch);
      Float64 fy_u = WBFL::Units::ConvertFromSysUnits(fy,WBFL::Units::Measure::KSI);
      Float64 fc_u = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);
      ATLASSERT(0 < fc_u);

      Float64 dl_u = 0;

      if (size==matRebar::bs3 || size==matRebar::bs4 || size==matRebar::bs5  || size==matRebar::bs6 || size==matRebar::bs7 ||
          size==matRebar::bs8 || size==matRebar::bs9 || size==matRebar::bs10 || size==matRebar::bs11)
      {
         dl_u = 1.25*ab_u*fy_u / sqrt(fc_u);
         dl_u = max(dl_u, 0.4 * db_u * fy_u);
      }
      else if (size==matRebar::bs14)
      {
         dl_u = 2.7*fy_u / sqrt(fc_u);
      }
      else if (size==matRebar::bs18)
      {
         dl_u = 3.5*fy_u / sqrt(fc_u);
      }
      else
      {
         ATLASSERT(false); // an unknown bar snuck in.
      }

      dl_u = max(dl_u, 12.0);

      dl = ConvertToSysUnits(dl_u,WBFL::Units::Measure::Inch);
   }

   return dl;
}

Float64 lrfdRebar::GetHookExtension(matRebar::Size size,Float64 db,Usage usage,Hook hook)
{
   if ( usage == Longitudinal )
   {
      if ( hook == hook90 )
      {
         return 12*db;
      }
      else if ( hook == hook180 )
      {
         return Max(WBFL::Units::ConvertToSysUnits(2.5,WBFL::Units::Measure::Inch),4*db);
      }
   }
   else if ( usage == Transverse )
   {
      if ( hook == hook90 )
      {
         if ( size <= matRebar::bs5 )
         {
            return 6*db;
         }
         else if ( matRebar::bs6 <= size && size <= matRebar::bs8 )
         {
            return 12*db;
         }
      }
      else if ( hook == hook135 )
      {
         if ( size <= matRebar::bs8 )
         {
            return 6*db;
         }
      }
   }
   else
   {
      ATLASSERT(usage == Seismic);
      if ( hook == hook135 )
      {
         return Max(WBFL::Units::ConvertToSysUnits(3.0,WBFL::Units::Measure::Inch),6*db);
      }
   }

   ATLASSERT(false);
   // invalid combination of usage and hook type
   // See LRFD 5.10.2.1 for longitudinal standard hooks
   return 0;
}

Float64 lrfdRebar::GetBendDiameter(matRebar::Size size,Float64 db,Usage usage,bool bFractional)
{
   Float64 K = 0;
   switch(size)
   {
   case matRebar::bs3:
   case matRebar::bs4:
   case matRebar::bs5:
      if ( usage == lrfdRebar::Longitudinal )
      {
         K = 6; // general
      }
      else
      {
         K = 4; // stirrups and ties
      }
      break;

   case matRebar::bs6:
   case matRebar::bs7:
   case matRebar::bs8:
      K = 6;
      break;


   case matRebar::bs9:
   case matRebar::bs10:
   case matRebar::bs11:
      K = 8;
      break;

   case matRebar::bs14:
   case matRebar::bs18:
      K = 10;
      break;

   default:
      ATLASSERT(false); // new bar size?
   }

   if ( bFractional )
   {
      return K;
   }

   Float64 D = K*db;
   return D;
}

Float64 lrfdRebar::GetCompressionControlledStrainLimit(matRebar::Grade grade)
{
   Float64 ecl;
   if ( grade <= matRebar::Grade60 )
   {
      ecl = 0.002;
   }
   else if ( matRebar::Grade100 <= grade )
   {
      ecl = 0.004;
   }
   else
   {
      ATLASSERT(grade == matRebar::Grade75 || grade == matRebar::Grade80);
      Float64 fy = (grade == matRebar::Grade75 ? 75 : 80);
      ecl = ::LinInterp(fy-60.,0.002,0.004,100.-60.);
   }

   return ecl;
}

Float64 lrfdRebar::GetTensionControlledStrainLimit(matRebar::Grade grade)
{
   Float64 etl;
   if ( grade <= matRebar::Grade75 )
   {
      etl = 0.005;
   }
   else if ( matRebar::Grade100 <= grade )
   {
      etl = 0.008;
   }
   else
   {
      ATLASSERT(grade == matRebar::Grade80);
      Float64 fy = 80;
      etl = ::LinInterp(fy-75,0.005,0.008,100.-75.);
   }

   return etl;
}

REBARDEVLENGTHDETAILS lrfdRebar::GetRebarDevelopmentLengthDetails(matRebar::Size size, Float64 Ab, Float64 db, Float64 fy, const matConcrete& concrete)
{
   return lrfdRebar::GetRebarDevelopmentLengthDetails(size,Ab,db,fy,concrete.GetType(),concrete.GetFc(),concrete.HasAggSplittingStrength(),concrete.GetAggSplittingStrength(),concrete.GetDensity());
}

REBARDEVLENGTHDETAILS lrfdRebar::GetRebarDevelopmentLengthDetails(matRebar::Size size, Float64 Ab, Float64 db, Float64 fy, matConcrete::Type type, Float64 fc, bool isFct, Float64 Fct,Float64 density)
{
   REBARDEVLENGTHDETAILS details;
   details.Ab = Ab;
   details.db = db;
   details.fy = fy;

   details.fc = fc;

   details.lambdaRl = 1.0; // intialize lambdas even though only used for 2015+
   details.lambdaLw = 1.0;

   // LRFD 5.11.2.1
   if ( lrfdVersionMgr::SeventhEditionWith2015Interims <= lrfdVersionMgr::GetVersion())
   {
      Float64 Ab = WBFL::Units::ConvertFromSysUnits(details.Ab,WBFL::Units::Measure::Inch2);
      Float64 db = WBFL::Units::ConvertFromSysUnits(details.db,WBFL::Units::Measure::Inch);
      Float64 fc = WBFL::Units::ConvertFromSysUnits(details.fc,WBFL::Units::Measure::KSI);
      Float64 fy = WBFL::Units::ConvertFromSysUnits(details.fy,WBFL::Units::Measure::KSI);
   
      if (type == matConcrete::PCI_UHPC)
      {
         details.ldb1 = 8.0 * db * fy / 60.0;
         details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1, WBFL::Units::Measure::Inch);
      }
      else
      {
         details.ldb1 = 2.4 * db * fy / sqrt(fc);
         details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1, WBFL::Units::Measure::Inch);
      }
      details.ldb2 = 0.0;

      Float64 ldb_min = WBFL::Units::ConvertToSysUnits(12.0,WBFL::Units::Measure::Inch);

      details.ldb = Max(details.ldb1,details.ldb2,ldb_min);
   
      // reinforcment location factor: only increase for concrete strength
      // we could get more fancy here and actually use location information in the future
      if (10.0 < fc)
      {
         details.lambdaRl = 1.3;
      }
      else
      {
         details.lambdaRl = 1.0;
      }

      // lightweight concrete factor
      if ( lrfdVersionMgr::SeventhEditionWith2016Interims <= lrfdVersionMgr::GetVersion())
      {
         details.lambdaLw = lrfdConcreteUtil::ComputeConcreteDensityModificationFactor((matConcrete::Type)type,density,isFct,Fct,fc);

         details.factor = details.lambdaRl / details.lambdaLw;// Eqn 5.11.2.1.1-1 was modified in LRFD 2016... using lambdaLw for lambda in the equation
      }
      else
      {
         if (type==matConcrete::Normal || type == matConcrete::PCI_UHPC)
         {
            details.lambdaLw = 1.0;
         }
         else if (type==matConcrete::AllLightweight || type==matConcrete::SandLightweight)
         {
            details.lambdaLw = 1.3;
         }
         else
         {
            ATLASSERT(0); // new type?
            details.lambdaLw = 1.0;
         }

         details.factor = details.lambdaRl * details.lambdaLw;
      }

   }
   else
   {
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::US )
      {
         Float64 Ab = WBFL::Units::ConvertFromSysUnits(details.Ab,WBFL::Units::Measure::Inch2);
         Float64 db = WBFL::Units::ConvertFromSysUnits(details.db,WBFL::Units::Measure::Inch);
         Float64 fc = WBFL::Units::ConvertFromSysUnits(details.fc,WBFL::Units::Measure::KSI);
         Float64 fy = WBFL::Units::ConvertFromSysUnits(details.fy,WBFL::Units::Measure::KSI);

         if (size == matRebar::bs14)
         {
            details.ldb1 = 2.70*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Inch);
         
            details.ldb2 = 0.0;
         }
         else if (size == matRebar::bs18)
         {
            details.ldb1 = 3.5*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Inch);
         
            details.ldb2 = 0.0;
         }
         else
         {
            details.ldb1 = 1.25*Ab*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Inch);

            details.ldb2 = 0.4*db*fy;
            details.ldb2 = WBFL::Units::ConvertToSysUnits(details.ldb2,WBFL::Units::Measure::Inch);
         }

         Float64 ldb_min = WBFL::Units::ConvertToSysUnits(12.0,WBFL::Units::Measure::Inch);

         details.ldb = Max(details.ldb1,details.ldb2,ldb_min);
      }
      else
      {
         Float64 Ab = WBFL::Units::ConvertFromSysUnits(details.Ab,WBFL::Units::Measure::Millimeter2);
         Float64 db = WBFL::Units::ConvertFromSysUnits(details.db,WBFL::Units::Measure::Millimeter);
         Float64 fc = WBFL::Units::ConvertFromSysUnits(details.fc,WBFL::Units::Measure::MPa);
         Float64 fy = WBFL::Units::ConvertFromSysUnits(details.fy,WBFL::Units::Measure::MPa);
      
         if (size == matRebar::bs14)
         {
            details.ldb1 = 25*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Millimeter);
         
            details.ldb2 = 0.0;
         }
         else if (size == matRebar::bs18)
         {
            details.ldb1 = 34*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Millimeter);
         
            details.ldb2 = 0.0;
         }
         else
         {
            details.ldb1 = 0.02*Ab*fy/sqrt(fc);
            details.ldb1 = WBFL::Units::ConvertToSysUnits(details.ldb1,WBFL::Units::Measure::Millimeter);
         
            details.ldb2 = 0.06*db*fy;
            details.ldb2 = WBFL::Units::ConvertToSysUnits(details.ldb2,WBFL::Units::Measure::Millimeter);
         }

         Float64 ldb_min = WBFL::Units::ConvertToSysUnits(12.0,WBFL::Units::Measure::Millimeter);

         details.ldb = Max(details.ldb1,details.ldb2,ldb_min);
      }

      // Compute and apply factor for LWC
      if (type==matConcrete::Normal || type == matConcrete::PCI_UHPC)
      {
         details.factor = 1.0;
      }
      else
      {
         if (isFct)
         {
            // compute factor
            Float64 fck  = WBFL::Units::ConvertFromSysUnits(fc,WBFL::Units::Measure::KSI);
            Float64 fctk = WBFL::Units::ConvertFromSysUnits(Fct,WBFL::Units::Measure::KSI);

            details.factor = 0.22 * sqrt(fck) / fctk;
            details.factor = Min(details.factor, 1.0);
         }
         else
         {
            // fct not specified
            if (type==matConcrete::AllLightweight)
            {
               details.factor = 1.3;
            }
            else if (type==matConcrete::SandLightweight)
            {
               details.factor = 1.2;
            }
            else
            {
               ATLASSERT(false); // new type?
               details.factor = 1.0;
            }
         }
      }
   }

   details.ld = details.ldb * details.factor;

   return details;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdRebar::AssertValid() const
{
   return true;
}

void lrfdRebar::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdRebar" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <Lrfd\AutoVersion.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\StrandPool.h>
bool lrfdRebar::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdRebar");
   TESTME_EPILOG("lrfdRebar");
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


