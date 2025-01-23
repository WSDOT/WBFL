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
#include <Lrfd\PCIUHPCCreepCoefficient.h>

using namespace WBFL::LRFD;

Float64 PCIUHPCCreepCoefficient::GetUltimateCreep() const
{
   return (m_bPCTT ? 0.3 : 1.2);
}

Float64 PCIUHPCCreepCoefficient::ComputeKvs() const
{
   return 1.0;
}

Float64 PCIUHPCCreepCoefficient::ComputeKhc() const
{
   return 1.0;
}

Float64 PCIUHPCCreepCoefficient::ComputeKf() const
{
   return 1.0;
}

Float64 PCIUHPCCreepCoefficient::ComputeKtd(Float64 t) const
{
   t = WBFL::Units::ConvertFromSysUnits(t, WBFL::Units::Measure::Day);
   Float64 fc = WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI);
   Float64 ktd = t / (12 * (100. - 4. * fc) / (fc + 20.) + t);
   return ktd;
}
