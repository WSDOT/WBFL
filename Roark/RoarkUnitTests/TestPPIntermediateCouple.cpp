#include "pch.h"
#include "CppUnitTest.h"
#include "NumericalTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Beams;

namespace RoarkUnitTest
{
	TEST_CLASS(TestPPIntermediateCouple)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// Don't run this test with the concentrated moment anywhere but the ends of the girder.
			// The numerical integration routine can't handle the discontinuity in the moment diagram
			// caused by the concentrated load.
			// Test_Numerical(PPIntermediateCouple(10,5,10,1));
			Test_Numerical(PPIntermediateCouple(10, 0, 10, 1));
			Test_Numerical(PPIntermediateCouple(10, 10, 10, 1));
		}
	};
}
