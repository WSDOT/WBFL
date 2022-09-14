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

namespace WBFL
{
   namespace Math
   {
      /// Utility class to solve quadratic equations. 
      ///
      /// Finds the roots of equations having the form ax^2 + bx + c = 0
      class MATHCLASS QuadraticSolver
      {
      public:
         QuadraticSolver() = default;
         QuadraticSolver(Float64 a,Float64 b,Float64 c);
         QuadraticSolver(const QuadraticSolver&) = default;
         
         ~QuadraticSolver() = default;

         QuadraticSolver& operator=(const QuadraticSolver&) = default;

         void SetCoefficients(Float64 a, Float64 b, Float64 c);
         void GetCoefficients(Float64* a, Float64* b, Float64* c) const;
         
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

         /// Solves the quadratic equation. Returns the number of roots found
         /// \param[out] x1 first root
         /// \param[out] x2 second root
         Uint8 Solve(Float64* x1, Float64* x2) const;

      private:
         Float64 m_A{0.0};
         Float64 m_B{0.0};
         Float64 m_C{0.0};

      #if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST
      };
   };
};
