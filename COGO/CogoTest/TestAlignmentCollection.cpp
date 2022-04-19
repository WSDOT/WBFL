///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// TestAlignmentCollection.cpp: implementation of the CTestAlignmentCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlignmentCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAlignmentCollection::CTestAlignmentCollection()
{

}

void CTestAlignmentCollection::Test()
{
   CComPtr<IAlignmentCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_AlignmentCollection ), S_OK);

   CollectionIndexType count;
   TRY_TEST(pColl->get_Count(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<IAlignment> Alignment;
   Alignment.CoCreateInstance(CLSID_Alignment);

   CComPtr<IAlignmentFactory> factory;
   TRY_TEST(pColl->get_Factory(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Factory(&factory),S_OK);
   TRY_TEST( factory != nullptr, true );
   TRY_TEST(pColl->putref_Factory(nullptr),E_INVALIDARG);
   TRY_TEST(pColl->putref_Factory(factory),S_OK);

   //
   // Test AddEx method
   //
   TRY_TEST(pColl->AddEx(1,Alignment),S_OK);
   TRY_TEST(pColl->AddEx(1,Alignment),COGO_E_ALIGNMENTALREADYDEFINED);
   CComPtr<IAlignment> a;
   TRY_TEST(pColl->get_Item(1,&a),S_OK);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,1);

   // Test Item property
   a.Release();
   TRY_TEST(pColl->get_Item(-1,&a),COGO_E_ALIGNMENTNOTFOUND);
   TRY_TEST(pColl->get_Item(1,nullptr),E_POINTER);
   TRY_TEST(pColl->get_Item(1,&a),S_OK);

   //
   // Test Remove
   //
   TRY_TEST(pColl->Remove(-1),COGO_E_ALIGNMENTNOTFOUND);
   TRY_TEST(pColl->Remove(1),S_OK);

   //
   // Test Clear
   //
   pColl->AddEx(1,Alignment);
   pColl->get_Count(&count);
   TRY_TEST(count,1);
   TRY_TEST( pColl->Clear(), S_OK );
   pColl->get_Count(&count);
   TRY_TEST(count,0);

   //
   // Test put_Item
   //
   TRY_TEST(pColl->AddEx(1,Alignment),S_OK);

   a.Release();
   a.CoCreateInstance(CLSID_Alignment);
   TRY_TEST(pColl->putref_Item(1,nullptr),E_INVALIDARG);
   TRY_TEST(pColl->putref_Item(-1,Alignment),COGO_E_ALIGNMENTNOTFOUND);
   TRY_TEST(pColl->putref_Item(1,a),S_OK);

   //
   // Test FindID
   //
   CogoObjectID id;
   TRY_TEST(pColl->FindID(nullptr,&id),E_INVALIDARG);
   TRY_TEST(pColl->FindID(a,nullptr),E_POINTER);
   TRY_TEST(pColl->FindID(a,&id),S_OK);
   TRY_TEST(id,1);

   //
   // Test ID
   //
   pColl->Clear();
   pColl->Add(1,nullptr);
   pColl->Add(2,nullptr);
   pColl->Add(3,nullptr);
   pColl->Add(4,nullptr);

   TRY_TEST(pColl->ID(-1,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(500,&id),E_INVALIDARG);
   TRY_TEST(pColl->ID(3,nullptr),E_POINTER);
   TRY_TEST(pColl->ID(3,&id),S_OK);
   TRY_TEST(id,4);
   
   //
   // Test _Enum
   //
   pColl->Clear();
   pColl->Add(1,nullptr);
   pColl->Add(2,nullptr);
   pColl->Add(3,nullptr);
   pColl->Add(4,nullptr);
   CComPtr<IEnumIDs> pEnum;
   TRY_TEST(pColl->get__EnumIDs(nullptr), E_POINTER );
   TRY_TEST( pColl->get__EnumIDs(&pEnum), S_OK );

   ULONG fetched;
   CogoObjectID target_id = 1;
   while( pEnum->Next(1,&id,&fetched ) == S_OK )
   {
      TRY_TEST(id,target_id++);
   }

   // Test __EnumAlignments
   //
   a.Release();
   a.CoCreateInstance(CLSID_Alignment);
   pColl->Clear();
   pColl->AddEx(1,a);
   pColl->AddEx(2,a);
   pColl->AddEx(3,a);
   pColl->AddEx(4,a);
   CComPtr<IEnumAlignments> pEnumAlignments;
   TRY_TEST(pColl->get__EnumAlignments(nullptr), E_POINTER );
   TRY_TEST( pColl->get__EnumAlignments(&pEnumAlignments), S_OK );

   CComPtr<IAlignment> testAlign;
   while( pEnumAlignments->Next(1,&testAlign,&fetched ) == S_OK )
   {
      TRY_TEST(a.IsEqualObject(testAlign),true);
      testAlign.Release();
   }


   //
   // Test ISupportErrorInfo
   //
   CComQIPtr<ISupportErrorInfo> eInfo(pColl);
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IAlignmentCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_AlignmentCollection,IID_IAlignmentCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_AlignmentCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
