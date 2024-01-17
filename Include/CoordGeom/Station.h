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

#include <Units/StationFormat.h>

namespace WBFL
{
   namespace COGO
   {
      class Alignment; // forward declaration

      /// @brief An object the represents a Station along an alignment
      class COORDGEOMCLASS Station
      {
      public:
         Station() = default;
         Station(Float64 station);
         Station(ZoneIndexType zoneIdx, Float64 station);
         Station(const std::_tstring& strStation, const WBFL::Units::StationFormat& format);
         Station(const std::_tstring& strStation);
         Station(const Station&) = default;
         ~Station() = default;
         Station& operator=(const Station&) = default;

         bool operator==(const Station& other) const;
         bool operator!=(const Station& other) const;

         /// @brief Sets the station zone index property.
         /// This property relates this station to a zone in a StationEquation object. A value of INVALID_INDEX means the station is not related to a StationEquation.
         /// @param zoneIdx 
         void SetStationZoneIndex(ZoneIndexType zoneIdx);

         /// @brief Returns the station zone index
         /// @return 
         ZoneIndexType GetStationZoneIndex() const;

         /// @brief Sets the value of the station
         /// @param value The station value in system units
         void SetValue(Float64 value);

         /// @brief Gets the value of the station
         /// @return The station value in system units
         Float64 GetValue() const;

         /// @brief Offsets the station by the specified amount
         /// @param offset 
         void Offset(Float64 offset);

         /// @brief Sets the station zone and station value
         /// @param zoneIdx Station zone index
         /// @param station station value in system units
         void SetStation(ZoneIndexType zoneIdx, Float64 station);

         /// @brief Gets the station zone and station value
         /// @return Returns a pair in the format (StationValue,StationZoneIndex)
         std::pair<Float64,ZoneIndexType> GetStation() const;

         /// @brief Initializes the station object with a string
         /// @param strStation The station represented as a string
         /// @param format Object that represents unit of measure for the stationing (use WBFL::Units::StationFormats::US or WBFL::Units::StationFormats::SI)
         void FromString(const std::_tstring& strStation, const WBFL::Units::StationFormat& format);

         /// @brief Initializes the station object with a string. The string must include the "+" station separator. The unit of measure is determined from the
         /// location of the "+" separator.
         /// @param strStation The station represented as a string
         void FromString(const std::_tstring& strStation);

         /// @brief Creates a text string representing the format
         /// @param format Unit format for the station (use WBFL::Units::StationFormats::US or WBFL::Units::StationFormats::SI)
         /// @param bIncludeStationZone Indicates if the station zone should be appended to the string. e.g. 5+01.23,2 The trailing ,2 indicates station zone 2
         /// @return 
         std::_tstring AsString(const WBFL::Units::StationFormat& format, bool bIncludeStationZone = false) const;

         /// @brief Returns true if the station is normalized
         /// @return 
         bool IsNormalized() const;

      private:
         Float64 m_Value{ 0.0 };
         ZoneIndexType m_ZoneIndex{ INVALID_INDEX };
      };
   };
};
