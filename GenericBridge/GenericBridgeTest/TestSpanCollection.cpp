///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TestSpanCollection.cpp: implementation of the CTestSpanCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSpanCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSpanCollection::CTestSpanCollection()
{

}

CTestSpanCollection::~CTestSpanCollection()
{

}

void CTestSpanCollection::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);

   stages->CreateStage(CComBSTR("Stage 1"),CComBSTR(""));

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);

   TRY_TEST(spans != NULL,true);

   SpanIndexType count;
   TRY_TEST(spans->get_Count(NULL),E_POINTER);
   TRY_TEST(spans->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   CComPtr<ISpan> span;
   TRY_TEST(spans->get_Item(0,NULL),E_POINTER);
   TRY_TEST(spans->get_Item(-1,&span),E_INVALIDARG);
   TRY_TEST(spans->get_Item(10,&span),E_INVALIDARG);
   TRY_TEST(spans->get_Item(0,&span),S_OK);

   bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight);
   bridge->InsertSpanAndPier(1,30.0,qcbAfter,qcbRight);

   spans->get_Count(&count);
   TRY_TEST(count,3);

   long i = 1;
   CComPtr<IEnumSpans> enumSpans;
   TRY_TEST(spans->get__EnumSpans(NULL),E_POINTER);
   TRY_TEST(spans->get__EnumSpans(&enumSpans),S_OK);
   span.Release();
   while ( enumSpans->Next(1,&span,NULL) != S_FALSE )
   {
      Float64 length;
      span->get_Length(&length);
      TRY_TEST(IsEqual(i*10.0,length),true);
      span.Release();
      i++;
   }

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestSpanCollection>* pTest;
   CComObject<CTestSpanCollection>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(spans,punk,IID_ISpanCollectionEvents,&dwCookie),S_OK);

   // there are only bubbled events that we need to worry about
   spans->get_Item(2,&span);
   pTest->InitEventTest();
   span->put_Length(35.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   CComPtr<ITemporaryPierItemCollection> tempPiers;
   span->get_TemporaryPiers(&tempPiers);

   pTest->InitEventTest();
   tempPiers->Add(11,2.5,CComBSTR("Stage 1"));
   TRY_TEST(pTest->PassedEventTest(), true );

   CComPtr<ITemporaryPierItem> tempPierItem;
   tempPiers->get_Item(0,&tempPierItem);

   pTest->InitEventTest();
   tempPierItem->put_Location(3.5);
   TRY_TEST(pTest->PassedEventTest(), true );

   CComPtr<IPier> pier;
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
   TRY_TEST(AtlUnadvise(spans,IID_ISpanCollectionEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(spans);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISpanCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(spans,IID_ISpanCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(spans,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestSpanCollection::OnSpanChanged(ISpan* Span)
{
   Pass();
   return S_OK;
}
