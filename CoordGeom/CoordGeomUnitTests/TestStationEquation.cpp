#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestStationEquation)
	{
	public:
		
		TEST_METHOD(Default)
		{
			StationEquation eq;
			Assert::AreEqual(0.0, eq.GetBack());
			Assert::AreEqual(0.0, eq.GetAhead());
			Assert::AreEqual(0.0, eq.GetNormalizedStation());
		}

		TEST_METHOD(Constructed)
		{
			StationEquation eq(300, 400, 200);
			Float64 back, ahead, normalized;
			std::tie(back, ahead, normalized) = eq.GetEquationParameters();
			Assert::AreEqual(300.0, back);
			Assert::AreEqual(400.0, ahead);
			Assert::AreEqual(200.0, normalized);
		}
	};
}
