///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

   model->StorePoint(1,0,0);
   model->StorePoint(2,5,5);
   model->StorePoint(3,6,12);
   model->StorePoint(4,12,6);

   CComPtr<IPoint2d> p1, p2;
   model->GetPointByID(1,&p1);
   model->GetPointByID(2,&p2);

   CComPtr<IPoint2d> pnt;
   Float64 x,y;

   /////////////////////////////////////
   // PointOnLineByPoints
   TRY_TEST(project->PointOnLineByPoints(5,-3,1,2,0.0), E_INVALIDARG);
   TRY_TEST(project->PointOnLineByPoints(5,3,-1,2,0.0), E_INVALIDARG);
   TRY_TEST(project->PointOnLineByPoints(5,3,1,-2,0.0), E_INVALIDARG);
   TRY_TEST(project->PointOnLineByPoints(1,3,1,2,0.0), S_FALSE);

   TRY_TEST(project->PointOnLineByPoints(5,3,1,2,0.0),S_OK);
   pnt.Release();
   TRY_TEST(model->GetPointByID(5,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,9.0),true);
   TRY_TEST(IsEqual(y,9.0),true);

   TRY_TEST(project->PointOnLineByPoints(6,4,1,2,0.0),S_OK);
   pnt.Release();
   TRY_TEST(model->GetPointByID(6,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,9.0),true);
   TRY_TEST(IsEqual(y,9.0),true);

   TRY_TEST(project->PointOnLineByPoints(7,3,1,2,4.24264068712),S_OK);
   pnt.Release();
   TRY_TEST(model->GetPointByID(7,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,12.0),true);
   TRY_TEST(IsEqual(y,6.0),true);

   TRY_TEST(project->PointOnLineByPoints(8,4,1,2,-4.24264068712),S_OK);
   pnt.Release();
   TRY_TEST(model->GetPointByID(8,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,6.0),true);
   TRY_TEST(IsEqual(y,12.0),true);

   ////////////////////////////////////////
   // PointOnLineSegment
   model->StorePathSegment(1,1,2);

   TRY_TEST(project->PointOnLineSegment(9,-3,1,0.0), E_INVALIDARG);
   TRY_TEST(project->PointOnLineSegment(9,3,-1,0.0), E_INVALIDARG);
   TRY_TEST(project->PointOnLineSegment(1,3,1,0.0), S_FALSE);

   TRY_TEST(project->PointOnLineSegment(9,3,1,0.0),S_OK);
   pnt.Release();
   TRY_TEST(model->GetPointByID(9,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,9.0),true);
   TRY_TEST(IsEqual(y,9.0),true);

   /////////////////////////////
   // PointOnCurve
   model->ClearPoints();
   model->StorePoint(1, 0, 1000);
   model->StorePoint(2, 700, 1000);
   model->StorePoint(3, 1000, 700);
   model->StoreCompoundCurve(1, 1, 2, 3, 500, 100, TransitionCurveType::Clothoid, 200, TransitionCurveType::Clothoid);

   TRY_TEST(project->PointOnCurve(1,2,1),S_FALSE);
   TRY_TEST(project->PointOnCurve(5,-1,1), E_INVALIDARG);
   TRY_TEST(project->PointOnCurve(5,2,-1), E_INVALIDARG);
   TRY_TEST(project->PointOnCurve(5,2,1),S_OK);
   pnt.Release();
   TRY_TEST(model->GetPointByID(5,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,683.1287,0.001),true);
   TRY_TEST(IsEqual(y,959.9504,0.001),true);
}