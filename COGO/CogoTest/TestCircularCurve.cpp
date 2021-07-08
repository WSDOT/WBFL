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

// TestCircularCurve.cpp: implementation of the CTestCircularCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCircularCurve.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCircularCurve::CTestCircularCurve()
{
}

void CTestCircularCurve::Test()
{
   //Test1();
   //Test2();
   //Test3();
   Test4();
   //Test5();
   //Test6();
   //Test7();
   //Test8a();
   //Test8b();
   //Test9a();
   //Test9b();
   //Test10a();
   //Test10b();
   //Test11a();
   //Test11b();
   TestEvents();

   // Test curve direction
   CComPtr<ICircularCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);

   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);

   // Back Tangent Bearing = N 45 E
   pbt->Move(0,1000);
   pi->Move(1000,1000);

   CurveDirectionType dir;

   // Left Curve
   pft->Move(1000,1500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(1000, 500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // Back Tangent Bearing = N 45 W
   pbt->Move(0,1000);
   pi->Move(1000,1000);

   // Left Curve
   pft->Move(-1000,1500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(-1000, 500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // Back Tangent Bearing = S 45 W
   pbt->Move(0,1000);
   pi->Move(-1000,-1000);

   // Left Curve
   pft->Move(-1000,-1500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(-1000, -500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // Back Tangent Bearing = S 45 E
   pbt->Move(0,1000);
   pi->Move(1000,-1000);

   // Left Curve
   pft->Move(1000,-500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   // Right
   pft->Move(1000, -1500);
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdRight );

   // PointFactory
   CComPtr<IPoint2dFactory> factory;
   TRY_TEST(hc->get_PointFactory(nullptr),E_POINTER);
   TRY_TEST(hc->get_PointFactory(&factory),S_OK);
   TRY_TEST(factory != nullptr,true);
   TRY_TEST(hc->putref_PointFactory(nullptr),E_INVALIDARG);
   TRY_TEST(hc->putref_PointFactory(factory),S_OK);

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CircularCurve,IID_ICircularCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

//void CTestCircularCurve::Test1()
//{
//   CComPtr<ICircularCurve> hc;
//   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);
//
//   /////////////////////////////////////////////////////
//   // Test a non-symmetrical spiral-curve-spiral to the right
//   // PBT = (0,1000)
//   // PI  = (700,1000)
//   // PFT = (1000,700)
//   // R   = 500
//   // Entry Spiral Length = 100
//   // Exit Spiral Length = 200
//   CComPtr<IPoint2d> pbt, pi, pft;
//   pbt.CoCreateInstance(CLSID_Point2d);
//   pi.CoCreateInstance(CLSID_Point2d);
//   pft.CoCreateInstance(CLSID_Point2d);
//
//   pbt->Move(0,1000);
//   pi->Move(700,1000);
//   pft->Move(1000,1300);
//
//   TRY_TEST( hc->putref_PBT(nullptr), E_INVALIDARG );
//   TRY_TEST( hc->putref_PI(nullptr), E_INVALIDARG );
//   TRY_TEST( hc->putref_PFT(nullptr), E_INVALIDARG );
//
//   TRY_TEST( hc->putref_PBT(pbt), S_OK );
//   TRY_TEST( hc->putref_PI(pi), S_OK );
//   TRY_TEST( hc->putref_PFT(pft), S_OK );
//
//   CComPtr<IPoint2d> pnt;
//   TRY_TEST( hc->get_PBT(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PBT(&pnt), S_OK );
//   TRY_TEST( pnt.IsEqualObject(pbt), true );
//
//   pnt.Release();
//   TRY_TEST( hc->get_PI(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PI(&pnt), S_OK );
//   TRY_TEST( pnt.IsEqualObject(pi), true );
//
//   pnt.Release();
//   TRY_TEST( hc->get_PFT(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PFT(&pnt), S_OK );
//   TRY_TEST( pnt.IsEqualObject(pft), true );
//
//   TRY_TEST( hc->put_Radius(-1), E_INVALIDARG);
//   TRY_TEST( hc->put_Radius(0),  E_INVALIDARG);
//   TRY_TEST( hc->put_Radius(500), S_OK);
//
//   TRY_TEST( hc->put_SpiralLength(spEntry,-1), E_INVALIDARG );
//   TRY_TEST( hc->put_SpiralLength(spEntry,100), S_OK);
//
//   TRY_TEST( hc->put_SpiralLength(spExit,-1), E_INVALIDARG );
//   TRY_TEST( hc->put_SpiralLength(spExit,200), S_OK);
//
//   CurveDirectionType dir;
//   TRY_TEST( hc->get_Direction(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Direction(&dir), S_OK );
//   TRY_TEST( dir, cdLeft );
//
//   pft->Move(1000,700);
//   TRY_TEST( hc->get_Direction(&dir), S_OK );
//   TRY_TEST( dir, cdRight );
//
//   Float64 radius;
//   TRY_TEST( hc->get_Radius(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Radius(&radius), S_OK );
//   TRY_TEST(IsEqual(radius,500.),true);
//
//   CComPtr<IAngle> angle;
//   Float64 val;
//   TRY_TEST( hc->get_SpiralAngle(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SpiralAngle(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_SpiralAngle(spExit,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SpiralAngle(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.2), true );
//
//   Float64 x,y;
//   TRY_TEST( hc->get_X(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_X(spEntry,&x), S_OK );
//   TRY_TEST( IsEqual(x,99.900046285613), true );
//   TRY_TEST( hc->get_X(spExit,&x), S_OK );
//   TRY_TEST( IsEqual(x,199.20148011396), true );
//
//   TRY_TEST( hc->get_Y(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_Y(spEntry,&y), S_OK );
//   TRY_TEST( IsEqual(y,3.3309531383959), true );
//   TRY_TEST( hc->get_Y(spExit,&y), S_OK );
//   TRY_TEST( IsEqual(y,13.295286546224), true );
//
//   Float64 Q;
//   TRY_TEST( hc->get_Q(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_Q(spEntry,&Q), S_OK );
//   TRY_TEST( IsEqual(Q,0.83303), true );
//
//   TRY_TEST( hc->get_Q(spExit,&Q), S_OK );
//   TRY_TEST( IsEqual(Q,3.32857), true );
//
//   Float64 K;
//   TRY_TEST( hc->get_T(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_T(spEntry,&K), S_OK );
//   TRY_TEST( IsEqual(K,49.98333), true );
//
//   TRY_TEST( hc->get_T(spExit,&K), S_OK );
//   TRY_TEST( IsEqual(K,99.86681), true );
//
//   CComPtr<IDirection> brg;
//   Float64 brgVal;
//   TRY_TEST( hc->get_BkTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_BkTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,0.0), true );
//
//   brg.Release();
//   TRY_TEST( hc->get_FwdTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_FwdTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,7*M_PI/4), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_CurveAngle(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CurveAngle(&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,M_PI/4), true);
//
//   Float64 tangent;
//   TRY_TEST( hc->get_BkTangentLength(nullptr), E_POINTER );
//   TRY_TEST( hc->get_BkTangentLength(&tangent), S_OK );
//   TRY_TEST( IsEqual(tangent,260.96439), true );
//
//   TRY_TEST( hc->get_FwdTangentLength(nullptr), E_POINTER );
//   TRY_TEST( hc->get_FwdTangentLength(&tangent), S_OK );
//   TRY_TEST( IsEqual(tangent,304.82311), true );
//
//   CComPtr<IPoint2d> ts;
//   TRY_TEST( hc->get_TS(nullptr), E_POINTER );
//   TRY_TEST( hc->get_TS(&ts), S_OK );
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST( IsEqual(x,439.03561), true );
//   TRY_TEST( IsEqual(y,1000.), true );
//
//   CComPtr<IPoint2d> st;
//   TRY_TEST( hc->get_ST(nullptr), E_POINTER );
//   TRY_TEST( hc->get_ST(&st), S_OK );
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST( IsEqual(x,915.54248), true );
//   TRY_TEST( IsEqual(y,784.45751), true );
//
//   CComPtr<IPoint2d> sc;
//   TRY_TEST( hc->get_SC(nullptr), E_POINTER );
//   TRY_TEST( hc->get_SC(&sc), S_OK );
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST( IsEqual(x,538.93564), true );
//   TRY_TEST( IsEqual(y,996.66904), true );
//
//   CComPtr<IPoint2d> cs;
//   TRY_TEST( hc->get_CS(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CS(&cs), S_OK );
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST( IsEqual(x,765.28458), true );
//   TRY_TEST( IsEqual(y,915.91304), true );
//
//   Float64 chord;
//   TRY_TEST( hc->get_Chord(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Chord(&chord), S_OK );
//   TRY_TEST( IsEqual(chord,240.32347), true);
//
//   angle.Release();
//   TRY_TEST( hc->get_CircularCurveAngle(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CircularCurveAngle(&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.4854), true);
//
//   TRY_TEST( hc->get_Tangent(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Tangent(&tangent), S_OK );
//   TRY_TEST( IsEqual(tangent,123.78966), true );
//
//   Float64 mo;
//   TRY_TEST( hc->get_MidOrdinate(nullptr), E_POINTER );
//   TRY_TEST( hc->get_MidOrdinate(&mo), S_OK );
//   TRY_TEST( IsEqual(mo,14.65357), true );
//
//   Float64 external;
//   TRY_TEST( hc->get_External(nullptr), E_POINTER);
//   TRY_TEST( hc->get_External(&external), S_OK);
//   TRY_TEST( IsEqual(external,15.095991), true);
//
//   angle.Release();
//   TRY_TEST( hc->get_DE(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_DE(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DE(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.2), true );
//
//   Float64 U;
//   TRY_TEST( hc->get_LongTangent(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_LongTangent(spEntry,&U), S_OK );
//   TRY_TEST( IsEqual(U,66.701620764682), true );
//   TRY_TEST( hc->get_LongTangent(spExit,&U), S_OK );
//   TRY_TEST( IsEqual(U,133.61377), true );
//
//   Float64 V;
//   TRY_TEST( hc->get_ShortTangent(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_ShortTangent(spEntry,&V), S_OK );
//   TRY_TEST( IsEqual(V,33.365112106495), true );
//   TRY_TEST( hc->get_ShortTangent(spExit,&V), S_OK );
//   TRY_TEST( IsEqual(V,66.92168), true );
//
//   CComPtr<IPoint2d> cc;
//   TRY_TEST( hc->get_CC(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CC(&cc), S_OK );
//   cc->get_X(&x);
//   cc->get_Y(&y);
//   TRY_TEST( IsEqual(x,439.03561), true );
//   TRY_TEST( IsEqual(y,307.95062), true );
//
//   CComPtr<IPoint2d> spi;
//   TRY_TEST( hc->get_SPI(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SPI(spEntry,&spi), S_OK );
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x,505.73722), true );
//   TRY_TEST( IsEqual(y,1000.0), true );
//
//   spi.Release();
//   TRY_TEST( hc->get_SPI(spExit,&spi), S_OK );
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x,821.06328), true );
//   TRY_TEST( IsEqual(y,878.93671), true );
//
//   brg.Release();
//   TRY_TEST( hc->get_CurveBkTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CurveBkTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,6.18318530718), true );
//
//   brg.Release();
//   TRY_TEST( hc->get_CurveFwdTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CurveFwdTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,5.69778), true );
//
//   CComPtr<IPoint2d> pci;
//   TRY_TEST( hc->get_PCI(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PCI(&pci), S_OK );
//   pci->get_X(&x);
//   pci->get_Y(&y);
//   TRY_TEST( IsEqual(x,662.10687), true );
//   TRY_TEST( IsEqual(y,984.31070), true );
//
//   CComPtr<IPoint2d> ccc;
//   TRY_TEST( hc->get_CCC(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CCC(&ccc), S_OK );
//   ccc->get_X(&x);
//   ccc->get_Y(&y);
//   TRY_TEST( IsEqual(x,489.01894), true );
//   TRY_TEST( IsEqual(y,499.16696), true );
//
//   TRY_TEST( hc->get_SpiralChord(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SpiralChord(spEntry,&chord), S_OK );
//   TRY_TEST( IsEqual(chord,99.95556), true );
//   TRY_TEST( hc->get_SpiralChord(spExit,&chord), S_OK );
//   TRY_TEST( IsEqual(chord,199.64467), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DF(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_DF(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0333305,1e-6), true );
//   angle.Release();
//   TRY_TEST( hc->get_DF(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666441,1e-6), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DH(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_DH(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666695,1e-6), true );
//   angle.Release();
//   TRY_TEST( hc->get_DH(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1333559,1e-6), true );
//
//   TRY_TEST(hc->get_CurveLength(nullptr),E_POINTER);
//   TRY_TEST(hc->get_CurveLength(&val),S_OK);
//   TRY_TEST(IsEqual(val,242.69908),true );
//
//   TRY_TEST(hc->get_TotalLength(nullptr),E_POINTER);
//   TRY_TEST(hc->get_TotalLength(&val),S_OK);
//   TRY_TEST(IsEqual(val,542.69908),true );
//
//   //
//   // Bearing and Normal
//   //
//   // Point before curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Bearing(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0),true);
//   brg.Release();
//   TRY_TEST(hc->Normal(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Normal(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,3*PI_OVER_2),true);
//
//   // At SC
//   brg.Release();
//   TRY_TEST(hc->Bearing(100.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,TWO_PI - 0.1), true );
//   brg.Release();
//   TRY_TEST(hc->Normal(100.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,TWO_PI - 0.1 - PI_OVER_2), true );
//
//   // At CS
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Bearing(100+val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 + 0.2), true );
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Normal(100+val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 + 0.2 - PI_OVER_2), true );
//
//   // Mid-point of exit spiral
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Bearing(100+val+200/2,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 + 0.05), true );
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Normal(100+val+200/2,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 + 0.05 - PI_OVER_2), true );
//
//   // Point after curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4), true);
//   brg.Release();
//   TRY_TEST(hc->Normal(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 - PI_OVER_2), true);
//
//   //
//   // Test PointOnCurve
//   //
//   Float64 px,py;
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(0.0,nullptr),E_POINTER);
//   
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(-100.0,&pnt),S_OK); // Before TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x-100,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(0.0,&pnt),S_OK); // TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(50.0,&pnt),S_OK); // half-way between TS and SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,489.03248),true);
//   TRY_TEST(IsEqual(py,999.58335),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(100.0,&pnt),S_OK); // SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val/2,&pnt),S_OK); // Half-way around the circular curve
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,657.03416),true);
//   TRY_TEST(IsEqual(py,970.09253),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val,&pnt),S_OK); // CS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val + 200./2,&pnt),S_OK); // Half-way along exit spiral
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,843.67118),true);
//   TRY_TEST(IsEqual(py,853.97221),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val + 200.,&pnt),S_OK); // ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val + 200 + 100,&pnt),S_OK); // 100 past ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x+100*cos(M_PI/4),px),true);
//   TRY_TEST(IsEqual(y-100*cos(M_PI/4),py),true);
//
//
//   //
//   // Test ProjectPoint
//   //
//   pnt.Release();
//   pnt.CoCreateInstance(CLSID_Point2d);
//   pnt->Move(300,1100);
//   CComPtr<IPoint2d> prjPoint;
//   Float64 distFromStart;
//   VARIANT_BOOL vbOnProjection;
//   TRY_TEST(hc->ProjectPoint(nullptr,&prjPoint, &distFromStart, &vbOnProjection),E_INVALIDARG);
//   TRY_TEST(hc->ProjectPoint(pnt,nullptr, &distFromStart, &vbOnProjection),E_POINTER);
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(300,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(500,1100);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 496.65666),true);
//   TRY_TEST(IsEqual(py, 999.36213),true);
//
//   pnt->Move(500,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 504.21291),true);
//   TRY_TEST(IsEqual(py, 999.07669),true);
//
//   pnt->Move(1000,1300);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 757.96599),true);
//   TRY_TEST(IsEqual(py, 920.67316),true);
//
//   pnt->Move(550,700);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 634.29003),true);
//   TRY_TEST(IsEqual(py, 977.59805),true);
//
//   pnt->Move(900,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 851.1983,0.001),true);
//   TRY_TEST(IsEqual(py, 847.0948,0.001),true);
//
//   pnt->Move(800,800);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 846.7079,0.001),true);
//   TRY_TEST(IsEqual(py, 851.2138,0.001),true);
//
//   pnt->Move(1100,500);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//
//   pnt->Move(1200,600);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//
//   // This point should project onto both tangents.
//   // It is nearest the back tangent.
//   pnt->Move(200,0);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 200.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   // This point should project onto both tangents.
//   // It is nearest the foward tangent.
//   pnt->Move(400,0);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1050.0),true);
//   TRY_TEST(IsEqual(py, 650.0),true);
//
//   // This point should project onto both spirals.
//   // It is nearest the entry spiral.
//   pnt->Move(450,430);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,450.78715),true);
//   TRY_TEST(IsEqual(py,999.99459),true);
//
//   // This point should project onto both spirals.
//   // It is nearest the exit spiral.
//   pnt->Move(470,400);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,879.50334),true);
//   TRY_TEST(IsEqual(py,820.18857),true);
//
//   ////////////////////////////////////
//   // Test ISupportErrorInfo
//   CComQIPtr<ISupportErrorInfo> eInfo(hc);
//   TRY_TEST( eInfo != nullptr, true );
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICircularCurve ), S_OK );
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
//   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
//
//   // Test IObjectSafety
//   TRY_TEST( TestIObjectSafety(CLSID_CircularCurve,IID_ICircularCurve,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
//   TRY_TEST( TestIObjectSafety(CLSID_CircularCurve,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
//}
//
//void CTestCircularCurve::Test2()
//{
//   CComPtr<ICircularCurve> hc;
//   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);
//
//   /////////////////////////////////////////////////////
//   // Test a symmetrical curve to the right
//   // PBT = (0,1000)
//   // PI  = (700,1000)
//   // PFT = (1000,700)
//   // R   = 500
//   // Entry Spiral Length = 100
//   // Exit Spiral Length = 0
//   CComPtr<IPoint2d> pbt, pi, pft;
//   pbt.CoCreateInstance(CLSID_Point2d);
//   pi.CoCreateInstance(CLSID_Point2d);
//   pft.CoCreateInstance(CLSID_Point2d);
//
//   pbt->Move(0,1000);
//   pi->Move(700,1000);
//   pft->Move(1000,1300);
//
//   hc->putref_PBT(pbt);
//   hc->putref_PI(pi);
//   hc->putref_PFT(pft);
//   hc->put_Radius(500);
//   hc->put_SpiralLength(spEntry,100);
//   hc->put_SpiralLength(spExit,0);
//
//   CurveDirectionType dir;
//   hc->get_Direction(&dir);
//   TRY_TEST( dir, cdLeft );
//
//   pft->Move(1000,700);
//   hc->get_Direction(&dir);
//   TRY_TEST( dir, cdRight );
//
//   CComPtr<IAngle> angle;
//   Float64 val;
//   hc->get_SpiralAngle(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1), true );
//
//   angle.Release();
//   hc->get_SpiralAngle(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//
//   Float64 x,y;
//   hc->get_X(spEntry,&x);
//   TRY_TEST( IsEqual(x,99.900,0.001), true );
//   hc->get_Y(spEntry,&y);
//   TRY_TEST( IsEqual(y,3.33095), true );
//
//   hc->get_X(spExit,&x);
//   TRY_TEST( IsEqual(x,0.0), true );
//   hc->get_Y(spExit,&y);
//   TRY_TEST( IsEqual(y,0.0), true );
//
//   Float64 Q;
//   hc->get_Q(spEntry,&Q);
//   TRY_TEST( IsEqual(Q,0.83304), true );
//
//   hc->get_Q(spExit,&Q);
//   TRY_TEST( IsEqual(Q,0.0), true );
//
//   Float64 K;
//   hc->get_T(spEntry,&K);
//   TRY_TEST( IsEqual(K,49.98334), true );
//
//   hc->get_T(spExit,&K);
//   TRY_TEST( IsEqual(K,0.0), true );
//
//   CComPtr<IDirection> brg;
//   Float64 brgVal;
//   hc->get_BkTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,0.0), true );
//
//   brg.Release();
//   hc->get_FwdTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,7*M_PI/4), true );
//
//   angle.Release();
//   hc->get_CurveAngle(&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,M_PI/4), true);
//
//   Float64 tangent;
//   hc->get_BkTangentLength(&tangent);
//   TRY_TEST( IsEqual(tangent,256.2571,0.001), true );
//
//   hc->get_FwdTangentLength(&tangent);
//   TRY_TEST( IsEqual(tangent,208.2848,0.001), true );
//
//   CComPtr<IPoint2d> ts;
//   hc->get_TS(&ts);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST( IsEqual(x,443.7429,0.001), true );
//   TRY_TEST( IsEqual(y,1000.), true );
//
//   CComPtr<IPoint2d> st;
//   hc->get_ST(&st);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST( IsEqual(x,847.2796,0.001), true );
//   TRY_TEST( IsEqual(y,852.7204,0.001), true );
//
//   CComPtr<IPoint2d> sc;
//   hc->get_SC(&sc);
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST( IsEqual(x,543.6430,0.001), true );
//   TRY_TEST( IsEqual(y,996.669,0.001), true );
//
//   CComPtr<IPoint2d> cs;
//   hc->get_CS(&cs);
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST( IsEqual(x,847.2796,0.001), true );
//   TRY_TEST( IsEqual(y,852.7204,0.001), true );
//
//   Float64 chord;
//   hc->get_Chord(&chord);
//   TRY_TEST( IsEqual(chord,336.03044), true);
//
//   angle.Release();
//   hc->get_CircularCurveAngle(&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.685398), true);
//
//   hc->get_Tangent(&tangent);
//   TRY_TEST( IsEqual(tangent,178.3883), true );
//
//   Float64 mo;
//   hc->get_MidOrdinate(&mo);
//   TRY_TEST( IsEqual(mo,29.07443), true );
//
//   angle.Release();
//   hc->get_DE(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1), true );
//
//   angle.Release();
//   hc->get_DE(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//
//   Float64 U;
//   hc->get_LongTangent(spEntry,&U);
//   TRY_TEST( IsEqual(U,66.7016,0.001), true );
//   hc->get_LongTangent(spExit,&U);
//   TRY_TEST( IsEqual(U,0.0), true );
//
//   Float64 V;
//   hc->get_ShortTangent(spEntry,&V);
//   TRY_TEST( IsEqual(V,33.3651,0.001), true );
//   hc->get_ShortTangent(spExit,&V);
//   TRY_TEST( IsEqual(V,0.0), true );
//
//// Not computed by WinCOGO and not easily derived
////   CComPtr<IPoint2d> cc;
////   hc->get_CC(&cc);
////   cc->get_X(&x);
////   cc->get_Y(&y);
////   TRY_TEST( IsEqual(x,493.7263), true );
////   TRY_TEST( IsEqual(y,499.1670), true );
//
//   CComPtr<IPoint2d> spi;
//   hc->get_SPI(spEntry,&spi);
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x,510.4445,0.001), true );
//   TRY_TEST( IsEqual(y,1000.), true );
//
//   spi.Release();
//   hc->get_SPI(spExit,&spi);
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x,847.27965), true );
//   TRY_TEST( IsEqual(y,852.72035), true );
//
//   brg.Release();
//   hc->get_CurveBkTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,6.18318530718), true );
//
//   brg.Release();
//   hc->get_CurveFwdTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,7*M_PI/4), true );
//
//   CComPtr<IPoint2d> pci;
//   hc->get_PCI(&pci);
//   pci->get_X(&x);
//   pci->get_Y(&y);
//   TRY_TEST( IsEqual(x,721.14007), true );
//   TRY_TEST( IsEqual(y,978.85993), true );
//
//   CComPtr<IPoint2d> ccc;
//   hc->get_CCC(&ccc);
//   ccc->get_X(&x);
//   ccc->get_Y(&y);
//   TRY_TEST( IsEqual(x,493.7263,0.001), true );
//   TRY_TEST( IsEqual(y,499.1670,0.001), true );
//
//   hc->get_SpiralChord(spEntry,&chord);
//   TRY_TEST( IsEqual(chord,99.955562), true );
//   hc->get_SpiralChord(spExit,&chord);
//   TRY_TEST( IsEqual(chord,0.0), true );
//
//   angle.Release();
//   hc->get_DF(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0333305), true );
//   angle.Release();
//   hc->get_DF(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//
//   angle.Release();
//   hc->get_DH(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666695), true );
//   angle.Release();
//   hc->get_DH(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//
//   hc->get_CurveLength(&val);
//   TRY_TEST(IsEqual(val,342.6991,0.001),true );
//
//   hc->get_TotalLength(&val);
//   TRY_TEST(IsEqual(val,442.6991,0.001),true );
//
//
//   //
//   // Bearing and Normal
//   //
//   // Point before curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Bearing(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0),true);
//   brg.Release();
//   TRY_TEST(hc->Normal(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Normal(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,3*PI_OVER_2),true);
//
//   // At SC
//   brg.Release();
//   TRY_TEST(hc->Bearing(100.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,TWO_PI - 0.1), true );
//   brg.Release();
//   TRY_TEST(hc->Normal(100.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,TWO_PI - 0.1 - PI_OVER_2), true );
//
//   // At CS
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Bearing(100+val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4), true );
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Normal(100+val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 - PI_OVER_2), true );
//
//   // Point after curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4), true);
//   brg.Release();
//   TRY_TEST(hc->Normal(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 - PI_OVER_2), true);
//
//   //
//   // Test PointOnCurve
//   //
//   Float64 px,py;
//   CComPtr<IPoint2d> pnt;
//   
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(-100.0,&pnt),S_OK); // Before TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x-100,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(0.0,&pnt),S_OK); // TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(50.0,&pnt),S_OK); // half-way between TS and SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,493.73979),true);
//   TRY_TEST(IsEqual(py,999.58335),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(100.0,&pnt),S_OK); // SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val/2,&pnt),S_OK); // Half-way around the circular curve
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,707.91621),true);
//   TRY_TEST(IsEqual(py,950.96633),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val,&pnt),S_OK); // CS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val,&pnt),S_OK); // ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val + 100,&pnt),S_OK); // 100 past ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x+100*cos(M_PI/4),px),true);
//   TRY_TEST(IsEqual(y-100*cos(M_PI/4),py),true);
//
//
//   //
//   // Test ProjectPoint
//   //
//   pnt.Release();
//   pnt.CoCreateInstance(CLSID_Point2d);
//   pnt->Move(300,1100);
//   CComPtr<IPoint2d> prjPoint;
//   Float64 distFromStart;
//   VARIANT_BOOL vbOnProjection;
//   TRY_TEST(hc->ProjectPoint(nullptr,&prjPoint, &distFromStart, &vbOnProjection),E_INVALIDARG);
//   TRY_TEST(hc->ProjectPoint(pnt,nullptr, &distFromStart, &vbOnProjection),E_POINTER);
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(300,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(500,1100);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 497.1337,0.001),true);
//   TRY_TEST(IsEqual(py, 999.4926,0.001),true);
//
//   pnt->Move(500,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 503.5543,0.001),true);
//   TRY_TEST(IsEqual(py, 999.2866,0.001),true);
//
//   pnt->Move(1000,1300);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 760.9055,0.001),true);
//   TRY_TEST(IsEqual(py, 921.7959,0.001),true);
//
//   pnt->Move(550,700);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 628.6312,0.001),true);
//   TRY_TEST(IsEqual(py, 980.6238,0.001),true);
//
//   pnt->Move(900,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 850.0000,0.001),true);
//   TRY_TEST(IsEqual(py, 850.0000,0.001),true);
//
//   pnt->Move(800,800);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 850.0000,0.001),true);
//   TRY_TEST(IsEqual(py, 850.0000,0.001),true);
//
//   pnt->Move(1100,500);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//
//   pnt->Move(1200,600);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//}
//
//void CTestCircularCurve::Test3()
//{
//   CComPtr<ICircularCurve> hc;
//   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);
//
//   /////////////////////////////////////////////////////
//   // Test a symmetrical curve to the right
//   // PBT = (0,1000)
//   // PI  = (700,1000)
//   // PFT = (1000,700)
//   // R   = 500
//   // Entry Spiral Length = 0
//   // Exit Spiral Length = 200
//   CComPtr<IPoint2d> pbt, pi, pft;
//   pbt.CoCreateInstance(CLSID_Point2d);
//   pi.CoCreateInstance(CLSID_Point2d);
//   pft.CoCreateInstance(CLSID_Point2d);
//
//   pbt->Move(0,1000);
//   pi->Move(700,1000);
//   pft->Move(1000,1300);
//
//   hc->putref_PBT(pbt);
//   hc->putref_PI(pi);
//   hc->putref_PFT(pft);
//   hc->put_Radius(500);
//   hc->put_SpiralLength(spEntry,0);
//   hc->put_SpiralLength(spExit,200);
//
//   CurveDirectionType dir;
//   hc->get_Direction(&dir);
//   TRY_TEST( dir, cdLeft );
//
//   pft->Move(1000,700);
//   hc->get_Direction(&dir);
//   TRY_TEST( dir, cdRight );
//
//   CComPtr<IAngle> angle;
//   Float64 val;
//   hc->get_SpiralAngle(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//
//   angle.Release();
//   hc->get_SpiralAngle(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.2), true );
//
//   Float64 x,y;
//   hc->get_X(spEntry,&x);
//   TRY_TEST( IsEqual(x,0.0), true );
//   hc->get_Y(spEntry,&y);
//   TRY_TEST( IsEqual(y,0.0), true );
//
//   hc->get_X(spExit,&x);
//   TRY_TEST( IsEqual(x,199.20148), true );
//   hc->get_Y(spExit,&y);
//   TRY_TEST( IsEqual(y,13.29528), true );
//
//   Float64 Q;
//   hc->get_Q(spEntry,&Q);
//   TRY_TEST( IsEqual(Q,0.0), true );
//
//   hc->get_Q(spExit,&Q);
//   TRY_TEST( IsEqual(Q,3.3286,0.001), true );
//
//   Float64 K;
//   hc->get_T(spEntry,&K);
//   TRY_TEST( IsEqual(K,0.0), true );
//
//   hc->get_T(spExit,&K);
//   TRY_TEST( IsEqual(K,99.8668,0.001), true );
//
//   CComPtr<IDirection> brg;
//   Float64 brgVal;
//   hc->get_BkTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,0.0), true );
//
//   brg.Release();
//   hc->get_FwdTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,7*M_PI/4), true );
//
//   angle.Release();
//   hc->get_CurveAngle(&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,M_PI/4), true);
//
//   Float64 tangent;
//   hc->get_BkTangentLength(&tangent);
//   TRY_TEST( IsEqual(tangent,211.8141,0.001), true );
//
//   hc->get_FwdTangentLength(&tangent);
//   TRY_TEST( IsEqual(tangent,303.6450,0.001), true );
//
//   CComPtr<IPoint2d> ts;
//   hc->get_TS(&ts);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST( IsEqual(x,488.1859,0.001), true );
//   TRY_TEST( IsEqual(y,1000.), true );
//
//   CComPtr<IPoint2d> st;
//   hc->get_ST(&st);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST( IsEqual(x,914.7095,0.001), true );
//   TRY_TEST( IsEqual(y,785.2905,0.001), true );
//
//   CComPtr<IPoint2d> sc;
//   hc->get_SC(&sc);
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST( IsEqual(x,488.1859,0.001), true );
//   TRY_TEST( IsEqual(y,1000.0), true );
//
//   CComPtr<IPoint2d> cs;
//   hc->get_CS(&cs);
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST( IsEqual(x,764.4515,0.001), true );
//   TRY_TEST( IsEqual(y,916.7461,0.001), true );
//
//   Float64 chord;
//   hc->get_Chord(&chord);
//   TRY_TEST( IsEqual(chord,288.5375,0.001), true);
//
//   angle.Release();
//   hc->get_CircularCurveAngle(&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.585398), true);
//
//   hc->get_Tangent(&tangent);
//   TRY_TEST( IsEqual(tangent,150.677299), true );
//
//   Float64 mo;
//   hc->get_MidOrdinate(&mo);
//   TRY_TEST( IsEqual(mo,21.2657,0.001), true );
//
//   angle.Release();
//   hc->get_DE(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//
//   angle.Release();
//   hc->get_DE(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.2), true );
//
//   Float64 U;
//   hc->get_LongTangent(spEntry,&U);
//   TRY_TEST( IsEqual(U,0.0), true );
//   hc->get_LongTangent(spExit,&U);
//   TRY_TEST( IsEqual(U,133.6138,0.001), true );
//
//   Float64 V;
//   hc->get_ShortTangent(spEntry,&V);
//   TRY_TEST( IsEqual(V,0.0), true );
//   hc->get_ShortTangent(spExit,&V);
//   TRY_TEST( IsEqual(V,66.92168), true );
//
////   CComPtr<IPoint2d> cc;
////   hc->get_CC(&cc);
////   cc->get_X(&x);
////   cc->get_Y(&y);
////   TRY_TEST( IsEqual(x,492.89322), true );
////   TRY_TEST( IsEqual(y,500.0), true );
//
//   CComPtr<IPoint2d> spi;
//   hc->get_SPI(spEntry,&spi);
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x,488.1859,0.001), true );
//   TRY_TEST( IsEqual(y,1000.), true );
//
//   spi.Release();
//   hc->get_SPI(spExit,&spi);
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x,820.23,0.001), true );
//   TRY_TEST( IsEqual(y,879.7697,0.001), true );
//
//   brg.Release();
//   hc->get_CurveBkTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,0.0), true );
//
//   brg.Release();
//   hc->get_CurveFwdTangentBrg(&brg);
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,7*M_PI/4+0.2), true );
//
//   CComPtr<IPoint2d> pci;
//   hc->get_PCI(&pci);
//   pci->get_X(&x);
//   pci->get_Y(&y);
//   TRY_TEST( IsEqual(x, 638.8632,0.001), true );
//   TRY_TEST( IsEqual(y,1000.0000,0.001), true );
//
//   CComPtr<IPoint2d> ccc;
//   hc->get_CCC(&ccc);
//   ccc->get_X(&x);
//   ccc->get_Y(&y);
//   TRY_TEST( IsEqual(x,488.1859,0.001), true );
//   TRY_TEST( IsEqual(y,500.0,0.001), true );
//
//   hc->get_SpiralChord(spEntry,&chord);
//   TRY_TEST( IsEqual(chord,0.0), true );
//   hc->get_SpiralChord(spExit,&chord);
//   TRY_TEST( IsEqual(chord,199.6446,0.001), true );
//
//   angle.Release();
//   hc->get_DF(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//   angle.Release();
//   hc->get_DF(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666441,1e-6), true );
//
//   angle.Release();
//   hc->get_DH(spEntry,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0), true );
//   angle.Release();
//   hc->get_DH(spExit,&angle);
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1333559,1e-6), true );
//
//   hc->get_CurveLength(&val);
//   TRY_TEST(IsEqual(val,292.6991,0.001),true );
//
//   hc->get_TotalLength(&val);
//   TRY_TEST(IsEqual(val,492.6991,0.001),true );
//
//
//   //
//   // Bearing and Normal
//   //
//   // Point before curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Bearing(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0),true);
//   brg.Release();
//   TRY_TEST(hc->Normal(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Normal(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,3*PI_OVER_2),true);
//
//   // At CS
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Bearing(val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 + 0.2), true );
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Normal(val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 + 0.2 - PI_OVER_2), true );
//
//   // Point after curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4), true);
//   brg.Release();
//   TRY_TEST(hc->Normal(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,7*M_PI/4 - PI_OVER_2), true);
//
//   //
//   // Test PointOnCurve
//   //
//   Float64 px,py;
//   CComPtr<IPoint2d> pnt;
//   
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(-100.0,&pnt),S_OK); // Before TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x-100,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(0.0,&pnt),S_OK); // TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(0.0,&pnt),S_OK); // SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(val/2,&pnt),S_OK); // Half-way around the circular curve
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,632.45468),true);
//   TRY_TEST(IsEqual(py,978.73429),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(val,&pnt),S_OK); // CS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(val + 200./2,&pnt),S_OK); // Half-way along exit spiral
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,842.83815),true);
//   TRY_TEST(IsEqual(py,854.80525),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(val + 200.,&pnt),S_OK); // ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(val + 200 + 100,&pnt),S_OK); // 100 past ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x+100*cos(M_PI/4),px),true);
//   TRY_TEST(IsEqual(y-100*cos(M_PI/4),py),true);
//
//
//   //
//   // Test ProjectPoint
//   //
//   pnt.Release();
//   pnt.CoCreateInstance(CLSID_Point2d);
//   pnt->Move(300,1100);
//   CComPtr<IPoint2d> prjPoint;
//   Float64 distFromStart;
//   VARIANT_BOOL vbOnProjection;
//   TRY_TEST(hc->ProjectPoint(nullptr,&prjPoint, &distFromStart, &vbOnProjection),E_INVALIDARG);
//   TRY_TEST(hc->ProjectPoint(pnt,nullptr, &distFromStart, &vbOnProjection),E_POINTER);
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(300,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(500,1100);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 498.0291,0.001),true);
//   TRY_TEST(IsEqual(py, 999.9031,0.001),true);
//
//   pnt->Move(500,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 502.9471,0.001),true);
//   TRY_TEST(IsEqual(py, 999.7821,0.001),true);
//
//   pnt->Move(1000,1300);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 757.6433,0.001),true);
//   TRY_TEST(IsEqual(py, 921.1801,0.001),true);
//
//   pnt->Move(550,700);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 635.8301,0.001),true);
//   TRY_TEST(IsEqual(py, 977.7041,0.001),true);
//
//   pnt->Move(900,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 851.1779,0.001),true);
//   TRY_TEST(IsEqual(py, 847.1775,0.001),true);
//
//   pnt->Move(800,800);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 846.8054,0.001),true);
//   TRY_TEST(IsEqual(py, 851.1971,0.001),true);
//
//   pnt->Move(1100,500);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//
//   pnt->Move(1200,600);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//}

void CTestCircularCurve::Test4()
{
   CComPtr<ICircularCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);

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

   hc->putref_PBT(pbt);
   hc->putref_PI(pi);
   hc->putref_PFT(pft);
   hc->put_Radius(500);

   CurveDirectionType dir;
   hc->get_Direction(&dir);
   TRY_TEST( dir, cdLeft );

   pft->Move(1000,700);
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

   hc->get_Length(&val);
   TRY_TEST(IsEqual(val,392.6991,0.001),true );

   //
   // Bearing and Normal
   //
   // Point before curve
   brg.Release();
   TRY_TEST(hc->Bearing(-1,nullptr),E_POINTER);
   TRY_TEST(hc->Bearing(-1,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,0.0),true);
   brg.Release();
   TRY_TEST(hc->Normal(-1,nullptr),E_POINTER);
   TRY_TEST(hc->Normal(-1,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,3*PI_OVER_2),true);

   // At mid-point of curve
   brg.Release();
   hc->get_Length(&val);
   TRY_TEST(hc->Bearing(val/2,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4 + M_PI/8), true );
   brg.Release();
   hc->get_Length(&val);
   TRY_TEST(hc->Normal(val/2,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4 + M_PI/8 - PI_OVER_2), true );

   // Point after curve
   brg.Release();
   TRY_TEST(hc->Bearing(10000.,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4), true);
   brg.Release();
   TRY_TEST(hc->Normal(10000.,&brg),S_OK);
   brg->get_Value(&val);
   TRY_TEST( IsEqual(val,7*M_PI/4 - PI_OVER_2), true);

   //
   // Test PointOnCurve
   //
   Float64 px,py;
   CComPtr<IPoint2d> pnt;
   
   pnt.Release();
   TRY_TEST(hc->PointOnCurve(-100.0,&pnt),S_OK); // Before PC
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pc->get_X(&x);
   pc->get_Y(&y);
   TRY_TEST(IsEqual(x-100,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   TRY_TEST(hc->PointOnCurve(0.0,&pnt),S_OK); // PC
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pc->get_X(&x);
   pc->get_Y(&y);
   TRY_TEST(IsEqual(x,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   hc->get_Length(&val); // length of circular curve
   TRY_TEST(hc->PointOnCurve(val/2,&pnt),S_OK); // Half-way around the circular curve
   pnt->get_X(&px);
   pnt->get_Y(&py);
   TRY_TEST(IsEqual(px,684.23493),true);
   TRY_TEST(IsEqual(py,961.93977),true);

   pnt.Release();
   hc->get_Length(&val); // length of circular curve
   TRY_TEST(hc->PointOnCurve(val,&pnt),S_OK); // PT
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pt->get_X(&x);
   pt->get_Y(&y);
   TRY_TEST(IsEqual(x,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   hc->get_Length(&val); // length of circular curve
   TRY_TEST(hc->PointOnCurve(val,&pnt),S_OK); // PT
   pnt->get_X(&px);
   pnt->get_Y(&py);
   pt->get_X(&x);
   pt->get_Y(&y);
   TRY_TEST(IsEqual(x,px),true);
   TRY_TEST(IsEqual(y,py),true);

   pnt.Release();
   hc->get_Length(&val); // length of circular curve
   TRY_TEST(hc->PointOnCurve(val + 100,&pnt),S_OK); // 100 past PT
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
   TRY_TEST(hc->ProjectPoint(nullptr,&prjPoint, &distFromStart, &vbOnProjection),E_INVALIDARG);
   TRY_TEST(hc->ProjectPoint(pnt,nullptr, &distFromStart, &vbOnProjection),E_POINTER);
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 300.0),true);
   TRY_TEST(IsEqual(py,1000.0),true);

   pnt->Move(300,900);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 300.0),true);
   TRY_TEST(IsEqual(py,1000.0),true);

   pnt->Move(500,1100);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 498.8151,0.001),true);
   TRY_TEST(IsEqual(py, 999.9649,0.001),true);

   pnt->Move(500,900);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 501.7753,0.001),true);
   TRY_TEST(IsEqual(py, 999.9211,0.001),true);

   pnt->Move(1000,1300);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 760.5851,0.001),true);
   TRY_TEST(IsEqual(py, 922.3045,0.001),true);

   pnt->Move(550,700);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 630.1736,0.001),true);
   TRY_TEST(IsEqual(py, 980.7849,0.001),true);

   pnt->Move(900,900);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 850.0000,0.001),true);
   TRY_TEST(IsEqual(py, 850.0000,0.001),true);

   pnt->Move(800,800);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px, 850.0000,0.001),true);
   TRY_TEST(IsEqual(py, 850.0000,0.001),true);

   pnt->Move(1100,500);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px,1150.0),true);
   TRY_TEST(IsEqual(py,550.0),true);

   pnt->Move(1200,600);
   prjPoint.Release();
   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
   prjPoint->get_X(&px);
   prjPoint->get_Y(&py);
   TRY_TEST(IsEqual(px,1150.0),true);
   TRY_TEST(IsEqual(py,550.0),true);
}

//void CTestCircularCurve::Test5()
//{
//   CComPtr<ICircularCurve> hc;
//   TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve),S_OK);
//
//   /////////////////////////////////////////////////////
//   // Test a non-symmetrical spiral-curve-spiral to the left
//   // PBT = (0,1000)
//   // PI  = (700,1000)
//   // PFT = (1000,1300)
//   // R   = 500
//   // Entry Spiral Length = 100
//   // Exit Spiral Length = 200
//   CComPtr<IPoint2d> pbt, pi, pft;
//   pbt.CoCreateInstance(CLSID_Point2d);
//   pi.CoCreateInstance(CLSID_Point2d);
//   pft.CoCreateInstance(CLSID_Point2d);
//
//   pbt->Move(0,1000);
//   pi->Move(700,1000);
//   pft->Move(1000,1300);
//
//   TRY_TEST( hc->putref_PBT(nullptr), E_INVALIDARG );
//   TRY_TEST( hc->putref_PI(nullptr), E_INVALIDARG );
//   TRY_TEST( hc->putref_PFT(nullptr), E_INVALIDARG );
//
//   TRY_TEST( hc->putref_PBT(pbt), S_OK );
//   TRY_TEST( hc->putref_PI(pi), S_OK );
//   TRY_TEST( hc->putref_PFT(pft), S_OK );
//
//   CComPtr<IPoint2d> pnt;
//   TRY_TEST( hc->get_PBT(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PBT(&pnt), S_OK );
//   TRY_TEST( pnt.IsEqualObject(pbt), true );
//
//   pnt.Release();
//   TRY_TEST( hc->get_PI(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PI(&pnt), S_OK );
//   TRY_TEST( pnt.IsEqualObject(pi), true );
//
//   pnt.Release();
//   TRY_TEST( hc->get_PFT(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PFT(&pnt), S_OK );
//   TRY_TEST( pnt.IsEqualObject(pft), true );
//
//   TRY_TEST( hc->put_Radius(-1), E_INVALIDARG);
//   TRY_TEST( hc->put_Radius(0),  E_INVALIDARG);
//   TRY_TEST( hc->put_Radius(500), S_OK);
//
//   TRY_TEST( hc->put_SpiralLength(spEntry,-1), E_INVALIDARG );
//   TRY_TEST( hc->put_SpiralLength(spEntry,100), S_OK);
//
//   TRY_TEST( hc->put_SpiralLength(spExit,-1), E_INVALIDARG );
//   TRY_TEST( hc->put_SpiralLength(spExit,200), S_OK);
//
//   CurveDirectionType dir;
//   TRY_TEST( hc->get_Direction(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Direction(&dir), S_OK );
//   TRY_TEST( dir, cdLeft );
//
//   Float64 radius;
//   TRY_TEST( hc->get_Radius(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Radius(&radius), S_OK );
//   TRY_TEST(IsEqual(radius,500.),true);
//
//   CComPtr<IAngle> angle;
//   Float64 val;
//   TRY_TEST( hc->get_SpiralAngle(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SpiralAngle(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_SpiralAngle(spExit,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SpiralAngle(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.2), true );
//
//   Float64 x,y;
//   TRY_TEST( hc->get_X(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_X(spEntry,&x), S_OK );
//   TRY_TEST( IsEqual(x,99.900046285613), true );
//   TRY_TEST( hc->get_X(spExit,&x), S_OK );
//   TRY_TEST( IsEqual(x,199.20148011396), true );
//
//   TRY_TEST( hc->get_Y(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_Y(spEntry,&y), S_OK );
//   TRY_TEST( IsEqual(y,3.3309531383959), true );
//   TRY_TEST( hc->get_Y(spExit,&y), S_OK );
//   TRY_TEST( IsEqual(y,13.295286546224), true );
//
//   Float64 Q;
//   TRY_TEST( hc->get_Q(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_Q(spEntry,&Q), S_OK );
//   TRY_TEST( IsEqual(Q,0.83303,0.001), true );
//
//   TRY_TEST( hc->get_Q(spExit,&Q), S_OK );
//   TRY_TEST( IsEqual(Q,3.3286,0.001), true );
//
//   Float64 K;
//   TRY_TEST( hc->get_T(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_T(spEntry,&K), S_OK );
//   TRY_TEST( IsEqual(K,49.98329,0.001), true );
//
//   TRY_TEST( hc->get_T(spExit,&K), S_OK );
//   TRY_TEST( IsEqual(K,99.8668,0.001), true );
//
//   CComPtr<IDirection> brg;
//   Float64 brgVal;
//   TRY_TEST( hc->get_BkTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_BkTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,0.0), true );
//
//   brg.Release();
//   TRY_TEST( hc->get_FwdTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_FwdTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,M_PI/4), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_CurveAngle(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CurveAngle(&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,M_PI/4), true);
//
//   Float64 tangent;
//   TRY_TEST( hc->get_BkTangentLength(nullptr), E_POINTER );
//   TRY_TEST( hc->get_BkTangentLength(&tangent), S_OK );
//   TRY_TEST( IsEqual(tangent,260.96439), true );
//
//   TRY_TEST( hc->get_FwdTangentLength(nullptr), E_POINTER );
//   TRY_TEST( hc->get_FwdTangentLength(&tangent), S_OK );
//   TRY_TEST( IsEqual(tangent,304.82311), true );
//
//   CComPtr<IPoint2d> ts;
//   TRY_TEST( hc->get_TS(nullptr), E_POINTER );
//   TRY_TEST( hc->get_TS(&ts), S_OK );
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST( IsEqual(x,439.03561), true );
//   TRY_TEST( IsEqual(y,1000.), true );
//
//   CComPtr<IPoint2d> st;
//   TRY_TEST( hc->get_ST(nullptr), E_POINTER );
//   TRY_TEST( hc->get_ST(&st), S_OK );
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST( IsEqual(x, 915.5425,0.001), true );
//   TRY_TEST( IsEqual(y,1215.5425,0.001), true );
//
//   CComPtr<IPoint2d> sc;
//   TRY_TEST( hc->get_SC(nullptr), E_POINTER );
//   TRY_TEST( hc->get_SC(&sc), S_OK );
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST( IsEqual(x,538.93561,0.001), true );
//   TRY_TEST( IsEqual(y,1003.3310,0.001), true );
//
//   CComPtr<IPoint2d> cs;
//   TRY_TEST( hc->get_CS(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CS(&cs), S_OK );
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST( IsEqual(x, 765.2846,0.001), true );
//   TRY_TEST( IsEqual(y,1084.0870,0.001), true );
//
//   Float64 chord;
//   TRY_TEST( hc->get_Chord(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Chord(&chord), S_OK );
//   TRY_TEST( IsEqual(chord,240.323,0.001), true);
//
//   angle.Release();
//   TRY_TEST( hc->get_CircularCurveAngle(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CircularCurveAngle(&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.4854,0.001), true);
//
//   TRY_TEST( hc->get_Tangent(nullptr), E_POINTER );
//   TRY_TEST( hc->get_Tangent(&tangent), S_OK );
//   TRY_TEST( IsEqual(tangent,123.78966), true );
//
//   Float64 mo;
//   TRY_TEST( hc->get_MidOrdinate(nullptr), E_POINTER );
//   TRY_TEST( hc->get_MidOrdinate(&mo), S_OK );
//   TRY_TEST( IsEqual(mo,14.6537,0.001), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DE(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_DE(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DE(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.2), true );
//
//   Float64 U;
//   TRY_TEST( hc->get_LongTangent(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_LongTangent(spEntry,&U), S_OK );
//   TRY_TEST( IsEqual(U,66.701620764682), true );
//   TRY_TEST( hc->get_LongTangent(spExit,&U), S_OK );
//   TRY_TEST( IsEqual(U,133.6138,0.001), true );
//
//   Float64 V;
//   TRY_TEST( hc->get_ShortTangent(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_ShortTangent(spEntry,&V), S_OK );
//   TRY_TEST( IsEqual(V,33.365112106495), true );
//   TRY_TEST( hc->get_ShortTangent(spExit,&V), S_OK );
//   TRY_TEST( IsEqual(V,66.92168), true );
//
//   CComPtr<IPoint2d> cc;
//   TRY_TEST( hc->get_CC(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CC(&cc), S_OK );
//   cc->get_X(&x);
//   cc->get_Y(&y);
//   TRY_TEST( IsEqual(x, 439.03561,0.001), true );
//   TRY_TEST( IsEqual(y,1692.04939,0.001), true );
//
//   CComPtr<IPoint2d> spi;
//   TRY_TEST( hc->get_SPI(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SPI(spEntry,&spi), S_OK );
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x,505.738,0.001), true );
//   TRY_TEST( IsEqual(y,1000.0,0.001), true );
//
//   spi.Release();
//   TRY_TEST( hc->get_SPI(spExit,&spi), S_OK );
//   spi->get_X(&x);
//   spi->get_Y(&y);
//   TRY_TEST( IsEqual(x, 821.06328,0.001), true );
//   TRY_TEST( IsEqual(y,1121.06328,0.001), true );
//
//   brg.Release();
//   TRY_TEST( hc->get_CurveBkTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CurveBkTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,0.1), true );
//
//   brg.Release();
//   TRY_TEST( hc->get_CurveFwdTangentBrg(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CurveFwdTangentBrg(&brg), S_OK );
//   brg->get_Value(&brgVal);
//   TRY_TEST( IsEqual(brgVal,M_PI/4 - 0.2), true );
//
//   CComPtr<IPoint2d> pci;
//   TRY_TEST( hc->get_PCI(nullptr), E_POINTER );
//   TRY_TEST( hc->get_PCI(&pci), S_OK );
//   pci->get_X(&x);
//   pci->get_Y(&y);
//   TRY_TEST( IsEqual(x, 662.10687,0.001), true );
//   TRY_TEST( IsEqual(y,1015.6893,0.001), true );
//
//   CComPtr<IPoint2d> ccc;
//   TRY_TEST( hc->get_CCC(nullptr), E_POINTER );
//   TRY_TEST( hc->get_CCC(&ccc), S_OK );
//   ccc->get_X(&x);
//   ccc->get_Y(&y);
//   TRY_TEST( IsEqual(x, 489.0189,0.001), true );
//   TRY_TEST( IsEqual(y,1500.8330,0.001), true );
//
//   TRY_TEST( hc->get_SpiralChord(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_SpiralChord(spEntry,&chord), S_OK );
//   TRY_TEST( IsEqual(chord,99.955,0.001), true );
//   TRY_TEST( hc->get_SpiralChord(spExit,&chord), S_OK );
//   TRY_TEST( IsEqual(chord,199.6446,0.001), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DF(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_DF(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0333305,1e-6), true );
//   angle.Release();
//   TRY_TEST( hc->get_DF(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666441,1e-6), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DH(spEntry,nullptr), E_POINTER );
//   TRY_TEST( hc->get_DH(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666695,1e-6), true );
//   angle.Release();
//   TRY_TEST( hc->get_DH(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1333559,1e-6), true );
//
//   TRY_TEST(hc->get_CurveLength(nullptr),E_POINTER);
//   TRY_TEST(hc->get_CurveLength(&val),S_OK);
//   TRY_TEST(IsEqual(val,242.6991,0.001),true );
//
//   TRY_TEST(hc->get_TotalLength(nullptr),E_POINTER);
//   TRY_TEST(hc->get_TotalLength(&val),S_OK);
//   TRY_TEST(IsEqual(val,542.6991,0.001),true );
//
//   //
//   // Bearing and Normal
//   //
//   // Point before curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Bearing(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0),true);
//   brg.Release();
//   TRY_TEST(hc->Normal(-1,nullptr),E_POINTER);
//   TRY_TEST(hc->Normal(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,3*PI_OVER_2),true);
//
//   // At SC
//   brg.Release();
//   TRY_TEST(hc->Bearing(100.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val, 0.1), true );
//   brg.Release();
//   TRY_TEST(hc->Normal(100.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val, 3*PI_OVER_2 + 0.1), true );
//
//   // At CS
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Bearing(100+val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val, M_PI/4 - 0.2), true );
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Normal(100+val,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,3*PI_OVER_2 + M_PI/4 - 0.2), true );
//
//   // Mid-point of exit spiral
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Bearing(100+val+200/2,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val, M_PI/4 - 0.05), true );
//   brg.Release();
//   hc->get_CurveLength(&val);
//   TRY_TEST(hc->Normal(100+val+200/2,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,3*PI_OVER_2 + M_PI/4 - 0.05), true );
//
//   // Point after curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,M_PI/4), true);
//   brg.Release();
//   TRY_TEST(hc->Normal(10000.,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,3*PI_OVER_2 + M_PI/4), true);
//
//   //
//   // Test PointOnCurve
//   //
//   Float64 px,py;
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(0.0,nullptr),E_POINTER);
//   
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(-100.0,&pnt),S_OK); // Before TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x-100,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(0.0,&pnt),S_OK); // TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(50.0,&pnt),S_OK); // half-way between TS and SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px, 489.03248),true);
//   TRY_TEST(IsEqual(py,1000.41665),true);
//
//   pnt.Release();
//   TRY_TEST(hc->PointOnCurve(100.0,&pnt),S_OK); // SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val/2,&pnt),S_OK); // Half-way around the circular curve
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px, 657.03416),true);
//   TRY_TEST(IsEqual(py,1029.90747),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val,&pnt),S_OK); // CS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val + 200./2,&pnt),S_OK); // Half-way along exit spiral
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px, 843.67118),true);
//   TRY_TEST(IsEqual(py,1146.02779),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val + 200.,&pnt),S_OK); // ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(hc->PointOnCurve(100.0 + val + 200 + 100,&pnt),S_OK); // 100 past ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x+100*cos(M_PI/4),px),true);
//   TRY_TEST(IsEqual(y+100*cos(M_PI/4),py),true);
//
//   //
//   // Test ProjectPoint
//   //
//   pnt.Release();
//   pnt.CoCreateInstance(CLSID_Point2d);
//   pnt->Move(400,1100);
//   CComPtr<IPoint2d> prjPoint;
//   Float64 distFromStart;
//   VARIANT_BOOL vbOnProjection;
//   TRY_TEST(hc->ProjectPoint(nullptr,&prjPoint, &distFromStart, &vbOnProjection),E_INVALIDARG);
//   TRY_TEST(hc->ProjectPoint(pnt,nullptr, &distFromStart, &vbOnProjection),E_POINTER);
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 400.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(400,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 400.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(490,1100);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 492.8860,0.001),true);
//   TRY_TEST(IsEqual(py,1000.5206,0.001),true);
//
//   pnt->Move(490,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 487.6289,0.001),true);
//   TRY_TEST(IsEqual(py,1000.3825,0.001),true);
//
//   pnt->Move(650,1100);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 675.3606,0.001),true);
//   TRY_TEST(IsEqual(py,1036.8537,0.001),true);
//
//   pnt->Move(650,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 618.4197,0.001),true);
//   TRY_TEST(IsEqual(py,1017.8678,0.001),true);
//
//   pnt->Move(850,1200);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 874.3554,0.001),true);
//   TRY_TEST(IsEqual(py,1174.8135,0.001),true);
//
//   pnt->Move(1050,1000);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 877.3483,0.001),true);
//   TRY_TEST(IsEqual(py,1177.7145,0.001),true);
//
//   pnt->Move(1200,1300);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint, &distFromStart, &vbOnProjection),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1100.0),true);
//   TRY_TEST(IsEqual(py,1400.0),true);
//}

void CTestCircularCurve::TestEvents()
{
	CComPtr<ICircularCurve> hc;
	TRY_TEST(hc.CoCreateInstance(CLSID_CircularCurve), S_OK);

	CComPtr<IPoint2d> pbt, pi, pft;
	pbt.CoCreateInstance(CLSID_Point2d);
	pi.CoCreateInstance(CLSID_Point2d);
	pft.CoCreateInstance(CLSID_Point2d);

	pbt->Move(0, 1000);
	pi->Move(700, 1000);
	pft->Move(1000, 700);

	CComObject<CTestCircularCurve>* pTestCurve;
	CComObject<CTestCircularCurve>::CreateInstance(&pTestCurve);
	pTestCurve->AddRef();

	DWORD dwCookie;
	CComPtr<IUnknown> punk(pTestCurve);
	TRY_TEST(AtlAdvise(hc, punk, IID_ICircularCurveEvents, &dwCookie), S_OK);

	pTestCurve->InitEventTest();
	hc->putref_PBT(pbt);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	hc->putref_PI(pi);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	hc->putref_PFT(pft);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	hc->put_Radius(500);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	pbt->Move(0, 150);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	pi->Move(100, 150);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	pft->Move(150, 250);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	CComPtr<IPoint2d> newPBT, newPI, newPFT; // non-event firing points
	newPBT.CoCreateInstance(CLSID_Point2d);
	newPI.CoCreateInstance(CLSID_Point2d);
	newPFT.CoCreateInstance(CLSID_Point2d);
	newPBT->Move(0, 1000);
	newPI->Move(700, 1000);
	newPFT->Move(1000, 700);

	pTestCurve->InitEventTest();
	hc->putref_PBT(newPBT);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	hc->putref_PI(newPI);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	pTestCurve->InitEventTest();
	hc->putref_PFT(newPFT);
	TRY_TEST(pTestCurve->PassedEventTest(), true);

	TRY_TEST(AtlUnadvise(hc, IID_ICircularCurveEvents, dwCookie), S_OK);
	pTestCurve->Release();
}

STDMETHODIMP CTestCircularCurve::OnCircularCurveChanged(ICircularCurve* pp)
{
	//   ::MessageBox(nullptr,"OnCompoundCurveChanged","Event",MB_OK);
	Pass();
	return S_OK;
}
