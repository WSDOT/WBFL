///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestPoint3dCollection.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestPoint3dCollection.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestPoint3dCollection)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IPoint3dCollection> pColl;
         ASSERT_EQ(pColl.CoCreateInstance( CLSID_Point3dCollection ), S_OK);

         IndexType count;
         ASSERT_EQ(pColl->get_Count(nullptr),E_POINTER);
         ASSERT_EQ(pColl->get_Count(&count),S_OK);
         ASSERT_EQ(count,0);

         //
         // Test Add method
         //
         ASSERT_EQ(pColl->Add(nullptr),E_INVALIDARG);

         // add some points and see if we get them back
         CComPtr<IPoint3d> p1;
         p1.CoCreateInstance( CLSID_Point3d );
         p1->put_X(10);
         p1->put_Y(10);
         p1->put_Z(10);
         ASSERT_EQ(pColl->Add(p1),S_OK);

         CComPtr<IPoint3d> p2;
         p2.CoCreateInstance( CLSID_Point3d );
         p2->put_X(20);
         p2->put_Y(20);
         p2->put_Z(20);
         ASSERT_EQ(pColl->Add(p2),S_OK);

         CComPtr<IPoint3d> p3;
         p3.CoCreateInstance( CLSID_Point3d );
         p3->put_X(30);
         p3->put_Y(30);
         p3->put_Z(30);
         ASSERT_EQ(pColl->Add(p3),S_OK);

         CComPtr<IPoint3d> p4;
         p4.CoCreateInstance( CLSID_Point3d );
         p4->put_X(40);
         p4->put_Y(40);
         p4->put_Z(40);
         ASSERT_EQ(pColl->Add(p4),S_OK);

         ASSERT_EQ(pColl->get_Count(&count),S_OK);
         ASSERT_EQ(count,4);

         // Test Item property
         CComPtr<IPoint3d> pnt;
         ASSERT_EQ(pColl->get_Item(-1,&pnt),E_INVALIDARG); // invalid index
         ASSERT_EQ(pColl->get_Item(10,&pnt),E_INVALIDARG); // index out of range - too high
         ASSERT_EQ(pColl->get_Item(1,nullptr),E_POINTER);
         ASSERT_EQ(pColl->get_Item(0,&pnt),S_OK);
         Float64 x,y,z;
         pnt->get_X(&x);
         pnt->get_Y(&y);
         pnt->get_Z(&z);
         ASSERT_EQ( IsEqual(x,10.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );
         ASSERT_EQ( IsEqual(z,10.0), true );

         // Points in the container should be references. Change p1 and see if pnt changes
         p1->put_X(100);
         pnt->get_X(&x);
         ASSERT_EQ( IsEqual(x,100.0), true );

         //
         // Test Remove
         //
         ASSERT_EQ(pColl->Remove(-1),E_INVALIDARG); // invalid index
         ASSERT_EQ(pColl->Remove(10),E_INVALIDARG); // index out of range - too high
         ASSERT_EQ(pColl->Remove(2),S_OK);

         // p3 should still be OK because the contains holds references
         ASSERT_EQ(p3->get_X(&x),S_OK); // this will crash if p3 is bad.

         // The count should now be 3
         pColl->get_Count(&count);
         ASSERT_EQ(count,3);

         // Getting the item at index 3 should fail
         pnt.Release();
         ASSERT_EQ( pColl->get_Item(3,&pnt), E_INVALIDARG);

         // The item at index 2 should be p4
         pnt.Release();
         pColl->get_Item(2,&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         pnt->get_Z(&z);
         ASSERT_EQ( IsEqual(x,40.0), true );
         ASSERT_EQ( IsEqual(y,40.0), true );
         ASSERT_EQ( IsEqual(z,40.0), true );

         //
         // Test Clear
         //
         ASSERT_EQ( pColl->Clear(), S_OK );
         pColl->get_Count(&count);
         ASSERT_EQ(count,0);

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
         CComPtr<IEnumPoint3d> pEnum;
         ASSERT_EQ(pColl->get__Enum(nullptr), E_POINTER );
         ASSERT_EQ( pColl->get__Enum(&pEnum), S_OK );

         ULONG fetched;
         Float64 i = 10;
         pnt.Release();
         while( pEnum->Next(1,&pnt,&fetched ) == S_OK )
         {
            pnt->get_X(&x);
            ASSERT_EQ( IsEqual(x,i), true );
            i += 10.0;
            pnt.Release();
         }
   }

   TEST_METHOD(SupportsErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Point3dCollection ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IPoint3dCollection ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests