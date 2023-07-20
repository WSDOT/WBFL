#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Materials;

namespace MaterialsUnitTest
{
	TEST_CLASS(TestUnconfinedConcreteModel)
	{
	public:
		
		TEST_METHOD(Test)
		{
			UnconfinedConcreteModel model;

			model.SetFc(89631844.81);
			Assert::IsTrue(IsEqual(model.GetFc(), 89631844.810000));

			Assert::IsTrue(model.ComputeStress(0.00764) == std::make_pair(0.00, true));
			Assert::IsTrue(model.ComputeStress(-0.00764) == std::make_pair(-78333650.161053866, false)); // false: strain is not within strain limits
			Assert::IsTrue(model.ComputeStress(-0.00245) == std::make_pair(-86277115.080388337, true)); // true: strain is within strain limits
		}
	};
}
