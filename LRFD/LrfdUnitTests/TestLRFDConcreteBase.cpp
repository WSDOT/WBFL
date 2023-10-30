#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestLRFDConcreteBase)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// ConcreteBase is an abstract base class that doesn't provide any significant functionality.
			// It has a bunch of Set/Get methods.
			// Nothing to test
			//Assert::Fail();
		}
	};
}
