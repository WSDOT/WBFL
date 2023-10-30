#include "pch.h"
#include "CppUnitTest.h"
#include "TestHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;
using namespace WBFL::Geometry;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestSinglePierLineFactory)
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

			auto vPierlines = factory.Create(bridge);
			Assert::AreEqual((size_t)1, vPierlines.size());

			auto pierline = vPierlines.front();
			Assert::AreEqual((IndexType)INVALID_INDEX, pierline->GetIndex());
			Assert::AreEqual((IDType)100, pierline->GetID());
			Assert::AreEqual((IDType)999, pierline->GetAlignmentID());
			Assert::IsTrue(Station(300.0) == pierline->GetStation());
			Assert::IsTrue(Direction(M_PI / 4) == pierline->GetDirection());
			Assert::IsTrue(Direction(7*M_PI / 4) == pierline->GetNormal());
			Assert::IsTrue(Angle(-M_PI/4) == pierline->GetSkewAngle());
			Assert::IsTrue(ConnectionGeometry() == pierline->GetConnectionGeometry(PierFaceType::Back));
			Assert::IsTrue(ConnectionGeometry() == pierline->GetConnectionGeometry(PierFaceType::Ahead));
			Assert::IsTrue(Point2d(300.0, 0.0) == pierline->GetAlignmentPoint());
			Assert::IsTrue(Point2d(300.0, 0.0) == pierline->GetBridgeLinePoint());
			Assert::IsTrue(Point2d(229.28932188134524, -70.710678118654755) == pierline->GetLeftPoint());
			Assert::IsTrue(Point2d(-194.97474683058329, -494.97474683058329) == pierline->GetRightPoint());
			Assert::IsTrue(Line2d(-212.13203435596427, Vector2d(Size2d(-0.70710678118654757, 0.70710678118654757))) == pierline->GetCenterLine());
			Assert::AreEqual(0.0, pierline->GetBearingOffset(PierFaceType::Ahead, M_PI / 4));
		}
	};
}
