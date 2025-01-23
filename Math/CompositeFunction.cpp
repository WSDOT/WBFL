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
#include <Math\CompositeFunction.h>
#include <Math\XFunction.h>
#include <algorithm>

using namespace WBFL::Math;

void CompositeFunction::AddFunction(Float64 xMin,Float64 xMax,const Function& func)
{
   m_Segments.emplace_back(xMin, xMax, func.Clone());
   std::sort(m_Segments.begin(), m_Segments.end());
}

void CompositeFunction::AddFunction(Float64 xMin, Float64 xMax, std::unique_ptr<Function>&& func)
{
   m_Segments.emplace_back(xMin, xMax, std::move(func));
   std::sort(m_Segments.begin(), m_Segments.end());
}

IndexType CompositeFunction::GetFunctionCount() const
{
   return m_Segments.size();
}

const std::unique_ptr<Function>& CompositeFunction::GetFunction(IndexType idx,Float64* pXMin,Float64* pXMax) const
{
   const Segment& segment = m_Segments[idx];
   *pXMax = segment.xMax;
   *pXMin = segment.xMin;
   return segment.pFunc;
}

void CompositeFunction::AdjustLimits(IndexType idx,Float64 xMin,Float64 xMax)
{
   Segment& segment = m_Segments[idx];
   segment.xMin = xMin;
   segment.xMax = xMax;
   std::sort(m_Segments.begin(), m_Segments.end());
}

Float64 CompositeFunction::Evaluate(Float64 x) const
{
   for(const Segment& segment : m_Segments)
   {
      if ( segment.InRange(x) )
      {
         return segment.pFunc->Evaluate(x);
      }
   }

   // function is undefined at x
   CHECK(false); // hmmm?
   THROW_FUNCTION(XFunction::Reason::Undefined);
}

std::unique_ptr<Function> CompositeFunction::Clone() const
{
   std::unique_ptr<CompositeFunction> clone(std::make_unique<CompositeFunction>());
   for (const Segment& segment : m_Segments)
   {
      clone->AddFunction(segment.xMin, segment.xMax, segment.pFunc->Clone());
   }
   return clone;
}

void CompositeFunction::Clear()
{
   m_Segments.clear();
}
