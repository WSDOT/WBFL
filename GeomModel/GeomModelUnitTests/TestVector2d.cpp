#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestVectorLine2d)
	{
	public:

      TEST_METHOD(Test)
      {
         // test all of the features of a vector

         Float64 pi = 4. * atan(1.);

         const Vector2d up(1, pi / 2), left(1, pi), down(1, 3 * pi / 2), right(1, 0);
         const Vector2d at45(Size2d(1, 1)), at135(Size2d(-1, 1)),
            at315(Size2d(1, -1)), at225(Size2d(-1, -1));

         Vector2d testvec1, testvec2;

         // size
         Size2d ts(2, 3);
         testvec1.SetSize(ts);
         Assert::IsTrue(ts == testvec1.GetSize());

         // dot product
         Float64 val = right.Dot(up);
         Assert::IsTrue(IsEqual(val, 0.));

         // add, subtract, reflection
         testvec1 = right + up;
         testvec2 = -left - down;
         Assert::IsTrue(testvec1 == at45);
         Assert::IsTrue(testvec1 == testvec2);

         // setmagnitude, length
         testvec1.SetMagnitude(4);
         val = testvec1.GetMagnitude();
         Assert::IsTrue(IsEqual(val, 4.0));

         // assignment, reflection, ==
         testvec1 = at45;
         testvec1.Reflect();
         Assert::IsTrue(testvec1 == at225);

         // Normal
         testvec1 = at315.Normal(Vector2d::Side::Left);
         Assert::IsTrue(testvec1 == at45);

         testvec1 = at315.Normal(Vector2d::Side::Right);
         Assert::IsTrue(testvec1 == at225);

         // Normalize
         testvec1 = at45.NormalizeBy();
         val = testvec1.GetMagnitude();
         Assert::IsTrue(IsEqual(val, 1., 1.0e-6));

         // Offset, OffsetBy
         testvec1 = at45.OffsetBy(21, 21);
         testvec2 = testvec1.Normal();
         val = at45.Dot(testvec2);
         Assert::IsTrue(val == 0);

         // Rotate, RotateBy
         testvec1 = right;
         testvec2 = testvec1.RotateBy(atan(1.));

         // scale, scaleby
         val = at45.GetMagnitude();
         testvec1 = at45.ScaleBy(4);
         Assert::IsTrue(IsEqual(4 * val, testvec1.GetMagnitude()));

         // projection.
         val = right.Projection(at315);
         Assert::IsTrue(IsEqual(val, sqrt(2.) / 2));

         //
         // Test Properties
         //
         Float64 x, y;
         x = -10.0;
         y = -20.0;
         Vector2d vec;
         vec.SetSize(x, y);
         Assert::IsTrue(IsEqual(x, vec.X()));
         Assert::IsTrue(IsEqual(y, vec.Y()));

         //
         // Test Size Property
         //
         auto size = vec.GetSize();
         Assert::IsTrue(IsEqual(x, size.Dx()));
         Assert::IsTrue(IsEqual(y, size.Dy()));

         //
         // Test Magnitude Property
         //

         // use a 3,4,5 triangle
         vec.SetSize(3, 4);
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 5.0));
         // Set magnitude to 15 (9,12,15 triangle, 
         // this is a 3,4,5 triangle scaled by a factor of 3)
         vec.SetMagnitude(15.0);
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 15.0));
         Assert::IsTrue(IsEqual(vec.X(), 9.0));
         Assert::IsTrue(IsEqual(vec.Y(), 12.0));

         // Magnitude must be a positive number
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.SetMagnitude(-10); });

         //
         // Test Direction property
         //

         // (45 deg line, direction = M_PI/4)
         vec.SetSize(1, 1);
         Assert::IsTrue(IsEqual(vec.GetDirection(), M_PI / 4));

         // Set direction to 90 deg
         vec.SetDirection(PI_OVER_2);
         Assert::IsTrue(IsEqual(vec.GetDirection(), PI_OVER_2));
         Assert::IsTrue(IsEqual(vec.X(), 0.0));
         Assert::IsTrue(IsEqual(vec.Y(), 1.4142135)); // Magnitude stays the same so magnitude is Sqrt(2) = 1.414

         //
         // Test Normalize
         //
         vec.SetSize(10, 10);
         vec.Normalize();
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 1.0));
         Assert::IsTrue(IsEqual(vec.X(), 0.70710678));
         Assert::IsTrue(IsEqual(vec.Y(), 0.70710678));

         // normalize a zero length vector
         vec.SetSize(0, 0);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.Normalize(); });

         //
         // Test IsZero
         //
         vec.SetSize(10, 0);
         Assert::IsTrue(vec.IsZero() == false);

         vec.SetSize(0, 10);
         Assert::IsTrue(vec.IsZero() == false);

         vec.SetSize(0, 0);
         Assert::IsTrue(vec.IsZero() == true);

         //
         // Test Normal
         //

         // Make source vector point to the right. Normal will be up
         vec.SetSize(10, 0);
         auto normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), 0.0));
         Assert::IsTrue(IsEqual(normal.Y(), 10.0));

         // Make source vector point to the left. Normal will be down
         vec.SetSize(-10, 0);
         normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), 0.0));
         Assert::IsTrue(IsEqual(normal.Y(), -10.0));

         // Make source vector point up.
         vec.SetSize(0, 10);
         normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), -10.0));
         Assert::IsTrue(IsEqual(normal.Y(), 0.0));

         // Make source vector point down.
         vec.SetSize(0, -10);
         normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), 10.0));
         Assert::IsTrue(IsEqual(normal.Y(), 0.0));

         // Make source vector point up and to the right (45 deg)
         vec.SetSize(10, 10);
         normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), -10.0));
         Assert::IsTrue(IsEqual(normal.Y(), 10.0));

         // Make source vector point up and to the left (45 deg)
         vec.SetSize(-10, 10);
         normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), -10.0));
         Assert::IsTrue(IsEqual(normal.Y(), -10.0));

         // Make source vector point down and to the right (45 deg)
         vec.SetSize(10, -10);
         normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), 10.0));
         Assert::IsTrue(IsEqual(normal.Y(), 10.0));

         // Make source vector point down and to the left (45 deg)
         vec.SetSize(-10, -10);
         normal = vec.Normal();
         Assert::IsTrue(IsEqual(normal.X(), 10.0));
         Assert::IsTrue(IsEqual(normal.Y(), -10.0));

         //
         // Test Offset and OffsetEx
         //
         vec.SetSize(10, 10);
         vec.Offset(5, 5);
         Assert::IsTrue(IsEqual(vec.X(), 15.0));
         Assert::IsTrue(IsEqual(vec.Y(), 15.0));

         vec.SetSize(10, 10);
         vec.Offset(Size2d(-20, -20));
         Assert::IsTrue(IsEqual(vec.X(), -10.0));
         Assert::IsTrue(IsEqual(vec.Y(), -10.0));

         //
         // Test Projection (Projection of Vec1 onto Vec2)
         //

         // Vector is zero length
         Vector2d vec2(0, 0);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.Projection(vec2); });

         // Vector is zero length
         vec.SetSize(0, 0);
         vec2.SetSize(10, 10);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.Projection(vec2); });

         // Vectors are right angles (projection = 0)
         vec.SetSize(10, 0);
         vec2.SetSize(0, 10);
         Assert::IsTrue(::IsZero(vec.Projection(vec2)) == true);

         // One vector in the X direction, and one at 3,4,5. Projection will
         // be 3
         vec.SetSize(3, 4);
         vec2.SetSize(10, 0);
         Assert::IsTrue(IsEqual(vec.Projection(vec2), 3.0));

         // One vector in the Y direction, and one at 3,4,5. Projection will
         // be 4
         vec.SetSize(3, 4);
         vec2.SetSize(0, 10);
         Assert::IsTrue(IsEqual(vec.Projection(vec2), 4.0));

         // Negative projections (vectors in opposite directions)
         vec.SetSize(-3, 4);
         vec2.SetSize(10, 0);
         Assert::IsTrue(IsEqual(vec.Projection(vec2), -3.0));

         //
         // Test Reflect
         //
         vec.SetSize(10, 10);
         vec.Reflect();
         Assert::IsTrue(IsEqual(vec.X(), -10.0));
         Assert::IsTrue(IsEqual(vec.Y(), -10.0));

         //
         // Test Rotate
         //
         vec.SetSize(10, 0);
         vec.Rotate(M_PI / 4);
         Assert::IsTrue(IsEqual(vec.X(), 7.0710678));
         Assert::IsTrue(IsEqual(vec.Y(), 7.0710678));

         vec.SetSize(10, 10);
         vec.Rotate(M_PI / 4);
         Assert::IsTrue(IsEqual(vec.X(), 0.0));
         Assert::IsTrue(IsEqual(vec.Y(), 14.142135));

         vec.SetSize(10, 10);
         vec.Rotate(-M_PI / 4);
         Assert::IsTrue(IsEqual(vec.X(), 14.142135));
         Assert::IsTrue(IsEqual(vec.Y(), 0.0));

         //
         // Test Scale
         //
         vec.SetSize(10, 10);
         vec.SetMagnitude(10.0);
         vec.Scale(2.0);
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 20.0));

         //
         // Test Dot
         //
         vec.SetSize(10, 20);
         vec2.SetSize(30, 40);
         Assert::IsTrue(IsEqual(vec.Dot(vec2), 1100.0));

         //
         // Test AngleBetween
         //
         vec.SetSize(10, 0);
         vec2.SetSize(10, 10);
         Assert::IsTrue(IsEqual(vec.AngleBetween(vec2), M_PI / 4.0));

         // pVec is zero
         vec.SetSize(0, 0);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.AngleBetween(vec2); });

         // pVec2 is zero
         vec.SetSize(10, 0);
         vec2.SetSize(0, 0);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.AngleBetween(vec2); });

         //
         // Test Increment and Decrement
         //
         vec.SetSize(10, 20);
         vec2.SetSize(50, 60);
         vec.Increment(vec2);
         Assert::IsTrue(IsEqual(vec.X(), 60.));
         Assert::IsTrue(IsEqual(vec.Y(), 80.));

         auto vec3 = vec.IncrementBy(vec2);
         // vector 1, unchanged
         Assert::IsTrue(IsEqual(vec.X(), 60.));
         Assert::IsTrue(IsEqual(vec.Y(), 80.));
         Assert::IsTrue(IsEqual(vec3.X(), 110.));
         Assert::IsTrue(IsEqual(vec3.Y(), 140.));

         vec.SetSize(10, 20);
         vec2.SetSize(50, 60);
         vec.Decrement(vec2);
         Assert::IsTrue(IsEqual(vec.X(), -40.));
         Assert::IsTrue(IsEqual(vec.Y(), -40.));

         vec3 = vec.DecrementBy(vec2);
         // vector 1, unchanged
         Assert::IsTrue(IsEqual(vec.X(), -40.));
         Assert::IsTrue(IsEqual(vec.Y(), -40.));
         Assert::IsTrue(IsEqual(vec3.X(), -90.));
         Assert::IsTrue(IsEqual(vec3.Y(), -100.));
      }
	};
}
