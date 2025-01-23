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

#pragma once
#include <Math\Function.h>
#include <MathEx.h>

namespace WBFL
{
   namespace Math
   {
      /// Objects of this class are functions that is made of up several function with
      /// adjacent ranges. It evaluates as a single function.
      class MATHCLASS CompositeFunction : public Function
      {
      public:
         CompositeFunction() = default;
         CompositeFunction(const CompositeFunction&) = delete;
         CompositeFunction& operator=(const CompositeFunction&) = delete;
         virtual ~CompositeFunction() = default;

         /// Adds a function to the composite
         /// \param xMin minimum X value
         /// \param xMax maximum X value
         /// \param func The function. This function is cloned
         void AddFunction(Float64 xMin, Float64 xMax, const Function& func);
         void AddFunction(Float64 xMin, Float64 xMax, std::unique_ptr<Function>&& func);

         /// Returns the number of functions in this composite
         IndexType GetFunctionCount() const;

         /// Gets a function and its range limits
         const std::unique_ptr<Function>& GetFunction(IndexType idx,Float64* pXMin,Float64* pXMax) const;

         /// Adjust the range limits for a function
         void AdjustLimits(IndexType idx,Float64 xMin,Float64 xMax);

         virtual Float64 Evaluate(Float64 x) const override;

         virtual std::unique_ptr<Function> Clone() const override;

         /// Removes all functions from this composite
         void Clear();

      private:
         struct Segment
         {
            Segment(Float64 xMin,Float64 xMax,std::unique_ptr<Function>&& func) : xMin(xMin),xMax(xMax),pFunc(std::move(func)) {}
            bool InRange(Float64 x) const { return ::InRange(xMin,x,xMax); }
            bool operator<(const Segment& other) const { return xMin < other.xMin; }

            Float64 xMin, xMax;
            std::unique_ptr<Function> pFunc;
         };

         std::vector<Segment> m_Segments;
      };
   };
};
