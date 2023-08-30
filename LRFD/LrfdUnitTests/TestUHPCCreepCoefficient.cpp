#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestUHPCCreepCoefficient)
	{
	public:
		
		TEST_METHOD(Test)
		{
         BDSAutoVersion av;
         BDSManager::SetUnits(BDSManager::Units::US);
         BDSManager::SetEdition(BDSManager::Edition::ThirdEditionWith2005Interims);

         // based on UHPC design example
         UHPCCreepCoefficient creep;
         creep.SetFci(WBFL::Units::ConvertToSysUnits(14.0, WBFL::Units::Measure::KSI));
         creep.SetRelHumidity(73);
         creep.SetK1(0.62);

         Float64 ti = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Day);
         Float64 td = WBFL::Units::ConvertToSysUnits(90, WBFL::Units::Measure::Day);
         Float64 tf = WBFL::Units::ConvertToSysUnits(20000, WBFL::Units::Measure::Day);

         Assert::IsTrue(IsEqual(creep.GetKvs(), 1.0));
         Assert::IsTrue(IsEqual(creep.GetKf(), 1.0));
         Assert::IsTrue(IsEqual(creep.GetKhc(), 0.94480));
         Assert::IsTrue(IsEqual(creep.GetKtd(td - ti), 1.237746));
         Assert::IsTrue(IsEqual(creep.GetCreepCoefficient(td - ti, ti), 0.870051));

         Assert::IsTrue(IsEqual(creep.GetKtd(tf - ti), 1.52302));
         Assert::IsTrue(IsEqual(creep.GetCreepCoefficient(tf - ti, ti), 1.070576));
      }
	};
}
