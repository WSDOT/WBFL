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
#include <Lrfd\PCIUHPCCreepCoefficient.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

lrfdPCIUHPCCreepCoefficient::lrfdPCIUHPCCreepCoefficient() :
   m_bPCTT(false)
{
}

lrfdPCIUHPCCreepCoefficient::~lrfdPCIUHPCCreepCoefficient()
{
}

Float64 lrfdPCIUHPCCreepCoefficient::GetUltimateCreep() const
{
   return (m_bPCTT ? 0.3 : 1.2);
}

Float64 lrfdPCIUHPCCreepCoefficient::ComputeKvs() const
{
   return 1.0;
}

Float64 lrfdPCIUHPCCreepCoefficient::ComputeKhc() const
{
   return 1.0;
}

Float64 lrfdPCIUHPCCreepCoefficient::ComputeKf() const
{
   return 1.0;
}

Float64 lrfdPCIUHPCCreepCoefficient::ComputeKtd(Float64 t) const
{
   t = WBFL::Units::ConvertFromSysUnits(t, WBFL::Units::Measure::Day);
   Float64 fc = WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI);
   Float64 ktd = t / (12 * (100. - 4. * fc) / (fc + 20.) + t);
   return ktd;
}

#if defined _UNITTEST
#include <LRFD\AutoVersion.h>
bool lrfdPCIUHPCCreepCoefficient::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("lrfdPCIUHPCCreepCoefficient");

   lrfdAutoVersion av;
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);


   lrfdPCIUHPCCreepCoefficient creep;
   creep.PostCureThermalTreatment(false);
   creep.SetCuringMethod(lrfdCreepCoefficient2005::Accelerated);
   creep.SetFci(WBFL::Units::ConvertToSysUnits(8.0,WBFL::Units::Measure::KSI));
   creep.SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
   creep.SetRelHumidity(75);
   creep.SetSurfaceArea( WBFL::Units::ConvertToSysUnits(1.0,WBFL::Units::Measure::Inch2) );
   creep.SetVolume( WBFL::Units::ConvertToSysUnits(2.88,WBFL::Units::Measure::Inch3) );

   Float64 ti = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
   Float64 t = WBFL::Units::ConvertToSysUnits(120, WBFL::Units::Measure::Day);

   TRY_TESTME( IsEqual( creep.GetKvs(), 1.0 ) );
   TRY_TESTME( IsEqual( creep.GetKf(),  1.0 ) );
   TRY_TESTME( IsEqual( creep.GetKhc(), 1.0 ) );
   TRY_TESTME( IsEqual( creep.GetKtd(t), 0.80460) );
   TRY_TESTME( IsEqual( creep.GetCreepCoefficient(t,ti), 0.96552) );

   creep.PostCureThermalTreatment(true);
   TRY_TESTME(IsEqual(creep.GetCreepCoefficient(t,ti), 0.24138));

   TESTME_EPILOG("lrfdPCIUHPCCreepCoefficient");
}
#endif // _UNITTEST
