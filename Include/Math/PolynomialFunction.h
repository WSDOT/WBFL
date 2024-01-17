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
#include <vector>

namespace WBFL
{
   namespace Math
   {
      /// Defines a polynomial function of the form K1*x^n + K2*x^(n-1) + ... + Kn-1*x + Kn = 0;
      class MATHCLASS PolynomialFunction : public Function
      {
      public:
         PolynomialFunction() = default;
         PolynomialFunction(const PolynomialFunction&) = default;
         PolynomialFunction(const std::vector<Float64>& coefficients);
         virtual ~PolynomialFunction() = default;

         PolynomialFunction& operator=(const PolynomialFunction&) = default;

         /// @brief Sets the coefficients of the polynomial
         /// @param coefficients 
         void SetCoefficients(const std::vector<Float64>& coefficients);
         const std::vector<Float64>& GetCoefficients() const;
   
         virtual Float64 Evaluate(Float64 x) const override;
         virtual std::unique_ptr<Function> Clone() const override;

         /// @brief Returns a polynomial function that is the derivative of this function.
         PolynomialFunction GetDerivative() const;

      private:
         std::vector<Float64> m_Coefficients;
      };
   };
};
