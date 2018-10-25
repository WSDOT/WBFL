///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <Math\Function2d.h>
#include <MathEx.h>

/*****************************************************************************
CLASS 
   mathCompositeFunction2d

DESCRIPTION
   Objects of this class are function that is made of up several function with
   adjacent ranges. It evaluates as a single function.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.17.2010 : Created file
*****************************************************************************/

class MATHCLASS mathCompositeFunction2d : public mathFunction2d
{
public:
   mathCompositeFunction2d();
   mathCompositeFunction2d(const mathCompositeFunction2d&);
   mathCompositeFunction2d& operator=(const mathCompositeFunction2d&);
   virtual ~mathCompositeFunction2d();

   void AddFunction(Float64 xMin,Float64 xMax,mathFunction2d& func);
   IndexType GetFunctionCount() const;
   void GetFunction(IndexType idx,const mathFunction2d** ppFunc,Float64* pXMin,Float64* pXMax) const;

   virtual Float64 Evaluate(Float64 x) const;

   virtual mathFunction2d* Clone() const;

   virtual void Clear();

private:
   struct Segment
   {
      Float64 xMin,xMax;
      mathFunction2d* pFunc;
      Segment() { pFunc = NULL; }
      Segment(const Segment& other) { xMin = other.xMin; xMax = other.xMax; pFunc = other.pFunc->Clone(); }
      ~Segment() { delete pFunc; }
      Segment& operator=(const Segment& other) { xMin = other.xMin; xMax = other.xMax; delete pFunc; pFunc = other.pFunc->Clone(); return *this; }
      bool InRange(Float64 x) const { return ::InRange(xMin,x,xMax); }
      bool operator<(const Segment& other) const { return xMin < other.xMin; }
   };

   std::vector<Segment> m_Segments;
};
