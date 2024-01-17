///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <Math\FixedPointIteration.h>
#include <Math\XFixedPointIteration.h>

using namespace WBFL::Math;

Float64 FixedPointIteration::Solve(const std::function<Float64(Float64)>& f, Float64 xo, Float64 tol, Uint32 maxIter) const
{
   Float64 x_guess = xo;
   for (Uint32 i = 0; i < maxIter; i++)
   {
      Float64 x = f(x_guess);
      if (IsEqual(x_guess, x, tol))
         return x_guess;

      x_guess = x; // use computed x as next guess
   }

   THROW_FIXEDPOINTITERATION(XFixedPointIteration::Reason::MaxIterExceeded, x_guess);

   return x_guess;
}

Float64 FixedPointIteration::Solve(const Function& eval,Float64 xo,Float64 tol,Uint32 maxIter) const
{
   return Solve([&eval](Float64 x) {return eval.Evaluate(x); }, xo, tol, maxIter);
}
