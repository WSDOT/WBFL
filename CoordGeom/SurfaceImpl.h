///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/SurfaceTemplate.h>
#include <CoordGeom/SurfaceProfile.h>
#include <CoordGeom/Superelevation.h>
#include <CoordGeom/Widening.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/Path.h>

#include <GeomModel/LineSegment2d.h>

#include <map>

namespace WBFL
{
   namespace COGO
   {
      class Profile; // Forward declaration

      class COORDGEOMCLASS SurfaceImpl
      {
      public:
         SurfaceImpl() = default;
         SurfaceImpl(const SurfaceImpl& surfaceImpl);
         SurfaceImpl& operator=(const SurfaceImpl&) = delete;
         ~SurfaceImpl() = default;

         void SetSurface(std::weak_ptr<const Surface> surface);
         std::shared_ptr<const Surface> GetSurface() const;

         void SetProfile(std::weak_ptr<const Profile> profile);
         std::shared_ptr<const Profile> GetProfile() const;

         void SetAlignmentPoint(IndexType ridgePointIdx);
         IndexType GetAlignmentPoint() const;

         void SetProfileGradePoint(IndexType ridgePointIdx);
         IndexType GetProfileGradePoint() const;

         void SetSurfaceTemplateSegmentCount(IndexType nSegments);
         IndexType GetSurfaceTemplateSegmentCount() const;

         void AddSurfaceTemplate(std::shared_ptr<SurfaceTemplate> surfaceTemplate);
         const std::vector<std::shared_ptr<SurfaceTemplate>>& GetSurfaceTemplates();
         std::pair<std::shared_ptr<SurfaceTemplate>, std::shared_ptr<SurfaceTemplate>> GetBoundingTemplates(const Station& station) const;
         void ClearSurfaceTemplates();

         void AddSuperelevation(std::shared_ptr<Superelevation> superelevation);
         std::shared_ptr<Superelevation> FindSuperelevation(const Station& station) const;
         void ClearSuperelevations();

         void AddWidening(std::shared_ptr<Widening> widening);
         std::shared_ptr<Widening> FindWidening(const Station& station) const;
         void ClearWidenings();

         WBFL::Geometry::LineSegment2d GetStartBoundaryLine() const;
         WBFL::Geometry::LineSegment2d GetEndBoundaryLine() const;
         std::pair<Station, Station> GetStationRange() const;
         bool ContainsStation(const Station& station) const;

         void ConfigureSurfaceTemplate(std::shared_ptr<SurfaceTemplate> surfaceTemplate, bool bApplySuperelevations) const;

         void ConfigureSurfaceProfile(std::shared_ptr<SurfaceProfile> surfaceProfile, const Station& station, const Angle& skewAngle, bool bApplySuperelevations) const;

      private:
         std::weak_ptr<const Surface> m_Surface;
         std::weak_ptr<const Profile> m_Profile;

         IndexType m_SurfaceTemplateSegmentCount = 2;

         IndexType m_AlignmentPoint = 1;
         IndexType m_ProfileGradePoint = 1;

         std::vector<std::shared_ptr<SurfaceTemplate>> m_SurfaceTemplates;
         std::vector<std::shared_ptr<Superelevation>> m_Superelevations;
         std::vector<std::shared_ptr<Widening>> m_Widenings;

         std::shared_ptr<const Widening> GetWidening(const Station& station) const;
         std::shared_ptr<const Superelevation> GetSuperelevation(const Station& station) const;
         Float64 GetWidening(const Station& station, IndexType templateSegmentIdx) const;
         std::pair<Float64, SurfaceTemplateSegment::SlopeType> GetSuperelevatedSlope(const Station& station, IndexType templateSegmentIdx, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType) const;
         WBFL::Geometry::LineSegment2d CreateTemplateLine(std::shared_ptr<const SurfaceTemplate> surfaceTemplate) const;

         void UpdateRidgeLines() const;
         mutable std::map<IndexType, std::vector<std::shared_ptr<Path>>> m_RidgeLines; // key is the sub-surface index

         void SortSurfaceTemplates();
         std::shared_ptr<const Alignment> GetAlignment();
      };
   };
};
