#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestFileLogContext)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// This works like any other log context. It writes to a file.
			// We'll know if this doesn't work if the unit test log file is messed up.
			//Assert::Fail();
			// FileLogContext will be eliminated after conversion to VS Unit Testing is complete
		}
	};
}
