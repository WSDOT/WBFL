///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestPoint.cpp: implementation of the CTestPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPoint::CTestPoint()
{

}

void CTestPoint::Test()
{
   CComPtr<IPoint2d> pPoint;
   TRY_TEST(pPoint.CoCreateInstance(CLSID_Point2d),S_OK);

   Float64 x,y;
   Float64 x1 = 10.0;
   Float64 y1 = 20.0;
   Float64 x2 = 50;
   Float64 y2 = -23;

   // Test Properties
   TRY_TEST( pPoint->put_X(x1), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,x1),true );

   TRY_TEST( pPoint->put_Y(y1), S_OK );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,y1),true );

   TRY_TEST( pPoint->get_X(nullptr), E_POINTER );
   TRY_TEST( pPoint->get_Y(nullptr), E_POINTER );

   // Test Move method
   TRY_TEST( pPoint->Move(x2,y2),S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,x2),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,y2),true );

   // Test Offset method
   TRY_TEST( pPoint->Offset(10,10), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,x2+10),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,y2+10),true );


   // Test MoveEx method
   CComPtr<IPoint2d> pPoint2;
   pPoint2.CoCreateInstance(CLSID_Point2d);
   pPoint2->Move(x1,y1);
   TRY_TEST( pPoint->MoveEx(pPoint2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,x1),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,y1),true );
   TRY_TEST( pPoint->MoveEx( nullptr ), E_INVALIDARG );

   // Test OffsetEx Method
   Float64 dx,dy;
   dx = 34;
   dy = -43;
   CComPtr<ISize2d> pSize;
   pSize.CoCreateInstance(CLSID_Size2d);
   pSize->put_Dx(dx);
   pSize->put_Dy(dy);
   TRY_TEST( pPoint->OffsetEx(nullptr),  E_INVALIDARG );
   pPoint->put_X(0.0);
   pPoint->put_Y(0.0);
   TRY_TEST( pPoint->OffsetEx(pSize), S_OK);
   TRY_TEST( pPoint->get_X(&x), S_OK );
   TRY_TEST( pPoint->get_Y(&y), S_OK );
   TRY_TEST( IsEqual(x,dx), true );
   TRY_TEST( IsEqual(y,dy), true );

   // Rotate a point through 90 deg increments.
   // Start point at 10,0 and have the center of rotation at 10,10
   pPoint->Move(10,0);
   TRY_TEST( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,20.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,10.0),true );

   TRY_TEST( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,10.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,20.0),true );

   TRY_TEST( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,0.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,10.0),true );

   TRY_TEST( pPoint->Rotate(10,10,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,10.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,0.0),true );

   // Test RotateEx Method
   TRY_TEST( pPoint->RotateEx( nullptr, M_PI ), E_INVALIDARG );
   CComPtr<IPoint2d> pCenter;
   pCenter.CoCreateInstance(CLSID_Point2d);
   pCenter->put_X(10);
   pCenter->put_Y(10);
   pPoint->Move(10,0);
   TRY_TEST( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,20.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,10.0),true );

   TRY_TEST( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,10.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,20.0),true );

   TRY_TEST( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,0.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,10.0),true );

   TRY_TEST( pPoint->RotateEx(pCenter,PI_OVER_2), S_OK );
   TRY_TEST( pPoint->get_X(&x), S_OK);
   TRY_TEST( IsEqual(x,10.0),true );
   TRY_TEST( pPoint->get_Y(&y), S_OK);
   TRY_TEST( IsEqual(y,0.0),true );

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pPoint);
   TRY_TEST( eInfo != nullptr, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPoint2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Point2d,IID_IPoint2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
