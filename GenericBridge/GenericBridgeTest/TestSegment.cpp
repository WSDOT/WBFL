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

// TestSegment.cpp: implementation of the CTestSegment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSegment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSegment::CTestSegment()
{

}

CTestSegment::~CTestSegment()
{

}

void CTestSegment::Test()
{
//   // Create a default bridge
//   CComPtr<IGenericBridge> bridge;
//   bridge.CoCreateInstance(CLSID_GenericBridge);
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
//   CComPtr<IPrismaticSegment> newSegment;
//   HRESULT hr = newSegment.CoCreateInstance(CLSID_PrismaticSegment);
//   TRY_TEST(hr,S_OK);
//   mbr->AddSegment(newSegment);
//
//   CComPtr<ISegment> segment;
//   mbr->get_Segment(0,&segment);
//   TRY_TEST(segment != NULL, true);
//   CComQIPtr<IPrismaticSegment> pris(segment);
//   TRY_TEST(pris != NULL,true);
//
//   // Test default value
//   Float64 value;
//   TRY_TEST(segment->get_Length(NULL),E_POINTER);
//   TRY_TEST(segment->get_Length(&value),S_OK);
//   TRY_TEST(IsEqual(value,1.0),true);
//
//   CComPtr<IShape> shape;
//   TRY_TEST(pris->get_Shape(0.00,NULL),E_POINTER);
//   TRY_TEST(pris->get_Shape(0.00,&shape),S_OK);
//   TRY_TEST(shape == NULL, true);
//
//   TRY_TEST(segment->put_Length(-1.0),GB_E_ABSOLUTE_EXPECTED);
//   segment->get_Length(&value);
//   TRY_TEST(IsEqual(value,1.0),true); // confirm value didn't change
//
//   TRY_TEST(segment->put_Length(3.0),S_OK);
//   segment->get_Length(&value);
//   TRY_TEST(IsEqual(value,3.0),true);
//
//   // convert to fractional measure (absolute by default)
//   // only testing the validation on put_Length. Fractional conversions
//   // will be tested on ISuperstructureMember
//   mbr->put_Fractional(VARIANT_TRUE);
//
//   TRY_TEST(segment->put_Length(3.0),GB_E_FRACTIONAL_EXPECTED);
//   TRY_TEST(segment->put_Length(-0.5),S_OK);
//   segment->get_Length(&value);
//   TRY_TEST(IsEqual(value,-0.5),true);
//
//   // Add a real shape to the segment
//   CComPtr<ICircle> circle;
//   circle.CoCreateInstance(CLSID_Circle);
//   circle->put_Radius(10);
//
//   CComQIPtr<IShape> circle_shape(circle);
//   TRY_TEST(pris->putref_Shape(NULL),E_INVALIDARG);
//   TRY_TEST(pris->putref_Shape(circle_shape),S_OK);
//
//   shape.Release();
//   TRY_TEST(pris->get_Shape(0.00,&shape),S_OK);
//   TRY_TEST(shape != NULL,true);
//   TRY_TEST(shape.IsEqualObject(circle),false); // circle should have been cloned
//
//#pragma Reminder("TestSegment - Is there a limit on x for get_Shape? If so, test it")
//
//   ///////////////////////////////////////
//   // Test Set with event sink
//   CComObject<CTestSegment>* pTest;
//   CComObject<CTestSegment>::CreateInstance(&pTest);
//   pTest->AddRef();
//   
//   DWORD dwCookie;
//   CComPtr<IUnknown> punk(pTest);
//   TRY_TEST(AtlAdvise(segment,punk,IID_ISegmentEvents,&dwCookie),S_OK);
//
//   pTest->InitEventTest();
//   segment->put_Length(-0.25);
//   TRY_TEST(pTest->PassedEventTest(), true );
//
//   // bubbled events
////   pTest->InitEventTest();
////   section->put_Area(10);
////   TRY_TEST(pTest->PassedEventTest(), true );
////
////   CComPtr<IStressPointCollection> stressPoints;
////   section->get_StressPoints(&stressPoints);
////
////   pTest->InitEventTest();
////   stressPoints->Add();
////   TRY_TEST(pTest->PassedEventTest(), true );
////
////   CComPtr<IStressPoint> stressPoint;
////   stressPoints->get_Item(0,&stressPoint);
////
////   pTest->InitEventTest();
////   stressPoint->put_Sa(5.0);
////   TRY_TEST(pTest->PassedEventTest(), true );
//
//   ///////////////////////////////////////
//   // Test Set with events
//   segment->put_Length(-0.05);
//
//   // Done with events
//   TRY_TEST(AtlUnadvise(segment,IID_ISegmentEvents,dwCookie),S_OK);
//   pTest->Release();
//
//   ///////////////////////////////////////
//   // Test Error Info
//   CComQIPtr<ISupportErrorInfo> eInfo(segment);
//   TRY_TEST( eInfo != 0, true );
//
//   // Interfaces that should be supported
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISegment ), S_OK );
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
//
//   // Interface that is not supported
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
//
//   // Test IObjectSafety
//   TRY_TEST( TestIObjectSafety(segment,IID_ISegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
//   TRY_TEST( TestIObjectSafety(segment,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}


STDMETHODIMP CTestSegment::OnSegmentChanged(ISegment* segment)
{
   Pass();
   return S_OK;
}