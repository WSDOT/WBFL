#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	GenericShape GetTestShape()
	{
      return GenericShape(5, Point2d(10, 20), 1, 2, 0, 0, 0, 0, 0, 10);
   }

	TEST_CLASS(TestGenericShape)
	{
	public:

      TEST_METHOD(Basic)
      {
         GenericShape shape;
         Assert::IsTrue(IsZero(shape.GetArea()));
         Assert::IsTrue(IsZero(shape.GetIxx()));
         Assert::IsTrue(IsZero(shape.GetIyy()));
         Assert::IsTrue(IsZero(shape.GetIxy()));
         Assert::IsTrue(IsZero(shape.GetPerimeter()));
         Assert::IsTrue(*shape.GetCentroid() == Point2d(0, 0));

         shape = GetTestShape();
         Assert::IsTrue(IsEqual(shape.GetArea(), 5.0));
         Assert::IsTrue(IsEqual(shape.GetIxx(), 1.0));
         Assert::IsTrue(IsEqual(shape.GetIyy(), 2.0));
         Assert::IsTrue(IsEqual(shape.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(shape.GetPerimeter(), 10.0));
         Assert::IsTrue(*shape.GetCentroid() == Point2d(10, 20));

         auto hookPnt = shape.GetHookPoint();
         auto new_hookPnt = std::make_shared<Point2d>(-50, -60);
         shape.SetCentroid(new_hookPnt);
         Assert::IsTrue(*hookPnt == Point2d(10, 20)); // the hook point object was replaced so this old hook point doesn't change
         hookPnt = shape.GetHookPoint(); // get the new hook point
         Assert::IsTrue(*hookPnt == Point2d(-50, -60));
      }

      TEST_METHOD(BoundingBox)
      {
         auto shape = GetTestShape();
         auto box = shape.GetBoundingBox();
         Assert::IsTrue(IsEqual(box.Left(), 10.0));
         Assert::IsTrue(IsEqual(box.Right(), 10.0));
         Assert::IsTrue(IsEqual(box.Top(), 20.0));
         Assert::IsTrue(IsEqual(box.Bottom(), 20.0));
      }

      TEST_METHOD(ShapeProperties)
      {
         auto shape = GetTestShape();
         auto props = shape.GetProperties();
         Assert::IsTrue(IsEqual(shape.GetArea(), 5.0));
         Assert::IsTrue(IsEqual(shape.GetIxx(), 1.0));
         Assert::IsTrue(IsEqual(shape.GetIyy(), 2.0));
         Assert::IsTrue(IsEqual(shape.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(shape.GetPerimeter(), 10.0));
         Assert::IsTrue(*shape.GetCentroid() == Point2d(10, 20));
         Assert::IsTrue(*shape.GetHookPoint() == Point2d(10, 20));
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(IsEqual(props.GetXleft(), 0.0));
         Assert::IsTrue(IsEqual(props.GetXright(), 0.0));
         Assert::IsTrue(IsEqual(props.GetYtop(), 0.0));
         Assert::IsTrue(IsEqual(props.GetYbottom(), 0.0));
         Assert::IsTrue(IsEqual(shape.GetPerimeter(), 10.0));
      }

      TEST_METHOD(FurthestDistance)
      {
         auto shape = GetTestShape();

         // Shape on right
         Point2d p1(0, 50);
         Point2d p2(100, 50);
         Line2d line(p1, p2);
         Assert::IsTrue(IsEqual(shape.GetFurthestDistance(line, Line2d::Side::Right), 30.000));

         // shape on left
         p1.Move(0, -50);
         p2.Move(100, -50);
         line.ThroughPoints(p1, p2);
         Assert::IsTrue(IsEqual(shape.GetFurthestDistance(line, Line2d::Side::Right), -70.000));
      }

      TEST_METHOD(PolyPoints)
      {
         auto shape = GetTestShape();
         auto points = shape.GetPolyPoints();
         Assert::IsTrue(points.size() == 1);
         Assert::IsTrue(points[0] == Point2d(10, 20));
      }

      TEST_METHOD(PointInShape)
      {
         auto shape = GetTestShape();
         Point2d pnt(-10, -10);
         Assert::IsTrue(shape.PointInShape(pnt) == false);

         pnt.Move(10, 20);
         Assert::IsTrue(shape.PointInShape(pnt) == true);

         pnt.Move(15, 20);
         Assert::IsTrue(shape.PointInShape(pnt) == false);
      }

      TEST_METHOD(ClipWithLine)
      {
         auto shape = GetTestShape();

         // line to left of shape... clipping result is null
         Point2d p1(0, 0);
         Point2d p2(20, 20);
         Line2d clipLine(p1, p2);

         auto clip = shape.CreateClippedShape(clipLine, Line2d::Side::Left);
         Assert::IsNull(clip.get());

         // line to right of shape
         p1.Move(0, 20);
         p2.Move(20, 40);
         clipLine.ThroughPoints(p1, p2);
         clip = shape.CreateClippedShape(clipLine, Line2d::Side::Left);
         Assert::IsNotNull(clip.get());
         auto points = clip->GetPolyPoints();
         Assert::IsTrue(points.size() == 1);
         Assert::IsTrue(points[0] == Point2d(10, 20));
      }

      TEST_METHOD(ClipIn)
      {
         auto shape = GetTestShape();

         Rect2d clipRect(100, 15, 200, 25);
         auto clip = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         Assert::IsNull(clip.get());

         // in rectangle
         clipRect.Set(-100, 15, 100, 25);
         clip = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         Assert::IsNotNull(clip.get());
         auto points = clip->GetPolyPoints();
         Assert::IsTrue(points.size() == 1);
         Assert::IsTrue(points[0] == Point2d(10, 20));
      }

      TEST_METHOD(HookPoint)
      {
         auto shape = GetTestShape();
         Assert::IsTrue(TestHookPoint(shape));
      }

      TEST_METHOD(Move)
      {
         auto shape = GetTestShape();
         auto hookPnt = shape.GetHookPoint();
         hookPnt->Move(10, 20);
         Point2d from(0, 0);
         Point2d to(110, 110);
         shape.Move(from, to);
         Assert::IsTrue(*hookPnt == Point2d(120, 130));
      }

      TEST_METHOD(Offset)
      {
         auto shape = GetTestShape();
         auto hookPnt = shape.GetHookPoint();
         Size2d size(10, 20);
         shape.Offset(size);
         Assert::IsTrue(*hookPnt == Point2d(20, 40));
      }

      TEST_METHOD(LocatorPoint)
      {
         auto shape = GetTestShape();
         auto hookPnt = shape.GetHookPoint();
      
         // BottomLeft
         hookPnt->Move(0, 0);
         Point2d to(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
         auto from = shape.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // BottomCenter
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // BottomRight
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // CenterLeft
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // CenterCenter
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // CenterRight
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // TopLeft
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // TopCenter
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // TopRight
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::TopRight);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

         // HookPoint
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         shape.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
         from = shape.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));
      }

      TEST_METHOD(Rotate)
      {
         auto shape = GetTestShape();
         auto hookPnt = shape.GetHookPoint();

         hookPnt->Move(10, 20);
         Point2d c(0, 0);

         shape.Rotate(c, PI_OVER_2);
         auto points = shape.GetPolyPoints();

         Assert::IsTrue(points.size() == 1);
         Assert::IsTrue(points[0] == Point2d(-20, 10));

         // Test section properties of the rectangle rotated 45 deg.
         hookPnt->Move(0, 0);
         c.Move(0, 0);
         shape.Rotate(c, M_PI / 4);

         auto props = shape.GetProperties();

         Assert::IsTrue(IsEqual(props.GetArea(), 5.));
         Assert::IsTrue(IsEqual(props.GetIxx(), 1.5));
         Assert::IsTrue(IsEqual(props.GetIyy(), 1.5));
         Assert::IsTrue(IsEqual(props.GetIxy(), -0.5));
      }
	};
}
