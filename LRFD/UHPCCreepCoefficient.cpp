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
#include <Lrfd\UHPCCreepCoefficient.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

lrfdUHPCCreepCoefficient::lrfdUHPCCreepCoefficient()
{
}

lrfdUHPCCreepCoefficient::~lrfdUHPCCreepCoefficient()
{
}

Float64 lrfdUHPCCreepCoefficient::GetUltimateCreep() const
{
   return 1.2;
}

Float64 lrfdUHPCCreepCoefficient::GetAdjustedInitialAge(Float64 ti) const
{
   return ti;
}

Float64 lrfdUHPCCreepCoefficient::GetKl(Float64 ti) const
{
   ti = WBFL::Units::ConvertFromSysUnits(ti, WBFL::Units::Measure::Day);
   Float64 kl = (ti < 7.0) ? 1.0 : Max(pow((ti - 6.0), -0.15), 0.5);
   return kl;
}

Float64 lrfdUHPCCreepCoefficient::ComputeKvs() const
{
   return 1.0;
}

Float64 lrfdUHPCCreepCoefficient::ComputeKhc() const
{
   return 1.12 - 0.0024*m_H;
}

Float64 lrfdUHPCCreepCoefficient::ComputeKf() const
{
   Float64 fci = WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI);
   return 18.0/(1.5*fci - 3.0);
}

Float64 lrfdUHPCCreepCoefficient::ComputeKtd(Float64 t) const
{
   t = WBFL::Units::ConvertFromSysUnits(t, WBFL::Units::Measure::Day);
   Float64 fci = WBFL::Units::ConvertFromSysUnits(m_Fci, WBFL::Units::Measure::KSI);
   Float64 ktd = t / (300. / (fci + 30.) + 0.8*pow(t,0.98));
   return ktd;
}

#if defined _UNITTEST
#include <LRFD\AutoVersion.h>
bool lrfdUHPCCreepCoefficient::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("lrfdUHPCCreepCoefficient");

   lrfdAutoVersion av;
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::ThirdEditionWith2005Interims);

   // based on UHPC design example
   lrfdUHPCCreepCoefficient creep;
   creep.SetFci(WBFL::Units::ConvertToSysUnits(14.0,WBFL::Units::Measure::KSI));
   creep.SetRelHumidity(73);
   creep.SetK1(0.62);

   Float64 ti = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
   Float64 td = WBFL::Units::ConvertToSysUnits(90, WBFL::Units::Measure::Day);
   Float64 tf = WBFL::Units::ConvertToSysUnits(20000, WBFL::Units::Measure::Day);

   TRY_TESTME( IsEqual( creep.GetKvs(), 1.0 ) );
   TRY_TESTME( IsEqual( creep.GetKf(),  1.0 ) );
   TRY_TESTME( IsEqual( creep.GetKhc(), 0.94480 ) );
   TRY_TESTME( IsEqual( creep.GetKtd(td-ti), 1.237746) );
   TRY_TESTME( IsEqual( creep.GetCreepCoefficient(td-ti,ti), 0.870051) );

   TRY_TESTME(IsEqual(creep.GetKtd(tf-ti), 1.52302));
   TRY_TESTME(IsEqual(creep.GetCreepCoefficient(tf-ti, ti), 1.070576));

   TESTME_EPILOG("lrfdUHPCCreepCoefficient");
}
#endif // _UNITTEST
