#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestILiveLoadDistributionFactor)
	{
	public:
		
		TEST_METHOD(Test)
		{
			ILiveLoadDistributionFactor::DFResult result;
			result.EqnData.m = 1.0;
			result.LeverRuleData.m = 2.0;
			result.RigidData.m = 3.0;
			result.LanesBeamsData.m = 4.0;

			result.ControllingMethod = SPEC_EQN;
			Assert::AreEqual(1.0, result.GetMultiplePresenceFactor());

			result.ControllingMethod = LEVER_RULE;
			Assert::AreEqual(2.0, result.GetMultiplePresenceFactor());

			result.ControllingMethod = RIGID_METHOD;
			Assert::AreEqual(3.0, result.GetMultiplePresenceFactor());

			result.ControllingMethod = LANES_DIV_BEAMS;
			Assert::AreEqual(4.0, result.GetMultiplePresenceFactor());

		}
	};
}
