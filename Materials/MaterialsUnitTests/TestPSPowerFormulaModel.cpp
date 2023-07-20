#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestPSPowerFormulaModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
         PSPowerFormulaModel model;

         auto result = model.ComputeStress(0.00764);
         Assert::IsTrue(IsEqual(result.first, 1446556950.5987, 0.0001) && result.second == true);

         result = model.ComputeStress(-0.00764);
         Assert::IsTrue(IsEqual(result.first, -1446556950.5987, 0.0001) && result.second == true);

         result = model.ComputeStress(0.1);
         Assert::IsTrue(IsEqual(result.first, 1861584469.1559, 0.0001) && result.second == false); // exceeds tension strain

         result = model.ComputeStress(-0.1);
         Assert::IsTrue(IsEqual(result.first, -1861584469.1559, 0.0001) && result.second == true); // assumes compression strain is infinite

         result = model.ComputeStress(0.035);
         Assert::IsTrue(IsEqual(result.first, 1861584469.1559, 0.0001) && result.second == true);
      }
	};
}
