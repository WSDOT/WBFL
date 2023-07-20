#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSimpleGirderLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("NORMAL"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, connection_geometry);
			piers.emplace_back(300, 300.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(piers, true);

			SimpleGirderLineFactory factory;
			factory.SetGirderLineID(1000);
			factory.SetGirderLineIDIncrement(1000);
			factory.SetLayoutLineID(SideType::Left,100);
			factory.SetLayoutLineID(SideType::Right, 102);
			factory.SetGirderLineType(GirderLineType::Chord);
			factory.SetPierID(EndType::Start, 100);
			factory.SetPierID(EndType::End, 300);
			factory.SetMeasurementType(EndType::Start, MeasurementType::NormalToItem);
			factory.SetMeasurementType(EndType::End, MeasurementType::NormalToItem);
			factory.SetMeasurementLocation(EndType::Start, MeasurementLocation::CenterlineBearing);
			factory.SetMeasurementLocation(EndType::End, MeasurementLocation::CenterlineBearing);
			factory.IsContinuous(true);

			auto girder_lines = factory.Create(bridge);
			Assert::AreEqual((size_t)3, girder_lines.size());
			Assert::IsNull(bridge->FindGirderLine(1000).get()); // factory does not store girder lines in the bridge
			Assert::IsNull(bridge->FindGirderLine(2000).get()); // factory does not store girder lines in the bridge
			Assert::IsNull(bridge->FindGirderLine(3000).get()); // factory does not store girder lines in the bridge

			auto girder_line = girder_lines[0];
			Assert::AreEqual((IDType)1000, girder_line->GetID());
			Assert::AreEqual((IDType)100, girder_line->GetLayoutLineID());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::Start).get());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::End).get());
			Assert::AreEqual((IDType)100, girder_line->GetPierLine(EndType::Start)->GetID());
			Assert::AreEqual((IDType)300, girder_line->GetPierLine(EndType::End)->GetID());
			Assert::AreEqual(197.0, girder_line->GetGirderLength(), 0.00001);
			Assert::AreEqual(195.0, girder_line->GetSpanLength(), 0.00001);
			Assert::AreEqual(200.0, girder_line->GetLayoutLength(), 0.00001);
			Assert::IsTrue(Point2d(73.639610306789294, 87.781745930520245) == girder_line->GetPierPoint(EndType::Start));
			Assert::IsTrue(Point2d(215.06096654409885, 229.20310216782980) == girder_line->GetPierPoint(EndType::End));
			Assert::IsTrue(Point2d(75.407377259755663, 89.549512883486614) == girder_line->GetBearingPoint(EndType::Start));
			Assert::IsTrue(Point2d(213.29319959113246, 227.43533521486344) == girder_line->GetBearingPoint(EndType::End));
			Assert::IsTrue(Point2d(74.700270478569109, 88.842406102300060) == girder_line->GetEndPoint(EndType::Start));
			Assert::IsTrue(Point2d(214.00030637231902, 228.14244199605000) == girder_line->GetEndPoint(EndType::End));
			Assert::IsNotNull(girder_line->GetPath().get());
			Assert::IsTrue(Direction(M_PI / 4) == girder_line->GetDirection());
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::Start), 0.00001);
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::End), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::Start), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::End), 0.00001);


			girder_line = girder_lines[1];
			Assert::AreEqual((IDType)2000, girder_line->GetID());
			Assert::AreEqual((IDType)101, girder_line->GetLayoutLineID());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::Start).get());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::End).get());
			Assert::AreEqual((IDType)100, girder_line->GetPierLine(EndType::Start)->GetID());
			Assert::AreEqual((IDType)300, girder_line->GetPierLine(EndType::End)->GetID());
			Assert::AreEqual(197.0, girder_line->GetGirderLength(), 0.00001);
			Assert::AreEqual(195.0, girder_line->GetSpanLength(), 0.00001);
			Assert::AreEqual(200.0, girder_line->GetLayoutLength(), 0.00001);
			Assert::IsTrue(Point2d(77.175144212722032, 84.246212024587507) == girder_line->GetPierPoint(EndType::Start));
			Assert::IsTrue(Point2d(218.59650045003158, 225.66756826189706) == girder_line->GetPierPoint(EndType::End));
			Assert::IsTrue(Point2d(78.942911165688400, 86.013978977553876) == girder_line->GetBearingPoint(EndType::Start));
			Assert::IsTrue(Point2d(216.82873349706520, 223.89980130893071) == girder_line->GetBearingPoint(EndType::End));
			Assert::IsTrue(Point2d(78.235804384501847, 85.306872196367323) == girder_line->GetEndPoint(EndType::Start));
			Assert::IsTrue(Point2d(217.53584027825175, 224.60690809011726) == girder_line->GetEndPoint(EndType::End));
			Assert::IsNotNull(girder_line->GetPath().get());
			Assert::IsTrue(Direction(M_PI / 4) == girder_line->GetDirection());
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::Start), 0.00001);
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::End), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::Start), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::End), 0.00001);

			girder_line = girder_lines[2];
			Assert::AreEqual((IDType)3000, girder_line->GetID());
			Assert::AreEqual((IDType)102, girder_line->GetLayoutLineID());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::Start).get());
			Assert::IsNotNull(girder_line->GetPierLine(EndType::End).get());
			Assert::AreEqual((IDType)100, girder_line->GetPierLine(EndType::Start)->GetID());
			Assert::AreEqual((IDType)300, girder_line->GetPierLine(EndType::End)->GetID());
			Assert::AreEqual(197.0, girder_line->GetGirderLength(), 0.00001);
			Assert::AreEqual(195.0, girder_line->GetSpanLength(), 0.00001);
			Assert::AreEqual(200.0, girder_line->GetLayoutLength(), 0.00001);
			Assert::IsTrue(Point2d(80.710678118654769, 80.710678118654769) == girder_line->GetPierPoint(EndType::Start));
			Assert::IsTrue(Point2d(222.13203435596432, 222.13203435596432) == girder_line->GetPierPoint(EndType::End));
			Assert::IsTrue(Point2d(82.478445071621138, 82.478445071621138) == girder_line->GetBearingPoint(EndType::Start));
			Assert::IsTrue(Point2d(220.36426740299794, 220.36426740299797) == girder_line->GetBearingPoint(EndType::End));
			Assert::IsTrue(Point2d(81.771338290434585, 81.771338290434585) == girder_line->GetEndPoint(EndType::Start));
			Assert::IsTrue(Point2d(221.07137418418449, 221.07137418418452) == girder_line->GetEndPoint(EndType::End));
			Assert::IsNotNull(girder_line->GetPath().get());
			Assert::IsTrue(Direction(M_PI / 4) == girder_line->GetDirection());
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::Start), 0.00001);
			Assert::AreEqual(2.5, girder_line->GetBearingOffset(EndType::End), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::Start), 0.00001);
			Assert::AreEqual(1.0, girder_line->GetEndDistance(EndType::End), 0.00001);
		}
	};
}
