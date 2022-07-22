///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MatLib.h>
#include <Materials/UnitTest.h>
#include <Materials/SimpleConcrete.h>
#include <Materials/Concrete.h>
#include <Materials/ConcreteStrengthModel.h>
#include <Materials/ACI209Concrete.h>
#include <Materials/CEBFIPConcrete.h>
#include <Materials/PCIUHPCConcrete.h>
#include <Materials/FHWAUHPCConcrete.h>
#include <Materials/ConcreteSecantModulusModel.h>
#include <Materials/ConcreteShrinkageModel.h>
#include <Materials/ConcreteShrinkageTemplateModel.h>
#include <Materials/ConcreteCreepModel.h>
#include <Materials/ConcreteCreepTemplateModel.h>
#include <Materials/PsStrand.h>
#include <Materials/Rebar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

bool UnitTest::TestMe(WBFL::Debug::Log& log)
{
   bool tst = true;

#if defined _UNITTEST
   tst &= ConstantConcreteStrengthModel::TestMe(log);
   tst &= SteppedConcreteStrengthModel::TestMe(log);

   tst &= ConstantConcreteSecantModulusModel::TestMe(log);
   tst &= SteppedConcreteSecantModulusModel::TestMe(log);
   tst &= PCIUHPCConcreteSecantModulusModel::TestMe(log);
   tst &= FHWAUHPCConcreteSecantModulusModel::TestMe(log);

   tst &= VSRatioCorrectionFactorModel::TestMe(log);
   tst &= HumidityCorrectionFactorModel::TestMe(log);
   tst &= ConcreteStrengthCorrectionFactorModel::TestMe(log);
   tst &= ConcreteTimeDevelopmentCorrectionFactorModel::TestMe(log);
   tst &= ConcretePhysicalTestingCorrectionFactorModel::TestMe(log);

   tst &= FHWAUHPCVSRatioCorrectionFactorModel::TestMe(log);
   tst &= FHWAUHPCShrinkageHumidityCorrectionFactorModel::TestMe(log);
   tst &= FHWAUHPCCreepHumidityCorrectionFactorModel::TestMe(log);
   tst &= FHWAUHPCConcreteStrengthCorrectionFactorModel::TestMe(log);
   tst &= FHWAUHPCConcreteTimeDevelopmentCorrectionFactorModel::TestMe(log);
   tst &= FHWAUHPCConcreteLoadingAgeCorrectionFactorModel::TestMe(log);

   tst &= PCIUHPCVSRatioCorrectionFactorModel::TestMe(log);
   tst &= PCIUHPCShrinkageHumidityCorrectionFactorModel::TestMe(log);
   tst &= PCIUHPCCreepHumidityCorrectionFactorModel::TestMe(log);
   tst &= PCIUHPCConcreteStrengthCorrectionFactorModel::TestMe(log);
   tst &= PCIUHPCConcreteTimeDevelopmentCorrectionFactorModel::TestMe(log);

   tst &= ConcreteShrinkageModel::TestMe(log);
   tst &= ConcreteShrinkageTemplateModel::TestMe(log);

   tst &= ConcreteCreepModel::TestMe(log);
   tst &= ConcreteCreepTemplateModel::TestMe(log);

   tst &= ACI209ConcreteStrengthModel::TestMe(log);
   tst &= ACI209ConcreteSecantModulusModel::TestMe(log);
   tst &= ACI209CreepVSRatioCorrectionFactorModel::TestMe(log);
   tst &= ACI209ShrinkageVSRatioCorrectionFactorModel::TestMe(log);
   tst &= ACI209ShrinkageHumidityCorrectionFactorModel::TestMe(log);
   tst &= ACI209CreepHumidityCorrectionFactorModel::TestMe(log);
   tst &= ACI209ShrinkageTimeDevelopmentCorrectionFactorModel::TestMe(log);
   tst &= ACI209CuringCorrectionFactorModel::TestMe(log);
   tst &= ACI209ConcreteShrinkageModel::TestMe(log);

   tst &= CEBFIPConcreteStrengthModel::TestMe(log);
   tst &= CEBFIPConcreteSecantModulusModel::TestMe(log);
   tst &= CEBFIPConcreteShrinkageModel::TestMe(log);

   tst &= Concrete::TestMe(log);

   tst &= SimpleConcrete::TestMe(log);
#pragma Reminder("WORKING HERE - need to add unit tests for time-dependent concrete models")
   tst &= PsStrand::TestMe(log);
   tst &= Rebar::TestMe(log);

#endif

   return tst;
}
