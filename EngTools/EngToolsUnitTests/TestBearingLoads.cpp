
#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;

namespace EngToolsUnitTests
{
	TEST_CLASS(TestBearingLoads)
	{
	public:

		TEST_METHOD(Test)
		{



			BearingLoads brg_loads;

			Assert::IsTrue(IsEqual(brg_loads.GetDeadLoad(), WBFL::Units::ConvertToSysUnits(86.0, WBFL::Units::Measure::Kip)));
			Assert::IsTrue(IsEqual(brg_loads.GetLiveLoad(), WBFL::Units::ConvertToSysUnits(47.0, WBFL::Units::Measure::Kip)));
			Assert::IsTrue(IsEqual(brg_loads.GetTotalLoad(), WBFL::Units::ConvertToSysUnits(133.0, WBFL::Units::Measure::Kip)));
			Assert::IsTrue(IsEqual(brg_loads.GetRotationX(), 0.014));
			Assert::IsTrue(IsEqual(brg_loads.GetRotationY(), 0.005));
			Assert::IsTrue(IsEqual(brg_loads.GetStaticRotation(), 0.008));
			Assert::IsTrue(IsEqual(brg_loads.GetCyclicRotation(), 0.006));
			Assert::IsTrue(IsEqual(brg_loads.GetShearDeformation(), WBFL::Units::ConvertToSysUnits(0.47, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_loads.GetEffectiveKFactorX(), 1.0));
			Assert::IsTrue(IsEqual(brg_loads.GetEffectiveKFactorY(), 2.0));





		}
	};
}
