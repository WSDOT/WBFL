///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// TestTemporaryPierItemCollection.cpp: implementation of the CTestTemporaryPierItemCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTemporaryPierItemCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestTemporaryPierItemCollection::CTestTemporaryPierItemCollection()
{

}

CTestTemporaryPierItemCollection::~CTestTemporaryPierItemCollection()
{

}

void CTestTemporaryPierItemCollection::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 100.00, qcbAfter, qcbRight);

   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);

   stages->CreateStage(CComBSTR("Stage 1"),CComBSTR(""));

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);

   CComPtr<ISpan> span;
   spans->get_Item(0,&span);

   CComPtr<ITemporaryPierItemCollection> tempPiers;
   span->get_TemporaryPiers(&tempPiers);

   TRY_TEST(tempPiers != NULL, true);

   CollectionIndexType count;
   TRY_TEST(tempPiers->get_Count(NULL),E_POINTER);
   TRY_TEST(tempPiers->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   TRY_TEST(tempPiers->Add(11,-0.5,CComBSTR("NotValidStage")),GB_E_STAGE_NOT_FOUND);
   TRY_TEST(tempPiers->Add(11,-0.5,CComBSTR("Stage 1")),S_OK);
   TRY_TEST(tempPiers->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   tempPiers->Add(12,-0.5,CComBSTR("Stage 1"));
   tempPiers->Add(13,-0.6,CComBSTR("Stage 1"));
   tempPiers->Add(14,-0.7,CComBSTR("Stage 1"));
   tempPiers->Add(15,-0.8,CComBSTR("Stage 1"));
   tempPiers->Add(16,-0.9,CComBSTR("Stage 1"));

   tempPiers->get_Count(&count);
   TRY_TEST(count,6);

   CComPtr<ITemporaryPierItem> tempPierItem;
   TRY_TEST(tempPiers->get_Item(-1,&tempPierItem),E_INVALIDARG);
   TRY_TEST(tempPiers->get_Item(100,&tempPierItem),E_INVALIDARG);
   TRY_TEST(tempPiers->get_Item(3,NULL),E_POINTER);
   TRY_TEST(tempPiers->get_Item(3,&tempPierItem),S_OK);

   long id;
   tempPierItem->get_ID(&id);
   TRY_TEST(id,14);

   tempPierItem.Release();
   TRY_TEST(tempPiers->Find(16,NULL),E_POINTER);
   TRY_TEST(tempPiers->Find(100,&tempPierItem),E_FAIL);
   TRY_TEST(tempPiers->Find(16,&tempPierItem),S_OK);
   tempPierItem->get_ID(&id);
   TRY_TEST(id,16);

   tempPierItem.Release();
   TRY_TEST(tempPiers->RemoveByID(100),E_FAIL);
   TRY_TEST(tempPiers->RemoveByID(14), S_OK);

   tempPiers->get_Count(&count);
   TRY_TEST(count,5);

   tempPierItem.Release();
   TRY_TEST(tempPiers->RemoveByIndex(-1),E_INVALIDARG);
   TRY_TEST(tempPiers->RemoveByIndex(100),E_INVALIDARG);
   TRY_TEST(tempPiers->RemoveByIndex(2), S_OK);

   tempPiers->get_Count(&count);
   TRY_TEST(count,4);

   TRY_TEST(tempPiers->Clear(),S_OK);
   tempPiers->get_Count(&count);
   TRY_TEST(count,0);
   
   ///////////////////////////////////////
   // Test with event sink
   CComObject<CTestTemporaryPierItemCollection>* pTest;
   CComObject<CTestTemporaryPierItemCollection>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(tempPiers,punk,IID_ITemporaryPierItemCollectionEvents,&dwCookie),S_OK);

   ///////////////////////////////////////
   // Test Set with events
   pTest->InitEventTest();
   tempPiers->Add(11,-0.5,CComBSTR("Stage 1"));
   tempPiers->get_Count(&count);
   TRY_TEST(count,1);
   TRY_TEST(pTest->PassedEventTest(), true );

   tempPiers->Add(11,-0.5,CComBSTR("Stage 1"));
   tempPiers->Add(12,-0.5,CComBSTR("Stage 1"));
   tempPiers->Add(13,-0.6,CComBSTR("Stage 1"));
   tempPiers->Add(14,-0.7,CComBSTR("Stage 1"));
   tempPiers->Add(15,-0.8,CComBSTR("Stage 1"));
   tempPiers->Add(16,-0.9,CComBSTR("Stage 1"));

   pTest->InitEventTest();
   tempPiers->get_Count(&count);
   TRY_TEST(count,6);
   tempPiers->RemoveByID(14);
   tempPiers->get_Count(&count);
   TRY_TEST(count,5);
   TRY_TEST(pTest->PassedEventTest(), true );

   // bubble events
   tempPierItem.Release();
   tempPiers->get_Item(0,&tempPierItem);

   pTest->InitEventTest();
   tempPierItem->put_Location(2.5);
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
   TRY_TEST(AtlUnadvise(tempPiers,IID_ITemporaryPierItemCollectionEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(tempPiers);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ITemporaryPierItemCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(tempPiers,IID_ITemporaryPierItemCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(tempPiers,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestTemporaryPierItemCollection::OnTemporaryPierItemChanged(ITemporaryPierItem* tpi)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestTemporaryPierItemCollection::OnTemporaryPierItemAdded(long idx)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestTemporaryPierItemCollection::OnTemporaryPierItemRemoved(long id)
{
   Pass();
   return S_OK;
}
