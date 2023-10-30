#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestCEBFIPConcrete)
	{
	public:
		
		TEST_METHOD(ModelParameters)
		{
			Float64 S, BetaSC;
			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::RS, &S, &BetaSC);
			Assert::AreEqual(0.2, S);
			Assert::AreEqual(8.0, BetaSC);

			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::N, &S, &BetaSC);
			Assert::AreEqual(0.25, S);
			Assert::AreEqual(5.0, BetaSC);

			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::R, &S, &BetaSC);
			Assert::AreEqual(0.25, S);
			Assert::AreEqual(5.0, BetaSC);

			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::SL, &S, &BetaSC);
			Assert::AreEqual(0.38, S);
			Assert::AreEqual(4.0, BetaSC);
		}

		TEST_METHOD(TypeRS)
		{
			CEBFIPConcrete concrete;
			Float64 S, BetaSC;
			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::RS, &S, &BetaSC);
			concrete.SetCureTime(3.0);
			concrete.SetS(S);
			concrete.SetBetaSc(BetaSC);
			concrete.SetFc28(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			concrete.SetStrengthDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetWeightDensity(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetRelativeHumidity(70);
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5, WBFL::Units::Measure::Inch));

			Assert::AreEqual(0.657, concrete.GetBetaSRH(), 0.001);
			Assert::AreEqual(-1.01835, concrete.GetBetaRH());
			Assert::AreEqual(0.00060420970827320005, concrete.GetEpsilonS());
			Assert::AreEqual(-0.00061529695642001327, concrete.GetNotionalShrinkageCoefficient());
			Assert::AreEqual(1.5383352739222556, concrete.GetPhiRH());
			Assert::AreEqual(2.8545087328087151, concrete.GetBetaFcm());
			Assert::AreEqual(528.26245790960991, concrete.GetBetaH());

			Assert::AreEqual(14612812.293290008, concrete.GetFc(1));
			Assert::AreEqual(30130417.571355715, concrete.GetFc(10));
			Assert::AreEqual(34473786.465850003, concrete.GetFc(28));
			Assert::AreEqual(36553533.832728043, concrete.GetFc(56));
			Assert::AreEqual(38346290.206840545, concrete.GetFc(128));

			Assert::AreEqual(19243196859.179970, concrete.GetEc(1));
			Assert::AreEqual(27632036580.891792, concrete.GetEc(10));
			Assert::AreEqual(29556623095.625591, concrete.GetEc(28));
			Assert::AreEqual(30435119016.465759, concrete.GetEc(56));
			Assert::AreEqual(31172526102.201046, concrete.GetEc(128));

			Assert::AreEqual(2332508.7102036332, concrete.GetShearFr(1));
			Assert::AreEqual(3349337.7673808238, concrete.GetShearFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetShearFr(28));
			Assert::AreEqual(3689105.3353291834, concrete.GetShearFr(56));
			Assert::AreEqual(3778488.0123880059, concrete.GetShearFr(128));

			Assert::AreEqual(2332508.7102036332, concrete.GetFlexureFr(1));
			Assert::AreEqual(3349337.7673808238, concrete.GetFlexureFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetFlexureFr(28));
			Assert::AreEqual(3689105.3353291834, concrete.GetFlexureFr(56));
			Assert::AreEqual(3778488.0123880059, concrete.GetFlexureFr(128));

			Assert::AreEqual(-0.00017468544341413302, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			CEBFIPConcreteShrinkageDetails* shrinkage_details = (CEBFIPConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(-0.00017468544341413302, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Steam);
			Assert::AreEqual(0.1778, shrinkage_details->h, 0.0001);
			Assert::AreEqual(8.0, shrinkage_details->BetaSC);
			Assert::AreEqual(0.657, shrinkage_details->BetaSRH);
			Assert::AreEqual(-1.01835, shrinkage_details->BetaRH);
			Assert::AreEqual(0.28390428652614602, shrinkage_details->BetaS);
			Assert::AreEqual(0.00060420970827320005, shrinkage_details->es);
			Assert::AreEqual(-0.00061529695642001327, shrinkage_details->ecso);

			Assert::AreEqual(0.0000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(-4.8786374367031180e-05, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(-9.1461264818548923e-05, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(-0.00013155180203746269, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(-0.00019603403881616378, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			CEBFIPConcreteCreepDetails* creep_details = (CEBFIPConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(1.1705945391195118, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(14612812.293290008, creep_details->fci);
			Assert::AreEqual(3.9919922485443324, creep_details->Yo);
			Assert::AreEqual(0.29323567437946940, creep_details->Bc);
			Assert::AreEqual(1.5383352739222556, creep_details->Yrh);
			Assert::AreEqual(2.8545087328087151, creep_details->Bfc);
			Assert::AreEqual(0.90909090909090906, creep_details->Bt);
			Assert::AreEqual(528.26245790960991, creep_details->Bh);
			Assert::AreEqual(0.1778, creep_details->h, 0.0001);

			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(1.6115705602628954, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(1.9657998114343658, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(2.4400921043933184, concrete.GetCreepCoefficient(128, 1));
		}

		TEST_METHOD(TypeN)
		{
			CEBFIPConcrete concrete;
			Float64 S, BetaSC;
			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::N, &S, &BetaSC);
			concrete.SetCureTime(3.0);
			concrete.SetS(S);
			concrete.SetBetaSc(BetaSC);
			concrete.SetFc28(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			concrete.SetStrengthDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetWeightDensity(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetRelativeHumidity(70);
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5, WBFL::Units::Measure::Inch));

			Assert::AreEqual(0.657, concrete.GetBetaSRH(), 0.001);
			Assert::AreEqual(-1.01835, concrete.GetBetaRH());
			Assert::AreEqual(0.00043763106767074998, concrete.GetEpsilonS());
			Assert::AreEqual(-0.00044566159776250830, concrete.GetNotionalShrinkageCoefficient());
			Assert::AreEqual(1.5383352739222556, concrete.GetPhiRH());
			Assert::AreEqual(2.8545087328087151, concrete.GetBetaFcm());
			Assert::AreEqual(528.26245790960991, concrete.GetBetaH());

			//std::vector<Float64> values{concrete.GetFc(1), concrete.GetFc(10), concrete.GetFc(28), concrete.GetFc(56), concrete.GetFc(128)};
			Assert::AreEqual(11790847.172209740, concrete.GetFc(1));
			Assert::AreEqual(29132931.744432811, concrete.GetFc(10));
			Assert::AreEqual(34473786.465850003, concrete.GetFc(28));
			Assert::AreEqual(37092786.893418908, concrete.GetFc(56));
			Assert::AreEqual(39380565.347343385, concrete.GetFc(128));

			//std::vector<Float64> values{concrete.GetEc(1), concrete.GetEc(10), concrete.GetEc(28), concrete.GetEc(56), concrete.GetEc(128)};
			Assert::AreEqual(17285534969.180264, concrete.GetEc(1));
			Assert::AreEqual(27170799366.695103, concrete.GetEc(10));
			Assert::AreEqual(29556623095.625591, concrete.GetEc(28));
			Assert::AreEqual(30658792923.557114, concrete.GetEc(56));
			Assert::AreEqual(31590121277.011513, concrete.GetEc(128));

			//std::vector<Float64> values{concrete.GetShearFr(1), concrete.GetShearFr(10), concrete.GetShearFr(28), concrete.GetShearFr(56), concrete.GetShearFr(128)};
			Assert::AreEqual(2095216.3599006387, concrete.GetShearFr(1));
			Assert::AreEqual(3293430.2262660740, concrete.GetShearFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetShearFr(28));
			Assert::AreEqual(3716217.3240675298, concrete.GetShearFr(56));
			Assert::AreEqual(3829105.6093347291, concrete.GetShearFr(128));

			//std::vector<Float64> values{concrete.GetFlexureFr(1), concrete.GetFlexureFr(10), concrete.GetFlexureFr(28), concrete.GetFlexureFr(56), concrete.GetFlexureFr(128)};
			Assert::AreEqual(2095216.3599006387, concrete.GetFlexureFr(1));
			Assert::AreEqual(3293430.2262660740, concrete.GetFlexureFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetFlexureFr(28));
			Assert::AreEqual(3716217.3240675298, concrete.GetFlexureFr(56));
			Assert::AreEqual(3829105.6093347291, concrete.GetFlexureFr(128));

			Assert::AreEqual(-0.00012652523794486720, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			CEBFIPConcreteShrinkageDetails* shrinkage_details = (CEBFIPConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(-0.00012652523794486720, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Steam);
			Assert::AreEqual(0.1778, shrinkage_details->h, 0.0001);
			Assert::AreEqual(5.0, shrinkage_details->BetaSC);
			Assert::AreEqual(0.657, shrinkage_details->BetaSRH);
			Assert::AreEqual(-1.01835, shrinkage_details->BetaRH);
			Assert::AreEqual(0.28390428652614602, shrinkage_details->BetaS);
			Assert::AreEqual(0.00043763106767074998, shrinkage_details->es);
			Assert::AreEqual(-0.00044566159776250830, shrinkage_details->ecso);

			//std::vector<Float64> values{concrete.GetFreeShrinkageStrain(1), concrete.GetFreeShrinkageStrain(10), concrete.GetFreeShrinkageStrain(28), concrete.GetFreeShrinkageStrain(56), concrete.GetFreeShrinkageStrain(128)};
			Assert::AreEqual(0.0000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(-3.5336130501853730e-05, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(-6.6245693217098132e-05, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(-9.5283400434265311e-05, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(-0.00014198809541162794, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			CEBFIPConcreteCreepDetails* creep_details = (CEBFIPConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(1.1705945391195118, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(11790847.172209740, creep_details->fci);
			Assert::AreEqual(3.9919922485443324, creep_details->Yo);
			Assert::AreEqual(0.29323567437946940, creep_details->Bc);
			Assert::AreEqual(1.5383352739222556, creep_details->Yrh);
			Assert::AreEqual(2.8545087328087151, creep_details->Bfc);
			Assert::AreEqual(0.90909090909090906, creep_details->Bt);
			Assert::AreEqual(528.26245790960991, creep_details->Bh);
			Assert::AreEqual(0.1778, creep_details->h, 0.0001);

			std::vector<Float64> value{concrete.GetCreepCoefficient(1, 1), concrete.GetCreepCoefficient(10, 1), concrete.GetCreepCoefficient(28, 1), concrete.GetCreepCoefficient(56, 1), concrete.GetCreepCoefficient(128, 1)};
			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(1.6115705602628954, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(1.9657998114343658, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(2.4400921043933184, concrete.GetCreepCoefficient(128, 1));
		}

		TEST_METHOD(TypeR)
		{
			CEBFIPConcrete concrete;
			Float64 S, BetaSC;
			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::R, &S, &BetaSC);
			concrete.SetCureTime(3.0);
			concrete.SetS(S);
			concrete.SetBetaSc(BetaSC);
			concrete.SetFc28(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			concrete.SetStrengthDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetWeightDensity(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetRelativeHumidity(70);
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5, WBFL::Units::Measure::Inch));

			Assert::AreEqual(0.657, concrete.GetBetaSRH(), 0.001);
			Assert::AreEqual(-1.01835, concrete.GetBetaRH());
			Assert::AreEqual(0.00043763106767074998, concrete.GetEpsilonS());
			Assert::AreEqual(-0.00044566159776250830, concrete.GetNotionalShrinkageCoefficient());
			Assert::AreEqual(1.5383352739222556, concrete.GetPhiRH());
			Assert::AreEqual(2.8545087328087151, concrete.GetBetaFcm());
			Assert::AreEqual(528.26245790960991, concrete.GetBetaH());

			//std::vector<Float64> values{concrete.GetFc(1), concrete.GetFc(10), concrete.GetFc(28), concrete.GetFc(56), concrete.GetFc(128)};
			Assert::AreEqual(11790847.172209740, concrete.GetFc(1));
			Assert::AreEqual(29132931.744432811, concrete.GetFc(10));
			Assert::AreEqual(34473786.465850003, concrete.GetFc(28));
			Assert::AreEqual(37092786.893418908, concrete.GetFc(56));
			Assert::AreEqual(39380565.347343385, concrete.GetFc(128));

			//std::vector<Float64> values{concrete.GetEc(1), concrete.GetEc(10), concrete.GetEc(28), concrete.GetEc(56), concrete.GetEc(128)};
			Assert::AreEqual(17285534969.180264, concrete.GetEc(1));
			Assert::AreEqual(27170799366.695103, concrete.GetEc(10));
			Assert::AreEqual(29556623095.625591, concrete.GetEc(28));
			Assert::AreEqual(30658792923.557114, concrete.GetEc(56));
			Assert::AreEqual(31590121277.011513, concrete.GetEc(128));

			//std::vector<Float64> values{concrete.GetShearFr(1), concrete.GetShearFr(10), concrete.GetShearFr(28), concrete.GetShearFr(56), concrete.GetShearFr(128)};
			Assert::AreEqual(2095216.3599006387, concrete.GetShearFr(1));
			Assert::AreEqual(3293430.2262660740, concrete.GetShearFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetShearFr(28));
			Assert::AreEqual(3716217.3240675298, concrete.GetShearFr(56));
			Assert::AreEqual(3829105.6093347291, concrete.GetShearFr(128));

			//std::vector<Float64> values{concrete.GetFlexureFr(1), concrete.GetFlexureFr(10), concrete.GetFlexureFr(28), concrete.GetFlexureFr(56), concrete.GetFlexureFr(128)};
			Assert::AreEqual(2095216.3599006387, concrete.GetFlexureFr(1));
			Assert::AreEqual(3293430.2262660740, concrete.GetFlexureFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetFlexureFr(28));
			Assert::AreEqual(3716217.3240675298, concrete.GetFlexureFr(56));
			Assert::AreEqual(3829105.6093347291, concrete.GetFlexureFr(128));

			Assert::AreEqual(-0.00012652523794486720, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			CEBFIPConcreteShrinkageDetails* shrinkage_details = (CEBFIPConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(-0.00012652523794486720, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Steam);
			Assert::AreEqual(0.1778, shrinkage_details->h, 0.0001);
			Assert::AreEqual(5.0, shrinkage_details->BetaSC);
			Assert::AreEqual(0.657, shrinkage_details->BetaSRH);
			Assert::AreEqual(-1.01835, shrinkage_details->BetaRH);
			Assert::AreEqual(0.28390428652614602, shrinkage_details->BetaS);
			Assert::AreEqual(0.00043763106767074998, shrinkage_details->es);
			Assert::AreEqual(-0.00044566159776250830, shrinkage_details->ecso);

			//std::vector<Float64> values{concrete.GetFreeShrinkageStrain(1), concrete.GetFreeShrinkageStrain(10), concrete.GetFreeShrinkageStrain(28), concrete.GetFreeShrinkageStrain(56), concrete.GetFreeShrinkageStrain(128)};
			Assert::AreEqual(0.0000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(-3.5336130501853730e-05, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(-6.6245693217098132e-05, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(-9.5283400434265311e-05, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(-0.00014198809541162794, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			CEBFIPConcreteCreepDetails* creep_details = (CEBFIPConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(1.1705945391195118, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(11790847.172209740, creep_details->fci);
			Assert::AreEqual(3.9919922485443324, creep_details->Yo);
			Assert::AreEqual(0.29323567437946940, creep_details->Bc);
			Assert::AreEqual(1.5383352739222556, creep_details->Yrh);
			Assert::AreEqual(2.8545087328087151, creep_details->Bfc);
			Assert::AreEqual(0.90909090909090906, creep_details->Bt);
			Assert::AreEqual(528.26245790960991, creep_details->Bh);
			Assert::AreEqual(0.1778, creep_details->h, 0.0001);

			//std::vector<Float64> value{concrete.GetCreepCoefficient(1, 1), concrete.GetCreepCoefficient(10, 1), concrete.GetCreepCoefficient(28, 1), concrete.GetCreepCoefficient(56, 1), concrete.GetCreepCoefficient(128, 1)};
			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(1.6115705602628954, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(1.9657998114343658, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(2.4400921043933184, concrete.GetCreepCoefficient(128, 1));
		}

		TEST_METHOD(TypeSL)
		{
			CEBFIPConcrete concrete;
			Float64 S, BetaSC;
			CEBFIPConcrete::GetModelParameters(CEBFIPConcrete::CementType::SL, &S, &BetaSC);
			concrete.SetCureTime(3.0);
			concrete.SetS(S);
			concrete.SetBetaSc(BetaSC);
			concrete.SetFc28(WBFL::Units::ConvertToSysUnits(5.0, WBFL::Units::Measure::KSI));
			concrete.SetStrengthDensity(WBFL::Units::ConvertToSysUnits(0.150, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetWeightDensity(WBFL::Units::ConvertToSysUnits(0.155, WBFL::Units::Measure::KipPerFeet3));
			concrete.SetRelativeHumidity(70);
			concrete.SetVSRatio(WBFL::Units::ConvertToSysUnits(3.5, WBFL::Units::Measure::Inch));

			Assert::AreEqual(0.657, concrete.GetBetaSRH(), 0.001);
			Assert::AreEqual(-1.01835, concrete.GetBetaRH());
			Assert::AreEqual(0.00038210485413660002, concrete.GetEpsilonS());
			Assert::AreEqual(-0.00038911647821000665, concrete.GetNotionalShrinkageCoefficient());
			Assert::AreEqual(1.5383352739222556, concrete.GetPhiRH());
			Assert::AreEqual(2.8545087328087151, concrete.GetBetaFcm());
			Assert::AreEqual(528.26245790960991, concrete.GetBetaH());

			//std::vector<Float64> values{concrete.GetFc(1), concrete.GetFc(10), concrete.GetFc(28), concrete.GetFc(56), concrete.GetFc(128)};
			Assert::AreEqual(6749228.6632264648, concrete.GetFc(1));
			Assert::AreEqual(26691298.208270967, concrete.GetFc(10));
			Assert::AreEqual(34473786.465850003, concrete.GetFc(28));
			Assert::AreEqual(38532369.173127100, concrete.GetFc(56));
			Assert::AreEqual(42202121.689378560, concrete.GetFc(128));

			//std::vector<Float64> values{concrete.GetEc(1), concrete.GetEc(10), concrete.GetEc(28), concrete.GetEc(56), concrete.GetEc(128)};
			Assert::AreEqual(13077881294.492981, concrete.GetEc(1));
			Assert::AreEqual(26007294087.061207, concrete.GetEc(10));
			Assert::AreEqual(29556623095.625591, concrete.GetEc(28));
			Assert::AreEqual(31248068371.017994, concrete.GetEc(56));
			Assert::AreEqual(32702237074.718178, concrete.GetEc(128));

			//std::vector<Float64> values{concrete.GetShearFr(1), concrete.GetShearFr(10), concrete.GetShearFr(28), concrete.GetShearFr(56), concrete.GetShearFr(128)};
			Assert::AreEqual(1585197.7326658161, concrete.GetShearFr(1));
			Assert::AreEqual(3152399.2832801472, concrete.GetShearFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetShearFr(28));
			Assert::AreEqual(3787644.6510324841, concrete.GetShearFr(56));
			Assert::AreEqual(3963907.5242082644, concrete.GetShearFr(128));

			//std::vector<Float64> values{concrete.GetFlexureFr(1), concrete.GetFlexureFr(10), concrete.GetFlexureFr(28), concrete.GetFlexureFr(56), concrete.GetFlexureFr(128)};
			Assert::AreEqual(1585197.7326658161, concrete.GetFlexureFr(1));
			Assert::AreEqual(3152399.2832801472, concrete.GetFlexureFr(10));
			Assert::AreEqual(3582620.9812879506, concrete.GetFlexureFr(28));
			Assert::AreEqual(3787644.6510324841, concrete.GetFlexureFr(56));
			Assert::AreEqual(3963907.5242082644, concrete.GetFlexureFr(128));

			Assert::AreEqual(-0.00011047183612177858, concrete.GetFreeShrinkageStrain(100));
			auto shrinkage = concrete.GetFreeShrinkageStrainDetails(100);
			CEBFIPConcreteShrinkageDetails* shrinkage_details = (CEBFIPConcreteShrinkageDetails*)(shrinkage.get());
			Assert::AreEqual(-0.00011047183612177858, shrinkage_details->esh);
			Assert::AreEqual(97., shrinkage_details->shrinkage_duration);
			Assert::IsTrue(shrinkage_details->curingType == CuringType::Steam);
			Assert::AreEqual(0.1778, shrinkage_details->h, 0.0001);
			Assert::AreEqual(4.0, shrinkage_details->BetaSC);
			Assert::AreEqual(0.657, shrinkage_details->BetaSRH);
			Assert::AreEqual(-1.01835, shrinkage_details->BetaRH);
			Assert::AreEqual(0.28390428652614602, shrinkage_details->BetaS);
			Assert::AreEqual(0.00038210485413660002, shrinkage_details->es);
			Assert::AreEqual(-0.00038911647821000665, shrinkage_details->ecso);

			//std::vector<Float64> values{concrete.GetFreeShrinkageStrain(1), concrete.GetFreeShrinkageStrain(10), concrete.GetFreeShrinkageStrain(28), concrete.GetFreeShrinkageStrain(56), concrete.GetFreeShrinkageStrain(128)};
			Assert::AreEqual(0.0000000000000000, concrete.GetFreeShrinkageStrain(1));
			Assert::AreEqual(-3.0852715880127912e-05, concrete.GetFreeShrinkageStrain(10));
			Assert::AreEqual(-5.7840502683281206e-05, concrete.GetFreeShrinkageStrain(28));
			Assert::AreEqual(-8.3193933233199514e-05, concrete.GetFreeShrinkageStrain(56));
			Assert::AreEqual(-0.00012397278094344934, concrete.GetFreeShrinkageStrain(128));

			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			auto creep = concrete.GetCreepCoefficientDetails(10, 1);
			CEBFIPConcreteCreepDetails* creep_details = (CEBFIPConcreteCreepDetails*)(creep.get());
			Assert::AreEqual(1.1705945391195118, creep_details->Ct);
			Assert::AreEqual(10.0, creep_details->age);
			Assert::AreEqual(1.0, creep_details->age_at_loading);
			Assert::AreEqual(6749228.6632264648, creep_details->fci);
			Assert::AreEqual(3.9919922485443324, creep_details->Yo);
			Assert::AreEqual(0.29323567437946940, creep_details->Bc);
			Assert::AreEqual(1.5383352739222556, creep_details->Yrh);
			Assert::AreEqual(2.8545087328087151, creep_details->Bfc);
			Assert::AreEqual(0.90909090909090906, creep_details->Bt);
			Assert::AreEqual(528.26245790960991, creep_details->Bh);
			Assert::AreEqual(0.1778, creep_details->h, 0.0001);

			std::vector<Float64> value{concrete.GetCreepCoefficient(1, 1), concrete.GetCreepCoefficient(10, 1), concrete.GetCreepCoefficient(28, 1), concrete.GetCreepCoefficient(56, 1), concrete.GetCreepCoefficient(128, 1)};
			Assert::AreEqual(0.0000000000000000, concrete.GetCreepCoefficient(1, 1));
			Assert::AreEqual(1.1705945391195118, concrete.GetCreepCoefficient(10, 1));
			Assert::AreEqual(1.6115705602628954, concrete.GetCreepCoefficient(28, 1));
			Assert::AreEqual(1.9657998114343658, concrete.GetCreepCoefficient(56, 1));
			Assert::AreEqual(2.4400921043933184, concrete.GetCreepCoefficient(128, 1));
		}
	};
}
