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

// TestCircularCurve.cpp: implementation of the CTestCircularCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCircularCurve.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCircularCurve::CTestCircularCurve()
{
}

void CTestCircularCurve::Test()
{
   Test1();

   // Test curve direction
   CComPtr<ICircularCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);

   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   // Back Tangent Bearing = N 45 E
   pbt->Move(0,1000);
   pi->Move(1000, 1000);

   hc->put_PBT(pbt);
   hc->put_PI(pi);

   CurveDirectionType dir;

   // Left Curve
   pft->Move(1000,1500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(1000, 500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // Back Tangent Bearing = N 45 W
   pbt->Move(0,1000);
   pi->Move(1000,1000);
   hc->put_PBT(pbt);
   hc->put_PI(pi);

   // Left Curve
   pft->Move(-1000,1500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(-1000, 500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // Back Tangent Bearing = S 45 W
   pbt->Move(0,1000);
   pi->Move(-1000,-1000);
   hc->put_PBT(pbt);
   hc->put_PI(pi);

   // Left Curve
   pft->Move(-1000,-1500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(-1000, -500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // Back Tangent Bearing = S 45 E
   pbt->Move(0,1000);
   pi->Move(1000,-1000);
   hc->put_PBT(pbt);
   hc->put_PI(pi);

   // Left Curve
   pft->Move(1000,-500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(1000, -1500);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CircularCurve,IID_ICircularCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

void CTestCircularCurve::Test1()
{
   CComPtr<ICircularCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a symmetrical curve to the right
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,700)
   // R   = 500
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,1000);
   pi->Move(700,1000);
   pft->Move(1000,1300);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);
   hc->put_Radius(500);

   CurveDirectionType dir;
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   pft->Move(1000,700);
   hc->put_PFT(pft);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   CComPtr<IDirection> brg;
   Float64 brgVal;
   hc->get_BkTangentBrg(&brg);
   brg->get_Value(&brgVal);
   TRY_TEST( IsEqual(brgVal,0.0), true );

   brg.Release();
   hc->get_FwdTangentBrg(&brg);
   brg->get_Value(&brgVal);
   TRY_TEST( IsEqual(brgVal,7*M_PI/4), true );

   Float64 x, y;

   CComPtr<IPoint2d> pc;
   hc->get_PC(&pc);
   pc->get_X(&x);
   pc->get_Y(&y);
   TRY_TEST( IsEqual(x,492.89322), true );
   TRY_TEST( IsEqual(y,1000.), true );

   CComPtr<IPoint2d> pt;
   hc->get_PT(&pt);
   pt->get_X(&x);
   pt->get_Y(&y);
   TRY_TEST( IsEqual(x,846.44661), true );
   TRY_TEST( IsEqual(y,853.55339), true );

   Float64 chord;
   hc->get_Chord(&chord);
   TRY_TEST( IsEqual(chord,382.683,0.001), true);

   CComPtr<IAngle> angle;
   hc->get_Angle(&angle);
   Float64 val;
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,M_PI/4), true);

   Float64 tangent;
   hc->get_Tangent(&tangent);
   TRY_TEST( IsEqual(tangent,207.10678,0.001), true );

   Float64 mo;
   hc->get_MidOrdinate(&mo);
   TRY_TEST( IsEqual(mo,38.0602,0.001), true );

   CComPtr<IPoint2d> cc;
   hc->get_Center(&cc);
   cc->get_X(&x);
   cc->get_Y(&y);
   TRY_TEST( IsEqual(x,492.89322), true );
   TRY_TEST( IsEqual(y,500.0), true );

   element->GetLength(&val);
   TRY_TEST(IsEqual(val,392.6991,0.001),true );

   //
   // Bearing and Normal
   //
   // Point before curve
   brg.Release();
   TRY_TEST(element->GetBearing(-1,nullptr),E_POINTER);
   TRY_TEST(element->GetBearing(-1,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,0.0),true);
   brg.Release();
   TRY_TEST(element->GetNormal(-1,nullptr),E_POINTER);
   TRY_TEST(element->GetNormal(-1,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,3*PI_OVER_2),true);

   // At mid-point of curve
   brg.Release();
   element->GetLength(&val);
   TRY_TEST(element->GetBearing(val/2,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4 + M_PI/8), true );
   brg.Release();
   element->GetLength(&val);
   TRY_TEST(element->GetNormal(val/2,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4 + M_PI/8 - PI_OVER_2), true );

   // Point after curve
   brg.Release();
   TRY_TEST(element->GetBearing(10000.,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4), true);
   brg.Release();
   TRY_TEST(element->GetNormal(10000.,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4 - PI_OVER_2), true);

   //
   // Test PointOnCurve
   //
   Float64 px,py;
   CComPtr<IPoint2d> pnt;
   
   pnt.Release();
   TRY_TEST(element->PointOnCurve(-100.0,&pnt),S_OK); // Before PC
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pc->get_X(&x);
   pc->get_Y(&y);
   TRY_TEST(IsEqual(x-100,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   TRY_TEST(element->PointOnCurve(0.0,&pnt),S_OK); // PC
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pc->get_X(&x);
   pc->get_Y(&y);
   TRY_TEST(IsEqual(x,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   element->GetLength(&val); // length of circular curve
   TRY_TEST(element->PointOnCurve(val/2,&pnt),S_OK); // Half-way around the circular curve
   pnt->get_X(&px);
   pnt->get_Y(&py);
   TRY_TEST(IsEqual(px,684.23493),true);
   TRY_TEST(IsEqual(py,961.93977),true);

   pnt.Release();
   element->GetLength(&val); // length of circular curve
   TRY_TEST(element->PointOnCurve(val,&pnt),S_OK); // PT
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pt->get_X(&x);
   pt->get_Y(&y);
   TRY_TEST(IsEqual(x,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   element->GetLength(&val); // length of circular curve
   TRY_TEST(element->PointOnCurve(val,&pnt),S_OK); // PT
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pt->get_X(&x);
   pt->get_Y(&y);
   TRY_TEST(IsEqual(x,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   element->GetLength(&val); // length of circular curve
   TRY_TEST(element->PointOnCurve(val + 100,&pnt),S_OK); // 100 past PT
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pt->get_X(&x);
   pt->get_Y(&y);
   TRY_TEST(IsEqual(x+100*cos(M_PI/4),px),true);
   TRY_TEST(IsEqual(y-100*cos(M_PI/4),py),true);
   
   //
   // Test ProjectPoint
   //
   pnt.Release();
   pnt.CoCreateInstance(CLSID_Point2d);
   pnt->Move(300,1100);
   CComPtr<IPoint2d> prjPoint;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(element->ProjectPoint(nullptr,&prjPoint, &distFromStart, &vbOnProjection),E_INVALIDARG);
   TRY_TEST(element->ProjectPoint(pnt,nullptr, &distFromStart, &vbOnProjection),E_POINTER);
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 300.0),true);
   TRY_TEST(IsEqual(py,1000.0),true);

   pnt->Move(300,900);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 300.0),true);
   TRY_TEST(IsEqual(py,1000.0),true);

   pnt->Move(500,1100);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 498.8151,0.001),true);
   TRY_TEST(IsEqual(py, 999.9649,0.001),true);

   pnt->Move(500,900);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 501.7753,0.001),true);
   TRY_TEST(IsEqual(py, 999.9211,0.001),true);

   pnt->Move(1000,1300);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 760.5851,0.001),true);
   TRY_TEST(IsEqual(py, 922.3045,0.001),true);

   pnt->Move(550,700);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 630.1736,0.001),true);
   TRY_TEST(IsEqual(py, 980.7849,0.001),true);

   pnt->Move(900,900);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 850.0000,0.001),true);
   TRY_TEST(IsEqual(py, 850.0000,0.001),true);

   pnt->Move(800,800);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 850.0000,0.001),true);
   TRY_TEST(IsEqual(py, 850.0000,0.001),true);

   pnt->Move(1100,500);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px,1150.0),true);
   TRY_TEST(IsEqual(py,550.0),true);

   pnt->Move(1200,600);
   prjPoint.Release();
   TRY_TEST(element->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px,1150.0),true);
   TRY_TEST(IsEqual(py,550.0),true);
}
