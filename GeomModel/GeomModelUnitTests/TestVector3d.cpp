#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestVectorLine3d)
	{
	public:

      TEST_METHOD(Test)
      {
         Float64 x, y, z;
         x = -10.0;
         y = -20.0;
         z = -30.0;

         Vector3d vec(x, y, z);
         Assert::IsTrue(IsEqual(x, vec.X()));
         Assert::IsTrue(IsEqual(y, vec.Y()));
         Assert::IsTrue(IsEqual(z, vec.Z()));

         //
         // Test Size Property
         //
         Size3d size = vec.GetSize();
         Assert::IsTrue(IsEqual(x, size.Dx()));
         Assert::IsTrue(IsEqual(y, size.Dy()));
         Assert::IsTrue(IsEqual(z, size.Dz()));

         //
         // Test Magnitude Property
         //
         vec.SetSize(Size3d(3, 4, 5));
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 7.07106781187));

         vec.SetMagnitude(70.7106781187);
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 70.7106781187));
         Assert::IsTrue(IsEqual(vec.X(), 30.0));
         Assert::IsTrue(IsEqual(vec.Y(), 40.0));
         Assert::IsTrue(IsEqual(vec.Z(), 50.0));

         // Magnitude must be a positive number
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.SetMagnitude(-10); });

         //
         // Test Normalize
         //
         vec.SetSize(Size3d(10, 20, 30));
         vec.Normalize();
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 1.0));
         Assert::IsTrue(IsEqual(vec.X(), 0.267261));
         Assert::IsTrue(IsEqual(vec.Y(), 0.534522));
         Assert::IsTrue(IsEqual(vec.Z(), 0.801784));

         // normalize a zero length vector
         vec.SetSize(Size3d(0, 0, 0));
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.Normalize(); });

         //
         // Test IsZero
         //
         Assert::IsTrue(vec.IsZero() == true);
         vec.SetSize(Size3d(10, 0, 0));
         Assert::IsTrue(vec.IsZero() == false);

         vec.SetSize(Size3d(0, 10, 0));
         Assert::IsTrue(vec.IsZero() == false);

         vec.SetSize(Size3d(0, 0, 10));
         Assert::IsTrue(vec.IsZero() == false);

         //
         // Test Offset and OffsetEx
         //
         vec.SetSize(Size3d(10, 10, 10));
         vec.Offset(Size3d(5, 5, 5));
         Assert::IsTrue(IsEqual(vec.X(), 15.0));
         Assert::IsTrue(IsEqual(vec.Y(), 15.0));
         Assert::IsTrue(IsEqual(vec.Z(), 15.0));

         vec.SetSize(Size3d(10, 10, 10));
         vec.Offset(Size3d(-20, -20, -20));
         Assert::IsTrue(IsEqual(vec.X(), -10.0));
         Assert::IsTrue(IsEqual(vec.Y(), -10.0));
         Assert::IsTrue(IsEqual(vec.Z(), -10.0));

         //
         // Test Projection (Projection of Vec2 onto Vec1)
         //

         // Vector is zero length
         Vector3d vec2(0, 0, 0);
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.Projection(vec2); });
         // Vector is zero length
         vec.SetSize(Size3d(0, 0, 0));
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.Projection(vec2); });

         // Vectors are right angles (projection = 0)
         vec.SetSize(Size3d(10, 10, 0));
         vec2.SetSize(Size3d(-10, 10, 0));
         Assert::IsTrue(::IsZero(vec.Projection(vec2)));

         // One vector in the X direction, and one at 3,4,5. Projection will
         // be 3
         vec.SetSize(Size3d(3, 4, 5));
         vec2.SetSize(Size3d(10, 0, 0));
         Assert::IsTrue(IsEqual(vec.Projection(vec2), 3.0));

         // One vector in the Y direction, and one at 3,4,5. Projection will
         // be 4
         vec.SetSize(Size3d(3, 4, 5));
         vec2.SetSize(Size3d(0, 10, 0));
         Assert::IsTrue(IsEqual(vec.Projection(vec2), 4.0));

         // Negative projections (vectors in opposite directions)
         vec.SetSize(Size3d(-3, 4, 5));
         vec2.SetSize(Size3d(10, 0, 0));
         Assert::IsTrue(IsEqual(vec.Projection(vec2), -3.0));

         vec.SetSize(Size3d(10, 10, 10));
         vec2.SetSize(Size3d(10, 0, 10));
         Assert::IsTrue(IsEqual(vec.Projection(vec2), 14.1421356));

         //
         // Test Reflect
         //
         vec.SetSize(Size3d(10, 10, 10));
         vec.Reflect();
         Assert::IsTrue(IsEqual(vec.X(), -10.0));
         Assert::IsTrue(IsEqual(vec.Y(), -10.0));
         Assert::IsTrue(IsEqual(vec.Z(), -10.0));

         //
         // Test Scale
         //
         vec.SetSize(Size3d(10, 10, 10)); // establish direction
         vec.SetMagnitude(10); // fix magnitude
         vec.Scale(2);
         Assert::IsTrue(IsEqual(vec.GetMagnitude(), 20.0));

         //
         // Test Dot
         //
         vec.SetSize(Size3d(10, 20, 30));
         vec2.SetSize(Size3d(40, 50, 60));
         Assert::IsTrue(IsEqual(vec.Dot(vec2), 3200.0));

         //
         // Test AngleBetween
         //
         vec.SetSize(Size3d(10, 0, 0));
         vec2.SetSize(Size3d(10, 10, 0));
         Assert::IsTrue(IsEqual(vec.AngleBetween(vec2), M_PI / 4));

         vec.SetSize(Size3d(10, 10, 10));
         vec2.SetSize(Size3d(-10, -10, -10));
         Assert::IsTrue(IsEqual(vec.AngleBetween(vec2), M_PI));

         // pVec is zero
         vec.SetSize(Size3d(0, 0, 0));
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.AngleBetween(vec2); });

         // pVec2 is zero
         vec.SetSize(Size3d(10, 0, 0));
         vec2.SetSize(Size3d(0, 0, 0));
         Assert::ExpectException<WBFL::Geometry::XGeometry>([&]() {vec.AngleBetween(vec2); });

         //
         // Test Cross 
         //
         vec.SetSize(Size3d(10, 20, 30));
         vec2.SetSize(Size3d(-32, -25, 4));
         auto cross = vec.Cross(vec2);
         Assert::IsTrue(IsEqual(cross.X(), 830.));
         Assert::IsTrue(IsEqual(cross.Y(), -1000.));
         Assert::IsTrue(IsEqual(cross.Z(), 390.));

         cross = vec2.Cross(vec);
         Assert::IsTrue(IsEqual(cross.X(), -830.));
         Assert::IsTrue(IsEqual(cross.Y(), 1000.));
         Assert::IsTrue(IsEqual(cross.Z(), -390.));

         //
         // Test Increment and Decrement
         //
         vec.SetSize(Size3d(10, 20, 30));
         vec2.SetSize(Size3d(50, 60, 70));
         vec.Increment(vec2);
         Assert::IsTrue(IsEqual(vec.X(), 60.));
         Assert::IsTrue(IsEqual(vec.Y(), 80.));
         Assert::IsTrue(IsEqual(vec.Z(), 100.));

         auto vec3 = vec.IncrementBy(vec2);
         // vector 1 unchanged
         Assert::IsTrue(IsEqual(vec.X(), 60.));
         Assert::IsTrue(IsEqual(vec.Y(), 80.));
         Assert::IsTrue(IsEqual(vec.Z(), 100.));
         Assert::IsTrue(IsEqual(vec3.X(), 110.));
         Assert::IsTrue(IsEqual(vec3.Y(), 140.));
         Assert::IsTrue(IsEqual(vec3.Z(), 170.));

         vec.SetSize(Size3d(10, 20, 30));
         vec2.SetSize(Size3d(50, 60, 70));
         vec.Decrement(vec2);
         Assert::IsTrue(IsEqual(vec.X(), -40.));
         Assert::IsTrue(IsEqual(vec.Y(), -40.));
         Assert::IsTrue(IsEqual(vec.Z(), -40.));

         vec3 = vec.DecrementBy(vec2);
         // vector 1, unchanged
         Assert::IsTrue(IsEqual(vec.X(), -40.));
         Assert::IsTrue(IsEqual(vec.Y(), -40.));
         Assert::IsTrue(IsEqual(vec.Z(), -40.));
         Assert::IsTrue(IsEqual(vec3.X(), -90.));
         Assert::IsTrue(IsEqual(vec3.Y(), -100.));
         Assert::IsTrue(IsEqual(vec3.Z(), -110.));
      }
	};
}
