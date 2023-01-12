///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#if defined VBA_BUILD
#if defined _WIN64

#if defined _DEBUG
#include <x64\VBA_Debug\_WBFLTypes.h>
#else // _DEBUG
#include <x64\VBA_Release\_WBFLTypes.h>
#endif // _DEBUG

#else // _WIN64

#if defined _DEBUG
#include <Win32\VBA_Debug\_WBFLTypes.h>
#else // _DEBUG
#include <Win32\VBA_Release\_WBFLTypes.h>
#endif // _DEBUG

#endif // _WIN64

#else // VBA_BUILD

#if defined _WIN64

#if defined _DEBUG
#include <x64\Debug\_WBFLTypes.h>
#else
#include <x64\Release\_WBFLTypes.h>
#endif

#else

#if defined _DEBUG
#include <Win32\Debug\_WBFLTypes.h>
#else
#include <Win32\Release\_WBFLTypes.h>
#endif

#endif // _WIN64

#endif // VBA_BUILD


#include <algorithm>
#include <utility>
#include <tuple>
template <class T>
class SimplePointT : private std::pair<T, T>
{
public:
   SimplePointT() : std::pair<T, T>(0, 0) {}
   SimplePointT(T x, T y) : std::pair<T, T>(x, y) {}
   SimplePointT(const SimplePointT&) = default;
   SimplePointT& operator=(const SimplePointT&) = default;
   ~SimplePointT() = default;

   T& X() { return first; }
   const T& X() const { return first; }
   T& Y() { return second; }
   const T& Y() const { return second; }
};

template <class T>
class SimpleSizeT : private std::pair<T, T>
{
public:
   SimpleSizeT() : std::pair<T, T>(0, 0) {}
   SimpleSizeT(T x, T y) : std::pair<T, T>(x, y) {}
   SimpleSizeT(const SimpleSizeT&) = default;
   SimpleSizeT& operator=(const SimpleSizeT&) = default;
   ~SimpleSizeT() = default;

   T& Dx() { return first; }
   const T& Dx() const { return first; }
   T& Dy() { return second; }
   const T& Dy() const { return second; }
};

template <class T>
class SimpleRectT : private std::tuple<T, T, T, T>
{
public:
   SimpleRectT() : std::tuple<T, T, T, T>(0, 0, 0, 0) {}
   SimpleRectT(const T& left, const T& bottom, const T& right, const T& top) : std::tuple<T, T, T, T>(left, bottom, right, top) {}
   SimpleRectT(const SimpleRectT&) = default;
   SimpleRectT& operator=(const SimpleRectT&) = default;
   ~SimpleRectT() = default;

   void Set(const T& left, const T& bottom, const T& right, const T& top) { Left() = left; Bottom() = bottom; Right() = right; Top() = top; }
   T& Left() { return std::get<0>(*this); }
   const T& Left() const { return std::get<0>(*this); }
   T& Bottom() { return std::get<1>(*this); }
   const T& Bottom() const { return std::get<1>(*this); }
   T& Right() { return std::get<2>(*this); }
   const T& Right() const { return std::get<2>(*this); }
   T& Top() { return std::get<3>(*this); }
   const T& Top() const { return std::get<3>(*this); }
   T Width() const { return Right() - Left(); }
   T Height() const { return Top() - Bottom(); }
   SimplePointT<T> TopLeft() const { return SimplePointT<T>(Left(), Top()); }
   SimplePointT<T> TopCenter() const { return SimplePointT<T>((Left() + Right()) / 2, Top()); }
   SimplePointT<T> TopRight() const { return SimplePointT<T>(Right(), Top()); }
   SimplePointT<T> BottomLeft() const { return SimplePointT<T>(Left(), Bottom()); }
   SimplePointT<T> BottomCenter() const { return SimplePointT<T>((Left() + Right()) / 2, Bottom()); }
   SimplePointT<T> BottomRight() const { return SimplePointT<T>(Right(), Bottom()); }
   SimplePointT<T> Center() const { return SimplePointT<T>((Left() + Right()) / 2, (Top() + Bottom()) / 2); }
   SimpleSizeT<T> Size() const { return SimpleSizeT<T>(Width(), Height()); }

   /// Changes the dimensions so that the rectangle bounds the point creating
   /// the smallest union of the existing rectangle and the point.
   /// Note: Both of the rectangles must be normalized or this function may fail. 
   /// You can call Normalize to normalize the rectangles before calling this function.
   SimpleRectT<T>& BoundPoint(const SimplePointT<T>& point) {
      Left() = std::min(point.X(), Left());
      Right() = std::max(point.X(), Right());
      Bottom() = std::min(point.Y(), Bottom());
      Top() = std::max(point.Y(), Top());
      return *this;
   }
};
