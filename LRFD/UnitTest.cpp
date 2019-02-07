///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include <Lrfd\UnitTest.h>
#include <Lrfd\AutoVersion.h>
#include <Lrfd\ConcreteUtil.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd\ApproximateLosses.h>
#include <Lrfd\ApproximateLosses2005.h>
#include <Lrfd\RefinedLosses.h>
#include <Lrfd\RefinedLosses2005.h>
#include <Lrfd\PsStrand.h>
#include <Lrfd\Shear.h>
#include <Lrfd\StrandPool.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\RebarPool.h>
#include <Lrfd\Utility.h>
#include <Lrfd\LoadModifier.h>
#include <Lrfd\LimitStateCalculator.h>
#include <Lrfd\LldfTypeAEKIJ.h>
#include <Lrfd\LldfTypeAEK.h>
#include <Lrfd\LldfTypeBC.h>
#include <Lrfd\LldfTypeHIJ.h>
#include <Lrfd\LldfTypeG.h>
#include <Lrfd\LldfTxdotMultiWeb.h>
#include <Lrfd\LldfTxdotSpreadSlab.h>
#include <Lrfd\CreepCoefficient.h>
#include <Lrfd\CreepCoefficient2005.h>

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
