#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestPlateGirder)
	{
	public:
		PlateGirder GetTestBeam()
		{
			PlateGirder beam(Point2d(0, 0), 22.0, 1.25, 22.0, 2.25, 122.0, 4.38);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -11.0));
			Assert::IsTrue(IsEqual(box.Right(), 11.0));
			Assert::IsTrue(IsEqual(box.Top(), 125.5));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();

			Assert::IsTrue(IsEqual(props.GetArea(), 611.36));
			Assert::IsTrue(IsEqual(props.GetIxx(), 955172.84424976027));
			Assert::IsTrue(IsEqual(props.GetIyy(), 3959.9479986666556));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 60.991919654540673));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 11.0));
			Assert::IsTrue(IsEqual(props.GetXright(), 11.0));
			Assert::IsTrue(IsEqual(props.GetYtop(), beam.GetHeight() - props.GetCentroid().Y()));
			Assert::IsTrue(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 330.24));

			Assert::IsTrue(IsEqual(beam.GetHeight(), 125.5));

			Assert::IsTrue(IsEqual(beam.GetQTopFlange(), 1756.7847095001314));
			Assert::IsTrue(IsEqual(beam.GetQBottomFlange(), 2963.4125228997632));
		}

		TEST_METHOD(FurthestDistance)
		{
			auto beam = GetTestBeam();

			Point2d p1(0, 20);
			Point2d p2(100, 20);
			Line2d line(p1, p2);

			// Shape on right
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.000));

			// shape on left
			p1.Move(0, -20);
			p2.Move(100, -20);
			line.ThroughPoints(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.000));
		}

		TEST_METHOD(PolyPoints)
		{
			auto beam = GetTestBeam();
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 12);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d( -11.000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d( -11.000000000000000, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d( -2.1899999999999999, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d( -2.1899999999999999, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d( -11.000000000000000, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d( -11.000000000000000, 125.50000000000000));
			Assert::IsTrue(points[i++] == Point2d( 11.000000000000000, 125.50000000000000));
			Assert::IsTrue(points[i++] == Point2d( 11.000000000000000, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d( 2.1899999999999999, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d( 2.1899999999999999, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d( 11.000000000000000, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::AreEqual(beamClone.GetTopFlangeWidth(), 22.0);
			Assert::AreEqual(beamClone.GetTopFlangeThickness(), 1.25);
			Assert::AreEqual(beamClone.GetBottomFlangeWidth(), 22.0);
			Assert::AreEqual(beamClone.GetBottomFlangeThickness(), 2.25);
			Assert::AreEqual(beamClone.GetWebHeight(), 122.0);
			Assert::AreEqual(beamClone.GetWebWidth(), 4.38);

		}

		TEST_METHOD(PointInShape)
		{
			auto beam = GetTestBeam();
			Point2d pnt(0, 0.5);
			Assert::IsTrue(beam.PointInShape(pnt));

			pnt.Move(500, 500);
			Assert::IsFalse(beam.PointInShape(pnt));

			pnt.Move(0, 0); // Point on perimeter
			Assert::IsFalse(beam.PointInShape(pnt));
		}

		TEST_METHOD(ClipWithLine)
		{
			auto beam = GetTestBeam();

			// setup clipping line
			Point2d p1(-50, 50);
			Point2d p2(50, 50);
			Line2d clipLine(p1, p2);

			auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 9);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000000, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-2.1899999999999999, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-2.1899999999999999, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.1899999999999999, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.1899999999999999, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.000000000000000, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 8);
			i = 0;
			Assert::IsTrue(points[i++] == Point2d(-2.1899999999999999, 50.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-2.1899999999999999, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000000, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000000, 125.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.000000000000000, 125.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.000000000000000, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.1899999999999999, 124.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.1899999999999999, 50.000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, 0.5, 100, 10);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 8);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000000, 0.50000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000000, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-2.1899999999999999, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(-2.1899999999999999, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.1899999999999999, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(2.1899999999999999, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.000000000000000, 2.2500000000000000));
			Assert::IsTrue(points[i++] == Point2d(11.000000000000000, 0.50000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(HookPoint)
		{
			// Test hook point behavior
			auto beam = GetTestBeam();
			Assert::IsTrue(TestHookPoint(beam));
		}

		TEST_METHOD(Move)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();

			// Get moment of inertia about CG before move
			// These properties should be invariant
			Float64 area = props.GetArea();
			Float64 Ixx = props.GetIxx();
			Float64 Iyy = props.GetIyy();
			Float64 Ixy = props.GetIxy();

			Point2d from(0, 0);
			Point2d to(100, 100);

			beam.Move(from, to);
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 12);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(97.810000000000002, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(97.810000000000002, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 225.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 225.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(102.19000000000000, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(102.19000000000000, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 100.00000000000000));
			Assert::IsTrue(i == points.size());

			props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), area, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxx(), Ixx, 0.01));
			Assert::IsTrue(IsEqual(props.GetIyy(), Iyy, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxy(), Ixy, 0.01));
		}

		TEST_METHOD(Offset)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();

			// Get moment of inertia about CG before move
			// These properties should be invariant
			Float64 area = props.GetArea();
			Float64 Ixx = props.GetIxx();
			Float64 Iyy = props.GetIyy();
			Float64 Ixy = props.GetIxy();

			Size2d size(100, 100);
			beam.Offset(size);
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 12);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(97.810000000000002, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(97.810000000000002, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(89.000000000000000, 225.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 225.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(102.19000000000000, 224.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(102.19000000000000, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 102.25000000000000));
			Assert::IsTrue(points[i++] == Point2d(111.00000000000000, 100.00000000000000));
			Assert::IsTrue(i == points.size());

			props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), area, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxx(), Ixx, 0.01));
			Assert::IsTrue(IsEqual(props.GetIyy(), Iyy, 0.01));
			Assert::IsTrue(IsEqual(props.GetIxy(), Ixy, 0.01));
		}

		TEST_METHOD(LocatorPoint)
		{
			auto beam = GetTestBeam();

			auto hookPnt = beam.GetHookPoint();

			// BottomLeft
			hookPnt->Move(0, 0);
			Point2d to(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
			auto from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(111.0, 100.0));

			// BottomCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));

			// BottomRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(89.0, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(111.0, 37.25));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 37.25));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(89.0, 37.25));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(111.0, -25.5));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, -25.5));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(89.0, -25.5));

			// HookPoint
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 100.0));
		}

		TEST_METHOD(Rotate)
		{
			auto beam = GetTestBeam();
			auto hookPnt = beam.GetHookPoint();
			hookPnt->Move(0, 0);

			Point2d c(0, 0);

			beam.Rotate(c, M_PI);

			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 12);
			int i = 0;
			Assert::IsTrue(points[i++]  == Point2d(11.000000000000000, -1.3471114790620886e-15 ));
			Assert::IsTrue(points[i++]  == Point2d(11.000000000000000, -2.2500000000000013 ));
			Assert::IsTrue(points[i++]  == Point2d(2.1899999999999995, -2.2500000000000004 ));
			Assert::IsTrue(points[i++]  == Point2d(2.1899999999999848, -124.25000000000000 ));
			Assert::IsTrue(points[i++]  == Point2d(10.999999999999984, -124.25000000000000 ));
			Assert::IsTrue(points[i++] == Point2d(10.999999999999984, -125.50000000000000));
			Assert::IsTrue(points[i++] == Point2d(-11.000000000000016, -125.50000000000000));
			Assert::IsTrue(points[i++]  == Point2d(-11.000000000000016, -124.25000000000000 ));
			Assert::IsTrue(points[i++]  == Point2d(-2.1900000000000150, -124.25000000000000 ));
			Assert::IsTrue(points[i++]  == Point2d(-2.1900000000000004, -2.2499999999999996 ));
			Assert::IsTrue(points[i++]  == Point2d(-11.000000000000000, -2.2499999999999987 ));
			Assert::IsTrue(points[i++]  == Point2d(-11.000000000000000, 1.3471114790620886e-15 ));
			Assert::IsTrue(i == points.size());
		}

	};
}
