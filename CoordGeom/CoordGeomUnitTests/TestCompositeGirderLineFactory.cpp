#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCompositeGirderLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			CompositeGirderLineFactory composite_factory;

			std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
			ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
			piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
			piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());
			auto bridge = CreateBridgeGeometry(piers, true);

			SingleGirderLineFactory factory;
			factory.SetGirderLineID(1000);
			factory.SetLayoutLineID(100);
			factory.SetGirderLineType(GirderLineType::Chord);
			factory.SetPierID(EndType::Start, 100);
			factory.SetPierID(EndType::End, 200);
			factory.SetMeasurementType(EndType::Start, MeasurementType::NormalToItem);
			factory.SetMeasurementType(EndType::End, MeasurementType::NormalToItem);
			factory.SetMeasurementLocation(EndType::Start, MeasurementLocation::CenterlineBearing);
			factory.SetMeasurementLocation(EndType::End, MeasurementLocation::CenterlineBearing);

			composite_factory.AddFactory(std::make_shared<SingleGirderLineFactory>(factory));
			composite_factory.AddFactory(std::make_shared<SingleGirderLineFactory>(factory));
			auto girder_lines = composite_factory.Create(bridge);
			Assert::AreEqual((size_t)2, girder_lines.size());
			Assert::AreEqual((IDType)1000, girder_lines.front()->GetID());
			Assert::AreEqual((IDType)1000, girder_lines.back()->GetID());
		}
	};
}
