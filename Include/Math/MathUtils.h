///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Math\MathExp.h>
#include <Math\PolynomialFunction.h>
#include <Math\LinearFunction.h>
#include <Math\Function.h>
#include <Math\XFunction.h>
#include <MathEx.h>
#include <WBFLDebug.h>

namespace WBFL
{
   namespace Math
   {

      /// Function to generate a parabola that has Y==0 at Sx and Ex and with a vertex at 
      /// x==(S+E)/2 with height Vy.
      ///
      ///
      ///              Y                 V
      ///              |                 * ---------------------------
      ///              |             *      *                      ^
      ///              |          *           *                    |
      ///              |        *               *                  |
      ///              |      *                  *                 |  Vy
      ///              |     *                    *                |
      ///              |    *                      *               v
      ///          --------*------------------------*---------------------------- x
      ///              |  *S                        E*             ^
      ///              | *                            *            |  dy
      ///              |                                           v
      ///          -------------------------------------------------------------- X
      ///              |
      ///              |

      MATHFUNC PolynomialFunction GenerateParabola(Float64 Sx, Float64 Ex, Float64 Vy, Float64 dy = 0.0);

      /// Create a parabola with a known slope at the left end and zero slope at the right end
      MATHFUNC PolynomialFunction GenerateParabola1(Float64 x1, Float64 y1, Float64 x2, Float64 y2, Float64 slope);

      /// Create a parabola with a known slope at the right end and zero slope at the left end
      MATHFUNC PolynomialFunction GenerateParabola2(Float64 x1, Float64 y1, Float64 x2, Float64 y2, Float64 slope);

      /// Create reverse parabolas
      MATHFUNC void GenerateReverseParabolas(Float64 x1, Float64 y1, Float64 x2, Float64 x3, Float64 y3, WBFL::Math::PolynomialFunction* pLeftParabola, WBFL::Math::PolynomialFunction* pRightParabola);

      /// Create a LinearFunction from two points at (X1, Y1), (X2, Y2)
      MATHFUNC LinearFunction GenerateLineFunc2dFromPoints(Float64 X1, Float64 Y1, Float64 X2, Float64 Y2);

      /// Math function class that just returns zero
      class MATHCLASS ZeroFunction : public Function
      {
      public:
         virtual Float64 Evaluate(Float64 x) const override;
         virtual std::unique_ptr<WBFL::Math::Function> Clone() const override;
      };
   };
};
