#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace WBFL::System;

namespace SystemUnitTest
{
	TEST_CLASS(TestException)
	{
	public:
		
		TEST_METHOD(Test)
		{
			XProgrammingError e;
			try
			{
				e.Throw();
			}
			catch (XProgrammingError& ex)
			{
				Assert::AreEqual((Int32)5, ex.GetReason());
				Assert::IsTrue(XProgrammingError::Reason::Unspecified == ex.GetReasonCode());
			}
      }
	};
}
