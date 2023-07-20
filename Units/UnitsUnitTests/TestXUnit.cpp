#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestXUnit)
	{
	public:
		
		TEST_METHOD(Test)
		{
			XUnit e(XUnit::Reason::BadStationFormat,_T(__FILE__),__LINE__);
			Assert::ExpectException<XUnit>([&e]() {e.Throw(); });
			try { e.Throw(); }
			catch (XUnit& ex)
			{
				Assert::IsTrue(ex.GetReasonCode() == XUnit::Reason::BadStationFormat);
			}
		}
	};
}
