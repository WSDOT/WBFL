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
#include <Lrfd\CreepCoefficient2005.h>
#include <Lrfd\XCreepCoefficient.h>
#include <Lrfd\VersionMgr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdCreepCoefficient2005
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdCreepCoefficient2005::lrfdCreepCoefficient2005()
{
   m_bUpdate = true;
   m_K1 = 1;
   m_K2 = 1;
}

lrfdCreepCoefficient2005::~lrfdCreepCoefficient2005()
{
}

Float64 lrfdCreepCoefficient2005::GetCreepCoefficient(Float64 t, Float64 ti) const
{
    if (m_bUpdate)
        Update();

    ti = GetAdjustedInitialAge(ti);

    Float64 C = GetUltimateCreep();
    Float64 ktd = GetKtd(t);
    Float64 kl = GetKl(ti);
    Float64 Ct = C * m_K1 * m_K2 * m_kvs * m_khc * m_kf * ktd * kl;
    return Ct;
}

Float64 lrfdCreepCoefficient2005::GetAdjustedInitialAge(Float64 ti) const
{
   Float64 tiAdjusted = ti;
   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FourthEdition2007 && m_CuringMethod == Normal)
   {
      // NCHRP 496...
      // ti = age of concrete, in days, when load is initially applied
      // for accelerated curing, or the age minus 6 days for moist (normal) curing
      Float64 one_day = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
      tiAdjusted -= (m_CuringMethodTimeAdjustmentFactor-one_day);
      if ( tiAdjusted < 0 )
      {
         tiAdjusted = one_day;
      }
   }

   return tiAdjusted;
}


void lrfdCreepCoefficient2005::SetK1(Float64 k1)
{
   m_K1 = k1;
}

Float64 lrfdCreepCoefficient2005::GetK1() const
{
   return m_K1;
}

void lrfdCreepCoefficient2005::SetK2(Float64 k2)
{
   m_K2 = k2;
}

Float64 lrfdCreepCoefficient2005::GetK2() const
{
   return m_K2;
}

Float64 lrfdCreepCoefficient2005::GetKvs() const
{
   if ( m_bUpdate )
      Update();

   return m_kvs;
}

Float64 lrfdCreepCoefficient2005::GetKhc() const
{
   if ( m_bUpdate )
      Update();

   return m_khc;
}

Float64 lrfdCreepCoefficient2005::GetKtd(Float64 t) const
{
    return ComputeKtd(t);
}

Float64 lrfdCreepCoefficient2005::GetKl(Float64 ti) const
{
   ti = WBFL::Units::ConvertFromSysUnits(ti, WBFL::Units::Measure::Day);
   return pow(ti, -0.118);
}

Float64 lrfdCreepCoefficient2005::GetUltimateCreep() const
{
   return 1.9;
}

Float64 lrfdCreepCoefficient2005::ComputeKvs() const
{
   bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // Check volume to surface ratio
   // Sometimes, V and S are zero... like in the case of a noncomposite girder and the
   // creep due to slab shrinkage is being computer... don't divide by zero
   Float64 VS = (m_S == 0 ? 0 : m_V / m_S);

   // kvs_limit is 1.0 in 2005, changed to 0.0 in 2006, changed back to 1.0 in 2007
   Float64 kvs_limit = (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::ThirdEditionWith2006Interims ? 0.0 : 1.0);

   Float64 kvs;
   if (bSI)
   {
      kvs = Max(kvs_limit, 1.45 - 0.0051 * WBFL::Units::ConvertFromSysUnits(VS, WBFL::Units::Measure::Millimeter));
      ATLASSERT(lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims);
   }
   else
   {
      kvs = Max(kvs_limit, 1.45 - 0.13 * WBFL::Units::ConvertFromSysUnits(VS, WBFL::Units::Measure::Inch));
   }

   return kvs;
}

Float64 lrfdCreepCoefficient2005::ComputeKhc() const
{
   return 1.56 - 0.008 * m_H;
}

Float64 lrfdCreepCoefficient2005::ComputeKf() const
{
   Float64 kf;
   bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
   if (bSI)
   {
      kf = 35.0 / (7.0 + WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::MPa));
      ATLASSERT(lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims);
   }
   else
   {
      kf = 5.0 / (1.0 + WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI));
   }

   return kf;
}

//Float64 lrfdCreepCoefficient2005::ComputeKtd() const
//{
//    return ComputeKtd(m_t);
//}

Float64 lrfdCreepCoefficient2005::ComputeKtd(Float64 t) const
{
   bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   t = WBFL::Units::ConvertFromSysUnits(t, WBFL::Units::Measure::Day);

   Float64 ktd;
   if (bSI)
   {
      ktd = t / (61. - 0.58 * WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::MPa) + t);
      ATLASSERT(lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims);
   }
   else
   {
      if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims)
      {
         ktd = t / (61. - 4. * WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI) + t);
      }
      else
      {
         // ktd equation changed in LRFD 2015
         Float64 fc = WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI);
         ktd = t / (12 * (100. - 4. * fc) / (fc + 20.) + t);
      }
   }

   return ktd;
}

void lrfdCreepCoefficient2005::Update() const
{
   // need to make sure spec version is ok
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
      throw lrfdXCreepCoefficient(lrfdXCreepCoefficient::Specification,_T(__FILE__),__LINE__);

   m_khc = ComputeKhc();
   m_kvs = ComputeKvs();
   m_kf = ComputeKf();

   m_bUpdate = false;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdCreepCoefficient2005::AssertValid() const
{
   return true;
}

void lrfdCreepCoefficient2005::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for lrfdCreepCoefficient2005" << WBFL::Debug::endl;
                                                                                                                             }
#endif // _DEBUG

#if defined _UNITTEST
#include <LRFD\AutoVersion.h>
bool lrfdCreepCoefficient2005::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("lrfdCreepCoefficient2005");

   lrfdAutoVersion av;
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);


   lrfdCreepCoefficient2005 creep;
   creep.SetCuringMethod(lrfdCreepCoefficient2005::Accelerated);
   creep.SetFci(WBFL::Units::ConvertToSysUnits(8.0,WBFL::Units::Measure::KSI));
   creep.SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
   creep.SetRelHumidity(75);
   creep.SetSurfaceArea( WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Inch2) );
   creep.SetVolume( WBFL::Units::ConvertToSysUnits(2.88,WBFL::Units::Measure::Inch3) );

   Float64 ti = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
   Float64 t = WBFL::Units::ConvertToSysUnits(120, WBFL::Units::Measure::Day);
   TRY_TESTME( IsEqual( creep.GetKvs(), 1.0756 ) );
   TRY_TESTME( IsEqual( creep.GetKf(),  0.55555 ) );
   TRY_TESTME( IsEqual( creep.GetKhc(), 0.96 ) );
   TRY_TESTME( IsEqual( creep.GetKtd(t), 0.805369) );
   TRY_TESTME( IsEqual( creep.GetCreepCoefficient(t,ti), 0.877805) );

   TESTME_EPILOG("lrfdCreepCoefficient2005");
}
#endif // _UNITTEST
