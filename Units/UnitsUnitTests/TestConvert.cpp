#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestConvert)
	{
	public:
		
		TEST_METHOD(TestUnitConvert)
		{
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::Inch, Measure::Millimeter), 25.4));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::Feet, Measure::Millimeter), 304.8));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::Inch2, Measure::Millimeter2), 645.16));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::Pound, Measure::Newton), 4.4482216));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::KSI, Measure::MPa), 6.8947573));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::KgPerMeter, Measure::LbfPerFeet), 0.6719689));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::LbfPerFeet, Measure::KgPerMeter), 1.4881639));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::LbfPerFeet3, Measure::KgPerMeter3), 16.018463));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::KipPerFeet3, Measure::KgPerMeter3), 16018.46337));
			Assert::IsTrue(IsEqual(Convert(0.0948, Measure::SqrtKSI, Measure::SqrtMPa), 0.2489246));

			Assert::IsTrue(IsEqual(Convert(100.0, Measure::Celsius, Measure::Fahrenheit), 212.0));
			Assert::IsTrue(IsEqual(Convert(212.0, Measure::Fahrenheit, Measure::Celsius), 100.0));
			Assert::IsTrue(IsEqual(Convert(0.0, Measure::Celsius, Measure::Fahrenheit), 32.0));
			Assert::IsTrue(IsEqual(Convert(32.0, Measure::Fahrenheit, Measure::Celsius), 0.0));

			Assert::IsTrue(IsEqual(Convert(1.0, Measure::NewtonMeter2, Measure::LbfFoot2), 2.419823));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::NewtonMeter2, Measure::LbfInch2), 348.45452));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::NewtonMeter2, Measure::KipInch2), 0.348455));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::NewtonMeter2, Measure::KipFoot2), 2.419823e-03));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::NewtonMeter2, Measure::KilonewtonMeter2), 1.0e-03));
			Assert::IsTrue(IsEqual(Convert(1.0, Measure::NewtonMeter2, Measure::NewtonMillimeter2), 1.0e-09));
		}

		TEST_METHOD(TestSystemUnits)
		{
			// Default system units are SI units
			auto value = ConvertToSysUnits(20, Measure::KSI);
			Assert::AreEqual(137895145.86340001, value); // value in system units (Pa)
			value = ConvertFromSysUnits(value, Measure::KSI);
			Assert::AreEqual(20.0, value);

			// change unit system US
			AutoSystem as;
			System::SetMassUnit(WBFL::Units::Measure::KSlug);
			System::SetLengthUnit(WBFL::Units::Measure::Feet);
			System::SetTimeUnit(WBFL::Units::Measure::Second);

			value = ConvertToSysUnits(1000., Measure::MPa);
			Assert::AreEqual(20885.434233159238, value); // value in system units (KSF)
			value = ConvertFromSysUnits(value, Measure::MPa);
			Assert::AreEqual(1000., value, 0.000001);
		}
	};
}
