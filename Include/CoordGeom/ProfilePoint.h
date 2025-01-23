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
#include <CoordGeom/Station.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief Object that represent a point in a vertical profile.
      /// A profile point is defined by its station and elevation.
      class COORDGEOMCLASS ProfilePoint
      {
      public:
         ProfilePoint() = default;
         ProfilePoint(const Station& station, Float64 elevation);
         ProfilePoint(const ProfilePoint&) = default;
         ~ProfilePoint() = default;
         ProfilePoint& operator=(const ProfilePoint&) = default;

         bool operator==(const ProfilePoint& other) const;
         bool operator!=(const ProfilePoint& other) const;

         /// @brief Sets the station
         /// @param station 
         void SetStation(const Station& station);

         /// @brief Gets the station
         /// @return 
         const Station& GetStation() const;

         /// @brief Sets the elevation
         /// @param elevation 
         void SetElevation(Float64 elevation);

         /// @brief Gets the elevation
         /// @return 
         Float64 GetElevation() const;

         /// @brief Moves the profile point to a new location
         /// @param station 
         /// @param elevation 
         void Move(const Station& station, Float64 elevation);

         /// @brief Gets the current location of the profile point
         /// @return Pair containing (Station,Elevation) 
         std::pair<Station,Float64> GetLocation() const;

      private:
         Station m_Station{ 0.0 };
         Float64 m_Elevation{ 0.0 };
      };
   };
};
