#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestCompositeFunction)
	{
	public:
		
		TEST_METHOD(Test)
		{
			LinearFunction f1(1, 10.0);
			LinearFunction f2(-1, -10.0);
			CompositeFunction cf;
			cf.AddFunction(0, 10, f1);
			cf.AddFunction(10, 20, f2);

			Assert::AreEqual(10.0, cf.Evaluate(0));
			Assert::AreEqual(20.0, cf.Evaluate(10));
			Assert::AreEqual(-25.0, cf.Evaluate(15));

			Assert::ExpectException<XFunction>([&cf]() {cf.Evaluate(-1); });
			Assert::ExpectException<XFunction>([&cf]() {cf.Evaluate(21); });
		}
	};
}
