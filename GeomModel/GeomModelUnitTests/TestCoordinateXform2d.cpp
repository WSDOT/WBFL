#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCoordinateXform2d)
	{
	public:

		TEST_METHOD(Test)
		{
         const Float64 tolerance = 1.0e-04;

         CoordinateXform2d xform;

         Point2d origin(7, -4);
         xform.SetNewOrigin(origin);

         xform.SetRotationAngle(27 * M_PI / 180);

         Point2d p1(-9, 7);
         Point2d p2 = xform.XformBy(p1, CoordinateXform2d::Type::OldToNew);
         Assert::IsTrue(IsEqual(p1.X(), -9.0, tolerance)); // should not change original point
         Assert::IsTrue(IsEqual(p1.Y(), 7.0, tolerance));
         Assert::IsTrue(IsEqual(p2.X(), -9.2622, tolerance));
         Assert::IsTrue(IsEqual(p2.Y(), 17.0649, tolerance));

         Point2d p3 = xform.Xform(p1, CoordinateXform2d::Type::OldToNew);
         Assert::IsTrue(IsEqual(p1.X(), -9.2622, tolerance)); // changes original point
         Assert::IsTrue(IsEqual(p1.Y(), 17.0649, tolerance));
         Assert::IsTrue(IsEqual(p3.X(), -9.2622, tolerance));
         Assert::IsTrue(IsEqual(p3.Y(), 17.0649, tolerance));

         Point2d p1_ = xform.XformBy(p1, CoordinateXform2d::Type::NewToOld);
         Assert::IsTrue(IsEqual(p1.X(), -9.2622, tolerance));
         Assert::IsTrue(IsEqual(p1.Y(), 17.0649, tolerance));
         Assert::IsTrue(IsEqual(p1_.X(), -9.0, tolerance));
         Assert::IsTrue(IsEqual(p1_.Y(), 7.0, tolerance));

         Point2d p2_ = xform.Xform(p1, CoordinateXform2d::Type::NewToOld);
         Assert::IsTrue(IsEqual(p1.X(), -9.0, tolerance));
         Assert::IsTrue(IsEqual(p1.Y(), 7.0, tolerance));
         Assert::IsTrue(IsEqual(p2_.X(), -9.0, tolerance));
         Assert::IsTrue(IsEqual(p2_.Y(), 7.0, tolerance));
      }
	};
}
