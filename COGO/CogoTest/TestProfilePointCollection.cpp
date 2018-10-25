///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestProfilePointCollection.cpp: implementation of the CTestProfilePointCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestProfilePointCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestProfilePointCollection::CTestProfilePointCollection()
{

}

void CTestProfilePointCollection::Test()
{
   CComPtr<IProfilePointCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_ProfilePointCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(NULL),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<IProfilePointFactory> factory;
   TRY_TEST(pColl->get_Factory(NULL),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST( factory != NULL, true );
   TRY_TEST(pColl->putref_Factory(NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(0,CComVariant(15.),20.,NULL),S_OK);
   CComPtr<IProfilePoint> pnt;
   TRY_TEST(pColl->get_Item(0,&pnt),S_OK);
   CComPtr<IStation> station;
   Float64 sta,elev;
   pnt->get_Station(&station);
   station->get_Value(&sta);
   pnt->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,15.0), true );
   TRY_TEST( IsEqual(elev,20.0), true );
   pColl->Clear();

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(0,NULL),E_INVALIDARG);

   // add some ProfilePoints and see if we get them back
   CComPtr<IProfilePoint> p1;
   p1.CoCreateInstance( CLSID_ProfilePoint );
   p1->put_Station(CComVariant(10));
   p1->put_Elevation(10);
   TRY_TEST(pColl->AddEx(1,p1),S_OK);

   CComPtr<IProfilePoint> p2;
   p2.CoCreateInstance( CLSID_ProfilePoint );
   p2->put_Station(CComVariant(20));
   p2->put_Elevation(20);
   TRY_TEST(pColl->AddEx(1,p2),COGO_E_PROFILEPOINTALREADYDEFINED);
   TRY_TEST(pColl->AddEx(2,p2),S_OK);

   CComPtr<IProfilePoint> p3;
   p3.CoCreateInstance( CLSID_ProfilePoint );
   p3->put_Station(CComVariant(30));
   p3->put_Elevation(30);
   TRY_TEST(pColl->AddEx(3,p3),S_OK);

   CComPtr<IProfilePoint> p4;
   p4.CoCreateInstance( CLSID_ProfilePoint );
   p4->put_Station(CComVariant(40));
   p4->put_Elevation(40);
   TRY_TEST(pColl->AddEx(4,p4),S_OK);

   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,4);

   // Test Item property
   pnt.Release();
   TRY_TEST(pColl->get_Item(-1,&pnt),COGO_E_PROFILEPOINTNOTFOUND);
   TRY_TEST(pColl->get_Item(1,NULL),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&pnt),S_OK);
   station.Release();
   pnt->get_Station(&station);
   station->get_Value(&sta);
   pnt->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,10.0), true );
   TRY_TEST( IsEqual(elev,10.0), true );

   // ProfilePoints in the container should be references. Change p1 and see if pnt changes
   p1->put_Station(CComVariant(100));
   station.Release();
   pnt->get_Station(&station);
   station->get_Value(&sta);
   TRY_TEST( IsEqual(sta,100.0), true );

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),COGO_E_PROFILEPOINTNOTFOUND);
   TRY_TEST(pColl->Remove(2),S_OK);

   // p3 should still be OK because the contains holds references
   station.Release();
   TRY_TEST(p3->get_Station(&station),S_OK); // this will crash if p3 is bad.

   // The count should now be 3
   pColl->get_Count(&count);
   TRY_TEST(count,3);

   // Getting the item with id = 2 should fail
   pnt.Release();
   TRY_TEST( pColl->get_Item(2,&pnt), COGO_E_PROFILEPOINTNOTFOUND);

   // We should still be able to get access to ProfilePoint 4
   pnt.Release();
   pColl->get_Item(4,&pnt);
   station.Release();
   pnt->get_Station(&station);
   station->get_Value(&sta);
   pnt->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,40.0), true );
   TRY_TEST( IsEqual(elev,40.0), true );

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

   TRY_TEST(pColl->putref_Item(3,NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(-1,p1),COGO_E_PROFILEPOINTNOTFOUND);
   TRY_TEST(pColl->putref_Item(3,p1),S_OK);

   pnt.Release();
   pColl->get_Item(3,&pnt);
   TRY_TEST(pnt.IsEqualObject(p1),true);

   //
   // Test FindID
   //
   CogoObjectID id;
   TRY_TEST(pColl->FindID(NULL,&id),E_INVALIDARG);
   TRY_TEST(pColl->FindID(p4,NULL),E_POINTER);
   TRY_TEST(pColl->FindID(p4,&id),S_OK);
   TRY_TEST(id,4);
   TRY_TEST(pColl->FindID(p3,&id),E_FAIL); // p3 is not part of collection, see putref_Item above

   //
   // Test ID
   //
   pColl->Clear();
   p1->put_Station(CComVariant(10));
   p2->put_Station(CComVariant(20));
   p3->put_Station(CComVariant(30));
   p4->put_Station(CComVariant(40));
   pColl->AddEx(1,p1);
   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);

   TRY_TEST(pColl->ID(-1,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(500,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(3,NULL),E_POINTER);
   TRY_TEST(pColl->ID(3,&id),S_OK);
   TRY_TEST(id,4);
   
   //
   // Test _Enum
   //
   pColl->Clear();
   p1->put_Station(CComVariant(10));
   p2->put_Station(CComVariant(20));
   p3->put_Station(CComVariant(30));
   p4->put_Station(CComVariant(40));
   pColl->AddEx(1,p1);
   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);
   CComPtr<IEnumIDs> pEnum;
   TRY_TEST(pColl->get__EnumIDs(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumIDs(&pEnum), S_OK );

   ULONG fetched;
   CogoObjectID target_id = 1;
   while( pEnum->Next(1,&id,&fetched ) == S_OK )
   {
      TRY_TEST(id,target_id++);
   }

   // Test __EnumVertCurves
   //
   pColl->Clear();
   p1->put_Station(CComVariant(10));
   p2->put_Station(CComVariant(20));
   p3->put_Station(CComVariant(30));
   p4->put_Station(CComVariant(40));
   pColl->AddEx(1,p1);
   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);
   CComPtr<IEnumProfilePoints> pEnumPP;
   TRY_TEST(pColl->get__EnumProfilePoints(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumProfilePoints(&pEnumPP), S_OK );

   CComPtr<IProfilePoint> pp;
   TRY_TEST( pEnumPP->Next(1,&pp,&fetched), S_OK );
   TRY_TEST( pp.IsEqualObject(p1), true );

   pp.Release();
   TRY_TEST( pEnumPP->Next(1,&pp,&fetched), S_OK );
   TRY_TEST( pp.IsEqualObject(p2), true );

   pp.Release();
   TRY_TEST( pEnumPP->Next(1,&pp,&fetched), S_OK );
   TRY_TEST( pp.IsEqualObject(p3), true );

   pp.Release();
   TRY_TEST( pEnumPP->Next(1,&pp,&fetched), S_OK );
   TRY_TEST( pp.IsEqualObject(p4), true );

   pp.Release();
   TRY_TEST( pEnumPP->Next(1,&pp,&fetched), S_FALSE );

   //
   // Test Events
   //
   pColl->Clear(); // start with an empty container

   CComObject<CTestProfilePointCollection>* pTestEvents;
   CComObject<CTestProfilePointCollection>::CreateInstance(&pTestEvents);
   pTestEvents->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestEvents);
   TRY_TEST(AtlAdvise(pColl,punk,IID_IProfilePointCollectionEvents,&dwCookie),S_OK);

   // Start with a "clean" profile point
   p1.Release();
   p1.CoCreateInstance( CLSID_ProfilePoint );
   p1->put_Station(CComVariant(10));
   p1->put_Elevation(10);

   // Add a ProfilePoint to the collection
   pTestEvents->InitEventTest(1);
   pColl->AddEx(1,p1);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Move a ProfilePoint... Event should fire
   pTestEvents->InitEventTest(1);
   p1->put_Station(CComVariant(150));
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   pTestEvents->InitEventTest(1);
   p1->put_Elevation(150);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   pColl->AddEx(2,p2);
   pColl->AddEx(3,p3);
   pColl->AddEx(4,p4);

   // Remove a ProfilePoint
   pTestEvents->InitEventTest(3);
   pColl->Remove(3);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Change ProfilePoint references
   pTestEvents->InitEventTest(2);
   pColl->putref_Item(2,p4);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Clear
   pTestEvents->InitEventTest(-1);
   pColl->Clear();
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   TRY_TEST(AtlUnadvise(pColl,IID_IProfilePointCollectionEvents,dwCookie),S_OK);
   pTestEvents->Release();

   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IProfilePointCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_ProfilePointCollection,IID_IProfilePointCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_ProfilePointCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestProfilePointCollection::OnProfilePointChanged(CogoObjectID id,IProfilePoint* pp)
{
//   MessageBox(NULL,"ProfilePointChanged","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestProfilePointCollection::OnProfilePointAdded(CogoObjectID id,IProfilePoint* pp)
{
//   MessageBox(NULL,"ProfilePointAdded","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestProfilePointCollection::OnProfilePointRemoved(CogoObjectID id)
{
//   MessageBox(NULL,"ProfilePointRemoved","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestProfilePointCollection::OnProfilePointsCleared()
{
//   MessageBox(NULL,"ProfilePointCleared","Event",MB_OK);
   Pass();
   return S_OK;
}
