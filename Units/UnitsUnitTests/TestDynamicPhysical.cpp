#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestDynamicPhysical)
	{
	public:

		TEST_METHOD(TestBasic)
		{
			DynamicPhysical crazy_unit(1.0, 2.0, 3.0, 4.0, 5.0, 999.99, _T("CrazyUnit"));
			Assert::AreEqual(9999.90, crazy_unit.ConvertFrom(10.0));
			Assert::AreEqual(10 / 999.99, crazy_unit.ConvertTo(10.0));
			Assert::AreEqual(0.0, crazy_unit.GetPreTerm());
			Assert::AreEqual(999.99, crazy_unit.GetConvFactor());
			Assert::AreEqual(0.0, crazy_unit.GetPostTerm());
			Assert::AreEqual(_T("CrazyUnit"), crazy_unit.UnitTag().c_str());
			Assert::AreEqual(1.0, crazy_unit.MassDim());
			Assert::AreEqual(2.0, crazy_unit.LengthDim());
			Assert::AreEqual(3.0, crazy_unit.TimeDim());
			Assert::AreEqual(4.0, crazy_unit.TemperatureDim());
			Assert::AreEqual(5.0, crazy_unit.AngleDim());
		}

		TEST_METHOD(TestExtended)
		{
			DynamicPhysical crazy_unit(1.0, 2.0, 3.0, 4.0, 5.0, 20.0, 999.99, 30.0, _T("CrazyUnit"));
			Assert::AreEqual(30029.7, crazy_unit.ConvertFrom(10.0));
			Assert::IsTrue(IsEqual(-20.020, crazy_unit.ConvertTo(10.0)));
			Assert::AreEqual(20.0, crazy_unit.GetPreTerm());
			Assert::AreEqual(999.99, crazy_unit.GetConvFactor());
			Assert::AreEqual(30.0, crazy_unit.GetPostTerm());
			Assert::AreEqual(_T("CrazyUnit"), crazy_unit.UnitTag().c_str());
			Assert::AreEqual(1.0, crazy_unit.MassDim());
			Assert::AreEqual(2.0, crazy_unit.LengthDim());
			Assert::AreEqual(3.0, crazy_unit.TimeDim());
			Assert::AreEqual(4.0, crazy_unit.TemperatureDim());
			Assert::AreEqual(5.0, crazy_unit.AngleDim());
		}

		TEST_METHOD(TestEquality)
		{
			DynamicPhysical a(1.0, 0.0, 0.0, 0.0, 0.0, 0.3048, _T("ft"));
			DynamicPhysical b(1.0, 0.0, 0.0, 0.0, 0.0, 0.3048, _T("ft"));
			DynamicPhysical c(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, _T("m"));
			Assert::IsTrue(a == b);
			Assert::IsFalse(a == c);
		}

		TEST_METHOD(TestIsSameDimension)
		{
			DynamicPhysical length(0.0, 1.0, 0.0, 0.0, 0.0, 0.3048, _T("ft"));
			DynamicPhysical length2(0.0, 1.0, 0.0, 0.0, 0.0, 1.0, _T("m"));
			DynamicPhysical force(1.0, 1.0, -2.0, 0.0, 0.0, 4.4482216, _T("lbf"));

			Assert::IsTrue(length.IsSameDimension(length2));
			Assert::IsFalse(length.IsSameDimension(force));
		}

		// Regression coverage ported from WBFLUnitServer's CTestUnitServer::Test() "Temp2" case: a custom
		// unit type of dimensionality Temperature^2, proving DynamicPhysical reproduces the compound-
		// dimensionality math the COM facade will eventually rely on.
		TEST_METHOD(TestTemp2)
		{
			AutoSystem as; // default system units are kg-m-sec-C-rad

			DynamicPhysical F2(0.0, 0.0, 0.0, 2.0, 0.0, (5. / 9.) * (5. / 9.), _T("F2"));
			DynamicPhysical C2(0.0, 0.0, 0.0, 2.0, 0.0, 1.0, _T("C2"));

			Assert::IsTrue(IsEqual(Convert(15.0, F2, C2), 4.629629629));

			auto result = ConvertToSysUnits(15.0, F2);
			result = ConvertFromSysUnits(result, C2);
			Assert::IsTrue(IsEqual(result, 4.629629629));
		}

		// Regression coverage ported from WBFLUnitServer's CTestUnitServer::Test() "Weird" case: a custom
		// unit type of dimensionality Length^2 * Temperature^3.
		TEST_METHOD(TestWeird)
		{
			AutoSystem as; // default system units are kg-m-sec-C-rad

			DynamicPhysical weirdFrom(0.0, 2.0, 0.0, 3.0, 0.0, (5. / 9.) * (5. / 9.) * (5. / 9.) * 0.3048 * 0.3048, _T("WeirdFrom"));
			DynamicPhysical weirdTo(0.0, 2.0, 0.0, 3.0, 0.0, 1.0, _T("WeirdTo"));

			Assert::IsTrue(IsEqual(Convert(15.0, weirdFrom, weirdTo), 0.238948148148));

			auto result = ConvertToSysUnits(15.0, weirdFrom);
			result = ConvertFromSysUnits(result, weirdTo);
			Assert::IsTrue(IsEqual(result, 0.238948148148));
		}

		TEST_METHOD(TestDimensionMismatchThrows)
		{
			DynamicPhysical length(0.0, 1.0, 0.0, 0.0, 0.0, 0.3048, _T("ft"));
			DynamicPhysical force(1.0, 1.0, -2.0, 0.0, 0.0, 4.4482216, _T("lbf"));

			Assert::ExpectException<XUnit>([&length, &force]() { Convert(1.0, length, force); });

			try { Convert(1.0, length, force); }
			catch (XUnit& ex)
			{
				Assert::IsTrue(ex.GetReasonCode() == XUnit::Reason::DimensionMismatch);
			}
		}

		// Mixed conversion between a compile-time-dimensioned unit (a PhysicalT/PhysicalExT alias, here
		// Measure::Feet/Measure::Meter) and a DynamicPhysical of the same dimensionality.
		TEST_METHOD(TestMixedConvert)
		{
			DynamicPhysical dynFeet(0.0, 1.0, 0.0, 0.0, 0.0, 0.3048, _T("ft"));

			Assert::IsTrue(IsEqual(Convert(1.0, Measure::Feet, dynFeet), 1.0));
			Assert::IsTrue(IsEqual(Convert(1.0, dynFeet, Measure::Feet), 1.0));

			Assert::IsTrue(IsEqual(Convert(1.0, Measure::Meter, dynFeet), 3.2808398950131));
			Assert::IsTrue(IsEqual(Convert(3.2808398950131, dynFeet, Measure::Meter), 1.0));
		}

		TEST_METHOD(TestMixedConvertDimensionMismatchThrows)
		{
			DynamicPhysical dynForce(1.0, 1.0, -2.0, 0.0, 0.0, 4.4482216, _T("lbf"));

			Assert::ExpectException<XUnit>([&dynForce]() { Convert(1.0, Measure::Feet, dynForce); });
			Assert::ExpectException<XUnit>([&dynForce]() { Convert(1.0, dynForce, Measure::Feet); });

			try { Convert(1.0, Measure::Feet, dynForce); }
			catch (XUnit& ex)
			{
				Assert::IsTrue(ex.GetReasonCode() == XUnit::Reason::DimensionMismatch);
			}
		}
	};
}
