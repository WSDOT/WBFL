#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestTypeHIJ)
	{
	public:
		
		TEST_METHOD(Test)
		{
         LRFDAutoVersion av;
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         Int16 Nb = 5;
         Float64 S = WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Feet);
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Float64 L = WBFL::Units::ConvertToSysUnits(120.25, WBFL::Units::Measure::Feet);
         Float64 W = S * Nb;
         Float64 I = WBFL::Units::ConvertToSysUnits(559367.214, WBFL::Units::Measure::Inch4);
         Float64 J = WBFL::Units::ConvertToSysUnits(33064.695, WBFL::Units::Measure::Inch4);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Int16 Nl = Int16((wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet));
         Float64 de = S / 2.0;

         LldfTypeHIJ df(1, S, spacings, de, de, Nl, wLane,
            L, W, I, J, 0.2, de, de,
            0.0, 0.0, true, true);

         Assert::AreEqual(0.55226, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.55226, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.800, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.8, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.6, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.6667, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.8, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.8, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.460188, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.6667, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.5, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.6667, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.460188, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.6667, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.5, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.6667, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
      }
	};
}
