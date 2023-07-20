#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSimpleDeckBoundaryFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// Create a basic bridge
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("N 45 E"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(0, 0, 0, 0, piers, true);

			// Create layout lines to locate transverse edge points
			auto layout_line_factory = std::make_shared<AlignmentOffsetLayoutLineFactory>();
			layout_line_factory->SetAlignmentID(999);
			layout_line_factory->SetLayoutLineID(1000);
			layout_line_factory->SetLayoutLineIDIncrement(1);
			layout_line_factory->SetLayoutLineCount(2); // create 2 layout lines
			layout_line_factory->SetOffset(-20.0); // offset from alignment (20 ft left)
			layout_line_factory->SetOffsetIncrement(40.0); // each subsequent layout line is 40 ft to the right of the previous
			bridge->AddLayoutLineFactory(layout_line_factory);

			// Use a factory to create the boundary
			SimpleDeckBoundaryFactory factory;
			factory.SetEdgeID(SideType::Left, 100);
			factory.SetEdgeID(SideType::Right, 104);

			factory.SetTransverseEdgeID(EndType::Start, 100);
			factory.SetTransverseEdgeType(EndType::Start, TransverseEdgeType::Pier);

			factory.SetTransverseEdgeID(EndType::End, 200);
			factory.SetTransverseEdgeType(EndType::End, TransverseEdgeType::Pier);

			factory.SetEdgeBreakID(SideType::Left, 1000);
			factory.SetEdgeBreakID(SideType::Right, 1001);

			factory.SetBreakEdge(EndType::Start, SideType::Left, true);
			factory.SetBreakEdge(EndType::Start, SideType::Right, true);
			factory.SetBreakEdge(EndType::End, SideType::Left, true);
			factory.SetBreakEdge(EndType::End, SideType::Right, true);

			auto deck_boundary = factory.Create(bridge);

			/// Test the boundary
			auto vPoints = deck_boundary->GetPerimeter(3);
			int i = 0;
			Assert::IsTrue(Point2d(80.000000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(80.000000000000000, 20.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(120.00000000000000, -20.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(120.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(150.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(180.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(180.00000000000000, -20.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(220.00000000000000, 20.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(220.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(150.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(100.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(80.000000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(i == vPoints.size());

			vPoints = deck_boundary->GetPerimeter(3, 100, 5.0, 200, 5.0, true);
			i = 0;
			Assert::IsTrue(Point2d(90.000000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(110.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(120.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(150.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(180.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(190.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(210.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(150.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(100.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(90.000000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(80.000000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(90.000000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(i == vPoints.size());

			auto edge_points = deck_boundary->GetTransverseEdgePoints(EndType::Start);
			i = 0;
			Assert::IsTrue(Point2d(80.000000000000000, 10.00000000000000) == edge_points[i++]);
			Assert::IsTrue(Point2d(80.000000000000000, 20.00000000000000) == edge_points[i++]);
			Assert::IsTrue(Point2d(120.00000000000000, -20.00000000000000) == edge_points[i++]);
			Assert::IsTrue(Point2d(120.00000000000000, -10.00000000000000) == edge_points[i++]);

			edge_points = deck_boundary->GetTransverseEdgePoints(EndType::End);
			i = 0;
			Assert::IsTrue(Point2d(180.00000000000000, -10.000000000000000) == edge_points[i++]);
			Assert::IsTrue(Point2d(180.00000000000000, -20.000000000000000) == edge_points[i++]);
			Assert::IsTrue(Point2d(220.00000000000000, 20.000000000000000) == edge_points[i++]);
			Assert::IsTrue(Point2d(220.00000000000000, 10.000000000000000) == edge_points[i++]);

			Assert::IsNotNull(deck_boundary->GetEdgePath(SideType::Left, true).get());
			Assert::IsNotNull(deck_boundary->GetEdgePath(SideType::Left, false).get());
			Assert::IsNotNull(deck_boundary->GetEdgePath(SideType::Right, true).get());
			Assert::IsNotNull(deck_boundary->GetEdgePath(SideType::Right, false).get());
		}
	};
}
