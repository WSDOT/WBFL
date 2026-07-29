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

// TestVector2d.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestVector2d.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestVector2d)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IVector2d> pVec;
         ASSERT_EQ(pVec.CoCreateInstance(CLSID_Vector2d),S_OK);

         //
         // Test Properties
         //
         Float64 x, y;
         Float64 x1, y1;
         x = -10.0;
         y = -20.0;
         ASSERT_EQ(pVec->put_X(x),S_OK);
         ASSERT_EQ(pVec->get_X(nullptr),E_POINTER);
         ASSERT_EQ(pVec->get_X(&x1),S_OK);
         ASSERT_EQ(IsEqual(x,x1),true);
         ASSERT_EQ(pVec->put_Y(y),S_OK);
         ASSERT_EQ(pVec->get_Y(nullptr),E_POINTER);
         ASSERT_EQ(pVec->get_Y(&y1),S_OK);
         ASSERT_EQ(IsEqual(y,y1),true);

         //
         // Test Size Property
         //
         CComPtr<ISize2d> pSize;
         ASSERT_EQ(pVec->get_Size(nullptr),E_POINTER);
         ASSERT_EQ(pVec->get_Size(&pSize),S_OK);
         pSize->get_Dx(&x1);
         pSize->get_Dy(&y1);
         ASSERT_EQ(IsEqual(x,x1),true);
         ASSERT_EQ(IsEqual(y,y1),true);

         //
         // Test Magnitude Property
         //

         Float64 mag;
         // use a 3,4,5 triangle
         pVec->put_X(3);
         pVec->put_Y(4);
         ASSERT_EQ(pVec->get_Magnitude(nullptr),E_POINTER);
         ASSERT_EQ(pVec->get_Magnitude(&mag),S_OK);
         ASSERT_EQ(IsEqual(mag,5.0),true);
         // Set magnitude to 15 (9,12,15 triangle, 
         // this is a 3,4,5 triangle scaled by a factor of 3)
         ASSERT_EQ(pVec->put_Magnitude(15.0),S_OK);
         pVec->get_Magnitude(&mag);
         ASSERT_EQ( IsEqual(mag,15.0), true );
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,9.0),true);
         ASSERT_EQ(IsEqual(y1,12.0),true);

         // Magnitude must be a positive number
         ASSERT_EQ(pVec->put_Magnitude(-10),GEOMETRY_E_MAGNITUDELESSTHANZERO);

         //
         // Test Direction property
         //

         // (45 deg line, direction = M_PI/4)
         pVec->put_X(1.0);
         pVec->put_Y(1.0);
         Float64 dir;
         ASSERT_EQ(pVec->get_Direction(nullptr),E_POINTER);
         ASSERT_EQ(pVec->get_Direction(&dir),S_OK);
         ASSERT_EQ(IsEqual(dir,M_PI/4),true);

         // Set direction to 90 deg
         ASSERT_EQ(pVec->put_Direction(PI_OVER_2),S_OK);
         pVec->get_Direction(&dir);
         ASSERT_EQ(IsEqual(dir,PI_OVER_2),true);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,0.0),true);
         ASSERT_EQ(IsEqual(y1,1.4142135),true); // Magnitude stays the same so magnitude is Sqrt(2) = 1.414

         //
         // Test Normalize
         //
         pVec->put_X(10.0);
         pVec->put_Y(10.0);
         ASSERT_EQ(pVec->Normalize(),S_OK);
         pVec->get_Magnitude(&mag);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ(IsEqual(mag,1.0),true);
         ASSERT_EQ(IsEqual(x1,0.70710678),true);
         ASSERT_EQ(IsEqual(y1,0.70710678),true);

         // normalize a zero length vector
         pVec->put_X(0.0);
         pVec->put_Y(0.0);
         ASSERT_EQ(pVec->Normalize(),GEOMETRY_E_ZEROMAGNITUDE);

         //
         // Test IsZero
         //
         ASSERT_EQ(pVec->IsZero(nullptr),E_POINTER);
         VARIANT_BOOL bIsZero;
         pVec->put_X(10);
         pVec->put_Y(0);
         ASSERT_EQ(pVec->IsZero(&bIsZero),S_OK);
         ASSERT_EQ(bIsZero,VARIANT_FALSE);

         pVec->put_X(0);
         pVec->put_Y(10);
         ASSERT_EQ(pVec->IsZero(&bIsZero),S_OK);
         ASSERT_EQ(bIsZero,VARIANT_FALSE);

         pVec->put_X(0);
         pVec->put_Y(0);
         ASSERT_EQ(pVec->IsZero(&bIsZero),S_OK);
         ASSERT_EQ(bIsZero,VARIANT_TRUE);

         //
         // Test Normal
         //
         CComPtr<IVector2d> pNormal;

         // Make source vector point to the right. Normal will be up
         pVec->put_X(10);
         pVec->put_Y(0); 
         ASSERT_EQ(pVec->Normal(nullptr),E_POINTER);
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,0.0),true);
         ASSERT_EQ(IsEqual(y1,10.0),true);

         // Make source vector point to the left. Normal will be down
         pVec->put_X(-10);
         pVec->put_Y(0); 
         pNormal.Release();
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,0.0),true);
         ASSERT_EQ(IsEqual(y1,-10.0),true);

         // Make source vector point up.
         pVec->put_X(0);
         pVec->put_Y(10); 
         pNormal.Release();
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,-10.0),true);
         ASSERT_EQ(IsEqual(y1,0.0),true);

         // Make source vector point down.
         pVec->put_X(0);
         pVec->put_Y(-10); 
         pNormal.Release();
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,10.0),true);
         ASSERT_EQ(IsEqual(y1,0.0),true);

         // Make source vector point up and to the right (45 deg)
         pVec->put_X(10);
         pVec->put_Y(10); 
         pNormal.Release();
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,-10.0),true);
         ASSERT_EQ(IsEqual(y1,10.0),true);

         // Make source vector point up and to the left (45 deg)
         pVec->put_X(-10);
         pVec->put_Y(10); 
         pNormal.Release();
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,-10.0),true);
         ASSERT_EQ(IsEqual(y1,-10.0),true);

         // Make source vector point down and to the right (45 deg)
         pVec->put_X(10);
         pVec->put_Y(-10); 
         pNormal.Release();
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,10.0),true);
         ASSERT_EQ(IsEqual(y1,10.0),true);

         // Make source vector point down and to the left (45 deg)
         pVec->put_X(-10);
         pVec->put_Y(-10); 
         pNormal.Release();
         ASSERT_EQ(pVec->Normal(&pNormal),S_OK);
         pNormal->get_X(&x1);
         pNormal->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,10.0),true);
         ASSERT_EQ(IsEqual(y1,-10.0),true);

         //
         // Test Offset and OffsetEx
         //
         pVec->put_X(10);
         pVec->put_Y(10);
         ASSERT_EQ(pVec->Offset(5,5),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ( IsEqual(x1,15.0), true );
         ASSERT_EQ( IsEqual(y1,15.0), true );

         pVec->put_X(10);
         pVec->put_Y(10);
         CComPtr<ISize2d> pOffset;
         pOffset.CoCreateInstance(CLSID_Size2d);
         pOffset->put_Dx(-20);
         pOffset->put_Dy(-20);
         ASSERT_EQ(pVec->OffsetEx(nullptr),E_INVALIDARG);
         ASSERT_EQ(pVec->OffsetEx(pOffset),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ( IsEqual(x1,-10.0), true );
         ASSERT_EQ( IsEqual(y1,-10.0), true );

         //
         // Test Projection (Projection of Vec1 onto Vec2)
         //
         Float64 projection;
         CComPtr<IVector2d> pVec2;
         pVec2.CoCreateInstance( CLSID_Vector2d );

         ASSERT_EQ(pVec->Projection(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pVec->Projection(pVec2,nullptr),E_POINTER);

         // Vector is zero length
         pVec2->put_X(0);
         pVec2->put_Y(0);
         ASSERT_EQ(pVec->Projection(pVec2,&projection), GEOMETRY_E_ZEROMAGNITUDE); // can't project onto a zero length vector

         // Vectors are right angles (projection = 0)
         pVec->put_X(10);
         pVec->put_Y(0);
         pVec2->put_X(0);
         pVec2->put_Y(10);
         ASSERT_EQ(pVec->Projection(pVec2,&projection),S_OK);
         ASSERT_EQ(IsZero(projection),true);

         // One vector in the X direction, and one at 3,4,5. Projection will
         // be 3
         pVec->put_X(3);
         pVec->put_Y(4);
         pVec2->put_X(10);
         pVec2->put_Y(0);
         ASSERT_EQ(pVec->Projection(pVec2,&projection),S_OK);
         ASSERT_EQ(IsEqual(projection,3.0),true);

         // One vector in the Y direction, and one at 3,4,5. Projection will
         // be 4
         pVec->put_X(3);
         pVec->put_Y(4);
         pVec2->put_X(0);
         pVec2->put_Y(10);
         ASSERT_EQ(pVec->Projection(pVec2,&projection),S_OK);
         ASSERT_EQ(IsEqual(projection,4.0),true);

         // Negative projections (vectors in opposite directions)
         pVec->put_X(-3);
         pVec->put_Y(4);
         pVec2->put_X(10);
         pVec2->put_Y(0);
         ASSERT_EQ(pVec->Projection(pVec2,&projection),S_OK);
         ASSERT_EQ(IsEqual(projection,-3.0),true);

         //
         // Test Reflect
         //
         pVec->put_X(10);
         pVec->put_Y(10);
         ASSERT_EQ(pVec->Reflect(),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ( IsEqual(x1,-10.0), true );
         ASSERT_EQ( IsEqual(y1,-10.0), true );

         //
         // Test Rotate
         //
         pVec->put_X(10);
         pVec->put_Y(0);
         ASSERT_EQ(pVec->Rotate(M_PI/4.0),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ( IsEqual(x1,7.0710678), true );
         ASSERT_EQ( IsEqual(y1,7.0710678), true );

         pVec->put_X(10);
         pVec->put_Y(10);
         ASSERT_EQ(pVec->Rotate(M_PI/4.0),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ( IsEqual(x1,0.0), true );
         ASSERT_EQ( IsEqual(y1,14.142135), true );

         pVec->put_X(10);
         pVec->put_Y(10);
         ASSERT_EQ(pVec->Rotate(-M_PI/4.0),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ( IsEqual(x1,14.142135), true );
         ASSERT_EQ( IsEqual(y1,0.0), true );

         //
         // Test Scale
         //
         pVec->put_X(10); // establish direction
         pVec->put_Y(10);
         pVec->put_Magnitude(10); // fix magnitude
         ASSERT_EQ(pVec->Scale(2),S_OK);
         pVec->get_Magnitude(&mag);
         ASSERT_EQ(IsEqual(mag,20.0),true);

         //
         // Test Dot
         //
         Float64 dot;

         ASSERT_EQ(pVec->Dot(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pVec->Dot(pVec2,nullptr),E_POINTER);

         pVec->put_X(10);
         pVec->put_Y(20);
         pVec2->put_X(30);
         pVec2->put_Y(40);
         ASSERT_EQ(pVec->Dot(pVec2,&dot),S_OK);
         ASSERT_EQ(IsEqual(dot,1100.0),true);

         //
         // Test AngleBetween
         //
         ASSERT_EQ(pVec->AngleBetween(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(pVec->AngleBetween(pVec2,nullptr),E_POINTER);
         pVec->put_X(10);
         pVec->put_Y(0);
         pVec2->put_X(10);
         pVec2->put_Y(10);
         Float64 angle;
         ASSERT_EQ(pVec->AngleBetween(pVec2,&angle),S_OK);
         ASSERT_EQ(IsEqual(angle,M_PI/4.0),true);

         // pVec is zero
         pVec->put_X(0);
         pVec->put_Y(0);
         ASSERT_EQ(pVec->AngleBetween(pVec2,&angle),GEOMETRY_E_ZEROMAGNITUDE);

         // pVec2 is zero
         pVec->put_X(10);
         pVec->put_Y(0);
         pVec2->put_X(0);
         pVec2->put_Y(0);
         ASSERT_EQ(pVec->AngleBetween(pVec2,&angle),GEOMETRY_E_ZEROMAGNITUDE);

         //
         // Test Increment and Decrement
         //
         pVec->put_X(10);
         pVec->put_Y(20);
         pVec2->put_X(50);
         pVec2->put_Y(60);
         ASSERT_EQ(pVec->Increment(nullptr),E_INVALIDARG);
         ASSERT_EQ(pVec->Increment(pVec2),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,60.),true);
         ASSERT_EQ(IsEqual(y1,80.),true);

         CComPtr<IVector2d> pVec3;
         ASSERT_EQ(pVec->IncrementBy(nullptr,&pVec3),E_INVALIDARG);
         ASSERT_EQ(pVec->IncrementBy(pVec2,nullptr), E_POINTER);
         ASSERT_EQ(pVec->IncrementBy(pVec2,&pVec3),S_OK);
         pVec->get_X(&x1); // vector 1, unchanged
         pVec->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,60.),true);
         ASSERT_EQ(IsEqual(y1,80.),true);
         pVec3->get_X(&x1);
         pVec3->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,110.),true);
         ASSERT_EQ(IsEqual(y1,140.),true);

         pVec->put_X(10);
         pVec->put_Y(20);
         pVec2->put_X(50);
         pVec2->put_Y(60);
         ASSERT_EQ(pVec->Decrement(nullptr),E_INVALIDARG);
         ASSERT_EQ(pVec->Decrement(pVec2),S_OK);
         pVec->get_X(&x1);
         pVec->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,-40.),true);
         ASSERT_EQ(IsEqual(y1,-40.),true);

         pVec3.Release();
         ASSERT_EQ(pVec->DecrementBy(nullptr,&pVec3),E_INVALIDARG);
         ASSERT_EQ(pVec->DecrementBy(pVec2,nullptr), E_POINTER);
         ASSERT_EQ(pVec->DecrementBy(pVec2,&pVec3),S_OK);
         pVec->get_X(&x1); // vector 1, unchanged
         pVec->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,-40.),true);
         ASSERT_EQ(IsEqual(y1,-40.),true);
         pVec3->get_X(&x1);
         pVec3->get_Y(&y1);
         ASSERT_EQ(IsEqual(x1,-90.),true);
         ASSERT_EQ(IsEqual(y1,-100.),true);
   }

   TEST_METHOD(SupportsErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Vector2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IVector2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests