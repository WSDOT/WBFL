#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestMultiWeb2)
	{
	public:
		
		MultiWeb2 GetTestBeam()
		{
			MultiWeb2 beam;
			beam.SetH1(20.00);
			beam.SetH2(3.00);
			beam.SetH3(6.00);
			beam.SetW1(30.00);
			beam.SetW2(36.0);
			beam.SetT1(1.25);
			beam.SetT2(5.25);
			beam.SetT3(2.25);
			beam.SetT4(2.25);
			beam.SetT5(6.00);
			beam.SetF1(3.00);
			beam.SetF2(5.00);
			beam.SetWebCount(4);
			return beam;
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -103.25));
			Assert::IsTrue(IsEqual(box.Right(), 103.25));
			Assert::IsTrue(IsEqual(box.Top(), 29.00));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
		
			Assert::IsTrue(IsEqual(props.GetArea(), 2488.5));
			Assert::IsTrue(IsEqual(props.GetIxx(), 121537.36857042369));
			Assert::IsTrue(IsEqual(props.GetIyy(), 7576799.3906250019));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 20.942837050431994));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 103.25));
			Assert::IsTrue(IsEqual(props.GetXright(), 103.25));
			Assert::IsTrue(IsEqual(props.GetYtop(), 8.0571629495680064));
			Assert::IsTrue(IsEqual(props.GetYbottom(), 20.942837050431994));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 551.64667921998034));
		}

		TEST_METHOD(FurthestDistance)
		{
			auto beam = GetTestBeam();

			// Shape on right of line
			Point2d p1(-100, 20);
			Point2d p2(100, 20);
			Line2d line(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 20.000));

			// shape on left of line
			p1.Move(100, 20);
			p2.Move(-100, 20);
			line.ThroughPoints(p1, p2);
			Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 9.000));
		}

		TEST_METHOD(PolyPoints)
		{
			auto beam = GetTestBeam();
			std::vector<Point2d> points = beam.GetPolyPoints();
			points = beam.GetPolyPoints();
			Assert::IsTrue(points.size() == 29);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-103.25, 29));
			Assert::IsTrue(points[i++] == Point2d(103.25, 29));
			Assert::IsTrue(points[i++] == Point2d(103.25, 23));
			Assert::IsTrue(points[i++] == Point2d(76.25, 20));
			Assert::IsTrue(points[i++] == Point2d(73.25, 17));
			Assert::IsTrue(points[i++] == Point2d(72, 0));
			Assert::IsTrue(points[i++] == Point2d(66.75, 0));
			Assert::IsTrue(points[i++] == Point2d(64.5, 17));
			Assert::IsTrue(points[i++] == Point2d(61.5, 20));
			Assert::IsTrue(points[i++] == Point2d(33.5, 20));
			Assert::IsTrue(points[i++] == Point2d(28.5, 15));
			Assert::IsTrue(points[i++] == Point2d(26.25, 0));
			Assert::IsTrue(points[i++] == Point2d(20.25, 0));
			Assert::IsTrue(points[i++] == Point2d(18, 15));
			Assert::IsTrue(points[i++] == Point2d(13, 20));
			Assert::IsTrue(points[i++] == Point2d(-13, 20));
			Assert::IsTrue(points[i++] == Point2d(-18, 15));
			Assert::IsTrue(points[i++] == Point2d(-20.25, 0));
			Assert::IsTrue(points[i++] == Point2d(-26.25, 0));
			Assert::IsTrue(points[i++] == Point2d(-28.5, 15));
			Assert::IsTrue(points[i++] == Point2d(-33.5, 20));
			Assert::IsTrue(points[i++] == Point2d(-61.5, 20));
			Assert::IsTrue(points[i++] == Point2d(-64.5, 17));
			Assert::IsTrue(points[i++] == Point2d(-66.75, 0));
			Assert::IsTrue(points[i++] == Point2d(-72, 0));
			Assert::IsTrue(points[i++] == Point2d(-73.25, 17));
			Assert::IsTrue(points[i++] == Point2d(-76.25, 20));
			Assert::IsTrue(points[i++] == Point2d(-103.25, 23));
			Assert::IsTrue(points[i++] == Point2d(-103.25, 29));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::IsTrue(IsEqual(beamClone.GetH1(),20.00));
			Assert::IsTrue(IsEqual(beamClone.GetH2(),3.00));
			Assert::IsTrue(IsEqual(beamClone.GetH3(),6.00));
			Assert::IsTrue(IsEqual(beamClone.GetW1(),30.00));
			Assert::IsTrue(IsEqual(beamClone.GetW2(),36.0));
			Assert::IsTrue(IsEqual(beamClone.GetT1(),1.25));
			Assert::IsTrue(IsEqual(beamClone.GetT2(),5.25));
			Assert::IsTrue(IsEqual(beamClone.GetT3(),2.25));
			Assert::IsTrue(IsEqual(beamClone.GetT4(),2.25));
			Assert::IsTrue(IsEqual(beamClone.GetT5(),6.00));
			Assert::IsTrue(IsEqual(beamClone.GetF1(),3.00));
			Assert::IsTrue(IsEqual(beamClone.GetF2(),5.00));
			Assert::AreEqual(beamClone.GetWebCount(),(WebIndexType)4);
		}

		TEST_METHOD(PointInShape)
		{
			auto beam = GetTestBeam();
			Point2d pnt(0, 25);
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
			Point2d p1(-100, 10.0);
			Point2d p2(100, 10.0);
			Line2d clipLine(p1, p2);

			auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 16);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(72.735294117647058, 10.0000));
			Assert::IsTrue(points[i++] == Point2d(72.000000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(66.750000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(65.426470588235290, 10.0000));
			Assert::IsTrue(points[i++] == Point2d(27.750000000000000, 10.0000));
			Assert::IsTrue(points[i++] == Point2d(26.250000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(20.250000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(18.750000000000000, 10.0000));
			Assert::IsTrue(points[i++] == Point2d(-18.750000000000000, 10.0000));
			Assert::IsTrue(points[i++] == Point2d(-20.250000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(-26.250000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(-27.750000000000000, 10.0000));
			Assert::IsTrue(points[i++] == Point2d(-65.426470588235290, 10.0000));
			Assert::IsTrue(points[i++] == Point2d(-66.750000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(-72.000000000000000, 0.00000));
			Assert::IsTrue(points[i++] == Point2d(-72.735294117647058, 10.0000));

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);
			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsNotNull(clip.get());

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 29);

			i = 0;
			Assert::IsTrue(points[i++] == Point2d(-103.25000000000000, 29.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(103.25000000000000, 29.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(103.25000000000000, 23.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(76.250000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(73.250000000000000, 17.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(72.735294117647058, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(65.426470588235290, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(64.500000000000000, 17.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(61.500000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(33.500000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(28.500000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(27.750000000000000, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.750000000000000, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.000000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(13.000000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-13.000000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-18.000000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-18.750000000000000, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-27.750000000000000, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-28.500000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-33.500000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-61.500000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-64.500000000000000, 17.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-65.426470588235290, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-72.735294117647058, 10.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-73.250000000000000, 17.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-76.250000000000000, 20.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-103.25000000000000, 23.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-103.25000000000000, 29.000000000000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(ClipIn)
		{
			auto beam = GetTestBeam();
			Rect2d clipRect(-50, 5, 50, 15);
			auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
			Assert::IsNotNull(clip.get());

			auto points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 11);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(50.000000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(28.500000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(27.000000000000000, 5.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(19.500000000000000, 5.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(18.000000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-18.000000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-19.500000000000000, 5.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-27.000000000000000, 5.0000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-28.500000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(-50.000000000000000, 15.000000000000000));
			Assert::IsTrue(points[i++] == Point2d(50.000000000000000, 15.000000000000002));
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
			Assert::IsTrue(points.size() == 29);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-3.25, 129));
			Assert::IsTrue(points[i++] == Point2d(203.25, 129));
			Assert::IsTrue(points[i++] == Point2d(203.25, 123));
			Assert::IsTrue(points[i++] == Point2d(176.25, 120));
			Assert::IsTrue(points[i++] == Point2d(173.25, 117));
			Assert::IsTrue(points[i++] == Point2d(172, 100));
			Assert::IsTrue(points[i++] == Point2d(166.75, 100));
			Assert::IsTrue(points[i++] == Point2d(164.5, 117));
			Assert::IsTrue(points[i++] == Point2d(161.5, 120));
			Assert::IsTrue(points[i++] == Point2d(133.5, 120));
			Assert::IsTrue(points[i++] == Point2d(128.5, 115));
			Assert::IsTrue(points[i++] == Point2d(126.25, 100));
			Assert::IsTrue(points[i++] == Point2d(120.25, 100));
			Assert::IsTrue(points[i++] == Point2d(118, 115));
			Assert::IsTrue(points[i++] == Point2d(113, 120));
			Assert::IsTrue(points[i++] == Point2d(87, 120));
			Assert::IsTrue(points[i++] == Point2d(82, 115));
			Assert::IsTrue(points[i++] == Point2d(79.75, 100));
			Assert::IsTrue(points[i++] == Point2d(73.75, 100));
			Assert::IsTrue(points[i++] == Point2d(71.5, 115));
			Assert::IsTrue(points[i++] == Point2d(66.5, 120));
			Assert::IsTrue(points[i++] == Point2d(38.5, 120));
			Assert::IsTrue(points[i++] == Point2d(35.5, 117));
			Assert::IsTrue(points[i++] == Point2d(33.25, 100));
			Assert::IsTrue(points[i++] == Point2d(28, 100));
			Assert::IsTrue(points[i++] == Point2d(26.75, 117));
			Assert::IsTrue(points[i++] == Point2d(23.75, 120));
			Assert::IsTrue(points[i++] == Point2d(-3.25, 123));
			Assert::IsTrue(points[i++] == Point2d(-3.25, 129));
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
			Assert::IsTrue(points.size() == 29);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(-3.25, 129));
			Assert::IsTrue(points[i++] == Point2d(203.25, 129));
			Assert::IsTrue(points[i++] == Point2d(203.25, 123));
			Assert::IsTrue(points[i++] == Point2d(176.25, 120));
			Assert::IsTrue(points[i++] == Point2d(173.25, 117));
			Assert::IsTrue(points[i++] == Point2d(172, 100));
			Assert::IsTrue(points[i++] == Point2d(166.75, 100));
			Assert::IsTrue(points[i++] == Point2d(164.5, 117));
			Assert::IsTrue(points[i++] == Point2d(161.5, 120));
			Assert::IsTrue(points[i++] == Point2d(133.5, 120));
			Assert::IsTrue(points[i++] == Point2d(128.5, 115));
			Assert::IsTrue(points[i++] == Point2d(126.25, 100));
			Assert::IsTrue(points[i++] == Point2d(120.25, 100));
			Assert::IsTrue(points[i++] == Point2d(118, 115));
			Assert::IsTrue(points[i++] == Point2d(113, 120));
			Assert::IsTrue(points[i++] == Point2d(87, 120));
			Assert::IsTrue(points[i++] == Point2d(82, 115));
			Assert::IsTrue(points[i++] == Point2d(79.75, 100));
			Assert::IsTrue(points[i++] == Point2d(73.75, 100));
			Assert::IsTrue(points[i++] == Point2d(71.5, 115));
			Assert::IsTrue(points[i++] == Point2d(66.5, 120));
			Assert::IsTrue(points[i++] == Point2d(38.5, 120));
			Assert::IsTrue(points[i++] == Point2d(35.5, 117));
			Assert::IsTrue(points[i++] == Point2d(33.25, 100));
			Assert::IsTrue(points[i++] == Point2d(28, 100));
			Assert::IsTrue(points[i++] == Point2d(26.75, 117));
			Assert::IsTrue(points[i++] == Point2d(23.75, 120));
			Assert::IsTrue(points[i++] == Point2d(-3.25, 123));
			Assert::IsTrue(points[i++] == Point2d(-3.25, 129));
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
			Assert::IsTrue(*hookPnt == Point2d(203.25, 100));

			// BottomCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100, 100));

			// BottomRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::BottomRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(-3.25, 100));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(203.25, 85.5));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100, 85.5));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(-3.25, 85.5));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(203.25, 71));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100, 71));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(-3.25, 71));

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
			Assert::IsTrue(points.size() == 29);

			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(103.25, -29));
			Assert::IsTrue(points[i++] == Point2d(-103.25, -29));
			Assert::IsTrue(points[i++] == Point2d(-103.25, -23));
			Assert::IsTrue(points[i++] == Point2d(-76.25, -20));
			Assert::IsTrue(points[i++] == Point2d(-73.25, -17));
			Assert::IsTrue(points[i++] == Point2d(-72, 0));
			Assert::IsTrue(points[i++] == Point2d(-66.75, 0));
			Assert::IsTrue(points[i++] == Point2d(-64.5, -17));
			Assert::IsTrue(points[i++] == Point2d(-61.5, -20));
			Assert::IsTrue(points[i++] == Point2d(-33.5, -20));
			Assert::IsTrue(points[i++] == Point2d(-28.5, -15));
			Assert::IsTrue(points[i++] == Point2d(-26.25, 0));
			Assert::IsTrue(points[i++] == Point2d(-20.25, 0));
			Assert::IsTrue(points[i++] == Point2d(-18, -15));
			Assert::IsTrue(points[i++] == Point2d(-13, -20));
			Assert::IsTrue(points[i++] == Point2d(13, -20));
			Assert::IsTrue(points[i++] == Point2d(18, -15));
			Assert::IsTrue(points[i++] == Point2d(20.25, 0));
			Assert::IsTrue(points[i++] == Point2d(26.25, 0));
			Assert::IsTrue(points[i++] == Point2d(28.5, -15));
			Assert::IsTrue(points[i++] == Point2d(33.5, -20));
			Assert::IsTrue(points[i++] == Point2d(61.5, -20));
			Assert::IsTrue(points[i++] == Point2d(64.5, -17));
			Assert::IsTrue(points[i++] == Point2d(66.75, 0));
			Assert::IsTrue(points[i++] == Point2d(72, 0));
			Assert::IsTrue(points[i++] == Point2d(73.25, -17));
			Assert::IsTrue(points[i++] == Point2d(76.25, -20));
			Assert::IsTrue(points[i++] == Point2d(103.25, -23));
			Assert::IsTrue(points[i++] == Point2d(103.25, -29));
			Assert::IsTrue(i == points.size());
		}
	};
}
