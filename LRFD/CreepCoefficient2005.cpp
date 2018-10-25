///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include <Units\SysUnits.h>
#include <MathEx.h>

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

lrfdCreepCoefficient2005::lrfdCreepCoefficient2005(const lrfdCreepCoefficient2005& rOther)
{
   MakeCopy(rOther);
}

lrfdCreepCoefficient2005::~lrfdCreepCoefficient2005()
{
}

//======================== OPERATORS  =======================================
lrfdCreepCoefficient2005& lrfdCreepCoefficient2005::operator= (const lrfdCreepCoefficient2005& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdCreepCoefficient2005::GetCreepCoefficient() const
{
   if ( m_bUpdate )
      Update();

   return m_Ct;
}

//======================== ACCESS     =======================================
void lrfdCreepCoefficient2005::SetRelHumidity(Float64 H)
{
   m_H = H;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient2005::GetRelHumidity() const
{
   return m_H;
}

void lrfdCreepCoefficient2005::SetFc(Float64 fc)
{
   m_Fc = fc;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient2005::GetFc() const
{
   return m_Fc;
}

void lrfdCreepCoefficient2005::SetVolume(Float64 V)
{
   m_V = V;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient2005::GetVolume() const
{
   return m_V;
}

void lrfdCreepCoefficient2005::SetSurfaceArea(Float64 S)
{
   m_S = S;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient2005::GetSurfaceArea() const
{
   return m_S;
}

void lrfdCreepCoefficient2005::SetMaturity(Float64 t)
{
   m_t = t;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient2005::GetMaturity() const
{
   return m_t;
}

void lrfdCreepCoefficient2005::SetInitialAge(Float64 ti)
{
   m_ti = ti;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient2005::GetInitialAge() const
{
   return m_ti;
}

Float64 lrfdCreepCoefficient2005::GetAdjustedInitialAge() const
{
   Float64 tiAdjusted = m_ti;
   if ( m_CuringMethod == Normal )
   {
      // NCHRP 496...
      // ti = age of concrete, in days, when load is initially applied
      // for accelerated curing, or the age minus 6 days for moist (normal) curing
      tiAdjusted -= (m_CuringMethodTimeAdjustmentFactor-1);
      if ( tiAdjusted < 0 )
      {
         tiAdjusted = 1;
      }
   }

   return tiAdjusted;
}

void lrfdCreepCoefficient2005::SetCuringMethod(lrfdCreepCoefficient2005::CuringMethod method)
{
   m_CuringMethod = method;
   m_bUpdate = true;
}

lrfdCreepCoefficient2005::CuringMethod lrfdCreepCoefficient2005::GetCuringMethod() const
{
   return m_CuringMethod;
}

void lrfdCreepCoefficient2005::SetCuringMethodTimeAdjustmentFactor(Float64 f)
{
   m_CuringMethodTimeAdjustmentFactor = f;
}

Float64 lrfdCreepCoefficient2005::GetCuringMethodTimeAdjustmentFactor() const
{
   return m_CuringMethodTimeAdjustmentFactor;
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

Float64 lrfdCreepCoefficient2005::GetKf() const
{
   if ( m_bUpdate )
      Update();

   return m_kf;
}

Float64 lrfdCreepCoefficient2005::GetKtd() const
{
   if ( m_bUpdate )
      Update();

   return m_ktd;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdCreepCoefficient2005::MakeCopy(const lrfdCreepCoefficient2005& rOther)
{
   m_H            = rOther.m_H;
   m_Fc           = rOther.m_Fc;
   m_V            = rOther.m_V;
   m_S            = rOther.m_S;
   m_t            = rOther.m_t;
   m_ti           = rOther.m_ti;
   m_tiAdjusted   = rOther.m_tiAdjusted;
   m_CuringMethod = rOther.m_CuringMethod;
   m_K1           = rOther.m_K1;
   m_K2           = rOther.m_K2;
   m_Ct           = rOther.m_Ct;
   m_kvs          = rOther.m_kvs;
   m_khc          = rOther.m_khc;
   m_kf           = rOther.m_kf;
   m_ktd          = rOther.m_ktd;
   m_CuringMethodTimeAdjustmentFactor = rOther.m_CuringMethodTimeAdjustmentFactor;
   m_bUpdate      = rOther.m_bUpdate;
}

void lrfdCreepCoefficient2005::MakeAssignment(const lrfdCreepCoefficient2005& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdCreepCoefficient2005::Update() const
{
   // need to make sure spec version is ok
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
      throw lrfdXCreepCoefficient(lrfdXCreepCoefficient::Specification,_T(__FILE__),__LINE__);

   bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
   
   // Check volume to surface ratio
   // Sometimes, V and S are zero... like in the case of a noncomposite girder and the
   // creep due to slab shrinkage is being computer... don't divide by zero
   Float64 VS = (m_S == 0 ? 0 : m_V/m_S);

   m_khc = 1.56 - 0.008*m_H;

   Float64 t, ti;
   ti = ::ConvertFromSysUnits(GetAdjustedInitialAge(),unitMeasure::Day);
   t  = ::ConvertFromSysUnits(m_t,unitMeasure::Day);

   // kvs_limit is 1.0 in 2005, changed to 0.0 in 2006, changed back to 1.0 in 2007
   Float64 kvs_limit = (lrfdVersionMgr::GetVersion() == lrfdVersionMgr::ThirdEditionWith2006Interims ? 0.0 : 1.0);

   if ( bSI )
   {
      m_kvs = Max(kvs_limit, 1.45-0.0051*::ConvertFromSysUnits(VS,unitMeasure::Millimeter));
      m_kf = 35.0 / ( 7.0 + ::ConvertFromSysUnits(m_Fc,unitMeasure::MPa) );
      m_ktd = t / ( 61. - 0.58*::ConvertFromSysUnits(m_Fc,unitMeasure::MPa) + t);
      ATLASSERT(lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims);
   }
   else
   {
      m_kvs = Max(kvs_limit, 1.45-0.13*::ConvertFromSysUnits(VS,unitMeasure::Inch));
      m_kf =  5.0 / ( 1.0 + ::ConvertFromSysUnits(m_Fc,unitMeasure::KSI) );

      if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEditionWith2015Interims )
      {
         m_ktd = t / ( 61. - 4.*::ConvertFromSysUnits(m_Fc,unitMeasure::KSI) + t);
      }
      else
      {
         // ktd equation changed in LRFD 2015
         Float64 fc = ::ConvertFromSysUnits(m_Fc,unitMeasure::KSI);
         m_ktd = t / (12*(100. - 4.*fc)/(fc + 20.) + t);
      }
   }

   m_Ct = 1.9*m_K1*m_K2*m_kvs*m_khc*m_kf*m_ktd*pow(ti,-0.118); // see NCHRP Report 496, Eqn 62

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

void lrfdCreepCoefficient2005::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdCreepCoefficient2005" << endl;
                                                                                                                             }
#endif // _DEBUG

#if defined _UNITTEST
#include <LRFD\AutoVersion.h>
bool lrfdCreepCoefficient2005::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdCreepCoefficient2005");

   lrfdAutoVersion av;
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);


   lrfdCreepCoefficient2005 creep;
   creep.SetCuringMethod(lrfdCreepCoefficient2005::Accelerated);
   creep.SetFc(::ConvertToSysUnits(8.0,unitMeasure::KSI));
   creep.SetInitialAge(::ConvertToSysUnits(1.0,unitMeasure::Day));
   creep.SetCuringMethodTimeAdjustmentFactor(7);
   creep.SetMaturity(::ConvertToSysUnits(120,unitMeasure::Day));
   creep.SetRelHumidity(75);
   creep.SetSurfaceArea( ::ConvertToSysUnits(1.0,unitMeasure::Inch2) );
   creep.SetVolume( ::ConvertToSysUnits(2.88,unitMeasure::Inch3) );

   TRY_TESTME( IsEqual( creep.GetKvs(), 1.0756 ) );
   TRY_TESTME( IsEqual( creep.GetKf(),  0.55555 ) );
   TRY_TESTME( IsEqual( creep.GetKhc(), 0.96 ) );
   TRY_TESTME( IsEqual( creep.GetKtd(), 0.805369) );
   TRY_TESTME( IsEqual( creep.GetCreepCoefficient(), 0.877805) );

   TESTME_EPILOG("lrfdCreepCoefficient2005");
}
#endif // _UNITTEST
