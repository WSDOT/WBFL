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

// TestAlignment1.cpp: implementation of the CTestAlignment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlignment1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAlignment1::CTestAlignment1()
{

}

void CTestAlignment1::Test()
{
   Test1();
   Test1a();
   Test2();
   Test2a();
   Test3();
   Test3a();
   Test4();
   Test4a();
}

void CTestAlignment1::Test1()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100,0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150,50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250,0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(500,100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   alignment->AddEx(hc);

   alignment->AddEx(pft);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 offset;
   Float64 stationVal;

   TRY_TEST(alignment->Bearing(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125),omtAlongDirection, 10,CComVariant(PI_OVER_2),nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,&station,nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,nullptr,&offset),E_POINTER);
   TRY_TEST(alignment->Offset(nullptr,&station,&offset),E_INVALIDARG);
   TRY_TEST(alignment->ProjectPoint(end,nullptr,nullptr,nullptr),E_POINTER);
   start.Release();
   TRY_TEST(alignment->ProjectPoint(nullptr,&start,nullptr,nullptr),E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-100.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);
   TRY_TEST(IsEqual(offset,10.0),true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt,&distFromStart,&vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);


   // Sta 1+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(100.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(100.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(100.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,  0.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,100.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,100.00),true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,25.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   // Sta 2+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(200.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(200.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4 + 3 * PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(200.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,107.0710678),true);
   TRY_TEST(IsEqual(y,-7.0710678),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,200.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,200.00),true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,142.4264,0.001),true);
   TRY_TEST(IsEqual(y, 28.2843,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.8195,0.001),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.8195 - PI_OVER_2,0.001),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,171.7250,0.001),true);
   TRY_TEST(IsEqual(y, 27.9571,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.0084083531428916),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.008408353 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,357.5699,0.001),true);
   TRY_TEST(IsEqual(y, -9.9882,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.39101),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.39101 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,400.3079,0.001),true);
   TRY_TEST(IsEqual(y, -1.65612,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.73327),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.73327 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,432.5904,0.001),true);
   TRY_TEST(IsEqual(y, 18.8222,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,457.8918,0.001),true);
   TRY_TEST(IsEqual(y, 43.7496,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);

   // Sta 7+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(700.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(700.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(700.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,528.6024,0.001),true);
   TRY_TEST(IsEqual(y,114.4603,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,700.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,700.00),true);


   // Add a station equation
   CComPtr<IStationEquationCollection> equations;
   alignment->get_StationEquations(&equations);
   CComPtr<IStationEquation> equation;
   equations->Add(650,800,&equation);

   CComPtr<IStation> objStation;
   equations->ConvertFromNormalizedStation(700,&objStation);

   ZoneIndexType idx;
   objStation->GetStation(&idx,&stationVal);
   TRY_TEST(idx,1);
   TRY_TEST(IsEqual(stationVal,850.0),true);

   // Sta 8+50 (station range 1)
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(objStation),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(objStation),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(objStation),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,528.6024,0.001),true);
   TRY_TEST(IsEqual(y,114.4603,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->GetStation(&idx,&stationVal);
   TRY_TEST(idx,1);
   TRY_TEST(IsEqual(stationVal,850.0),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->GetStation(&idx,&stationVal);
   TRY_TEST(idx,1);
   TRY_TEST(IsEqual(stationVal,850.0),true);
}

void CTestAlignment1::Test1a()
{
   // this test is the same as Test1 except we use a transition curve, circular curve, transition curve instead of a compound curve
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100, 0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150, 50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250, 0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(0.0);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(363.3826055,0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(421.682819278,22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(436.2818872224,36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(M_PI/4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(396.225283748,1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral,start_entry_spiral_direction,0.0,100.0,10, Clothoid);
   alignment->AddEx(entry_transition);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->putref_PBT(end_entry_spiral);
   curve->putref_PI(pi);
   curve->putref_PFT(start_exit_spiral);
   curve->put_Radius(100);
   alignment->AddEx(curve);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, start_exit_spiral_direction, 100.0, 0.0, 20, Clothoid);
   alignment->AddEx(exit_transition);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(500, 100);

   alignment->AddEx(pft);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x, y;
   CComPtr<IStation> station;
   Float64 offset;
   Float64 stationVal;

   TRY_TEST(alignment->Bearing(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125), omtAlongDirection, 10, CComVariant(PI_OVER_2), nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, &station, nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, nullptr, &offset), E_POINTER);
   TRY_TEST(alignment->Offset(nullptr, &station, &offset), E_INVALIDARG);
   TRY_TEST(alignment->ProjectPoint(end, nullptr, nullptr, nullptr), E_POINTER);
   start.Release();
   TRY_TEST(alignment->ProjectPoint(nullptr, &start, nullptr, nullptr), E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.00), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3 * PI_OVER_2), true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -100.0), true);
   TRY_TEST(IsEqual(y, -10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);
   TRY_TEST(IsEqual(offset, 10.0), true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);


   // Sta 1+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(100.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.00), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(100.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3 * PI_OVER_2), true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(100.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 0.0), true);
   TRY_TEST(IsEqual(y, -10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 100.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 100.00), true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.00), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 25.0), true);
   TRY_TEST(IsEqual(y, -10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   // Sta 2+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(200.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(200.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(200.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 107.0710678), true);
   TRY_TEST(IsEqual(y, -7.0710678), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 200.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 200.00), true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 142.4264, 0.001), true);
   TRY_TEST(IsEqual(y, 28.2843, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5.8195, 0.001), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5.8195 - PI_OVER_2, 0.001), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 171.7250, 0.001), true);
   TRY_TEST(IsEqual(y, 27.9571, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.0084083531428916), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.008408353 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 357.5699, 0.001), true);
   TRY_TEST(IsEqual(y, -9.9882, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.39101), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.39101 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 400.3079, 0.001), true);
   TRY_TEST(IsEqual(y, -1.65612, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.73327), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.73327 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 432.5904, 0.001), true);
   TRY_TEST(IsEqual(y, 18.8222, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 457.8918, 0.001), true);
   TRY_TEST(IsEqual(y, 43.7496, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);

   // Sta 7+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(700.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(700.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(700.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 528.6024, 0.001), true);
   TRY_TEST(IsEqual(y, 114.4603, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 700.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 700.00), true);


   // Add a station equation
   CComPtr<IStationEquationCollection> equations;
   alignment->get_StationEquations(&equations);
   CComPtr<IStationEquation> equation;
   equations->Add(650, 800, &equation);

   CComPtr<IStation> objStation;
   equations->ConvertFromNormalizedStation(700, &objStation);

   ZoneIndexType idx;
   objStation->GetStation(&idx, &stationVal);
   TRY_TEST(idx, 1);
   TRY_TEST(IsEqual(stationVal, 850.0), true);

   // Sta 8+50 (station range 1)
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(objStation), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(objStation), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(objStation), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 528.6024, 0.001), true);
   TRY_TEST(IsEqual(y, 114.4603, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->GetStation(&idx, &stationVal);
   TRY_TEST(idx, 1);
   TRY_TEST(IsEqual(stationVal, 850.0), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->GetStation(&idx, &stationVal);
   TRY_TEST(idx, 1);
   TRY_TEST(IsEqual(stationVal, 850.0), true);
}

void CTestAlignment1::Test2()
{
   // Mirror Test1 about X axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100,0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150,-50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250,0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(500,-100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   alignment->AddEx(hc);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   TRY_TEST(alignment->Bearing(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125),omtAlongDirection, 10,CComVariant(PI_OVER_2),nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,&station,nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,nullptr,&offset),E_POINTER);
   TRY_TEST(alignment->Offset(nullptr,&station,&offset),E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-100.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.00),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,25.0),true);
   TRY_TEST(IsEqual(y,-10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,7*M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,7*M_PI/4 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,128.2843,0.001),true);
   TRY_TEST(IsEqual(y,-42.4264,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.46365),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,0.46365 + 3*PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,180.6693,0.001),true);
   TRY_TEST(IsEqual(y,-45.8457,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,6.27477),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,6.27477 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,357.4018,0.001),true);
   TRY_TEST(IsEqual(y,-10.0111,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.89218),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.89218 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,392.6856,0.001),true);
   TRY_TEST(IsEqual(y,-16.8344,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.5499),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5.5499 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,419.2043,0.001),true);
   TRY_TEST(IsEqual(y,-33.6819,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,7*M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,7*M_PI/4 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,443.7496,0.001),true);
   TRY_TEST(IsEqual(y,-57.8918,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);
}

void CTestAlignment1::Test2a()
{
   // Mirror Test1a about X axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100, 0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150, -50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250, 0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(0.0);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(363.3826055, -0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(TWO_PI - 0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(421.682819278, -22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(TWO_PI - 0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(436.2818872224, -36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(TWO_PI - M_PI / 4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(396.225283748, -1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral, start_entry_spiral_direction, 0.0, -100.0, 10, Clothoid);
   alignment->AddEx(entry_transition);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->putref_PBT(end_entry_spiral);
   curve->putref_PI(pi);
   curve->putref_PFT(start_exit_spiral);
   curve->put_Radius(100);
   alignment->AddEx(curve);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, start_exit_spiral_direction, -100.0, 0.0, 20, Clothoid);
   alignment->AddEx(exit_transition);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(500, -100);

   alignment->AddEx(pft);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x, y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   TRY_TEST(alignment->Bearing(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125), omtAlongDirection, 10, CComVariant(PI_OVER_2), nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, &station, nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, nullptr, &offset), E_POINTER);
   TRY_TEST(alignment->Offset(nullptr, &station, &offset), E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.00), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3 * PI_OVER_2), true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -100.0), true);
   TRY_TEST(IsEqual(y, -10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.00), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 25.0), true);
   TRY_TEST(IsEqual(y, -10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 7 * M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 7 * M_PI / 4 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 128.2843, 0.001), true);
   TRY_TEST(IsEqual(y, -42.4264, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.46365), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 0.46365 + 3 * PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 180.6693, 0.001), true);
   TRY_TEST(IsEqual(y, -45.8457, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 6.27477), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 6.27477 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 357.4018, 0.001), true);
   TRY_TEST(IsEqual(y, -10.0111, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5.89218), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5.89218 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 392.6856, 0.001), true);
   TRY_TEST(IsEqual(y, -16.8344, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5.5499), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5.5499 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 419.2043, 0.001), true);
   TRY_TEST(IsEqual(y, -33.6819, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 7 * M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 7 * M_PI / 4 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 443.7496, 0.001), true);
   TRY_TEST(IsEqual(y, -57.8918, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);
}

void CTestAlignment1::Test3()
{
   // Mirror Test1 about Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100,0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150,50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250,0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(-300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(-500,100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   alignment->AddEx(hc);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   TRY_TEST(alignment->Bearing(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125),omtAlongDirection, 10,CComVariant(PI_OVER_2),nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,&station,nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,nullptr,&offset),E_POINTER);
   TRY_TEST(alignment->Offset(nullptr,&station,&offset),E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-25.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-128.2843,0.001),true);
   TRY_TEST(IsEqual(y,  42.4264,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.60524),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.60524 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-180.6693,0.001),true);
   TRY_TEST(IsEqual(y, 45.84569,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.133184),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.133184 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-357.4018,0.001),true);
   TRY_TEST(IsEqual(y,  10.0111,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,2.750584),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,2.750584 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-392.6856,0.001),true);
   TRY_TEST(IsEqual(y,  16.8344,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,2.408316),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,2.408316 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-419.2043,0.001),true);
   TRY_TEST(IsEqual(y,  33.6819,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3*M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI/4),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-443.7496,0.001),true);
   TRY_TEST(IsEqual(y,  57.8918,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);
}

void CTestAlignment1::Test3a()
{
   // Mirror Test1 about Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100, 0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150, 50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250, 0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(-353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(M_PI);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(-363.3826055, 0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(M_PI - 0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(-421.682819278, 22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(M_PI - 0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(-436.2818872224, 36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(M_PI - M_PI / 4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-396.225283748, 1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral, start_entry_spiral_direction, 0.0, -100.0, 10, Clothoid);
   alignment->AddEx(entry_transition);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->putref_PBT(end_entry_spiral);
   curve->putref_PI(pi);
   curve->putref_PFT(start_exit_spiral);
   curve->put_Radius(100);
   alignment->AddEx(curve);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, start_exit_spiral_direction, -100.0, 0.0, 20, Clothoid);
   alignment->AddEx(exit_transition);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(-500, 100);

   alignment->AddEx(pft);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x, y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   TRY_TEST(alignment->Bearing(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125), omtAlongDirection, 10, CComVariant(PI_OVER_2), nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, &station, nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, nullptr, &offset), E_POINTER);
   TRY_TEST(alignment->Offset(nullptr, &station, &offset), E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, PI_OVER_2), true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -25.0), true);
   TRY_TEST(IsEqual(y, 10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3 * M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -128.2843, 0.001), true);
   TRY_TEST(IsEqual(y, 42.4264, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.60524), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.60524 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -180.6693, 0.001), true);
   TRY_TEST(IsEqual(y, 45.84569, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.133184), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.133184 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -357.4018, 0.001), true);
   TRY_TEST(IsEqual(y, 10.0111, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 2.750584), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 2.750584 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -392.6856, 0.001), true);
   TRY_TEST(IsEqual(y, 16.8344, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 2.408316), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 2.408316 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -419.2043, 0.001), true);
   TRY_TEST(IsEqual(y, 33.6819, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3 * M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI / 4), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -443.7496, 0.001), true);
   TRY_TEST(IsEqual(y, 57.8918, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);
}

void CTestAlignment1::Test4()
{
   // Mirror Test1 about both X and Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100,0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150,-50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250,0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(-300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(-500,-100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   alignment->AddEx(hc);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   TRY_TEST(alignment->Bearing(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125),omtAlongDirection, 10,CComVariant(PI_OVER_2),nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,&station,nullptr),E_POINTER);
   TRY_TEST(alignment->Offset(end,nullptr,&offset),E_POINTER);
   TRY_TEST(alignment->Offset(nullptr,&station,&offset),E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI - PI_OVER_2),true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,0.00),true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,M_PI - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-25.0),true);
   TRY_TEST(IsEqual(y, 10.0),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,125.00),true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5*M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5*M_PI/4 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-142.4264,0.001),true);
   TRY_TEST(IsEqual(y, -28.2843,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,250.00),true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,2.677945),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,2.677945 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-171.7250,0.001),true);
   TRY_TEST(IsEqual(y, -27.9571,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,300.00),true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.1500010067327),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.1500010067327 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-357.5699,0.001),true);
   TRY_TEST(IsEqual(y,   9.9882,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,490.00),true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.5326,0.001),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.5326 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-400.3079,0.001),true);
   TRY_TEST(IsEqual(y,   1.65612,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,530.00),true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.87487),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,3.87487 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-432.5904,0.001),true);
   TRY_TEST(IsEqual(y, -18.8222,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,565.00),true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5*M_PI/4),true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00),&dir),S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal,5*M_PI/4 - PI_OVER_2),true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00),omtAlongDirection, 10,CComVariant(dirVal),&pnt),S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x,-457.8918,0.001),true);
   TRY_TEST(IsEqual(y, -43.7496,0.001),true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset, 10.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt,&newPnt, &distFromStart, &vbOnProjection),S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt,&station,&offset),S_OK);
   TRY_TEST(IsEqual(offset,0.0),true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal,600.00),true);
}

void CTestAlignment1::Test4a()
{
   // Mirror Test1 about both X and Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);
   alignment->AddEx(p1);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100, 0);
   alignment->AddEx(p2);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150, -50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250, 0);

   CComPtr<ILineSegment2d> ls;
   ls.CoCreateInstance(CLSID_LineSegment2d);
   ls->putref_StartPoint(start);
   ls->putref_EndPoint(end);
   alignment->AddEx(ls);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(-353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(M_PI);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(-363.3826055, -0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(M_PI + 0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(-421.682819278, -22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(M_PI + 0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(-436.2818872224, -36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(M_PI + M_PI / 4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-396.225283748, -1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral, start_entry_spiral_direction, 0.0, 100.0, 10, Clothoid);
   alignment->AddEx(entry_transition);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->putref_PBT(end_entry_spiral);
   curve->putref_PI(pi);
   curve->putref_PFT(start_exit_spiral);
   curve->put_Radius(100);
   alignment->AddEx(curve);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, start_exit_spiral_direction, 100.0, 0.0, 20, Clothoid);
   alignment->AddEx(exit_transition);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(-500, -100);

   alignment->AddEx(pft);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x, y;
   CComPtr<IStation> station;
   Float64 stationVal, offset;

   TRY_TEST(alignment->Bearing(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->Normal(CComVariant(0.00), nullptr), E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125), omtAlongDirection, 10, CComVariant(PI_OVER_2), nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, &station, nullptr), E_POINTER);
   TRY_TEST(alignment->Offset(end, nullptr, &offset), E_POINTER);
   TRY_TEST(alignment->Offset(nullptr, &station, &offset), E_INVALIDARG);

   // Sta 0+00
   TRY_TEST(alignment->Bearing(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI - PI_OVER_2), true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);

   CComPtr<IPoint2d> newPnt;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);

   // Sta 1+25
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, M_PI - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -25.0), true);
   TRY_TEST(IsEqual(y, 10.0), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   // Sta 2+50
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5 * M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5 * M_PI / 4 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -142.4264, 0.001), true);
   TRY_TEST(IsEqual(y, -28.2843, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   // Sta 3+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 2.677945), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 2.677945 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -171.7250, 0.001), true);
   TRY_TEST(IsEqual(y, -27.9571, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   // Sta 4+90
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.1500010067327), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.1500010067327 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -357.5699, 0.001), true);
   TRY_TEST(IsEqual(y, 9.9882, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   // Sta 5+30
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.5326, 0.001), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.5326 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -400.3079, 0.001), true);
   TRY_TEST(IsEqual(y, 1.65612, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   // Sta 5+65
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.87487), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 3.87487 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -432.5904, 0.001), true);
   TRY_TEST(IsEqual(y, -18.8222, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   // Sta 6+00
   dir.Release();
   TRY_TEST(alignment->Bearing(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5 * M_PI / 4), true);

   dir.Release();
   TRY_TEST(alignment->Normal(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, 5 * M_PI / 4 - PI_OVER_2), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00), omtAlongDirection, 10, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, -457.8918, 0.001), true);
   TRY_TEST(IsEqual(y, -43.7496, 0.001), true);

   station.Release();
   TRY_TEST(alignment->Offset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 10.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);

   newPnt.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &distFromStart, &vbOnProjection), S_OK);

   station.Release();
   TRY_TEST(alignment->Offset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);
}
