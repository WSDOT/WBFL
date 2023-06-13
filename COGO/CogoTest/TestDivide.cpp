///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TestDivide.cpp: implementation of the CTestDivide class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDivide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDivide::CTestDivide()
{

}

CTestDivide::~CTestDivide()
{

}

void CTestDivide::Test()
{
   CComPtr<IDivide> divide;
   TRY_TEST(divide.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(divide);
   TRY_TEST( model != nullptr, true );

   model->StorePoint(1,0,0);
   model->StorePoint(2,10,0);
   model->StorePoint(3,-10,0);

   CComPtr<IPoint2d> pnt;
   Float64 x,y;

   // Test DivideArc
   TRY_TEST(divide->Arc(4,1,2,1,3,-1),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,2,1,3,0),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,2,1,3,1),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,-2,1,3,4), E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,2,-1,3,4), E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,2,1,-3,4), E_INVALIDARG);
   TRY_TEST(divide->Arc(1,1,2,1,3,4), S_FALSE);
   TRY_TEST(divide->Arc(4,0,2,1,3,4),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,1,1,3,4), S_FALSE);
   TRY_TEST(divide->Arc(4,1,2,1,1,4), S_FALSE);
   //TRY_TEST(divide->Arc(4,1,2,1,2,4), E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,2,1,3,4),S_OK);
   pnt.Release();
   TRY_TEST(model->GetPointByID(4,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,7.07106781187),true);
   TRY_TEST(IsEqual(y,7.07106781187),true);

   pnt.Release();
   TRY_TEST(model->GetPointByID(5,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,0.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   pnt.Release();
   TRY_TEST(model->GetPointByID(6,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-7.07106781187),true);
   TRY_TEST(IsEqual(y,7.07106781187),true);

   // Test Divide BetweenPoints
   model->ClearPoints();
   model->StorePoint(1,10,10);
   model->StorePoint(2,110,110);

   TRY_TEST(divide->BetweenPoints(3,1,1,2,-1),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,1,1,2, 0),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,1,1,2, 1),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,0,1,2,10),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,1,-1,2,10), E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,1,1,-2,10), E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(1,1,1,2,10), S_FALSE);

   TRY_TEST(divide->BetweenPoints(3,1,1,2,10),S_OK);
   for ( IDType i = 3; i <= 11; i++ )
   {
      pnt.Release();
      TRY_TEST(model->GetPointByID(i,&pnt),S_OK);
      pnt->get_X(&x);
      pnt->get_Y(&y);
      TRY_TEST(IsEqual(x,(i-1)*10.),true);
      TRY_TEST(IsEqual(y,(i-1)*10.),true);
   }

   // Test Divide LineSegment
   model->ClearPoints();
   model->StorePoint(1,10,10);
   model->StorePoint(2,110,110);
   CComPtr<IPoint2d> p1, p2;
   model->GetPointByID(1,&p1);
   model->GetPointByID(2,&p2);

   model->StorePathSegment(1,1,2);

   TRY_TEST(divide->LineSegment(3,1,1,-1),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,1,1, 0),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,1,1, 1),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,0,1,10),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,1,-1,10), E_INVALIDARG);
   TRY_TEST(divide->LineSegment(1,1,1,10),  S_FALSE);

   TRY_TEST(divide->LineSegment(3,1,1,10),S_OK);
   for ( int i = 3; i <= 11; i++ )
   {
      pnt.Release();
      TRY_TEST(model->GetPointByID(i,&pnt),S_OK);
      pnt->get_X(&x);
      pnt->get_Y(&y);
      TRY_TEST(IsEqual(x,(i-1)*10.),true);
      TRY_TEST(IsEqual(y,(i-1)*10.),true);
   }

   // Test CompoundCurve
   model->StorePoint(101,0,1000);
   model->StorePoint(102,700,1000);
   model->StorePoint(103,1000,700);

   model->StoreCompoundCurve(1,101,102,103,500,100,TransitionCurveType::Clothoid,200, TransitionCurveType::Clothoid);

   TRY_TEST(divide->CompoundCurve(150,1,1,-1),E_INVALIDARG);
   TRY_TEST(divide->CompoundCurve(150,0,1,5),E_INVALIDARG);
   TRY_TEST(divide->CompoundCurve(150,1,-1,5), E_INVALIDARG);
   TRY_TEST(divide->CompoundCurve(99,1,1,5),S_FALSE);

   TRY_TEST(divide->CompoundCurve(150,1,1,10),S_OK);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(150,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,493.3008,0.001),true);
   TRY_TEST(IsEqual(y,999.4672,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(151,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,547.4251,0.001),true);
   TRY_TEST(IsEqual(y,995.7440,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(152,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,600.8740,0.001),true);
   TRY_TEST(IsEqual(y,986.4948,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(153,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,653.0065,0.001),true);
   TRY_TEST(IsEqual(y,971.5102,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(154,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,703.2089,0.001),true);
   TRY_TEST(IsEqual(y,950.9663,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(155,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,750.8904,0.001),true);
   TRY_TEST(IsEqual(y,925.1051,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(156,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,795.5411,0.001),true);
   TRY_TEST(IsEqual(y,894.2997,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(157,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,837.3133,0.001),true);
   TRY_TEST(IsEqual(y,859.6735,0.001),true);
   
   pnt.Release();
   TRY_TEST(model->GetPointByID(158,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,876.9803,0.001),true);
   TRY_TEST(IsEqual(y,822.6429,0.001),true);
}