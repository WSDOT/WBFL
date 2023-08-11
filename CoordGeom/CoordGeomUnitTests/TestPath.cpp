#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestPath)
	{
	public:
		
      void CommonPathTest(std::shared_ptr<Path> path, Float64 xSign, Float64 ySign)
      {
         //////////////
         // Bearing, Normal, LocatePoint, Distance From Start, and Offset
         Float64 path_offset = (ySign / xSign) * 10;
         Float64 dir;
         WBFL::Geometry::Point2d pnt;
         Float64 distance_from_start;
         Float64 offset;
         WBFL::Geometry::Point2d newPnt;
         bool bOnProjection;

         auto PathDirection = [&xSign, &ySign](Float64 dir) {return atan2(ySign * tan(dir), xSign); };

         //
         distance_from_start = -100.0;
         dir = PathDirection(0.0);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * -100, ySign * -10));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(distance_from_start == -100.0);

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * -100, ySign * 0));
         Assert::IsTrue(distance_from_start == -100.00);
         Assert::IsTrue(bOnProjection == true);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(distance_from_start == -100.0);


         //
         distance_from_start = 0;
         dir = PathDirection(0.0);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 0.0, ySign * -10.0));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(distance_from_start == 0.0);

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 0, ySign * 0));
         Assert::IsTrue(IsEqual(distance_from_start, 0.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 0.0));

         //
         distance_from_start = 25;
         dir = PathDirection(0.0);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 25.0, ySign * -10.0));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 25.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 25, ySign * 0));
         Assert::IsTrue(IsEqual(distance_from_start, 25.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 25.0));

         //
         distance_from_start = 100;
         dir = PathDirection(M_PI / 4);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 107.0710678, ySign * -7.0710678));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 100.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 100, ySign * 0));
         Assert::IsTrue(IsEqual(distance_from_start, 100.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 100.0));

         //
         distance_from_start = 150;
         dir = PathDirection(M_PI / 4);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 142.42641, ySign * 28.28427));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 150.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 135.35533905932738, ySign * 35.355339059327392));
         Assert::IsTrue(IsEqual(distance_from_start, 150.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 150.0));

         //
         distance_from_start = 200;
         dir = PathDirection(5.8195376981787801);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 171.72503, ySign * 27.95714));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 200.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 176.19716589662397, ySign * 36.901417051688000));
         Assert::IsTrue(IsEqual(distance_from_start, 200.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 200.0));

         //
         distance_from_start = 390;
         dir = PathDirection(0.0084083531428916);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 357.56997655414648, ySign * -9.9881528501514651));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 390.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 357.48589488932885, ySign * 0.011493657282799078));
         Assert::IsTrue(IsEqual(distance_from_start, 390.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 390.0));

         //
         distance_from_start = 430;
         dir = PathDirection(0.39101);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 400.30796498659186, ySign * -1.6561192213706857));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 430.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 396.49675804330548, ySign * 7.5891337029933084));
         Assert::IsTrue(IsEqual(distance_from_start, 430.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 430.0));

         //
         distance_from_start = 465;
         dir = PathDirection(0.73327699338782193);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 432.59047672020114, ySign * 18.822245727601619));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 465.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 425.89739504565671, ySign * 26.252094830906742));
         Assert::IsTrue(IsEqual(distance_from_start, 465.0));
         Assert::IsTrue(bOnProjection == false);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 465.0));

         //
         distance_from_start = 500;
         dir = PathDirection(M_PI / 4);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 457.89177856524304, ySign * 43.749642941512093));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 500.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 450.82071075337751, ySign * 50.820710753377611));
         Assert::IsTrue(IsEqual(distance_from_start, 500.0));
         Assert::IsTrue(bOnProjection == true);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 500.0));

         //
         distance_from_start = 600;
         dir = PathDirection(M_PI / 4);
         Assert::IsTrue(path->GetBearing(distance_from_start) == Direction(dir));
         Assert::IsTrue(path->GetNormal(distance_from_start) == Direction(dir + 3 * PI_OVER_2));
         pnt = path->LocatePoint(distance_from_start, OffsetType::AlongDirection, path_offset, path->GetNormal(distance_from_start));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 528.60245668389769, ySign * 114.46032106016685));

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, path_offset));
         Assert::IsTrue(IsEqual(distance_from_start, 600.0));

         std::tie(newPnt, distance_from_start, bOnProjection) = path->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 521.53138887203227, ySign * 121.531388872032281));
         Assert::IsTrue(IsEqual(distance_from_start, 600.0));
         Assert::IsTrue(bOnProjection == true);

         std::tie(distance_from_start, offset) = path->DistanceAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(IsEqual(distance_from_start, 600.0));
      }

      void ComparePaths(std::shared_ptr<const WBFL::COGO::Path> path1, std::shared_ptr<const WBFL::COGO::Path> path2, Float64 pathOffset, Float64 start, Float64 end, long nPoints)
      {
         for (long i = 0; i < nPoints; i++)
         {
            Float64 dist_from_start = start + (end - start) * i / (nPoints - 1);
            auto pnt1 = path1->LocatePoint(dist_from_start, OffsetType::AlongDirection, 0.0, Direction(0));
            auto pnt2 = path2->LocatePoint(dist_from_start - pathOffset, OffsetType::AlongDirection, 0.0, Direction(0));

            // I think the error may accumulate over the length of the sub-spline
            // because spirals are represented with cubic splines when the full spiral isn't modeled
            // Use a reduced tolerance
            Assert::IsTrue(IsEqual(pnt1.X(), pnt2.X(), 0.2) && IsEqual(pnt1.Y(), pnt2.Y(), 0.2));

            auto dir1 = path1->GetNormal(dist_from_start);
            auto dir2 = path2->GetNormal(dist_from_start - pathOffset);
            Assert::IsTrue(IsEqual(dir1.GetValue(), dir2.GetValue(), 0.2));
         }
      }

      TEST_METHOD(Path)
      {
         auto path = Path::Create();

         auto segment = PathSegment::Create(10, 20, 20, 30);
         path->AddPathElement(segment);

         auto hc = CompoundCurve::Create();
         hc->SetPBT(WBFL::Geometry::Point2d(100, 100));
         path->AddPathElement(hc);

         Assert::IsTrue(path->GetPathElementCount() == 2);

         auto pe = path->GetPathElement(0);
         Assert::IsNotNull(std::dynamic_pointer_cast<const PathSegment>(pe).get());
         Assert::IsTrue(segment == pe);
         Assert::IsTrue(std::dynamic_pointer_cast<const PathSegment>(pe)->GetStartPoint() == WBFL::Geometry::Point2d(10, 20));
         Assert::IsTrue(std::dynamic_pointer_cast<const PathSegment>(pe)->GetEndPoint() == WBFL::Geometry::Point2d(20, 30));

         pe = path->GetPathElement(1);
         Assert::IsNotNull(std::dynamic_pointer_cast<const CompoundCurve>(pe).get());
         Assert::IsTrue(hc == pe);
         Assert::IsTrue(std::dynamic_pointer_cast<const CompoundCurve>(pe)->GetPBT() == WBFL::Geometry::Point2d(100, 100));

         path->Clear();
         Assert::IsTrue(path->GetPathElementCount() == 0);
      }


      TEST_METHOD(Path1)
      {
         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         path->AddPathElement(PathSegment::Create(150, 50, 250, 0));

         WBFL::Geometry::Point2d pbt(300, 0);
         WBFL::Geometry::Point2d pi(400, 0);
         WBFL::Geometry::Point2d pft(500, 100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         path->AddPathElement(hc);

         CommonPathTest(path, 1.0, 1.0);
      }

      TEST_METHOD(Path1a)
      {
         // this test is the same as Test1 except we use a transition curve, circular curve, transition curve instead of a compound curve
         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         path->AddPathElement(PathSegment::Create(150, 50, 250, 0));

         WBFL::Geometry::Point2d start_entry_spiral(353.385105248, 0);
         Direction start_entry_spiral_direction(0.0);

         WBFL::Geometry::Point2d end_entry_spiral(363.3826055, 0.1666369);
         Direction end_entry_spiral_direction(0.05);

         WBFL::Geometry::Point2d start_exit_spiral(421.682819278, 22.624955);
         Direction start_exit_spiral_direction(0.685398116);

         WBFL::Geometry::Point2d end_exit_spiral(436.2818872224, 36.2818872224);
         Direction end_exit_spiral_direction(M_PI / 4);

         WBFL::Geometry::Point2d pi(396.225283748, 1.8101406324);

         auto entry_spiral = TransitionCurve::Create(start_entry_spiral, start_entry_spiral_direction, 0.0, 100.0, 10.0, TransitionCurveType::Clothoid);
         auto curve = CircularCurve::Create(end_entry_spiral, pi, start_exit_spiral, 100.0);
         auto exit_spiral = TransitionCurve::Create(start_exit_spiral, start_exit_spiral_direction, 100.0, 0.0, 20.0, TransitionCurveType::Clothoid);

         path->AddPathElement(entry_spiral);
         path->AddPathElement(curve);
         path->AddPathElement(exit_spiral);

         CommonPathTest(path, 1.0, 1.0);
      }

      TEST_METHOD(Path2)
      {
         // Mirror Test1 about X axis

         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         path->AddPathElement(PathSegment::Create(150, -50, 250, 0));

         WBFL::Geometry::Point2d pbt(300, 0);
         WBFL::Geometry::Point2d pi(400, 0);
         WBFL::Geometry::Point2d pft(500, -100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         path->AddPathElement(hc);

         CommonPathTest(path, 1.0, -1.0);
      }

      TEST_METHOD(Path2a)
      {
         // Mirror Test1a about X axis

         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         path->AddPathElement(PathSegment::Create(150, -50, 250, 0));

         WBFL::Geometry::Point2d start_entry_spiral(353.385105248, 0);
         Direction start_entry_spiral_direction(0.0);

         WBFL::Geometry::Point2d end_entry_spiral(363.3826055, -0.1666369);
         Direction end_entry_spiral_direction(TWO_PI - 0.05);

         WBFL::Geometry::Point2d start_exit_spiral(421.682819278, -22.624955);
         Direction start_exit_spiral_direction(TWO_PI - 0.685398116);

         WBFL::Geometry::Point2d end_exit_spiral(436.2818872224, -36.2818872224);
         Direction end_exit_spiral_direction(TWO_PI - M_PI / 4);

         WBFL::Geometry::Point2d pi(396.225283748, -1.8101406324);

         auto entry_spiral = TransitionCurve::Create(start_entry_spiral, start_entry_spiral_direction, 0.0, -100.0, 10.0, TransitionCurveType::Clothoid);
         auto curve = CircularCurve::Create(end_entry_spiral, pi, start_exit_spiral, 100.0);
         auto exit_spiral = TransitionCurve::Create(start_exit_spiral, start_exit_spiral_direction, -100.0, 0.0, 20.0, TransitionCurveType::Clothoid);

         path->AddPathElement(entry_spiral);
         path->AddPathElement(curve);
         path->AddPathElement(exit_spiral);

         CommonPathTest(path, 1.0, -1.0);
      }

      TEST_METHOD(Path3)
      {
         // Mirror Test1 about Y axis
         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         path->AddPathElement(PathSegment::Create(-150, 50, -250, 0));

         WBFL::Geometry::Point2d pbt(-300, 0);
         WBFL::Geometry::Point2d pi(-400, 0);
         WBFL::Geometry::Point2d pft(-500, 100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         path->AddPathElement(hc);

         CommonPathTest(path, -1.0, 1.0);
      }

      TEST_METHOD(Path3a)
      {
         // Mirror Test1a about Y axis
         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         path->AddPathElement(PathSegment::Create(-150, 50, -250, 0));

         WBFL::Geometry::Point2d start_entry_spiral(-353.385105248, 0);
         Direction start_entry_spiral_direction(M_PI);

         WBFL::Geometry::Point2d end_entry_spiral(-363.3826055, 0.1666369);
         Direction end_entry_spiral_direction(M_PI - 0.05);

         WBFL::Geometry::Point2d start_exit_spiral(-421.682819278, 22.624955);
         Direction start_exit_spiral_direction(M_PI - 0.685398116);

         WBFL::Geometry::Point2d end_exit_spiral(-436.2818872224, 36.2818872224);
         Direction end_exit_spiral_direction(3 * M_PI / 4);

         WBFL::Geometry::Point2d pi(-396.225283748, 1.8101406324);

         auto entry_spiral = TransitionCurve::Create(start_entry_spiral, start_entry_spiral_direction, 0.0, -100.0, 10.0, TransitionCurveType::Clothoid);
         auto curve = CircularCurve::Create(end_entry_spiral, pi, start_exit_spiral, 100.0);
         auto exit_spiral = TransitionCurve::Create(start_exit_spiral, start_exit_spiral_direction, -100.0, 0.0, 20.0, TransitionCurveType::Clothoid);

         path->AddPathElement(entry_spiral);
         path->AddPathElement(curve);
         path->AddPathElement(exit_spiral);

         CommonPathTest(path, -1.0, 1.0);
      }

      TEST_METHOD(Path4)
      {
         // Mirror Test1 about both X and Y axis

         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         path->AddPathElement(PathSegment::Create(-150, -50, -250, 0));

         WBFL::Geometry::Point2d pbt(-300, 0);
         WBFL::Geometry::Point2d pi(-400, 0);
         WBFL::Geometry::Point2d pft(-500, -100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         path->AddPathElement(hc);

         CommonPathTest(path, -1.0, -1.0);
      }

      TEST_METHOD(Path4a)
      {
         // Mirror Test1a about both X and Y axis

         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         path->AddPathElement(PathSegment::Create(-150, -50, -250, 0));

         WBFL::Geometry::Point2d start_entry_spiral(-353.385105248, 0);
         Direction start_entry_spiral_direction(M_PI);

         WBFL::Geometry::Point2d end_entry_spiral(-363.3826055, -0.1666369);
         Direction end_entry_spiral_direction(M_PI + 0.05);

         WBFL::Geometry::Point2d start_exit_spiral(-421.682819278, -22.624955);
         Direction start_exit_spiral_direction(M_PI + 0.685398116);

         WBFL::Geometry::Point2d end_exit_spiral(-436.2818872224, -36.2818872224);
         Direction end_exit_spiral_direction(5 * M_PI / 4);

         WBFL::Geometry::Point2d pi(-396.225283748, -1.8101406324);

         auto entry_spiral = TransitionCurve::Create(start_entry_spiral, start_entry_spiral_direction, 0.0, 100.0, 10.0, TransitionCurveType::Clothoid);
         auto curve = CircularCurve::Create(end_entry_spiral, pi, start_exit_spiral, 100.0);
         auto exit_spiral = TransitionCurve::Create(start_exit_spiral, start_exit_spiral_direction, 100.0, 0.0, 20.0, TransitionCurveType::Clothoid);

         path->AddPathElement(entry_spiral);
         path->AddPathElement(curve);
         path->AddPathElement(exit_spiral);

         CommonPathTest(path, -1.0, -1.0);
      }


      TEST_METHOD(Test1)
      {
         // Test an empty path
         auto path = Path::Create();

         Float64 path_offset = 10;

         Float64 dist_from_start = 0.0;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(0.0));
         auto pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, 3*PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(0, -10));
         Float64 dist, offset;
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);

         dist_from_start = 200.0;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(0.0));
         pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, 3*PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(200, -10));
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);
      }

      TEST_METHOD(Test3)
      {
         // path consisting of a single line segment
         auto path = Path::Create();

         path->AddPathElement(PathSegment::Create(50, 50, 250, 250));

         Float64 path_offset = 10;

         Float64 dist_from_start = -100.0;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(M_PI / 4));
         auto pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, M_PI/4 - PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(-13.639610306789281, -27.781745930520231));
         Float64 dist;
         Float64 offset;
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);

         dist_from_start = 50.0;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(M_PI / 4));
         pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, M_PI/4 - PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(92.426406871192853, 78.284271247461902));
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);

         dist_from_start = 400;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(M_PI / 4));
         pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, M_PI/4 - PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(339.91378028648450, 325.77164466275354));
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);
      }

      TEST_METHOD(Test4)
      {
         // path consisting of a single curve
         auto path = Path::Create();

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 700);
         path->AddPathElement(CompoundCurve::Create(pbt, pi, pft, 500, 100, TransitionCurveType::Clothoid, 200, TransitionCurveType::Clothoid));

         Float64 path_offset = 10;

         Float64 dist_from_start = -100;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(0.00));
         auto pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, -PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(339.035600, 990.00));
         Float64 dist;
         Float64 offset;
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);

         dist_from_start = 50;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(6.2581853));
         pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, 6.2581853 - PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(488.78250119134225, 989.58647677139686));
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);

         dist_from_start = 150;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(6.083185));
         pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, 6.083185 - PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(586.36691011184678, 979.39958736479957));
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);

         dist_from_start = 350;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(5.68345));
         pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, 5.68345 - PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(765.69629901726250, 903.58045792794292));
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);

         dist_from_start = 550.0;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(5.497787));
         pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, 5.497787 - PI_OVER_2);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(913.63394982918112, 772.22391454708782));
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);
      }

      TEST_METHOD(Test5)
      {
         // path consisting of two line segments

         auto path = Path::Create();
         path->AddPathElement(PathSegment::Create(0, 0, 10, 0));
         path->AddPathElement(PathSegment::Create(10, 10, 20, 10));

         Float64 path_offset = 3;

         Float64 dist_from_start = 15;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(PI_OVER_2));
         auto pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, path_offset, 0.0);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(13, 5));
         Float64 dist, offset;
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(path_offset, offset, 0.0001);
         Assert::AreEqual(dist_from_start, dist, 0.0001);
      }


      TEST_METHOD(SubPath1)
      {
         // Test sub-path with empty alignment
         auto path = Path::Create();

         // sub-path that captures entire alignment
         auto subpath = path->CreateSubpath(-110.0, 200.0);
         Assert::IsTrue(subpath.size() == 3);
         auto element = subpath[0];
         auto segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(-110, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(0, 0));
         element = subpath[1];
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(0, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(100, 0));
         element = subpath[2];
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(100, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(200, 0));

         // sub-path that captures start
         subpath = path->CreateSubpath(-110, 5);
         Assert::IsTrue(subpath.size() == 2);
         element = subpath[0];
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(-110, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(0, 0));
         element = subpath[1];
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(0, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(5, 0));

         // sub-path that captures the middle
         subpath = path->CreateSubpath(10, 50);
         Assert::IsTrue(subpath.size() == 1);
         element = subpath[0];
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(10, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(50, 0));
      }

      TEST_METHOD(SubPath2)
      {
         // Test sub path with 2-point path
         auto path = Path::Create();
         path->AddPathElement(PathSegment::Create(10, 10, 110, 110));

         // sub-path that captures entire path
         auto sub_path = Path::Create(path->CreateSubpath(-10.0, 300.0));

         Assert::IsTrue(sub_path->GetPathElementCount() == 3);
         auto element = sub_path->GetPathElement(0);
         auto segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(2.9289321881345245, 2.9289321881345245));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(10, 10));
         element = sub_path->GetPathElement(1);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(10, 10));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(110, 110));
         element = sub_path->GetPathElement(2);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(110, 110));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(222.13203435596427, 222.13203435596427));

         // sub-path that captures start
         sub_path = Path::Create(path->CreateSubpath(-10, 5));
         Assert::IsTrue(sub_path->GetPathElementCount() == 2);
         element = sub_path->GetPathElement(0);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(2.9289321881345245, 2.9289321881345245));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(10, 10));
         element = sub_path->GetPathElement(1);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(10, 10));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(13.535533905932738, 13.535533905932738));

         // sub-path that captures end
         sub_path = Path::Create(path->CreateSubpath(100, 300));
         Assert::IsTrue(sub_path->GetPathElementCount() == 2);
         element = sub_path->GetPathElement(0);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(80.710678118654755, 80.710678118654755));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(110, 110));
         element = sub_path->GetPathElement(1);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(110, 110));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(222.13203435596427, 222.13203435596427));

         // sub-Alignment that captures the middle
         sub_path = Path::Create(path->CreateSubpath(30, 130));
         Assert::IsTrue(sub_path->GetPathElementCount() == 1);
         element = sub_path->GetPathElement(0);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(31.213203435596427, 31.213203435596427));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(101.92388155425118, 101.92388155425118));

         ComparePaths(path, sub_path, 30, 10, 110, 10);
      }

      TEST_METHOD(SubPath3)
      {
         // Path consisting of a single horizontal curve
         auto path = Path::Create();
         WBFL::Geometry::Point2d pbt(0, 0);
         WBFL::Geometry::Point2d pi(1000, 0);
         WBFL::Geometry::Point2d pft(5000, 5000);
         path->AddPathElement(CompoundCurve::Create(pbt, pi, pft, 500, 20, TransitionCurveType::Clothoid, 30, TransitionCurveType::Clothoid));

         // sub path that captures entire element
         // start on back tangent, end in circular curve
         auto sub_path = Path::Create(path->CreateSubpath(-10, 300));
         ComparePaths(path, sub_path, -10, -10, 300, 10);

         Assert::IsTrue(sub_path->GetPathElementCount() == 2);

         auto element = sub_path->GetPathElement(1);
         auto hc = std::dynamic_pointer_cast<const CompoundCurve>(element);
         Assert::IsNotNull(hc.get());
         Assert::IsTrue(IsEqual(hc->GetRadius(), 500.));
         Assert::IsTrue(IsEqual(hc->GetSpiralLength(CompoundCurve::SpiralLocation::Entry), 20.0));
         Assert::IsTrue(IsEqual(hc->GetSpiralLength(CompoundCurve::SpiralLocation::Exit), 0.0)); // sub alignment stops before the exit spiral so this length is now 0.0

         // start on back tangent and end in entry spiral
         sub_path = Path::Create(path->CreateSubpath(-10, 110));
         ComparePaths(path, sub_path, -10, -10, 110, 10);

         // start on back tangent and end in exit spiral
         sub_path = Path::Create(path->CreateSubpath(-10, 550));
         ComparePaths(path, sub_path, -10, -10, 550, 30);

         // start on back tangent and end on forward tangent
         sub_path = Path::Create(path->CreateSubpath(-10, 800));
         ComparePaths(path, sub_path, -10, -10, 80, 40);

         // start in entry spiral, end in entry spiral
         sub_path = Path::Create(path->CreateSubpath(110, 118));
         ComparePaths(path, sub_path, 110, 110, 118, 10);

         // start in entry spiral, end in circular curve
         sub_path = Path::Create(path->CreateSubpath(110, 300));
         ComparePaths(path, sub_path, 110, 110, 300, 10);

         // start in entry spiral, end in exit spiral
         sub_path = Path::Create(path->CreateSubpath(110, 560));
         ComparePaths(path, sub_path, 110, 110, 560, 30);

         // start in entry spiral, end on fwd tangent
         sub_path = Path::Create(path->CreateSubpath(110, 800));
         ComparePaths(path, sub_path, 110, 110, 800, 30);

         // start and end in circular curve
         sub_path = Path::Create(path->CreateSubpath(200, 500));
         ComparePaths(path, sub_path, 200, 200, 500, 10);

         // start in circular curve, end in exit spiral
         sub_path = Path::Create(path->CreateSubpath(300, 550));
         ComparePaths(path, sub_path, 300, 300, 550, 10);

         // start in circular curve, end in fwd tangent
         sub_path = Path::Create(path->CreateSubpath(300, 1000));
         ComparePaths(path, sub_path, 300, 300, 1000, 10);

         // start in exit spiral, end in exit spiral
         sub_path = Path::Create(path->CreateSubpath(545, 570));
         ComparePaths(path, sub_path, 545, 545, 570, 10);

         // start in exit spiral, end in fwd tangent
         sub_path = Path::Create(path->CreateSubpath(545, 1000));
         ComparePaths(path, sub_path, 545, 545, 1000, 10);

         // start and end on back tangent
         sub_path= Path::Create(path->CreateSubpath(-10, 50));
         ComparePaths(path, sub_path, -10, -10, 50, 10);

         // start and end on fwd tangent
         sub_path = Path::Create(path->CreateSubpath(600, 800));
         ComparePaths(path, sub_path, 600, 600, 800, 10);
      }

      TEST_METHOD(SubPath4)
      {
         auto path = Path::Create();

         auto spline = CubicSpline::Create();

         spline->AddPoint(5, 5);
         spline->AddPoint(8, 7);
         spline->AddPoint(13, 9);
         spline->AddPoint(16, 10);
         spline->AddPoint(17, 15);
         spline->AddPoint(22, 16);

         spline->SetStartDirection(M_PI / 4);
         spline->SetEndDirection(M_PI / 6);

         path->AddPathElement(spline);

         auto Ls = spline->GetLength();

         // full length of spline
         auto sub_path= Path::Create(path->CreateSubpath(0.0, Ls));
         ComparePaths(path, sub_path, 0.0, 0.0, Ls, 10);


         // before spline
         sub_path = Path::Create(path->CreateSubpath(-50, -1));
         ComparePaths(path, sub_path, -50, -50, -1, 10);


         // after spline
         sub_path = Path::Create(path->CreateSubpath(Ls+50, Ls+100));
         ComparePaths(path, sub_path, Ls+50, Ls+50, Ls+100, 10);

         // mid-spline
         sub_path = Path::Create(path->CreateSubpath(Ls/4,Ls/2));
         ComparePaths(path, sub_path, Ls/4, Ls/4, Ls/2, 10);

         // start before spline, end mid-spline
         sub_path = Path::Create(path->CreateSubpath(-20, 3*Ls/4 - 20));
         ComparePaths(path, sub_path, -20, -20, 3*Ls/4 - 20, 10);

         // start mid-spline, end after spline
         sub_path = Path::Create(path->CreateSubpath(Ls/4, Ls/4 + Ls + 10));
         ComparePaths(path, sub_path, Ls/4, Ls/4, Ls / 4 + Ls + 10, 10);
      }

      TEST_METHOD(SubPath5)
      {
         // path consisting of a two line segments
         auto path = Path::Create();

         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);
         WBFL::Geometry::Point2d p3(10, 10);
         WBFL::Geometry::Point2d p4(20, 10);

         auto segment1 = PathSegment::Create(p1, p2);
         auto segment2 = PathSegment::Create(p3, p4);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);

         //////////////
         // Bearing,Normal,LocatePoint, Station, and Offset

         Float64 dist_from_start = 15;
         Assert::IsTrue(path->GetBearing(dist_from_start) == Direction(PI_OVER_2));
         auto pnt = path->LocatePoint(dist_from_start, OffsetType::AlongDirection, 3, TWO_PI);
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(13.0, 5.0));

         Float64 dist;
         Float64 offset;
         std::tie(dist, offset) = path->DistanceAndOffset(pnt);
         Assert::AreEqual(3.0,offset);
         Assert::AreEqual(dist_from_start, dist);
      }

      TEST_METHOD(OffsetPath1)
      {
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);
         WBFL::Geometry::Point2d p3(20, 10);

         auto segment1 = PathSegment::Create(p1, p2);
         auto segment2 = PathSegment::Create(p2, p3);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);

         // Compute offset paths right and left of this path
         //                       / (20,10)
         //                      /
         //                     /
         //                    /
         //                   /
         //  +---------------+
         // (0,0)          (10,0)

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10);
         Assert::AreEqual((size_t)2, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, -10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(14.142135623730951, -10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(14.142135623730951, -10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(27.071067811865476, 2.9289321881345245) == offset_path_elements[1]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10);
         Assert::AreEqual((size_t)2, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, 10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690499, 10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690499, 10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(12.928932188134524, 17.071067811865476) == offset_path_elements[1]->GetEndPoint());


         // Compute offset paths right and left of this path
         //                        +---------------+ (30,10)
         //                       / (20,10)
         //                      /
         //                     /
         //                    /
         //                   /
         //  +---------------+
         // (0,0)          (10,0)

         WBFL::Geometry::Point2d p4(30, 10);
         auto segment3 = PathSegment::Create(p3, p4);
         path->AddPathElement(segment3);

         // offset to the right
         offset_path_elements = path->CreateOffsetPath(10);
         Assert::AreEqual((size_t)3, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, -10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(14.142135623730951, -10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(14.142135623730951, -10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(24.142135623730951, 0.0) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(24.142135623730951, 0.0) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(30.0, 0.0) == offset_path_elements[2]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10);
         Assert::AreEqual((size_t)3, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, 10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690499, 10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690499, 10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(15.857864376269049, 20.0) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(15.857864376269049, 20.0) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(30.0, 20.0) == offset_path_elements[2]->GetEndPoint());
      };


      TEST_METHOD(OffsetPath2)
      {
         // same as OffsetPath1, but rotated 90 degrees
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(0, 10);
         WBFL::Geometry::Point2d p3(-10, 20);

         auto segment1 = PathSegment::Create(p1, p2);
         auto segment2 = PathSegment::Create(p2, p3);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);

         // Compute offset paths right and left of this path
         // (-10,20)
         // \
         //  \
         //   \
         //    \
         //     \
         //      + (0,10)
         //      |
         //      |
         //      |
         //      |
         //      |
         //      + (0,0)

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10);
         Assert::AreEqual((size_t)2, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(10, 0) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(10.0, 14.142135623730951) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(10.0, 14.142135623730951) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-2.9289321881345245, 27.071067811865476) == offset_path_elements[1]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10);
         Assert::AreEqual((size_t)2, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(-10, 0) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-10, 5.8578643762690499) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-10, 5.8578643762690499) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-17.071067811865476, 12.928932188134524) == offset_path_elements[1]->GetEndPoint());


         // Compute offset paths right and left of this path
         // + (-10,30)
         // |
         // |
         // |
         // |
         // |
         // + (-10,20)
         //  \
         //   \
         //    \
         //     \
         //      \
         //       + (0,10)
         //       |
         //       |
         //       |
         //       |
         //       |
         //       + (0,0)

         WBFL::Geometry::Point2d p4(-10, 30);
         auto segment3 = PathSegment::Create(p3, p4);
         path->AddPathElement(segment3);

         // offset to the right
         offset_path_elements = path->CreateOffsetPath(10);
         Assert::AreEqual((size_t)3, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(10, 0) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(10.0, 14.142135623730951) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(10.0, 14.142135623730951) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(0.0, 24.142135623730951) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(0.0, 24.142135623730951) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(0.0, 30.0) == offset_path_elements[2]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10);
         Assert::AreEqual((size_t)3, offset_path_elements.size());

         Assert::IsTrue(WBFL::Geometry::Point2d(-10, 0) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-10.0, 5.8578643762690499) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-10.0, 5.8578643762690499) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-20.0, 15.857864376269049) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-20.0, 15.857864376269049) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-20, 30.0) == offset_path_elements[2]->GetEndPoint());
      };

      TEST_METHOD(OffsetPath3)
      {
         // Discontinuous path: segment-gap-curve-gap-segment
         // Same as OffsetPath4, except Segment1 and Segment3 are shortened and don't connect to the curve Segment 2
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);
         WBFL::Geometry::Point2d p3(20, 10);
         WBFL::Geometry::Point2d p4(30, 20);

         auto segment2 = CircularCurve::Create(p1, p2, p3, 1.0); // 45 degree curve
         auto segment1 = PathSegment::Create(p1, segment2->GetPC().Offset(-1.0, 0)); // make segment 1 end a little before the PC
         auto segment3 = PathSegment::Create(segment2->GetPT().Offset(1, 1), p4); // make segment 3 start a little after the PT

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);
         path->AddPathElement(segment3);

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10.0);
         Assert::AreEqual((size_t)3, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, -10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(9.5857864376269042, -10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(9.5857864376269042, -10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(17.363961030678929, -6.7781745930520243) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(17.363961030678929, -6.7781745930520243) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(37.071067811865476, 12.928932188134524) == offset_path_elements[2]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10.0);
         Assert::AreEqual((size_t)2, offset_path_elements.size()); // the circular curve degrades to nothing
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[1]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, 10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690472, 10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690472, 10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(22.928932188134524, 27.071067811865476) == offset_path_elements[1]->GetEndPoint());
      }

      TEST_METHOD(OffsetPath4)
      {
         // Continuous path: segment-curve-segment
         //               
         //                      + (30,20)
         //                     /
         //                    /
         //                   + (20,10)
         //                  /
         //                 /
         //  +-------------+        Curve at PI with R=1
         // (0,0)          (10,0)
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);
         WBFL::Geometry::Point2d p3(20, 10);
         WBFL::Geometry::Point2d p4(30, 20);

         auto segment2 = CircularCurve::Create(p1, p2, p3, 1.0); // 45 degree curve
         auto segment1 = PathSegment::Create(p1, segment2->GetPC());
         auto segment3 = PathSegment::Create(segment2->GetPT(), p4);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);
         path->AddPathElement(segment3);

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10.0);
         Assert::AreEqual((size_t)3, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, -10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(9.5857864376269042, -10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(9.5857864376269042, -10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(17.363961030678929, -6.7781745930520243) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(17.363961030678929, -6.7781745930520243) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(37.071067811865476, 12.928932188134524) == offset_path_elements[2]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10.0);
         Assert::AreEqual((size_t)2, offset_path_elements.size()); // the circular curve degrades to nothing
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[1]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, 10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690472, 10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690472, 10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(22.928932188134524, 27.071067811865476) == offset_path_elements[1]->GetEndPoint());
      }

      TEST_METHOD(OffsetPath5)
      {
         // Continuous path: segment-curve-segment
         //               
         // (0,0)          (10,0)
         //  +-------------+        Curve at PI with R=1
         //                 \
         //                  \
         //                   + (20,-10)
         //                    \
         //                     \
         //                      + (30,-20)
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);
         WBFL::Geometry::Point2d p3(20, -10);
         WBFL::Geometry::Point2d p4(30, -20);

         auto segment2 = CircularCurve::Create(p1, p2, p3, 1.0); // 45 degree curve
         auto segment1 = PathSegment::Create(p1, segment2->GetPC());
         auto segment3 = PathSegment::Create(segment2->GetPT(), p4);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);
         path->AddPathElement(segment3);

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10.0);
         Assert::AreEqual((size_t)2, offset_path_elements.size()); // the circular curve degrades to nothing
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[1]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, -10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690472, -10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(5.8578643762690472, -10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(22.928932188134524, -27.071067811865476) == offset_path_elements[1]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10.0);
         Assert::AreEqual((size_t)3, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, 10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(9.5857864376269042, 10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(9.5857864376269042, 10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(17.363961030678929, 6.7781745930520243) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(17.363961030678929, 6.7781745930520243) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(37.071067811865476, -12.928932188134524) == offset_path_elements[2]->GetEndPoint());
      };

      TEST_METHOD(OffsetPath6)
      {
         // Continuous path: segment-curve-segment
         //               
         // + (-30,20)
         //  \
         //   \
         //    + (-20,10)
         //     \
         //      \
         //       +-------------+        Curve at PI with R=1
         //     (-10,0)         (0,0)
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(-10, 0);
         WBFL::Geometry::Point2d p3(-20, 10);
         WBFL::Geometry::Point2d p4(-30, 20);

         auto segment2 = CircularCurve::Create(p1, p2, p3, 1.0); // 45 degree curve
         auto segment1 = PathSegment::Create(p1, segment2->GetPC());
         auto segment3 = PathSegment::Create(segment2->GetPT(), p4);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);
         path->AddPathElement(segment3);

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10.0);
         Assert::AreEqual((size_t)2, offset_path_elements.size()); // the circular curve degrades to nothing
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[1]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, 10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-5.8578643762690454, 10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-5.8578643762690454, 10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-22.928932188134524, 27.071067811865476) == offset_path_elements[1]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10.0);
         Assert::AreEqual((size_t)3, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, -10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-9.5857864376269042, -10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-9.5857864376269042, -10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-17.363961030678929, -6.7781745930520243) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-17.363961030678929, -6.7781745930520243) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-37.071067811865476, 12.928932188134524) == offset_path_elements[2]->GetEndPoint());
      }

      TEST_METHOD(OffsetPath7)
      {
         // Continuous path: segment-curve-segment
         //               
         //     (-10,0)         (0,0)
         //       +-------------+        Curve at PI with R=1
         //      /
         //     /
         //    + (-20,-10)
         //   /
         //  /
         // + (-30,-20)
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(-10, 0);
         WBFL::Geometry::Point2d p3(-20, -10);
         WBFL::Geometry::Point2d p4(-30, -20);

         auto segment2 = CircularCurve::Create(p1, p2, p3, 1.0); // 45 degree curve
         auto segment1 = PathSegment::Create(p1, segment2->GetPC());
         auto segment3 = PathSegment::Create(segment2->GetPT(), p4);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);
         path->AddPathElement(segment3);

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10.0);
         Assert::AreEqual((size_t)3, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, 10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-9.5857864376269042, 10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-9.5857864376269042, 10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-17.363961030678929, 6.7781745930520243) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-17.363961030678929, 6.7781745930520243) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-37.071067811865476, -12.928932188134524) == offset_path_elements[2]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10.0);
         Assert::AreEqual((size_t)2, offset_path_elements.size()); // the circular curve degrades to nothing
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[1]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(0, -10) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-5.8578643762690454, -10.0) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-5.8578643762690454, -10.0) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-22.928932188134524, -27.071067811865476) == offset_path_elements[1]->GetEndPoint());
      }

      TEST_METHOD(OffsetPath8)
      {
         // Continuous path: segment-curve-segment
         //      (20,30) +
         //             /
         //            /
         //   (10,20) +
         //          /
         //         /
         // (0,10) +   Curve at PI with R=1
         //        |
         //        |
         //        |
         //        |
         // (0,0)  +
         auto path = Path::Create();
         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(0, 10);
         WBFL::Geometry::Point2d p3(10, 20);
         WBFL::Geometry::Point2d p4(20, 30);

         auto segment2 = CircularCurve::Create(p1, p2, p3, 1.0); // 45 degree curve
         auto segment1 = PathSegment::Create(p1, segment2->GetPC());
         auto segment3 = PathSegment::Create(segment2->GetPT(), p4);

         path->AddPathElement(segment1);
         path->AddPathElement(segment2);
         path->AddPathElement(segment3);

         // offset to the right
         auto offset_path_elements = path->CreateOffsetPath(10.0);
         Assert::AreEqual((size_t)2, offset_path_elements.size()); // the circular curve degrades to nothing
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[1]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(10, 0) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(10, 5.8578643762690472) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(10, 5.8578643762690472) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(27.071067811865476, 22.928932188134524) == offset_path_elements[1]->GetEndPoint());

         // offset to the left
         offset_path_elements = path->CreateOffsetPath(-10.0);
         Assert::AreEqual((size_t)3, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(-10, 0) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-10.0, 9.5857864376269042) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-10.0, 9.5857864376269042) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-6.7781745930520243, 17.363961030678929) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(-6.7781745930520243, 17.363961030678929) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(12.928932188134524, 37.071067811865476) == offset_path_elements[2]->GetEndPoint());
      }

      TEST_METHOD(OffsetPath_BigSandyCreek)
      {
         // This test is based on the geometry in the BigSandyCreek.pgs regression test file.
         // This bridge model was causing crashes due to multiple issues in the CoordGeom library.
         // These issues have since been fixed. This test case will help to prevent re-introducing
         // those problems.
         // The geometry of the bridge model is unique because the alignment consists of several
         // circular curves with very small radii. The curve degrade to nothing when creating
         // offset paths for the left and right deck edges. This was causing the crashes.
         WBFL::Geometry::Point2d pbt1(0, 0);
         WBFL::Geometry::Point2d pi1(0.0010404609598609654, -0.0014248733366743086);
         WBFL::Geometry::Point2d pft1(0.17888308511377340, -0.24896283211077880);
         Float64 r1 = 0.30480000000000002;

         WBFL::Geometry::Point2d pbt2(0.0017267496659959226, -0.0023801139954004475);
         WBFL::Geometry::Point2d pi2(51.607413144755434, -71.831989759889638);
         WBFL::Geometry::Point2d pft2(51.609195267232494, -71.834462479743721);
         Float64 r2 = 0.0030480000000000004;

         WBFL::Geometry::Point2d pbt3(51.607414476002809, -71.831991607013990);
         WBFL::Geometry::Point2d pi3(68.537576676837375, -95.322828373634650);
         WBFL::Geometry::Point2d pft3(68.539382238244812, -95.325284030777652);
         Float64 r3 = 0.0030480000000000004;

         auto curve1 = CircularCurve::Create(pbt1, pi1, pft1, r1);
         auto curve2 = CircularCurve::Create(pbt2, pi2, pft2, r2);
         auto curve3 = CircularCurve::Create(pbt3, pi3, pft3, r3);

         auto path = Path::Create();
         path->AddPathElement(curve1);
         path->AddPathElement(curve2);
         path->AddPathElement(curve3);

         // offset to the right (right edge of deck path)
         auto offset_path_elements = path->CreateOffsetPath(4.572);
         Assert::AreEqual((size_t)4, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[3]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(-3.7113426319455711, -2.6700194763040868) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(47.894342434657581, -74.499627273087157) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(47.894342434657581, -74.499627273087157) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(47.898334694878010, -74.505175322595676) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(47.898334694878010, -74.505175322595676) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(64.828488420101067, -97.996000329186884) == offset_path_elements[2]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(64.828488420101067, -97.996000329186884) == offset_path_elements[3]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(64.854099549426437, -98.031182163679546) == offset_path_elements[3]->GetEndPoint());


         // offset to the left (left edge of deck path)
         offset_path_elements = path->CreateOffsetPath(-4.572);
         Assert::AreEqual((size_t)3, offset_path_elements.size());
         Assert::IsNotNull(std::dynamic_pointer_cast<CircularCurve>(offset_path_elements[0]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[1]).get());
         Assert::IsNotNull(std::dynamic_pointer_cast<PathSegment>(offset_path_elements[2]).get());

         Assert::IsTrue(WBFL::Geometry::Point2d(3.6927172617408162, 2.6957417477775265) == offset_path_elements[0]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(3.7147961312775890, 2.6652592483132507) == offset_path_elements[0]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(3.7147961312775890, 2.6652592483132507) == offset_path_elements[1]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(55.318489796944029, -69.161576730828671) == offset_path_elements[2]->GetStartPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(55.318489796944029, -69.161576730828671) == offset_path_elements[1]->GetEndPoint());
         Assert::IsTrue(WBFL::Geometry::Point2d(72.246647982336114, -92.649632898003276) == offset_path_elements[2]->GetEndPoint());
      };
   };
}
