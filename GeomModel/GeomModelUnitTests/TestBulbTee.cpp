#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestBulbTee)
	{
	public:
		
		BulbTee GetTestBeam()
		{
			BulbTee beam;

			// WSDOT WF69G
			beam.SetD1(6);
			beam.SetD2(3);
			beam.SetD3(3);
			beam.SetD4(5.125);
			beam.SetD5(4.5);
			beam.SetD6(3);
			beam.SetD7(44.375);
			beam.SetW1(18.4375);
			beam.SetW2(3);
			beam.SetW3(13.125);
			beam.SetW4(3);
			beam.SetW5(30);
			beam.SetW6(30);
			beam.SetT1(6.125);
			beam.SetT2(6.125);
			beam.SetC1(1);
			beam.SetC2(15);
			beam.SetN1(0.02);
			beam.SetN2(-0.02);


			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -30.0));
			Assert::IsTrue(IsEqual(box.Right(), 30.0));
			Assert::IsTrue(IsEqual(box.Top(), 69.9));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.0));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
		
			Assert::IsTrue(IsEqual(props.GetArea(), 1119.03125));
			Assert::IsTrue(IsEqual(props.GetIxx(), 798071.07781859976));
			Assert::IsTrue(IsEqual(props.GetIyy(), 158329.51421028795));
			Assert::IsTrue(IsEqual(props.GetIxy(), -7399.6791562527796));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), -0.22117344801586084));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 39.565942803019738));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 29.778826551984139));
			Assert::IsTrue(IsEqual(props.GetXright(), 30.221173448015861));
			Assert::IsTrue(IsEqual(props.GetYtop(), 69.9 - 39.565942803019738));
			Assert::IsTrue(IsEqual(props.GetYbottom(), 39.565942803019738));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 301.89593547481729));
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
			std::vector<Point2d> points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 21);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d( 18.1875, 0.0000));
			Assert::IsTrue(points[i++] == Point2d( 19.1875, 1.0000));
			Assert::IsTrue(points[i++] == Point2d( 19.1875, 5.1250));
			Assert::IsTrue(points[i++] == Point2d( 6.06250, 9.6250));
			Assert::IsTrue(points[i++] == Point2d( 3.06250, 12.625));
			Assert::IsTrue(points[i++] == Point2d( 3.06250, 57.000));
			Assert::IsTrue(points[i++] == Point2d( 6.06250, 60.000));
			Assert::IsTrue(points[i++] == Point2d( 24.5000, 63.000));
			Assert::IsTrue(points[i++] == Point2d( 30.0000, 63.000));
			Assert::IsTrue(points[i++] == Point2d( 30.0000, 69.000));
			Assert::IsTrue(points[i++] == Point2d(-15.0000, 69.900));
			Assert::IsTrue(points[i++] == Point2d(-30.0000, 69.600));
			Assert::IsTrue(points[i++] == Point2d(-30.0000, 63.000));
			Assert::IsTrue(points[i++] == Point2d(-24.5000, 63.000));
			Assert::IsTrue(points[i++] == Point2d(-6.06250, 60.000));
			Assert::IsTrue(points[i++] == Point2d(-3.06250, 57.000));
			Assert::IsTrue(points[i++] == Point2d(-3.06250, 12.625));
			Assert::IsTrue(points[i++] == Point2d(-6.06250, 9.6250));
			Assert::IsTrue(points[i++] == Point2d(-19.1875, 5.1250));
			Assert::IsTrue(points[i++] == Point2d(-19.1875, 1.0000));
			Assert::IsTrue(points[i++] == Point2d(-18.1875, 0.0000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::IsTrue(IsEqual(beamClone.GetD1(), 6.0));
			Assert::IsTrue(IsEqual(beamClone.GetD2(), 3.0));
			Assert::IsTrue(IsEqual(beamClone.GetD3(), 3.0));
			Assert::IsTrue(IsEqual(beamClone.GetD4(), 5.125));
			Assert::IsTrue(IsEqual(beamClone.GetD5(), 4.5));
			Assert::IsTrue(IsEqual(beamClone.GetD6(), 3.0));
			Assert::IsTrue(IsEqual(beamClone.GetD7(), 44.375));
			Assert::IsTrue(IsEqual(beamClone.GetW1(), 18.4375));
			Assert::IsTrue(IsEqual(beamClone.GetW2(), 3.0));
			Assert::IsTrue(IsEqual(beamClone.GetW3(), 13.125));
			Assert::IsTrue(IsEqual(beamClone.GetW4(), 3.0));
			Assert::IsTrue(IsEqual(beamClone.GetW5(), 30.0));
			Assert::IsTrue(IsEqual(beamClone.GetW6(), 30.0));
			Assert::IsTrue(IsEqual(beamClone.GetT1(), 6.125));
			Assert::IsTrue(IsEqual(beamClone.GetT2(), 6.125));
			Assert::IsTrue(IsEqual(beamClone.GetC1(), 1.0));
			Assert::IsTrue(IsEqual(beamClone.GetC2(), 15.0));
			Assert::IsTrue(IsEqual(beamClone.GetN1(), 0.02));
			Assert::IsTrue(IsEqual(beamClone.GetN2(), -0.02));
		}

		TEST_METHOD(PointInShape)
		{
			auto beam = GetTestBeam();
			Point2d pnt(0, 1);
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
			Point2d p1(-50, 0.50);
			Point2d p2(50, 0.50);
			Line2d clipLine(p1, p2);

			auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 5);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d( 18.1875, 0.0));
			Assert::IsTrue(points[i++] == Point2d( 18.6875, 0.5));
			Assert::IsTrue(points[i++] == Point2d(-18.6875, 0.5));
			Assert::IsTrue(points[i++] == Point2d(-18.1875, 0.0));
			Assert::IsTrue(points[i++] == Point2d(18.1875, 0.0));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);
			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsNotNull(clip.get());

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 21);

			i = 0;
			Assert::IsTrue(points[i++] == Point2d( 18.6875, 0.5000));
			Assert::IsTrue(points[i++] == Point2d( 19.1875, 1.0000));
			Assert::IsTrue(points[i++] == Point2d( 19.1875, 5.1250));
			Assert::IsTrue(points[i++] == Point2d( 6.06250, 9.6250));
			Assert::IsTrue(points[i++] == Point2d( 3.06250, 12.625));
			Assert::IsTrue(points[i++] == Point2d( 3.06250, 57.000));
			Assert::IsTrue(points[i++] == Point2d( 6.06250, 60.000));
			Assert::IsTrue(points[i++] == Point2d( 24.5000, 63.000));
			Assert::IsTrue(points[i++] == Point2d( 30.0000, 63.000));
			Assert::IsTrue(points[i++] == Point2d( 30.0000, 69.000));
			Assert::IsTrue(points[i++] == Point2d(-15.0000, 69.900));
			Assert::IsTrue(points[i++] == Point2d(-30.0000, 69.600));
			Assert::IsTrue(points[i++] == Point2d(-30.0000, 63.000));
			Assert::IsTrue(points[i++] == Point2d(-24.5000, 63.000));
			Assert::IsTrue(points[i++] == Point2d(-6.06250, 60.000));
			Assert::IsTrue(points[i++] == Point2d(-3.06250, 57.000));
			Assert::IsTrue(points[i++] == Point2d(-3.06250, 12.625));
			Assert::IsTrue(points[i++] == Point2d(-6.06250, 9.6250));
			Assert::IsTrue(points[i++] == Point2d(-19.1875, 5.1250));
			Assert::IsTrue(points[i++] == Point2d(-19.1875, 1.0000));
			Assert::IsTrue(points[i++] == Point2d(-18.6875, 0.5000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, 1.5, 100, 16.5);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 10);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d( 19.1875, 1.5000));
			Assert::IsTrue(points[i++] == Point2d( 19.1875, 5.1250));
			Assert::IsTrue(points[i++] == Point2d( 6.06250, 9.6250));
			Assert::IsTrue(points[i++] == Point2d( 3.06250, 12.625));
			Assert::IsTrue(points[i++] == Point2d( 3.06250, 16.500));
			Assert::IsTrue(points[i++] == Point2d(-3.06250, 16.500));
			Assert::IsTrue(points[i++] == Point2d(-3.06250, 12.625));
			Assert::IsTrue(points[i++] == Point2d(-6.06250, 9.6250));
			Assert::IsTrue(points[i++] == Point2d(-19.1875, 5.1250));
			Assert::IsTrue(points[i++] == Point2d(-19.1875, 1.5000));
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
			Assert::IsTrue(points.size() == 21);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(118.1875, 100.000));
			Assert::IsTrue(points[i++] == Point2d(119.1875, 101.000));
			Assert::IsTrue(points[i++] == Point2d(119.1875, 105.125));
			Assert::IsTrue(points[i++] == Point2d(106.0625, 109.625));
			Assert::IsTrue(points[i++] == Point2d(103.0625, 112.625));
			Assert::IsTrue(points[i++] == Point2d(103.0625, 157.000));
			Assert::IsTrue(points[i++] == Point2d(106.0625, 160.000));
			Assert::IsTrue(points[i++] == Point2d(124.5000, 163.000));
			Assert::IsTrue(points[i++] == Point2d(130.0000, 163.000));
			Assert::IsTrue(points[i++] == Point2d(130.0000, 169.000));
			Assert::IsTrue(points[i++] == Point2d(85.00000, 169.900));
			Assert::IsTrue(points[i++] == Point2d(70.00000, 169.600));
			Assert::IsTrue(points[i++] == Point2d(70.00000, 163.000));
			Assert::IsTrue(points[i++] == Point2d(75.50000, 163.000));
			Assert::IsTrue(points[i++] == Point2d(93.93750, 160.000));
			Assert::IsTrue(points[i++] == Point2d(96.93750, 157.000));
			Assert::IsTrue(points[i++] == Point2d(96.93750, 112.625));
			Assert::IsTrue(points[i++] == Point2d(93.93750, 109.625));
			Assert::IsTrue(points[i++] == Point2d(80.81250, 105.125));
			Assert::IsTrue(points[i++] == Point2d(80.81250, 101.000));
			Assert::IsTrue(points[i++] == Point2d(81.81250, 100.000));
			Assert::IsTrue(i == points.size());

			props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), area));
			Assert::IsTrue(IsEqual(props.GetIxx(), Ixx));
			Assert::IsTrue(IsEqual(props.GetIyy(), Iyy));
			Assert::IsTrue(IsEqual(props.GetIxy(), Ixy));
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

			Size2d size(-100, -100);
			beam.Offset(size);
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 21);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-81.81250, -100.0000));
			Assert::IsTrue(points[i++] == Point2d(-80.81250, -99.00000));
			Assert::IsTrue(points[i++] == Point2d(-80.81250, -94.87500));
			Assert::IsTrue(points[i++] == Point2d(-93.93750, -90.37500));
			Assert::IsTrue(points[i++] == Point2d(-96.93750, -87.37500));
			Assert::IsTrue(points[i++] == Point2d(-96.93750, -43.00000));
			Assert::IsTrue(points[i++] == Point2d(-93.93750, -40.00000));
			Assert::IsTrue(points[i++] == Point2d(-75.50000, -37.00000));
			Assert::IsTrue(points[i++] == Point2d(-70.00000, -37.00000));
			Assert::IsTrue(points[i++] == Point2d(-70.00000, -31.00000));
			Assert::IsTrue(points[i++] == Point2d(-115.0000, -30.09999));
			Assert::IsTrue(points[i++] == Point2d(-130.0000, -30.39999));
			Assert::IsTrue(points[i++] == Point2d(-130.0000, -37.00000));
			Assert::IsTrue(points[i++] == Point2d(-124.5000, -37.00000));
			Assert::IsTrue(points[i++] == Point2d(-106.0625, -40.00000));
			Assert::IsTrue(points[i++] == Point2d(-103.0625, -43.00000));
			Assert::IsTrue(points[i++] == Point2d(-103.0625, -87.37500));
			Assert::IsTrue(points[i++] == Point2d(-106.0625, -90.37500));
			Assert::IsTrue(points[i++] == Point2d(-119.1875, -94.87500));
			Assert::IsTrue(points[i++] == Point2d(-119.1875, -99.00000));
			Assert::IsTrue(points[i++] == Point2d(-118.1875, -100.0000));
			Assert::IsTrue(i == points.size());

			props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), area));
			Assert::IsTrue(IsEqual(props.GetIxx(), Ixx));
			Assert::IsTrue(IsEqual(props.GetIyy(), Iyy));
			Assert::IsTrue(IsEqual(props.GetIxy(), Ixy));
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
			Assert::IsTrue(*hookPnt == Point2d(130., 100.0));

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
			Assert::IsTrue(*hookPnt == Point2d(70.0, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(130.0, 65.05));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 65.05));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(70.0, 65.05));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(130.0, 30.1));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 30.1));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(70.0, 30.1));

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
			Assert::IsTrue(points.size() == 21);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-18.18750, 2.2273263659492487e-15));
			Assert::IsTrue(points[i++] == Point2d(-19.18750, -0.99999999999999767));
			Assert::IsTrue(points[i++] == Point2d(-19.18750, -5.1249999999999973));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, -9.6250000000000000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, -12.625000000000000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, -57.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, -60.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-24.50000, -63.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-30.00000, -62.999999999999993));
			Assert::IsTrue(points[i++] == Point2d(-30.00000, -69.000000000000000));
			Assert::IsTrue(points[i++] == Point2d( 14.99999, -69.900000000000006));
			Assert::IsTrue(points[i++] == Point2d( 29.99999, -69.600000000000009));
			Assert::IsTrue(points[i++] == Point2d( 29.99999, -63.000000000000007));
			Assert::IsTrue(points[i++] == Point2d( 24.49999, -63.000000000000000));
			Assert::IsTrue(points[i++] == Point2d( 6.062499, -60.000000000000000));
			Assert::IsTrue(points[i++] == Point2d( 3.062499, -57.000000000000000));
			Assert::IsTrue(points[i++] == Point2d( 3.062499, -12.625000000000000));
			Assert::IsTrue(points[i++] == Point2d( 6.062499, -9.6250000000000000));
			Assert::IsTrue(points[i++] == Point2d( 19.18750, -5.1250000000000027));
			Assert::IsTrue(points[i++] == Point2d( 19.18750, -1.0000000000000024));
			Assert::IsTrue(points[i++] == Point2d( 18.18750, -2.2273263659492487e-15));
			Assert::IsTrue(i == points.size());
		}
	};
}
