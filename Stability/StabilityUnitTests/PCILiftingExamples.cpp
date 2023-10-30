#include "pch.h"
#include "CppUnitTest.h"
#include <LRFD\ConcreteUtil.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Stability;

namespace StabilityUnitTest
{
	TEST_CLASS(TestPCILiftingExamples)
	{
	public:
		
		TEST_METHOD(Test)
		{
         // Build the basic girder model for the PCI Examples (6.1.x)
         Girder girder;
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
         Float64 fci = 5.5;
         concrete.SetFc(WBFL::Units::ConvertToSysUnits(fci, WBFL::Units::Measure::KSI));
         concrete.SetDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
         concrete.SetDensityForWeight(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
         Float64 Eci = WBFL::LRFD::ConcreteUtil::ModE(concrete.GetType(), concrete.GetFc(), concrete.GetDensity(), false);
         concrete.SetE(Eci);
         concrete.SetFlexureFr(WBFL::Units::ConvertToSysUnits(0.24 * sqrt(fci), WBFL::Units::Measure::KSI));

         LiftingStabilityProblem stabilityProblem;
         stabilityProblem.SetConcrete(concrete);

         stabilityProblem.AddAnalysisPoint(std::move(std::make_unique<AnalysisPoint>(0.4 * L))); // harp point

         // Example 6.1.1
         Float64 fpe = WBFL::Units::ConvertToSysUnits(1232.0, WBFL::Units::Measure::Kip);
         stabilityProblem.AddFpe(_T("Prestress"), 0.0, fpe, Xleft, -Hg + WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::Inch));

         stabilityProblem.SetCamber(WBFL::Units::ConvertToSysUnits(2.92, WBFL::Units::Measure::Inch));

         stabilityProblem.SetSupportLocations(WBFL::Units::ConvertToSysUnits(9, WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(9, WBFL::Units::Measure::Feet));
         stabilityProblem.SetSweepTolerance(0.000520833333);
         stabilityProblem.SetSupportPlacementTolerance(WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch));
         stabilityProblem.SetLiftAngle(PI_OVER_2);
         stabilityProblem.SetYRollAxis(WBFL::Units::ConvertToSysUnits(0.0, WBFL::Units::Measure::Inch));

         stabilityProblem.SetImpact(0.0, 0.0);

         StabilityEngineer engineer;

         LiftingResults result = engineer.AnalyzeLifting(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;

               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+impact][+wind][+sectionResult.MinFScrCorner[+impact][+wind]], 1.844, 0.001));

                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.113, 0.001));
                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.290, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+impact][+wind], 1.839, 0.001));
            }
         }

         // Example 6.1.1 with eccentric loading due to overhang brackets installed prior to lift
         stabilityProblem.SetAppurtenanceLoading(WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Feet), WBFL::Units::ConvertToSysUnits(0.05, WBFL::Units::Measure::KipPerFoot));
         result = engineer.AnalyzeLifting(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;

               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+impact][+wind][+sectionResult.MinFScrCorner[+impact][+wind]], 1.235, 0.001));

                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::TopLeft], WBFL::Units::Measure::KSI), 0.353, 0.001));
                  Assert::IsTrue(::IsEqual(WBFL::Units::ConvertFromSysUnits(sectionResult.f[+impact][+wind][+Corner::BottomRight], WBFL::Units::Measure::KSI), -3.412, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+impact][+wind], 1.470, 0.001));
            }
         }
         stabilityProblem.SetAppurtenanceLoading(0.0, 0.0); // remove eccentric load

         // Example 6.1.2
         stabilityProblem.SetImpact(0, 0.20);
         result = engineer.AnalyzeLifting(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;
               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+impact][+wind][+sectionResult.MinFScrCorner[+impact][+wind]], impact == ImpactDirection::ImpactDown ? 1.708 : 1.844, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+impact][+wind], impact == ImpactDirection::ImpactDown ? 1.593 : 1.839, 0.001));
            }
         }

         // Example 6.1.3
         stabilityProblem.SetImpact(0, 0);
         stabilityProblem.SetWindLoading(WindLoadType::Pressure, WBFL::Units::ConvertToSysUnits(2.5, WBFL::Units::Measure::PSF));
         result = engineer.AnalyzeLifting(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;
               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopLeft], wind == WindDirection::Left ? 2.541 : 1.578, 0.001));
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopRight], Float64_Max, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+impact][+wind], wind == WindDirection::Left ? 2.241 : 1.658, 0.001));
               Assert::IsTrue(::IsEqual(result.AdjFsFailure[+impact][+wind], wind == WindDirection::Left ? 2.541 : 1.658, 0.001));
            }
         }

         // Example 6.1.4
         stabilityProblem.SetLiftAngle(M_PI / 4);
         result = engineer.AnalyzeLifting(&girder, &stabilityProblem);
         for (int i = 0; i < 3; i++)
         {
            ImpactDirection impact = (ImpactDirection)i;
            for (int j = 0; j < 2; j++)
            {
               WindDirection wind = (WindDirection)j;
               for (const auto& sectionResult : result.vSectionResults)
               {
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopLeft], wind == WindDirection::Left ? 2.398 : 1.628, 0.001));
                  Assert::IsTrue(::IsEqual(sectionResult.FScr[+impact][+wind][+Corner::TopRight], Float64_Max, 0.001));
               }

               Assert::IsTrue(::IsEqual(result.FsFailure[+impact][+wind], wind == WindDirection::Left ? 2.033 : 1.568, 0.001));
               Assert::IsTrue(::IsEqual(result.AdjFsFailure[+impact][+wind], wind == WindDirection::Left ? 2.398 : 1.628, 0.001));
            }
         }
      }
	};
}
