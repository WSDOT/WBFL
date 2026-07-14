///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright � 1999-2026  Washington State Department of Transportation
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

#include <System\Exception.h>
#include <Units\UnitsExp.h>

namespace WBFL
{
   namespace Units
   {
      /// Converts a floating point number into stationing format.
      class UNITSCLASS StationFormat
      {
      public:
         enum class UnitOfMeasure { Meter, ///< Stations are in meters
                                    Feet   ///< Stations are in feet
         };

         StationFormat() = default;
         StationFormat(const StationFormat&) = default;

         /// Constructs a station formatter for the given unit of measure.
         StationFormat(UnitOfMeasure unitOfMeasure);

         virtual ~StationFormat();

         StationFormat& operator=(const StationFormat&) = default;

         /// Returns true if other has the same unit of measure as this station formatter.
         bool operator==(const StationFormat& other) const;

         /// Returns true if other does not have the same unit of measure as this station formatter.
         bool operator!=(const StationFormat& other) const;

         /// Returns the station as a pair in the format (StationValue,ZoneIndex)
         /// If station is ill-formed, an unitXUnit exception will be thrown.
         std::pair<Float64, ZoneIndexType> FromString(const std::_tstring& station) const;

         /// Returns a string that represents the station.
         std::_tstring AsString(Float64 station, ZoneIndexType zoneIdx = INVALID_INDEX) const;

         /// Sets the unit of measure used to format and parse stations.
         void SetUnitOfMeasure(UnitOfMeasure unitOfMeasure);

         /// Returns the unit of measure used to format and parse stations.
         UnitOfMeasure GetUnitOfMeasure() const;

      private:
         UnitOfMeasure m_UnitOfMeasure{ UnitOfMeasure::Meter };
      };


      /// Encapsulates instantiations of station formats for SI and US unit systems.
      class UNITSCLASS StationFormats
      {
      public:
         StationFormats() = delete;
         ~StationFormats() = delete;

         static const StationFormat SI; ///< SI-unit (meter) stationing, e.g. "3+034.540" (3 digits before "+", 3 decimal places)
         static const StationFormat US; ///< US-unit (feet) stationing, e.g. "3+34.54" (2 digits before "+", 2 decimal places)
      };
   };
};
