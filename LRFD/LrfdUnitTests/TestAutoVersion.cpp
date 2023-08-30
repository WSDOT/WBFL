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
			auto version = BDSManager::GetEdition();
			auto units = BDSManager::GetUnits();

			// make sure the default values are not equal to the values we are going to set
			Assert::IsTrue(version != BDSManager::Edition::FirstEditionWith1997Interims);
			Assert::IsTrue(units != BDSManager::Units::SI);

			{
				// put this in a scope so av get destroyed
				BDSAutoVersion av;
				BDSManager::SetEdition(BDSManager::Edition::FirstEditionWith1997Interims);
				BDSManager::SetUnits(BDSManager::Units::SI);
			}

			// verify settings rolled back to their original values
			Assert::IsTrue(version == BDSManager::GetEdition());
			Assert::IsTrue(units == BDSManager::GetUnits());
		}

		TEST_METHOD(LRFR)
		{
			auto version = MBEManager::GetEdition();

			// make sure the default values are not equal to the values we are going to set
			Assert::IsTrue(version != MBEManager::Edition::SecondEditionWith2014Interims);

			{
				// put this in a scope so av get destroyed
				MBEAutoVersion av;
				MBEManager::SetEdition(MBEManager::Edition::SecondEditionWith2014Interims);
			}

			// verify settings rolled back to their original values
			Assert::IsTrue(version == MBEManager::GetEdition());
		}
	};
}
