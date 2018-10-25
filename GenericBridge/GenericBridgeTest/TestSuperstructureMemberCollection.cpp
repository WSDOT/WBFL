///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestSuperstructureMemberCollection.cpp: implementation of the CTestSuperstructureMemberCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSuperstructureMemberCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSuperstructureMemberCollection::CTestSuperstructureMemberCollection()
{

}

CTestSuperstructureMemberCollection::~CTestSuperstructureMemberCollection()
{

}

void CTestSuperstructureMemberCollection::Test()
{
   TestDefaults();
   TestMethods();
}

void CTestSuperstructureMemberCollection::TestDefaults()
{
//   // Create a default bridge
//   CComPtr<IGenericBridge> bridge;
//   bridge.CoCreateInstance(CLSID_GenericBridge);
//
//   // Drill down and get a superstructure members collection
//   CComPtr<ISuperstructureMemberCollection> members;
//   bridge->get_SuperstructureMembers(0,&members);
//
//   TRY_TEST(members != NULL,true);
//
//   // Validate Defaults
//   long nMembers;
//   TRY_TEST(members->get_Count(NULL),E_POINTER);
//   TRY_TEST(members->get_Count(&nMembers),S_OK);
//   TRY_TEST(nMembers,0);
//
//   Float64 length;
//   TRY_TEST(members->get_MemberLength(NULL),E_POINTER);
//   TRY_TEST(members->get_MemberLength(&length),S_OK);
//   TRY_TEST(IsEqual(length,0.0),true);
//
//   VARIANT_BOOL bSymmetrical;
//   TRY_TEST(members->get_Symmetrical(NULL),E_POINTER);
//   TRY_TEST(members->get_Symmetrical(&bSymmetrical),S_OK);
//   TRY_TEST(bSymmetrical,VARIANT_FALSE);
//
//   ///////////////////////////////////////
//   // Test Error Info
//   CComQIPtr<ISupportErrorInfo> eInfo(members);
//   TRY_TEST( eInfo != 0, true );
//
//   // Interfaces that should be supported
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISuperstructureMemberCollection ), S_OK );
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
//
//   // Interface that is not supported
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
//
//   // Test IObjectSafety
//   TRY_TEST( TestIObjectSafety(members,IID_ISuperstructureMemberCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
//   TRY_TEST( TestIObjectSafety(members,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestSuperstructureMemberCollection::TestMethods()
{
//   // Create a default bridge
//   CComPtr<IGenericBridge> bridge;
//   bridge.CoCreateInstance(CLSID_GenericBridge);
//
////   CComPtr<IGirderSpacing> spacing;
////   bridge->get_GirderSpacing(&spacing);
////   spacing->Add(1);
//
//   // Drill down and get a superstructure members collection
//   CComPtr<ISuperstructureMemberCollection> members;
//   bridge->get_SuperstructureMembers(0,&members);
//
//   // Add
//   TRY_TEST(members->Add(),S_OK);
//   long nMembers;
//   TRY_TEST(members->get_Count(&nMembers),S_OK);
//   TRY_TEST(nMembers,1);
//
//   // Clear
//   TRY_TEST(members->Clear(),S_OK);
//   TRY_TEST(members->get_Count(&nMembers),S_OK);
//   TRY_TEST(nMembers,0);
//
//   // CopyTo
//   members->Add();
//   members->Add();
//
//   CComPtr<ISuperstructureMember> mbr;
//   members->get_Item(0,&mbr);
//
//   mbr->put_Length(10.0);
//
//   TRY_TEST(members->CopyTo(-1,1),E_INVALIDARG);
//   TRY_TEST(members->CopyTo(100,1),E_INVALIDARG);
//   TRY_TEST(members->CopyTo(0,-1),E_INVALIDARG);
//   TRY_TEST(members->CopyTo(0,100),E_INVALIDARG);
//   TRY_TEST(members->CopyTo(0,0),S_OK);
//   TRY_TEST(members->CopyTo(0,1),S_OK);
//   mbr.Release();
//   members->get_Item(1,&mbr);
//   Float64 length;
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   // Insert
//   members->Clear();
//   members->Add();
//   members->Add();
//   mbr.Release();
//   members->get_Item(0,&mbr);
//   mbr->put_Length(10.0);
//   mbr.Release();
//   members->get_Item(1,&mbr);
//   mbr->put_Length(20.0);
//
//   TRY_TEST(members->Insert(-1),E_INVALIDARG);
//   TRY_TEST(members->Insert(100),E_INVALIDARG);
//   TRY_TEST(members->Insert(1),S_OK);
//
//   mbr.Release();
//   members->get_Item(0,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   mbr.Release();
//   members->get_Item(1,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   mbr.Release();
//   members->get_Item(2,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   members->get_MemberLength(&length);
//   TRY_TEST(IsEqual(length,31.0),true);
//
//   // Reverse
//   TRY_TEST(members->Reverse(),S_OK);
//
//   mbr.Release();
//   members->get_Item(0,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   mbr.Release();
//   members->get_Item(1,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   mbr.Release();
//   members->get_Item(2,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   // MoveTo
//   TRY_TEST(members->MoveTo(-1,0),E_INVALIDARG);
//   TRY_TEST(members->MoveTo(200,0),E_INVALIDARG);
//   TRY_TEST(members->MoveTo(2,-1),E_INVALIDARG);
//   TRY_TEST(members->MoveTo(2,200),E_INVALIDARG);
//   TRY_TEST(members->MoveTo(2,0),S_OK);
//
//   mbr.Release();
//   members->get_Item(0,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   mbr.Release();
//   members->get_Item(1,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,20.0),true);
//
//   mbr.Release();
//   members->get_Item(2,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   // Remove
//   TRY_TEST(members->Remove(-1),E_INVALIDARG);
//   TRY_TEST(members->Remove(100),E_INVALIDARG);
//   TRY_TEST(members->Remove(1),S_OK);
//
//   mbr.Release();
//   members->get_Item(0,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,10.0),true);
//
//   mbr.Release();
//   members->get_Item(1,&mbr);
//   mbr->get_Length(&length);
//   TRY_TEST(IsEqual(length,1.0),true);
//
//   // Clear
//   TRY_TEST(members->Clear(),S_OK);
//   members->get_Count(&nMembers);
//   TRY_TEST(nMembers,0);
}
