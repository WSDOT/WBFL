///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 2003  Washington State Department of Transportation
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

#ifndef INCLUDED_MATHEX_H_
#define INCLUDED_MATHEX_H_

#pragma once

#include <WBFLTypes.h>
#include <math.h>
#include <assert.h>
#include <xutility>

#if !defined TOLERANCE
#define TOLERANCE 0.00001
#endif // TOLERANCE

// Returns true if value is within tolerance of zero
template <class T>
inline bool IsZero(const T& value, T tolerance = TOLERANCE)
{   return (-tolerance <= value && value <= tolerance);   }

// Returns true if val1 and val2 are equal within the supplied tolerance. 
// Useful when comparing non-geometric values
template <class T>
inline bool IsEqual(const T& val1, const T& val2, T tolerance = TOLERANCE)
{   return IsZero(val1-val2,tolerance); }

inline bool IsEqual(IndexType v1,IndexType v2)
{ return v1 == v2; }

// Returns true if value is within the range [minVal,maxVal]
template <class T>
inline bool InRange(const T& minVal, const T& value, const T& maxVal, T tolerance = TOLERANCE)
{   return (minVal < value) && (value < maxVal) ||
           IsEqual(minVal, value, tolerance) || IsEqual(value, maxVal, tolerance);  }

// Returns true if value is less than or equal to the threshold value
template <class T>
inline bool IsLE(const T& value, const T& threshold, T tolerance = TOLERANCE)
{   return (value < (threshold + tolerance)); }

// Returns true if value is less than the threshold value
template <class T>
inline bool IsLT(const T& value, const T& threshold, T tolerance = TOLERANCE)
{   return (value < threshold && !IsEqual(value,threshold,tolerance)); }

// Returns true if value is greater than the threshold value
template <class T>
inline bool IsGT(const T& threshold,const T& value, T tolerance = TOLERANCE)
{   return (threshold < value && !IsEqual(value,threshold,tolerance)); }

// Returns true if value is greater than or equal to the threshold value
template <class T>
inline bool IsGE(const T& threshold, const T& value, T tolerance = TOLERANCE)
{   return ((threshold - tolerance) < value); }

// Returns true if the Float64s val1 and val2 are within the given tolerance along the number line
inline bool IsNearby(Float64 val1, Float64 val2, Float64 tolerance = TOLERANCE)
{   
   assert(0.0 <= tolerance);
   return fabs(val1-val2)<=tolerance;
}

// Round a to the nearest integer value.
template <class T>
inline T Round(const T& a)
{
   Float64 i;
   if (0.5 <= modf(a,&i))
      return 0 <= a ? ceil(a) : floor(a);
   else
      return a < 0 ? ceil(a) : floor(a);
}

// Round a to the specified accurarcy.
inline Float64 RoundOff(const Float64& a,Float64 accuracy)
{
   assert(0.0 < accuracy);
   Float64 i;
   if ( 0 <= a )
   {
      modf(a/accuracy+0.5,&i);
      return i*accuracy;
   }
   else
   {
      modf(0.5-a/accuracy,&i);
      i *= -accuracy;
      return IsZero(i) ? 0 : i;
   }
}
// Floor a to the specified accurarcy.
inline Float64 FloorOff(const Float64& a,Float64 accuracy)
{
   assert(0.0 < accuracy);
   Float64 tst = (Float64)((long)(a/accuracy)*accuracy);
   if (tst==a)
      return a;
   else if (a>=0)
      return tst;
   else
      return (Float64)((long)(a/accuracy-1)*accuracy);
}

// Ceil a to the specified accurarcy.
inline Float64 CeilOff(const Float64& a,Float64 accuracy)
{
   assert(0.0 < accuracy);
   Float64 tst = (Float64)((long)(a/accuracy)*accuracy);
   if (tst==a)
      return a;
   else if (a>0)
      return (Float64)((long)(a/accuracy+1)*accuracy);
   else
      return tst;
}

// Returns the sign of a,  either -1, 0, or 1
template <class T>
inline int Sign(const T& a)
{
   return int( a < 0 ? -1 : a > 0 ? 1 : 0 );
}

// Returns the binary sign of a, either -1, or 1 if a >= 0
template <class T>
inline int BinarySign(const T& a)
{
   return int( a < 0 ? -1 : 1 );
}

// Linear interpolation from l to h. delta is the distance between l and h
// a is the interpolation distance from l.
template <class H,class V>
inline V LinInterp( const H& a, const V& l,const V& h, const H& delta)
{
   if ( delta == 0 )
      return l;
   else
      return l + (h-l)*(V)a/(V)delta;
}

// Forces v into the range [l,h]
template <class T>
inline T ForceIntoRange(const T& l,const T& v,const T& h)
{
   return v <= l ? l : v >= h ? h : v;
}

// Returns the maximum value
template <class T>
inline T Max(const T& a,const T& b)
{
   return _cpp_max(a,b);
}

// Returns the index of the maximum values
template <class T>
inline long MaxIndex(const T& a,const T& b)
{
   T value = Max(a,b);
   if ( IsEqual(a,value) )
      return 0;

   return 1;
}

// Returns the minimum value
template <class T>
inline T Min(const T& a,const T& b)
{
   return _cpp_min(a,b);
}

// Returns the index of the minimum values
template <class T>
inline long MinIndex(const T& a,const T& b)
{
   T value = Min(a,b);
   if ( IsEqual(a,value) )
      return 0;

   return 1;
}

// Returns the maximum value
template <class T>
inline T Max(const T& a,const T& b, const T& c)
{
   return Max(Max(a,b),c);
}

// Returns the index of the maximum value
template <class T>
inline long MaxIndex(const T& a,const T& b, const T& c)
{
   T value = Max(a,b,c);
   if ( IsEqual(a,value) )
      return 0;

   if ( IsEqual(b,value) )
      return 1;

   return 2;
}

// Returns the minimum value
template <class T>
inline T Min(const T& a,const T& b, const T& c)
{
   return Min(Min(a,b),c);
}

// Returns the index of the minimum value
template <class T>
inline long MinIndex(const T& a,const T& b, const T& c)
{
   T value = Min(a,b,c);
   if ( IsEqual(a,value) )
      return 0;

   if ( IsEqual(b,value) )
      return 1;

   return 2;
}

// Returns the maximum value
template <class T>
inline T Max(const T& a,const T& b, const T& c, const T& d)
{
   return Max(Max(a,b),Max(c,d));
}

// Returns the index of the maximum value
template <class T>
inline long MaxIndex(const T& a,const T& b, const T& c, const T& d)
{
   T value = Max(a,b,c,d);
   if ( IsEqual(a,value) )
      return 0;

   if ( IsEqual(b,value) )
      return 1;

   if ( IsEqual(c,value) )
      return 2;

   return 3;
}

// Returns the minimum value
template <class T>
inline T Min(const T& a,const T& b, const T& c, const T& d)
{
   return Min(Min(a,b),Min(c,d));
}

// Returns the index of the minimum value
template <class T>
inline long MinIndex(const T& a,const T& b, const T& c, const T& d)
{
   T value = Min(a,b,c,d);
   if ( IsEqual(a,value) )
      return 0;

   if ( IsEqual(b,value) )
      return 1;

   if ( IsEqual(c,value) )
      return 2;

   return 3;
}

// Difference between an approximate value and an exact value
template <class T>
inline T PercentError(const T& approx,const T& exact)
{
   if (exact == 0)
      return 0;

   return (fabs(approx-exact)/exact)*(T)100;
}

// Compares an "old" value to a "new" value
template <class T>
inline T PercentChange(const T& a,const T& b)
{
   if ( a == 0 )
      return 0;

   return ((b-a)/a)*(T)100;
}

// The difference between town values divided by the average of the two
// values, as a percentage. Use when both values mean the same kind of thing
// and neither value is more signifant that the other.
template <class T>
inline T PercentDifference(const T& a,const T& b)
{
   if ( IsZero(a+b) )
      return 0;

   return ((fabs(a-b)/((a+b)/2)))*(T)100;
}

// returns true if value is an even number
template <class T>
inline bool IsEven(const T& value) { return value % 2 == 0; }

// returns true if value is an odd number
template <class T>
inline bool IsOdd(const T& value) { return !IsEven(value); }

#undef  M_PI
#define M_PI        3.1415926535897932384626433832795

#undef  TWO_PI
#define TWO_PI      6.28318530717958647692528676655901

#undef  PI_OVER_2
#define PI_OVER_2   1.57079632679489661923132169163975

inline Float64 ToRadians(Float64 deg) { return deg*M_PI/180.; }
inline Float64 ToDegrees(Float64 rad) { return rad*180./M_PI; }

#endif // INCLUDED_MATHEX_H_
