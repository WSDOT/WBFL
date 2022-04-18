///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#include <Math\MathLib.h>
#include <Math\UnitTest.h>
#include <Math\BrentsRootFinder2d.h>
#include <Math\BisectionRootFinder2d.h>
#include <Math\RootFinder2d.h>
#include <Math\CoordMapper1d.h>
#include <Math\Function2d.h>
#include <Math\Polynomial2d.h>
#include <Math\LinFunc2d.h>
#include <Math\QuadraticSolver.h>
#include <Math\CubicSolver.h>
#include <Math\1dRange.h>
#include <Math\PwLinearFunction2dUsingPoints.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathUnitTest
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

bool test_rootfinders(dbgLog& rlog);

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool mathUnitTest::TestMe(dbgLog& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= mathBrentsRootFinder2d::TestMe(rlog);
   tst &= mathBisectionRootFinder2d::TestMe(rlog);
   tst &= mathCoordMapper1d::TestMe( rlog );
//   tst &= mathFunction2d::TestMe( rlog );
   tst &= mathRootFinder2d::TestMe(rlog);
//   tst &= mathLinFunc2d::TestMe( rlog );
//   tst &= mathXEvalError::TestMe( rlog );
//   tst &= mathXRootFinder2dFailed::TestMe( rlog );
   tst &= mathQuadraticSolver::TestMe( rlog );
   tst &= mathCubicSolver::TestMe( rlog );
   tst &= math1dRange::TestMe(rlog);
   tst &= mathPwLinearFunction2dUsingPoints::TestMe(rlog);

   tst &= test_rootfinders(rlog);

   tst &= TestEx(rlog);

#endif

   return tst;
}


bool mathUnitTest::TestEx(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathEx");

   TRY_TESTME( IsEqual( FloorOff(3.15,0.15), 3.15));
   TRY_TESTME( IsEqual( FloorOff(0.0,.15), 0.0));
   TRY_TESTME( IsEqual( FloorOff(3.12,0.15), 3.0));
   TRY_TESTME( IsEqual( FloorOff(3.01,0.15), 3.0));
   TRY_TESTME( IsEqual( FloorOff(-3.15,0.15), -3.15));
   TRY_TESTME( IsEqual( FloorOff(-3.16,0.15), -3.30));
   TRY_TESTME( IsEqual( FloorOff(-3.25,0.15), -3.30));

   TRY_TESTME( IsEqual( CeilOff(3.15,0.15), 3.15));
   TRY_TESTME( IsEqual( CeilOff(0.0,.15), 0.0));
   TRY_TESTME( IsEqual( CeilOff(3.12,0.15), 3.15));
   TRY_TESTME( IsEqual( CeilOff(3.01,0.15), 3.15));
   TRY_TESTME( IsEqual( CeilOff(-3.15,0.15), -3.15));
   TRY_TESTME( IsEqual( CeilOff(-3.12,0.15), -3.0));
   TRY_TESTME( IsEqual( CeilOff(-3.01,0.15), -3.0));

   TESTME_EPILOG("mathEx")
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

bool test_rootfinders(dbgLog& rlog)
{
   TESTME_PROLOGUE("Root Finder Tests");

   mathBrentsRootFinder2d brents;
   mathBisectionRootFinder2d bisection;

   std::vector<Float64> c;
   c.push_back(1);
   c.push_back(4);
   c.push_back(0);
   c.push_back(-10);
   mathPolynomial2d f1(c);
   Float64 x;
   Float64 tol = 1e-03;

   x = brents.FindRootInRange(f1,1,2,tol);
   TRY_TESTME( IsEqual(x,1.365,tol) );
   TRY_TESTME( IsZero(f1.Evaluate(x),tol) );

   x = bisection.FindRootInRange(f1,1,2,tol);
   TRY_TESTME( IsEqual(x,1.365,tol) );
   TRY_TESTME( IsZero(f1.Evaluate(x),tol) );

   TESTME_EPILOG("Root Finder Tests complete");
}
