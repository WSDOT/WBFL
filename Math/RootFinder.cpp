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
#include <Math\RootFinder.h>
#include <Math\Function.h>
#include <Math\XRootFinder.h>

using namespace WBFL::Math;

const int NTRY = 50;
const Float64 FACTOR = 1.6;
const Float64 EPS = 3.0e-10; // from Ken P.

Float64 RootFinder::FindRoot(const Function& f, Float64 xNearest, Float64 tol) const
{
   return FindRoot([&f](Float64 x) {return f.Evaluate(x); }, xNearest, tol);
}

Float64 RootFinder::FindRoot(const std::function<Float64(Float64)>& f, Float64 xNearest, Float64 tol) const
{
   // This form of findRoot attempts to find a root by geometrically expanding a range out 
   // in the vicinity of "xNearest".
   // 
   // ensure that the root is bracketed
   Float64 x[] = {xNearest, xNearest};

   BracketOutcome outcome = Bracket(f, x, tol);

   if (outcome == RootFinder::BracketOutcome::Bracketted)
   {
      return FindRootInRange(f, x[0], x[1], tol);
   }
   else if (outcome == RootFinder::BracketOutcome::FoundRoot)
   {
      return x[0];
   }
   else
   {
      THROW_ROOTFINDER(XRootFinder::Reason::BracketFailed);
   }
}

Float64 RootFinder::FindRootConstrainedMin(const Function& f, Float64 xNearest, Float64 xMin, Float64 tol) const
{
   return FindRootConstrainedMin([&f](Float64 x) {return f.Evaluate(x); }, xNearest, xMin, tol);
}

Float64 RootFinder::FindRootConstrainedMin(const std::function<Float64(Float64)>& f, Float64 xNearest, Float64 xMin, Float64 tol) const
{
   // This form of findRoot attempts to find a root by geometrically expanding a range out 
   // in the vicinity of "a" subject to the constraint that the function will never be
   // evaluated for any x <= xmin.

   // attempt to bracket root
   Float64 x[] = {xNearest, xNearest};
 
   BracketOutcome outcome = BracketConstrainedMin(f, x, xMin, tol);
   
   if (outcome == RootFinder::BracketOutcome::Bracketted)
   {
      return FindRootInRange(f, x[0], x[1], tol);
   }
   else if (outcome == RootFinder::BracketOutcome::FoundRoot)
   {
      return x[0];
   }
   else
   {
      THROW_ROOTFINDER(XRootFinder::Reason::BracketFailed);
   }
}

Float64 RootFinder::FindRootConstrainedMax(const Function& f, Float64 xNearest, Float64 xMax, Float64 tol) const
{
   return FindRootConstrainedMax([&f](Float64 x) {return f.Evaluate(x); }, xNearest, xMax, tol);
}

Float64 RootFinder::FindRootConstrainedMax(const std::function<Float64(Float64)>& f,Float64 xNearest, Float64 xMax,Float64 tol) const
{
   // This form of findRoot attempts to find a root by geometrically expanding a range out 
   // in the vicinity of "a" subject to the constraint that the function will never be
   // evaluated for any x >= xmax.

   // ensure that the root is bracketed
   Float64 x[] = {xNearest, xNearest};
   
   BracketOutcome outcome = BracketConstrainedMax(f, x, xMax, tol);
   
   if (outcome == RootFinder::BracketOutcome::Bracketted)
   {
      return FindRootInRange(f, x[0], x[1], tol);
   }
   else if (outcome == RootFinder::BracketOutcome::FoundRoot)
   {
      return x[0];
   }
   else
   {
      THROW_ROOTFINDER(XRootFinder::Reason::BracketFailed);
   }
}

void RootFinder::SetMaxIter(Uint32 maxIter)
{
   m_MaxIter = maxIter;
}

Uint32 RootFinder::GetMaxIter() const
{
   return m_MaxIter;
}

RootFinder::BracketOutcome RootFinder::Bracket(const std::function<Float64(Float64)>& f, Float64 x[], Float64 tol) const
{
   if (x[0] == 0.0 && x[1] == 0.0) 
   {
      x[1] = 1.0;
   }
   else if (x[0] == x[1]) 
   {
      x[1] = FACTOR*x[0];
   }
   
   Float64 f0 = f(x[0]);
   if (fabs(f0)<tol)
   {
      x[0] = x[0];
      x[1] = f0;
      return BracketOutcome::FoundRoot;
   }

   Float64 f1 = f(x[1]);
   if (fabs(f1)<tol)
   {
      x[0] = x[1];
      x[1] = f1;
      return BracketOutcome::FoundRoot;
   }

   for (int j = 1; j <= NTRY; j++) 
   {
   
      if (f0*f1 < 0.0)
      {
         WATCH(_T("bracket complete, n = ") << j);
         return BracketOutcome::Bracketted; // normal return
      }  
      else if (fabs(f0) < fabs(f1))
      {
         x[0] += FACTOR*(x[0] - x[1]);
         f0 = f(x[0]);
         if (fabs(f0)<tol)
         {
            x[0] = x[0];
            x[1] = f0;
            return BracketOutcome::FoundRoot;
         }
      }
      else 
      {
         x[1] += FACTOR*(x[1] - x[0]);
         f1 = f(x[1]);
         if (fabs(f1)<tol)
         {
            x[0] = x[1];
            x[1] = f1;
            return BracketOutcome::FoundRoot;
         }
      }
   }
   // root not present
   return BracketOutcome::Failed;
}

RootFinder::BracketOutcome RootFinder::BracketConstrainedMin(const std::function<Float64(Float64)>& f, Float64 x[], Float64 xmin, Float64 tol) const
{
   // need to insure that both x[0] and x[1] are greater than xmin.
   if (x[0] <= xmin || x[1] <= xmin) 
      return BracketOutcome::Failed;
   
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

   Float64 f0 = f(x[0]);
   if (fabs(f0)<tol)
   {
      x[0] = x[0];
      x[1] = f0;
      return BracketOutcome::FoundRoot;
   }
   Float64 f1 = f(x[1]);
   if (fabs(f1)<tol)
   {
      x[0] = x[1];
      x[1] = f1;
      return BracketOutcome::FoundRoot;
   }

   for (int j = 1; j <= NTRY; j++) {
   
      if (f0*f1 < 0.0) 
      {
         WATCH(_T("bracket complete, n = ") << j);
         return BracketOutcome::Bracketted; // normal return
      }  
      else if (!constrainedMin && (f0 < f1)) 
      {
         x[0] += FACTOR*(x[0] - x[1]);
         if (x[0] <= xmin) 
         {
            x[0] = xmin + EPS;
            constrainedMin = true;
         }

         f0 = f(x[0]);
         if (fabs(f0)<tol)
         {
            x[0] = x[0];
            x[1] = f0;
            return BracketOutcome::FoundRoot;
         }
      }
      else 
      {
         x[1] += FACTOR*(x[1] - x[0]);
         f1 = f(x[1]);

         if (fabs(f1)<tol)
         {
            x[0] = x[1];
            x[1] = f1;
            return BracketOutcome::FoundRoot;
         }
      }
   }
   return BracketOutcome::Failed;
}

RootFinder::BracketOutcome RootFinder::BracketConstrainedMax(const std::function<Float64(Float64)>& f, Float64 x[], Float64 xmax, Float64 tol) const
{
   // need to insure that both x[0] and x[1] are less than xmax.
   if (xmax <= x[0] || xmax <= x[1])
      return BracketOutcome::Failed;
   
   bool constrainedMax = false;

   if (x[0] == 0.0 && x[1] == 0.0) 
   {
      if (1.0 <= xmax)
         x[1] = 1.0;
      else if (0 < xmax)
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
      if (xmax < x[1])
         x[1] = xmax;
   }
   
   // insure x0 < x1
   if (x[1] < x[0])
   {
      std::swap(x[0], x[1]);
   }

   Float64 f0 = f(x[0]);
   if (fabs(f0)<tol)
   {
      x[0] = x[0];
      x[1] = f0;
      return BracketOutcome::FoundRoot;
   }

   Float64 f1 = f(x[1]);
   if (fabs(f1)<tol)
   {
      x[0] = x[1];
      x[1] = f1;
      return BracketOutcome::FoundRoot;
   }

   for (int j = 1; j <= NTRY; j++) 
   {
   
      if (f0*f1 < 0.0) 
      {
         WATCH(_T("bracket complete, n = ") << j);
         return BracketOutcome::Bracketted; // normal return
      }  
      else if (!constrainedMax && (f0 < f1)) 
      {
         x[1] += FACTOR*(x[1] - x[0]);
         if (xmax <= x[1])
         {
            x[1] = xmax - EPS;
            constrainedMax = true;
         }

         f1 = f(x[1]);
         if (fabs(f1)<tol)
         {
            x[0] = x[1];
            x[1] = f1;
            return BracketOutcome::FoundRoot;
         }
      }
      else 
      {
         x[0] += FACTOR*(x[0] - x[1]);
         f0 = f(x[0]);

         if (fabs(f0)<tol)
         {
            x[0] = x[0];
            x[1] = f0;
            return BracketOutcome::FoundRoot;
         }
      }
   }
   return BracketOutcome::Failed;
}
