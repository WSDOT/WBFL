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
#include "TestAlignment3.h"
#include <CoordGeom/Alignment.h>
#include <CoordGeom/PathSegment.h>
#include <CoordGeom/CompoundCurve.h>
#include <CoordGeom/TransitionCurve.h>
#include <CoordGeom/CircularCurve.h>
#include <CoordGeom/CubicSpline.h>

using namespace WBFL::COGO;


bool CTestAlignment3::Test(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment3::Test");
   TRY_TESTME(Test1(rlog));
   TRY_TESTME(Test2(rlog));
   TRY_TESTME(Test3(rlog));
   TRY_TESTME(Test4(rlog));
   TRY_TESTME(Test5(rlog));
   TESTME_EPILOG("CTestAlignment3::Test");
}

bool CTestAlignment3::Test1(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment3::Test1");
   // Test sub-path with empty alignment
   auto alignment = Alignment::Create();
   alignment->SetReferenceStation(100);

   // sub-path that captures entire alignment
   auto subpath = alignment->CreateSubAlignment(-10.0, 300.0);
   TRY_TESTME(subpath->GetPathElementCount() == 2);
   auto element = subpath->GetPathElement(0);
   auto segment = std::dynamic_pointer_cast<const PathSegment>(element);
   TRY_TESTME(segment);
   TRY_TESTME(segment->GetStartPoint() == WBFL::Geometry::Point2d(-110, 0));
   TRY_TESTME(segment->GetEndPoint() == WBFL::Geometry::Point2d(0, 0));

   // sub-Alignment that captures start
   subpath = alignment->CreateSubAlignment(-10, -5);
   TRY_TESTME(subpath->GetPathElementCount() == 2);
   element = subpath->GetPathElement(1);
   segment = std::dynamic_pointer_cast<const PathSegment>(element);
   TRY_TESTME(segment);
   TRY_TESTME(segment->GetStartPoint() == WBFL::Geometry::Point2d(-110, 0));
   TRY_TESTME(segment->GetEndPoint() == WBFL::Geometry::Point2d(-105, 0));

   // sub-Alignment that captures the middle
   subpath = alignment->CreateSubAlignment(110, 200);
   TRY_TESTME(subpath->GetPathElementCount() == 2);
   element = subpath->GetPathElement(1);
   segment = std::dynamic_pointer_cast<const PathSegment>(element);
   TRY_TESTME(segment);
   TRY_TESTME(segment->GetStartPoint() == WBFL::Geometry::Point2d(10, 0));
   TRY_TESTME(segment->GetEndPoint() == WBFL::Geometry::Point2d(100, 0));

   TESTME_EPILOG("CTestAlignment3::Test1");
}

bool CTestAlignment3::Test2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment3::Test2");

   // Test sub path with 2-point alignment
   auto alignment = Alignment::Create();
   alignment->SetReferenceStation(100);
   alignment->AddPathElement(PathSegment::Create(10, 10, 110, 110));

   // sub-alignment that captures entire alignment
   auto sub_alignment = alignment->CreateSubAlignment(-10.0, 300.0);
   TRY_TESTME(sub_alignment->GetPathElementCount() == 2);
   auto element = sub_alignment->GetPathElement(1);
   auto segment = std::dynamic_pointer_cast<const PathSegment>(element);
   TRY_TESTME(segment);
   TRY_TESTME(segment->GetStartPoint() == WBFL::Geometry::Point2d(10, 10));
   TRY_TESTME(segment->GetEndPoint() == WBFL::Geometry::Point2d(110, 110));

   // sub-Alignment that captures start
   sub_alignment = alignment->CreateSubAlignment(-10, -5);
   TRY_TESTME(sub_alignment->GetPathElementCount() == 2);
   element = sub_alignment->GetPathElement(1);
   segment = std::dynamic_pointer_cast<const PathSegment>(element);
   TRY_TESTME(segment);
   TRY_TESTME(segment->GetStartPoint() == WBFL::Geometry::Point2d(-67.781745930520231, -67.781745930520231));
   TRY_TESTME(segment->GetEndPoint() == WBFL::Geometry::Point2d(-64.246212024587493, -64.246212024587493));

   // sub-Alignment that captures the middle
   sub_alignment = alignment->CreateSubAlignment(110, 200);
   TRY_TESTME(sub_alignment->GetPathElementCount() == 2);
   element = sub_alignment->GetPathElement(1);
   segment = std::dynamic_pointer_cast<const PathSegment>(element);
   TRY_TESTME(segment);
   TRY_TESTME(segment->GetStartPoint() == WBFL::Geometry::Point2d(17.071067811865476, 17.071067811865476));
   TRY_TESTME(segment->GetEndPoint() == WBFL::Geometry::Point2d(80.710678118654755, 80.710678118654755));

   CompareAlignments(alignment, sub_alignment, 110, 200, 10);

   TESTME_EPILOG("CTestAlignment3::Test2");
}

bool CTestAlignment3::Test3(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment3::Test3");
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
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, -10, 300, 10));

   TRY_TESTME(sub_alignment->GetPathElementCount() == 2);

   auto element = sub_alignment->GetPathElement(1);
   auto hc = std::dynamic_pointer_cast<const CompoundCurve>(element);
   TRY_TESTME(hc);
   TRY_TESTME(IsEqual(hc->GetRadius(), 500.));
   TRY_TESTME(IsEqual(hc->GetSpiralLength(CompoundCurve::SpiralLocation::Entry), 20.0));
   TRY_TESTME(IsEqual(hc->GetSpiralLength(CompoundCurve::SpiralLocation::Exit), 0.0)); // sub alignment stops before the exit spiral so this length is now 0.0

   // start on back tangent and end in entry spiral
   sub_alignment = alignment->CreateSubAlignment(-10, 110);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, -10, 110, 10));

   // start on back tangent and end in exit spiral
   sub_alignment = alignment->CreateSubAlignment(-10, 550);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, -10, 550, 30));

   // start on back tangent and end on forward tangent
   sub_alignment = alignment->CreateSubAlignment(-10, 800);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, -10, 80, 40));

   // start in entry spiral, end in entry spiral
   sub_alignment = alignment->CreateSubAlignment(110,118);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 110, 118, 10));

   // start in entry spiral, end in circular curve
   sub_alignment = alignment->CreateSubAlignment(110, 300);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 110, 300, 10));

   // start in entry spiral, end in exit spiral
   sub_alignment = alignment->CreateSubAlignment(110, 560);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 110, 560, 30));

   // start in entry spiral, end on fwd tangent
   sub_alignment = alignment->CreateSubAlignment(110, 800);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 110, 800, 30));

   // start and end in circular curve
   sub_alignment = alignment->CreateSubAlignment(200, 500);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 200, 500, 10));

   // start in circular curve, end in exit spiral
   sub_alignment = alignment->CreateSubAlignment(300, 550);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 300, 550, 10));

   // start in circular curve, end in fwd tangent
   sub_alignment = alignment->CreateSubAlignment(300, 1000);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 300, 1000, 10));

   // start in exit spiral, end in exit spiral
   sub_alignment = alignment->CreateSubAlignment(545, 570);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 545, 570, 10));

   // start in exit spiral, end in fwd tangent
   sub_alignment = alignment->CreateSubAlignment(545, 1000);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 545, 1000, 10));

   // start and end on back tangent
   sub_alignment = alignment->CreateSubAlignment(-10, 50);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, -10, 50, 10));

   // start and end on fwd tangent
   sub_alignment = alignment->CreateSubAlignment(600, 800);
   TRY_TESTME(CompareAlignments(alignment,sub_alignment, 600, 800, 10));

   TESTME_EPILOG("CTestAlignment3::Test3");
}

bool CTestAlignment3::Test4(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment3::Test4");

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


   TESTME_EPILOG("CTestAlignment3::Test4");
}

bool CTestAlignment3::Test5(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestAlignment3::Test5");

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
   TRY_TESTME(alignment->GetBearing(115.00) == Direction(PI_OVER_2));
   TRY_TESTME(alignment->GetNormal(115.00) == Direction(0.0));
   auto pnt = alignment->LocatePoint(115, OffsetType::AlongDirection, 3, alignment->GetNormal(115.0));
   TRY_TESTME(pnt == WBFL::Geometry::Point2d(13.0, 5.0));

   Station station;
   Float64 offset;
   std::tie(station,offset) = alignment->StationAndOffset(pnt);
   TRY_TESTME(IsEqual(offset, 3.0));
   TRY_TESTME(station == 115.0);

   TESTME_EPILOG("CTestAlignment3::Test5");
}

bool CTestAlignment3::CompareAlignments(std::shared_ptr<const WBFL::COGO::Alignment> alignment1, std::shared_ptr<const WBFL::COGO::Alignment> alignment2, Float64 start, Float64 end, long nPoints)
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
      if (!IsEqual(dir1.GetValue(),dir2.GetValue(),0.2))
         return false;
   }
   return true;
}
