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

// TestVertCurve.cpp: implementation of the CTestVertCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestVertCurve.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestVertCurve::CTestVertCurve()
{

}

void CTestVertCurve::Test()
{
   Test1();
   Test2();
   Test3();
}

void CTestVertCurve::Test1()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);
   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);
   alignment->AddProfile(0, profile);

   CComPtr<IVerticalCurve> vc;
   TRY_TEST(vc.CoCreateInstance(CLSID_VerticalCurve),S_OK);

   CComQIPtr<IProfileElement> element(vc);
   profile->AddProfileElement(element);

   CComPtr<IProfilePoint> pbg, pvi, pfg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pvi.CoCreateInstance(CLSID_ProfilePoint);
   pfg.CoCreateInstance(CLSID_ProfilePoint);

   // Sag curve
   pbg->put_Station(CComVariant(100));
   pbg->put_Elevation(100);

   pvi->put_Station(CComVariant(200));
   pvi->put_Elevation(50);
   
   pfg->put_Station(CComVariant(400));
   pfg->put_Elevation(100);

   TRY_TEST( vc->put_PBG(nullptr), E_INVALIDARG );
   TRY_TEST( vc->put_PVI(nullptr), E_INVALIDARG );
   TRY_TEST( vc->put_PFG(nullptr), E_INVALIDARG );

   TRY_TEST( vc->put_PBG(pbg), S_OK );
   TRY_TEST( vc->put_PVI(pvi), S_OK );
   TRY_TEST( vc->put_PFG(pfg), S_OK );

   TRY_TEST( vc->put_L1(-1),E_INVALIDARG);
   TRY_TEST( vc->put_L1(0),S_OK);
   TRY_TEST( vc->put_L1(100),S_OK);

   TRY_TEST( vc->put_L2(-1),E_INVALIDARG);
   TRY_TEST( vc->put_L2(0),S_OK);
   TRY_TEST( vc->put_L2(200),S_OK);

   Float64 g1, g2;
   TRY_TEST( vc->get_EntryGrade(nullptr), E_POINTER );
   TRY_TEST( vc->get_EntryGrade(&g1), S_OK );
   TRY_TEST( IsEqual(g1,-0.5), true );

   TRY_TEST( vc->get_ExitGrade(nullptr), E_POINTER );
   TRY_TEST( vc->get_ExitGrade(&g2), S_OK );
   TRY_TEST( IsEqual(g2,0.25), true );

   Float64 L;
   TRY_TEST( element->GetLength(nullptr), E_POINTER );
   TRY_TEST( element->GetLength(&L), S_OK );
   TRY_TEST( IsEqual( L, 300.), true );

   Float64 elev;
   TRY_TEST( vc->Elevation(CComVariant(150),nullptr),E_POINTER );
   TRY_TEST( vc->Elevation(CComVariant(150),&elev), S_OK );
   TRY_TEST( IsEqual(elev,81.25), true );
   TRY_TEST( vc->Elevation(CComVariant(200),&elev), S_OK );
   TRY_TEST( IsEqual(elev,75.0), true );
   TRY_TEST( vc->Elevation(CComVariant(250),&elev), S_OK );
   TRY_TEST( IsEqual(elev,76.5625), true );

   Float64 grade;
   TRY_TEST( vc->Grade(CComVariant(150),nullptr),E_POINTER );
   TRY_TEST( vc->Grade(CComVariant(150),&grade), S_OK );
   TRY_TEST( IsEqual(grade,-0.25), true );
   TRY_TEST( vc->Grade(CComVariant(200),&grade), S_OK );
   TRY_TEST( IsEqual(grade,0.0), true );
   TRY_TEST( vc->Grade(CComVariant(250),&grade), S_OK );
   TRY_TEST( IsEqual(grade,0.0625), true );
   TRY_TEST( vc->Grade(CComVariant(0),&grade), S_OK );
   TRY_TEST( IsEqual(grade,-0.50), true );
   TRY_TEST( vc->Grade(CComVariant(600),&grade), S_OK );
   TRY_TEST( IsEqual(grade, 0.25), true );

   // high point at start
   CComPtr<IProfilePoint> point;
   CComPtr<IStation> station;
   Float64 sta;
   TRY_TEST( vc->get_HighPoint(nullptr), E_POINTER );
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,100.0), true );
   TRY_TEST(IsEqual(elev,100.0),true);

   // low point between ends
   point.Release();
   TRY_TEST( vc->get_LowPoint(nullptr), E_POINTER );
   TRY_TEST( vc->get_LowPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,200.0), true );
   TRY_TEST(IsEqual(elev,75.0),true);

   // high point at end
   pfg->put_Elevation(200);
   vc->put_PFG(pfg);
   point.Release();
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,400.0), true );
   TRY_TEST(IsEqual(elev,200.0),true);

   // make a crest curve
   pbg->put_Station(CComVariant(100));
   pbg->put_Elevation(100);

   pvi->put_Station(CComVariant(200));
   pvi->put_Elevation(150);

   pfg->put_Station(CComVariant(300));
   pfg->put_Elevation(50);

   vc->put_L2(100);
   vc->put_PBG(pbg);
   vc->put_PVI(pvi);
   vc->put_PFG(pfg);

   // high point between ends
   point.Release();
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,166.66667), true );
   TRY_TEST(IsEqual(elev,116.66667),true);

   // low point at end
   point.Release();
   TRY_TEST( vc->get_LowPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,300.0), true );
   TRY_TEST(IsEqual(elev,50.0),true);

   // low point at start
   pbg->put_Elevation(10);
   vc->put_PBG(pbg);
   point.Release();
   TRY_TEST( vc->get_LowPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,100.0), true );
   TRY_TEST(IsEqual(elev, 10.0),true);

   // put the points out of order
   vc->put_PBG(pfg);
   vc->put_PVI(pbg);
   vc->put_PFG(pvi);
   TRY_TEST( element->GetLength(&L), E_FAIL );

   // From "Fundamentals of Surveying" Schmidt and Wong, Third Edition
   // PWS Engineering Press, 1985, ISBN 0-534-04161-2, pg 453, Example 12.3
   pbg->put_Station(CComVariant(4850));
   pbg->put_Elevation(436.34);

   pvi->put_Station(CComVariant(5250));
   pvi->put_Elevation(432.34);

   pfg->put_Station(CComVariant(5650));
   pfg->put_Elevation(441.14);

   vc->put_PBG(pbg);
   vc->put_PVI(pvi);
   vc->put_PFG(pfg);

   vc->put_L1(400);
   vc->put_L2(400);

   vc->Elevation(CComVariant(4700),&elev);   TRY_TEST(IsEqual(elev,437.84),true);
   vc->Elevation(CComVariant(4850),&elev);   TRY_TEST(IsEqual(elev,436.34),true);
   vc->Elevation(CComVariant(4900),&elev);   TRY_TEST(IsEqual(elev,435.89),true);
   vc->Elevation(CComVariant(5000),&elev);   TRY_TEST(IsEqual(elev,435.29),true);
   vc->Elevation(CComVariant(5100),&elev);   TRY_TEST(IsEqual(elev,435.09),true);
   vc->Elevation(CComVariant(5200),&elev);   TRY_TEST(IsEqual(elev,435.29),true);
   vc->Elevation(CComVariant(5300),&elev);   TRY_TEST(IsEqual(elev,435.89),true);
   vc->Elevation(CComVariant(5400),&elev);   TRY_TEST(IsEqual(elev,436.89),true);
   vc->Elevation(CComVariant(5500),&elev);   TRY_TEST(IsEqual(elev,438.29),true);
   vc->Elevation(CComVariant(5600),&elev);   TRY_TEST(IsEqual(elev,440.09),true);
   vc->Elevation(CComVariant(5650),&elev);   TRY_TEST(IsEqual(elev,441.14),true);
   vc->Elevation(CComVariant(6000),&elev);   TRY_TEST(IsEqual(elev,448.84),true);


   point.Release();
   TRY_TEST( vc->get_HighPoint(nullptr), E_POINTER);
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,5650.0), true );
   TRY_TEST(IsEqual(elev,441.14),true);

   point.Release();
   TRY_TEST( vc->get_LowPoint(nullptr), E_POINTER );
   TRY_TEST( vc->get_LowPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,5100.0), true );
   TRY_TEST(IsEqual(elev,435.09),true);

   Float64 L1, L2;
   vc->get_L1(&L1);
   vc->get_L2(&L2);
   L = L1 + L2;

   vc->get_EntryGrade(&g1);
   vc->get_ExitGrade(&g2);

   Float64 A;
   TRY_TEST( vc->get_A(nullptr), E_POINTER );
   TRY_TEST( vc->get_A(&A), S_OK);
   TRY_TEST( IsEqual(g2-g1,A),true);

   Float64 K;
   TRY_TEST(vc->get_K1(nullptr), E_POINTER);
   TRY_TEST(vc->get_K2(nullptr), E_POINTER);
   TRY_TEST( vc->get_K1(&K), S_OK );
   TRY_TEST( IsEqual( A/L, K), true);

   Float64 H;
   TRY_TEST( vc->get_H(nullptr), E_POINTER );
   TRY_TEST( vc->get_H(&H), S_OK );
   TRY_TEST( IsEqual( A*L1*L2/(2*L), H), true);

   Float64 e;
   TRY_TEST( vc->get_E(0,nullptr), E_POINTER );
   TRY_TEST( vc->get_E(0,&e), S_OK );
   TRY_TEST( IsZero(e), true);

   TRY_TEST( vc->get_E(L,&e), S_OK );
   TRY_TEST( IsZero(e), true);

   TRY_TEST( vc->get_E(L1,&e), S_OK );
   TRY_TEST( IsEqual(e,H), true);

   TRY_TEST( vc->get_E(L1/2,&e), S_OK );
   TRY_TEST( IsEqual(e,0.8), true);

   TRY_TEST( vc->get_E(L1+L2/2,&e), S_OK );
   TRY_TEST( IsEqual(e,0.8), true);


   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(vc);
   TRY_TEST( eInfo != nullptr, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IVerticalCurve ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_VerticalCurve,IID_IVerticalCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestVertCurve::Test2()
{
   CComPtr<IAlignment> alignment;
   TRY_TEST(alignment.CoCreateInstance(CLSID_Alignment),S_OK);

   // create station equation
   alignment->AddStationEquation(150, 250);
   alignment->AddStationEquation(400, 200);

   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);
   alignment->AddProfile(0, profile);

   CComPtr<IVerticalCurve> vc;
   TRY_TEST(vc.CoCreateInstance(CLSID_VerticalCurve),S_OK);

   CComPtr<IProfilePoint> pbg, pvi, pfg;
   vc->get_PBG(&pbg);
   vc->get_PVI(&pvi);
   vc->get_PFG(&pfg);

   // Sag curve
   pbg->put_Station(CComVariant(100)); // normalized station
   pbg->put_Elevation(100);
   vc->put_PBG(pbg);

   CComPtr<IStation> objPVIStation;
   objPVIStation.CoCreateInstance(CLSID_Station);
   objPVIStation->SetStation(1,300); // station in equation zone 1
   pvi->put_Station(CComVariant(objPVIStation));
   pvi->put_Elevation(50);
   vc->put_PVI(pvi);
   
   pfg->put_Station(CComVariant(400)); // normalized station
   pfg->put_Elevation(100);
   vc->put_PFG(pfg);

   TRY_TEST( vc->put_L1(100),S_OK);
   TRY_TEST( vc->put_L2(200),S_OK);

   CComQIPtr<IProfileElement> element(vc);
   profile->AddProfileElement(element);

   profile.Release();
   TRY_TEST(element->get_Profile(nullptr), E_POINTER);
   TRY_TEST(element->get_Profile(&profile), S_OK);
   TRY_TEST(profile != nullptr, true);

   Float64 g1, g2;
   TRY_TEST( vc->get_EntryGrade(&g1), S_OK );
   TRY_TEST( IsEqual(g1,-0.5), true );

   TRY_TEST( vc->get_ExitGrade(&g2), S_OK );
   TRY_TEST( IsEqual(g2,0.25), true );

   Float64 L;
   TRY_TEST( element->GetLength(&L), S_OK );
   TRY_TEST( IsEqual( L, 300.), true );

   CComPtr<IStation> station;
   alignment->ConvertFromNormalizedStation(150,&station);
   Float64 elev;
   TRY_TEST( vc->Elevation(CComVariant(station),&elev), S_OK );
   TRY_TEST( IsEqual(elev,81.25), true );
   station.Release();
   alignment->ConvertFromNormalizedStation(200,&station);
   TRY_TEST( vc->Elevation(CComVariant(station),&elev), S_OK );
   TRY_TEST( IsEqual(elev,75.0), true );
   station.Release();
   alignment->ConvertFromNormalizedStation(250,&station);
   TRY_TEST( vc->Elevation(CComVariant(station),&elev), S_OK );
   TRY_TEST( IsEqual(elev,76.5625), true );

   Float64 grade;
   station.Release();
   alignment->ConvertFromNormalizedStation(150,&station);
   TRY_TEST( vc->Grade(CComVariant(station),&grade), S_OK );
   TRY_TEST( IsEqual(grade,-0.25), true );
   station.Release();
   alignment->ConvertFromNormalizedStation(200,&station);
   TRY_TEST( vc->Grade(CComVariant(station),&grade), S_OK );
   TRY_TEST( IsEqual(grade,0.0), true );
   station.Release();
   alignment->ConvertFromNormalizedStation(250,&station);
   TRY_TEST( vc->Grade(CComVariant(station),&grade), S_OK );
   TRY_TEST( IsEqual(grade,0.0625), true );
   station.Release();
   alignment->ConvertFromNormalizedStation(0,&station);
   TRY_TEST( vc->Grade(CComVariant(station),&grade), S_OK );
   TRY_TEST( IsEqual(grade,-0.50), true );
   station.Release();
   alignment->ConvertFromNormalizedStation(600,&station);
   TRY_TEST( vc->Grade(CComVariant(station),&grade), S_OK );
   TRY_TEST( IsEqual(grade, 0.25), true );

   // high point at start
   CComPtr<IProfilePoint> point;
   ZoneIndexType zoneIdx;
   Float64 sta;
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->GetStation(&zoneIdx,&sta);
   point->get_Elevation(&elev);
   TRY_TEST(zoneIdx == 0 || zoneIdx == INVALID_INDEX,true);
   TRY_TEST( IsEqual(sta,100.0), true );
   TRY_TEST(IsEqual(elev,100.0),true);

   // low point between ends
   point.Release();
   TRY_TEST( vc->get_LowPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->GetStation(&zoneIdx,&sta);
   point->get_Elevation(&elev);
   TRY_TEST(zoneIdx,1);
   TRY_TEST( IsEqual(sta,300.0), true );
   TRY_TEST(IsEqual(elev,75.0),true);

   // high point at end
   pfg->put_Elevation(200);
   vc->put_PFG(pfg);
   point.Release();
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->GetStation(&zoneIdx,&sta);
   point->get_Elevation(&elev);
   TRY_TEST(zoneIdx,2);
   TRY_TEST( IsEqual(sta,300.0), true );
   TRY_TEST(IsEqual(elev,200.0),true);
}

void CTestVertCurve::Test3()
{
   CComPtr<IAlignment> alignment;
   TRY_TEST(alignment.CoCreateInstance(CLSID_Alignment), S_OK);

   CComPtr<IProfile> profile;
   profile.CoCreateInstance(CLSID_Profile);
   alignment->AddProfile(0, profile);

   // This is same as Test1, except that instead of PBG and PFG being points off the curve, 
   // they are the BVC and EVC. We input grades instead of lengths (PVI gets computed)
   CComPtr<IVerticalCurve> vc;
   TRY_TEST(vc.CoCreateInstance(CLSID_VerticalCurve),S_OK);

   CComPtr<IProfilePoint> pbg, pfg;
   pbg.CoCreateInstance(CLSID_ProfilePoint);
   pfg.CoCreateInstance(CLSID_ProfilePoint);

   // Sag curve
   pbg->put_Station(CComVariant(100));
   pbg->put_Elevation(100);
   
   pfg->put_Station(CComVariant(400));
   pfg->put_Elevation(100);

   vc->Init2(pbg, pfg, -0.5, 0.25);

   CComQIPtr<IProfileElement> element(vc);
   profile->AddProfileElement(element); // add the curve to the profile before we get any values

   Float64 l1, l2;
   TRY_TEST(vc->get_L1(nullptr), E_POINTER);
   TRY_TEST(vc->get_L1(&l1),  S_OK);
   TRY_TEST(vc->get_L2(nullptr), E_POINTER);
   TRY_TEST(vc->get_L2(&l2),  S_OK);
   TRY_TEST(IsEqual(l1,100.0),true);
   TRY_TEST(IsEqual(l2,200.0),true);

   Float64 L;
   TRY_TEST( element->GetLength(nullptr), E_POINTER );
   TRY_TEST( element->GetLength(&L), S_OK );
   TRY_TEST( IsEqual( L, 300.), true );

   Float64 elev;
   TRY_TEST( vc->Elevation(CComVariant(150),nullptr),E_POINTER );
   TRY_TEST( vc->Elevation(CComVariant(150),&elev), S_OK );
   TRY_TEST( IsEqual(elev,81.25), true );
   TRY_TEST( vc->Elevation(CComVariant(200),&elev), S_OK );
   TRY_TEST( IsEqual(elev,75.0), true );
   TRY_TEST( vc->Elevation(CComVariant(250),&elev), S_OK );
   TRY_TEST( IsEqual(elev,76.5625), true );

   Float64 grade;
   TRY_TEST( vc->Grade(CComVariant(150),nullptr),E_POINTER );
   TRY_TEST( vc->Grade(CComVariant(150),&grade), S_OK );
   TRY_TEST( IsEqual(grade,-0.25), true );
   TRY_TEST( vc->Grade(CComVariant(200),&grade), S_OK );
   TRY_TEST( IsEqual(grade,0.0), true );
   TRY_TEST( vc->Grade(CComVariant(250),&grade), S_OK );
   TRY_TEST( IsEqual(grade,0.0625), true );
   TRY_TEST( vc->Grade(CComVariant(0),&grade), S_OK );
   TRY_TEST( IsEqual(grade,-0.50), true );
   TRY_TEST( vc->Grade(CComVariant(600),&grade), S_OK );
   TRY_TEST( IsEqual(grade, 0.25), true );

   // high point at start
   CComPtr<IProfilePoint> point;
   CComPtr<IStation> station;
   Float64 sta;
   TRY_TEST( vc->get_HighPoint(nullptr), E_POINTER );
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,100.0), true );
   TRY_TEST(IsEqual(elev,100.0),true);

   // low point between ends
   point.Release();
   TRY_TEST( vc->get_LowPoint(nullptr), E_POINTER );
   TRY_TEST( vc->get_LowPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,200.0), true );
   TRY_TEST(IsEqual(elev,75.0),true);

   // high point at end
   pfg->put_Elevation(200);
   vc->put_PFG(pfg);
   vc->put_ExitGrade(0.75);
   point.Release();
   TRY_TEST( vc->get_HighPoint(&point), S_OK );
   station.Release();
   point->get_Station(&station);
   station->get_Value(&sta);
   point->get_Elevation(&elev);
   TRY_TEST( IsEqual(sta,400.0), true );
   TRY_TEST(IsEqual(elev,200.0),true);
}
