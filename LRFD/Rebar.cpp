///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// precompute conversions
static const Float64 g_140p0_MPA  = ::ConvertToSysUnits(140.0,unitMeasure::MPa);

static const Float64 g_20p0_KSI   = ::ConvertToSysUnits(20.0,unitMeasure::KSI);

static const Float64 g_150_MM = ::ConvertToSysUnits( 150, unitMeasure::Millimeter );
static const Float64 g_300_MM = ::ConvertToSysUnits( 300, unitMeasure::Millimeter );
static const Float64 g_600_MM = ::ConvertToSysUnits( 600, unitMeasure::Millimeter );

static const Float64 g_6_IN =  ::ConvertToSysUnits( 6, unitMeasure::Inch );
static const Float64 g_12_IN = ::ConvertToSysUnits(12, unitMeasure::Inch );
static const Float64 g_24_IN = ::ConvertToSysUnits(24, unitMeasure::Inch );


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
#pragma Reminder("Need min confinement bar in SI units") // rebar pool not set up for this
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
      Float64 bv_u = ::ConvertFromSysUnits(bv, unitMeasure::Millimeter);
      Float64 fy_u = ::ConvertFromSysUnits(fy, unitMeasure::MPa);
      Float64 fc_u = ::ConvertFromSysUnits(fc, unitMeasure::MPa);
      Float64 avs_u = 0.083*sqrt(fc_u)*bv_u/fy_u;
      avs = ConvertToSysUnits(avs_u, unitMeasure::Millimeter2PerMillimeter);
   }
   else
   {
      Float64 bv_u = ::ConvertFromSysUnits(bv, unitMeasure::Inch);
      Float64 fy_u = ::ConvertFromSysUnits(fy, unitMeasure::KSI);
      Float64 fc_u = ::ConvertFromSysUnits(fc, unitMeasure::KSI);
      Float64 avs_u = 0.0316*sqrt(fc_u)*bv_u/fy_u;
      avs = ConvertToSysUnits(avs_u, unitMeasure::Inch2PerInch);
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

Float64  lrfdRebar::GetTensileDevelopmentLength(const matRebar& rebar, Float64 fc)
{
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
      Float64 ab_u = ::ConvertFromSysUnits(ab,unitMeasure::Millimeter2);
      Float64 db_u = ::ConvertFromSysUnits(db,unitMeasure::Millimeter);
      Float64 fy_u = ::ConvertFromSysUnits(fy,unitMeasure::MPa);
      Float64 fc_u = ::ConvertFromSysUnits(fc,unitMeasure::MPa);
      CHECK(fc_u>0);

      Float64 dl_u=0;

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
         CHECK(0); // an unknown bar snuck in.

      dl_u = max(dl_u, 305);

      dl = ConvertToSysUnits(dl_u,unitMeasure::Millimeter);
   }
   else
   {
      Float64 ab_u = ::ConvertFromSysUnits(ab,unitMeasure::Inch2);
      Float64 db_u = ::ConvertFromSysUnits(db,unitMeasure::Inch);
      Float64 fy_u = ::ConvertFromSysUnits(fy,unitMeasure::KSI);
      Float64 fc_u = ::ConvertFromSysUnits(fc,unitMeasure::KSI);
      CHECK(fc_u>0);

      Float64 dl_u=0;

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
         CHECK(0); // an unknown bar snuck in.

      dl_u = max(dl_u, 12.0);

      dl = ConvertToSysUnits(dl_u,unitMeasure::Inch);
   }

   return dl;
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


