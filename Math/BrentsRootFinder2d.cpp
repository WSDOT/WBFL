///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include <Math\BrentsRootFinder2d.h>
#include <Math\Function2d.h>
#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathBrentsRootFinder2d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathBrentsRootFinder2d::mathBrentsRootFinder2d() :
mathRootFinder2d()
{
}


mathBrentsRootFinder2d::~mathBrentsRootFinder2d()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

const Float64 EPS = 3.0e-10; // from Ken P.
Float64 mathBrentsRootFinder2d::FindRootInRange(const mathFunction2d& eval,
                                                Float64 a,Float64 b, Float64 tol)
{
   // This form of findRoot finds a root subject to the requirement that the root is
   // bracketted by a and b. The exception mathXRootFinderFailed is thrown if "a"
   // and "b" do not bracket the root, i.e., do not cause the function to change sign.

   try {
      Float64 fa = eval.Evaluate(a);
      Float64 fb = eval.Evaluate(b);
      Float64 c = b; 
      Float64 fc = fb;

      fa = (IsZero(fa,tol) ? 0 : fa);
      fb = (IsZero(fb,tol) ? 0 : fb);

      // ensure that the root is bracketed
      if (fa*fb > 0.0) 
      {
         mathXRootFinder2dFailed mx(mathXRootFinder2dFailed::BracketFailed,_T(__FILE__),__LINE__);
         mx.Throw();
      }
   
      Float64 d = 0.0, e = 0.0, min1, min2;
      Float64 p, q, r, s, tol1, xm;

      for (int iter = 1; iter <= GetMaxIter(); iter++) {
         // for iter = 1, fc == fb so next statement is always true
         if ((fb > 0.0 && fc > 0.0) || (fb < 0.0 && fc < 0.0)) {
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
         tol1 = 2.0*EPS*fabs(b) + 0.5*tol;
         xm = 0.5*(c - b);
         
         if (fabs(xm) <= tol1 || fb == 0.0)
            return b; // found a root, normal return
            
         if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) {
            s = fb/fa;
            if (a == c) {
               p = 2.0*xm*s;
               q = 1.0 - s;
            }
            else {
               q = fa/fc;
               r = fb/fc;
               p = s*(2.0*xm*q*(q - r)  -  (b - a)*(r - 1.0));
               q = (q - 1.0)*(r - 1.0)*(s - 1.0);
            }
            if (p > 0.0) 
               q = -q;
            p = fabs(p);
            min1 = 3.0*xm*q - fabs(tol1*q);
            min2 = fabs(e*q);
            if (2.0*p < Min(min1, min2)) {
               e = d;
               d = p/q;
            }
            else {
               d = xm;
               e = d;
            }
         }
         else {
            d = xm;
            e = d;
         }
         
         a = b;
         fa = fb;
         
         if (fabs(d) > tol1)
            b += d;
         else
            b += xm > 0.0 ? tol1 : -tol1;
            
         fb = eval.Evaluate(b);
      }
   }
   catch (mathXEvalError e) {
      mathXRootFinder2dFailed mx(mathXRootFinder2dFailed::RootNotPresent,_T(__FILE__),__LINE__);
      mx.Throw();
   }
   // too many iters
   mathXRootFinder2dFailed mx(mathXRootFinder2dFailed::MaxIterExceeded,_T(__FILE__),__LINE__);
   mx.Throw();
   return 0; // pacify the compiler
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool mathBrentsRootFinder2d::AssertValid() const
{
   return mathRootFinder2d::AssertValid();
}

void mathBrentsRootFinder2d::Dump(dbgDumpContext& os) const
{
   mathRootFinder2d::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathBrentsRootFinder2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathBrentsRootFinder2d");
   // Unit Tests implemented on package level
   TESTME_EPILOG("mathBrentsRootFinder2d");
}
#endif

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


