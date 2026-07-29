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

// TestPoint3d.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestPoint3d.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestPoint3d)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IPoint3d> pPoint;
         ASSERT_EQ(pPoint.CoCreateInstance(CLSID_Point3d),S_OK);

         Float64 x,y,z;
         Float64 x1 = 10.0;
         Float64 y1 = 20.0;
         Float64 x2 = 50;
         Float64 y2 = -23;
         Float64 z1 = 30;
         Float64 z2 = -34;

         // Test Properties
         ASSERT_EQ( pPoint->put_X(x1), S_OK );
         ASSERT_EQ( pPoint->get_X(&x), S_OK);
         ASSERT_EQ( IsEqual(x,x1),true );

         ASSERT_EQ( pPoint->put_Y(y1), S_OK );
         ASSERT_EQ( pPoint->get_Y(&y), S_OK);
         ASSERT_EQ( IsEqual(y,y1),true );

         ASSERT_EQ( pPoint->put_Z(z1), S_OK );
         ASSERT_EQ( pPoint->get_Z(&z), S_OK);
         ASSERT_EQ( IsEqual(z,z1),true );

         ASSERT_EQ( pPoint->get_X(nullptr), E_POINTER );
         ASSERT_EQ( pPoint->get_Y(nullptr), E_POINTER );
         ASSERT_EQ( pPoint->get_Z(nullptr), E_POINTER );

         // Test Move method
         ASSERT_EQ( pPoint->Move(x2,y2,z2),S_OK );
         ASSERT_EQ( pPoint->get_X(&x), S_OK);
         ASSERT_EQ( IsEqual(x,x2),true );
         ASSERT_EQ( pPoint->get_Y(&y), S_OK);
         ASSERT_EQ( IsEqual(y,y2),true );
         ASSERT_EQ( pPoint->get_Z(&z), S_OK);
         ASSERT_EQ( IsEqual(z,z2),true );

         // Test Offset method
         ASSERT_EQ( pPoint->Offset(10,10,10), S_OK );
         ASSERT_EQ( pPoint->get_X(&x), S_OK);
         ASSERT_EQ( IsEqual(x,x2+10),true );
         ASSERT_EQ( pPoint->get_Y(&y), S_OK);
         ASSERT_EQ( IsEqual(y,y2+10),true );
         ASSERT_EQ( pPoint->get_Z(&z), S_OK);
         ASSERT_EQ( IsEqual(z,z2+10),true );

         // Test MoveEx method
         CComPtr<IPoint3d> pPoint2;
         pPoint2.CoCreateInstance(CLSID_Point3d);
         pPoint2->Move(x1,y1,z1);
         ASSERT_EQ( pPoint->MoveEx(pPoint2), S_OK );
         ASSERT_EQ( pPoint->get_X(&x), S_OK);
         ASSERT_EQ( IsEqual(x,x1),true );
         ASSERT_EQ( pPoint->get_Y(&y), S_OK);
         ASSERT_EQ( IsEqual(y,y1),true );
         ASSERT_EQ( pPoint->get_Z(&z), S_OK);
         ASSERT_EQ( IsEqual(z,z1),true );
         ASSERT_EQ( pPoint->MoveEx( nullptr ), E_INVALIDARG );

         // Test OffsetEx Method
         Float64 dx,dy,dz;
         dx = 34;
         dy = -43;
         dz = 32.4;
         CComPtr<ISize3d> pSize;
         pSize.CoCreateInstance(CLSID_Size3d);
         pSize->put_Dx(dx);
         pSize->put_Dy(dy);
         pSize->put_Dz(dz);
         ASSERT_EQ( pPoint->OffsetEx(nullptr),  E_INVALIDARG );
         pPoint->put_X(0.0);
         pPoint->put_Y(0.0);
         pPoint->put_Z(0.0);
         ASSERT_EQ( pPoint->OffsetEx(pSize), S_OK);
         ASSERT_EQ( pPoint->get_X(&x), S_OK );
         ASSERT_EQ( pPoint->get_Y(&y), S_OK );
         ASSERT_EQ( pPoint->get_Z(&z), S_OK );
         ASSERT_EQ( IsEqual(x,dx), true );
         ASSERT_EQ( IsEqual(y,dy), true );
         ASSERT_EQ( IsEqual(z,dz), true );

         // Test Rotate Method
         CComPtr<IVector3d> rv; // Rotation Vector
         ASSERT_EQ(rv.CoCreateInstance(CLSID_Vector3d),S_OK);

         ASSERT_EQ( pPoint->Rotate(0,0,0,nullptr,10.0), E_INVALIDARG );

         rv->put_X(0);
         rv->put_Y(0);
         rv->put_Z(0);
         ASSERT_EQ( pPoint->Rotate(0,0,0,rv,10.0), GEOMETRY_E_ZEROMAGNITUDE);

         // Just do some simple mirroring on the primary axes.
         pPoint->Move(10,0,0);
         rv->put_X(0);
         rv->put_Y(0);
         rv->put_Z(1);
         pPoint->Rotate(5.0,0.0,0.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,-5.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
         ASSERT_EQ( IsEqual(z,0.0), true );

         pPoint->Move(10,0,0);
         rv->put_X(0);
         rv->put_Y(1);
         rv->put_Z(0);
         pPoint->Rotate(5.0,0.0,0.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,-5.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
         ASSERT_EQ( IsEqual(z,0.0), true );

         pPoint->Move(0,10,0);
         rv->put_X(1);
         rv->put_Y(0);
         rv->put_Z(0);
         pPoint->Rotate(0.0,5.0,0.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,-5.0), true );
         ASSERT_EQ( IsEqual(z,0.0), true );

         pPoint->Move(0,10,0);
         rv->put_X(0);
         rv->put_Y(0);
         rv->put_Z(1);
         pPoint->Rotate(0.0,5.0,0.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,-5.0), true );
         ASSERT_EQ( IsEqual(z,0.0), true );

         pPoint->Move(0,0,10);
         rv->put_X(1);
         rv->put_Y(0);
         rv->put_Z(0);
         pPoint->Rotate(0.0,0.0,5.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
         ASSERT_EQ( IsEqual(z,-5.0), true );

         pPoint->Move(0,0,10);
         rv->put_X(0);
         rv->put_Y(1);
         rv->put_Z(0);
         pPoint->Rotate(0.0,0.0,5.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
         ASSERT_EQ( IsEqual(z,-5.0), true );

         // Rotate a point out in space
         pPoint->Move(10,10,10);
         rv->put_X(-1);
         rv->put_Y(0);
         rv->put_Z(1);
         pPoint->Rotate(0.0,0.0,0.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,-10.0), true );
         ASSERT_EQ( IsEqual(y,-10.0), true );
         ASSERT_EQ( IsEqual(z,-10.0), true );

         pPoint->Move(10,10,10);
         rv->put_X(-1);
         rv->put_Y(0);
         rv->put_Z(1);
         pPoint->Rotate(5.0,5.0,5.0,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,-5.0), true );
         ASSERT_EQ( IsEqual(y,-5.0), true );
         ASSERT_EQ( IsEqual(z,-5.0), true );

         pPoint->Move(3.9,2.1,7.0);
         rv->put_X(0);
         rv->put_Y(-1);
         rv->put_Z(-1);
         pPoint->Rotate(2.45,4.00,4.25,rv,62.5*M_PI/180);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,3.58607), true );
         ASSERT_EQ( IsEqual(y,0.26089), true );
         ASSERT_EQ( IsEqual(z,0.58911), true );


         // Test RotateEx Method
         ASSERT_EQ( pPoint->RotateEx( nullptr, nullptr, 10.0 ), E_INVALIDARG );
         ASSERT_EQ( pPoint->RotateEx( pPoint2, nullptr, 10.0), E_INVALIDARG );

         pPoint2->Move(5,5,5);
         pPoint->Move(10,10,10);
         rv->put_X(-1);
         rv->put_Y(0);
         rv->put_Z(1);
         pPoint->RotateEx(pPoint2,rv,M_PI);
         pPoint->get_X(&x);
         pPoint->get_Y(&y);
         pPoint->get_Z(&z);
         ASSERT_EQ( IsEqual(x,-5.0), true );
         ASSERT_EQ( IsEqual(y,-5.0), true );
         ASSERT_EQ( IsEqual(z,-5.0), true );
   }

   TEST_METHOD(SupportsErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Point3d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IPoint3d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests