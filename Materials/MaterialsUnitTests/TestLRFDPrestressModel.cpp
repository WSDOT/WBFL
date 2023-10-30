#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestLRFDPrestressModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
			LRFDPrestressModel model;
			Assert::AreEqual(1861584469.1559000, model.GetFpu());
			Assert::AreEqual(196500582855.34500, model.GetEps());
			Assert::IsTrue(StrandType::LowRelaxation == model.GetStrandType());
			Float64 minStrain, maxStrain;
			model.GetStrainLimits(&minStrain,&maxStrain);
			Assert::AreEqual(-10.0, minStrain);
			Assert::AreEqual(0.035, maxStrain);
			Assert::AreEqual(0.9 * 270.0/28500.0, model.GetYieldStrain());
			Assert::AreEqual(196500582855.34500, model.GetModulusOfElasticity());
			Assert::IsTrue(std::make_pair(1470651730.6331611, true) == model.ComputeStress(0.001));
			Assert::IsTrue(std::make_pair(1820433654.5745590, true) == model.ComputeStress(0.035));
			Assert::IsTrue(std::make_pair(1638194332.8571920, true) == model.ComputeStress(0.004));
			Assert::IsTrue(std::make_pair(-1470651730.6331611, true) == model.ComputeStress(-0.001));
			Assert::IsTrue(std::make_pair(-1861428142.9583502, true) == model.ComputeStress(-10.0));
			Assert::IsTrue(std::make_pair(-1861506294.3344188, true) == model.ComputeStress(-20.0));
			Assert::AreEqual(maxStrain, model.GetStrainAtPeakStress());
		}
	};
}
