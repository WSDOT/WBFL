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
			brg_calc.SetAbsoluteMinimumShimThickness(WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch));

			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableStress(), WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetElastomerBulkModulus(), WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch)));

			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(200, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(220, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(36, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch));
			brg.SetLength(WBFL::Units::ConvertToSysUnits(11, WBFL::Units::Measure::Inch));
			brg.SetWidth(WBFL::Units::ConvertToSysUnits(13, WBFL::Units::Measure::Inch));
			brg.SetIntermediateLayerThickness(WBFL::Units::ConvertToSysUnits(0.5, WBFL::Units::Measure::Inch));
			brg.SetNumIntLayers(4);
			brg.SetSteelShimThickness(WBFL::Units::ConvertToSysUnits(0.0747, WBFL::Units::Measure::Inch));
			brg_loads.SetStaticRotation(0.0001);
			brg_loads.SetCyclicRotation(0.0001);
			brg_loads.SetRotationX(0.0001);
			brg_loads.SetRotationY(0.0001);
			brg_loads.SetShearDeformation(WBFL::Units::ConvertToSysUnits(0.4, WBFL::Units::Measure::Inch));
			brg_loads.SetDeadLoad(WBFL::Units::ConvertToSysUnits(20, WBFL::Units::Measure::Kip));
			brg_loads.SetLiveLoad(WBFL::Units::ConvertToSysUnits(10, WBFL::Units::Measure::Kip));
			brg_loads.SetFixedTranslationX(BearingLoads::FixedTranslationX::No);
			brg_loads.SetFixedTranslationY(BearingLoads::FixedTranslationY::No);

			Assert::IsTrue(IsEqual(brg_calc.GetConcreteElasticModulusMethodA(brg), WBFL::Units::ConvertToSysUnits(44.732, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetConcreteElasticModulusMethodB(brg), WBFL::Units::ConvertToSysUnits(42.602, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetInitialDeadLoadDeflectionMethodA(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetInstantaneousLiveLoadDeflectionMethodB(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.005, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalLoadStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(210, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetLiveLoadStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(70, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetSigmaMultiplier(brg_loads), 1.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableArea(brg, brg_loads), WBFL::Units::ConvertToSysUnits(24.0, WBFL::Units::Measure::Inch2), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Inch2)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableLength(brg, brg_loads), WBFL::Units::ConvertToSysUnits(1.85, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableWidth(brg, brg_loads), WBFL::Units::ConvertToSysUnits(2.18, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableIntermediateLayerThickness(brg, brg_loads), WBFL::Units::ConvertToSysUnits(3.55, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableShapeFactor(brg, brg_loads), 0.84, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableShapeFactor(brg, brg_loads), 10.49, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersShearDeformation(brg, brg_loads), -0.4, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationX(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationY(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableNumLayersStabilityX(brg, brg_loads), 4.5, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableNumLayersStabilityY(brg, brg_loads), 5.7, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableSteelShimThicknessService(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.009, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableSteelShimThicknessFatigue(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.003, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticDisplacementPrimaryShearStrain(brg, brg_loads), 0.133, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicDisplacementPrimaryShearStrain(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticAxialPrimaryShearStrain(brg, brg_loads), 0.150, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicAxialPrimaryShearStrain(brg, brg_loads), 0.075, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticRotationalPrimaryShearStrain(brg, brg_loads), 0.004, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicRotationalPrimaryShearStrain(brg, brg_loads), 0.004, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainComboSum(brg, brg_loads), 0.427, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticDisplacementSecondaryShearStrain(), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicDisplacementSecondaryShearStrain(), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticAxialSecondaryShearStrain(brg, brg_loads), 0.139, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicAxialSecondaryShearStrain(brg, brg_loads), 0.070, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticRotationalSecondaryShearStrain(brg, brg_loads), 0.555, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicRotationalSecondaryShearStrain(brg, brg_loads), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainComboSum(brg, brg_loads), 0.816, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.140, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.070, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.210, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryIntermediateCalculationA(brg), 0.31913, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryIntermediateCalculationA(brg), 0.24159, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryIntermediateCalculationB(brg), 0.27692, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryIntermediateCalculationB(brg), 0.25898, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetCompressibilityIndex(brg), 0.217568, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainAxialCoefficient(brg), 1.277249, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainAxialCoefficient(brg), 1.1850084, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainRotationCoefficient(brg), 0.45472, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainRotationCoefficient(brg), 0.41046221, 0.00000001));
			Assert::IsTrue(IsEqual(brg_calc.GetPeakHydrostaticStressCoefficient(brg), 1.888966, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalAxialStrain(brg, brg_loads), 0.006517, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetAlphaCoefficient(brg, brg_loads), 19.88762, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetCaCoefficient(brg, brg_loads), 20962.47, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetHydrostaticStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(146329.11, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumStress(brg), WBFL::Units::ConvertToSysUnits(450.0, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.RestraintSystemCalc(brg, brg_loads), 0.02, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetAllowableTotalLoadStressStabilityX(brg, brg_loads), WBFL::Units::ConvertToSysUnits(3298, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAllowableTotalLoadStressStabilityY(brg, brg_loads), WBFL::Units::ConvertToSysUnits(5315, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetHorizontalForce(brg, brg_loads), WBFL::Units::ConvertToSysUnits(3.8, WBFL::Units::Measure::Kip), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Kip)));

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
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessAbsoluteCheck(brg, brg_loads));
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

		TEST_METHOD(TestAllFail)
		{


			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;

			brg_calc.SetElastomerBulkModulus(WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI));
			brg_calc.SetMaximumAllowableStress(WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI));
			brg_calc.SetAbsoluteMinimumShimThickness(WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch));

			Assert::IsTrue(IsEqual(brg_calc.GetElastomerBulkModulus(), WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableStress(), WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch)));

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
			brg_loads.SetFixedTranslationX(BearingLoads::FixedTranslationX::No);
			brg_loads.SetFixedTranslationY(BearingLoads::FixedTranslationY::No);

			Assert::IsTrue(IsEqual(brg_calc.GetConcreteElasticModulusMethodA(brg), WBFL::Units::ConvertToSysUnits(45.360, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetConcreteElasticModulusMethodB(brg), WBFL::Units::ConvertToSysUnits(43.200, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetInitialDeadLoadDeflectionMethodA(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.19, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetInstantaneousLiveLoadDeflectionMethodB(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.098, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalLoadStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(8333, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetLiveLoadStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(2778, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetSigmaMultiplier(brg_loads), 1.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableArea(brg, brg_loads), WBFL::Units::ConvertToSysUnits(240.0, WBFL::Units::Measure::Inch2), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Inch2)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableLength(brg, brg_loads), WBFL::Units::ConvertToSysUnits(40.0, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableWidth(brg, brg_loads), WBFL::Units::ConvertToSysUnits(40.0, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableIntermediateLayerThickness(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.05, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableShapeFactor(brg, brg_loads), 33.33, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableShapeFactor(brg, brg_loads), 11.49, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersShearDeformation(brg, brg_loads), 6.3, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationX(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationY(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableNumLayersStabilityX(brg, brg_loads), 7.9, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableNumLayersStabilityY(brg, brg_loads), 7.9, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableSteelShimThicknessService(brg, brg_loads), WBFL::Units::ConvertToSysUnits(3.125, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableSteelShimThicknessFatigue(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.694, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticDisplacementPrimaryShearStrain(brg, brg_loads), 0.526, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicDisplacementPrimaryShearStrain(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticAxialPrimaryShearStrain(brg, brg_loads), 5.719, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicAxialPrimaryShearStrain(brg, brg_loads), 2.860, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticRotationalPrimaryShearStrain(brg, brg_loads), 0.004, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicRotationalPrimaryShearStrain(brg, brg_loads), 0.004, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainComboSum(brg, brg_loads), 11.262, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticDisplacementSecondaryShearStrain(), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicDisplacementSecondaryShearStrain(), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticAxialSecondaryShearStrain(brg, brg_loads), 5.719, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicAxialSecondaryShearStrain(brg, brg_loads), 2.860, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticRotationalSecondaryShearStrain(brg, brg_loads), 0.416, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicRotationalSecondaryShearStrain(brg, brg_loads), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainComboSum(brg, brg_loads), 11.140, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(5.556, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(2.778, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(8.333, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryIntermediateCalculationA(brg), 0.280823, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryIntermediateCalculationA(brg), 0.280823, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryIntermediateCalculationB(brg), 0.267, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryIntermediateCalculationB(brg), 0.267, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetCompressibilityIndex(brg), 0.219089, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainAxialCoefficient(brg), 1.235399, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainAxialCoefficient(brg), 1.23539904, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainRotationCoefficient(brg), 0.432983, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainRotationCoefficient(brg), 0.4329826, 0.00000001));
			Assert::IsTrue(IsEqual(brg_calc.GetPeakHydrostaticStressCoefficient(brg), 1.902494, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalAxialStrain(brg, brg_loads), 0.253485, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetAlphaCoefficient(brg, brg_loads), 921.7623, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetCaCoefficient(brg, brg_loads), 2090000000.0, 10000000.0));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumStress(brg), WBFL::Units::ConvertToSysUnits(450.0, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.RestraintSystemCalc(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetAllowableTotalLoadStressStabilityX(brg, brg_loads), WBFL::Units::ConvertToSysUnits(4073, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAllowableTotalLoadStressStabilityY(brg, brg_loads), WBFL::Units::ConvertToSysUnits(4073, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetHorizontalForce(brg, brg_loads), WBFL::Units::ConvertToSysUnits(3.8, WBFL::Units::Measure::Kip), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Kip)));
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
			Assert::IsFalse(brg_calc.MinimumSteelShimThicknessAbsoluteCheck(brg, brg_loads));
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
			brg_calc.SetAbsoluteMinimumShimThickness(WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch));

			Assert::IsTrue(IsEqual(brg_calc.GetElastomerBulkModulus(), WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableStress(), WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch)));

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
			brg_loads.SetFixedTranslationX(BearingLoads::FixedTranslationX::No);
			brg_loads.SetFixedTranslationY(BearingLoads::FixedTranslationY::Yes);

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
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessAbsoluteCheck(brg, brg_loads));
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
			brg_calc.SetAbsoluteMinimumShimThickness(WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch));
			
			
			Assert::IsTrue(IsEqual(brg_calc.GetElastomerBulkModulus(), WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableStress(), WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch)));

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
			brg_loads.SetFixedTranslationX(BearingLoads::FixedTranslationX::Yes);
			brg_loads.SetFixedTranslationY(BearingLoads::FixedTranslationY::Yes);

			Assert::IsTrue(IsEqual(brg_calc.GetConcreteElasticModulusMethodA(brg), WBFL::Units::ConvertToSysUnits(28350.0, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetInitialDeadLoadDeflectionMethodA(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.0, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetInstantaneousLiveLoadDeflectionMethodB(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.0, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalLoadStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(83, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetLiveLoadStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(28, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetSigmaMultiplier(brg_loads), 1.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableArea(brg, brg_loads), WBFL::Units::ConvertToSysUnits(2.4, WBFL::Units::Measure::Inch2), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Inch2)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableLength(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.4, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableWidth(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.4, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableIntermediateLayerThickness(brg, brg_loads), WBFL::Units::ConvertToSysUnits(4.5, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableShapeFactor(brg, brg_loads), 0.33, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableShapeFactor(brg, brg_loads), 16.91, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersShearDeformation(brg, brg_loads), 110.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationX(brg, brg_loads), 35639999.0, 1.0));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationY(brg, brg_loads), 35639999.0, 1.0));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableNumLayersStabilityX(brg, brg_loads), 142.8, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableNumLayersStabilityY(brg, brg_loads), 142.8, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableSteelShimThicknessService(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableSteelShimThicknessFatigue(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.0, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::Inch)));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticDisplacementPrimaryShearStrain(brg, brg_loads), 1.290, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicDisplacementPrimaryShearStrain(brg, brg_loads), 0.0, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticAxialPrimaryShearStrain(brg, brg_loads), 0.027, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicAxialPrimaryShearStrain(brg, brg_loads), 0.014, 0.014));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticDisplacementSecondaryShearStrain(), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicDisplacementSecondaryShearStrain(), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticAxialSecondaryShearStrain(brg, brg_loads), 0.027, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicAxialSecondaryShearStrain(brg, brg_loads), 0.014, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticRotationalSecondaryShearStrain(brg, brg_loads), -127.520, 0.01));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicRotationalSecondaryShearStrain(brg, brg_loads), 0.000, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainComboSum(brg, brg_loads), -127.469, 0.001));
			Assert::IsTrue(IsEqual(brg_calc.GetStaticStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.056, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetCyclicStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.028, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetTotalStress(brg, brg_loads), WBFL::Units::ConvertToSysUnits(0.083, WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(0.001, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryIntermediateCalculationA(brg), 0.114546, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryIntermediateCalculationA(brg), 0.114546, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryIntermediateCalculationB(brg), 0.01405263, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryIntermediateCalculationB(brg), 0.01405263, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetCompressibilityIndex(brg), 5.477226, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainAxialCoefficient(brg), 14.60022, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainAxialCoefficient(brg), 14.6002174, 0.000001));
			Assert::IsTrue(IsEqual(brg_calc.GetPrimaryShearStrainRotationCoefficient(brg), -0.460488, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetSecondaryShearStrainRotationCoefficient(brg), -0.460488, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetPeakHydrostaticStressCoefficient(brg), -7.87764, 0.00001));
			Assert::IsTrue(IsEqual(brg_calc.GetCaCoefficient(brg, brg_loads), 0.2566, 0.0001));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumStress(brg), WBFL::Units::ConvertToSysUnits(450.0, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.RestraintSystemCalc(brg, brg_loads), 1370769.23, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetAllowableTotalLoadStressStabilityX(brg, brg_loads), WBFL::Units::ConvertToSysUnits(298526, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAllowableTotalLoadStressStabilityY(brg, brg_loads), WBFL::Units::ConvertToSysUnits(298526, WBFL::Units::Measure::PSI), WBFL::Units::ConvertToSysUnits(1, WBFL::Units::Measure::PSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetHorizontalForce(brg, brg_loads), WBFL::Units::ConvertToSysUnits(9.3, WBFL::Units::Measure::Kip), WBFL::Units::ConvertToSysUnits(0.1, WBFL::Units::Measure::Kip)));

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
			Assert::IsTrue(brg_calc.MinimumSteelShimThicknessAbsoluteCheck(brg, brg_loads) == false);
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
			brg_calc.SetAbsoluteMinimumShimThickness(WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch));


			Assert::IsTrue(IsEqual(brg_calc.GetElastomerBulkModulus(), WBFL::Units::ConvertToSysUnits(450, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetMaximumAllowableStress(), WBFL::Units::ConvertToSysUnits(1.25, WBFL::Units::Measure::KSI)));
			Assert::IsTrue(IsEqual(brg_calc.GetAbsoluteMinimumShimThickness(), WBFL::Units::ConvertToSysUnits(0.0625, WBFL::Units::Measure::Inch)));

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
			brg_loads.SetFixedTranslationX(BearingLoads::FixedTranslationX::Yes);
			brg_loads.SetFixedTranslationY(BearingLoads::FixedTranslationY::No);



			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationX(brg, brg_loads), 10.2, 0.1));
			Assert::IsTrue(IsEqual(brg_calc.GetMinimumAllowableNumLayersRotationY(brg, brg_loads), 23.2, 0.1));
			Assert::IsFalse(brg_calc.MinimumNumLayersRotationXCheck(brg, brg_loads));
			Assert::IsFalse(brg_calc.MinimumNumLayersRotationYCheck(brg, brg_loads));

		};

        
    };
}
