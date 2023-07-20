#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestACI209Concrete)
	{
	public:
		TEST_METHOD(ModelParameters)
		{
			Float64 A, B;
			ACI209Concrete::GetModelParameters(CuringType::Moist, CementType::TypeI, &A, &B);
			Assert::AreEqual(345600.0, A, 0.1);
			Assert::AreEqual(0.85, B);

			ACI209Concrete::GetModelParameters(CuringType::Moist, CementType::TypeII, &A, &B);
			Assert::AreEqual(198720.0, A, 0.1);
			Assert::AreEqual(0.92, B);

			ACI209Concrete::GetModelParameters(CuringType::Steam, CementType::TypeI, &A, &B);
			Assert::AreEqual(86400.0, A, 0.1);
			Assert::AreEqual(0.95, B);

			ACI209Concrete::GetModelParameters(CuringType::Steam, CementType::TypeII, &A, &B);
			Assert::AreEqual(60480.0, A, 0.1);
			Assert::AreEqual(0.98, B);
		}
		TEST_METHOD(MoistCuredConcrete)
		{
			ACI209Concrete concrete;
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
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5,WBFL::Units::Measure::Inch));

			Assert::AreEqual(1.1, concrete.GetInitialMoistCureFactor());
			Assert::AreEqual(0.80099999999999993, concrete.GetRelativeHumidityFactorCreep());
			Assert::AreEqual(0.68599999999999983, concrete.GetRelativeHumidityFactorShrinkage());
			Assert::AreEqual(0.78047409599006601, concrete.GetSizeFactorCreep());
			Assert::AreEqual(0.78845618377806803, concrete.GetSizeFactorShrinkage());

			Assert::AreEqual(40555186.953998156, concrete.GetFc(1));
			Assert::AreEqual(40557174.942530811, concrete.GetFc(10));
			Assert::AreEqual(40557316.949169643, concrete.GetFc(28));
			Assert::AreEqual(40557356.395634696, concrete.GetFc(56));
			Assert::AreEqual(40557378.584305011, concrete.GetFc(128));

			Assert::AreEqual(32057785877.040569, concrete.GetEc(1));
			Assert::AreEqual(32058571593.178314, concrete.GetEc(10));
			Assert::AreEqual(32058627717.970276, concrete.GetEc(28));
			Assert::AreEqual(32058643308.242580, concrete.GetEc(56));
			Assert::AreEqual(32058652077.780750, concrete.GetEc(128));

			Assert::AreEqual(3885792.2275200691, concrete.GetShearFr(1));
			Assert::AreEqual(3885887.4658397962, concrete.GetShearFr(10));
			Assert::AreEqual(3885894.2688448830, concrete.GetShearFr(28));
			Assert::AreEqual(3885896.1585748591, concrete.GetShearFr(56));
			Assert::AreEqual(3885897.2215491827, concrete.GetShearFr(128));

			Assert::AreEqual(3885792.2275200691, concrete.GetFlexureFr(1));
			Assert::AreEqual(3885887.4658397962, concrete.GetFlexureFr(10));
			Assert::AreEqual(3885894.2688448830, concrete.GetFlexureFr(28));
			Assert::AreEqual(3885896.1585748591, concrete.GetFlexureFr(56));
			Assert::AreEqual(3885897.2215491827, concrete.GetFlexureFr(128));

			Assert::AreEqual(0.20986180552384079, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			ACI209ConcreteShrinkageDetails* shrinkage_details = (ACI209ConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(0.20986180552384079, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Moist);
			Assert::AreEqual(35.0, shrinkage_details->f);
			Assert::AreEqual(0.73484848484848486, shrinkage_details->time_factor);
			Assert::AreEqual(1.1, shrinkage_details->curing_factor);
			Assert::AreEqual(0.68599999999999983, shrinkage_details->humidity_factor);
			Assert::AreEqual(0.78845618377806803, shrinkage_details->vs_factor);

			Assert::AreEqual(0.00000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(0.04759752290231440, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(0.11899380725578601, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(0.17200013957881796, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(0.22311338860459876, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(0.59525981535025330, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			ACI209ConcreteCreepDetails* creep_details = (ACI209ConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(0.59525981535025330, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(40555186.953998156, creep_details->fci);
			Assert::AreEqual(0.80099999999999993, creep_details->humidity_factor);
			Assert::AreEqual(1.0, creep_details->loading_age_factor);
			Assert::AreEqual(0.27204923656013341, creep_details->time_factor);
			Assert::AreEqual(0.78047409599006601, creep_details->vs_factor);

			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(0.59525981535025330, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(0.91775402914691406, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(1.1496757127213619, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(1.4146989580422951, concrete.GetCreepCoefficient(128, 1));
		}

		TEST_METHOD(SteamCuredConcrete)
		{
			ACI209Concrete concrete;
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

			Assert::AreEqual(1.0, concrete.GetInitialMoistCureFactor());
			Assert::AreEqual(0.80099999999999993, concrete.GetRelativeHumidityFactorCreep());
			Assert::AreEqual(0.68599999999999983, concrete.GetRelativeHumidityFactorShrinkage());
			Assert::AreEqual(0.78047409599006601, concrete.GetSizeFactorCreep());
			Assert::AreEqual(0.78845618377806803, concrete.GetSizeFactorShrinkage());

			Assert::AreEqual(40555186.953998156, concrete.GetFc(1));
			Assert::AreEqual(40557174.942530811, concrete.GetFc(10));
			Assert::AreEqual(40557316.949169643, concrete.GetFc(28));
			Assert::AreEqual(40557356.395634696, concrete.GetFc(56));
			Assert::AreEqual(40557378.584305011, concrete.GetFc(128));

			Assert::AreEqual(32057785877.040569, concrete.GetEc(1));
			Assert::AreEqual(32058571593.178314, concrete.GetEc(10));
			Assert::AreEqual(32058627717.970276, concrete.GetEc(28));
			Assert::AreEqual(32058643308.242580, concrete.GetEc(56));
			Assert::AreEqual(32058652077.780750, concrete.GetEc(128));

			Assert::AreEqual(3885792.2275200691, concrete.GetShearFr(1));
			Assert::AreEqual(3885887.4658397962, concrete.GetShearFr(10));
			Assert::AreEqual(3885894.2688448830, concrete.GetShearFr(28));
			Assert::AreEqual(3885896.1585748591, concrete.GetShearFr(56));
			Assert::AreEqual(3885897.2215491827, concrete.GetShearFr(128));

			Assert::AreEqual(3885792.2275200691, concrete.GetFlexureFr(1));
			Assert::AreEqual(3885887.4658397962, concrete.GetFlexureFr(10));
			Assert::AreEqual(3885894.2688448830, concrete.GetFlexureFr(28));
			Assert::AreEqual(3885896.1585748591, concrete.GetFlexureFr(56));
			Assert::AreEqual(3885897.2215491827, concrete.GetFlexureFr(128));

			Assert::AreEqual(0.16568037278197956, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			ACI209ConcreteShrinkageDetails* shrinkage_details = (ACI209ConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(0.16568037278197956, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Steam);
			Assert::AreEqual(55.0, shrinkage_details->f);
			Assert::AreEqual(0.63815789473684215, shrinkage_details->time_factor);
			Assert::AreEqual(1.0, shrinkage_details->curing_factor);
			Assert::AreEqual(0.68599999999999983, shrinkage_details->humidity_factor);
			Assert::AreEqual(0.78845618377806803, shrinkage_details->vs_factor);

			Assert::AreEqual(0.0000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(0.029312257505824117, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(0.081132141310763170, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(0.12740751079912441, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(0.18029364735725151, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(0.59525981535025330, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			ACI209ConcreteCreepDetails* creep_details = (ACI209ConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(0.59525981535025330, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(40555186.953998156, creep_details->fci);
			Assert::AreEqual(0.80099999999999993, creep_details->humidity_factor);
			Assert::AreEqual(1.0, creep_details->loading_age_factor);
			Assert::AreEqual(0.27204923656013341, creep_details->time_factor);
			Assert::AreEqual(0.78047409599006601, creep_details->vs_factor);

			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(0.59525981535025330, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(0.91775402914691406, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(1.1496757127213619, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(1.4146989580422951, concrete.GetCreepCoefficient(128, 1));
		}
	};
}
