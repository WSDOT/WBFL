#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestCoordMapper1d)
	{
	public:
		
		TEST_METHOD(Default)
		{
			CoordMapper1d m1;
			Assert::AreEqual(0.0, m1.GetA(0.0));
			Assert::AreEqual(0.0, m1.GetB(0.0));
			Assert::AreEqual(10.0, m1.GetA(10.0));
			Assert::AreEqual(10.0, m1.GetB(10.0));
		}

		TEST_METHOD(Offset)
		{
			//            0.0      10.0     20.0
			// A ----------|---------|--------|----->
			// B ----------|---------|--------|----->
			//          -10.0       0.0     10.0
			CoordMapper1d m1(10.0,true);
			Assert::AreEqual(-10.0, m1.GetB(0.0));
			Assert::AreEqual(0.0, m1.GetB(10.0));
			Assert::AreEqual(20.0, m1.GetA(10.0));

			//            0.0      10.0     20.0
			// A ----------|---------|--------|----->
			// B <---------|---------|--------|-----
			//           10.0       0.0    -10.0
			CoordMapper1d m2(10.0, false);
			Assert::AreEqual(10.0, m2.GetB(0.0));
			Assert::AreEqual(0.0, m2.GetB(10.0));
			Assert::AreEqual(20.0, m2.GetA(-10.0));
			Assert::AreEqual(0.0, m2.GetA(10.0));
		}

		TEST_METHOD(Scaled)
		{
			//          -10.0       0.0     10.0
			// A ----------|---------|--------|----->
			// B <---------|---------|--------|-----
			//           20.0       0.0    -20.0
			CoordMapper1d m(0.0, 0.0, 10.0, -20.0);
			Assert::AreEqual(20.0, m.GetB(-10.0));
			Assert::AreEqual(-20.0, m.GetB( 10.0));
			Assert::AreEqual(0.0, m.GetB(0.0));
			Assert::AreEqual(0.0, m.GetA(0.0));
			Assert::AreEqual(10.0, m.GetA(-20.0));
			Assert::AreEqual(-10.0, m.GetA(20.0));
		}
	};
}
