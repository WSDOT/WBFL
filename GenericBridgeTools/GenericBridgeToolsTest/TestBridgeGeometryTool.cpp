///////////////////////////////////////////////////////////////////////
// GenericBridgeToolsTest - Test driver for generic bridge tools library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestBridgeGeometryTool.cpp: implementation of the CTestBridgeGeometryTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBridgeGeometryTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestBridgeGeometryTool::CTestBridgeGeometryTool()
{

}

CTestBridgeGeometryTool::~CTestBridgeGeometryTool()
{

}

void CTestBridgeGeometryTool::Test()
{
   TestPrecastGirderBridge();
   TestSplicedGirderBridge();
}

void CTestBridgeGeometryTool::TestPrecastGirderBridge()
{
   CComPtr<IBridgeGeometryTool> tool;
   TRY_TEST(tool.CoCreateInstance(CLSID_BridgeGeometryTool),S_OK);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(tool);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IBridgeGeometryTool ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(tool,IID_IBridgeGeometryTool,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestBridgeGeometryTool::TestSplicedGirderBridge()
{
   CComPtr<IBridgeGeometryTool> tool;
   TRY_TEST(tool.CoCreateInstance(CLSID_BridgeGeometryTool),S_OK);

   CComPtr<IGenericBridge> bridge;
   CreateSplicedGirderBridge(&bridge);

   CComPtr<IPoint2d> pnt;
   TRY_TEST(tool->PointBySSMbr(bridge,1, 50, &pnt),S_OK);
   Float64 x,y;
   pnt->Location(&x,&y);
   TRY_TEST(IsEqual(x,50.0),true);
   TRY_TEST(IsEqual(y, 0.0),true);

   CComPtr<IStation> objStation;
   Float64 offset;
	TRY_TEST(tool->StationAndOffsetBySSMbr(bridge,0,50.0,&objStation,&offset),S_OK);

   Float64 station;
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,50.0),true);
   TRY_TEST(IsEqual(offset,-10.0),true);

   Float64 overhang;
   TRY_TEST(tool->DeckOverhangBySSMbr(bridge,0,50.0,NULL,qcbLeft,&overhang),S_OK);
   TRY_TEST(IsEqual(overhang,6.0),true);

   Float64 spacing;
   TRY_TEST(tool->GirderSpacingBySSMbr(bridge,1,50.0,0,&spacing),S_OK);
   TRY_TEST(IsEqual(spacing,10.0),true);

   TRY_TEST(tool->GirderSpacingBySSMbr(bridge,1,50.0,2,&spacing),S_OK);
   TRY_TEST(IsEqual(spacing,10.0),true);
}
