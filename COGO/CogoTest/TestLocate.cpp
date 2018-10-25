///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestLocate.cpp: implementation of the CTestLocate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestLocate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLocate::CTestLocate()
{

}

CTestLocate::~CTestLocate()
{

}

void CTestLocate::Test()
{
   CComPtr<ILocate> locate;
   TRY_TEST(locate.CoCreateInstance(CLSID_CogoModel),S_OK);

   CComQIPtr<ICogoModel> model(locate);
   TRY_TEST( model != NULL, true );

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   CComPtr<IPoint2d> pnt;
   Float64 x,y;

   points->Add(1,0.0,0.0,NULL);
   points->Add(2,10.0,0.0,NULL);

   // Locate ByDistDir
   TRY_TEST(locate->ByDistDir(1,2,10.0,CComVariant(PI_OVER_2),0.00),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(locate->ByDistDir(3,-1,10.0,CComVariant(PI_OVER_2),0.00),COGO_E_POINTNOTFOUND);
   TRY_TEST(locate->ByDistDir(3,2,10.0,CComVariant(points),0.00),E_INVALIDARG);
   CComPtr<IUnknown> unk(points);
   TRY_TEST(locate->ByDistDir(3,2,10.0,CComVariant(unk),0.00),E_INVALIDARG);

   TRY_TEST(locate->ByDistDir(3,2,10.0,CComVariant(PI_OVER_2),0.00),S_OK);
   points->get_Item(3,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,10.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   pnt.Release();
   TRY_TEST(locate->ByDistDir(4,2,10.0,CComVariant(PI_OVER_2),5.00),S_OK);
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,15.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   pnt.Release();
   TRY_TEST(locate->ByDistDir(5,2,10.0,CComVariant(PI_OVER_2),-5.00),S_OK);
   points->get_Item(5,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 5.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   CComPtr<IDirection> dir;
   dir.CoCreateInstance(CLSID_Direction);
   dir->FromDMS(nsNorth,45,0,0.0,ewWest);
   CComPtr<IUnknown> unkDir(dir);
   pnt.Release();
   TRY_TEST(locate->ByDistDir(6,2,10.0,CComVariant(unkDir),0.00),S_OK);
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,2.92893218813),true);
   TRY_TEST(IsEqual(y,7.07106781187),true);

   pnt.Release();
   TRY_TEST(locate->ByDistDir(7,2,10.0,CComVariant(dir),5.00),S_OK);
   points->get_Item(7,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,6.46446609407),true);
   TRY_TEST(IsEqual(y,10.6066017178),true);

   pnt.Release();
   TRY_TEST(locate->ByDistDir(8,2,10.0,CComVariant(dir),-5.00),S_OK);
   points->get_Item(8,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-0.60660171781),true);
   TRY_TEST(IsEqual(y,3.53553390593),true);

   pnt.Release();
   TRY_TEST(locate->ByDistDir(9,2,-10.0,CComVariant(dir),0.00),S_OK);
   points->get_Item(9,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,17.07106781187),true);
   TRY_TEST(IsEqual(y,-7.07106781187),true);

   // Locate ByDistAngle
   points->Clear();
   points->Add(1,10,10,NULL);
   points->Add(2,0,0,NULL);

   TRY_TEST(locate->ByDistAngle(1,1,2,10.0,CComVariant(M_PI),0.0),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(locate->ByDistAngle(3,-1,2,10.0,CComVariant(M_PI),0.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(locate->ByDistAngle(3,1,-2,10.0,CComVariant(M_PI),0.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(locate->ByDistAngle(3,1,2,10.0,CComVariant(points),0.0),E_INVALIDARG);
   TRY_TEST(locate->ByDistAngle(3,1,2,10.0,CComVariant(unk),0.0),E_INVALIDARG);

   TRY_TEST(locate->ByDistAngle(3,1,2,10.0,CComVariant(M_PI),0.0),S_OK);
   pnt.Release();
   points->get_Item(3,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-7.07106781187),true);
   TRY_TEST(IsEqual(y,-7.07106781187),true);

   TRY_TEST(locate->ByDistAngle(4,1,2,10.0,CComVariant(M_PI/4),0.0),S_OK);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 0.0),true);
   TRY_TEST(IsEqual(y,10.0),true);

   CComPtr<IAngle> angle;
   angle.CoCreateInstance(CLSID_Angle);
   angle->FromDMS(225,0,0);
   TRY_TEST(locate->ByDistAngle(5,1,2,10.0,CComVariant(angle),-5.0),S_OK);
   pnt.Release();
   points->get_Item(5,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,  3.53553390594),true);
   TRY_TEST(IsEqual(y,-13.53553390594),true);

   TRY_TEST(locate->ByDistAngle(6,1,2,-10.0,CComVariant(angle),-5.0),S_OK);
   pnt.Release();
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,3.53553390594),true);
   TRY_TEST(IsEqual(y,6.46446609406),true);

   // Locate ByDistDefAngle
   points->Clear();
   points->Add(1,10,10,NULL);
   points->Add(2,0,0,NULL);

   TRY_TEST(locate->ByDistDefAngle(1,1,2,10.0,CComVariant(M_PI),0.0),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(locate->ByDistDefAngle(3,-1,2,10.0,CComVariant(M_PI),0.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(locate->ByDistDefAngle(3,1,-2,10.0,CComVariant(M_PI),0.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(locate->ByDistDefAngle(3,1,2,10.0,CComVariant(points),0.0),E_INVALIDARG);
   TRY_TEST(locate->ByDistDefAngle(3,1,2,10.0,CComVariant(unk),0.0),E_INVALIDARG);

   TRY_TEST(locate->ByDistDefAngle(3,1,2,10.0,CComVariant(M_PI),0.0),S_OK);
   pnt.Release();
   points->get_Item(3,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,7.07106781187),true);
   TRY_TEST(IsEqual(y,7.07106781187),true);

   TRY_TEST(locate->ByDistDefAngle(4,1,2,10.0,CComVariant(M_PI/4),0.0),S_OK);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,  0.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   CComPtr<IAngle> defAngle;
   defAngle.CoCreateInstance(CLSID_Angle);
   defAngle->FromDMS(45,0,0);
   TRY_TEST(locate->ByDistDefAngle(5,1,2,10.0,CComVariant(defAngle),-5.0),S_OK);
   pnt.Release();
   points->get_Item(5,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,  3.53553390594),true);
   TRY_TEST(IsEqual(y,-13.53553390594),true);

   TRY_TEST(locate->ByDistDefAngle(6,1,2,-10.0,CComVariant(defAngle),-5.0),S_OK);
   pnt.Release();
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,3.53553390594),true);
   TRY_TEST(IsEqual(y,6.46446609406),true);

   // Locate PointOnLine
   points->Clear();
   points->Add(1,10,10,NULL);
   points->Add(2,20,20,NULL);

   TRY_TEST(locate->PointOnLine(3,1,2,20.0,0.0),S_OK);
   pnt.Release();
   points->get_Item(3,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,24.1421356237),true);
   TRY_TEST(IsEqual(y,24.1421356237),true);

   TRY_TEST(locate->PointOnLine(4,1,2,-20.0,0.0),S_OK);
   pnt.Release();
   points->get_Item(4,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-4.1421356237),true);
   TRY_TEST(IsEqual(y,-4.1421356237),true);

   TRY_TEST(locate->PointOnLine(5,1,2,10.0,5.0),S_OK);
   pnt.Release();
   points->get_Item(5,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,20.6066017178),true);
   TRY_TEST(IsEqual(y,13.5355339059),true);

   TRY_TEST(locate->PointOnLine(6,1,2,10.0,-5.0),S_OK);
   pnt.Release();
   points->get_Item(6,&pnt);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,13.5355339059),true);
   TRY_TEST(IsEqual(y,20.6066017178),true);

   // Test ParallelLineSegment and ParallelLineByPoints
   //
   points->Clear();
   points->Add(1,0,0,NULL);
   points->Add(2,20,20,NULL);
   CComPtr<IPoint2d> p1, p2;
   points->get_Item(1,&p1);
   points->get_Item(2,&p2);

   CComPtr<ILineSegment2d> line;
   CComPtr<ILineSegmentCollection> lines;
   model->get_LineSegments(&lines);

   lines->Clear();
   lines->Add(1,p1,p2,NULL);

   TRY_TEST(locate->ParallelLineSegment(1,3,4,1,5.0),COGO_E_LINESEGMENTALREADYDEFINED);
   TRY_TEST(locate->ParallelLineSegment(2,1,4,1,5.0),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(locate->ParallelLineSegment(2,3,1,1,5.0),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(locate->ParallelLineSegment(2,3,4,-1,5.0),COGO_E_LINESEGMENTNOTFOUND);
   TRY_TEST(locate->ParallelLineByPoints(3,4,-1,2,5.0),COGO_E_POINTNOTFOUND);
   TRY_TEST(locate->ParallelLineByPoints(3,4,1,-2,5.0),COGO_E_POINTNOTFOUND);

   TRY_TEST(locate->ParallelLineSegment(2,3,4,1,5.0),S_OK);
   line.Release();
   TRY_TEST(lines->get_Item(2,&line),S_OK);

   CogoElementKey startID, endID;
   CComPtr<IPoint2d> start, end;
   line->get_StartPoint(&start);
   line->get_EndPoint(&end);
   CComQIPtr<IPoint2d> startEx(start);
   CComQIPtr<IPoint2d> endEx(end);
   TRY_TEST( points->FindKey(startEx,&startID), S_OK );
   TRY_TEST( points->FindKey(endEx,&endID), S_OK );
   TRY_TEST(startID,3);
   TRY_TEST(endID,4);

   pnt.Release();
   TRY_TEST(points->get_Item(startID,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.53553390594),true);
   TRY_TEST(IsEqual(y,-3.53553390594),true);
   pnt.Release();
   TRY_TEST(points->get_Item(endID,&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,23.5355339059),true);
   TRY_TEST(IsEqual(y,16.4644660941),true);

   TRY_TEST(locate->ParallelLineSegment(3,5,6,1,-5.0),S_OK);
   line.Release();
   TRY_TEST(lines->get_Item(3,&line),S_OK);
   start.Release();
   end.Release();
   line->get_StartPoint(&start);
   line->get_EndPoint(&end);
   startEx.Release();
   start.QueryInterface(&startEx);
   endEx.Release();
   end.QueryInterface(&endEx);
   TRY_TEST( points->FindKey(startEx,&startID), S_OK );
   TRY_TEST( points->FindKey(endEx,&endID), S_OK );
   TRY_TEST(startID,5);
   TRY_TEST(endID,6);
   pnt.Release();
   TRY_TEST(points->get_Item(startID,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-3.53553390594),true);
   TRY_TEST(IsEqual(y, 3.53553390594),true);
   pnt.Release();
   TRY_TEST(points->get_Item(endID,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,16.4644660941),true);
   TRY_TEST(IsEqual(y,23.5355339059),true);

   TRY_TEST(locate->ParallelLineByPoints(3,4,1,2,5.0),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(locate->ParallelLineByPoints(13,4,1,2,5.0),COGO_E_POINTALREADYDEFINED);
   TRY_TEST(locate->ParallelLineByPoints(13,14,1,2,5.0),S_OK);
   pnt.Release();
   TRY_TEST(points->get_Item(13,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 3.53553390594),true);
   TRY_TEST(IsEqual(y,-3.53553390594),true);
   pnt.Release();
   TRY_TEST(points->get_Item(14,&pnt),S_OK);
   TRY_TEST(CheckPointType(pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,23.5355339059),true);
   TRY_TEST(IsEqual(y,16.4644660940),true);
}