///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// TestLongitudinalPierDescription.cpp: implementation of the CTestLongitudinalPierDescription class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLongitudinalPierDescription.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLongitudinalPierDescription::CTestLongitudinalPierDescription()
{

}

CTestLongitudinalPierDescription::~CTestLongitudinalPierDescription()
{

}

void CTestLongitudinalPierDescription::Test()
{
   // Create a default bridge
   CComPtr<IGenericBridge> bridge;
   bridge.CoCreateInstance(CLSID_GenericBridge);

   bridge->InsertSpanAndPier(0, 100.00, qcbAfter,qcbLeft);


   CComPtr<IStageCollection> stages;
   bridge->get_Stages(&stages);
   stages->CreateStage(CComBSTR("Stage 2"),CComBSTR(""));

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> pier;
   piers->get_Item(0,&pier);

   CComPtr<ILongitudinalPierDescription> lpd;
   pier->get_LongitudinalPierDescription(&lpd);

   TRY_TEST(lpd != NULL, true);

   // Verify default values
   Float64 offset;
   TRY_TEST(lpd->get_BaseOffset(NULL),E_POINTER);
   TRY_TEST(lpd->get_BaseOffset(&offset),S_OK);
   TRY_TEST(IsZero(offset),true);

   ConnectivityType connectivity;
   TRY_TEST(lpd->get_Connectivity(NULL),E_POINTER);
   TRY_TEST(lpd->get_Connectivity(&connectivity),S_OK);
   TRY_TEST(connectivity,ctPinned);

   CComBSTR bstrStage;
   TRY_TEST(lpd->get_ContinuityStage(NULL),E_POINTER);
   TRY_TEST(lpd->get_ContinuityStage(&bstrStage),S_OK);
   TRY_TEST(bstrStage == CComBSTR("Stage 1"),true);

   VARIANT_BOOL bFractional;
   TRY_TEST(lpd->get_Fractional(NULL),E_POINTER);
   TRY_TEST(lpd->get_Fractional(&bFractional),S_OK);
   TRY_TEST(bFractional,VARIANT_FALSE);

   Float64 height;
   TRY_TEST(lpd->get_Height(NULL),E_POINTER);
   TRY_TEST(lpd->get_Height(&height),S_OK);
   TRY_TEST(IsEqual(height,1.0),true);

   Float64 length;
   TRY_TEST(lpd->get_Length(NULL),E_POINTER);
   TRY_TEST(lpd->get_Length(&length),S_OK);
   TRY_TEST(IsZero(length),true);

   CComPtr<IPier> parentPier;
   TRY_TEST(lpd->get_Pier(NULL),E_POINTER);
   TRY_TEST(lpd->get_Pier(&parentPier),S_OK);
   TRY_TEST(pier.IsEqualObject(parentPier),true);

   VARIANT_BOOL bSymmetrical;
   TRY_TEST(lpd->get_Symmetrical(NULL),E_POINTER);
   TRY_TEST(lpd->get_Symmetrical(&bSymmetrical),S_OK);
   TRY_TEST(bSymmetrical,VARIANT_FALSE);

   CollectionIndexType count;
   TRY_TEST(lpd->get_SegmentCount(NULL),E_POINTER);
   TRY_TEST(lpd->get_SegmentCount(&count),S_OK);
   TRY_TEST(count,0);

   // Manipulate segments
   
   // first change connectivity so that it is not a zero-height support
   TRY_TEST(lpd->put_Connectivity(ctHingedIntegral),S_OK);
   lpd->get_Connectivity(&connectivity);
   TRY_TEST(connectivity,ctHingedIntegral);

   CComPtr<IPrismaticSegment> newSegment;
   newSegment.CoCreateInstance(CLSID_PrismaticSegment);
   TRY_TEST(lpd->AddSegment(newSegment),S_OK);
   TRY_TEST(lpd->AddSegment(newSegment),S_OK);
   TRY_TEST(lpd->AddSegment(newSegment),S_OK);

   TRY_TEST(lpd->get_SegmentCount(&count),S_OK);
   TRY_TEST(count,3);

   TRY_TEST(lpd->put_BaseOffset(-3.0),S_OK);
   TRY_TEST(lpd->put_BaseOffset( 0.0),S_OK);
   TRY_TEST(lpd->put_BaseOffset( 3.0),S_OK);

   TRY_TEST(lpd->put_Height(-1.0),E_INVALIDARG);
   TRY_TEST(lpd->put_Height( 0.0),S_OK);
   TRY_TEST(lpd->put_Height( 4.0),S_OK);

   lpd->get_Length(&length);
   TRY_TEST(IsEqual(length,5.0),true);

   CComPtr<IFilteredSegmentCollection> segments;
   TRY_TEST(lpd->GetMemberSegments(NULL),E_POINTER);
   TRY_TEST(lpd->GetMemberSegments(&segments),S_OK);

   CComPtr<IEnumSegment> enumSegments;
   segments->get__EnumElements(&enumSegments);
   CComPtr<ISegment> segment;
   while ( enumSegments->Next(1,&segment,NULL) != S_FALSE )
   {
      segment->put_Length(2.5);
      segment.Release();
   }

   segment.Release();
   lpd->get_Segment(0,&segment);
   segment->put_Length(1.0);

   segment.Release();
   lpd->get_Segment(1,&segment);
   segment->put_Length(2.0);

   segment.Release();
   lpd->get_Segment(2,&segment);
   segment->put_Length(3.0);

   // MoveSegmentTo
   TRY_TEST(lpd->MoveSegmentTo(-1,1),E_INVALIDARG);
   TRY_TEST(lpd->MoveSegmentTo(100,1),E_INVALIDARG);
   TRY_TEST(lpd->MoveSegmentTo(0,-1),E_INVALIDARG);
   TRY_TEST(lpd->MoveSegmentTo(0,100),E_INVALIDARG);
   TRY_TEST(lpd->MoveSegmentTo(0,1),S_OK);
   lpd->get_SegmentCount(&count);
   TRY_TEST(count,3);
   segment.Release();
   lpd->get_Segment(0,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,2.0),true);
   segment.Release();
   lpd->get_Segment(1,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,1.0),true);

   // CopySegmentTo
   TRY_TEST(lpd->CopySegmentTo(-1,1),E_INVALIDARG);
   TRY_TEST(lpd->CopySegmentTo(100,1),E_INVALIDARG);
   TRY_TEST(lpd->CopySegmentTo(0,-1),E_INVALIDARG);
   TRY_TEST(lpd->CopySegmentTo(0,100),E_INVALIDARG);
   TRY_TEST(lpd->CopySegmentTo(0,2),S_OK);
   lpd->get_SegmentCount(&count);
   TRY_TEST(count,4);
   segment.Release();
   lpd->get_Segment(0,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,2.0),true);
   segment.Release();
   lpd->get_Segment(2,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,2.0),true);

   // RemoveSegment
   TRY_TEST(lpd->RemoveSegment(-1),E_INVALIDARG);
   TRY_TEST(lpd->RemoveSegment(100),E_INVALIDARG);
   TRY_TEST(lpd->RemoveSegment(1), S_OK);
   lpd->get_SegmentCount(&count);
   TRY_TEST(count,3);

   // RemoveSegments
   TRY_TEST(lpd->RemoveSegments(),S_OK);
   lpd->get_SegmentCount(&count);
   TRY_TEST(count,0);

   // ReverseSegments
   TRY_TEST(lpd->AddSegment(newSegment),S_OK);
   TRY_TEST(lpd->AddSegment(newSegment),S_OK);
   TRY_TEST(lpd->AddSegment(newSegment),S_OK);

   segment.Release();
   lpd->get_Segment(0,&segment);
   segment->put_Length(1.0);

   segment.Release();
   lpd->get_Segment(1,&segment);
   segment->put_Length(2.0);

   segment.Release();
   lpd->get_Segment(2,&segment);
   segment->put_Length(3.0);

   TRY_TEST(lpd->ReverseSegments(),S_OK);

   segment.Release();
   lpd->get_Segment(0,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,3.0),true);

   segment.Release();
   lpd->get_Segment(1,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,2.0),true);

   segment.Release();
   lpd->get_Segment(2,&segment);
   segment->get_Length(&length);
   TRY_TEST(IsEqual(length,1.0),true);

   // GetSegmentForMemberLocation
   CComPtr<ISegmentItem> segItem;
   Float64 dist;
   lpd->put_BaseOffset(0.0);
   TRY_TEST(lpd->GetSegmentForMemberLocation(2.5,&dist,NULL),E_POINTER);
   TRY_TEST(lpd->GetSegmentForMemberLocation(2.5,NULL,&segItem),E_POINTER);
   TRY_TEST(lpd->GetSegmentForMemberLocation(-2,&dist,&segItem),GB_E_LOCATION_OUT_OF_RANGE);
   //TRY_TEST(lpd->GetSegmentForMemberLocation(200,&dist,&segItem),GB_E_LOCATION_OUT_OF_RANGE);
   TRY_TEST(lpd->GetSegmentForMemberLocation(2.5,&dist,&segItem),S_OK);
   CollectionIndexType position;
   bstrStage.Empty();
   segItem->get_RelPosition(&position);
   TRY_TEST(position,0);
   TRY_TEST(IsEqual(dist,2.5),true);

   segItem.Release();
   bstrStage.Empty();
   TRY_TEST(lpd->GetSegmentForMemberLocation(0,&dist,&segItem),S_OK);
   segItem->get_RelPosition(&position);
   TRY_TEST(position,0);
   TRY_TEST(IsEqual(dist,0.0),true);

   segItem.Release();
   bstrStage.Empty();
   TRY_TEST(lpd->GetSegmentForMemberLocation(3.0,&dist,&segItem),S_OK);
   segItem->get_RelPosition(&position);
   TRY_TEST(position,0);
   TRY_TEST(IsEqual(dist,3.0),true);

   segItem.Release();
   bstrStage.Empty();
   TRY_TEST(lpd->GetSegmentForMemberLocation(3.001,&dist,&segItem),S_OK);
   segItem->get_RelPosition(&position);
   TRY_TEST(position,1);
   TRY_TEST(IsEqual(dist,0.001),true);

   segItem.Release();
   bstrStage.Empty();
   TRY_TEST(lpd->GetSegmentForMemberLocation(3.5,&dist,&segItem),S_OK);
   segItem->get_RelPosition(&position);
   TRY_TEST(position,1);
   TRY_TEST(IsEqual(dist,0.5),true);

   segItem.Release();
   bstrStage.Empty();
   TRY_TEST(lpd->GetSegmentForMemberLocation(-0.5,&dist,&segItem),S_OK);
   segItem->get_RelPosition(&position);
   TRY_TEST(position,0);
   TRY_TEST(IsEqual(dist,2.0),true);

   segItem.Release();
   bstrStage.Empty();
   TRY_TEST(lpd->GetSegmentForMemberLocation(-0.99,&dist,&segItem),S_OK);
   segItem->get_RelPosition(&position);
   TRY_TEST(position,1);
   TRY_TEST(IsEqual(dist,0.96),true);

   TRY_TEST(lpd->get_SegmentLength(NULL),E_POINTER);
   TRY_TEST(lpd->get_SegmentLength(&length),S_OK);
   TRY_TEST(IsEqual(length,6.0),true);

   ///////////////////////////////////////
   // Test with event sink

   // start off with each stage having 2 segments
   lpd->RemoveSegments();

   lpd->AddSegment(newSegment);
   lpd->AddSegment(newSegment);

   CComObject<CTestLongitudinalPierDescription>* pTest;
   CComObject<CTestLongitudinalPierDescription>::CreateInstance(&pTest);
   pTest->AddRef();
   
   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTest);
   TRY_TEST(AtlAdvise(lpd,punk,IID_ILongitudinalPierDescriptionEvents,&dwCookie),S_OK);

   //////////////////////////////////////
   // Test Set with transactions and events
   pTest->InitEventTest();
   lpd->AddSegment(newSegment);
   lpd->get_SegmentCount(&count);
   TRY_TEST(count,3);
   TRY_TEST(pTest->PassedEventTest(), true );

   lpd->put_BaseOffset(1.0);
   pTest->InitEventTest();
   lpd->put_BaseOffset(2.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   lpd->put_Connectivity(ctHinged);
   pTest->InitEventTest();
   lpd->put_Connectivity(ctIntegral);
   TRY_TEST(pTest->PassedEventTest(), true );

   lpd->put_ContinuityStage(CComBSTR("Stage 1"));
   pTest->InitEventTest();
   lpd->put_ContinuityStage(CComBSTR("Stage 2"));
   TRY_TEST(pTest->PassedEventTest(), true );

   lpd->put_Fractional(VARIANT_FALSE);
   pTest->InitEventTest();
   lpd->put_Fractional(VARIANT_TRUE);
   TRY_TEST(pTest->PassedEventTest(), true );

   lpd->put_Height(10.0);
   pTest->InitEventTest();
   lpd->put_Height(20.0);
   TRY_TEST(pTest->PassedEventTest(), true );

   lpd->put_Symmetrical(VARIANT_FALSE);
   pTest->InitEventTest();
   lpd->put_Symmetrical(VARIANT_TRUE);
   TRY_TEST(pTest->PassedEventTest(), true );

   // add a few segments and give them easily identifiable lengths so we can test CopyTo, MoveTo, Remove, and Reverse
   lpd->AddSegment(newSegment);
   segment.Release();
   lpd->get_Segment(0,&segment);
   segment->put_Length(1.0);

   segment.Release();
   lpd->get_Segment(1,&segment);
   segment->put_Length(2.0);

   segment.Release();
   lpd->get_Segment(2,&segment);
   segment->put_Length(3.0);

   // Reverse
//   pTest->InitEventTest();
//   lpd->ReverseSegments();
//   TRY_TEST(pTest->PassedEventTest(), true );
//   segment.Release();
//   lpd->get_Segment(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,3.0),true);
//   segment.Release();
//   lpd->get_Segment(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,2.0),true);
//   segment.Release();
//   lpd->get_Segment(2,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   // CopyTo
//   pTest->InitEventTest();
//   lpd->CopySegmentTo(0,2);
//   TRY_TEST(pTest->PassedEventTest(), true );
//   lpd->get_SegmentCount(&count);
//   TRY_TEST(count,4);
//   segment.Release();
//   lpd->get_Segment(2,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   // MoveTo
//   pTest->InitEventTest();
//   lpd->MoveSegmentTo(0,2);
//   TRY_TEST(pTest->PassedEventTest(), true );
//   segment.Release();
//   lpd->get_Segment(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,2.0),true);
//   segment.Release();
//   lpd->get_Segment(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,3.0),true);
//   segment.Release();
//   lpd->get_Segment(2,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   // InsertSegment
//   pTest->InitEventTest();
//   lpd->InsertSegment(1,newSegment);
//   TRY_TEST(pTest->PassedEventTest(), true );
//   lpd->get_SegmentCount(&count);
//   TRY_TEST(count,4);
//
//   // RemoveSegment
//   pTest->InitEventTest();
//   lpd->RemoveSegment(1);
//   TRY_TEST(pTest->PassedEventTest(), true );
//   lpd->get_SegmentCount(&count);
//   TRY_TEST(count,2);
//
//   // RemoveSegments
//   pTest->InitEventTest();
//   lpd->RemoveSegments();
//   TRY_TEST(pTest->PassedEventTest(), true );
//   lpd->get_SegmentCount(&count);
//   TRY_TEST(count,0);
//
//   // Bubbled events
//   segment.Release();
//   lpd->get_Segment(0,&segment);
//
//   pTest->InitEventTest();
//   segment->put_Length(5.5);
//   TRY_TEST(pTest->PassedEventTest(), true );

   // Done with events
   TRY_TEST(AtlUnadvise(lpd,IID_ILongitudinalPierDescriptionEvents,dwCookie),S_OK);
   pTest->Release();

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(lpd);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ILongitudinalPierDescription ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(lpd,IID_ILongitudinalPierDescription,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(lpd,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestLongitudinalPierDescription::OnChanged()
{
   Pass();
   return S_OK;
}