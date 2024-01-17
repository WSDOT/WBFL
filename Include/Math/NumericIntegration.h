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

#pragma once

#include <Math\MathExp.h>
#include <Math\Function.h>
#include <functional>

namespace WBFL
{
   namespace Math
   {
      /// Abstract base class for numeric integration.
      class MATHCLASS NumericIntegration
      {
      public:
         /// @brief Performs the numeric integration
         /// @param f Function to be integrated
         /// @param xMin Minimum value for the integration range
         /// @param xMax Maximum value for the integration range
         /// @param nIntervals Number of intervals in the integration range to consider
         /// @return The integration result (area under the curve)
         virtual Float64 Evaluate(const Function& f,Float64 xMin,Float64 xMax,Uint16 nIntervals) const = 0;
         virtual Float64 Evaluate(const std::function<Float64(Float64)>& f, Float64 xMin, Float64 xMax, Uint16 nIntervals) const = 0;
      };
   };
};
