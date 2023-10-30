#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestBisectionRootFinder)
	{
	public:
		
		TEST_METHOD(Test)
		{
			BisectionRootFinder rf;
			Float64 x1 = rf.FindRootInRange([](Float64 x) {return sin(x); }, -0.1, 0.1, 0.001);
			Assert::IsTrue(IsEqual(x1, 0.0));

			Float64 x2 = rf.FindRootInRange([](Float64 x) {return sin(x); }, M_PI - 0.1, M_PI + 0.1, 0.001);
			Assert::IsTrue(IsEqual(x2, M_PI));

			Float64 x3 = rf.FindRootInRange([](Float64 x) {return cos(x); }, PI_OVER_2 - 0.1, PI_OVER_2 + 0.1, 0.001);
			Assert::IsTrue(IsEqual(x3, PI_OVER_2));
		}
	};
}
