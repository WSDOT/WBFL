#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::Geometry;

namespace GeomModelUnitTest
{
	TEST_CLASS(TestGeometricOperations)
	{
	public:

      TEST_METHOD(Angle)
      {
         Point2d p1(3, 8);
         Point2d p2(0, 0);
         Point2d p3(5, 7);

         Float64 angle = GeometricOperations::Angle(p1, p2, p3);
         Assert::IsTrue(IsEqual(angle, 6.02170649147));
         angle = GeometricOperations::Angle(p3, p2, p1);
         Assert::IsTrue(IsEqual(angle, 0.2614788157));

         Assert::ExpectException<XGeometry>([&]() {GeometricOperations::Angle(p1, p1, p3); });
         Assert::ExpectException<XGeometry>([&]() {GeometricOperations::Angle(p1, p3, p3); });

         p1.Move(10, 0);
         p3.Move(0, 10);
         angle = GeometricOperations::Angle(p1, p2, p3);
         Assert::IsTrue(IsEqual(angle, PI_OVER_2));
         angle = GeometricOperations::Angle(p3, p2, p1);
         Assert::IsTrue(IsEqual(angle, 3 * PI_OVER_2));

         p1.Move(-3, -8);
         p3.Move(-5, -7);
         angle = GeometricOperations::Angle(p1, p2, p3);
         Assert::IsTrue(IsEqual(angle, 6.02170649147));
         angle = GeometricOperations::Angle(p3, p2, p1);
         Assert::IsTrue(IsEqual(angle, 0.2614788157));
      }

      TEST_METHOD(ShortestOffsetToPoint)
      {
         Point2d p1(10, 10);
         Point2d p2(20, 20);
         Line2d line(p1, p2);

         Point2d p3(10, 20);
         Float64 dist = GeometricOperations::ShortestOffsetToPoint(line, p3);
         Assert::IsTrue(IsEqual(dist, -7.07106)); // Point on left side (-)

         p3.Move(20, 10);
         dist = GeometricOperations::ShortestOffsetToPoint(line, p3);
         Assert::IsTrue(IsEqual(dist, 7.07106)); // Point on right side (+)
      }

      TEST_METHOD(ReflectPointAcrossLine)
      {
         Point2d p1, p2, p3;

         // 45degree line
         p1.Move(0, 0);
         p2.Move(100, 100);
         Line2d line(p1, p2);
         p3.Move(50, 0);
         auto rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(0, 50));

         // -45degree line
         p1.Move(0, 0);
         p2.Move(-100, -100);
         line.ThroughPoints(p1, p2);
         p3.Move(50, 0);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(0, 50));

         // 135degree line
         p1.Move(0, 0);
         p2.Move(-100, 100);
         line.ThroughPoints(p1, p2);
         p3.Move(50, 0);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(0, -50));

         // -135degree line
         p1.Move(0, 0);
         p2.Move(100, -100);
         line.ThroughPoints(p1, p2);
         p3.Move(50, 0);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(0, -50));

         // x-axis
         p1.Move(0, 0);
         p2.Move(100, 0);
         line.ThroughPoints(p1, p2);
         p3.Move(50, 0);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(50, 0));

         p3.Move(50, 50);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(50, -50));

         p3.Move(50, -50);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(50, 50));

         // horizontal parallel to x-axis
         p1.Move(0, 10);
         p2.Move(100, 10);
         line.ThroughPoints(p1, p2);
         p3.Move(50, 0);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(50, 20));

         // y-axis
         p1.Move(0, 0);
         p2.Move(0, 100);
         line.ThroughPoints(p1, p2);
         p3.Move(0, 50);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(0, 50));

         p3.Move(50, 50);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(-50, 50));

         p3.Move(-50, 50);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(50, 50));

         // vertical parallel to y-axis
         p1.Move(10, 0);
         p2.Move(10, 100);
         line.ThroughPoints(p1, p2);
         p3.Move(0, 50);
         rp = GeometricOperations::ReflectPointAcrossLine(p3, line);
         Assert::IsTrue(rp == Point2d(20, 50));
      }

      TEST_METHOD(PointOnLineNearest)
      {
         Point2d p1, p2, p3;

         p1.Move(0, 10);
         p2.Move(10, 10);
         Line2d line(p1, p2);
         p3.Move(5, 5);

         Point2d poln = GeometricOperations::PointOnLineNearest(line, p3);
         Assert::IsTrue(poln == Point2d(5.0, 10.0));

         p3.Move(20, 10);
         poln = GeometricOperations::PointOnLineNearest(line, p3);
         Assert::IsTrue(poln == Point2d(20.0, 10.0));

         p1.Move(0, 0);
         p2.Move(10, 10);
         line.ThroughPoints(p1, p2);
         p3.Move(0, 10);
         poln = GeometricOperations::PointOnLineNearest(line, p3);
         Assert::IsTrue(poln == Point2d(5.0, 5.0));

         p1.Move(0, 0);
         p2.Move(-10, 10);
         line.ThroughPoints(p1, p2);
         p3.Move(0, 10);
         poln = GeometricOperations::PointOnLineNearest(line, p3);
         Assert::IsTrue(poln == Point2d(-5.0, 5.0));

         p1.Move(0, 0);
         p2.Move(-10, -10);
         line.ThroughPoints(p1, p2);
         p3.Move(0, -10);
         poln = GeometricOperations::PointOnLineNearest(line, p3);
         Assert::IsTrue(poln == Point2d(-5.0, -5.0));

         p1.Move(0, 0);
         p2.Move(10, -10);
         line.ThroughPoints(p1, p2);
         p3.Move(0, -10);
         poln = GeometricOperations::PointOnLineNearest(line, p3);
         Assert::IsTrue(poln == Point2d(5.0, -5.0));
      }

      TEST_METHOD(CreateParallelLine)
      {
         Point2d p1, p2;

         p1.Move(0, 0);
         p2.Move(10, 10);
         Line2d line(p1, p2);
         Line2d line2 = GeometricOperations::CreateParallelLine(line, 10.0);
         Assert::IsTrue(GeometricOperations::IsParallel(line, line2));

         p1.Move(0, 0);
         p2.Move(10, 0);
         line.ThroughPoints(p1, p2);
         line2 = GeometricOperations::CreateParallelLine(line, 10.0);
         Assert::IsTrue(GeometricOperations::IsParallel(line, line2));

         p1.Move(0, 0);
         p2.Move(0, 10);
         line.ThroughPoints(p1, p2);
         line2 = GeometricOperations::CreateParallelLine(line, 10.0);
         Assert::IsTrue(GeometricOperations::IsParallel(line, line2));
      }

      TEST_METHOD(CreateParallelLineSegment)
      {
         Point2d p1, p2;

         p1.Move(0, 0);
         p2.Move(10, 10);
         LineSegment2d seg1(p1, p2);
         LineSegment2d seg2 = GeometricOperations::CreateParallelLineSegment(seg1, 10.0);
         Assert::IsTrue(GeometricOperations::IsParallel(seg1, seg2));

         p1.Move(0, 0);
         p2.Move(10, 0);
         seg1.ThroughPoints(p1, p2);
         seg2 = GeometricOperations::CreateParallelLineSegment(seg1, 10.0);
         Assert::IsTrue(GeometricOperations::IsParallel(seg1, seg2));

         p1.Move(0, 0);
         p2.Move(0, 10);
         seg1.ThroughPoints(p1, p2);
         seg2 = GeometricOperations::CreateParallelLineSegment(seg1, 10.0);
         Assert::IsTrue(GeometricOperations::IsParallel(seg1, seg2));
      }

      TEST_METHOD(CreateParallelLineThroughPoint)
      {
         Point2d p1, p2, p3;

         p1.Move(10, 10);
         p2.Move(20, 30);
         Line2d line(p1, p2);
         p3.Move(-10, 15);
         auto line2 = GeometricOperations::CreateParallelLineThroughPoint(line, p3);
         Assert::IsTrue(GeometricOperations::IsParallel(line, line2));
      }

      TEST_METHOD(CreateNormalLineThroughPoint)
      {
         Point2d p1, p2, p3;

         p1.Move(40, 34);
         p2.Move(0, 4);
         Line2d line(p1, p2);
         p3.Move(-3, 8);
         auto line2 = GeometricOperations::CreateNormalLineThroughPoint(line, p3);

         Float64 c; Vector2d v;
         std::tie(c, v) = line2.GetImplicit();
         Assert::IsTrue(IsEqual(c, 2.4));
         Assert::IsTrue(v == Vector2d(Size2d(0.8, 0.6)));

         p3.Move(0, 4);
         line2 = GeometricOperations::CreateNormalLineThroughPoint(line, p3);
         std::tie(c, v) = line2.GetImplicit();
         Assert::IsTrue(IsEqual(c, 2.4));
         Assert::IsTrue(v == Vector2d(Size2d(0.8, 0.6)));
      }

      TEST_METHOD(LineCircleIntersect)
      {
         Point2d p1, p2, p3;

         p1.Move(0, 0);
         p2.Move(10, 10);
         Line2d line(p1, p2);

         p3.Move(5, 5);
         Circle circle1(p3, 5.0);
         Point2d intersect1, intersect2;

         auto nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
         Assert::IsTrue(nIntersect == 2);
         Assert::IsTrue(intersect1 == Point2d(1.464466, 1.464466));
         Assert::IsTrue(intersect2 == Point2d(8.535534, 8.535534));

         p1.Move(0, 100);
         p2.Move(10, 110);
         line.ThroughPoints(p1, p2);
         nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
         Assert::IsTrue(nIntersect == 0);

         p1.Move(0, 10);
         p2.Move(10, 10);
         line.ThroughPoints(p1, p2);
         nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
         Assert::IsTrue(nIntersect == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 10));

         p1.Move(5, 0);
         p2.Move(5, 10);
         line.ThroughPoints(p1, p2);
         nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
         Assert::IsTrue(nIntersect == 2);
         Assert::IsTrue(intersect1 == Point2d(5, 10));
         Assert::IsTrue(intersect2 == Point2d(5, 0));

         p1.Move(10, 0);
         p2.Move(10, 10);
         line.ThroughPoints(p1, p2);
         nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
         Assert::IsTrue(nIntersect == 1);
         Assert::IsTrue(intersect1 == Point2d(10, 5));

         p1.Move(-50, -210);
         p2.Move(90, 90);
         line.ThroughPoints(p1, p2);
         circle1.GetHookPoint()->Move(0, 0);
         circle1.SetRadius(100.);
         nIntersect = GeometricOperations::Intersect(line, circle1, &intersect1, &intersect2);
         Assert::IsTrue(nIntersect == 2);
         Assert::IsTrue(intersect1 == Point2d(1.337507, -99.991055));
         Assert::IsTrue(intersect2 == Point2d(77.49461, 63.202734));
      }

      TEST_METHOD(LineLineIntersect)
      {
         Point2d p1, p2, p3, p4;
         p1.Move(10, 0);
         p2.Move(10, 10);
         Line2d line(p1, p2);

         p3.Move(20, 0);
         p4.Move(20, 10);
         Line2d line2(p3, p4);

         Point2d intersect1;
         Int16 result = GeometricOperations::Intersect(line, line2, &intersect1);
         Assert::IsTrue(result == 0);

         p1.Move(0, 0);
         p2.Move(10, 10);
         line.ThroughPoints(p1, p2);

         p3.Move(10, 0);
         p4.Move(0, 10);
         line2.ThroughPoints(p3, p4);

         result = GeometricOperations::Intersect(line, line2, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 5));
      }

      TEST_METHOD(SegSegIntersect)
      {
         Point2d p1, p2, p3, p4;
         p1.Move(10, 0);
         p2.Move(10, 10);
         LineSegment2d seg1(p1, p2);

         p3.Move(20, 0);
         p4.Move(20, 10);
         LineSegment2d seg2(p3, p4);

         Point2d intersect1;
         auto result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 0);

         p1.Move(0, 0);
         p2.Move(10, 10);
         seg1.ThroughPoints(p1, p2);
         p3.Move(10, 0);
         p4.Move(0, 10);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 5));

         p1.Move(0, 0);
         p2.Move(0, 0);
         seg1.ThroughPoints(p1, p2);
         p3.Move(10, 0);
         p4.Move(0, 10);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 0);

         p1.Move(5, 5);
         p2.Move(5, 5);
         seg1.ThroughPoints(p1, p2);
         p3.Move(10, 0);
         p4.Move(0, 10);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 5));

         p1.Move(0, 0);
         p2.Move(10, 10);
         seg1.ThroughPoints(p1, p2);
         p3.Move(0, 10);
         p4.Move(0, 10);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 0);

         p1.Move(0, 0);
         p2.Move(10, 10);
         seg1.ThroughPoints(p1, p2);
         p3.Move(5, 5);
         p4.Move(5, 5);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 5));

         p1.Move(5, 5);
         p2.Move(5, 5);
         seg1.ThroughPoints(p1, p2);
         p3.Move(10, 10);
         p4.Move(10, 10);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 0);

         p1.Move(10, 10);
         p2.Move(10, 10);
         seg1.ThroughPoints(p1, p2);
         p3.Move(10, 10);
         p4.Move(10, 10);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(10, 10));

         p1.Move(0, 0);
         p2.Move(4, 4);
         seg1.ThroughPoints(p1, p2);
         p3.Move(0, 10);
         p4.Move(10, 0);
         seg2.ThroughPoints(p3, p4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 0);

         p1.Move(0, 0);
         p2.Move(4, 4);
         seg1.ThroughPoints(p1, p2);
         p3.Move(0, 10);
         p4.Move(5, 4);
         result = GeometricOperations::Intersect(seg1, seg2, &intersect1);
         Assert::IsTrue(result == 0);
      }

      TEST_METHOD(IntersectLineWithLineSegment)
      {
         Point2d p1, p2, p3, p4;

         p1.Move(0, 0);
         p2.Move(10, 10);
         p3.Move(10, 0);
         p4.Move(0, 10);
         Line2d line(p1, p2);
         LineSegment2d seg1(p3, p4);

         Point2d intersect1;
         auto result = GeometricOperations::Intersect(line, seg1, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 5));

         p2.Move(100, 100);
         seg1.ThroughPoints(seg1.GetStartPoint(), p2);
         result = GeometricOperations::Intersect(line, seg1, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(100, 100));

         p1.Move(0, 0);
         p2.Move(10, 10);
         seg1.ThroughPoints(p1, p2);
         result = GeometricOperations::Intersect(line, seg1, &intersect1);
         Assert::IsTrue(result == -1);

         p1.Move(10, 15);
         p2.Move(10, 15);
         seg1.ThroughPoints(p1, p2);
         result = GeometricOperations::Intersect(line, seg1, &intersect1);
         Assert::IsTrue(result == 0);

         p1.Move(5, 5);
         p2.Move(5, 5);
         seg1.ThroughPoints(p1, p2);
         result = GeometricOperations::Intersect(line, seg1, &intersect1);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 5));
      }

      TEST_METHOD(CircleCircleIntersect)
      {
         Circle circle1(Point2d(0, 0), 5);
         Circle circle2(Point2d(5, 5), 5);

         Point2d intersect1, intersect2;
         auto result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(0, 5));
         Assert::IsTrue(intersect2 == Point2d(5, 0));

         circle2.GetHookPoint()->Move(0, 0); // same center and radius - infinite number of results
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 3);

         circle2.SetRadius(10.0); // same center, bigger radius, no intersections
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 0);

         circle2.GetHookPoint()->Move(100, 100); // circles don't overlap
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 0);

         circle2.GetHookPoint()->Move(10, 0);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 1);
         Assert::IsTrue(intersect1 == Point2d(5, 0));

         circle2.GetHookPoint()->Move(5, 5);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(0, 5));
         Assert::IsTrue(intersect2 == Point2d(5, 0));

         circle2.GetHookPoint()->Move(-5, 5);
         circle2.SetRadius(5);

         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(-5, 0));
         Assert::IsTrue(intersect2 == Point2d(0, 5));

         circle2.GetHookPoint()->Move(-5, -5);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(-5, 0));
         Assert::IsTrue(intersect2 == Point2d(0, -5));

         circle2.GetHookPoint()->Move(5, -5);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(0, -5));
         Assert::IsTrue(intersect2 == Point2d(5, 0));

         circle2.GetHookPoint()->Move(0, 5);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(-4.330127, 2.5));
         Assert::IsTrue(intersect2 == Point2d(4.330127, 2.5));

         circle2.GetHookPoint()->Move(0, -5);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(-4.330127, -2.5));
         Assert::IsTrue(intersect2 == Point2d(4.330127, -2.5));

         circle2.GetHookPoint()->Move(5, 0);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(2.5, 4.330127));
         Assert::IsTrue(intersect2 == Point2d(2.5, -4.330127));


         circle2.GetHookPoint()->Move(-5, 0);
         circle2.SetRadius(5);
         result = GeometricOperations::Intersect(circle1, circle2, &intersect1, &intersect2);
         Assert::IsTrue(result == 2);
         Assert::IsTrue(intersect1 == Point2d(-2.5, 4.330127));
         Assert::IsTrue(intersect2 == Point2d(-2.5, -4.330127));
      }

      TEST_METHOD(IsLineParallelToLineSEgment)
      {
         Point2d p1, p2, p3, p4;
         p1.Move(0, 0);
         p2.Move(10, 10);
         p3.Move(10, 0);
         p4.Move(0, 10);
         Line2d line(p1, p2);
         LineSegment2d seg1(p3, p4);
         Assert::IsTrue(!GeometricOperations::IsParallel(line, seg1));

         p3.Move(0, 10);
         p4.Move(10, 20);
         seg1.ThroughPoints(p3, p4);
         Assert::IsTrue(GeometricOperations::IsParallel(line, seg1));
         Assert::IsTrue(GeometricOperations::IsParallel(seg1, line));
      }

      TEST_METHOD(AreLineSegmentsParallel)
      {
         Point2d p1, p2, p3, p4;
         p1.Move(-10, -10);
         p2.Move(-20, -20);
         LineSegment2d seg1(p1, p2);

         p3.Move(0, -20);
         p4.Move(-20, -40);
         LineSegment2d seg2(p3, p4);
         Assert::IsTrue(GeometricOperations::IsParallel(seg1, seg2));

         p4.Offset(3, 5);
         seg2.ThroughPoints(seg2.GetStartPoint(), p4);
         Assert::IsTrue(!GeometricOperations::IsParallel(seg1, seg2));
      }

      TEST_METHOD(AreLinesParallel)
      {
         Point2d p1, p2, p3, p4;
         p1.Move(-10, -10);
         p2.Move(-20, -20);
         Line2d line(p1, p2);

         p3.Move(0, -20);
         p4.Move(-20, -40);
         Line2d line2(p3, p4);
         Assert::IsTrue(GeometricOperations::IsParallel(line, line2));
         Assert::IsTrue(GeometricOperations::IsParallel(line2, line));
         Assert::IsTrue(GeometricOperations::IsParallel(line, line));

         p4.Offset(3, 5);
         line2.ThroughPoints(p3, p4);
         Assert::IsTrue(!GeometricOperations::IsParallel(line, line2));
      }

      TEST_METHOD(PointInTriangle)
      {
         Point2d p1, p2, p3, p4;
         p1.Move(5, 5);
         p2.Move(0, 0);
         p3.Move(20, 0);
         p4.Move(0, 20);
         Assert::IsTrue(GeometricOperations::IsPointInTriangle(p1, p2, p3, p4));
         p1.Move(30, 30);
         Assert::IsFalse(GeometricOperations::IsPointInTriangle(p1, p2, p3, p4));
      }

      TEST_METHOD(Intersect)
      {
         Point2d p1_7(1, 7), pn3_3(-3, 3), p0_4(0, 4), p3_5(3, 5), p6_6(6, 6);
         Point2d p8_0(8, 0), p9_n1(9, -1), p5_n5(5, -5), p12_2(12, 2);

         Line2d l1(pn3_3, p0_4), l2(p1_7, p8_0), l3(p5_n5, p12_2);
         Line2d ln2(p8_0, p1_7);

         LineSegment2d ls0(p1_7, p1_7), ls1(pn3_3, p0_4), ls2(p1_7, p9_n1), ls3(p5_n5, p12_2);
         LineSegment2d ls4(p0_4, p6_6), ls5(pn3_3, p6_6), ls6(p3_5, p1_7);

         Point2d pt;

         // intersect
         Assert::IsTrue(1 == GeometricOperations::Intersect(l1, l2, &pt));
         Assert::IsTrue(pt == p3_5);
         Assert::IsTrue(1 == GeometricOperations::Intersect(l3, l2, &pt));
         Assert::IsTrue(pt == p9_n1);
         Assert::IsTrue(-1 == GeometricOperations::Intersect(l2, ln2, &pt));

         Assert::IsTrue(1 == GeometricOperations::Intersect(ls4, ls2, &pt));
         Assert::IsTrue(pt == p3_5);
         Assert::IsTrue(1 == GeometricOperations::Intersect(ls2, ls3, &pt));
         Assert::IsTrue(pt == p9_n1);
         Assert::IsTrue(-1 == GeometricOperations::Intersect(ls1, ls4, &pt));
         Assert::IsTrue(pt == p0_4);
         Assert::IsTrue(0 == GeometricOperations::Intersect(ls4, ls3, &pt));
         Assert::IsTrue(0 == GeometricOperations::Intersect(ls2, ls1, &pt));
         Assert::IsTrue(0 == GeometricOperations::Intersect(ls0, ls1, &pt));

         // zero length line segment tests
         LineSegment2d ls7(10, 50, 10, 100);
         Line2d l4(ls7);
         LineSegment2d zls1(10, 10, 10, 10);
         LineSegment2d zls2(10, 60, 10, 60);
         LineSegment2d zls3(10, 10, 10, 10);
         Assert::IsTrue(GeometricOperations::Intersect(ls7, zls1, &pt) == 0);
         Assert::IsTrue(GeometricOperations::Intersect(ls7, zls2, &pt) == 1 && pt == Point2d(10, 60));
         Assert::IsTrue(GeometricOperations::Intersect(zls1, zls3, &pt) == 1 && pt == Point2d(10, 10));
         Assert::IsTrue(GeometricOperations::Intersect(l4, zls2, &pt) == 1 && pt == Point2d(10, 60));
         Assert::IsTrue(GeometricOperations::Intersect(zls2, l4, &pt) == 1 && pt == Point2d(10, 60));

         LineSegment2d ls8(25.6792, 0.000, 25.6792, -.0001);
         LineSegment2d ls9(25.6792, -0.000007, 25.6792, -0.000007);
         Assert::IsTrue(GeometricOperations::Intersect(ls8, ls9, &pt) == 1);

         // parallel
         Assert::IsTrue(GeometricOperations::IsParallel(ls2, ls6));
         Assert::IsTrue(!GeometricOperations::SameDirection(ls2, ls6)); // parallel, but not in the same direction
         Assert::IsTrue(GeometricOperations::IsParallel(ls1, ls4));
         Assert::IsTrue(!GeometricOperations::IsParallel(ls1, ls3));

         try
         {
            // ls0 - end points are coincident so it isn't a valid line
            Assert::IsTrue(!GeometricOperations::IsParallel(ls1, ls0));
            Assert::IsTrue(false);
         }
         catch (...)
         {
            Assert::IsTrue(true);
         }
      }

      TEST_METHOD(GenerateCircle)
      {
         std::vector<Point2d> points;
         GeometricOperations::GenerateCircle(0, Point2d(0, 0), 10, M_PI / 4, &points);
         Assert::IsTrue(points.empty());

         GeometricOperations::GenerateCircle(4, Point2d(0, 0), 10., 0., &points);
         Assert::IsTrue(points.size() == 4);
         Assert::IsTrue(points[0] == Point2d(10, 0));
         Assert::IsTrue(points[1] == Point2d(0, 10));
         Assert::IsTrue(points[2] == Point2d(-10, 0));
         Assert::IsTrue(points[3] == Point2d(0, -10));

         points.clear();
         GeometricOperations::GenerateCircle(4, Point2d(0, 0), 10., M_PI / 4, &points);
         Assert::IsTrue(points.size() == 4);
         Assert::IsTrue(points[0] == Point2d(7.071067, 7.071067));
         Assert::IsTrue(points[1] == Point2d(-7.071067, 7.071067));
         Assert::IsTrue(points[2] == Point2d(-7.071067, -7.071067));
         Assert::IsTrue(points[3] == Point2d(7.071067, -7.071067));
      }

      TEST_METHOD(NormalizeAngle)
      {
         Float64 angle = 3 * M_PI / 4;
         Assert::IsTrue(IsEqual(GeometricOperations::NormalizeAngle(angle), angle));
         Assert::IsTrue(IsEqual(GeometricOperations::NormalizeAngle(5 * TWO_PI + angle), angle));
         Assert::IsTrue(IsEqual(GeometricOperations::NormalizeAngle(-5 * TWO_PI + angle), angle));
      }

      TEST_METHOD(LineCircleIntersection)
      {
         Circle2d circle(Point2d(0, 0), Point2d(10, 0));

         Point2d p1, p2;

         // Line on horizontal diameter
         Line2d l1(Point2d(0, 0), Point2d(10, 0));
         auto nIntersect = GeometricOperations::Intersect(l1, circle, &p1, &p2);
         Assert::IsTrue(nIntersect == 2);
         Assert::IsTrue(p1 == Point2d(0, 0));
         Assert::IsTrue(p2 == Point2d(10, 0));

         // Horizontal line at top of circle
         l1.ThroughPoints(Point2d(0, 5), Point2d(5, 5));
         nIntersect = GeometricOperations::Intersect(l1, circle, &p1, &p2);
         Assert::IsTrue(nIntersect == 1);
         Assert::IsTrue(p1 == Point2d(5, 5));

         // Vertical line on diameter
         l1.ThroughPoints(Point2d(5, -5), Point2d(5, 5));
         nIntersect = GeometricOperations::Intersect(l1, circle, &p1, &p2);
         Assert::IsTrue(nIntersect == 2);
         Assert::IsTrue(p1 == Point2d(5, 5));
         Assert::IsTrue(p2 == Point2d(5, -5));

         // Vertical line on right edge of circle
         l1.ThroughPoints(Point2d(10, 0), Point2d(10, 5));
         nIntersect = GeometricOperations::Intersect(l1, circle, &p1, &p2);
         Assert::IsTrue(nIntersect == 1);
         Assert::IsTrue(p1 == Point2d(10, 0));

         // 45 degree line through the origin
         l1.ThroughPoints(Point2d(0, 0), Point2d(5, 5));
         nIntersect = GeometricOperations::Intersect(l1, circle, &p1, &p2);
         Assert::IsTrue(nIntersect == 2);
         Assert::IsTrue(p1 == Point2d(0, 0));
         Assert::IsTrue(p2 == Point2d(5, 5));

         // Line that doesn't intersect
         l1.ThroughPoints(Point2d(100, 100), Point2d(100, 200));
         nIntersect = GeometricOperations::Intersect(l1, circle, &p1, &p2);
         Assert::IsTrue(nIntersect == 0);
      }
	};
}
