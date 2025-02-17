///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
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
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<IBridgeGeometry> bridgeGeometry;
   bridge->get_BridgeGeometry(&bridgeGeometry);

   IDType alignmentID = 0;
   IDType profileID = 0;

   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);
   
   bridgeGeometry->AddAlignment(alignmentID, alignment);
   bridgeGeometry->put_BridgeAlignmentID(alignmentID);

   CComPtr<ISinglePierLineFactory> pier_1_factory;
   pier_1_factory.CoCreateInstance(CLSID_SinglePierLineFactory);
   pier_1_factory->put_AlignmentID(alignmentID);
   pier_1_factory->put_Station(CComVariant(0.0));
   pier_1_factory->put_Direction(CComBSTR("NORMAL"));
   pier_1_factory->put_Length(10);
   pier_1_factory->put_Offset(-5);
   bridgeGeometry->AddPierLineFactory(pier_1_factory);

   CComPtr<ISinglePierLineFactory> pier_2_factory;
   pier_2_factory.CoCreateInstance(CLSID_SinglePierLineFactory);
   pier_2_factory->put_AlignmentID(alignmentID);
   pier_2_factory->put_Station(CComVariant(100.0));
   pier_2_factory->put_Direction(CComBSTR("NORMAL"));
   pier_2_factory->put_Length(10);
   pier_2_factory->put_Offset(-5);
   bridgeGeometry->AddPierLineFactory(pier_2_factory);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   TRY_TEST(piers != nullptr,true);

   PierIndexType count;
   TRY_TEST(piers->get_Count(nullptr),E_POINTER);
   TRY_TEST(piers->get_Count(&count),S_OK);
   TRY_TEST(count,2);

   CComPtr<IBridgePier> pier1, pier2;
   TRY_TEST(piers->get_Item(0,nullptr),E_POINTER);
   TRY_TEST(piers->get_Item(-1,&pier1),E_INVALIDARG);
   TRY_TEST(piers->get_Item(100,&pier1),E_INVALIDARG);
   TRY_TEST(piers->get_Item(0,&pier1),S_OK);
   TRY_TEST(piers->get_Item(1,&pier2),S_OK);

   TRY_TEST(pier1 != nullptr,true);
   TRY_TEST(pier2 != nullptr,true);

   CComPtr<IStation> station;
   Float64 value;
   pier1->get_Station(&station);
   station->get_Value(&value);
   TRY_TEST(IsEqual(value,0.0),true);

   station.Release();
   pier2->get_Station(&station);
   station->get_Value(&value);
   TRY_TEST(IsEqual(value,100.0),true);

   CComPtr<IBridgePier> foundPier;
   TRY_TEST(piers->FindPier(-200,&foundPier),E_FAIL);

   foundPier.Release();
   TRY_TEST(piers->FindPier(200,&foundPier),S_OK);
   station.Release();
   foundPier->get_Station(&station);
   station->get_Value(&value);
   TRY_TEST(IsEqual(value,100.0),true);

   foundPier.Release();
   TRY_TEST(piers->FindPier(50,&foundPier),S_OK);
   station.Release();
   foundPier->get_Station(&station);
   station->get_Value(&value);
   TRY_TEST(IsEqual(value,0.0),true);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(piers);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPierCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(piers,IID_IPierCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(piers,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
