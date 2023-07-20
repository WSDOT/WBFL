#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphingUnitTests
{
	TEST_CLASS(TestAxisXY)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// This class is difficult to test. The code that computes drawing values (such as coordinates)
			// needs to be refactored so it is testable. However, after using this class for many years without
			// issue there isn't a compelling need to do the refactoring at this time.
			//Assert::Fail();
		}
	};
}
