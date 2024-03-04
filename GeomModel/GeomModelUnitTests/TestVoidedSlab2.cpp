#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestVoidedSlab2)
	{
	public:
		
		VoidedSlab2 GetTestBeam()
		{
			VoidedSlab2 beam;

			beam.SetHeight(36);
			beam.SetWidth(260);
			beam.SetExteriorVoidDiameter(20);
			beam.SetInteriorVoidDiameter(30);
			beam.SetExteriorVoidElevation(12);
			beam.SetInteriorVoidElevation(18);
			beam.SetInteriorVoidSpacing(45);
			beam.SetExteriorVoidSpacing(45);
			beam.SetVoidCount(5);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -130.0));
			Assert::IsTrue(IsEqual(box.Right(), 130.0));
			Assert::IsTrue(IsEqual(box.Top(), 36.0));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.0));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), 6611.1064281089311));
			Assert::IsTrue(IsEqual(props.GetIxx(), 851120.47291073855));
			Assert::IsTrue(IsEqual(props.GetIyy(), 44640853.286266908));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 18.570239070464662));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
			Assert::IsTrue(IsEqual(props.GetXleft(), 130.0));
			Assert::IsTrue(IsEqual(props.GetXright(), 130.0));
			Assert::IsTrue(IsEqual(props.GetYtop(), 17.429760929535338));
			Assert::IsTrue(IsEqual(props.GetYbottom(), 18.570239070464662));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 592.));
		}

		TEST_METHOD(FurthestDistance)
		{
			auto beam = GetTestBeam();
			Point2d p1(0, 50);
			Point2d p2(100, 50);
			Line2d line(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 50.000));

			// shape on left
			p1.Move(0, -50);
			p2.Move(100, -50);
			line.ThroughPoints(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -50.000));
		}

		TEST_METHOD(PolyPoints)
		{
			auto beam = GetTestBeam();
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 4);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(130.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(130.000000, 36.000000));
			Assert::IsTrue(points[i++] == Point2d(-130.000000, 36.000000));
			Assert::IsTrue(points[i++] == Point2d(-130.000000, 0.000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::AreEqual(beamClone.GetHeight(), 36.);
			Assert::AreEqual(beamClone.GetWidth(), 260.);
			Assert::AreEqual(beamClone.GetExteriorVoidDiameter(), 20.);
			Assert::AreEqual(beamClone.GetInteriorVoidDiameter(), 30.);
			Assert::AreEqual(beamClone.GetExteriorVoidElevation(), 12.);
			Assert::AreEqual(beamClone.GetInteriorVoidElevation(), 18.);
			Assert::AreEqual(beamClone.GetInteriorVoidSpacing(), 45.);
			Assert::AreEqual(beamClone.GetExteriorVoidSpacing(), 45.);
			Assert::AreEqual(beamClone.GetVoidCount(), (IndexType)5);
		}

		TEST_METHOD(PointInShape)
		{
			auto beam = GetTestBeam();
			Point2d pnt(0, 1.0);
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
			Assert::IsTrue(points.size() == 5);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(130.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(130.000000, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(-130.000000, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(-130.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(130.000000, 0.000000));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 4);
			i = 0;
			Assert::IsTrue(points[i++] == Point2d(130.000000, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(130.000000, 36.000000));
			Assert::IsTrue(points[i++] == Point2d(-130.000000, 36.000000));
			Assert::IsTrue(points[i++] == Point2d(-130.000000, 0.500000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, 1.5, 100, 16.5);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 5);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.000000, 16.500000));
			Assert::IsTrue(points[i++] == Point2d(-100.000000, 16.500000));
			Assert::IsTrue(points[i++] == Point2d(-100.000000, 1.500000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 1.500000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 16.500000));
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
			Assert::IsTrue(points.size() == 4);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(230.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(230.000000, 136.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.000000, 136.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.000000, 100.000000));
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
			Assert::IsTrue(points.size() == 4);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(230.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(230.000000, 136.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.000000, 136.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.000000, 100.000000));
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
			Assert::IsTrue(*hookPnt == Point2d(230.0, 100.0));

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
			Assert::IsTrue(*hookPnt == Point2d(-30.0, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(230.0, 82.0));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 82.0));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(-30.0, 82.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(230.0, 64.0));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 64.0));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(-30.0, 64.0));

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

			Point2d c(-24, 0);

			beam.Rotate(c, PI_OVER_2);

			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 4);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-24.000000, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(-60.000000, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(-60.000000, -106.000000));
			Assert::IsTrue(points[i++] == Point2d(-24.000000, -106.000000));
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
