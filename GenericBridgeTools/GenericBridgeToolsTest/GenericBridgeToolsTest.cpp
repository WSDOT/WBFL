///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
// Copyright © 1999-2013  Washington State Department of Transportation
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

// GenericBridgeToolsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initguid.h>
#include <WBFLGenericBridgeTools.h>
#include <WBFLGenericBridgeTools_i.c>

#include <WBFLGenericBridge.h>
#include <WBFLGenericBridge_i.c>

#include <WBFLBridgeGeometry.h>
#include <WBFLBridgeGeometry_i.c>

#include <WBFLGeometry_i.c>
#include <WBFLCogo_i.c>

#include "TestBridgeGeometryTool.h"
#include "TestEffectiveFlangeWidthTool.h"
#include "TestSectionCutTool.h"
#include "TestStrandPattern.h"
#include "TestPrecastGirder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

int main(int argc, TCHAR* argv[])
{
   //_crtBreakAlloc = 355517; // causes program to break at a specific memory allocation

   ::CoInitialize(NULL);

   CTestBridgeGeometryTool::Test();
   CTestEffectiveFlangeWidthTool::Test(); // also tests tributary width
   CTestSectionCutTool::Test();
   CTestStrandPattern::Test();
   CTestPrecastGirder::Test();

   ::CoUninitialize();

	return 0;
}

bool TestIObjectSafety(IUnknown* punk,REFIID riid,DWORD dwSupportedOptions)
{
   CComQIPtr<IObjectSafety> safety(punk);

   if ( safety == NULL )
      return false;


   DWORD dwSupported, dwEnabled;
   safety->GetInterfaceSafetyOptions(riid,&dwSupported,&dwEnabled);
   return dwSupported == dwSupportedOptions;
}

/////////////////////////////////
LineIDType GetGirderLayoutLineID(SpanIndexType spanIdx,GirderIndexType gdrIdx)
{
   ATLASSERT( spanIdx < Int16_Max && gdrIdx < Int16_Max );
   return ::make_Int32((Int16)spanIdx,(Int16)gdrIdx);
}

GirderIDType GetGirderLineID(SpanIndexType spanIdx,GirderIndexType gdrIdx)
{
   return ::GetGirderLayoutLineID(spanIdx,gdrIdx);
}

LineIDType GetGirderSegmentLineID(GirderIndexType gdrIdx,SegmentIndexType segIdx)
{
   ATLASSERT( gdrIdx < Int16_Max && segIdx < Int16_Max );
   return ::make_Int32((Int16)gdrIdx,(Int16)segIdx);
}

void CreateBasicBridge(IGenericBridge** ppBridge)
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<ICogoModel> cogoModel;
   cogoModel.CoCreateInstance(CLSID_CogoModel);

   CComPtr<IBridgeGeometry> geometry;
   TRY_TEST(bridge->get_BridgeGeometry(&geometry),S_OK);
   geometry->putref_CogoModel(cogoModel);

   //
   // Create the Alignment
   //
   CComPtr<IAlignmentCollection> alignments;
   cogoModel->get_Alignments(&alignments);

   CComPtr<IAlignment> alignment;
   alignments->Add(0,&alignment);

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100,0);

   alignment->put_RefStation(CComVariant(0.00));
   alignment->AddEx(p1);
   alignment->AddEx(p2);

   geometry->putref_Alignment(0,alignment);
   geometry->put_BridgeAlignmentID(0);

   bridge.CopyTo(ppBridge);
}

void CreatePrecastGirderBridge(Float64 alignmentOffset,const std::vector<Float64>& spanLengths,Float64 gdrSpacing,GirderIndexType nGirders,IShape* shape,Float64 overhang,int deckType,bool bCompositeDeck,IGenericBridge** ppBridge)
{
   Float64 width = gdrSpacing*(nGirders-1);
   Float64 offset = width/2; // left most girder is offset to the left of the bridge line
   std::vector<SpanDefinition> spanDefs;
   std::vector<Float64>::const_iterator iter(spanLengths.begin());
   std::vector<Float64>::const_iterator end(spanLengths.end());
   for ( ; iter != end; iter++ )
   {
      SpanDefinition spanDef;
      spanDef.length = *iter;
      spanDef.spacingOffset.first = offset;
      spanDef.spacingOffset.second = offset;
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders-1; gdrIdx++ )
      {
         spanDef.girderSpacing.push_back( std::make_pair(gdrSpacing,gdrSpacing) );
      }

      spanDefs.push_back(spanDef);
   }

   CreatePrecastGirderBridge(alignmentOffset,spanDefs,shape,overhang,deckType,bCompositeDeck,ppBridge);
}

void CreatePrecastGirderBridge(Float64 alignmentOffset,const std::vector<SpanDefinition>& spanDefinitions,IShape* shape,Float64 overhang,int deckType,bool bCompositeDeck,IGenericBridge** ppBridge)
{
   CComPtr<IGenericBridge> bridge;
   CreateBasicBridge(&bridge);

   CComPtr<IBridgeGeometry> geometry;
   bridge->get_BridgeGeometry(&geometry);

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   //
   // Layout the Piers
   //
   Float64 pierWidth = 20;

   CComBSTR bstrOrientation("NORMAL"); //if this ever changes alignmentOffset needs to be dealt with (see comment for girder spacing below)
   std::vector<SpanDefinition>::const_iterator spanDefIter(spanDefinitions.begin());
   std::vector<SpanDefinition>::const_iterator spanDefIterEnd(spanDefinitions.end());
   PierIDType pierID = 0;
   Float64 station = 0;
   for ( ; spanDefIter != spanDefIterEnd; spanDefIter++ )
   {
      CComPtr<IPierLine> pierLine;
      geometry->CreatePierLine(pierID,0,CComVariant(station),bstrOrientation,pierWidth,pierWidth/2,&pierLine);

      const SpanDefinition& spanDef = *spanDefIter;
      station += spanDef.length;
      pierID++;
   }

   // last pier
   CComPtr<IPierLine> lastPierLine;
   geometry->CreatePierLine(pierID,0,CComVariant(station),bstrOrientation,pierWidth,pierWidth/2,&lastPierLine);

   //
   // Layout girder lines 
   //
   CComPtr<IUniformSpacingLayoutLineFactory> layoutLineFactory;
   layoutLineFactory.CoCreateInstance(CLSID_UniformSpacingLayoutLineFactory);
   layoutLineFactory->put_AlignmentID(0);

   CComPtr<IDblArray> startSpacing, endSpacing;
   startSpacing.CoCreateInstance(CLSID_DblArray);
   endSpacing.CoCreateInstance(CLSID_DblArray);

   layoutLineFactory->put_StartSpacing(startSpacing);
   layoutLineFactory->put_EndSpacing(endSpacing);

   CComPtr<ISingleGirderLineFactory> girderLineFactory;
   girderLineFactory.CoCreateInstance(CLSID_SingleGirderLineFactory);

   // Create layout lines and girder lines one span at a time (as each span has unique spacing)
   Float64 maxWidth = 0; // keep track of the max outside girder to outside girder width

   SpanIndexType nSpans = spanDefinitions.size();
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      const SpanDefinition& spanDef = spanDefinitions[spanIdx];

      SpacingIndexType nSpaces = spanDef.girderSpacing.size();
      GirderIndexType nGirders = nSpaces+1;

      LineIDType layoutLineID = ::GetGirderLayoutLineID(spanIdx*nGirders,0);
      layoutLineFactory->put_LayoutLineID(layoutLineID);
      layoutLineFactory->put_LayoutLineIDInc(1);

      PierIndexType startPierIdx = (PierIndexType)spanIdx;
      PierIndexType endPierIdx   = startPierIdx+1;

      PierIDType startPierID = PierIDType(startPierIdx);
      PierIDType endPierID   = PierIDType(endPierIdx);

      layoutLineFactory->put_StartPierID(startPierID);
      layoutLineFactory->put_EndPierID(endPierID);

      // alignmentOffset is measured normal to the alignment
      // spacing is measured along the CL pier
      // this method assumes the piers are normal to the alignment
      layoutLineFactory->put_StartSpacingOffset(alignmentOffset + spanDef.spacingOffset.first);
      layoutLineFactory->put_EndSpacingOffset(alignmentOffset   + spanDef.spacingOffset.second);


      Float64 startWidth = 0;
      Float64 endWidth = 0;
      for (SpacingIndexType spaceIdx = 0; spaceIdx < nSpaces; spaceIdx++ )
      {
         Float64 startSpace = spanDef.girderSpacing[spaceIdx].first;
         Float64 endSpace   = spanDef.girderSpacing[spaceIdx].second;

         startSpacing->Add(startSpace);
         endSpacing->Add(endSpace);

         startWidth += startSpace;
         endWidth += endWidth;
      }

      maxWidth = ::Max(maxWidth,startWidth,endWidth);

      // create the layout lines
      geometry->CreateLayoutLines(layoutLineFactory);

      // Generate girder lines
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
      {
         GirderIDType gdrLineID  = ::GetGirderLineID(spanIdx,gdrIdx);
         LineIDType layoutLineID = ::GetGirderLayoutLineID(spanIdx*nGirders,0) + gdrIdx;
         girderLineFactory->put_GirderLineID( gdrLineID ); // girder line ID
         girderLineFactory->put_LayoutLineID( layoutLineID ); // layout line used to layout this girder line
         girderLineFactory->put_Type(glChord);        // layout as a chord
         girderLineFactory->put_StartPierID(startPierID); 
         girderLineFactory->put_EndPierID(endPierID);
         geometry->CreateGirderLines(girderLineFactory);
      }

      // clear the spacing arrays for the next span
      startSpacing->Clear();
      endSpacing->Clear();
   }


   //
   // Build Girder Lines and Superstructure Members
   //
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      PierIDType startPier = PierIDType(spanIdx);
      PierIDType endPier = startPier+1;

      const SpanDefinition& spanDef = spanDefinitions[spanIdx];
      SpacingIndexType nSpaces = spanDef.girderSpacing.size();
      GirderIndexType nGirders = nSpaces+1;

      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
      {
         GirderIDType gdrLineID  = ::GetGirderLineID(spanIdx,gdrIdx);

         LocationType locationType(gdrIdx == 0 ? ltLeftExteriorGirder : (gdrIdx == nGirders-1 ? ltRightExteriorGirder : ltInteriorGirder));
         CComPtr<ISuperstructureMember> ssmbr;
         bridge->CreateSuperstructureMember(gdrLineID,locationType,&ssmbr);

         CComPtr<IPrismaticSegment> segment;
         segment.CoCreateInstance(CLSID_PrismaticSegment);

         // segment material
         CComPtr<IMaterial> material;
         material.CoCreateInstance(CLSID_Material);
         for ( int i = 0; i < 4; i++ ) // fill up material properties for 4 stages
         {
            material->put_E(i,604800.);     // 4200 ksi = 604800 ksf
            material->put_Density(i,160.0); //  160 kcf
         }
         
         segment->AddShape(shape,material,NULL);
         
         // segment geometry
         CComPtr<IGirderLine> girderline;
         geometry->FindGirderLine(gdrLineID,&girderline);
         TRY_TEST(girderline != NULL,true);
         segment->putref_GirderLine(girderline);

         // item data specific for precast girder bridges
         CComQIPtr<IItemData> item_data(segment);

         CComPtr<IStrandMover> strandMover;

         CComPtr<IPrecastGirder> girder;
         girder.CoCreateInstance(CLSID_PrecastGirder);
         girder->Initialize(segment,strandMover);
         item_data->AddItemData(CComBSTR("Precast Girder"),girder);

         TRY_TEST(ssmbr->AddSegment(segment),S_OK);
      }
   }

   //
   // Add the slab
   //
   CComPtr<IBridgeDeck> deck;
   CreateDeck(deckType,maxWidth,overhang,geometry,0,0,nSpans,&deck);
   if ( deck )
   {
      deck->put_Composite(bCompositeDeck ? VARIANT_TRUE : VARIANT_FALSE);

      CComPtr<IMaterial> deck_material;
      deck_material.CoCreateInstance(CLSID_Material);

      // deck is composite in stage 3... use 0 properties prior to stage 3
      deck_material->put_E(0,0);
      deck_material->put_Density(0,0);
      deck_material->put_E(1,0);
      deck_material->put_Density(1,0);
      deck_material->put_E(2,0);
      deck_material->put_Density(2,0);

      if ( bCompositeDeck )
         deck_material->put_E(3,200000.);
      else
         deck_material->put_E(3,0); // not composite, so no stiffness

      deck_material->put_Density(3,160.0);

      deck->putref_Material(deck_material);
   }

   bridge->putref_Deck(deck);
   bridge->put_SacrificialDepth(1./12);

   bridge->UpdateBridgeModel(); // forces the geometry to be up to date

   bridge.CopyTo(ppBridge);
}

void CreateSplicedGirderBridge(IGenericBridge** ppBridge)
{
   Float64 alignmentOffset = 0;

   CComPtr<IGenericBridge> bridge;
   CreateBasicBridge(&bridge);

   CComPtr<IBridgeGeometry> geometry;
   bridge->get_BridgeGeometry(&geometry);

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   Float64 spacing = 10; // 10 ft spacing
   GirderIndexType nGirders = 3; // 3 girder lines
   SegmentIndexType nSegments = 5; // 5 segments per girder
   Float64 width = spacing*(nGirders-1);

   //
   // Layout the Piers
   //
   CComPtr<IPierLine> pierLine;
   geometry->CreatePierLine(0,0,CComVariant(  0.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 0+00 permanent pier
   pierLine.Release();
   geometry->CreatePierLine(1,0,CComVariant(150.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 1+50 permanent pier
   pierLine.Release();
   geometry->CreatePierLine(2,0,CComVariant(350.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 3+50 permanent pier
   pierLine.Release();
   geometry->CreatePierLine(3,0,CComVariant(500.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 5+00 permanent pier

   //
   // Layout the Temporary Supports (these are modeled as piers in the geometry model)
   //
   pierLine.Release();
   geometry->CreatePierLine(-1,0,CComVariant(100.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 1+00 temporary support
   pierLine.Release();
   geometry->CreatePierLine(-2,0,CComVariant(200.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 2+00 temporary support
   pierLine.Release();
   geometry->CreatePierLine(-3,0,CComVariant(300.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 3+00 temporary support
   pierLine.Release();
   geometry->CreatePierLine(-4,0,CComVariant(400.00),CComBSTR("NORMAL"),width,width/2,&pierLine); // 4+00 temporary support

   //
   // Create girder Layout Lines
   //
   Float64 offset = width/2 + alignmentOffset; // offset from bridge line to left girder line

   // Layout lines are parallel to and offset from the alignment
   // Layout line IDs are the girder IDs
   CComPtr<IAlignmentOffsetLayoutLineFactory> layoutLineFactory;
   layoutLineFactory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory);
   layoutLineFactory->put_LayoutLineID(0); // ID of first layout line
   layoutLineFactory->put_LayoutLineIDInc(1);
   layoutLineFactory->put_LayoutLineCount(nGirders); 
   layoutLineFactory->put_Offset(offset);
   layoutLineFactory->put_OffsetIncrement(-spacing); // neg spacing because we want to generate parallel lines to the right of the first line
   layoutLineFactory->put_AlignmentID(0);
   geometry->CreateLayoutLines(layoutLineFactory);

   //
   // Create girder lines
   //

   // one line per segment. three segments per girder. continuous over pier 1
   // pier 0 -> pier -1 -> pier -2 -> pier 2
   CComPtr<ISingleGirderLineFactory> girderLineFactory;
   girderLineFactory.CoCreateInstance(CLSID_SingleGirderLineFactory);
   for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
   {
      // Segment 0
      SegmentIDType segID = GetGirderSegmentLineID(gdrIdx,0);
      girderLineFactory->put_GirderLineID(segID); // ID of the girder line that will be created
      girderLineFactory->put_LayoutLineID(gdrIdx); // ID of the layout line that will provide the geometry
      girderLineFactory->put_Type(glChord); // use a straight chord
      girderLineFactory->put_StartPierID(0); // first pier
      girderLineFactory->put_EndPierID(-1);  // temporary pier in span 1
      geometry->CreateGirderLines(girderLineFactory);

      // Segment 1
      segID = GetGirderSegmentLineID(gdrIdx,1);
      girderLineFactory->put_GirderLineID(segID); // ID of the girder line that will be created
      girderLineFactory->put_LayoutLineID(gdrIdx); // ID of the layout line that will provide the geometry
      girderLineFactory->put_Type(glChord); // use a straight chord
      girderLineFactory->put_StartPierID(-1); // temporary pier in span 1
      girderLineFactory->put_EndPierID(-2);  // temporary pier in span 2
      geometry->CreateGirderLines(girderLineFactory);

      // Segment 2
      segID = GetGirderSegmentLineID(gdrIdx,2);
      girderLineFactory->put_GirderLineID(segID); // ID of the girder line that will be created
      girderLineFactory->put_LayoutLineID(gdrIdx); // ID of the layout line that will provide the geometry
      girderLineFactory->put_Type(glChord); // use a straight chord
      girderLineFactory->put_StartPierID(-2); // temporary pier in span 2
      girderLineFactory->put_EndPierID(-3);  // temporary pier in span 2
      geometry->CreateGirderLines(girderLineFactory);

      // Segment 3
      segID = GetGirderSegmentLineID(gdrIdx,3);
      girderLineFactory->put_GirderLineID(segID); // ID of the girder line that will be created
      girderLineFactory->put_LayoutLineID(gdrIdx); // ID of the layout line that will provide the geometry
      girderLineFactory->put_Type(glChord); // use a straight chord
      girderLineFactory->put_StartPierID(-3); // temporary pier in span 2
      girderLineFactory->put_EndPierID(-4);  // temporary pier in span 3
      geometry->CreateGirderLines(girderLineFactory);

      // Segment 4
      segID = GetGirderSegmentLineID(gdrIdx,4);
      girderLineFactory->put_GirderLineID(segID); // ID of the girder line that will be created
      girderLineFactory->put_LayoutLineID(gdrIdx); // ID of the layout line that will provide the geometry
      girderLineFactory->put_Type(glChord); // use a straight chord
      girderLineFactory->put_StartPierID(-4); // temporary pier in span 3
      girderLineFactory->put_EndPierID(3);  // last pier
      geometry->CreateGirderLines(girderLineFactory);
   }

   //
   // Create Superstructure Members
   //
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->CreateSuperstructureMember(0,ltLeftExteriorGirder,&ssmbr);

   ssmbr.Release();
   bridge->CreateSuperstructureMember(1,ltInteriorGirder,&ssmbr);

   ssmbr.Release();
   bridge->CreateSuperstructureMember(2,ltRightExteriorGirder,&ssmbr);

   //
   // Create Segments
   //
   for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirders; gdrIdx++ )
   {
      ssmbr.Release();
      bridge->get_SuperstructureMember(GirderIDType(gdrIdx),&ssmbr);

      for ( SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++ )
      {
         SegmentIDType gdrLineID = GetGirderSegmentLineID(gdrIdx,segIdx);
         
         CComPtr<ISplicedGirderSegment> segment;
         TRY_TEST(segment.CoCreateInstance(CLSID_FlangedSplicedGirderSegment),S_OK);

         if ( segIdx == 0 )
         {
            segment->put_VariationType(svtParabolic);
            segment->SetVariationParameters(sztLeftPrismatic,50.0,10.0,1.0);
            segment->SetVariationParameters(sztRightPrismatic,0.0,-1,1.0);
         }
         else if ( segIdx == 1 )
         {
            segment->put_VariationType(svtDoubleParabolic);
            segment->SetVariationParameters(sztLeftPrismatic,0.0,-1,1.0);
            segment->SetVariationParameters(sztLeftTapered,25.0,14.0,1.0);
            segment->SetVariationParameters(sztRightTapered,25.0,14.0,1.0);
            segment->SetVariationParameters(sztRightPrismatic,0.0,-1,1.0);
         }
         else if ( segIdx == 2 )
         {
            segment->put_VariationType(svtDoubleParabolic);
            segment->SetVariationParameters(sztLeftPrismatic,0.0,-1,1.0);
            segment->SetVariationParameters(sztLeftTapered,25.0,10.0,1.0);
            segment->SetVariationParameters(sztRightTapered,25.0,10.0,1.0);
            segment->SetVariationParameters(sztRightPrismatic,0.0,-1,1.0);
         }
         else if ( segIdx == 3 )
         {
            segment->put_VariationType(svtDoubleParabolic);
            segment->SetVariationParameters(sztLeftPrismatic,0.0,-1,1.0);
            segment->SetVariationParameters(sztLeftTapered,25.0,14.0,1.0);
            segment->SetVariationParameters(sztRightTapered,25.0,14.0,1.0);
            segment->SetVariationParameters(sztRightPrismatic,0.0,-1,1.0);
         }
         else if ( segIdx == 4 )
         {
            segment->put_VariationType(svtParabolic);
            segment->SetVariationParameters(sztLeftPrismatic,0.0,-1,1.0);
            segment->SetVariationParameters(sztRightPrismatic,50.0,10.0,1.0);
         }
         else
         {
            ATLASSERT(false); // new segment ?
         }

         // segment shape
         CComPtr<IFlangedGirderSection> section;
         section.CoCreateInstance(CLSID_FlangedGirderSection);
         DimensionWFG(section);
         CComQIPtr<IShape> shape(section);

         // segment material
         CComPtr<IMaterial> material;
         material.CoCreateInstance(CLSID_Material);
         for ( int i = 0; i < 7; i++ )
         {
            material->put_E(i,604800.);     // 4200 ksi = 604800 ksf
            material->put_Density(i,160.0); //  160 kcf
         }

         segment->AddShape(shape,material,NULL);

         // segment geometry
         CComPtr<IGirderLine> girderline;
         geometry->FindGirderLine(gdrLineID,&girderline);
         TRY_TEST(girderline != NULL,true);
         segment->putref_GirderLine(girderline);

         // item data specific for precast girder bridges
         CComQIPtr<IItemData> item_data(segment);

         CComPtr<IStrandMover> strandMover;

         CComPtr<IPrecastGirder> girder;
         girder.CoCreateInstance(CLSID_PrecastGirder);
         girder->Initialize(segment,strandMover);
         item_data->AddItemData(CComBSTR("Precast Girder"),girder);

         TRY_TEST(ssmbr->AddSegment(segment),S_OK);
      }
   }

   //
   // Add the slab
   //
   int deckType = CIP_DECK;
   Float64 overhang = 6.0;
   bool bCompositeDeck = true;

   CComPtr<IBridgeDeck> deck;
   CreateDeck(deckType,width,overhang,geometry,0,0,3,&deck);

   if ( deck )
   {
      deck->put_Composite(bCompositeDeck ? VARIANT_TRUE : VARIANT_FALSE );

      CComPtr<IMaterial> deck_material;
      deck_material.CoCreateInstance(CLSID_Material);
      for ( int i = 0; i < 6; i++ )
      {
         deck_material->put_E(i,0);
         deck_material->put_Density(i,0);
      }
      if ( bCompositeDeck )
         deck_material->put_E(6,200000.);
      else
         deck_material->put_E(6,0);

      deck_material->put_Density(6,160.0);

      deck->putref_Material(deck_material);
   }

   bridge->putref_Deck(deck);
   bridge->put_SacrificialDepth(1./12);

   bridge->UpdateBridgeModel(); // forces the geometry to be up to date
   bridge.CopyTo(ppBridge);
}

void CreateDeck(int deckType,Float64 maxWidth,Float64 overhang,IBridgeGeometry* geometry,CogoObjectID alignmentID,PierIDType backPierID,PierIDType forwardPierID,IBridgeDeck** deck)
{
   // create layout lines for the bridge deck boundary
   CComPtr<IAlignmentOffsetLayoutLineFactory> layoutLineFactory;
   layoutLineFactory.CoCreateInstance(CLSID_AlignmentOffsetLayoutLineFactory);

   layoutLineFactory->put_LayoutLineID(-500); // ID of first layout line (left deck edge)
   layoutLineFactory->put_LayoutLineIDInc(-1); // increment by -1 for right deck edge
   layoutLineFactory->put_LayoutLineCount(2);  // 2 deck edges
   layoutLineFactory->put_Offset(maxWidth/2+overhang); // + is left of alignment 
   layoutLineFactory->put_OffsetIncrement(-(maxWidth+2*overhang)); // - offsets next line toward the right
   layoutLineFactory->put_AlignmentID(alignmentID);
   geometry->CreateLayoutLines(layoutLineFactory);

   // create the bridge deck boundary
   CComPtr<ISimpleDeckBoundaryFactory> deckBoundaryFactory;
   deckBoundaryFactory.CoCreateInstance(CLSID_SimpleDeckBoundaryFactory);
   deckBoundaryFactory->put_BackEdgeID( backPierID );
   deckBoundaryFactory->put_BackEdgeType(setPier);
   deckBoundaryFactory->put_ForwardEdgeID( forwardPierID ); 
   deckBoundaryFactory->put_ForwardEdgeType(setPier);
   deckBoundaryFactory->put_LeftEdgeID(-500); // left edge of slab (layout line 1000)
   deckBoundaryFactory->put_RightEdgeID(-501); // right edge of slab (layout line 2000)
   geometry->CreateDeckBoundary(deckBoundaryFactory); 

   // get the deck boundary
   CComPtr<IDeckBoundary> deckBoundary;
   geometry->get_DeckBoundary(&deckBoundary);

   // create the deck model
   if ( deckType == CIP_DECK )
   {
      CComPtr<ICastSlab> slab;
      slab.CoCreateInstance(CLSID_CastSlab);
      slab->put_Fillet(0.75/12);
      slab->put_GrossDepth(9./12);

      slab.QueryInterface(deck);
   }
   else if ( deckType == SIP_DECK )
   {
      CComPtr<IPrecastSlab> slab;
      slab.CoCreateInstance(CLSID_PrecastSlab);
      slab->put_Fillet(0.75/12);
      slab->put_PanelDepth(5./12);
      slab->put_CastDepth(4./12);
      
      slab.QueryInterface(deck);
   }
   else if ( deckType == OVL_DECK )
   {
      CComPtr<IOverlaySlab> slab;
      slab.CoCreateInstance(CLSID_OverlaySlab);
      slab->put_GrossDepth(9./12);
      
      slab.QueryInterface(deck);
   }
   else
   {
      // no deck
      (*deck) = NULL;
   }

   if ( *deck )
      (*deck)->putref_DeckBoundary(deckBoundary);
}

void DimensionWFG(IFlangedGirderSection* fgs)
{
   CComPtr<IPrecastBeam> beam;
   fgs->get_Beam(&beam);

   // Create a W74G (dimensions in feet)
   beam->put_D1(2.875/12.);
   beam->put_D2(2.626/12.);
   beam->put_D3(2.0/12.);
   beam->put_D4(6.0/12.);
   beam->put_D5(3.0/12.);
   beam->put_D6(0.0/12.);
   beam->put_D7(57.0/12.);
   beam->put_T1(6.0/12.);
   beam->put_T2(6.0/12.);
   beam->put_W1(16.5/12.);
   beam->put_W2(2.0/12.);
   beam->put_W3(9.5/12.);
   beam->put_W4(0.0/12.);
};

void DimensionNUG(INUGirderSection* ngs)
{
   CComPtr<INUBeam> beam;
   ngs->get_Beam(&beam);

   // Use some real dimensions (NU2400 - 150mm web)
   // Convert mm to feet
   beam->put_W1(1225./304.8);
   beam->put_W2(975./304.8);
   beam->put_D1(65./304.8);
   beam->put_D2(45./304.8);
   beam->put_D3(2015./304.8);
   beam->put_D4(140./304.8);
   beam->put_D5(135./304.8);
   beam->put_T(150./304.8);
   beam->put_R1(200./304.8);
   beam->put_R2(200./304.8);
   beam->put_R3(50./304.8);
   beam->put_R4(50./304.8);
};

void DimensionUG(IUGirderSection* ugs)
{
   CComPtr<IUBeam> beam;
   ugs->get_Beam(&beam);

   beam->put_W1(4);
   beam->put_W2(6.4047619047619047619047619047619);
   beam->put_W3(1.0);
   beam->put_W4(3./12);
   beam->put_W5(5./12);
   beam->put_D1(72./12);
   beam->put_D2(0.5);
   beam->put_D3(0.5);
   beam->put_D4(4.5/12);
   beam->put_D5(1.5/12);
   beam->put_D6(4.5/12);
   beam->put_D7(1.5/12);
   beam->put_T(7./12);
};
