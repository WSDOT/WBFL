///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestSpan.cpp: implementation of the CTestSpan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSpan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSpan::CTestSpan()
{

}

CTestSpan::~CTestSpan()
{

}

void CTestSpan::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 100.00, qcbAfter, qcbRight);

   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);

   stages->CreateStage(CComBSTR("Stage 1"),CComBSTR(""));

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers); // we will need this later

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);

   CComPtr<ISpan> span;
   spans->get_Item(0,&span);

   TRY_TEST(span != NULL, true);

   CComPtr<ITemporaryPierItemCollection> tempPiers;
   TRY_TEST(span->get_TemporaryPiers(NULL),       E_POINTER);
   TRY_TEST(span->get_TemporaryPiers(&tempPiers), S_OK);
   TRY_TEST(tempPiers != NULL,true);

   Float64 length;
   TRY_TEST(span->get_Length(NULL),E_POINTER);
   TRY_TEST(span->get_Length(&length),S_OK);
   TRY_TEST(IsEqual(length,100.0),true);

//   TRY_TEST(span->get_GirderLineLength(0,NULL),E_POINTER);
//   TRY_TEST(span->get_GirderLineLength(-1,&length),E_INVALIDARG);
//   TRY_TEST(span->get_GirderLineLength(100,&length),E_INVALIDARG);
//   TRY_TEST(span->get_GirderLineLength(0,&length),S_OK);
//   TRY_TEST(IsEqual(length,100.0),true);
#pragma Reminder("Need a more rigorous test") // this stupid little test doesn't really push the code

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestSpan>* pTest;
   CComObject<CTestSpan>::CreateInstance(&pTest);
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(span,punk,IID_ISpanEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test Set with events
   TRY_TEST(span->put_Length(-100),E_INVALIDARG);
   TRY_TEST(span->put_Length(20),S_OK);
   pTest->InitEventTest();
   TRY_TEST(span->put_Length(30),S_OK);
   TRY_TEST(pTest->PassedEventTest(), true );

   CComPtr<IPier> pier;
   piers->get_Item(1,&pier);
   CComPtr<IStation> objStation;
   pier->get_Station(&objStation);
   Float64 value;
   objStation->get_Value(&value);
   TRY_TEST(IsEqual(value,30.0),true);

   objStation->put_Value(40.0);
   span->get_Length(&length);
   TRY_TEST(IsEqual(length,40.0),true);

   // bubbled events
   pTest->InitEventTest();
   tempPiers->Add(11,2.5,CComBSTR("Stage 1"));
   TRY_TEST(pTest->PassedEventTest(), true );

   CComPtr<ITemporaryPierItem> tempPierItem;
   tempPiers->get_Item(0,&tempPierItem);

   pTest->InitEventTest();
   tempPierItem->put_Location(3.5);
   TRY_TEST(pTest->PassedEventTest(), true );

   pier.Release();
   tempPierItem->get_Pier(&pier);

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
   TRY_TEST(AtlUnadvise(span,IID_ISpanEvents,dwCookie),S_OK);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(span);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISpan ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(span,IID_ISpan,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(span,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestSpan::OnSpanChanged(ISpan* Span)
{
   Pass();
   return S_OK;
}