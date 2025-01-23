///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <Math\CubicSolver.h>
#include <Math\QuadraticSolver.h>
#include <algorithm>
#include <functional>

using namespace WBFL::Math;

CubicSolver::CubicSolver(Float64 a,Float64 b,Float64 c,Float64 d) :
   m_A(a), m_B(b), m_C(c), m_D(d)
{
}

void CubicSolver::SetCoefficients(Float64 a, Float64 b, Float64 c, Float64 d)
{
   m_A = a;
   m_B = b;
   m_C = c;
   m_D = d;
}

void CubicSolver::GetCoefficients(Float64* a, Float64* b, Float64* c, Float64* d) const
{
   *a = m_A;
   *b = m_B;
   *c = m_C;
   *d = m_D;
}

void CubicSolver::SetA(Float64 a)
{
   m_A = a;
}

Float64 CubicSolver::GetA() const
{
   return m_A;
}

void CubicSolver::SetB(Float64 b)
{
   m_B = b;
}

Float64 CubicSolver::GetB() const
{
   return m_B;
}

void CubicSolver::SetC(Float64 c)
{
   m_C = c;
}

Float64 CubicSolver::GetC() const
{
   return m_C;
}

void CubicSolver::SetD(Float64 d)
{
   m_D = d;
}

Float64 CubicSolver::GetD() const
{
   return m_D;
}

std::vector<Float64> CubicSolver::Solve() const
{
   Float64 a = m_A;
   Float64 b = m_B;
   Float64 c = m_C;
   Float64 d = m_D;

   std::vector<Float64> roots;

   if (a == 0)
   {
      // function is a quadratic
      QuadraticSolver solver(b, c, d);
      roots = solver.Solve();
   }
   else  if (d == 0)
   {
      // one of the roots is zero. divide through by x and solve the quadratic
      QuadraticSolver solver(a, b, c);
      roots = solver.Solve();
      roots.push_back(0.0);
   }
   else
   {
      // I don't have a very good reference for this algorithm. It was 
      // taken from http://www.1728.com/cubic2.htm
      Float64 f = (3 * c / a - (b * b) / (a * a)) / 3;
      Float64 g = (2 * b * b * b / (a * a * a) - (9 * b * c / (a * a)) + (27 * d / a)) / 27;
      Float64 h = g * g / 4 + f * f * f / 27;

      if (IsZero(h) || h < 0)
      {
         if (IsZero(h) && IsZero(f) && IsZero(g))
         {
            // all roots are real and equal
            roots.push_back(-(d / a < 0 ? -pow(-d / a, 1. / 3.) : pow(d / a, 1. / 3.)));
         }
         else
         {
            // roots are real
            Float64 i = sqrt((g * g) / 4 - h);
            Float64 j = pow(i, 1. / 3.);
            Float64 k = acos(-(g / (2 * i)));
            Float64 l = -j;
            Float64 m = cos(k / 3);
            Float64 n = sqrt(3.) * sin(k / 3);
            Float64 p = -b / (3 * a);
            Float64 x1 = 2 * j * cos(k / 3) + p;
            Float64 x2 = l * (m + n) + p;
            Float64 x3 = l * (m - n) + p;

            // if h = 0, then two of the roots are the same
            if (IsZero(h))
            {
               // 2 roots are the same, eliminate the redundant root
               if (IsEqual(x1, x2))
               {
                  // roots 1 and 2 are the same so roots 1 and 3 are unique
                  roots.push_back(x1);
                  roots.push_back(x3);
               }
               else if (IsEqual(x2, x3) || IsEqual(x1,x3))
               {
                  // roots 2 and 3 or 1 and 3 are the same so roots 1 and 2 are unique
                  roots.push_back(x1);
                  roots.push_back(x2);
               }
            }
            else
            {
               // all roots are unique
               roots.push_back(x1);
               roots.push_back(x2);
               roots.push_back(x3);
            }
         }
      }
      else /*if ( 0 < h )*/
      {
         // only 1 real root
         assert(0 < h);
         Float64 r = -g / 2 + sqrt(h);
         Float64 s = (r < 0 ? -pow(-r, 1. / 3.) : pow(r, 1. / 3.));
         Float64 t = -g / 2 - sqrt(h);
         Float64 u = (t < 0 ? -pow(-t, 1. / 3.) : pow(t, 1. / 3.));
         roots.push_back( (s + u) - b / (3 * a) );
      }
   }

   std::sort(roots.begin(), roots.end());
   return roots;
}
