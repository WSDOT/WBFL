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
			BearingCalculator brg_calc;
			Bearing brg;
			BearingLoads brg_loads;
			BearingDesignCriteria criteria;

			const auto& spec = WBFL::LRFD::BDSManager::GetEdition();

			const auto& artifact = 
				brg_calc.CheckBearing(brg, brg_loads, spec, criteria);


			criteria.bMinimumTotalBearingHeight = true;
			criteria.bRequiredBearingEdgeToGirderEdgeDistance = true;
			criteria.bMaximumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumTotalBearingHeight = true;
			criteria.bMaximumTotalLoad = true;

			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(165, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(165, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(36, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(24, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch));
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

			Float64 gdrFlgDist = WBFL::Units::ConvertToSysUnits(1.0, WBFL::Units::Measure::Inch);

			Assert::IsTrue(artifact.MinimumAreaCheck());
			Assert::IsTrue(artifact.MinimumLengthCheck());
			Assert::IsTrue(artifact.MinimumWidthCheck());
			Assert::IsTrue(artifact.MaximumStressCheck());
			Assert::IsTrue(artifact.MaximumIntermediateLayerThicknessCheck());
			Assert::IsTrue(artifact.MinimumShapeFactorCheck());
			Assert::IsTrue(artifact.MaximumShapeFactorCheck());
			Assert::IsTrue(artifact.MinimumNumLayersShearDeformationCheck());
			Assert::IsTrue(artifact.MinimumNumLayersRotationXCheck());
			Assert::IsTrue(artifact.MinimumNumLayersRotationYCheck());
			Assert::IsTrue(artifact.MaximumNumLayersStabilityXCheck());
			Assert::IsTrue(artifact.MaximumNumLayersStabilityYCheck());
			Assert::IsTrue(artifact.MinimumSteelShimThicknessServiceCheck());
			Assert::IsTrue(artifact.MinimumSteelShimThicknessFatigueCheck());
			Assert::IsTrue(artifact.MinimumElastomerCoverThicknessCheck());
			Assert::IsTrue(artifact.MaximumElastomerCoverThicknessCheck());
			Assert::IsTrue(artifact.MaximumCompressiveStrainCheck());
			Assert::IsTrue(artifact.ShearDeformationCheck());
			Assert::IsTrue(artifact.StaticAxialPrimaryShearStrainCheck());
			Assert::IsTrue(artifact.StaticAxialSecondaryShearStrainCheck());
			Assert::IsTrue(artifact.PrimaryShearStrainComboSumCheck());
			Assert::IsTrue(artifact.SecondaryShearStrainComboSumCheck());
			Assert::IsFalse(criteria.CheckApplicabilityTotalStressStabilityX());
			Assert::IsFalse(criteria.CheckApplicabilityTotalStressStabilityY());
			Assert::IsTrue(artifact.RestraintSystemRequirementCheck());
			Assert::IsFalse(artifact.HydrostaticStressCheck());
			Assert::IsTrue(artifact.HorizontalForceCheck());
			Assert::IsTrue(artifact.MaximumLiveLoadDeflectionMethodBCheck());
			Assert::IsTrue(artifact.MinimumAllowableShearModulusCheck());
			Assert::IsTrue(artifact.MaximumAllowableShearModulusCheck());
			Assert::IsTrue(artifact.RequiredIntermediateElastomerThicknessCheck());
			Assert::IsTrue(artifact.MinimumTotalBearingHeightCheck());
			Assert::IsTrue(artifact.MinimumBearingEdgeToBottomFlangeEdgeDistCheck());
			Assert::IsTrue(artifact.MaximumBearingEdgeToBottomFlangeEdgeDistCheck());
			Assert::IsTrue(artifact.RequiredBearingEdgeToBottomFlangeEdgeDistCheck());
			Assert::IsTrue(artifact.MaximumTotalLoadCheck());
		}

		TEST_METHOD(TestAllFail)
		{


			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;
			BearingDesignCriteria criteria;

			const auto& spec = WBFL::LRFD::BDSManager::GetEdition();

			const auto& artifact =
				brg_calc.CheckBearing(brg, brg_loads, spec, criteria);

			criteria.bMinimumTotalBearingHeight = true;
			criteria.bRequiredBearingEdgeToGirderEdgeDistance = true;
			criteria.bMaximumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumTotalBearingHeight = true;
			criteria.bMaximumTotalLoad = true;

			brg.SetShearModulusMinimum(WBFL::Units::ConvertToSysUnits(70, WBFL::Units::Measure::PSI));
			brg.SetShearModulusMaximum(WBFL::Units::ConvertToSysUnits(220, WBFL::Units::Measure::PSI));
			brg.SetYieldStrength(WBFL::Units::ConvertToSysUnits(2, WBFL::Units::Measure::KSI));
			brg.SetFatigueThreshold(WBFL::Units::ConvertToSysUnits(2, WBFL::Units::Measure::KSI));
			brg.SetCoverThickness(WBFL::Units::ConvertToSysUnits(0.01, WBFL::Units::Measure::Inch));
			brg.SetLength(WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Inch));
			brg.SetWidth(WBFL::Units::ConvertToSysUnits(6, WBFL::Units::Measure::Inch));
			brg.SetIntermediateLayerThickness(WBFL::Units::ConvertToSysUnits(0.25, WBFL::Units::Measure::Inch));
			brg.SetNumIntLayers(1);
			brg.SetSteelShimThickness(WBFL::Units::ConvertToSysUnits(0.0005, WBFL::Units::Measure::Inch));
			brg_loads.SetStaticRotation(0.0001);
			brg_loads.SetCyclicRotation(0.0001);
			brg_loads.SetRotationX(0.000);
			brg_loads.SetRotationY(0.000);
			brg_loads.SetShearDeformation(WBFL::Units::ConvertToSysUnits(0.8, WBFL::Units::Measure::Inch));
			brg_loads.SetDeadLoad(WBFL::Units::ConvertToSysUnits(2000, WBFL::Units::Measure::Kip));
			brg_loads.SetLiveLoad(WBFL::Units::ConvertToSysUnits(100, WBFL::Units::Measure::Kip));
			brg_loads.SetFixedTranslationX(false);
			brg_loads.SetFixedTranslationY(false);

			Float64 gdrFlgDist = WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Inch);

			Assert::IsFalse(artifact.MinimumAreaCheck());
			Assert::IsFalse(artifact.MinimumLengthCheck());
			Assert::IsFalse(artifact.MinimumWidthCheck());
			Assert::IsFalse(artifact.MaximumStressCheck());
			Assert::IsFalse(artifact.MaximumIntermediateLayerThicknessCheck());
			Assert::IsFalse(artifact.MinimumShapeFactorCheck());
			Assert::IsFalse(artifact.MaximumShapeFactorCheck());
			Assert::IsFalse(artifact.MinimumNumLayersShearDeformationCheck());
			Assert::IsTrue(artifact.MinimumNumLayersRotationXCheck());
			Assert::IsTrue(artifact.MinimumNumLayersRotationYCheck());
			Assert::IsTrue(artifact.MaximumNumLayersStabilityXCheck());
			Assert::IsTrue(artifact.MaximumNumLayersStabilityYCheck());
			Assert::IsFalse(artifact.MinimumSteelShimThicknessServiceCheck());
			Assert::IsFalse(artifact.MinimumSteelShimThicknessFatigueCheck());
			Assert::IsFalse(artifact.MinimumSteelShimThicknessAbsoluteCheck());
			Assert::IsFalse(artifact.MinimumElastomerCoverThicknessCheck());
			Assert::IsTrue(artifact.MaximumElastomerCoverThicknessCheck());
			Assert::IsFalse(artifact.MaximumCompressiveStrainCheck());
			Assert::IsFalse(artifact.ShearDeformationCheck());
			Assert::IsFalse(artifact.StaticAxialPrimaryShearStrainCheck());
			Assert::IsFalse(artifact.StaticAxialSecondaryShearStrainCheck());
			Assert::IsFalse(artifact.PrimaryShearStrainComboSumCheck());
			Assert::IsFalse(artifact.SecondaryShearStrainComboSumCheck());
			Assert::IsFalse(criteria.CheckApplicabilityTotalStressStabilityX());
			Assert::IsFalse(criteria.CheckApplicabilityTotalStressStabilityY());
			Assert::IsTrue(artifact.RestraintSystemRequirementCheck());
			Assert::IsFalse(artifact.HydrostaticStressCheck());
			Assert::IsTrue(artifact.HorizontalForceCheck());
			Assert::IsTrue(artifact.MaximumLiveLoadDeflectionMethodBCheck());
			Assert::IsFalse(artifact.MinimumAllowableShearModulusCheck());
			Assert::IsFalse(artifact.MaximumAllowableShearModulusCheck());
			Assert::IsFalse(artifact.RequiredIntermediateElastomerThicknessCheck());
			Assert::IsFalse(artifact.MinimumTotalBearingHeightCheck());
			Assert::IsTrue(artifact.MinimumBearingEdgeToBottomFlangeEdgeDistCheck());
			Assert::IsFalse(artifact.MaximumBearingEdgeToBottomFlangeEdgeDistCheck());
			Assert::IsFalse(artifact.RequiredBearingEdgeToBottomFlangeEdgeDistCheck());
			Assert::IsFalse(artifact.MaximumTotalLoadCheck());
		}


		TEST_METHOD(TestPGExampleFail)
		{
			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;
			BearingDesignCriteria criteria;

			const auto& spec = WBFL::LRFD::BDSManager::GetEdition();

			const auto& artifact =
				brg_calc.CheckBearing(brg, brg_loads, spec, criteria);

			criteria.bMinimumTotalBearingHeight = true;
			criteria.bRequiredBearingEdgeToGirderEdgeDistance = true;
			criteria.bMaximumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumTotalBearingHeight = true;
			criteria.bMaximumTotalLoad = true;


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

			Assert::IsTrue(artifact.MinimumAreaCheck());
			Assert::IsTrue(artifact.MinimumLengthCheck());
			Assert::IsTrue(artifact.MinimumWidthCheck());
			Assert::IsTrue(artifact.MaximumStressCheck());
			Assert::IsTrue(artifact.MaximumIntermediateLayerThicknessCheck());
			Assert::IsTrue(artifact.MinimumShapeFactorCheck());
			Assert::IsTrue(artifact.MaximumShapeFactorCheck());
			Assert::IsTrue(artifact.MinimumNumLayersShearDeformationCheck());
			Assert::IsTrue(artifact.MinimumNumLayersRotationXCheck());
			Assert::IsTrue(artifact.MinimumNumLayersRotationYCheck());
			Assert::IsFalse(artifact.MaximumNumLayersStabilityXCheck());
			Assert::IsFalse(artifact.MaximumNumLayersStabilityYCheck());
			Assert::IsTrue(artifact.MinimumSteelShimThicknessServiceCheck());
			Assert::IsTrue(artifact.MinimumSteelShimThicknessFatigueCheck());
			Assert::IsTrue(artifact.MinimumSteelShimThicknessAbsoluteCheck());
			Assert::IsTrue(artifact.MaximumCompressiveStrainCheck());
			Assert::IsTrue(artifact.ShearDeformationCheck());
			Assert::IsTrue(artifact.StaticAxialPrimaryShearStrainCheck());
			Assert::IsTrue(artifact.StaticAxialSecondaryShearStrainCheck());
			Assert::IsTrue(artifact.PrimaryShearStrainComboSumCheck());
			Assert::IsTrue(artifact.SecondaryShearStrainComboSumCheck());
			Assert::IsTrue(criteria.CheckApplicabilityTotalStressStabilityX());
			Assert::IsTrue(criteria.CheckApplicabilityTotalStressStabilityY());
			Assert::IsTrue(artifact.StabilityXDirectionCheck());
			Assert::IsTrue(artifact.StabilityYDirectionCheck());
			Assert::IsTrue(artifact.RestraintSystemRequirementCheck());
			Assert::IsFalse(artifact.HydrostaticStressCheck());
			Assert::IsTrue(artifact.HorizontalForceCheck());


		}

		TEST_METHOD(TestEtc)
		{
			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;
			BearingDesignCriteria criteria;

			const auto& spec = WBFL::LRFD::BDSManager::GetEdition();

			const auto& artifact =
				brg_calc.CheckBearing(brg, brg_loads, spec, criteria);

			criteria.bMinimumTotalBearingHeight = true;
			criteria.bRequiredBearingEdgeToGirderEdgeDistance = true;
			criteria.bMaximumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumTotalBearingHeight = true;
			criteria.bMaximumTotalLoad = true;
		
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

			Assert::IsTrue(artifact.MinimumAreaCheck() == true);
			Assert::IsTrue(artifact.MinimumLengthCheck() == true);
			Assert::IsTrue(artifact.MinimumWidthCheck() == true);
			Assert::IsTrue(artifact.MaximumStressCheck() == true);
			Assert::IsTrue(artifact.MaximumIntermediateLayerThicknessCheck() == true);
			Assert::IsTrue(artifact.MinimumShapeFactorCheck() == true);
			Assert::IsTrue(artifact.MaximumShapeFactorCheck() == false);
			Assert::IsTrue(artifact.MinimumNumLayersShearDeformationCheck() == false);
			Assert::IsTrue(artifact.MinimumNumLayersRotationXCheck() == false);
			Assert::IsTrue(artifact.MinimumNumLayersRotationYCheck() == false);
			Assert::IsTrue(artifact.MaximumNumLayersStabilityXCheck() == true);
			Assert::IsTrue(artifact.MaximumNumLayersStabilityYCheck() == true);
			Assert::IsTrue(artifact.MinimumSteelShimThicknessServiceCheck() == false);
			Assert::IsTrue(artifact.MinimumSteelShimThicknessFatigueCheck() == true);
			Assert::IsTrue(artifact.MinimumSteelShimThicknessAbsoluteCheck() == false);
			Assert::IsTrue(artifact.MaximumCompressiveStrainCheck() == true);
			Assert::IsTrue(artifact.ShearDeformationCheck() == false);
			Assert::IsTrue(artifact.StaticAxialPrimaryShearStrainCheck() == true);
			Assert::IsTrue(artifact.StaticAxialSecondaryShearStrainCheck() == true);
			Assert::IsTrue(artifact.PrimaryShearStrainComboSumCheck() == false);
			Assert::IsTrue(artifact.SecondaryShearStrainComboSumCheck() == false);
			Assert::IsTrue(criteria.CheckApplicabilityTotalStressStabilityX() == true);
			Assert::IsTrue(criteria.CheckApplicabilityTotalStressStabilityY() == true);
			Assert::IsTrue(artifact.StabilityXDirectionCheck() == true);
			Assert::IsTrue(artifact.StabilityYDirectionCheck() == true);
			Assert::IsTrue(artifact.RestraintSystemRequirementCheck() == false);
			Assert::IsTrue(artifact.HydrostaticStressCheck() == false);
			Assert::IsTrue(artifact.HorizontalForceCheck() == false);

		}


		TEST_METHOD(TestAssymNLayRotation)
		{
			Bearing brg;
			BearingLoads brg_loads;
			BearingCalculator brg_calc;
			BearingDesignCriteria criteria;

			const auto& spec = WBFL::LRFD::BDSManager::GetEdition();

			const auto& artifact =
				brg_calc.CheckBearing(brg, brg_loads, spec, criteria);

			criteria.bMinimumTotalBearingHeight = true;
			criteria.bRequiredBearingEdgeToGirderEdgeDistance = true;
			criteria.bMaximumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumBearingEdgeToGirderEdgeDistance = true;
			criteria.bMinimumTotalBearingHeight = true;
			criteria.bMaximumTotalLoad = true;

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



			Assert::IsTrue(IsEqual(criteria.GetMinimumAllowableNumLayersRotationX(), 10.2, 0.1));
			Assert::IsTrue(IsEqual(criteria.GetMinimumAllowableNumLayersRotationY(), 23.2, 0.1));
			Assert::IsFalse(artifact.MinimumNumLayersRotationXCheck());
			Assert::IsFalse(artifact.MinimumNumLayersRotationYCheck());

		};

		//TO DO: add stability failure when applicable

        
    };
}
