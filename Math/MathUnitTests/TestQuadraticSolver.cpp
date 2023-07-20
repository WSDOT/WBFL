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
         Float64 x1, x2;

         Assert::IsTrue(solver.Solve(&x1, &x2) == 0);

         solver.SetA(1.0);
         solver.SetB(9.0);
         solver.SetC(-2.0);
         Assert::IsTrue(solver.Solve(&x1, &x2) == 2);
         Assert::IsTrue(IsEqual(x1, 0.21699056605));
         Assert::IsTrue(IsEqual(x2, -9.21699056605));

         solver.SetA(1.0);
         solver.SetB(0);
         solver.SetC(-25);
         Assert::IsTrue(solver.Solve(&x1, &x2) == 2);
         Assert::IsTrue(IsEqual(x1, 5.0));
         Assert::IsTrue(IsEqual(x2, -5.0));

         solver.SetA(0);
         solver.SetB(10);
         solver.SetC(-25);
         Assert::IsTrue(solver.Solve(&x1, &x2) == 1);
         Assert::IsTrue(IsEqual(x1, 2.5));
      }
	};
}
