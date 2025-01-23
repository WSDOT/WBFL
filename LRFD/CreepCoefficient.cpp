///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Lrfd/BDSManager.h>

using namespace WBFL::LRFD;

Float64 CreepCoefficient::ComputeKtd(Float64 t) const
{
    bool bSI = BDSManager::GetUnits() == BDSManager::Units::SI;

    // Check volume to surface ratio
    Float64 VS = m_V / m_S;
    Float64 VSMax;
    if (bSI)
    {
        VS = WBFL::Units::ConvertFromSysUnits(VS, WBFL::Units::Measure::Millimeter);
        VSMax = 150.0; // millimeters
    }
    else
    {
        VS = WBFL::Units::ConvertFromSysUnits(VS, WBFL::Units::Measure::Inch);
        VSMax = 6.0; // inches
    }

    VS = Min(VS, VSMax);

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

    t = WBFL::Units::ConvertFromSysUnits(t, WBFL::Units::Measure::Day);

    a = t / (26.0 * pow(e, x1 * VS) + t);
    b = t / (45.0 + t);
    c = 1.80 + 1.77 * pow(e, x2 * VS);

    Float64 ktd = (a / b) * (c / 2.587);
    return ktd; // this is really Kc
}

Float64 CreepCoefficient::GetCreepCoefficient(Float64 t, Float64 ti) const
{
    if (m_bUpdate)
        Update();

    Float64 tiAdjusted = GetAdjustedInitialAge(ti);
    tiAdjusted = WBFL::Units::ConvertFromSysUnits(tiAdjusted, WBFL::Units::Measure::Day);

    Float64 kc = ComputeKtd(t);

    t = WBFL::Units::ConvertFromSysUnits(t, WBFL::Units::Measure::Day); // do after calling ComputeKtd because it expects t in system units

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

void CreepCoefficient::SetRelHumidity(Float64 H)
{
   m_H = H;
   m_bUpdate = true;
}

Float64 CreepCoefficient::GetRelHumidity() const
{
   return m_H;
}

void CreepCoefficient::SetFci(Float64 fci)
{
   m_Fci = fci;
   m_bUpdate = true;
}

Float64 CreepCoefficient::GetFci() const
{
   return m_Fci;
}

void CreepCoefficient::SetVolume(Float64 V)
{
   m_V = V;
   m_bUpdate = true;
}

Float64 CreepCoefficient::GetVolume() const
{
   return m_V;
}

void CreepCoefficient::SetSurfaceArea(Float64 S)
{
   m_S = S;
   m_bUpdate = true;
}

Float64 CreepCoefficient::GetSurfaceArea() const
{
   return m_S;
}

Float64 CreepCoefficient::GetAdjustedInitialAge(Float64 ti) const
{
    Float64 tiAdjusted = ti;
    if (m_CuringMethod == CuringMethod::Accelerated && ti < WBFL::Units::ConvertToSysUnits(7.0,WBFL::Units::Measure::Day))
    {
        // NCHRP 496...
        // ti = age of concrete, in days, when load is initially applied
        // for accelerated curing, or the age minus 6 days for moist (normal) curing
        Float64 one_day = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
        tiAdjusted += m_CuringMethodTimeAdjustmentFactor - one_day; // days
    }

    return tiAdjusted;
}

void CreepCoefficient::SetCuringMethod(CreepCoefficient::CuringMethod method)
{
   m_CuringMethod = method;
   m_bUpdate = true;
}

CreepCoefficient::CuringMethod CreepCoefficient::GetCuringMethod() const
{
   return m_CuringMethod;
}

void CreepCoefficient::SetCuringMethodTimeAdjustmentFactor(Float64 f)
{
   m_CuringMethodTimeAdjustmentFactor = f;
   m_bUpdate = true;
}

Float64 CreepCoefficient::GetCuringMethodTimeAdjustmentFactor() const
{
   return m_CuringMethodTimeAdjustmentFactor;
}

Float64 CreepCoefficient::GetKf() const
{
   if ( m_bUpdate )
   {
      Update();
   }

   return m_kf;
}

Float64 CreepCoefficient::GetKtd(Float64 t) const
{
    // this is really Kc
    return ComputeKtd(t);
}

Float64 CreepCoefficient::ComputeKf() const
{
    bool bSI = BDSManager::GetUnits() == BDSManager::Units::SI;
    Float64 kf;
    if (bSI)
    {
        kf = 62.0 / (42.0 + WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::MPa));
    }
    else
    {
        kf = 1.0 / (0.67 + (WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI) / 9.0));
    }

    return kf;
}

void CreepCoefficient::Update() const
{
   // need to make sure spec version is ok
   if ( BDSManager::Edition::ThirdEditionWith2005Interims <= BDSManager::GetEdition() )
   {
      WBFL_LRFD_THROW(XCreepCoefficient,Specification);
   }

   m_kf = ComputeKf();

   m_bUpdate = false;
}
