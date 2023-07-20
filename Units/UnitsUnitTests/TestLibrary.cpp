#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitsUnitTest
{
	TEST_CLASS(TestLibrary)
	{
	public:
		
		TEST_METHOD(Test)
		{
			Assert::IsTrue(true, _T("Nothing to test"));
		}
	};
}
