#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestPrimitives)
	{
	public:
		TEST_METHOD(TestSize2d)
		{
         const Size2d s0_0(0, 0), s1_1(1, 1), s0_1(0, 1), s1_4(1, 4), s0_3(0, 3),
            sn3_0(-3, 0), s3_0(3, 0);
         Size2d st1, st2;
         Point2d pt1;

         // add, subtract, ==
         Assert::IsTrue(st1 == s0_0);
         st1 = s1_1 + s1_4;
         st2 = st1;
         Assert::IsTrue(st1 == Size2d(2, 5));
         st1 -= s1_1;
         Assert::IsTrue(st1 == s1_4);
         st1 = st2 - s1_4;
         Assert::IsTrue(st1 == s1_1);
         st1 += sn3_0;
         Assert::IsTrue(st1 == Size2d(-2, 1));
         st1 = -s1_1 + s1_1;
         Assert::IsTrue(st1 == s0_0);

         // magnitude
         st1 = Size2d(4, 4);
         Assert::IsTrue(st1.Magnitude() == sqrt(32.));
         Assert::IsTrue(s0_3.Magnitude() == 3);
      }

		TEST_METHOD(TestPoint2d)
		{
         const Point2d p0_0(0, 0), p1_1(1, 1), p0_1(0, 1), p1_4(1, 4), p0_3(0, 3),
            pn3_0(-3, 0), p3_0(3, 0);
         Point2d pt1, pt2;
         Size2d st;

         // add, subtract, ==
         Assert::IsTrue(pt1 == p0_0);
         pt1 = p1_1 + p1_4;
         pt2 = pt1;
         Assert::IsTrue(pt1 == Point2d(2, 5));
         pt1 -= p1_1;
         Assert::IsTrue(pt1 == p1_4);
         pt1 = p0_0;
         pt1 += pn3_0;
         Assert::IsTrue(pt1 == pn3_0);

         Assert::IsTrue((Point2d(10, 10) - Point2d(5, 5)) == Size2d(5, 5));

         // distance, magnitude
         pt1 = Point2d(4, 4);
         Assert::IsTrue(pt1.Magnitude() == sqrt(32.));
         Assert::IsTrue(pt1.Distance(p0_0) == sqrt(32.));
         Assert::IsTrue(p1_4.Distance(pn3_0) == sqrt(32.));

         // move, offset, rotate
         pt1.Move(-3, 0);
         Assert::IsTrue(pt1 == pn3_0);
         pt1.Move(p1_4);
         Assert::IsTrue(pt1 == p1_4);
         pt1.Offset(-1, -4);
         Assert::IsTrue(pt1 == p0_0);
         pt1.Offset(Size2d(0, 3));
         Assert::IsTrue(pt1 == p0_3);
         pt1 = p1_1.OffsetBy(0, 3);
         Assert::IsTrue(pt1 == p1_4);
         pt1 = pt1.OffsetBy(Size2d(-1, -4));
         Assert::IsTrue(pt1 == p0_0);
         pt1 = p0_0.RotateBy(p0_0, 1);
         Assert::IsTrue(pt1 == p0_0);
         pt1 = p1_1.RotateBy(p0_0, atan(1.));
         Assert::IsTrue(pt1 == Point2d(0, sqrt(2.)));
         pt1 = pn3_0;
         pt1.Rotate(p3_0, -2 * atan(1.));
         Assert::IsTrue(pt1 == Point2d(3, 6));
      }

		TEST_METHOD(TestRect2d)
		{
         const Point2d pn2_n4(-2, -4), p4_n1(4, -1), p1_2(1, 2), pn4_n2(-4, -2);
         const Rect2d r1(pn4_n2, p1_2), r1u(p1_2, pn4_n2);
         const Rect2d r2(-2, -4, 4, -1);

         Point2d pt1, pt2;
         Rect2d rt1, rt2;

         // Area & Inquiry
         Assert::IsTrue(rt1.IsNull());
         Assert::IsTrue(!r1.IsNull());
         Assert::IsTrue(r1.Bottom() == -2);
         Assert::IsTrue(r1.Right() == 1);
         Assert::IsTrue(r1.Top() == 2);
         Assert::IsTrue(r1.Left() == -4);
         Assert::IsTrue(r1.Width() == 5);
         Assert::IsTrue(r1.Height() == 4);
         Assert::IsTrue(rt1.Area() == 0);
         Assert::IsTrue(r1.Area() == 20);
         Assert::IsTrue(!r1u.IsNormalized());
         Assert::IsTrue(r1.IsNormalized());
         rt1 = r1u.Normalized();
         Assert::IsTrue(r1 == rt1);

         // location points
         pt1 = r2.Center();
         Assert::IsTrue(pt1 == Point2d(1, -2.5));
         pt1 = r2.LeftCenter();
         Assert::IsTrue(pt1 == Point2d(-2, -2.5));
         pt1 = r2.BottomCenter();
         Assert::IsTrue(pt1 == Point2d(1, -4));
         pt1 = r2.RightCenter();
         Assert::IsTrue(pt1 == Point2d(4, -2.5));
         pt1 = r2.TopCenter();
         Assert::IsTrue(pt1 == Point2d(1, -1));

         // set, move
         rt1 = r2.MovedTo(-2, -4);
         Assert::IsTrue(rt1 != r2);
         rt1.SetWH(pn4_n2, Size2d(5, 4));
         Assert::IsTrue(rt1 == r1);
         rt1.SetWH(-2, -4, 6, 3);
         Assert::IsTrue(rt1 == r2);
         rt1 = r2;
         rt1.MoveTo(12, 12);
         rt2 = r2.MovedTo(12, 12);
         Assert::IsTrue(rt1 == rt2);
         rt1 = r2.OffsetBy(14, 16);
         Assert::IsTrue(rt1 == rt2);
         rt2 = r2;
         rt2.Offset(14, 16);
         Assert::IsTrue(rt1 == rt2);
         rt1.SetEmpty();
         rt2.SetNull();
         Assert::IsTrue(rt1 == rt2);
         Assert::IsTrue(rt1.IsNull());

         // contains, intersect, union
         Assert::IsTrue(r2.Touches(r1));
         Assert::IsTrue(!r2.Contains(r1));
         Assert::IsTrue(r2.Contains(pn2_n4));
         Assert::IsTrue(r2.Contains(Point2d(1, -2)));
         Assert::IsTrue(!r2.Contains(Point2d(5, -2)));

         rt1 = r1.IntersectionBy(r2);
         rt2 = r2;
         rt2.Intersection(r1);
         Assert::IsTrue(rt1 == rt2);
         Assert::IsTrue(rt1.Area() == 3);
         rt1 = r1.UnionBy(r2);
         rt2 = r2;
         rt2.Union(r1);
         Assert::IsTrue(rt1 == rt2);
         Assert::IsTrue(rt1.Area() == 48);

         // bound points
         Rect2d br = r2.BoundPointBy(Point2d(0, -2));
         Assert::IsTrue(br == r2);
         br = r2.BoundPointBy(Point2d(10, 10));//  -2,-4,4,-1);
         Assert::IsTrue(br == Rect2d(-2, -4, 10, 10));
         br = br.BoundPointBy(Point2d(-10, -10));
         Assert::IsTrue(br == Rect2d(-10, -10, 10, 10));

         // test derived properties
         Float64 left, right, top, bottom;
         left = 10;
         top = 10;
         right = 20;
         bottom = 5;
         Rect2d r(left, bottom, right, top);
         Assert::IsTrue(IsEqual(r.Width(), right - left));
         Assert::IsTrue(IsEqual(r.Height(), top - bottom));
         Assert::IsTrue(IsEqual(r.Area(), (right - left) * (top - bottom)));

         // Points
         // make this an easy rectangle
         r.Set(-10, -10, 10, 10);
         Assert::IsTrue(r.TopLeft() == Point2d(-10, 10));
         Assert::IsTrue(r.TopCenter() == Point2d(0, 10));
         Assert::IsTrue(r.TopRight() == Point2d(10, 10));
         Assert::IsTrue(r.LeftCenter() == Point2d(-10, 0));
         Assert::IsTrue(r.Center() == Point2d(0, 0));
         Assert::IsTrue(r.RightCenter() == Point2d(10, 0));
         Assert::IsTrue(r.BottomLeft() == Point2d(-10, -10));
         Assert::IsTrue(r.BottomCenter() == Point2d(0, -10));
         Assert::IsTrue(r.BottomRight() == Point2d(10, -10));

         // Contains
         r.Set(0, 0, 10, 10);
         Assert::IsTrue(r.Contains(Point2d(5, 5)) == true);
         Assert::IsTrue(r.Contains(Point2d(50, 50)) == false);
         // Test a point a the middle of each side and at each corner
         // (points on bottom and left sides are contained)
         Assert::IsTrue(r.Contains(Point2d(0, 0)) == true);
         Assert::IsTrue(r.Contains(Point2d(5, 0)) == true);
         Assert::IsTrue(r.Contains(Point2d(10, 0)) == false);
         Assert::IsTrue(r.Contains(Point2d(10, 5)) == false);
         Assert::IsTrue(r.Contains(Point2d(10, 10)) == false);
         Assert::IsTrue(r.Contains(Point2d(5, 10)) == false);
         Assert::IsTrue(r.Contains(Point2d(0, 10)) == false);
         Assert::IsTrue(r.Contains(Point2d(0, 5)) == true);

         // Contains Rect and Touches
         r.Set(0, 0, 10, 10);
         Rect2d r_(20, 0, 30, 10);
         Assert::IsTrue(r.Contains(r_) == false);
         Assert::IsTrue(r.Touches(r_) == false);

         // make both rects the same
         r_ = r;
         Assert::IsTrue(r.Contains(r_) == true);
         Assert::IsTrue(r.Touches(r_) == true);

         r_.Set(2., 2., 8., 8.);
         Assert::IsTrue(r.Contains(r_) == true);
         Assert::IsTrue(r.Touches(r_) == true);

         // covers top left corner
         r_.Set(-2, 2, 8, 12);
         Assert::IsTrue(r.Contains(r_) == false);
         Assert::IsTrue(r.Touches(r_) == true);

         // covers bottom left corner
         r_.Set(2, -2, 12, 8);
         Assert::IsTrue(r.Contains(r_) == false);
         Assert::IsTrue(r.Touches(r_) == true);

         // Normalize & IsNormalized
         r.Set(100, 0, 0, 100);
         Assert::IsTrue(r.IsNormalized() == false);
         r.Normalize();
         Assert::IsTrue(r.IsNormalized() == true);
         Assert::IsTrue(IsEqual(r.Left(), 0.0));
         Assert::IsTrue(IsEqual(r.Right(), 100.0));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.0));
         Assert::IsTrue(IsEqual(r.Top(), 100.0));

         r.Set(0, 100, 100, 0);
         Assert::IsTrue(r.IsNormalized() == false);
         r.Normalize();
         Assert::IsTrue(r.IsNormalized() == true);
         Assert::IsTrue(IsEqual(r.Left(), 0.0));
         Assert::IsTrue(IsEqual(r.Right(), 100.0));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.0));
         Assert::IsTrue(IsEqual(r.Top(), 100.0));

         r.Set(0, 100, 100, 0);
         Assert::IsTrue(r.IsNormalized() == false);
         r.Normalize();
         Assert::IsTrue(r.IsNormalized() == true);
         Assert::IsTrue(IsEqual(r.Left(), 0.0));
         Assert::IsTrue(IsEqual(r.Right(), 100.0));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.0));
         Assert::IsTrue(IsEqual(r.Top(), 100.0));

         // Null/Empty
         r.Set(0, 0, 100, 100);
         Assert::IsTrue(r.IsNull() == false);
         r.SetNull();
         Assert::IsTrue(r.IsNull() == true);
         Assert::IsTrue(IsEqual(r.Left(), 0.0));
         Assert::IsTrue(IsEqual(r.Right(), 0.0));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.0));
         Assert::IsTrue(IsEqual(r.Top(), 0.0));

         //
         // Test the Union method
         //
         r.Set(0, 0, 10, 10);

         // Rect2 is to the left
         r_.Set(20, 0, 30, 10);
         r.Union(r_);
         Assert::IsTrue(IsEqual(r.Left(), 0.00));
         Assert::IsTrue(IsEqual(r.Right(), 30.00));
         Assert::IsTrue(IsEqual(r.Top(), 10.00));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.00));

         // reset Rect
         r.Set(0, 0, 10, 10);

         //Rect2 is to the right
         r_.Set(-30, 0, -20, 10);

         r.Union(r_);
         Assert::IsTrue(IsEqual(r.Left(), -30.00));
         Assert::IsTrue(IsEqual(r.Right(), 10.00));
         Assert::IsTrue(IsEqual(r.Top(), 10.00));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.00));

         // reset Rect
         r.Set(0, 0, 10, 10);

         //Rect2 is above
         r_.Set(0, 20, 10, 30);

         r.Union(r_);
         Assert::IsTrue(IsEqual(r.Left(), 0.00));
         Assert::IsTrue(IsEqual(r.Right(), 10.00));
         Assert::IsTrue(IsEqual(r.Top(), 30.00));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.00));

         // reset Rect
         r.Set(0, 0, 10, 10);

         //Rect2 is below
         r_.Set(0, -30, 10, -20);

         r.Union(r_);
         Assert::IsTrue(IsEqual(r.Left(), 0.00));
         Assert::IsTrue(IsEqual(r.Right(), 10.00));
         Assert::IsTrue(IsEqual(r.Top(), 10.00));
         Assert::IsTrue(IsEqual(r.Bottom(), -30.00));

         // pRect is not normalized
         r.Set(10, 0, 0, 10);

         r_.Set(10, 10, 20, 20);

         try
         {
            r.Union(r_);
            Assert::IsTrue(false); // exception should throw and skip this line
         }
         catch (...)
         {
            Assert::IsTrue(true);
            //TRY_TEST(pRect->Union(pRect2), WBFL_GEOMETRY_E_NOTNORMALIZED);
         }

         // pRect2 is not normalized
         r.Set(0, 0, 10, 10);
         r_.Set(20, 10, 10, 20);
         try
         {
            r.Union(r_);
            Assert::IsTrue(false); // exception should throw and skip this line
         }
         catch (...)
         {
            Assert::IsTrue(true);
            //TRY_TEST(pRect->Union(pRect2), WBFL_GEOMETRY_E_NOTNORMALIZED);
         }

         //
         // Test the UnionBy method
         //
         Rect2d r_union;

         r.Set(0, 0, 10, 10);

         // Rect2 is to the left
         r_.Set(20, 0, 30, 10);

         r_union = r.UnionBy(r_);
         Assert::IsTrue(IsEqual(r_union.Left(), 0.00));
         Assert::IsTrue(IsEqual(r_union.Right(), 30.00));
         Assert::IsTrue(IsEqual(r_union.Top(), 10.00));
         Assert::IsTrue(IsEqual(r_union.Bottom(), 0.00));

         //Rect2 is to the right
         r_.Set(-30, 0, -20, 10);

         r_union = r.UnionBy(r_);
         Assert::IsTrue(IsEqual(r_union.Left(), -30.00));
         Assert::IsTrue(IsEqual(r_union.Right(), 10.00));
         Assert::IsTrue(IsEqual(r_union.Top(), 10.00));
         Assert::IsTrue(IsEqual(r_union.Bottom(), 0.00));

         //Rect2 is above
         r_.Set(0, 20, 10, 30);

         r_union = r.UnionBy(r_);
         Assert::IsTrue(IsEqual(r_union.Left(), 0.00));
         Assert::IsTrue(IsEqual(r_union.Right(), 10.00));
         Assert::IsTrue(IsEqual(r_union.Top(), 30.00));
         Assert::IsTrue(IsEqual(r_union.Bottom(), 0.00));

         //Rect2 is below
         r_.Set(0, -30, 10, -20);

         r_union = r.UnionBy(r_);
         Assert::IsTrue(IsEqual(r_union.Left(), 0.00));
         Assert::IsTrue(IsEqual(r_union.Right(), 10.00));
         Assert::IsTrue(IsEqual(r_union.Top(), 10.00));
         Assert::IsTrue(IsEqual(r_union.Bottom(), -30.00));

         // pRect is not normalized
         r.Set(10, 0, 0, 10);
         r_.Set(10, 10, 20, 20);

         try
         {
            r_union = r.UnionBy(r_);
            Assert::IsTrue(false);
         }
         catch (...)
         {
            Assert::IsTrue(true);
         }

         // pRect2 is not normalized
         r.Set(0, 0, 10, 10);
         r_.Set(20, 10, 10, 20);

         try
         {
            r_union = r.UnionBy(r_);
            Assert::IsTrue(false);
         }
         catch (...)
         {
            Assert::IsTrue(true);
         }

         //
         // Test BoundPoint and BoundPointEx
         //
         r.Set(0, 0, 10, 10);
         Point2d p(20, 20);

         r.BoundPoint(p);
         r.BoundPoint(-10, -10);

         Assert::IsTrue(IsEqual(r.Left(), -10.00));
         Assert::IsTrue(IsEqual(r.Right(), 20.00));
         Assert::IsTrue(IsEqual(r.Top(), 20.00));
         Assert::IsTrue(IsEqual(r.Bottom(), -10.00));

         // pRect is not normalized
         r.Set(10, 0, 0, 10);
         try
         {
            r.BoundPoint(-10, -10);
            Assert::IsTrue(false);
         }
         catch (...)
         {
            Assert::IsTrue(true);
         }

         // make sure pRect didn't change
         Assert::IsTrue(IsEqual(r.Left(), 10.00));
         Assert::IsTrue(IsEqual(r.Right(), 0.00));
         Assert::IsTrue(IsEqual(r.Top(), 10.00));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.00));

         //
         // Test Inflate and InflateEx
         //
         r.Set(0, 0, 10, 10);

         Size2d inflate(10, 10);

         r.Inflate(inflate);
         Assert::IsTrue(IsEqual(r.Left(), -10.00));
         Assert::IsTrue(IsEqual(r.Right(), 20.00));
         Assert::IsTrue(IsEqual(r.Top(), 20.00));
         Assert::IsTrue(IsEqual(r.Bottom(), -10.00));

         r.Inflate(-10, -10);
         Assert::IsTrue(IsEqual(r.Left(), 0.00));
         Assert::IsTrue(IsEqual(r.Right(), 10.00));
         Assert::IsTrue(IsEqual(r.Top(), 10.00));
         Assert::IsTrue(IsEqual(r.Bottom(), 0.00));

         //
         // Test Size method
         //
         r.Set(0, 0, 10, 10);

         Size2d size = r.Size();
         Assert::IsTrue(IsEqual(size.Dx(), 10.0));
         Assert::IsTrue(IsEqual(size.Dy(), 10.0));

         r.Set(10, 10, 0, 0);
         size = r.Size();
         Assert::IsTrue(IsEqual(size.Dx(), -10.0));
         Assert::IsTrue(IsEqual(size.Dy(), -10.0));

         //
         // Test Offset and OffsetEx
         //
         r.Set(0, 0, 10, 10);

         Size2d offset(10, 10);
         r.Offset(offset);
         Assert::IsTrue(IsEqual(r.Left(), 10.00));
         Assert::IsTrue(IsEqual(r.Right(), 20.00));
         Assert::IsTrue(IsEqual(r.Top(), 20.00));
         Assert::IsTrue(IsEqual(r.Bottom(), 10.00));

         r.Offset(20, 20);
         Assert::IsTrue(IsEqual(r.Left(), 30.00));
         Assert::IsTrue(IsEqual(r.Right(), 40.00));
         Assert::IsTrue(IsEqual(r.Top(), 40.00));
         Assert::IsTrue(IsEqual(r.Bottom(), 30.00));

         //
         // Test Intersect
         //
         r.Set(0, 0, 10, 10);
         r_.Set(25, 5, 35, 15);

         Rect2d intersect = r.IntersectionBy(r_);
         Assert::IsTrue(IsEqual(intersect.Left(), 0.00));
         Assert::IsTrue(IsEqual(intersect.Right(), 0.00));
         Assert::IsTrue(IsEqual(intersect.Top(), 0.00));
         Assert::IsTrue(IsEqual(intersect.Bottom(), 0.00));

         // Basic intersection
         r_.Set(5, 5, 15, 15);
         intersect = r.IntersectionBy(r_);
         Assert::IsTrue(IsEqual(intersect.Left(), 5.00));
         Assert::IsTrue(IsEqual(intersect.Right(), 10.00));
         Assert::IsTrue(IsEqual(intersect.Top(), 10.00));
         Assert::IsTrue(IsEqual(intersect.Bottom(), 5.00));

         // pRect is not normalized
         r.Set(10, 0, 0, 10);
         r_.Set(5, 5, 15, 15);
         try
         {
            r_union = r.Intersection(r_);
            Assert::IsTrue(false);
         }
         catch (...)
         {
            Assert::IsTrue(true);
         }

         // pRect2 is not normalized
         r.Set(0, 0, 10, 10);
         r_.Set(15, 5, 5, 15);
         try
         {
            r_union = r.Intersection(r_);
            Assert::IsTrue(false);
         }
         catch (...)
         {
            Assert::IsTrue(true);
         }
      }
	};
}
