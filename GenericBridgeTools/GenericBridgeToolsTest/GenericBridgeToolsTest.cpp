///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
// Copyright © 1999-2011  Washington State Department of Transportation
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

#include <WBFLGeometry_i.c>

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
   ::CoInitialize(NULL);

   CTestEffectiveFlangeWidthTool::Test();
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

void CreateBridge(const std::vector<Float64>& spanLengths,Float64 gdrSpacing,GirderIndexType nGirderLines,IShape* shape,Float64 overhang,int deckType,bool bCompositeDeck,IGenericBridge** ppBridge)
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   std::vector<Float64>::const_iterator iter;
   for ( iter = spanLengths.begin(); iter != spanLengths.end(); iter++ )
   {
      bridge->InsertSpanAndPier(-1,*iter,qcbAfter,qcbRight);
   }

   //
   // Layout girder lines 
   //
   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);
   SpanIndexType nSpans = spanLengths.size();
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      CComPtr<ISpan> span;
      spans->get_Item(spanIdx,&span);

      span->put_GirderCount(nGirderLines);

      CComPtr<IGirderSpacing> start_spacing, end_spacing;
      span->get_GirderSpacing(etStart,&start_spacing);
      span->get_GirderSpacing(etEnd,  &end_spacing);

      for ( SpacingIndexType spaceIdx = 0; spaceIdx < SpacingIndexType(nGirderLines-1); spaceIdx++ )
      {
         start_spacing->put_Spacing(spaceIdx,gdrSpacing);
         end_spacing->put_Spacing(spaceIdx,gdrSpacing);
      }

      //
      // Layout Superstructure Members
      //
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirderLines; gdrIdx++ )
      {
         CComPtr<ISuperstructureMember> ssmbr;
         span->get_SuperstructureMember(gdrIdx,&ssmbr);

         ssmbr->put_AreSegmentLengthsFractional(VARIANT_FALSE);
         ssmbr->put_Length(spanLengths[spanIdx]);

         CComPtr<IPrismaticSegment> segment;
         segment.CoCreateInstance(CLSID_PrismaticSegment);
         segment->put_Length(spanLengths[spanIdx]);

         CComPtr<IMaterial> material;
         material.CoCreateInstance(CLSID_Material);
         material->put_E(604800.);     // 4200 ksi = 604800 ksf
         material->put_Density(160.0); //  160 kcf

         segment->putref_Shape(shape);
         segment->putref_Material(material);

         ssmbr->AddSegment(segment);
      }
   }


   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);
   stages->CreateStage(CComBSTR("Stage 1"),CComBSTR("Girder Placement"));
   stages->CreateStage(CComBSTR("Stage 2"),CComBSTR("Deck Placement"));
   stages->CreateStage(CComBSTR("Stage 3"),CComBSTR("Composite Slab"));

   //
   // Add the slab
   //
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   CComPtr<IAlignmentOffsetStrategy> left_strategy, right_strategy;
   left_strategy.CoCreateInstance(CLSID_AlignmentOffsetStrategy);
   left_strategy->putref_Alignment(alignment);
   left_strategy->put_Offset(-(gdrSpacing*(nGirderLines-1)/2+overhang));

   right_strategy.CoCreateInstance(CLSID_AlignmentOffsetStrategy);
   right_strategy->putref_Alignment(alignment);
   right_strategy->put_Offset( (gdrSpacing*(nGirderLines-1)/2+overhang));

   CComQIPtr<IOverhangPathStrategy> lstrategy(left_strategy);
   CComQIPtr<IOverhangPathStrategy> rstrategy(right_strategy);

   CComPtr<IBridgeDeck> deck;
   if ( deckType == CIP_DECK )
   {
      CComPtr<ICastSlab> slab;
      slab.CoCreateInstance(CLSID_CastSlab);
      slab->put_Fillet(0.75/12);
      slab->put_GrossDepth(9./12);
      slab->put_SacrificialDepth(1./12);

      slab->putref_LeftOverhangPathStrategy(lstrategy);
      slab->putref_RightOverhangPathStrategy(rstrategy);

      slab.QueryInterface(&deck);
   }
   else if ( deckType == SIP_DECK )
   {
      CComPtr<IPrecastSlab> slab;
      slab.CoCreateInstance(CLSID_PrecastSlab);
      slab->put_Fillet(0.75/12);
      slab->put_PanelDepth(5./12);
      slab->put_CastDepth(4./12);
      slab->put_SacrificialDepth(1./12);

      slab->putref_LeftOverhangPathStrategy(lstrategy);
      slab->putref_RightOverhangPathStrategy(rstrategy);
      
      slab.QueryInterface(&deck);
   }
   else if ( deckType == OVL_DECK )
   {
      CComPtr<IOverlaySlab> slab;
      slab.CoCreateInstance(CLSID_OverlaySlab);
      slab->put_GrossDepth(9./12);
      slab->put_SacrificialDepth(1./12);

      slab->putref_LeftOverhangPathStrategy(lstrategy);
      slab->putref_RightOverhangPathStrategy(rstrategy);
      
      slab.QueryInterface(&deck);
   }
   else
   {
      // no deck
   }

   if ( deck )
   {
      deck->put_ConstructionStage(CComBSTR("Stage 2"));

      deck->put_Composite(bCompositeDeck ? VARIANT_TRUE : VARIANT_FALSE );
      if ( bCompositeDeck )
         deck->put_CompositeStage(CComBSTR("Stage 3"));

      CComPtr<IMaterial> deck_material;
      deck_material.CoCreateInstance(CLSID_Material);
      deck_material->put_E(200000.);
      deck_material->put_Density(160.0);

      deck->put_Material(deck_material);
   }

   bridge->putref_Deck(deck);

   bridge->UpdateBridgeModel(); // forces the geometry to be up to date

   (*ppBridge) = bridge;
   (*ppBridge)->AddRef();
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
