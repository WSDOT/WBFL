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

// TestVector3d.cpp: implementation of the CTestVector3d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestVector3d.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestVector3d::CTestVector3d()
{

}

CTestVector3d::~CTestVector3d()
{

}

void CTestVector3d::Test()
{
   CComPtr<IVector3d> pVec;
   TRY_TEST(pVec.CoCreateInstance(CLSID_Vector3d),S_OK);

   //
   // Test Properties
   //
   Float64 x, y, z;
   Float64 x1, y1, z1;
   x = -10.0;
   y = -20.0;
   z = -30.0;
   TRY_TEST(pVec->put_X(x),S_OK);
   TRY_TEST(pVec->get_X(nullptr),E_POINTER);
   TRY_TEST(pVec->get_X(&x1),S_OK);
   TRY_TEST(IsEqual(x,x1),true);

   TRY_TEST(pVec->put_Y(y),S_OK);
   TRY_TEST(pVec->get_Y(nullptr),E_POINTER);
   TRY_TEST(pVec->get_Y(&y1),S_OK);
   TRY_TEST(IsEqual(y,y1),true);

   TRY_TEST(pVec->put_Z(z),S_OK);
   TRY_TEST(pVec->get_Z(nullptr),E_POINTER);
   TRY_TEST(pVec->get_Z(&z1),S_OK);
   TRY_TEST(IsEqual(z,z1),true);

   //
   // Test Size Property
   //
   CComPtr<ISize3d> pSize;
   TRY_TEST(pVec->get_Size(nullptr),E_POINTER);
   TRY_TEST(pVec->get_Size(&pSize),S_OK);
   pSize->get_Dx(&x1);
   pSize->get_Dy(&y1);
   pSize->get_Dz(&z1);
   TRY_TEST(IsEqual(x,x1),true);
   TRY_TEST(IsEqual(y,y1),true);
   TRY_TEST(IsEqual(z,z1),true);

   //
   // Test Magnitude Property
   //

   Float64 mag;
   pVec->put_X(3);
   pVec->put_Y(4);
   pVec->put_Z(5);
   TRY_TEST(pVec->get_Magnitude(nullptr),E_POINTER);
   TRY_TEST(pVec->get_Magnitude(&mag),S_OK);
   TRY_TEST(IsEqual(mag,7.07106781187),true);

   TRY_TEST(pVec->put_Magnitude(70.7106781187),S_OK);
   pVec->get_Magnitude(&mag);
   TRY_TEST( IsEqual(mag,70.7106781187), true );
   pVec->get_X(&x1);
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST(IsEqual(x1,30.0),true);
   TRY_TEST(IsEqual(y1,40.0),true);
   TRY_TEST(IsEqual(z1,50.0),true);

   // Magnitude must be a positive number
   TRY_TEST(pVec->put_Magnitude(-10),GEOMETRY_E_MAGNITUDELESSTHANZERO);
 
   //
   // Test Normalize
   //
   pVec->put_X(10.0);
   pVec->put_Y(20.0);
   pVec->put_Z(30.0);
   TRY_TEST(pVec->Normalize(),S_OK);
   pVec->get_Magnitude(&mag);
   pVec->get_X(&x1);
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST(IsEqual(mag,1.0),true);
   TRY_TEST(IsEqual(x1,0.267261),true);
   TRY_TEST(IsEqual(y1,0.534522),true);
   TRY_TEST(IsEqual(z1,0.801784),true);

   // normalize a zero length vector
   pVec->put_X(0.0);
   pVec->put_Y(0.0);
   pVec->put_Z(0.0);
   TRY_TEST(pVec->Normalize(),GEOMETRY_E_ZEROMAGNITUDE);

   //
   // Test IsZero
   //
   TRY_TEST(pVec->IsZero(nullptr),E_POINTER);
   VARIANT_BOOL bIsZero;
   pVec->put_X(10);
   pVec->put_Y(0);
   pVec->put_Z(0);
   TRY_TEST(pVec->IsZero(&bIsZero),S_OK);
   TRY_TEST(bIsZero,VARIANT_FALSE);

   pVec->put_X(0);
   pVec->put_Y(10);
   pVec->put_Z(0);
   TRY_TEST(pVec->IsZero(&bIsZero),S_OK);
   TRY_TEST(bIsZero,VARIANT_FALSE);

   pVec->put_X(0);
   pVec->put_Y(0);
   pVec->put_Z(10);
   TRY_TEST(pVec->IsZero(&bIsZero),S_OK);
   TRY_TEST(bIsZero,VARIANT_FALSE);

   pVec->put_X(0);
   pVec->put_Y(0);
   pVec->put_Z(0);
   TRY_TEST(pVec->IsZero(&bIsZero),S_OK);
   TRY_TEST(bIsZero,VARIANT_TRUE);

   //
   // Test Offset and OffsetEx
   //
   pVec->put_X(10);
   pVec->put_Y(10);
   pVec->put_Z(10);
   TRY_TEST(pVec->Offset(5,5,5),S_OK);
   pVec->get_X(&x1);
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST( IsEqual(x1,15.0), true );
   TRY_TEST( IsEqual(y1,15.0), true );
   TRY_TEST( IsEqual(z1,15.0), true );

   pVec->put_X(10);
   pVec->put_Y(10);
   pVec->put_Z(10);
   CComPtr<ISize3d> pOffset;
   pOffset.CoCreateInstance(CLSID_Size3d);
   pOffset->put_Dx(-20);
   pOffset->put_Dy(-20);
   pOffset->put_Dz(-20);
   TRY_TEST(pVec->OffsetEx(nullptr),E_INVALIDARG);
   TRY_TEST(pVec->OffsetEx(pOffset),S_OK);
   pVec->get_X(&x1);
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST( IsEqual(x1,-10.0), true );
   TRY_TEST( IsEqual(y1,-10.0), true );
   TRY_TEST( IsEqual(z1,-10.0), true );

   //
   // Test Projection (Projection of Vec2 onto Vec1)
   //
   Float64 projection;
   CComPtr<IVector3d> pVec2;
   pVec2.CoCreateInstance( CLSID_Vector3d );

   TRY_TEST(pVec->Projection(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pVec->Projection(pVec2,nullptr),E_POINTER);

   // Vector is zero length
   pVec2->put_X(0);
   pVec2->put_Y(0);
   pVec2->put_Z(0);
   TRY_TEST(pVec->Projection(pVec2,&projection), GEOMETRY_E_ZEROMAGNITUDE);

   // Vectors are right angles (projection = 0)
   pVec->put_X(10);
   pVec->put_Y(10);
   pVec->put_Z(0);

   pVec2->put_X(-10);
   pVec2->put_Y(10);
   pVec2->put_Z(0);
   TRY_TEST(pVec->Projection(pVec2,&projection),S_OK);
   TRY_TEST(IsZero(projection),true);

   // One vector in the X direction, and one at 3,4,5. Projection will
   // be 3
   pVec->put_X(3);
   pVec->put_Y(4);
   pVec->put_Z(0);
   pVec2->put_X(10);
   pVec2->put_Y(0);
   pVec2->put_Z(0);
   TRY_TEST(pVec->Projection(pVec2,&projection),S_OK);
   TRY_TEST(IsEqual(projection,3.0),true);

   // One vector in the Y direction, and one at 3,4,5. Projection will
   // be 4
   pVec->put_X(3);
   pVec->put_Y(4);
   pVec->put_Z(0);
   pVec2->put_X(0);
   pVec2->put_Y(10);
   pVec2->put_Z(0);
   TRY_TEST(pVec->Projection(pVec2,&projection),S_OK);
   TRY_TEST(IsEqual(projection,4.0),true);

   // Negative projections (vectors in opposite directions)
   pVec->put_X(-3);
   pVec->put_Y(4);
   pVec->put_Z(0);
   pVec2->put_X(10);
   pVec2->put_Y(0);
   pVec2->put_Z(0);
   TRY_TEST(pVec->Projection(pVec2,&projection),S_OK);
   TRY_TEST(IsEqual(projection,-3.0),true);

   pVec->put_X(10);
   pVec->put_Y(10);
   pVec->put_Z(10);
   pVec2->put_X(10);
   pVec2->put_Y(00);
   pVec2->put_Z(10);
   TRY_TEST(pVec->Projection(pVec2,&projection),S_OK);
   TRY_TEST(IsEqual(projection,14.1421356),true);

   //
   // Test Reflect
   //
   pVec->put_X(10);
   pVec->put_Y(10);
   pVec->put_Z(10);
   TRY_TEST(pVec->Reflect(),S_OK);
   pVec->get_X(&x1);
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST( IsEqual(x1,-10.0), true );
   TRY_TEST( IsEqual(y1,-10.0), true );
   TRY_TEST( IsEqual(z1,-10.0), true );

   //
   // Test Scale
   //
   pVec->put_X(10); // establish direction
   pVec->put_Y(10);
   pVec->put_Z(10);
   pVec->put_Magnitude(10); // fix magnitude
   TRY_TEST(pVec->Scale(2),S_OK);
   pVec->get_Magnitude(&mag);
   TRY_TEST(IsEqual(mag,20.0),true);

   //
   // Test Dot
   //
   Float64 dot;

   TRY_TEST(pVec->Dot(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pVec->Dot(pVec2,nullptr),E_POINTER);

   pVec->put_X(10);
   pVec->put_Y(20);
   pVec->put_Z(30);
   pVec2->put_X(40);
   pVec2->put_Y(50);
   pVec2->put_Z(60);
   TRY_TEST(pVec->Dot(pVec2,&dot),S_OK);
   TRY_TEST(IsEqual(dot,3200.0),true);

   //
   // Test AngleBetween
   //
   TRY_TEST(pVec->AngleBetween(nullptr,nullptr),E_INVALIDARG);
   TRY_TEST(pVec->AngleBetween(pVec2,nullptr),E_POINTER);
   pVec->put_X(10);
   pVec->put_Y(0);
   pVec->put_Z(0);
   pVec2->put_X(10);
   pVec2->put_Y(10);
   pVec2->put_Z(0);
   Float64 angle;
   TRY_TEST(pVec->AngleBetween(pVec2,&angle),S_OK);
   TRY_TEST(IsEqual(angle,M_PI/4.0),true);

   pVec->put_X(10);
   pVec->put_Y(10);
   pVec->put_Z(10);
   pVec2->put_X(-10);
   pVec2->put_Y(-10);
   pVec2->put_Z(-10);
   TRY_TEST(pVec->AngleBetween(pVec2,&angle),S_OK);
   TRY_TEST(IsEqual(angle,M_PI),true);

   // pVec is zero
   pVec->put_X(0);
   pVec->put_Y(0);
   pVec->put_Z(0);
   TRY_TEST(pVec->AngleBetween(pVec2,&angle),GEOMETRY_E_ZEROMAGNITUDE);

   // pVec2 is zero
   pVec->put_X(10);
   pVec->put_Y(0);
   pVec->put_Z(0);
   pVec2->put_X(0);
   pVec2->put_Y(0);
   pVec2->put_Z(0);
   TRY_TEST(pVec->AngleBetween(pVec2,&angle),GEOMETRY_E_ZEROMAGNITUDE);

   //
   // Test Cross 
   //
   pVec->put_X(10);
   pVec->put_Y(20);
   pVec->put_Z(30);
   pVec2->put_X(-32);
   pVec2->put_Y(-25);
   pVec2->put_Z(4);

   CComPtr<IVector3d> cross;
   TRY_TEST( pVec->Cross(nullptr,nullptr), E_INVALIDARG);
   TRY_TEST( pVec->Cross(pVec2,nullptr), E_POINTER);
   TRY_TEST( pVec->Cross(pVec2,&cross), S_OK );
   cross->get_X(&x);
   cross->get_Y(&y);
   cross->get_Z(&z);
   TRY_TEST( IsEqual(x,830.), true );
   TRY_TEST( IsEqual(y,-1000.), true );
   TRY_TEST( IsEqual(z,390.), true );

   cross.Release();
   TRY_TEST( pVec2->Cross(pVec,&cross), S_OK );
   cross->get_X(&x);
   cross->get_Y(&y);
   cross->get_Z(&z);
   TRY_TEST( IsEqual(x,-830.), true );
   TRY_TEST( IsEqual(y,1000.), true );
   TRY_TEST( IsEqual(z,-390.), true );

   //
   // Test Increment and Decrement
   //
   pVec->put_X(10);
   pVec->put_Y(20);
   pVec->put_Z(30);
   pVec2->put_X(50);
   pVec2->put_Y(60);
   pVec2->put_Z(70);
   TRY_TEST(pVec->Increment(nullptr),E_INVALIDARG);
   TRY_TEST(pVec->Increment(pVec2),S_OK);
   pVec->get_X(&x1);
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST(IsEqual(x1,60.),true);
   TRY_TEST(IsEqual(y1,80.),true);
   TRY_TEST(IsEqual(z1,100.),true);

   CComPtr<IVector3d> pVec3;
   TRY_TEST(pVec->IncrementBy(nullptr,&pVec3),E_INVALIDARG);
   TRY_TEST(pVec->IncrementBy(pVec2,nullptr), E_POINTER);
   TRY_TEST(pVec->IncrementBy(pVec2,&pVec3),S_OK);
   pVec->get_X(&x1); // vector 1 unchanged
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST(IsEqual(x1,60.),true);
   TRY_TEST(IsEqual(y1,80.),true);
   TRY_TEST(IsEqual(z1,100.),true);
   pVec3->get_X(&x1);
   pVec3->get_Y(&y1);
   pVec3->get_Z(&z1);
   TRY_TEST(IsEqual(x1,110.),true);
   TRY_TEST(IsEqual(y1,140.),true);
   TRY_TEST(IsEqual(z1,170.),true);

   pVec->put_X(10);
   pVec->put_Y(20);
   pVec->put_Z(30);
   pVec2->put_X(50);
   pVec2->put_Y(60);
   pVec2->put_Z(70);
   TRY_TEST(pVec->Decrement(nullptr),E_INVALIDARG);
   TRY_TEST(pVec->Decrement(pVec2),S_OK);
   pVec->get_X(&x1);
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST(IsEqual(x1,-40.),true);
   TRY_TEST(IsEqual(y1,-40.),true);
   TRY_TEST(IsEqual(z1,-40.),true);

   pVec3.Release();
   TRY_TEST(pVec->DecrementBy(nullptr,&pVec3),E_INVALIDARG);
   TRY_TEST(pVec->DecrementBy(pVec2,nullptr), E_POINTER);
   TRY_TEST(pVec->DecrementBy(pVec2,&pVec3),S_OK);
   pVec->get_X(&x1); // vector 1, unchanged
   pVec->get_Y(&y1);
   pVec->get_Z(&z1);
   TRY_TEST(IsEqual(x1,-40.),true);
   TRY_TEST(IsEqual(y1,-40.),true);
   TRY_TEST(IsEqual(z1,-40.),true);
   pVec3->get_X(&x1);
   pVec3->get_Y(&y1);
   pVec3->get_Z(&z1);
   TRY_TEST(IsEqual(x1,-90.),true);
   TRY_TEST(IsEqual(y1,-100.),true);
   TRY_TEST(IsEqual(z1,-110.),true);

   TestISupportErrorInfo();
}

void CTestVector3d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_Vector3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IVector3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
