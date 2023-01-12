///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#include <Math\MathLib.h>
#include <Math\UnitTest.h>

#undef BUILDMATHLIB
#include <Math\Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Math;

bool test_rootfinders(WBFL::Debug::Log& rlog);

bool UnitTest::TestMe(WBFL::Debug::Log& rlog)
{
   bool tst = true;

#if defined _UNITTEST

   tst &= BisectionRootFinder::TestMe(rlog);
   tst &= BrentsRootFinder::TestMe(rlog);
   //tst &= CDRatio::TestMe(rlog);
   tst &= CompositeFunction::TestMe(rlog);
   tst &= CoordMapper1d::TestMe( rlog );
   tst &= CubicSolver::TestMe(rlog);
   tst &= FixedPointIteration::TestMe(rlog);
   //tst &= Function::TestMe(rlog);
   //tst &= LinearFunction::TestMe(rlog);
   //tst &= NumericIntegration::TestMe(rlog);
   tst &= PolynomialFunction::TestMe(rlog);
   tst &= PiecewiseFunction::TestMe(rlog);
   tst &= QuadraticSolver::TestMe(rlog);
   tst &= Range::TestMe(rlog);
   tst &= RootFinder::TestMe(rlog);
   tst &= TrapezoidalRuleIntegrator::TestMe(rlog);
   //tst &= UnsymmetricBandedMatrix::TestMe(rlog);
   //tst &= XFixedPointIteration::TestMe(rlog);
   //tst &= XFunction::TestMe(rlog);
   //tst &= XNumericIntegration::TestMe(rlog);
   //tst &= XRootFinder::TestMe(rlog);

   tst &= test_rootfinders(rlog);

   tst &= TestEx(rlog);

#endif

   return tst;
}


bool UnitTest::TestEx(WBFL::Debug::Log& rlog)
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

   Float64 x;
   x = 6.2343;
   x = RoundOff(x, 0.001);
   TRY_TESTME(x == 6.234);

   x = 6.2347;
   x = RoundOff(x, 0.001);
   TRY_TESTME(x == 6.235);

   x = -6.2343;
   x = RoundOff(x, 0.001);
   TRY_TESTME(x == -6.234);

   x = -6.2347;
   x = RoundOff(x, 0.001);
   TRY_TESTME(x == -6.235);
   TESTME_EPILOG("mathEx")
}

bool test_rootfinders(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Root Finder Tests");

   BrentsRootFinder brents;
   BisectionRootFinder bisection;

   std::vector<Float64> c;
   c.push_back(1);
   c.push_back(4);
   c.push_back(0);
   c.push_back(-10);
   PolynomialFunction f1(c);
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
