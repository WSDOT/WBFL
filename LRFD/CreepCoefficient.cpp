///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2012  Washington State Department of Transportation
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
#include <Lrfd\CreepCoefficient.h>
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
   lrfdCreepCoefficient
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdCreepCoefficient::lrfdCreepCoefficient()
{
   m_bUpdate = true;
}

lrfdCreepCoefficient::lrfdCreepCoefficient(const lrfdCreepCoefficient& rOther)
{
   MakeCopy(rOther);
}

lrfdCreepCoefficient::~lrfdCreepCoefficient()
{
}

//======================== OPERATORS  =======================================
lrfdCreepCoefficient& lrfdCreepCoefficient::operator= (const lrfdCreepCoefficient& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdCreepCoefficient::GetCreepCoefficient() const
{
   if ( m_bUpdate )
      Update();

   return m_Ct;
}

//======================== ACCESS     =======================================
void lrfdCreepCoefficient::SetRelHumidity(Float64 H)
{
   m_H = H;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetRelHumidity() const
{
   return m_H;
}

void lrfdCreepCoefficient::SetFc(Float64 fc)
{
   m_Fc = fc;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetFc() const
{
   return m_Fc;
}

void lrfdCreepCoefficient::SetVolume(Float64 V)
{
   m_V = V;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetVolume() const
{
   return m_V;
}

void lrfdCreepCoefficient::SetSurfaceArea(Float64 S)
{
   m_S = S;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetSurfaceArea() const
{
   return m_S;
}

void lrfdCreepCoefficient::SetMaturity(Float64 t)
{
   m_t = t;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetMaturity() const
{
   return m_t;
}

void lrfdCreepCoefficient::SetInitialAge(Float64 ti)
{
   m_ti = ti;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetInitialAge() const
{
   return m_ti;
}

Float64 lrfdCreepCoefficient::GetAdjustedInitialAge() const
{
   if ( m_bUpdate )
      Update();

   return m_tiAdjusted;
}

void lrfdCreepCoefficient::SetCuringMethod(lrfdCreepCoefficient::CuringMethod method)
{
   m_CuringMethod = method;
   m_bUpdate = true;
}

lrfdCreepCoefficient::CuringMethod lrfdCreepCoefficient::GetCuringMethod() const
{
   return m_CuringMethod;
}

Float64 lrfdCreepCoefficient::GetKc() const
{
   if ( m_bUpdate )
      Update();

   return m_kc;
}

Float64 lrfdCreepCoefficient::GetKf() const
{
   if ( m_bUpdate )
      Update();

   return m_kf;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdCreepCoefficient::MakeCopy(const lrfdCreepCoefficient& rOther)
{
   m_H            = rOther.m_H;
   m_Fc           = rOther.m_Fc;
   m_V            = rOther.m_V;
   m_S            = rOther.m_S;
   m_t            = rOther.m_t;
   m_ti           = rOther.m_ti;
   m_tiAdjusted   = rOther.m_tiAdjusted;
   m_CuringMethod = rOther.m_CuringMethod;
   m_Ct           = rOther.m_Ct;
   m_kc           = rOther.m_kc;
   m_kf           = rOther.m_kf;
   m_bUpdate      = rOther.m_bUpdate;
}

void lrfdCreepCoefficient::MakeAssignment(const lrfdCreepCoefficient& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdCreepCoefficient::Update() const
{
   // need to make sure spec version is ok
   if ( lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
      throw lrfdXCreepCoefficient(lrfdXCreepCoefficient::Specification,_T(__FILE__),__LINE__);

   bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
   
   // Check volume to surface ratio
   Float64 VS = m_V/m_S;
   Float64 VSMax;
   if ( bSI )
   {
      VS = ::ConvertFromSysUnits( VS, unitMeasure::Millimeter );
      VSMax = 150.0; // millimeters
   }
   else
   {
      VS = ::ConvertFromSysUnits( VS, unitMeasure::Inch );
      VSMax = 6.0; // inches
   }

//   if ( VS > VSMax )
//      throw lrfdXCreepCoefficient(lrfdXCreepCoefficient::VSRatio,_T(__FILE__),__LINE__);

   // Compute Kf
   if ( bSI )
      m_kf = 62.0 / ( 42.0 + ::ConvertFromSysUnits(m_Fc,unitMeasure::MPa) );
   else
      m_kf = 1.0 / ( 0.67 + (::ConvertFromSysUnits(m_Fc,unitMeasure::KSI)/9.0) );

   // Compute Kc
   Float64 a,b,c;
   Float64 x1, x2;
   Float64 e = pow(10.,1./log(10.));
   if ( bSI )
   {
      x1 = 0.0142;
      x2 = -0.0213;
   }
   else
   {
      x1 = 0.36;
      x2 = -0.54;
   }

   Float64 ti;
   m_tiAdjusted = m_ti;
   ti = ::ConvertFromSysUnits(m_ti,unitMeasure::Day);
   if ( m_CuringMethod == Accelerated )
   {
      ti *= 7; // days
      m_tiAdjusted = ::ConvertToSysUnits(ti,unitMeasure::Day);
   }

   Float64 t = ::ConvertFromSysUnits( m_t, unitMeasure::Day );

   a = t/(26.0*pow(e,x1*VS)+t);
   b = t/(45.0 + t);
   c = 1.80 + 1.77*pow(e,x2*VS);

   m_kc = (a/b)*(c/2.587);

   m_Ct = 3.5*m_kc*m_kf*(1.58 - m_H/120.)*pow(ti,-0.118) * (  pow(t - ti,0.6)/(10.0 + pow(t - ti,0.6) ) );

   m_bUpdate = false;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdCreepCoefficient::AssertValid() const
{
   return true;
}

void lrfdCreepCoefficient::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdCreepCoefficient" << endl;
                                                                                                                             }
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdCreepCoefficient::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdCreepCoefficient");

   TESTME_EPILOG("lrfdCreepCoefficient");
}
#endif // _UNITTEST
