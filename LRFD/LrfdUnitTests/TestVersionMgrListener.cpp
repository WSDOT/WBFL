#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestVersionMgrListener)
	{
	public:
		
		TEST_METHOD(Test)
		{
			LRFDVersionMgrListener listener;
			// this is a class with 3 do-nothing methods
			// there isn't anything to test
		}
	};
}
