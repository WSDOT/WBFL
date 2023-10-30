#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLosses)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// This is an abstract base class that doesn't do too much of anything
			// It's methods are tested when testing the derived classes for prestress losses
			//Assert::Fail();
		}
	};
}
