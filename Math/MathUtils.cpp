///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Math\MathLib.h>
#include <Math\MathUtils.h>

WBFL::Math::PolynomialFunction WBFL::Math::GenerateParabola(Float64 Sx, Float64 Ex, Float64 Vy, Float64 dy)
{
   PRECONDITION(Sx < Ex);
   Float64 Vx = (Sx + Ex) / 2.0;   // X ordinate of vertex
   Float64 SV2 = (Sx - Vx) * (Sx - Vx); // used many times

   // y = Ax^2 + Bx + C
   Float64 A = -Vy / SV2;
   Float64 B = 2 * Vy * Vx / SV2;
   Float64 C = Vy - Vy * Vx * Vx / SV2 + dy;

   std::vector<Float64> coefficients;
   coefficients.push_back(A);
   coefficients.push_back(B);
   coefficients.push_back(C);

   return WBFL::Math::PolynomialFunction(coefficients);
}

WBFL::Math::PolynomialFunction WBFL::Math::GenerateParabola1(Float64 x1, Float64 y1, Float64 x2, Float64 y2, Float64 slope)
{
   // slope is known at left end
   Float64 A = ((y2 - y1) - (x2 - x1) * slope) / ((x2 - x1) * (x2 - x1));
   Float64 B = slope - 2 * A * x1;
   Float64 C = y1 - A * x1 * x1 - B * x1;

   std::vector<Float64> coefficients;
   coefficients.push_back(A);
   coefficients.push_back(B);
   coefficients.push_back(C);

   return WBFL::Math::PolynomialFunction(coefficients);
}

WBFL::Math::PolynomialFunction WBFL::Math::GenerateParabola2(Float64 x1, Float64 y1, Float64 x2, Float64 y2, Float64 slope)
{
   // slope is known at right end
   Float64 A = -((y2 - y1) - (x2 - x1) * slope) / ((x2 - x1) * (x2 - x1));
   Float64 B = slope - 2 * A * x2;
   Float64 C = y1 - A * x1 * x1 - B * x1;

   std::vector<Float64> coefficients;
   coefficients.push_back(A);
   coefficients.push_back(B);
   coefficients.push_back(C);

   return WBFL::Math::PolynomialFunction(coefficients);
}

void WBFL::Math::GenerateReverseParabolas(Float64 x1, Float64 y1, Float64 x2, Float64 x3, Float64 y3, WBFL::Math::PolynomialFunction* pLeftParabola, WBFL::Math::PolynomialFunction* pRightParabola)
{
   Float64 y2 = (y3 * (x2 - x1) + y1 * (x3 - x2)) / (x3 - x1);

   *pLeftParabola = WBFL::Math::GenerateParabola1(x1, y1, x2, y2, 0.0);
   *pRightParabola = WBFL::Math::GenerateParabola2(x2, y2, x3, y3, 0.0);
}

WBFL::Math::LinearFunction WBFL::Math::GenerateLineFunc2dFromPoints(Float64 X1, Float64 Y1, Float64 X2, Float64 Y2)
{
   if (IsEqual(X1, X2))
   {
      THROW_FUNCTION(WBFL::Math::XFunction::Reason::Undefined);
   }

   Float64 slope = (Y2 - Y1) / (X2 - X1);
   Float64 intercept = Y1 - slope * X1;

   return WBFL::Math::LinearFunction(slope, intercept);
}

Float64 WBFL::Math::ZeroFunction::Evaluate(Float64 x) const
{
   return 0.0;
}

std::unique_ptr<WBFL::Math::Function> WBFL::Math::ZeroFunction::Clone() const
{
   return std::make_unique<WBFL::Math::ZeroFunction>();
}
