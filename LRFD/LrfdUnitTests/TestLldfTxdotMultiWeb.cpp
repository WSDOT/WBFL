#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLldfTxdotMultiWeb)
	{
	public:
		
		TEST_METHOD(Test)
		{
         BDSManager::SetUnits(BDSManager::Units::US);

         Int16 Nb = 5;
         Float64 Savg = WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Feet);
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, Savg);
         Float64 wL = WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Feet);
         Float64 L = WBFL::Units::ConvertToSysUnits(120.25, WBFL::Units::Measure::Feet);
         Int16 Nl = 3;
         Float64 ohang = Savg / 2.0;
         Float64 W = (Nb)*Savg;

         TxdotLldfMultiWeb df(1, Savg, spacings, ohang, ohang, Nl, wL, W, L, 2, 0.0, 0.0);

         Assert::AreEqual(0.50405, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.50405, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.50405, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.50405, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.50405, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.50405, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.50405, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.50405, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.42004, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.42004, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.42004, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.42004, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.42004, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.42004, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.42004, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.42004, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);


         BDSManager::SetUnits(BDSManager::Units::SI);
      }
	};
}
