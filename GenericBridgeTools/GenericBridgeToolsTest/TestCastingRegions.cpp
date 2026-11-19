///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestCastingRegions.cpp: implementation of the CTestCastingRegions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCastingRegions.h"

void CTestCastingRegions::Test()
{
   TestFindRegionExParallelToPiers();
}

void CTestCastingRegions::TestFindRegionExParallelToPiers()
{
   // Regression test for ICastingRegions::FindRegionEx when the region boundaries are parallel to the piers and
   // adjacent piers have different skews. FindRegionEx used to project the point onto the alignment along a line
   // parallel to the closest pier and look up the distance along the alignment. On a girder far from the alignment
   // that projection can put the point in the wrong region or past the end of the bridge (no region found, E_FAIL).
   //
   // The alignment runs east along the X axis (station = X). Piers:
   //    Pier 0, Sta 0,   N 45 W
   //    Pier 1, Sta 100, N 45 W
   //    Pier 2, Sta 150, NORMAL
   // Casting regions:
   //    Region 0 - Span:  Pier 0         to Pier 1 - 5 ft
   //    Region 1 - Pier:  Pier 1 - 5 ft  to Pier 1 + 5 ft
   //    Region 2 - Span:  Pier 1 + 5 ft  to Pier 2
   // A girder runs parallel to the alignment, 40 ft left of it (Y = 40). On this girder line the N 45 W
   // region boundaries are 40 ft back of where they cross the alignment:
   //    Region 0/1 boundary at X = 55, Region 1/2 boundary at X = 65
   CComPtr<IGenericBridge> bridge;
   CreateBasicBridge(&bridge);

   CComPtr<IBridgeGeometry> geometry;
   bridge->get_BridgeGeometry(&geometry);

   const Float64 girderOffset = 40.0; // left of alignment
   std::vector<std::pair<Float64, CComBSTR>> piers{ {0.0,CComBSTR("N 45 W")}, {100.0,CComBSTR("N 45 W")}, {150.0,CComBSTR("NORMAL")} };
   PierIDType pierID = 0;
   for (const auto& [station, orientation] : piers)
   {
      CComPtr<ISinglePierLineFactory> pier_line_factory;
      pier_line_factory.CoCreateInstance(CLSID_SinglePierLineFactory);
      pier_line_factory->put_PierLineID(pierID++);
      pier_line_factory->put_AlignmentID(0);
      pier_line_factory->put_Station(CComVariant(station));
      pier_line_factory->put_Direction(orientation);
      pier_line_factory->put_Length(200);
      pier_line_factory->put_Offset(100);
      geometry->AddPierLineFactory(pier_line_factory);
   }

   // layout line for the girder
   const IDType girderLayoutLineID = 900;
   CComPtr<IAlignmentOffsetLayoutLineFactory> girderLayoutLineFactory;
   girderLayoutLineFactory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory);
   girderLayoutLineFactory->put_LayoutLineID(girderLayoutLineID);
   girderLayoutLineFactory->put_LayoutLineIDIncrement(1);
   girderLayoutLineFactory->put_LayoutLineCount(1);
   girderLayoutLineFactory->put_Offset(-girderOffset); // - is left of alignment
   girderLayoutLineFactory->put_OffsetIncrement(0);
   girderLayoutLineFactory->put_AlignmentID(0);
   geometry->AddLayoutLineFactory(girderLayoutLineFactory);

   // one girder line, and one superstructure member, in each span
   const GirderIDType ssmbrID[2] = { 100, 101 };
   for (SpanIndexType spanIdx = 0; spanIdx < 2; spanIdx++)
   {
      CComPtr<ISingleGirderLineFactory> girderLineFactory;
      girderLineFactory.CoCreateInstance(CLSID_SingleGirderLineFactory);
      girderLineFactory->put_GirderLineID(ssmbrID[spanIdx]);
      girderLineFactory->put_LayoutLineID(girderLayoutLineID);
      girderLineFactory->put_Type(glChord);
      girderLineFactory->put_StartPierID((PierIDType)spanIdx);
      girderLineFactory->put_EndPierID((PierIDType)(spanIdx + 1));
      geometry->AddGirderLineFactory(girderLineFactory);
   }

   for (SpanIndexType spanIdx = 0; spanIdx < 2; spanIdx++)
   {
      CComPtr<ISuperstructureMember> ssmbr;
      TRY_TEST(bridge->CreateSuperstructureMember(ssmbrID[spanIdx], INVALID_ID, INVALID_ID, &ssmbr), S_OK);

      CComPtr<IPrismaticSuperstructureMemberSegment> segment;
      segment.CoCreateInstance(CLSID_PrismaticSuperstructureMemberSegment);

      CComPtr<IGirderLine> girderLine;
      geometry->FindGirderLine(ssmbrID[spanIdx], &girderLine);
      TRY_TEST(girderLine != nullptr, true);
      segment->putref_GirderLine(girderLine);
      TRY_TEST(ssmbr->AddSegment(segment), S_OK);
   }

   // deck, edges 45 ft left and right of the alignment, ends at Pier 0 and Pier 2
   CComPtr<IBridgeDeck> deck;
   CreateDeck(CIP_DECK, 80.0, 5.0, geometry, 0, 0, 2, &deck);
   bridge->putref_Deck(deck);

   CComQIPtr<ICastSlab> slab(deck);
   CComPtr<ICastingRegions> castingRegions;
   slab->get_CastingRegions(&castingRegions);
   castingRegions->put_Boundary(crbParallelToPier);
   CComPtr<IMaterial> material;
   material.CoCreateInstance(CLSID_Material);
   CComPtr<ICastingRegion> region;
   TRY_TEST(castingRegions->CreateRegion(0, 0.0, 1, -5.0, material, &region), S_OK); region.Release();
   TRY_TEST(castingRegions->CreateRegion(1, -5.0, 1, 5.0, material, &region), S_OK); region.Release();
   TRY_TEST(castingRegions->CreateRegion(1, 5.0, 2, 0.0, material, &region), S_OK); region.Release();

   // Finds the region for the point on the girder at X, in the given span
   auto find_region = [&](SpanIndexType spanIdx, Float64 X, SectionBias bias)
   {
      CComPtr<IGirderLine> girderLine;
      geometry->FindGirderLine(ssmbrID[spanIdx], &girderLine);
      CComPtr<IPoint2d> pntStart;
      girderLine->get_EndPoint(etStart, &pntStart);
      Float64 xStart, yStart;
      pntStart->Location(&xStart, &yStart);
      TRY_TEST(IsEqual(yStart, girderOffset), true); // girder is parallel to the alignment, so Xs is measured along X

      IndexType regionIdx = INVALID_INDEX;
      CComPtr<ICastingRegion> region;
      HRESULT hr = castingRegions->FindRegionEx(ssmbrID[spanIdx], 0, X - xStart, bias, &regionIdx, &region);
      return SUCCEEDED(hr) ? regionIdx : INVALID_INDEX;
   };

   // Span 0 girder
   TRY_TEST(find_region(0, 40.0, sbLeft), 0);
   TRY_TEST(find_region(0, 40.0, sbRight), 0);
   TRY_TEST(find_region(0, 55.0, sbLeft), 0);  // on the Region 0/1 boundary
   TRY_TEST(find_region(0, 55.0, sbRight), 1);
   TRY_TEST(find_region(0, 58.0, sbLeft), 1);
   TRY_TEST(find_region(0, -45.0, sbLeft), 0); // back of Pier 0 (X = -40 on this girder), start of first region is not bounded

   // Span 1 girder
   TRY_TEST(find_region(1, 62.0, sbRight), 1);
   TRY_TEST(find_region(1, 65.0, sbLeft), 1);  // on the Region 1/2 boundary
   TRY_TEST(find_region(1, 65.0, sbRight), 2);

   // This is the case that failed. Pier 1 (20 ft away) is closer than Pier 2 (30 ft away). Projecting the point onto the
   // alignment parallel to Pier 1 gives X = 160, past the end of the bridge, so no region was found.
   TRY_TEST(find_region(1, 120.0, sbLeft), 2);
   TRY_TEST(find_region(1, 120.0, sbRight), 2);

   TRY_TEST(find_region(1, 150.0, sbRight), 2); // at Pier 2, the end of the last region
   TRY_TEST(find_region(1, 155.0, sbRight), 2); // ahead of Pier 2, end of last region is not bounded
}
