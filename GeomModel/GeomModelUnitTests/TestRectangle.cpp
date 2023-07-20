#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestRectangle)
	{
	public:
		TEST_METHOD(Test)
		{
         WBFL::Geometry::Rectangle rt(Point2d(1, 2), 2, 4);
         Assert::IsTrue(IsEqual(2., rt.GetWidth()));
         Assert::IsTrue(IsEqual(4., rt.GetHeight()));
         Assert::IsTrue(Point2d(1, 2) == *rt.GetHookPoint());
         ShapeProperties aprops = rt.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 8.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 10.66, .1));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 2.66, .1));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), 0.00, .001));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(0, 0, 2, 4));

         rt.SetHookPoint(Point2d(0, 0));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(-1, -2, 1, 2));
         rt.Move(Shape::LocatorPoint::CenterCenter, Point2d(1, 2));
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(0, 0, 2, 4));

         Float64 ang = atan(.5);
         Float64 dis = 2 * cos(ang);
         rt.Rotate(Point2d(0, 0), ang);
         Assert::IsTrue(rt.GetBoundingBox() == Rect2d(-dis, 0, dis, sqrt(20.)));
         rt.Rotate(Point2d(0, 0), -ang);

         // resize rectangle and clip it into a triangle
         rt.SetWidth(40);
         rt.SetHeight(50);
         rt.SetHookPoint(Point2d(20, 25));
         Line2d up_left(Point2d(0, 0), Vector2d(Size2d(1, 1)));
         Line2d up_rgt(Point2d(40, 0), Vector2d(Size2d(-3, 5)));
         std::unique_ptr<Shape> pfirst(rt.CreateClippedShape(up_left, Line2d::Side::Left));
         std::unique_ptr<Shape> ptriang(pfirst->CreateClippedShape(up_rgt, Line2d::Side::Right));
         aprops = ptriang->GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 500.));
         Assert::IsTrue(ptriang->GetBoundingBox() == Rect2d(0, 0, 40, 25));
		}
	};
}
