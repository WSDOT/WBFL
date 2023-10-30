#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestTypeG)
	{
	public:
		
		TEST_METHOD(LRFD)
		{
         BDSAutoVersion av;
         BDSManager::SetUnits(BDSManager::Units::US);

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
         Float64 b = S;
         Float64 d = WBFL::Units::ConvertToSysUnits(18.0, WBFL::Units::Measure::Inch);
         Float64 de = WBFL::Units::ConvertToSysUnits(-10.5, WBFL::Units::Measure::Inch);

         LldfTypeG df(1, S, spacings, de, de,
            Nl, wLane,
            L, W, I, J, b, d,
            de, de, 0.2,
            0.0, 0.0, true, true);

         Assert::AreEqual(0.5523, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.5523, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.6051, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.5550, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.600, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.6667, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3125, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3125, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.4601, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.5043, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.5000, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.2604, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.4601, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.5043, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.5000, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.2604, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
      }

		TEST_METHOD(TxDOTVoidedSlab)
		{
         BDSAutoVersion av;
         BDSManager::SetUnits(BDSManager::Units::US);

         Int16 Nb = 5;
         Float64 S = WBFL::Units::ConvertToSysUnits(4, WBFL::Units::Measure::Feet);
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Float64 L = WBFL::Units::ConvertToSysUnits(115., WBFL::Units::Measure::Feet);
         Float64 W = S * Nb;
         Float64 I = WBFL::Units::ConvertToSysUnits(559367.214, WBFL::Units::Measure::Inch4);
         Float64 J = WBFL::Units::ConvertToSysUnits(33064.695, WBFL::Units::Measure::Inch4);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Int16 Nl = Int16((wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet));
         Float64 b = S;
         Float64 de = WBFL::Units::ConvertToSysUnits(-10.5, WBFL::Units::Measure::Inch);
         Float64 d = WBFL::Units::ConvertToSysUnits(18.0, WBFL::Units::Measure::Inch);

         TxdotVoidedSlab df(1, S, spacings, de, de, Nl, wLane,
            L, W, I, J, b, d,
            de, de, 0.2, 0.0, 0.0);

         Assert::AreEqual(0.3484, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3484, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3484, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3484, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.3484, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3484, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3484, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3484, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.2903, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.2903, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.2903, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.2903, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.2903, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.2903, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.2903, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.2903, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
      }
	};

	TEST_CLASS(TestTypeF)
	{
	public:

		TEST_METHOD(LRFD)
		{
         BDSAutoVersion av;
         BDSManager::SetUnits(BDSManager::Units::US);

         Int16 Nb = 5;
         Float64 S = WBFL::Units::ConvertToSysUnits(4, WBFL::Units::Measure::Feet);
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Float64 L = WBFL::Units::ConvertToSysUnits(115, WBFL::Units::Measure::Feet);
         Float64 W = S * Nb;
         Float64 I = WBFL::Units::ConvertToSysUnits(559367.214, WBFL::Units::Measure::Inch4);
         Float64 J = WBFL::Units::ConvertToSysUnits(33064.695, WBFL::Units::Measure::Inch4);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Int16 Nl = Int16((wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet));
         Float64 b = S;
         Float64 d = WBFL::Units::ConvertToSysUnits(18.0, WBFL::Units::Measure::Inch);
         Float64 de = WBFL::Units::ConvertToSysUnits(-10.5, WBFL::Units::Measure::Inch);

         LldfTypeF df(1, S, spacings, de, de, Nl, wLane,
            L, W, I, J, b, d,
            de, de, 0.2, 0.0, 0.0, true, true);

         Assert::AreEqual(0.4114, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3616, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.4508, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.363454, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         
         Assert::AreEqual(0.4869, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.5138, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.5873, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.6000, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         
         Assert::AreEqual(0.3428, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.3757, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.4057, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.4894, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         
         Assert::AreEqual(0.3428, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.3757, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.4057, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.4894, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
      }

		TEST_METHOD(TxDOTAdjacentBox)
		{
         BDSManager::SetUnits(BDSManager::Units::US);

         Int16 Nb = 5;
         Float64 S = WBFL::Units::ConvertToSysUnits(4, WBFL::Units::Measure::Feet);
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Float64 L = WBFL::Units::ConvertToSysUnits(115., WBFL::Units::Measure::Feet);
         Float64 W = S * Nb;
         Float64 I = WBFL::Units::ConvertToSysUnits(559367.214, WBFL::Units::Measure::Inch4);
         Float64 J = WBFL::Units::ConvertToSysUnits(33064.695, WBFL::Units::Measure::Inch4);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12.0, WBFL::Units::Measure::Feet);
         Int16 Nl = Int16((wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Feet));
         Float64 b = S;
         Float64 de = WBFL::Units::ConvertToSysUnits(-10.5, WBFL::Units::Measure::Inch);
         Float64 d = WBFL::Units::ConvertToSysUnits(18.0, WBFL::Units::Measure::Inch);

         TxdotLldfAdjacentBox df(1, S, spacings, de, de, Nl, wLane,
            L, W, I, J, b, d,
            de, de, 0.2,
            0.0, 0.0);

         Assert::AreEqual(0.4114, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3616, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.4508, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.3634, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.4869, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.5138, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.5873, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.5999, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.3428, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.3757, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.4057, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.4894, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.3428, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.3757, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.4057, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.4894, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);

         BDSManager::SetUnits(BDSManager::Units::SI);
      }
	};
}
