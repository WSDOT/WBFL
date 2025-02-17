///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestEffectiveFlangeWidthTool.cpp: implementation of the CTestEffectiveFlangeWidthTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestEffectiveFlangeWidthTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestEffectiveFlangeWidthTool::CTestEffectiveFlangeWidthTool()
{

}

CTestEffectiveFlangeWidthTool::~CTestEffectiveFlangeWidthTool()
{

}

void CTestEffectiveFlangeWidthTool::Test()
{
   TestPrecastGirderBridge();
   TestSpliceGirderBridge();
}

void CTestEffectiveFlangeWidthTool::TestPrecastGirderBridge()
{
   CComPtr<IEffectiveFlangeWidthTool> tool;
   tool.CoCreateInstance(CLSID_EffectiveFlangeWidthTool);
   TRY_TEST(tool != nullptr,true);

   std::vector<Float64> spanLengths;
   spanLengths.push_back(100);
   spanLengths.push_back(200);
   spanLengths.push_back(100);

   GirderIndexType nGirderLines = 5;

   CComPtr<IGenericBridge> bridge;
   CComPtr<IShape> shape;

   Float64 value;

   // This test fires a lot of asserts (as it should), but it is getting annoying
   // Uncomment it later
#pragma Reminder("Enable these tests")
   // Use bad shape
   //bridge.Release();
   //shape.Release();
   //shape.CoCreateInstance(CLSID_Circle);
   //CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,4.0,CIP_DECK,true,&bridge);
   //TRY_TEST(tool->EffectiveFlangeWidth(bridge,0,1,25.0,&value),GBMT_E_GIRDERSECTION);

   // Need a valid shape... use an I-beam
   shape.Release();
   shape.CoCreateInstance(CLSID_FlangedGirderSection);

   // No deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,4.0,NO_DECK,true,&bridge);
   TRY_TEST(tool->EffectiveFlangeWidthBySSMbr(bridge,1,25.0,&value),GBMT_E_NODECK);

   // Noncomposite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,4.0,SIP_DECK,false,&bridge);
   TRY_TEST(tool->EffectiveFlangeWidthBySSMbr(bridge,1,25.0,&value),GBMT_E_COMPOSITEDECK);

   // use a I-Beam for the shape
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,4.0,CIP_DECK,true,&bridge);
   
   SpanIndexType nSpans = spanLengths.size();
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirderLines; gdrIdx++ )
      {
         GirderIDType ssMbrID       = ::GetGirderLineID(spanIdx,gdrIdx);

	      TRY_TEST(tool->EffectiveFlangeWidthBySSMbr(bridge,ssMbrID,25.0,&value),S_OK);
         TRY_TEST(IsEqual(value,8.0),true);

         TRY_TEST(tool->TributaryFlangeWidthBySSMbr(bridge,ssMbrID,25.0,&value),S_OK);
         if ( gdrIdx == 0 || gdrIdx == nGirderLines-1 )
         {
            TRY_TEST(IsEqual(value,9.0),true); // exterior
         }
         else
         {
            TRY_TEST(IsEqual(value,10.0),true); // interior
         }
      }
   }

   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,4.0,SIP_DECK,true,&bridge);
   
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirderLines; gdrIdx++ )
      {
         GirderIDType ssMbrID       = ::GetGirderLineID(spanIdx,gdrIdx);  //GirderIDType(::HashSpanGirder(spanIdx,gdrIdx)   );

	      TRY_TEST(tool->EffectiveFlangeWidthBySSMbr(bridge,ssMbrID,0.25,&value),S_OK);
         TRY_TEST(IsEqual(value,8.0),true);

         TRY_TEST(tool->TributaryFlangeWidthBySSMbr(bridge,ssMbrID,0.25,&value),S_OK);
         if ( gdrIdx == 0 || gdrIdx == nGirderLines-1 )
         {
            TRY_TEST(IsEqual(value,9.0),true); // exterior
         }
         else
         {
            TRY_TEST(IsEqual(value,10.0),true); // interior
         }
      }
   }
   

   // Repeat test with U-beams
   bridge.Release();
   shape.Release();
   shape.CoCreateInstance(CLSID_UGirderSection);

   CComQIPtr<IUGirderSection> section(shape);
   CComPtr<IUBeam> beam;
   section->get_Beam(&beam);
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

   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,4.0,CIP_DECK,true,&bridge);
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirderLines; gdrIdx++ )
      {
         GirderIDType ssMbrID       = ::GetGirderLineID(spanIdx,gdrIdx);  //GirderIDType(::HashSpanGirder(spanIdx,gdrIdx)   );

	      TRY_TEST(tool->EffectiveFlangeWidthBySSMbr(bridge,ssMbrID,0.25,&value),S_OK);

         if ( gdrIdx == 0 || gdrIdx == nGirderLines-1 )
         {
            TRY_TEST(IsEqual(value,8.9761904761904772),true); // exterior
         }
         else
         {
            TRY_TEST(IsEqual(value,9.9761904761904781),true); // interior
         }

         TRY_TEST(tool->TributaryFlangeWidthBySSMbr(bridge,ssMbrID,0.25,&value),S_OK);
         if ( gdrIdx == 0 || gdrIdx == nGirderLines-1 )
         {
            TRY_TEST(IsEqual(value,9.0),true); // exterior
         }
         else
         {
            TRY_TEST(IsEqual(value,10.0),true); // interior
         }
      }
   }

   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,4.0,SIP_DECK,true,&bridge);
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      for ( GirderIndexType gdrIdx = 0; gdrIdx < nGirderLines; gdrIdx++ )
      {
         GirderIDType ssMbrID       = ::GetGirderLineID(spanIdx,gdrIdx);  //GirderIDType(::HashSpanGirder(spanIdx,gdrIdx)   );

	      TRY_TEST(tool->EffectiveFlangeWidthBySSMbr(bridge,ssMbrID,0.25,&value),S_OK);

         if ( gdrIdx == 0 || gdrIdx == nGirderLines-1 )
         {
            TRY_TEST(IsEqual(value,8.9761904761904772),true); // exterior
         }
         else
         {
            TRY_TEST(IsEqual(value,9.9761904761904781),true); // interior
         }

         TRY_TEST(tool->TributaryFlangeWidthBySSMbr(bridge,ssMbrID,0.25,&value),S_OK);
         if ( gdrIdx == 0 || gdrIdx == nGirderLines-1 )
         {
            TRY_TEST(IsEqual(value,9.0),true); // exterior
         }
         else
         {
            TRY_TEST(IsEqual(value,10.0),true); // interior
         }
      }
   }

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(tool);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IEffectiveFlangeWidthTool ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(tool,IID_IEffectiveFlangeWidthTool,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestEffectiveFlangeWidthTool::TestSpliceGirderBridge()
{
   CComPtr<IGenericBridge> bridge;
   CreateSplicedGirderBridge(&bridge);

   CComPtr<IEffectiveFlangeWidthTool> tool;
   tool.CoCreateInstance(CLSID_EffectiveFlangeWidthTool);
   TRY_TEST(tool != nullptr,true);

   Float64 value;

   // Center girder
   GirderIDType ssMbrID       = GirderIDType(1);
   TRY_TEST(tool->TributaryFlangeWidthBySSMbr(bridge,ssMbrID,25.0,&value),S_OK);
   TRY_TEST(IsEqual(value,10.0),true);

   // Left exterior girder
   ssMbrID      = GirderIDType(0);
   TRY_TEST(tool->TributaryFlangeWidthBySSMbr(bridge,ssMbrID,25.0,&value),S_OK);
   TRY_TEST(IsEqual(value,11.0),true);

   // Right exterior girder
   ssMbrID      = GirderIDType(2);
   TRY_TEST(tool->TributaryFlangeWidthBySSMbr(bridge,ssMbrID,25.0,&value),S_OK);
   TRY_TEST(IsEqual(value,11.0),true);
}
