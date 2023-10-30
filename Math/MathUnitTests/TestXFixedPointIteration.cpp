#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestXFixedPointIteration)
	{
	public:
		
		TEST_METHOD(Test)
		{
			try
			{
				THROW_FIXEDPOINTITERATION(XFixedPointIteration::Reason::MaxIterExceeded, 999.999);
			}
			catch (XFixedPointIteration& e)
			{
				Assert::AreEqual(999.999, e.GetLast());
				Assert::IsTrue(XFixedPointIteration::Reason::MaxIterExceeded == e.GetReasonCode());
			}
		}
	};
}
