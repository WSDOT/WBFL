#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
   TEST_CLASS(TestTypeAEK)
   {
   public:

      TEST_METHOD(LRFD)
      {
         Float64 S = WBFL::Units::ConvertToSysUnits(8., WBFL::Units::Measure::Feet);
         Float64 de = WBFL::Units::ConvertToSysUnits(2., WBFL::Units::Measure::Feet);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Feet);
         Float64 L = WBFL::Units::ConvertToSysUnits(151., WBFL::Units::Measure::Feet);
         Float64 ts = WBFL::Units::ConvertToSysUnits(7.5, WBFL::Units::Measure::Inch);
         Float64 n = 1.54;
         Float64 I = WBFL::Units::ConvertToSysUnits(960951.2, WBFL::Units::Measure::Inch4);
         Float64 A = WBFL::Units::ConvertToSysUnits(977.359, WBFL::Units::Measure::Inch2);
         Float64 eg = WBFL::Units::ConvertToSysUnits(46.587, WBFL::Units::Measure::Inch);
         Int16 Nb = 5;
         Int16 Nl = 3;
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);

         // use us units for this test
         LRFDVersionMgr::Units old_units = LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::US);


         LldfTypeAEK df(1, S, spacings, de, de,
            Nl, wLane, L, ts, n, I, A, eg,
            false, 0.0, 0.0, false, false);

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.4575, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.67665, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.750, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.6697, 0.001));

         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.680, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.8144, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.750, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.6515, 0.001));

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.3812, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.6250, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.5666, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.625, 0.001));

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.3812, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.6250, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.5666, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.625, 0.001));

         LRFDVersionMgr::SetUnits(old_units);
      }

      TEST_METHOD(WSDOT)
      {
         LRFDAutoVersion av;
         LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEdition1994);
         LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);

         Float64 S = WBFL::Units::ConvertToSysUnits(2000., WBFL::Units::Measure::Millimeter);
         Float64 de = WBFL::Units::ConvertToSysUnits(910., WBFL::Units::Measure::Millimeter);
         Float64 overhang = WBFL::Units::ConvertToSysUnits(950, WBFL::Units::Measure::Millimeter);
         Float64 wLane = WBFL::Units::ConvertToSysUnits(3600., WBFL::Units::Measure::Millimeter);
         Float64 L = WBFL::Units::ConvertToSysUnits(20000., WBFL::Units::Measure::Millimeter);
         Float64 ts = WBFL::Units::ConvertToSysUnits(240., WBFL::Units::Measure::Millimeter);
         Float64 n = 1.32;
         Float64 I = WBFL::Units::ConvertToSysUnits(216.9e9, WBFL::Units::Measure::Millimeter4);
         Float64 A = WBFL::Units::ConvertToSysUnits(653587., WBFL::Units::Measure::Millimeter2);
         Float64 eg = WBFL::Units::ConvertToSysUnits(908., WBFL::Units::Measure::Millimeter);
         Int16 Nb = 5;
         Int16 Nl = 3;
         std::vector<Float64> spacings;
         spacings.assign(Nb - 1, S);

         WsdotLldfTypeAEK df(1, S, spacings, de, de,
            Nl, wLane, L, ts, n, I, A, eg,
            overhang, overhang,
            false, 0.0, 0.0, false, false, 0.4);

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.480, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.649, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.711, 0.001));

         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.623, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.721, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.721, 0.001));

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.400, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.519, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.705, 0.001));

         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.400, 0.001));
         Assert::IsTrue(IsEqual(df.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.519, 0.001));
         Assert::IsTrue(IsEqual(df.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.705, 0.001));

         overhang = WBFL::Units::ConvertToSysUnits(1100, WBFL::Units::Measure::Millimeter);
         WsdotLldfTypeAEK df2(1, S, spacings, de, de,
            Nl, wLane, L, ts, n, I, A, eg,
            overhang, overhang,
            false, 0.0, 0.0, false, false, 0.5);

         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.480, 0.001));
         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.649, 0.001));
         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.711, 0.001));

         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.623, 0.001));
         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.721, 0.001));
         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::StrengthI), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::TwoOrMore, LimitState::StrengthI), 0.7206, 0.001));

         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.400, 0.001));
         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.519, 0.001));
         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueI), 0.705, 0.001));

         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.400, 0.001));
         Assert::IsTrue(IsEqual(df2.MomentDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.705, 0.001));
         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::IntGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.519, 0.001));
         Assert::IsTrue(IsEqual(df2.ShearDF(ILiveLoadDistributionFactor::Location::ExtGirder, ILiveLoadDistributionFactor::NumLoadedLanes::One, LimitState::FatigueII), 0.705, 0.001));
      }
   };
}
