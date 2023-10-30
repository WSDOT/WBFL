#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSingleDiaphragmLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("N"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(0.0, 0.0, 0.0, 0.0, piers, true);

			SingleDiaphragmLineFactory factory;
			factory.SetAlignmentID(999);
			factory.SetDiaphragmLineID(100);
			factory.SetGirderLineID(SideType::Left, 500);
			factory.SetGirderLineID(SideType::Right, 501);
			factory.SetOrientation(_T("N 45 W"));
			factory.SetStation(150.0);
			factory.IsStaggered(false);

			auto vDiaphragmLines = factory.Create(bridge);
			const auto& diaphragm_line = vDiaphragmLines.front();

			Assert::AreEqual((IDType)100, diaphragm_line->GetID());
			Assert::AreEqual(7.0710678118654755, diaphragm_line->Length(500));
			Assert::IsTrue(Point2d(140.0, 10.0) == diaphragm_line->GetPoint(500, EndType::Start));
			Assert::IsTrue(Point2d(145.0, 5.0) == diaphragm_line->GetPoint(500, EndType::End));
		}
	};
}
