#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Math;

namespace MathUnitTests
{
	TEST_CLASS(TestXNumericalIntegration)
	{
	public:
		
		TEST_METHOD(Test)
		{
			try
			{
				THROW_NUMERICINTEGRATION(XNumericIntegration::Reason::Unknown);
			}
			catch (XNumericIntegration& e)
			{
				Assert::IsTrue(XNumericIntegration::Reason::Unknown == e.GetReasonCode());
			}
		}
	};
}
