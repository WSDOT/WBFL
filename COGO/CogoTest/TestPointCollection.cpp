///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestPointCollection.cpp: implementation of the CTestPointCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPointCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPointCollection::CTestPointCollection()
{

}

void CTestPointCollection::Test()
{
   CComPtr<IPointCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_PointCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(0,15.,20.,nullptr),S_OK);
   CComPtr<IPoint2d> pnt;
   TRY_TEST(pColl->get_Item(0,&pnt),S_OK);
   Float64 x,y;
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,15.0), true );
   TRY_TEST( IsEqual(y,20.0), true );
   pColl->Clear();

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(0,nullptr),E_INVALIDARG);

   // add some points and see if we get them back
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance( CLSID_Point2d );
   p1->put_X(10);
   p1->put_Y(10);
   TRY_TEST(pColl->AddEx(1,p1),S_OK);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance( CLSID_Point2d );
   p2->put_X(20);
   p2->put_Y(20);
   TRY_TEST(pColl->AddEx(1,p2),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(pColl->AddEx(2,p2),S_OK);

   CComPtr<IPoint2d> p3;
   p3.CoCreateInstance( CLSID_Point2d );
   p3->put_X(30);
   p3->put_Y(30);
   TRY_TEST(pColl->AddEx(3,p3),S_OK);

   CComPtr<IPoint2d> p4;
   p4.CoCreateInstance( CLSID_Point2d );
   p4->put_X(40);
   p4->put_Y(40);
   TRY_TEST(pColl->AddEx(4,p4),S_OK);

   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,4);

   // Test Item property
   pnt.Release();
   TRY_TEST(pColl->get_Item(-1,&pnt),COGO_E_POINTNOTFOUND);
   TRY_TEST(pColl->get_Item(1,nullptr),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,10.0), true );

   // Points in the container should be references. Change p1 and see if pnt changes
   p1->put_X(100);
   pnt->get_X(&x);
   TRY_TEST( IsEqual(x,100.0), true );

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),COGO_E_POINTNOTFOUND);
   TRY_TEST(pColl->Remove(2),S_OK);

   // p3 should still be OK because the contains holds references
   TRY_TEST(p3->get_X(&x),S_OK); // this will crash if p3 is bad.

   // The count should now be 3
   pColl->get_Count(&count);
   TRY_TEST(count,3);

   // Getting the item with id = 2 should fail
   pnt.Release();
   TRY_TEST( pColl->get_Item(2,&pnt), COGO_E_POINTNOTFOUND);

   // We should still be able to get access to point 4
   pnt.Release();
   pColl->get_Item(4,&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,40.0), true );
   TRY_TEST( IsEqual(y,40.0), true );

   //
   // Test Clear
   //
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);

   //
   // Test putref_Item
   //
   TRY_TEST(pColl->AddEx(1,p1),S_OK);
   TRY_TEST(pColl->AddEx(2,p2),S_OK);
   TRY_TEST(pColl->AddEx(3,p3),S_OK);
   TRY_TEST(pColl->AddEx(4,p4),S_OK);

   TRY_TEST(pColl->putref_Item(3,nullptr),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(-1,p1),COGO_E_POINTNOTFOUND);
   TRY_TEST(pColl->putref_Item(3,p1),S_OK);

   pnt.Release();
   pColl->get_Item(3,&pnt);
   TRY_TEST(pnt.IsEqualObject(p1),true);

   //
   // Test FindID
   //
   CogoObjectID id;
   TRY_TEST(pColl->FindID(nullptr,&id),E_INVALIDARG);
   TRY_TEST(pColl->FindID(p2,nullptr),E_POINTER);
   TRY_TEST(pColl->FindID(p2,&id),S_OK);
   TRY_TEST(id,2);
   TRY_TEST(pColl->FindID(p3,&id),E_FAIL); // p3 is not part of collection, see putref_Item above

   //
   // Test ID
   //
   pColl->Clear();
   p1->put_X(10);
   p2->put_X(20);
   p3->put_X(30);
   p4->put_X(40);
   pColl->AddEx(1,p1);
   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);

   TRY_TEST(pColl->ID(-1,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(500,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(3,nullptr),E_POINTER);
   TRY_TEST(pColl->ID(3,&id),S_OK);
   TRY_TEST(id,4);
   
   //
   // Test _Enum
   //
   pColl->Clear();
   p1->put_X(10);
   p2->put_X(20);
   p3->put_X(30);
   p4->put_X(40);
   pColl->AddEx(1,p1);
   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);
   CComPtr<IEnumIDs> pEnum;
   TRY_TEST(pColl->get__EnumIDs(nullptr), E_POINTER );
   TRY_TEST( pColl->get__EnumIDs(&pEnum), S_OK );

   ULONG fetched;
   CogoObjectID target_id = 1;
   while( pEnum->Next(1,&id,&fetched ) == S_OK )
   {
      TRY_TEST(id,target_id++);
   }
   
   //
   // Test _EnumPoints
   //
   pColl->Clear();
   p1->put_X(10);
   p2->put_X(20);
   p3->put_X(30);
   p4->put_X(40);
   pColl->AddEx(1,p1);
   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);
   CComPtr<IEnumPoint2d> pEnumPoints;
   TRY_TEST(pColl->get__EnumPoints(nullptr), E_POINTER );
   TRY_TEST( pColl->get__EnumPoints(&pEnumPoints), S_OK );

   CComPtr<IPoint2d> point;
   pEnumPoints->Next(1,&point,&fetched);
   TRY_TEST(point.IsEqualObject(p1),true);
   
   point.Release();
   pEnumPoints->Next(1,&point,&fetched);
   TRY_TEST(point.IsEqualObject(p2),true);
   
   point.Release();
   pEnumPoints->Next(1,&point,&fetched);
   TRY_TEST(point.IsEqualObject(p3),true);
   
   point.Release();
   pEnumPoints->Next(1,&point,&fetched);
   TRY_TEST(point.IsEqualObject(p4),true);

   //
   // PointFactory
   //
   CComPtr<IPoint2dFactory> factory;
   TRY_TEST(pColl->get_Factory(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST(factory != nullptr,true);
   TRY_TEST(pColl->putref_Factory(nullptr),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);


   //
   // Test Events
   //
   pColl->Clear(); // start with an empty container

   CComObject<CTestPointCollection>* pTestEvents;
   CComObject<CTestPointCollection>::CreateInstance(&pTestEvents);
   pTestEvents->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestEvents);
   TRY_TEST(AtlAdvise(pColl,punk,IID_IPointCollectionEvents,&dwCookie),S_OK);

   // Add a point to the collection
   pTestEvents->InitEventTest(1);
   pColl->AddEx(1,p1);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Move a point... Event should fire
   pTestEvents->InitEventTest(1);
   p1->Move(15,15);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);

   // Remove a point
   pTestEvents->InitEventTest(3);
   pColl->Remove(3);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Change point references
   pTestEvents->InitEventTest(2);
   pColl->putref_Item(2,p4);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Add a point that doesn't support event firing
   // This point should be successfully added.
   // Review the profile output to verify that the approrate
   // return paths were followed when this object was encountered
   CComPtr<IPoint2d> geoPoint;
   geoPoint.CoCreateInstance(CLSID_Point2d);
   TRY_TEST(pColl->AddEx(6,geoPoint),S_OK);

   // Clear
   pTestEvents->InitEventTest(-1);
   pColl->Clear();
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   TRY_TEST(AtlUnadvise(pColl,IID_IPointCollectionEvents,dwCookie),S_OK);
   pTestEvents->Release();

   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPointCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_PointCollection,IID_IPointCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_PointCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestPointCollection::OnPointChanged(CogoObjectID id,IPoint2d* point)
{
//   MessageBox(nullptr,"PointChanged","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestPointCollection::OnPointAdded(CogoObjectID id,IPoint2d* point)
{
//   MessageBox(nullptr,"PointAdded","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestPointCollection::OnPointRemoved(CogoObjectID id)
{
//   MessageBox(nullptr,"PointRemoved","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestPointCollection::OnPointsCleared()
{
//   MessageBox(nullptr,"PointCleared","Event",MB_OK);
   Pass();
   return S_OK;
}
