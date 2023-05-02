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
#include <CoordGeom/ProfileElement.h>
#include <CoordGeom/Surface.h>
#include <map>
#include <memory>

namespace WBFL
{
   namespace COGO
   {
      /// @brief An object that represents the surface, such as a roadway surface, associated with a Profile.
      /// A Surface is defined by collection of SurfaceTemplate objects and modified by Superelevation and Widening objects.
      class ProfileImpl
      {
      public:
         ProfileImpl();
         ProfileImpl(const ProfileImpl& profileImpl);
         ProfileImpl& operator=(const ProfileImpl& profileImpl) = delete;
         ~ProfileImpl() = default;

         void OnProfileChanged();

         void SetProfile(std::weak_ptr<Profile> profile);
         void SetAlignment(std::weak_ptr<const Alignment> alignment);

         /// @brief Adds a ProfileElement to this profile
         /// @param profileElement 
         void AddProfileElement(std::shared_ptr<ProfileElement>& profileElement);

         /// @brief Returns the specified ProfileElement
         /// @param idx Index of the element to return
         /// @return 
         std::shared_ptr<const ProfileElement> GetProfileElement(IndexType idx) const;
         std::shared_ptr<ProfileElement> GetProfileElement(IndexType idx);

         /// @brief Returns the number of ProfileElements
         /// @return 
         IndexType GetProfileElementCount() const;

         /// @brief Returns the profile elements
         /// @return 
         const std::vector<std::shared_ptr<ProfileElement>>& GetProfileElements() const;

         /// @brief Removes all the ProfileElement objects from the Profile
         void ClearProfileElements();

         /// @brief Returns the Alignment object associated with this Profile
         /// @return 
         std::shared_ptr<const Alignment> GetAlignment() const;

         /// @brief Associates a surface with the profile.
         /// A surface can be existing ground, finished roadway, or others. Each surface is defined by an ID
         /// @param id ID of surface
         /// @param surface 
         void AddSurface(IDType id,std::shared_ptr<const Surface> surface);

         /// @brief Returns a Surface
         /// @param id ID of the surface
         /// @return 
         std::shared_ptr<const Surface> GetSurface(IDType id) const;

         /// @brief Returns the surfaces along with their IDs
         /// @return 
         const std::map<IDType, std::shared_ptr<const Surface>>& GetSurfaces() const;

         /// @brief Removes all surfaces from the profile
         void ClearSurfaces();

         void Clear();

         std::pair<IDType, std::shared_ptr<const Surface>> GetSurfaceContainingStation(const Station& station) const;

         /// @brief Returns the profile elevation at the specified station
         /// @param station 
         /// @return 
         Float64 Elevation(const Station& station) const;

         /// @brief Returns the surface elevation at the specified station and offset
         /// @param station Station where the elevation is to be computed
         /// @param surfaceID ID of surface from which the elevation is calculated
         /// @param offset Offset from the profile
         /// @return 
         Float64 Elevation(IDType surfaceID, const Station& station, Float64 offset) const;

         /// @brief Returns the surface elevation at the specified station and offset
         /// @param station Station where the elevation is to be computed
         /// @param surface The surface from which the elevation is computed. Surface must be associated with this Profile.
         /// @param offset Offset from the profile
         /// @return 
         Float64 Elevation(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const;

         /// @brief Returns the profile grade at the specified station
         /// @param station 
         /// @return 
         Float64 Grade(const Station& station) const;

         Float64 SurfaceTemplateSegmentSlope(IDType surfaceID, const Station& station, IndexType segmentIdx) const;
         Float64 SurfaceTemplateSegmentSlope(std::shared_ptr<const Surface> surface, const Station& station, IndexType segmentIdx) const;

         /// @brief Computes the cross slope at the specified station and offset
         /// @param station Station where the cross slope is computed
         /// @param surfaceID ID of the surface from which the cross slope is calculated
         /// @param offset Offset from the profile
         /// @return 
         Float64 CrossSlope(IDType surfaceID, const Station& station, Float64 offset) const;

         /// @brief Computes the cross slope at the specified station and offset
         /// @param station Station where the cross slope is computed
         /// @param surface The surface from which the cross slope is computed. Surface must be associated with this Profile.
         /// @param offset Offset from the profile
         /// @return 
         Float64 CrossSlope(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const;

         Float64 GetRidgePointOffset(IDType surfaceID, const Station& station, IndexType ridgePointIdx, IndexType refPointIdx) const;
         Float64 GetRidgePointElevation(IDType surfaceID, const Station& station,IndexType ridgePointIdx) const;
         std::pair<Float64, Float64> GetRidgePointOffsetAndElevation(IDType surfaceID, const Station& station,IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const;

      private:
         std::weak_ptr<Profile> m_Profile;
         std::shared_ptr<Profile> GetProfile() { return m_Profile.lock(); }
         std::shared_ptr<const Profile> GetProfile() const { return m_Profile.lock(); }

         std::weak_ptr<const Alignment> m_Alignment;
         std::map<IDType,std::shared_ptr<const Surface>> m_Surfaces;
         std::vector<std::shared_ptr<ProfileElement>> m_Elements; // These are the input elements, there could be gaps between elements

         struct Element
         {
            Element(Float64 s, Float64 e, std::shared_ptr<ProfileElement> pe) :
               start_station(s), end_station(e), element(pe) {}

            Float64 start_station{ 0 }; // normalized station at start of element
            Float64 end_station{ 0 }; // normalized station at end of element
            std::shared_ptr<ProfileElement> element;
         };
         using Element = Element;
         mutable std::vector<Element> m_ProfileElements;// not the same as m_Elements. This is a fully connected path of elements

         // Returns a vector of Element objects that captures the start and end location
         // along the alignment as well as the profile element itself.
         // Don't access m_ProfileElements directly. Use GetProfileElements because it
         // initializes m_ProfileElements on demand.
         const std::vector<Element>& GetConnectedProfileElements() const;

         // Finds a ProfileElement object that contains the specified distance from start of the alignment.
         // Also determines the distance to the beginning of that ProfileElement
         std::pair<std::shared_ptr<ProfileElement>, Float64> FindElement(Float64 normalizedStation) const;

         // Returns Grade,Elevation,Slope
         std::tuple<Float64,Float64,Float64> GradeAndElevation(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset) const;
         
         // Returns (Grade,Elevation)
         std::pair<Float64,Float64> BeforeProfileGradeAndElevation(const Station& station) const;
         std::pair<Float64, Float64> ProfileGradeAndElevation(const Station& station) const;
         std::pair<Float64, Float64> AfterProfileGradeAndElevation(const Station& station) const;

         // Returns (AdjustedElevation,Slope)
         std::pair<Float64,Float64> AdjustForOffset(std::shared_ptr<const Surface> surface, const Station& station, Float64 offset, Float64 profileElevation) const;
      };
   };
};
