#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestTrafficBarrier)
	{
	public:
		
		TrafficBarrier GetTestBeam()
		{
			TrafficBarrier beam;
			beam.SetX1(6);
			beam.SetX2(10.5);
			beam.SetX3(25);
			beam.SetX4(3);
			beam.SetX5(4);
			beam.SetY1(9);
			beam.SetY2(12);
			beam.SetY3(48);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -21.5));
			Assert::IsTrue(IsEqual(box.Right(), 10.5));
			Assert::IsTrue(IsEqual(box.Top(), 48.0));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
		
			Assert::IsTrue(IsEqual(props.GetArea(), 991.5));
			Assert::IsTrue(IsEqual(props.GetIxx(), 190915.38086232985));
			Assert::IsTrue(IsEqual(props.GetIyy(), 48046.253025718594));
			Assert::IsTrue(IsEqual(props.GetIxy(), -46957.062594553718));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), -3.7647503782148259));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 25.414523449319212));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 17.735249621785172));
			Assert::IsTrue(IsEqual(props.GetXright(), 14.264750378214826));
			Assert::IsTrue(IsEqual(props.GetYtop(), 48.0 - props.GetCentroid().Y()));
			Assert::IsTrue(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 140.75582513208252));
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
			Assert::IsTrue(points.size() == 8);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(10.500000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(10.500000000000000, 9.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(6.5000000000000000, 21.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(3.5000000000000000, 48.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-21.500000000000000, 48.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-6.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::AreEqual(beamClone.GetX1(),6.0);
			Assert::AreEqual(beamClone.GetX2(),10.5);
			Assert::AreEqual(beamClone.GetX3(),25.0);
			Assert::AreEqual(beamClone.GetX4(),3.0);
			Assert::AreEqual(beamClone.GetX5(),4.0);
			Assert::AreEqual(beamClone.GetY1(),9.0);
			Assert::AreEqual(beamClone.GetY2(),12.0);
			Assert::AreEqual(beamClone.GetY3(),48.0);
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
			Point2d p1(-50, 25);
			Point2d p2(50, 25);
			Line2d clipLine(p1, p2);

			auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 8);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(10.500000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(10.500000000000000, 9.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(6.5000000000000000, 21.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(6.0555555555555554, 25.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-14.072916666666666, 25.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-6.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 4);
			i = 0;
			Assert::IsTrue(points[i++] == Point2d(6.0555555555555554, 25.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(3.5000000000000000, 48.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-21.500000000000000, 48.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-14.072916666666666, 25.000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, 12, 100, 36);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 5);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(9.5000000000000000, 12.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(6.5000000000000000, 21.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(4.8333333333333339, 36.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-17.625000000000000, 36.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-9.8750000000000000, 12.000000000000000));
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
			Assert::IsTrue(points.size() == 8);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(110.50000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(110.50000000000000, 109.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(106.50000000000000, 121.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(103.50000000000000, 148.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(78.500000000000000, 148.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(94.000000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
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
			Assert::IsTrue(points.size() == 8);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(110.50000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(110.50000000000000, 109.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(106.50000000000000, 121.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(103.50000000000000, 148.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(78.500000000000000, 148.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(94.000000000000000, 100.00000000000000));
			Assert::IsTrue(points[i++] == Point2d(100.00000000000000, 100.00000000000000));
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
			Assert::IsTrue(*hookPnt == Point2d(121.5, 100.0));

			// BottomCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(105.5, 100.0));

			// BottomRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(89.5, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(121.5, 76.0));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(105.5, 76.0));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(89.5, 76.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(121.5, 52.0));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(105.5, 52.0));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(89.5, 52.0));

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
			Assert::IsTrue(points.size() == 8);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000,  0.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-10.500000000000000, 1.2858791391047208e-15));
			Assert::IsTrue(points[i++] == Point2d(-10.500000000000002, -8.9999999999999982));
			Assert::IsTrue(points[i++] == Point2d(-6.5000000000000027, -21.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-3.5000000000000058, -48.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(21.499999999999993, -48.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(6.0000000000000000, -7.3478807948841188e-16));
			Assert::IsTrue(points[i++] == Point2d(0.0000000000000000, 0.0000000000000000));
			Assert::IsTrue(i == points.size());
		}
	};
}
