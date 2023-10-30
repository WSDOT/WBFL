#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLldfTxdotSpreadSlab)
	{
	public:
		
		TEST_METHOD(Test)
		{
         BDSManager::SetUnits(BDSManager::Units::US);

         Float64 Savg = WBFL::Units::ConvertToSysUnits(7.5, WBFL::Units::Measure::Feet);
         Int16 Nb = 5;
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, Savg);
         Float64 d = WBFL::Units::ConvertToSysUnits(15.0, WBFL::Units::Measure::Inch);
         Float64 L = WBFL::Units::ConvertToSysUnits(40.5, WBFL::Units::Measure::Feet);
         Float64 ts = WBFL::Units::ConvertToSysUnits(8.0, WBFL::Units::Measure::Inch);
         Int16 Nl = 3;
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Float64 ohang = Savg / 2.0;

         TxdotLldfSpreadSlab df(1, Savg, spacings, ohang, ohang, Nl, wLane, d, L, ts, 0.0, 0.0);

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.41585, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.58219, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.44609, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.58219, 0.001)); // <== interior beam controls

         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.66347, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.71841, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.66347, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.71841, 0.001));

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.34654, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.37174, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.55289, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.55289, 0.001));

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.34654, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.37174, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.55289, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.55289, 0.001));
      }
	};
}
