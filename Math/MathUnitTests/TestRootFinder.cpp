#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestRootFinder)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// RootFinder is an abstract class. Use BisectionRootFinder as an implementation
			BisectionRootFinder rf;
			Float64 x1 = rf.FindRoot([](Float64 x) {return sin(x); }, 3*PI_OVER_2 + 0.1, 0.001);
			Assert::IsTrue(IsEqual(x1, TWO_PI, 0.001));

			Float64 x2 = rf.FindRootConstrainedMin([](Float64 x) {return sin(x); }, PI_OVER_2 + 0.1, 0.0, 0.001);
			Assert::IsTrue(IsEqual(x2, M_PI, 0.001));

			Float64 x3 = rf.FindRootConstrainedMax([](Float64 x) {return sin(x); }, PI_OVER_2 + 0.1, M_PI, 0.001);
			Assert::IsTrue(IsEqual(x3, M_PI, 0.001));
		}
	};
}
