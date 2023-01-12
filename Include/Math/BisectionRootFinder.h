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
#include <Math\RootFinder.h>

namespace WBFL
{
   namespace Math
   {
      /// This class implements Bisection method for finding a root of a function when
      /// derivatives of the function are not known.
      class MATHCLASS BisectionRootFinder : public RootFinder
      {
      public:
         BisectionRootFinder() = default;
         virtual ~BisectionRootFinder() = default;

         virtual Float64 FindRootInRange(const Function& f,Float64 xMin,Float64 xMax,Float64 tol) const override;
         virtual Float64 FindRootInRange(const std::function<Float64(Float64)>& f, Float64 xMin, Float64 xMax, Float64 tol) const override;

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST
      };
   };
};
