///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

/// @brief Template for a lightweight Point class. This can be used when there isn't otherwise a need to depend on the full WBFLGeomModel library.
template <class T>
class SimplePointT : private std::pair<T, T>
{
public:
   SimplePointT() : std::pair<T, T>(0, 0) {}
   SimplePointT(const T& x, const T& y) : std::pair<T, T>(x, y) {}
   SimplePointT(const SimplePointT&) = default;
   SimplePointT& operator=(const SimplePointT&) = default;
   ~SimplePointT() = default;

   bool operator==(const SimplePointT& other) { return X() == other.X() && Y() == other.Y(); }
   bool operator!=(const SimplePointT& other) { return !operator==(other); }

   T& X() { return this->first; }
   const T& X() const { return this->first; }
   T& Y() { return this->second; }
   const T& Y() const { return this->second; }
};

/// @brief Template for a lightweight Size class. This can be used when there isn't otherwise a need to depend on the full WBFLGeomModel library.
template <class T>
class SimpleSizeT : private std::pair<T, T>
{
public:
   SimpleSizeT() : std::pair<T, T>(0, 0) {}
   SimpleSizeT(const T& x, const T& y) : std::pair<T, T>(x, y) {}
   SimpleSizeT(const SimpleSizeT&) = default;
   SimpleSizeT& operator=(const SimpleSizeT&) = default;
   ~SimpleSizeT() = default;

   bool operator==(const SimpleSizeT& other) { return Dx() == other.Dx() && Dy() == other.Dy(); }
   bool operator!=(const SimpleSizeT& other) { return !operator==(other); }

   T& Dx() { return this->first; }
   const T& Dx() const { return this->first; }
   T& Dy() { return this->second; }
   const T& Dy() const { return this->second; }
};

/// @brief Template for a lightweight Rect class. This can be used when there isn't otherwise a need to depend on the full WBFLGeomModel library.
template <class T>
class SimpleRectT : private std::tuple<T, T, T, T>
{
public:
   SimpleRectT() : std::tuple<T, T, T, T>(0, 0, 0, 0) {}
   SimpleRectT(const T& left, const T& bottom, const T& right, const T& top) : std::tuple<T, T, T, T>(left, bottom, right, top) {}
   SimpleRectT(const SimpleRectT&) = default;
   SimpleRectT& operator=(const SimpleRectT&) = default;
   ~SimpleRectT() = default;

   bool operator==(const SimpleRectT& other) { return Left() == other.Left() && Right() == other.Right() && Top() == other.Top() && Bottom() == other.Bottom(); }
   bool operator!=(const SimpleRectT& other) { return !operator==(other); }

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
      Left() = point.X() < Left() ? point.X() : Left(); // std::min(point.X(),Left()); // std::min and std::max cause compilation problems for some clients. don't know why. the algorithm header is included
      Right() = Right() < point.X() ? point.X() : Right(); //std::max(point.X(),Right());
      Bottom() = point.Y() < Bottom() ? point.Y() : Bottom();// std::min(point.Y(), Bottom());
      Top() = Top() < point.Y() ? point.Y() : Top(); // std::max(point.Y(), Top());
      return *this;
   }
};
