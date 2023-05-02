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
#include <Math\BisectionRootFinder.h>
#include <Math\Function.h>
#include <Math\XRootFinder.h>
#include <Math\XFunction.h>

using namespace WBFL::Math;

Float64 BisectionRootFinder::FindRootInRange(const std::function<Float64(Float64)>& f, Float64 a, Float64 b, Float64 tol) const
{
   // This form of findRoot finds a root subject to the requirement that the root is
   // bracketted by a and b. The exception mathXRootFinderFailed is thrown if "a"
   // and "b" do not bracket the root, i.e., do not cause the function to change sign.

   try  // eval could throw...
   {
      Float64 fa = f(a);
      if (IsZero(fa, tol))
      {
         // the root is at a
         return a;
      }

      Float64 fb = f(b);
      if (IsZero(fb, tol))
      {
         // the root is at b
         return b;
      }

      // Ensure that the root is bracketed
      if (0.0 < fa * fb)
      {
         THROW_ROOTFINDER(XRootFinder::Reason::BracketFailed);
      }


      // Iterate until root is found or until we exceed the max number of iterations
      Uint32 cIter = GetMaxIter();
      for (Uint32 i = 0; i < cIter; i++)
      {
         Float64 p = a + (b - a) / 2;
         Float64 fp = f(p);

         // Did we hit the root?
         if (IsZero(fp, tol))
            return p;

         if (0.0 < fa * fp)
         {
            a = p;
            fa = fp;
         }
         else
         {
            b = p;
            // We don't actually do anything with fb except checking for
            // bracketting, above.  Don't update fb here. It is a waist of
            // time.  At the start of the loop, this new b is used to compute
            // a new p which is evaluated.
         }

         CHECK(b != a);
      }
   }
   catch (XFunction e)
   {
      THROW_ROOTFINDER(XRootFinder::Reason::RootNotPresent);
   }

   // too many iters
   THROW_ROOTFINDER(XRootFinder::Reason::MaxIterExceeded);

   return 0; // pacify the compiler
}

Float64 BisectionRootFinder::FindRootInRange(const Function& eval, Float64 a,Float64 b, Float64 tol) const
{
   return FindRootInRange([&eval](Float64 x) {return eval.Evaluate(x); }, a, b, tol);
}

#if defined _UNITTEST
bool BisectionRootFinder::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("BisectionRootFinder");

   BisectionRootFinder rf;
   Float64 x1 = rf.FindRootInRange([](Float64 x) {return sin(x); }, -0.1, 0.1,0.001);
   TRY_TESTME(IsEqual(x1, 0.0));

   Float64 x2 = rf.FindRootInRange([](Float64 x) {return sin(x); }, M_PI - 0.1, M_PI + 0.1, 0.001);
   TRY_TESTME(IsEqual(x2, M_PI));

   Float64 x3 = rf.FindRootInRange([](Float64 x) {return cos(x); }, PI_OVER_2 - 0.1, PI_OVER_2 + 0.1, 0.001);
   TRY_TESTME(IsEqual(x3, PI_OVER_2));

   TESTME_EPILOG("BisectionRootFinder");
}
#endif
