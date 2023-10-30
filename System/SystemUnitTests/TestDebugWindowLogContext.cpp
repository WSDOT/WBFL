#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestDebugWindowLogContext)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// This context writes logging information to the Visual Studio output window. Can't really test it
			// other than observe messages get written out.
			//Assert::Fail();
			// DebugWindowLogContext will be eliminated after conversion to VS Unit Testing is complete
		}
	};
}
