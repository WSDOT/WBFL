///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\UnitTest.h>
#include <Material\Concrete.h>
#include <Material\ConcreteEx.h>
#include <Material\ConcreteListener.h>
#include <Material\LinearStressStrainCurve.h>
#include <Material\Metal.h>
#include <Material\MetalListener.h>
#include <Material\PsStrand.h>
#include <Material\PsStrandCurve.h>
#include <Material\Rebar.h>
#include <Material\StressStrainCurve.h>
#include <Material\YieldStressStrainCurve.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matUnitTest
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool matUnitTest::TestMe(WBFL::Debug::Log& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= matConcrete::TestMe(rlog);
   tst &= matConcreteEx::TestMe(rlog);
   tst &= matConcreteListener::TestMe(rlog);
   tst &= matLinearStressStrainCurve::TestMe(rlog);
   tst &= matMetal::TestMe(rlog);
   tst &= matMetalListener::TestMe(rlog);
   tst &= matPsStrand::TestMe(rlog);
   tst &= matPsStrandCurve::TestMe(rlog);
   tst &= matRebar::TestMe(rlog);
   tst &= matStressStrainCurve::TestMe(rlog);
   tst &= matYieldStressStrainCurve::TestMe(rlog);

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
