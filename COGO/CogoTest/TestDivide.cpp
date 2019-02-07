///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->Add(1,0,0,nullptr);
   points->Add(2,10,0,nullptr);
   points->Add(3,-10,0,nullptr);

   CComPtr<IPoint2d> pnt;
   Float64 x,y;

   // Test DivideArc
   TRY_TEST(divide->Arc(4,1,2,1,3,-1),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,2,1,3,0),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,2,1,3,1),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,-2,1,3,4),COGO_E_POINTNOTFOUND);
   TRY_TEST(divide->Arc(4,1,2,-1,3,4),COGO_E_POINTNOTFOUND);
   TRY_TEST(divide->Arc(4,1,2,1,-3,4),COGO_E_POINTNOTFOUND);
   TRY_TEST(divide->Arc(1,1,2,1,3,4),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(divide->Arc(4,0,2,1,3,4),E_INVALIDARG);
   TRY_TEST(divide->Arc(4,1,1,1,3,4),COGO_E_ANGLE);
   TRY_TEST(divide->Arc(4,1,2,1,1,4),COGO_E_ANGLE);
   TRY_TEST(divide->Arc(4,1,2,1,2,4),COGO_E_ANGLE);
   TRY_TEST(divide->Arc(4,1,2,1,3,4),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(4,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,7.07106781187),true);
   TRY_TEST(IsEqual(y,7.07106781187),true);

   pnt.Release();
   TRY_TEST(points->get_Item(5,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,0.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   pnt.Release();
   TRY_TEST(points->get_Item(6,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-7.07106781187),true);
   TRY_TEST(IsEqual(y,7.07106781187),true);

   // Test Divide BetweenPoints
   points->Clear();
   points->Add(1,10,10,nullptr);
   points->Add(2,110,110,nullptr);

   TRY_TEST(divide->BetweenPoints(3,1,1,2,-1),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,1,1,2, 0),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,1,1,2, 1),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,0,1,2,10),  E_INVALIDARG);
   TRY_TEST(divide->BetweenPoints(3,1,-1,2,10), COGO_E_POINTNOTFOUND);
   TRY_TEST(divide->BetweenPoints(3,1,1,-2,10), COGO_E_POINTNOTFOUND);
   TRY_TEST(divide->BetweenPoints(1,1,1,2,10),  COGO_E_POINTALREADYDEFINED);

   TRY_TEST(divide->BetweenPoints(3,1,1,2,10),S_OK);
   for ( CogoObjectID i = 3; i <= 11; i++ )
   {
      pnt.Release();
      TRY_TEST(points->get_Item(i,&pnt),S_OK);
      TRY_TEST(CheckPointType(pnt),S_OK);
      pnt->get_X(&x);
      pnt->get_Y(&y);
      TRY_TEST(IsEqual(x,(i-1)*10.),true);
      TRY_TEST(IsEqual(y,(i-1)*10.),true);
   }

   // Test Divide LineSegment
   points->Clear();
   points->Add(1,10,10,nullptr);
   points->Add(2,110,110,nullptr);
   CComPtr<IPoint2d> p1, p2;
   points->get_Item(1,&p1);
   points->get_Item(2,&p2);

   CComPtr<ILineSegmentCollection> lines;
   model->get_LineSegments(&lines);
   lines->Add(1,p1,p2,nullptr);

   TRY_TEST(divide->LineSegment(3,1,1,-1),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,1,1, 0),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,1,1, 1),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,0,1,10),  E_INVALIDARG);
   TRY_TEST(divide->LineSegment(3,1,-1,10), COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(divide->LineSegment(1,1,1,10),  COGO_E_POINTALREADYDEFINED);

   TRY_TEST(divide->LineSegment(3,1,1,10),S_OK);
   for ( int i = 3; i <= 11; i++ )
   {
      pnt.Release();
      TRY_TEST(points->get_Item(i,&pnt),S_OK);
      TRY_TEST(CheckPointType(pnt),S_OK);
      pnt->get_X(&x);
      pnt->get_Y(&y);
      TRY_TEST(IsEqual(x,(i-1)*10.),true);
      TRY_TEST(IsEqual(y,(i-1)*10.),true);
   }

   // Test HorzCurve
   points->Add(101,0,1000,nullptr);
   points->Add(102,700,1000,nullptr);
   points->Add(103,1000,700,nullptr);
   CComPtr<IHorzCurveCollection> hcurves;
   model->get_HorzCurves(&hcurves);

   CComPtr<IPoint2d> pbt, pi, pft;
   points->get_Item(101,&pbt);
   points->get_Item(102,&pi);
   points->get_Item(103,&pft);

   hcurves->Add(1,pbt,pi,pft,500,100,200,nullptr);

   TRY_TEST(divide->HorzCurve(150,1,1,-1),E_INVALIDARG);
   TRY_TEST(divide->HorzCurve(150,0,1,5),E_INVALIDARG);
   TRY_TEST(divide->HorzCurve(150,1,-1,5),COGO_E_HORZCURVENOTFOUND);
   TRY_TEST(divide->HorzCurve(99,1,1,5),COGO_E_POINTALREADYDEFINED);

   TRY_TEST(divide->HorzCurve(150,1,1,10),S_OK);
   
   pnt.Release();
   TRY_TEST(points->get_Item(150,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,493.3008,0.001),true);
   TRY_TEST(IsEqual(y,999.4672,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(151,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,547.4251,0.001),true);
   TRY_TEST(IsEqual(y,995.7440,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(152,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,600.8740,0.001),true);
   TRY_TEST(IsEqual(y,986.4948,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(153,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,653.0065,0.001),true);
   TRY_TEST(IsEqual(y,971.5102,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(154,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,703.2089,0.001),true);
   TRY_TEST(IsEqual(y,950.9663,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(155,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,750.8904,0.001),true);
   TRY_TEST(IsEqual(y,925.1051,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(156,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,795.5411,0.001),true);
   TRY_TEST(IsEqual(y,894.2997,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(157,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,837.3133,0.001),true);
   TRY_TEST(IsEqual(y,859.6735,0.001),true);
   
   pnt.Release();
   TRY_TEST(points->get_Item(158,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,876.9803,0.001),true);
   TRY_TEST(IsEqual(y,822.6429,0.001),true);
}