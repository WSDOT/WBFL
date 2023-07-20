///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/SurfaceTemplateSegment.h>
#include <CoordGeom/Station.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/SurfacePoint.h>

namespace WBFL
{
   namespace COGO
   {
      class Surface; // forward declaration
      class SurfaceImpl;

      /// @brief An object that represents a cross section for a Surface taken at an arbitrary orientation. 
      ///
      /// A SurfaceProfile differs from a SurfaceTemplate in that it represents a cross section cut through a surface at an arbitrary orientation.
      /// A SurfaceProfile is defined by a sequence of SurfacePoint objects where a SurfaceTemplate is defined by a sequence of TemplateSegment objects.
      /// A SurfaceProfile can only be created from a Surface.
      class COORDGEOMCLASS SurfaceProfile
      {
      private:
         SurfaceProfile() = default;
         SurfaceProfile(const Station& station);
         SurfaceProfile(const SurfaceProfile&) = delete;
         SurfaceProfile& operator=(const SurfaceProfile&) = delete;

         static std::shared_ptr<SurfaceProfile> Create();

         void SetSurface(std::weak_ptr<const Surface> surface);
         void SetStation(const Station& station);
         void SetSkewAngle(const Angle& skewAngle);
         void SetDirection(const Direction& direction);
         std::shared_ptr<SurfacePoint> CreateSurfacePoint(const Station& station, Float64 normalOffset, Float64 cutlineOffset, Float64 elevation, const WBFL::Geometry::Point2d& location);

         friend Surface;
         friend SurfaceImpl;

      public:
         ~SurfaceProfile() = default;

         /// @brief Returns the associated Surface
         /// @return 
         std::shared_ptr<const Surface> GetSurface() const;

         /// @brief Station where the SurfaceProfile is taken
         /// @param station 
         const Station& GetStation() const;

         /// @brief Returns the skew angle relative to the alignment normal.
         /// @return 
         const Angle& GetSkewAngle() const;

         /// @brief Direction of the cut line
         const Direction& GetDirection() const;

         /// @brief Returns the number of SurfacePoint objects defining this SurfaceProfile
         /// @return 
         IndexType GetSurfacePointCount() const;

         /// @brief Returns a SurfacePoint
         /// @param surfacePointIdx Index of the desired SurfacePoint
         /// @return 
         std::shared_ptr<SurfacePoint> GetSurfacePoint(IndexType surfacePointIdx);
         std::shared_ptr<const SurfacePoint> GetSurfacePoint(IndexType surfacePointIdx) const;

         /// @brief Returns the elevation change between two SurfacePoint objects
         /// @param surfacePoint1Idx Index of the first SurfacePoint
         /// @param surfacePoint2Idx Index of the second SurfacePoint
         /// @return 
         Float64 GetSurfacePointElevationChange(IndexType surfacePoint1Idx, IndexType surfacePoint2Idx) const;

         /// @brief Returns the elevation of the Surface at the specified offset from a SurfacePoint.
         /// @param surfacePointIdx Index of the SurfacePoint from which the offset is measured
         /// @param offset Offset measured from the specified SurfacePoint in the plane of the SurfaceProfile
         /// @return 
         Float64 GetElevationChange(IndexType surfacePointIdx, Float64 offset) const;

         /// @brief Returns the slop of the Surface at the specified offset from a SurfacePoint
         /// @param surfacePointIdx Index of the SurfacePoint from which the offset is measured
         /// @param offset Offset measured from the specified SurfacePoint in the plane of the SurfaceProfile
         /// @return 
         Float64 GetSlope(IndexType surfacePointIdx, Float64 offset) const;

         /// @brief Returns the slope of the specified segment
         /// @param segmentIdx 
         /// @return 
         Float64 GetSegmentSlope(IndexType segmentIdx) const;

         /// @brief Returns the offset of the specified SurfacePoint from the Alignment in the plane of this SurfaceProfile
         /// @param surfacePointIdx 
         /// @return 
         Float64 GetSurfacePointOffset(IndexType surfacePointIdx) const;

         /// @brief Returns the elevation and offset for the specified SurfacePoint
         /// @param surfacePointIdx Index of the SurfacePoint
         /// @return Returns a pair in the format (Offset,Elevation). Offset is the offset from the Alignment in the plane of this SurfaceProfile. Elevation is the elevation of the SurfacePoint
         std::pair<Float64,Float64> GetSurfacePointOffsetAndElevation(IndexType surfacePointIdx) const;

      private:
         std::weak_ptr<const Surface> m_Surface;
         Station m_Station;
         Direction m_Direction;
         Angle m_SkewAngle;
         std::vector<std::shared_ptr<SurfacePoint>> m_SurfacePoints;
      };
   };
};
