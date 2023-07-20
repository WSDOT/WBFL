#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestTypeBC)
	{
	public:
		
		TEST_METHOD(LRFD)
		{
         LRFDAutoVersion av;
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         Float64 S = WBFL::Units::ConvertToSysUnits(8.57, WBFL::Units::Measure::Feet);
         Float64 de = WBFL::Units::ConvertToSysUnits(2.574, WBFL::Units::Measure::Feet);
         Float64 oh = WBFL::Units::ConvertToSysUnits(5.145, WBFL::Units::Measure::Feet);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Float64 L = WBFL::Units::ConvertToSysUnits(114., WBFL::Units::Measure::Feet);
         Float64 d = WBFL::Units::ConvertToSysUnits(48., WBFL::Units::Measure::Inch);
         Int16 Nb = 5;
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Int16 Nl = Int16((2 * de + wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet));
         Float64 skew = WBFL::Units::ConvertToSysUnits(20.0, WBFL::Units::Measure::Degree);

         LldfTypeBC df(1, S, spacings, oh, oh,
            Nl, wLane, d, L,
            de, de,
            skew, skew, true, true);

         Assert::AreEqual(0.31382, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.54911, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(1.17, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.582, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.7506, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.9261, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(1.404, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.9792, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.2615, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.9752, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.6255, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(1.1706, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.2615, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.9752, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.6255, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(1.1706, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
      }

      TEST_METHOD(WSDOT)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         Float64 S = WBFL::Units::ConvertToSysUnits(8.57, WBFL::Units::Measure::Feet);
         Float64 de = WBFL::Units::ConvertToSysUnits(2.574, WBFL::Units::Measure::Feet);
         Float64 oh = WBFL::Units::ConvertToSysUnits(5.145, WBFL::Units::Measure::Feet);
         Float64 ohs = WBFL::Units::ConvertToSysUnits(6.145, WBFL::Units::Measure::Feet);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Float64 L = WBFL::Units::ConvertToSysUnits(114., WBFL::Units::Measure::Feet);
         Float64 d = WBFL::Units::ConvertToSysUnits(48., WBFL::Units::Measure::Inch);
         Int16 Nb = 5;
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Int16 Nl = Int16((2 * de + wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet));
         Float64 skew = WBFL::Units::ConvertToSysUnits(20.0, WBFL::Units::Measure::Degree);

         WsdotLldfTypeBC df(1, S, spacings, oh, oh,
            Nl, wLane, d, L,
            de, de,
            ohs, ohs,
            skew, skew, true, true);

         Assert::AreEqual(0.31382, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.54911, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.975, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.582, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.7506, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.9261, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(1.171, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.9792, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.2615, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.9752, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.6255, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(1.1706, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.2615, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.9752, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.6255, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(1.1706, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
      }

		TEST_METHOD(TxDOT)
		{
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);

         Float64 S = WBFL::Units::ConvertToSysUnits(8.57, WBFL::Units::Measure::Feet);
         Float64 de = WBFL::Units::ConvertToSysUnits(2.574, WBFL::Units::Measure::Feet);
         Float64 oh = WBFL::Units::ConvertToSysUnits(5.145, WBFL::Units::Measure::Feet);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Float64 L = WBFL::Units::ConvertToSysUnits(114., WBFL::Units::Measure::Feet);
         Float64 d = WBFL::Units::ConvertToSysUnits(48., WBFL::Units::Measure::Inch);
         Int16 Nb = 5;
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Int16 Nl = Int16((2 * de + wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet));
         Float64 skew = WBFL::Units::ConvertToSysUnits(20.0, WBFL::Units::Measure::Degree);

         LldfTypeBC df(1, S, spacings, oh, oh,
            Nl, wLane, d, L,
            de, de,
            skew, skew, true, true);

         Assert::AreEqual(0.31382, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.54911, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(1.17, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.582, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.7506, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.9261, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(1.404, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.9792, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.2615, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.9752, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.6255, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(1.1706, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.2615, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.9752, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.6255, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(1.1706, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);

         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
      }
	};
}
