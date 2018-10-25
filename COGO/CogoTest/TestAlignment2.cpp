///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestAlignment2.cpp: implementation of the CTestAlignment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlignment2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAlignment2::CTestAlignment2()
{

}

void CTestAlignment2::Test()
{
   Test1();
   Test2();
   Test3();
   Test4();
   Test5();
}

void CTestAlignment2::Test1()
{
   // Test an empty alignment object
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-100.0),true);
   TRY_TEST(IsEqual(y, -10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   // Sta 2+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(2.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(2.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(200),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0),true);
   TRY_TEST(IsEqual(y, -10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,200.00),true);
}

void CTestAlignment2::Test2()
{
   // Test an alignment that consists of a single point
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(50,50);
   alignment->AddEx(p1);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-50.0),true);
   TRY_TEST(IsEqual(y, 40.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   // Sta 2+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(200.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(200.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(200),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,150.0),true);
   TRY_TEST(IsEqual(y, 40.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,200.00),true);
}

void CTestAlignment2::Test3()
{
   // Alignment consisting of a single line segment
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(50,50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250,250);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4 + 3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-13.6396,0.001),true);
   TRY_TEST(IsEqual(y,-27.7817,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   // Sta 1+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(150.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(150.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4 + 3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(150),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 92.4264,0.001),true);
   TRY_TEST(IsEqual(y, 78.2843,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,150.00),true);

   // Sta 5+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(500.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(500.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4 + 3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(500),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 339.91378),true);
   TRY_TEST(IsEqual(y, 325.77164),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,500.00),true);
}

void CTestAlignment2::Test4()
{
   // Alignment consisting of a single curve
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(0,1000);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(700,1000);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(1000,700);

   CComPtr<IHorzCurve> hc;
   hc.CoCreateInstance(CLSID_HorzCurve);
   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);
   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,100);
   hc->put_SpiralLength(spExit,200);
   alignment->AddEx(hc);

   //////////////
   // Bearing,Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 339.0356,0.001),true);
   TRY_TEST(IsEqual(y, 990.0000,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   // Sta 1+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(150.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,6.2581853),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(150.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,6.2581853 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(150),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,488.7825,0.001),true);
   TRY_TEST(IsEqual(y,989.5865,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,150.00),true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,6.083185),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,6.083185 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,586.3669,0.001),true);
   TRY_TEST(IsEqual(y,979.3996,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   // Sta 4+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(450.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.68345),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(450.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.68345 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(450),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,765.6963,0.001),true);
   TRY_TEST(IsEqual(y,903.5804,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,450.00),true);

   // Sta 6+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(650.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.497787),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(650.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.497787 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(650),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,913.6339,0.001),true);
   TRY_TEST(IsEqual(y,772.2239,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,650.00),true);
}

void CTestAlignment2::Test5()
{
   // Alignment consisting of a two line segments
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1, p2, p3, p4;
   p1.CoCreateInstance(CLSID_Point2d);
   p2.CoCreateInstance(CLSID_Point2d);
   p3.CoCreateInstance(CLSID_Point2d);
   p4.CoCreateInstance(CLSID_Point2d);

   p1->Move(0,0);
   p2->Move(10,0);
   p3->Move(10,10);
   p4->Move(20,10);

   CComPtr<ILineSegment2d> ls1, ls2;
   ls1.CoCreateInstance(CLSID_LineSegment2d);
   ls2.CoCreateInstance(CLSID_LineSegment2d);

   ls1->putref_StartPoint(p1);
   ls1->putref_EndPoint(p2);
   ls2->putref_StartPoint(p3);
   ls2->putref_EndPoint(p4);

   alignment->AddEx(ls1);
   alignment->AddEx(ls2);

   //////////////
   // Bearing,Normal,LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   // Sta 1+15
   TRY_TEST(alignment->Bearing(CComVariant(115.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,PI_OVER_2),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(115.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.0),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(115),omtAlongDirection, 3,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 13.0),true);
   TRY_TEST(IsEqual(y,  5.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,3.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,115.00),true);
}
