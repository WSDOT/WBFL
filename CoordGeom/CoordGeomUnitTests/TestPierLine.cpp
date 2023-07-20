#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestPierLine)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(piers, true);

			auto pierline1 = bridge->GetPierLine(0);
			Assert::AreEqual((IndexType)0, pierline1->GetIndex());
			Assert::AreEqual((IDType)100, pierline1->GetID());
			Assert::AreEqual((IDType)999, pierline1->GetAlignmentID());
			Assert::IsTrue(Station(100.0) == pierline1->GetStation());
			Assert::IsTrue(Direction(3 * M_PI/ 4) == pierline1->GetDirection());
			Assert::IsTrue(Direction(M_PI / 4) == pierline1->GetNormal());
			Assert::IsTrue(Angle(0.0) == pierline1->GetSkewAngle());
			Assert::IsTrue(ConnectionGeometry() == pierline1->GetConnectionGeometry(PierFaceType::Back));
			Assert::IsTrue(connection_geometry == pierline1->GetConnectionGeometry(PierFaceType::Ahead));
			Assert::IsTrue(Point2d(80.710678118654755, 80.710678118654755) == pierline1->GetAlignmentPoint());
			Assert::IsTrue(Point2d(80.710678118654755, 80.710678118654755) == pierline1->GetBridgeLinePoint());
			Assert::IsTrue(Point2d(87.781745930520231, 73.639610306789280) == pierline1->GetLeftPoint());
			Assert::IsTrue(Point2d(101.92388155425118, 59.497474683058329) == pierline1->GetRightPoint());
			Assert::IsTrue(Line2d(-114.14213562373095,Vector2d(Size2d(-0.70710678118654757, -0.70710678118654757))) == pierline1->GetCenterLine());
			Assert::AreEqual(2.5, pierline1->GetBearingOffset(PierFaceType::Ahead, M_PI / 4));

			auto pierline2 = bridge->GetPierLine(1);
			Assert::AreEqual((IndexType)1, pierline2->GetIndex());
			Assert::AreEqual((IDType)200, pierline2->GetID());
			Assert::AreEqual((IDType)999, pierline2->GetAlignmentID());
			Assert::IsTrue(Station(200.0) == pierline2->GetStation());
			Assert::IsTrue(Direction(3 * M_PI / 4) == pierline2->GetDirection());
			Assert::IsTrue(Direction(M_PI / 4) == pierline2->GetNormal());
			Assert::IsTrue(Angle(0.0) == pierline2->GetSkewAngle());
			Assert::IsTrue(ConnectionGeometry() == pierline2->GetConnectionGeometry(PierFaceType::Ahead));
			Assert::IsTrue(connection_geometry == pierline2->GetConnectionGeometry(PierFaceType::Back));
			Assert::IsTrue(Point2d(151.42135623730951, 151.42135623730951) == pierline2->GetAlignmentPoint());
			Assert::IsTrue(Point2d(151.42135623730951, 151.42135623730951) == pierline2->GetBridgeLinePoint());
			Assert::IsTrue(Point2d(158.49242404917499, 144.35028842544403) == pierline2->GetLeftPoint());
			Assert::IsTrue(Point2d(172.63455967290594, 130.20815280171308) == pierline2->GetRightPoint());
			Assert::IsTrue(Line2d(-214.14213562373095, Vector2d(Size2d(-0.70710678118654757, -0.70710678118654757))) == pierline2->GetCenterLine());
			Assert::AreEqual(2.5, pierline2->GetBearingOffset(PierFaceType::Back, M_PI / 4));
		}
	};
}
