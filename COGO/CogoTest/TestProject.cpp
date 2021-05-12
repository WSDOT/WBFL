///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

// TestProject.cpp: implementation of the CTestProject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestProject::CTestProject()
{

}

CTestProject::~CTestProject()
{

}

void CTestProject::Test()
{
   CComPtr<IProject> project;
   TRY_TEST(project.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(project);
   TRY_TEST( model != nullptr, true );

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->Add(1,0,0,nullptr);
   points->Add(2,5,5,nullptr);
   points->Add(3,6,12,nullptr);
   points->Add(4,12,6,nullptr);
   CComPtr<IPoint2d> p1, p2;
   points->get_Item(1,&p1);
   points->get_Item(2,&p2);

   CComPtr<IPoint2d> pnt;
   Float64 x,y;

   /////////////////////////////////////
   // PointOnLineByPoints
   TRY_TEST(project->PointOnLineByPoints(5,-3,1,2,0.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(project->PointOnLineByPoints(5,3,-1,2,0.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(project->PointOnLineByPoints(5,3,1,-2,0.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(project->PointOnLineByPoints(1,3,1,2,0.0),COGO_E_POINTALREADYDEFINED);

   TRY_TEST(project->PointOnLineByPoints(5,3,1,2,0.0),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(5,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,9.0),true);
   TRY_TEST(IsEqual(y,9.0),true);

   TRY_TEST(project->PointOnLineByPoints(6,4,1,2,0.0),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(6,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,9.0),true);
   TRY_TEST(IsEqual(y,9.0),true);

   TRY_TEST(project->PointOnLineByPoints(7,3,1,2,4.24264068712),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(7,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,12.0),true);
   TRY_TEST(IsEqual(y,6.0),true);

   TRY_TEST(project->PointOnLineByPoints(8,4,1,2,-4.24264068712),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(8,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,6.0),true);
   TRY_TEST(IsEqual(y,12.0),true);

   ////////////////////////////////////////
   // PointOnLineSegment
   CComPtr<ILineSegmentCollection> lines;
   model->get_LineSegments(&lines);
   lines->Add(1,p1,p2,nullptr);

   TRY_TEST(project->PointOnLineSegment(9,-3,1,0.0), COGO_E_POINTNOTFOUND);
   TRY_TEST(project->PointOnLineSegment(9,3,-1,0.0), COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(project->PointOnLineSegment(1,3,1,0.0),  COGO_E_POINTALREADYDEFINED);

   TRY_TEST(project->PointOnLineSegment(9,3,1,0.0),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(9,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,9.0),true);
   TRY_TEST(IsEqual(y,9.0),true);

   /////////////////////////////
   // PointOnCurve
   CComPtr<IHorzCurveCollection> hcurves;
   model->get_HorzCurves(&hcurves);
   CComPtr<IHorzCurve> hc;
   hc.CoCreateInstance(CLSID_HorzCurve);
   CComPtr<IPoint2d> pbt, pi, pft;
   hc->get_PBT(&pbt);
   hc->get_PI(&pi);
   hc->get_PFT(&pft);

   pbt->Move(0,1000);
   pi->Move(700,1000);
   pft->Move(1000,700);
   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,100);
   hc->put_SpiralLength(spExit,200);

   hcurves->AddEx(1,hc);

   points->Clear();
   points->AddEx(1,pbt);
   points->AddEx(2,pi);
   points->AddEx(3,pft);

   TRY_TEST(project->PointOnCurve(1,2,1),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(project->PointOnCurve(5,-1,1),COGO_E_POINTNOTFOUND);
   TRY_TEST(project->PointOnCurve(5,2,-1),COGO_E_HORZCURVENOTFOUND);
   TRY_TEST(project->PointOnCurve(5,2,1),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(5,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,683.1287,0.001),true);
   TRY_TEST(IsEqual(y,959.9504,0.001),true);
}