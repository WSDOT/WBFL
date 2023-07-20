#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::LRFD;

namespace LrfdUnitTests
{
	TEST_CLASS(TestAutoVersion)
	{
	public:
		
		TEST_METHOD(LRFD)
		{
			auto version = LRFDVersionMgr::GetVersion();
			auto units = LRFDVersionMgr::GetUnits();

			// make sure the default values are not equal to the values we are going to set
			Assert::IsTrue(version != LRFDVersionMgr::Version::FirstEditionWith1997Interims);
			Assert::IsTrue(units != LRFDVersionMgr::Units::SI);

			{
				// put this in a scope so av get destroyed
				LRFDAutoVersion av;
				LRFDVersionMgr::SetVersion(LRFDVersionMgr::Version::FirstEditionWith1997Interims);
				LRFDVersionMgr::SetUnits(LRFDVersionMgr::Units::SI);
			}

			// verify settings rolled back to their original values
			Assert::IsTrue(version == LRFDVersionMgr::GetVersion());
			Assert::IsTrue(units == LRFDVersionMgr::GetUnits());
		}

		TEST_METHOD(LRFR)
		{
			auto version = LRFRVersionMgr::GetVersion();

			// make sure the default values are not equal to the values we are going to set
			Assert::IsTrue(version != LRFRVersionMgr::Version::SecondEditionWith2014Interims);

			{
				// put this in a scope so av get destroyed
				LRFRAutoVersion av;
				LRFRVersionMgr::SetVersion(LRFRVersionMgr::Version::SecondEditionWith2014Interims);
			}

			// verify settings rolled back to their original values
			Assert::IsTrue(version == LRFRVersionMgr::GetVersion());
		}
	};
}
