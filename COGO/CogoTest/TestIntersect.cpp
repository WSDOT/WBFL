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

// TestIntersect.cpp: implementation of the CTestIntersect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestIntersect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestIntersect::CTestIntersect()
{

}

CTestIntersect::~CTestIntersect()
{

}

void CTestIntersect::Test()
{
   CComPtr<IIntersect> intersect;
   TRY_TEST(intersect.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(intersect);
   TRY_TEST( model != nullptr, true );

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   VARIANT_BOOL bFound;

   // Test Bearings
   points->Clear();
   points->Add(1,0,0,nullptr);
   points->Add(2,10,0,nullptr);

   TRY_TEST(intersect->Bearings(3,1,CComVariant(M_PI/4),0.0,2,CComVariant(3*M_PI/4),0.0,nullptr), E_POINTER);
   TRY_TEST(intersect->Bearings(3,1,CComVariant(points),0.0,2,CComVariant(3*M_PI/4),0.0,&bFound), E_INVALIDARG);
   TRY_TEST(intersect->Bearings(3,1,CComVariant(M_PI/4),0.0,2,CComVariant(points),0.0,&bFound), E_INVALIDARG);
   TRY_TEST(intersect->Bearings(3,-1,CComVariant(M_PI/4),0.0,2,CComVariant(3*M_PI/4),0.0,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->Bearings(3,1,CComVariant(M_PI/4),0.0,-2,CComVariant(3*M_PI/4),0.0,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->Bearings(1,1,CComVariant(M_PI/4),0.0,2,CComVariant(3*M_PI/4),0.0,&bFound), COGO_E_POINTALREADYDEFINED);

   TRY_TEST(intersect->Bearings(3,1,CComVariant(M_PI/4),0.0,2,CComVariant(3*M_PI/4),0.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(3,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,5.0),true);
   TRY_TEST(IsEqual(y,5.0),true);
   
   TRY_TEST(intersect->Bearings(4,1,CComVariant(M_PI/4),5.0,2,CComVariant(3*M_PI/4),5.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,12.0710678119),true);
   TRY_TEST(IsEqual(y,5.0),true);

   TRY_TEST(intersect->Bearings(5,1,CComVariant(M_PI/4),0.0,2,CComVariant(M_PI/4),0.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_FALSE);
   pnt.Release();
   TRY_TEST(points->get_Item(5,&pnt),COGO_E_POINTNOTFOUND);
   TRY_TEST(pnt == nullptr, true );

   // Test BearingCircle
   points->Clear();
   points->Add(1,0,0,nullptr);
   points->Add(2,10,10,nullptr);
   points->Add(3,15,15,nullptr);

   TRY_TEST(intersect->BearingCircle(4,1,CComVariant(M_PI/4),0.0,2,5.0,3,nullptr),     E_POINTER);
   TRY_TEST(intersect->BearingCircle(4,-1,CComVariant(M_PI/4),0.0,2,5.0,3,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->BearingCircle(1,1,CComVariant(M_PI/4),0.0,2,5.0,3,&bFound),  COGO_E_POINTALREADYDEFINED);
   TRY_TEST(intersect->BearingCircle(4,1,CComVariant(M_PI/4),0.0,-2,5.0,3,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->BearingCircle(4,1,CComVariant(M_PI/4),0.0,2,5.0,-3,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->BearingCircle(4,1,CComVariant(M_PI/4),0.0,2,-5.0,3,&bFound), COGO_E_RADIUS);

   TRY_TEST(intersect->BearingCircle(4,1,CComVariant(M_PI/4),0.0,2,5.0,3,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,13.5355339059),true);
   TRY_TEST(IsEqual(y,13.5355339059),true);

   TRY_TEST(intersect->BearingCircle(5,1,CComVariant(M_PI/4),0.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(5,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,6.46446609406),true);
   TRY_TEST(IsEqual(y,6.46446609406),true);

   TRY_TEST(intersect->BearingCircle(6,1,CComVariant(PI_OVER_2),5.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,5.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   TRY_TEST(intersect->BearingCircle(7,1,CComVariant(PI_OVER_2),0.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_FALSE);

   // Test Circles
   points->Clear();
   points->Add(1,0,0,nullptr);
   points->Add(2,10,10,nullptr);
   points->Add(3,20,20,nullptr);
   points->Add(4,20,0,nullptr);
   points->Add(5,0,20,nullptr);

   TRY_TEST(intersect->Circles(6,2,10.0,3,10.0,4,nullptr),E_POINTER);
   TRY_TEST(intersect->Circles(6,-2,10.0,3,10.0,4,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->Circles(6,2,-10.0,3,10.0,4,&bFound),COGO_E_RADIUS);
   TRY_TEST(intersect->Circles(6,2,10.0,-3,10.0,4,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->Circles(6,2,10.0,3,-10.0,4,&bFound),COGO_E_RADIUS);
   TRY_TEST(intersect->Circles(6,2,10.0,3,10.0,-4,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->Circles(2,2,10.0,3,10.0,4,&bFound),COGO_E_POINTALREADYDEFINED);

   TRY_TEST(intersect->Circles(6,2,10.0,3,10.0,4,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   TRY_TEST(intersect->Circles(7,2,20.0,6,10.0,4,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(7,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,30.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   TRY_TEST(intersect->Circles(8,2,20.0,6,20.0,5,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(8,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,15.0),true);
   TRY_TEST(IsEqual(y,29.3649167),true);

   TRY_TEST(intersect->Circles(8,2,2.0,3,2.0,4,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_FALSE);

   // Test LineByPointsCircle
   points->Clear();
   points->Add(1,0,0,nullptr);
   points->Add(2,10,10,nullptr);
   points->Add(3,15,15,nullptr);
   points->Add(10,0,20,nullptr);

   TRY_TEST(intersect->LineByPointsCircle(4,1,3,0.0,2,5.0,3,nullptr),E_POINTER);
   TRY_TEST(intersect->LineByPointsCircle(4,-1,3,0.0,2,5.0,3,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LineByPointsCircle(4,1,-3,0.0,2,5.0,3,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LineByPointsCircle(1,1,3,0.0,2,5.0,3,&bFound),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(intersect->LineByPointsCircle(4,1,3,0.0,-2,5.0,3,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LineByPointsCircle(4,1,3,0.0,2,5.0,-3,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LineByPointsCircle(4,1,3,0.0,2,-5.0,3,&bFound),COGO_E_RADIUS);

   TRY_TEST(intersect->LineByPointsCircle(4,1,3,0.0,2,5.0,3,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,13.5355339059),true);
   TRY_TEST(IsEqual(y,13.5355339059),true);

   TRY_TEST(intersect->LineByPointsCircle(5,1,3,0.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(5,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,6.46446609406),true);
   TRY_TEST(IsEqual(y,6.46446609406),true);

   TRY_TEST(intersect->LineByPointsCircle(6,1,10,5.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,5.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   TRY_TEST(intersect->LineByPointsCircle(7,1,10,0.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_FALSE);

   // Test LinesByPoints
   points->Clear();
   points->Add(1,0,0,nullptr);
   points->Add(2,10,0,nullptr);
   points->Add(30,10,10,nullptr);
   points->Add(40,0,10,nullptr);

   TRY_TEST(intersect->LinesByPoints(3,1,30,0.0,2,40,0.0,nullptr), E_POINTER);
   TRY_TEST(intersect->LinesByPoints(3,1,-30,0.0,2,40,0.0,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LinesByPoints(3,1,30,0.0,2,-40,0.0,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LinesByPoints(3,-1,30,0.0,2,40,0.0,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LinesByPoints(3,1,30,0.0,-2,40,0.0,&bFound), COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LinesByPoints(1,1,30,0.0,2,40,0.0,&bFound), COGO_E_POINTALREADYDEFINED);

   TRY_TEST(intersect->LinesByPoints(3,1,30,0.0,2,40,0.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(3,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,5.0),true);
   TRY_TEST(IsEqual(y,5.0),true);
   
   TRY_TEST(intersect->LinesByPoints(4,1,30,5.0,2,40,5.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,12.0710678119),true);
   TRY_TEST(IsEqual(y,5.0),true);

   TRY_TEST(intersect->LinesByPoints(5,1,2,0.0,30,40,0.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_FALSE);
   pnt.Release();
   TRY_TEST(points->get_Item(5,&pnt),COGO_E_POINTNOTFOUND);
   TRY_TEST(pnt == nullptr, true );

   // Test LineSegments
   points->Clear();
   points->Add(1,0,0,nullptr);
   points->Add(2,10,0,nullptr);
   points->Add(30,10,10,nullptr);
   points->Add(40,0,10,nullptr);
   CComPtr<IPoint2d> p1, p2, p30, p40;
   points->get_Item(1,&p1);
   points->get_Item(2,&p2);
   points->get_Item(30,&p30);
   points->get_Item(40,&p40);

   CComPtr<ILineSegmentCollection> lines;
   model->get_LineSegments(&lines);
   lines->Add(1,p1,p30,nullptr);
   lines->Add(2,p2,p40,nullptr);

   TRY_TEST(intersect->Lines(3,1,0.0,2,0.0,nullptr), E_POINTER);
   TRY_TEST(intersect->Lines(3,-1,0.0,2,0.0,&bFound), COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(intersect->Lines(3,1,0.0,-2,0.0,&bFound), COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(intersect->Lines(1,1,0.0,2,0.0,&bFound), COGO_E_POINTALREADYDEFINED);

   TRY_TEST(intersect->Lines(3,1,0.0,2,0.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(3,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,5.0),true);
   TRY_TEST(IsEqual(y,5.0),true);
   
   TRY_TEST(intersect->Lines(4,1,5.0,2,5.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,12.0710678119),true);
   TRY_TEST(IsEqual(y,5.0),true);

   // parallel lines
   p1->Move(0,0);
   p2->Move(10,0);
   p30->Move(0,10);
   p40->Move(10,10);
   TRY_TEST(intersect->Lines(5,1,0.0,2,0.0,&bFound), S_OK);
   TRY_TEST(bFound,VARIANT_FALSE);

   //
   // LineSegmentCircle
   //
   points->Clear();
   points->Add(1,0,0,nullptr);
   points->Add(2,10,10,nullptr);
   points->Add(3,15,15,nullptr);
   points->Add(10,0,20,nullptr);
   p1.Release();
   p2.Release();
   CComPtr<IPoint2d> p3, p10;
   points->get_Item(1,&p1);
   points->get_Item(2,&p2);
   points->get_Item(3,&p3);
   points->get_Item(10,&p10);

   lines->Clear();
   lines->Add(1,p1,p3,nullptr);
   lines->Add(2,p1,p10,nullptr);

   TRY_TEST(intersect->LineSegmentCircle(4,1,0.0,2,5.0,3,nullptr),E_POINTER);
   TRY_TEST(intersect->LineSegmentCircle(4,-1,0.0,2,5.0,3,&bFound),COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(intersect->LineSegmentCircle(1,1,0.0,2,5.0,3,&bFound),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(intersect->LineSegmentCircle(4,1,0.0,-2,5.0,3,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LineSegmentCircle(4,1,0.0,2,5.0,-3,&bFound),COGO_E_POINTNOTFOUND);
   TRY_TEST(intersect->LineSegmentCircle(4,1,0.0,2,-5.0,3,&bFound),COGO_E_RADIUS);

   TRY_TEST(intersect->LineSegmentCircle(4,1,0.0,2,5.0,3,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,13.5355339059),true);
   TRY_TEST(IsEqual(y,13.5355339059),true);

   TRY_TEST(intersect->LineSegmentCircle(5,1,0.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(5,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,6.46446609406),true);
   TRY_TEST(IsEqual(y,6.46446609406),true);

   TRY_TEST(intersect->LineSegmentCircle(6,2,5.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_TRUE);
   pnt.Release();
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,5.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   TRY_TEST(intersect->LineSegmentCircle(7,2,0.0,2,5.0,1,&bFound),S_OK);
   TRY_TEST(bFound,VARIANT_FALSE);
}
