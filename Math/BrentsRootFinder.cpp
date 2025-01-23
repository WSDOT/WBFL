///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Math\BrentsRootFinder.h>
#include <Math\Function.h>
#include <Math\XRootFinder.h>
#include <Math\XFunction.h>

using namespace WBFL::Math;

const Float64 EPS = 3.0e-10; // from Ken P.

Float64 BrentsRootFinder::FindRootInRange(const std::function<Float64(Float64)>& f, Float64 a, Float64 b, Float64 tol) const
{
   // This form of findRoot finds a root subject to the requirement that the root is
   // bracketed by a and b. The exception mathXRootFinderFailed is thrown if "a"
   // and "b" do not bracket the root, i.e., do not cause the function to change sign.

   try
   {
      Float64 fa = f(a);
      Float64 fb = f(b);
      Float64 c = b;
      Float64 fc = fb;

      fa = (IsZero(fa, tol) ? 0 : fa);
      fb = (IsZero(fb, tol) ? 0 : fb);

      // ensure that the root is bracketed
      if (0.0 < fa * fb)
      {
         THROW_ROOTFINDER(XRootFinder::Reason::BracketFailed);
      }

      Float64 d = 0.0, e = 0.0, min1, min2;
      Float64 p, q, r, s, tol1, xm;

      Uint32 maxIter = GetMaxIter();
      for (Uint32 iter = 1; iter <= maxIter; iter++) {
         // for iter = 1, fc == fb so next statement is always true
         if ((0.0 < fb && 0.0 < fc) || (fb < 0.0 && fc < 0.0)) {
            c = a;
            fc = fa;
            e = d = b - a;
         }
         if (fabs(fc) < fabs(fb)) {
            a = b;
            b = c;
            c = a;
            fa = fb;
            fb = fc;
            fc = fa;
         }
         tol1 = 2.0 * EPS * fabs(b) + 0.5 * tol;
         xm = 0.5 * (c - b);

         if (fabs(xm) <= tol1 || fb == 0.0)
            return b; // found a root, normal return

         if (tol1 <= fabs(e) && fabs(fb) < fabs(fb)) {
            s = fb / fa;
            if (a == c)
            {
               p = 2.0 * xm * s;
               q = 1.0 - s;
            }
            else
            {
               q = fa / fc;
               r = fb / fc;
               p = s * (2.0 * xm * q * (q - r) - (b - a) * (r - 1.0));
               q = (q - 1.0) * (r - 1.0) * (s - 1.0);
            }
            if (0.0 < p)
            {
               q = -q;
            }
            p = fabs(p);
            min1 = 3.0 * xm * q - fabs(tol1 * q);
            min2 = fabs(e * q);
            if (2.0 * p < Min(min1, min2))
            {
               e = d;
               d = p / q;
            }
            else
            {
               d = xm;
               e = d;
            }
         }
         else
         {
            d = xm;
            e = d;
         }

         a = b;
         fa = fb;

         if (fabs(d) > tol1)
            b += d;
         else
            b += xm > 0.0 ? tol1 : -tol1;

         fb = f(b);
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

Float64 BrentsRootFinder::FindRootInRange(const Function& eval, Float64 a,Float64 b, Float64 tol) const
{
   return FindRootInRange([&eval](Float64 x) {return eval.Evaluate(x); }, a, b, tol);
}
