#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestXRootFinder)
	{
	public:
		
		TEST_METHOD(Test)
		{
			try
			{
				THROW_ROOTFINDER(XRootFinder::Reason::RootNotPresent);
			}
			catch (XRootFinder& e)
			{
				Assert::IsTrue(XRootFinder::Reason::RootNotPresent == e.GetReasonCode());
			}
		}
	};
}
