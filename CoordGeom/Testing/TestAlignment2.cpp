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
#include "TestAlignment2.h"
#include <CoordGeom/Alignment.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/TransitionCurve.h>
#include <CoordGeom/CircularCurve.h>

using namespace WBFL::COGO;


bool CTestAlignment2::Test(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment2::Test");
   TRY_TESTME(Test1(rlog));
   TRY_TESTME(Test2(rlog));
   TRY_TESTME(Test3(rlog));
   TRY_TESTME(Test4(rlog));
   TRY_TESTME(Test5(rlog));
   TESTME_EPILOG("CTestAlignment2::Test");
}

bool CTestAlignment2::Test1(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment2::Test1");

   // Test an empty alignment
   auto alignment = Alignment::Create();
   alignment->SetReferenceStation(100);

   Float64 alignment_offset = 10;

   // Station 0+00
   Station station(0.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(0.0));
   TRY_TESTME(alignment->GetNormal(station) == Direction(3*PI_OVER_2));
   auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(-100, -10));
   Float64 offset;
   std::tie(station,offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(0.0));

   // Station 2+00
   station.SetValue(200.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(0.0));
   TRY_TESTME(alignment->GetNormal(station) == Direction(3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(100, -10));
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(200.0));

   TESTME_EPILOG("CTestAlignment2::Test1");
}


bool CTestAlignment2::Test2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment2::Test2");
   // In the old COM COGO library, this tested an alignment with a single point
   // Single point alignments are no longer supported
   // This test is a placeholder so the other tests have the same number as before
   TESTME_EPILOG("CTestAlignment2::Test2");
}

bool CTestAlignment2::Test3(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment2::Test3");

   // Alignment consisting of a single line segment
   auto alignment = Alignment::Create();
   alignment->SetReferenceStation(100);

   alignment->AddPathElement(PathSegment::Create(50, 50, 250, 250));

   Float64 alignment_offset = 10;


   // Station 0+00
   Station station(0.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(M_PI / 4));
   TRY_TESTME(alignment->GetNormal(station) == Direction(M_PI / 4 + 3 * PI_OVER_2));
   auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(-13.639610306789281, -27.781745930520231));
   Float64 offset;
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(0.0));

   // Station 1+50
   station.SetValue(150.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(M_PI / 4));
   TRY_TESTME(alignment->GetNormal(station) == Direction(M_PI / 4 + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(92.426406871192853, 78.284271247461902));
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(150.0));

   // Station 5+00
   station.SetValue(500);
   TRY_TESTME(alignment->GetBearing(station) == Direction(M_PI / 4));
   TRY_TESTME(alignment->GetNormal(station) == Direction(M_PI / 4 + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(339.91378028648450, 325.77164466275354));
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(500));

   TESTME_EPILOG("CTestAlignment2::Test3");
}

bool CTestAlignment2::Test4(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment2::Test4");
   // Alignment consisting of a single curve
   auto alignment = Alignment::Create();
   alignment->SetReferenceStation(100);

   WBFL::Geometry::Point2d pbt(0, 1000);
   WBFL::Geometry::Point2d pi(700, 1000);
   WBFL::Geometry::Point2d pft(1000, 700);
   alignment->AddPathElement(CompoundCurve::Create(pbt,pi,pft,500,100,TransitionCurveType::Clothoid,200,TransitionCurveType::Clothoid));

   Float64 alignment_offset = 10;

   // Station 0+00
   Station station(0.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(0.00));
   TRY_TESTME(alignment->GetNormal(station) == Direction(3 * PI_OVER_2));
   auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(339.035600, 990.00));
   Float64 offset;
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(0.0));

   // Station 1+50
   station.SetValue(150.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(6.2581853));
   TRY_TESTME(alignment->GetNormal(station) == Direction(6.2581853 + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(488.78250119134225, 989.58647677139686));
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(150.0));

   // Station 2+50
   station.SetValue(250.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(6.083185));
   TRY_TESTME(alignment->GetNormal(station) == Direction(6.083185 + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(586.36691011184678, 979.39958736479957));
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(250.0));

   // Station 4+50
   station.SetValue(450.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(5.68345));
   TRY_TESTME(alignment->GetNormal(station) == Direction(5.68345 + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(765.69631407593351, 903.58044763162241));
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(450.0));

   // Station 6+50
   station.SetValue(650.0);
   TRY_TESTME(alignment->GetBearing(station) == Direction(5.497787));
   TRY_TESTME(alignment->GetNormal(station) == Direction(5.497787 + 3 * PI_OVER_2));
   pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(913.63394982918112, 772.22391454708782));
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(650.0));

   TESTME_EPILOG("CTestAlignment2::Test4");
}

bool CTestAlignment2::Test5(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment2::Test5");
   // Alignment consisting of two line segments
   
   auto alignment = Alignment::Create();
   alignment->SetReferenceStation(100);
   alignment->AddPathElement(PathSegment::Create(0, 0, 10, 0));
   alignment->AddPathElement(PathSegment::Create(10,10,20,10));

   Float64 alignment_offset = 3;

   // Station 1+15
   Station station(115);
   TRY_TESTME(alignment->GetBearing(station) == Direction(PI_OVER_2));
   TRY_TESTME(alignment->GetNormal(station) == Direction(0.0));
   auto pnt = alignment->LocatePoint(station, OffsetType::AlongDirection, alignment_offset, alignment->GetNormal(station));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(13, 5));
   Float64 offset;
   std::tie(station, offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, alignment_offset));
   TRY_TESTME(station == Station(115));

   TESTME_EPILOG("CTestAlignment2::Test5");
}
