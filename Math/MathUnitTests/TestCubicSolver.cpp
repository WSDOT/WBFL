#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestCubicSolver)
	{
	public:
		
		TEST_METHOD(Test)
		{
         CubicSolver solver(1, 6, -4, -24);
         // 3 real roots
         auto roots = solver.Solve();
         Assert::AreEqual((size_t)3,roots.size());
         Assert::IsTrue(IsEqual(roots[0], -6.0));
         Assert::IsTrue(IsEqual(roots[1], -2.0));
         Assert::IsTrue(IsEqual(roots[2], 2.0));

         // one real root (two complex)
         solver.SetA(1.0);
         solver.SetB(-11);
         solver.SetC(49);
         solver.SetD(-75);
         roots = solver.Solve();
         Assert::AreEqual((size_t)1, roots.size());
         Assert::IsTrue(IsEqual(roots[0], 3.0));

         // 3 real roots
         solver.SetA(2.0);
         solver.SetB(-4);
         solver.SetC(-22);
         solver.SetD(24);
         roots = solver.Solve();
         Assert::AreEqual((size_t)3, roots.size());
         Assert::IsTrue(IsEqual(roots[0], -3.0));
         Assert::IsTrue(IsEqual(roots[1], 1.0));
         Assert::IsTrue(IsEqual(roots[2], 4.0));

         // one real root (two complex)
         solver.SetA(3.0);
         solver.SetB(-10);
         solver.SetC(14);
         solver.SetD(27);
         roots = solver.Solve();
         Assert::AreEqual((size_t)1, roots.size());
         Assert::IsTrue(IsEqual(roots[0], -1.0));

         // 3 real, with all roots equal
         solver.SetA(1.0);
         solver.SetB(6);
         solver.SetC(12);
         solver.SetD(8);
         roots = solver.Solve();
         Assert::AreEqual((size_t)1, roots.size());
         Assert::IsTrue(IsEqual(roots[0], -2.0));


         // 3 real, with 2 equal roots
         solver.SetA(1.0);
         solver.SetB(-12);
         solver.SetC(45);
         solver.SetD(-50);
         roots = solver.Solve();
         Assert::AreEqual((size_t)2, roots.size());
         Assert::IsTrue(IsEqual(roots[0], 2.0));
         Assert::IsTrue(IsEqual(roots[1], 5.0));


         // 3 real, with 2 equal roots
         solver.SetA(1.0);
         solver.SetB(-9);
         solver.SetC(24);
         solver.SetD(-20);
         roots = solver.Solve();
         Assert::AreEqual((size_t)2, roots.size());
         Assert::IsTrue(IsEqual(roots[0], 2.0));
         Assert::IsTrue(IsEqual(roots[1], 5.0));

         // 3 real roots, one root is 0
         solver.SetA(1);
         solver.SetB(3);
         solver.SetC(-28);
         solver.SetD(0);
         roots = solver.Solve();
         Assert::AreEqual((size_t)3, roots.size());
         Assert::IsTrue(IsEqual(roots[0], -7.0));
         Assert::IsTrue(IsEqual(roots[1], 0.0));
         Assert::IsTrue(IsEqual(roots[2], 4.0));

         // this is actually a quadratic with 2 roots
         solver.SetA(0);
         solver.SetB(1);
         solver.SetC(3);
         solver.SetD(-28);
         roots = solver.Solve();
         Assert::AreEqual((size_t)2, roots.size());
         Assert::IsTrue(IsEqual(roots[0], -7.0));
         Assert::IsTrue(IsEqual(roots[1], 4.0));
      }
	};
}
