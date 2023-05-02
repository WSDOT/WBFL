///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
#pragma once

#include <CoordGeom/CoordGeomLib.h>
#include "TestAlignment1.h"
#include <CoordGeom/Alignment.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/TransitionCurve.h>
#include <CoordGeom/CircularCurve.h>

using namespace WBFL::COGO;

void AlignmentDump(const Alignment& alignment, std::ostream& os)
{
   std::vector<Float64> vStations = linspace(0.00, 700.0, 50);

   for (const auto& station : vStations)
   {
      auto pnt = alignment.LocatePoint(station, OffsetType::AlongDirection, 0.0, Direction(0.0));
      os << pnt.X() << ", " << pnt.Y() << std::endl;
   }
}

bool CommonAlignmentTest(WBFL::Debug::Log& rlog,std::shared_ptr<Alignment> alignment,Float64 xSign,Float64 ySign)
{
   TESTME_PROLOGUE("CTestAlignment1::CommonAlignmentTest");

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   Float64 alignment_offset = (ySign/xSign) * 10;
   Float64 dir;
   WBFL::Geometry::Point2d pnt;
   Station station;
   Float64 offset;
   WBFL::Geometry::Point2d newPnt;
   bool bOnProjection;

   auto AlignmentDirection = [&xSign,&ySign](Float64 dir) {return atan2(ySign * tan(dir),xSign); };

   // Sta 0+00
   station.SetValue(0.0);
   dir = AlignmentDirection(0.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(0.00, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(0.00));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*-100, ySign*-10));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(0.0));

   std::tie(newPnt,station,bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*-100, ySign*0));
   TRY_TESTME(station == Station(0.00));
   TRY_TESTME(bOnProjection == true);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(0.0));


   // Sta 1+00
   station.SetValue(100);
   dir = AlignmentDirection(0.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*0.0, ySign*-10.0));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(100.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*0, ySign*0));
   TRY_TESTME(station == Station(100.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(100.0));

   // Sta 1+25
   station.SetValue(125);
   dir = AlignmentDirection(0.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*25.0, ySign*-10.0));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(125.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*25, ySign*0));
   TRY_TESTME(station == Station(125.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(125.0));

   // Sta 2+00
   station.SetValue(200);
   dir = AlignmentDirection(M_PI/4);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*107.0710678, ySign*-7.0710678));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(200.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*100, ySign*0));
   TRY_TESTME(station == Station(200.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(200.0));

   // Sta 2+50
   station.SetValue(250);
   dir = AlignmentDirection(M_PI/4);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*142.42641, ySign*28.28427));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(250.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*135.35533905932738, ySign*35.355339059327392));
   TRY_TESTME(station == Station(250.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(250.0));

   // Sta 3+00
   station.SetValue(300);
   dir = AlignmentDirection(5.8195376981787801);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*171.72503, ySign*27.95714));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(300.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*176.19716589662397, ySign*36.901417051688000));
   TRY_TESTME(station == Station(300.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(300.0));

   // Sta 4+90
   station.SetValue(490);
   dir = AlignmentDirection(0.0084083531428916);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*357.56997655414648, ySign*-9.9881528501514651));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(490.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*357.48589488932885, ySign*0.011493657282799078));
   TRY_TESTME(station == Station(490.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(490.0));

   // Sta 5+30
   station.SetValue(530);
   dir = AlignmentDirection(0.39101);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*400.30796498659186, ySign*-1.6561192213706857));

   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(530.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*396.49675804330548, ySign*7.5891337029933084));
   TRY_TESTME(station == Station(530.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(530.0));

   // Sta 5+65
   station.SetValue(565);
   dir = AlignmentDirection(0.73327699338782193);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*432.59047672020114, ySign*18.822245727601619));

   std::tie(station,offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(565.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*425.89739504565671, ySign*26.252094830906742));
   TRY_TESTME(station == Station(565.00));
   TRY_TESTME(bOnProjection == false);

   std::tie(station,offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(565.0));

   // Sta 6+00
   station.SetValue(600);
   dir = AlignmentDirection(M_PI/4);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*457.89177856524304, ySign*43.749642941512093));

   std::tie(station,offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(600.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*450.82071075337751, ySign*50.820710753377611));
   TRY_TESTME(station == Station(600.00));
   TRY_TESTME(bOnProjection == true);

   std::tie(station,offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(600.0));

   // Sta 7+00
   station.SetValue(700);
   dir = AlignmentDirection(M_PI/4);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*528.60245668389769, ySign*114.46032106016685));

   std::tie(station,offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(700.0));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*521.53138887203227, ySign*121.531388872032281));
   TRY_TESTME(station == Station(700.00));
   TRY_TESTME(bOnProjection == true);

   std::tie(station,offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(700.0));

   // Add a station equation
   alignment->AddStationEquation(650, 800);

   station = alignment->ConvertFromNormalizedStation(700);
   TRY_TESTME(station.GetStationZoneIndex() == 1);
   TRY_TESTME(IsEqual(station.GetValue(), 850.0));

   // Sta 8+50 (station range 1)
   station.SetStation(1, 850);
   dir = AlignmentDirection(M_PI/4);
   TRY_TESTME(alignment->GetBearing(station) == Direction(dir));
   TRY_TESTME(alignment->GetNormal(station) == Direction(dir + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(xSign*528.60245668389769, ySign*114.46032106016685));

   std::tie(station,offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(1, 850.00));

   std::tie(newPnt, station, bOnProjection) = alignment->ProjectPoint(pnt);
   TRY_TESTME(newPnt == WBFL::Geometry::Point2d(xSign*521.53138887203227, ySign*121.531388872032281));
   TRY_TESTME(station == Station(1, 850.00));
   TRY_TESTME(bOnProjection == true);

   std::tie(station, offset) = alignment->StationAndOffset(newPnt);
   TRY_TESTME(IsEqual(offset, 0.0));
   TRY_TESTME(station == Station(1, 850.00));

   TESTME_EPILOG("CTestAlignment1::CommonAlignmentTest");
}

CTestAlignment1::CTestAlignment1()
{
}


bool CTestAlignment1::Test(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test");
   TRY_TESTME(Test1(rlog));
   TRY_TESTME(Test1a(rlog));
   TRY_TESTME(Test2(rlog));
   TRY_TESTME(Test2a(rlog));
   TRY_TESTME(Test3(rlog));
   TRY_TESTME(Test3a(rlog));
   TRY_TESTME(Test4(rlog));
   TRY_TESTME(Test4a(rlog));
   TESTME_EPILOG("CTestAlignment1::Test");
}

bool CTestAlignment1::Test1(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test1");

   auto alignment = Alignment::Create();
   alignment->SetReferenceStation(Station(100.00));

   alignment->AddPathElement(PathSegment::Create(0, 0, 100, 0));
   alignment->AddPathElement(PathSegment::Create(150, 50, 250, 0));

   WBFL::Geometry::Point2d pbt(300, 0);
   WBFL::Geometry::Point2d pi(400, 0);
   WBFL::Geometry::Point2d pft(500, 100);
   auto hc = CompoundCurve::Create(pbt, pi, pft, 100.0, 10.0, TransitionCurveType::Clothoid, 20, TransitionCurveType::Clothoid);

   alignment->AddPathElement(hc);

//   AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog,alignment, 1.0, 1.0));

   TESTME_EPILOG("CTestAlignment1::Test1");
}

bool CTestAlignment1::Test1a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test1a");
   
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
   Direction end_exit_spiral_direction(M_PI/4);

   WBFL::Geometry::Point2d pi(396.225283748, 1.8101406324);

   auto entry_spiral = TransitionCurve::Create(start_entry_spiral,start_entry_spiral_direction, 0.0, 100.0, 10.0, TransitionCurveType::Clothoid);
   auto curve = CircularCurve::Create(end_entry_spiral, pi, start_exit_spiral, 100.0);
   auto exit_spiral = TransitionCurve::Create(start_exit_spiral, start_exit_spiral_direction, 100.0, 0.0, 20.0, TransitionCurveType::Clothoid);

   alignment->AddPathElement(entry_spiral);
   alignment->AddPathElement(curve);
   alignment->AddPathElement(exit_spiral);

   //AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog, alignment, 1.0, 1.0));

   TESTME_EPILOG("CTestAlignment1::Test1a");
}

bool CTestAlignment1::Test2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test2");

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

   //AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog, alignment, 1.0, -1.0));

   TESTME_EPILOG("CTestAlignment1::Test2");
}

bool CTestAlignment1::Test2a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test2a");

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

   //AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog, alignment, 1.0, -1.0));

   TESTME_EPILOG("CTestAlignment1::Test2a");
}

bool CTestAlignment1::Test3(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test3");

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

   //AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog, alignment, -1.0, 1.0));

   TESTME_EPILOG("CTestAlignment1::Test3");
}

bool CTestAlignment1::Test3a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test3a");

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

   //AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog, alignment, -1.0, 1.0));

   TESTME_EPILOG("CTestAlignment1::Test3a");
}

bool CTestAlignment1::Test4(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test4");

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

   //AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog, alignment, -1.0, -1.0));

   TESTME_EPILOG("CTestAlignment1::Test4");
}

bool CTestAlignment1::Test4a(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment1::Test4a");

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

   //AlignmentDump(alignment, std::cout);

   TRY_TESTME(CommonAlignmentTest(rlog, alignment, -1.0, -1.0));

   TESTME_EPILOG("CTestAlignment1::Test4a");
}
