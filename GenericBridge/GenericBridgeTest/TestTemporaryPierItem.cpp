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

// TestTemporaryPierItem.cpp: implementation of the CTestTemporaryPierItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTemporaryPierItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestTemporaryPierItem::CTestTemporaryPierItem()
{

}

CTestTemporaryPierItem::~CTestTemporaryPierItem()
{

}

void CTestTemporaryPierItem::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 100.00, qcbAfter, qcbRight);

   // create a second stage
   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);

   stages->CreateStage(CComBSTR("Stage 1"),CComBSTR(""));
   stages->CreateStage(CComBSTR("Stage 2"),CComBSTR(""));

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);

   CComPtr<ISpan> span;
   spans->get_Item(0,&span);

   CComPtr<ITemporaryPierItemCollection> tempPiers;
   span->get_TemporaryPiers(&tempPiers);

   tempPiers->Add(11,-0.5,CComBSTR("Stage 2"));

   CComPtr<ITemporaryPierItem> tempPierItem;
   tempPiers->get_Item(0,&tempPierItem);

   TRY_TEST(tempPierItem != NULL,true);

   CComPtr<IPier> pier;
   TRY_TEST(tempPierItem->get_Pier(NULL),  E_POINTER);
   TRY_TEST(tempPierItem->get_Pier(&pier), S_OK);
   TRY_TEST(pier != NULL, true);

   IDType id;
   TRY_TEST(tempPierItem->get_ID(NULL),E_POINTER);
   TRY_TEST(tempPierItem->get_ID(&id), S_OK);
   TRY_TEST(id,11);

   Float64 location;
   TRY_TEST(tempPierItem->get_Location(NULL),E_POINTER);
   TRY_TEST(tempPierItem->get_Location(&location),S_OK);
   TRY_TEST(IsEqual(location,-0.5),true);
   TRY_TEST(tempPierItem->put_Location(-1.5),S_OK);
   TRY_TEST(tempPierItem->put_Location(25.0),S_OK);

   CComBSTR bstrRemovalStage;
   TRY_TEST(tempPierItem->get_RemovalStage(NULL),E_POINTER);
   TRY_TEST(tempPierItem->get_RemovalStage(&bstrRemovalStage), S_OK);
   TRY_TEST(bstrRemovalStage == CComBSTR("Stage 2"),true);
   TRY_TEST(tempPierItem->put_RemovalStage(CComBSTR("NotValidStage")), GB_E_STAGE_NOT_FOUND);
   TRY_TEST(tempPierItem->put_RemovalStage(CComBSTR("Stage 1")), S_OK);
   
   ///////////////////////////////////////
   // Test Set with event sink
   CComObject<CTestTemporaryPierItem>* pTest;
   CComObject<CTestTemporaryPierItem>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(tempPierItem,punk,IID_ITemporaryPierItemEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test Set with events
   tempPierItem->put_Location(10.0);
   pTest->InitEventTest();
   tempPierItem->put_Location(30.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   tempPierItem->put_RemovalStage(CComBSTR("Stage 1"));
   pTest->InitEventTest();
   tempPierItem->put_RemovalStage(CComBSTR("Stage 2"));
   TRY_TEST(pTest->PassedEventTest(), true );

   // bubbled events
   CComPtr<ILongitudinalPierDescription> lpd;
   pier->get_LongitudinalPierDescription(&lpd);

   CComPtr<IPrismaticSegment> newSegment;
   newSegment.CoCreateInstance(CLSID_PrismaticSegment);
   lpd->AddSegment(newSegment);

   CComPtr<ISegment> segment;
   lpd->get_Segment(0,&segment);

//   CComPtr<ISegmentCrossSection> section;
//   segment->get_CrossSection(&section);
//
//   CComPtr<IStressPointCollection> stressPoints;
//   section->get_StressPoints(&stressPoints);
//
//   pTest->InitEventTest();
//   stressPoints->Add();
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   CComPtr<IStressPoint> sp;
//   stressPoints->get_Item(0,&sp);
//   pTest->InitEventTest();
//   sp->put_Sa(10.0);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   section->put_Area(10.0);
//   TRY_TEST(pTest->PassedEventTest(), true );

   pTest->InitEventTest();
   segment->put_Length(15.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   // Done with events
   TRY_TEST(AtlUnadvise(tempPierItem,IID_ITemporaryPierItemEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(tempPierItem);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ITemporaryPierItem ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(tempPierItem,IID_ITemporaryPierItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(tempPierItem,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestTemporaryPierItem::OnTemporaryPierChanged(PoiIDType id)
{
   Pass();
   return S_OK;
}