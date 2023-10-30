#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestCOGO)
	{
	public:
	
      TEST_METHOD(Measure)
      {
         WBFL::Geometry::Point2d p1(10, 10);
         WBFL::Geometry::Point2d p2(20, 20);
         WBFL::Geometry::Point2d p3(30, 10);

         Assert::IsTrue(COGO::MeasureAngle(p1, p2, p3) == Angle(PI_OVER_2));
         Assert::IsTrue(COGO::MeasureAngle(p3, p2, p1) == Angle(3 * PI_OVER_2));

         Assert::IsTrue(IsEqual(COGO::MeasureDistance(p1, p2), sqrt(200)));
         Assert::IsTrue(IsEqual(COGO::MeasureDistance(p2, p3), sqrt(200)));
         Assert::IsTrue(IsEqual(COGO::MeasureDistance(p1, p3), 20.0));

         Assert::IsTrue(COGO::MeasureDirection(p1, p2) == Direction(M_PI / 4));
         Assert::IsTrue(COGO::MeasureDirection(p2, p3) == Direction(7 * M_PI / 4));
         Assert::IsTrue(COGO::MeasureDirection(p1, p3) == Direction(0.0));
         Assert::IsTrue(COGO::MeasureDirection(p3, p1) == Direction(M_PI));

         std::vector<WBFL::Geometry::Point2d> points{ p1, p2, p3 };
         Assert::IsTrue(IsEqual(COGO::MeasureArea(points), 100.0));
      }

      TEST_METHOD(Locate)
      {
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);

         Assert::IsTrue(COGO::LocateByDistanceAndDirection(p2, 10.0, PI_OVER_2, 0.0) == WBFL::Geometry::Point2d(10., 10.));
         Assert::IsTrue(COGO::LocateByDistanceAndDirection(p2, 10.0, PI_OVER_2, 5.0) == WBFL::Geometry::Point2d(15., 10.));
         Assert::IsTrue(COGO::LocateByDistanceAndDirection(p2, 10.0, PI_OVER_2, -5.0) == WBFL::Geometry::Point2d(5., 10.));

         Direction direction(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::West);
         Assert::IsTrue(COGO::LocateByDistanceAndDirection(p2, 10.0, direction, 0.0) == WBFL::Geometry::Point2d(2.92893218813, 7.07106781187));
         Assert::IsTrue(COGO::LocateByDistanceAndDirection(p2, 10.0, direction, 5.0) == WBFL::Geometry::Point2d(6.4644660940, 10.6066017178));
         Assert::IsTrue(COGO::LocateByDistanceAndDirection(p2, 10.0, direction, -5.0) == WBFL::Geometry::Point2d(-0.60660171781, 3.53553390593));
         Assert::IsTrue(COGO::LocateByDistanceAndDirection(p2, -10.0, direction, 0.0) == WBFL::Geometry::Point2d(17.07106781187, -7.07106781187));

         p1.Move(10, 10);
         p2.Move(0, 0);
         Angle angle(225, 0, 0);
         Assert::IsTrue(COGO::LocateByDistanceAndAngle(p1, p2, 10.0, M_PI / 4, 0.0) == WBFL::Geometry::Point2d(0.0, 10.0));
         Assert::IsTrue(COGO::LocateByDistanceAndAngle(p1, p2, 10.0, angle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, -13.53553390594));
         Assert::IsTrue(COGO::LocateByDistanceAndAngle(p1, p2, -10.0, angle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

         Angle defAngle(45, 0, 0);
         Assert::IsTrue(COGO::LocateByDistanceAndDeflectionAngle(p1, p2, 10.0, M_PI, 0.0) == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));
         Assert::IsTrue(COGO::LocateByDistanceAndDeflectionAngle(p1, p2, 10.0, M_PI / 4, 0.0) == WBFL::Geometry::Point2d(0.0, -10.0));
         Assert::IsTrue(COGO::LocateByDistanceAndDeflectionAngle(p1, p2, 10.0, defAngle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, -13.53553390594));
         Assert::IsTrue(COGO::LocateByDistanceAndDeflectionAngle(p1, p2, -10.0, defAngle, -5.0) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

         p1.Move(10, 10);
         p2.Move(20, 20);
         Assert::IsTrue(COGO::LocatePointOnLine(p1, p2, 20.0, 0.0) == WBFL::Geometry::Point2d(24.1421356237, 24.1421356237));
         Assert::IsTrue(COGO::LocatePointOnLine(p1, p2, -20.0, 0.0) == WBFL::Geometry::Point2d(-4.1421356237, -4.1421356237));
         Assert::IsTrue(COGO::LocatePointOnLine(p1, p2, 10.0, 5.0) == WBFL::Geometry::Point2d(20.6066017178, 13.5355339059));
         Assert::IsTrue(COGO::LocatePointOnLine(p1, p2, 10.0, -5.0) == WBFL::Geometry::Point2d(13.5355339059, 20.6066017178));

         // ParallelLineSegment and ParallelLineByPoints
         p1.Move(0, 0);
         p2.Move(20, 20);
         WBFL::Geometry::LineSegment2d segment(p1, p2);

         auto newSegment = COGO::LocateParallelLineSegment(segment, 5.0);
         Assert::IsTrue(newSegment.GetStartPoint() == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
         Assert::IsTrue(newSegment.GetEndPoint() == WBFL::Geometry::Point2d(23.5355339059, 16.4644660941));

         newSegment = COGO::LocateParallelLineSegment(segment, -5.0);
         Assert::IsTrue(newSegment.GetStartPoint() == WBFL::Geometry::Point2d(-3.53553390594, 3.53553390594));
         Assert::IsTrue(newSegment.GetEndPoint() == WBFL::Geometry::Point2d(16.4644660941, 23.5355339059));

         std::tie(p1, p2) = COGO::LocateParallelLineByPoints(p1, p2, 5.0);
         Assert::IsTrue(p1 == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
         Assert::IsTrue(p2 == WBFL::Geometry::Point2d(23.5355339059, 16.4644660940));
      }

      TEST_METHOD(Intersect)
      {
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);

         Assert::IsTrue(COGO::IntersectBearings(p1, M_PI / 4, 0.0, p2, 3 * M_PI / 4, 0.0) == WBFL::Geometry::Point2d(5.0, 5.0));
         Assert::IsTrue(COGO::IntersectBearings(p1, M_PI / 4, 5.0, p2, 3 * M_PI / 4, 5.0) == WBFL::Geometry::Point2d(12.0710678119, 5.0));
         try { COGO::IntersectBearings(p1, M_PI / 4, 0.0, p2, M_PI / 4, 0.0); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }


         p1.Move(0, 0);
         WBFL::Geometry::Point2d center(10, 10);
         WBFL::Geometry::Point2d nearest(15, 15);
         Assert::IsTrue(COGO::IntersectBearingAndCircle(p1, M_PI / 4, 0.0, center, 5.0, nearest) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));
         Assert::IsTrue(COGO::IntersectBearingAndCircle(p1, M_PI / 4, 0.0, center, 5.0, p1) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));
         Assert::IsTrue(COGO::IntersectBearingAndCircle(p1, PI_OVER_2, 5.0, center, 5.0, p1) == WBFL::Geometry::Point2d(5.0, 10.0));
         try { COGO::IntersectBearingAndCircle(p1, PI_OVER_2, 0.0, center, 5.0, p1); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }


         p1.Move(10, 10);
         p2.Move(20, 20);
         nearest.Move(20, 0);
         Assert::IsTrue(COGO::IntersectCircles(p1, 10.0, p2, 10.0, nearest) == WBFL::Geometry::Point2d(20, 10));
         Assert::IsTrue(COGO::IntersectCircles(p1, 20.0, WBFL::Geometry::Point2d(20, 10), 10.0, nearest) == WBFL::Geometry::Point2d(30, 10));
         Assert::IsTrue(COGO::IntersectCircles(p1, 20.0, WBFL::Geometry::Point2d(20, 10), 20.0, WBFL::Geometry::Point2d(0, 20)) == WBFL::Geometry::Point2d(15.0, 29.3649167));
         try { COGO::IntersectCircles(p1, 2.0, p2, 2.0, nearest); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

         p1.Move(0, 0);
         p2.Move(15, 15);
         center.Move(10, 10);
         Assert::IsTrue(COGO::IntersectLineByPointsAndCircle(p1, p2, 0.0, center, 5.0, p2) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));
         Assert::IsTrue(COGO::IntersectLineByPointsAndCircle(p1, p2, 0.0, center, 5.0, p1) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));
         Assert::IsTrue(COGO::IntersectLineByPointsAndCircle(p1, WBFL::Geometry::Point2d(0, 20), 5.0, center, 5.0, p1) == WBFL::Geometry::Point2d(5, 10));
         try { COGO::IntersectLineByPointsAndCircle(p1, WBFL::Geometry::Point2d(0, 20), 0.0, center, 5.0, p1); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

         p1.Move(0, 0);
         p2.Move(10, 0);
         WBFL::Geometry::Point2d p3(10, 10);
         WBFL::Geometry::Point2d p4(0, 10);

         Assert::IsTrue(COGO::IntersectLinesByPoints(p1, p3, 0.0, p2, p4, 0.0) == WBFL::Geometry::Point2d(5, 5));
         Assert::IsTrue(COGO::IntersectLinesByPoints(p1, p3, 5.0, p2, p4, 5.0) == WBFL::Geometry::Point2d(12.0710678119, 5));
         try { COGO::IntersectLinesByPoints(p1, p2, 0.0, p3, p4, 0.0); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

         Assert::IsTrue(COGO::IntersectLineSegments(WBFL::Geometry::LineSegment2d(p1, p3), 0.0, WBFL::Geometry::LineSegment2d(p2, p4), 0.0) == WBFL::Geometry::Point2d(5, 5));
         Assert::IsTrue(COGO::IntersectLineSegments(WBFL::Geometry::LineSegment2d(p1, p3), 5.0, WBFL::Geometry::LineSegment2d(p2, p4), 5.0) == WBFL::Geometry::Point2d(12.0710678119, 5));
         try { COGO::IntersectLineSegments(WBFL::Geometry::LineSegment2d(p1, p2), 0.0, WBFL::Geometry::LineSegment2d(p3, p4), 0.0); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

         p1.Move(0, 0);
         p2.Move(10, 10);
         p3.Move(15, 15);
         p4.Move(0, 20);
         Assert::IsTrue(COGO::IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p3), 0.0, p2, 5.0, p3) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));
         Assert::IsTrue(COGO::IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p3), 0.0, p2, 5.0, p1) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));
         Assert::IsTrue(COGO::IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p4), 5.0, p2, 5.0, p1) == WBFL::Geometry::Point2d(5, 10));
         try { COGO::IntersectLineSegmentAndCircle(WBFL::Geometry::LineSegment2d(p1, p4), 0.0, p2, 5.0, p1); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_NOINTERSECTION); }

      }

      TEST_METHOD(Project)
      {
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(5, 5);
         WBFL::Geometry::Point2d p3(6, 12);
         WBFL::Geometry::Point2d p4(12, 6);

         Assert::IsTrue(COGO::ProjectPointOnLineByPoints(p3, p1, p2, 0.0) == WBFL::Geometry::Point2d(9, 9));
         Assert::IsTrue(COGO::ProjectPointOnLineByPoints(p4, p1, p2, 0.0) == WBFL::Geometry::Point2d(9, 9));
         Assert::IsTrue(COGO::ProjectPointOnLineByPoints(p3, p1, p2, 4.24264068712) == WBFL::Geometry::Point2d(12, 6));
         Assert::IsTrue(COGO::ProjectPointOnLineByPoints(p3, p1, p2, -4.24264068712) == WBFL::Geometry::Point2d(6, 12));

         Assert::IsTrue(COGO::ProjectPointOnLineSegment(p3, WBFL::Geometry::LineSegment2d(p1, p2), 0.0) == WBFL::Geometry::Point2d(9, 9));
         Assert::IsTrue(COGO::ProjectPointOnLineSegment(p3, WBFL::Geometry::LineSegment2d(p1, p2), 4.24264068712) == WBFL::Geometry::Point2d(12, 6));
      }

      TEST_METHOD(Divide)
      {
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);
         WBFL::Geometry::Point2d p3(-10, 0);

         auto points = COGO::DivideArc(p2, p1, p3, 4);
         Assert::IsTrue(points.size() == 5); // divided the arc into 4 pieces, with 5 points
         Assert::IsTrue(points[0] == p2);
         Assert::IsTrue(points[1] == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));
         Assert::IsTrue(points[2] == WBFL::Geometry::Point2d(0, 10));
         Assert::IsTrue(points[3] == WBFL::Geometry::Point2d(-7.07106781187, 7.07106781187));
         Assert::IsTrue(points[4] == p3);

         p1.Move(10, 10);
         p2.Move(110, 110);
         points = COGO::DivideBetweenPoints(p1, p2, 10);
         Assert::IsTrue(points.size() == 11);
         int i = 1;
         for (const auto& point : points)
         {
            Assert::IsTrue(point == WBFL::Geometry::Point2d(p1.X() * i, p1.Y() * i));
            i++;
         }
      }

      TEST_METHOD(Tangent)
      {
         WBFL::Geometry::Point2d p1(10, 10);
         WBFL::Geometry::Point2d p2(40, 10);
         WBFL::Geometry::Point2d t1, t2;

         // ExternalTangents

         // define the big circle first
         std::tie(t1, t2) = COGO::ExternalTangents(p1, 20, p2, 5, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(20.0, 27.3205));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(42.5, 14.33013));

         std::tie(t1, t2) = COGO::ExternalTangents(p1, 20, p2, 5, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(20.0, 27.3205));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(42.5, 14.33013));

         // define the small circle first
         std::tie(t1, t2) = COGO::ExternalTangents(p2, 5, p1, 20, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(42.5, 14.33013));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(20.0, 27.3205));

         std::tie(t1, t2) = COGO::ExternalTangents(p2, 5, p1, 20, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(42.5, 14.33013));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(20.0, 27.3205));

         // rotate both circles 180 deg around (0,0) (make x = -x)
         p1.X() *= -1;
         p2.X() *= -1;

         // big circle first
         std::tie(t1, t2) = COGO::ExternalTangents(p1, 20, p2, 5, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-20.0, -7.3205));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-42.5, 5.66987));

         std::tie(t1, t2) = COGO::ExternalTangents(p1, 20, p2, 5, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-20.0, -7.3205));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-42.5, 5.66987));

         // small circle first
         std::tie(t1, t2) = COGO::ExternalTangents(p2, 5, p1, 20, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-42.5, 5.66987));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-20.0, -7.3205));

         std::tie(t1, t2) = COGO::ExternalTangents(p2, 5, p1, 20, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-42.5, 5.66987));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-20.0, -7.3205));

         // make Y = x and X = -Y
         p1.Move(-10, 10);
         p2.Move(-10, 40);

         // big circle first
         std::tie(t1, t2) = COGO::ExternalTangents(p1, 20, p2, 5, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-27.3205, 20));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-14.33013, 42.5));

         std::tie(t1, t2) = COGO::ExternalTangents(p1, 20, p2, 5, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-27.3205, 20));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-14.33013, 42.5));

         // small circle first
         std::tie(t1, t2) = COGO::ExternalTangents(p2, 5, p1, 20, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-14.33013, 42.5));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-27.3205, 20.0));

         std::tie(t1, t2) = COGO::ExternalTangents(p2, 5, p1, 20, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-14.33013, 42.5));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-27.3205, 20.0));

         // Quadrants   ^
         //             |
         //       2     |     1
         //             |
         //   ----------+----------->
         //             |
         //       3     |     4
         //             |

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 1
         p1.Move(0, 0);
         p2.Move(10, 10);
         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-3.53553, 3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(6.46447, 13.53553));

         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-3.53553, 3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(6.46447, 13.53553));

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 2
         p1.Move(0, 0);
         p2.Move(-10, 10);
         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-3.53553, -3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-13.53553, 6.46447));

         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(-3.53553, -3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-13.53553, 6.46447));

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 3
         p1.Move(0, 0);
         p2.Move(-10, -10);
         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(3.53553, -3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-6.46447, -13.53553));

         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(3.53553, -3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(-6.46447, -13.53553));

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 4
         p1.Move(0, 0);
         p2.Move(10, -10);
         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(3.53553, 3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(13.53553, -6.46447));

         std::tie(t1, t2) = COGO::ExternalTangents(p1, 5.0, p2, 5.0, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(3.53553, 3.53553));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(13.53553, -6.46447));

         // CrossingTangents
         p1.Move(10, 10);
         p2.Move(40, 10);
         std::tie(t1, t2) = COGO::CrossingTangents(p1, 20.0, p2, 5.0, TangentSign::CW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(26.66666, -1.05541));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(44.16667, 12.76385));

         std::tie(t1, t2) = COGO::CrossingTangents(p1, 20.0, p2, 5.0, TangentSign::CCW);
         Assert::IsTrue(t1 == WBFL::Geometry::Point2d(26.66666, 21.055415));
         Assert::IsTrue(t2 == WBFL::Geometry::Point2d(44.16667, 7.23615));

         // TangentPoint
         Float64 radius = 20.;
         p1.Move(10, 10);
         p2.Move(10 + radius * sqrt(2.), 10);

         Assert::IsTrue(COGO::TangentPoint(p1, radius, p2, TangentSign::CW) == WBFL::Geometry::Point2d(24.14214, -4.14214));
         Assert::IsTrue(COGO::TangentPoint(p1, radius, p2, TangentSign::CCW) == WBFL::Geometry::Point2d(24.14214, 24.14214));
         Assert::IsTrue(COGO::TangentPoint(p1, radius, WBFL::Geometry::Point2d(10 + radius, 10 + radius), TangentSign::CW) == WBFL::Geometry::Point2d(30, 10));
         Assert::IsTrue(COGO::TangentPoint(p1, radius, WBFL::Geometry::Point2d(10 + radius, 10 + radius), TangentSign::CCW) == WBFL::Geometry::Point2d(10, 30));
      }
   };
}
