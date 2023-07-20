#include "pch.h"
#include "CppUnitTest.h"

#include <Units/Convert.h>
#include <Units/AutoSystem.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestStation)
	{
	public:
		
		TEST_METHOD(Test)
		{
         Station station;
         Assert::IsTrue(IsZero(station.GetValue()));
         Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

         station.SetValue(100);
         station.SetStationZoneIndex(2);
         Assert::IsTrue(IsEqual(station.GetValue(), 100.0));
         Assert::IsTrue(station.GetStationZoneIndex() == 2);

         station.SetStation(3, 200);
         Float64 value;
         ZoneIndexType zoneIdx;
         std::tie(value, zoneIdx) = station.GetStation();
         Assert::IsTrue(IsEqual(value, 200.0));
         Assert::IsTrue(zoneIdx == 3);

         {
            // Work in feet for US stations
            WBFL::Units::AutoSystem au;
            WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);

            // Valid US station
            std::_tstring usStation(L"3+34.54");
            station.FromString(usStation, WBFL::Units::StationFormats::US);
            Assert::IsTrue(IsEqual(station.GetValue(), 334.54));
            Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

            std::_tstring usStation2(L"-3+34.54");
            station.FromString(usStation2, WBFL::Units::StationFormats::US);
            Assert::IsTrue(IsEqual(station.GetValue(), -334.54));
            Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

            std::_tstring usStationWithZone(L"3+34.54,5");
            station.FromString(usStationWithZone, WBFL::Units::StationFormats::US);
            Assert::IsTrue(IsEqual(station.GetValue(), 334.54));
            Assert::IsTrue(station.GetStationZoneIndex() == 4);

            station.SetValue(WBFL::Units::ConvertToSysUnits(3434.34, WBFL::Units::Measure::Feet));
            auto strStation = station.AsString(WBFL::Units::StationFormats::US, false);
            Assert::IsTrue(strStation == std::_tstring(L"34+34.34"));

            station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Feet));
            strStation = station.AsString(WBFL::Units::StationFormats::US, false);
            Assert::IsTrue(strStation == std::_tstring(L"99+99.99"));

            station.SetValue(WBFL::Units::ConvertToSysUnits(-9999.99, WBFL::Units::Measure::Feet));
            strStation = station.AsString(WBFL::Units::StationFormats::US, false);
            Assert::IsTrue(strStation == std::_tstring(L"-99+99.99"));

            station.SetValue(WBFL::Units::ConvertToSysUnits(0.45, WBFL::Units::Measure::Feet));
            strStation = station.AsString(WBFL::Units::StationFormats::US, false);
            Assert::IsTrue(strStation == std::_tstring(L"0+00.45"));

            station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Feet));
            station.SetStationZoneIndex(INVALID_INDEX);
            strStation = station.AsString(WBFL::Units::StationFormats::US, true);
            Assert::IsTrue(strStation == std::_tstring(L"99+99.99"));

            station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Feet));
            station.SetStationZoneIndex(3);
            strStation = station.AsString(WBFL::Units::StationFormats::US, true);
            Assert::IsTrue(strStation == std::_tstring(L"99+99.99,4"));

            // Bad US Station (use the SI station)
            try { station.FromString(L"3+034.54", WBFL::Units::StationFormats::US); }
            catch (...) { Assert::IsTrue(true); }
         }

         {
            // Valid SI station
            std::_tstring siStation(L"3+034.54");
            station.FromString(siStation, WBFL::Units::StationFormats::SI);
            Assert::IsTrue(IsEqual(station.GetValue(), 3034.54));
            Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

            std::_tstring siStation2(L"-3+034.54");
            station.FromString(siStation2, WBFL::Units::StationFormats::SI);
            Assert::IsTrue(IsEqual(station.GetValue(), -3034.54));
            Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

            station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Meter));
            auto strStation = station.AsString(WBFL::Units::StationFormats::SI, false);
            Assert::IsTrue(strStation == std::_tstring(L"9+999.990"));

            station.SetValue(WBFL::Units::ConvertToSysUnits(0.45, WBFL::Units::Measure::Meter));
            strStation = station.AsString(WBFL::Units::StationFormats::SI, false);
            Assert::IsTrue(strStation == std::_tstring(L"0+000.450"));

            station.SetValue(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Meter));
            station.SetStationZoneIndex(3);
            strStation = station.AsString(WBFL::Units::StationFormats::SI, true);
            Assert::IsTrue(strStation == std::_tstring(L"9+999.990,4"));

            // Bad SI Station (use the US station)
            try { station.FromString(L"3+34.54", WBFL::Units::StationFormats::SI); }
            catch (...) { Assert::IsTrue(true); }
         }


         // String without units
         station.FromString(L"1+25");
         Assert::IsTrue(IsEqual(station.GetValue(), WBFL::Units::ConvertToSysUnits(125.0, WBFL::Units::Measure::Feet)));
         Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

         station.FromString(L"-3+34.34");
         Assert::IsTrue(IsEqual(station.GetValue(), WBFL::Units::ConvertToSysUnits(-334.34, WBFL::Units::Measure::Feet)));
         Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

         station.FromString(L"35+353.35");
         Assert::IsTrue(IsEqual(station.GetValue(), WBFL::Units::ConvertToSysUnits(35353.35, WBFL::Units::Measure::Meter)));
         Assert::IsTrue(station.GetStationZoneIndex() == INVALID_INDEX);

         try { station.FromString(L"125.00"); } // "+" is required
         catch (...) { Assert::IsTrue(true); }
      }
	};
}
