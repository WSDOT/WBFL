///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
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

// TestColumn.cpp: implementation of the CTestColumn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestColumn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestColumn::CTestColumn()
{

}

CTestColumn::~CTestColumn()
{

}

void CTestColumn::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);

   CComPtr<ITransversePierDescription> tpd;
   pier->CreateTransversePierDescription();
   pier->get_TransversePierDescription(&tpd);

   CComPtr<IColumn> column;
   TRY_TEST(tpd->get_Column(-1,&column),E_INVALIDARG);
   TRY_TEST(tpd->get_Column(100,&column),E_INVALIDARG);
   TRY_TEST(tpd->get_Column(0,NULL),E_POINTER);
   TRY_TEST(tpd->get_Column(0,&column),S_OK);
   TRY_TEST(column != NULL,true);

   Float64 height;
   TRY_TEST(column->get_Height(NULL),E_POINTER);
   TRY_TEST(column->get_Height(&height),S_OK);
   TRY_TEST(IsEqual(height,0.0),true);

   Float64 baseOffset;
   TRY_TEST(column->get_BaseOffset(NULL),E_POINTER);
   TRY_TEST(column->get_BaseOffset(&baseOffset),S_OK);
   TRY_TEST(IsEqual(baseOffset,0.0),true);

   CollectionIndexType count;
   TRY_TEST(column->get_SegmentCount(NULL),E_POINTER);
   TRY_TEST(column->get_SegmentCount(&count),S_OK);
   TRY_TEST(count,0);

   VARIANT_BOOL bFractional;
   TRY_TEST(column->get_Fractional(NULL),E_POINTER);
   TRY_TEST(column->get_Fractional(&bFractional),S_OK);
   TRY_TEST(bFractional,VARIANT_FALSE);

   VARIANT_BOOL bSymmetrical;
   TRY_TEST(column->get_Symmetrical(NULL),E_POINTER);
   TRY_TEST(column->get_Symmetrical(&bSymmetrical),S_OK);
   TRY_TEST(bSymmetrical,VARIANT_FALSE);

   ///////////////////////////////////////
   // Test with event sink and transactions
   CComObject<CTestColumn>* pTest;
   CComObject<CTestColumn>::CreateInstance(&pTest);
   pTest->AddRef();
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(column,punk,IID_IColumnEvents,&dwCookie),S_OK);

   TRY_TEST(column->put_Height(-1),E_INVALIDARG);
   TRY_TEST(column->put_Height(50),S_OK);
   pTest->InitEventTest();
   TRY_TEST(column->put_Height(100),S_OK);
   column->get_Height(&height);
   TRY_TEST(IsEqual(height,100.0),true);
   TRY_TEST(pTest->PassedEventTest(),true);

   TRY_TEST(column->put_BaseOffset(-1),S_OK);
   TRY_TEST(column->put_BaseOffset( 1),S_OK);
   TRY_TEST(column->put_BaseOffset( 0),S_OK);
   pTest->InitEventTest();
   column->put_BaseOffset(10.0);
   column->get_BaseOffset(&baseOffset);
   TRY_TEST(IsEqual(baseOffset,10.0),true);
   TRY_TEST(pTest->PassedEventTest(),true);

   CComPtr<IPrismaticSegment> newSegment;
   newSegment.CoCreateInstance(CLSID_PrismaticSegment);

   TRY_TEST(column->AddSegment(newSegment),S_OK);
   TRY_TEST(column->AddSegment(newSegment),S_OK);
   pTest->InitEventTest();
   column->AddSegment(newSegment);
   column->get_SegmentCount(&count);
   TRY_TEST(count,3);
   TRY_TEST(pTest->PassedEventTest(),true);

   CComPtr<ISegment> segment;
   TRY_TEST(column->get_Segment(-1,&segment),E_INVALIDARG);
   TRY_TEST(column->get_Segment(10,&segment),E_INVALIDARG);
   TRY_TEST(column->get_Segment( 0,NULL),E_POINTER);
   TRY_TEST(column->get_Segment( 0,&segment),S_OK);
//   CComPtr<ISegmentCrossSection> section;
//   segment->get_CrossSection(&section);
//   section->put_Area(10.0);

   pTest->InitEventTest();
   TRY_TEST(column->CopySegmentTo(-1,1),E_INVALIDARG);
   TRY_TEST(column->CopySegmentTo(10,1),E_INVALIDARG);
   TRY_TEST(column->CopySegmentTo(0,-1),E_INVALIDARG);
   TRY_TEST(column->CopySegmentTo(0,10),E_INVALIDARG);
   TRY_TEST(column->CopySegmentTo(0,1),S_OK);

   column->get_SegmentCount(&count);
   TRY_TEST(count,4);
   TRY_TEST(pTest->PassedEventTest(),true);

   column->AddSegment(newSegment);
   segment.Release();
   column->get_Segment(0,&segment);
   segment->put_Length(10.0);
   segment.Release();
   column->get_Segment(1,&segment);
   segment->put_Length(20.0);
   segment.Release();
   column->get_Segment(2,&segment);
   segment->put_Length(30.0);

   Float64 length;
   pTest->InitEventTest();
   TRY_TEST(column->MoveSegmentTo(-1,1),E_INVALIDARG);
   TRY_TEST(column->MoveSegmentTo(10,1),E_INVALIDARG);
   TRY_TEST(column->MoveSegmentTo(0,-1),E_INVALIDARG);
   TRY_TEST(column->MoveSegmentTo(0,10),E_INVALIDARG);
   TRY_TEST(column->MoveSegmentTo(0,1),S_OK);
   segment.Release();
   column->get_Segment(0,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,20.0),true);
   segment.Release();
   column->get_Segment(1,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,10.0),true);
   TRY_TEST(pTest->PassedEventTest(),true);

   pTest->InitEventTest();
   TRY_TEST(column->InsertSegment(-1,newSegment),E_INVALIDARG);
   TRY_TEST(column->InsertSegment(10,newSegment),E_INVALIDARG);
   TRY_TEST(column->InsertSegment( 1,newSegment),S_OK);
   column->get_SegmentCount(&count);
   TRY_TEST(count,6);
   segment.Release();
   column->get_Segment(1,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,1.0),true);
   TRY_TEST(pTest->PassedEventTest(),true);

   pTest->InitEventTest();
   TRY_TEST(column->RemoveSegment(-1),E_INVALIDARG);
   TRY_TEST(column->RemoveSegment(10),E_INVALIDARG);
   TRY_TEST(column->RemoveSegment( 0),S_OK);
   column->get_SegmentCount(&count);
   TRY_TEST(count,5);
   TRY_TEST(pTest->PassedEventTest(),true);

   pTest->InitEventTest();
   TRY_TEST(column->RemoveSegments(),S_OK);
   column->get_SegmentCount(&count);
   TRY_TEST(count,0);
   TRY_TEST(pTest->PassedEventTest(),true);

   // bubbled events
//   segment.Release();
//   section.Release();
//   column->get_Segment(0,&segment);
//   segment->get_CrossSection(&section);
//   CComPtr<IStressPointCollection> stressPoints;
//   section->get_StressPoints(&stressPoints);
//
//   pTest->InitEventTest();
//   stressPoints->Add();
//   TRY_TEST(pTest->PassedEventTest(),true);
//
//   CComPtr<IStressPoint> stressPoint;
//   stressPoints->get_Item(0,&stressPoint);
//
//   pTest->InitEventTest();
//   stressPoint->put_Sa(10.0);
//   TRY_TEST(pTest->PassedEventTest(),true);
//
//   pTest->InitEventTest();
//   section->put_Area(30.0);
//   TRY_TEST(pTest->PassedEventTest(),true);

   // Done with events
   TRY_TEST(AtlUnadvise(column,IID_IColumnEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(column);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IColumn ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(column,IID_IColumn,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(column,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}


STDMETHODIMP CTestColumn::OnColumnChanged(IColumn* mbr)
{
   Pass();
   return S_OK;
}