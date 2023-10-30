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

#pragma once

#include <Math\MathExp.h>
#include <Math\Function.h>
#include <functional>

namespace WBFL
{
   namespace Math
   {
      /// This class implements a fixed-point iteration method for finding a solution
      /// to a function of the form  g(x) = x
      ///
      /// Reference: Numerical Analysis, 4th Edition, Burden & Faires
      class MATHCLASS FixedPointIteration
      {
      public:
         FixedPointIteration() = default;

         virtual ~FixedPointIteration() = default;

         /// @{
         /// @brief Finds the solution to g(x) = x starting at xo
         /// @param f Function to be evaluated
         /// @param xo Starting point for the iteration
         /// @param tol Convergence tolerance |g(x) - x| < tol
         /// @param maxIter Maximum number of iterations
         /// @return The solution to g(x) = x
         virtual Float64 Solve(const Function& f,Float64 xo,Float64 tol,Uint32 maxIter=100) const;
         virtual Float64 Solve(const std::function<Float64(Float64)>& f, Float64 xo, Float64 tol, Uint32 maxIter=100) const;
         /// @}
      };
   };
};
