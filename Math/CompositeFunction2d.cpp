///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <Math\CompositeFunction2d.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

mathCompositeFunction2d::mathCompositeFunction2d()
{
}

mathCompositeFunction2d::mathCompositeFunction2d(const mathCompositeFunction2d& other)
{
   *this = other;
}

mathCompositeFunction2d& mathCompositeFunction2d::operator=(const mathCompositeFunction2d& other)
{
   m_Segments.clear();
   m_Segments = other.m_Segments;
   return *this;
}

mathCompositeFunction2d::~mathCompositeFunction2d()
{
}

void mathCompositeFunction2d::AddFunction(Float64 xMin,Float64 xMax,mathFunction2d& func)
{
   Segment segment;
   segment.xMin = xMin;
   segment.xMax = xMax;
   segment.pFunc = func.Clone();

   m_Segments.push_back(segment);
   std::sort(m_Segments.begin(), m_Segments.end());
}

IndexType mathCompositeFunction2d::GetFunctionCount() const
{
   return m_Segments.size();
}

void mathCompositeFunction2d::GetFunction(IndexType idx,const mathFunction2d** ppFunc,Float64* pXMin,Float64* pXMax) const
{
   const Segment& segment = m_Segments[idx];
   *ppFunc = segment.pFunc;
   *pXMax = segment.xMax;
   *pXMin = segment.xMin;
}

void mathCompositeFunction2d::AdjustLimits(IndexType idx,Float64 xMin,Float64 xMax)
{
   Segment& segment = m_Segments[idx];
   segment.xMin = xMin;
   segment.xMax = xMax;
   std::sort(m_Segments.begin(), m_Segments.end());
}

Float64 mathCompositeFunction2d::Evaluate(Float64 x) const
{
   std::vector<Segment>::const_iterator iter(m_Segments.begin());
   std::vector<Segment>::const_iterator iterEnd(m_Segments.end());
   for ( ; iter != iterEnd; iter++ )
   {
      const Segment& segment = *iter;
      if ( segment.InRange(x) )
      {
         return segment.pFunc->Evaluate(x);
      }
   }

   // function is undefined at x
   ASSERT(false); // hmmm?
   throw new mathXEvalError(mathXEvalError::Undefined,_T(__FILE__),__LINE__);
}

mathFunction2d* mathCompositeFunction2d::Clone() const
{
   return new mathCompositeFunction2d(*this);
}

void mathCompositeFunction2d::Clear()
{
   m_Segments.clear();
}