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
#include <Lrfd\CreepCoefficient.h>
#include <Lrfd\XCreepCoefficient.h>
#include <Lrfd\VersionMgr.h>

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
   m_CuringMethodTimeAdjustmentFactor = ::ConvertToSysUnits(7.0,unitMeasure::Day);
   m_bUpdate = true;
}

lrfdCreepCoefficient::~lrfdCreepCoefficient()
{
}

Float64 lrfdCreepCoefficient::ComputeKtd(Float64 t) const
{
    bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

    // Check volume to surface ratio
    Float64 VS = m_V / m_S;
    Float64 VSMax;
    if (bSI)
    {
        VS = ::ConvertFromSysUnits(VS, unitMeasure::Millimeter);
        VSMax = 150.0; // millimeters
    }
    else
    {
        VS = ::ConvertFromSysUnits(VS, unitMeasure::Inch);
        VSMax = 6.0; // inches
    }

    // Compute Kc
    Float64 a, b, c;
    Float64 x1, x2;
    Float64 e = pow(10., 1. / log(10.));
    if (bSI)
    {
        x1 = 0.0142;
        x2 = -0.0213;
    }
    else
    {
        x1 = 0.36;
        x2 = -0.54;
    }

    t = ::ConvertFromSysUnits(t, unitMeasure::Day);

    a = t / (26.0 * pow(e, x1 * VS) + t);
    b = t / (45.0 + t);
    c = 1.80 + 1.77 * pow(e, x2 * VS);

    Float64 ktd = (a / b) * (c / 2.587);
    return ktd; // this is really Kc
}

Float64 lrfdCreepCoefficient::GetCreepCoefficient(Float64 t, Float64 ti) const
{
    if (m_bUpdate)
        Update();

    Float64 tiAdjusted = GetAdjustedInitialAge(ti);
    tiAdjusted = ::ConvertFromSysUnits(tiAdjusted, unitMeasure::Day);

    Float64 kc = ComputeKtd(t);

    t = ::ConvertFromSysUnits(t, unitMeasure::Day); // do after calling ComputeKtd because it expects t in system units

    Float64 Ct;
    if (t < tiAdjusted)
    {
        Ct = 0;
    }
    else
    {
        Ct = 3.5 * kc * m_kf * (1.58 - m_H / 120.) * pow(tiAdjusted, -0.118) * (pow(t - tiAdjusted, 0.6) / (10.0 + pow(t - tiAdjusted, 0.6)));
    }

    return Ct;
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

void lrfdCreepCoefficient::SetFci(Float64 fci)
{
   m_Fci = fci;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetFci() const
{
   return m_Fci;
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

Float64 lrfdCreepCoefficient::GetAdjustedInitialAge(Float64 ti) const
{
    Float64 tiAdjusted = ti;
    if (m_CuringMethod == Accelerated && ti < ::ConvertToSysUnits(7.0,unitMeasure::Day))
    {
        // NCHRP 496...
        // ti = age of concrete, in days, when load is initially applied
        // for accelerated curing, or the age minus 6 days for moist (normal) curing
        Float64 one_day = ::ConvertToSysUnits(1.0, unitMeasure::Day);
        tiAdjusted += m_CuringMethodTimeAdjustmentFactor - one_day; // days
    }

    return tiAdjusted;
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

void lrfdCreepCoefficient::SetCuringMethodTimeAdjustmentFactor(Float64 f)
{
   m_CuringMethodTimeAdjustmentFactor = f;
   m_bUpdate = true;
}

Float64 lrfdCreepCoefficient::GetCuringMethodTimeAdjustmentFactor() const
{
   return m_CuringMethodTimeAdjustmentFactor;
}

Float64 lrfdCreepCoefficient::GetKf() const
{
   if ( m_bUpdate )
   {
      Update();
   }

   return m_kf;
}

Float64 lrfdCreepCoefficient::GetKtd(Float64 t) const
{
    // this is really Kc
    return ComputeKtd(t);
}

Float64 lrfdCreepCoefficient::ComputeKf() const
{
    bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
    Float64 kf;
    if (bSI)
    {
        kf = 62.0 / (42.0 + ::ConvertFromSysUnits(m_Fci, unitMeasure::MPa));
    }
    else
    {
        kf = 1.0 / (0.67 + (::ConvertFromSysUnits(m_Fci, unitMeasure::KSI) / 9.0));
    }

    return kf;
}

void lrfdCreepCoefficient::Update() const
{
   // need to make sure spec version is ok
   if ( lrfdVersionMgr::ThirdEditionWith2005Interims <= lrfdVersionMgr::GetVersion() )
   {
      throw lrfdXCreepCoefficient(lrfdXCreepCoefficient::Specification,_T(__FILE__),__LINE__);
   }

   m_kf = ComputeKf();

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
