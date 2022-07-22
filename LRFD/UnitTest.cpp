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

#include <LRFD/LrfdLib.h>
#include <LRFD/UnitTest.h>
#include <LRFD/AutoVersion.h>
#include <LRFD/ConcreteUtil.h>
#include <LRFD/ElasticShortening.h>
#include <LRFD/ApproximateLosses.h>
#include <LRFD/ApproximateLosses2005.h>
#include <LRFD/RefinedLosses.h>
#include <LRFD/RefinedLosses2005.h>
#include <LRFD/PCIUHPCLosses.h>
#include <LRFD/PsStrand.h>
#include <LRFD/Shear.h>
#include <LRFD/StrandPool.h>
#include <LRFD/VersionMgr.h>
#include <LRFD/RebarPool.h>
#include <LRFD/Utility.h>
#include <LRFD/LoadModifier.h>
#include <LRFD/LldfTypeAEKIJ.h>
#include <LRFD/LldfTypeAEK.h>
#include <LRFD/LldfTypeBC.h>
#include <LRFD/LldfTypeHIJ.h>
#include <LRFD/LldfTypeG.h>
#include <LRFD/LldfTxdotMultiWeb.h>
#include <LRFD/LldfTxdotSpreadSlab.h>
#include <LRFD/CreepCoefficient.h>
#include <LRFD/CreepCoefficient2005.h>
#include <LRFD/PCIUHPCCreepCoefficient.h>
#include <LRFD/LRFDConcrete2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdUnitTest
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool lrfdUnitTest::TestMe(WBFL::Debug::Log& log)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= lrfdAutoVersion::TestMe(log);
   tst &= lrfdConcreteUtil::TestMe(log);
   tst &= lrfdApproximateLosses::TestMe(log);
   tst &= lrfdApproximateLosses2005::TestMe(log);
   tst &= lrfdRefinedLosses::TestMe(log);
   tst &= lrfdRefinedLosses2005::TestMe(log);
   tst &= lrfdPCIUHPCLosses::TestMe(log);
   tst &= lrfdPsStrand::TestMe(log);
   tst &= lrfdShear::TestMe(log);
   tst &= lrfdStrandPool::TestMe(log);
   tst &= lrfdStrandIter::TestMe(log);
   tst &= lrfdVersionMgr::TestMe(log);
   tst &= lrfdRebarPool::TestMe(log);
   tst &= lrfdRebarIter::TestMe(log);
   tst &= lrfdUtility::TestMe(log);
   tst &= lrfdLoadModifier::TestMe(log);
   tst &= lrfdCreepCoefficient::TestMe(log);
   tst &= lrfdCreepCoefficient2005::TestMe(log);
   tst &= lrfdPCIUHPCCreepCoefficient::TestMe(log);

   tst &= lrfdLldfTypeAEKIJ::TestMe(log);
   tst &= lrfdLldfTypeAEK::TestMe(log);
   tst &= lrfdWsdotLldfTypeAEK::TestMe(log);
   tst &= lrfdLldfTypeBC::TestMe(log);
   tst &= lrfdWsdotLldfTypeBC::TestMe(log);
   tst &= lrfdLldfTypeHIJ::TestMe(log);
   tst &= lrfdLldfTypeG::TestMe(log);
   tst &= lrfdTxdotVoidedSlab::TestMe(log);
   tst &= lrfdLldfTypeF::TestMe(log);
   tst &= lrfdTxdotLldfSpreadSlab::TestMe(log);

   tst &= WBFL::LRFD::LRFDConcreteSecantModulusModel::TestMe(log);
   tst &= WBFL::LRFD::LRFDVSRatioCorrectionFactorModel::TestMe(log);
   tst &= WBFL::LRFD::LRFDShrinkageHumidityCorrectionFactorModel::TestMe(log);
   tst &= WBFL::LRFD::LRFDCreepHumidityCorrectionFactorModel::TestMe(log);
   tst &= WBFL::LRFD::LRFDConcreteStrengthCorrectionFactorModel::TestMe(log);
   tst &= WBFL::LRFD::LRFDConcreteTimeDevelopmentCorrectionFactorModel::TestMe(log);
   tst &= WBFL::LRFD::LRFDConcreteLoadingAgeCorrectionFactorModel::TestMe(log);
#endif

   return tst;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
