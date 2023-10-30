#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestGirderLine)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("N"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(piers, true);

			auto girder_line = bridge->GetGirderLine(0);
			Assert::AreEqual((IDType)500, girder_line->GetID());
			Assert::AreEqual((IDType)100, girder_line->GetLayoutLineID());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::Start).get());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::End).get());
			Assert::AreEqual(97.0, girder_line->GetGirderLength(), 0.00001);
			Assert::AreEqual(95.0, girder_line->GetSpanLength(), 0.00001);
			Assert::AreEqual(100.0, girder_line->GetLayoutLength(), 0.00001);
			Assert::IsTrue(Point2d(73.639610306789294, 87.781745930520245) == girder_line->GetPierPoint(EndType::Start));
			Assert::IsTrue(Point2d(144.35028842544403, 158.49242404917499) == girder_line->GetPierPoint(EndType::End));
			Assert::IsTrue(Point2d(75.407377259755663, 89.549512883486614) == girder_line->GetBearingPoint(EndType::Start));
			Assert::IsTrue(Point2d(142.58252147247765, 156.72465709620863) == girder_line->GetBearingPoint(EndType::End));
			Assert::IsTrue(Point2d(74.700270478569109, 88.842406102300060) == girder_line->GetEndPoint(EndType::Start));
			Assert::IsTrue(Point2d(143.28962825366420, 157.43176387739518) == girder_line->GetEndPoint(EndType::End));
			Assert::IsNotNull(girder_line->GetPath().get());
			Assert::IsTrue(Direction(M_PI / 4) == girder_line->GetDirection());
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::Start), 0.00001);
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::End), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::Start), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::End), 0.00001);

		}
	};
}
