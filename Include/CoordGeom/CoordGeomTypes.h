///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>

namespace WBFL
{
   namespace COGO
   {
      ///@brief Constant identifying the direction of the angle formed by a circular curve tangent line and the line connecting the centers of circles.
      enum class TangentSign
      {
         CCW = 1, ///< Counter-clockwise angle
         CW = -1 ///< Clockwise angle
      };

      /// @brief Defines the direction of a curve when the observer is looking ahead on station
      enum class CurveDirection
      {
         Left,
         Right
      };

      /// @brief Defines the methods for computing degree of curvature
      enum class DegreeCurvature
      {
         Chord,
         Arc,
         Railroad,
         Highway
      };

      /// @brief Defines the type of transition curve
      enum class TransitionCurveType
      {
         Clothoid
         // Bloss.... and others in the future
      };

      /// @brief Defines how an offset is measured
      enum class OffsetType
      {
         AlongDirection, ///< Offset is measured along a line projecting from an object
         Normal ///< Offset is measured normal to the object
      };

      /// @brief Defines the relative location of a pier face for an observer looking ahead on station
      enum class PierFaceType
      {
         Back, ///< Back on station face
         Ahead ///< Ahead on station face
      };
      inline constexpr auto operator+(PierFaceType t) noexcept { return std::underlying_type<PierFaceType>::type(t); }

      /// @brief Defines how a geometric parameter is measured
      enum class MeasurementType
      {
         AlongItem, ///< The parameter is measured along the item being defined
         NormalToItem ///< The parameters is measured normal to the item being defined
      };
      inline constexpr auto operator+(MeasurementType t) noexcept { return std::underlying_type<MeasurementType>::type(t); }

      /// @brief Defines the datum from where the girder end distance is measured
      enum class MeasurementLocation
      {
         PierLine, ///< Measured from the pier line
         CenterlineBearing ///< Measured from the centerline bearing
      };
      inline constexpr auto operator+(MeasurementLocation t) noexcept { return std::underlying_type<MeasurementLocation>::type(t); }

      /// @brief Defines the relative end of a geometry object such as a girder
      enum class EndType
      {
         Start,
         End
      };
      inline constexpr auto operator+(EndType t) noexcept { return std::underlying_type<EndType>::type(t); }

      /// @brief Defines the location of a geometric object relative to another geometric object based on the observer looking in a positive direction.
      /// The sides of a bridge deck are an example.
      enum class SideType
      {
         Left,
         Right
      };
      inline constexpr auto operator+(SideType t) noexcept { return std::underlying_type<SideType>::type(t); }

      /// @brief Defines how a girder line is defined
      enum class GirderLineType
      {
         Chord, ///< A straight chord between end points
         Path ///< Follows a curvilinear path
      };

      /// @brief Defines how the transverse edge of a deck is defined
      enum class TransverseEdgeType
      {
         Pier, ///< The edge is defined by the pier line
         LayoutLine ///< The edge is defined by a layout line
      };
   };
};