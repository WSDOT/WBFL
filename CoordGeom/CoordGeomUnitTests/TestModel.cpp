#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestModel)
	{
	public:
      TEST_METHOD(Measure)
      {
         // Distance
         Model model;
         model.StorePoint(1, 10.0, 10.0);
         model.StorePoint(2, 40.0, 20.0);
         model.StorePoint(3, 40.0, 0.0);

         try { model.MeasureDistance(1, 20); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_INVALIDARG); }

         try { model.MeasureDistance(10, 2); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_INVALIDARG); }

         Assert::IsTrue(IsEqual(model.MeasureDistance(1, 2), 31.62277660));
         Assert::IsTrue(IsEqual(model.MeasureDistance(1, 1), 0.0));

         // Angle
         model.ClearPoints();
         model.StorePoint(1, 10, 0);
         model.StorePoint(2, 0, 0);
         model.StorePoint(3, 0, 10);

         Assert::IsTrue(model.MeasureAngle(1, 2, 3) == Angle(PI_OVER_2));
         Assert::IsTrue(model.MeasureAngle(3, 2, 1) == Angle(3 * PI_OVER_2));

         // Direction
         model.ClearPoints();
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 20, 20);
         Assert::IsTrue(model.MeasureDirection(1, 2) == Direction(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::East));
         Assert::IsTrue(model.MeasureDirection(1, 1) == Direction(Direction::NSDirection::North, 90, 0, 0, Direction::EWDirection::East));

         // Area
         model.ClearPoints();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 0);
         model.StorePoint(3, 10, 10);
         model.StorePoint(4, 0, 10);
         std::vector<IDType> vID{ 1, 2, 3, 4 };
         Assert::IsTrue(IsEqual(model.MeasureArea(vID), 100.0));
         vID.pop_back(); // remove two points so there isn't enough to compute an area
         vID.pop_back();
         Assert::IsTrue(IsEqual(model.MeasureArea(vID), 0.0));
      }

      TEST_METHOD(Locate)
      {
         // Distance and Direction
         Model model;
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 0);

         Assert::IsTrue(model.LocateByDistanceAndDirection(3, 2, 10.0, PI_OVER_2, 0.0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(10, 10));

         Assert::IsTrue(model.LocateByDistanceAndDirection(3, 2, 10.0, PI_OVER_2, 5.0) == false);
         Assert::IsTrue(model.LocateByDistanceAndDirection(4, 2, 10.0, PI_OVER_2, 5.0));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(15, 10));

         Assert::IsTrue(model.LocateByDistanceAndDirection(5, 2, 10.0, PI_OVER_2, -5.0));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(5, 10));

         Direction direction(Direction::NSDirection::North, 45, 0, 0, Direction::EWDirection::West);
         Assert::IsTrue(model.LocateByDistanceAndDirection(6, 2, 10, direction, 0.0));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(2.92893218813, 7.07106781187));

         Assert::IsTrue(model.LocateByDistanceAndDirection(7, 2, 10, direction, 5.0));
         Assert::IsTrue(model.GetPoint(7) == WBFL::Geometry::Point2d(6.46446609407, 10.6066017178));

         Assert::IsTrue(model.LocateByDistanceAndDirection(8, 2, 10, direction, -5.0));
         Assert::IsTrue(model.GetPoint(8) == WBFL::Geometry::Point2d(-0.60660171781, 3.53553390593));

         Assert::IsTrue(model.LocateByDistanceAndDirection(9, 2, -10, direction, 0.0));
         Assert::IsTrue(model.GetPoint(9) == WBFL::Geometry::Point2d(17.07106781187, -7.07106781187));

         // Distance and Angle
         model.ClearPoints();
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 0, 0);

         Assert::IsTrue(model.LocateByDistanceAndAngle(3, 1, 2, 10.0, M_PI, 0.0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(-7.07106781187, -7.07106781187));

         Assert::IsTrue(model.LocateByDistanceAndAngle(4, 1, 2, 10.0, M_PI / 4, 0.0));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(0, 10));

         Angle angle(225, 0, 0);
         Assert::IsTrue(model.LocateByDistanceAndAngle(5, 1, 2, 10.0, angle, -5.0));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(3.53553390594, -13.53553390594));

         Assert::IsTrue(model.LocateByDistanceAndAngle(6, 1, 2, -10.0, angle, -5.0));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

         // Distance and Deflection Angle
         model.ClearPoints();
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 0, 0);

         Assert::IsTrue(model.LocateByDistanceAndDeflectionAngle(3, 1, 2, 10, M_PI, 0.0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));

         Assert::IsTrue(model.LocateByDistanceAndDeflectionAngle(4, 1, 2, 10, M_PI / 4, 0.0));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(0, -10));

         Angle defAngle(45, 0, 0);
         Assert::IsTrue(model.LocateByDistanceAndDeflectionAngle(5, 1, 2, 10, defAngle, -5.0));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(3.53553390594, -13.53553390594));

         Assert::IsTrue(model.LocateByDistanceAndDeflectionAngle(6, 1, 2, -10, defAngle, -5.0));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(3.53553390594, 6.46446609406));

         // Point On Line
         model.ClearPoints();
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 20, 20);

         Assert::IsTrue(model.LocatePointOnLine(3, 1, 2, 20, 0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(24.1421356237, 24.1421356237));

         Assert::IsTrue(model.LocatePointOnLine(4, 1, 2, -20, 0));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(-4.1421356237, -4.1421356237));

         Assert::IsTrue(model.LocatePointOnLine(5, 1, 2, 10, 5));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(20.6066017178, 13.5355339059));

         Assert::IsTrue(model.LocatePointOnLine(6, 1, 2, 10, -5));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(13.5355339059, 20.6066017178));

         // ParallelLineSegment and ParallelLineByPoints
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 20, 20);
         model.StorePathSegment(1, 1, 2);

         Assert::IsTrue(model.LocateParallelLineSegment(2, 3, 4, 1, 5.0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(23.5355339059, 16.4644660941));
         Assert::IsTrue(model.CreatePathSegment(2)->GetStartPoint() == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
         Assert::IsTrue(model.CreatePathSegment(2)->GetEndPoint() == WBFL::Geometry::Point2d(23.5355339059, 16.4644660941));

         Assert::IsTrue(model.LocateParallelLineSegment(3, 5, 6, 1, -5.0));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(-3.53553390594, 3.53553390594));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(16.4644660941, 23.5355339059));
         Assert::IsTrue(model.CreatePathSegment(3)->GetStartPoint() == WBFL::Geometry::Point2d(-3.53553390594, 3.53553390594));
         Assert::IsTrue(model.CreatePathSegment(3)->GetEndPoint() == WBFL::Geometry::Point2d(16.4644660941, 23.5355339059));


         Assert::IsTrue(model.LocateParallelLineByPoints(13, 14, 1, 2, 5.0));
         Assert::IsTrue(model.GetPoint(13) == WBFL::Geometry::Point2d(3.53553390594, -3.53553390594));
         Assert::IsTrue(model.GetPoint(14) == WBFL::Geometry::Point2d(23.5355339059, 16.4644660940));
      }

      TEST_METHOD(Intersect)
      {
         Model model;

         // IntersectBearings
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 0);
         Assert::IsTrue(model.IntersectBearings(3, 1, M_PI / 4, 0.0, 2, 3 * M_PI / 4, 0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(5, 5));

         Assert::IsTrue(model.IntersectBearings(4, 1, M_PI / 4, 5.0, 2, 3 * M_PI / 4, 5));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(12.0710678119, 5));

         Assert::IsTrue(model.IntersectBearings(5, 1, M_PI / 4, 0.0, 2, M_PI / 4, 0) == false);

         // IntersectBearingAndCircle
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 10);
         model.StorePoint(3, 15, 15);

         Assert::IsTrue(model.IntersectBearingAndCircle(4, 1, M_PI / 4, 0.0, 2, 5.0, 3));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));

         Assert::IsTrue(model.IntersectBearingAndCircle(5, 1, M_PI / 4, 0.0, 2, 5.0, 1));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));

         Assert::IsTrue(model.IntersectBearingAndCircle(6, 1, PI_OVER_2, 5.0, 2, 5.0, 1));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(5, 10));

         Assert::IsTrue(model.IntersectBearingAndCircle(7, 1, PI_OVER_2, 0.0, 2, 5.0, 1) == false);

         // IntersectCircles
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 10);
         model.StorePoint(3, 20, 20);
         model.StorePoint(4, 20, 0);
         model.StorePoint(5, 0, 20);

         Assert::IsTrue(model.IntersectCircles(6, 2, 10.0, 3, 10.0, 4));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(20, 10));

         Assert::IsTrue(model.IntersectCircles(7, 2, 20.0, 6, 10.0, 4));
         Assert::IsTrue(model.GetPoint(7) == WBFL::Geometry::Point2d(30, 10));

         Assert::IsTrue(model.IntersectCircles(8, 2, 20.0, 6, 20.0, 5));
         Assert::IsTrue(model.GetPoint(8) == WBFL::Geometry::Point2d(15, 29.3649167));

         Assert::IsTrue(model.IntersectCircles(9, 2, 2.0, 3, 2.0, 4) == false);

         // IntersectLineByPointsAndCircle
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 10);
         model.StorePoint(3, 15, 15);
         model.StorePoint(10, 0, 20);

         Assert::IsTrue(model.IntersectLineByPointsAndCircle(4, 1, 3, 0.0, 2, 5.0, 3));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));

         Assert::IsTrue(model.IntersectLineByPointsAndCircle(5, 1, 3, 0.0, 2, 5.0, 1));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));

         Assert::IsTrue(model.IntersectLineByPointsAndCircle(6, 1, 10, 5.0, 2, 5.0, 1));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(5, 10));

         Assert::IsTrue(model.IntersectLineByPointsAndCircle(7, 1, 10, 0.0, 2, 5.0, 1) == false);

         // IntersectLinesByPoints
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 0);
         model.StorePoint(30, 10, 10);
         model.StorePoint(40, 0, 10);

         Assert::IsTrue(model.IntersectLinesByPoints(3, 1, 30, 0.0, 2, 40, 0.0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(5, 5));

         Assert::IsTrue(model.IntersectLinesByPoints(4, 1, 30, 5.0, 2, 40, 5.0));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(12.0710678119, 5));

         Assert::IsTrue(model.IntersectLinesByPoints(5, 1, 2, 0.0, 30, 40, 0.0) == false);

         // IntersectPathSegments
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 0);
         model.StorePoint(30, 10, 10);
         model.StorePoint(40, 0, 10);
         model.StorePathSegment(1, 1, 30);
         model.StorePathSegment(2, 2, 40);

         Assert::IsTrue(model.IntersectPathSegments(3, 1, 0.0, 2, 0.0));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(5, 5));

         Assert::IsTrue(model.IntersectPathSegments(4, 1, 5.0, 2, 5.0));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(12.0710678119, 5));

         // make lines parallel
         auto p30 = model.GetPoint(30);// ->Move(0, 10);
         auto p40 = model.GetPoint(40);// ->Move(10, 10);
         p30.Move(0, 10);
         p40.Move(10, 10);
         model.ReplacePoint(30, p30);
         model.ReplacePoint(40, p40);
         Assert::IsTrue(model.IntersectPathSegments(5, 1, 0.0, 2, 0.0) == false);

         // IntersectLineSegmentAndCircle
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 10);
         model.StorePoint(3, 15, 15);
         model.StorePoint(10, 0, 20);
         model.StorePathSegment(1, 1, 3);
         model.StorePathSegment(2, 1, 10);

         Assert::IsTrue(model.IntersectPathSegmentAndCircle(4, 1, 0.0, 2, 5.0, 3));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(13.5355339059, 13.5355339059));

         Assert::IsTrue(model.IntersectPathSegmentAndCircle(5, 1, 0.0, 2, 5.0, 1));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(6.46446609406, 6.46446609406));

         Assert::IsTrue(model.IntersectPathSegmentAndCircle(6, 2, 5.0, 2, 5.0, 1));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(5, 10));

         Assert::IsTrue(model.IntersectPathSegmentAndCircle(7, 2, 0.0, 2, 5.0, 1) == false);
      }

      TEST_METHOD(Project)
      {
         Model model;

         model.StorePoint(1, 0, 1000);
         model.StorePoint(2, 700, 1000);
         model.StorePoint(3, 1000, 700);

         // ProjectPointOnCompoundCurve
         model.StoreCompoundCurve(1, 1, 2, 3, 500, 100, TransitionCurveType::Clothoid, 200, TransitionCurveType::Clothoid);
         Assert::IsTrue(model.ProjectPointOnCompoundCurve(5, 2, 1));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(683.12870529355951, 959.95042556846295));

         // ProjectPointOnLineByPoints
         model.Clear();
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 5, 5);
         model.StorePoint(3, 6, 12);
         model.StorePoint(4, 12, 6);

         Assert::IsTrue(model.ProjectPointOnLineByPoints(5, 3, 1, 2, 0.0));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(9, 9));

         Assert::IsTrue(model.ProjectPointOnLineByPoints(6, 4, 1, 2, 0.0));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(9, 9));

         Assert::IsTrue(model.ProjectPointOnLineByPoints(7, 3, 1, 2, 4.24264068712));
         Assert::IsTrue(model.GetPoint(7) == WBFL::Geometry::Point2d(12, 6));

         Assert::IsTrue(model.ProjectPointOnLineByPoints(8, 4, 1, 2, -4.24264068712));
         Assert::IsTrue(model.GetPoint(8) == WBFL::Geometry::Point2d(6, 12));

         // ProjectPointOnPathSegment
         model.StorePathSegment(1, 1, 2);
         Assert::IsTrue(model.ProjectPointOnPathSegment(9, 3, 1, 0.0));
         Assert::IsTrue(model.GetPoint(9) == WBFL::Geometry::Point2d(9, 9));
      }

      TEST_METHOD(Divide)
      {
         Model model;

         // Test DivideArc
         model.StorePoint(1, 0, 0);
         model.StorePoint(2, 10, 0);
         model.StorePoint(3, -10, 0);
         Assert::IsTrue(model.DivideArc(4, 1, 2, 1, 3, -1) == false);
         Assert::IsTrue(model.DivideArc(4, 1, 2, 1, 3, 0) == false);
         Assert::IsTrue(model.DivideArc(4, 1, 2, 1, 3, 1) == false);
         Assert::ExpectException<XCoordGeom>([&model]() {model.DivideArc(4, 1, -2, 1, 3, 4); });
         Assert::ExpectException<XCoordGeom>([&model]() {model.DivideArc(4, 1, 2, -1, 3, 4); });
         Assert::ExpectException<XCoordGeom>([&model]() {model.DivideArc(4, 1, 2, 1, -3, 4); });
         Assert::IsTrue(model.DivideArc(1, 1, 2, 1, 3, 4) == false);
         Assert::IsTrue(model.DivideArc(4, 0, 2, 1, 3, 4) == false);
         Assert::IsTrue(model.DivideArc(4, 1, 1, 1, 3, 4) == false);
         Assert::IsTrue(model.DivideArc(4, 1, 2, 1, 1, 4) == false);
         Assert::IsTrue(model.DivideArc(4, 1, 2, 1, 3, 4) == true);
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(7.07106781187, 7.07106781187));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(0, 10));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(-7.07106781187, 7.07106781187));

         // Test DivideBetweenPoints
         model.Clear();
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 110, 110);
         Assert::IsTrue(model.DivideBetweenPoints(3, 1, 1, 2, 10));
         for (IDType i = 3; i <= 11; i++)
         {
            Assert::IsTrue(model.GetPoint(i) == WBFL::Geometry::Point2d((Float64)(i - 1) * 10, (Float64)(i - 1) * 10));
            i++;
         }

         // Test DivideLineSegment
         model.Clear();
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 110, 110);
         model.StorePathSegment(1, 1, 2);

         Assert::IsTrue(model.DivideLineSegment(3, 1, 1, -1) == false);
         Assert::IsTrue(model.DivideLineSegment(3, 1, 1, 0) == false);
         Assert::IsTrue(model.DivideLineSegment(3, 1, 1, 1) == false);
         Assert::IsTrue(model.DivideLineSegment(3, 0, 1, 10) == false);
         Assert::ExpectException<XCoordGeom>([&model]() {model.DivideLineSegment(3, 1, -1, 10); });
         Assert::IsTrue(model.DivideLineSegment(1, 1, 1, 10) == false);

         Assert::IsTrue(model.DivideLineSegment(3, 1, 1, 10) == true);
         for (IDType i = 3; i <= 11; i++)
         {
            Assert::IsTrue(model.GetPoint(i) == WBFL::Geometry::Point2d((Float64)(i - 1) * 10, (Float64)(i - 1) * 10));
            i++;
         }

         // Test CompoundCurve
         model.StorePoint(101, 0, 1000);
         model.StorePoint(102, 700, 1000);
         model.StorePoint(103, 1000, 700);

         model.StoreCompoundCurve(1, 101, 102, 103, 500, 100, TransitionCurveType::Clothoid, 200, TransitionCurveType::Clothoid);

         Assert::IsTrue(model.DivideCompoundCurve(150, 1, 1, -1) == false);
         Assert::IsTrue(model.DivideCompoundCurve(150, 0, 1, 5) == false);
         Assert::ExpectException<XCoordGeom>([&model]() {model.DivideCompoundCurve(150, 1, -1, 5); });
         Assert::IsTrue(model.DivideCompoundCurve(99, 1, 1, 5) == false);
         Assert::IsTrue(model.DivideCompoundCurve(150, 1, 1, 10) == true);

         Assert::IsTrue(model.GetPoint(150) == WBFL::Geometry::Point2d(493.30080, 999.46724));
         Assert::IsTrue(model.GetPoint(151) == WBFL::Geometry::Point2d(547.42511, 995.74397));
         Assert::IsTrue(model.GetPoint(152) == WBFL::Geometry::Point2d(600.87402, 986.49482));
         Assert::IsTrue(model.GetPoint(153) == WBFL::Geometry::Point2d(653.00647, 971.51016));
         Assert::IsTrue(model.GetPoint(154) == WBFL::Geometry::Point2d(703.20889, 950.96633));
         Assert::IsTrue(model.GetPoint(155) == WBFL::Geometry::Point2d(750.89045, 925.10512));
         Assert::IsTrue(model.GetPoint(156) == WBFL::Geometry::Point2d(795.54108, 894.29971));
         Assert::IsTrue(model.GetPoint(157) == WBFL::Geometry::Point2d(837.31329, 859.67354));
         Assert::IsTrue(model.GetPoint(158) == WBFL::Geometry::Point2d(876.98033, 822.64293));

         // Divide Path
         auto curve = model.CreateCompoundCurve(1);
         model.StorePoint(200, curve->GetTS());
         model.StorePoint(201, curve->GetST());

         std::vector<std::pair<Model::PathElementType, IDType>> vPathElements;
         vPathElements.emplace_back(Model::PathElementType::Point, 101);
         vPathElements.emplace_back(Model::PathElementType::Point, 200);
         vPathElements.emplace_back(Model::PathElementType::CompoundCurve, 1);
         vPathElements.emplace_back(Model::PathElementType::Point, 201);
         vPathElements.emplace_back(Model::PathElementType::Point, 103);
         model.StorePath(1, vPathElements);
         model.DividePath(350, 1, 1, 10, 0.0, -1.0);
         Assert::IsTrue(model.GetPoint(350) == WBFL::Geometry::Point2d(110.11756, 1000.00000));
         Assert::IsTrue(model.GetPoint(351) == WBFL::Geometry::Point2d(220.23513, 1000.00000));
         Assert::IsTrue(model.GetPoint(352) == WBFL::Geometry::Point2d(330.35269, 1000.00000));
         Assert::IsTrue(model.GetPoint(353) == WBFL::Geometry::Point2d(440.47026, 999.99999));
         Assert::IsTrue(model.GetPoint(354) == WBFL::Geometry::Point2d(550.41581, 995.38307));
         Assert::IsTrue(model.GetPoint(355) == WBFL::Geometry::Point2d(657.33575, 969.98482));
         Assert::IsTrue(model.GetPoint(356) == WBFL::Geometry::Point2d(756.12468, 921.84240));
         Assert::IsTrue(model.GetPoint(357) == WBFL::Geometry::Point2d(843.08205, 854.50477));
         Assert::IsTrue(model.GetPoint(358) == WBFL::Geometry::Point2d(922.13512, 777.86488));
      }

      TEST_METHOD(Tangent)
      {
         Model model;

         // Test ExternalTangent
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 40, 10);

         // Test some error cases
         Assert::IsTrue(model.ExternalTangents(3, 1, -20.0, 4, 2, 5.0, TangentSign::CW) == false); // COGO_E_RADIUS
         Assert::IsTrue(model.ExternalTangents(3, 1, 20.0, 4, 2, -5.0, TangentSign::CW) == false); // COGO_E_RADIUS
         Assert::ExpectException<XCoordGeom>([&model]() {model.ExternalTangents(3, 10, 20.0, 4, 2, 5.0, TangentSign::CW); }); // COGO_E_POINTNOTFOUND
         Assert::ExpectException<XCoordGeom>([&model]() {model.ExternalTangents(3, 1, 20.0, 4, 20, 5.0, TangentSign::CW); }); // COGO_E_POINTNOTFOUND
         Assert::IsTrue(model.ExternalTangents(1, 1, 20.0, 4, 2, 5.0, TangentSign::CW) == false); // COGO_E_POINTALREADYDEFINED
         Assert::IsTrue(model.ExternalTangents(3, 1, 20.0, 2, 2, 5.0, TangentSign::CW) == false); // COGO_E_POINTALREADYDEFINED
         Assert::IsTrue(model.ExternalTangents(3, 1, 20.0, 4, 1, 5.0, TangentSign::CW) == false); // COGO_E_COINCIDENTPOINTS

         // define the big circle first
         Assert::IsTrue(model.ExternalTangents(3, 1, 20.0, 4, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(20, 27.3205));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(42.5, 14.33013));

         Assert::IsTrue(model.ExternalTangents(5, 1, 20.0, 6, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(20, 27.3205));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(42.5, 14.33013));

         // define the small circle first
         Assert::IsTrue(model.ExternalTangents(7, 2, 5.0, 8, 1, 20.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(7) == WBFL::Geometry::Point2d(42.5, 14.33013));
         Assert::IsTrue(model.GetPoint(8) == WBFL::Geometry::Point2d(20, 27.3205));

         Assert::IsTrue(model.ExternalTangents(9, 2, 5.0, 10, 1, 20.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(9) == WBFL::Geometry::Point2d(42.5, 14.33013));
         Assert::IsTrue(model.GetPoint(10) == WBFL::Geometry::Point2d(20, 27.3205));

         // rotate both circles 180deg around (0,0)
         // (make x = -x)
         auto p1 = model.GetPoint(1);
         auto p2 = model.GetPoint(2);
         p1.Move(-10, 10);
         p2.Move(-40, 10);
         model.ReplacePoint(1, p1);
         model.ReplacePoint(2, p2);


         // big circle first
         Assert::IsTrue(model.ExternalTangents(11, 1, 20.0, 12, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(11) == WBFL::Geometry::Point2d(-20.0, -7.3205));
         Assert::IsTrue(model.GetPoint(12) == WBFL::Geometry::Point2d(-42.5, 5.66987));

         Assert::IsTrue(model.ExternalTangents(13, 1, 20.0, 14, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(13) == WBFL::Geometry::Point2d(-20.0, -7.3205));
         Assert::IsTrue(model.GetPoint(14) == WBFL::Geometry::Point2d(-42.5, 5.66987));

         // small circle first
         Assert::IsTrue(model.ExternalTangents(15, 2, 5.0, 16, 1, 20.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(15) == WBFL::Geometry::Point2d(-42.5, 5.66987));
         Assert::IsTrue(model.GetPoint(16) == WBFL::Geometry::Point2d(-20.0, -7.3205));

         Assert::IsTrue(model.ExternalTangents(17, 2, 5.0, 18, 1, 20.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(17) == WBFL::Geometry::Point2d(-42.5, 5.66987));
         Assert::IsTrue(model.GetPoint(18) == WBFL::Geometry::Point2d(-20.0, -7.3205));

         // rotate both (original) circles 90deg around (0,0)
         // (make Y = x, X = -Y)
         p1 = model.GetPoint(1);
         p2 = model.GetPoint(2);
         p1.Move(-10, 10);
         p2.Move(-10, 40);
         model.ReplacePoint(1, p1);
         model.ReplacePoint(2, p2);

         // big circle first
         Assert::IsTrue(model.ExternalTangents(19, 1, 20.0, 20, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(19) == WBFL::Geometry::Point2d(-27.3205, 20.0));
         Assert::IsTrue(model.GetPoint(20) == WBFL::Geometry::Point2d(-14.33013, 42.5));

         Assert::IsTrue(model.ExternalTangents(21, 1, 20.0, 22, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(21) == WBFL::Geometry::Point2d(-27.3205, 20.0));
         Assert::IsTrue(model.GetPoint(22) == WBFL::Geometry::Point2d(-14.33013, 42.5));

         // small circle first
         Assert::IsTrue(model.ExternalTangents(23, 2, 5.0, 24, 1, 20.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(23) == WBFL::Geometry::Point2d(-14.33013, 42.5));
         Assert::IsTrue(model.GetPoint(24) == WBFL::Geometry::Point2d(-27.3205, 20.0));

         Assert::IsTrue(model.ExternalTangents(25, 2, 5.0, 26, 1, 20.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(25) == WBFL::Geometry::Point2d(-14.33013, 42.5));
         Assert::IsTrue(model.GetPoint(26) == WBFL::Geometry::Point2d(-27.3205, 20.0));

         /////////////////////////////////////////////////////////////////////////////////////////

         // Quadrants   ^
         //             |
         //       2     |     1
         //             |
         //   ----------+----------->
         //             |
         //       3     |     4
         //             |

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 1
         p1 = model.GetPoint(1);
         p2 = model.GetPoint(2);
         p1.Move(0, 0);
         p2.Move(10, 10);
         model.ReplacePoint(1, p1);
         model.ReplacePoint(2, p2);
         Assert::IsTrue(model.ExternalTangents(27, 1, 5.0, 28, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(27) == WBFL::Geometry::Point2d(-3.53553, 3.53553));
         Assert::IsTrue(model.GetPoint(28) == WBFL::Geometry::Point2d(6.46447, 13.53553));

         Assert::IsTrue(model.ExternalTangents(29, 1, 5.0, 30, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(29) == WBFL::Geometry::Point2d(-3.53553, 3.53553));
         Assert::IsTrue(model.GetPoint(30) == WBFL::Geometry::Point2d(6.46447, 13.53553));

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 2
         p1 = model.GetPoint(1);
         p2 = model.GetPoint(2);
         p1.Move(0, 0);
         p2.Move(-10, 10);
         model.ReplacePoint(1, p1);
         model.ReplacePoint(2, p2);

         Assert::IsTrue(model.ExternalTangents(31, 1, 5.0, 32, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(31) == WBFL::Geometry::Point2d(-3.53553, -3.53553));
         Assert::IsTrue(model.GetPoint(32) == WBFL::Geometry::Point2d(-13.53553, 6.46447));

         Assert::IsTrue(model.ExternalTangents(33, 1, 5.0, 34, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(33) == WBFL::Geometry::Point2d(-3.53553, -3.53553));
         Assert::IsTrue(model.GetPoint(34) == WBFL::Geometry::Point2d(-13.53553, 6.46447));

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 3
         p1 = model.GetPoint(1);
         p2 = model.GetPoint(2);
         p1.Move(0, 0);
         p2.Move(-10, -10);
         model.ReplacePoint(1, p1);
         model.ReplacePoint(2, p2);

         Assert::IsTrue(model.ExternalTangents(35, 1, 5.0, 36, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(35) == WBFL::Geometry::Point2d(3.53553, -3.53553));
         Assert::IsTrue(model.GetPoint(36) == WBFL::Geometry::Point2d(-6.46447, -13.53553));

         Assert::IsTrue(model.ExternalTangents(37, 1, 5.0, 38, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(37) == WBFL::Geometry::Point2d(3.53553, -3.53553));
         Assert::IsTrue(model.GetPoint(38) == WBFL::Geometry::Point2d(-6.46447, -13.53553));

         // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 4
         p1 = model.GetPoint(1);
         p2 = model.GetPoint(2);
         p1.Move(0, 0);
         p2.Move(10, -10);
         model.ReplacePoint(1, p1);
         model.ReplacePoint(2, p2);

         Assert::IsTrue(model.ExternalTangents(39, 1, 5.0, 40, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(39) == WBFL::Geometry::Point2d(3.53553, 3.53553));
         Assert::IsTrue(model.GetPoint(40) == WBFL::Geometry::Point2d(13.53553, -6.46447));

         Assert::IsTrue(model.ExternalTangents(41, 1, 5.0, 42, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(41) == WBFL::Geometry::Point2d(3.53553, 3.53553));
         Assert::IsTrue(model.GetPoint(42) == WBFL::Geometry::Point2d(13.53553, -6.46447));

         // Test CrossingTangent
         model.Clear();

         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 40, 10);

         Assert::IsTrue(model.CrossingTangents(3, 1, -20.0, 4, 2, 5.0, TangentSign::CW) == false);
         Assert::IsTrue(model.CrossingTangents(3, 1, 20.0, 4, 2, -5.0, TangentSign::CW) == false);
         Assert::ExpectException<XCoordGeom>([&model]() {model.CrossingTangents(3, 10, 20.0, 4, 2, 5.0, TangentSign::CW); });
         Assert::ExpectException<XCoordGeom>([&model]() {model.CrossingTangents(3, 1, 20.0, 4, 20, 5.0, TangentSign::CW); });
         Assert::IsTrue(model.CrossingTangents(1, 1, 20.0, 4, 2, 5.0, TangentSign::CW) == false);
         Assert::IsTrue(model.CrossingTangents(3, 1, 20.0, 2, 2, 5.0, TangentSign::CW) == false);
         Assert::IsTrue(model.CrossingTangents(3, 1, 20.0, 4, 1, 5.0, TangentSign::CW) == false);

         // define the big circle first
         Assert::IsTrue(model.CrossingTangents(3, 1, 20.0, 4, 2, 5.0, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(3) == WBFL::Geometry::Point2d(26.66666, -1.05541));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(44.16667, 12.76385));

         Assert::IsTrue(model.CrossingTangents(5, 1, 20.0, 6, 2, 5.0, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(26.66666, 21.055415));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(44.16667, 7.23615));

         // Test Point
         Float64 radius = 20;

         model.Clear();
         model.StorePoint(1, 10, 10);
         model.StorePoint(2, 10 + radius * sqrt(2.), 10);
         model.StorePoint(3, 10 + radius, 10 + radius);
         model.StorePoint(999, 5, 5);

         Assert::IsTrue(model.TangentPoint(4, 1, -20.0, 2, TangentSign::CW) == false);
         Assert::ExpectException<XCoordGeom>([&model]() {model.TangentPoint(4, 10, 20.0, 2, TangentSign::CW); });
         Assert::ExpectException<XCoordGeom>([&model]() {model.TangentPoint(4, 1, 20.0, 4, TangentSign::CW); });
         Assert::IsTrue(model.TangentPoint(1, 1, 20.0, 2, TangentSign::CW) == false);
         Assert::IsTrue(model.TangentPoint(4, 1, 20.0, 1, TangentSign::CW) == false);
         Assert::IsTrue(model.TangentPoint(4, 1, 20.0, 999, TangentSign::CW) == false);

         Assert::IsTrue(model.TangentPoint(4, 1, radius, 2, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(4) == WBFL::Geometry::Point2d(24.14214, -4.14214));

         Assert::IsTrue(model.TangentPoint(5, 1, radius, 2, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(5) == WBFL::Geometry::Point2d(24.14214, 24.14214));

         Assert::IsTrue(model.TangentPoint(6, 1, radius, 3, TangentSign::CW));
         Assert::IsTrue(model.GetPoint(6) == WBFL::Geometry::Point2d(30, 10));

         Assert::IsTrue(model.TangentPoint(7, 1, radius, 3, TangentSign::CCW));
         Assert::IsTrue(model.GetPoint(7) == WBFL::Geometry::Point2d(10, 30));
      }

	};
}
