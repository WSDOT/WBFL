#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestPCIUHPCModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
         WBFL::Units::AutoSystem au;
         WBFL::Units::System::SetSystemUnits(WBFL::Units::Measure::_12KSlug, WBFL::Units::Measure::Inch, WBFL::Units::Measure::Second, WBFL::Units::Measure::Fahrenheit, WBFL::Units::Measure::Degree);

         PCIUHPCModel model;
         model.SetFc(18.0);

         // compression
         auto result = model.ComputeStress(-0.0005);
         Assert::IsTrue(IsEqual(result.first, -0.85 * 18.0 / 2));
         Assert::IsTrue(result.second == true);

         result = model.ComputeStress(-0.001);
         Assert::IsTrue(IsEqual(result.first, -0.85 * 18.0));
         Assert::IsTrue(result.second == true);

         result = model.ComputeStress(-0.002);
         Assert::IsTrue(IsEqual(result.first, -0.85 * 18.0));
         Assert::IsTrue(result.second == true);

         result = model.ComputeStress(-0.003);
         Assert::IsTrue(IsEqual(result.first, -0.85 * 18.0));
         Assert::IsTrue(result.second == true);

         result = model.ComputeStress(-0.004);
         Assert::IsTrue(IsEqual(result.first, -0.85 * 18.0));
         Assert::IsTrue(result.second == true);

         // tension
         result = model.ComputeStress(0.00006);
         Assert::IsTrue(IsEqual(result.first, 0.75 / 2));
         Assert::IsTrue(result.second == true);

         result = model.ComputeStress(0.00012);
         Assert::IsTrue(IsEqual(result.first, 0.75));
         Assert::IsTrue(result.second == true);

         result = model.ComputeStress(0.005);
         Assert::IsTrue(IsEqual(result.first, 0.75));
         Assert::IsTrue(result.second == true);

         result = model.ComputeStress(0.010);
         Assert::IsTrue(IsEqual(result.first, 0.0));
         Assert::IsTrue(result.second == true);
      }
	};
}
