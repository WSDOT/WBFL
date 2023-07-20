#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestXFunction)
	{
	public:
		
		TEST_METHOD(Test)
		{
			try
			{
				THROW_FUNCTION(XFunction::Reason::MultiValued);
			}
			catch (XFunction& e)
			{
				Assert::IsTrue(XFunction::Reason::MultiValued == e.GetReasonCode());
			}
		}
	};
}
