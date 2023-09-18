#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestCDRatio)
	{
	public:
		
		TEST_METHOD(CDRatio)
		{
			Assert::AreEqual(5.0, CDRatio::Compute(50.0, 10.0));
			Assert::AreEqual(-5.0, CDRatio::Compute(50.0, -10.0));
			Assert::AreEqual(-5.0, CDRatio::Compute(-50.0, 10.0));
		}

		TEST_METHOD(IsCDRatioLess)
		{
			Assert::IsFalse(CDRatio::IsCDRatioLess(CDRatio::Sense::Positive, 50.0, 10.0, 25.0, 10.0));
			Assert::IsTrue(CDRatio::IsCDRatioLess(CDRatio::Sense::Positive, 50.0, 10.0, 250.0, 10.0));

			Assert::IsFalse(CDRatio::IsCDRatioLess(CDRatio::Sense::Negative, 50.0, 10.0, 25.0, 10.0));
			Assert::IsTrue(CDRatio::IsCDRatioLess(CDRatio::Sense::Negative, 50.0, 10.0, 250.0, 10.0));
		}

		TEST_METHOD(MinCDRatio)
		{
			auto [cd,idx] = CDRatio::MinCDRatio(CDRatio::Sense::Positive, 50.0, 10.0, 40.0, 10.0, 30.0, 10.0, 20.0, 10.0);
			Assert::AreEqual(2.0, cd);
			Assert::AreEqual(3, idx);
		}
	};
}
