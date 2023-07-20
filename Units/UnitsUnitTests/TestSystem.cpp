#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestSystem)
	{
	public:
		
		TEST_METHOD(TestDefaults)
		{
			// Default unit system is SI
			Assert::IsTrue(System::GetMassUnit() == Measure::Kilogram);
			Assert::IsTrue(System::GetLengthUnit() == Measure::Meter);
			Assert::IsTrue(System::GetTimeUnit() == Measure::Second);
			Assert::IsTrue(System::GetTemperatureUnit() == Measure::Celsius);
			Assert::IsTrue(System::GetAngleUnit() == Measure::Radian);
			Assert::AreEqual(9.80665, System::GetGravitationalAcceleration());
		}

		TEST_METHOD(TestCustomUnitSystem)
		{
			AutoSystem au; // make sure unit system rolls back to default after we are done messing with it

			// US system Kip and Feet Measure
			System::SetSystemUnits(Measure::KSlug, Measure::Feet, Measure::Second, Measure::Fahrenheit, Measure::Degree);
			Assert::IsTrue(System::GetMassUnit() == Measure::KSlug);
			Assert::IsTrue(System::GetLengthUnit() == Measure::Feet);
			Assert::IsTrue(System::GetTimeUnit() == Measure::Second);
			Assert::IsTrue(System::GetTemperatureUnit() == Measure::Fahrenheit);
			Assert::IsTrue(System::GetAngleUnit() == Measure::Degree);
			Assert::AreEqual(32.174048556430442, System::GetGravitationalAcceleration());

			// US system Kip and Inch measure
			System::SetMassUnit(Measure::_12KSlug);
			System::SetLengthUnit(Measure::Inch);
			Assert::IsTrue(System::GetMassUnit() == Measure::_12KSlug);
			Assert::IsTrue(System::GetLengthUnit() == Measure::Inch);
			Assert::AreEqual(1.0, ConvertToSysUnits(1000.0, Measure::Pound), 0.00001);
			Assert::AreEqual(12.0, ConvertToSysUnits(1.0, Measure::Feet), 0.00001);
			Assert::AreEqual(144000., ConvertFromSysUnits(1.0, Measure::PSF), 0.00001); // KSI -> PSF
		}
	};
}
