#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestUniformSpacingLayoutLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// Create a 3 span bridge framing model
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, connection_geometry);
			piers.emplace_back(300, 300.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(100,0,0,0,piers, true);

			// Create layout lines
			UniformSpacingLayoutLineFactory factory;
			factory.SetAlignmentID(999);
			factory.SetStartPierLineID(100);
			factory.SetEndPierLineID(300);
			factory.SetPierLineIDIncrement(100);

			factory.SetLayoutLineID(500);
			factory.SetLayoutLineIDIncrement(1);

			factory.SetStartSpacingOffset(-10.0);
			factory.SetEndSpacingOffset(-10.0);
			std::vector<Float64> s{5, 5, 5, 5};
			factory.SetStartSpacing(s);
			factory.SetEndSpacing(s);

			auto layout_lines = factory.Create(bridge);
			Assert::AreEqual((size_t)10, layout_lines.size());

			// Span 1 layout lines
			auto layout_line = layout_lines[0];
			Assert::AreEqual((IDType)500, layout_line.first);
			Assert::IsTrue(Point2d(-7.0710678118654746, 7.0710678118654746) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(100, 10.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[1];
			Assert::AreEqual((IDType)501, layout_line.first);
			Assert::IsTrue(Point2d(-3.5355339059327373, 3.5355339059327373) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(100, 5.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[2];
			Assert::AreEqual((IDType)502, layout_line.first);
			Assert::IsTrue(Point2d(0.0, 0.0) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(100, 0.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[3];
			Assert::AreEqual((IDType)503, layout_line.first);
			Assert::IsTrue(Point2d(3.5355339059327373, -3.5355339059327373) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(100, -5.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[4];
			Assert::AreEqual((IDType)504, layout_line.first);
			Assert::IsTrue(Point2d(7.0710678118654746, -7.0710678118654746) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(100, -10.0) == layout_line.second->GetEndPoint());

			// Span 2 layout lines
			layout_line = layout_lines[5];
			Assert::AreEqual((IDType)505, layout_line.first);
			Assert::IsTrue(Point2d(100, 10.0) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(200, 10.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[6];
			Assert::AreEqual((IDType)506, layout_line.first);
			Assert::IsTrue(Point2d(100, 5.0) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(200, 5.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[7];
			Assert::AreEqual((IDType)507, layout_line.first);
			Assert::IsTrue(Point2d(100, 0.0) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(200, 0.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[8];
			Assert::AreEqual((IDType)508, layout_line.first);
			Assert::IsTrue(Point2d(100, -5.0) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(200, -5.0) == layout_line.second->GetEndPoint());

			layout_line = layout_lines[9];
			Assert::AreEqual((IDType)509, layout_line.first);
			Assert::IsTrue(Point2d(100, -10.0) == layout_line.second->GetStartPoint());
			Assert::IsTrue(Point2d(200, -10.0) == layout_line.second->GetEndPoint());
		}
	};
}
