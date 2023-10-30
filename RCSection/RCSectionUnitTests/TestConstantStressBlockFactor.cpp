#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestConstantStressBlockFactor)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ConstantStressBlockFactor factor;
			Assert::IsTrue(IsEqual(factor.GetIntensityFactor(), 0.85));
			Assert::IsTrue(IsEqual(factor.GetDepthFactor(), 0.85));

			ConstantStressBlockFactor factor1(0.90, 0.65);
			Assert::IsTrue(IsEqual(factor1.GetIntensityFactor(), 0.90));
			Assert::IsTrue(IsEqual(factor1.GetDepthFactor(), 0.65));
		}
	};
}
