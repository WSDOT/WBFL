#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::COGO;

namespace CoordGeomUnitTest
{
	TEST_CLASS(TestAlignment)
	{
	public:

      void CommonAlignmentTest(std::shared_ptr<Alignment> alignment, Float64 xSign, Float64 ySign)
      {
         //////////////
         // Bearing, Normal, LocatePoint, Station, and Offset
         Float64 alignment_offset = (ySign / xSign) * 10;
         Float64 dir;
         WBFL::Geometry::Point2d pnt;
         Station station;
         Float64 offset;
         WBFL::Geometry::Point2d newPnt;
         bool bOnProjection;

         auto AlignmentDirection = [&xSign, &ySign](Float64 dir) {return atan2(ySign * tan(dir), xSign); };

         // Sta 0+00
         station.SetValue(0.0);
         dir = AlignmentDirection(0.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(0.00, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(0.00));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * -100, ySign * -10));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(0.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * -100, ySign * 0));
         Assert::IsTrue(station == Station(0.00));
         Assert::IsTrue(bOnProjection == true);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(0.0));


         // Sta 1+00
         station.SetValue(100);
         dir = AlignmentDirection(0.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 0.0, ySign * -10.0));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(100.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 0, ySign * 0));
         Assert::IsTrue(station == Station(100.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(100.0));

         // Sta 1+25
         station.SetValue(125);
         dir = AlignmentDirection(0.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 25.0, ySign * -10.0));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(125.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 25, ySign * 0));
         Assert::IsTrue(station == Station(125.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(125.0));

         // Sta 2+00
         station.SetValue(200);
         dir = AlignmentDirection(M_PI / 4);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 107.0710678, ySign * -7.0710678));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(200.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 100, ySign * 0));
         Assert::IsTrue(station == Station(200.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(200.0));

         // Sta 2+50
         station.SetValue(250);
         dir = AlignmentDirection(M_PI / 4);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 142.42641, ySign * 28.28427));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(250.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 135.35533905932738, ySign * 35.355339059327392));
         Assert::IsTrue(station == Station(250.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(250.0));

         // Sta 3+00
         station.SetValue(300);
         dir = AlignmentDirection(5.8195376981787801);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 171.72503, ySign * 27.95714));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(300.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 176.19716589662397, ySign * 36.901417051688000));
         Assert::IsTrue(station == Station(300.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(300.0));

         // Sta 4+90
         station.SetValue(490);
         dir = AlignmentDirection(0.0084083531428916);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 357.56997655414648, ySign * -9.9881528501514651));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(490.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 357.48589488932885, ySign * 0.011493657282799078));
         Assert::IsTrue(station == Station(490.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(490.0));

         // Sta 5+30
         station.SetValue(530);
         dir = AlignmentDirection(0.39101);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 400.30796498659186, ySign * -1.6561192213706857));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(530.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 396.49675804330548, ySign * 7.5891337029933084));
         Assert::IsTrue(station == Station(530.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(530.0));

         // Sta 5+65
         station.SetValue(565);
         dir = AlignmentDirection(0.73327699338782193);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 432.59047672020114, ySign * 18.822245727601619));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(565.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 425.89739504565671, ySign * 26.252094830906742));
         Assert::IsTrue(station == Station(565.00));
         Assert::IsTrue(bOnProjection == false);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(565.0));

         // Sta 6+00
         station.SetValue(600);
         dir = AlignmentDirection(M_PI / 4);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 457.89177856524304, ySign * 43.749642941512093));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(600.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 450.82071075337751, ySign * 50.820710753377611));
         Assert::IsTrue(station == Station(600.00));
         Assert::IsTrue(bOnProjection == true);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(600.0));

         // Sta 7+00
         station.SetValue(700);
         dir = AlignmentDirection(M_PI / 4);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 528.60245668389769, ySign * 114.46032106016685));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(700.0));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 521.53138887203227, ySign * 121.531388872032281));
         Assert::IsTrue(station == Station(700.00));
         Assert::IsTrue(bOnProjection == true);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(700.0));

         // Add a station equation
         alignment->AddStationEquation(650, 800);

         station = alignment->ConvertFromNormalizedStation(700);
         Assert::IsTrue(station.GetStationZoneIndex() == 1);
         Assert::IsTrue(IsEqual(station.GetValue(), 850.0));

         // Sta 8+50 (station range 1)
         station.SetStation(1, 850);
         dir = AlignmentDirection(M_PI / 4);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(dir));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(xSign * 528.60245668389769, ySign * 114.46032106016685));

         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(1, 850.00));

         std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
         Assert::IsTrue(newPnt == WBFL::Geometry::Point2d(xSign * 521.53138887203227, ySign * 121.531388872032281));
         Assert::IsTrue(station == Station(1, 850.00));
         Assert::IsTrue(bOnProjection == true);

         std::tie(station, offset) = alignment->StationAndOffset(newPnt);
         Assert::IsTrue(IsEqual(offset, 0.0));
         Assert::IsTrue(station == Station(1, 850.00));
      }

      bool CompareAlignments(std::shared_ptr<const WBFL::COGO::Alignment> alignment1, std::shared_ptr<const WBFL::COGO::Alignment> alignment2, Float64 start, Float64 end, long nPoints)
      {
         for (long i = 0; i < nPoints; i++)
         {
            Station station(start + (end - start) * i / (nPoints - 1));
            auto pnt1 = alignment1->LocatePoint(station, OffsetType::AlongDirection, 0.0, Direction(0));
            auto pnt2 = alignment2->LocatePoint(station, OffsetType::AlongDirection, 0.0, Direction(0));

            // I think the error may accumulate over the length of the sub-spline
            // because spirals are represented with cubic splines when the full spiral isn't modeled
            // Use a reduced tolerance
            if (!IsEqual(pnt1.X(), pnt2.X(), 0.2) || !IsEqual(pnt1.Y(), pnt2.Y(), 0.2))
               return false;

            auto dir1 = alignment1->GetNormal(station);
            auto dir2 = alignment2->GetNormal(station);
            if (!IsEqual(dir1.GetValue(), dir2.GetValue(), 0.2))
               return false;
         }
         return true;
      }

      TEST_METHOD(StationEquations)
      {
         auto alignment = Alignment::Create();
         Assert::IsTrue(alignment->GetStationEquations().empty()); // should start off empty

         auto equation = alignment->AddStationEquation(3400, 3200);
         Assert::IsTrue(alignment->GetStationEquations().size() == 1);
         Assert::IsTrue(IsEqual(equation.GetBack(), 3400.0));
         Assert::IsTrue(IsEqual(equation.GetAhead(), 3200.0));

         try { alignment->AddStationEquation(200.00, 50.0); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_STATIONEQUATIONBACK); }

         equation = alignment->AddStationEquation(4200, 500.0);
         Assert::IsTrue(alignment->GetStationEquations().size() == 2);
         Assert::IsTrue(IsEqual(equation.GetBack(), 4200.0));
         Assert::IsTrue(IsEqual(equation.GetAhead(), 500.0));

         equation = alignment->AddStationEquation(600, 1500.0);
         Assert::IsTrue(alignment->GetStationEquations().size() == 3);
         Assert::IsTrue(IsEqual(equation.GetBack(), 600.0));
         Assert::IsTrue(IsEqual(equation.GetAhead(), 1500.0));

         alignment->ClearStationEquations();
         Assert::IsTrue(alignment->GetStationEquations().empty());

         // test with some real values
         alignment->AddStationEquation(1500, 1350);
         alignment->AddStationEquation(2000, 2150);
         alignment->AddStationEquation(3200, 4000);
         alignment->AddStationEquation(4800, 0);

         Station station;

         // before first equation
         station.SetStation(0, 11700);
         try { alignment->ConvertToNormalizedStation(station); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

         station.SetStation(0, 1200);
         Assert::IsTrue(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 1200.0));

         // after last equation
         station.SetStation(25, 11700); // bad zone index
         try { alignment->ConvertToNormalizedStation(station); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_INVALIDINDEX); }

         station.SetStation(4, -600);
         try { alignment->ConvertToNormalizedStation(station); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

         station.SetStation(4, 1200);
         Assert::IsTrue(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 5200.0));

         station.SetStation(1, 11700);
         try { alignment->ConvertToNormalizedStation(station); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

         station.SetStation(1, 1250);
         try { alignment->ConvertToNormalizedStation(station); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

         station.SetStation(1, 1700);
         Assert::IsTrue(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 1850.0));

         // station is already normalized
         station.SetStation(INVALID_INDEX, 1700);
         Assert::IsTrue(IsEqual(alignment->ConvertToNormalizedStation(station).GetValue(), 1700.0));

         station = alignment->ConvertFromNormalizedStation(1200);
         Assert::IsTrue(station.GetStationZoneIndex() == 0);
         Assert::IsTrue(IsEqual(station.GetValue(), 1200.0));

         station = alignment->ConvertFromNormalizedStation(1800);
         Assert::IsTrue(station.GetStationZoneIndex() == 1);
         Assert::IsTrue(IsEqual(station.GetValue(), 1650.0));

         station = alignment->ConvertFromNormalizedStation(2300);
         Assert::IsTrue(station.GetStationZoneIndex() == 2);
         Assert::IsTrue(IsEqual(station.GetValue(), 2300.0));

         station = alignment->ConvertFromNormalizedStation(3300);
         Assert::IsTrue(station.GetStationZoneIndex() == 3);
         Assert::IsTrue(IsEqual(station.GetValue(), 4100.0));

         station = alignment->ConvertFromNormalizedStation(4500);
         Assert::IsTrue(station.GetStationZoneIndex() == 4);
         Assert::IsTrue(IsEqual(station.GetValue(), 500.));

         station = alignment->ConvertFromNormalizedStation(2150);
         Assert::IsTrue(station.GetStationZoneIndex() == 1);
         Assert::IsTrue(IsEqual(station.GetValue(), 2000.0));

         station = alignment->ConvertFromNormalizedStation(3200);
         Assert::IsTrue(station.GetStationZoneIndex() == 2);
         Assert::IsTrue(IsEqual(station.GetValue(), 3200.0));

         station.SetStation(1, 1360);
         try { alignment->ConvertFromNormalizedStation(station); }
         catch (XCoordGeom& e) { Assert::IsTrue(e.GetReason() == WBFL_COGO_E_STATIONRANGEERROR); }

         station.SetStation(INVALID_INDEX, 1360);
         station = alignment->ConvertFromNormalizedStation(station);
         Assert::IsTrue(station.GetStationZoneIndex() == 0);
         Assert::IsTrue(IsEqual(station.GetValue(), 1360.0));

         // Test Distance
         auto dist = alignment->DistanceBetweenStations(2000.0, 3000.0);
         Assert::IsTrue(IsEqual(dist, 1000.0));

         dist = alignment->DistanceBetweenStations(3000.0, 2000.0);
         Assert::IsTrue(IsEqual(dist, -1000.0));

         dist = alignment->DistanceBetweenStations(Station(1, 1400.0), Station(2, 3000.0));
         Assert::IsTrue(IsEqual(dist, 1450.0));

         // Test Increment
         station.SetStation(3, 4100);
         alignment->IncrementStation(station, -500);
         Assert::IsTrue(station.GetStationZoneIndex() == 2);
         Assert::IsTrue(IsEqual(station.GetValue(), 2800.0));
      }

      TEST_METHOD(Alignment)
      {
         auto alignment = Alignment::Create();

         auto segment = PathSegment::Create(10, 20, 20, 30);
         alignment->AddPathElement(segment);

         auto hc = CompoundCurve::Create();
         hc->SetPBT(WBFL::Geometry::Point2d(100, 100));
         alignment->AddPathElement(hc);

         Assert::IsTrue(alignment->GetPathElementCount() == 2);

         auto pe = alignment->GetPathElement(0);
         Assert::IsNotNull(std::dynamic_pointer_cast<const PathSegment>(pe).get());
         Assert::IsTrue(segment == pe);
         Assert::IsTrue(std::dynamic_pointer_cast<const PathSegment>(pe)->GetStartPoint() == WBFL::Geometry::Point2d(10, 20));
         Assert::IsTrue(std::dynamic_pointer_cast<const PathSegment>(pe)->GetEndPoint() == WBFL::Geometry::Point2d(20, 30));

         pe = alignment->GetPathElement(1);
         Assert::IsNotNull(std::dynamic_pointer_cast<const CompoundCurve>(pe).get());
         Assert::IsTrue(hc == pe);
         Assert::IsTrue(std::dynamic_pointer_cast<const CompoundCurve>(pe)->GetPBT() == WBFL::Geometry::Point2d(100, 100));

         Assert::IsTrue(alignment->GetReferenceStation() == Station(0.0));
         alignment->SetReferenceStation(50.0);
         Assert::IsTrue(alignment->GetReferenceStation() == Station(50.0));

         alignment->ClearPathElements();
         Assert::IsTrue(alignment->GetPathElementCount() == 0);

         // Test GetDirection
         segment->ThroughPoints(WBFL::Geometry::Point2d(0, 0), WBFL::Geometry::Point2d(100, 100));
         alignment->AddPathElement(segment);
         Assert::IsTrue(alignment->GetDirection(0.0, _T("N")) == Direction(3 * M_PI / 4));
         Assert::IsTrue(alignment->GetDirection(0.0, _T("Normal")) == Direction(3 * M_PI / 4));
         Assert::IsTrue(alignment->GetDirection(50.0, _T("15 0 0 L")) == Direction(3 * M_PI / 4 + ToRadians(15)));
         Assert::IsTrue(alignment->GetDirection(50.0, _T("15 0 0 R")) == Direction(3 * M_PI / 4 - ToRadians(15)));
         Assert::IsTrue(alignment->GetDirection(100.0, _T("N 45 W")) == Direction(3 * M_PI / 4));
         Assert::IsTrue(alignment->GetDirection(100.0, _T("S 45 W")) == Direction(5 * M_PI / 4));
         Assert::IsTrue(alignment->GetDirection(100.0, _T("N 45 E")) == Direction(M_PI / 4));
         Assert::IsTrue(alignment->GetDirection(100.0, _T("S 45 E")) == Direction(3 * M_PI / 4));
      }


      TEST_METHOD(Alignment1)
      {
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         alignment->AddPathElement(PathSegment::Create(150, 50, 250, 0));

         WBFL::Geometry::Point2d pbt(300, 0);
         WBFL::Geometry::Point2d pi(400, 0);
         WBFL::Geometry::Point2d pft(500, 100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         alignment->AddPathElement(hc);

         CommonAlignmentTest(alignment, 1.0, 1.0);
      }

      TEST_METHOD(Alignment1a)
      {
         // this test is the same as Test1 except we use a transition curve, circular curve, transition curve instead of a compound curve
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         alignment->AddPathElement(PathSegment::Create(150, 50, 250, 0));

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

         alignment->AddPathElement(entry_spiral);
         alignment->AddPathElement(curve);
         alignment->AddPathElement(exit_spiral);

         CommonAlignmentTest(alignment, 1.0, 1.0);
      }

      TEST_METHOD(Alignment2)
      {
         // Mirror Test1 about X axis

         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         alignment->AddPathElement(PathSegment::Create(150, -50, 250, 0));

         WBFL::Geometry::Point2d pbt(300, 0);
         WBFL::Geometry::Point2d pi(400, 0);
         WBFL::Geometry::Point2d pft(500, -100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         alignment->AddPathElement(hc);

         CommonAlignmentTest(alignment, 1.0, -1.0);
      }

      TEST_METHOD(Alignment2a)
      {
         // Mirror Test1a about X axis

         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, 100, 0));
         alignment->AddPathElement(PathSegment::Create(150, -50, 250, 0));

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

         alignment->AddPathElement(entry_spiral);
         alignment->AddPathElement(curve);
         alignment->AddPathElement(exit_spiral);

         CommonAlignmentTest(alignment, 1.0, -1.0);
      }

      TEST_METHOD(Alignment3)
      {
         // Mirror Test1 about Y axis
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         alignment->AddPathElement(PathSegment::Create(-150, 50, -250, 0));

         WBFL::Geometry::Point2d pbt(-300, 0);
         WBFL::Geometry::Point2d pi(-400, 0);
         WBFL::Geometry::Point2d pft(-500, 100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         alignment->AddPathElement(hc);

         CommonAlignmentTest(alignment, -1.0, 1.0);
      }

      TEST_METHOD(Alignment3a)
      {
         // Mirror Test1a about Y axis
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         alignment->AddPathElement(PathSegment::Create(-150, 50, -250, 0));

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

         alignment->AddPathElement(entry_spiral);
         alignment->AddPathElement(curve);
         alignment->AddPathElement(exit_spiral);

         CommonAlignmentTest(alignment, -1.0, 1.0);
      }

      TEST_METHOD(Alignment4)
      {
         // Mirror Test1 about both X and Y axis

         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         alignment->AddPathElement(PathSegment::Create(-150, -50, -250, 0));

         WBFL::Geometry::Point2d pbt(-300, 0);
         WBFL::Geometry::Point2d pi(-400, 0);
         WBFL::Geometry::Point2d pft(-500, -100);
         auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

         alignment->AddPathElement(hc);

         CommonAlignmentTest(alignment, -1.0, -1.0);
      }

      TEST_METHOD(Alignment4a)
      {
         // Mirror Test1a about both X and Y axis

         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(Station(100.00));

         alignment->AddPathElement(PathSegment::Create(0, 0, -100, 0));
         alignment->AddPathElement(PathSegment::Create(-150, -50, -250, 0));

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

         alignment->AddPathElement(entry_spiral);
         alignment->AddPathElement(curve);
         alignment->AddPathElement(exit_spiral);

         CommonAlignmentTest(alignment, -1.0, -1.0);
      }
   

      TEST_METHOD(Test1)
      {
         // Test an empty alignment
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(100);

         Float64 alignment_offset = 10;

         // Station 0+00
         Station station(0.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(0.0));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(3 * PI_OVER_2));
         auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(-100, -10));
         Float64 offset;
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(0.0));

         // Station 2+00
         station.SetValue(200.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(0.0));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(100, -10));
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(200.0));
      }

      TEST_METHOD(Test3)
      {
         // Alignment consisting of a single line segment
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(100);

         alignment->AddPathElement(PathSegment::Create(50, 50, 250, 250));

         Float64 alignment_offset = 10;


         // Station 0+00
         Station station(0.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(M_PI / 4));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(M_PI / 4 + 3 * PI_OVER_2));
         auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(-13.639610306789281, -27.781745930520231));
         Float64 offset;
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(0.0));

         // Station 1+50
         station.SetValue(150.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(M_PI / 4));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(M_PI / 4 + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(92.426406871192853, 78.284271247461902));
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(150.0));

         // Station 5+00
         station.SetValue(500);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(M_PI / 4));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(M_PI / 4 + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(339.91378028648450, 325.77164466275354));
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(500));
      }

      TEST_METHOD(Test4)
      {
         // Alignment consisting of a single curve
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(100);

         WBFL::Geometry::Point2d pbt(0, 1000);
         WBFL::Geometry::Point2d pi(700, 1000);
         WBFL::Geometry::Point2d pft(1000, 700);
         alignment->AddPathElement(CompoundCurve::Create(pbt, pi, pft, 500, 100, TransitionCurveType::Clothoid, 200, TransitionCurveType::Clothoid));

         Float64 alignment_offset = 10;

         // Station 0+00
         Station station(0.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(0.00));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(3 * PI_OVER_2));
         auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(339.035600, 990.00));
         Float64 offset;
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(0.0));

         // Station 1+50
         station.SetValue(150.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(6.2581853));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(6.2581853 + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(488.78250119134225, 989.58647677139686));
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(150.0));

         // Station 2+50
         station.SetValue(250.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(6.083185));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(6.083185 + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(586.36691011184678, 979.39958736479957));
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(250.0));

         // Station 4+50
         station.SetValue(450.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(5.68345));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(5.68345 + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(765.69631407593351, 903.58044763162241));
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(450.0));

         // Station 6+50
         station.SetValue(650.0);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(5.497787));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(5.497787 + 3 * PI_OVER_2));
         pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(913.63394982918112, 772.22391454708782));
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(650.0));
      }

      TEST_METHOD(Test5)
      {
         // Alignment consisting of two line segments

         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(100);
         alignment->AddPathElement(PathSegment::Create(0, 0, 10, 0));
         alignment->AddPathElement(PathSegment::Create(10, 10, 20, 10));

         Float64 alignment_offset = 3;

         // Station 1+15
         Station station(115);
         Assert::IsTrue(alignment->GetBearing(station) == Direction(PI_OVER_2));
         Assert::IsTrue(alignment->GetNormal(station) == Direction(0.0));
         auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(13, 5));
         Float64 offset;
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, alignment_offset));
         Assert::IsTrue(station == Station(115));
      }


      TEST_METHOD(Subalignment1)
      {
         // Test sub-path with empty alignment
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(100);

         // sub-path that captures entire alignment
         auto subpath = alignment->CreateSubAlignment(-10.0, 300.0);
         Assert::IsTrue(subpath->GetPathElementCount() == 3);
         auto element = subpath->GetPathElement(0);
         auto segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(-110, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(0, 0));

         // sub-Alignment that captures start
         subpath = alignment->CreateSubAlignment(-10, -5);
         Assert::IsTrue(subpath->GetPathElementCount() == 1);
         element = subpath->GetPathElement(0);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(-110, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(-105, 0));

         // sub-Alignment that captures the middle
         subpath = alignment->CreateSubAlignment(110, 200);
         Assert::IsTrue(subpath->GetPathElementCount() == 1);
         element = subpath->GetPathElement(0);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(10, 0));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(100, 0));
      }

      TEST_METHOD(Subalignment2)
      {
         // Test sub path with 2-point alignment
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(100);
         alignment->AddPathElement(PathSegment::Create(10, 10, 110, 110));

         // sub-alignment that captures entire alignment
         auto sub_alignment = alignment->CreateSubAlignment(-10.0, 300.0);
         Assert::IsTrue(sub_alignment->GetPathElementCount() == 3);
         auto element = sub_alignment->GetPathElement(1);
         auto segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(10, 10));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(110, 110));

         // sub-Alignment that captures start
         sub_alignment = alignment->CreateSubAlignment(-10, -5);
         Assert::IsTrue(sub_alignment->GetPathElementCount() == 1);
         element = sub_alignment->GetPathElement(0);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(-67.781745930520231, -67.781745930520231));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(-64.246212024587493, -64.246212024587493));

         // sub-Alignment that captures the middle
         sub_alignment = alignment->CreateSubAlignment(110, 200);
         Assert::IsTrue(sub_alignment->GetPathElementCount() == 1);
         element = sub_alignment->GetPathElement(0);
         segment = std::dynamic_pointer_cast<const PathSegment>(element);
         Assert::IsNotNull(segment.get());
         Assert::IsTrue(segment->GetStartPoint() == WBFL::Geometry::Point2d(17.071067811865476, 17.071067811865476));
         Assert::IsTrue(segment->GetEndPoint() == WBFL::Geometry::Point2d(80.710678118654755, 80.710678118654755));

         CompareAlignments(alignment, sub_alignment, 110, 200, 10);
      }

      TEST_METHOD(Subalignment3)
      {
         // Alignment consisting of a single horizontal curve
         auto alignment = Alignment::Create();
         alignment->SetReferenceStation(100.0);
         WBFL::Geometry::Point2d pbt(0, 0);
         WBFL::Geometry::Point2d pi(1000, 0);
         WBFL::Geometry::Point2d pft(5000, 5000);
         alignment->AddPathElement(CompoundCurve::Create(pbt, pi, pft, 500, 20, TransitionCurveType::Clothoid, 30, TransitionCurveType::Clothoid));

         // sub alignment that captures entire element
         // start on back tangent, end in circular curve
         auto sub_alignment = alignment->CreateSubAlignment(-10, 300);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, -10, 300, 10));

         Assert::IsTrue(sub_alignment->GetPathElementCount() == 2);

         auto element = sub_alignment->GetPathElement(1);
         auto hc = std::dynamic_pointer_cast<const CompoundCurve>(element);
         Assert::IsNotNull(hc.get());
         Assert::IsTrue(IsEqual(hc->GetRadius(), 500.));
         Assert::IsTrue(IsEqual(hc->GetSpiralLength(CompoundCurve::SpiralLocation::Entry), 20.0));
         Assert::IsTrue(IsEqual(hc->GetSpiralLength(CompoundCurve::SpiralLocation::Exit), 0.0)); // sub alignment stops before the exit spiral so this length is now 0.0

         // start on back tangent and end in entry spiral
         sub_alignment = alignment->CreateSubAlignment(-10, 110);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, -10, 110, 10));

         // start on back tangent and end in exit spiral
         sub_alignment = alignment->CreateSubAlignment(-10, 550);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, -10, 550, 30));

         // start on back tangent and end on forward tangent
         sub_alignment = alignment->CreateSubAlignment(-10, 800);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, -10, 80, 40));

         // start in entry spiral, end in entry spiral
         sub_alignment = alignment->CreateSubAlignment(110, 118);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 110, 118, 10));

         // start in entry spiral, end in circular curve
         sub_alignment = alignment->CreateSubAlignment(110, 300);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 110, 300, 10));

         // start in entry spiral, end in exit spiral
         sub_alignment = alignment->CreateSubAlignment(110, 560);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 110, 560, 30));

         // start in entry spiral, end on fwd tangent
         sub_alignment = alignment->CreateSubAlignment(110, 800);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 110, 800, 30));

         // start and end in circular curve
         sub_alignment = alignment->CreateSubAlignment(200, 500);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 200, 500, 10));

         // start in circular curve, end in exit spiral
         sub_alignment = alignment->CreateSubAlignment(300, 550);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 300, 550, 10));

         // start in circular curve, end in fwd tangent
         sub_alignment = alignment->CreateSubAlignment(300, 1000);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 300, 1000, 10));

         // start in exit spiral, end in exit spiral
         sub_alignment = alignment->CreateSubAlignment(545, 570);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 545, 570, 10));

         // start in exit spiral, end in fwd tangent
         sub_alignment = alignment->CreateSubAlignment(545, 1000);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 545, 1000, 10));

         // start and end on back tangent
         sub_alignment = alignment->CreateSubAlignment(-10, 50);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, -10, 50, 10));

         // start and end on fwd tangent
         sub_alignment = alignment->CreateSubAlignment(600, 800);
         Assert::IsTrue(CompareAlignments(alignment, sub_alignment, 600, 800, 10));
      }

      TEST_METHOD(Subalignment4)
      {
         auto alignment = Alignment::Create();
         Float64 refStation = 100.0;
         alignment->SetReferenceStation(refStation);

         auto spline = CubicSpline::Create();

         spline->AddPoint(5, 5);
         spline->AddPoint(8, 7);
         spline->AddPoint(13, 9);
         spline->AddPoint(16, 10);
         spline->AddPoint(17, 15);
         spline->AddPoint(22, 16);

         spline->SetStartDirection(M_PI / 4);
         spline->SetEndDirection(M_PI / 6);

         alignment->AddPathElement(spline);

         auto Ls = spline->GetLength();

         // full length of spline
         Float64 startStation = refStation;
         Float64 endStation = startStation + Ls;
         auto subAlignment = alignment->CreateSubAlignment(startStation, endStation);
         CompareAlignments(alignment, subAlignment, startStation, endStation, 10);


         // before spline
         startStation = refStation - 50;
         endStation = startStation + 49;
         subAlignment = alignment->CreateSubAlignment(startStation, endStation);
         CompareAlignments(alignment, subAlignment, startStation, endStation, 10);


         // after spline
         startStation = refStation + Ls + 50;
         endStation = startStation + 50;
         subAlignment = alignment->CreateSubAlignment(startStation, endStation);
         CompareAlignments(alignment, subAlignment, startStation, endStation, 10);

         // mid-spline
         startStation = refStation + int(Ls / 4);
         endStation = startStation + int(Ls / 2);
         subAlignment = alignment->CreateSubAlignment(startStation, endStation);
         CompareAlignments(alignment, subAlignment, startStation, endStation, 10);

         // start before spline, end mid-spline
         startStation = refStation - 20;
         endStation = startStation + 3 * Ls / 4;
         subAlignment = alignment->CreateSubAlignment(startStation, endStation);
         CompareAlignments(alignment, subAlignment, startStation, endStation, 10);

         // start mid-spline, end after spline
         startStation = refStation + Ls / 4;
         endStation = startStation + Ls + 10;
         subAlignment = alignment->CreateSubAlignment(startStation, endStation);
         CompareAlignments(alignment, subAlignment, startStation, endStation, 10);
      }

      TEST_METHOD(Subalignment5)
      {
         // Alignment consisting of a two line segments
         auto alignment = Alignment::Create();

         alignment->SetReferenceStation(100.00);

         WBFL::Geometry::Point2d p1(0, 0);
         WBFL::Geometry::Point2d p2(10, 0);
         WBFL::Geometry::Point2d p3(10, 10);
         WBFL::Geometry::Point2d p4(20, 10);

         auto segment1 = PathSegment::Create(p1, p2);
         auto segment2 = PathSegment::Create(p3, p4);

         alignment->AddPathElement(segment1);
         alignment->AddPathElement(segment2);

         //////////////
         // Bearing,Normal,LocatePoint, Station, and Offset

         // Sta 1+15
         Assert::IsTrue(alignment->GetBearing(115.00) == Direction(PI_OVER_2));
         Assert::IsTrue(alignment->GetNormal(115.00) == Direction(0.0));
         auto pnt = alignment->LocatePoint(115, OffsetType::AlongDirection, 3, alignment->GetNormal(115.0));
         Assert::IsTrue(pnt == WBFL::Geometry::Point2d(13.0, 5.0));

         Station station;
         Float64 offset;
         std::tie(station, offset) = alignment->StationAndOffset(pnt);
         Assert::IsTrue(IsEqual(offset, 3.0));
         Assert::IsTrue(station == 115.0);
      }
   };
}
