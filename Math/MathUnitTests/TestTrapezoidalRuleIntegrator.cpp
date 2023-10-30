#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestTrapezoidalRuleIntegrator)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// Example from https://en.wikipedia.org/wiki/Trapezoidal_rule
			TrapezoidalRuleIntegrator integrator;
			auto area = integrator.Evaluate(std::function<Float64(Float64)>([](auto x) {return 5 * x * exp(-2 * x); }), 0.1, 1.3, 3);
			Assert::AreEqual(0.84385, area, 0.00001);

			area = integrator.Evaluate(std::function<Float64(Float64)>([](auto x) {return 5 * x * exp(-2 * x); }), 0.1, 1.3, 3000);
			Assert::AreEqual(0.89387, area, 0.00001);
		}
	};
}
