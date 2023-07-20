#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Units;

namespace UnitsUnitTest
{
	TEST_CLASS(TestUnitValueNumericalFormatTools)
	{
	public:
		
		TEST_METHOD(Test)
		{
			IndirectMeasure id;
			LengthTool tool(id.SpanLength);
			Float64 span_length = ConvertToSysUnits(100.0, Measure::Feet);
   		Assert::AreEqual(_T("3.048e+01"), tool.AsString(span_length).c_str());
		}
	};
}
