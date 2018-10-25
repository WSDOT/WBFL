///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestTangent.cpp: implementation of the CTestTangent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTangent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestTangent::CTestTangent()
{

}

CTestTangent::~CTestTangent()
{

}

void CTestTangent::Test()
{
   TestExternal();
   TestCross();
   TestPoint();
}

void CTestTangent::TestExternal()
{
   CComPtr<ITangent> tangent;
   TRY_TEST(tangent.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(tangent);
   TRY_TEST( model != NULL, true );

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->Add(1,10,10,NULL);
   points->Add(2,40,10,NULL);

   // Test some error cases
   TRY_TEST(tangent->External(3,1,-20.0,4,2,5.0,tsCW), COGO_E_RADIUS);
   TRY_TEST(tangent->External(3,1, 20.0,4,2,-5.0,tsCW),COGO_E_RADIUS);
   TRY_TEST(tangent->External(3,10, 20.0,4,2,5.0,tsCW),COGO_E_POINTNOTFOUND);
   TRY_TEST(tangent->External(3,1,20.0,4,20,5.0,tsCW), COGO_E_POINTNOTFOUND);
   TRY_TEST(tangent->External(1,1,20.0,4,2,5.0,tsCW),  COGO_E_POINTALREADYDEFINED);
   TRY_TEST(tangent->External(3,1,20.0,2,2,5.0,tsCW),  COGO_E_POINTALREADYDEFINED);
   TRY_TEST(tangent->External(3,1,20.0,4,1,5.0,tsCW),  COGO_E_COINCIDENTPOINTS);

   CComPtr<IPoint2d> A, B;
   Float64 x,y;

   // define the big circle first
   TRY_TEST(tangent->External(3,1,20.0,4,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(3,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   B.Release();
   TRY_TEST(points->get_Item(4,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y,14.33013),true);

   TRY_TEST(tangent->External(5,1,20.0,6,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(5,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);

   B.Release();
   TRY_TEST(points->get_Item(6,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);

   // define the small circle first
   TRY_TEST(tangent->External(7,2,5.0,8,1,20.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(7,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y,14.33013),true);

   B.Release();
   TRY_TEST(points->get_Item(8,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   TRY_TEST(tangent->External(9,2,5.0,10,1,20.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(9,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);

   B.Release();
   TRY_TEST(points->get_Item(10,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);

   // rotate both circles 180deg around (0,0)
   // (make x = -x)
   A.Release();
   points->get_Item(1,&A);
   A->get_X(&x);
   A->put_X(-x);

   B.Release();
   points->get_Item(2,&B);
   B->get_X(&x);
   B->put_X(-x);

   // big circle first
   TRY_TEST(tangent->External(11,1,20.0,12,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(11,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);
 
   B.Release();
   TRY_TEST(points->get_Item(12,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);

   TRY_TEST(tangent->External(13,1,20.0,14,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(13,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   B.Release();
   TRY_TEST(points->get_Item(14,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,14.33013),true);

   // small circle first
   TRY_TEST(tangent->External(15,2,5.0,16,1,20.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(15,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);
 
   B.Release();
   TRY_TEST(points->get_Item(16,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);

   TRY_TEST(tangent->External(17,2,5.0,18,1,20.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(17,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,14.33013),true);

   B.Release();
   TRY_TEST(points->get_Item(18,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   // rotate both (original) circles 90deg around (0,0)
   // (make Y = x, X = -Y)
   A.Release();
   points->get_Item(1,&A);
   A->put_X(-10);
   A->put_Y( 10);

   B.Release();
   points->get_Item(2,&B);
   B->put_X(-10);
   B->put_Y( 40);

   // big circle first
   TRY_TEST(tangent->External(19,1,20.0,20,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(19,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-27.3205),true);
   TRY_TEST(IsEqual(y, 20.0),true);
 
   B.Release();
   TRY_TEST(points->get_Item(20,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y, 42.5),true);

   TRY_TEST(tangent->External(21,1,20.0,22,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(21,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,7.3205),true);
   TRY_TEST(IsEqual(y,20.0),true);

   B.Release();
   TRY_TEST(points->get_Item(22,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-5.66987),true);
   TRY_TEST(IsEqual(y,42.5),true);

   // small circle first
   TRY_TEST(tangent->External(23,2,5.0,24,1,20.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(23,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y, 42.5),true);
 
   B.Release();
   TRY_TEST(points->get_Item(23,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y, 42.5),true);

   TRY_TEST(tangent->External(25,2,5.0,26,1,20.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(25,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-5.66987),true);
   TRY_TEST(IsEqual(y, 42.5),true);

   B.Release();
   TRY_TEST(points->get_Item(26,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,7.3205),true);
   TRY_TEST(IsEqual(y,20.0),true);

   /////////////////////////////////////////////////////////////////////////////////////////

   // Quadrants   ^
   //             |
   //       2     |     1
   //             |
   //   ----------+----------->
   //             |
   //       3     |     4
   //             |

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 1
   A.Release();
   points->get_Item(1,&A);
   A->put_X(0);
   A->put_Y(0);

   B.Release();
   points->get_Item(2,&B);
   B->put_X(10);
   B->put_Y(10);

   TRY_TEST(tangent->External(27,1,5.0,28,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(27,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(points->get_Item(28,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,6.46447,0.001),true);
   TRY_TEST(IsEqual(y,13.5355,0.001),true);

   TRY_TEST(tangent->External(29,1,5.0,30,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(29,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);

   B.Release();
   TRY_TEST(points->get_Item(30,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,13.5355,0.001),true);
   TRY_TEST(IsEqual(y,6.46447,0.001),true);

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 2
   A.Release();
   points->get_Item(1,&A);
   A->put_X(0);
   A->put_Y(0);

   B.Release();
   points->get_Item(2,&B);
   B->put_X(-10);
   B->put_Y(10);
   TRY_TEST(tangent->External(31,1,5.0,32,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(31,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(points->get_Item(32,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-13.5355,0.001),true);
   TRY_TEST(IsEqual(y, 6.46447,0.001),true);

   TRY_TEST(tangent->External(33,1,5.0,34,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(33,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);

   B.Release();
   TRY_TEST(points->get_Item(34,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-6.46447,0.001),true);
   TRY_TEST(IsEqual(y, 13.5355,0.001),true);

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 3
   A.Release();
   points->get_Item(1,&A);
   A->put_X(0);
   A->put_Y(0);

   B.Release();
   points->get_Item(2,&B);
   B->put_X(-10);
   B->put_Y(-10);
   TRY_TEST(tangent->External(35,1,5.0,36,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(35,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(points->get_Item(36,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-6.46447,0.001),true);
   TRY_TEST(IsEqual(y,-13.5355,0.001),true);

   TRY_TEST(tangent->External(37,1,5.0,38,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(37,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);

   B.Release();
   TRY_TEST(points->get_Item(38,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-13.5355,0.001),true);
   TRY_TEST(IsEqual(y,-6.46447,0.001),true);

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 4
   A.Release();
   points->get_Item(1,&A);
   A->put_X(0);
   A->put_Y(0);

   B.Release();
   points->get_Item(2,&B);
   B->put_X( 10);
   B->put_Y(-10);
   TRY_TEST(tangent->External(39,1,5.0,40,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(39,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(points->get_Item(40,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,13.5355,0.001),true);
   TRY_TEST(IsEqual(y,-6.46447,0.001),true);

   TRY_TEST(tangent->External(41,1,5.0,42,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(41,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);

   B.Release();
   TRY_TEST(points->get_Item(42,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x, 6.46447,0.001),true);
   TRY_TEST(IsEqual(y,-13.5355,0.001),true);
}

void CTestTangent::TestCross()
{
   CComPtr<ITangent> tangent;
   TRY_TEST(tangent.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(tangent);
   TRY_TEST( model != NULL, true );

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->Add(1,10,10,NULL);
   points->Add(2,40,10,NULL);

   // Test some error cases
   TRY_TEST(tangent->Cross(3,1,-20.0,4,2,5.0,tsCW), COGO_E_RADIUS);
   TRY_TEST(tangent->Cross(3,1, 20.0,4,2,-5.0,tsCW),COGO_E_RADIUS);
   TRY_TEST(tangent->Cross(3,10, 20.0,4,2,5.0,tsCW),COGO_E_POINTNOTFOUND);
   TRY_TEST(tangent->Cross(3,1,20.0,4,20,5.0,tsCW), COGO_E_POINTNOTFOUND);
   TRY_TEST(tangent->Cross(1,1,20.0,4,2,5.0,tsCW),  COGO_E_POINTALREADYDEFINED);
   TRY_TEST(tangent->Cross(3,1,20.0,2,2,5.0,tsCW),  COGO_E_POINTALREADYDEFINED);
   TRY_TEST(tangent->Cross(3,1,20.0,4,1,5.0,tsCW),  COGO_E_COINCIDENTPOINTS);

   CComPtr<IPoint2d> A, B;
   Float64 x,y;

   // define the big circle first
   TRY_TEST(tangent->Cross(3,1,20.0,4,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(3,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,26.66666),true);
   TRY_TEST(IsEqual(y,21.05541),true);

   B.Release();
   TRY_TEST(points->get_Item(4,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,44.16667),true);
   TRY_TEST(IsEqual(y, 7.23615),true);

   TRY_TEST(tangent->Cross(5,1,20.0,6,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(5,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,26.66666),true);
   TRY_TEST(IsEqual(y,-1.055415),true);

   B.Release();
   TRY_TEST(points->get_Item(6,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,44.16667),true);
   TRY_TEST(IsEqual(y,12.76385),true);
}

void CTestTangent::TestPoint()
{
   CComPtr<ITangent> tangent;
   TRY_TEST(tangent.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(tangent);
   TRY_TEST( model != NULL, true );

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   Float64 radius = 20;

   points->Add(1,10,10,NULL);
   points->Add(2,10 + radius*sqrt(2.),10,NULL);
   points->Add(3,10 + radius,10 + radius,NULL);
   points->Add(999,5,5,NULL);

   // Test some error cases
   TRY_TEST(tangent->Point(4,1,-20.0,2,tsCW), COGO_E_RADIUS);
   TRY_TEST(tangent->Point(4,10,20.0,2,tsCW),COGO_E_POINTNOTFOUND);
   TRY_TEST(tangent->Point(4,1,20.0,4,tsCW), COGO_E_POINTNOTFOUND);
   TRY_TEST(tangent->Point(1,1,20.0,2,tsCW),  COGO_E_POINTALREADYDEFINED);
   TRY_TEST(tangent->Point(4,1,20.0,1,tsCW),  COGO_E_COINCIDENTPOINTS);
   TRY_TEST(tangent->Point(4,1,20.0,999,tsCW),  COGO_E_POINTINCIRCLE);

   CComPtr<IPoint2d> A, B;
   Float64 x,y;

   TRY_TEST(tangent->Point(4,1,radius,2,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(4,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,24.14214),true);
   TRY_TEST(IsEqual(y,24.14214),true);

   TRY_TEST(tangent->Point(5,1,radius,2,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(5,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,24.14214),true);
   TRY_TEST(IsEqual(y,-4.14214),true);

   TRY_TEST(tangent->Point(6,1,radius,3,tsCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(6,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 10.),true);
   TRY_TEST(IsEqual(y, 30.),true);

   TRY_TEST(tangent->Point(7,1,radius,3,tsCCW),S_OK);

   A.Release();
   TRY_TEST(points->get_Item(7,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 30.),true);
   TRY_TEST(IsEqual(y, 10.),true);
}
