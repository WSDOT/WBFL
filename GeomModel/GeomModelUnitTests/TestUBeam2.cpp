#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestUBeam2)
	{
	public:
		
		UBeam2 GetTestBeam()
		{
			// Use some real dimensions (TXDOT U40 girder)
			UBeam2 beam;
			beam.SetW1(55);
			beam.SetW2(89);
			beam.SetW3(3);
			beam.SetW4(0.375);
			beam.SetW5(8.25);
			beam.SetW6(15.75);
			beam.SetW7(1.75);
			beam.SetD1(40);
			beam.SetD2(8.25);
			beam.SetD3(3);
			beam.SetD4(0.875);
			beam.SetD5(5.875);
			beam.SetD6(21.625);
			beam.SetC1(0.0);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -44.5));
			Assert::IsTrue(IsEqual(box.Right(), 44.5));
			Assert::IsTrue(IsEqual(box.Top(), 40.00));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), 978.1015625));
			Assert::IsTrue(IsEqual(props.GetIxx(), 183371.372367286));
			Assert::IsTrue(IsEqual(props.GetIyy(), 672244.006479706));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 16.3516905452245));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
			Assert::IsTrue(IsEqual(props.GetXleft(), 44.5));
			Assert::IsTrue(IsEqual(props.GetXright(), 44.5));
			Assert::IsTrue(IsEqual(props.GetYtop(), 23.6483094547755));
			Assert::IsTrue(IsEqual(props.GetYbottom(), 16.3516905452245));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 294.425976857583));

			Assert::IsTrue(IsEqual(beam.GetHeight(), 40.0));

			Assert::IsTrue(IsEqual(beam.GetSlope(0), -3.970149));
			Assert::IsTrue(IsEqual(beam.GetSlope(1), 3.970149));

			Assert::IsTrue(IsEqual(beam.GetTopWidth(), 89.0));

			Assert::IsTrue(beam.GetTopFlangeCount() == 2);
			Assert::IsTrue(IsEqual(beam.GetTopFlangeWidth(0), 15.75));
			Assert::IsTrue(IsEqual(beam.GetTopFlangeWidth(1), 15.75));

			Assert::IsTrue(IsEqual(beam.GetWebSpacing(), 70.022086466165405));

			Assert::IsTrue(beam.GetWebCount() == 2);
			Assert::IsTrue(IsEqual(beam.GetWebLocation(0), -35.011043233082702));
			Assert::IsTrue(IsEqual(beam.GetWebLocation(1), 35.011043233082702));
		}

		TEST_METHOD(FurthestDistance)
		{
			auto beam = GetTestBeam();
			// Shape on right
			Point2d p1(0, 20);
			Point2d p2(100, 20);
			Line2d line(p1, p2);

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
			Assert::IsTrue(points.size() == 19);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.500000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-35.875000, 33.250000));
			Assert::IsTrue(points[i++] == Point2d(-44.125000, 34.125000));
			Assert::IsTrue(points[i++] == Point2d(-44.500000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(-28.750000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.000000, 18.375000));
			Assert::IsTrue(points[i++] == Point2d(-25.205357, 11.250000));
			Assert::IsTrue(points[i++] == Point2d(-22.205357, 8.250000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 8.250000));
			Assert::IsTrue(points[i++] == Point2d(22.205357, 8.250000));
			Assert::IsTrue(points[i++] == Point2d(25.205357, 11.250000));
			Assert::IsTrue(points[i++] == Point2d(27.000000, 18.375000));
			Assert::IsTrue(points[i++] == Point2d(28.750000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(44.500000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(44.125000, 34.125000));
			Assert::IsTrue(points[i++] == Point2d(35.875000, 33.250000));
			Assert::IsTrue(points[i++] == Point2d(27.500000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::AreEqual(beam.GetW1(), 55.0);
			Assert::AreEqual(beam.GetW2(), 89.0);
			Assert::AreEqual(beam.GetW3(), 3.0);
			Assert::AreEqual(beam.GetW4(), 0.375);
			Assert::AreEqual(beam.GetW5(), 8.25);
			Assert::AreEqual(beam.GetW6(), 15.75);
			Assert::AreEqual(beam.GetW7(), 1.75);
			Assert::AreEqual(beam.GetD1(), 40.0);
			Assert::AreEqual(beam.GetD2(), 8.25);
			Assert::AreEqual(beam.GetD3(), 3.0);
			Assert::AreEqual(beam.GetD4(), 0.875);
			Assert::AreEqual(beam.GetD5(), 5.875);
			Assert::AreEqual(beam.GetD6(), 21.625);
			Assert::AreEqual(beam.GetC1(), 0.0);
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
			Point2d p1(-50, 0.50);
			Point2d p2(50, 0.50);
			Line2d clipLine(p1, p2);

			auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			auto points = clip->GetPolyPoints();
			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 6);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.500000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.625940, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(27.625940, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(27.500000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 17);

			i = 0;
			Assert::IsTrue(points[i++] == Point2d(-27.625940, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(-35.875000, 33.250000));
			Assert::IsTrue(points[i++] == Point2d(-44.125000, 34.125000));
			Assert::IsTrue(points[i++] == Point2d(-44.500000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(-28.750000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.000000, 18.375000));
			Assert::IsTrue(points[i++] == Point2d(-25.205357, 11.250000));
			Assert::IsTrue(points[i++] == Point2d(-22.205357, 8.250000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 8.250000));
			Assert::IsTrue(points[i++] == Point2d(22.205357, 8.250000));
			Assert::IsTrue(points[i++] == Point2d(25.205357, 11.250000));
			Assert::IsTrue(points[i++] == Point2d(27.000000, 18.375000));
			Assert::IsTrue(points[i++] == Point2d(28.750000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(44.500000, 40.000000));
			Assert::IsTrue(points[i++] == Point2d(44.125000, 34.125000));
			Assert::IsTrue(points[i++] == Point2d(35.875000, 33.250000));
			Assert::IsTrue(points[i++] == Point2d(27.625940, 0.500000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, 0.5, 100, 0.6);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 4);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-27.625940, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(-27.651128, 0.600000));
			Assert::IsTrue(points[i++] == Point2d(27.651128, 0.600000));
			Assert::IsTrue(points[i++] == Point2d(27.625940, 0.500000));
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
			Assert::IsTrue(points.size() == 19);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(72.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(64.125000, 133.250000));
			Assert::IsTrue(points[i++] == Point2d(55.875000, 134.125000));
			Assert::IsTrue(points[i++] == Point2d(55.500000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(71.250000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(73.000000, 118.375000));
			Assert::IsTrue(points[i++] == Point2d(74.794643, 111.250000));
			Assert::IsTrue(points[i++] == Point2d(77.794643, 108.250000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 108.250000));
			Assert::IsTrue(points[i++] == Point2d(122.205357, 108.250000));
			Assert::IsTrue(points[i++] == Point2d(125.205357, 111.250000));
			Assert::IsTrue(points[i++] == Point2d(127.000000, 118.375000));
			Assert::IsTrue(points[i++] == Point2d(128.750000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(144.500000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(144.125000, 134.125000));
			Assert::IsTrue(points[i++] == Point2d(135.875000, 133.250000));
			Assert::IsTrue(points[i++] == Point2d(127.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
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
			Assert::IsTrue(points.size() == 19);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(72.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(64.125000, 133.250000));
			Assert::IsTrue(points[i++] == Point2d(55.875000, 134.125000));
			Assert::IsTrue(points[i++] == Point2d(55.500000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(71.250000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(73.000000, 118.375000));
			Assert::IsTrue(points[i++] == Point2d(74.794643, 111.250000));
			Assert::IsTrue(points[i++] == Point2d(77.794643, 108.250000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 108.250000));
			Assert::IsTrue(points[i++] == Point2d(122.205357, 108.250000));
			Assert::IsTrue(points[i++] == Point2d(125.205357, 111.250000));
			Assert::IsTrue(points[i++] == Point2d(127.000000, 118.375000));
			Assert::IsTrue(points[i++] == Point2d(128.750000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(144.500000, 140.000000));
			Assert::IsTrue(points[i++] == Point2d(144.125000, 134.125000));
			Assert::IsTrue(points[i++] == Point2d(135.875000, 133.250000));
			Assert::IsTrue(points[i++] == Point2d(127.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
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
			Assert::IsTrue(*hookPnt == Point2d(144.5, 100.0));

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
			Assert::IsTrue(*hookPnt == Point2d(55.5, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(144.5, 80.0));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 80.0));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(55.5, 80.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(144.5, 60.0));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 60.0));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(55.5, 60.0));

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
			Assert::IsTrue(points.size() == 19);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(27.500000, -0.000000));
			Assert::IsTrue(points[i++] == Point2d(35.875000, -33.250000));
			Assert::IsTrue(points[i++] == Point2d(44.125000, -34.125000));
			Assert::IsTrue(points[i++] == Point2d(44.500000, -40.000000));
			Assert::IsTrue(points[i++] == Point2d(28.750000, -40.000000));
			Assert::IsTrue(points[i++] == Point2d(27.000000, -18.375000));
			Assert::IsTrue(points[i++] == Point2d(25.205357, -11.250000));
			Assert::IsTrue(points[i++] == Point2d(22.205357, -8.250000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, -8.250000));
			Assert::IsTrue(points[i++] == Point2d(-22.205357, -8.250000));
			Assert::IsTrue(points[i++] == Point2d(-25.205357, -11.250000));
			Assert::IsTrue(points[i++] == Point2d(-27.000000, -18.375000));
			Assert::IsTrue(points[i++] == Point2d(-28.750000, -40.000000));
			Assert::IsTrue(points[i++] == Point2d(-44.500000, -40.000000));
			Assert::IsTrue(points[i++] == Point2d(-44.125000, -34.125000));
			Assert::IsTrue(points[i++] == Point2d(-35.875000, -33.250000));
			Assert::IsTrue(points[i++] == Point2d(-27.500000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(i == points.size());
		}
	};
}
