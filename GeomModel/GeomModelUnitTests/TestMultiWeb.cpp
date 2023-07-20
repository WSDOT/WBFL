#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestMultiWeb)
	{
	public:
		
		MultiWeb GetTestBeam()
		{
			// Use some real dimensions (2'-3" by 6' with 3 webs)
			MultiWeb beam;
			beam.SetD1(6.00);
			beam.SetD2(21.00);
			beam.SetW1(13.125);
			beam.SetW2(12.0);
			beam.SetT1(7.25);
			beam.SetT2(5.25);
			beam.SetWebCount(3);

			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -36.0));
			Assert::IsTrue(IsEqual(box.Right(), 36.0));
			Assert::IsTrue(IsEqual(box.Top(), 0.0));
			Assert::IsTrue(IsEqual(box.Bottom(), -27.0));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
		
			Assert::IsTrue(IsEqual(props.GetArea(), 825.75));
			Assert::IsTrue(IsEqual(props.GetIxx(), 50135.30160));
			Assert::IsTrue(IsEqual(props.GetIyy(), 285211.20703));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), -9.1702997275204368));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 36.));
			Assert::IsTrue(IsEqual(props.GetXright(), 36.));
			Assert::IsTrue(IsEqual(props.GetYtop(), 9.17029972752044));
			Assert::IsTrue(IsEqual(props.GetYbottom(), 17.8297002724796));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 276.142776249772));
		}

		TEST_METHOD(FurthestDistance)
		{
			auto beam = GetTestBeam();

			Point2d p1(-100, 20);
			Point2d p2(100, 20);
			Line2d line(p1, p2);

			// Shape on right
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 47.000));

			// shape on left
			p1.Move(100, 20);
			p2.Move(-100, 20);
			line.ThroughPoints(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -20.000));
		}

		TEST_METHOD(PolyPoints)
		{
			auto beam = GetTestBeam();
			std::vector<Point2d> points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 19);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0, 0));
			Assert::IsTrue(points[i++] == Point2d(-36, 0));
			Assert::IsTrue(points[i++] == Point2d(-36, -6));
			Assert::IsTrue(points[i++] == Point2d(-22.875, -6));
			Assert::IsTrue(points[i++] == Point2d(-21.875, -27));
			Assert::IsTrue(points[i++] == Point2d(-16.625, -27));
			Assert::IsTrue(points[i++] == Point2d(-15.625, -6));
			Assert::IsTrue(points[i++] == Point2d(-3.625, -6));
			Assert::IsTrue(points[i++] == Point2d(-2.625, -27));
			Assert::IsTrue(points[i++] == Point2d(0, -27));
			Assert::IsTrue(points[i++] == Point2d(2.625, -27));
			Assert::IsTrue(points[i++] == Point2d(3.625, -6));
			Assert::IsTrue(points[i++] == Point2d(15.625, -6));
			Assert::IsTrue(points[i++] == Point2d(16.625, -27));
			Assert::IsTrue(points[i++] == Point2d(21.875, -27));
			Assert::IsTrue(points[i++] == Point2d(22.875, -6));
			Assert::IsTrue(points[i++] == Point2d(36, -6));
			Assert::IsTrue(points[i++] == Point2d(36, 0));
			Assert::IsTrue(points[i++] == Point2d(0, 0));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::IsTrue(IsEqual(beamClone.GetD1(),6.00));
			Assert::IsTrue(IsEqual(beamClone.GetD2(),21.00));
			Assert::IsTrue(IsEqual(beamClone.GetW1(),13.125));
			Assert::IsTrue(IsEqual(beamClone.GetW2(),12.0));
			Assert::IsTrue(IsEqual(beamClone.GetT1(),7.25));
			Assert::IsTrue(IsEqual(beamClone.GetT2(),5.25));
			Assert::AreEqual(beamClone.GetWebCount(),(WebIndexType)3);
		}

		TEST_METHOD(PointInShape)
		{
			auto beam = GetTestBeam();
			Point2d pnt(0, -5);
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
			Point2d p1(-100, -10.0);
			Point2d p2(100, -10.0);
			Line2d clipLine(p1, p2);

			auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 13);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-22.68452, -10));
			Assert::IsTrue(points[i++] == Point2d(-21.875, -27));
			Assert::IsTrue(points[i++] == Point2d(-16.625, -27));
			Assert::IsTrue(points[i++] == Point2d(-15.81548, -10));
			Assert::IsTrue(points[i++] == Point2d(-3.43452, -10));
			Assert::IsTrue(points[i++] == Point2d(-2.625, -27));
			Assert::IsTrue(points[i++] == Point2d(0, -27));
			Assert::IsTrue(points[i++] == Point2d(2.625, -27));
			Assert::IsTrue(points[i++] == Point2d(3.43452, -10));
			Assert::IsTrue(points[i++] == Point2d(15.81548, -10));
			Assert::IsTrue(points[i++] == Point2d(16.625, -27));
			Assert::IsTrue(points[i++] == Point2d(21.875, -27));
			Assert::IsTrue(points[i++] == Point2d(22.68452, -10));

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);
			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsNotNull(clip.get());

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 18);

			i = 0;
			Assert::IsTrue(points[i++] == Point2d(0, 0));
			Assert::IsTrue(points[i++] == Point2d(-36, 0));
			Assert::IsTrue(points[i++] == Point2d(-36, -6));
			Assert::IsTrue(points[i++] == Point2d(-22.875, -6));
			Assert::IsTrue(points[i++] == Point2d(-22.68452, -10));
			Assert::IsTrue(points[i++] == Point2d(-15.815476, -10));
			Assert::IsTrue(points[i++] == Point2d(-15.625, -6));
			Assert::IsTrue(points[i++] == Point2d(-3.625, -6));
			Assert::IsTrue(points[i++] == Point2d(-3.43452, -10));
			Assert::IsTrue(points[i++] == Point2d(3.43452, -10));
			Assert::IsTrue(points[i++] == Point2d(3.625, -6));
			Assert::IsTrue(points[i++] == Point2d(15.625, -6));
			Assert::IsTrue(points[i++] == Point2d(15.815476, -10));
			Assert::IsTrue(points[i++] == Point2d(22.68452, -10));
			Assert::IsTrue(points[i++] == Point2d(22.875, -6));
			Assert::IsTrue(points[i++] == Point2d(36, -6));
			Assert::IsTrue(points[i++] == Point2d(36, 0));
			Assert::IsTrue(points[i++] == Point2d(0, 0));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-100, -7, 100, 10);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 18);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0, 0));
			Assert::IsTrue(points[i++] == Point2d(-36, 0));
			Assert::IsTrue(points[i++] == Point2d(-36, -6));
			Assert::IsTrue(points[i++] == Point2d(-22.875, -6));
			Assert::IsTrue(points[i++] == Point2d(-22.82738, -7));
			Assert::IsTrue(points[i++] == Point2d(-15.67262, -7));
			Assert::IsTrue(points[i++] == Point2d(-15.625, -6));
			Assert::IsTrue(points[i++] == Point2d(-3.625, -6));
			Assert::IsTrue(points[i++] == Point2d(-3.57738, -7));
			Assert::IsTrue(points[i++] == Point2d(3.57738, -7));
			Assert::IsTrue(points[i++] == Point2d(3.625, -6));
			Assert::IsTrue(points[i++] == Point2d(15.625, -6));
			Assert::IsTrue(points[i++] == Point2d(15.67262, -7));
			Assert::IsTrue(points[i++] == Point2d(22.82738, -7));
			Assert::IsTrue(points[i++] == Point2d(22.875, -6));
			Assert::IsTrue(points[i++] == Point2d(36, -6));
			Assert::IsTrue(points[i++] == Point2d(36, 0));
			Assert::IsTrue(points[i++] == Point2d(0, 0));
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
			Assert::IsTrue(points[i++] == Point2d(100, 100));
			Assert::IsTrue(points[i++] == Point2d(64, 100));
			Assert::IsTrue(points[i++] == Point2d(64, 94));
			Assert::IsTrue(points[i++] == Point2d(77.125, 94));
			Assert::IsTrue(points[i++] == Point2d(78.125, 73));
			Assert::IsTrue(points[i++] == Point2d(83.375, 73));
			Assert::IsTrue(points[i++] == Point2d(84.375, 94));
			Assert::IsTrue(points[i++] == Point2d(96.375, 94));
			Assert::IsTrue(points[i++] == Point2d(97.375, 73));
			Assert::IsTrue(points[i++] == Point2d(100, 73));
			Assert::IsTrue(points[i++] == Point2d(102.625, 73));
			Assert::IsTrue(points[i++] == Point2d(103.625, 94));
			Assert::IsTrue(points[i++] == Point2d(115.625, 94));
			Assert::IsTrue(points[i++] == Point2d(116.625, 73));
			Assert::IsTrue(points[i++] == Point2d(121.875, 73));
			Assert::IsTrue(points[i++] == Point2d(122.875, 94));
			Assert::IsTrue(points[i++] == Point2d(136, 94));
			Assert::IsTrue(points[i++] == Point2d(136, 100));
			Assert::IsTrue(points[i++] == Point2d(100, 100));
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

			Size2d size(100, 100);
			beam.Offset(size);
			auto points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 19);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100, 100));
			Assert::IsTrue(points[i++] == Point2d(64, 100));
			Assert::IsTrue(points[i++] == Point2d(64, 94));
			Assert::IsTrue(points[i++] == Point2d(77.125, 94));
			Assert::IsTrue(points[i++] == Point2d(78.125, 73));
			Assert::IsTrue(points[i++] == Point2d(83.375, 73));
			Assert::IsTrue(points[i++] == Point2d(84.375, 94));
			Assert::IsTrue(points[i++] == Point2d(96.375, 94));
			Assert::IsTrue(points[i++] == Point2d(97.375, 73));
			Assert::IsTrue(points[i++] == Point2d(100, 73));
			Assert::IsTrue(points[i++] == Point2d(102.625, 73));
			Assert::IsTrue(points[i++] == Point2d(103.625, 94));
			Assert::IsTrue(points[i++] == Point2d(115.625, 94));
			Assert::IsTrue(points[i++] == Point2d(116.625, 73));
			Assert::IsTrue(points[i++] == Point2d(121.875, 73));
			Assert::IsTrue(points[i++] == Point2d(122.875, 94));
			Assert::IsTrue(points[i++] == Point2d(136, 94));
			Assert::IsTrue(points[i++] == Point2d(136, 100));
			Assert::IsTrue(points[i++] == Point2d(100, 100));
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
			Assert::IsTrue(*hookPnt == Point2d(136, 127));

			// BottomCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100, 127));

			// BottomRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(64, 127));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(136, 113.5));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100, 113.5));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(64, 113.5));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(136, 100));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100, 100));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(64, 100));

			// HookPoint
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::HookPoint, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::HookPoint);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100, 100));
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
			Assert::IsTrue(points[i++] == Point2d(0, 0));
			Assert::IsTrue(points[i++] == Point2d(36, 0));
			Assert::IsTrue(points[i++] == Point2d(36, 6));
			Assert::IsTrue(points[i++] == Point2d(22.875, 6));
			Assert::IsTrue(points[i++] == Point2d(21.875, 27));
			Assert::IsTrue(points[i++] == Point2d(16.625, 27));
			Assert::IsTrue(points[i++] == Point2d(15.625, 6));
			Assert::IsTrue(points[i++] == Point2d(3.625, 6));
			Assert::IsTrue(points[i++] == Point2d(2.625, 27));
			Assert::IsTrue(points[i++] == Point2d(0, 27));
			Assert::IsTrue(points[i++] == Point2d(-2.625, 27));
			Assert::IsTrue(points[i++] == Point2d(-3.625, 6));
			Assert::IsTrue(points[i++] == Point2d(-15.625, 6));
			Assert::IsTrue(points[i++] == Point2d(-16.625, 27));
			Assert::IsTrue(points[i++] == Point2d(-21.875, 27));
			Assert::IsTrue(points[i++] == Point2d(-22.875, 6));
			Assert::IsTrue(points[i++] == Point2d(-36, 6));
			Assert::IsTrue(points[i++] == Point2d(-36, 0));
			Assert::IsTrue(points[i++] == Point2d(0, 0));
			Assert::IsTrue(i == points.size());
		}
	};
}
