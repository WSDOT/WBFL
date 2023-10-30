#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLiveLoadDistributionFactorMixin)
	{
	public:
		
		TEST_METHOD(LeverRule)
		{
			LiveLoadDistributionFactorMixin mixin;
			ILiveLoadDistributionFactor::LeverRuleMethod lever_rule = mixin.DistributeByLeverRule(3, std::vector<Float64>{8.0, 8.0, 8.0}, 7.0, 7.0, 12.0, 3, true);

			Assert::IsTrue(lever_rule.bWasUsed);
			Assert::AreEqual(14.3904, lever_rule.AxleLocations[0], 0.0001);
			Assert::AreEqual(12.5616, lever_rule.AxleLocations[1], 0.0001);
			Assert::AreEqual(2.3904, lever_rule.AxleLocations[2], 0.0001);
			Assert::AreEqual(0.5616, lever_rule.AxleLocations[3], 0.0001);
			Assert::AreEqual(8.0, lever_rule.Sleft);
			Assert::AreEqual(8.0, lever_rule.Sright);
			Assert::AreEqual(1.0, lever_rule.m);
			Assert::AreEqual(7.0, lever_rule.de);
			Assert::AreEqual((IndexType)2, lever_rule.nLanesUsed);
			Assert::AreEqual((IndexType)4, lever_rule.Nb);
			Assert::IsTrue(lever_rule.bWasExterior);
		}

		TEST_METHOD(Statical)
		{
			LiveLoadDistributionFactorMixin mixin;
			ILiveLoadDistributionFactor::RigidMethod statical = mixin.DistributeByRigidMethod(ILiveLoadDistributionFactor::DfSide::LeftSide, std::vector<Float64>{8.0, 8.0, 8.0}, 7.0, 7.0, 12.0, 0, 3, true);
			Assert::IsTrue(statical.bWasUsed);
			Assert::AreEqual(2.0, statical.Nl);
			Assert::AreEqual(4.0, statical.Nb);
			Assert::AreEqual(12.0, statical.Xext);
			Assert::AreEqual(17.476, statical.e[0], 0.0001);
			Assert::AreEqual(5.476, statical.e[1], 0.0001);
			Assert::AreEqual(-12.0, statical.x[0]);
			Assert::AreEqual(-4.0, statical.x[1]);
			Assert::AreEqual(4.0, statical.x[2]);
			Assert::AreEqual(12.0, statical.x[3]);
			Assert::AreEqual(1.0, statical.m);
			Assert::AreEqual(1.3607, statical.mg);
		}

		TEST_METHOD(LaneBeams)
		{
			LiveLoadDistributionFactorMixin mixin;
			ILiveLoadDistributionFactor::DFResult result = mixin.GetLanesBeamsMethod(4, 3, true);
			Assert::AreEqual((Int16)LANES_DIV_BEAMS, result.ControllingMethod);
			Assert::IsTrue(result.LanesBeamsData.bWasUsed);
			Assert::AreEqual((IndexType)3, result.LanesBeamsData.Nb);
			Assert::AreEqual((IndexType)4, result.LanesBeamsData.Nl);
			Assert::AreEqual(0.65, result.LanesBeamsData.m);
			Assert::AreEqual(0.866666, result.LanesBeamsData.mg, 0.00001);
			Assert::AreEqual(0.866666, result.mg, 0.00001);
		}

		TEST_METHOD(Other)
		{
			BDSAutoVersion av;
			BDSManager::SetEdition(BDSManager::Edition::FirstEdition1994);

			LiveLoadDistributionFactorMixin mixin;

			BDSManager::SetUnits(BDSManager::Units::US);
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(2.0,WBFL::Units::Measure::Feet), mixin.GetShyDistance());
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(6.0,WBFL::Units::Measure::Feet), mixin.GetWheelLineSpacing());
			Assert::AreEqual(WBFL::Units::ConvertToSysUnits(10.0,WBFL::Units::Measure::Feet), mixin.GetTruckWidth());

			BDSManager::SetUnits(BDSManager::Units::SI);
			Assert::AreEqual(0.6, mixin.GetShyDistance());
			Assert::AreEqual(1.8, mixin.GetWheelLineSpacing());
			Assert::AreEqual(3.0, mixin.GetTruckWidth());
		}
	};
}
