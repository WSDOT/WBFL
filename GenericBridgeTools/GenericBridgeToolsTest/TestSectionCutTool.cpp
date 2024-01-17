///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// TestSectionCutTool.cpp: implementation of the CTestSectionCutTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSectionCutTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSectionCutTool::CTestSectionCutTool()
{

}

CTestSectionCutTool::~CTestSectionCutTool()
{

}

void CTestSectionCutTool::Test()
{
   TestPrecastGirderBridge();
   TestSplicedGirderBridge();
}

void CTestSectionCutTool::TestPrecastGirderBridge()
{
#pragma Reminder("Improve these tests")
   // Left and right exterior girders need to be tested as well

   CComPtr<ISectionCutTool> tool;
   TRY_TEST(tool.CoCreateInstance(CLSID_SectionCutTool),S_OK);

   std::vector<Float64> spanLengths;
   spanLengths.push_back(100);
   spanLengths.push_back(200);
   spanLengths.push_back(100);

   GirderIndexType nGirderLines = 5;

   CComPtr<IGenericBridge> bridge;
   CComPtr<IShape> shape;

   GirderIDType ssMbrID       = ::GetGirderLineID(0,1);

   shape.CoCreateInstance(CLSID_FlangedGirderSection); // I-beam
   CComQIPtr<IFlangedGirderSection> fgs(shape);
   DimensionWFG(fgs);

   // Create bridge with no deck
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,NO_DECK,true,&bridge);

   IndexType beamIdx, slabIdx;
   CComPtr<ISection> section;
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft,cstBridge,3,spmGross,hdmHaunchIsZero,FALSE,&beamIdx,&slabIdx,&section),S_OK);

   CComPtr<IElasticProperties> eprops;
   section->get_ElasticProperties(&eprops);

   Float64 value;
   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,15970811.888899315),true);

   // Create bridge with non-composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,CIP_DECK,false,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,15970811.888899315),true);

   // Create bridge with composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,CIP_DECK,true,&bridge);

   // results before composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,1,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,15970811.888899315),true);

   // results at/after composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,25997381.589508355),true);

   // Repeat with stay in place deck panels
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,SIP_DECK,false,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,15970811.888899315),true);

   // Create bridge with composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,SIP_DECK,true,&bridge);

   // results before composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,1,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,15970811.888899315),true);

   // results at/after composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,25997381.589508355),true);

   /////////////////////////////////////////////////////////////////////
   // Use a different girder section - NU beam
   /////////////////////////////////////////////////////////////////////
   shape.Release();
   shape.CoCreateInstance(CLSID_NUGirderSection); // NU I-beam
   CComQIPtr<INUGirderSection> ngs(shape);
   DimensionNUG(ngs);

   // Create bridge with no deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,NO_DECK,true,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,36035420.351917922),true);

   // Create bridge with non-composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,CIP_DECK,false,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,36035420.351917922),true);

   // Create bridge with composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,CIP_DECK,true,&bridge);

   // results before composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,1,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,36035420.351917922),true);

   // results at/after composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,57682216.965132132),true);

   // Repeat with stay in place deck panels
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,SIP_DECK,false,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,36035420.351917922),true);

   // Create bridge with composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,SIP_DECK,true,&bridge);

   // results before composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,1,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,36035420.351917922),true);

   // results at/after composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,57682216.965132132),true);

   /////////////////////////////////////////////////////////////////////
   // Use a different girder section - U beam
   /////////////////////////////////////////////////////////////////////
   shape.Release();
   shape.CoCreateInstance(CLSID_UGirderSection); // U-beam
   CComQIPtr<IUGirderSection> ugs(shape);
   DimensionUG(ugs);

   // Create bridge with no deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,NO_DECK,true,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,23361276.303486),true);

   // Create bridge with non-composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,CIP_DECK,false,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,23361276.303486),true);

   // Create bridge with composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,CIP_DECK,true,&bridge);

   // results before composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,1,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,23361276.303486),true);

   // results at/after composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,37767619.516997069),true);

   // Repeat with stay in place deck panels
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,SIP_DECK,false,&bridge);

   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,23361276.303486355),true);

   // Create bridge with composite deck
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,SIP_DECK,true,&bridge);

   // results before composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,1,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,23361276.303486355),true);

   // results at/after composite stage
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,37767619.516997069),true);
   

   /////////////////////////////////////////////////////////////////////
   // Use a different girder section - I beam with overlay deck
   /////////////////////////////////////////////////////////////////////
   shape.Release();
   shape.CoCreateInstance(CLSID_FlangedGirderSection); // I-beam
   fgs.Release();
   shape.QueryInterface(&fgs);
   DimensionWFG(fgs);

   // Create bridge with overlay
   bridge.Release();
   CreatePrecastGirderBridge(0.0,spanLengths,10.0,nGirderLines,shape,3.0,OVL_DECK,true,&bridge);

   // before composite
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,1,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,15970811.888899323),true);

   // after composite
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,25.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);

   eprops->get_EI11(&value);
   TRY_TEST(IsEqual(value,25997381.589508355),true);

   /////////////////////////////////////////////////////////
   // Test bridge section cut
   section.Release();
   tool->CreateBridgeSection(bridge,1.0,sbRight,3,bscAll,&section);
#pragma Reminder("UPDATE: Finish this unit test")

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(tool);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISectionCutTool ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(tool,IID_ISectionCutTool,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestSectionCutTool::TestSplicedGirderBridge()
{
   CComPtr<ISectionCutTool> tool;
   TRY_TEST(tool.CoCreateInstance(CLSID_SectionCutTool),S_OK);

   CComPtr<IGenericBridge> bridge;
   CreateSplicedGirderBridge(&bridge);

   GirderIDType ssMbrID      = GirderIDType(1); // interior girder

   // cut section in first prismatic zone
   IndexType beamIdx, slabIdx;
   CComPtr<ISection> section;
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,0.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   CComPtr<IElasticProperties> eprops;
   section->get_ElasticProperties(&eprops);
   
   Float64 Yb,Yt;
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   Float64 H = Yb + Yt;
   TRY_TEST(IsEqual(H,10.0),true);

   // at first segment transition
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,50.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,10.0),true);

   // cut section at end of first segment first prismatic zone
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,100.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,11.77777),true);

   // cut section at end of left taper in center segment
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,125.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,14.0),true);

   // cut section at start of right taper in center segment
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,175.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,14.0),true);

   // cut section at end of second segment
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,200.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,11.0),true);

   // cut section in prismatic zone of last segment
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,225.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,10.0),true);

   //
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,250.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,10.0),true);

   //
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,275.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,10.0),true);

   // cut section at end
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,300.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,11.0),true);

   // 
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,325.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,14.0),true);

   // 
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,375.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,14.0),true);

   // 
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,400.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,11.77777),true);

   // 
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,450.0,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,10.0),true);

   // 
   section.Release();
   TRY_TEST(tool->CreateGirderSectionBySSMbr(bridge,ssMbrID,500,sbLeft, cstBridge,3,spmGross,hdmHaunchIsZero, FALSE,&beamIdx,&slabIdx,&section),S_OK);

   eprops.Release();
   section->get_ElasticProperties(&eprops);
   
   eprops->get_Ybottom(&Yb);
   eprops->get_Ytop(&Yt);
   H = Yb + Yt;
   TRY_TEST(IsEqual(H,10.0),true);
}
