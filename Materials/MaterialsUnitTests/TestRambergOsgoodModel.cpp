#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestRambergOsgoodModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
			RambergOsgoodModel model;
			model.SetModelParameters(800./28500, 115, 6.5, 28500, 270, 0.0, 0.045);

			Assert::AreEqual(0.0085263157894736839, model.GetYieldStrain());
			Assert::AreEqual(-0.003, model.GetStrainAtPeakStress());
			Assert::IsTrue(std::make_pair(236.63917517435993, true) == model.ComputeStress(0.01));
			Assert::IsTrue(std::make_pair(256.70492961809856, true) == model.ComputeStress(0.02));
			Assert::IsTrue(std::make_pair(264.85773576972576, true) == model.ComputeStress(0.03));
			Assert::IsTrue(std::make_pair(270.0, true) == model.ComputeStress(0.04));
			Assert::IsTrue(std::make_pair(270.0, false) == model.ComputeStress(0.05));
			Assert::IsTrue(std::make_pair(270.0, false) == model.ComputeStress(0.06));
		}
	};
}
