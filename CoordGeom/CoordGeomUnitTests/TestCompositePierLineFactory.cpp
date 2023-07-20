#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCompositePierLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			auto alignment = CreateStraightAlignment(0, 0, 0, 0);
			auto bridge = BridgeFramingGeometry::Create();
			bridge->AddAlignment(999, alignment);
			bridge->SetBridgeAlignmentID(999);

			SinglePierLineFactory factory(100, 999, 300, _T("N 45 E"), 600, 100, ConnectionGeometry(), ConnectionGeometry());
			Assert::AreEqual((IDType)100, factory.GetPierLineID());
			Assert::AreEqual((IDType)999, factory.GetAlignmentID());
			Assert::IsTrue(Station(300) == factory.GetStation());
			Assert::AreEqual(_T("N 45 E"), factory.GetDirection().c_str());
			Assert::AreEqual(600.0, factory.GetLength());
			Assert::AreEqual(100.0, factory.GetOffset());
			Assert::IsTrue(ConnectionGeometry() == factory.GetConnectionGeometry(PierFaceType::Back));
			Assert::IsTrue(ConnectionGeometry() == factory.GetConnectionGeometry(PierFaceType::Ahead));

			CompositePierLineFactory composite_factory;
			composite_factory.AddFactory(std::make_shared<SinglePierLineFactory>(factory));
			composite_factory.AddFactory(std::make_shared<SinglePierLineFactory>(factory));

			auto vPierlines = composite_factory.Create(bridge);
			Assert::AreEqual((size_t)2, vPierlines.size());
		}
	};
}
