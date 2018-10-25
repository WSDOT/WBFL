///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TestLineSegment2d.cpp: implementation of the CTestLineSegment2d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLineSegment2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLineSegment2d::CTestLineSegment2d()
{

}

void CTestLineSegment2d::Test()
{
   CComPtr<ILineSegment2d> pSeg;
   TRY_TEST(pSeg.CoCreateInstance( CLSID_LineSegment2d ),S_OK);

   //
   // Test StartPoint property
   //
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance( CLSID_Point2d );
   p1->put_X(10);
   p1->put_Y(10);

   TRY_TEST(pSeg->putref_StartPoint(NULL),E_INVALIDARG);
   TRY_TEST(pSeg->putref_StartPoint(p1),S_OK);

   CComPtr<IPoint2d> pStart;
   TRY_TEST(pSeg->get_StartPoint(NULL),E_POINTER);
   TRY_TEST(pSeg->get_StartPoint(&pStart),S_OK);
   Float64 x,y;
   pStart->get_X(&x);
   pStart->get_Y(&y);
   TRY_TEST(IsEqual(x,10.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   // Get the start point when the receiving point object already
   // references an existing point.
   p1.Release();
   TRY_TEST(pSeg->get_StartPoint(&p1),S_OK);
   p1->get_X(&x);
   p1->get_Y(&y);
   TRY_TEST(IsEqual(x,10.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   // Move p1, pStart should change as well
   p1->put_X(30);
   pStart->get_X(&x);
   TRY_TEST( IsEqual(x,30.0), true );
   pStart.Release();
   pSeg->get_StartPoint(&pStart);
   pStart->get_X(&x);
   TRY_TEST( IsEqual(x,30.0), true );

   //
   // Test EndPoint property
   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance( CLSID_Point2d );
   p2->put_X(20);
   p2->put_Y(20);
   TRY_TEST(pSeg->putref_EndPoint(NULL),E_INVALIDARG);
   TRY_TEST(pSeg->putref_EndPoint(p2),S_OK);

   CComPtr<IPoint2d> pEnd;
   TRY_TEST(pSeg->get_EndPoint(NULL),E_POINTER);
   TRY_TEST(pSeg->get_EndPoint(&pEnd),S_OK);
   pEnd->get_X(&x);
   pEnd->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,20.0),true);

   // Get the start point when the receiving point object already
   // references an existing point.
   p2.Release();
   TRY_TEST(pSeg->get_EndPoint(&p2),S_OK);
   p2->get_X(&x);
   p2->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,20.0),true);

   // Move p2, pEnd should change as well
   p2->put_X(30);
   pEnd->get_X(&x);
   TRY_TEST( IsEqual(x,30.0), true );
   pEnd.Release();
   pSeg->get_EndPoint(&pEnd);
   pEnd->get_X(&x);
   TRY_TEST( IsEqual(x,30.0), true );

   //
   // Test Length property
   //
   p1->put_X(10);
   p1->put_Y(10);
   p2->put_X(20);
   p2->put_Y(20);
   pSeg->putref_StartPoint(p1);
   pSeg->putref_EndPoint(p2);
   Float64 length;
   TRY_TEST(pSeg->get_Length(NULL),E_POINTER);
   TRY_TEST(pSeg->get_Length(&length),S_OK);
   TRY_TEST(IsEqual(length,14.1421356),true);

   //
   // Test Offset method
   //
   p1->put_X(10);
   p1->put_Y(10);
   p2->put_X(20);
   p2->put_Y(20);
   pSeg->putref_StartPoint(p1);
   pSeg->putref_EndPoint(p2);
   TRY_TEST(pSeg->Offset(-10,-10),S_OK);
   pStart.Release();
   pSeg->get_StartPoint(&pStart);
   pEnd.Release();
   pSeg->get_EndPoint(&pEnd);
   pStart->get_X(&x);
   pStart->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );
   pEnd->get_X(&x);
   pEnd->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,10.0), true );

   //
   // Test OffsetEx method
   //
   p1->put_X(-10);
   p1->put_Y(-10);
   p2->put_X(-20);
   p2->put_Y(-20);
   pSeg->putref_StartPoint(p1);
   pSeg->putref_EndPoint(p2);
   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(10);
   size->put_Dy(10);
   TRY_TEST(pSeg->OffsetEx(NULL),E_INVALIDARG);
   TRY_TEST(pSeg->OffsetEx(size),S_OK);
   pStart.Release();
   pSeg->get_StartPoint(&pStart);
   pEnd.Release();
   pSeg->get_EndPoint(&pEnd);
   pStart->get_X(&x);
   pStart->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );
   pEnd->get_X(&x);
   pEnd->get_Y(&y);
   TRY_TEST( IsEqual(x,-10.0), true );
   TRY_TEST( IsEqual(y,-10.0), true );
   
   //
   // Test Rotate method
   //
   pStart->put_X(10);
   pStart->put_Y(10);
   pEnd->put_X(20);
   pEnd->put_Y(20);
   pSeg->putref_StartPoint(pStart);
   pSeg->putref_EndPoint(pEnd);

   TRY_TEST(pSeg->Rotate(0,0,M_PI),S_OK);
   pStart.Release();
   pEnd.Release();
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);
   pStart->get_X(&x);
   pStart->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);
   pEnd->get_X(&x);
   pEnd->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,-20.0),true);

   //
   // Test RotateEx method
   //
   pStart->put_X(10);
   pStart->put_Y(10);
   pEnd->put_X(20);
   pEnd->put_Y(20);
   pSeg->putref_StartPoint(pStart);
   pSeg->putref_EndPoint(pEnd);

   CComPtr<IPoint2d> center;
   center.CoCreateInstance( CLSID_Point2d );
   center->put_X(0.00);
   center->put_Y(0.00);
   TRY_TEST(pSeg->RotateEx(NULL,M_PI/2),E_INVALIDARG);
   TRY_TEST(pSeg->RotateEx(center,M_PI/2),S_OK);
   pStart.Release();
   pEnd.Release();
   pSeg->get_StartPoint(&pStart);
   pSeg->get_EndPoint(&pEnd);
   pStart->get_X(&x);
   pStart->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);
   pEnd->get_X(&x);
   pEnd->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y, 20.0),true);

   TestISupportErrorInfo();


   // Test Events
   CComObject<CTestLineSegment2d>* pTestSegment;
   CComObject<CTestLineSegment2d>::CreateInstance(&pTestSegment);
   pTestSegment->AddRef();

   CComPtr<IUnknown> punk(pTestSegment);
   DWORD dwCookie;
   TRY_TEST(AtlAdvise(pSeg,punk,IID_ILineSegment2dEvents,&dwCookie),S_OK);

   pTestSegment->InitEventTest();
   pSeg->Offset(10,20);
   TRY_TEST(pTestSegment->PassedEventTest(), true );

   pTestSegment->InitEventTest();
   pSeg->OffsetEx(size);
   TRY_TEST(pTestSegment->PassedEventTest(), true );

   pTestSegment->InitEventTest();
   pSeg->Rotate(10,20,0.25);
   TRY_TEST(pTestSegment->PassedEventTest(), true );

   pTestSegment->InitEventTest();
   pSeg->RotateEx(center,0.25);
   TRY_TEST(pTestSegment->PassedEventTest(), true );

   pTestSegment->InitEventTest();
   pStart->Move(4,4);
   TRY_TEST(pTestSegment->PassedEventTest(), true );

   pTestSegment->InitEventTest();
   pEnd->Move(5,5);
   TRY_TEST(pTestSegment->PassedEventTest(), true );

   CComPtr<IPoint2d> newStart;
   newStart.CoCreateInstance(CLSID_Point2d);
   pTestSegment->InitEventTest();
   pSeg->putref_StartPoint(newStart);
   TRY_TEST(pTestSegment->PassedEventTest(), true );
   pTestSegment->InitEventTest();
   newStart->Move(4,4);
   TRY_TEST(pTestSegment->PassedEventTest(), true );
   pTestSegment->InitEventTest();
   pStart->Move(4,4);
   TRY_TEST(pTestSegment->PassedEventTest(), false );

   CComPtr<IPoint2d> newEnd;
   newEnd.CoCreateInstance(CLSID_Point2d);
   pTestSegment->InitEventTest();
   pSeg->putref_EndPoint(newEnd);
   TRY_TEST(pTestSegment->PassedEventTest(), true );
   pTestSegment->InitEventTest();
   newEnd->Move(4,4);
   TRY_TEST(pTestSegment->PassedEventTest(), true );
   pTestSegment->InitEventTest();
   pEnd->Move(4,4);
   TRY_TEST(pTestSegment->PassedEventTest(), false );


   TRY_TEST(AtlUnadvise(pSeg,IID_ILineSegment2dEvents,dwCookie),S_OK);

   pTestSegment->Release();

}

void CTestLineSegment2d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_LineSegment2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ILineSegment2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}


STDMETHODIMP CTestLineSegment2d::OnLineSegmentChanged(ILineSegment2d* lineSegment)
{
   Pass();
   return S_OK;
}
