///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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
#include <Math\RootFinder2d.h>
#include <Math\Function2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathXRootFinder2dFailed
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathXRootFinder2dFailed::mathXRootFinder2dFailed(Reason reason,LPCTSTR file,Int16 line) :
sysXBase(file,line)
{
   m_Reason = reason;
}

mathXRootFinder2dFailed::mathXRootFinder2dFailed(const mathXRootFinder2dFailed& rOther) :
sysXBase( rOther )
{
   m_Reason = rOther.m_Reason;
}

mathXRootFinder2dFailed::~mathXRootFinder2dFailed()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
mathXRootFinder2dFailed& mathXRootFinder2dFailed::operator=(const mathXRootFinder2dFailed& rOther)
{
   if ( this != &rOther )
   {
      sysXBase::operator=( rOther);
      m_Reason = rOther.m_Reason;
   }

   return *this;
}

//======================== ACCESS     =======================================
void mathXRootFinder2dFailed::Throw() const
{
   throw *static_cast<const mathXRootFinder2dFailed*>(this);
}

Int32 mathXRootFinder2dFailed::GetReason() const
{
   return m_Reason;
}

mathXRootFinder2dFailed::Reason mathXRootFinder2dFailed::GetReasonCode() const
{
   return m_Reason;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

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


/****************************************************************************
CLASS
   mathRootFinder2d
****************************************************************************/

   const int NTRY = 50;
   const Float64 FACTOR = 1.6;
   const Float64 EPS = 3.0e-10; // from Ken P.

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathRootFinder2d::mathRootFinder2d():
m_MaxIter(1000)
{
}

mathRootFinder2d::~mathRootFinder2d()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

Float64 mathRootFinder2d::FindRoot(const mathFunction2d& f,Float64 xNearest,
                                         Float64 tol)
{
/*
   This form of findRoot attempts to find a root by geometrically expanding a range out 
   in the vicinity of "xNearest".
*/
   // ensure that the root is bracketed
   Float64 x[] = {xNearest, xNearest};

   BracketOutcome outcome = Bracket(f, x, tol);

   if (outcome == mathRootFinder2d::Bracketted)
   {
      return FindRootInRange(f, x[0], x[1], tol);
   }
   else if (outcome == mathRootFinder2d::FoundRoot)
   {
      return x[0];
   }
   else
   {
      mathXRootFinder2dFailed mx(mathXRootFinder2dFailed::BracketFailed,_T(__FILE__),__LINE__);
      mx.Throw();
      return 0;
   }
}

Float64 mathRootFinder2d::FindRootConstrainedMin(const mathFunction2d& f,Float64 xNearest,
                                                       Float64 xMin,Float64 tol)
{
/*
This form of findRoot attempts to find a root by geometrically expanding a range out 
in the vicinity of "a" subject to the constraint that the function will never be
evaluated for any x <= xmin.
*/
   // attempt to bracket root
   Float64 x[] = {xNearest, xNearest};
 
   BracketOutcome outcome = BracketConstrainedMin(f, x, xMin, tol);
   
   if (outcome == mathRootFinder2d::Bracketted)
   {
      return FindRootInRange(f, x[0], x[1], tol);
   }
   else if (outcome == mathRootFinder2d::FoundRoot)
   {
      return x[0];
   }
   else
   {
      mathXRootFinder2dFailed mx(mathXRootFinder2dFailed::BracketFailed,_T(__FILE__),__LINE__);
      mx.Throw();
      return 0;
   }
}

Float64 mathRootFinder2d::FindRootConstrainedMax(const mathFunction2d& f,Float64 xNearest,
                                                       Float64 xMax,Float64 tol)
{
/*
This form of findRoot attempts to find a root by geometrically expanding a range out 
in the vicinity of "a" subject to the constraint that the function will never be
evaluated for any x >= xmax.
*/
   // ensure that the root is bracketed
   Float64 x[] = {xNearest, xNearest};
   
   BracketOutcome outcome = BracketConstrainedMax(f, x, xMax, tol);
   
   if (outcome == mathRootFinder2d::Bracketted)
   {
      return FindRootInRange(f, x[0], x[1], tol);
   }
   else if (outcome == mathRootFinder2d::FoundRoot)
   {
      return x[0];
   }
   else
   {
      mathXRootFinder2dFailed mx(mathXRootFinder2dFailed::BracketFailed,_T(__FILE__),__LINE__);
      mx.Throw();
      return 0;
   }
}

void mathRootFinder2d::SetMaxIter(Int32 maxIter)
{
   m_MaxIter = maxIter;
}

Int32 mathRootFinder2d::GetMaxIter() const
{
   return m_MaxIter;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool mathRootFinder2d::AssertValid() const
{
   return true;
}

void mathRootFinder2d::Dump(dbgDumpContext& os) const
{
   os << "Dump for mathRootFinder2d - Not Implemented" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathRootFinder2d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathRootFinder2d");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for mathRootFinder2d");
   TESTME_EPILOG("mathRootFinder2d");
}
#endif

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

mathRootFinder2d::BracketOutcome mathRootFinder2d::Bracket(const mathFunction2d& eval, Float64 x[],
                                         Float64 tol)
{

   if (x[0] == 0.0 && x[1] == 0.0) 
   {
      x[1] = 1.0;
   }
   else if (x[0] == x[1]) 
   {
      x[1] = FACTOR*x[0];
   }

   
   Float64 f0 = eval.Evaluate(x[0]);
   if (fabs(f0)<tol)
   {
      x[0] = x[0];
      x[1] = f0;
      return FoundRoot;
   }

   Float64 f1 = eval.Evaluate(x[1]);
   if (fabs(f1)<tol)
   {
      x[0] = x[1];
      x[1] = f1;
      return FoundRoot;
   }

   for (int j = 1; j <= NTRY; j++) 
   {
   
      if (f0*f1 < 0.0)
      {
         WATCH("bracket complete, n = " << j);
         return Bracketted; // normal return
      }  
      else if (fabs(f0) < fabs(f1))
      {
         x[0] += FACTOR*(x[0] - x[1]);
         f0 = eval.Evaluate(x[0]);
         if (fabs(f0)<tol)
         {
            x[0] = x[0];
            x[1] = f0;
            return FoundRoot;
         }
      }
      else 
      {
         x[1] += FACTOR*(x[1] - x[0]);
         f1 = eval.Evaluate(x[1]);
         if (fabs(f1)<tol)
         {
            x[0] = x[1];
            x[1] = f1;
            return FoundRoot;
         }
      }
   }
   // root not present
   return Failed;
}

mathRootFinder2d::BracketOutcome mathRootFinder2d::BracketConstrainedMin(const mathFunction2d& eval, Float64 x[], 
                                          Float64 xmin, Float64 tol) 
{
   // need to insure that both x[0] and x[1] are greater than xmin.
   if (x[0] <= xmin || x[1] <= xmin) 
      return Failed;
   
   bool constrainedMin = false;

   if (x[0] == 0.0 && x[1] == 0.0) 
   {
      x[1] = 1.0;
   }
   else if (x[0] == x[1]) 
   {
      x[1] = FACTOR*x[0];
   }
   
   // insure x0 < x1
   if (x[0] > x[1]) 
   {
      Float64 t = x[0];
      x[0] = x[1];
      x[1] = t;
   }

   Float64 f0 = eval.Evaluate(x[0]);
   if (fabs(f0)<tol)
   {
      x[0] = x[0];
      x[1] = f0;
      return FoundRoot;
   }
   Float64 f1 = eval.Evaluate(x[1]);
   if (fabs(f1)<tol)
   {
      x[0] = x[1];
      x[1] = f1;
      return FoundRoot;
   }

   for (int j = 1; j <= NTRY; j++) {
   
      if (f0*f1 < 0.0) 
      {
         WATCH("bracket complete, n = " << j);
         return Bracketted; // normal return
      }  
      else if (!constrainedMin && (f0 < f1)) 
      {
         x[0] += FACTOR*(x[0] - x[1]);
         if (x[0] <= xmin) 
         {
            x[0] = xmin + EPS;
            constrainedMin = true;
         }

         f0 = eval.Evaluate(x[0]);
         if (fabs(f0)<tol)
         {
            x[0] = x[0];
            x[1] = f0;
            return FoundRoot;
         }
      }
      else 
      {
         x[1] += FACTOR*(x[1] - x[0]);
         f1 = eval.Evaluate(x[1]);

         if (fabs(f1)<tol)
         {
            x[0] = x[1];
            x[1] = f1;
            return FoundRoot;
         }
      }
   }
   return Failed;
}

mathRootFinder2d::BracketOutcome mathRootFinder2d::BracketConstrainedMax(const mathFunction2d& eval, Float64 x[], 
                                          Float64 xmax, Float64 tol) 
{
   // need to insure that both x[0] and x[1] are less than xmax.
   if (x[0] >= xmax || x[1] >= xmax)
      return Failed;
   
   bool constrainedMax = false;

   if (x[0] == 0.0 && x[1] == 0.0) 
   {
      if (xmax>=1.0)
         x[1] = 1.0;
      else if (xmax>0)
         x[1] = xmax-EPS;
      else
      {
         x[0] = xmax-1.0;
         x[1] = xmax-EPS;
      }
   }
   else if (x[0] == x[1]) 
   {
      x[1] = FACTOR*x[0];
      if (x[1]>xmax)
         x[1] = xmax;
   }
   
   // insure x0 < x1
   if (x[0] > x[1]) 
   {
      Float64 t = x[0];
      x[0] = x[1];
      x[1] = t;
   }

   Float64 f0 = eval.Evaluate(x[0]);
   if (fabs(f0)<tol)
   {
      x[0] = x[0];
      x[1] = f0;
      return FoundRoot;
   }

   Float64 f1 = eval.Evaluate(x[1]);
   if (fabs(f1)<tol)
   {
      x[0] = x[1];
      x[1] = f1;
      return FoundRoot;
   }

   for (int j = 1; j <= NTRY; j++) 
   {
   
      if (f0*f1 < 0.0) 
      {
         WATCH("bracket complete, n = " << j);
         return Bracketted; // normal return
      }  
      else if (!constrainedMax && (f0 < f1)) 
      {
         x[1] += FACTOR*(x[1] - x[0]);
         if (x[1] >= xmax)
         {
            x[1] = xmax - EPS;
            constrainedMax = true;
         }

         f1 = eval.Evaluate(x[1]);
         if (fabs(f1)<tol)
         {
            x[0] = x[1];
            x[1] = f1;
            return FoundRoot;
         }
      }
      else 
      {
         x[0] += FACTOR*(x[0] - x[1]);
         f0 = eval.Evaluate(x[0]);

         if (fabs(f0)<tol)
         {
            x[0] = x[0];
            x[1] = f0;
            return FoundRoot;
         }
      }
   }
   return Failed;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


