#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestPolynomialFunction)
	{
	public:
		
		TEST_METHOD(Polynomial)
		{
			std::vector<Float64> coefficients{10.0, -5.0, 3.0};
			PolynomialFunction pf(coefficients);
			Assert::AreEqual(3.0, pf.Evaluate(0.0));
			Assert::AreEqual(953.0, pf.Evaluate(10.0));
			Assert::AreEqual(1053.0, pf.Evaluate(-10.0));

			auto derivative = pf.GetDerivative();
			const auto& c = derivative.GetCoefficients();
			Assert::AreEqual((size_t)2, c.size());
			Assert::AreEqual(20.0, c.front());
			Assert::AreEqual(-5.0, c.back());
		}

		TEST_METHOD(Cubic)
		{
			std::vector<Float64> coefficients{10.0, -5.0, 3.0, 4.0};
			PolynomialFunction pf(coefficients);
			Assert::AreEqual(4.0, pf.Evaluate(0.0));
			Assert::AreEqual(9534.0, pf.Evaluate(10.0));
			Assert::AreEqual(-10526.0, pf.Evaluate(-10.0));

			auto derivative = pf.GetDerivative();
			const auto& c = derivative.GetCoefficients();
			Assert::AreEqual((size_t)3, c.size());
			Assert::AreEqual(30.0, c[0]);
			Assert::AreEqual(-10.0, c[1]);
			Assert::AreEqual(3.0, c[2]);
		}
	};
}
