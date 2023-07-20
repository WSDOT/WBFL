#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;
using namespace WBFL::Materials;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLRFDTimeDependentConcrete)
	{
	public:
		
		TEST_METHOD(ModelParameters)
		{
			Float64 A, B;
			LRFDTimeDependentConcrete::GetModelParameters(CuringType::Moist, CementType::TypeI, &A, &B);
			Assert::AreEqual(345600.0, A, 0.1);
			Assert::AreEqual(0.85, B);

			LRFDTimeDependentConcrete::GetModelParameters(CuringType::Moist, CementType::TypeII, &A, &B);
			Assert::AreEqual(198720.0, A, 0.1);
			Assert::AreEqual(0.92, B);

			LRFDTimeDependentConcrete::GetModelParameters(CuringType::Steam, CementType::TypeI, &A, &B);
			Assert::AreEqual(86400.0, A, 0.1);
			Assert::AreEqual(0.95, B);

			LRFDTimeDependentConcrete::GetModelParameters(CuringType::Steam, CementType::TypeII, &A, &B);
			Assert::AreEqual(60480.0, A, 0.1);
			Assert::AreEqual(0.98, B);
		}

		TEST_METHOD(MoistCuredConcrete)
		{
			LRFDTimeDependentConcrete concrete;
			concrete.SetA(4.0);
			concrete.SetBeta(0.85);
			concrete.SetCuringType(CuringType::Moist);
			concrete.SetCureTime(3);
			concrete.SetAgeAtInitialLoading(1.0);
			concrete.SetTimeAtCasting(0.0);
			concrete.SetFc28(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			concrete.SetEc28(WBFL::Units::ConvertToSysUnits(4000, WBFL::Units::Measure::KSI));
			concrete.SetStrengthDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetWeightDensity(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetRelativeHumidity(70);
			concrete.SetUltimateCreepCoefficient(3.5);
			concrete.SetUltimateShrinkageStrain(480e-03);
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5, WBFL::Units::Measure::Inch));

			{
				// this call only valid before LRFD 2005
				LRFDAutoVersion av;
				LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEdition2004);
				Assert::AreEqual(0.75551897172962801, concrete.GetConcreteStrengthFactor());
			}
			Assert::ExpectException<XCreepCoefficient>([&]() {concrete.GetConcreteStrengthFactor(); });
			Assert::AreEqual(0.99666666666666670, concrete.GetRelativeHumidityFactorCreep());
			Assert::AreEqual(1.0, concrete.GetRelativeHumidityFactorShrinkage());

			Assert::AreEqual(40555186.953998156, concrete.GetFc(1));
			Assert::AreEqual(40557174.942530811, concrete.GetFc(10));
			Assert::AreEqual(40557316.949169643, concrete.GetFc(28));
			Assert::AreEqual(40557356.395634696, concrete.GetFc(56));
			Assert::AreEqual(40557378.584305011, concrete.GetFc(128));

			Assert::AreEqual(31184498360.859184, concrete.GetEc(1));
			Assert::AreEqual(31185002804.948540, concrete.GetEc(10));
			Assert::AreEqual(31185038837.927650, concrete.GetEc(28));
			Assert::AreEqual(31185048847.118298, concrete.GetEc(56));
			Assert::AreEqual(31185054477.293732, concrete.GetEc(128));

			Assert::AreEqual(4013228.9557353212, concrete.GetShearFr(1));
			Assert::AreEqual(4013327.3174489806, concrete.GetShearFr(10));
			Assert::AreEqual(4013334.3435624219, concrete.GetShearFr(28));
			Assert::AreEqual(4013336.2952671489, concrete.GetShearFr(56));
			Assert::AreEqual(4013337.3931023092, concrete.GetShearFr(128));

			Assert::AreEqual(4013228.9557353212, concrete.GetFlexureFr(1));
			Assert::AreEqual(4013327.3174489806, concrete.GetFlexureFr(10));
			Assert::AreEqual(4013334.3435624219, concrete.GetFlexureFr(28));
			Assert::AreEqual(4013336.2952671489, concrete.GetFlexureFr(56));
			Assert::AreEqual(4013337.3931023092, concrete.GetFlexureFr(128));

			Assert::AreEqual(-0.00026048498393823558, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			LRFDTimeDependentConcreteShrinkageDetails* shrinkage_details = (LRFDTimeDependentConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(-0.00026048498393823558, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Moist);
			Assert::AreEqual(1.0, shrinkage_details->kvs);
			Assert::AreEqual(1.02, shrinkage_details->khs);
			Assert::AreEqual(0.72650699982325662, shrinkage_details->kf);
			Assert::AreEqual(0.73232098731697270, shrinkage_details->ktd);

			Assert::AreEqual(0.0000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(-5.8646822857849601e-05, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(-0.00014709057299663896, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(-0.00021312375277312418, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(-0.00027709992269166049, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(0.27945788983433939, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			LRFDTimeDependentConcreteCreepDetails* creep_details = (LRFDTimeDependentConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(0.27945788983433939, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(40556659.519382015, creep_details->fci);
			Assert::AreEqual(0.72650699982325662, creep_details->kf);
			Assert::AreEqual(0.0, creep_details->kc);
			Assert::AreEqual(1.0, creep_details->kvs);
			Assert::AreEqual(0.99666666666666670, creep_details->khc);
			Assert::AreEqual(0.20245241952051715, creep_details->ktd);

			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(0.27945788983433939, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(0.59674765593040369, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(0.83931318304003222, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(1.0791065708804275, concrete.GetCreepCoefficient(128, 1));
		}

		TEST_METHOD(SteamCuredConcrete)
		{
			LRFDTimeDependentConcrete concrete;
			concrete.SetA(4.0);
			concrete.SetBeta(0.85);
			concrete.SetCuringType(CuringType::Steam);
			concrete.SetCureTime(3);
			concrete.SetAgeAtInitialLoading(1.0);
			concrete.SetTimeAtCasting(0.0);
			concrete.SetFc28(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			concrete.SetEc28(WBFL::Units::ConvertToSysUnits(4000, WBFL::Units::Measure::KSI));
			concrete.SetStrengthDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetWeightDensity(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetRelativeHumidity(70);
			concrete.SetUltimateCreepCoefficient(3.5);
			concrete.SetUltimateShrinkageStrain(480e-03);
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5, WBFL::Units::Measure::Inch));

			{
				// this call only valid before LRFD 2005
				LRFDAutoVersion av;
				LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::ThirdEdition2004);
				Assert::AreEqual(0.75551897172962801, concrete.GetConcreteStrengthFactor());
			}
			Assert::ExpectException<XCreepCoefficient>([&]() {concrete.GetConcreteStrengthFactor(); });
			Assert::AreEqual(0.99666666666666670, concrete.GetRelativeHumidityFactorCreep());
			Assert::AreEqual(1.0, concrete.GetRelativeHumidityFactorShrinkage());

			Assert::AreEqual(40555186.953998156, concrete.GetFc(1));
			Assert::AreEqual(40557174.942530811, concrete.GetFc(10));
			Assert::AreEqual(40557316.949169643, concrete.GetFc(28));
			Assert::AreEqual(40557356.395634696, concrete.GetFc(56));
			Assert::AreEqual(40557378.584305011, concrete.GetFc(128));

			Assert::AreEqual(31184498360.859184, concrete.GetEc(1));
			Assert::AreEqual(31185002804.948540, concrete.GetEc(10));
			Assert::AreEqual(31185038837.927650, concrete.GetEc(28));
			Assert::AreEqual(31185048847.118298, concrete.GetEc(56));
			Assert::AreEqual(31185054477.293732, concrete.GetEc(128));

			Assert::AreEqual(4013228.9557353212, concrete.GetShearFr(1));
			Assert::AreEqual(4013327.3174489806, concrete.GetShearFr(10));
			Assert::AreEqual(4013334.3435624219, concrete.GetShearFr(28));
			Assert::AreEqual(4013336.2952671489, concrete.GetShearFr(56));
			Assert::AreEqual(4013337.3931023092, concrete.GetShearFr(128));

			Assert::AreEqual(4013228.9557353212, concrete.GetFlexureFr(1));
			Assert::AreEqual(4013327.3174489806, concrete.GetFlexureFr(10));
			Assert::AreEqual(4013334.3435624219, concrete.GetFlexureFr(28));
			Assert::AreEqual(4013336.2952671489, concrete.GetFlexureFr(56));
			Assert::AreEqual(4013337.3931023092, concrete.GetFlexureFr(128));

			Assert::AreEqual(-0.00026048498393823558, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			LRFDTimeDependentConcreteShrinkageDetails* shrinkage_details = (LRFDTimeDependentConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(-0.00026048498393823558, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Steam);
			Assert::AreEqual(1.0, shrinkage_details->kvs);
			Assert::AreEqual(1.02, shrinkage_details->khs);
			Assert::AreEqual(0.72650699982325662, shrinkage_details->kf);
			Assert::AreEqual(0.73232098731697270, shrinkage_details->ktd);

			Assert::AreEqual(0.0000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(-5.8646822857849601e-05, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(-0.00014709057299663896, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(-0.00021312375277312418, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(-0.00027709992269166049, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(0.27945788983433939, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			LRFDTimeDependentConcreteCreepDetails* creep_details = (LRFDTimeDependentConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(0.27945788983433939, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(40556659.519382015, creep_details->fci);
			Assert::AreEqual(0.72650699982325662, creep_details->kf);
			Assert::AreEqual(0.0, creep_details->kc);
			Assert::AreEqual(1.0, creep_details->kvs);
			Assert::AreEqual(0.99666666666666670, creep_details->khc);
			Assert::AreEqual(0.20245241952051715, creep_details->ktd);

			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(0.27945788983433939, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(0.59674765593040369, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(0.83931318304003222, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(1.0791065708804275, concrete.GetCreepCoefficient(128, 1));
		}
	};
}
