#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestQuadraticSolver)
	{
	public:
		
		TEST_METHOD(Test)
		{
         QuadraticSolver solver(10, 10, 10);

         auto [r1, r2] = solver.Solve();
         Assert::IsFalse(r1.has_value());
         Assert::IsFalse(r2.has_value());

         solver.SetA(1.0);
         solver.SetB(9.0);
         solver.SetC(-2.0);
         std::tie(r1, r2) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsTrue(IsEqual(r1.value(), 0.21699056605));
         Assert::IsTrue(IsEqual(r2.value(), -9.21699056605));

         solver.SetA(1.0);
         solver.SetB(0);
         solver.SetC(-25);
         std::tie(r1, r2) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsTrue(IsEqual(r1.value(), 5.0));
         Assert::IsTrue(IsEqual(r2.value(), -5.0));

         solver.SetA(0);
         solver.SetB(10);
         solver.SetC(-25);
         std::tie(r1, r2) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsFalse(r2.has_value());
         Assert::IsTrue(IsEqual(r1.value(), 2.5));
      }
	};
}
