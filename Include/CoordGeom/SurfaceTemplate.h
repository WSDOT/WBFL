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
#include <CoordGeom/SurfaceTemplateSegment.h>
#include <CoordGeom/Station.h>

namespace WBFL
{
   namespace COGO
   {
      class Surface;
      class SurfaceImpl;
      class SurfaceTemplateImpl;
   
      /// @brief A surface template defines the cross section of a surface. 
      /// The template consists of a sequence of straight line segments (SurfaceTemplateSegment), defined left to right looking in the forward direction (ahead on station).
      /// The end points of the segments are known as ridge points.
      /// A SurfaceTemplate can only be created from a Surface or Profile object.
      /// Slopes and Elevations at locations beyond the boundary of the surface template will be taken as those at the nearest ridge point.
      /// @image html Images/SurfaceTemplate.png
      class COORDGEOMCLASS SurfaceTemplate
      {
      private:
         SurfaceTemplate() = delete;
         SurfaceTemplate(const Station& station);
         SurfaceTemplate(const SurfaceTemplate&);
         SurfaceTemplate& operator=(const SurfaceTemplate&) = delete;

         static std::shared_ptr<SurfaceTemplate> Create(const Station& station);
         static std::shared_ptr<SurfaceTemplate> Create(const SurfaceTemplate& surfaceTemplate);
         void SetSurface(std::weak_ptr<const Surface> surface);
         friend Surface;
         friend SurfaceImpl;

      public:
         ~SurfaceTemplate();

         /// @brief Returns the associated Surface
         /// @return 
         std::shared_ptr<const Surface> GetSurface() const;

         /// @brief Returns the station where this surface template is applied
         /// @return 
         const Station& GetStation() const;

         /// @brief Gets the SurfaceTemplateSegment parameters
         /// @param segmentIdx 
         /// @return Returns a tuple in the form (Width,Slope,SlopeType)
         std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType> GetSegmentParameters(IndexType segmentIdx);

         /// @brief Updates a SurfaceTemplateSegment parameters
         /// @param segmentIdx Index of the segment whose parameters are being updated
         /// @param width Width of the segment
         /// @param slope Slope of the segment
         /// @param slopeType Type of slope used to define the segment
         void UpdateSegmentParameters(IndexType segmentIdx,Float64 width, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType);

         /// @brief Returns the number of segments in the template
         /// > NOTE: All SurfaceTemplate objects associated with the Surface object must have the same number of segments
         /// @return 
         IndexType GetCount() const;

         /// @brief Gets a SurfaceTemplateSegment
         /// @param idx 
         /// @return 
         SurfaceTemplateSegment& GetSegment(IndexType idx);

         /// @brief Gets a SurfaceTemplateSegment
         /// @param idx 
         /// @return 
         const SurfaceTemplateSegment& GetSegment(IndexType idx) const;

         /// @brief Removes all SurfaceTemplateSegment objects from this SurfaceTemplate
         void Clear();

         /// @brief Returns the change in elevation between two ridge points.
         /// @param ridgePoint1Idx The first ridge point
         /// @param ridgePoint2Idx The second ridge point
         /// @return The change in elevation from the first to second ridge points
         Float64 GetRidgePointElevationChange(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;

         /// @brief Returns the elevation change from a ridge point to an offset point
         /// @param ridgePointIdx Index of a ridge point
         /// @param offset Offset from the ridge point
         /// @return Change of elevation between the ridge point and the offset point
         Float64 GetElevationChange(IndexType ridgePointIdx, Float64 offset) const;

         /// @brief Returns the slope at a point offset from a ridge point
         /// @param ridgePointIdx Index of a ridge point
         /// @param offset Offset from the ridge point
         /// @return Slope at the offset point. A slope of 0.0 is returned when the offset is beyond the boundary of the Surface.
         Float64 GetSlope(IndexType ridgePointIdx, Float64 offset) const;

         /// @brief Returns the slope from horizontal for a segment
         /// @param segmentIdx 
         /// @return 
         Float64 GetSegmentSlope(IndexType segmentIdx) const;

         /// @brief Returns the offset from one ridge point to another
         /// @param ridgePoint1Idx The first ridge point
         /// @param ridgePoint2Idx The second ridge point
         /// @return The offset distance from the first to the second ridge point
         Float64 GetRidgePointOffset(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;

         /// @brief Returns the elevation of a ridge point
         /// @param ridgePointIdx 
         /// @return 
         Float64 GetRidgePointElevation(IndexType ridgePointIdx) const;

         /// @brief Returns the offset from a reference ridge point to another ridge point and the elevation at that ridge point
         /// @param ridgePoint1Idx The first ridge point
         /// @param ridgePoint2Idx The second ridge point
         /// @return Returns the pair<Offset,Elevation> where Offset is the distance from the first to the second ridge point and Elevation is the elevation of the second ridge point
         std::pair<Float64,Float64> GetRidgePointOffsetAndElevation(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;

      private:
         std::unique_ptr<SurfaceTemplateImpl> m_pImpl;
      };
   };
};
