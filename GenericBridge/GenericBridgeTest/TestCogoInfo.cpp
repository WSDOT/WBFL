///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TestCogoInfo.cpp: implementation of the CTestCogoInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCogoInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCogoInfo::CTestCogoInfo()
{

}

CTestCogoInfo::~CTestCogoInfo()
{

}

void CTestCogoInfo::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   CComPtr<ICogoInfo> cogoInfo;
   bridge->get_CogoInfo(&cogoInfo);

   TRY_TEST(cogoInfo != NULL,true);

   // build up a reasonable framing plan
   bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight);
   bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight);
   bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight);

//   CComPtr<IGirderSpacing> girderSpacing;
//   bridge->get_GirderSpacing(&girderSpacing);
//   girderSpacing->Add(4);
//
//   // now, get access to the points in the cogo model
   long pointID;
//   TRY_TEST(cogoInfo->get_GirderPointID(0,0,NULL),E_POINTER);
//   TRY_TEST(cogoInfo->get_GirderPointID(-1,0,&pointID),E_INVALIDARG);
//   TRY_TEST(cogoInfo->get_GirderPointID(100,0,&pointID),E_INVALIDARG);
//   TRY_TEST(cogoInfo->get_GirderPointID(0,-1,&pointID),E_INVALIDARG);
//   TRY_TEST(cogoInfo->get_GirderPointID(0,100,&pointID),E_INVALIDARG);
//   TRY_TEST(cogoInfo->get_GirderPointID(0,0,&pointID),S_OK);
//   TRY_TEST(pointID,1001);
//   TRY_TEST(cogoInfo->get_GirderPointID(3,4,&pointID),S_OK);
//   TRY_TEST(pointID,4005);

   TRY_TEST(cogoInfo->get_PierPointID(0,pptLeft,NULL),E_POINTER);
   TRY_TEST(cogoInfo->get_PierPointID(-1,pptLeft,&pointID),E_INVALIDARG);
   TRY_TEST(cogoInfo->get_PierPointID(100,pptLeft,&pointID),E_INVALIDARG);
   TRY_TEST(cogoInfo->get_PierPointID(0,pptLeft,&pointID),S_OK);
   TRY_TEST(pointID,-100110);
   TRY_TEST(cogoInfo->get_PierPointID(0,pptAlignment,&pointID),S_OK);
   TRY_TEST(pointID,-100000);
   TRY_TEST(cogoInfo->get_PierPointID(0,pptRight,&pointID),S_OK);
   TRY_TEST(pointID,-100010);

   TRY_TEST(cogoInfo->get_PierPointID(3,pptLeft,&pointID),S_OK);
   TRY_TEST(pointID,-400110);
   TRY_TEST(cogoInfo->get_PierPointID(3,pptAlignment,&pointID),S_OK);
   TRY_TEST(pointID,-400000);
   TRY_TEST(cogoInfo->get_PierPointID(3,pptRight,&pointID),S_OK);
   TRY_TEST(pointID,-400010);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(cogoInfo);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICogoInfo ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(cogoInfo,IID_ICogoInfo,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
