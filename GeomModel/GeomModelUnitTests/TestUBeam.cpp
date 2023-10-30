#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestUBeam)
	{
	public:
		
		UBeam GetTestBeam()
		{
			UBeam beam;
			beam.SetD1(60.00);
			beam.SetD2(6.00);
			beam.SetD3(6.00);
			beam.SetD4(4.50);
			beam.SetD5(1.50);
			beam.SetD6(4.50);
			beam.SetD7(1.50);
			beam.SetW1(60.00);
			beam.SetW2(85.43);
			beam.SetW3(12.00);
			beam.SetW4(3.00);
			beam.SetW5(5.00);
			beam.SetT(7.00);
			return beam;
		}

		TEST_METHOD(U48G4)
		{
			Float64 t = 7.;
			Float64 w1 = 48;
			Float64 w2 = 61.71428571;
			Float64 w3 = 12;
			Float64 w4 = 0;
			Float64 w5 = 0;
			Float64 d1 = 48;
			Float64 d2 = 6;
			Float64 d3 = 6;
			Float64 d4 = 0;
			Float64 d5 = 0;
			Float64 d6 = 0;
			Float64 d7 = 0;

			UBeam U48G4(w1, w2, w3, w4, w5, d1, d2, d3, d4, d5, d6, d7, t, Point2d());
			auto aprops = U48G4.GetProperties();
			Assert::IsTrue(U48G4.GetBoundingBox() == Rect2d(-30.857142857143, 0.0, 30.857142857143, 48.));
			Assert::IsTrue(IsEqual(aprops.GetArea(), 953.9697));
			Assert::IsTrue(IsEqual(aprops.GetIxx(), 208841.6, 0.1));
			Assert::IsTrue(IsEqual(aprops.GetIxy(), 0.));
			Assert::IsTrue(IsEqual(aprops.GetCentroid().X(), 0.));
			Assert::IsTrue(IsEqual(aprops.GetCentroid().Y(), 18.29891));
			Assert::IsTrue(IsEqual(U48G4.GetHeight(), 48.0));
			Assert::IsTrue(IsEqual(U48G4.GetTopFlangeWidth(0), 7.0710678118212806));
			Assert::IsTrue(IsEqual(U48G4.GetTopFlangeWidth(1), 7.0710678118212806));
			Assert::IsTrue(IsEqual(U48G4.GetBottomFlangeWidth(0), 48.0));
			Assert::IsTrue(IsEqual(U48G4.GetT(), 7.));
			Assert::IsTrue(IsEqual(U48G4.GetSlope(0), -7.));
			Assert::IsTrue(IsEqual(U48G4.GetW1(), w1));
			Assert::IsTrue(IsEqual(U48G4.GetW2(), w2));
			Assert::IsTrue(IsEqual(U48G4.GetW3(), w3));
			Assert::IsTrue(IsEqual(U48G4.GetW4(), w4));
			Assert::IsTrue(IsEqual(U48G4.GetW5(), w5));
			Assert::IsTrue(IsEqual(U48G4.GetD1(), d1));
			Assert::IsTrue(IsEqual(U48G4.GetD2(), d2));
			Assert::IsTrue(IsEqual(U48G4.GetD3(), d3));
			Assert::IsTrue(IsEqual(U48G4.GetD4(), d4));
			Assert::IsTrue(IsEqual(U48G4.GetD5(), d5));
			Assert::IsTrue(IsEqual(U48G4.GetD6(), d6));
			Assert::IsTrue(IsEqual(U48G4.GetD7(), d7));
			Assert::IsTrue(IsEqual(U48G4.GetT(), t));
		}

		TEST_METHOD(UF48G4)
		{
			Float64 t = 7.;
			Float64 w1 = 48;
			Float64 w2 = 70;
			Float64 w3 = 12;
			Float64 w4 = 3;
			Float64 w5 = 5;
			Float64 d1 = 48;
			Float64 d2 = 6;
			Float64 d3 = 6;
			Float64 d4 = 4.5;
			Float64 d5 = 1.5;
			Float64 d6 = 4.5;
			Float64 d7 = 1.5;

			UBeam UF48G4(w1, w2, w3, w4, w5, d1, d2, d3, d4, d5, d6, d7, t, Point2d());
			auto aprops = UF48G4.GetProperties();
			Assert::IsTrue(UF48G4.GetBoundingBox() == Rect2d(-35, 0.0, 35, 48.));
			Assert::IsTrue(IsEqual(aprops.GetArea(), 1037.9696961966997));
			Assert::IsTrue(IsEqual(aprops.GetIxx(), 265565.70300474146));
			Assert::IsTrue(IsEqual(aprops.GetIyy(), 496020.14081542683));
			Assert::IsTrue(IsEqual(aprops.GetIxy(), 0.));
			Assert::IsTrue(IsEqual(aprops.GetCentroid().X(), 0.));
			Assert::IsTrue(IsEqual(aprops.GetCentroid().Y(), 20.488662093569786));
			Assert::IsTrue(IsEqual(UF48G4.GetHeight(), 48.0));
			Assert::IsTrue(IsEqual(UF48G4.GetTopFlangeWidth(0), 15.071067811865476));
			Assert::IsTrue(IsEqual(UF48G4.GetTopFlangeWidth(1), 15.071067811865476));
			Assert::IsTrue(IsEqual(UF48G4.GetBottomFlangeWidth(0), 48.0));
			Assert::IsTrue(IsEqual(UF48G4.GetT(), 7.));
			Assert::IsTrue(IsEqual(UF48G4.GetSlope(1), 7.));
			Assert::IsTrue(IsEqual(UF48G4.GetW1(), w1));
			Assert::IsTrue(IsEqual(UF48G4.GetW2(), w2));
			Assert::IsTrue(IsEqual(UF48G4.GetW3(), w3));
			Assert::IsTrue(IsEqual(UF48G4.GetW4(), w4));
			Assert::IsTrue(IsEqual(UF48G4.GetW5(), w5));
			Assert::IsTrue(IsEqual(UF48G4.GetD1(), d1));
			Assert::IsTrue(IsEqual(UF48G4.GetD2(), d2));
			Assert::IsTrue(IsEqual(UF48G4.GetD3(), d3));
			Assert::IsTrue(IsEqual(UF48G4.GetD4(), d4));
			Assert::IsTrue(IsEqual(UF48G4.GetD5(), d5));
			Assert::IsTrue(IsEqual(UF48G4.GetD6(), d6));
			Assert::IsTrue(IsEqual(UF48G4.GetD7(), d7));
			Assert::IsTrue(IsEqual(UF48G4.GetT(), t));
		}

		TEST_METHOD(BoundingBox)
		{
			auto beam = GetTestBeam();
			auto box = beam.GetBoundingBox();

			Assert::IsTrue(IsEqual(box.Left(), -42.715));
			Assert::IsTrue(IsEqual(box.Right(), 42.715));
			Assert::IsTrue(IsEqual(box.Top(), 60.00));
			Assert::IsTrue(IsEqual(box.Bottom(), 0.00));
		}

		TEST_METHOD(ShapeProperties)
		{
			auto beam = GetTestBeam();
			auto props = beam.GetProperties();
			Assert::IsTrue(IsEqual(props.GetArea(), 1279.67674));
			Assert::IsTrue(IsEqual(props.GetIxx(), 519561.213035));
			Assert::IsTrue(IsEqual(props.GetIyy(), 999211.50319));
			Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
			Assert::IsTrue(IsEqual(props.GetCentroid().Y(), 24.73653));
			Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);

			Assert::IsTrue(IsEqual(props.GetXleft(), 42.715));
			Assert::IsTrue(IsEqual(props.GetXright(), 42.715));
			Assert::IsTrue(IsEqual(props.GetYtop(), 60.0 - props.GetCentroid().Y()));
			Assert::IsTrue(IsEqual(props.GetYbottom(), props.GetCentroid().Y()));

			Assert::IsTrue(IsEqual(beam.GetPerimeter(), 371.35986));

			Assert::IsTrue(IsEqual(beam.GetHeight(), 60.0));

			Assert::IsTrue(beam.GetWebCount() == 2);
			Assert::IsTrue(IsEqual(beam.GetSlope(0), -6.9993519118600096)); // not exactly 7 because W2 is rounded off
			Assert::IsTrue(IsEqual(beam.GetSlope(1), 6.9993519118600096));
			Assert::IsTrue(IsEqual(beam.GetWebSpacing(), 70.073363537414849));
			Assert::IsTrue(IsEqual(beam.GetWebLocation(0), -35.036681768707425));
			Assert::IsTrue(IsEqual(beam.GetWebLocation(1), 35.036681768707425));

			Assert::IsTrue(IsEqual(beam.GetTopWidth(), 85.43));
			Assert::IsTrue(beam.GetTopFlangeCount() == 2);
			Assert::IsTrue(IsEqual(beam.GetTopFlangeLocation(0), -35.179459546485205));
			Assert::IsTrue(IsEqual(beam.GetTopFlangeLocation(1), 35.179459546485205));
			Assert::IsTrue(IsEqual(beam.GetTopFlangeWidth(0), 15.071080907029602));
			Assert::IsTrue(IsEqual(beam.GetTopFlangeWidth(1), 15.071080907029602));

			Assert::IsTrue(beam.GetBottomFlangeCount() == 1);
			Assert::IsTrue(IsEqual(beam.GetBottomFlangeLocation(0), 0.0));
			Assert::IsTrue(IsEqual(beam.GetBottomFlangeWidth(0), 60.0));
			Assert::IsTrue(IsEqual(beam.GetBottomWidth(), 60.0));
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
			Assert::IsTrue(points.size() == 21);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-37.715000, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(-42.715000, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(-42.715000, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.643919, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.643919, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(-30.643919, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(-24.643364, 12.000000));
			Assert::IsTrue(points[i++] == Point2d(-12.643364, 6.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 6.000000));
			Assert::IsTrue(points[i++] == Point2d(12.643364, 6.000000));
			Assert::IsTrue(points[i++] == Point2d(24.643364, 12.000000));
			Assert::IsTrue(points[i++] == Point2d(30.643919, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(27.643919, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(27.643919, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(42.715000, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(42.715000, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(37.715000, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(30.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(i == points.size());
		}

		TEST_METHOD(Clone)
		{
			auto beam = GetTestBeam();
			auto beamClone(beam);
			Assert::AreEqual(beamClone.GetD1(),60.00);
			Assert::AreEqual(beamClone.GetD2(),6.00);
			Assert::AreEqual(beamClone.GetD3(),6.00);
			Assert::AreEqual(beamClone.GetD4(),4.50);
			Assert::AreEqual(beamClone.GetD5(),1.50);
			Assert::AreEqual(beamClone.GetD6(),4.50);
			Assert::AreEqual(beamClone.GetD7(),1.50);
			Assert::AreEqual(beamClone.GetW1(),60.00);
			Assert::AreEqual(beamClone.GetW2(),85.43);
			Assert::AreEqual(beamClone.GetW3(),12.00);
			Assert::AreEqual(beamClone.GetW4(),3.00);
			Assert::AreEqual(beamClone.GetW5(),5.00);
			Assert::AreEqual(beamClone.GetT(),7.00);
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
			Assert::IsTrue(points.size() == 6);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.071435, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(30.071435, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(30.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(i == points.size());

			// clip in other direction
			clipLine.ThroughPoints(p2, p1);

			clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
			Assert::IsTrue(clip != nullptr);

			points = clip->GetPolyPoints();
			Assert::IsTrue(points.size() == 19);
			i = 0;
			Assert::IsTrue(points[i++] == Point2d(-30.071435, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(-37.715000, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(-42.715000, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(-42.715000, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.643919, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.643919, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(-30.643919, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(-24.643364, 12.000000));
			Assert::IsTrue(points[i++] == Point2d(-12.643364, 6.000000));
			Assert::IsTrue(points[i++] == Point2d(0.0, 6.000000));
			Assert::IsTrue(points[i++] == Point2d(12.643364, 6.000000));
			Assert::IsTrue(points[i++] == Point2d(24.643364, 12.000000));
			Assert::IsTrue(points[i++] == Point2d(30.643919, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(27.643919, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(27.643919, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(42.715000, 60.000000));
			Assert::IsTrue(points[i++] == Point2d(42.715000, 55.500000));
			Assert::IsTrue(points[i++] == Point2d(37.715000, 54.000000));
			Assert::IsTrue(points[i++] == Point2d(30.071435, 0.500000));
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
			Assert::IsTrue(points[i++] == Point2d(-30.071435, 0.500000));
			Assert::IsTrue(points[i++] == Point2d(-30.085722, 0.600000));
			Assert::IsTrue(points[i++] == Point2d(30.085722, 0.600000));
			Assert::IsTrue(points[i++] == Point2d(30.071435, 0.500000));
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
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(70.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(62.285000, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(57.285000, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(57.285000, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(72.356081, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(72.356081, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(69.356081, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(75.356636, 112.000000));
			Assert::IsTrue(points[i++] == Point2d(87.356636, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(112.643364, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(124.643364, 112.000000));
			Assert::IsTrue(points[i++] == Point2d(130.643919, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(127.643919, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(127.643919, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(142.715000, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(142.715000, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(137.715000, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(130.000000, 100.000000));
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
			Assert::IsTrue(points.size() == 21);
			int i = 0;
			Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(70.000000, 100.000000));
			Assert::IsTrue(points[i++] == Point2d(62.285000, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(57.285000, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(57.285000, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(72.356081, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(72.356081, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(69.356081, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(75.356636, 112.000000));
			Assert::IsTrue(points[i++] == Point2d(87.356636, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(100.000000, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(112.643364, 106.000000));
			Assert::IsTrue(points[i++] == Point2d(124.643364, 112.000000));
			Assert::IsTrue(points[i++] == Point2d(130.643919, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(127.643919, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(127.643919, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(142.715000, 160.000000));
			Assert::IsTrue(points[i++] == Point2d(142.715000, 155.500000));
			Assert::IsTrue(points[i++] == Point2d(137.715000, 154.000000));
			Assert::IsTrue(points[i++] == Point2d(130.000000, 100.000000));
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
			Assert::IsTrue(*hookPnt == Point2d(142.715, 100.0));

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
			Assert::IsTrue(*hookPnt == Point2d(57.285, 100.0));

			// CenterLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(142.715, 70.0));

			// CenterCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 70.0));

			// CenterRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(57.285, 70.0));

			// TopLeft
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(142.715, 40.0));

			// TopCenter
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(100.0, 40.0));

			// TopRight
			hookPnt->Move(0, 0);
			to.Move(100, 100);
			beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
			from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
			Assert::IsTrue(from == Point2d(100, 100));
			Assert::IsTrue(*hookPnt == Point2d(57.285, 40.0));

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
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(30.000000, -0.000000));
			Assert::IsTrue(points[i++] == Point2d(37.715000, -54.000000));
			Assert::IsTrue(points[i++] == Point2d(42.715000, -55.500000));
			Assert::IsTrue(points[i++] == Point2d(42.715000, -60.000000));
			Assert::IsTrue(points[i++] == Point2d(27.643919, -60.000000));
			Assert::IsTrue(points[i++] == Point2d(27.643919, -55.500000));
			Assert::IsTrue(points[i++] == Point2d(30.643919, -54.000000));
			Assert::IsTrue(points[i++] == Point2d(24.643364, -12.000000));
			Assert::IsTrue(points[i++] == Point2d(12.643364, -6.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, -6.000000));
			Assert::IsTrue(points[i++] == Point2d(-12.643364, -6.000000));
			Assert::IsTrue(points[i++] == Point2d(-24.643364, -12.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.643919, -54.000000));
			Assert::IsTrue(points[i++] == Point2d(-27.643919, -55.500000));
			Assert::IsTrue(points[i++] == Point2d(-27.643919, -60.000000));
			Assert::IsTrue(points[i++] == Point2d(-42.715000, -60.000000));
			Assert::IsTrue(points[i++] == Point2d(-42.715000, -55.500000));
			Assert::IsTrue(points[i++] == Point2d(-37.715000, -54.000000));
			Assert::IsTrue(points[i++] == Point2d(-30.000000, 0.000000));
			Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
			Assert::IsTrue(i == points.size());
		}
	};
}
