///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// TestPoint2dCollection.cpp: implementation of the CTestPoint2dCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPoint2dCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPoint2dCollection::CTestPoint2dCollection()
{

}

CTestPoint2dCollection::~CTestPoint2dCollection()
{

}

void CTestPoint2dCollection::Test()
{
   CComPtr<IPoint2dCollection> pColl;
   TRY_TEST(pColl.CoCreateInstance( CLSID_Point2dCollection ), S_OK);

   IndexType count;
   TRY_TEST(pColl->get_Count(nullptr),E_POINTER);
   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   //
   // Test Add method
   //
   TRY_TEST(pColl->Add(nullptr),E_INVALIDARG);

   // add some points and see if we get them back
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance( CLSID_Point2d );
   p1->put_X(10);
   p1->put_Y(10);
   TRY_TEST(pColl->Add(p1),S_OK);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance( CLSID_Point2d );
   p2->put_X(20);
   p2->put_Y(20);
   TRY_TEST(pColl->Add(p2),S_OK);

   CComPtr<IPoint2d> p3;
   p3.CoCreateInstance( CLSID_Point2d );
   p3->put_X(30);
   p3->put_Y(30);
   TRY_TEST(pColl->Add(p3),S_OK);

   CComPtr<IPoint2d> p4;
   p4.CoCreateInstance( CLSID_Point2d );
   p4->put_X(40);
   p4->put_Y(40);
   TRY_TEST(pColl->Add(p4),S_OK);

   TRY_TEST(pColl->get_Count(&count),S_OK);
   TRY_TEST(count,4);

   // Test Item property
   CComPtr<IPoint2d> pnt;
   TRY_TEST(pColl->get_Item(-1,&pnt),E_INVALIDARG); // invalid index
   TRY_TEST(pColl->get_Item(10,&pnt),E_INVALIDARG); // index out of range - too high
   TRY_TEST(pColl->get_Item(1,nullptr),E_POINTER);
   TRY_TEST(pColl->get_Item(0,&pnt),S_OK);
   Float64 x,y;
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
   TRY_TEST(pColl->Remove(-1),E_INVALIDARG); // invalid index
   TRY_TEST(pColl->Remove(10),E_INVALIDARG); // index out of range - too high
   TRY_TEST(pColl->Remove(2),S_OK);

   // p3 should still be OK because the contains holds references
   TRY_TEST(p3->get_X(&x),S_OK); // this will crash if p3 is bad.

   // The count should now be 3
   pColl->get_Count(&count);
   TRY_TEST(count,3);

   // Getting the item at index 3 should fail
   pnt.Release();
   TRY_TEST( pColl->get_Item(3,&pnt), E_INVALIDARG);

   // The item at index 2 should be p4
   pnt.Release();
   pColl->get_Item(2,&pnt);
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
   // Test _Enum
   //
   p1->put_X(10);
   p2->put_X(20);
   p3->put_X(30);
   p4->put_X(40);
   pColl->Add(p1);
   pColl->Add(p2);
   pColl->Add(p3);
   pColl->Add(p4);
   CComPtr<IEnumPoint2d> pEnum;
   TRY_TEST(pColl->get__Enum(nullptr), E_POINTER );
   TRY_TEST( pColl->get__Enum(&pEnum), S_OK );

   ULONG fetched;
   Float64 i = 10;
   pnt.Release();
   while( pEnum->Next(1,&pnt,&fetched ) == S_OK )
   {
      pnt->get_X(&x);
      TRY_TEST( IsEqual(x,i), true );
      i += 10.0;
      pnt.Release();
   }

   TestISupportErrorInfo();
}

void CTestPoint2dCollection::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_Point2dCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPoint2dCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
