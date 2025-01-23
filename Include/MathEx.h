///////////////////////////////////////////////////////////////////////
// WBFL - Washington Bridge Foundation Libraries
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <WBFLTypes.h>
#include <math.h>
#include <cmath>
#include <cassert>
#include <xutility>
#include <limits>

#if (202002L <= _MSVC_LANG )
#include <numbers>
#endif

#if !defined TOLERANCE
#define TOLERANCE 0.00001
#endif // TOLERANCE

/// Returns true if value is within tolerance of zero
template <class T>
inline bool IsZero(const T& value, T tolerance = TOLERANCE)
{   return (-tolerance <= value && value <= tolerance);   }

/// Returns true if val1 and val2 are equal within the supplied tolerance. 
/// Useful when comparing non-geometric values
template <class T>
inline bool IsEqual(const T& val1, const T& val2, T tolerance = TOLERANCE)
{   return IsZero(val1-val2,tolerance); }

inline bool IsEqual(IndexType v1, IndexType v2)
{
   return v1 == v2;
}

/// Returns true if value is within the range [minVal,maxVal]
template <class T>
inline bool InRange(const T& minVal, const T& value, const T& maxVal, T tolerance = TOLERANCE)
{   return (minVal < value) && (value < maxVal) ||
           IsEqual(minVal, value, tolerance) || IsEqual(value, maxVal, tolerance);  }

/// Returns true if value is less than or equal to the threshold value
template <class T>
inline bool IsLE(const T& value, const T& threshold, T tolerance = TOLERANCE)
{   return (value < (threshold + tolerance)); }

/// Returns true if value is less than the threshold value
template <class T>
inline bool IsLT(const T& value, const T& threshold, T tolerance = TOLERANCE)
{   return (value < threshold && !IsEqual(value,threshold,tolerance)); }

/// Returns true if value is greater than the threshold value
template <class T>
inline bool IsGT(const T& threshold,const T& value, T tolerance = TOLERANCE)
{   return (threshold < value && !IsEqual(value,threshold,tolerance)); }

/// Returns true if value is greater than or equal to the threshold value
template <class T>
inline bool IsGE(const T& threshold, const T& value, T tolerance = TOLERANCE)
{   return ((threshold - tolerance) < value); }

/// Returns true if the Float64s val1 and val2 are within the given tolerance along the number line
inline bool IsNearby(Float64 val1, Float64 val2, Float64 tolerance = TOLERANCE)
{   
   assert(0.0 <= tolerance);
   return fabs(val1-val2)<=tolerance;
}

/// Round a to the nearest integer value.
template <class T>
inline T Round(const T& a)
{
   Float64 i;
   if (0.5 <= modf(a,&i))
      return 0 <= a ? ceil(a) : floor(a);
   else
      return a < 0 ? ceil(a) : floor(a);
}

/// Round a to the specified accuracy.
inline Float64 RoundOff(const Float64& a,Float64 accuracy)
{
   assert(0.0 < accuracy);
   if (a == Float64_Max || a == Float64_Inf)
   {
      return a;
   }

   Float64 i;
   if ( 0 <= a )
   {
      Float64 n = modf(a/accuracy+0.5,&i);
      return i*accuracy;
   }
   else
   {
      Float64 n = modf(0.5-a/accuracy,&i);
      i *= -accuracy;
      return IsZero(i) ? 0 : i;
   }
}

/// Floor a to the specified multiple.
inline Float64 FloorOff(const Float64& a,Float64 multiple)
{
   assert(0.0 < multiple);
   if (a == Float64_Max || a == Float64_Inf)
   {
      return a;
   }

   Float64 tst = (Float64)((long)(a/multiple)*multiple);
   if (tst == a)
   {
      return a;
   }
   else if (0 <= a)
   {
      return tst;
   }
   else
   {
      return (Float64)((long)(a / multiple - 1)*multiple);
   }
}

/// Floor a to the specified multiple with a tolerance
inline Float64 FloorOffTol(const Float64& a,Float64 multiple, Float64 tolerance = TOLERANCE)
{
   assert(0.0 < multiple);
   if (a == Float64_Max || a == Float64_Inf)
   {
      return a;
   }

   Float64 tst = (Float64)((long)(a/multiple)*multiple);
   if (IsEqual(tst, a, tolerance))
   {
      return a;
   }
   else if (0 <= a)
   {
      return tst;
   }
   else
   {
      return (Float64)((long)(a / multiple - 1)*multiple);
   }
}

/// Ceiling a to the specified multiple.
inline Float64 CeilOff(const Float64& a,Float64 multiple)
{
   assert(0.0 < multiple);
   if (a == Float64_Max || a == Float64_Inf)
   {
      return a;
   }

   Float64 tst = (Float64)((long)(a/multiple)*multiple);
   if (tst == a)
   {
      return a;
   }
   else if (0 < a)
   {
      return (Float64)((long)(a / multiple + 1)*multiple);
   }
   else
   {
      return tst;
   }
}

/// Ceiling a to the specified multiple within a tolerance
inline Float64 CeilOffTol(const Float64& a,Float64 multiple, Float64 tolerance = TOLERANCE)
{
   assert(0.0 < multiple);
   if (a == Float64_Max || a == Float64_Inf)
   {
      return a;
   }

   Float64 tst = (Float64)((long)(a/multiple)*multiple);
   if (IsEqual(tst, a, tolerance))
   {
      return a;
   }
   else if (0 < a)
   {
      return (Float64)((long)(a / multiple + 1)*multiple);
   }
   else
   {
      return tst;
   }
}

/// Returns the sign of a,  either -1, 0, or 1
template <class T>
inline int Sign(const T& a)
{
   return int( a < 0 ? -1 : a > 0 ? 1 : 0 );
}

/// Returns the binary sign of a, either -1, or 1 if a >= 0
template <class T>
inline int BinarySign(const T& a)
{
   return int( a < 0 ? -1 : 1 );
}

/// Linear interpolation from l to h. delta is the distance between l and h
/// a is the interpolation distance from l.
template <class H,class V>
inline V LinInterp( const H& a, const V& l,const V& h, const H& delta)
{
   if (delta == 0)
   {
      return l;
   }
   else
   {
#if (202002L <= _MSVC_LANG)
      auto t = a / delta;
      return std::lerp(l, h, t);
#else
      return l + (h - l) * (V)a / (V)delta;
#endif
   }
}

/// Linear interpolation using line analogy. Return Y(x) along a line defined by the points (x1, y1), (x2, y2)
template <typename T>
inline T LinInterpLine(const T& x1, const T& y1, const T& x2, const T& y2, const T& x)
{
   auto dX = x - x1;
   auto deltaY = y2 - y1;
   auto deltaX = x2 - x1;
   if (deltaX == 0)
   {
      if (dX == 0)
      {
         return y1;
      }
      else
      {
         assert(false);
         return std::numeric_limits<T>::infinity(); // No Solution. For lack of better option
      }
   }
   else if (deltaY==0)
   {
      return y1;
   }
   else
   {
      return y1 + dX * deltaY / deltaX;
   }
}

#if (_MSVC_LANG < 202002L)
namespace std
{
   inline Float64 midpoint(Float64 a, Float64 b) { return a + (b - a) / 2; }
};
#endif

/// Forces v into the range [l,h]
template <class T>
inline T ForceIntoRange(const T& l,const T& v,const T& h)
{
   return v <= l ? l : v >= h ? h : v;
}

/// Returns the maximum value
template <class T>
inline T Max(const T& a,const T& b)
{
   return max(a,b);
}

/// Returns the index of the maximum values
template <class T>
inline IndexType MaxIndex(const T& a,const T& b)
{
   T value = Max(a,b);
   if ( IsEqual(a,value) )
      return 0;

   return 1;
}

/// Returns the minimum value
template <class T>
inline T Min(const T& a,const T& b)
{
   return min(a,b);
}

/// Returns the index of the minimum values
template <class T>
inline IndexType MinIndex(const T& a,const T& b)
{
   T value = Min(a,b);
   if ( IsEqual(a,value) )
      return 0;

   return 1;
}

/// Returns the maximum value
template <class T>
inline T Max(const T& a,const T& b, const T& c)
{
   return Max(Max(a,b),c);
}

/// Returns the index of the maximum value
template <class T>
inline IndexType MaxIndex(const T& a,const T& b, const T& c)
{
   T value = Max(a,b,c);
   if ( IsEqual(a,value) )
      return 0;

   if ( IsEqual(b,value) )
      return 1;

   return 2;
}

/// Returns the minimum value
template <class T>
inline T Min(const T& a,const T& b, const T& c)
{
   return Min(Min(a,b),c);
}

/// Returns the index of the minimum value
template <class T>
inline IndexType MinIndex(const T& a,const T& b, const T& c)
{
   T value = Min(a,b,c);
   if ( IsEqual(a,value) )
      return 0;

   if ( IsEqual(b,value) )
      return 1;

   return 2;
}

/// Returns the maximum value
template <class T>
inline T Max(const T& a,const T& b, const T& c, const T& d)
{
   return Max(Max(a,b),Max(c,d));
}

/// Returns the index of the maximum value
template <class T>
inline IndexType MaxIndex(const T& a,const T& b, const T& c, const T& d)
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

/// Returns the minimum value
template <class T>
inline T Min(const T& a,const T& b, const T& c, const T& d)
{
   return Min(Min(a,b),Min(c,d));
}

/// Returns the index of the minimum value
template <class T>
inline IndexType MinIndex(const T& a,const T& b, const T& c, const T& d)
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

/// Returns the value with the greatest magnitude
template <class T>
inline T MaxMagnitude(const T& a,const T& b)
{
   // want the value with the greatest magnitude, but we want to retain the sign
   return (fabs(b) < fabs(a) ? a : b);
}

/// Returns the value with the greatest magnitude
template <class T>
inline T MaxMagnitude(const T& a,const T& b,const T& c)
{
   // want the value with the greatest magnitude, but we want to retain the sign
   return MaxMagnitude(MaxMagnitude(a,b),c);
}

/// Returns the value with the greatest magnitude
template <class T>
inline T MaxMagnitude(const T& a,const T& b,const T& c,const T& d)
{
   // want the value with the greatest magnitude, but we want to retain the sign
   return MaxMagnitude(MaxMagnitude(a,b),MaxMagnitude(c,d));
}


/// Returns the index of the value with the greatest magnitude
template <class T>
inline IndexType MaxMagnitudeIndex(const T& a,const T& b)
{
   // want the value with the greatest magnitude, but we want to retain the sign
   return (fabs(b) < fabs(a) ? 0 : 1);
}

/// Returns the index of the value with the greatest magnitude
template <class T>
inline IndexType MaxMagnitudeIndex(const T& a,const T& b,const T& c)
{
   // want the value with the greatest magnitude, but we want to retain the sign
   return MaxMagnitudeIndex((T)MaxMagnitudeIndex(a,b),c);
}

/// Returns the index of the value with the greatest magnitude
template <class T>
inline IndexType MaxMagnitudeIndex(const T& a,const T& b,const T& c,const T& d)
{
   // want the value with the greatest magnitude, but we want to retain the sign
   return MaxMagnitudeIndex((T)MaxMagnitudeIndex(a,b),(T)MaxMagnitudeIndex(c,d));
}

/// Returns the value with the least magnitude
template <class T>
inline T MinMagnitude(const T& a,const T& b)
{
   // want the value with the smallest magnitude, but we want to retain the sign
   return (fabs(b) < fabs(a) ? b : a);
}

/// Returns the value with the least magnitude
template <class T>
inline T MinMagnitude(const T& a,const T& b,const T& c)
{
   // want the value with the smallest magnitude, but we want to retain the sign
   return MinMagnitude(MinMagnitude(a,b),c);
}

/// Returns the value with the least magnitude
template <class T>
inline T MinMagnitude(const T& a,const T& b,const T& c,const T& d)
{
   // want the value with the smallest magnitude, but we want to retain the sign
   return MinMagnitude(MinMagnitude(a,b),MinMagnitude(c,d));
}

/// Returns the index of the value with the least magnitude
template <class T>
inline IndexType MinMagnitudeIndex(const T& a,const T& b)
{
   // want the value with the smallest magnitude, but we want to retain the sign
   return (fabs(b) < fabs(a) ? 1 : 0);
}

/// Returns the index of the value with the least magnitude
template <class T>
inline IndexType MinMagnitudeIndex(const T& a,const T& b,const T& c)
{
   // want the value with the smallest magnitude, but we want to retain the sign
   return MinMagnitudeIndex((T)MinMagnitudeIndex(a,b),c);
}

/// Returns the index of the value with the least magnitude
template <class T>
inline IndexType MinMagnitudeIndex(const T& a,const T& b,const T& c,const T& d)
{
   // want the value with the smallest magnitude, but we want to retain the sign
   return MinMagnitudeIndex((T)MinMagnitudeIndex(a,b),(T)MinMagnitudeIndex(c,d));
}

/// Computes percent error defined as the difference between an approximate value and an exact value
template <class T>
inline T PercentError(const T& approx,const T& exact)
{
   if (exact == 0)
      return 0;

   return (fabs(approx-exact)/exact)*(T)100;
}

/// Compares percent change defined as the difference between an "old" value to a "new" value
template <class T>
inline T PercentChange(const T& a,const T& b)
{
   if ( a == 0 )
      return 0;

   return ((b-a)/a)*(T)100;
}

/// The difference between two values divided by the average of the two
/// values, as a percentage. Use when both values mean the same kind of thing
/// and neither value is more significant that the other.
template <class T>
inline T PercentDifference(const T& a,const T& b)
{
   if ( IsZero(a+b) )
      return 0;

   return ((fabs(a-b)/((a+b)/2)))*(T)100;
}

/// returns true if value is an even number
template <class T>
inline bool IsEven(const T& value) { return value % 2 == 0; }

/// returns true if value is an odd number
template <class T>
inline bool IsOdd(const T& value) { return !IsEven(value); }


/// Generates a range of N uniformly spaced values between a and b
/// C++ analogous method for Python.Numpy linspace method
#include <vector>
template <typename T>
std::vector<T> linspace(T a, T b, size_t N)
{
   T h = (b - a) / static_cast<T>(N - 1);
   std::vector<T> xs(N);
   typename std::vector<T>::iterator x;
   T val;
   auto end = std::end(xs);
   for (x = std::begin(xs), val = a; x != end; ++x, val += h)
   {
      *x = val;
   }
   return xs;
}

#undef  M_PI
#if (202002L <= _MSVC_LANG)
#define M_PI        std::numbers::pi
#else
#define M_PI        3.1415926535897932384626433832795
#endif

#undef  TWO_PI
#define TWO_PI      (2.0*M_PI) //6.28318530717958647692528676655901

#undef  PI_OVER_2
#define PI_OVER_2   (M_PI/2.0) //1.57079632679489661923132169163975

/// Converts an angle from degrees to radians
inline Float64 ToRadians(Float64 deg) { return deg*M_PI/180.; }
/// Converts an angle from radians to degrees
inline Float64 ToDegrees(Float64 rad) { return rad*180./M_PI; }
