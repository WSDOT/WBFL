#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestSectionValue)
	{
	public:
		
		TEST_METHOD(Constructors)
		{
			SectionValue v1;
			Assert::AreEqual(0.0, v1.Left());
			Assert::AreEqual(0.0, v1.Right());

			SectionValue v2(5.0, 1.0);
			Assert::AreEqual(5.0, v2.Left());
			Assert::AreEqual(1.0, v2.Right());

			SectionValue v3(v2);
			Assert::AreEqual(5.0, v3.Left());
			Assert::AreEqual(1.0, v3.Right());
		}

		TEST_METHOD(Operators)
		{
			SectionValue v;
			v = 10;
			Assert::AreEqual(10.0, v.Left());
			Assert::AreEqual(10.0, v.Right());

			v += 10;
			Assert::AreEqual(20.0, v.Left());
			Assert::AreEqual(20.0, v.Right());

			v -= 40;
			Assert::AreEqual(-20.0, v.Left());
			Assert::AreEqual(-20.0, v.Right());
		
			v *= -2;
			Assert::AreEqual(40.0, v.Left());
			Assert::AreEqual(40.0, v.Right());

			v /= 4;
			Assert::AreEqual(10.0, v.Left());
			Assert::AreEqual(10.0, v.Right());

			v = -v;
			Assert::AreEqual(-10.0, v.Left());
			Assert::AreEqual(-10.0, v.Right());

			v.Left() = 1;
			v.Right() = 1;
			Assert::AreEqual(1.0, v.Left());
			Assert::AreEqual(1.0, v.Right());

			v += SectionValue(3, 5);
			Assert::AreEqual(4.0, v.Left());
			Assert::AreEqual(6.0, v.Right());

			v -= SectionValue(5, 3);
			Assert::AreEqual(-1.0, v.Left());
			Assert::AreEqual(3.0, v.Right());

			v *= SectionValue(10, 10);
			Assert::AreEqual(-10.0, v.Left());
			Assert::AreEqual(30.0, v.Right());

			v /= SectionValue(100, 100);
			Assert::AreEqual(-0.1, v.Left());
			Assert::AreEqual(0.3, v.Right());
		}

		TEST_METHOD(AsString)
		{
			SectionValue v(10.0);
			Assert::AreEqual(_T("10"), v.AsString().c_str());

			v += SectionValue(10, 20);
			Assert::AreEqual(_T("20\\30"), v.AsString().c_str());
		}
	};
}
