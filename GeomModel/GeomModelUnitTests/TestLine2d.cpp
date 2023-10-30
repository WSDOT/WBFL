#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestLine2d)
	{
	public:

      TEST_METHOD(GetSlope)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0);
         const Line2d up(p0_0, p0_1);
         const Line2d down(p0_1, p0_0), left(p0_1, p1_1);
         const Line2d at45(pn3_0, p1_4);
         const Line2d atn45(p1_4, pn3_0);

         constexpr auto infinity = std::numeric_limits<Float64>::infinity();

         Float64 val = up.GetSlope();
         Assert::IsTrue(val == infinity);
         val = down.GetSlope();
         Assert::IsTrue(val == -infinity);
         val = at45.GetSlope();
         Assert::IsTrue(IsEqual(val, 1.));
         val = atn45.GetSlope();
         Assert::IsTrue(IsEqual(val, 1.));
         Line2d ltemp1(p1_4, p4_1);
         val = ltemp1.GetSlope();
         Assert::IsTrue(IsEqual(val, -1.));
         ltemp1 = Line2d(p0_0, pn1_0);
         val = ltemp1.GetSlope();
         Assert::IsTrue(IsEqual(val, 0.));

      }

      TEST_METHOD(Contains)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0);
         const Line2d up(p0_0, p0_1);
         const Line2d down(p0_1, p0_0), left(p0_1, p1_1);
         const Line2d at45(pn3_0, p1_4);
         const Line2d atn45(p1_4, pn3_0);

         Assert::IsTrue(at45.ContainsPoint(p1_4));
         Assert::IsTrue(atn45.ContainsPoint(p1_4));
         Assert::IsTrue(at45.ContainsPoint(pn1_2));
         Assert::IsTrue(atn45.ContainsPoint(pn1_2));
         Assert::IsTrue(up.ContainsPoint(Point2d(0, 456)));
         Assert::IsTrue(up.ContainsPoint(Point2d(0, -456)));
         Assert::IsTrue(left.ContainsPoint(Point2d(110, 1)));
         Assert::IsTrue(left.ContainsPoint(Point2d(-110, 1)));

      }

      TEST_METHOD(PointOnLineNearest)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0);
         const Line2d up(p0_0, p0_1);
         const Line2d down(p0_1, p0_0), left(p0_1, p1_1);
         const Line2d at45(pn3_0, p1_4);
         const Line2d atn45(p1_4, pn3_0);

         // point nearest on line
         Point2d ptest = at45.PointOnLineNearest(p4_1);
         Assert::IsTrue(ptest == p1_4);
         ptest = at45.PointOnLineNearest(pn1_2);
         Assert::IsTrue(ptest == pn1_2);
         ptest = atn45.PointOnLineNearest(p4_1);
         Assert::IsTrue(ptest == p1_4);
         ptest = up.PointOnLineNearest(p4_1);
         Assert::IsTrue(ptest == Point2d(0, 1));
      }

      TEST_METHOD(Offset)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0);
         const Line2d up(p0_0, p0_1);
         const Line2d down(p0_1, p0_0), left(p0_1, p1_1);
         const Line2d at45(pn3_0, p1_4);
         const Line2d atn45(p1_4, pn3_0);

         auto ltemp1 = at45.OffsetBy(-1, 0);
         auto ptest = ltemp1.PointOnLineNearest(p1_1);
         Assert::IsTrue(ptest == Point2d(-1, 3));
         ltemp1 = at45.OffsetBy(1, 0);
         ptest = ltemp1.PointOnLineNearest(p1_1);
         Assert::IsTrue(ptest == Point2d(0, 2));
         ltemp1 = at45.OffsetBy(1, 1);  // offset in direction of line
         Assert::IsTrue(ltemp1 == at45);
         ltemp1 = up.OffsetBy(1, 1);
         Assert::IsTrue(ltemp1 == Line2d(Point2d(1, 0), Point2d(1, 1)));
      }

      TEST_METHOD(Normal)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0);
         const Line2d up(p0_0, p0_1);
         const Line2d down(p0_1, p0_0), left(p0_1, p1_1);
         const Line2d at45(pn3_0, p1_4);
         const Line2d atn45(p1_4, pn3_0);

         Line2d at315(p4_1, p1_4);
         auto ltemp1 = at45.Normal(p4_1);
         Assert::IsTrue(ltemp1 == at315);
         auto ptest = ltemp1.PointOnLineNearest(pn3_0);
         Assert::IsTrue(ptest == p1_4);
         auto ltemp2 = at45.Normal(p1_4);  // point on line
         Assert::IsTrue(ltemp1 == at315);
         ltemp1 = up.Normal(p4_1);
         ptest = ltemp1.PointOnLineNearest(pn3_0);
         Assert::IsTrue(ptest == Point2d(-3, 1));
         ltemp1 = left.Normal(pn1_2);
         ptest = ltemp1.PointOnLineNearest(pn3_0);
         Assert::IsTrue(ptest == Point2d(-1, 0));
      }

      TEST_METHOD(Parallel)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0);
         const Line2d up(p0_0, p0_1);
         const Line2d down(p0_1, p0_0), left(p0_1, p1_1);
         const Line2d at45(pn3_0, p1_4);
         const Line2d atn45(p1_4, pn3_0);

         // parallel
         auto ltemp1 = at45.Parallel(sqrt(2.), Line2d::Side::Left);
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-3, 2)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-5, 0)));
         auto ltemp2 = atn45.Parallel(sqrt(2.), Line2d::Side::Right);
         Assert::IsTrue(ltemp2.ContainsPoint(Point2d(-3, 2)));
         Assert::IsTrue(ltemp2.ContainsPoint(Point2d(-5, 0)));

         // lines are collinear but have different direction and are hence not equal
         Assert::IsTrue(ltemp2 != ltemp1);
         ltemp1 = at45.Parallel(1.5 * sqrt(2.), Line2d::Side::Right);

         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(0, 0)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(2, 2)));
         ltemp1 = up.Parallel(1, Line2d::Side::Left);
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-1, 0)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-1, 2)));
         ltemp1 = left.Parallel(2, Line2d::Side::Left);
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(0, 3)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-1, 3)));
         ltemp1 = at45.Parallel(Point2d(-3, 2));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-3, 2)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-5, 0)));
         ltemp1 = at45.Parallel(Point2d(0, 0));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(2, 2)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-5, -5)));
         ltemp1 = down.Parallel(Point2d(5, 5));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(5, 2)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(5, -5)));
         ltemp1 = left.Parallel(Point2d(0, 122));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(2, 122)));
         Assert::IsTrue(ltemp1.ContainsPoint(Point2d(-5, 122)));

         // rotate
         ltemp1 = left.RotateBy(Point2d(-2, 1), atan(1.));
         Assert::IsTrue(ltemp1 == at45);
         ltemp1 = up.RotateBy(Point2d(0, 3), -atan(1.));
         Assert::IsTrue(ltemp1 == at45);
         ltemp1 = left.RotateBy(Point2d(-2, 1), 5 * atan(1.));
         Assert::IsTrue(ltemp1 == atn45);
      }

      TEST_METHOD(Implicit_Explicity_Forms)
      {
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), pn3_0(-3, 0);
         const Point2d p4_1(4, 1), pn1_2(-1, 2), pn1_0(-1, 0);
         const Line2d up(p0_0, p0_1);
         const Line2d down(p0_1, p0_0), left(p0_1, p1_1);
         const Line2d at45(pn3_0, p1_4);
         const Line2d atn45(p1_4, pn3_0);

         Vector2d ve(Size2d(1, 1)), ve2;
         Point2d  pe(0, 3), pe2;
         Line2d ex45(pe, ve);
         Assert::IsTrue(ex45 == at45);
         std::tie(pe, ve) = ex45.GetExplicit();
         std::tie(pe2, ve2) = at45.GetExplicit();
         Assert::IsTrue(ve == ve2 && pe == pe2);

         Float64 c1, c2;
         Vector2d vi, vi2;
         std::tie(c1, vi) = ex45.GetImplicit();
         std::tie(c2, vi2) = at45.GetImplicit();
         Assert::IsTrue(c1 == c2 && vi == vi2);

         // collinearity
         Assert::IsTrue(at45.IsColinear(at45));
         Assert::IsTrue(atn45.IsColinear(at45));
         Assert::IsTrue(!at45.IsColinear(up));

         // line segment constructor
         Line2d lsat45(pn3_0, p1_4);
         LineSegment2d sat45(pn3_0, p1_4);
         Line2d ssat45(sat45);
         Assert::IsTrue(lsat45 == ssat45);

         Line2d ltemp1(pn3_0, p1_4);
         Assert::IsTrue(ltemp1 == at45);
      }

      TEST_METHOD(ContainsPoint)
      {
         Point2d p1(-10, -10);
         Point2d p2(-50, 20);
         Line2d l1(p1, p2);
         Point2d p3(-30, 5);
         Point2d p4(0, 0);
         Assert::IsTrue(l1.ContainsPoint(p3));
         Assert::IsFalse(l1.ContainsPoint(p4));
      }

      TEST_METHOD(AreLinesColinear)
      {
         Point2d p1(5, 5);
         Point2d p2(15, 15);
         Point2d p3(25, 25);
         Point2d p4(35, 35);

         Line2d line(p1, p2);
         Line2d line2(p3, p4);
         Assert::IsTrue(line.IsColinear(line));
         Assert::IsTrue(line.IsColinear(line2));
         Assert::IsTrue(line2.IsColinear(line));

         line2.ThroughPoints(p4, p3); // Reverse l2
         Assert::IsTrue(line.IsColinear(line2));

         p4.Move(3, 4);
         line2.ThroughPoints(p3, p4);
         Assert::IsTrue(!line.IsColinear(line2));
      }
	};
}
