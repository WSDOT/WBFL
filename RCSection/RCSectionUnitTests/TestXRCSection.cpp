#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::RCSection;

namespace RCSectionUnitTest
{
	TEST_CLASS(TestXRCSection)
	{
	public:
		
		TEST_METHOD(Test)
		{
			try
			{
				THROW_RCSECTION(_T("Test exception"));
			}
			catch (XRCSection& e)
			{
				Assert::AreEqual(0, e.GetReason());
			}
		}
	};
}
