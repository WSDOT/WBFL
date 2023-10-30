#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestLinearFunction)
	{
	public:
		
		TEST_METHOD(Test)
		{
			LinearFunction fn(0.5, 10.0);
			Assert::AreEqual(0.5, fn.GetSlope());
			Assert::AreEqual(10.0, fn.GetYIntercept());
			Assert::AreEqual(10.0, fn.Evaluate(0.0));
			Assert::AreEqual(15.0, fn.Evaluate(10));
		}
	};
}
