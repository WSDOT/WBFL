#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestStationFormat)
	{
	public:

      TEST_METHOD(TestDefaultValues)
      {
         StationFormat sf;
         Assert::IsTrue(sf.GetUnitOfMeasure() == StationFormat::UnitOfMeasure::Meter);

         sf.SetUnitOfMeasure(StationFormat::UnitOfMeasure::Feet);
         Assert::IsTrue(sf.GetUnitOfMeasure() == StationFormat::UnitOfMeasure::Feet);

         StationFormat sf1;
         StationFormat sf2(StationFormat::UnitOfMeasure::Feet);
         Assert::IsFalse(sf1 == sf2);
         Assert::IsFalse(StationFormats::SI == StationFormats::US);
         Assert::IsTrue(sf1 == StationFormats::SI);
         Assert::IsTrue(sf2 == StationFormats::US);
      }
		
		TEST_METHOD(TestSIFormat)
		{
         auto siFormat = StationFormats::SI;

         std::_tstring siStation(L"3+034.54");
         Assert::IsTrue(IsEqual(siFormat.FromString(siStation).first, 3034.54));

         std::_tstring siStation2(L"-3+034.54");
         Assert::IsTrue(IsEqual(siFormat.FromString(siStation2).first, -3034.54));

         Assert::IsTrue(siFormat.AsString(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Meter)) == std::_tstring(L"9+999.990"));
         Assert::IsTrue(siFormat.AsString(WBFL::Units::ConvertToSysUnits(0.45, WBFL::Units::Measure::Meter)) == std::_tstring(L"0+000.450"));

         // Bad SI Station (use the US station)
         try { siFormat.FromString(L"3+34.54"); }
         catch (XUnit& e) { Assert::IsTrue(e.GetReasonCode() == XUnit::Reason::BadStationFormat); }
		}

      TEST_METHOD(TestUSFormat)
      {
         // We want to work in feet
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetLengthUnit(WBFL::Units::Measure::Feet);

         auto usFormat = StationFormats::US;

         // Valid US station
         std::_tstring usStation(L"3+34.54");
         Assert::IsTrue(IsEqual(usFormat.FromString(usStation).first, 334.54));

         std::_tstring usStation2(L"-3+34.54");
         Assert::IsTrue(IsEqual(usFormat.FromString(usStation2).first, -334.54));

         Assert::IsTrue(usFormat.AsString(WBFL::Units::ConvertToSysUnits(3434.34, WBFL::Units::Measure::Feet)) == std::_tstring(L"34+34.34"));
         Assert::IsTrue(usFormat.AsString(WBFL::Units::ConvertToSysUnits(9999.99, WBFL::Units::Measure::Feet)) == std::_tstring(L"99+99.99"));
         Assert::IsTrue(usFormat.AsString(WBFL::Units::ConvertToSysUnits(-9999.99, WBFL::Units::Measure::Feet)) == std::_tstring(L"-99+99.99"));
         Assert::IsTrue(usFormat.AsString(WBFL::Units::ConvertToSysUnits(0.45, WBFL::Units::Measure::Feet)) == std::_tstring(L"0+00.45"));

         // Bad US Station (use the SI station)
         try { usFormat.FromString(L"3+034.54"); }
         catch (XUnit& e) { Assert::IsTrue(e.GetReasonCode() == XUnit::Reason::BadStationFormat); }
      }
	};
}
