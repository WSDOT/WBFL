#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestLineSegment2d)
	{
	public:

      TEST_METHOD(Test)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), p0_3(0, 3), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0), p0_6(0, 6);
         const LineSegment2d up(p0_0, p0_6), down(p0_1, p0_0), left(p0_1, p4_1);
         const LineSegment2d at45(pn3_0, p1_4);
         const LineSegment2d atn45(p1_4, Size2d(-4, -4));
         LineSegment2d ltemp1, ltemp2;

         // get/set endpoints
         Assert::IsTrue(at45.GetEndPoint() == p1_4);
         Assert::IsTrue(at45.GetStartPoint() == pn3_0);
         ltemp1 = at45;
         ltemp1.SetEndPoint(pn1_0);
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-2, 0)));
         ltemp1.SetStartPoint(Point2d(1, -4));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(0, -2)));

         // Length
         Assert::IsTrue(up.Length() == 6);
         Assert::IsTrue(left.Length() == 4);
         Assert::IsTrue(at45.Length() == sqrt(32.));
         Assert::IsTrue(atn45.Length() == sqrt(32.));

         // ContainsPoint
         Assert::IsTrue(at45.ContainsPoint(p1_4));
         Assert::IsTrue(atn45.ContainsPoint(p0_3));
         Assert::IsTrue(at45.ContainsPoint(pn1_2));
         Assert::IsTrue(atn45.ContainsPoint(pn1_2));
         Assert::IsTrue(up.ContainsPoint(Point2d(0, .5)));
         Assert::IsTrue(up.ContainsPoint(p0_0));
         Assert::IsTrue(left.ContainsPoint(Point2d(.5, 1)));
         Assert::IsTrue(left.ContainsPoint(Point2d(0, 1)));

         Point2d p1(-10, -10);
         Point2d p2(-50, 20);
         LineSegment2d seg1(p1, p2);
         Point2d p3(-30, 5);
         Point2d p4(0, 0);
         Assert::IsTrue(seg1.ContainsPoint(p3, 1.0e-6));
         Assert::IsTrue(!seg1.ContainsPoint(p4, 1.0e-6));
         Assert::IsTrue(seg1.ContainsPoint(p1, 1.0e-6));
         Assert::IsTrue(seg1.ContainsPoint(p2, 1.0e-6));

         // offset - offsetby
         Point2d ptest;
         ltemp1 = at45.OffsetBy(-1, 0);
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-2, 2)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(0, 4)));
         ltemp2 = at45.OffsetBy(0, 1);
         Assert::IsTrue(ltemp1 != ltemp2); // should not be equal
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-2, 2)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(0, 4)));
         ltemp1 = at45.OffsetBy(1, 1);  // offset in direction of line
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(1, 4)));


         // rotate
         ltemp1 = left.RotateBy(Point2d(-2, 1), atan(1.));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(1, 4)));
         ltemp1 = up.RotateBy(Point2d(0, 3), -atan(1.));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(1, 4)));
         ltemp1 = left.RotateBy(Point2d(-2, 1), 5 * atan(1.));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-5, -2)));

         // divide
         std::vector<Point2d> points;
         std::vector<Point2d> correct_points;
         LineSegment2d div_line(Point2d(0, 0), Point2d(10, 10));
         points = div_line.Divide(2);
         correct_points.emplace_back(0, 0);
         correct_points.emplace_back(5, 5);
         correct_points.emplace_back(10, 10);
         Assert::IsTrue(points == correct_points);

         correct_points.clear();
         correct_points.emplace_back(0, 0);
         correct_points.emplace_back(-5, -5);
         correct_points.emplace_back(-10, -10);
         div_line.SetEndPoint(Point2d(-10, -10));
         points = div_line.Divide(2);
         Assert::IsTrue(points == correct_points);

         //
         // DivideLineSegment
         //
         p1.Move(10, 10);
         p2.Move(30, 30);
         seg1.SetStartPoint(p1);
         seg1.SetEndPoint(p2);
         points = seg1.Divide(1);
         Assert::IsTrue(points.size() == 2);

         points = seg1.Divide(4);
         Assert::IsTrue(points.size() == 5);

         Assert::IsTrue(points[0] == Point2d(10, 10));
         Assert::IsTrue(points[1] == Point2d(15, 15));
         Assert::IsTrue(points[2] == Point2d(20, 20));
         Assert::IsTrue(points[3] == Point2d(25, 25));
         Assert::IsTrue(points[4] == Point2d(30, 30));
      }
	};
}
