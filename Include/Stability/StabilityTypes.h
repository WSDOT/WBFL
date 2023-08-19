///////////////////////////////////////////////////////////////////////
// Stability
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

#include <Stability/StabilityExp.h>
#include <WBFLTypes.h>
#include <MathEx.h>

namespace WBFL
{
   namespace Stability
   {
      // Causes the compiler to instantiate the class and export it's symbols
      STABILITYTPL SimplePointT<Float64>;
      class STABILITYCLASS Point : public SimplePointT<Float64>
      {
      public:
         Point() = default;
         Point(const Point& other) = default;
         bool operator==(const Point& other) const { return IsEqual(X(), other.X()) && IsEqual(Y(), other.Y()); }
         bool operator!=(const Point & other) const {return !operator==(other);}

         Point& Offset(Float64 dx, Float64 dy) { X() += dx; Y() += dy; return *this; }
      };

      /// Constant indicating the face of a girder
      enum class GirderFace
      {
         Top, ///< Top face
         Bottom ///< Bottom face
      };
      inline constexpr auto operator+(GirderFace t) noexcept { return std::underlying_type<GirderFace>::type(t); }

      /// Constant indicating the side of a girder
      enum class GirderSide
      {
         Left, ///< Left side
         Right ///< Right side
      };
      inline constexpr auto operator+(GirderSide t) noexcept { return std::underlying_type<GirderSide>::type(t); }

      /// Constant indicate the direction of impact
      enum class ImpactDirection
      {
         NoImpact, ///< No impact
         ImpactUp, ///< Impact up
         ImpactDown ///< Impact down
      };
      inline constexpr auto operator+(ImpactDirection t) noexcept { return std::underlying_type<ImpactDirection>::type(t); }

      /// Constant indicating when impact is considered in hauling stability analysis
      enum class HaulingImpact
      {
         NormalCrown, ///< impact applied only to the normal crown condition
         MaxSuper,    ///< impact applied only to the max superelevation condition   
         Both         ///< impact applied to both conditions
      };
      inline constexpr auto operator+(HaulingImpact t) noexcept { return std::underlying_type<HaulingImpact>::type(t); }

      /// Constant indicating the direction of wind
      enum class WindDirection
      {
         Left, ///< Towards the Left (right to left <--)
         Right ///< Towards the Right (left to right -->)
      };
      inline constexpr auto operator+(WindDirection t) noexcept { return std::underlying_type<WindDirection>::type(t); }

      /// Constant indicating how wind load is defined
      enum class WindLoadType
      {
         Speed, ///< defined by a wind speed and wind pressure is to be computed
         Pressure ///< wind pressure is input
      };
      inline constexpr auto operator+(WindLoadType t) noexcept { return std::underlying_type<WindLoadType>::type(t); }

      /// Constant indicating a nominal corner of the girder
      enum class Corner
      {
         TopLeft,
         TopRight,
         BottomLeft,
         BottomRight
      };
      inline constexpr auto operator+(Corner t) noexcept { return std::underlying_type<Corner>::type(t); }

      /// Constant indicate the location of a harp point
      enum class HarpPointLocation
      {
         StartHP, ///< Point near start of the girder where strands are deflected (typically the left end of the girder)
         LeftHP, ///< Point where strands are deflected, left of mid-span
         RightHP, ///< Point where strands are deflected, right of mid-span
         EndHP ///< Point near end of the girder where strands are deflected (typically the right end of the girder)
      };
      inline constexpr auto operator+(HarpPointLocation t) noexcept { return std::underlying_type<HarpPointLocation>::type(t); }

      /// Constant indicating the face of prismatic section of the girder
      enum class Section
      {
         Start, ///< Start of the section
         End ///< End of the section
      };
      inline constexpr auto operator+(Section t) noexcept { return std::underlying_type<Section>::type(t); }

      /// Constant indicating the type of centrifugal force occurring in the analysis
      enum class CFType
      {
         Adverse, ///< CF is towards the left (increases lateral deflection and roll over)
         Favorable ///< CF is towards the right
      };
      inline constexpr auto operator+(CFType t) noexcept { return std::underlying_type<CFType>::type(t); }

      /// Constant indicating the method for compute the lateral offset of the center of mass /f$ z_o /f$
      enum class CalculationMethod
      {
         Exact, ///< A closed form, exact method 
         Approximate ///< An approximate numerical method
      };
      inline constexpr auto operator+(CalculationMethod t) noexcept { return std::underlying_type<CalculationMethod>::type(t); }

      /// Constant indicating one of the hauling analysis crown slope types
      enum class HaulingSlope
      {
         CrownSlope, ///< The normal roadway crown slope
         Superelevation ///< Slope at maximum superelevation
      };
      inline constexpr auto operator+(HaulingSlope t) noexcept { return std::underlying_type<HaulingSlope>::type(t); }

      /// Returns the GirderFace corresponding to a Corner
      inline GirderFace GetFace(Corner corner)
      {
         return (corner == Corner::TopLeft || corner == Corner::TopRight ? GirderFace::Top : GirderFace::Bottom);
      }

      /// Returns the GirderSide corresponding to a Corner
      inline GirderSide GetSide(Corner corner)
      {
         return (corner == Corner::TopLeft || corner == Corner::BottomLeft ? GirderSide::Left : GirderSide::Right);
      }
   }
}