#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestPlane3d)
	{
	public:
		
		TEST_METHOD(XYPlane)
		{
			Plane3d plane;

			// XY Plane at Altitude = 10.0
			plane.ThroughAltitude(10.0);
			Assert::IsTrue(IsEqual(plane.GetZ(5, 5), 10.0));

			Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {plane.GetX(5, 5); });
			Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {plane.GetY(5, 5); });
		}

		TEST_METHOD(ThreePointConstruction)
		{
			Point3d p1(0, 0, 0), p2(0, 0, 10), p3(10, 10, 0);
			Plane3d plane(p1, p2, p3);

			Assert::IsTrue(IsEqual(plane.GetX(5, 5), 5.0));
			Assert::IsTrue(IsEqual(plane.GetY(5, 5), 5.0));
			Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {plane.GetZ(5, 5); });
		}

		TEST_METHOD(ThroughLine)
		{
         Line2d line; // Line on the X axis
         line.Rotate(Point2d(0, 0), PI_OVER_2); // Line is now in the pos Y direction
         Point3d p(10, 0, 10);
         Plane3d plane(line, p);

         Assert::IsTrue(IsEqual(plane.GetX(5, 5), 5.0));
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {plane.GetY(5, 5); });
         Assert::IsTrue(IsEqual(plane.GetZ(5, 5), 5.0));

         p.Move(0, 10, 0); // point is now on the line
			Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {plane.ThroughLine(line, p); });
      }

		TEST_METHOD(ArbitraryPlane)
		{
         Point3d p1(10, 0, 0);
         Point3d p2(0, 10, 0);
         Point3d p3(0, 0, 10);
         Plane3d plane;
         plane.ThroughPoints(p1, p2, p3);

         Assert::IsTrue(IsEqual(plane.GetX(5, 5), 0.0));
         Assert::IsTrue(IsEqual(plane.GetY(5, 5), 0.0));
         Assert::IsTrue(IsEqual(plane.GetZ(5, 5), 0.0));


         p1.Move(1, 0, 0);
         p2.Move(0, 1, 0);
         p3.Move(0, 0, 1);
         plane.ThroughPoints(p1, p2, p3);

         Point3d A(0, 0, 0);
         Point3d B(10, 10, 10);
         LineSegment3d seg(A, B);

         Point3d intersect = plane.LineSegmentIntersect(seg);
         Assert::IsTrue(intersect == Point3d(1. / 3., 1. / 3., 1. / 3.));

         B.Move(10, 10, 0);
         seg.ThroughPoints(A, B);
         intersect = plane.LineSegmentIntersect(seg);
         Assert::IsTrue(intersect == Point3d(0.5, 0.5, 0.0));

         B.Move(0, 10, 10);
         seg.ThroughPoints(A, B);
         intersect = plane.LineSegmentIntersect(seg);
         Assert::IsTrue(intersect == Point3d(0.0, 0.5, 0.5));

         B.Move(10, 0, 10);
         seg.ThroughPoints(A, B);
         intersect = plane.LineSegmentIntersect(seg);
         Assert::IsTrue(intersect == Point3d(0.5, 0.0, 0.5));

         // Parallel to YZ at X = 1
         p1.Move(1, 0, 0);
         p2.Move(1, 1, 0);
         p3.Move(1, 0, 1);
         plane.ThroughPoints(p1, p2, p3);

         B.Move(10, 0, 0);
         seg.ThroughPoints(A, B);
         intersect = plane.LineSegmentIntersect(seg);
         Assert::IsTrue(intersect == Point3d(1.0, 0.0, 0.0));

         // parallel to the plane
         B.Move(0, 10, 10);
         seg.ThroughPoints(A, B);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {plane.LineSegmentIntersect(seg); });

         // in the plane
         A.Move(1, 0, 0);
         B.Move(1, 10, 10);
         seg.ThroughPoints(A, B);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {plane.LineSegmentIntersect(seg); });

         p1.Move(1, -2, 0);
         p2.Move(3, 1, 4);
         p3.Move(0, -1, 2);
         plane.ThroughPoints(p1, p2, p3);
         auto v = plane.NormalVector();
         Assert::IsTrue(IsEqual(v.X(), 2.0));
         Assert::IsTrue(IsEqual(v.Y(), -8.0));
         Assert::IsTrue(IsEqual(v.Z(), 5.0));

         plane.Init(p1, v);
         Float64 a, b, c, d;
         std::tie(a, b, c, d) = plane.GetConstants();
         Assert::IsTrue(IsEqual(a, 2.0));
         Assert::IsTrue(IsEqual(b, -8.0));
         Assert::IsTrue(IsEqual(c, 5.0));
         Assert::IsTrue(IsEqual(d, -18.0));
      }
	};
}
