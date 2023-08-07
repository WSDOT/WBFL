#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestArc)
	{
	public:

		std::pair<WBFL::Geometry::Arc, WBFL::Geometry::Arc> GetTestArcs()
		{
			return std::make_pair(
				WBFL::Geometry::Arc(Point2d(10, 0), Point2d(0, 0), Point2d(0, 10)),
			   WBFL::Geometry::Arc(Point2d(-5, -5), Point2d(0, 0), Point2d(-5, 5)));
		}
		
		TEST_METHOD(IsPointOnArc)
		{
			auto [a1, a2] = GetTestArcs();

			Assert::IsFalse(a1.IsPointOnArc(Point2d(-10, 0)));
			Assert::IsFalse(a1.IsPointOnArc(Point2d(0, -10)));
			Assert::IsTrue(a1.IsPointOnArc(Point2d(10, 0)));
			Assert::IsTrue(a1.IsPointOnArc(Point2d(0, 10)));

			Assert::IsTrue(a2.IsPointOnArc(Point2d(7.07106781187, 0)));
			Assert::IsFalse(a2.IsPointOnArc(Point2d(-7.07106781187, 0)));
		}

		TEST_METHOD(GetCentralAngle)
		{
			auto [a1, a2] = GetTestArcs();

			Assert::IsTrue(IsEqual(a1.GetCentralAngle(), PI_OVER_2));
			a1.Reverse();
			Assert::IsTrue(IsEqual(a1.GetCentralAngle(), 3 * PI_OVER_2));

			Assert::IsTrue(IsEqual(a2.GetCentralAngle(), 3 * PI_OVER_2));
			a2.Reverse();
			Assert::IsTrue(IsEqual(a2.GetCentralAngle(), PI_OVER_2));
		}

		TEST_METHOD(DivideArc)
		{
			WBFL::Geometry::Arc a3(Point2d(10, 0), Point2d(0, 0), Point2d(-10, 0));
			Assert::ExpectException<WBFL::Geometry::XGeometry>([&a3]() {a3.Divide(0); });

			auto points = a3.Divide(1);
			Assert::AreEqual(points.size(), (size_t)2);

			points = a3.Divide(4);
			Assert::AreEqual(points.size(), (size_t)5);
			Assert::IsTrue(points[0] == Point2d(10, 0));
			Assert::IsTrue(points[1] == Point2d(7.0710678, 7.0710678));
			Assert::IsTrue(points[2] == Point2d(0, 10));
			Assert::IsTrue(points[3] == Point2d(-7.0710678, 7.0710678));
			Assert::IsTrue(points[4] == Point2d(-10, 0));
		}
	};
}
