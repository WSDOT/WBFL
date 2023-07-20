#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestAlignmentOffsetLayoutLineFactory)
	{
	public:
		
		TEST_METHOD(Test)
		{
			auto alignment = CreateStraightAlignment(0, 0, 0, 0);
			auto bridge = BridgeFramingGeometry::Create();
			bridge->AddAlignment(999, alignment);
			bridge->SetBridgeAlignmentID(999);

			AlignmentOffsetLayoutLineFactory factory(999, 1, 2, 5, -10, 5.0);
			Assert::AreEqual((IDType)999, factory.GetAlignmentID());
			Assert::AreEqual((IDType)1, factory.GetLayoutLineID());
			Assert::AreEqual((IDType)2, factory.GetLayoutLineIDIncrement());
			Assert::AreEqual((IndexType)5, factory.GetLayoutLineCount());
			Assert::AreEqual(-10.0, factory.GetOffset());
			Assert::AreEqual(5.0, factory.GetOffsetIncrement());

			auto layout_lines = factory.Create(bridge);
			Assert::AreEqual((size_t)5, layout_lines.size());

			Assert::AreEqual((IDType)1, layout_lines[0].first);
			Assert::IsTrue(Point2d(0, 10.0) == layout_lines[0].second->GetStartPoint());
			Assert::IsTrue(Point2d(100, 10.0) == layout_lines[0].second->GetEndPoint());

			Assert::AreEqual((IDType)3, layout_lines[1].first);
			Assert::IsTrue(Point2d(0, 5.0) == layout_lines[1].second->GetStartPoint());
			Assert::IsTrue(Point2d(100, 5.0) == layout_lines[1].second->GetEndPoint());

			Assert::AreEqual((IDType)5, layout_lines[2].first);
			Assert::IsTrue(Point2d(0, 0.0) == layout_lines[2].second->GetStartPoint());
			Assert::IsTrue(Point2d(100, 0.0) == layout_lines[2].second->GetEndPoint());

			Assert::AreEqual((IDType)7, layout_lines[3].first);
			Assert::IsTrue(Point2d(0, -5.0) == layout_lines[3].second->GetStartPoint());
			Assert::IsTrue(Point2d(100, -5.0) == layout_lines[3].second->GetEndPoint());

			Assert::AreEqual((IDType)9, layout_lines[4].first);
			Assert::IsTrue(Point2d(0, -10.0) == layout_lines[4].second->GetStartPoint());
			Assert::IsTrue(Point2d(100, -10.0) == layout_lines[4].second->GetEndPoint());
		}
	};
}
