#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTests
{
	TEST_CLASS(TestDeckBoundary)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// Create a basic bridge
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("N 45 E"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(0,0,0,0,piers, true);

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

			// Start line is parallel to Pier 100 (N 45 W) through Sta 105, end line is parallel to Pier 200 (N 45 E) through Sta 205
			vPoints = deck_boundary->GetPerimeter(3, 100, 5.0, 200, 5.0, true);
			i = 0;
			Assert::IsTrue(Point2d(95.000000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(115.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(120.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(155.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(180.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(195.00000000000000, -10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(215.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(155.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(100.00000000000000, 10.000000000000000) == vPoints[i++]);
			Assert::IsTrue(Point2d(95.000000000000000, 10.000000000000000) == vPoints[i++]);
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

		TEST_METHOD(PierRegion)
		{
			// Regression test for deck casting regions in PGSplice. A pier region is requested with
			// the same start and end pier and Xstart < 0 < Xend. When bParallelToPiers is true, the region
			// must be a parallelogram with its transverse edges parallel to the pier and passing through
			// the alignment at the pier station + Xstart and + Xend. Previously both transverse edges were
			// left on the pier centerline, producing a zero-width region.

			// 3 pier bridge with two 100 ft spans along the X axis
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("N 45 W"), connection_geometry, connection_geometry);
			piers.emplace_back(300, 300.0, _T("N 45 E"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(0, 0, 0, 0, piers, true);

			// Deck edges are layout lines 100 (10 ft left, y = 10) and 104 (10 ft right, y = -10)
			SimpleDeckBoundaryFactory factory;
			factory.SetEdgeID(SideType::Left, 100);
			factory.SetEdgeID(SideType::Right, 104);

			factory.SetTransverseEdgeID(EndType::Start, 100);
			factory.SetTransverseEdgeType(EndType::Start, TransverseEdgeType::Pier);

			factory.SetTransverseEdgeID(EndType::End, 300);
			factory.SetTransverseEdgeType(EndType::End, TransverseEdgeType::Pier);

			// Edge breaks and edge break IDs are intentionally not set - the factory defaults must be "no breaks"

			auto deck_boundary = factory.Create(bridge);

			// Pier region at Pier 200 extending 10% of the span length (10 ft) on either side of the pier.
			// Transverse edges are parallel to Pier 200 (N 45 W) through Sta 190 and Sta 210
			auto vPoints = deck_boundary->GetPerimeter(2, 200, -10.0, 200, 10.0, true);
			int i = 0;
			Assert::IsTrue(Point2d(180.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(200.0, -10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(220.0, -10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(200.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(180.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(i == vPoints.size());

			// Intermediate edge points are included between the transverse edges, and nothing outside of them
			vPoints = deck_boundary->GetPerimeter(3, 200, -10.0, 200, 10.0, true);
			i = 0;
			Assert::IsTrue(Point2d(180.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(200.0, -10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(210.0, -10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(220.0, -10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(200.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(190.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(180.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(i == vPoints.size());

			// Same region with transverse edges normal to the alignment - a rectangle
			vPoints = deck_boundary->GetPerimeter(2, 200, -10.0, 200, 10.0, false);
			i = 0;
			Assert::IsTrue(Point2d(190.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(190.0, -10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(210.0, -10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(210.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(Point2d(190.0, 10.0) == vPoints[i++]);
			Assert::IsTrue(i == vPoints.size());
		}
	};
}
