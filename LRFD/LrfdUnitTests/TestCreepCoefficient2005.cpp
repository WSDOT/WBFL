#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestCreepCoefficient2005)
	{
	public:
		
		TEST_METHOD(Test)
		{
         BDSAutoVersion av;
         BDSManager::SetUnits(BDSManager::Units::US);
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2005Interims);


         CreepCoefficient2005 creep;
         creep.SetCuringMethod(CreepCoefficient2005::CuringMethod::Accelerated);
         creep.SetFci(WBFL::Units::ConvertToSysUnits(8.0, WBFL::Units::Measure::KSI));
         creep.SetCuringMethodTimeAdjustmentFactor(WBFL::Units::ConvertToSysUnits(7, WBFL::Units::Measure::Day));
         creep.SetRelHumidity(75);
         creep.SetSurfaceArea(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch2));
         creep.SetVolume(WBFL::Units::ConvertToSysUnits(2.88, WBFL::Units::Measure::Inch3));

         Float64 ti = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
         Float64 t = WBFL::Units::ConvertToSysUnits(120, WBFL::Units::Measure::Day);
         Assert::IsTrue(IsEqual(creep.GetKvs(), 1.0756));
         Assert::IsTrue(IsEqual(creep.GetKf(), 0.55555));
         Assert::IsTrue(IsEqual(creep.GetKhc(), 0.96));
         Assert::IsTrue(IsEqual(creep.GetKtd(t), 0.805369));
         Assert::IsTrue(IsEqual(creep.GetCreepCoefficient(t, ti), 0.877805));
      }
	};
}
