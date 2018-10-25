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

// TestGenericBridge.cpp: implementation of the CTestGenericBridge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestGenericBridge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestGenericBridge::CTestGenericBridge()
{

}

CTestGenericBridge::~CTestGenericBridge()
{

}

void CTestGenericBridge::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   TRY_TEST(bridge != NULL,true);

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   TestAlignment();
   TestCogoInfo();
   TestCogoModel();
   TestPiers();
   TestSpans();
   TestStageCollection();
   TestSuperstructureMemberCollection();
   TestAddRemove();
   TestClone();
   TestSegmentLayout();

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestGenericBridge>* pTest;
   CComObject<CTestGenericBridge>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(bridge,punk,IID_IGenericBridgeEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test with events
   DumpBridge(bridge);

   SpanIndexType nSpans;
   PierIndexType nPiers;
   pTest->InitEventTest();
//   TRY_TEST(bridge->InsertSpanAndPier(-1,20.0,qcbAfter,qcbRight),E_INVALIDARG); // this is ok
   TRY_TEST(bridge->InsertSpanAndPier(10,20.0,qcbAfter,qcbRight),E_INVALIDARG);
   TRY_TEST(bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight),S_OK);
   
   DumpBridge(bridge);

   TRY_TEST(pTest->PassedEventTest(), true );
   pTest->InitEventTest();
   TRY_TEST(bridge->InsertSpanAndPier(0,-1,qcbAfter,qcbRight),S_OK);
   
   DumpBridge(bridge);

   spans->get_Count(&nSpans);
   TRY_TEST(nSpans,3);
   piers->get_Count(&nPiers);
   TRY_TEST(nPiers,4);
   pTest->InitEventTest();

   pTest->InitEventTest();
   TRY_TEST(bridge->RemoveSpanAndPier(-1,qcbLeft),E_INVALIDARG);
   TRY_TEST(bridge->RemoveSpanAndPier(100,qcbLeft),E_INVALIDARG);
   TRY_TEST(bridge->RemoveSpanAndPier(0,qcbLeft),S_OK);
   
   DumpBridge(bridge);

   spans->get_Count(&nSpans);
   TRY_TEST(nSpans,2);
   piers->get_Count(&nPiers);
   TRY_TEST(nPiers,3);
   TRY_TEST(pTest->PassedEventTest(), true );
   pTest->InitEventTest();

   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);
   CComPtr<IStation> station;
   Float64 value;
   pier->get_Station(&station);
   pTest->InitEventTest();
   TRY_TEST(bridge->Move(10),S_OK);
   station->get_Value(&value);
   TRY_TEST(IsEqual(value,20.0),true);
   TRY_TEST(pTest->PassedEventTest(), true );
   
   DumpBridge(bridge);

   pTest->InitEventTest();
   TRY_TEST(bridge->Move(-20),S_OK);
   
   DumpBridge(bridge);

   station->get_Value(&value);
   TRY_TEST(IsEqual(value,0.0),true);
   TRY_TEST(pTest->PassedEventTest(), true );
   pTest->InitEventTest();

   pTest->InitEventTest();
   TRY_TEST(bridge->MoveToStation(-1,100.0),E_INVALIDARG);
   TRY_TEST(bridge->MoveToStation(100,100.0),E_INVALIDARG);
   TRY_TEST(bridge->MoveToStation(1,100.0),S_OK);
   station->get_Value(&value);
   TRY_TEST(IsEqual(value,90.0),true);
   
   DumpBridge(bridge);

   TRY_TEST(pTest->PassedEventTest(), true );
   pTest->InitEventTest();

   bridge->InsertSpanAndPier(1,100.0,qcbAfter,qcbLeft);
   
   DumpBridge(bridge);

   bridge->InsertSpanAndPier(1,200.0,qcbAfter,qcbLeft);
   
   DumpBridge(bridge);

   CComPtr<ISpan> span;
   spans->get_Item(0,&span);
   span->get_Length(&value);
   TRY_TEST(IsEqual(value,10.0),true);
   span.Release();
   spans->get_Item(1,&span);
   span->get_Length(&value);
   TRY_TEST(IsEqual(value,20.0),true);
   span.Release();
   spans->get_Item(2,&span);
   span->get_Length(&value);
   TRY_TEST(IsEqual(value,200.0),true);
   span.Release();
   spans->get_Item(3,&span);
   span->get_Length(&value);
   TRY_TEST(IsEqual(value,100.0),true);
   pTest->InitEventTest();
   
   SAFEARRAY* lengths;
   SAFEARRAYBOUND bounds = { 4, 10 };
   lengths = SafeArrayCreate(VT_R8,1,&bounds);
   for ( long i = bounds.lLbound; i < long(bounds.lLbound+bounds.cElements); i++ )
   {
      long key = i - bounds.lLbound + 1;
      Float64 newLength = 250;
      SafeArrayPutElement(lengths,&i,&newLength);
   }
   CComVariant varLengths;
   varLengths.vt = VT_ARRAY | VT_R8;
   varLengths.parray = lengths;
   TRY_TEST(bridge->ResizeSpans(CComVariant("Junk")),E_INVALIDARG);
   TRY_TEST(bridge->ResizeSpans(varLengths),S_OK);
   
   DumpBridge(bridge);

   span.Release();
   spans->get_Item(0,&span);
   span->get_Length(&value);
   TRY_TEST(IsEqual(value,250.0),true);
   span.Release();
   spans->get_Item(1,&span);
   span->get_Length(&value);
   TRY_TEST(IsEqual(value,250.0),true);
   span.Release();
   spans->get_Item(2,&span);
   span->get_Length(&value);
   TRY_TEST(IsEqual(value,250.0),true);

   TRY_TEST(pTest->PassedEventTest(), true );
   
   span.Release();

   CComPtr<IGenericBridge> clone;
   TRY_TEST(bridge->Clone(NULL),E_POINTER);
   TRY_TEST(bridge->Clone(&clone),S_OK);
   TRY_TEST(clone != NULL,true);

   DumpBridge(clone);

   // Done with events
   TRY_TEST(AtlUnadvise(bridge,IID_IGenericBridgeEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(bridge);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IGenericBridge ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(bridge,IID_IGenericBridge,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(bridge,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);

   span.Release();
   pier.Release();
   spans.Release();
   piers.Release();

   bridge.Release();
   clone.Release();

   eInfo.Release();
}


STDMETHODIMP CTestGenericBridge::OnBridgeChanged(IGenericBridge* bridge)
{
   Pass();
   return S_OK;
}

void CTestGenericBridge::TestAlignment()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<IAlignment> alignment;
   TRY_TEST(bridge->get_Alignment(NULL),E_POINTER);
   TRY_TEST(bridge->get_Alignment(&alignment),S_OK);
   TRY_TEST(alignment != NULL,true);

   // Users are free to manipulate the alignment, however there can be dire concequences.
   // No events or transactions... It could goof up the internal state of the generic bridge
   // model
}

void CTestGenericBridge::TestCogoInfo()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<ICogoInfo> cogoInfo;
   TRY_TEST(bridge->get_CogoInfo(NULL),E_POINTER);
   TRY_TEST(bridge->get_CogoInfo(&cogoInfo),S_OK);
   TRY_TEST(cogoInfo != NULL,true);

   // No edits... No events, no transactions
}

void CTestGenericBridge::TestCogoModel()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<ICogoModel> cogoModel;
   TRY_TEST(bridge->get_CogoModel(NULL),E_POINTER);
   TRY_TEST(bridge->get_CogoModel(&cogoModel),S_OK);
   TRY_TEST(cogoModel != NULL,true);

   // Users are free to manipulate the cogo model, however there can be dire concequences.
   // No events or transactions... It could goof up the internal state of the generic bridge
   // model
}

void CTestGenericBridge::TestPiers()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   CComPtr<IPierCollection> piers;
   TRY_TEST(bridge->get_Piers(NULL),E_POINTER);
   TRY_TEST(bridge->get_Piers(&piers),S_OK);
   TRY_TEST(piers != NULL,true);

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestGenericBridge>* pTest;
   CComObject<CTestGenericBridge>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(bridge,punk,IID_IGenericBridgeEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test with events
//   pTest->InitEventTest();
//   piers->CopyTo(0,1);
//   TRY_TEST(pTest->PassedEventTest(), true );

   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);

   CComPtr<ILongitudinalPierDescription> lpd;
   pier->get_LongitudinalPierDescription(&lpd);

   CComPtr<IPrismaticSegment> newSegment;
   newSegment.CoCreateInstance(CLSID_PrismaticSegment);
   lpd->AddSegment(newSegment);
   
   CComPtr<ISegment> segment;
   lpd->get_Segment(0,&segment);

   pTest->InitEventTest();
   segment->put_Length(15.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   // Done with events
   TRY_TEST(AtlUnadvise(bridge,IID_IGenericBridgeEvents,dwCookie),S_OK);
   pTest->Release();
}

void CTestGenericBridge::TestSpans()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight);
   bridge->InsertSpanAndPier(1,30.0,qcbAfter,qcbRight);

   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);
   stages->CreateStage(CComBSTR("Stage 1"),CComBSTR(""));

   CComPtr<ISpanCollection> spans;
   TRY_TEST(bridge->get_Spans(NULL),E_POINTER);
   TRY_TEST(bridge->get_Spans(&spans),S_OK);
   TRY_TEST(spans != NULL,true);

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestGenericBridge>* pTest;
   CComObject<CTestGenericBridge>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(bridge,punk,IID_IGenericBridgeEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test with transactions and events

   // there are only bubbled events that we need to worry about
   CComPtr<ISpan> span;
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
//   pTest->InitEventTest();
//
//   TRY_TEST(txnMgr->Undo(),S_OK);
   
   TRY_TEST(pTest->PassedEventTest(), true );

//   pTest->InitEventTest();
//   section->put_Area(10.0);
//   TRY_TEST(pTest->PassedEventTest(), true );
//   pTest->InitEventTest();
//
//   TRY_TEST(txnMgr->Undo(),S_OK);

   TRY_TEST(pTest->PassedEventTest(), true );

   pTest->InitEventTest();
   segment->put_Length(15.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   // Done with events
   TRY_TEST(AtlUnadvise(bridge,IID_IGenericBridgeEvents,dwCookie),S_OK);
   pTest->Release();
}

void CTestGenericBridge::TestStageCollection()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   CComPtr<IStageCollection> stages;
   TRY_TEST(bridge->get_Stages(NULL),E_POINTER);
   TRY_TEST(bridge->get_Stages(&stages),S_OK);
   TRY_TEST(stages != NULL,true);

   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestGenericBridge>* pTest;
   CComObject<CTestGenericBridge>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(bridge,punk,IID_IGenericBridgeEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test with events
   pTest->InitEventTest();
   stages->CreateStage(CComBSTR("Stage 2"),CComBSTR(""));
   TRY_TEST(pTest->PassedEventTest(), true);

   CComPtr<IStage> stage;
   stages->get_Item(0,&stage);

   pTest->InitEventTest();
   stage->put_Name(CComBSTR("First Stage"));
   TRY_TEST(pTest->PassedEventTest(), true);

//   Events related to stage descriptions changing aren't bubbled by the bridge model
//   pTest->InitEventTest();
//   stage->put_Description(CComBSTR("It all begins here"));
//   TRY_TEST(pTest->PassedEventTest(), true);
//   pTest->InitEventTest();
//   TRY_TEST(txnMgr->Undo(),S_OK);
//   TRY_TEST(pTest->PassedEventTest(), true);


   // Done with events
   TRY_TEST(AtlUnadvise(bridge,IID_IGenericBridgeEvents,dwCookie),S_OK);
   pTest->Release();
}


void CTestGenericBridge::TestSuperstructureMemberCollection()
{
//   CComPtr<IGenericBridge> bridge;
//   bridge.CoCreateInstance(CLSID_GenericBridge);
//
//   CComPtr<ISuperstructureMemberCollection> members;
//   TRY_TEST(bridge->get_SuperstructureMembers(-1,&members),E_INVALIDARG);
//   TRY_TEST(bridge->get_SuperstructureMembers(100,&members),E_INVALIDARG);
//   TRY_TEST(bridge->get_SuperstructureMembers(0,NULL),E_POINTER);
//   TRY_TEST(bridge->get_SuperstructureMembers(0,&members),S_OK);
//   TRY_TEST(members != NULL, true );
//
//   ///////////////////////////////////////
//   // Test with event sink
//   CComObject<CTestGenericBridge>* pTest;
//   CComObject<CTestGenericBridge>::CreateInstance(&pTest);
//   pTest->AddRef();
//   
//   DWORD dwCookie;
//   CComPtr<IUnknown> punk(pTest);
//   TRY_TEST(AtlAdvise(bridge,punk,IID_IGenericBridgeEvents,&dwCookie),S_OK);
//
//   ///////////////////////////////////////
//   // Test with transactions and events
//   members->Add();
//   CComPtr<ISuperstructureMember> mbr;
//   members->get_Item(0,&mbr);
//
//   pTest->InitEventTest();
//   CComPtr<IPrismaticSegment> newSegment;
//   newSegment.CoCreateInstance(CLSID_PrismaticSegment);
//   mbr->AddSegment(newSegment);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   CComPtr<ISegment> segment;
//   mbr->get_Segment(0,&segment);
//
//   pTest->InitEventTest();
//   segment->put_Length(10.0);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   mbr->put_Length(10.0);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   // Done with events
//   TRY_TEST(AtlUnadvise(bridge,IID_IGenericBridgeEvents,dwCookie),S_OK);
//   pTest->Release();
}

#define STATIONS(a,b,c,d,e) stations[0] = a; stations[1] = b; stations[2] = c; stations[3] = d; stations[4] = e;
#define SPANLENGTHS(a,b,c,d) spanLengths[0] = a; spanLengths[1] = b; spanLengths[2] = c; spanLengths[3] = d;
#define ORIENTATIONS(a,b,c,d,e) orientations[0] = a; orientations[1] = b; orientations[2] = c; orientations[3] = d; orientations[4] = e;
#define SPACING(a,b,c,d,e) spacings[0] = a; spacings[1] = b; spacings[2] = c; spacings[3] = d; spacings[4] = e;

void CTestGenericBridge::TestAddRemove()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);
   pier->put_Orientation(CComBSTR("N 1 E"));
   pier.Release();
   piers->get_Item(1,&pier);
   pier->put_Orientation(CComBSTR("N 2 E"));

   bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight);
   pier.Release();
   piers->get_Item(2,&pier);
   pier->put_Orientation(CComBSTR("N 3 E"));

   bridge->InsertSpanAndPier(1,30.0,qcbAfter,qcbRight);
   pier.Release();
   piers->get_Item(3,&pier);
   pier->put_Orientation(CComBSTR("N 4 E"));

   // Variables to hold test results
   Float64 stations[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
   Float64 spanLengths[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
   CComBSTR orientations[] = { "", "", "", "", "" };
   Float64 spacings[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

   DumpBridge(bridge);

   // Insert at Span 0
   bridge->InsertSpanAndPier(0,15.0,qcbAfter,qcbRight);
   DumpBridge(bridge);
   SPANLENGTHS(10.0, 15.0, 20.0, 30.0 );
   STATIONS(0.0, 10.0, 25.0, 45.0, 75.0);
   ORIENTATIONS("N 1 E", "N 2 E", "Normal", "N 3 E", "N 4 E" );
   SPACING(1.0, 2.0, 2.0, 3.0, 4.0);
   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);

//   // Insert at Span 1
//   bridge->InsertSpanAndPier(1,15.0,qcbAfter,qcbRight);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 15.0, 30.0 );
//   STATIONS(0.0, 10.0, 30.0, 45.0, 75.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "N 3 E", "Normal", "N 4 E" );
//   SPACING(1.0, 2.0, 3.0, 3.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->InsertSpanAndPier(1,15.0,qcbAfter,qcbLeft);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 15.0, 30.0 );
//   STATIONS(0.0, 10.0, 30.0, 45.0, 75.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "Normal", "N 3 E", "N 4 E");
//   SPACING(1.0, 2.0, 3.0, 3.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->InsertSpanAndPier(1,15.0,qcbBefore,qcbRight);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 15.0, 20.0, 30.0);
//   STATIONS(0.0, 10.0, 25.0, 45.0, 75.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "Normal", "N 3 E", "N 4 E");
//   SPACING(1.0, 2.0, 2.0, 3.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->InsertSpanAndPier(1,15.0,qcbBefore,qcbLeft);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 15.0, 20.0, 30.0);
//   STATIONS(0.0, 10.0, 25.0, 45.0, 75.0);
//   ORIENTATIONS("N 1 E", "Normal", "N 2 E", "N 3 E", "N 4 E");
//   SPACING(1.0, 2.0, 2.0, 3.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   // Insert at Span 2
//   bridge->InsertSpanAndPier(2,15.0,qcbAfter,qcbRight);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 30.0, 15.0 );
//   STATIONS(0.0, 10.0, 30.0, 60.0, 75.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "N 3 E", "N 4 E", "Normal" );
//   SPACING(1.0, 2.0, 3.0, 4.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->InsertSpanAndPier(2,15.0,qcbAfter,qcbLeft);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 30.0, 15 );
//   STATIONS(0.0, 10.0, 30.0, 60.0, 75.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "N 3 E", "Normal", "N 4 E");
//   SPACING(1.0, 2.0, 3.0, 4.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->InsertSpanAndPier(2,15.0,qcbBefore,qcbRight);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 15.0, 30.0);
//   STATIONS(0.0, 10.0, 30.0, 45.0, 75.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "N 3 E", "Normal", "N 4 E");
//   SPACING(1.0, 2.0, 3.0, 3.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->InsertSpanAndPier(2,15.0,qcbBefore,qcbLeft);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 15.0, 30.0);
//   STATIONS(0.0, 10.0, 30.0, 45.0, 75.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "Normal", "N 3 E", "N 4 E");
//   SPACING(1.0, 2.0, 3.0, 3.0, 4.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);

   ///////////////////////////////////////////////////////////////////////////////////////

   // Remove Span 0
//   bridge->RemoveSpanAndPier(0,qcbLeft);
//   DumpBridge(bridge);
//   SPANLENGTHS(20.0, 30.0, 00.0, 0.0);
//   STATIONS(10.0, 30.0, 60.0, 00.0, 0.0);
//   ORIENTATIONS("N 2 E", "N 3 E", "N 4 E", "", "");
//   SPACING(2.0, 3.0, 4.0, 0.0, 0.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->RemoveSpanAndPier(0,qcbRight);
//   DumpBridge(bridge);
//   SPANLENGTHS(20.0, 30.0, 00.0, 0.0);
//   STATIONS(0.0, 20.0, 50.0, 00.0, 0.0);
//   ORIENTATIONS("N 1 E", "N 3 E", "N 4 E", "", "");
//   SPACING(1.0, 3.0, 4.0, 0.0, 0.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   // Remove Span 1
//   bridge->RemoveSpanAndPier(1,qcbLeft);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 30.0, 00.0, 0.0);
//   STATIONS(0.0, 10.0, 40.0, 00.0, 0.0);
//   ORIENTATIONS("N 1 E", "N 3 E", "N 4 E", "", "");
//   SPACING(1.0, 3.0, 4.0, 0.0, 0.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->RemoveSpanAndPier(1,qcbRight);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 30.0, 00.0, 0.0);
//   STATIONS(0.0, 10.0, 40.0, 00.0, 0.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "N 4 E", "", "");
//   SPACING(1.0, 2.0, 4.0, 0.0, 0.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   // Remove Span 2
//   bridge->RemoveSpanAndPier(2,qcbLeft);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 00.0, 0.0);
//   STATIONS(0.0, 10.0, 30.0, 00.0, 0.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "N 4 E", "", "");
//   SPACING(1.0, 2.0, 4.0, 0.0, 0.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
//
//   bridge->RemoveSpanAndPier(2,qcbRight);
//   DumpBridge(bridge);
//   SPANLENGTHS(10.0, 20.0, 00.0, 0.0);
//   STATIONS(0.0, 10.0, 30.0, 00.0, 0.0);
//   ORIENTATIONS("N 1 E", "N 2 E", "N 3 E", "", "");
//   SPACING(1.0, 2.0, 3.0, 0.0, 0.0);
//   ValidateBridge(bridge,stations,spanLengths,orientations,spacings);
}

void CTestGenericBridge::TestClone()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);
   pier->put_Orientation(CComBSTR("N 1 E"));
   pier.Release();
   piers->get_Item(1,&pier);
   pier->put_Orientation(CComBSTR("N 2 E"));

   bridge->InsertSpanAndPier(0,20.0,qcbAfter,qcbRight);
   pier.Release();
   piers->get_Item(2,&pier);
   pier->put_Orientation(CComBSTR("N 3 E"));

   bridge->InsertSpanAndPier(1,30.0,qcbAfter,qcbRight);
   pier.Release();
   piers->get_Item(3,&pier);
   pier->put_Orientation(CComBSTR("N 4 E"));
   pier->CreateTransversePierDescription();

   // Variables to hold test results
   Float64 stations[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
   Float64 spanLengths[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
   CComBSTR orientations[] = { "", "", "", "", "" };
   Float64 spacings[] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

   CComPtr<IGenericBridge> clone;
   TRY_TEST(bridge->Clone(NULL),E_POINTER);
   TRY_TEST(bridge->Clone(&clone),S_OK);

   DumpBridge(clone);

   SPANLENGTHS(10.0, 20.0, 30.0, 0.0);
   STATIONS(0.0, 10.0, 30.0, 60.0, 0.0);
   ORIENTATIONS("N 1 E", "N 2 E", "N 3 E", "N 4 E", "");
   SPACING(1.0, 2.0, 3.0, 4.0, 0.0);
   ValidateBridge(clone,stations,spanLengths,orientations,spacings);
}

void CTestGenericBridge::DumpBridge(IGenericBridge* bridge)
{
   USES_CONVERSION;

   std::_tcout << "Dump Bridge Data\n";
   std::_tcout << "================\n";

   std::_tcout << "Dump by span\n";
   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);
   SpanIndexType nSpans;
   spans->get_Count(&nSpans);
   for ( SpanIndexType i = 0; i < nSpans; i++ )
   {
      CComPtr<ISpan> span;
      spans->get_Item(i,&span);

      Float64 length;
      span->get_Length(&length);
      std::_tcout << "Span " << (i+1) << " Length = " << length << "\n";
   }
//
//   std::_tcout << "Dump by pier\n";
//   long nPiers;
//   CComPtr<IPierCollection> piers;
//   bridge->get_Piers(&piers);
//   piers->get_Count(&nPiers);
//   CComPtr<IGirderSpacing> spacing;
//   bridge->get_GirderSpacing(&spacing);
//   for ( i = 0; i < nPiers; i++ )
//   {
//      CComPtr<IPier> pier;
//      piers->get_Item(i,&pier);
//
//      CComPtr<IStation> station;
//      pier->get_Station(&station);
//
//      CComBSTR bstrStation;
//      station->AsString(umSI,&bstrStation);
//
//      CComBSTR bstrOrientation;
//      pier->get_Orientation(&bstrOrientation);
//
//      Float64 space;
//      spacing->get_Spacing(i,0,&space);
//
//      std::_tcout << "Pier " << (i+1) << " " << OLE2T(bstrOrientation) << " Station = " << OLE2T(bstrStation) << " Spacing = " << space << "\n";
//   }
}

void CTestGenericBridge::ValidateBridge(IGenericBridge* bridge,Float64 stations[],Float64 spanLengths[],CComBSTR orientations[],Float64 spacings[])
{
   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);
   CComPtr<IEnumSpans> enumSpans;
   spans->get__EnumSpans(&enumSpans);
   CComPtr<ISpan> span;
   long index = 0;
   while ( enumSpans->Next(1,&span,NULL) != S_FALSE )
   {
      Float64 length;
      span->get_Length(&length);

      TRY_TEST(IsEqual(spanLengths[index],length),true);

      span.Release();
      index++;
   }

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);
   CComPtr<IEnumPiers> enumPiers;
   piers->get__EnumPiers(&enumPiers);
   CComPtr<IPier> pier;
   index = 0;
   while ( enumPiers->Next(1,&pier,NULL) != S_FALSE )
   {
      CComBSTR bstrOrientation;
      pier->get_Orientation(&bstrOrientation);
      TRY_TEST(bstrOrientation == orientations[index],true);

      CComPtr<IStation> station;
      pier->get_Station(&station);

      Float64 value;
      station->get_Value(&value);
      TRY_TEST(IsEqual(value,stations[index]),true);

      pier.Release();
      index++;
   }

//   long nPiers;
//   piers->get_Count(&nPiers);
//   CComPtr<IGirderSpacing> spacing;
//   bridge->get_GirderSpacing(&spacing);
//   for ( long i = 0; i < nPiers; i++ )
//   {
//      Float64 space;
//      spacing->get_SpacingAtPier(i,0,&space);
//      TRY_TEST(IsEqual(space,spacings[i]),true);
//   }
}

void CTestGenericBridge::TestSegmentLayout()
{
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   // Create 2 spans
   bridge->InsertSpanAndPier(-1,100,qcbAfter,qcbRight);
   bridge->InsertSpanAndPier(-1,100,qcbAfter,qcbRight);

   // remove the default span and pier
   bridge->RemoveSpanAndPier(0,qcbLeft);

//   // layout 3 girder lines at a uniform 10' spacing
//   CComPtr<IGirderSpacing> spacing;
//   bridge->get_GirderSpacing(&spacing);
//   spacing->put_Uniform(VARIANT_TRUE);
//   spacing->Add(3);
//   spacing->put_SpacingAtPier(0,0,10.0);

//   // get the superstructure members for the girderlines
//   CComPtr<ISuperstructureMemberCollection> ssmbrs[3];
//   bridge->get_SuperstructureMembers(0,&ssmbrs[0]);
//   bridge->get_SuperstructureMembers(1,&ssmbrs[1]);
//   bridge->get_SuperstructureMembers(2,&ssmbrs[2]);
//
//   // add 3 superstructure member along the girder line
//   ssmbrs[0]->Add();
//   ssmbrs[0]->Add();
//   ssmbrs[0]->Add();
//
//   // get the newly created superstructure members
//   CComPtr<ISuperstructureMember> ssmbr[3];
//   ssmbrs[0]->get_Item(0,&ssmbr[0]);
//   ssmbrs[0]->get_Item(1,&ssmbr[1]);
//   ssmbrs[0]->get_Item(2,&ssmbr[2]);
//
//   // create a segment
//   CComPtr<IPrismaticSegment> segment;
//   segment.CoCreateInstance(CLSID_PrismaticSegment);
//
//   // Divide each superstructure member into 2 segments
//   // segments are cloned when added
//   ssmbr[0]->AddSegment(segment);
//   ssmbr[0]->AddSegment(segment);
//
//   ssmbr[1]->AddSegment(segment);
//   ssmbr[1]->AddSegment(segment);
//
//   ssmbr[2]->AddSegment(segment);
//   ssmbr[2]->AddSegment(segment);
//
//   // segments are measured fractional
//   ssmbr[0]->put_Fractional(VARIANT_TRUE);
//   ssmbr[1]->put_Fractional(VARIANT_TRUE);
//   ssmbr[2]->put_Fractional(VARIANT_TRUE);
//
//   // set the superstructure member lengths
//   ssmbr[0]->put_Length(50);
//   ssmbr[1]->put_Length(65);
//   ssmbr[2]->put_Length(100);
//
//   // get the cloned segments and set their length
//   CComPtr<ISegment> segment1, segment2, segment3, segment4, segment5, segment6;
//   ssmbr[0]->get_Segment(0,&segment1);
//   ssmbr[0]->get_Segment(1,&segment2);
//   ssmbr[1]->get_Segment(0,&segment3);
//   ssmbr[1]->get_Segment(1,&segment4);
//   ssmbr[2]->get_Segment(0,&segment5);
//   ssmbr[2]->get_Segment(1,&segment6);
//
//   segment1->put_Length(-0.25);
//   segment2->put_Length(-0.75);
//
//   segment3->put_Length(-0.50);
//   segment4->put_Length(-0.50);
//
//   segment5->put_Length(-0.75);
//   segment6->put_Length(-0.25);
//
//   // verify all girder lines are the same length
//   Float64 length;
//   bridge->get_GirderLineLength(0,&length);
//   TRY_TEST(IsEqual(length,215.),true);
//   bridge->get_GirderLineLength(1,&length);
//   TRY_TEST(IsEqual(length,215.),true);
//   bridge->get_GirderLineLength(2,&length);
//   TRY_TEST(IsEqual(length,215.),true);

//   // verify that the correct segment is found
//   CComPtr<ISegment> seg;
//   TRY_TEST(bridge->GetSuperstructureMemberSegment(-1, 1, 5.0,&seg),E_INVALIDARG);
//   TRY_TEST(bridge->GetSuperstructureMemberSegment(10, 1, 5.0,&seg),E_INVALIDARG);
//   TRY_TEST(bridge->GetSuperstructureMemberSegment( 1,-1, 5.0,&seg),E_INVALIDARG);
//   TRY_TEST(bridge->GetSuperstructureMemberSegment( 1,10, 5.0,&seg),E_INVALIDARG);
//   TRY_TEST(bridge->GetSuperstructureMemberSegment( 1, 1,-5.0,&seg),E_INVALIDARG);
//   TRY_TEST(bridge->GetSuperstructureMemberSegment( 0, 1,120.,&seg),E_INVALIDARG);
//   TRY_TEST(bridge->GetSuperstructureMemberSegment( 1, 1, 5.0,NULL),E_POINTER);
//
//   seg.Release();
//   TRY_TEST(bridge->GetSuperstructureMemberSegment( 0, 1,-5.0,&seg),S_OK);
//   TRY_TEST(seg.IsEqualObject(segment1),true);
//
//   seg.Release();
//   TRY_TEST(bridge->GetSuperstructureMemberSegment(1,1,5.0,&seg),S_OK);
//   TRY_TEST(seg.IsEqualObject(segment4),true);
//
//   seg.Release();
//   TRY_TEST(bridge->GetSuperstructureMemberSegment(1,1,15.0,&seg),S_OK);
//   TRY_TEST(seg.IsEqualObject(segment5),true);
//
//   seg.Release();
//   TRY_TEST(bridge->GetSuperstructureMemberSegment(1,1,105.0,&seg),S_OK);
//   TRY_TEST(seg.IsEqualObject(segment6),true);

   //Uint32 ssmbrIdx;
   //Uint32 segmentIdx;
   //Float64 dist;

#pragma Reminder("Revisit this testing")
//   TRY_TEST(bridge->SpanGirderToSegment( -1,  1, -2.0,&ssmbrIdx,&segmentIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SpanGirderToSegment(100,  1, -2.0,&ssmbrIdx,&segmentIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SpanGirderToSegment(  0, -1, -2.0,&ssmbrIdx,&segmentIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SpanGirderToSegment(  0,100, -2.0,&ssmbrIdx,&segmentIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SpanGirderToSegment(  0,  1,-50.0,&ssmbrIdx,&segmentIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SpanGirderToSegment(  1,  1,200.0,&ssmbrIdx,&segmentIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SpanGirderToSegment(  0,  1, -2.0,NULL,     &segmentIdx,&dist),E_POINTER);
//   TRY_TEST(bridge->SpanGirderToSegment(  0,  1, -2.0,&ssmbrIdx,NULL,       &dist),E_POINTER);
//   TRY_TEST(bridge->SpanGirderToSegment(  0,  1, -2.0,&ssmbrIdx,&segmentIdx,NULL), E_POINTER);
//
//   // point on cantilever before first pier
//   TRY_TEST(bridge->SpanGirderToSegment(0,1,-2.0,&ssmbrIdx,&segmentIdx,&dist),S_OK);
//   TRY_TEST(ssmbrIdx,0);
//   TRY_TEST(segmentIdx,0);
//   TRY_TEST(IsEqual(dist,3.0),true);
//
//   TRY_TEST(bridge->SpanGirderToSegment(1,1,5.0,&ssmbrIdx,&segmentIdx,&dist),S_OK);
//   TRY_TEST(ssmbrIdx,1);
//   TRY_TEST(segmentIdx,1);
//   TRY_TEST(IsEqual(dist,27.5),true);
//
//   TRY_TEST(bridge->SpanGirderToSegment(1,1,15.0,&ssmbrIdx,&segmentIdx,&dist),S_OK);
//   TRY_TEST(ssmbrIdx,2);
//   TRY_TEST(segmentIdx,0);
//   TRY_TEST(IsEqual(dist,5.0),true);
//
//   // point on cantilever after last pier
//   TRY_TEST(bridge->SpanGirderToSegment(1,1,105.0,&ssmbrIdx,&segmentIdx,&dist),S_OK);
//   TRY_TEST(ssmbrIdx,2);
//   TRY_TEST(segmentIdx,1);
//   TRY_TEST(IsEqual(dist,20.0),true);


//   long spanIdx;
//   TRY_TEST(bridge->SegmentToSpanGirder( -1, 0, 0, 3.0,&spanIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SegmentToSpanGirder(100, 0, 0, 3.0,&spanIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1,-1, 0, 3.0,&spanIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1,10, 0, 3.0,&spanIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1, 0,-1, 3.0,&spanIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1, 0,10, 3.0,&spanIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1, 0, 0, 3.0,NULL,    &dist),E_POINTER);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1, 0, 0, 3.0,&spanIdx,NULL), E_POINTER);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1, 0, 0,-3.0,&spanIdx,&dist),E_INVALIDARG);
//   TRY_TEST(bridge->SegmentToSpanGirder(  1, 0, 0,55.0,&spanIdx,&dist),E_INVALIDARG);
//   
//   // fractional measure
//   TRY_TEST(bridge->SegmentToSpanGirder(1,0,0,-0.24,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,0);
//   TRY_TEST(IsEqual(dist,-2.0),true);
//
//   TRY_TEST(bridge->SegmentToSpanGirder(1,1,1,-0.84615384615384615384615384615385,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,1);
//   TRY_TEST(IsEqual(dist,5.0),true);
//
//   TRY_TEST(bridge->SegmentToSpanGirder(1,2,0,-0.066666666666666666666666666666667,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,1);
//   TRY_TEST(IsEqual(dist,15.0),true);
//
//   TRY_TEST(bridge->SegmentToSpanGirder(1,2,1,-0.8,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,1);
//   TRY_TEST(IsEqual(dist,105.0),true);
//
//   // absolute measure
//   TRY_TEST(bridge->SegmentToSpanGirder(1,0,0,3.0,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,0);
//   TRY_TEST(IsEqual(dist,-2.0),true);
//
//   TRY_TEST(bridge->SegmentToSpanGirder(1,1,1,27.5,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,1);
//   TRY_TEST(IsEqual(dist,5.0),true);
//
//   TRY_TEST(bridge->SegmentToSpanGirder(1,2,0,5.0,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,1);
//   TRY_TEST(IsEqual(dist,15.0),true);
//
//   TRY_TEST(bridge->SegmentToSpanGirder(1,2,1,20.0,&spanIdx,&dist),S_OK);
//   TRY_TEST(spanIdx,1);
//   TRY_TEST(IsEqual(dist,105.0),true);
}

