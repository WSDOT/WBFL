#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestPCIUHPCCreepCoefficient)
	{
	public:
		
		TEST_METHOD(Test)
		{

         BDSAutoVersion av;
         BDSManager::SetUnits(BDSManager::Units::US);
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2005Interims);


         PCIUHPCCreepCoefficient creep;
         creep.PostCureThermalTreatment(false);
         creep.SetCuringMethod(CreepCoefficient2005::CuringMethod::Accelerated);
         creep.SetFci(WBFL::Units::ConvertToSysUnits(8.0, WBFL::Units::Measure::KSI));
         creep.SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
         creep.SetRelHumidity(75);
         creep.SetSurfaceArea(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch2));
         creep.SetVolume(WBFL::Units::ConvertToSysUnits(2.88, WBFL::Units::Measure::Inch3));

         Float64 ti = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
         Float64 t = WBFL::Units::ConvertToSysUnits(120, WBFL::Units::Measure::Day);

         Assert::IsTrue(IsEqual(creep.GetKvs(), 1.0));
         Assert::IsTrue(IsEqual(creep.GetKf(), 1.0));
         Assert::IsTrue(IsEqual(creep.GetKhc(), 1.0));
         Assert::IsTrue(IsEqual(creep.GetKtd(t), 0.80460));
         Assert::IsTrue(IsEqual(creep.GetCreepCoefficient(t, ti), 0.96552));

         creep.PostCureThermalTreatment(true);
         Assert::IsTrue(IsEqual(creep.GetCreepCoefficient(t, ti), 0.24138));
      }
	};
}
