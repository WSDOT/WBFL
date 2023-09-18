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
         auto [r1, r2, r3] = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsTrue(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), -6.0));
         Assert::IsTrue(IsEqual(r2.value(), -2.0));
         Assert::IsTrue(IsEqual(r3.value(), 2.0));

         // one real root (two complex)
         solver.SetA(1.0);
         solver.SetB(-11);
         solver.SetC(49);
         solver.SetD(-75);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsFalse(r2.has_value());
         Assert::IsFalse(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), 3.0));

         // 3 real roots
         solver.SetA(2.0);
         solver.SetB(-4);
         solver.SetC(-22);
         solver.SetD(24);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsTrue(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), -3.0));
         Assert::IsTrue(IsEqual(r2.value(), 1.0));
         Assert::IsTrue(IsEqual(r3.value(), 4.0));

         // one real root (two complex)
         solver.SetA(3.0);
         solver.SetB(-10);
         solver.SetC(14);
         solver.SetD(27);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsFalse(r2.has_value());
         Assert::IsFalse(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), -1.0));

         // 3 real, with all roots equal
         solver.SetA(1.0);
         solver.SetB(6);
         solver.SetC(12);
         solver.SetD(8);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsFalse(r2.has_value());
         Assert::IsFalse(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), -2.0));


         // 3 real, with 2 equal roots
         solver.SetA(1.0);
         solver.SetB(-12);
         solver.SetC(45);
         solver.SetD(-50);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsFalse(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), 2.0));
         Assert::IsTrue(IsEqual(r2.value(), 5.0));


         // 3 real, with 2 equal roots
         solver.SetA(1.0);
         solver.SetB(-9);
         solver.SetC(24);
         solver.SetD(-20);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsFalse(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), 2.0));
         Assert::IsTrue(IsEqual(r2.value(), 5.0));

         // 3 real roots, one root is 0
         solver.SetA(1);
         solver.SetB(3);
         solver.SetC(-28);
         solver.SetD(0);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsTrue(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), -7.0));
         Assert::IsTrue(IsEqual(r2.value(), 0.0));
         Assert::IsTrue(IsEqual(r3.value(), 4.0));

         // this is actually a quadratic with 2 roots
         solver.SetA(0);
         solver.SetB(1);
         solver.SetC(3);
         solver.SetD(-28);
         std::tie(r1, r2, r3) = solver.Solve();
         Assert::IsTrue(r1.has_value());
         Assert::IsTrue(r2.has_value());
         Assert::IsFalse(r3.has_value());
         Assert::IsTrue(IsEqual(r1.value(), -7.0));
         Assert::IsTrue(IsEqual(r2.value(), 4.0));
      }
	};
}
