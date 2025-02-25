#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EngTools;

namespace EngToolsUnitTests
{
    TEST_CLASS(TestBearingCalculator)
    {
    public:

		TEST_METHOD(TestAllPass)
		{

			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;

			brg_calc.SetElastomerBulkModulus(WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI));
			brg_calc.SetMaximumAllowableStress(WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI));
			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(200, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(220, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(36, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.35, WBFL::Units::Measure::Inch));
			brg.SetLength(WBFL::Units::ConvertToSysUnits(11, WBFL::Units::Measure::Inch));
			brg.SetWidth(WBFL::Units::ConvertToSysUnits(13, WBFL::Units::Measure::Inch));
			brg.SetIntermediateLayerThickness(WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch));
			brg.SetNumIntLayers(4);
			brg.SetSteelShimThickness(WBFL::Units::ConvertToSysUnits(0.0747, WBFL::Units::Measure::Inch));
			brg_loads.SetStaticRotation(0.008);
			brg_loads.SetCyclicRotation(0.006);
			brg_loads.SetRotationX(0.0);
			brg_loads.SetRotationY(0.0);
			brg_loads.SetShearDeformation(WBFL::Units::ConvertToSysUnits(0.8, WBFL::Units::Measure::Inch));
			brg_loads.SetDeadLoad(WBFL::Units::ConvertToSysUnits(100, WBFL::Units::Measure::Kip));
			brg_loads.SetLiveLoad(WBFL::Units::ConvertToSysUnits(10, WBFL::Units::Measure::Kip));
			brg_loads.SetFixedTranslationX(true);
			brg_loads.SetFixedTranslationY(true);

			Assert::IsTrue(brg_calc.MinimumAreaCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumLengthCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumWidthCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumStressCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumIntermediateLayerThicknessCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumShapeFactorCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumShapeFactorCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersShearDeformationCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationXCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationYCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumNumLayersStabilityXCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumNumLayersStabilityYCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessServiceCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessFatigueCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumElastomerCoverThicknessCheck(brg));
			Assert::IsTrue(brg_calc.MaximumElastomerCoverThicknessCheck(brg));
			Assert::IsTrue(brg_calc.MaximumCompressiveStrainCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.ShearDeformationCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.StaticAxialPrimaryShearStrainCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.StaticAxialSecondaryShearStrainCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.PrimaryShearStrainComboSumCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.SecondaryShearStrainComboSumCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.CheckApplicabilityTotalStressStabilityX(brg, brg_loads));
			Assert::IsFalse(brg_calc.CheckApplicabilityTotalStressStabilityY(brg, brg_loads));
			Assert::IsTrue(brg_calc.StabilityXDirectionCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.RestraintSystemRequirementCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.HydrostaticStressCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.HorizontalForceCheck(brg, brg_loads));

		}

		TEST_METHOD(TestAllFail)
		{


			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;

			brg_calc.SetElastomerBulkModulus(WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI));
			brg_calc.SetMaximumAllowableStress(WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI));
			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(200, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(220, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(2, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(2, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch));
			brg.SetLength(WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Inch));
			brg.SetWidth(WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Inch));
			brg.SetIntermediateLayerThickness(WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch));
			brg.SetNumIntLayers(6);
			brg.SetSteelShimThickness(WBFL::Units::ConvertToSysUnits(0.0005, WBFL::Units::Measure::Inch));
			brg_loads.SetStaticRotation(0.0001);
			brg_loads.SetCyclicRotation(0.0001);
			brg_loads.SetRotationX(0.000);
			brg_loads.SetRotationY(0.000);
			brg_loads.SetShearDeformation(WBFL::Units::ConvertToSysUnits(0.8, WBFL::Units::Measure::Inch));
			brg_loads.SetDeadLoad(WBFL::Units::ConvertToSysUnits(200, WBFL::Units::Measure::Kip));
			brg_loads.SetLiveLoad(WBFL::Units::ConvertToSysUnits(100, WBFL::Units::Measure::Kip));
			brg_loads.SetFixedTranslationX(false);
			brg_loads.SetFixedTranslationY(false);


			Assert::IsFalse(brg_calc.MinimumAreaCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumLengthCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumWidthCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MaximumStressCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MaximumIntermediateLayerThicknessCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumShapeFactorCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumShapeFactorCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumNumLayersShearDeformationCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationXCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationYCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumNumLayersStabilityXCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumNumLayersStabilityYCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumSteelShimThicknessServiceCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumSteelShimThicknessFatigueCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumSteelShimThicknessAbsoluteCheck(brg));
			Assert::IsFalse(brg_calc.MinimumElastomerCoverThicknessCheck(brg));
			Assert::IsTrue(brg_calc.MaximumElastomerCoverThicknessCheck(brg));
			Assert::IsFalse(brg_calc.MaximumCompressiveStrainCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.ShearDeformationCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.StaticAxialPrimaryShearStrainCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.StaticAxialSecondaryShearStrainCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.PrimaryShearStrainComboSumCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.SecondaryShearStrainComboSumCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.CheckApplicabilityTotalStressStabilityX(brg, brg_loads));
			Assert::IsTrue(brg_calc.CheckApplicabilityTotalStressStabilityY(brg, brg_loads));
			Assert::IsFalse(brg_calc.StabilityXDirectionCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.StabilityYDirectionCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.RestraintSystemRequirementCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.HydrostaticStressCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.HorizontalForceCheck(brg, brg_loads));
		}


		TEST_METHOD(TestPGExampleFail)
		{

			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;

			brg_calc.SetElastomerBulkModulus(WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI));
			brg_calc.SetMaximumAllowableStress(WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI));
			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(140, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(190, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(36, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch));
			brg.SetLength(WBFL::Units::ConvertToSysUnits(14, WBFL::Units::Measure::Inch));
			brg.SetWidth(WBFL::Units::ConvertToSysUnits(16, WBFL::Units::Measure::Inch));
			brg.SetIntermediateLayerThickness(WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch));
			brg.SetNumIntLayers(9);
			brg.SetSteelShimThickness(WBFL::Units::ConvertToSysUnits(0.075, WBFL::Units::Measure::Inch));
			brg_loads.SetStaticRotation(0.01174);
			brg_loads.SetCyclicRotation(0.00303);
			brg_loads.SetRotationX(0.015);
			brg_loads.SetRotationY(0.000);
			brg_loads.SetShearDeformation(WBFL::Units::ConvertToSysUnits(2.38, WBFL::Units::Measure::Inch));
			brg_loads.SetDeadLoad(WBFL::Units::ConvertToSysUnits(216, WBFL::Units::Measure::Kip));
			brg_loads.SetLiveLoad(WBFL::Units::ConvertToSysUnits(51, WBFL::Units::Measure::Kip));
			brg_loads.SetFixedTranslationX(false);
			brg_loads.SetFixedTranslationY(true);

			Assert::IsTrue(brg_calc.MinimumAreaCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumLengthCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumWidthCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumStressCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumIntermediateLayerThicknessCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumShapeFactorCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MaximumShapeFactorCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersShearDeformationCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationXCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationYCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MaximumNumLayersStabilityXCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MaximumNumLayersStabilityYCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessServiceCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessFatigueCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessAbsoluteCheck(brg));
			Assert::IsTrue(brg_calc.MaximumCompressiveStrainCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.ShearDeformationCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.StaticAxialPrimaryShearStrainCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.StaticAxialSecondaryShearStrainCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.PrimaryShearStrainComboSumCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.SecondaryShearStrainComboSumCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.CheckApplicabilityTotalStressStabilityX(brg, brg_loads));
			Assert::IsTrue(brg_calc.CheckApplicabilityTotalStressStabilityY(brg, brg_loads));
			Assert::IsTrue(brg_calc.StabilityXDirectionCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.StabilityYDirectionCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.RestraintSystemRequirementCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.HydrostaticStressCheck(brg, brg_loads));
			Assert::IsTrue(brg_calc.HorizontalForceCheck(brg, brg_loads));


		}

		TEST_METHOD(TestEtc)
		{

			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;

			brg_calc.SetElastomerBulkModulus(WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI));
			brg_calc.SetMaximumAllowableStress(WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI));			
			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(200, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(220, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(2, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(2, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch));
			brg.SetLength(WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Inch));
			brg.SetWidth(WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Inch));
			brg.SetIntermediateLayerThickness(WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch));
			brg.SetNumIntLayers(12);
			brg.SetSteelShimThickness(WBFL::Units::ConvertToSysUnits(0.0005, WBFL::Units::Measure::Inch));
			brg_loads.SetStaticRotation(0.5);
			brg_loads.SetCyclicRotation(0.5);
			brg_loads.SetRotationX(0.5);
			brg_loads.SetRotationY(0.5);
			brg_loads.SetShearDeformation(WBFL::Units::ConvertToSysUnits(0.8, WBFL::Units::Measure::Inch));
			brg_loads.SetDeadLoad(WBFL::Units::ConvertToSysUnits(2, WBFL::Units::Measure::Kip));
			brg_loads.SetLiveLoad(WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::Kip));
			brg_loads.SetFixedTranslationX(true);
			brg_loads.SetFixedTranslationY(true);

			Assert::IsTrue(brg_calc.MinimumAreaCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MinimumLengthCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MinimumWidthCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MaximumStressCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MaximumIntermediateLayerThicknessCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MinimumShapeFactorCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MaximumShapeFactorCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.MinimumNumLayersShearDeformationCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationXCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.MinimumNumLayersRotationYCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.MaximumNumLayersStabilityXCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MaximumNumLayersStabilityYCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessServiceCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessFatigueCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessAbsoluteCheck(brg) == false);
			Assert::IsTrue(brg_calc.MaximumCompressiveStrainCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.ShearDeformationCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.StaticAxialPrimaryShearStrainCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.StaticAxialSecondaryShearStrainCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.PrimaryShearStrainComboSumCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.SecondaryShearStrainComboSumCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.CheckApplicabilityTotalStressStabilityX(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.CheckApplicabilityTotalStressStabilityY(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.StabilityXDirectionCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.StabilityYDirectionCheck(brg, brg_loads) == true);
			Assert::IsTrue(brg_calc.RestraintSystemRequirementCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.HydrostaticStressCheck(brg, brg_loads) == false);
			Assert::IsTrue(brg_calc.HorizontalForceCheck(brg, brg_loads) == false);

		}


		TEST_METHOD(TestAssymNLayRotation)
		{
			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;

			brg_calc.SetElastomerBulkModulus(WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI));
			brg_calc.SetMaximumAllowableStress(WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI));
			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(140, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(190, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(36, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch));
			brg.SetLength(WBFL::Units::ConvertToSysUnits(11, WBFL::Units::Measure::Inch));
			brg.SetWidth(WBFL::Units::ConvertToSysUnits(27, WBFL::Units::Measure::Inch));
			brg.SetIntermediateLayerThickness(WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch));
			brg.SetNumIntLayers(4);
			brg.SetSteelShimThickness(WBFL::Units::ConvertToSysUnits(0.0005, WBFL::Units::Measure::Inch));
			brg_loads.SetStaticRotation(0.014);
			brg_loads.SetCyclicRotation(0.005);
			brg_loads.SetRotationX(0.014);
			brg_loads.SetRotationY(0.005);
			brg_loads.SetShearDeformation(WBFL::Units::ConvertToSysUnits(0.47, WBFL::Units::Measure::Inch));
			brg_loads.SetDeadLoad(WBFL::Units::ConvertToSysUnits(86, WBFL::Units::Measure::Kip));
			brg_loads.SetLiveLoad(WBFL::Units::ConvertToSysUnits(47, WBFL::Units::Measure::Kip));
			brg_loads.SetFixedTranslationX(true);
			brg_loads.SetFixedTranslationY(false);



			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationX(brg, brg_loads), 10.2, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationY(brg, brg_loads), 23.2, 0.1));
			Assert::IsFalse(brg_calc.MinimumNumLayersRotationXCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumNumLayersRotationYCheck(brg, brg_loads));

		};

        
    };
}
