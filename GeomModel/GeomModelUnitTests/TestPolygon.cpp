#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestPolygon)
	{
	public:
		
		TEST_METHOD(Test)
		{
         WBFL::Geometry::Polygon anglep;
         anglep.AddPoint(Point2d(0, 0));
         anglep.AddPoint(Point2d(0, 50));
         anglep.AddPoint(Point2d(10, 50));
         anglep.AddPoint(Point2d(10, 10));
         anglep.AddPoint(Point2d(40, 10));
         anglep.AddPoint(Point2d(40, 0));  // don't close polygon

         ShapeProperties aprops = anglep.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 800.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 181666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 101666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), -75000., 10.));
         Assert::IsTrue(anglep.GetBoundingBox() == Rect2d(0, 0, 40, 50));

         // test assignment
         auto anglec = anglep;
         aprops = anglec.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 800.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 181666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 101666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), -75000., 10.));
         Assert::IsTrue(anglep.GetBoundingBox() == Rect2d(0, 0, 40, 50));

         // try translation
         Point2d center = anglec.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
         Assert::IsTrue(center == Point2d(20, 25));
         Point2d top_right = anglec.GetLocatorPoint(Shape::LocatorPoint::TopRight);
         Assert::IsTrue(top_right == Point2d(40, 50));

         anglec.Move(center, top_right);
         aprops = anglec.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 800.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 181666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 101666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), -75000., 10.));
         Assert::IsTrue(anglec.GetBoundingBox() == Rect2d(20, 25, 60, 75));

         // turn shape into a rectangle
         anglec.RemovePoint(4);
         anglec.RemovePoint(3);
         anglec.ReplacePoint(2, Point2d(60, 75));
         aprops = anglec.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 2000.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 416666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 266666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), 0., 1.));
         Assert::IsTrue(anglec.GetBoundingBox() == Rect2d(20, 25, 60, 75));

         // rotate to principal axes
         anglep.Rotate(center, -0.54105);
         aprops = anglep.GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 800.));
         Assert::IsTrue(IsEqual(aprops.GetIxx(), 226666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIyy(), 56666., 10.));
         Assert::IsTrue(IsEqual(aprops.GetIxy(), 107., 10.));

         // create a line and find farthest point
         Line2d down_left(Point2d(25, 25), Vector2d(Size2d(1, -1)));
         Float64 dist = anglec.GetFurthestDistance(down_left, Line2d::Side::Left);
         Assert::IsTrue(IsEqual(60.1, dist, .1));
         dist = anglec.GetFurthestDistance(down_left, Line2d::Side::Right);
         Assert::IsTrue(IsEqual(3.53, dist, .01));

         // create a rectangle and clip it into a triangle
         WBFL::Geometry::Polygon rect;
         rect.AddPoint(Point2d(0, 0));
         rect.AddPoint(Point2d(0, 50));
         rect.AddPoint(Point2d(40, 50));
         rect.AddPoint(Point2d(40, 0));
         Line2d up_left(Point2d(0, 0), Vector2d(Size2d(1, 1)));
         Line2d up_rgt(Point2d(40, 0), Vector2d(Size2d(-3, 5)));
         std::unique_ptr<Shape> pfirst(rect.CreateClippedShape(up_left, Line2d::Side::Left));
         aprops = pfirst->GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 800.));
         Assert::IsTrue(IsEqual(aprops.GetCentroid().X(), 26.666666667));
         Assert::IsTrue(IsEqual(aprops.GetCentroid().Y(), 13.333333333));

         std::unique_ptr<Shape> ptriang(pfirst->CreateClippedShape(up_rgt, Line2d::Side::Right));
         aprops = ptriang->GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 500.));
         Assert::IsTrue(ptriang->GetBoundingBox() == Rect2d(0, 0, 40, 25));

         // clip triangle into a right triangle
         Rect2d clip_box(0, 5, 20, 25);
         std::unique_ptr<Shape> prtri(ptriang->CreateClippedShape(clip_box, Shape::ClipRegion::In));
         aprops = prtri->GetProperties();
         Assert::IsTrue(IsEqual(aprops.GetArea(), 112.5));
         Assert::IsTrue(prtri->GetBoundingBox() == Rect2d(5, 5, 20, 20));

         auto hookPnt = rect.GetHookPoint();
         Assert::IsTrue(*hookPnt == Point2d(0, 0));
         hookPnt->Move(10, 10);
         auto points = rect.GetPolyPoints();
         Assert::IsTrue(points[0] == Point2d(10, 10));
         Assert::IsTrue(points[1] == Point2d(10, 60));
         Assert::IsTrue(points[2] == Point2d(50, 60));
         Assert::IsTrue(points[3] == Point2d(50, 10));

         // Test hook point behavior
         Assert::IsTrue(TestHookPoint(anglep));

         // Test X-axis Symmetry (shape defined above Y=0)
         //
         //  (0,10) +=============+ (10,10)
         //         |             |
         //         |             |
         //         |             |  Input
         //         |             |
         //  (0,0)  +=============+ (10,0)
         //         :             :
         //         :             :
         //         :             :  Assumed from symmetry
         //         :             :
         // (0,-10) +-------------+ (10,-10)
         WBFL::Geometry::Polygon sym_shape;
         sym_shape.SetSymmetry(Polygon::Symmetry::X);
         // shape is symmetric about the Y=0 axis so don't define an edge on that axis
         sym_shape.AddPoint(10, 0);
         sym_shape.AddPoint(10, 10);
         sym_shape.AddPoint(0, 10);
         sym_shape.AddPoint(0, 0);

         WBFL::Geometry::Polygon shape;
         shape.AddPoint(0, -10);
         shape.AddPoint(10, -10);
         shape.AddPoint(10, 10);
         shape.AddPoint(0, 10);

         Assert::IsTrue(sym_shape.GetProperties() == shape.GetProperties());
         Assert::IsTrue(sym_shape.GetBoundingBox() == shape.GetBoundingBox());
         Assert::IsTrue(IsEqual(sym_shape.GetPerimeter(), shape.GetPerimeter()));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, 5)) == shape.PointInShape(Point2d(5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, -5)) == shape.PointInShape(Point2d(5, -5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, 5)) == shape.PointInShape(Point2d(-5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, -5)) == shape.PointInShape(Point2d(-5, -5)));

         Line2d line(Point2d(-10, 20), Point2d(20, 20));
         Assert::IsTrue(IsEqual(sym_shape.GetFurthestDistance(line, Line2d::Side::Right), shape.GetFurthestDistance(line, Line2d::Side::Right)));
         Assert::IsTrue(IsEqual(sym_shape.GetFurthestDistance(line, Line2d::Side::Left), shape.GetFurthestDistance(line, Line2d::Side::Left)));

         line.ThroughPoints(shape.GetBoundingBox().TopLeft(), shape.GetBoundingBox().BottomRight()); // diagonal line from top-left to bottom-right
         auto clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Left);
         auto clip2 = shape.CreateClippedShape(line, Line2d::Side::Left);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Right);
         clip2 = shape.CreateClippedShape(line, Line2d::Side::Right);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         Rect2d clipRect(-15, -5, 15, 5);
         clip1 = sym_shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         clip2 = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         // Test X-axis Symmetry (shape defined below Y=0)
         //
         //  (0,10) +-------------+ (10,10)
         //         :             :
         //         :             :
         //         :             :  Assumed by symmetry
         //         :             :
         //  (0,0)  +=============+ (10,0)
         //         |             |
         //         |             |
         //         |             |  Input
         //         |             |
         // (0,-10) +=============+ (10,-10)
         sym_shape.Clear();
         sym_shape.SetSymmetry(Polygon::Symmetry::X);
         // shape is symmetric about the Y=0 axis so don't define an edge on that axis
         sym_shape.AddPoint(0, 0);
         sym_shape.AddPoint(0, -10);
         sym_shape.AddPoint(10, -10);
         sym_shape.AddPoint(10, 0);

         Assert::IsTrue(sym_shape.GetProperties() == shape.GetProperties());
         Assert::IsTrue(sym_shape.GetBoundingBox() == shape.GetBoundingBox());
         Assert::IsTrue(IsEqual(sym_shape.GetPerimeter(), shape.GetPerimeter()));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, 5)) == shape.PointInShape(Point2d(5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, -5)) == shape.PointInShape(Point2d(5, -5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, 5)) == shape.PointInShape(Point2d(-5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, -5)) == shape.PointInShape(Point2d(-5, -5)));

         line.ThroughPoints(Point2d(-10, 20), Point2d(20, 20));
         Point2d furthestPoint, sym_furthestPoint;
         Float64 furthestDistance, sym_furthestDistance;
         sym_shape.GetFurthestPoint(line, Line2d::Side::Right, sym_furthestPoint, sym_furthestDistance);
         shape.GetFurthestPoint(line, Line2d::Side::Right, furthestPoint, furthestDistance);
         Assert::IsTrue(IsEqual(sym_furthestDistance, furthestDistance));
         Assert::IsTrue(sym_furthestPoint == furthestPoint);
         Assert::IsTrue(sym_furthestPoint == Point2d(0, -10));

         sym_shape.GetFurthestPoint(line, Line2d::Side::Left, sym_furthestPoint, sym_furthestDistance);
         shape.GetFurthestPoint(line, Line2d::Side::Left, furthestPoint, furthestDistance);
         Assert::IsTrue(IsEqual(sym_furthestDistance, furthestDistance));
         // NOTE: there are two valid solutions.... shape and sym_shape each get one of them
         Assert::IsTrue(furthestPoint == Point2d(10, 10));
         Assert::IsTrue(sym_furthestPoint == Point2d(0, 10));

         line.ThroughPoints(shape.GetBoundingBox().TopLeft(), shape.GetBoundingBox().BottomRight()); // diagonal line from top-left to bottom-right
         clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Left);
         clip2 = shape.CreateClippedShape(line, Line2d::Side::Left);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Right);
         clip2 = shape.CreateClippedShape(line, Line2d::Side::Right);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         clipRect.Set(-15, -5, 15, 5);
         clip1 = sym_shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         clip2 = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         // Test Y axis symmetry (shape defined right of X=0)
         //  (-10,10)    (0,10)         (10,10)
         //  +------------+=============+
         //  :            |             |
         //  :            |             |
         //  :            |             |  Input
         //  :            |             |
         //  +------------+=============+
         // (-10,0)     (0,0)          (10,0)
         sym_shape.Clear();
         sym_shape.SetSymmetry(Polygon::Symmetry::Y);
         // shape is symmetric about the X=0 axis so don't define an edge on that axis
         sym_shape.AddPoint(0, 0);
         sym_shape.AddPoint(10, 0);
         sym_shape.AddPoint(10, 10);
         sym_shape.AddPoint(0, 10);

         shape.Clear();
         shape.AddPoint(-10, 0);
         shape.AddPoint(10, 0);
         shape.AddPoint(10, 10);
         shape.AddPoint(-10, 10);

         Assert::IsTrue(sym_shape.GetProperties() == shape.GetProperties());
         Assert::IsTrue(sym_shape.GetBoundingBox() == shape.GetBoundingBox());
         Assert::IsTrue(IsEqual(sym_shape.GetPerimeter(), shape.GetPerimeter()));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, 5)) == shape.PointInShape(Point2d(5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, -5)) == shape.PointInShape(Point2d(5, -5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, 5)) == shape.PointInShape(Point2d(-5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, -5)) == shape.PointInShape(Point2d(-5, -5)));

         line.ThroughPoints(Point2d(-20, -20), Point2d(-20, 20));
         Assert::IsTrue(IsEqual(sym_shape.GetFurthestDistance(line, Line2d::Side::Right), shape.GetFurthestDistance(line, Line2d::Side::Right)));
         Assert::IsTrue(IsEqual(sym_shape.GetFurthestDistance(line, Line2d::Side::Left), shape.GetFurthestDistance(line, Line2d::Side::Left)));

         line.ThroughPoints(shape.GetBoundingBox().TopLeft(), shape.GetBoundingBox().BottomRight()); // diagonal line from top-left to bottom-right
         clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Left);
         clip2 = shape.CreateClippedShape(line, Line2d::Side::Left);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Right);
         clip2 = shape.CreateClippedShape(line, Line2d::Side::Right);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         clipRect.Set(-15, 2, 15, 8);
         clip1 = sym_shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         clip2 = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());


         // Test Y axis symmetry (shape defined left of X=0)
         //  (-10,10)    (0,10)         (10,10)
         //  +============+-------------+
         //  |            |             :
         //  |            |             :
         //  |            |             :  Input
         //  |            |             :
         //  +============+-------------+
         // (-10,0)     (0,0)          (10,0)
         sym_shape.Clear();
         sym_shape.SetSymmetry(Polygon::Symmetry::Y);
         // shape is symmetric about the X=0 axis so don't define an edge on that axis
         sym_shape.AddPoint(0, 10);
         sym_shape.AddPoint(-10, 10);
         sym_shape.AddPoint(-10, 0);
         sym_shape.AddPoint(0, 0);

         shape.Clear();
         shape.AddPoint(-10, 0);
         shape.AddPoint(10, 0);
         shape.AddPoint(10, 10);
         shape.AddPoint(-10, 10);

         Assert::IsTrue(sym_shape.GetProperties() == shape.GetProperties());
         Assert::IsTrue(sym_shape.GetBoundingBox() == shape.GetBoundingBox());
         Assert::IsTrue(IsEqual(sym_shape.GetPerimeter(), shape.GetPerimeter()));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, 5)) == shape.PointInShape(Point2d(5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(5, -5)) == shape.PointInShape(Point2d(5, -5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, 5)) == shape.PointInShape(Point2d(-5, 5)));
         Assert::IsTrue(sym_shape.PointInShape(Point2d(-5, -5)) == shape.PointInShape(Point2d(-5, -5)));

         line.ThroughPoints(Point2d(-20, -20), Point2d(-20, 20));
         Assert::IsTrue(IsEqual(sym_shape.GetFurthestDistance(line, Line2d::Side::Right), shape.GetFurthestDistance(line, Line2d::Side::Right)));
         Assert::IsTrue(IsEqual(sym_shape.GetFurthestDistance(line, Line2d::Side::Left), shape.GetFurthestDistance(line, Line2d::Side::Left)));

         line.ThroughPoints(shape.GetBoundingBox().TopLeft(), shape.GetBoundingBox().BottomRight()); // diagonal line from top-left to bottom-right
         clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Left);
         clip2 = shape.CreateClippedShape(line, Line2d::Side::Left);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         clip1 = sym_shape.CreateClippedShape(line, Line2d::Side::Right);
         clip2 = shape.CreateClippedShape(line, Line2d::Side::Right);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());

         clipRect.Set(-15, 2, 15, 8);
         clip1 = sym_shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         clip2 = shape.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         Assert::IsTrue(clip1->GetProperties() == clip2->GetProperties());
         Assert::IsTrue(clip1->GetBoundingBox() == clip2->GetBoundingBox());
         Assert::IsTrue(clip1->GetPerimeter() == clip2->GetPerimeter());
		}
	};
}
