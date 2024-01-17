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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/Station.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

#include <Units/XUnit.h>

using namespace WBFL::COGO;

Station::Station(Float64 normalizedStation) :
   m_Value(normalizedStation), m_ZoneIndex(INVALID_INDEX)
{
}

Station::Station(ZoneIndexType zoneIdx, Float64 station) :
   m_Value(station), m_ZoneIndex(zoneIdx)
{
}

Station::Station(const std::_tstring& strStation, const WBFL::Units::StationFormat& format)
{
   FromString(strStation, format);
}

Station::Station(const std::_tstring& strStation)
{
   FromString(strStation);
}

bool Station::operator==(const Station& other) const
{
   return IsEqual(m_Value, other.m_Value) && m_ZoneIndex == other.m_ZoneIndex;
}

bool Station::operator!=(const Station& other) const
{
   return !operator==(other);
}

void Station::SetStationZoneIndex(ZoneIndexType zoneIdx)
{
   m_ZoneIndex = zoneIdx;
}

ZoneIndexType Station::GetStationZoneIndex() const
{
   return m_ZoneIndex;
}

void Station::SetValue(Float64 value)
{
   m_Value = value;
}

Float64 Station::GetValue() const
{
   return m_Value;
}

void Station::Offset(Float64 offset)
{
   m_Value += offset;
}

void Station::SetStation(ZoneIndexType zoneIdx, Float64 station)
{
   m_ZoneIndex = zoneIdx;
   m_Value = station;
}

std::pair<Float64,ZoneIndexType> Station::GetStation() const
{
   return std::make_pair(m_Value, m_ZoneIndex);
}

void Station::FromString(const std::_tstring& strStation)
{
   auto pos_plus = strStation.find('+');
   if (pos_plus == std::_tstring::npos) THROW_COGO(WBFL_COGO_E_STATION); // string must have a '+' to determine format

   auto pos_decimal = strStation.find('.', pos_plus);
   if (pos_decimal == std::_tstring::npos) pos_decimal = strStation.length();

   auto num_secondary_digits = pos_decimal - pos_plus - 1;
   if (num_secondary_digits == 2)
      FromString(strStation, WBFL::Units::StationFormats::US);
   else if (num_secondary_digits == 3)
      FromString(strStation, WBFL::Units::StationFormats::SI);
   else
      THROW_COGO(WBFL_COGO_E_STATION);

}

void Station::FromString(const std::_tstring& strStation, const WBFL::Units::StationFormat& format)
{
   try
   {
      auto [station, zoneIdx] = format.FromString(strStation);
      m_Value = station;
      m_ZoneIndex = zoneIdx;
   }
   catch (...)
   {
      THROW_COGO(WBFL_COGO_E_STATION);
   }
}

std::_tstring Station::AsString(const WBFL::Units::StationFormat& format, bool bIncludeStationZone) const
{
   return format.AsString(m_Value,bIncludeStationZone ? m_ZoneIndex : INVALID_INDEX); // let the format object create the string for the basic station
}

bool Station::IsNormalized() const
{
   return m_ZoneIndex == INVALID_INDEX;
}
