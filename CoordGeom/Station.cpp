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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/Station.h>
#include <CoordGeom/Utilities.h>
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
   Float64 station;
   ZoneIndexType zoneIdx;
   try
   {
      std::tie(station, zoneIdx) = format.FromString(strStation);
   }
   catch (...)
   {
      THROW_COGO(WBFL_COGO_E_STATION);
   }

   m_Value = station;
   m_ZoneIndex = zoneIdx;
}

std::_tstring Station::AsString(const WBFL::Units::StationFormat& format, bool bIncludeStationZone) const
{
   return format.AsString(m_Value,bIncludeStationZone ? m_ZoneIndex : INVALID_INDEX); // let the format object create the string for the basic station
}

bool Station::IsNormalized() const
{
   return m_ZoneIndex == INVALID_INDEX;
}


#if defined _UNITTEST
#include <Units/Convert.h>
#include <Units\AutoSystem.h>
bool Station::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Station");

   Station station;
   TRY_TESTME(IsZero(station.GetValue()));
   TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

   station.SetValue(100);
   station.SetStationZoneIndex(2);
   TRY_TESTME(IsEqual(station.GetValue(), 100.0));
   TRY_TESTME(station.GetStationZoneIndex() == 2);

   station.SetStation(3, 200);
   Float64 value;
   ZoneIndexType zoneIdx;
   std::tie(value,zoneIdx) = station.GetStation();
   TRY_TESTME(IsEqual(value, 200.0));
   TRY_TESTME(zoneIdx == 3);

   {
      // Work in feet for US stations
      WBFL::Units::AutoSystem au;
      WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);

      // Valid US station
      std::_tstring usStation(L"3+34.54");
      station.FromString(usStation, WBFL::Units::StationFormats::US);
      TRY_TESTME(IsEqual(station.GetValue(), 334.54));
      TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

      std::_tstring usStation2(L"-3+34.54");
      station.FromString(usStation2, WBFL::Units::StationFormats::US);
      TRY_TESTME(IsEqual(station.GetValue(), -334.54));
      TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

      std::_tstring usStationWithZone(L"3+34.54,5");
      station.FromString(usStationWithZone, WBFL::Units::StationFormats::US);
      TRY_TESTME(IsEqual(station.GetValue(), 334.54));
      TRY_TESTME(station.GetStationZoneIndex() == 4);

      station.SetValue(WBFL::Units::ConvertToSysUnits(3434.34, WBFL::Units::Measure::Feet));
      auto strStation = station.AsString(WBFL::Units::StationFormats::US, false);
      TRY_TESTME(strStation == std::_tstring(L"34+34.34"));

      station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Feet));
      strStation = station.AsString(WBFL::Units::StationFormats::US, false);
      TRY_TESTME(strStation == std::_tstring(L"99+99.99"));

      station.SetValue(WBFL::Units::ConvertToSysUnits(-9999.99, WBFL::Units::Measure::Feet));
      strStation = station.AsString(WBFL::Units::StationFormats::US, false);
      TRY_TESTME(strStation == std::_tstring(L"-99+99.99"));

      station.SetValue(WBFL::Units::ConvertToSysUnits(0.45, WBFL::Units::Measure::Feet));
      strStation = station.AsString(WBFL::Units::StationFormats::US, false);
      TRY_TESTME(strStation == std::_tstring(L"0+00.45"));

      station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Feet));
      station.SetStationZoneIndex(INVALID_INDEX);
      strStation = station.AsString(WBFL::Units::StationFormats::US, true);
      TRY_TESTME(strStation == std::_tstring(L"99+99.99"));

      station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Feet));
      station.SetStationZoneIndex(3);
      strStation = station.AsString(WBFL::Units::StationFormats::US, true);
      TRY_TESTME(strStation == std::_tstring(L"99+99.99,4"));

      // Bad US Station (use the SI station)
      try { station.FromString(L"3+034.54", WBFL::Units::StationFormats::US); }
      catch (...) { TRY_TESTME(true); }
   }

   {
      // Valid SI station
      std::_tstring siStation(L"3+034.54");
      station.FromString(siStation, WBFL::Units::StationFormats::SI);
      TRY_TESTME(IsEqual(station.GetValue(), 3034.54));
      TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

      std::_tstring siStation2(L"-3+034.54");
      station.FromString(siStation2, WBFL::Units::StationFormats::SI);
      TRY_TESTME(IsEqual(station.GetValue(), -3034.54));
      TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

      station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Meter));
      auto strStation = station.AsString(WBFL::Units::StationFormats::SI, false);
      TRY_TESTME(strStation == std::_tstring(L"9+999.990"));

      station.SetValue(WBFL::Units::ConvertToSysUnits(0.45, WBFL::Units::Measure::Meter));
      strStation = station.AsString(WBFL::Units::StationFormats::SI, false);
      TRY_TESTME(strStation == std::_tstring(L"0+000.450"));

      station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Meter));
      station.SetStationZoneIndex(3);
      strStation = station.AsString(WBFL::Units::StationFormats::SI, true);
      TRY_TESTME(strStation == std::_tstring(L"9+999.990,4"));

      // Bad SI Station (use the US station)
      try { station.FromString(L"3+34.54", WBFL::Units::StationFormats::SI); }
      catch (...) { TRY_TESTME(true); }
   }


   // String without units
   station.FromString(L"1+25");
   TRY_TESTME(IsEqual(station.GetValue(), WBFL::Units::ConvertToSysUnits(125.0,WBFL::Units::Measure::Feet)));
   TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

   station.FromString(L"-3+34.34");
   TRY_TESTME(IsEqual(station.GetValue(), WBFL::Units::ConvertToSysUnits(-334.34, WBFL::Units::Measure::Feet)));
   TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

   station.FromString(L"35+353.35");
   TRY_TESTME(IsEqual(station.GetValue(), WBFL::Units::ConvertToSysUnits(35353.35, WBFL::Units::Measure::Meter)));
   TRY_TESTME(station.GetStationZoneIndex() == INVALID_INDEX);

   try { station.FromString(L"125.00"); } // "+" is required
   catch (...) { TRY_TESTME(true); }

   TESTME_EPILOG("Station");
}
#endif // _UNITTEST


