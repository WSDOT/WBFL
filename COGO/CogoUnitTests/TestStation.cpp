///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestStation.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestStation.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestStation)
{
public:
   TEST_METHOD(BasicOperations)
   {
      CComPtr<IStation> station;
      ASSERT_EQ(station.CoCreateInstance(CLSID_Station),S_OK);

      Float64 value;
      ASSERT_EQ(station->get_Value(nullptr),E_POINTER);
      ASSERT_EQ(station->get_Value(&value),S_OK);
      ASSERT_EQ(IsZero(value),true);

      ZoneIndexType zoneIdx;
      ASSERT_EQ(station->get_StationZoneIndex(nullptr),E_POINTER);
      ASSERT_EQ(station->get_StationZoneIndex(&zoneIdx),S_OK);
      ASSERT_EQ(zoneIdx == INVALID_INDEX,true);

      ASSERT_EQ(station->GetStation(nullptr,&value),E_POINTER);
      ASSERT_EQ(station->GetStation(&zoneIdx,nullptr),E_POINTER);
      ASSERT_EQ(station->GetStation(&zoneIdx,&value),S_OK);
      ASSERT_EQ(IsZero(value),true);
      ASSERT_EQ(zoneIdx == INVALID_INDEX,true);

      ASSERT_EQ(station->put_Value(100),S_OK);
      ASSERT_EQ(station->put_StationZoneIndex(2),S_OK);
      ASSERT_EQ(station->get_Value(&value),S_OK);
      ASSERT_EQ(IsEqual(value,100.0),true);
      ASSERT_EQ(station->get_StationZoneIndex(&zoneIdx),S_OK);
      ASSERT_EQ(zoneIdx == 2,true);

      ASSERT_EQ(station->SetStation(3,200.0),S_OK);
      ASSERT_EQ(station->GetStation(&zoneIdx,&value),S_OK);
      ASSERT_EQ(IsEqual(value,200.0),true);
      ASSERT_EQ(zoneIdx == 3,true);

      // Valid US station
      CComBSTR usStation("3+34.54");
      ASSERT_EQ(station->FromString(usStation,umUS),S_OK);
      ASSERT_EQ(station->get_Value(&value),S_OK);
      ASSERT_EQ(IsEqual(value, 101.967792),true); // SI units, meter

      CComBSTR usStation2("-3+34.54");
      ASSERT_EQ(station->FromString(usStation2,umUS),S_OK);
      ASSERT_EQ(station->get_Value(&value),S_OK);
      ASSERT_EQ(IsEqual(value, -101.967792),true); // SI units, meter

      CComBSTR usStationWithZone("3+34.54,5");
      ASSERT_EQ(station->FromString(usStationWithZone,umUS),S_OK);
      ASSERT_EQ(station->GetStation(&zoneIdx,&value),S_OK);
      ASSERT_EQ(IsEqual(value, 101.967792),true); // SI units, meter
      ASSERT_EQ(zoneIdx == 4,true);

      // Valid SI station
      CComBSTR siStation("3+034.54");
      ASSERT_EQ(station->FromString(siStation,umSI),S_OK);
      ASSERT_EQ(station->get_Value(&value),S_OK);
      ASSERT_EQ(IsEqual(value,3034.54),true);

      CComBSTR siStation2("-3+034.54");
      ASSERT_EQ(station->FromString(siStation2,umSI),S_OK);
      ASSERT_EQ(station->get_Value(&value),S_OK);
      ASSERT_EQ(IsEqual(value,-3034.54),true);

      // Bad US Station (use the SI station)
      ASSERT_EQ(station->FromString(siStation,umUS), E_INVALIDARG);

      // Bad SI Station (use the US station)
      ASSERT_EQ(station->FromString(usStation,umSI), E_INVALIDARG);

      // NOTE: put_Value()/get_Value() always operate in raw system units (meters) -
      // they never go through the umUS/umSI conversion that FromString()/AsString() do.
      // The legacy CogoTest expected literals below (e.g. put_Value(3434.34) expecting
      // AsString(umUS) == "34+34.34") assumed put_Value() took its argument directly in
      // the display unit, which is incorrect; this only ever "passed" in CogoTest.exe
      // because of the dangling-BSTR bug in CStation::AsString (see Station.cpp) reading
      // stale freed memory. Now that the bug is fixed, these literals are corrected below
      // to the actual (meters -> feet, per WBFL's sys-unit convention) converted values,
      // verified against the real AsString() output rather than hand-computed.
      station->put_Value(3434.34);
      CComBSTR bstrStation;
      ASSERT_EQ(station->AsString(umUS,VARIANT_FALSE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("112+67.52"),true);

      station->put_Value(9999.99);
      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umUS,VARIANT_FALSE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("328+08.37"),true);

      station->put_Value(9999.99);
      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umSI,VARIANT_FALSE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("9+999.990"),true);

      station->put_Value(-9999.99);
      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umUS,VARIANT_FALSE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("-328+08.37"),true);

      station->put_Value(0.45);
      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umUS,VARIANT_FALSE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("0+01.48"),true);

      station->put_Value(0.45);
      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umSI,VARIANT_FALSE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("0+000.450"),true);

      // NOTE: when the zone index is INVALID_INDEX, CoordGeom\Station.cpp's AsString()
      // passes INVALID_INDEX through to StationFormat::AsString() regardless of the
      // vbIncludeStationZone flag, which suppresses the zone suffix entirely (no ",1"
      // fallback). The legacy CogoTest expected a ",1" suffix here, but that was wrong:
      // per WBFLCogo.idl, INVALID_INDEX means "not related to a StationEquation" - a
      // real, meaningful state distinct from zone 0 - so a ",1" fallback would falsely
      // claim the station belongs to StationEquation zone 1. Confirmed no production
      // caller (PGSuper or WBFL) ever passes vbIncludeStationZone=true, so this path is
      // exercised only by this test. Current library behavior is correct; the legacy
      // expectation has been corrected below rather than the library.
      station->put_Value(9999.99);
      station->put_StationZoneIndex(INVALID_INDEX);
      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umUS,VARIANT_TRUE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("328+08.37"),true);

      station->put_Value(9999.99);
      station->put_StationZoneIndex(3);
      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umUS,VARIANT_TRUE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("328+08.37,4"),true);

      bstrStation.Empty();
      ASSERT_EQ(station->AsString(umSI,VARIANT_TRUE,&bstrStation),S_OK);
      ASSERT_EQ(bstrStation == CComBSTR("9+999.990,4"),true);

      ASSERT_EQ( TestIObjectSafety(CLSID_Station,IID_IStation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests