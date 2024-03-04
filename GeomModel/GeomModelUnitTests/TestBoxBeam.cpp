#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestBoxBeam)
	{
	public:
		
		BoxBeam GetTestBeam()
		{
			BoxBeam beam;

			// TXDOT Box Beam Type 4B40
			beam.SetH1(5.5);
			beam.SetH2(29.5);
			beam.SetH3(5.0);
			beam.SetH4(4.0);
			beam.SetH5(3.0);
			beam.SetH6(5.0);
			beam.SetH7(17.0);
			beam.SetW1(3.0);
			beam.SetW2(5.0);
			beam.SetW3(27.75);
			beam.SetW4(5.0);
			beam.SetF1(5.0);
			beam.SetF2(5.0);
			beam.SetC1(0.0);

			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -23.875));
			Assert::IsTrue(IsEqual(box.Right(), 23.875));
			Assert::IsTrue(IsEqual(box.Top(), 40.0));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.0));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
		
			Assert::IsTrue(IsEqual(props.GetArea(), 969.375));
			Assert::IsTrue(IsEqual(props.GetIxx(), 185480.77672323846));
			Assert::IsTrue(IsEqual(props.GetIyy(), 236459.59049479163));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 18.731990113905013));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 23.875));
			Assert::IsTrue(IsEqual(props.GetXright(), 23.875));
			Assert::IsTrue(IsEqual(props.GetYtop(), 21.268009886094987));
			Assert::IsTrue(IsEqual(props.GetYbottom(), 18.731990113905013));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 178.12741699796953));
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
			Assert::IsTrue(points.size() == 13);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0, 0.0));
			Assert::IsTrue(points[i++] == Point2d(23.875, 0.0));
			Assert::IsTrue(points[i++] == Point2d(23.875, 17.0));
			Assert::IsTrue(points[i++] == Point2d(18.875, 22.0));
			Assert::IsTrue(points[i++] == Point2d(18.875, 33.0));
			Assert::IsTrue(points[i++] == Point2d(21.875, 36.0));
			Assert::IsTrue(points[i++] == Point2d(21.875, 40.0));
			Assert::IsTrue(points[i++] == Point2d(-21.875, 40.0));
			Assert::IsTrue(points[i++] == Point2d(-21.875, 36.0));
			Assert::IsTrue(points[i++] == Point2d(-18.875, 33.0));
			Assert::IsTrue(points[i++] == Point2d(-18.875, 22.0));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 17.0));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 0.0));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::IsTrue(IsEqual(beamClone.GetH1(), 5.5));
			Assert::IsTrue(IsEqual(beamClone.GetH2(), 29.5));
			Assert::IsTrue(IsEqual(beamClone.GetH3(), 5.0));
			Assert::IsTrue(IsEqual(beamClone.GetH4(), 4.0));
			Assert::IsTrue(IsEqual(beamClone.GetH5(), 3.0));
			Assert::IsTrue(IsEqual(beamClone.GetH6(), 5.0));
			Assert::IsTrue(IsEqual(beamClone.GetH7(), 17.0));
			Assert::IsTrue(IsEqual(beamClone.GetW1(), 3.0));
			Assert::IsTrue(IsEqual(beamClone.GetW2(), 5.0));
			Assert::IsTrue(IsEqual(beamClone.GetW3(), 27.75));
			Assert::IsTrue(IsEqual(beamClone.GetW4(), 5.0));
			Assert::IsTrue(IsEqual(beamClone.GetF1(), 5.0));
			Assert::IsTrue(IsEqual(beamClone.GetF2(), 5.0));
			Assert::IsTrue(IsEqual(beamClone.GetC1(), 0.0));
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
			Assert::IsTrue(points.size() == 6);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0, 0.0));
			Assert::IsTrue(points[i++] == Point2d(23.875, 0.0));
			Assert::IsTrue(points[i++] == Point2d(23.875, 0.5));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 0.5));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 0.0));
			Assert::IsTrue(points[i++] == Point2d(0.0, 0.0));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);
			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsNotNull(clip.get());

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 12);

			i = 0;
			Assert::IsTrue(points[i++] == Point2d(23.875, 0.5));
			Assert::IsTrue(points[i++] == Point2d(23.875, 17.0));
			Assert::IsTrue(points[i++] == Point2d(18.875, 22.0));
			Assert::IsTrue(points[i++] == Point2d(18.875, 33.0));
			Assert::IsTrue(points[i++] == Point2d(21.875, 36.0));
			Assert::IsTrue(points[i++] == Point2d(21.875, 40.0));
			Assert::IsTrue(points[i++] == Point2d(-21.875, 40.0));
			Assert::IsTrue(points[i++] == Point2d(-21.875, 36.0));
			Assert::IsTrue(points[i++] == Point2d(-18.875, 33.0));
			Assert::IsTrue(points[i++] == Point2d(-18.875, 22.0));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 17.0));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 0.5));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, 1.5, 100, 16.5);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 4);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(23.875, 1.5));
			Assert::IsTrue(points[i++] == Point2d(23.875, 16.5));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 16.5));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 1.5));
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
			Assert::IsTrue(points.size() == 13);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100, 100));
			Assert::IsTrue(points[i++] == Point2d(123.875, 100));
			Assert::IsTrue(points[i++] == Point2d(123.875, 117));
			Assert::IsTrue(points[i++] == Point2d(118.875, 122));
			Assert::IsTrue(points[i++] == Point2d(118.875, 133));
			Assert::IsTrue(points[i++] == Point2d(121.875, 136));
			Assert::IsTrue(points[i++] == Point2d(121.875, 140));
			Assert::IsTrue(points[i++] == Point2d(78.125, 140));
			Assert::IsTrue(points[i++] == Point2d(78.125, 136));
			Assert::IsTrue(points[i++] == Point2d(81.125, 133));
			Assert::IsTrue(points[i++] == Point2d(81.125, 122));
			Assert::IsTrue(points[i++] == Point2d(76.125, 117));
			Assert::IsTrue(points[i++] == Point2d(76.125, 100));
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
			Assert::IsTrue(points.size() == 13);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-100.0, -100.0));
			Assert::IsTrue(points[i++] == Point2d(-76.125, -100.0));
			Assert::IsTrue(points[i++] == Point2d(-76.125, -83.0));
			Assert::IsTrue(points[i++] == Point2d(-81.125, -78.0));
			Assert::IsTrue(points[i++] == Point2d(-81.125, -67.0));
			Assert::IsTrue(points[i++] == Point2d(-78.125, -64.0));
			Assert::IsTrue(points[i++] == Point2d(-78.125, -60.0));
			Assert::IsTrue(points[i++] == Point2d(-121.875, -60.0));
			Assert::IsTrue(points[i++] == Point2d(-121.875, -64.0));
			Assert::IsTrue(points[i++] == Point2d(-118.875, -67.0));
			Assert::IsTrue(points[i++] == Point2d(-118.875, -78.0));
			Assert::IsTrue(points[i++] == Point2d(-123.875, -83.0));
			Assert::IsTrue(points[i++] == Point2d(-123.875, -100.0));
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
			Assert::IsTrue(*hookPnt == Point2d(123.875, 100.0));

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
			Assert::IsTrue(*hookPnt == Point2d(76.125, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(123.875, 80.0));

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
			Assert::IsTrue(*hookPnt == Point2d(76.125, 80.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(123.875, 60.0));

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
			Assert::IsTrue(*hookPnt == Point2d(76.125, 60.0));

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
			Assert::IsTrue(points.size() == 13);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.0, 0.0));
			Assert::IsTrue(points[i++] == Point2d(-23.875, 0));
			Assert::IsTrue(points[i++] == Point2d(-23.875, -17));
			Assert::IsTrue(points[i++] == Point2d(-18.875, -22));
			Assert::IsTrue(points[i++] == Point2d(-18.875, -33));
			Assert::IsTrue(points[i++] == Point2d(-21.875, -36));
			Assert::IsTrue(points[i++] == Point2d(-21.875, -40.0));
			Assert::IsTrue(points[i++] == Point2d(21.875, -40.0));
			Assert::IsTrue(points[i++] == Point2d(21.875, -36.0));
			Assert::IsTrue(points[i++] == Point2d(18.875, -33.0));
			Assert::IsTrue(points[i++] == Point2d(18.875, -22.0));
			Assert::IsTrue(points[i++] == Point2d(23.875, -17.0));
			Assert::IsTrue(points[i++] == Point2d(23.875, 0.0));
			Assert::IsTrue(i == points.size());
		}
		
		TEST_METHOD(Rotate2)
		{
			// there was a bug on shapes implementing ShapeOnCompositeImpl
			// where the hook point did not get moved when the shape was rotated
			// this test confirms the hook points moves
			auto beam = GetTestBeam();
			auto hookPnt_before = *beam.GetHookPoint();
			beam.Rotate(Point2d(5, 5), M_PI / 2);
			auto hookPnt_after = *beam.GetHookPoint();
			Assert::IsFalse(hookPnt_before == hookPnt_after);
		}
	};
}
