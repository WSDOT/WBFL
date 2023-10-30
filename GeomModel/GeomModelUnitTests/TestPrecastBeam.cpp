#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestPrecastBeam)
	{
	public:
		
		PrecastBeam GetTestBeam()
		{
			// Use some real dimensions (WSDOT Modified WF100G girder)
			PrecastBeam beam;
			beam.SetW1(6.0);
			beam.SetW2(18.4375);
			beam.SetW3(3.0);
			beam.SetW4(3.0);
			beam.SetW5(13.125);
			beam.SetD1(3.0);
			beam.SetD2(3.0);
			beam.SetD3(3.0);
			beam.SetD4(3.0);
			beam.SetD5(4.5);
			beam.SetD6(5.125);
			beam.SetHeight(100.0);
			beam.SetT1(6.125);
			beam.SetT2(6.125);
			beam.SetC1(1.0);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -30.5));
			Assert::IsTrue(IsEqual(box.Right(), 30.5));
			Assert::IsTrue(IsEqual(box.Top(), 100.0));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
		
			Assert::IsTrue(IsEqual(props.GetArea(), 1118.78125));
			Assert::IsTrue(IsEqual(props.GetIxx(), 1612833.8649339355));
			Assert::IsTrue(IsEqual(props.GetIyy(), 99849.307047526003));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 49.889825586808556));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 30.5));
			Assert::IsTrue(IsEqual(props.GetXright(), 30.5));
			Assert::IsTrue(IsEqual(props.GetYtop(), 100.0 - props.GetCentroid().Y()));
			Assert::IsTrue(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 365.28393667457732));

			Assert::IsTrue(IsEqual(beam.GetHeight(), 100.0));

			Assert::IsTrue(beam.GetWebCount() == 1);
			Assert::IsTrue(beam.GetTopFlangeCount() == 1);
			Assert::IsTrue(IsEqual(beam.GetTopFlangeLocation(0), 0.0));
			Assert::IsTrue(IsEqual(beam.GetTopFlangeWidth(0), 61.0));
			Assert::IsTrue(beam.GetBottomFlangeCount() == 1);
			Assert::IsTrue(IsEqual(beam.GetBottomFlangeLocation(0), 0.0));
			Assert::IsTrue(IsEqual(beam.GetBottomFlangeWidth(0), 38.375));
			Assert::IsTrue(beam.GetMatingSurfaceCount() == 1);
			Assert::IsTrue(IsEqual(beam.GetMatingSurfaceLocation(0), 0.0));
			Assert::IsTrue(IsEqual(beam.GetMatingSurfaceWidth(0), 61.0));
			Assert::IsTrue(IsEqual(beam.GetAvgWebWidth(), 6.125));
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
			Assert::IsTrue(points.size() == 23);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(-24.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, 94.000000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, 91.000000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, 12.625000));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, 9.625000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500, 5.125000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500, 1.000000));
			Assert::IsTrue(points[i++] == Point2d(-18.187500, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(18.187500, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(19.187500, 1.000000));
			Assert::IsTrue(points[i++] == Point2d(19.187500, 5.125000));
			Assert::IsTrue(points[i++] == Point2d(6.062500, 9.625000));
			Assert::IsTrue(points[i++] == Point2d(3.062500, 12.625000));
			Assert::IsTrue(points[i++] == Point2d(3.062500, 91.000000));
			Assert::IsTrue(points[i++] == Point2d(6.062500, 94.000000));
			Assert::IsTrue(points[i++] == Point2d(24.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(30.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(30.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 100.000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::AreEqual(beamClone.GetW1(), 6.0);
			Assert::AreEqual(beamClone.GetW2(), 18.4375);
			Assert::AreEqual(beamClone.GetW3(), 3.0);
			Assert::AreEqual(beamClone.GetW4(), 3.0);
			Assert::AreEqual(beamClone.GetW5(), 13.125);
			Assert::AreEqual(beamClone.GetD1(), 3.0);
			Assert::AreEqual(beamClone.GetD2(), 3.0);
			Assert::AreEqual(beamClone.GetD3(), 3.0);
			Assert::AreEqual(beamClone.GetD4(), 3.0);
			Assert::AreEqual(beamClone.GetD5(), 4.5);
			Assert::AreEqual(beamClone.GetD6(), 5.125);
			Assert::AreEqual(beamClone.GetHeight(), 100.0);
			Assert::AreEqual(beamClone.GetT1(), 6.125);
			Assert::AreEqual(beamClone.GetT2(), 6.125);
			Assert::AreEqual(beamClone.GetC1(), 1.0);
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
			Assert::IsTrue(points.size() == 5);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-18.687500, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(-18.187500, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(18.187500, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(18.687500, 0.500000));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 22);
			i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(-24.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, 94.000000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, 91.000000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, 12.625000));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, 9.625000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500, 5.125000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500, 1.000000));
			Assert::IsTrue(points[i++] == Point2d(-18.687500, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(18.687500, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(19.187500, 1.000000));
			Assert::IsTrue(points[i++] == Point2d(19.187500, 5.125000));
			Assert::IsTrue(points[i++] == Point2d(6.062500, 9.625000));
			Assert::IsTrue(points[i++] == Point2d(3.062500, 12.625000));
			Assert::IsTrue(points[i++] == Point2d(3.062500, 91.000000));
			Assert::IsTrue(points[i++] == Point2d(6.062500, 94.000000));
			Assert::IsTrue(points[i++] == Point2d(24.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(30.500000, 97.000000));
			Assert::IsTrue(points[i++] == Point2d(30.500000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 100.000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, 0.5, 100, 0.6);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 5);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-18.787500, 0.600000));
			Assert::IsTrue(points[i++] == Point2d(-18.687500, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(18.687500, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(18.787500, 0.600000));
			Assert::IsTrue(points[i++] == Point2d(-18.787500, 0.600000));
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
			Assert::IsTrue(points.size() == 23);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.000000, 200.000000));
			Assert::IsTrue(points[i++] == Point2d(69.500000, 200.000000));
			Assert::IsTrue(points[i++] == Point2d(69.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(75.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(93.937500, 194.000000));
			Assert::IsTrue(points[i++] == Point2d(96.937500, 191.000000));
			Assert::IsTrue(points[i++] == Point2d(96.937500, 112.625000));
			Assert::IsTrue(points[i++] == Point2d(93.937500, 109.625000));
			Assert::IsTrue(points[i++] == Point2d(80.812500, 105.125000));
			Assert::IsTrue(points[i++] == Point2d(80.812500, 101.000000));
			Assert::IsTrue(points[i++] == Point2d(81.812500, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(118.187500, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(119.187500, 101.000000));
			Assert::IsTrue(points[i++] == Point2d(119.187500, 105.125000));
			Assert::IsTrue(points[i++] == Point2d(106.062500, 109.625000));
			Assert::IsTrue(points[i++] == Point2d(103.062500, 112.625000));
			Assert::IsTrue(points[i++] == Point2d(103.062500, 191.000000));
			Assert::IsTrue(points[i++] == Point2d(106.062500, 194.000000));
			Assert::IsTrue(points[i++] == Point2d(124.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(130.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(130.500000, 200.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 200.000000));
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
			Assert::IsTrue(points.size() == 23);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.000000, 200.000000));
			Assert::IsTrue(points[i++] == Point2d(69.500000, 200.000000));
			Assert::IsTrue(points[i++] == Point2d(69.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(75.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(93.937500, 194.000000));
			Assert::IsTrue(points[i++] == Point2d(96.937500, 191.000000));
			Assert::IsTrue(points[i++] == Point2d(96.937500, 112.625000));
			Assert::IsTrue(points[i++] == Point2d(93.937500, 109.625000));
			Assert::IsTrue(points[i++] == Point2d(80.812500, 105.125000));
			Assert::IsTrue(points[i++] == Point2d(80.812500, 101.000000));
			Assert::IsTrue(points[i++] == Point2d(81.812500, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(118.187500, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(119.187500, 101.000000));
			Assert::IsTrue(points[i++] == Point2d(119.187500, 105.125000));
			Assert::IsTrue(points[i++] == Point2d(106.062500, 109.625000));
			Assert::IsTrue(points[i++] == Point2d(103.062500, 112.625000));
			Assert::IsTrue(points[i++] == Point2d(103.062500, 191.000000));
			Assert::IsTrue(points[i++] == Point2d(106.062500, 194.000000));
			Assert::IsTrue(points[i++] == Point2d(124.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(130.500000, 197.000000));
			Assert::IsTrue(points[i++] == Point2d(130.500000, 200.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 200.000000));
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
			Assert::IsTrue(*hookPnt == Point2d(130.5, 100.0));

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
			Assert::IsTrue(*hookPnt == Point2d(69.5, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(130.5, 50.0));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 50.0));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(69.5, 50.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(130.5, 0.0));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 0.0));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(69.5, 0.0));

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
			Assert::IsTrue(points.size() == 23);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-0.000000, -100.000000));
			Assert::IsTrue(points[i++] == Point2d(30.500000, -100.000000));
			Assert::IsTrue(points[i++] == Point2d(30.500000, -97.000000));
			Assert::IsTrue(points[i++] == Point2d(24.500000, -97.000000));
			Assert::IsTrue(points[i++] == Point2d(6.062500, -94.000000));
			Assert::IsTrue(points[i++] == Point2d(3.062500, -91.000000));
			Assert::IsTrue(points[i++] == Point2d(3.062500, -12.625000));
			Assert::IsTrue(points[i++] == Point2d(6.062500, -9.625000));
			Assert::IsTrue(points[i++] == Point2d(19.187500, -5.125000));
			Assert::IsTrue(points[i++] == Point2d(19.187500, -1.000000));
			Assert::IsTrue(points[i++] == Point2d(18.187500, -0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-18.187500, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500, -1.000000));
			Assert::IsTrue(points[i++] == Point2d(-19.187500, -5.125000));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, -9.625000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, -12.625000));
			Assert::IsTrue(points[i++] == Point2d(-3.062500, -91.000000));
			Assert::IsTrue(points[i++] == Point2d(-6.062500, -94.000000));
			Assert::IsTrue(points[i++] == Point2d(-24.500000, -97.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.500000, -97.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.500000, -100.000000));
			Assert::IsTrue(points[i++] == Point2d(-0.000000, -100.000000));
			Assert::IsTrue(i == points.size());
		}
	};
}
