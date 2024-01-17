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
#include <CoordGeom/CoordGeomTypes.h>
#include <CoordGeom/ProfilePoint.h>

namespace WBFL
{
   namespace COGO
   {
      class Profile;
      class ProfileImpl;

      /// @brief Abstract base class for an element of a vertical profile
      class COORDGEOMCLASS ProfileElement
      {
      private:
         void SetProfile(std::weak_ptr<Profile> profile) { PRECONDITION(profile.lock());  m_Profile = profile; }
         friend Profile;
         friend ProfileImpl; // Not a fan of making the implementation class a friend, but can't figure out how to set the profile
         // on ProfileElements after creation from within the ProfileImpl class (ProfileImpl::CreateProfileElements)

      protected:
         ProfileElement() = default;
         ProfileElement(const ProfileElement&) = default;
         ProfileElement& operator=(const ProfileElement&) = delete;

      public:
         virtual ~ProfileElement() = default;

         /// @brief Returns the Profile associated with this element
         /// @return 
         std::shared_ptr<const Profile> GetProfile() const;
         std::shared_ptr<Profile> GetProfile();

         /// @brief Creates a copy of this profile element
         /// @return 
         virtual std::shared_ptr<ProfileElement> Clone() const = 0;

         /// @brief Returns the start ProfilePoint of this element
         /// @return 
         virtual const ProfilePoint& GetStartPoint() const = 0;

         /// @brief Returns the end ProfilePoint of this element
         /// @return 
         virtual const ProfilePoint& GetEndPoint() const = 0;

         /// @brief Returns the projected length of the element. This length is the distance between stations.
         /// @return 
         virtual Float64 GetLength() const = 0;

         /// @brief Computes the grade and elevation at the specified station
         /// @param station 
         /// @return A pair of the format (Grade,Elevation)
         virtual std::pair<Float64,Float64> ComputeGradeAndElevation(const Station& station) const = 0;

      protected:
         /// @brief Subclasses should call this method whenever their data changes in such a way
         /// to modify the layout of the profile.
         void OnProfileElementChanged();

      private:
         std::weak_ptr<Profile> m_Profile;
      };
   };
};
