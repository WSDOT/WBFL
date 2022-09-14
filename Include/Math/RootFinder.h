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

#pragma once

#include <Math\MathExp.h>
#include <functional>

namespace WBFL
{
   namespace Math
   {
      class MATHCLASS Function;

      /// Abstract base class for root finders. Root finders of
      /// this type find zeros in Function objects.
      class MATHCLASS RootFinder
      {
      public:
         RootFinder() = default;
         RootFinder(const RootFinder&) = delete;

         virtual ~RootFinder() = default;

         RootFinder& operator=(const RootFinder&) = delete;

         /// Finds the root of f that is nearest to xNearest, such that -tol < f(x) < tol.
         /// Throws a XRootFinder exception if a root could not be found.
         virtual Float64 FindRoot(const Function& f,Float64 xNearest,Float64 tol) const;

         /// Finds the root of f that is nearest to xNearest, subject to the constraint
         /// x > xMin, such that -tol < f(x) < tol.
         /// Throws a XRootFinder exception if a root could not be found.
         virtual Float64 FindRootConstrainedMin(const Function& f,Float64 xNearest,Float64 xMin, Float64 tol) const;

         /// Finds the root of f that is nearest to xNearest, subject to the constraint
         /// x < xMax, such that -tol < f(x) < tol.
         /// Throws a XRootFinder exception if a root could not be found.
         virtual Float64 FindRootConstrainedMax(const Function& f,Float64 xNearest, Float64 xMax, Float64 tol) const;

         /// Finds the root of f that is in the range [xMin,xMax], such that -tol < f(x) < tol.
         /// Throws a XRootFinder exception if a root could not be found.
         virtual Float64 FindRootInRange(const Function& f,Float64 xMin,Float64 xMax,Float64 tol) const = 0;

         /// Finds the root of f that is in the range [xMin,xMax], such that -tol < f(x) < tol.
         /// Throws a XRootFinder exception if a root could not be found.
         virtual Float64 FindRootInRange(const std::function<Float64(Float64)>& f, Float64 xMin, Float64 xMax, Float64 tol) const = 0;

         /// Sets the maximum number of iterations
         void SetMaxIter(Uint32 maxIter);

         /// Returns the maximum number of iteratioms
         Uint32 GetMaxIter() const;

      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST


      protected:
         enum class BracketOutcome { Bracketted, ///< bracket was sucessful. put in x[0,1]
                                     FoundRoot,  ///< found a root - stored it in x[0]
                                     Failed      ///< bracket failed.
         };

         //------------------------------------------------------------------------
         // bracketing functions. These functions are not meant to find a root, merely
         // find x values on either side of it. If they sucessfully bracket a root they will
         // return Bracketted put the x values in x[0,1]. However, if they are lucky enough
         // to actually find a root, they will return FoundRoot and place the root into x[0].
         virtual BracketOutcome Bracket(const Function& eval, Float64 x[], Float64 tol) const;
         virtual BracketOutcome BracketConstrainedMin(const Function& eval, Float64 x[], Float64 xmin, Float64 tol) const;
         virtual BracketOutcome BracketConstrainedMax(const Function& eval, Float64 x[], Float64 xmax, Float64 tol) const;

         // GROUP: ACCESS
         // GROUP: INQUIRY

      private:
         Uint32 m_MaxIter{1000};
      };
   };
};
