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

         auto roots = solver.Solve();
         Assert::AreEqual((size_t)0, roots.size());

         solver.SetA(1.0);
         solver.SetB(9.0);
         solver.SetC(-2.0);
         roots = solver.Solve();
         Assert::AreEqual((size_t)2, roots.size());
         Assert::IsTrue(IsEqual(roots[0], -9.21699056605));
         Assert::IsTrue(IsEqual(roots[1], 0.21699056605));

         solver.SetA(1.0);
         solver.SetB(0);
         solver.SetC(-25);
         roots = solver.Solve();
         Assert::AreEqual((size_t)2, roots.size());
         Assert::IsTrue(IsEqual(roots[0], -5.0));
         Assert::IsTrue(IsEqual(roots[1], 5.0));

         solver.SetA(0);
         solver.SetB(10);
         solver.SetC(-25);
         roots = solver.Solve();
         Assert::AreEqual((size_t)1, roots.size());
         Assert::IsTrue(IsEqual(roots[0], 2.5));
      }
	};
}
