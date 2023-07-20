#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestTypeAEKIJ)
	{
	public:
		
		TEST_METHOD(Test)
		{
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);

         Float64 S = WBFL::Units::ConvertToSysUnits(2000., WBFL::Units::Measure::Millimeter);
         Float64 de = WBFL::Units::ConvertToSysUnits(910., WBFL::Units::Measure::Millimeter);
         Float64 ro = de;
         Float64 wLane = WBFL::Units::ConvertToSysUnits(3600., WBFL::Units::Measure::Millimeter);
         Float64 L = WBFL::Units::ConvertToSysUnits(20000., WBFL::Units::Measure::Millimeter);
         Float64 ts = WBFL::Units::ConvertToSysUnits(240., WBFL::Units::Measure::Millimeter);
         Float64 n = 1.32;
         Float64 I = WBFL::Units::ConvertToSysUnits(216.9e9, WBFL::Units::Measure::Millimeter4);
         Float64 A = WBFL::Units::ConvertToSysUnits(653587., WBFL::Units::Measure::Millimeter2);
         Float64 eg = WBFL::Units::ConvertToSysUnits(908., WBFL::Units::Measure::Millimeter);
         Int16 Nb = 5;
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);
         Int16 Nl = Int16((2 * de + wLane * (Nb - 1)) / WBFL::Units::ConvertToSysUnits(3000., WBFL::Units::Measure::Millimeter));

         LldfTypeAEKIJ df(1, S, spacings, de, de, Nl, wLane,
            de, de, L, ts, n, I, A, eg,
            0.0, 0.0, false, false);

         Assert::AreEqual(0.480, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.649, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.846, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.711, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.623, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.721, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.846, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.001);
         Assert::AreEqual(0.651, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.001);

         Assert::AreEqual(0.3996, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.7050, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.5193, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);
         Assert::AreEqual(0.7050, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.001);

         Assert::AreEqual(0.3996, df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.7050, df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.5193, df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
         Assert::AreEqual(0.7050, df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.001);
      }
	};
}
