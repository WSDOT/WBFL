#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCoordinateXform3d)
	{
	public:

		TEST_METHOD(Test)
		{
         const Float64 tolerance = 1e-04;

         CoordinateXform3d xform;

         // Setup for some real transformations (XY Plane)
         Point3d origin(7, -4, 0);
         Vector3d rv(0, 0, 0); // this is an invalid rotation vector.... will be tested below
         xform.SetNewOrigin(origin);
         try
         {
            xform.SetRotationVector(rv);
            Assert::IsTrue(false);
         }
         catch (...)
         {
            Assert::IsTrue(true);
         }

         xform.SetRotationAngle(ToRadians(27));

         // use a valid rotation vector
         rv.SetSize(Size3d(0, 0, 1));
         xform.SetRotationVector(rv);

         Point3d pnt(-9, 7, 0);
         Point3d p1;

         p1 = xform.XformBy(pnt, CoordinateXform3d::Type::OldToNew);
         // original point should not change
         Assert::IsTrue(IsEqual(pnt.X(), -9., tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), 7., tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 0., tolerance));
         // point in new coordinate system
         Assert::IsTrue(IsEqual(p1.X(), -9.2622, tolerance));
         Assert::IsTrue(IsEqual(p1.Y(), 17.0649, tolerance));
         Assert::IsTrue(IsEqual(p1.Z(), 0., tolerance));

         // convert back to original system
         auto p2 = xform.XformBy(p1, CoordinateXform3d::Type::NewToOld);
         Assert::IsTrue(IsEqual(pnt.X(), p2.X(), tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), p2.Y(), tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), p2.Z(), tolerance));

         // same as the first transformation, except that pnt is changed
         xform.Xform(pnt, CoordinateXform3d::Type::OldToNew);
         Assert::IsTrue(IsEqual(pnt.X(), p1.X(), tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), p1.Y(), tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), p1.Z(), tolerance));

         // transform back to the origina coodinates
         xform.Xform(pnt, CoordinateXform3d::Type::NewToOld);
         Assert::IsTrue(IsEqual(pnt.X(), -9., tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), 7., tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 0., tolerance));

         // Test XZ Plane
         origin.Move(7, 0, -4);
         rv.SetSize(Size3d(0, -1, 0));
         xform.SetNewOrigin(origin);
         xform.SetRotationVector(rv);
         pnt.Move(-9, 0, 7);
         xform.Xform(pnt, CoordinateXform3d::Type::OldToNew);
         Assert::IsTrue(IsEqual(pnt.X(), -9.2622, tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), 0.0000, tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 17.0649, tolerance));

         pnt.Move(-9.2622, 0.0000, 17.0649);
         xform.Xform(pnt, CoordinateXform3d::Type::NewToOld);
         Assert::IsTrue(IsEqual(pnt.X(), -9., tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), 0., tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 7., tolerance));

         // Test YZ Plane
         origin.Move(0, 7, -4);
         rv.SetSize(Size3d(1, 0, 0));
         xform.SetNewOrigin(origin);
         xform.SetRotationVector(rv);
         pnt.Move(0, -9, 7);
         xform.Xform(pnt, CoordinateXform3d::Type::OldToNew);
         Assert::IsTrue(IsEqual(pnt.X(), 0.0000, tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), -9.2622, tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 17.0649, tolerance));

         pnt.Move(0.0000, -9.2622, 17.0649);
         xform.Xform(pnt, CoordinateXform3d::Type::NewToOld);
         Assert::IsTrue(IsEqual(pnt.X(), 0., tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), -9., tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 7., tolerance));

         // 3D Transformation
         origin.Move(2.45, 4, 4.25);
         rv.SetSize(Size3d(0, -1, -1));
         xform.SetNewOrigin(origin);
         xform.SetRotationVector(rv);
         xform.SetRotationAngle(ToRadians(62.5));
         pnt.Move(3.9, 2.1, 7.0);
         xform.Xform(pnt, CoordinateXform3d::Type::OldToNew);
         Assert::IsTrue(IsEqual(pnt.X(), 3.5861, tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), 0.2609, tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 0.5891, tolerance));

         pnt.Move(3.5861, 0.2609, 0.5891);
         xform.Xform(pnt, CoordinateXform3d::Type::NewToOld);
         Assert::IsTrue(IsEqual(pnt.X(), 3.9, 0.1));
         Assert::IsTrue(IsEqual(pnt.Y(), 2.1, 0.1));
         Assert::IsTrue(IsEqual(pnt.Z(), 7.0, 0.1));

         pnt.Move(1, 1, 1);
         xform.Xform(pnt, CoordinateXform3d::Type::NewToOld);
         Assert::IsTrue(IsEqual(pnt.X(), 2.9117, tolerance));
         Assert::IsTrue(IsEqual(pnt.Y(), 4.3728, tolerance));
         Assert::IsTrue(IsEqual(pnt.Z(), 5.8772, tolerance));

         pnt.Move(2.9117, 4.3728, 5.8772);
         xform.Xform(pnt, CoordinateXform3d::Type::OldToNew);
         Assert::IsTrue(IsEqual(pnt.X(), 1.0, 0.1));
         Assert::IsTrue(IsEqual(pnt.Y(), 1.0, 0.1));
         Assert::IsTrue(IsEqual(pnt.Z(), 1.0, 0.1));
      }
	};
}
