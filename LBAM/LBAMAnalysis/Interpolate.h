///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2022  Washington State Department of Transportation
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

#if !defined INCLUDED_INTERPOLATE_H_
#define INCLUDED_INTERPOLATE_H_

#include <MathEx.h>

inline Float64 InterpolateZeroLocation(Float64 xStart, Float64 xEnd, Float64 yStart, Float64 yEnd)
{
   ATLASSERT(IsLE(xStart,xEnd));
   ATLASSERT( (yStart>=0 && yEnd<=0) || (yStart<=0 && yEnd>=0)); // y values must have different signs

   Float64 slope = (yEnd-yStart)/(xEnd-xStart);
   Float64 loc = xStart - yStart/slope;

   ATLASSERT(loc>=xStart && loc <=xEnd);

   return loc;
}

inline Float64 InterpolateTrapezoid(Float64 x, Float64 xStart, Float64 xEnd, Float64 yStart, Float64 yEnd)
{
   ATLASSERT(xEnd>xStart);
   ATLASSERT(x>=xStart);
   ATLASSERT(x<=xEnd);

   Float64 ord = yEnd-yStart;
   if (ord==0.0)
   {
      return yEnd;
   }
   else
   {
      Float64 slope = ord/(xEnd-xStart);
      return yStart + slope*(x-xStart);
   }
}

enum LineAttitude {trpCrossingUpward, trpPositive, trpCrossingDownward, trpNegative, trpZero};

// function gets attitude of line segment wrt y=zero and returns intersection if it crosses zero
inline LineAttitude GetLineSegmentAttitude(Float64 xStart, Float64 yStart, Float64 xEnd, Float64 yEnd, 
                                           Float64* xIntersectZero,  Float64 zeroTolerance=1.0e-6)
{
   ATLASSERT(IsLE(xStart,xEnd));

   // start testing y values
   if ( IsZero(yStart, zeroTolerance) )
   {
      if ( IsZero(yEnd, zeroTolerance) )
      {
         return trpZero;
      }
      else if (yEnd>0.0)
      {
         *xIntersectZero = xStart;
         return trpCrossingUpward;
      }
      else
      {
         *xIntersectZero = xStart;
         return trpCrossingDownward;
      }
   }
   else if (yStart > 0.0)
   {
      if (IsZero(yEnd, zeroTolerance) )
      {
         // crossing downward to zero
         *xIntersectZero = xEnd;
         return trpCrossingDownward;
      }
      if (yEnd > 0.0)
      {
        return trpPositive;
      }
      else
      {
         // crossing downward through zero
         if (IsEqual(xStart,xEnd))
         {
            *xIntersectZero = xEnd;
         }
         else
         {
            *xIntersectZero = InterpolateZeroLocation(xStart, xEnd, yStart, yEnd);
         }

         return trpCrossingDownward;
      }
   }
   else  // (yStart<0.0) 
   {
      if ( IsZero(yEnd, zeroTolerance) )
      {
         // crossing downward to zero
         *xIntersectZero = xEnd;
         return trpCrossingUpward;
      }
      if (yEnd < 0.0)
      {
        return trpNegative;
      }
      else
      {
         // crossing upward through zero
         if (IsEqual(xStart,xEnd))
         {
            *xIntersectZero = xEnd;
         }
         else
         {
            *xIntersectZero = InterpolateZeroLocation(xStart, xEnd, yStart, yEnd);
         }

         return trpCrossingUpward;
      }
   }
}

inline Float64 TrapezoidArea(Float64 xStart, Float64 xEnd, Float64 yStart, Float64 yEnd)
{
   return (xEnd-xStart) * (yStart+yEnd)/2.0;
}


#endif 