#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCompositeDiaphragmLineFactory)
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

			CompositeDiaphragmLineFactory composite_factory;
			composite_factory.AddFactory(std::make_shared<SingleDiaphragmLineFactory>(factory));
			composite_factory.AddFactory(std::make_shared<SingleDiaphragmLineFactory>(factory));

			auto vDiaphragmLines = composite_factory.Create(bridge);
			Assert::AreEqual((size_t)2, vDiaphragmLines.size());
		}
	};
}
