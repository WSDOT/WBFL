///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
   TRY_TEST( model != nullptr, true );

   model->StorePoint(1,10,10);
   model->StorePoint(2,40,10);

   // Test some error cases
   TRY_TEST(tangent->External(3,1,-20.0,4,2,5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->External(3,1, 20.0,4,2,-5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->External(3,10, 20.0,4,2,5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->External(3,1,20.0,4,20,5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->External(1,1,20.0,4,2,5.0,tsCW),  S_FALSE);
   TRY_TEST(tangent->External(3,1,20.0,2,2,5.0,tsCW), S_FALSE);
   TRY_TEST(tangent->External(3,1,20.0,4,1,5.0,tsCW), S_FALSE);

   CComPtr<IPoint2d> A, B;
   Float64 x,y;

   // define the big circle first
   TRY_TEST(tangent->External(3,1,20.0,4,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(3,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   B.Release();
   TRY_TEST(model->GetPointByID(4,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y,14.33013),true);

   TRY_TEST(tangent->External(5,1,20.0,6,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(5,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   B.Release();
   TRY_TEST(model->GetPointByID(6,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y, 14.33013),true);

   // define the small circle first
   TRY_TEST(tangent->External(7,2,5.0,8,1,20.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(7,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y,14.33013),true);

   B.Release();
   TRY_TEST(model->GetPointByID(8,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   TRY_TEST(tangent->External(9,2,5.0,10,1,20.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(9,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,42.5),true);
   TRY_TEST(IsEqual(y, 14.33013),true);

   B.Release();
   TRY_TEST(model->GetPointByID(10,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,27.3205),true);

   // rotate both circles 180deg around (0,0)
   // (make x = -x)
   A.Release();
   model->GetPointByID(1,&A);
   A->get_X(&x);
   A->put_X(-x);
   model->ReplacePointByIDEx(1, A);

   B.Release();
   model->GetPointByID(2,&B);
   B->get_X(&x);
   B->put_X(-x);
   model->ReplacePointByIDEx(2, B);

   // big circle first
   TRY_TEST(tangent->External(11,1,20.0,12,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(11,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(12,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);

   TRY_TEST(tangent->External(13,1,20.0,14,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(13,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);

   B.Release();
   TRY_TEST(model->GetPointByID(14,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);

   // small circle first
   TRY_TEST(tangent->External(15,2,5.0,16,1,20.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(15,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(16,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);

   TRY_TEST(tangent->External(17,2,5.0,18,1,20.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(17,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-42.5),true);
   TRY_TEST(IsEqual(y,5.66987),true);

   B.Release();
   TRY_TEST(model->GetPointByID(18,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-20.0),true);
   TRY_TEST(IsEqual(y,-7.3205),true);

   // rotate both (original) circles 90deg around (0,0)
   // (make Y = x, X = -Y)
   A.Release();
   model->GetPointByID(1,&A);
   A->put_X(-10);
   A->put_Y( 10);
   model->ReplacePointByIDEx(1, A);

   B.Release();
   model->GetPointByID(2,&B);
   B->put_X(-10);
   B->put_Y( 40);
   model->ReplacePointByIDEx(2, B);

   // big circle first
   TRY_TEST(tangent->External(19,1,20.0,20,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(19,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-27.3205),true);
   TRY_TEST(IsEqual(y, 20.0),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(20,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y, 42.5),true);

   TRY_TEST(tangent->External(21,1,20.0,22,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(21,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-27.3205),true);
   TRY_TEST(IsEqual(y,20.0),true);

   B.Release();
   TRY_TEST(model->GetPointByID(22,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y,42.5),true);

   // small circle first
   TRY_TEST(tangent->External(23,2,5.0,24,1,20.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(23,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y, 42.5),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(23,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y, 42.5),true);

   TRY_TEST(tangent->External(25,2,5.0,26,1,20.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(25,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-14.33013),true);
   TRY_TEST(IsEqual(y, 42.5),true);

   B.Release();
   TRY_TEST(model->GetPointByID(26,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-27.3205),true);
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
   model->GetPointByID(1,&A);
   A->put_X(0);
   A->put_Y(0);
   model->ReplacePointByIDEx(1, A);

   B.Release();
   model->GetPointByID(2,&B);
   B->put_X(10);
   B->put_Y(10);
   model->ReplacePointByIDEx(2, B);

   TRY_TEST(tangent->External(27,1,5.0,28,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(27,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(28,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,6.46447,0.001),true);
   TRY_TEST(IsEqual(y,13.5355,0.001),true);

   TRY_TEST(tangent->External(29,1,5.0,30,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(29,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);

   B.Release();
   TRY_TEST(model->GetPointByID(30,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,6.46447,0.001),true);
   TRY_TEST(IsEqual(y,13.5355,0.001), true);

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 2
   A.Release();
   model->GetPointByID(1,&A);
   A->put_X(0);
   A->put_Y(0);
   model->ReplacePointByIDEx(1, A);

   B.Release();
   model->GetPointByID(2,&B);
   B->put_X(-10);
   B->put_Y(10);
   model->ReplacePointByIDEx(2, B);
   TRY_TEST(tangent->External(31,1,5.0,32,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(31,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(32,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-13.5355,0.001),true);
   TRY_TEST(IsEqual(y, 6.46447,0.001),true);

   TRY_TEST(tangent->External(33,1,5.0,34,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(33,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);

   B.Release();
   TRY_TEST(model->GetPointByID(34,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-13.5355,0.001),true);
   TRY_TEST(IsEqual(y, 6.46447,0.001),true);

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 3
   A.Release();
   model->GetPointByID(1,&A);
   A->put_X(0);
   A->put_Y(0);
   model->ReplacePointByIDEx(1, A);

   B.Release();
   model->GetPointByID(2,&B);
   B->put_X(-10);
   B->put_Y(-10);
   model->ReplacePointByIDEx(2, B);
   TRY_TEST(tangent->External(35,1,5.0,36,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(35,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(36,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-6.46447,0.001),true);
   TRY_TEST(IsEqual(y,-13.5355,0.001),true);

   TRY_TEST(tangent->External(37,1,5.0,38,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(37,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y,-3.5355,0.001),true);

   B.Release();
   TRY_TEST(model->GetPointByID(38,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,-6.46447,0.001),true);
   TRY_TEST(IsEqual(y,-13.5355,0.001),true);

   // 2 Equal radius circles, one centered at the origin, one at 45deg in quadrant 4
   A.Release();
   model->GetPointByID(1,&A);
   A->put_X(0);
   A->put_Y(0);
   model->ReplacePointByIDEx(1, A);

   B.Release();
   model->GetPointByID(2,&B);
   B->put_X( 10);
   B->put_Y(-10);
   model->ReplacePointByIDEx(2, B);
   TRY_TEST(tangent->External(39,1,5.0,40,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(39,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);
 
   B.Release();
   TRY_TEST(model->GetPointByID(40,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,13.5355,0.001),true);
   TRY_TEST(IsEqual(y,-6.46447,0.001),true);

   TRY_TEST(tangent->External(41,1,5.0,42,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(41,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.5355,0.001),true);
   TRY_TEST(IsEqual(y, 3.5355,0.001),true);

   B.Release();
   TRY_TEST(model->GetPointByID(42,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x, 13.5355,0.001),true);
   TRY_TEST(IsEqual(y,-6.46447,0.001),true);
}

void CTestTangent::TestCross()
{
   CComPtr<ITangent> tangent;
   TRY_TEST(tangent.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(tangent);
   TRY_TEST( model != nullptr, true );

   model->StorePoint(1,10,10);
   model->StorePoint(2,40,10);

   // Test some error cases
   TRY_TEST(tangent->Cross(3,1,-20.0,4,2,5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->Cross(3,1, 20.0,4,2,-5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->Cross(3,10, 20.0,4,2,5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->Cross(3,1,20.0,4,20,5.0,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->Cross(1,1,20.0,4,2,5.0,tsCW), S_FALSE);
   TRY_TEST(tangent->Cross(3,1,20.0,2,2,5.0,tsCW), S_FALSE);
   TRY_TEST(tangent->Cross(3,1,20.0,4,1,5.0,tsCW), S_FALSE);

   CComPtr<IPoint2d> A, B;
   Float64 x,y;

   // define the big circle first
   TRY_TEST(tangent->Cross(3,1,20.0,4,2,5.0,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(3,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,26.66666),true);
   TRY_TEST(IsEqual(y,-1.05541),true);

   B.Release();
   TRY_TEST(model->GetPointByID(4,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,44.16667),true);
   TRY_TEST(IsEqual(y,12.76385),true);

   TRY_TEST(tangent->Cross(5,1,20.0,6,2,5.0,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(5,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,26.66666),true);
   TRY_TEST(IsEqual(y,21.055415),true);

   B.Release();
   TRY_TEST(model->GetPointByID(6,&B),S_OK);
   B->get_X(&x);
   B->get_Y(&y);
   TRY_TEST(IsEqual(x,44.16667),true);
   TRY_TEST(IsEqual(y, 7.23615),true);
}

void CTestTangent::TestPoint()
{
   CComPtr<ITangent> tangent;
   TRY_TEST(tangent.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(tangent);
   TRY_TEST( model != nullptr, true );

   Float64 radius = 20;

   model->StorePoint(1,10,10);
   model->StorePoint(2,10 + radius*sqrt(2.),10);
   model->StorePoint(3,10 + radius,10 + radius);
   model->StorePoint(999,5,5);

   // Test some error cases
   TRY_TEST(tangent->Point(4,1,-20.0,2,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->Point(4,10,20.0,2,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->Point(4,1,20.0,4,tsCW), E_INVALIDARG);
   TRY_TEST(tangent->Point(1,1,20.0,2,tsCW), S_FALSE);
   TRY_TEST(tangent->Point(4,1,20.0,1,tsCW), S_FALSE);
   TRY_TEST(tangent->Point(4,1,20.0,999,tsCW), S_FALSE);

   CComPtr<IPoint2d> A, B;
   Float64 x,y;

   TRY_TEST(tangent->Point(4,1,radius,2,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(4,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,24.14214),true);
   TRY_TEST(IsEqual(y,-4.14214),true);

   TRY_TEST(tangent->Point(5,1,radius,2,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(5,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x,24.14214),true);
   TRY_TEST(IsEqual(y,24.14214),true);

   TRY_TEST(tangent->Point(6,1,radius,3,tsCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(6,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 30.),true);
   TRY_TEST(IsEqual(y, 10.),true);

   TRY_TEST(tangent->Point(7,1,radius,3,tsCCW),S_OK);

   A.Release();
   TRY_TEST(model->GetPointByID(7,&A),S_OK);
   A->get_X(&x);
   A->get_Y(&y);
   TRY_TEST(IsEqual(x, 10.),true);
   TRY_TEST(IsEqual(y, 30.),true);
}
