#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestThroughPointDiaphragmLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("N"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(0.0, 0.0, 0.0, 0.0, piers, true);

			ThroughPointDiaphragmLineFactory factory;
			factory.SetPoint(Point2d(50.0, 50.0));
			factory.SetDirection(M_PI/4);
			factory.SetDiaphragmLineID(100);
			factory.IsStaggered(true);
			factory.SetGirderLineID(SideType::Left, 500);
			factory.SetGirderLineID(SideType::Right, 504);

			auto vDiaphragmLines = factory.Create(bridge);
			Assert::AreEqual((size_t)1, vDiaphragmLines.size());
			const auto& diaphragm_line = vDiaphragmLines.front();

			Assert::AreEqual((IDType)100, diaphragm_line->GetID());
			Assert::AreEqual(5.0, diaphragm_line->Length(500));
			Assert::IsTrue(Point2d(7.5, 10.0) == diaphragm_line->GetPoint(500, EndType::Start));
			Assert::IsTrue(Point2d(7.5,  5.0) == diaphragm_line->GetPoint(500, EndType::End));

			factory.IsStaggered(false);
			vDiaphragmLines = factory.Create(bridge);
			Assert::AreEqual((size_t)1, vDiaphragmLines.size());
			const auto& diaphragm_line2 = vDiaphragmLines.front();

			Assert::AreEqual((IDType)100, diaphragm_line2->GetID());
			Assert::AreEqual(7.0710678118654755, diaphragm_line2->Length(500));
			Assert::IsTrue(Point2d(10.0, 10.0) == diaphragm_line2->GetPoint(500, EndType::Start));
			Assert::IsTrue(Point2d(5.0, 5.0) == diaphragm_line2->GetPoint(500, EndType::End));
		}
	};
}
