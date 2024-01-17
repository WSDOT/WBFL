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
#include <System\Exception.h>

namespace WBFL
{
   namespace Math
   {
      /// Defines an abstract interface for a continuous single variable, single value function.
      class MATHCLASS Function
      {
      public:
         Function() = default;
         Function(const Function&) = default;
         virtual ~Function() = default;

         Function& operator=(const Function&) = default;

         /// Evaluates the function at x.  If an error occurs during the evaluation,
         /// a XFunctionError exception will be thrown.
         virtual Float64 Evaluate(Float64 x) const = 0;

         /// Creates a clone of the function object
         virtual std::unique_ptr<Function> Clone() const = 0;
      };
   };
};
