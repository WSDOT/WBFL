#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	DeckedSlabBeam GetTestBeam()
	{
      // 6DS20
      DeckedSlabBeam beam;
      Float64 A = 77.75;
      beam.SetA(A);
      beam.SetB(9.0);
      beam.SetC(12.0);
      beam.SetW(6.0);
      beam.SetTt(8.0);
      beam.SetTb(7.0);
      beam.SetF(1.75);
      beam.SetLeftBlockout(true);
      beam.SetRightBlockout(true);

      return beam;
   }

	TEST_CLASS(TestDeckSlabBeam)
	{
	public:

      TEST_METHOD(BoundingBox)
      {
         auto beam = GetTestBeam();
         Rect2d box = beam.GetBoundingBox();
         auto A = beam.GetA();
         Assert::IsTrue(IsEqual(box.Left(), -A / 2.0));
         Assert::IsTrue(IsEqual(box.Right(), A / 2.0));
         Assert::IsTrue(IsEqual(box.Top(), 20.0));
         Assert::IsTrue(IsEqual(box.Bottom(), 0.0));
      }

      TEST_METHOD(ShapeProperties)
      {
         auto beam = GetTestBeam();
         auto props = beam.GetProperties();

         Float64 d_area = 1086.25;
         Float64 d_ixx = 43711.5237997;
         Float64 d_iyy = 460753.3242187;
         Float64 d_cgy = 10.81077867;

         auto A = beam.GetA();

         Assert::IsTrue(IsEqual(props.GetArea(), d_area));
         Assert::IsTrue(IsEqual(props.GetIxx(), d_ixx));
         Assert::IsTrue(IsEqual(props.GetIyy(), d_iyy));
         Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().Y(), d_cgy));
         Assert::IsTrue(props.GetCoordinateSystem() == ShapeProperties::CoordinateSystemType::Centroidal);
         Assert::IsTrue(IsEqual(props.GetXleft(), A / 2.0));
         Assert::IsTrue(IsEqual(props.GetXright(), A / 2.0));
         Assert::IsTrue(IsEqual(props.GetYtop(), 20 - d_cgy));
         Assert::IsTrue(IsEqual(props.GetYbottom(), d_cgy));
         Assert::IsTrue(IsEqual(beam.GetPerimeter(), 192.378339));
      }

      TEST_METHOD(FurthestDistance)
      {
         auto beam = GetTestBeam();
         Point2d p1(0, 50);
         Point2d p2(100, 50);
         Line2d line(p1, p2);

         // Shape on right
         Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), 50.0));

         // shape on left
         p1.Move(0, -50);
         p2.Move(100, -50);
         line.ThroughPoints(p1, p2);
         Assert::IsTrue(IsEqual(beam.GetFurthestDistance(line, Line2d::Side::Right), -50.0));
      }

      TEST_METHOD(PolyPoints)
      {
         auto beam = GetTestBeam();

         auto points = beam.GetPolyPoints();
         Assert::IsTrue(points.size() == 11);

         Float64 A = beam.GetA();
         Float64 Wb2 = (A - 9 * 2) / 2.0;

         int i = 0;
         Assert::IsTrue(points[i++] == Point2d(0.0, 0.0));
         Assert::IsTrue(points[i++] == Point2d(Wb2, 0.0));
         Assert::IsTrue(points[i++] == Point2d(Wb2, 12.0));
         Assert::IsTrue(points[i++] == Point2d(A / 2, 12.0));
         Assert::IsTrue(points[i++] == Point2d(A / 2 - 1.75, 20.0));
         Assert::IsTrue(points[i++] == Point2d(0.0, 20.0));
         Assert::IsTrue(points[i++] == Point2d(-(A / 2 - 1.75), 20.0));
         Assert::IsTrue(points[i++] == Point2d(-A / 2, 12.0));
         Assert::IsTrue(points[i++] == Point2d(-Wb2, 12.0));
         Assert::IsTrue(points[i++] == Point2d(-Wb2, 0.0));
         Assert::IsTrue(points[i++] == Point2d(0.0, 0.0));
         Assert::IsTrue(i == points.size());
      }

      TEST_METHOD(PointInShape)
      {
         auto beam = GetTestBeam();
         Point2d pnt(0, 1);
         Assert::IsTrue(beam.PointInShape(pnt) == true);

         pnt.Move(500, 500);
         Assert::IsTrue(beam.PointInShape(pnt) == false);

         pnt.Move(0, 0); // Point on perimeter
         Assert::IsTrue(beam.PointInShape(pnt) == false);
      }

      TEST_METHOD(ClipWithLine)
      {
         auto beam = GetTestBeam();

         // setup clipping line
         Point2d p1(-50, 0.50);
         Point2d p2(50, 0.50);
         Line2d clipLine(p1, p2);

         auto clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
         auto points = clip->GetPolyPoints();
         Assert::IsTrue(points.size() == 6);

         int i = 0;
         Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
         Assert::IsTrue(points[i++] == Point2d(29.875000, 0.000000));
         Assert::IsTrue(points[i++] == Point2d(29.875000, 0.500000));
         Assert::IsTrue(points[i++] == Point2d(-29.875000, 0.500000));
         Assert::IsTrue(points[i++] == Point2d(-29.875000, 0.000000));
         Assert::IsTrue(points[i++] == Point2d(0.000000, 0.000000));
         Assert::IsTrue(i == points.size());

         // clip in other direction
         p1.Move(50, 0.50);
         p2.Move(-50, 0.50);
         clipLine.ThroughPoints(p1, p2);

         clip = beam.CreateClippedShape(clipLine, Line2d::Side::Left);
         points = clip->GetPolyPoints();

         Assert::IsTrue(points.size() == 9);

         i = 0;
         Assert::IsTrue(points[i++] == Point2d(29.875000, 0.500000));
         Assert::IsTrue(points[i++] == Point2d(29.875000, 12.000000));
         Assert::IsTrue(points[i++] == Point2d(38.875000, 12.000000));
         Assert::IsTrue(points[i++] == Point2d(37.125000, 20.000000));
         Assert::IsTrue(points[i++] == Point2d(0.000000, 20.000000));
         Assert::IsTrue(points[i++] == Point2d(-37.125000, 20.000000));
         Assert::IsTrue(points[i++] == Point2d(-38.875000, 12.000000));
         Assert::IsTrue(points[i++] == Point2d(-29.875000, 12.000000));
         Assert::IsTrue(points[i++] == Point2d(-29.875000, 0.500000));
         Assert::IsTrue(i == points.size());
      }

      TEST_METHOD(ClipIn)
      {
         auto beam = GetTestBeam();

         Rect2d clipRect(-100, 1.5, 100, 11.0);
         auto clip = beam.CreateClippedShape(clipRect, Shape::ClipRegion::In);
         auto points = clip->GetPolyPoints();

         Assert::IsTrue(points.size() == 4);

         int i = 0;
         Assert::IsTrue(points[i++] == Point2d(29.875000, 1.500000));
         Assert::IsTrue(points[i++] == Point2d(29.875000, 11.000000));
         Assert::IsTrue(points[i++] == Point2d(-29.875000, 11.000000));
         Assert::IsTrue(points[i++] == Point2d(-29.875000, 1.500000));
         Assert::IsTrue(i == points.size());
      }

      TEST_METHOD(RemoveVoid)
      {
         auto beam = GetTestBeam();
         beam.SetVoidCount(0);
         auto props = beam.GetProperties();

         auto d_area = 1325.0;
         auto d_ixx = 44545.211236897274;
         auto d_iyy = 506117.06770833326;
         auto d_cgy = 10.574591194968553;

         Assert::IsTrue(IsEqual(props.GetArea(), d_area));
         Assert::IsTrue(IsEqual(props.GetIxx(), d_ixx));
         Assert::IsTrue(IsEqual(props.GetIyy(), d_iyy));
         Assert::IsTrue(IsEqual(props.GetIxy(), 0.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().X(), 0.0));
         Assert::IsTrue(IsEqual(props.GetCentroid().Y(), d_cgy));
      }

      TEST_METHOD(HookPoint)
      {
         auto beam = GetTestBeam();
         Assert::IsTrue(TestHookPoint(beam));
      }

      TEST_METHOD(Move)
      {
         auto beam = GetTestBeam();

         std::shared_ptr<Point2d> hookPnt = std::make_shared<Point2d>(0, 0);

         beam.SetHookPoint(hookPnt);

         // Get moment of inertia about CG before move
         // These properties should be invariant
         auto props = beam.GetProperties();
         auto area = props.GetArea();
         auto Ixx = props.GetIxx();
         auto Iyy = props.GetIyy();
         auto Ixy = props.GetIxy();

         Point2d from(0, 0);
         Point2d to(100, 100);

         beam.Move(from, to);

         // Check the points
         auto points = beam.GetPolyPoints();
         Assert::IsTrue(points.size() == 11);

         int i = 0;
         Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
         Assert::IsTrue(points[i++] == Point2d(129.875000, 100.000000));
         Assert::IsTrue(points[i++] == Point2d(129.875000, 112.000000));
         Assert::IsTrue(points[i++] == Point2d(138.875000, 112.000000));
         Assert::IsTrue(points[i++] == Point2d(137.125000, 120.000000));
         Assert::IsTrue(points[i++] == Point2d(100.000000, 120.000000));
         Assert::IsTrue(points[i++] == Point2d(62.875000, 120.000000));
         Assert::IsTrue(points[i++] == Point2d(61.125000, 112.000000));
         Assert::IsTrue(points[i++] == Point2d(70.125000, 112.000000));
         Assert::IsTrue(points[i++] == Point2d(70.125000, 100.000000));
         Assert::IsTrue(points[i++] == Point2d(100.000000, 100.000000));
         Assert::IsTrue(i == points.size());

         props = beam.GetProperties();
         Assert::IsTrue(IsEqual(area, props.GetArea()));
         Assert::IsTrue(IsEqual(Ixx, props.GetIxx()));
         Assert::IsTrue(IsEqual(Iyy, props.GetIyy()));
         Assert::IsTrue(IsEqual(Ixy, props.GetIxy()));
      }

      TEST_METHOD(Offset)
      {
         auto beam = GetTestBeam();

         Size2d size(-100, -100);
         beam.Offset(size);

         // Check the points
         auto points = beam.GetPolyPoints();
         Assert::IsTrue(points.size() == 11);

         int i = 0;
         Assert::IsTrue(points[i++] == Point2d(-100.000, -100.00));
         Assert::IsTrue(points[i++] == Point2d(-70.1250, -100.00));
         Assert::IsTrue(points[i++] == Point2d(-70.1250, -88.000));
         Assert::IsTrue(points[i++] == Point2d(-61.1250, -88.000));
         Assert::IsTrue(points[i++] == Point2d(-62.8750, -80.000));
         Assert::IsTrue(points[i++] == Point2d(-100.000, -80.000));
         Assert::IsTrue(points[i++] == Point2d(-137.125, -80.000));
         Assert::IsTrue(points[i++] == Point2d(-138.875, -88.000));
         Assert::IsTrue(points[i++] == Point2d(-129.875, -88.000));
         Assert::IsTrue(points[i++] == Point2d(-129.875, -100.00));
         Assert::IsTrue(points[i++] == Point2d(-100.000, -100.00));
         Assert::IsTrue(i == points.size());
      }

      TEST_METHOD(LocatorPoint)
      {
         auto beam = GetTestBeam();
         std::shared_ptr<Point2d> hookPnt = std::make_shared<Point2d>(0, 0);
         beam.SetHookPoint(hookPnt);

         // BottomLeft
         hookPnt->Move(0, 0);
         Point2d to(100, 100);
         beam.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, to);
         auto from = beam.GetLocatorPoint(Shape::LocatorPoint::BottomLeft);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(138.875, 100.0));

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
         Assert::IsTrue(*hookPnt == Point2d(61.125, 100.0));

         // CenterLeft
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         beam.SetLocatorPoint(Shape::LocatorPoint::CenterLeft, to);
         from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterLeft);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(138.875, 90.0));

         // CenterCenter
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         beam.SetLocatorPoint(Shape::LocatorPoint::CenterCenter, to);
         from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterCenter);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 90.0));

         // CenterRight
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         beam.SetLocatorPoint(Shape::LocatorPoint::CenterRight, to);
         from = beam.GetLocatorPoint(Shape::LocatorPoint::CenterRight);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(61.125, 90.0));

         // TopLeft
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         beam.SetLocatorPoint(Shape::LocatorPoint::TopLeft, to);
         from = beam.GetLocatorPoint(Shape::LocatorPoint::TopLeft);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(138.875, 80.0));

         // TopCenter
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         beam.SetLocatorPoint(Shape::LocatorPoint::TopCenter, to);
         from = beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(100.0, 80.0));

         // TopRight
         hookPnt->Move(0, 0);
         to.Move(100, 100);
         beam.SetLocatorPoint(Shape::LocatorPoint::TopRight, to);
         from = beam.GetLocatorPoint(Shape::LocatorPoint::TopRight);
         Assert::IsTrue(from == Point2d(100, 100));
         Assert::IsTrue(*hookPnt == Point2d(61.125, 80.0));

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
         std::shared_ptr<Point2d> hookPnt = std::make_shared<Point2d>(0, 0);
         beam.SetHookPoint(hookPnt);

         hookPnt->Move(0, 0);
         Point2d c(-38.875, 0.0);

         beam.Rotate(c, PI_OVER_2);

         // Check the points
         auto points = beam.GetPolyPoints();
         Assert::IsTrue(points.size() == 11);

         int i = 0;
         Assert::IsTrue(points[i++] == Point2d(-38.875000, 38.875000));
         Assert::IsTrue(points[i++] == Point2d(-38.875000, 68.750000));
         Assert::IsTrue(points[i++] == Point2d(-50.875000, 68.750000));
         Assert::IsTrue(points[i++] == Point2d(-50.875000, 77.750000));
         Assert::IsTrue(points[i++] == Point2d(-58.875000, 76.000000));
         Assert::IsTrue(points[i++] == Point2d(-58.875000, 38.875000));
         Assert::IsTrue(points[i++] == Point2d(-58.875000, 1.750000));
         Assert::IsTrue(points[i++] == Point2d(-50.875000, 0.000000));
         Assert::IsTrue(points[i++] == Point2d(-50.875000, 9.000000));
         Assert::IsTrue(points[i++] == Point2d(-38.875000, 9.000000));
         Assert::IsTrue(points[i++] == Point2d(-38.875000, 38.875000));
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
