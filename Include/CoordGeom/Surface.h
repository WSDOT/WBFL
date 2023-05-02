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
#include <CoordGeom/SurfaceTemplate.h>
#include <CoordGeom/SurfaceProfile.h>
#include <CoordGeom/Superelevation.h>
#include <CoordGeom/Widening.h>
#include <CoordGeom/Direction.h>
#include <CoordGeom/Path.h>

#include <GeomModel/LineSegment2d.h>

namespace WBFL
{
   namespace COGO
   {
      class SurfaceImpl;
      class Profile; // Forward declaration

      /// @brief An object that represents the surface, such as a roadway surface, associated with a Profile.
      /// A Surface is defined by collection of SurfaceTemplate objects and is modified by Superelevation and Widening objects.
      /// The ends of a surface, as well as the SurfaceTemplate objects are defined in a section normal to the alignment.
      class COORDGEOMCLASS Surface : public  std::enable_shared_from_this<Surface>
      {
      private:
         Surface();
         Surface(const Surface& surface);
         Surface& operator=(const Surface&) = delete;

         void SetProfile(std::weak_ptr<const Profile> profile);
         friend Profile;

      public:
         /// @brief Creates a new Surface object defined by two SurfaceTemplateSegments with the alignment and profile coincident with ridge point index 1
         /// @return 
         static std::shared_ptr<Surface> Create();

         static std::shared_ptr<Surface> Create(const Surface& surface);

         /// @brief Creates a new Surface object with the specified surface template parameters
         /// @param nSegments Number of SurfaceTemplateSegment objects define this Surface.
         /// @param alignmentPointIdx Ridge point index that is coincident with the Alignment
         /// @param profilePointIdx Ridge point index that is coincident with the Profile
         /// @return 
         static std::shared_ptr<Surface> Create(IndexType nSegments, IndexType alignmentPointIdx, IndexType profilePointIdx);

         ~Surface();

         /// @brief Returns the Profile with which this Surface is associated
         /// @return 
         std::shared_ptr<const Profile> GetProfile() const;

         /// @brief Sets the ridge point index that is coincident with the Alignment
         /// @param ridgePointIdx 
         void SetAlignmentPoint(IndexType ridgePointIdx);
         IndexType GetAlignmentPoint() const;

         /// @brief Sets the ridge point index that is coincident with the Profile
         /// @param ridgePointIdx 
         void SetProfileGradePoint(IndexType ridgePointIdx);
         IndexType GetProfileGradePoint() const;

         /// @brief Sets the number of SurfaceTemplateSegment objects define this Surface.
         /// All SurfaceTemplate objects for a given Surface have the same number of segments.
         /// All previously defined SurfaceTemplate objects are removed from this Surface when this parameter is set.
         /// @param nSegments 
         void SetSurfaceTemplateSegmentCount(IndexType nSegments);
         IndexType GetSurfaceTemplateSegmentCount() const;

         /// @brief Creates a SurfaceTemplate at the specified station.
         /// @param station Station where the surface template is created
         /// @return 
         std::shared_ptr<SurfaceTemplate> CreateSurfaceTemplate(const Station& station);

         /// @brief Returns the SurfaceTemplate objects that define this Surface
         /// @return 
         const std::vector<std::shared_ptr<SurfaceTemplate>>& GetSurfaceTemplates();

         /// @brief Get the SurfaceTemplate objects that bound the specified station
         /// @param station 
         /// @return Pair of the format (Template before station,Template after station)
         std::pair<std::shared_ptr<SurfaceTemplate>, std::shared_ptr<SurfaceTemplate>> GetBoundingTemplates(const Station& station) const;

         /// @brief Removes all SurfaceTemplate objects from this Surface
         void ClearSurfaceTemplates();

         /// @brief Adds a Superelevation modifier to the surface
         /// @param superelevation 
         void AddSuperelevation(std::shared_ptr<Superelevation> superelevation);

         /// @brief Finds a superelevation modifier for the given station
         /// @param station 
         /// @return Superelevation modifier. Will be nullptr if station is not within the bounds of a Superelevation 
         std::shared_ptr<Superelevation> FindSuperelevation(const Station& station) const;

         /// @brief Removes all superelevation modifiers from this Surface
         void ClearSuperelevations();

         /// @brief Adds a Widening modifier for this surface
         /// @param widening 
         void AddWidening(std::shared_ptr<Widening> widening);

         /// @brief Find a widening modifier for the given station
         /// @param station 
         /// @return Widening modifier. Will be nullptr if station is not within the bounds of a Widening
         std::shared_ptr<Widening> FindWidening(const Station& station) const;
         void ClearWidenings();

         /// @brief Returns the boundary line at the start of this Surface
         /// @return 
         WBFL::Geometry::LineSegment2d GetStartBoundaryLine() const;

         /// @brief Returns the boundary line at the end of this Surface
         /// @return 
         WBFL::Geometry::LineSegment2d GetEndBoundaryLine() const;

         /// @brief Gets the stationing range covered by this Surface
         /// @return Pair in the format (Start,End)
         std::pair<Station,Station> GetStationRange() const;

         /// @brief Returns true if station is within the station range covered by this surface
         /// @param station 
         /// @return 
         bool ContainsStation(const Station& station) const;

         /// @brief Creates a SurfaceTemplate object that represents a section cut normal to the alignment at the specified station
         /// @param station Station where the surface is cut
         /// @param bApplyModifiers If true, the superelevation and widening modifiers are applied
         /// @return 
         std::shared_ptr<SurfaceTemplate> CreateSurfaceTemplateSectionCut(const Station& station, bool bApplyModifiers) const;

         /// @brief Creates a SurfaceTemplate object that represents a section cut at the specified direction and station
         /// @param station Station where the surface is cut
         /// @param skewAngle The direction of the cut line relative to the alignment normal at the cut station.
         /// @param bApplyModifiers If true, the superelevation and widening modifiers are applied
         /// @return 
         std::shared_ptr<SurfaceProfile> CreateSurfaceProfileSectionCut(const Station& station, const Angle& skewAngle, bool bApplyModifiers) const;

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
         static bool TestBasicSurface(WBFL::Debug::Log& rlog);
         static bool TestWidenedSurface(WBFL::Debug::Log& rlog);
         static bool TestSuperelevatedSurface(WBFL::Debug::Log& rlog);

#endif // _UNITTEST

      private:
         std::unique_ptr<SurfaceImpl> m_pImpl;
      };
   };
};
