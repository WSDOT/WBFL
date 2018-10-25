///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestLineSegmentCollection.cpp: implementation of the CTestLineSegmentCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLineSegmentCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLineSegmentCollection::CTestLineSegmentCollection()
{

}

void CTestLineSegmentCollection::Test()
{
   CComPtr<ILineSegmentCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_LineSegmentCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(NULL),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<IPoint2d> start, end;
   start.CoCreateInstance(CLSID_Point2d);
   end.CoCreateInstance(CLSID_Point2d);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(0,NULL,end,NULL),E_INVALIDARG);
   TRY_TEST(pColl->Add(0,start,NULL,NULL),E_INVALIDARG);
   TRY_TEST(pColl->Add(0,start,end,NULL),S_OK);
   CComPtr<ILineSegment2d> ls;
   TRY_TEST(pColl->get_Item(0,&ls),S_OK);

   CComPtr<IPoint2d> pnt;
   ls->get_StartPoint(&pnt);
   TRY_TEST(pnt.IsEqualObject(start),true);
   pnt.Release();
   ls->get_EndPoint(&pnt);
   TRY_TEST(pnt.IsEqualObject(end),true);

   pColl->Clear();

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(0,NULL),E_INVALIDARG);

   // add some LineSegments and see if we get them back
   CComPtr<ILineSegment2d> ls1;
   ls1.CoCreateInstance( CLSID_LineSegment2d );
   ls1->putref_StartPoint(start);
   ls1->putref_EndPoint(end);
   TRY_TEST(pColl->AddEx(1,ls1),S_OK);

   CComPtr<ILineSegment2d> ls2;
   ls2.CoCreateInstance( CLSID_LineSegment2d );
   ls2->putref_StartPoint(start);
   ls2->putref_EndPoint(end);
   TRY_TEST(pColl->AddEx(1,ls2),COGO_E_LINESEGMENTALREADYDEFINED);
   TRY_TEST(pColl->AddEx(2,ls2),S_OK);

   CComPtr<ILineSegment2d> ls3;
   ls3.CoCreateInstance( CLSID_LineSegment2d );
   ls3->putref_StartPoint(start);
   ls3->putref_EndPoint(end);
   TRY_TEST(pColl->AddEx(3,ls3),S_OK);

   CComPtr<ILineSegment2d> ls4;
   ls4.CoCreateInstance( CLSID_LineSegment2d );
   ls4->putref_StartPoint(start);
   ls4->putref_EndPoint(end);
   TRY_TEST(pColl->AddEx(4,ls4),S_OK);

   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,4);

   // Test Item property
   ls.Release();
   TRY_TEST(pColl->get_Item(-1,&ls),COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(pColl->get_Item(1,NULL),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&ls),S_OK);
   pnt.Release();
   ls->get_StartPoint(&pnt);
   TRY_TEST(pnt.IsEqualObject(start),true);
   pnt.Release();
   ls->get_EndPoint(&pnt);
   TRY_TEST(pnt.IsEqualObject(end),true);

   // LineSegments in the container should be references. Change ls1 and see if ls changes
   ls1->putref_StartPoint(end);
   pnt.Release();
   ls->get_StartPoint(&pnt);
   TRY_TEST( pnt.IsEqualObject(end), true );

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(pColl->Remove(2),S_OK);

   // The count should now be 3
   pColl->get_Count(&count);
   TRY_TEST(count,3);

   // Getting the item with key = 2 should fail
   ls.Release();
   TRY_TEST( pColl->get_Item(2,&ls), COGO_E_LINESEGMENTNOTFOUND);

   // We should still be able to get access to LineSegment 4
   ls.Release();
   TRY_TEST(pColl->get_Item(4,&ls),S_OK);
   TRY_TEST(ls != NULL, true );

   //
   // Test Clear
   //
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);

   //
   // Test putref_Item
   //
   TRY_TEST(pColl->AddEx(1,ls1),S_OK);
   TRY_TEST(pColl->AddEx(2,ls2),S_OK);
   TRY_TEST(pColl->AddEx(3,ls3),S_OK);
   TRY_TEST(pColl->AddEx(4,ls4),S_OK);

   TRY_TEST(pColl->putref_Item(3,NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(-1,ls1),COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(pColl->putref_Item(3,ls1),S_OK);

   ls.Release();
   pColl->get_Item(3,&ls);
   TRY_TEST(ls.IsEqualObject(ls1),true);

   //
   // Test FindKey
   //
   CogoElementKey key;
   TRY_TEST(pColl->FindKey(NULL,&key),E_INVALIDARG);
   TRY_TEST(pColl->FindKey(ls4,NULL),E_POINTER);
   TRY_TEST(pColl->FindKey(ls4,&key),S_OK);
   TRY_TEST(key,4);
   TRY_TEST(pColl->FindKey(ls3,&key),E_FAIL); // ls3 is not part of collection, see putref_Item above

   //
   // Test Key
   //
   TRY_TEST(pColl->Key(-1,&key),E_INVALIDARG);
   TRY_TEST(pColl->Key(500,&key),E_INVALIDARG);
   TRY_TEST(pColl->Key(3,NULL),E_POINTER);
   TRY_TEST(pColl->Key(3,&key),S_OK);
   TRY_TEST(key,4);

   //
   // Test _Enum
   //
   pColl->Clear();
   TRY_TEST(pColl->AddEx(1,ls1),S_OK);
   TRY_TEST(pColl->AddEx(2,ls2),S_OK);
   TRY_TEST(pColl->AddEx(3,ls3),S_OK);
   TRY_TEST(pColl->AddEx(4,ls4),S_OK);
   CComPtr<IEnumKeys> pEnum;
   TRY_TEST(pColl->get__EnumKeys(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumKeys(&pEnum), S_OK );

   ULONG fetched;
   CogoElementKey target_key = 1;
   while( pEnum->Next(1,&key,&fetched ) == S_OK )
   {
      TRY_TEST(key,target_key++);
   }

   
   //
   // Test _EnumPoints
   //
   pColl->Clear();
   pColl->AddEx(1,ls1);
   pColl->AddEx(2,ls2);
   pColl->AddEx(3,ls3);
   pColl->AddEx(4,ls4);
   CComPtr<IEnumLineSegments> pEnumLineSegments;
   TRY_TEST(pColl->get__EnumLineSegments(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumLineSegments(&pEnumLineSegments), S_OK );

   ls.Release();
   pEnumLineSegments->Next(1,&ls,&fetched);
   TRY_TEST(ls.IsEqualObject(ls1),true);
   
   ls.Release();
   pEnumLineSegments->Next(1,&ls,&fetched);
   TRY_TEST(ls.IsEqualObject(ls2),true);
   
   ls.Release();
   pEnumLineSegments->Next(1,&ls,&fetched);
   TRY_TEST(ls.IsEqualObject(ls3),true);
   
   ls.Release();
   pEnumLineSegments->Next(1,&ls,&fetched);
   TRY_TEST(ls.IsEqualObject(ls4),true);

   //
   // Factory
   //
   CComPtr<ILineSegment2dFactory> factory;
   TRY_TEST(pColl->get_Factory(NULL),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST(factory != NULL,true);
   TRY_TEST(pColl->putref_Factory(NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);

   //
   // Test Events
   //
   pColl->Clear(); // start with an empty container

   CComObject<CTestLineSegmentCollection>* pTestEvents;
   CComObject<CTestLineSegmentCollection>::CreateInstance(&pTestEvents);
   pTestEvents->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestEvents);
   TRY_TEST(AtlAdvise(pColl,punk,IID_ILineSegmentCollectionEvents,&dwCookie),S_OK);

   // Add a LineSegment to the collection
   pTestEvents->InitEventTest(1);
   pColl->AddEx(1,ls1);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Change a LineSegment... Event should fire
   pTestEvents->InitEventTest(1);
   ls1->putref_StartPoint(start);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   pColl->AddEx(2,ls2);
   pColl->AddEx(3,ls3);
   pColl->AddEx(4,ls4);

   // Remove a LineSegment
   pTestEvents->InitEventTest(3);
   pColl->Remove(3);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Change LineSegment references
   pTestEvents->InitEventTest(2);
   pColl->putref_Item(2,ls4);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Clear
   pTestEvents->InitEventTest(-1);
   pColl->Clear();
   TRY_TEST(pTestEvents->PassedEventTest(),true);


   TRY_TEST(AtlUnadvise(pColl,IID_ILineSegmentCollectionEvents,dwCookie),S_OK);
   pTestEvents->Release();

   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ILineSegmentCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_LineSegmentCollection,IID_ILineSegmentCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_LineSegmentCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestLineSegmentCollection::OnLineSegmentChanged(CogoElementKey key,ILineSegment2d* lineSeg)
{
//   MessageBox(NULL,"LineSegmentChanged","Event",MB_OK);
   if ( key == m_expectedKey )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestLineSegmentCollection::OnLineSegmentAdded(CogoElementKey key,ILineSegment2d* lineSeg)
{
//   MessageBox(NULL,"LineSegmentAdded","Event",MB_OK);
   if ( key == m_expectedKey )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestLineSegmentCollection::OnLineSegmentRemoved(CogoElementKey key)
{
//   MessageBox(NULL,"LineSegmentRemoved","Event",MB_OK);
   if ( key == m_expectedKey )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestLineSegmentCollection::OnLineSegmentsCleared()
{
//   MessageBox(NULL,"LineSegmentCleared","Event",MB_OK);
   Pass();
   return S_OK;
}
