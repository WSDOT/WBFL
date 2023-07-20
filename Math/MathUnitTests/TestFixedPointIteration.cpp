#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestFixedPointIteration)
	{
	public:
		
		TEST_METHOD(Test)
		{
			FixedPointIteration fpi;
			auto x = fpi.Solve(std::function<Float64(Float64)>([](Float64 x) { return cos(x); }), -1.0, 0.0001);
			Assert::AreEqual(0.739085133, x, 0.0001);

			x = fpi.Solve(std::function<Float64(Float64)>([](Float64 x) { return cos(x); }), 2.0, 0.0001);
			Assert::AreEqual(0.739085133, x, 0.0001);

			Assert::ExpectException< XFixedPointIteration>([&]() {fpi.Solve(std::function<Float64(Float64)>([](Float64 x) { return sin(x); }), -1.0, 0.0001); });

			x = fpi.Solve(std::function<Float64(Float64)>([](Float64 x) { return sin(x); }), -0.5, 0.0001,10000);
			Assert::AreEqual(-0.084299405363274821, x, 0.0001);

			x = fpi.Solve(std::function<Float64(Float64)>([](Float64 x) { return sin(x); }), 2.0, 0.0001, 10000);
			Assert::AreEqual(0.084299405363274821, x, 0.0001);
		}
	};
}
