#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Graphing;

namespace GraphingUnitTests
{
	TEST_CLASS(TestGraphColor)
	{
	public:
		
		TEST_METHOD(Test)
		{
			GraphColor gc;

			gc.SetHueRange(200, 300);
			gc.SetSaturationRange(0.1, 0.9);
			gc.SetLightnessRange(0.2, 0.8);

			Assert::AreEqual((COLORREF)5716525, gc.GetColor(0));
			Assert::AreEqual((COLORREF)6762802, gc.GetColor(1));
			Assert::AreEqual((COLORREF)13598551, gc.GetColor(10));
			Assert::AreEqual((COLORREF)5455147, gc.GetColor(100));
		}
	};
}
