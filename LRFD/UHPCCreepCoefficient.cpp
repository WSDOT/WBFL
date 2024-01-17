///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <Lrfd\UHPCCreepCoefficient.h>

using namespace WBFL::LRFD;

Float64 UHPCCreepCoefficient::GetUltimateCreep() const
{
   return 1.2;
}

Float64 UHPCCreepCoefficient::GetAdjustedInitialAge(Float64 ti) const
{
   return ti;
}

Float64 UHPCCreepCoefficient::GetKl(Float64 ti) const
{
   ti = WBFL::Units::ConvertFromSysUnits(ti, WBFL::Units::Measure::Day);
   Float64 kl = (ti < 7.0) ? 1.0 : Max(pow((ti - 6.0), -0.15), 0.5);
   return kl;
}

Float64 UHPCCreepCoefficient::ComputeKvs() const
{
   return 1.0;
}

Float64 UHPCCreepCoefficient::ComputeKhc() const
{
   return 1.12 - 0.0024*m_H;
}

Float64 UHPCCreepCoefficient::ComputeKf() const
{
   Float64 fci = WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI);
   return 18.0/(1.5*fci - 3.0);
}

Float64 UHPCCreepCoefficient::ComputeKtd(Float64 t) const
{
   t = WBFL::Units::ConvertFromSysUnits(t, WBFL::Units::Measure::Day);
   Float64 fci = WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI);
   Float64 ktd = t / (300. / (fci + 30.) + 0.8*pow(t,0.98));
   return ktd;
}
