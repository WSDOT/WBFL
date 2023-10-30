#include "pch.h"
#include "CppUnitTest.h"
#include <LRFD\ConcreteUtil.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Stability;

namespace StabilityUnitTest
{
	TEST_CLASS(TestPCIHaulingExamples)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // Build the basic girder model for the PCI Examples (6.2.x)
         Girder girder;
         HaulingStabilityProblem stabilityProblem;
         Float64 Hg = WBFL::Units::ConvertToSysUnits(72, WBFL::Units::Measure::Inch);
         Float64 Wtf = WBFL::Units::ConvertToSysUnits(42, WBFL::Units::Measure::Inch);
         Float64 Wbf = WBFL::Units::ConvertToSysUnits(26, WBFL::Units::Measure::Inch);

         Float64 Ag = WBFL::Units::ConvertToSysUnits(767, WBFL::Units::Measure::Inch2);
         Float64 Ix = WBFL::Units::ConvertToSysUnits(545894, WBFL::Units::Measure::Inch4);
         Float64 Iy = WBFL::Units::ConvertToSysUnits(37634, WBFL::Units::Measure::Inch4);
         Float64 Ixy = 0;
         Float64 Xleft = Wtf / 2;
         Float64 Ytop = WBFL::Units::ConvertToSysUnits(36.6 - 72, WBFL::Units::Measure::Inch); // want neg because we are in section coordinates
         Float64 L = WBFL::Units::ConvertToSysUnits(136, WBFL::Units::Measure::Feet);
         girder.AddSection(L, Ag, Ix, Iy, Ixy, Xleft, Ytop, Hg, Wtf, Wbf);

         WBFL::Materials::SimpleConcrete concrete;
         Float64 fc = 7.0;
         concrete.SetFc(WBFL::Units::ConvertToSysUnits(fc, WBFL::Units::Measure::KSI));
         concrete.SetDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
         concrete.SetDensityForWeight(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
         Float64 Ec = WBFL::LRFD::ConcreteUtil::ModE(concrete.GetType(), concrete.GetFc(), concrete.GetDensity(), false);
         concrete.SetE(Ec);
         concrete.SetFlexureFr(WBFL::Units::ConvertToSysUnits(0.24 * sqrt(fc), WBFL::Units::Measure::KSI));
         stabilityProblem.SetConcrete(concrete);

         stabilityProblem.AddAnalysisPoint(std::move(std::make_unique<AnalysisPoint>(0.4 * L))); // harp point

         // Example 6.2.1
         Float64 fpe = WBFL::Units::ConvertToSysUnits(1251.5, WBFL::Units::Measure::Kip);
         stabilityProblem.AddFpe(_T("Prestress"), 0.0, fpe, Xleft, -Hg + WBFL::Units::ConvertToSysUnits(7.91, WBFL::Units::Measure::Inch));

         stabilityProblem.SetCamber(WBFL::Units::ConvertToSysUnits(2.92, WBFL::Units::Measure::Inch));


         stabilityProblem.SetSupportLocations(WBFL::Units::ConvertToSysUnits(10, WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(10, WBFL::Units::Measure::Feet));
         stabilityProblem.SetSweepTolerance(2 * 0.000520833333);
         stabilityProblem.SetSweepGrowth(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch));
         stabilityProblem.SetSupportPlacementTolerance(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch));
         stabilityProblem.SetYRollAxis(WBFL::Units::ConvertToSysUnits(-48.0, WBFL::Units::Measure::Inch) - Hg); // location of roll axes below top of girder);

         stabilityProblem.SetImpact(0.0, 0.0);
         stabilityProblem.SetImpactUsage(HaulingImpact::Both);

         stabilityProblem.SetRotationalStiffness(WBFL::Units::ConvertToSysUnits(40500., WBFL::Units::Measure::KipInchPerRadian));
         stabilityProblem.SetSupportSlope(0.06);
         stabilityProblem.SetSuperelevation(0.06);
         stabilityProblem.SetSupportWidth(WBFL::Units::ConvertToSysUnits(72., WBFL::Units::Measure::Inch));
         stabilityProblem.SetHeightOfRollAxis(WBFL::Units::ConvertToSysUnits(24., WBFL::Units::Measure::Inch));


         StabilityEngineer engineer;

         HaulingResults result = engineer.AnalyzeHauling(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;
               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], 1.428, 0.001));

                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.466, 0.001));
                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.486, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+HaulingSlope::Superelevation][+impact][+wind], 2.825, 0.001));
               Assert::IsTrue(::IsEqual(result.FsRollover[+HaulingSlope::Superelevation][+impact][+wind], 1.994, 0.001));
            }
         }


         // Example 6.2.1 with eccentric load due to overhang brackets
         stabilityProblem.SetAppurtenanceLoading(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(0.05, WBFL::Units::Measure::KipPerFoot));
         result = engineer.AnalyzeHauling(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;
               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], 1.276, 0.001));

                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.501, 0.001));
                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.482, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+HaulingSlope::Superelevation][+impact][+wind], 2.596, 0.001));
               Assert::IsTrue(::IsEqual(result.FsRollover[+HaulingSlope::Superelevation][+impact][+wind], 1.845, 0.001));
            }
         }
         stabilityProblem.SetAppurtenanceLoading(0.0, 0.0); // remove eccentric load

         // Example 6.2.2
         stabilityProblem.SetTurningRadius(WBFL::Units::ConvertToSysUnits(120, WBFL::Units::Measure::Feet));
         stabilityProblem.SetVelocity(WBFL::Units::ConvertToSysUnits(10., WBFL::Units::Measure::Mile) / WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Hour));
         stabilityProblem.SetCentrifugalForceType(CFType::Adverse);
         stabilityProblem.SetSupportSlope(0.02);
         stabilityProblem.SetSuperelevation(0.02);
         result = engineer.AnalyzeHauling(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;
               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], 0.970, 0.001));

                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.647, 0.001));
                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+HaulingSlope::Superelevation][+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.598, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+HaulingSlope::Superelevation][+impact][+wind], 2.787, 0.001));
               Assert::IsTrue(::IsEqual(result.FsRollover[+HaulingSlope::Superelevation][+impact][+wind], 1.835, 0.001));
            }
         }
      }
	};
}
