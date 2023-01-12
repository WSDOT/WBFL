///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2023  Washington State Department of Transportation
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

#pragma once

#include <Math\Polynomial2d.h>
#include <Math\LinFunc2d.h>
#include <Math\Function2d.h>
#include <MathEx.h>


/* //////////// Parabolas ////////////////////////

   Function to generate a parabola that has Y==0 at Sx and Ex and with a vertex at 
    x==(S+E)/2 with height Vy.


                 Y                 V
                 |                 * ---------------------------
                 |             *      *                      ^
                 |          *           *                    |
                 |        *               *                  |
                 |      *                  *                 |  Vy
                 |     *                    *                |
                 |    *                      *               v
             --------*------------------------*---------------------------- x
                 |  *S                        E*             ^
                 | *                            *            |  dy
                 |                                           v
             -------------------------------------------------------------- X
                 |
                 |
*/
inline mathPolynomial2d GenerateParabola(Float64 Sx,Float64 Ex,Float64 Vy,Float64 dy=0.0)
{
   ATLASSERT(Sx<Ex);
   Float64 Vx  = (Sx + Ex)/2.0;   // X ordinate of vertex
   Float64 SV2 = (Sx-Vx)*(Sx-Vx); // used many times

   // y = Ax^2 + Bx + C
   Float64 A = -Vy/SV2;
   Float64 B = 2*Vy*Vx/SV2;
   Float64 C = Vy - Vy*Vx*Vx/SV2 + dy;

   std::vector<Float64> coefficients;
   coefficients.push_back(A);
   coefficients.push_back(B);
   coefficients.push_back(C);

   return mathPolynomial2d(coefficients);
}

inline mathPolynomial2d GenerateParabola1(Float64 x1,Float64 y1,Float64 x2,Float64 y2,Float64 slope)
{
   // slope is known at left end
   Float64 A = ((y2-y1) - (x2-x1)*slope)/((x2-x1)*(x2-x1));
   Float64 B = slope - 2*A*x1;
   Float64 C = y1 - A*x1*x1 - B*x1;

   std::vector<Float64> coefficients;
   coefficients.push_back(A);
   coefficients.push_back(B);
   coefficients.push_back(C);

   return mathPolynomial2d(coefficients);
}

inline mathPolynomial2d GenerateParabola2(Float64 x1,Float64 y1,Float64 x2,Float64 y2,Float64 slope)
{
   // slope is known at right end
   Float64 A = -((y2-y1) - (x2-x1)*slope)/((x2-x1)*(x2-x1));
   Float64 B = slope - 2*A*x2;
   Float64 C = y1 - A*x1*x1 - B*x1;

   std::vector<Float64> coefficients;
   coefficients.push_back(A);
   coefficients.push_back(B);
   coefficients.push_back(C);

   return mathPolynomial2d(coefficients);
}

inline void GenerateReverseParabolas(Float64 x1,Float64 y1,Float64 x2,Float64 x3,Float64 y3,mathPolynomial2d* pLeftParabola,mathPolynomial2d* pRightParabola)
{
   Float64 y2 = (y3*(x2-x1) + y1*(x3-x2))/(x3 - x1);

   *pLeftParabola  = GenerateParabola1(x1,y1,x2,y2,0.0);
   *pRightParabola = GenerateParabola2(x2,y2,x3,y3,0.0);
}

/* //////////// Line ////////////////////////
* 
     Return a line from two points at (X1, Y1), (X2, Y2)

     NOTE: This will throw a mathXEvalError::Undefined if X1==X2 !!!

*/
inline mathLinFunc2d GenerateLineFunc2dFromPoints(Float64 X1,Float64 Y1,Float64 X2,Float64 Y2)
{
   if (IsEqual(X1,X2))
   {
      ATLASSERT(0);
      throw mathXEvalError::Undefined;
   }

   Float64 slope = (Y2 - Y1) / (X2 - X1);
   Float64 intercept = Y1 - slope * X1;

   return mathLinFunc2d(slope,intercept);
}


// Math function class that just returns zero
class ZeroFunction : public mathFunction2d
{
   virtual Float64 Evaluate(Float64 x) const
   {
      return 0.0;
   }

   virtual mathFunction2d* Clone() const
   {
      return new ZeroFunction();
   }
};
