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

namespace WBFL
{
   namespace Math
   {
      /// This class represents a linear function of the form f(x) = mx + b.
      class MATHCLASS LinearFunction : public Function
      {
      public:
         /// Creates a function whose slope and y-intercept are zero.
         LinearFunction() = default;

         /// Creates a linear function using slope and yIntercept.
         LinearFunction(Float64 slope,Float64 yIntercept);

         LinearFunction(const LinearFunction&) = default;

         virtual ~LinearFunction() = default;

         LinearFunction& operator=(const LinearFunction&) = default;

         virtual Float64 Evaluate(Float64 x) const override;

         virtual std::unique_ptr<Function> Clone() const override;

         Float64 GetSlope() const;
         void SetSlope(Float64 slope);

         Float64 GetYIntercept() const;
         void SetYIntercept(Float64 yIntercept);

      private:
         Float64 m_Slope{0.0};
         Float64 m_Yintercept{0.0};
      };
   };
};
