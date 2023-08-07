///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestBridgeGeometry.cpp: implementation of the CTestBridgeFramingGeometry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBridgeGeometry.h"
#include <array>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

constexpr IDType g_AlignmentID = 999;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestBridgeFramingGeometry::CTestBridgeFramingGeometry()
{

}

void CTestBridgeFramingGeometry::Test()
{
   Test1();
   Test2();
   Test3();
   Test4();
   Test5();
}

HRESULT CreateStraightAlignment(Float64 refStation, Float64 x, Float64 y, Float64 direction, IAlignment** ppAlignment)
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   Float64 segment_length = 100.0;
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(x, y);
   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(x + segment_length * cos(direction), y + segment_length * sin(direction));
   CComPtr<IPathSegment> path_segment;
   path_segment.CoCreateInstance(CLSID_PathSegment);
   path_segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(path_segment);
   alignment->AddPathElement(element);
   return alignment.CopyTo(ppAlignment);
}

HRESULT CreateBridgeGeometry(const std::vector<std::tuple<IDType,Float64,BSTR>>& vPiers,VARIANT_BOOL bContinuous, IBridgeGeometry** ppBridge)
{
   CComPtr<IAlignment> alignment;
   CreateStraightAlignment(0, 10, 10, M_PI / 4, &alignment);

   CComPtr<IBridgeGeometry> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_BridgeGeometry), S_OK);

   bridge->AddAlignment(g_AlignmentID, alignment);
   bridge->put_BridgeAlignmentID(g_AlignmentID);

   Float64 pier_length = 20;

   for (const auto& pier : vPiers)
   {
      auto [id, station, strDirection] = pier;

      CComPtr<ISinglePierLineFactory> factory;
      TRY_TEST(factory.CoCreateInstance(CLSID_SinglePierLineFactory), S_OK);
      factory->put_PierLineID(id);
      factory->put_AlignmentID(g_AlignmentID);
      factory->put_Station(CComVariant(station));
      factory->put_Direction(strDirection);
      factory->put_Length(pier_length);
      factory->put_Offset(pier_length / 2);
      factory->put_BearingOffset(pfBack,2.5);
      factory->put_BearingOffsetMeasurementType(pfBack, mtNormal);
      factory->put_BearingOffset(pfAhead, 2.5);
      factory->put_BearingOffsetMeasurementType(pfAhead, mtNormal);
      factory->put_EndDistance(pfBack, 1.0);
      factory->put_EndDistanceMeasurementType(pfBack, mtNormal);
      factory->put_EndDistanceMeasurementLocation(pfBack, mlCenterlineBearing);
      factory->put_EndDistance(pfAhead, 1.0);
      factory->put_EndDistanceMeasurementType(pfAhead, mtNormal);
      factory->put_EndDistanceMeasurementLocation(pfAhead, mlCenterlineBearing);

      bridge->AddPierLineFactory(factory);
   }

   CComPtr<IAlignmentOffsetLayoutLineFactory> layout_line_factory;
   TRY_TEST(layout_line_factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory), S_OK);
   layout_line_factory->put_AlignmentID(g_AlignmentID);
   layout_line_factory->put_LayoutLineID(100);
   layout_line_factory->put_LayoutLineIDIncrement(1);
   layout_line_factory->put_LayoutLineCount(5);
   layout_line_factory->put_Offset(-10.0);
   layout_line_factory->put_OffsetIncrement(5);
   bridge->AddLayoutLineFactory(layout_line_factory);

   CComPtr<ISimpleGirderLineFactory> girder_line_factory;
   TRY_TEST(girder_line_factory.CoCreateInstance(CLSID_SimpleGirderLineFactory), S_OK);
   girder_line_factory->put_GirderLineID(500);
   girder_line_factory->put_GirderLineIDInc(1);
   girder_line_factory->put_LeftLayoutLineID(100);
   girder_line_factory->put_RightLayoutLineID(104);
   girder_line_factory->put_LayoutLineIDInc(1);
   girder_line_factory->put_Type(glChord);
   girder_line_factory->put_StartPierID(std::get<0>(vPiers.front()));
   girder_line_factory->put_EndPierID(std::get<0>(vPiers.back()));
   girder_line_factory->put_PierIDInc(100);
   girder_line_factory->put_Continuous(bContinuous);
   bridge->AddGirderLineFactory(girder_line_factory);

   return bridge.CopyTo(ppBridge);
}

bool TestPoint(IPoint2d* pPoint, Float64 x, Float64 y)
{
   Float64 _x, _y;
   pPoint->Location(&_x, &_y);
   return IsEqual(_x, x) && IsEqual(_y, y);
}

bool TestDirection(IDirection* pDirection, Float64 direction)
{
   Float64 value;
   pDirection->get_Value(&value);
   return IsEqual(value, direction);
}

void CTestBridgeFramingGeometry::Test1()
{
   std::vector<std::tuple<IDType, Float64, BSTR>> piers;
   piers.emplace_back(100, 100.0, CComBSTR("N 45 W"));
   piers.emplace_back(200, 200.0, CComBSTR("NORMAL"));
   CComPtr<IBridgeGeometry> bridge;
   CreateBridgeGeometry(piers, VARIANT_TRUE, &bridge);

   IndexType nGirderLines;
   bridge->get_GirderLineCount(&nGirderLines);
   TRY_TEST(nGirderLines, 5);

   CComPtr<IPierLine> pier1, pier2;
   TRY_TEST(bridge->FindPierLine(100, &pier1), S_OK);
   TRY_TEST(bridge->FindPierLine(200, &pier2), S_OK);

   CComPtr<IPoint2d> point;
   pier1->get_AlignmentPoint(&point);
   TRY_TEST(TestPoint(point, 80.710678, 80.710678), true);

   point.Release();
   pier2->get_AlignmentPoint(&point);
   TRY_TEST(TestPoint(point, 151.421356, 151.421356), true);

   CComPtr<IDirection> direction;
   pier1->get_Direction(&direction);
   TRY_TEST(TestDirection(direction, 3 * M_PI / 4), true);
   direction.Release();
   pier2->get_Direction(&direction);
   TRY_TEST(TestDirection(direction, 3 * M_PI / 4), true);

   CComPtr<IGirderLine> girder_line;
   bridge->FindGirderLine(502,&girder_line);
   Float64 length;
   girder_line->get_LayoutLength(&length);
   TRY_TEST(IsEqual(length, 100.0), true);

   point.Release();
   girder_line->get_PierPoint(etStart, &point);
   TRY_TEST(TestPoint(point, 80.710678, 80.710678), true);
   point.Release();
   girder_line->get_PierPoint(etEnd, &point);
   TRY_TEST(TestPoint(point, 151.421356, 151.421356), true);

   point.Release();
   girder_line->get_BearingPoint(etStart, &point);
   TRY_TEST(TestPoint(point, 80.710678 + 2.5 * cos(M_PI / 4), 80.710678 + 2.5 * sin(M_PI / 4)), true);
   point.Release();
   girder_line->get_BearingPoint(etEnd, &point);
   TRY_TEST(TestPoint(point, 151.421356 - 2.5 * cos(M_PI / 4), 151.421356 - 2.5 * cos(M_PI / 4)), true);

   point.Release();
   girder_line->get_EndPoint(etStart, &point);
   TRY_TEST(TestPoint(point, 80.710678 + 1.5 * cos(M_PI / 4), 80.710678 + 1.5 * sin(M_PI / 4)), true);
   point.Release();
   girder_line->get_EndPoint(etEnd, &point);
   TRY_TEST(TestPoint(point, 151.421356 - 1.5 * cos(M_PI / 4), 151.421356 - 1.5 * cos(M_PI / 4)), true);
}

void CTestBridgeFramingGeometry::Test2()
{
   std::vector<std::tuple<IDType, Float64, BSTR>> piers;
   piers.emplace_back(100, 100.0, CComBSTR("N 45 W"));
   piers.emplace_back(200, 200.0, CComBSTR("NORMAL"));
   piers.emplace_back(300, 300.0, CComBSTR("NORMAL"));
   CComPtr<IBridgeGeometry> bridge;
   CreateBridgeGeometry(piers, VARIANT_FALSE, &bridge);

   IndexType nGirderLines;
   bridge->get_GirderLineCount(&nGirderLines);
   TRY_TEST(nGirderLines, 10);
}

void CTestBridgeFramingGeometry::Test3()
{
   CComPtr<IAlignment> alignment;
   CreateStraightAlignment(0.0, 10.0, 10.0, M_PI / 4, &alignment);

   CComPtr<IBridgeGeometry> bridge;
   TRY_TEST(bridge.CoCreateInstance(CLSID_BridgeGeometry), S_OK);

   bridge->AddAlignment(g_AlignmentID, alignment);
   bridge->put_BridgeAlignmentID(g_AlignmentID);

   std::vector<std::tuple<IDType, Float64, BSTR>> piers;
   piers.emplace_back(100, 100.0, CComBSTR("N 45 W"));
   piers.emplace_back(200, 200.0, CComBSTR("NORMAL"));
   piers.emplace_back(300, 300.0, CComBSTR("NORMAL"));

   Float64 pier_length = 20;

   for (const auto& pier : piers)
   {
      auto [id, station, direction] = pier;
      CComPtr<ISinglePierLineFactory> factory;
      TRY_TEST(factory.CoCreateInstance(CLSID_SinglePierLineFactory), S_OK);
      factory->put_PierLineID(id);
      factory->put_AlignmentID(g_AlignmentID);
      factory->put_Station(CComVariant(station));
      factory->put_Direction(direction);
      factory->put_Length(pier_length);
      factory->put_Offset(pier_length / 2);
      factory->put_BearingOffset(pfBack, 2.5);
      factory->put_BearingOffsetMeasurementType(pfBack, mtNormal);
      factory->put_BearingOffset(pfAhead, 2.5);
      factory->put_BearingOffsetMeasurementType(pfAhead, mtNormal);
      factory->put_EndDistance(pfBack, 1.0);
      factory->put_EndDistanceMeasurementType(pfBack, mtNormal);
      factory->put_EndDistanceMeasurementLocation(pfBack, mlPierLine);
      factory->put_EndDistance(pfAhead, 1.0);
      factory->put_EndDistanceMeasurementType(pfAhead, mtNormal);
      factory->put_EndDistanceMeasurementLocation(pfAhead, mlPierLine);
      bridge->AddPierLineFactory(factory);
   }

   // Girder spacing in span 1 (4 girders = 3 spaces)
   // Girder spacing in span 2 (5 girders = 4 spaces)
   CComPtr<IDblArray> span_1_spacing;
   span_1_spacing.CoCreateInstance(CLSID_DblArray);
   span_1_spacing->Add(6.0);
   span_1_spacing->Add(6.0);
   span_1_spacing->Add(6.0);

   CComPtr<IDblArray> span_2_spacing;
   span_2_spacing.CoCreateInstance(CLSID_DblArray);
   span_2_spacing->Add(6.0);
   span_2_spacing->Add(6.0);
   span_2_spacing->Add(6.0);
   span_2_spacing->Add(6.0);

   CComPtr<IUniformSpacingLayoutLineFactory> layout_line_factory_span_1;
   TRY_TEST(layout_line_factory_span_1.CoCreateInstance(CLSID_UniformSpacingLayoutLineFactory), S_OK);
   layout_line_factory_span_1->put_AlignmentID(g_AlignmentID);
   layout_line_factory_span_1->put_StartPierID(100);
   layout_line_factory_span_1->put_EndPierID(200);
   layout_line_factory_span_1->put_PierIDInc(100);
   layout_line_factory_span_1->put_StartSpacingOffset(-12.0);
   layout_line_factory_span_1->put_EndSpacingOffset(-12.0);
   layout_line_factory_span_1->put_StartSpacing(span_1_spacing);
   layout_line_factory_span_1->put_EndSpacing(span_1_spacing);
   layout_line_factory_span_1->put_LayoutLineID(100);
   bridge->AddLayoutLineFactory(layout_line_factory_span_1);

   CComPtr<IUniformSpacingLayoutLineFactory> layout_line_factory_span_2;
   TRY_TEST(layout_line_factory_span_2.CoCreateInstance(CLSID_UniformSpacingLayoutLineFactory), S_OK);
   layout_line_factory_span_2->put_AlignmentID(g_AlignmentID);
   layout_line_factory_span_2->put_StartPierID(200);
   layout_line_factory_span_2->put_EndPierID(300);
   layout_line_factory_span_2->put_PierIDInc(100);
   layout_line_factory_span_2->put_StartSpacingOffset(-12);
   layout_line_factory_span_2->put_EndSpacingOffset(-12);
   layout_line_factory_span_2->put_StartSpacing(span_2_spacing);
   layout_line_factory_span_2->put_EndSpacing(span_2_spacing);
   layout_line_factory_span_2->put_LayoutLineID(200);
   bridge->AddLayoutLineFactory(layout_line_factory_span_2);

   CComPtr<ISimpleGirderLineFactory> girder_line_factory_span_1;
   TRY_TEST(girder_line_factory_span_1.CoCreateInstance(CLSID_SimpleGirderLineFactory), S_OK);
   girder_line_factory_span_1->put_GirderLineID(100);
   girder_line_factory_span_1->put_GirderLineIDInc(1);
   girder_line_factory_span_1->put_LeftLayoutLineID(100);
   girder_line_factory_span_1->put_RightLayoutLineID(103);
   girder_line_factory_span_1->put_Type(glChord);
   girder_line_factory_span_1->put_StartPierID(100);
   girder_line_factory_span_1->put_EndPierID(200);
   girder_line_factory_span_1->put_PierIDInc(100);
   girder_line_factory_span_1->put_Continuous(VARIANT_FALSE);
   bridge->AddGirderLineFactory(girder_line_factory_span_1);

   CComPtr<ISimpleGirderLineFactory> girder_line_factory_span_2;
   TRY_TEST(girder_line_factory_span_2.CoCreateInstance(CLSID_SimpleGirderLineFactory), S_OK);
   girder_line_factory_span_2->put_GirderLineID(200);
   girder_line_factory_span_2->put_GirderLineIDInc(1);
   girder_line_factory_span_2->put_LeftLayoutLineID(200);
   girder_line_factory_span_2->put_RightLayoutLineID(204);
   girder_line_factory_span_2->put_Type(glChord);
   girder_line_factory_span_2->put_StartPierID(200);
   girder_line_factory_span_2->put_EndPierID(300);
   girder_line_factory_span_2->put_PierIDInc(100);
   girder_line_factory_span_2->put_Continuous(VARIANT_FALSE);
   bridge->AddGirderLineFactory(girder_line_factory_span_2);

   IndexType nGirderLines;
   bridge->get_GirderLineCount(&nGirderLines);
   TRY_TEST(nGirderLines, 9);
}

void CTestBridgeFramingGeometry::Test4()
{
   std::vector<std::tuple<IDType, Float64, BSTR>> piers;
   piers.emplace_back(100, 100.0, CComBSTR("N 45 W"));
   piers.emplace_back(200, 200.0, CComBSTR("NORMAL"));
   piers.emplace_back(300, 300.0, CComBSTR("NORMAL"));
   CComPtr<IBridgeGeometry> bridge;
   CreateBridgeGeometry(piers, VARIANT_FALSE, &bridge);

   CComPtr<IEqualSpacingDiaphragmLineFactory> span_1_diaphragm_line_factory;
   TRY_TEST(span_1_diaphragm_line_factory.CoCreateInstance(CLSID_EqualSpacingDiaphragmLineFactory), S_OK);
   span_1_diaphragm_line_factory->put_AlignmentID(g_AlignmentID);
   span_1_diaphragm_line_factory->SetStationRange(CComVariant(100.0), CComVariant(200.0));
   span_1_diaphragm_line_factory->put_DiaphragmLineID(0);
   span_1_diaphragm_line_factory->put_DiaphragmLineIDInc(1);
   span_1_diaphragm_line_factory->put_LeftGirderLineID(500);
   span_1_diaphragm_line_factory->put_RightGirderLineID(504);
   span_1_diaphragm_line_factory->put_Divisor(4);
   span_1_diaphragm_line_factory->put_Staggered(VARIANT_TRUE);
   bridge->AddDiaphragmLineFactory(span_1_diaphragm_line_factory);

   CComPtr<ISingleDiaphragmLineFactory> span_2_diaphragm_line_factory;
   TRY_TEST(span_2_diaphragm_line_factory.CoCreateInstance(CLSID_SingleDiaphragmLineFactory), S_OK);
   span_2_diaphragm_line_factory->put_AlignmentID(g_AlignmentID);
   span_2_diaphragm_line_factory->put_Station(CComVariant(250)); // 2+50, middle of span 2
   span_2_diaphragm_line_factory->put_Orientation(CComBSTR("45 L"));
   span_2_diaphragm_line_factory->put_DiaphragmLineID(4);
   span_2_diaphragm_line_factory->put_LeftGirderLineID(505);
   span_2_diaphragm_line_factory->put_RightGirderLineID(509);
   span_2_diaphragm_line_factory->put_Staggered(VARIANT_TRUE);
   bridge->AddDiaphragmLineFactory(span_2_diaphragm_line_factory);

   CComPtr<IThroughPointDiaphragmLineFactory> pier_2_diaphragm_line_factory;
   TRY_TEST(pier_2_diaphragm_line_factory.CoCreateInstance(CLSID_ThroughPointDiaphragmLineFactory), S_OK);
   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   point->Move(151.421, 151.421);
   pier_2_diaphragm_line_factory->put_Point(point);
   pier_2_diaphragm_line_factory->put_Direction(CComVariant(0.0));
   pier_2_diaphragm_line_factory->put_DiaphragmLineID(5);
   pier_2_diaphragm_line_factory->put_LeftGirderLineID(505);
   pier_2_diaphragm_line_factory->put_RightGirderLineID(509);
   pier_2_diaphragm_line_factory->put_Staggered(VARIANT_TRUE);
   bridge->AddDiaphragmLineFactory(pier_2_diaphragm_line_factory);


   using DiaphragmBay = std::array<std::pair<std::pair<Float64, Float64>, std::pair<Float64, Float64>>, 3>; // 3 lines of diaphragms in each bay
   using DiaphragmBays = std::array<DiaphragmBay, 4>; // 4 bays between 5 girders in span 1

   DiaphragmBay bay1 // Bay between 500 and 501
   {
      std::make_pair(std::make_pair(91.31727984, 105.4594155), std::make_pair(94.85281374, 101.9238816)), // Diaphragm line 0
      std::make_pair(std::make_pair(108.9949494, 123.137085), std::make_pair(112.5304833, 119.6015511)), // Diaphragm line 1
      std::make_pair(std::make_pair(126.6726189, 140.8147545), std::make_pair(130.2081528, 137.2792206)) // Diaphragm line 2
   };

   DiaphragmBay bay2 // Bay between 501 and 502
   {
      std::make_pair(std::make_pair(94.85281374, 101.9238816), std::make_pair(98.38834765, 98.38834765)), // Diaphragm line 0
      std::make_pair(std::make_pair(112.5304833, 119.6015511), std::make_pair(116.0660172, 116.0660172)), // Diaphragm line 1
      std::make_pair(std::make_pair(130.2081528, 137.2792206), std::make_pair(133.7436867, 133.7436867)) // Diaphragm line 2
   };

   DiaphragmBay bay3 // Bay between 502 and 503
   {
      std::make_pair(std::make_pair(98.38834765, 98.38834765), std::make_pair(101.9238816, 94.85281374)), // Diaphragm line 0
      std::make_pair(std::make_pair(116.0660172, 116.0660172), std::make_pair(119.6015511, 112.5304833)), // Diaphragm line 1
      std::make_pair(std::make_pair(133.7436867, 133.7436867), std::make_pair(137.2792206, 130.2081528)) // Diaphragm line 2
   };

   DiaphragmBay bay4 // Bay between 503 and 504
   {
      std::make_pair(std::make_pair(101.9238816, 94.85281374), std::make_pair(105.4594155, 91.31727984)), // Diaphragm line 0
      std::make_pair(std::make_pair(119.6015511, 112.5304833), std::make_pair(123.137085, 108.9949494)), // Diaphragm line 1
      std::make_pair(std::make_pair(137.2792206, 130.2081528), std::make_pair(140.8147545, 126.6726189)) // Diaphragm line 2
   };

   DiaphragmBays span_1_expected_results
   {
      bay1, bay2, bay3, bay4
   };

   IndexType nDiaphragmLines;
   bridge->get_DiaphragmLineCount(&nDiaphragmLines);
   TRY_TEST(nDiaphragmLines, 5); // 3 in span 1, and 1 in spans 2 and 3
   for (IDType gdrID = 500; gdrID < 504; gdrID++)
   {
      for (IndexType i = 0; i < 3; i++)
      {
         CComPtr<IDiaphragmLine> diaphragm_line;
         bridge->GetDiaphragmLine(i, &diaphragm_line);
         IDType id;
         diaphragm_line->get_ID(&id);
         TRY_TEST(id, (IDType)i);

         Float64 length;
         diaphragm_line->get_Length(gdrID, &length);
         TRY_TEST(IsEqual(length, 5.0), true);

         point.Release();
         diaphragm_line->get_Point(gdrID, etStart, &point);
         auto expected = span_1_expected_results[gdrID - 500][i].first;
         TRY_TEST(TestPoint(point, expected.first, expected.second), true);

         point.Release();
         diaphragm_line->get_Point(gdrID, etEnd, &point);
         expected = span_1_expected_results[gdrID - 500][i].second;
         TRY_TEST(TestPoint(point, expected.first, expected.second), true);
      }
   }


   std::array<std::pair<std::pair<Float64, Float64>, std::pair<Float64, Float64>>, 4> span_2_expected_results
   {
      std::make_pair(std::make_pair(174.4023266, 188.5444622), std::make_pair(177.9378605, 185.0089283)), // Bay between 505 and 506
      std::make_pair(std::make_pair(180.589511, 187.6605788), std::make_pair(184.1250449, 184.1250449)), // Bay between 506 and 507
      std::make_pair(std::make_pair(187.218637, 187.218637), std::make_pair(190.7541709, 183.6831031)), // Bay between 507 and 508
      std::make_pair(std::make_pair(194.068734, 186.9976662), std::make_pair(197.6042679, 183.4621323)) // Bay between 508 and 509
   };

   CComPtr<IDiaphragmLine> diaphragm_line;
   bridge->FindDiaphragmLine(4, &diaphragm_line);
   for (IDType gdrID = 505; gdrID < 509; gdrID++)
   {
      Float64 length;
      diaphragm_line->get_Length(gdrID, &length);
      TRY_TEST(IsEqual(length, 5.0), true);

      CComPtr<IPoint2d> point;
      diaphragm_line->get_Point(gdrID, etStart, &point);
      auto expected = span_2_expected_results[gdrID - 505].first;
      TRY_TEST(TestPoint(point, expected.first, expected.second), true);

      point.Release();
      diaphragm_line->get_Point(gdrID, etEnd, &point);
      expected = span_2_expected_results[gdrID - 505].second;
      TRY_TEST(TestPoint(point, expected.first, expected.second), true);
   }

   std::array<std::pair<std::pair<Float64, Float64>, std::pair<Float64, Float64>>, 4> pier_2_expected_results
   {
      std::make_pair(std::make_pair(139.0466313, 153.188767), std::make_pair(142.5821652, 149.653233)), // Bay between 505 and 506
      std::make_pair(std::make_pair(145.2338157, 152.3048835), std::make_pair(148.7693496, 148.7693496)), // Bay between 506 and 507
      std::make_pair(std::make_pair(151.8629417, 151.8629417), std::make_pair(155.3984756, 148.3274078)), // Bay between 507 and 508
      std::make_pair(std::make_pair(158.7130387, 151.6419709), std::make_pair(162.2485726, 148.106437)) // Bay between 508 and 509
   };
 
   diaphragm_line.Release();
   bridge->FindDiaphragmLine(5, &diaphragm_line);
   for (IDType gdrID = 505; gdrID < 509; gdrID++)
   {
      Float64 length;
      diaphragm_line->get_Length(gdrID, &length);
      TRY_TEST(IsEqual(length, 5.0), true);
   
      CComPtr<IPoint2d> point;
      diaphragm_line->get_Point(gdrID, etStart, &point);
      auto expected = pier_2_expected_results[gdrID - 505].first;
      TRY_TEST(TestPoint(point, expected.first, expected.second), true);

      point.Release();
      diaphragm_line->get_Point(gdrID, etEnd, &point);
      expected = pier_2_expected_results[gdrID - 505].second;
      TRY_TEST(TestPoint(point, expected.first, expected.second), true);
   }
}

void CTestBridgeFramingGeometry::Test5()
{
   std::vector<std::tuple<IDType, Float64, BSTR>> piers;
   piers.emplace_back(100, 100.0, CComBSTR("45 L"));
   piers.emplace_back(200, 200.0, CComBSTR("45 L"));
   piers.emplace_back(300, 300.0, CComBSTR("45 L"));
   CComPtr<IBridgeGeometry> bridge;
   CreateBridgeGeometry(piers, VARIANT_FALSE, &bridge);

   // Create some layout lines to define the slab edge paths
   CComPtr<IAlignmentOffsetLayoutLineFactory> deck_edge_layout_line_factory;
   TRY_TEST(deck_edge_layout_line_factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory), S_OK);
   deck_edge_layout_line_factory->put_AlignmentID(g_AlignmentID);
   deck_edge_layout_line_factory->put_LayoutLineID(1000); // left edge = 1000, right edge = 2000
   deck_edge_layout_line_factory->put_LayoutLineIDIncrement(1000);
   deck_edge_layout_line_factory->put_LayoutLineCount(2);
   deck_edge_layout_line_factory->put_Offset(-12.0);
   deck_edge_layout_line_factory->put_OffsetIncrement(24);
   bridge->AddLayoutLineFactory(deck_edge_layout_line_factory);

   // Create layout lines for the break lines
   CComPtr<IAlignmentOffsetLayoutLineFactory> break_line_layout_line_factory;
   TRY_TEST(break_line_layout_line_factory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory), S_OK);
   break_line_layout_line_factory->put_AlignmentID(g_AlignmentID);
   break_line_layout_line_factory->put_LayoutLineID(1001); // left edge = 1000, right edge = 2000
   break_line_layout_line_factory->put_LayoutLineIDIncrement(1000); // left break like = 1001, right bream like = 2001
   break_line_layout_line_factory->put_LayoutLineCount(2);
   break_line_layout_line_factory->put_Offset(-10.0);
   break_line_layout_line_factory->put_OffsetIncrement(20);
   bridge->AddLayoutLineFactory(break_line_layout_line_factory);

   CComPtr<ISimpleDeckBoundaryFactory> deck_boundary_factory;
   TRY_TEST(deck_boundary_factory.CoCreateInstance(CLSID_SimpleDeckBoundaryFactory), S_OK);
   deck_boundary_factory->put_TransverseEdgeID(etStart, 100); // use Pier 1 (ID=100) for the back edge transverse slab line
   deck_boundary_factory->put_TransverseEdgeType(etStart, setPier);
   deck_boundary_factory->put_TransverseEdgeID(etEnd, 300); // use Pier 3 (ID=300) for the forward edge transverse slab line
   deck_boundary_factory->put_TransverseEdgeType(etEnd, setPier);
   deck_boundary_factory->put_EdgeID(stLeft, 1000); // left edge of slab (layout line 1000)
   deck_boundary_factory->put_EdgeID(stRight, 2000); // right edge of slab (layout line 2000)

   // break slab at all four corners
   deck_boundary_factory->put_BreakEdge(etStart, stLeft, VARIANT_TRUE);
   deck_boundary_factory->put_BreakEdge(etEnd, stLeft, VARIANT_TRUE);
   deck_boundary_factory->put_BreakEdge(etStart, stRight, VARIANT_TRUE);
   deck_boundary_factory->put_BreakEdge(etEnd, stRight, VARIANT_TRUE);
   deck_boundary_factory->put_EdgeBreakID(stLeft, 1001);
   deck_boundary_factory->put_EdgeBreakID(stRight, 2001);
   
   bridge->AddDeckBoundaryFactory(deck_boundary_factory);

   CComPtr<IDeckBoundary> deck_boundary;
   TRY_TEST(bridge->get_DeckBoundary(&deck_boundary),S_OK);
   CComPtr<IPoint2dCollection> points;
   deck_boundary->get_Perimeter(10, &points);
   IndexType nPoints;
   points->get_Count(&nPoints);
   TRY_TEST(nPoints,26);

   std::array<std::pair<Float64,Float64>, 26> expected_points
   {
      std::make_pair(65.15432893, 82.12489168),
      std::make_pair(66.56854249, 80.71067812),
      std::make_pair(94.85281374, 80.71067812),
      std::make_pair(96.2670273, 79.29646456),
      std::make_pair(111.9805113, 95.00994858),
      std::make_pair(127.6939954, 110.7234326),
      std::make_pair(143.4074794, 126.4369166),
      std::make_pair(159.1209634, 142.1504007),
      std::make_pair(174.8344474, 157.8638847),
      std::make_pair(190.5479315, 173.5773687),
      std::make_pair(206.2614155, 189.2908527),
      std::make_pair(221.9748995, 205.0043368),
      std::make_pair(237.6883835, 220.7178208),
      std::make_pair(236.27417, 222.1320344),
      std::make_pair(207.9898987, 222.1320344),
      std::make_pair(206.5756852, 223.5462479),
      std::make_pair(190.8622011, 207.8327639),
      std::make_pair(175.1487171, 192.1192799),
      std::make_pair(159.4352331, 176.4057958),
      std::make_pair(143.7217491, 160.6923118),
      std::make_pair(128.008265, 144.9788278),
      std::make_pair(112.294781, 129.2653438),
      std::make_pair(96.58129699, 113.5518597),
      std::make_pair(80.86781296, 97.83837571),
      std::make_pair(72.22539674, 89.19595949),
      std::make_pair(65.15432893, 82.12489168)
   };

   for (IndexType i = 0; i < nPoints; i++)
   {
      CComPtr<IPoint2d> point;
      points->get_Item(i, &point);
      TRY_TEST(TestPoint(point, expected_points[i].first, expected_points[i].second), true);
   }
}


