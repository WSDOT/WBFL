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

namespace WBFL
{
   namespace COGO
   {
      class Surface; // forward declaration
      class Profile; // forward declaration

      class SurfaceTemplateImpl
      {
      public:
         SurfaceTemplateImpl() = delete;
         SurfaceTemplateImpl(const Station& station);
         SurfaceTemplateImpl(const SurfaceTemplateImpl& impl) = default;
         SurfaceTemplateImpl& operator=(const SurfaceTemplateImpl&) = default;
         ~SurfaceTemplateImpl() = default;

         void SetSurface(std::weak_ptr<const Surface> surface);
         std::shared_ptr<const Surface> GetSurface() const;
         const Station& GetStation() const;
         std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType> GetSegmentParameters(IndexType segmentIdx);
         void UpdateSegmentParameters(IndexType segmentIdx,Float64 width, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType);
         IndexType GetCount() const;
         SurfaceTemplateSegment& GetSegment(IndexType idx);
         const SurfaceTemplateSegment& GetSegment(IndexType idx) const;
         void Clear();
         Float64 GetRidgePointElevationChange(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;
         Float64 GetElevationChange(IndexType ridgePointIdx, Float64 offset) const;
         Float64 GetSlope(IndexType ridgePointIdx, Float64 offset) const;
         Float64 GetSegmentSlope(IndexType idx) const;
         Float64 GetRidgePointOffset(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;
         Float64 GetRidgePointElevation(IndexType ridgePointIdx) const;
         std::pair<Float64, Float64> GetRidgePointOffsetAndElevation(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;

      private:
         std::weak_ptr<const Surface> m_Surface;
         Station m_Station;
         std::vector<SurfaceTemplateSegment> m_SegmentTemplates;
      };
   };
};
