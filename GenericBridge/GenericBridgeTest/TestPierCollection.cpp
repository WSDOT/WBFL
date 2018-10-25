///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
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

// TestPierCollection.cpp: implementation of the CTestPierCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPierCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPierCollection::CTestPierCollection()
{

}

CTestPierCollection::~CTestPierCollection()
{

}

void CTestPierCollection::Test()
{
   //// Create a default bridge
   //CComPtr<IGenericBridge> bridge;
   //bridge.CoCreateInstance(CLSID_GenericBridge);

   //bridge->InsertSpanAndPier(0, 100.00, qcbAfter, qcbRight);

   //CComPtr<IPierCollection> piers;
   //bridge->get_Piers(&piers);

   //TRY_TEST(piers != NULL,true);

   //PierIndexType count;
   //TRY_TEST(piers->get_Count(NULL),E_POINTER);
   //TRY_TEST(piers->get_Count(&count),S_OK);
   //TRY_TEST(count,2);

   //CComPtr<IPier> pier1, pier2;
   //TRY_TEST(piers->get_Item(0,NULL),E_POINTER);
   //TRY_TEST(piers->get_Item(-1,&pier1),E_INVALIDARG);
   //TRY_TEST(piers->get_Item(100,&pier1),E_INVALIDARG);
   //TRY_TEST(piers->get_Item(0,&pier1),S_OK);
   //TRY_TEST(piers->get_Item(1,&pier2),S_OK);

   //TRY_TEST(pier1 != NULL,true);
   //TRY_TEST(pier2 != NULL,true);

   //CComPtr<IStation> station;
   //Float64 value;
   //pier1->get_Station(&station);
   //station->get_Value(&value);
   //TRY_TEST(IsEqual(value,0.0),true);

   //station.Release();
   //pier2->get_Station(&station);
   //station->get_Value(&value);
   //TRY_TEST(IsEqual(value,100.0),true);


   /////////////////////////////////////////
   //// Test Error Info
   //CComQIPtr<ISupportErrorInfo> eInfo(piers);
   //TRY_TEST( eInfo != 0, true );

   //// Interfaces that should be supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPierCollection ), S_OK );
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   //// Interface that is not supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //// Test IObjectSafety
   //TRY_TEST( TestIObjectSafety(piers,IID_IPierCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   //TRY_TEST( TestIObjectSafety(piers,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
