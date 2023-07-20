#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestPhysical)
	{
	public:
		
		TEST_METHOD(TestTemplate)
		{
			PhysicalT<10, 20, 30, 40, 50> crazy_phyiscal_unit(999.99,_T("CrazyUnit"));
			Assert::AreEqual(9999.90, crazy_phyiscal_unit.ConvertFrom(10.0));
			Assert::AreEqual(10 / 999.99, crazy_phyiscal_unit.ConvertTo(10.0));
			Assert::AreEqual(999.99, crazy_phyiscal_unit.GetConvFactor());
			Assert::AreEqual(_T("CrazyUnit"), crazy_phyiscal_unit.UnitTag().c_str());
			Assert::AreEqual(1.0, crazy_phyiscal_unit.MassDim());
			Assert::AreEqual(2.0, crazy_phyiscal_unit.LengthDim());
			Assert::AreEqual(3.0, crazy_phyiscal_unit.TimeDim());
			Assert::AreEqual(4.0, crazy_phyiscal_unit.TemperatureDim());
			Assert::AreEqual(5.0, crazy_phyiscal_unit.AngleDim());
		}

		TEST_METHOD(TestTemplateEx)
		{
			PhysicalExT<10, 20, 30, 40, 50> crazy_phyiscal_unit(20.0, 999.99, 30.0, _T("CrazyUnit"));
			Assert::AreEqual(30029.7, crazy_phyiscal_unit.ConvertFrom(10.0));
			Assert::IsTrue(IsEqual(-20.020, crazy_phyiscal_unit.ConvertTo(10.0)));
			Assert::AreEqual(20.0, crazy_phyiscal_unit.GetPreTerm());
			Assert::AreEqual(999.99, crazy_phyiscal_unit.GetConvFactor());
			Assert::AreEqual(30.0, crazy_phyiscal_unit.GetPostTerm());
			Assert::AreEqual(_T("CrazyUnit"), crazy_phyiscal_unit.UnitTag().c_str());
			Assert::AreEqual(1.0, crazy_phyiscal_unit.MassDim());
			Assert::AreEqual(2.0, crazy_phyiscal_unit.LengthDim());
			Assert::AreEqual(3.0, crazy_phyiscal_unit.TimeDim());
			Assert::AreEqual(4.0, crazy_phyiscal_unit.TemperatureDim());
			Assert::AreEqual(5.0, crazy_phyiscal_unit.AngleDim());
		}
	};
}
