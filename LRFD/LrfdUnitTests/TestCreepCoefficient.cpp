#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestCreepCoefficient)
	{
	public:
		
		TEST_METHOD(NormalCuring)
		{
			LRFDAutoVersion av;

			CreepCoefficient creep;
			creep.SetRelHumidity(75);
			creep.SetVolume(WBFL::Units::ConvertToSysUnits(10.0,WBFL::Units::Measure::Inch3));
			creep.SetSurfaceArea(WBFL::Units::ConvertToSysUnits(7.0,WBFL::Units::Measure::Inch2));
			creep.SetFci(WBFL::Units::ConvertToSysUnits(5.0,WBFL::Units::Measure::KSI));
			creep.SetCuringMethod(CreepCoefficient::CuringMethod::Normal);

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // became invalid in 2005
			Assert::ExpectException<XCreepCoefficient>([&]() {creep.GetKf(); });

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994); // version of LRFD where both US and SI are valid
			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Assert::AreEqual(172800.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(864000.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.81595648232094276, creep.GetKf());
			Assert::AreEqual(1.0458686681362190, creep.GetKtd(WBFL::Units::ConvertToSysUnits(2.0,WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.23878100859571433, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(3.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(1.5686625195506945, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(100.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(172800.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(864000.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.81595648232094276, creep.GetKf());
			Assert::AreEqual(1.0444222588878544, creep.GetKtd(WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.23845554274070827, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(3.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(1.5674869413363011, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(100.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
		}

		TEST_METHOD(AcceleratedCuring)
		{
			LRFDAutoVersion av;

			CreepCoefficient creep;
			creep.SetRelHumidity(75);
			creep.SetVolume(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Inch3));
			creep.SetSurfaceArea(WBFL::Units::ConvertToSysUnits(7.0, WBFL::Units::Measure::Inch2));
			creep.SetFci(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			creep.SetCuringMethod(CreepCoefficient::CuringMethod::Accelerated);

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // became invalid in 2005
			Assert::ExpectException<XCreepCoefficient>([&]() {creep.GetKf(); });

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994); // version of LRFD where both US and SI are valid
			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Assert::AreEqual(691200.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(864000.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.81595648232094276, creep.GetKf());
			Assert::AreEqual(1.0458686681362190, creep.GetKtd(WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.0, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(3.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(1.3121869512025177, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(100.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(691200.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(864000.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.81595648232094276, creep.GetKf());
			Assert::AreEqual(1.0444222588878544, creep.GetKtd(WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.0, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(3.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(1.3112035794614203, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(100.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Day)));
		}

		TEST_METHOD(LimitingVSRatio)
		{
			LRFDAutoVersion av;

			CreepCoefficient creep;
			creep.SetRelHumidity(75);
			creep.SetVolume(WBFL::Units::ConvertToSysUnits(100.0, WBFL::Units::Measure::Inch3));
			creep.SetSurfaceArea(WBFL::Units::ConvertToSysUnits(7.0, WBFL::Units::Measure::Inch2));
			creep.SetFci(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			creep.SetCuringMethod(CreepCoefficient::CuringMethod::Normal);

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEditionWith2005Interims); // became invalid in 2005
			Assert::ExpectException<XCreepCoefficient>([&]() {creep.GetKf(); });

			LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994); // version of LRFD where both US and SI are valid
			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);
			Assert::AreEqual(864000.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.81595648232094276, creep.GetKf());
			Assert::AreEqual(0.16879206127745114, creep.GetKtd(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.40016529401091566, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(100.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));

			LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			Assert::AreEqual(864000.0, creep.GetAdjustedInitialAge(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.81595648232094276, creep.GetKf());
			Assert::AreEqual(0.17400435400684902, creep.GetKtd(WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
			Assert::AreEqual(0.40922655462951590, creep.GetCreepCoefficient(WBFL::Units::ConvertToSysUnits(100.0, WBFL::Units::Measure::Day), WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Day)));
		}
	};
}
