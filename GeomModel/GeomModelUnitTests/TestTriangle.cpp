#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestTriangle)
	{
	public:
		TEST_METHOD(Test)
		{
         Triangle rt(Point2d(1, 2), 4, 2, 1);
         Assert::IsTrue(IsEqual(2., rt.GetWidth()));
         Assert::IsTrue(IsEqual(4., rt.GetHeight()));
         Assert::IsTrue(IsEqual(1., rt.GetOffset()));
         Assert::IsTrue(Point2d(1, 2) == *rt.GetHookPoint());
         ShapeProperties aprops = rt.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 4.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 3.55, .1));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 0.67, .1));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), 0.00, .001));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(1, 2, 3, 6));

         rt.SetHookPoint(Point2d(0, 0));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(0, 0, 2, 4));
         rt.Move(Shape::LocatorPoint::CenterCenter, Point2d(0, 0));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(-1, -2, 1, 2));

         Float64 ang = atan(.25);
         Float64 cosa = cos(ang);
         rt.SetHookPoint(Point2d(0, 0));
         rt.Rotate(Point2d(0, 0), ang);
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(0, 0, 2 * cosa, 4 / cosa));
         rt.SetRotationAngle(0);
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(0, 0, 2, 4));

         Assert::IsTrue(TestHookPoint(rt));
      }
	};
}
