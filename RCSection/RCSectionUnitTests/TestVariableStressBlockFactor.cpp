#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestVariableStressBlockFactor)
	{
	public:
		
		TEST_METHOD(Test)
		{
         VariableStressBlockFactor factor;
         factor.SetFc(1);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));

         factor.SetFc(10);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));

         factor.SetFc(12.5);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.80));

         factor.SetFc(15);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.75));

         factor.SetFc(20);
         Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.75));

         Assert::IsTrue(IsEqual(factor.GetDepthFactor(), 0.85));
      }
	};
}
