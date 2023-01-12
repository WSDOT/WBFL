///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <LRFD\LrfdLib.h>
#include <LRFD\UnitTest.h>
#include <LRFD\AutoVersion.h>
#include <LRFD\ConcreteUtil.h>
#include <LRFD\ElasticShortening.h>
#include <LRFD\ApproximateLosses.h>
#include <LRFD\ApproximateLosses2005.h>
#include <LRFD\RefinedLosses.h>
#include <LRFD\RefinedLosses2005.h>
#include <LRFD\PCIUHPCLosses.h>
#include <LRFD\PsStrand.h>
#include <LRFD\Shear.h>
#include <LRFD\StrandPool.h>
#include <LRFD\VersionMgr.h>
#include <LRFD\RebarPool.h>
#include <LRFD\Utility.h>
#include <LRFD\LoadModifier.h>
#include <LRFD\LimitStateCalculator.h>
#include <LRFD\LldfTypeAEKIJ.h>
#include <LRFD\LldfTypeAEK.h>
#include <LRFD\LldfTypeBC.h>
#include <LRFD\LldfTypeHIJ.h>
#include <LRFD\LldfTypeG.h>
#include <LRFD\LldfTxdotMultiWeb.h>
#include <LRFD\LldfTxdotSpreadSlab.h>
#include <LRFD\CreepCoefficient.h>
#include <LRFD\CreepCoefficient2005.h>
#include <LRFD\PCIUHPCCreepCoefficient.h>

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

bool lrfdUnitTest::TestMe(dbgLog& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= lrfdAutoVersion::TestMe(rlog);
   tst &= lrfdConcreteUtil::TestMe(rlog);
   tst &= lrfdApproximateLosses::TestMe(rlog);
   tst &= lrfdApproximateLosses2005::TestMe(rlog);
   tst &= lrfdRefinedLosses::TestMe(rlog);
   tst &= lrfdRefinedLosses2005::TestMe(rlog);
   tst &= lrfdPCIUHPCLosses::TestMe(rlog);
   tst &= lrfdPsStrand::TestMe(rlog);
   tst &= lrfdShear::TestMe(rlog);
   tst &= lrfdStrandPool::TestMe(rlog);
   tst &= lrfdStrandIter::TestMe(rlog);
   tst &= lrfdVersionMgr::TestMe(rlog);
   tst &= lrfdRebarPool::TestMe(rlog);
   tst &= lrfdRebarIter::TestMe(rlog);
   tst &= lrfdUtility::TestMe(rlog);
   tst &= lrfdLoadModifier::TestMe(rlog);
   tst &= lrfdLimitStateCalculator::TestMe(rlog);
   tst &= lrfdCreepCoefficient::TestMe(rlog);
   tst &= lrfdCreepCoefficient2005::TestMe(rlog);
   tst &= lrfdPCIUHPCCreepCoefficient::TestMe(rlog);

   tst &= lrfdLldfTypeAEKIJ::TestMe(rlog);
   tst &= lrfdLldfTypeAEK::TestMe(rlog);
   tst &= lrfdWsdotLldfTypeAEK::TestMe(rlog);
   tst &= lrfdLldfTypeBC::TestMe(rlog);
   tst &= lrfdWsdotLldfTypeBC::TestMe(rlog);
   tst &= lrfdLldfTypeHIJ::TestMe(rlog);
   tst &= lrfdLldfTypeG::TestMe(rlog);
   tst &= lrfdTxdotVoidedSlab::TestMe(rlog);
   tst &= lrfdLldfTypeF::TestMe(rlog);
   tst &= lrfdTxdotLldfSpreadSlab::TestMe(rlog);

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
