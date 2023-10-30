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

namespace WBFL
{
   namespace Math
   {
      /// Utility class to solve quadratic equations.
      /// Finds the roots of equations having the form ax^3 + bx^2 + cx + d = 0
      class MATHCLASS CubicSolver
      {
      public:
         // GROUP: LIFECYCLE

         CubicSolver(Float64 a,Float64 b,Float64 c,Float64 d);

         CubicSolver(const CubicSolver&) = default;

         ~CubicSolver() = default;

         CubicSolver& operator=(const CubicSolver&) = default;

         /// @{
         /// @brief coefficients of a quadratic equation in the form ax^3 + bx^2 + cx + d = 0
         void SetCoefficients(Float64 a, Float64 b, Float64 c,Float64 d);
         void GetCoefficients(Float64* a, Float64* b, Float64* c,Float64* d) const;
         /// @}

         /// Sets the coefficient a
         void SetA(Float64 a);

         /// Gets the coefficient a
         Float64 GetA() const;

         /// Sets the coefficient b
         void SetB(Float64 b);

         /// Gets the coefficient b
         Float64 GetB() const;

         /// Sets the coefficient c
         void SetC(Float64 c);

         /// Gets the coefficient c
         Float64 GetC() const;

         /// Sets the coefficient d
         void SetD(Float64 d);

         /// Gets the coefficient d
         Float64 GetD() const;

         /// Solves the cubic equation.
         /// @return The roots
         std::vector<Float64> Solve() const;

      private:
         Float64 m_A{0.0};
         Float64 m_B{ 0.0 };
         Float64 m_C{ 0.0 };
         Float64 m_D{ 0.0 };
      };
   };
};
