///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestPoint.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestPoint.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestPoint)
{
public:
   TEST_METHOD(BasicOperations)
   {
      CComPtr<IPoint2d> pPoint;
      ASSERT_EQ(pPoint.CoCreateInstance(CLSID_Point2d),S_OK);

      Float64 x,y;
      Float64 x1 = 10.0;
      Float64 y1 = 20.0;
      Float64 x2 = 50;
      Float64 y2 = -23;

      // Test Properties
      ASSERT_EQ( pPoint->put_X(x1), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,x1),true );

      ASSERT_EQ( pPoint->put_Y(y1), S_OK );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,y1),true );

      ASSERT_EQ( pPoint->get_X(nullptr), E_POINTER );
      ASSERT_EQ( pPoint->get_Y(nullptr), E_POINTER );

      // Test Move method
      ASSERT_EQ( pPoint->Move(x2,y2),S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,x2),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,y2),true );

      // Test Offset method
      ASSERT_EQ( pPoint->Offset(10,10), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,x2+10),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,y2+10),true );


      // Test MoveEx method
      CComPtr<IPoint2d> pPoint2;
      pPoint2.CoCreateInstance(CLSID_Point2d);
      pPoint2->Move(x1,y1);
      ASSERT_EQ( pPoint->MoveEx(pPoint2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,x1),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,y1),true );
      ASSERT_EQ( pPoint->MoveEx( nullptr ), E_INVALIDARG );

      // Test OffsetEx Method
      Float64 dx,dy;
      dx = 34;
      dy = -43;
      CComPtr<ISize2d> pSize;
      pSize.CoCreateInstance(CLSID_Size2d);
      pSize->put_Dx(dx);
      pSize->put_Dy(dy);
      ASSERT_EQ( pPoint->OffsetEx(nullptr),  E_INVALIDARG );
      pPoint->put_X(0.0);
      pPoint->put_Y(0.0);
      ASSERT_EQ( pPoint->OffsetEx(pSize), S_OK);
      ASSERT_EQ( pPoint->get_X(&x), S_OK );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK );
      ASSERT_EQ( IsEqual(x,dx), true );
      ASSERT_EQ( IsEqual(y,dy), true );

      // Rotate a point through 90 deg increments.
      // Start point at 10,0 and have the center of rotation at 10,10
      pPoint->Move(10,0);
      ASSERT_EQ( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,20.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,10.0),true );

      ASSERT_EQ( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,10.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,20.0),true );

      ASSERT_EQ( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,0.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,10.0),true );

      ASSERT_EQ( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,10.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,0.0),true );

      // Test RotateEx Method
      ASSERT_EQ( pPoint->RotateEx( nullptr, M_PI ), E_INVALIDARG );
      CComPtr<IPoint2d> pCenter;
      pCenter.CoCreateInstance(CLSID_Point2d);
      pCenter->put_X(10);
      pCenter->put_Y(10);
      pPoint->Move(10,0);
      ASSERT_EQ( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,20.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,10.0),true );

      ASSERT_EQ( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,10.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,20.0),true );

      ASSERT_EQ( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,0.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,10.0),true );

      ASSERT_EQ( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
      ASSERT_EQ( pPoint->get_X(&x), S_OK);
      ASSERT_EQ( IsEqual(x,10.0),true );
      ASSERT_EQ( pPoint->get_Y(&y), S_OK);
      ASSERT_EQ( IsEqual(y,0.0),true );

      // Test ISupportErrorInfo
      CComQIPtr<ISupportErrorInfo> eInfo(pPoint);
      ASSERT_EQ( eInfo != nullptr, true );
      ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IPoint2d ), S_OK );
      ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

      // Test IObjectSafety
      ASSERT_EQ( TestIObjectSafety(CLSID_Point2d,IID_IPoint2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests