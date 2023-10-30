#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

#include <iostream>

namespace MathUnitTests
{
	TEST_CLASS(TestUnsymmetricBandedMatrix)
	{
	public:
		
		/// [A] = [5|2|0|0]
		///       [3|4|2|0]
		///       [0|7|6|3]
		///       [0|0|4|9]
		TEST_METHOD(ColumnStorage)
		{
			UnsymmetricBandedMatrix m(4, 3, UnsymmetricBandedMatrix::Storage::Column);
			m.SetCoefficient(0, 0, 5);
			m.SetCoefficient(0, 1, 2);
			m.SetCoefficient(1, 0, 3);
			m.SetCoefficient(1, 1, 4);
			m.SetCoefficient(1, 2, 2);
			m.SetCoefficient(2, 1, 7);
			m.SetCoefficient(2, 2, 6);
			m.SetCoefficient(2, 3, 3);
			m.SetCoefficient(3, 2, 4);
			m.SetCoefficient(3, 3, 9);

			m.SetC(0, 5);
			m.SetC(1, 1);
			m.SetC(2, -5);
			m.SetC(3, 1);

			auto solution = m.Solve();

			std::streambuf* backup;
			backup = std::cout.rdbuf();
			std::stringstream ss;
			std::cout.rdbuf(ss.rdbuf());
			m.Dump(std::cout, true);
			OutputDebugStringA(ss.str().c_str());
			std::cout.rdbuf(backup);

			auto b1 = solution[0];
			auto b2 = solution[1];
			auto b3 = solution[2];
			auto b4 = solution[3];

			Assert::AreEqual(1.5714285714285716, b1);
			Assert::AreEqual(-1.4285714285714286, b2);
			Assert::AreEqual(1.0, b3);
			Assert::AreEqual(-0.33333333333333331, b4);

		}

		TEST_METHOD(RowStorage)
		{
			UnsymmetricBandedMatrix m(4, 3, UnsymmetricBandedMatrix::Storage::Row);
			m.SetCoefficient(0, 0, 5);
			m.SetCoefficient(0, 1, 2);
			m.SetCoefficient(1, 0, 3);
			m.SetCoefficient(1, 1, 4);
			m.SetCoefficient(1, 2, 2);
			m.SetCoefficient(2, 1, 7);
			m.SetCoefficient(2, 2, 6);
			m.SetCoefficient(2, 3, 3);
			m.SetCoefficient(3, 2, 4);
			m.SetCoefficient(3, 3, 9);

			m.SetC(0, 5);
			m.SetC(1, 1);
			m.SetC(2, -5);
			m.SetC(3, 1);

			auto solution = m.Solve();

			auto b1 = solution[0];
			auto b2 = solution[1];
			auto b3 = solution[2];
			auto b4 = solution[3];

			Assert::AreEqual(1.5714285714285716, b1);
			Assert::AreEqual(-1.4285714285714286, b2);
			Assert::AreEqual(1.0, b3);
			Assert::AreEqual(-0.33333333333333331, b4);
		}
	};
}
