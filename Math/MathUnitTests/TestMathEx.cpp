#include "pch.h"
#include "CppUnitTest.h"
#include <MathEx.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestMathEx)
	{
	public:
		
		TEST_METHOD(TestIsEqual)
		{
         // Zeroness checks
         double a;
         double b;

         a = 1.00001;
         b = 1.00002;
         Assert::IsTrue(IsEqual(a, b));

         a = 1.0000001;
         b = 1.0000002;
         Assert::IsTrue(IsEqual(a, b));

         a = 1.000001e20;
         b = 1.000002e20;
         Assert::IsFalse(IsEqual(a, b));

         a = 1.1e20;
         b = 1.2e20;
         Assert::IsFalse(IsEqual(a, b));

         a = 12.3456789;
         b = 12.3456789;
         Assert::IsTrue(IsEqual(a, b));

         a = 12.3456798;
         b = 12.3456789;
         Assert::IsTrue(IsEqual(a, b));

         a = 0.;
         b = 1.;
         Assert::IsFalse(IsEqual(a, b));

         a = 1.;
         b = 0.;
         Assert::IsFalse(IsEqual(a, b));

         a = 0.;
         b = 0.;
         Assert::IsTrue(IsEqual(a, b));

         a = 1e-20;
         b = 1e-10;
         Assert::IsTrue(IsEqual(a, b));
      }
	};
}
