///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestSuperstructureMember.cpp: implementation of the CTestSuperstructureMember class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSuperstructureMember.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSuperstructureMember::CTestSuperstructureMember()
{

}

CTestSuperstructureMember::~CTestSuperstructureMember()
{

}

void CTestSuperstructureMember::Test()
{
//   // Create a default bridge
//   CComPtr<IGenericBridge> bridge;
//   bridge.CoCreateInstance(CLSID_GenericBridge);
//
//   // Create a second stage (we will need it for testing)
//   CComPtr<IStageCollection> stages;
//   bridge->get_Stages(&stages);
//   stages->CreateStage(CComBSTR("Stage 2"),CComBSTR(""));
//
//   // Drill down and get a stress point
//   CComPtr<ISuperstructureMemberCollection> ssms;
//   bridge->get_SuperstructureMembers(0,&ssms);
//
//   ssms->Add();
//
//   CComPtr<ISuperstructureMember> mbr;
//   ssms->get_Item(0,&mbr);
//
//   TRY_TEST(mbr != nullptr, true);
//
//
//   // Test default values
//   long nSegCount;
//   TRY_TEST(mbr->get_SegmentCount(nullptr),E_POINTER);
//   TRY_TEST(mbr->get_SegmentCount(&nSegCount),S_OK);
//   TRY_TEST(nSegCount,0);
//
//   VARIANT_BOOL bFractional;
//   TRY_TEST(mbr->get_Fractional(nullptr),E_POINTER);
//   TRY_TEST(mbr->get_Fractional(&bFractional),S_OK);
//   TRY_TEST(bFractional,VARIANT_FALSE);
//
//   Float64 length;
//   TRY_TEST(mbr->get_Length(nullptr),E_POINTER);
//   TRY_TEST(mbr->get_Length(&length),S_OK);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   CComPtr<ISegment> segment;
//   TRY_TEST(mbr->get_Segment(0,nullptr),E_POINTER);
//   TRY_TEST(mbr->get_Segment(-1,&segment),E_INVALIDARG);
//   TRY_TEST(mbr->get_Segment(100,&segment),E_INVALIDARG);
//   TRY_TEST(mbr->get_Segment(0,&segment),E_INVALIDARG);
//
//   VARIANT_BOOL bSymmetrical;
//   TRY_TEST(mbr->get_Symmetrical(nullptr),E_POINTER);
//   TRY_TEST(mbr->get_Symmetrical(&bSymmetrical),S_OK);
//   TRY_TEST(bSymmetrical,VARIANT_FALSE);
//
//   CComBSTR bstrReleaseStage;
//   ReleaseType releaseType;
//   TRY_TEST(mbr->GetEndRelease(etStart,&bstrReleaseStage,&releaseType),S_OK);
//   TRY_TEST(bstrReleaseStage == CComBSTR(""), true );
//   TRY_TEST(releaseType, rtNone);
//
//   ////////////////////////////////////////////
//   // Test some methods...
//
//   // AddSegment
//   CComPtr<IPrismaticSegment> newSegment;
//   newSegment.CoCreateInstance(CLSID_PrismaticSegment);
//
//   TRY_TEST(mbr->AddSegment(newSegment),S_OK);
//   mbr->get_SegmentCount(&nSegCount);
//   TRY_TEST(nSegCount,1);
//   TRY_TEST(mbr->AddSegment(newSegment),S_OK);
//   mbr->get_SegmentCount(&nSegCount);
//   TRY_TEST(nSegCount,2);
//
//   // CopySegment
//   segment.Release();
//   mbr->get_Segment(0,&segment);
//   segment->put_Length(10.0);
//
//   TRY_TEST(mbr->CopySegmentTo(-1,1),E_INVALIDARG);
//   TRY_TEST(mbr->CopySegmentTo(100,1),E_INVALIDARG);
//   TRY_TEST(mbr->CopySegmentTo(0,-1),E_INVALIDARG);
//   TRY_TEST(mbr->CopySegmentTo(0,100),E_INVALIDARG);
//   TRY_TEST(mbr->CopySegmentTo(0,0),S_OK); // nothing actually changes
//   TRY_TEST(mbr->CopySegmentTo(0,1),S_OK);
//
//   segment.Release();
//   mbr->get_Segment(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   CComPtr<ISegment> copySegment;
//   mbr->get_Segment(1,&copySegment);
//   copySegment->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   TRY_TEST(segment.IsEqualObject(copySegment),false);
//
//   // Fractional measure
//
//   CComPtr<ISegment> segment1, segment2;
//   mbr->get_Segment(0,&segment1);
//   mbr->get_Segment(1,&segment2);
//
//   mbr->put_Length(20);
//
//   // make length of segments shorter than length of member
//   segment1->put_Length(5);
//   segment2->put_Length(10);
// 
//   TRY_TEST(mbr->get_SegmentLength(nullptr),E_POINTER);
//   TRY_TEST(mbr->get_SegmentLength(&length),S_OK);
//   TRY_TEST(IsEqual(length,15.0),true);
//
//   // Set to current value... do nothing
//   TRY_TEST(mbr->put_Fractional(VARIANT_FALSE),S_OK);
//   segment1->get_Length(&length);
//   TRY_TEST(IsEqual(length,5.0),true);
//   segment2->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   TRY_TEST(mbr->put_Fractional(VARIANT_TRUE),S_OK);
//   segment1->get_Length(&length);
//   TRY_TEST(IsEqual(length,-0.25),true);
//   segment2->get_Length(&length);
//   TRY_TEST(IsEqual(length,-0.50),true);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   TRY_TEST(mbr->put_Fractional(VARIANT_FALSE),S_OK);
//   segment1->get_Length(&length);
//   TRY_TEST(IsEqual(length,5.0),true);
//   segment2->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   // make length of segments long than length of member
//   segment1->put_Length(15);
//   segment2->put_Length(10);
// 
//   TRY_TEST(mbr->get_SegmentLength(nullptr),E_POINTER);
//   TRY_TEST(mbr->get_SegmentLength(&length),S_OK);
//   TRY_TEST(IsEqual(length,25.0),true);
//
//   // Set to current value... do nothing
//   TRY_TEST(mbr->put_Fractional(VARIANT_FALSE),S_OK);
//   segment1->get_Length(&length);
//   TRY_TEST(IsEqual(length,15.0),true);
//   segment2->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   TRY_TEST(mbr->put_Fractional(VARIANT_TRUE),S_OK);
//   segment1->get_Length(&length);
//   TRY_TEST(IsEqual(length,-0.75),true);
//   segment2->get_Length(&length);
//   TRY_TEST(IsEqual(length,-0.50),true);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   TRY_TEST(mbr->put_Fractional(VARIANT_FALSE),S_OK);
//   segment1->get_Length(&length);
//   TRY_TEST(IsEqual(length,15.0),true);
//   segment2->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   // GetSegmentForMemberLocation
//   segment1->put_Length( 5);
//   segment2->put_Length(10);
//   Float64 dist;
//   CComPtr<ISegmentItem> segItem;
//   TRY_TEST(mbr->GetSegmentForMemberLocation(2.5,&dist,nullptr),E_POINTER);
//   TRY_TEST(mbr->GetSegmentForMemberLocation(2.5,nullptr,&segItem),E_POINTER);
//   TRY_TEST(mbr->GetSegmentForMemberLocation(-2,&dist,&segItem),GB_E_LOCATION_OUT_OF_RANGE);
//   TRY_TEST(mbr->GetSegmentForMemberLocation(200,&dist,&segItem),GB_E_LOCATION_OUT_OF_RANGE);
//   TRY_TEST(mbr->GetSegmentForMemberLocation(2.5,&dist,&segItem),S_OK);
//   long position;
//   segItem->get_RelPosition(&position);
//   TRY_TEST(position,0);
//   TRY_TEST(IsEqual(dist,2.5),true);
//
//   segItem.Release();
//   TRY_TEST(mbr->GetSegmentForMemberLocation(0,&dist,&segItem),S_OK);
//   segItem->get_RelPosition(&position);
//   TRY_TEST(position,0);
//   TRY_TEST(IsEqual(dist,0.0),true);
//
//   segItem.Release();
//   TRY_TEST(mbr->GetSegmentForMemberLocation(5.0,&dist,&segItem),S_OK);
//   segItem->get_RelPosition(&position);
//   TRY_TEST(position,0);
//   TRY_TEST(IsEqual(dist,5.0),true);
//
//   segItem.Release();
//   TRY_TEST(mbr->GetSegmentForMemberLocation(5.001,&dist,&segItem),S_OK);
//   segItem->get_RelPosition(&position);
//   TRY_TEST(position,1);
//   TRY_TEST(IsEqual(dist,0.001),true);
//
//   segItem.Release();
//   TRY_TEST(mbr->GetSegmentForMemberLocation(18,&dist,&segItem),S_OK);
//   segItem->get_RelPosition(&position);
//   TRY_TEST(position,1);
//   TRY_TEST(IsEqual(dist,13.0),true);
//
//   segItem.Release();
//   TRY_TEST(mbr->GetSegmentForMemberLocation(-0.5,&dist,&segItem),S_OK);
//   segItem->get_RelPosition(&position);
//   TRY_TEST(position,1);
//   TRY_TEST(IsEqual(dist,5.0),true);
//
//   segItem.Release();
//   TRY_TEST(mbr->GetSegmentForMemberLocation(-0.99,&dist,&segItem),S_OK);
//   segItem->get_RelPosition(&position);
//   TRY_TEST(position,1);
//   TRY_TEST(IsEqual(dist,14.8),true);
//
//   // RemoveSegments()
//   TRY_TEST(mbr->RemoveSegments(),S_OK);
//   TRY_TEST(mbr->get_SegmentCount(&nSegCount),S_OK);
//   TRY_TEST(nSegCount,0);
//
//   // GetMemberSegments()
//   // Gets the segments, stretched or shrunk to fill the length of the member
//   mbr->AddSegment(newSegment);
//   mbr->AddSegment(newSegment);
//
//   segment1.Release();
//   segment2.Release();
//   mbr->get_Segment(0,&segment1);
//   mbr->get_Segment(1,&segment2);
//
//   // make length of segments shorter than member... last segment should be stretched
//   segment1->put_Length(5);
//   segment2->put_Length(10);
//
//   CComPtr<IFilteredSegmentCollection> segments;
//   TRY_TEST(mbr->GetMemberSegments(nullptr),E_POINTER);
//   TRY_TEST(mbr->GetMemberSegments(&segments),S_OK);
//   segments->get_Count(&nSegCount);
//   TRY_TEST(nSegCount,2);
//   segment.Release();
//   segments->get_Item(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,5.0),true);
//
//   segment.Release();
//   segments->get_Item(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,15.0),true);
//
//
//   // make length of segments longer than member... last segment should be shrunk
//   segment1->put_Length(15);
//   segment2->put_Length(10);
//
//   segments.Release();
//   TRY_TEST(mbr->GetMemberSegments(nullptr),E_POINTER);
//   TRY_TEST(mbr->GetMemberSegments(&segments),S_OK);
//   segments->get_Count(&nSegCount);
//   TRY_TEST(nSegCount,2);
//   segment.Release();
//   segments->get_Item(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,15.0),true);
//
//   segment.Release();
//   segments->get_Item(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,5.0),true);
//
//   // symmetrical segments
//   
//   // Make segments shorter than half the member length
//   segment1->put_Length(1.0);
//   segment2->put_Length(5.0);
//
//   TRY_TEST(mbr->put_Symmetrical(VARIANT_TRUE),S_OK);
//
//   segments.Release();
//   TRY_TEST(mbr->GetMemberSegments(&segments),S_OK);
//   segments->get_Count(&nSegCount);
//   TRY_TEST(nSegCount,3);
//
//   segment.Release();
//   segments->get_Item(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   segment.Release();
//   segments->get_Item(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,18.0),true);
//
//   segment.Release();
//   segments->get_Item(2,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   
//   // Make segments longer than half the member length
//   segment1->put_Length(5.0);
//   segment2->put_Length(10.0);
//
//   TRY_TEST(mbr->put_Symmetrical(VARIANT_TRUE),S_OK);
//
//   segments.Release();
//   TRY_TEST(mbr->GetMemberSegments(&segments),S_OK);
//   segments->get_Count(&nSegCount);
//   TRY_TEST(nSegCount,3);
//
//   segment.Release();
//   segments->get_Item(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,5.0),true);
//
//   segment.Release();
//   segments->get_Item(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   segment.Release();
//   segments->get_Item(2,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,5.0),true);
//
//   // InsertSegment()
//   mbr->RemoveSegments();
//
//   mbr->AddSegment(newSegment);
//   mbr->AddSegment(newSegment);
//   segment.Release();
//   mbr->get_Segment(0,&segment);
//   segment->put_Length(2.0);
//   segment.Release();
//   mbr->get_Segment(1,&segment);
//   segment->put_Length(3.0);
//
//   TRY_TEST(mbr->InsertSegment(-1,newSegment),E_INVALIDARG);
//   TRY_TEST(mbr->InsertSegment(100,newSegment),E_INVALIDARG);
//   TRY_TEST(mbr->InsertSegment(1,nullptr),E_INVALIDARG);
//   TRY_TEST(mbr->InsertSegment(1,newSegment),S_OK);
//   mbr->get_SegmentCount(&nSegCount);
//   TRY_TEST(nSegCount,3);
//
//   segment.Release();
//   mbr->get_Segment(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,2.0),true);
//
//   segment.Release();
//   mbr->get_Segment(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   segment.Release();
//   mbr->get_Segment(2,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,3.0),true);
//
//   // MoveSegmentTo()
//   TRY_TEST(mbr->MoveSegmentTo(-1,2),E_INVALIDARG);
//   TRY_TEST(mbr->MoveSegmentTo(100,2),E_INVALIDARG);
//   TRY_TEST(mbr->MoveSegmentTo(0,-1),E_INVALIDARG);
//   TRY_TEST(mbr->MoveSegmentTo(0,100),E_INVALIDARG);
//   TRY_TEST(mbr->MoveSegmentTo(0,0),S_OK);
//   TRY_TEST(mbr->MoveSegmentTo(0,2),S_OK);
//
//   mbr->get_SegmentCount(&nSegCount);
//   TRY_TEST(nSegCount,3);
//
//   segment.Release();
//   mbr->get_Segment(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   segment.Release();
//   mbr->get_Segment(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,3.0),true);
//
//   segment.Release();
//   mbr->get_Segment(2,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,2.0),true);
//   
//   // RemoveSegment()
//   TRY_TEST(mbr->RemoveSegment(-1),E_INVALIDARG);
//   TRY_TEST(mbr->RemoveSegment(100),E_INVALIDARG);
//   TRY_TEST(mbr->RemoveSegment(1),S_OK);
//
//   mbr->get_SegmentCount(&nSegCount);
//   TRY_TEST(nSegCount,2);
//
//   segment.Release();
//   mbr->get_Segment(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   segment.Release();
//   mbr->get_Segment(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,2.0),true);   
//   
//   // ReverseSegments()
//   TRY_TEST(mbr->ReverseSegments(),S_OK);
//
//   mbr->get_SegmentCount(&nSegCount);
//   TRY_TEST(nSegCount,2);
//
//   segment.Release();
//   mbr->get_Segment(0,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,2.0),true);
//
//   segment.Release();
//   mbr->get_Segment(1,&segment);
//   segment->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);     
//   
//   // SetEndRelease()
//   TRY_TEST(mbr->SetEndRelease(etStart,CComBSTR("Stage 2"),rtHinged),S_OK);
//
//   ///////////////////////////////////////
//   // Test Set with event sink
//   CComObject<CTestSuperstructureMember>* pTest;
//   CComObject<CTestSuperstructureMember>::CreateInstance(&pTest);
//   pTest->AddRef();
//   
//   DWORD dwCookie;
//   CComPtr<IUnknown> punk(pTest);
//   TRY_TEST(AtlAdvise(mbr,punk,IID_ISuperstructureMemberEvents,&dwCookie),S_OK);
//
//   pTest->InitEventTest();
//   mbr->RemoveSegments();
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   mbr->AddSegment(newSegment);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   mbr->AddSegment(newSegment);
//
//   pTest->InitEventTest();
//   mbr->CopySegmentTo(0,1);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   mbr->get_Fractional(&bFractional);
//   mbr->put_Fractional(bFractional);
//   TRY_TEST(pTest->PassedEventTest(), false );
//   mbr->put_Fractional(!bFractional);
//   TRY_TEST(pTest->PassedEventTest(), true );
// 
//   pTest->InitEventTest();
//   mbr->InsertSegment(0,newSegment);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   mbr->MoveSegmentTo(0,1);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   mbr->RemoveSegment(0);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   mbr->ReverseSegments();
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   pTest->InitEventTest();
//   mbr->SetEndRelease(etEnd,CComBSTR("Stage 2"),rtHinged);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   mbr->get_Symmetrical(&bSymmetrical);
//   pTest->InitEventTest();
//   mbr->put_Symmetrical(bSymmetrical);
//   TRY_TEST(pTest->PassedEventTest(), false );
//   mbr->put_Symmetrical(!bSymmetrical);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   ///////////////////////////////////////
//   // Test with events
//   mbr->RemoveSegments();
////
////   CComPtr<IWBFLTransactionMgr> txnMgr;
////   txnMgr.CoCreateInstance(CLSID_TransactionMgr);
////
////   CComQIPtr<IWBFLSupportTransactions> supTxns(mbr);
////   TRY_TEST(supTxns != nullptr,true);
////   TRY_TEST(supTxns->putref_TransactionMgr(txnMgr),S_OK);
////
////   // Undo AddSegment
////   mbr->AddSegment(newSegment);
////   pTest->InitEventTest();
////   TRY_TEST(txnMgr->Undo(),S_OK);
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,0);
////   TRY_TEST(pTest->PassedEventTest(), true );
////
////   // Undo CopySegmentTo
////   // create 2 segments
////   mbr->AddSegment(newSegment);
////   mbr->AddSegment(newSegment);
////
////   // set length of first segment to 5
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->put_Length(5.0); 
////
////   // confirm the length of second segment
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true); 
////
////   mbr->CopySegmentTo(0,1);
////
////   // confirm length of second segment after copy
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,5.0),false); // this is the pointer to the segment that
////                                        // was replaced by the copy
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,5.0),true);
////
////   // undo the copy
////   pTest->InitEventTest();
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   // confirm the length is restored 
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),false); // Undo removes the copy from the collection
////                                        // and replaces it with the original object
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   // verify the event fired
////   TRY_TEST(pTest->PassedEventTest(), true ); 
////
////   // Undo Fractional
////   VARIANT_BOOL bOriginal;
////   mbr->get_Fractional(&bOriginal);
////   mbr->put_Fractional(!bOriginal);
////   pTest->InitEventTest();
////   TRY_TEST(txnMgr->Undo(),S_OK);
////   mbr->get_Fractional(&bFractional);
////   TRY_TEST(bOriginal == bFractional,true);
////   TRY_TEST(pTest->PassedEventTest(), true ); // verify the event fired
////
////   // Undo Insert
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->put_Length(100.0);
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->put_Length(200.0);
////
////   mbr->InsertSegment(1,newSegment);
////
////   // confirm the insertion by checking count and segment lengths
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   // undo
////   pTest->InitEventTest();
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   // confirm by checking count and segment lengths
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,2);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   // verify the event fired
////   TRY_TEST(pTest->PassedEventTest(), true ); 
////
////   // Undo Length
////   mbr->get_Length(&length);
////   TRY_TEST(IsEqual(length,20.0),true);
////
////   mbr->put_Length(100.0);
////   mbr->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   pTest->InitEventTest();
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   mbr->get_Length(&length);
////   TRY_TEST(IsEqual(length,20.0),true);
////
////   TRY_TEST(pTest->PassedEventTest(), true ); 
////
////   // Undo MoveSegmentTo()
////   mbr->InsertSegment(1,newSegment);
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   mbr->MoveSegmentTo(0,1);
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   pTest->InitEventTest();
////
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   TRY_TEST(pTest->PassedEventTest(), true ); 
////
////   // Undo ReverseSegments
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   mbr->ReverseSegments();
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   pTest->InitEventTest();
////
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   TRY_TEST(pTest->PassedEventTest(), true ); 
////
////
////   // Undo RemoveSegment
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   mbr->RemoveSegment(1);
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,2);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   pTest->InitEventTest();
////
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   segment.Release();
////   mbr->get_Segment(0,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,100.0),true);
////
////   segment.Release();
////   mbr->get_Segment(1,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,1.0),true);
////
////   segment.Release();
////   mbr->get_Segment(2,&segment);
////   segment->get_Length(&length);
////   TRY_TEST(IsEqual(length,200.0),true);
////
////   TRY_TEST(pTest->PassedEventTest(), true ); 
////
////   // Undo RemoveSegments
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   mbr->RemoveSegments();
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,0);
////
////   pTest->InitEventTest();
////
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   mbr->get_SegmentCount(&nSegCount);
////   TRY_TEST(nSegCount,3);
////
////   TRY_TEST(pTest->PassedEventTest(), true ); 
////
////   // Undo SetEndRelease()
//   CComBSTR bstrCurrReleaseStage;
//   ReleaseType rtCurrReleaseType;
////
////   mbr->GetEndRelease(etStart,&bstrCurrReleaseStage,&rtCurrReleaseType);
////   TRY_TEST(bstrCurrReleaseStage == CComBSTR("Stage 2"),true);
////   TRY_TEST(rtCurrReleaseType == rtHinged,true);
////
////   mbr->SetEndRelease(etStart,CComBSTR("Stage 1"),rtNone);
////
////   pTest->InitEventTest();
////
////   TRY_TEST(txnMgr->Undo(),S_OK);
////
////   bstrReleaseStage.Empty();
////   mbr->GetEndRelease(etStart,&bstrReleaseStage,&releaseType);
////   TRY_TEST(bstrCurrReleaseStage == bstrReleaseStage,true);
////   TRY_TEST(rtCurrReleaseType == releaseType,true);
////
////   // Undo Symmetrical
////   mbr->get_Symmetrical(&bOriginal);
////   mbr->put_Symmetrical(!bOriginal);
////   pTest->InitEventTest();
////   TRY_TEST(txnMgr->Undo(),S_OK);
////   mbr->get_Symmetrical(&bSymmetrical);
////   TRY_TEST(bOriginal == bSymmetrical,true);
////   TRY_TEST(pTest->PassedEventTest(), true ); // verify the event fired
////
////   // Remove transaction manager
////   TRY_TEST(supTxns->putref_TransactionMgr(nullptr),S_OK);
//
//   // Done with events
//   TRY_TEST(AtlUnadvise(mbr,IID_ISuperstructureMemberEvents,dwCookie),S_OK);
//   pTest->Release();
//
//   // Responses to stage changes
//   mbr->SetEndRelease(etStart,CComBSTR("Stage 1"),rtNone);
//   CComPtr<IStage> stage1;
//   stages->get_Item(0,&stage1);
//   stage1->put_Name(CComBSTR("First Stage"));
//
//   bstrCurrReleaseStage.Empty();
//   mbr->GetEndRelease(etStart,&bstrCurrReleaseStage,&rtCurrReleaseType);
//   TRY_TEST(bstrCurrReleaseStage == CComBSTR("First Stage"),true);
//   TRY_TEST(rtCurrReleaseType == rtNone,true);
//
//   ///////////////////////////////////////
//   // Test Error Info
//   CComQIPtr<ISupportErrorInfo> eInfo(mbr);
//   TRY_TEST( eInfo != 0, true );
//
//   // Interfaces that should be supported
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISuperstructureMember ), S_OK );
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
//
//   // Interface that is not supported
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
//
//   // Test IObjectSafety
//   TRY_TEST( TestIObjectSafety(mbr,IID_ISuperstructureMember,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
//   TRY_TEST( TestIObjectSafety(mbr,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
