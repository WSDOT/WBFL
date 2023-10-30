#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestAutoSystem)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// Test default unit system
			Assert::IsTrue(System::GetMassUnit() == WBFL::Units::Measure::Kilogram);
			Assert::IsTrue(System::GetLengthUnit() == WBFL::Units::Measure::Meter);
			Assert::IsTrue(System::GetTimeUnit() == WBFL::Units::Measure::Second);
			Assert::IsTrue(System::GetTemperatureUnit() == WBFL::Units::Measure::Celsius);
			Assert::IsTrue(System::GetAngleUnit() == WBFL::Units::Measure::Radian);

			{
				AutoSystem as;
				// change unit system
				System::SetMassUnit(WBFL::Units::Measure::KSlug);
				System::SetLengthUnit(WBFL::Units::Measure::Feet);
				System::SetTimeUnit(WBFL::Units::Measure::Minute);
				System::SetTemperatureUnit(WBFL::Units::Measure::Fahrenheit);
				System::SetAngleUnit(WBFL::Units::Measure::Degree);

				// test that unit system was changed
				Assert::IsTrue(System::GetMassUnit() == WBFL::Units::Measure::KSlug);
				Assert::IsTrue(System::GetLengthUnit() == WBFL::Units::Measure::Feet);
				Assert::IsTrue(System::GetTimeUnit() == WBFL::Units::Measure::Minute);
				Assert::IsTrue(System::GetTemperatureUnit() == WBFL::Units::Measure::Fahrenheit);
				Assert::IsTrue(System::GetAngleUnit() == WBFL::Units::Measure::Degree);
			}

			// test that unitbsystem reverts to original values
			Assert::IsTrue(System::GetMassUnit() == WBFL::Units::Measure::Kilogram);
			Assert::IsTrue(System::GetLengthUnit() == WBFL::Units::Measure::Meter);
			Assert::IsTrue(System::GetTimeUnit() == WBFL::Units::Measure::Second);
			Assert::IsTrue(System::GetTemperatureUnit() == WBFL::Units::Measure::Celsius);
			Assert::IsTrue(System::GetAngleUnit() == WBFL::Units::Measure::Radian);
		}
	};
}
