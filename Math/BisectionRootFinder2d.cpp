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
#include <Math\BisectionRootFinder2d.h>
#include <Math\Function2d.h>
#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathBisectionRootFinder2d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathBisectionRootFinder2d::mathBisectionRootFinder2d() :
mathRootFinder2d()
{
}


mathBisectionRootFinder2d::~mathBisectionRootFinder2d()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Float64 mathBisectionRootFinder2d::FindRootInRange(const mathFunction2d& eval,
                                                   Float64 a,Float64 b, Float64 tol)
{
   // This form of findRoot finds a root subject to the requirement that the root is
   // bracketted by a and b. The exception mathXRootFinderFailed is thrown if "a"
   // and "b" do not bracket the root, i.e., do not cause the function to change sign.

   try  // eval could throw...
   {
      Float64 fa = eval.Evaluate(a);
      if (IsZero(fa, tol))
      {
         // the root is at a
         return a;
      }

      Float64 fb = eval.Evaluate(b);
      if (IsZero(fb, tol))
      {
         // the root is at b
         return b;
      }
      
      // Ensure that the root is bracketed
      if (fa*fb > 0.0) 
      {
         mathXRootFinder2dFailed mx(mathXRootFinder2dFailed::BracketFailed,_T(__FILE__),__LINE__);
         mx.Throw();
      }


      // Iterate until root is found or until we exceed the max number of iterations
      Int32 cIter = GetMaxIter();
      for ( Int32 i = 0; i < cIter; i++ )
      {
         Float64 p  = a + (b-a)/2;
         Float64 fp = eval.Evaluate(p);

         // Did we hit the root?
         if ( IsZero(fp,tol) )
            return p;

         if ( fa*fp > 0.0 )
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

         CHECK( b != a );
      }
   }
   catch (mathXEvalError e) 
   {
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
bool mathBisectionRootFinder2d::AssertValid() const
{
   return mathRootFinder2d::AssertValid();
}

void mathBisectionRootFinder2d::Dump(dbgDumpContext& os) const
{
   mathRootFinder2d::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathBisectionRootFinder2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathBisectionRootFinder2d");
   // Unit Tests implemented on package level
   TESTME_EPILOG("mathBisectionRootFinder2d");
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


