#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestColorConverter)
	{
	public:
		
		// https://www.w3schools.com/colors/colors_converter.asp
		TEST_METHOD(HSLtoRGB)
		{
			BYTE r, b, g;
			std::tie(r, b, g) = ColorConverter::HSLtoRGB(195, 0.5, 0.5);
			Assert::IsTrue(63 == r);
			Assert::IsTrue(191 == g);
			Assert::IsTrue(159 == b);

			std::tie(r, b, g) = ColorConverter::HSLtoRGB(0, 0, 0);
			Assert::IsTrue(0 == r);
			Assert::IsTrue(0 == g);
			Assert::IsTrue(0 == b);

			std::tie(r, b, g) = ColorConverter::HSLtoRGB(0, 0, 1.0);
			Assert::IsTrue(255 == r);
			Assert::IsTrue(255 == g);
			Assert::IsTrue(255 == b);
		}

		TEST_METHOD(RGBtoHSL)
		{
			Float64 h, s, l;
			std::tie(h, s, l) = ColorConverter::RGBtoHSL(63, 159, 191);
			Assert::AreEqual(195., h);
			Assert::AreEqual(0.50393700787401574, s);
			Assert::AreEqual(0.49803921568627452, l);

			std::tie(h, s, l) = ColorConverter::RGBtoHSL(0, 0, 0);
			Assert::AreEqual(0.0, h);
			Assert::AreEqual(0.0, s);
			Assert::AreEqual(0.0, l);

			std::tie(h, s, l) = ColorConverter::RGBtoHSL(255,255,255);
			Assert::AreEqual(0.0, h);
			Assert::AreEqual(1.0, l);
			Assert::AreEqual(0.0, s);
		}

		TEST_METHOD(HSVtoRGB)
		{
			BYTE r, g, b;
			std::tie(r, g, b) = ColorConverter::HSVtoRGB(195, 0.67, 0.75);
			Assert::IsTrue(63 == r);
			Assert::IsTrue(159 == g);
			Assert::IsTrue(191 == b);

			std::tie(r, b, g) = ColorConverter::HSVtoRGB(0, 0, 0);
			Assert::IsTrue(0 == r);
			Assert::IsTrue(0 == g);
			Assert::IsTrue(0 == b);

			std::tie(r, b, g) = ColorConverter::HSVtoRGB(0, 0, 1.0);
			Assert::IsTrue(255 == r);
			Assert::IsTrue(255 == g);
			Assert::IsTrue(255 == b);
		}

		TEST_METHOD(RGBtoHSV)
		{
			Float64 h, s, v;
			std::tie(h, s, v) = ColorConverter::RGBtoHSV(63, 159, 191);
			Assert::AreEqual(195., h);
			Assert::AreEqual(0.67015706806282727, s);
			Assert::AreEqual(0.74901960784313726, v);

			std::tie(h, s, v) = ColorConverter::RGBtoHSV(0, 0, 0);
			Assert::AreEqual(0.0, h);
			Assert::AreEqual(0.0, s);
			Assert::AreEqual(0.0, v);

			std::tie(h, s, v) = ColorConverter::RGBtoHSL(255, 255, 255);
			Assert::AreEqual(0.0, h);
			Assert::AreEqual(0.0, s);
			Assert::AreEqual(1.0, v);
		}
	};
}
