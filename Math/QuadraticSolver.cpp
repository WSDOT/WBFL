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

#include <Math\MathLib.h>
#include <Math\QuadraticSolver.h>

using namespace WBFL::Math;

QuadraticSolver::QuadraticSolver(Float64 a,Float64 b,Float64 c)
{
   SetCoefficients(a, b, c);
}

void QuadraticSolver::SetCoefficients(Float64 a, Float64 b, Float64 c)
{
   m_A = a;
   m_B = b;
   m_C = c;
}

void QuadraticSolver::GetCoefficients(Float64* a, Float64* b, Float64* c) const
{
   *a = m_A;
   *b = m_B;
   *c = m_C;
}

void QuadraticSolver::SetA(Float64 a)
{
   m_A = a;
}

Float64 QuadraticSolver::GetA() const
{
   return m_A;
}

void QuadraticSolver::SetB(Float64 b)
{
   m_B = b;
}

Float64 QuadraticSolver::GetB() const
{
   return m_B;
}

void QuadraticSolver::SetC(Float64 c)
{
   m_C = c;
}

Float64 QuadraticSolver::GetC() const
{
   return m_C;
}

std::pair<std::optional<Float64>, std::optional<Float64>> QuadraticSolver::Solve() const
{
   Float64 a = m_A;
   Float64 b = m_B;
   Float64 c = m_C;

   std::optional<Float64> r1, r2;

   if (IsZero(a))
   {
      // the function is linear
      if (IsZero(b))
      {
         // the function is a horizontal line
         return { r1,r2 }; // no roots
      }
      else
      {
         // the function is a sloped line
         r1 = -c / b;
         return { r1,r2 }; // 1 roots
      }
   }

   Float64 K = b * b - 4.0 * a * c;

   if (K < 0)
      return { r1,r2 }; // no roots

   K = sqrt(K);

   r1 = (-b + K) / (2 * a);
   r2 = (-b - K) / (2 * a);

   return { r1,r2 };
}
