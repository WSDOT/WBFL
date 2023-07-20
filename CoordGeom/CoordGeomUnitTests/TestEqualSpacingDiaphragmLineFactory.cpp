#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestEqualSpacingDiaphragmLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("N"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(0.0, 0.0, 0.0, 0.0, piers, true);

			EqualSpacingDiaphragmLineFactory factory;
			factory.SetAlignmentID(999);
			factory.SetStationRange(110, 190);
			factory.SetDiaphragmLineID(100);
			factory.SetDiaphragmLineIDIncrement(10);
			factory.SetGirderLineID(SideType::Left, 500);
			factory.SetGirderLineID(SideType::Right, 504);
			factory.IsStaggered(true);

			factory.SetDivisor(0);
			auto vDiaphragmLines = factory.Create(bridge);
			Assert::AreEqual((size_t)0, vDiaphragmLines.size());

			factory.SetDivisor(1);
			vDiaphragmLines = factory.Create(bridge);
			Assert::AreEqual((size_t)0, vDiaphragmLines.size());

			factory.SetDivisor(2);
			vDiaphragmLines = factory.Create(bridge);
			Assert::AreEqual((size_t)1, vDiaphragmLines.size());

			auto diaphragm_line = vDiaphragmLines[0];
			Assert::AreEqual((IDType)100, diaphragm_line->GetID());
			Assert::AreEqual(5.0, diaphragm_line->Length(500));
			Assert::IsTrue(Point2d(150, 10.0) == diaphragm_line->GetPoint(500, EndType::Start));
			Assert::IsTrue(Point2d(150, 5.0) == diaphragm_line->GetPoint(500, EndType::End));
			Assert::IsTrue(Point2d(150, 5.0) == diaphragm_line->GetPoint(501, EndType::Start));
			Assert::IsTrue(Point2d(150, 0.0) == diaphragm_line->GetPoint(501, EndType::End));
			Assert::IsTrue(Point2d(150, 0.0) == diaphragm_line->GetPoint(502, EndType::Start));
			Assert::IsTrue(Point2d(150, -5.0) == diaphragm_line->GetPoint(502, EndType::End));
			Assert::IsTrue(Point2d(150, -5.0) == diaphragm_line->GetPoint(503, EndType::Start));
			Assert::IsTrue(Point2d(150, -10.0) == diaphragm_line->GetPoint(503, EndType::End));
		}
	};
}
