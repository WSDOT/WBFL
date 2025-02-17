///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/CoordGeomTypes.h>

#include <array>

namespace WBFL
{
   namespace COGO
   {
      /// @brief Contains connection geometry data for a PierLine
      struct COORDGEOMCLASS ConnectionGeometry
      {
      public:
         ConnectionGeometry() = default;
         ConnectionGeometry(Float64 bearingOffset, MeasurementType brgOffsetMeasure, Float64 endDistance, MeasurementType endDistMeasure, MeasurementLocation endDistMeasureLocation) :
            BearingOffset(bearingOffset), BearingOffsetMeasurementType(brgOffsetMeasure), EndDistance(endDistance), EndDistanceMeasurementType(endDistMeasure), EndDistanceMeasurementLocationType(endDistMeasureLocation)
         {
         }
         ConnectionGeometry(const ConnectionGeometry&) = default;
         ConnectionGeometry& operator=(const ConnectionGeometry& other) = default;
         ~ConnectionGeometry() = default;

         bool operator==(const ConnectionGeometry& other) const
         {
            return IsEqual(BearingOffset, other.BearingOffset) && 
               BearingOffsetMeasurementType == other.BearingOffsetMeasurementType && 
               IsEqual(EndDistance, other.EndDistance) && 
               EndDistanceMeasurementType == other.EndDistanceMeasurementType && 
               EndDistanceMeasurementLocationType == other.EndDistanceMeasurementLocationType;
         }

         bool operator!=(const ConnectionGeometry& other) const
         {
            return !operator==(other);
         }

         Float64 BearingOffset = 0.0; ///< Distance from centerline of pier to the centerline of bearing point
         MeasurementType BearingOffsetMeasurementType = MeasurementType::NormalToItem; ///< The method of measuring the bearing offset
         Float64 EndDistance = 0.0; ///< The distance from a datum point to the end of the beam supported by a pier
         MeasurementType EndDistanceMeasurementType = MeasurementType::NormalToItem; ///< The method of measuring the end distance
         MeasurementLocation EndDistanceMeasurementLocationType = MeasurementLocation::CenterlineBearing; ///< The datum for measuring the end distance
      };
   };
};
