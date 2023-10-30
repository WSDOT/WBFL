#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestConfinedConcreteModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
			WBFL::Units::AutoSystem au;
			WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

			ConfinedConcreteModel model;
			auto section = std::make_shared<CircularManderSection>();
			section->SetAs(1.56*28);
			section->SetAsp(0.44);
			section->SetCover(1.5);
			section->SetDiameter(72);
			section->SetS(3);
			section->SetTransvReinforcementRuptureStrian(0.06);
			section->SetTransvReinforcemenType(TransvReinforcementType::Spiral);
			section->SetTransvYieldStrength(60);
			section->Set_db(0.75);
			model.SetSection(section);
			model.SetR(5);
			model.Set_eco(0.003);
			model.Set_fco(5);

			auto [fr, fcc, ecc] = model.ComputeConcreteProperties();
			Assert::AreEqual(0.25668951715790977, fr);
			Assert::AreEqual(6.5877194021790491, fcc);
			Assert::AreEqual(0.0077631582065371459, ecc);
			Assert::AreEqual(-1.1785113019723510, model.GetYieldStrain());
			Assert::AreEqual(4.2426406871381079, model.GetModulusOfElasticity());
			Assert::IsTrue(std::make_pair(0.0, true) == model.ComputeStress(0.001));
			Assert::IsTrue(std::make_pair(0.80057123837402666, true) == model.ComputeStress(-0.001));
			Assert::IsTrue(std::make_pair(-7.5826048703208722, true) == model.ComputeStress(-0.005));
			Assert::IsTrue(std::make_pair(-6.7722581146571965, true) == model.ComputeStress(-0.010));
			Assert::IsTrue(std::make_pair(-7.6791908056432732, true) == model.ComputeStress(-0.015));
			Float64 minStrain, maxStrain;
			model.GetStrainLimits(&minStrain, &maxStrain);
			Assert::AreEqual(-0.010576339136233816, minStrain);
			Assert::AreEqual(Float64_Max, maxStrain);
			Assert::AreEqual(-0.0077631582065371459, model.GetStrainAtPeakStress());
		}
	};
}
