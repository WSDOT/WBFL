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
#include "TestBridgeFramingGeometry.h"

#include <CoordGeom/PathSegment.h>
#include <CoordGeom/AlignmentOffsetLayoutLineFactory.h>
#include <CoordGeom/SimpleGirderLineFactory.h>
#include <CoordGeom/UniformSpacingLayoutLineFactory.h>
#include <CoordGeom/CompositeGirderLineFactory.h>
#include <CoordGeom/CompositeLayoutLineFactory.h>
#include <CoordGeom/EqualSpacingDiaphragmLineFactory.h>
#include <CoordGeom/SingleDiaphragmLineFactory.h>
#include <CoordGeom/ThroughPointDiaphragmLineFactory.h>
#include <CoordGeom/CompositeDiaphragmLineFactory.h>
#include <CoordGeom/SimpleDeckBoundaryFactory.h>
#include <CoordGeom/SinglePierLineFactory.h>
#include <CoordGeom/CompositePierLineFactory.h>

#include <MathEx.h>

#include <iostream>
#include <iomanip>

using namespace WBFL::COGO;

constexpr IDType g_AlignmentID = 999;

CTestBridgeFramingGeometry::CTestBridgeFramingGeometry()
{
}

bool CTestBridgeFramingGeometry::Test(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestBridgeGeometry::Test");
   TRY_TESTME(Test1(rlog));
   TRY_TESTME(Test2(rlog));
   TRY_TESTME(Test3(rlog));
   TRY_TESTME(Test4(rlog));
   TRY_TESTME(Test5(rlog));
   TESTME_EPILOG("CTestBridgeGeometry::Test");
}

std::shared_ptr<WBFL::COGO::Alignment> CTestBridgeFramingGeometry::CreateStraightAlignment(Float64 refStation, Float64 x, Float64 y, Float64 direction)
{
   auto alignment = Alignment::Create();

   Float64 segment_length = 100;
   auto path_segment = PathSegment::Create(WBFL::Geometry::Point2d(x, y), WBFL::Geometry::Size2d(segment_length * cos(direction), segment_length * sin(direction)));

   alignment->AddPathElement(path_segment);
   alignment->SetReferenceStation(refStation);

   return alignment;
}

std::shared_ptr<WBFL::COGO::BridgeFramingGeometry> CTestBridgeFramingGeometry::CreateBridgeGeometry(const std::vector<std::tuple<IDType,Float64,std::_tstring,ConnectionGeometry,ConnectionGeometry>>& piers,bool bContinuousGirders)
{
   // create the alignment
   auto alignment = CreateStraightAlignment(0.00, 10.0, 10.0, M_PI / 4);

   // create the blank bridge geometry and associate it with the alignment
   auto bridge = BridgeFramingGeometry::Create(g_AlignmentID, alignment);

   // build the model
   Float64 pier_length = 20;

   for (const auto& pier : piers)
   {
      IDType id;
      Float64 station;
      std::_tstring direction;
      ConnectionGeometry back, ahead;
      std::tie(id, station, direction, back, ahead) = pier;
      auto single_pier_line_factory = std::make_shared<SinglePierLineFactory>(id, g_AlignmentID, station, direction, pier_length, pier_length / 2, back, ahead);
      bridge->AddPierLineFactory(single_pier_line_factory);
   }

   // create a girder layout line
   // layout line is parallel to and offset from the alignment
   auto layout_line_factory = std::make_shared<AlignmentOffsetLayoutLineFactory>();
   layout_line_factory->SetAlignmentID(g_AlignmentID);
   layout_line_factory->SetLayoutLineID(100);
   layout_line_factory->SetLayoutLineIDIncrement(1);
   layout_line_factory->SetLayoutLineCount(5); // create 5 layout lines
   layout_line_factory->SetOffset(-10.0); // offset from alignment (10 ft left)
   layout_line_factory->SetOffsetIncrement(5.0); // each subsequent layout line is 5 ft to the right of the previous
   bridge->AddLayoutLineFactory(layout_line_factory);

   // Create girder lines
   auto girder_line_factory = std::make_shared<SimpleGirderLineFactory>();
   girder_line_factory->SetGirderLineID(500); // left most girder line has ID 500
   girder_line_factory->SetGirderLineIDIncrement(1); // girder line ID increments by 1
   girder_line_factory->SetLayoutLineID(SideType::Left, 100); // layout line used to locate the left girder line
   girder_line_factory->SetLayoutLineID(SideType::Right, 104); // layout line used to location the right girder line
   girder_line_factory->SetLayoutLineIDIncrement(1);
   girder_line_factory->SetGirderLineType(GirderLineType::Chord); // layout as a chord
   girder_line_factory->SetPierID(EndType::Start, std::get<0>(piers.front())); // layout between first and last piers
   girder_line_factory->SetPierID(EndType::End, std::get<0>(piers.back()));
   girder_line_factory->SetPierIDIncrement(100);
   girder_line_factory->IsContinuous(bContinuousGirders);
   bridge->AddGirderLineFactory(girder_line_factory);

   return bridge;
}

bool CTestBridgeFramingGeometry::Test1(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestBridgeGeometry::Test1");

   std::vector<std::tuple<IDType, Float64, std::_tstring,ConnectionGeometry,ConnectionGeometry>> piers;
   ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
   piers.emplace_back(100, 100.0, _T("N 45 W"),ConnectionGeometry(),connection_geometry);
   piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());
   auto bridge = CTestBridgeFramingGeometry::CreateBridgeGeometry(piers,true);

   TRY_TESTME(bridge->GetGirderLineCount() == 5);

   auto pier1 = bridge->FindPierLine(100);
   auto pier2 = bridge->FindPierLine(200);

   TRY_TESTME(pier1->GetAlignmentPoint() == WBFL::Geometry::Point2d( 80.710678,  80.710678));
   TRY_TESTME(pier2->GetAlignmentPoint() == WBFL::Geometry::Point2d(151.421356, 151.421356));

   TRY_TESTME(pier1->GetDirection() == Direction(3 * M_PI / 4));
   TRY_TESTME(pier2->GetDirection() == Direction(3 * M_PI / 4));

   auto girder_line = bridge->FindGirderLine(502);

   TRY_TESTME(IsEqual(girder_line->GetLayoutLength(), 100.0));
   TRY_TESTME(girder_line->GetPierPoint(EndType::Start) == WBFL::Geometry::Point2d( 80.710678,  80.710678));
   TRY_TESTME(girder_line->GetPierPoint(EndType::End)   == WBFL::Geometry::Point2d(151.421356, 151.421356));

   TRY_TESTME(girder_line->GetBearingPoint(EndType::Start) == WBFL::Geometry::Point2d(80.710678 + 2.5 * cos(M_PI / 4), 80.710678 + 2.5 * sin(M_PI / 4)));
   TRY_TESTME(girder_line->GetBearingPoint(EndType::End) == WBFL::Geometry::Point2d(151.421356 - 2.5 * cos(M_PI / 4), 151.421356 - 2.5 * cos(M_PI / 4)));

   TRY_TESTME(girder_line->GetEndPoint(EndType::Start) == WBFL::Geometry::Point2d(80.710678 + 1.5 * cos(M_PI / 4), 80.710678 + 1.5 * sin(M_PI / 4)));
   TRY_TESTME(girder_line->GetEndPoint(EndType::End) == WBFL::Geometry::Point2d(151.421356 - 1.5 * cos(M_PI / 4), 151.421356 - 1.5 * cos(M_PI / 4)));

   TESTME_EPILOG("CTestBridgeGeometry::Test1");
}

bool CTestBridgeFramingGeometry::Test2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestBridgeGeometry::Test2");

   std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
   ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
   piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
   piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, connection_geometry);
   piers.emplace_back(300, 300.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());
   auto bridge = CTestBridgeFramingGeometry::CreateBridgeGeometry(piers, false);

   TRY_TESTME(bridge->GetGirderLineCount() == 10);

   TESTME_EPILOG("CTestBridgeGeometry::Test2");
}

bool CTestBridgeFramingGeometry::Test3(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestBridgeGeometry::Test3");

   std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
   ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
   piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
   piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, connection_geometry);
   piers.emplace_back(300, 300.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());

   // create the alignment
   auto alignment = CreateStraightAlignment(0.00, 10.0, 10.0, M_PI / 4);

   // create the blank bridge geometry and associate it with the alignment
   auto bridge = BridgeFramingGeometry::Create(g_AlignmentID, alignment);

   // build the model
   Float64 pier_length = 20;

   for (const auto& pier : piers)
   {
      IDType id;
      Float64 station;
      std::_tstring direction;
      ConnectionGeometry back, ahead;
      std::tie(id, station, direction, back, ahead) = pier;
      auto single_pier_line_factory = std::make_shared<SinglePierLineFactory>(id, g_AlignmentID, station, direction, pier_length, pier_length / 2, back, ahead);
      bridge->AddPierLineFactory(single_pier_line_factory);
   }

   // create a girder layout line

   // Girder spacing in span 1 (4 girders = 3 spaces)
   // Girder spacing in span 2 (5 girders = 4 spaces)
   std::vector<Float64> span_1_spacing{ 6.0,6.0,6.0 };
   std::vector<Float64> span_2_spacing{ 6.0,6.0,6.0,6.0 };

   auto layout_line_factory_span_1 = std::make_shared<UniformSpacingLayoutLineFactory>(); // creates layout lines 100, 101, 102, 103
   layout_line_factory_span_1->SetAlignmentID(g_AlignmentID);
   layout_line_factory_span_1->SetStartPierLineID(100);
   layout_line_factory_span_1->SetEndPierLineID(200);
   layout_line_factory_span_1->SetPierLineIDIncrement(100);
   layout_line_factory_span_1->SetStartSpacingOffset(-12.0);
   layout_line_factory_span_1->SetEndSpacingOffset(-12.0);
   layout_line_factory_span_1->SetStartSpacing(span_1_spacing);
   layout_line_factory_span_1->SetEndSpacing(span_1_spacing);
   layout_line_factory_span_1->SetLayoutLineID(100);
   bridge->AddLayoutLineFactory(layout_line_factory_span_1);

   auto layout_line_factory_span_2 = std::make_shared<UniformSpacingLayoutLineFactory>(); // creates layout lines 200, 201, 202, 203, 204
   layout_line_factory_span_2->SetAlignmentID(g_AlignmentID);
   layout_line_factory_span_2->SetStartPierLineID(200);
   layout_line_factory_span_2->SetEndPierLineID(300);
   layout_line_factory_span_2->SetPierLineIDIncrement(100);
   layout_line_factory_span_2->SetStartSpacingOffset(-12.0);
   layout_line_factory_span_2->SetEndSpacingOffset(-12.0);
   layout_line_factory_span_2->SetStartSpacing(span_2_spacing);
   layout_line_factory_span_2->SetEndSpacing(span_2_spacing);
   layout_line_factory_span_2->SetLayoutLineID(200);
   bridge->AddLayoutLineFactory(layout_line_factory_span_2);

   // Span 1
   auto girder_line_factory_span_1 = std::make_shared<SimpleGirderLineFactory>();
   girder_line_factory_span_1->SetGirderLineID(100);
   girder_line_factory_span_1->SetGirderLineIDIncrement(1);
   girder_line_factory_span_1->SetLayoutLineID(SideType::Left, 100); // layout line used to locate the left girder line
   girder_line_factory_span_1->SetLayoutLineID(SideType::Right, 103); // layout line used to location the right girder line
   girder_line_factory_span_1->SetLayoutLineIDIncrement(1);
   girder_line_factory_span_1->SetGirderLineType(GirderLineType::Chord); // layout as a chord
   girder_line_factory_span_1->SetPierID(EndType::Start,100); // layout between first and last piers
   girder_line_factory_span_1->SetPierID(EndType::End, 200);
   girder_line_factory_span_1->SetPierIDIncrement(100);
   girder_line_factory_span_1->IsContinuous(false);
   bridge->AddGirderLineFactory(girder_line_factory_span_1);

   // Span 2
   auto girder_line_factory_span_2 = std::make_shared<SimpleGirderLineFactory>();
   girder_line_factory_span_2->SetGirderLineID(200);
   girder_line_factory_span_2->SetGirderLineIDIncrement(1);
   girder_line_factory_span_2->SetLayoutLineID(SideType::Left, 200); // layout line used to locate the left girder line
   girder_line_factory_span_2->SetLayoutLineID(SideType::Right, 204); // layout line used to location the right girder line
   girder_line_factory_span_2->SetLayoutLineIDIncrement(1);
   girder_line_factory_span_2->SetGirderLineType(GirderLineType::Chord); // layout as a chord
   girder_line_factory_span_2->SetPierID(EndType::Start, 200); // layout between first and last piers
   girder_line_factory_span_2->SetPierID(EndType::End, 300);
   girder_line_factory_span_2->SetPierIDIncrement(100);
   girder_line_factory_span_2->IsContinuous(false);
   bridge->AddGirderLineFactory(girder_line_factory_span_2);

   TRY_TESTME(bridge->GetGirderLineCount() == 9);

   TESTME_EPILOG("CTestBridgeGeometry::Test3");
}

bool CTestBridgeFramingGeometry::Test4(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestBridgeGeometry::Test4");

   std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
   ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
   piers.emplace_back(100, 100.0, _T("N 45 W"), ConnectionGeometry(), connection_geometry);
   piers.emplace_back(200, 200.0, _T("NORMAL"), connection_geometry, connection_geometry);
   piers.emplace_back(300, 300.0, _T("NORMAL"), connection_geometry, ConnectionGeometry());

   auto bridge = CreateBridgeGeometry(piers, false);

   auto span_1_diaphragm_line_factory = std::make_shared<EqualSpacingDiaphragmLineFactory>();
   span_1_diaphragm_line_factory->SetAlignmentID(g_AlignmentID);
   span_1_diaphragm_line_factory->SetStationRange(100.0, 200.0);
   span_1_diaphragm_line_factory->SetDiaphragmLineID(0);
   span_1_diaphragm_line_factory->SetDiaphragmLineIDIncrement(1);
   span_1_diaphragm_line_factory->SetGirderLineID(SideType::Left, 500);
   span_1_diaphragm_line_factory->SetGirderLineID(SideType::Right, 504);
   span_1_diaphragm_line_factory->SetDivisor(4);
   span_1_diaphragm_line_factory->IsStaggered(true);
   bridge->AddDiaphragmLineFactory(span_1_diaphragm_line_factory);

   auto span_2_diaphragm_line_factory = std::make_shared<SingleDiaphragmLineFactory>();
   span_2_diaphragm_line_factory->SetAlignmentID(g_AlignmentID);
   span_2_diaphragm_line_factory->SetStation(250); // middle of span 2, 2+50
   span_2_diaphragm_line_factory->SetOrientation(_T("45 L"));
   span_2_diaphragm_line_factory->SetDiaphragmLineID(4);
   span_2_diaphragm_line_factory->SetGirderLineID(SideType::Left, 505);
   span_2_diaphragm_line_factory->SetGirderLineID(SideType::Right, 509);
   span_2_diaphragm_line_factory->IsStaggered(true);
   bridge->AddDiaphragmLineFactory(span_2_diaphragm_line_factory);

   auto pier_2_diaphragm_line_factory = std::make_shared<ThroughPointDiaphragmLineFactory>();
   pier_2_diaphragm_line_factory->SetPoint({ 151.421, 151.421 }); // Pier 2 at Station 2+00
   pier_2_diaphragm_line_factory->SetDirection(0.0);
   pier_2_diaphragm_line_factory->SetDiaphragmLineID(5);
   pier_2_diaphragm_line_factory->SetGirderLineID(SideType::Left, 505);
   pier_2_diaphragm_line_factory->SetGirderLineID(SideType::Right, 509);
   pier_2_diaphragm_line_factory->IsStaggered(true);
   bridge->AddDiaphragmLineFactory(pier_2_diaphragm_line_factory);

   using namespace WBFL::Geometry;
   using DiaphragmBay = std::array<std::pair<WBFL::Geometry::Point2d, WBFL::Geometry::Point2d>, 3>; // 3 lines of diaphragms in each bay
   using DiaphragmBays = std::array<DiaphragmBay, 4>; // 4 bays between 5 girders in span 1

   DiaphragmBay bay1 // Bay between 500 and 501
   {
      std::make_pair(Point2d(91.31727984, 105.4594155), Point2d(94.85281374, 101.9238816)), // Diaphragm line 0
      std::make_pair(Point2d(108.9949494, 123.137085), Point2d(112.5304833, 119.6015511)), // Diaphragm line 1
      std::make_pair(Point2d(126.6726189, 140.8147545), Point2d(130.2081528, 137.2792206)) // Diaphragm line 2
   };

   DiaphragmBay bay2 // Bay between 501 and 502
   {
      std::make_pair(Point2d(94.85281374, 101.9238816), Point2d(98.38834765, 98.38834765)), // Diaphragm line 0
      std::make_pair(Point2d(112.5304833, 119.6015511), Point2d(116.0660172, 116.0660172)), // Diaphragm line 1
      std::make_pair(Point2d(130.2081528, 137.2792206), Point2d(133.7436867, 133.7436867)) // Diaphragm line 2
   };

   DiaphragmBay bay3 // Bay between 502 and 503
   {
      std::make_pair(Point2d(98.38834765, 98.38834765), Point2d(101.9238816, 94.85281374)), // Diaphragm line 0
      std::make_pair(Point2d(116.0660172, 116.0660172), Point2d(119.6015511, 112.5304833)), // Diaphragm line 1
      std::make_pair(Point2d(133.7436867, 133.7436867), Point2d(137.2792206, 130.2081528)) // Diaphragm line 2
   };

   DiaphragmBay bay4 // Bay between 503 and 504
   {
      std::make_pair(Point2d(101.9238816, 94.85281374), Point2d(105.4594155, 91.31727984)), // Diaphragm line 0
      std::make_pair(Point2d(119.6015511, 112.5304833), Point2d(123.137085, 108.9949494)), // Diaphragm line 1
      std::make_pair(Point2d(137.2792206, 130.2081528), Point2d(140.8147545, 126.6726189)) // Diaphragm line 2
   };

   DiaphragmBays span_1_expected_results
   {
      bay1, bay2, bay3, bay4
   };

   IndexType nDiaphragmLines = bridge->GetDiaphragmLineCount();
   TRY_TESTME(nDiaphragmLines == 5); // 3 in span 1 and 1 in spans 2 and 3
   for (IDType gdrID = 500; gdrID < 504; gdrID++)
   {
      for (IndexType i = 0; i < 3; i++) // there are only 3 in span 1
      {
         auto diaphragm_line = bridge->GetDiaphragmLine(i);
         TRY_TESTME(diaphragm_line->GetID() == (IDType)i);

         auto length = diaphragm_line->Length(gdrID);
         TRY_TESTME(IsEqual(length, 5.0));

         const auto& start_point = diaphragm_line->GetPoint(gdrID, EndType::Start);
         const auto& end_point = diaphragm_line->GetPoint(gdrID, EndType::End);

         const auto& expected_start_point(span_1_expected_results[gdrID - 500][i].first);
         const auto& expected_end_point(span_1_expected_results[gdrID - 500][i].second);

         TRY_TESTME(start_point == expected_start_point);
         TRY_TESTME(end_point == expected_end_point);
      }
   }

   std::array<std::pair<Point2d, Point2d>, 4> span_2_expected_results
   {
      std::make_pair(Point2d(174.4023266, 188.5444622), Point2d(177.9378605, 185.0089283)), // Bay between 505 and 506
      std::make_pair(Point2d(180.589511, 187.6605788), Point2d(184.1250449, 184.1250449)), // Bay between 506 and 507
      std::make_pair(Point2d(187.218637, 187.218637), Point2d(190.7541709, 183.6831031)), // Bay between 507 and 508
      std::make_pair(Point2d(194.068734, 186.9976662), Point2d(197.6042679, 183.4621323)) // Bay between 508 and 509
   };

   auto diaphragm_line = bridge->FindDiaphragmLine(4);
   for (IDType gdrID = 505; gdrID < 509; gdrID++)
   {
      auto length = diaphragm_line->Length(gdrID);
      TRY_TESTME(IsEqual(length, 5.0));

      const auto& start_point = diaphragm_line->GetPoint(gdrID, EndType::Start);
      const auto& end_point = diaphragm_line->GetPoint(gdrID, EndType::End);

      const auto& expected_start_point(span_2_expected_results[gdrID - 505].first);
      const auto& expected_end_point(span_2_expected_results[gdrID - 505].second);

      TRY_TESTME(start_point == expected_start_point);
      TRY_TESTME(end_point == expected_end_point);
   }


   std::array<std::pair<Point2d, Point2d>, 4> pier_2_expected_results
   {
      std::make_pair(Point2d(139.0466313, 153.188767), Point2d(142.5821652, 149.653233)), // Bay between 505 and 506
      std::make_pair(Point2d(145.2338157, 152.3048835), Point2d(148.7693496, 148.7693496)), // Bay between 506 and 507
      std::make_pair(Point2d(151.8629417, 151.8629417), Point2d(155.3984756, 148.3274078)), // Bay between 507 and 508
      std::make_pair(Point2d(158.7130387, 151.6419709), Point2d(162.2485726, 148.106437)) // Bay between 508 and 509
   };

   diaphragm_line = bridge->FindDiaphragmLine(5);
   for (IDType gdrID = 505; gdrID < 509; gdrID++)
   {
      auto length = diaphragm_line->Length(gdrID);
      TRY_TESTME(IsEqual(length, 5.0));

      const auto& start_point = diaphragm_line->GetPoint(gdrID, EndType::Start);
      const auto& end_point = diaphragm_line->GetPoint(gdrID, EndType::End);

      const auto& expected_start_point(pier_2_expected_results[gdrID - 505].first);
      const auto& expected_end_point(pier_2_expected_results[gdrID - 505].second);

      TRY_TESTME(start_point == expected_start_point);
      TRY_TESTME(end_point == expected_end_point);
   }
   TESTME_EPILOG("CTestBridgeGeometry::Test4");
}

bool CTestBridgeFramingGeometry::Test5(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CTestBridgeGeometry::Test5");

   std::vector<std::tuple<IDType, Float64, std::_tstring, ConnectionGeometry, ConnectionGeometry>> piers;
   ConnectionGeometry connection_geometry{ 2.5,MeasurementType::NormalToItem,1.0,MeasurementType::NormalToItem,MeasurementLocation::CenterlineBearing };
   piers.emplace_back(100, 100.0, _T("45 L"), ConnectionGeometry(), connection_geometry);
   piers.emplace_back(200, 200.0, _T("45 L"), connection_geometry, connection_geometry);
   piers.emplace_back(300, 300.0, _T("45 L"), connection_geometry, ConnectionGeometry());

   auto bridge = CreateBridgeGeometry(piers, false);

   // Create some layout lines to defined the slab edge paths
   auto deck_edge_layout_line_factory = std::make_shared<AlignmentOffsetLayoutLineFactory>();
   deck_edge_layout_line_factory->SetAlignmentID(g_AlignmentID);
   deck_edge_layout_line_factory->SetLayoutLineID(1000); // left edge = 1000, right edge = 2000
   deck_edge_layout_line_factory->SetLayoutLineIDIncrement(1000);
   deck_edge_layout_line_factory->SetLayoutLineCount(2);
   deck_edge_layout_line_factory->SetOffset(-12);
   deck_edge_layout_line_factory->SetOffsetIncrement(24);
   bridge->AddLayoutLineFactory(deck_edge_layout_line_factory);

   // Create layout lines for the break lines
   auto break_line_layout_line_factory = std::make_shared<AlignmentOffsetLayoutLineFactory>(*deck_edge_layout_line_factory);
   break_line_layout_line_factory->SetLayoutLineID(1001); // left break like = 1001, right bream like = 2001
   break_line_layout_line_factory->SetOffset(-10);
   break_line_layout_line_factory->SetOffsetIncrement(20);
   bridge->AddLayoutLineFactory(break_line_layout_line_factory);


   auto deck_boundary_factory = std::make_shared<SimpleDeckBoundaryFactory>();
   deck_boundary_factory->SetTransverseEdgeID(EndType::Start, 100); // use pier 1 (ID=100) for back edge transverse slab line
   deck_boundary_factory->SetTransverseEdgeType(EndType::Start,TransverseEdgeType::Pier);
   deck_boundary_factory->SetTransverseEdgeID(EndType::End,300); // use pier 3 (ID=300) for forward edge transverse slab line
   deck_boundary_factory->SetTransverseEdgeType(EndType::End, TransverseEdgeType::Pier);
   deck_boundary_factory->SetEdgeID(SideType::Left,1000); // left edge of slab (layout line 1000)
   deck_boundary_factory->SetEdgeID(SideType::Right,2000); // right edge of slab (layout line 2000)

   // break slab at all four corners
   deck_boundary_factory->SetBreakEdge(EndType::Start,SideType::Left,true);
   deck_boundary_factory->SetBreakEdge(EndType::End, SideType::Left, true);
   deck_boundary_factory->SetBreakEdge(EndType::Start, SideType::Right, true);
   deck_boundary_factory->SetBreakEdge(EndType::End, SideType::Right, true);
   deck_boundary_factory->SetEdgeBreakID(SideType::Left, 1001);
   deck_boundary_factory->SetEdgeBreakID(SideType::Right, 2001);

   bridge->SetDeckBoundaryFactory(deck_boundary_factory);

   auto deck_boundary = bridge->GetDeckBoundary();
   auto points = deck_boundary->GetPerimeter(10); // 10 points per side, plus control points
   TRY_TESTME(points.size() == 26);

   std::array<WBFL::Geometry::Point2d, 26> expected_points
   {
      WBFL::Geometry::Point2d(65.15432893, 82.12489168),
      WBFL::Geometry::Point2d(66.56854249, 80.71067812),
      WBFL::Geometry::Point2d(94.85281374, 80.71067812),
      WBFL::Geometry::Point2d(96.2670273, 79.29646456),
      WBFL::Geometry::Point2d(111.9805113, 95.00994858),
      WBFL::Geometry::Point2d(127.6939954, 110.7234326),
      WBFL::Geometry::Point2d(143.4074794, 126.4369166),
      WBFL::Geometry::Point2d(159.1209634, 142.1504007),
      WBFL::Geometry::Point2d(174.8344474, 157.8638847),
      WBFL::Geometry::Point2d(190.5479315, 173.5773687),
      WBFL::Geometry::Point2d(206.2614155, 189.2908527),
      WBFL::Geometry::Point2d(221.9748995, 205.0043368),
      WBFL::Geometry::Point2d(237.6883835, 220.7178208),
      WBFL::Geometry::Point2d(236.27417, 222.1320344),
      WBFL::Geometry::Point2d(207.9898987, 222.1320344),
      WBFL::Geometry::Point2d(206.5756852, 223.5462479),
      WBFL::Geometry::Point2d(190.8622011, 207.8327639),
      WBFL::Geometry::Point2d(175.1487171, 192.1192799),
      WBFL::Geometry::Point2d(159.4352331, 176.4057958),
      WBFL::Geometry::Point2d(143.7217491, 160.6923118),
      WBFL::Geometry::Point2d(128.008265, 144.9788278),
      WBFL::Geometry::Point2d(112.294781, 129.2653438),
      WBFL::Geometry::Point2d(96.58129699, 113.5518597),
      WBFL::Geometry::Point2d(80.86781296, 97.83837571),
      WBFL::Geometry::Point2d(72.22539674, 89.19595949),
      WBFL::Geometry::Point2d(65.15432893, 82.12489168)
   };

   int i = 0;
   for(const auto& point : points)
   {
      const auto& expected_point = expected_points[i++];
      TRY_TESTME(point == expected_point);
      //std::_tcout << point.X() << _T(", ") << point.Y() << std::endl;
   }

   TESTME_EPILOG("CTestBridgeGeometry::Test5");
}
