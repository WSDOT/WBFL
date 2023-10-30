#include "pch.h"
#include "CppUnitTest.h"
#include <Units\Units.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Graphing;

namespace GraphingUnitTests
{
	TEST_CLASS(TestGraphXY)
	{
	public:
		
		// There isn't much else to test in the public interface.
		// There are a bunch of set/get methods that work, and test cases can be added later
		// This class can be refactored to be more testable, separating the calculations from the drawing code
		TEST_METHOD(Test)
		{
			WBFL::Units::LengthData DUMMY(WBFL::Units::Measure::Meter);
			WBFL::Units::LengthTool DUMMY_TOOL(DUMMY);
			GraphXY graph(&DUMMY_TOOL,&DUMMY_TOOL);

			auto series1 = graph.CreateDataSeries(_T("Series1"), PS_SOLID, 1, RGB(10, 10, 10));
			auto series2 = graph.CreateDataSeries(_T("Series2"), PS_SOLID, 1, RGB(10, 10, 10));

			GraphXY::DataSeries data1{Point(0, 0), Point(10, 10), Point(20, 20)};
			graph.AddPoints(series1, data1);

			GraphXY::DataSeries data2{Point(0, 0), Point(10, 10), Point(20, 20), Point(20, 20)};
			graph.AddPoints(series2, data2);

			Assert::AreEqual((IndexType)2, graph.GetDataSeriesCount());
			Assert::AreEqual((IndexType)3, graph.GetPointCount(series1));
			Assert::AreEqual((IndexType)4, graph.GetPointCount(series2));
			Assert::IsTrue(Rect(0,0,20,20) == graph.GetRawWorldRect());

			graph.RemoveDataSeries(series1);
			Assert::AreEqual((IndexType)1, graph.GetDataSeriesCount());
		}
	};
}
