///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MatLib.h>
#include <Materials/UnitTest.h>
#include <Materials/SimpleConcrete.h>
#include <Materials/PsStrand.h>
#include <Materials/Rebar.h>
#include <Materials/StressStrainModel.h>
#include <Materials/ConfinedConcreteModel.h>
#include <Materials/UnconfinedConcreteModel.h>
#include <Materials/UHPCModel.h>
#include <Materials/PCIUHPCModel.h>
#include <Materials/RambergOsgoodModel.h>
#include <Materials/PSPowerFormulaModel.h>
#include <Materials/LRFDPrestressModel.h>
#include <Materials/RebarModel.h>

using namespace WBFL::Materials;

bool UnitTest::TestMe(WBFL::Debug::Log& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= SimpleConcrete::TestMe(rlog);
#pragma Reminder("WORKING HERE - need to add unit tests for time-dependent concrete models")
   tst &= PsStrand::TestMe(rlog);
   tst &= Rebar::TestMe(rlog);

   tst &= StressStrainModel::TestMe(rlog);
   tst &= ConfinedConcreteModel::TestMe(rlog);
   tst &= UnconfinedConcreteModel::TestMe(rlog);
   tst &= UHPCModel::TestMe(rlog);
   tst &= PCIUHPCModel::TestMe(rlog);
   tst &= RambergOsgoodModel::TestMe(rlog);
   tst &= PSPowerFormulaModel::TestMe(rlog);
   tst &= LRFDPrestressModel::TestMe(rlog);
   tst &= RebarModel::TestMe(rlog);

#endif

   return tst;
}
