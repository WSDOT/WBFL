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
#include <Math\TrapezoidalRuleIntegrator.h>

using namespace WBFL::Math;

Float64 TrapezoidalRuleIntegrator::Evaluate(const std::function<Float64(Float64)>& f, Float64 xMin, Float64 xMax, Uint16 nIntervals) const
{
   Float64 stepSize = (xMax - xMin) / nIntervals;

   Float64 A = 0;
   for (Uint16 i = 0; i < nIntervals; i++)
   {
      Float64 xa = xMin + stepSize * i;
      Float64 xb = xMin + stepSize * (i + 1);

      Float64 ya = f(xa);
      Float64 yb = f(xb);

      A += 0.5 * (yb + ya) * (xb - xa);
   }

   return A;
}

Float64 TrapezoidalRuleIntegrator::Evaluate(const Function& f,Float64 xMin,Float64 xMax,Uint16 nIntervals) const
{
   return Evaluate([&f](Float64 x) {return f.Evaluate(x); }, xMin, xMax, nIntervals);
}
