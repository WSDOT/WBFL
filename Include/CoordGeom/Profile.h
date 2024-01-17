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
#include <CoordGeom/ProfileElement.h>
#include <CoordGeom/Surface.h>
#include <map>
#include <memory>

namespace WBFL
{
   namespace COGO
   {
      class ProfileImpl;

      /// @brief An object that represents a vertical profile. A profile can be a roadway profile, profile of an underground utility, or other such items associated with an alignment.
      ///
      /// A Profile consists of ProfileElement objects. ProfileElement objects are positioned end to end in the order they are defined. 
      /// Straight lines are used to connect the ProfileElement objects together. 
      /// The tangents at the beginning and end of the profile are projected as straight lines.
      /// If a Profile does not contain any ProfileElement objects, it is assumed that the profile is at a constant elevation of 0.00.
      class COORDGEOMCLASS Profile : public std::enable_shared_from_this<Profile>
      {
      private:
         Profile();
         Profile(const Profile&);
         Profile& operator=(const Profile&) = delete;

         void SetAlignment(std::weak_ptr<const Alignment> alignment);
         friend Alignment;
         friend ProfileElement;

      public:
         /// @brief Creates a Profile
         /// @return 
         static std::shared_ptr<Profile> Create();
         static std::shared_ptr<Profile> Create(const Profile& profile);

         ~Profile();

         /// @brief Returns the Alignment object associated with this Profile
         /// @return 
         std::shared_ptr<const Alignment> GetAlignment() const;

         /// @brief Adds a ProfileElement to this profile
         /// @param profileElement 
         void AddProfileElement(std::shared_ptr<ProfileElement> profileElement);

         /// @brief Returns the specified ProfileElement
         /// @param idx Index of the element to return
         /// @return 
         std::shared_ptr<const ProfileElement> GetProfileElement(IndexType idx) const;
         std::shared_ptr<ProfileElement> GetProfileElement(IndexType idx);

         /// @brief Returns the profile elements
         /// @return 
         const std::vector<std::shared_ptr<ProfileElement>>& GetProfileElements() const;

         /// @brief Returns the number of ProfileElements
         /// @return 
         IndexType GetProfileElementCount() const;

         /// @brief Removes all the ProfileElement objects from the Profile
         void ClearProfileElements();

         /// @brief Associates a surface with the profile.
         /// A surface can be existing ground, finished roadway, or others. Each surface is defined by an ID
         /// @param id ID of surface
         /// @param surface 
         void AddSurface(IDType id,std::shared_ptr<Surface> surface);

         /// @brief Returns a Surface
         /// @param id ID of the surface
         /// @return 
         std::shared_ptr<const Surface> GetSurface(IDType id) const;

         /// @brief Returns the surfaces along with their IDs
         /// @return 
         const std::map<IDType, std::shared_ptr<const Surface>>& GetSurfaces() const;

         /// @brief Removes all surfaces from the profile
         void ClearSurfaces();

         /// @brief Removes everything from this profile
         void Clear();

         /// @brief Finds a surface containing the specified station
         /// @param station Station used to search for a surface
         /// @return pair in the for (SurfaceID,Surface). If a surface is not found SurfaceID is INVALID_ID and Surface is nullptr
         std::pair<IDType, std::shared_ptr<const Surface>> GetSurfaceContainingStation(const Station& station) const;

         /// @brief Creates a SurfaceTemplate object at the specified station
         /// @param surfaceID ID of the surface from which to create the SurfaceTemplate
         /// @param station Location of the SurfaceTemplate
         /// @param bApplySuperelevations If true, the SurfaceTemplate is modified by Superelevation objects, if applicable
         /// @return The SurfraceTemplate
         std::shared_ptr<SurfaceTemplate> CreateSurfaceTemplateSectionCut(IDType surfaceID, const Station& station, bool bApplySuperelevations) const;

         /// @brief Creates a SurfaceTemplate object at the specified station
         /// @param surface The surface from which to create the SurfaceTemplate. Surface must be associated with this Profile.
         /// @param station Location of the SurfaceTemplate
         /// @param bApplySuperelevations If true, the SurfaceTemplate is modified by Superelevation objects, if applicable
         /// @return The SurfraceTemplate
         std::shared_ptr<SurfaceTemplate> CreateSurfaceTemplateSectionCut(std::shared_ptr<const Surface> surface, const Station& station, bool bApplySuperelevations) const;

         /// @brief Returns the profile elevation at the specified station
         /// @param station 
         /// @return 
         Float64 Elevation(const Station& station) const;

         /// @brief Returns the surface elevation at the specified station and offset
         /// @param station Station where the elevation is to be computed
         /// @param surfaceID ID of surface from which the elevation is calculated
         /// @param offset Offset from the alignment
         /// @return 
         Float64 Elevation(IDType surfaceID, const Station& station, Float64 offset) const;

         /// @brief Returns the surface elevation at the specified station and offset
         /// @param station Station where the elevation is to be computed
         /// @param surface The surface from which the elevation is computed. Surface must be associated with this Profile.
         /// @param offset Offset from the alignment
         /// @return 
         Float64 Elevation(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const;

         /// @brief Returns the profile grade at the specified station
         /// @param station 
         /// @return 
         Float64 Grade(const Station& station) const;

         /// @brief Returns a surface template slope with respect to the horizontal
         /// @param station Station where a SurfaceTemplate is created
         /// @param surfaceID ID of the surface being evaluated
         /// @param segmentIdx Index of the SurfaceTemplateSegment from which the slope is returned
         /// @return The SurfaceTemplateSegment slope
         Float64 SurfaceTemplateSegmentSlope(IDType surfaceID, const Station& station, IndexType segmentIdx) const;

         /// @brief Returns a surface template slope with respect to the horizontal
         /// @param station Station where a SurfaceTemplate is created
         /// @param surface The surface being evaluated
         /// @param segmentIdx Index of the SurfaceTemplateSegment from which the slope is returned
         /// @return The SurfaceTemplateSegment slope
         Float64 SurfaceTemplateSegmentSlope(std::shared_ptr<const Surface> surface, const Station& station, IndexType segmentIdx) const;

         /// @brief Computes the cross slope at the specified station and offset
         /// @param surfaceID ID of the surface from which the cross slope is calculated
         /// @param station Station where the cross slope is computed
         /// @param offset Offset from alignment
         /// @return 
         Float64 CrossSlope(IDType surfaceID, const Station& station, Float64 offset) const;

         /// @brief Computes the cross slope at the specified station and offset
         /// @param surface The surface from which the cross slope is computed. Surface must be associated with this Profile.
         /// @param station Station where the cross slope is computed
         /// @param offset Offset from alignment
         /// @return 
         Float64 CrossSlope(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const;

         /// @brief Returns the offset from one ridge point to another ridge point
         /// @param surfaceID ID of the surface were the ridge point offset is to be computed
         /// @param station Location where the ridge point offset is to be computed
         /// @param ridgePoint1Idx The first ridge point
         /// @param ridgePoint2Idx The second ridge point
         /// @return The offset distance from the first to the second ridge point
         Float64 GetRidgePointOffset(IDType surfaceID,const Station& station,IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;

         /// @brief Returns the elevation of a ridge point
         /// @param surfaceID ID of the surface were the ridge point elevation is to be computed
         /// @param station Location where the ridge point offset is to be computed
         /// @param ridgePointIdx Index of a ridge point
         /// @return The ridge point elevation
         Float64 GetRidgePointElevation(IDType surfaceID, const Station& station, IndexType ridgePointIdx) const;

         /// @brief Returns the offset from a reference ridge point to another ridge point and the elevation at that ridge point
         /// @param surfaceID ID of the surface were the ridge point elevation is to be computed
         /// @param station Location where the ridge point elevation is to be computed
         /// @param ridgePoint1Idx The first ridge point
         /// @param ridgePoint2Idx The second ridge point
         /// @return Returns the pair<Offset,Elevation> where Offset is the distance from the first to the second ridge point and Elevation is the elevation of the second ridge point
         std::pair<Float64, Float64> GetRidgePointOffsetAndElevation(IDType surfaceID, const Station& station, IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;

      private:
         std::unique_ptr<ProfileImpl> m_pImpl;
         void OnProfileChanged();
      };
   };
};
