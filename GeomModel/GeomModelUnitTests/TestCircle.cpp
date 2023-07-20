#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestCircle)
	{
	public:

		TEST_METHOD(Basic)
		{
         Circle rt(Point2d(2, 2), 2);
         Assert::IsTrue(IsEqual(2., rt.GetRadius()));
         Assert::IsTrue(Point2d(2, 2) == *rt.GetHookPoint());

         ShapeProperties aprops = rt.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 12.566, .01));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 12.56, .1));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 12.56, .1));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), 0.00, .001));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(0, 0, 4, 4));

         rt.SetHookPoint(Point2d(0, 0));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(-2, -2, 2, 2));
         rt.Move(Shape::LocatorPoint::CenterCenter, Point2d(2, 2));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(0, 0, 4, 4));

         Float64 ang = atan(1.);
         Float64 dis = 2 / cos(ang);
         rt.Rotate(Point2d(0, 0), ang);
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(-2, dis - 2, 2, dis + 2));

         // Resize circle and clip it into a hemi
         rt.SetRadius(40);
         rt.SetHookPoint(Point2d(0, 40));
         Line2d at45(Point2d(0, 40), Vector2d(Size2d(1, 1)));
         std::unique_ptr<Shape> phemi(rt.CreateClippedShape(at45, Line2d::Side::Right));
         aprops = phemi->GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 2513.2, .1));

         // clip should return entire circle
         rt.SetHookPoint(Point2d(60, 0));
         std::unique_ptr<Shape> prt(rt.CreateClippedShape(at45, Line2d::Side::Left));
         aprops = prt->GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 5026.55, .1));
      }
	};
}
