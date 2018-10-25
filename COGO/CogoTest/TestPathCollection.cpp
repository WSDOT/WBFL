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

// TestPathCollection.cpp: implementation of the CTestPathCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPathCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPathCollection::CTestPathCollection()
{

}

void CTestPathCollection::Test()
{
   CComPtr<IPathCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_PathCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(NULL),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<IPath> Path;
   Path.CoCreateInstance(CLSID_Path);

   CComPtr<IPathFactory> factory;
   TRY_TEST(pColl->get_Factory(NULL),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST( factory != NULL, true );
   TRY_TEST(pColl->putref_Factory(NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(1,Path),S_OK);
   TRY_TEST(pColl->AddEx(1,Path),COGO_E_PATHALREADYDEFINED);
   CComPtr<IPath> a;
   TRY_TEST(pColl->get_Item(1,&a),S_OK);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   // Test Item property
   a.Release();
   TRY_TEST(pColl->get_Item(-1,&a),COGO_E_PATHNOTFOUND);
   TRY_TEST(pColl->get_Item(1,NULL),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&a),S_OK);

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),COGO_E_PATHNOTFOUND);
   TRY_TEST(pColl->Remove(1),S_OK);

   //
   // Test Clear
   //
   pColl->AddEx(1,Path);
   pColl->get_Count(&count);
   TRY_TEST(count,1);
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);

   //
   // Test putref_Item
   //
   TRY_TEST(pColl->AddEx(1,Path),S_OK);

   a.Release();
   a.CoCreateInstance(CLSID_Path);
   TRY_TEST(pColl->putref_Item(1,NULL),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(-1,Path),COGO_E_PATHNOTFOUND);
   TRY_TEST(pColl->putref_Item(1,a),S_OK);

   //
   // Test FindID
   //
   CogoObjectID id;
   TRY_TEST(pColl->FindID(NULL,&id),E_INVALIDARG);
   TRY_TEST(pColl->FindID(a,NULL),E_POINTER);
   TRY_TEST(pColl->FindID(a,&id),S_OK);
   TRY_TEST(id,1);

   //
   // Test ID
   //
   pColl->Clear();
   pColl->Add(1,NULL);
   pColl->Add(2,NULL);
   pColl->Add(3,NULL);
   pColl->Add(4,NULL);

   TRY_TEST(pColl->ID(-1,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(500,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(3,NULL),E_POINTER);
   TRY_TEST(pColl->ID(3,&id),S_OK);
   TRY_TEST(id,4);
   
   //
   // Test _Enum
   //
   pColl->Clear();
   pColl->Add(1,NULL);
   pColl->Add(2,NULL);
   pColl->Add(3,NULL);
   pColl->Add(4,NULL);
   CComPtr<IEnumIDs> pEnum;
   TRY_TEST(pColl->get__EnumIDs(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumIDs(&pEnum), S_OK );

   ULONG fetched;
   CogoObjectID target_id = 1;
   while( pEnum->Next(1,&id,&fetched ) == S_OK )
   {
      TRY_TEST(id,target_id++);
   }

   // Test __EnumPaths
   //
   a.Release();
   a.CoCreateInstance(CLSID_Path);
   pColl->Clear();
   pColl->AddEx(1,a);
   pColl->AddEx(2,a);
   pColl->AddEx(3,a);
   pColl->AddEx(4,a);
   CComPtr<IEnumPaths> pEnumPaths;
   TRY_TEST(pColl->get__EnumPaths(NULL), E_POINTER );
   TRY_TEST( pColl->get__EnumPaths(&pEnumPaths), S_OK );

   CComPtr<IPath> testAlign;
   while( pEnumPaths->Next(1,&testAlign,&fetched ) == S_OK )
   {
      TRY_TEST(a.IsEqualObject(testAlign),true);
      testAlign.Release();
   }


   //
   // Test Events
   //
   pColl->Clear(); // start with an empty container

   CComObject<CTestPathCollection>* pTestEvents;
   CComObject<CTestPathCollection>::CreateInstance(&pTestEvents);
   pTestEvents->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestEvents);
   TRY_TEST(AtlAdvise(pColl,punk,IID_IPathCollectionEvents,&dwCookie),S_OK);

   // Add a Path to the collection
   pTestEvents->InitEventTest(1);
   pColl->AddEx(1,Path);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Change the Path
   pTestEvents->InitEventTest(1);
   CComPtr<IPoint2d> point;
   point.CoCreateInstance(CLSID_Point2d);
   Path->AddEx(point);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Remove a Path
   pTestEvents->InitEventTest(1);
   pColl->Remove(1);
   TRY_TEST(pTestEvents->PassedEventTest(),true);

//   // Change Path references
//   pTestEvents->InitEventTest(2);
//   pColl->putref_Item(2,p4);
//   TRY_TEST(pTestEvents->PassedEventTest(),true);

   // Clear
   pTestEvents->InitEventTest(-1);
   pColl->Clear();
   TRY_TEST(pTestEvents->PassedEventTest(),true);

   TRY_TEST(AtlUnadvise(pColl,IID_IPathCollectionEvents,dwCookie),S_OK);
   pTestEvents->Release();

   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPathCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_PathCollection,IID_IPathCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_PathCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestPathCollection::OnPathChanged(IPathCollection* coll,CogoObjectID id,IPath* vc)
{
//   MessageBox(NULL,"PathChanged","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestPathCollection::OnProfileChanged(IPathCollection* coll,IProfile* profile)
{
//   MessageBox(NULL,"ProfileChanged","Event",MB_OK);
   Pass();

   return S_OK;
}

STDMETHODIMP CTestPathCollection::OnPathAdded(IPathCollection* coll,CogoObjectID id,IPath* Path)
{
//   MessageBox(NULL,"PathAdded","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestPathCollection::OnPathRemoved(IPathCollection* coll,CogoObjectID id)
{
//   MessageBox(NULL,"PathRemoved","Event",MB_OK);
   if ( id == m_expectedID )
      Pass();

   return S_OK;
}

STDMETHODIMP CTestPathCollection::OnPathsCleared(IPathCollection* coll)
{
//   MessageBox(NULL,"PathCleared","Event",MB_OK);
   Pass();
   return S_OK;
}
