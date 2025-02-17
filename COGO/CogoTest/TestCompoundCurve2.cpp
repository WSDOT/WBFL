///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

// TestCompoundCurve.cpp: implementation of the CTestCompoundCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCompoundCurve.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void MakeLine(IPoint2d* pPoint,IDirection* pDirection,ILine2d** ppLine)
{
   Float64 angle;
   pDirection->get_Value(&angle);

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_X(cos(angle));
   v->put_Y(sin(angle));

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(pPoint,v);

   (*ppLine) = line;
   (*ppLine)->AddRef();
}

void CTestCompoundCurve::Test6()
{
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // PBT = (-1000,0)
   // PI  = (0,0)
   // PFT = (937.993610303, -346.652545108)
   // R   = 1000
   // Entry Spiral Length = 350
   // Exit Spiral Length = 150
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(-1000,0);
   pi->Move(0,0);
   pft->Move(937.993610303,-346.652545108);

   TRY_TEST( hc->put_PBT(pbt), S_OK );
   TRY_TEST( hc->put_PI(pi), S_OK );
   TRY_TEST( hc->put_PFT(pft), S_OK );


   TRY_TEST( hc->put_Radius(1000), S_OK);
   TRY_TEST( hc->put_SpiralLength(spEntry,350),S_OK);
   TRY_TEST( hc->put_SpiralLength(spExit,150), S_OK);

   CurveDirectionType dir;
   TRY_TEST( hc->get_Direction(&dir), S_OK );
   TRY_TEST( dir, cdRight );

   Float64 radius;
   TRY_TEST( hc->get_Radius(&radius), S_OK );
   TRY_TEST(IsEqual(radius,1000.),true);

   CComPtr<IAngle> angle;
   Float64 val;
   TRY_TEST( hc->get_SpiralAngle(spEntry,&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,0.175), true );

   angle.Release();
   TRY_TEST( hc->get_SpiralAngle(spExit,&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,0.075), true );

   Float64 x,y;
   TRY_TEST( hc->get_X(spEntry,&x), S_OK );
   TRY_TEST( IsEqual(x,348.929643656), true );
   TRY_TEST( hc->get_Y(spEntry,&y), S_OK );
   TRY_TEST( IsEqual(y,20.3720487046), true );

   TRY_TEST( hc->get_X(spExit,&x), S_OK );
   TRY_TEST( IsEqual(x,149.91564697), true );
   TRY_TEST( hc->get_Y(spExit,&y), S_OK );
   TRY_TEST( IsEqual(y,3.7484935732), true );

   Float64 Q;
   TRY_TEST( hc->get_Q(spEntry,&Q), S_OK );
   TRY_TEST( IsEqual(Q,5.0985876095420), true );

   TRY_TEST( hc->get_Q(spExit,&Q), S_OK );
   TRY_TEST( IsEqual(Q,0.93731168541681), true );

   Float64 K;
   TRY_TEST( hc->get_T(spEntry,&K), S_OK );
   TRY_TEST( IsEqual(K,174.82150606254), true );

   TRY_TEST( hc->get_T(spExit,&K), S_OK );
   TRY_TEST( IsEqual(K,74.985939697062), true );

   CComPtr<IDirection> brg;
   Float64 brgVal;
   TRY_TEST( hc->get_BkTangentBrg(&brg), S_OK );
   brg->get_Value(&brgVal);
   TRY_TEST( IsEqual(brgVal,0.0), true );

   brg.Release();
   TRY_TEST( hc->get_FwdTangentBrg(&brg), S_OK );
   brg->get_Value(&brgVal);
   TRY_TEST( IsEqual(brgVal,TWO_PI-0.354), true );

   angle.Release();
   TRY_TEST( hc->get_CurveAngle(&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,0.354), true);

   Float64 tangent;
   TRY_TEST( hc->get_BkTangentLength(&tangent), S_OK );
   TRY_TEST( IsEqual(tangent,342.6018,0.001), true );

   TRY_TEST( hc->get_FwdTangentLength(&tangent), S_OK );
   TRY_TEST( IsEqual(tangent,266.0296,0.001), true );

   CComPtr<IPoint2d> ts;
   TRY_TEST( hc->get_TS(&ts), S_OK );
   ts->get_X(&x);
   ts->get_Y(&y);
   TRY_TEST( IsEqual(x,-342.6018,0.001), true );
   TRY_TEST( IsEqual(y,0.), true );

   CComPtr<IPoint2d> st;
   TRY_TEST( hc->get_ST(&st), S_OK );
   st->get_X(&x);
   st->get_Y(&y);
   TRY_TEST( IsEqual(x,249.5341,0.001), true );
   TRY_TEST( IsEqual(y,-92.2198,0.001), true );

   CComPtr<IPoint2d> sc;
   TRY_TEST( hc->get_SC(&sc), S_OK );
   sc->get_X(&x);
   sc->get_Y(&y);
   TRY_TEST( IsEqual(x, 6.3284,0.0011), true );
   TRY_TEST( IsEqual(y,-20.3720,0.001), true );

   CComPtr<IPoint2d> cs;
   TRY_TEST( hc->get_CS(&cs), S_OK );
   cs->get_X(&x);
   cs->get_Y(&y);
   TRY_TEST( IsEqual(x,107.61475,0.001), true );
   TRY_TEST( IsEqual(y,-43.76727,0.001), true );

   Float64 chord;
   TRY_TEST( hc->get_Chord(&chord), S_OK );
   TRY_TEST( IsEqual(chord,103.95313,0.001), true);

   angle.Release();
   TRY_TEST( hc->get_CircularCurveAngle(&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,0.104), true);

   TRY_TEST( hc->get_Tangent(&tangent), S_OK );
   TRY_TEST( IsEqual(tangent,52.04692,0.001), true );

   Float64 mo;
   TRY_TEST( hc->get_MidOrdinate(&mo), S_OK );
   TRY_TEST( IsEqual(mo,1.35169,0.001), true );

   angle.Release();
   TRY_TEST( hc->get_DE(spEntry,&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,0.175), true );

   angle.Release();
   TRY_TEST( hc->get_DE(spExit,&angle), S_OK );
   angle->get_Value(&val);
   TRY_TEST( IsEqual(val,0.075), true );

   Float64 U;
   TRY_TEST( hc->get_LongTangent(spEntry,&U), S_OK );
   TRY_TEST( IsEqual(U,233.70873,0.001), true );
   TRY_TEST( hc->get_LongTangent(spExit,&U), S_OK );
   TRY_TEST( IsEqual(U,100.02948,0.001), true );

   Float64 V;
   TRY_TEST( hc->get_ShortTangent(spEntry,&V), S_OK );
   TRY_TEST( IsEqual(V,117.00802,0.001), true );
   TRY_TEST( hc->get_ShortTangent(spExit,&V), S_OK );
   TRY_TEST( IsEqual(V,50.026801,0.001), true );

   CComPtr<IPoint2d> cc;
   TRY_TEST( hc->get_CC(&cc), S_OK );
   cc->get_X(&x);
   cc->get_Y(&y);
   TRY_TEST( IsEqual(x, -342.60120,0.001), true );
   TRY_TEST( IsEqual(y,-1694.45569,0.001), true );

   CComPtr<IPoint2d> spi;
   TRY_TEST( hc->get_SPI(spEntry,&spi), S_OK );
   spi->get_X(&x);
   spi->get_Y(&y);
   TRY_TEST( IsEqual(x,-108.89246,0.001), true );
   TRY_TEST( IsEqual(y,0.0), true );

   spi.Release();
   TRY_TEST( hc->get_SPI(spExit,&spi), S_OK );
   spi->get_X(&x);
   spi->get_Y(&y);
   TRY_TEST( IsEqual(x,155.70708,0.001), true );
   TRY_TEST( IsEqual(y,-57.54437,0.001), true );

   brg.Release();
   TRY_TEST( hc->get_CurveBkTangentBrg(&brg), S_OK );
   brg->get_Value(&brgVal);
   TRY_TEST( IsEqual(brgVal,6.10818,0.001), true );

   brg.Release();
   TRY_TEST( hc->get_CurveFwdTangentBrg(&brg), S_OK );
   brg->get_Value(&brgVal);
   TRY_TEST( IsEqual(brgVal,6.00418,0.001), true );

   CComPtr<IPoint2d> pci;
   TRY_TEST( hc->get_PCI(&pci), S_OK );
   pci->get_X(&x);
   pci->get_Y(&y);
   TRY_TEST( IsEqual(x,57.580424,0.001), true );
   TRY_TEST( IsEqual(y,-29.43384,0.001), true );

   CComPtr<IPoint2d> ccc;
   TRY_TEST( hc->get_CCC(&ccc), S_OK );
   ccc->get_X(&x);
   ccc->get_Y(&y);
   TRY_TEST( IsEqual(x,-167.77969,0.001), true );
   TRY_TEST( IsEqual(y,-1005.0985,0.001), true );

//   TRY_TEST( hc->get_SpiralChord(spEntry,&chord), S_OK );
//   TRY_TEST( IsEqual(chord,349.52384), true );
//   TRY_TEST( hc->get_SpiralChord(spExit,&chord), S_OK );
//   TRY_TEST( IsEqual(chord,149.96250), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DF(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0333305,1e-6), true );
//   angle.Release();
//   TRY_TEST( hc->get_DF(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666441,1e-6), true );
//
//   angle.Release();
//   TRY_TEST( hc->get_DH(spEntry,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0666695,1e-6), true );
//   angle.Release();
//   TRY_TEST( hc->get_DH(spExit,&angle), S_OK );
//   angle->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.1333559,1e-6), true );
//
//   TRY_TEST(hc->get_CurveLength(&val),S_OK);
//   TRY_TEST(IsEqual(val,242.6991),true );
//
//   TRY_TEST(hc->get_TotalLength(&val),S_OK);
//   TRY_TEST(IsEqual(val,542.6991),true );
//
//   //
//   // Bearing and Normal
//   //
//   // Point before curve
//   brg.Release();
//   TRY_TEST(hc->Bearing(-1,&brg),S_OK);
//   brg->get_Value(&val);
//   TRY_TEST( IsEqual(val,0.0),true);
//   brg.Release();
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
//   TRY_TEST(element->PointOnCurve(-100.0,&pnt),S_OK); // Before TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x-100,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(element->PointOnCurve(0.0,&pnt),S_OK); // TS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   ts->get_X(&x);
//   ts->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   TRY_TEST(element->PointOnCurve(50.0,&pnt),S_OK); // half-way between TS and SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,489.03248),true);
//   TRY_TEST(IsEqual(py,999.58335),true);
//
//   pnt.Release();
//   TRY_TEST(element->PointOnCurve(100.0,&pnt),S_OK); // SC
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   sc->get_X(&x);
//   sc->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(element->PointOnCurve(100.0 + val/2,&pnt),S_OK); // Half-way around the circular curve
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,657.03416),true);
//   TRY_TEST(IsEqual(py,970.09253),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(element->PointOnCurve(100.0 + val,&pnt),S_OK); // CS
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   cs->get_X(&x);
//   cs->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(element->PointOnCurve(100.0 + val + 200./2,&pnt),S_OK); // Half-way along exit spiral
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   TRY_TEST(IsEqual(px,843.67118),true);
//   TRY_TEST(IsEqual(py,853.97221),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(element->PointOnCurve(100.0 + val + 200.,&pnt),S_OK); // ST
//   pnt->get_X(&px);
//   pnt->get_Y(&py);
//   st->get_X(&x);
//   st->get_Y(&y);
//   TRY_TEST(IsEqual(x,px),true);
//   TRY_TEST(IsEqual(y,py),true);
//
//   pnt.Release();
//   hc->get_CurveLength(&val); // length of circular curve
//   TRY_TEST(element->PointOnCurve(100.0 + val + 200 + 100,&pnt),S_OK); // 100 past ST
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
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(300,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 300.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   pnt->Move(500,1100);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 496.6567),true);
//   TRY_TEST(IsEqual(py, 999.3621),true);
//
//   pnt->Move(500,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 504.2128),true);
//   TRY_TEST(IsEqual(py, 999.0767),true);
//
//   pnt->Move(1000,1300);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 757.9660),true);
//   TRY_TEST(IsEqual(py, 920.6732),true);
//
//   pnt->Move(550,700);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 634.2900),true);
//   TRY_TEST(IsEqual(py, 977.5981),true);
//
//   pnt->Move(900,900);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 851.1983),true);
//   TRY_TEST(IsEqual(py, 847.0948),true);
//
//   pnt->Move(800,800);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 846.7079),true);
//   TRY_TEST(IsEqual(py, 851.2138),true);
//
//   pnt->Move(1100,500);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//
//   pnt->Move(1200,600);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1150.0),true);
//   TRY_TEST(IsEqual(py,550.0),true);
//
//   // This point should project onto both tangents.
//   // It is nearest the back tangent.
//   pnt->Move(200,0);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px, 200.0),true);
//   TRY_TEST(IsEqual(py,1000.0),true);
//
//   // This point should project onto both tangents.
//   // It is nearest the foward tangent.
//   pnt->Move(400,0);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,1050.0),true);
//   TRY_TEST(IsEqual(py, 650.0),true);
//
//   // This point should project onto both spirals.
//   // It is nearest the entry spiral.
//   pnt->Move(450,430);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,450.78715),true);
//   TRY_TEST(IsEqual(py,999.99459),true);
//
//   // This point should project onto both spirals.
//   // It is nearest the exit spiral.
//   pnt->Move(470,400);
//   prjPoint.Release();
//   TRY_TEST(hc->ProjectPoint(pnt,&prjPoint),S_OK);
//   prjPoint->get_X(&px);
//   prjPoint->get_Y(&py);
//   TRY_TEST(IsEqual(px,879.50334),true);
//   TRY_TEST(IsEqual(py,820.18857),true);
}

void CTestCompoundCurve::Test7()
{
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,1300)
   // R   = 500
   // Entry Spiral Length = 500
   // Exit Spiral Length = 700
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,1000);
   pi->Move(700,1000);
   pft->Move(1000,1300);

   TRY_TEST( hc->put_PBT(nullptr), E_INVALIDARG );
   TRY_TEST( hc->put_PI(nullptr), E_INVALIDARG );
   TRY_TEST( hc->put_PFT(nullptr), E_INVALIDARG );

   TRY_TEST( hc->put_PBT(pbt), S_OK );
   TRY_TEST( hc->put_PI(pi), S_OK );
   TRY_TEST( hc->put_PFT(pft), S_OK );

   TRY_TEST( hc->put_Radius(-1), E_INVALIDARG);
   TRY_TEST( hc->put_Radius(0),  E_INVALIDARG);
   TRY_TEST( hc->put_Radius(500), S_OK);

   TRY_TEST( hc->put_SpiralLength(spEntry,-1), E_INVALIDARG );
   TRY_TEST( hc->put_SpiralLength(spEntry,500), S_OK);

   TRY_TEST( hc->put_SpiralLength(spExit,-1), E_INVALIDARG );
   TRY_TEST( hc->put_SpiralLength(spExit,700), S_OK);

   CComPtr<IAngle> angle;
   TRY_TEST( hc->get_CircularCurveAngle(nullptr), E_POINTER );
   TRY_TEST( hc->get_CircularCurveAngle(&angle), E_FAIL );

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdLeft);
}

void CTestCompoundCurve::Test8a()
{
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (0,1000)
   // PI  = (700,1000)
   // PFT = (1000,1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
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
   hc->put_SpiralLength(spEntry,100);
   hc->put_SpiralLength(spExit,200);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdLeft);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE, &points), E_INVALIDARG);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 505.64225645686224),true);
   TRY_TEST(IsEqual(py, 1000.9854331731150),true);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 818.84459859920526),true);
   TRY_TEST(IsEqual(py, 1124.3794191254133),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 684.65428056880842),true);
   TRY_TEST(IsEqual(py, 1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 508.67043163106791),true);
   TRY_TEST(IsEqual(py, 1001.1261389033072),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 809.35182374575743),true);
   TRY_TEST(IsEqual(py, 1116.5668976835791),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(110,&cp1);
   element->PointOnCurve(140,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 548.87503670886008),true);
   TRY_TEST(IsEqual(py, 1004.4287172526595),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 578.53372538212068),true);
   TRY_TEST(IsEqual(py, 1008.9111895010718),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(150,&cp1);
   element->PointOnCurve(151,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 588.35360,0.001),true);
   TRY_TEST(IsEqual(py, 1010.79974,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 589.33345,0.001),true);
   TRY_TEST(IsEqual(py, 1010.99939,0.001),true);

   //// line tangent to entry spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247,0.001),true);
   TRY_TEST(IsEqual(py, 1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, 1000.41664, 0.001), true);

   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 474.03507484100646),true);
   TRY_TEST(IsEqual(py, 1000.1429151347374),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 484.03375483745350),true);
   TRY_TEST(IsEqual(py, 1000.3037411037024),true);

   // line tangent to exit spiral
   Float64 length;
   hc->get_TotalLength(&length);
   POC.Release();
   element->PointOnCurve(length-50,&POC);
   dir.Release();
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419),true);
   TRY_TEST(IsEqual(py, 1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419), true);
   TRY_TEST(IsEqual(py, 1180.3350144338078), true);


   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 883.61562936445966),true);
   TRY_TEST(IsEqual(py, 1183.8304112645556),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 890.74331577219289),true);
   TRY_TEST(IsEqual(py, 1190.8443728455015),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 703.20889,0.0011),true);
   TRY_TEST(IsEqual(py, 1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pbt,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.50118,0.001),true);
   TRY_TEST(IsEqual(py, 1119.94828,0.001),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.5011,0.001),true);
   TRY_TEST(IsEqual(py, 1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi1,pft);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.07029,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,900);
   cp2->Move(700,900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,1100);
   cp2->Move(700,1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 787.9642,0.001),true);
   TRY_TEST(IsEqual(py, 1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,1500);
   cp2->Move(700,1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1200.00),true);
   TRY_TEST(IsEqual(py, 1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(800,1000);
   cp2->Move(1100,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(600,1000);
   cp2->Move(900,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 617.6666,0.001),true);
   TRY_TEST(IsEqual(py, 1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(200,1000);
   cp2->Move(500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,  200.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);

   // again, but don't project curve
   cp1->Move(200,1000);
   cp2->Move(500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,1000);
   cp2->Move(1000,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(690,1000);
   cp2->Move(710,1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}

void CTestCompoundCurve::Test8b()
{
   // same as Test8a except the direction of the curve is reverse
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (1000,1300)
   // PI  = (700,1000)
   // PFT = (0,1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(1000,1300);
   pi->Move(700,1000);
   pft->Move(0,1000);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);

   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,200);
   hc->put_SpiralLength(spExit,100);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdRight);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE,&points), E_INVALIDARG);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 505.64225645686224),true);
   TRY_TEST(IsEqual(py, 1000.9854331731150),true);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 818.84459859920526),true);
   TRY_TEST(IsEqual(py, 1124.3794191254133),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 684.65428056880842),true);
   TRY_TEST(IsEqual(py, 1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 809.35182374575743),true);
   TRY_TEST(IsEqual(py, 1116.5668976835791),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 508.67043163106791),true);
   TRY_TEST(IsEqual(py, 1001.1261389033072),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length;
   hc->get_TotalLength(&length);
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(length-140,&cp1);
   element->PointOnCurve(length-110,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 578.53372538212068),true);
   TRY_TEST(IsEqual(py, 1008.9111895010718),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 548.87503670886008),true);
   TRY_TEST(IsEqual(py, 1004.4287172526595),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(length-151,&cp1);
   element->PointOnCurve(length-150,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints,2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 589.33345,0.001),true);
   TRY_TEST(IsEqual(py, 1010.99939,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 588.35360,0.001),true);
   TRY_TEST(IsEqual(py, 1010.79974,0.001),true);

   //// line tangent to exit spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(length-50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247,0.001),true);
   TRY_TEST(IsEqual(py, 1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, 1000.41664, 0.001), true);

   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints,2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 484.03375483745350),true);
   TRY_TEST(IsEqual(py, 1000.3037411037024),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 474.03507484100646),true);
   TRY_TEST(IsEqual(py, 1000.1429151347374),true);

   // line tangent to exit spiral
   POC.Release();
   element->PointOnCurve(50,&POC);
   dir.Release();
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419),true);
   TRY_TEST(IsEqual(py, 1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419), true);
   TRY_TEST(IsEqual(py, 1180.3350144338078), true);

   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 890.74331577219289),true);
   TRY_TEST(IsEqual(py, 1190.8443728455015),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 883.61562929997854),true);
   TRY_TEST(IsEqual(py, 1183.8304112013670),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 703.20889,0.0011),true);
   TRY_TEST(IsEqual(py, 1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pft,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.50118,0.001),true);
   TRY_TEST(IsEqual(py, 1119.94828,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.5011,0.001),true);
   TRY_TEST(IsEqual(py, 1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi2,pbt);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.07029,0.001),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,900);
   cp2->Move(700,900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,1100);
   cp2->Move(700,1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 787.9642,0.001),true);
   TRY_TEST(IsEqual(py, 1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,1500);
   cp2->Move(700,1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1200.00),true);
   TRY_TEST(IsEqual(py, 1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(800,1000);
   cp2->Move(1100,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(600,1000);
   cp2->Move(900,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 617.6666,0.001),true);
   TRY_TEST(IsEqual(py, 1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(200,1000);
   cp2->Move(500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,  200.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);

   // again, but don't project curve
   cp1->Move(200,1000);
   cp2->Move(500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,1000);
   cp2->Move(1000,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(690,1000);
   cp2->Move(710,1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}


void CTestCompoundCurve::Test9a()
{
   // This is the same as Test8a except the curve has been mirrored about the Y axis
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (0,1000)
   // PI  = (-700,1000)
   // PFT = (-1000,1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,1000);
   pi->Move(-700,1000);
   pft->Move(-1000,1300);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);

   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,100);
   hc->put_SpiralLength(spExit,200);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdRight);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE,&points), E_INVALIDARG);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -505.64225645686224),true);
   TRY_TEST(IsEqual(py, 1000.9854331731151),true);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -818.84459859920526),true);
   TRY_TEST(IsEqual(py, 1124.3794191254133),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-684.65428056880842),true);
   TRY_TEST(IsEqual(py, 1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -508.67043163106791),true);
   TRY_TEST(IsEqual(py, 1001.1261389033072),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-809.35182374575743),true);
   TRY_TEST(IsEqual(py, 1116.5668976835791),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(110,&cp1);
   element->PointOnCurve(140,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-548.87503670886008),true);
   TRY_TEST(IsEqual(py, 1004.4287172526595),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-578.53372538212068),true);
   TRY_TEST(IsEqual(py, 1008.9111895010718),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(150,&cp1);
   element->PointOnCurve(151,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-588.35360,0.001),true);
   TRY_TEST(IsEqual(py, 1010.79974,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-589.33345,0.001),true);
   TRY_TEST(IsEqual(py, 1010.99939,0.001),true);

   //// line tangent to entry spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-489.03247,0.001),true);
   TRY_TEST(IsEqual(py, 1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, 1000.41664, 0.001), true);


   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-474.03507484100646),true);
   TRY_TEST(IsEqual(py, 1000.1429151347374),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-484.03375483745350),true);
   TRY_TEST(IsEqual(py, 1000.3037411037024),true);

   // line tangent to exit spiral
   Float64 length;
   hc->get_TotalLength(&length);
   POC.Release();
   element->PointOnCurve(length-50,&POC);
   dir.Release();
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-880.04038989655419),true);
   TRY_TEST(IsEqual(py, 1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -880.04038989655419), true);
   TRY_TEST(IsEqual(py, 1180.3350144338078), true);

   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -883.61562936445966),true);
   TRY_TEST(IsEqual(py, 1183.8304112645556),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-890.74331577219289),true);
   TRY_TEST(IsEqual(py, 1190.8443728455015),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-703.20889,0.0011),true);
   TRY_TEST(IsEqual(py, 1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pbt,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.50118,0.001),true);
   TRY_TEST(IsEqual(py, 1119.94828,0.001),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.5011,0.001),true);
   TRY_TEST(IsEqual(py, 1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi1,pft);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.07029,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,900);
   cp2->Move(-700,900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,1100);
   cp2->Move(-700,1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-787.9642,0.001),true);
   TRY_TEST(IsEqual(py, 1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,1500);
   cp2->Move(-700,1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1200.00),true);
   TRY_TEST(IsEqual(py, 1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(-800,1000);
   cp2->Move(-1100,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(-600,1000);
   cp2->Move(-900,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-617.6666,0.001),true);
   TRY_TEST(IsEqual(py, 1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(-200,1000);
   cp2->Move(-500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -200.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);

   // again, but don't project curve
   cp1->Move(-200,1000);
   cp2->Move(-500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,1000);
   cp2->Move(-1000,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(-690,1000);
   cp2->Move(-710,1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}

void CTestCompoundCurve::Test9b()
{
   // same as Test9a except the direction of the curve is reverse
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (-1000,1300)
   // PI  = (-700,1000)
   // PFT = (0,1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(-1000,1300);
   pi->Move(-700,1000);
   pft->Move(0,1000);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);

   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,200);
   hc->put_SpiralLength(spExit,100);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdLeft);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE,&points), E_INVALIDARG);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -505.64225645686224),true);
   TRY_TEST(IsEqual(py, 1000.9854331731151),true);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -818.84459859920514),true);
   TRY_TEST(IsEqual(py, 1124.3794191254135),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-684.65428056880842),true);
   TRY_TEST(IsEqual(py, 1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-809.35182374575743),true);
   TRY_TEST(IsEqual(py, 1116.5668976835791),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, -508.67043163106791),true);
   TRY_TEST(IsEqual(py, 1001.1261389033072),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length;
   hc->get_TotalLength(&length);
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(length-140,&cp1);
   element->PointOnCurve(length-110,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-578.53372538212068),true);
   TRY_TEST(IsEqual(py, 1008.9111895010718),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-548.87503670886008),true);
   TRY_TEST(IsEqual(py, 1004.4287172526595),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(length-151,&cp1);
   element->PointOnCurve(length-150,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-589.33345,0.001),true);
   TRY_TEST(IsEqual(py, 1010.99939,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-588.35360,0.001),true);
   TRY_TEST(IsEqual(py, 1010.79974,0.001),true);

   //// line tangent to exit spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(length-50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-489.03247,0.001),true);
   TRY_TEST(IsEqual(py, 1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, 1000.41664, 0.001), true);

   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-484.03375483745350),true);
   TRY_TEST(IsEqual(py, 1000.3037411037024),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-474.03507484100646),true);
   TRY_TEST(IsEqual(py, 1000.1429151347374),true);

   // line tangent to exit spiral
   POC.Release();
   element->PointOnCurve(50,&POC);
   dir.Release();
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-880.04038989655419),true);
   TRY_TEST(IsEqual(py, 1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -880.04038989655419), true);
   TRY_TEST(IsEqual(py, 1180.3350144338078), true);

   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-890.74331577219289),true);
   TRY_TEST(IsEqual(py, 1190.8443728455015),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, -883.61562929997831),true);
   TRY_TEST(IsEqual(py, 1183.8304112013673),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-703.20889,0.0011),true);
   TRY_TEST(IsEqual(py, 1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pft,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.50118,0.001),true);
   TRY_TEST(IsEqual(py, 1119.94828,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.5011,0.001),true);
   TRY_TEST(IsEqual(py, 1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi2,pbt);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.07029,0.001),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py, 1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,900);
   cp2->Move(-700,900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,1100);
   cp2->Move(-700,1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-787.9642,0.001),true);
   TRY_TEST(IsEqual(py, 1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,1500);
   cp2->Move(-700,1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1200.00),true);
   TRY_TEST(IsEqual(py, 1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(-800,1000);
   cp2->Move(-1100,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(-600,1000);
   cp2->Move(-900,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-617.6666,0.001),true);
   TRY_TEST(IsEqual(py, 1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(-200,1000);
   cp2->Move(-500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -200.00),true);
   TRY_TEST(IsEqual(py, 1000.00),true);

   // again, but don't project curve
   cp1->Move(-200,1000);
   cp2->Move(-500,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,1000);
   cp2->Move(-1000,1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py, 1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py, 1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(-690,1000);
   cp2->Move(-710,1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}


void CTestCompoundCurve::Test10a()
{
   // same as Test8a except curve has been mirrored about the X axis
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (0,-1000)
   // PI  = (700,-1000)
   // PFT = (1000,-1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,-1000);
   pi->Move(700,-1000);
   pft->Move(1000,-1300);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);

   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,100);
   hc->put_SpiralLength(spExit,200);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdRight);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE,&points), E_INVALIDARG);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 505.64225645686224),true);
   TRY_TEST(IsEqual(py, -1000.9854331731150),true);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 818.84459859920514),true);
   TRY_TEST(IsEqual(py, -1124.3794191254133),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 684.65428056880842),true);
   TRY_TEST(IsEqual(py,-1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 508.67043163106791),true);
   TRY_TEST(IsEqual(py, -1001.1261389033072),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 809.35182374575743),true);
   TRY_TEST(IsEqual(py,-1116.5668976835791),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(110,&cp1);
   element->PointOnCurve(140,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 548.87503670886008),true);
   TRY_TEST(IsEqual(py,-1004.4287172526595),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 578.53372538212068),true);
   TRY_TEST(IsEqual(py,-1008.9111895010718),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(150,&cp1);
   element->PointOnCurve(151,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 588.35360,0.001),true);
   TRY_TEST(IsEqual(py,-1010.79974,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 589.33345,0.001),true);
   TRY_TEST(IsEqual(py,-1010.99939,0.001),true);

   //// line tangent to entry spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247,0.001),true);
   TRY_TEST(IsEqual(py,-1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, -1000.41664, 0.001), true);

   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 474.03507484100646),true);
   TRY_TEST(IsEqual(py,-1000.1429151347374),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 484.03375483745350),true);
   TRY_TEST(IsEqual(py,-1000.3037411037024),true);

   // line tangent to exit spiral
   Float64 length;
   hc->get_TotalLength(&length);
   POC.Release();
   element->PointOnCurve(length-50,&POC);
   dir.Release();
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419),true);
   TRY_TEST(IsEqual(py,-1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419), true);
   TRY_TEST(IsEqual(py, -1180.3350144338078), true);

   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 883.61562936445955),true);
   TRY_TEST(IsEqual(py, -1183.8304112645556),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 890.74331577219289),true);
   TRY_TEST(IsEqual(py,-1190.8443728455015),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 703.20889,0.0011),true);
   TRY_TEST(IsEqual(py,-1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pbt,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.50118,0.001),true);
   TRY_TEST(IsEqual(py,-1119.94828,0.001),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.5011,0.001),true);
   TRY_TEST(IsEqual(py,-1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi1,pft);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.07029,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,-900);
   cp2->Move(700,-900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,-1100);
   cp2->Move(700,-1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 787.9642,0.001),true);
   TRY_TEST(IsEqual(py,-1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,-1500);
   cp2->Move(700,-1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1200.00),true);
   TRY_TEST(IsEqual(py,-1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(800,-1000);
   cp2->Move(1100,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(600,-1000);
   cp2->Move(900,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 617.6666,0.001),true);
   TRY_TEST(IsEqual(py,-1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(200,-1000);
   cp2->Move(500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,  200.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);

   // again, but don't project curve
   cp1->Move(200,-1000);
   cp2->Move(500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,-1000);
   cp2->Move(1000,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(690,-1000);
   cp2->Move(710,-1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}


void CTestCompoundCurve::Test10b()
{
   // same as Test10a except the direction of the curve is reverse
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (1000,-1300)
   // PI  = (700,-1000)
   // PFT = (0,-1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(1000,-1300);
   pi->Move(700,-1000);
   pft->Move(0,-1000);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);

   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,200);
   hc->put_SpiralLength(spExit,100);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdLeft);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE,&points), E_INVALIDARG);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 505.64225645686224),true);
   TRY_TEST(IsEqual(py, -1000.9854331731150),true);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 818.84459859920514),true);
   TRY_TEST(IsEqual(py, -1124.3794191254133),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 684.65428056880842),true);
   TRY_TEST(IsEqual(py,-1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 809.35182374575743),true);
   TRY_TEST(IsEqual(py,-1116.5668976835791),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 508.67043163106791),true);
   TRY_TEST(IsEqual(py, -1001.1261389033072),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length;
   hc->get_TotalLength(&length);
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(length-140,&cp1);
   element->PointOnCurve(length-110,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 578.53372538212068),true);
   TRY_TEST(IsEqual(py,-1008.9111895010718),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 548.87503670886008),true);
   TRY_TEST(IsEqual(py,-1004.4287172526595),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(length-151,&cp1);
   element->PointOnCurve(length-150,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 589.33345,0.001),true);
   TRY_TEST(IsEqual(py,-1010.99939,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 588.35360,0.001),true);
   TRY_TEST(IsEqual(py,-1010.79974,0.001),true);

   //// line tangent to exit spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(length-50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247,0.001),true);
   TRY_TEST(IsEqual(py,-1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, -1000.41664, 0.001), true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, -1000.41664, 0.001), true);

   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 484.03375483745350),true);
   TRY_TEST(IsEqual(py,-1000.3037411037024),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 474.03507484100646),true);
   TRY_TEST(IsEqual(py,-1000.1429151347374),true);

   // line tangent to exit spiral
   POC.Release();
   element->PointOnCurve(50,&POC);
   dir.Release();
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419),true);
   TRY_TEST(IsEqual(py,-1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 880.04038989655419), true);
   TRY_TEST(IsEqual(py, -1180.3350144338078), true);

   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 890.74331577219289),true);
   TRY_TEST(IsEqual(py,-1190.8443728455015),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 883.61562929997842),true);
   TRY_TEST(IsEqual(py, -1183.8304112013670),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 703.20889,0.0011),true);
   TRY_TEST(IsEqual(py,-1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pft,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.50118,0.001),true);
   TRY_TEST(IsEqual(py,-1119.94828,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 813.5011,0.001),true);
   TRY_TEST(IsEqual(py,-1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi2,pbt);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.07029,0.001),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,-900);
   cp2->Move(700,-900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,-1100);
   cp2->Move(700,-1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 787.9642,0.001),true);
   TRY_TEST(IsEqual(py,-1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,-1500);
   cp2->Move(700,-1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1200.00),true);
   TRY_TEST(IsEqual(py,-1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(800,-1000);
   cp2->Move(1100,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(600,-1000);
   cp2->Move(900,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 617.6666,0.001),true);
   TRY_TEST(IsEqual(py,-1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(200,-1000);
   cp2->Move(500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,  200.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);

   // again, but don't project curve
   cp1->Move(200,-1000);
   cp2->Move(500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,-1000);
   cp2->Move(1000,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(690,-1000);
   cp2->Move(710,-1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}

void CTestCompoundCurve::Test11a()
{
   // same as Test8 except curve has been mirrored about the X axis and the Y axis
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the left
   // Spiral lengths overlap
   // PBT = (0,-1000)
   // PI  = (-700,-1000)
   // PFT = (-1000,-1300)
   // R   = 500
   // Entry Spiral Length = 100
   // Exit Spiral Length = 200
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(0,-1000);
   pi->Move(-700,-1000);
   pft->Move(-1000,-1300);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);

   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,100);
   hc->put_SpiralLength(spExit,200);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdLeft);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE,&points), E_INVALIDARG);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -505.64225645686224),true);
   TRY_TEST(IsEqual(py, -1000.9854331731150),true);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -818.84459859920526),true);
   TRY_TEST(IsEqual(py, -1124.3794191254133),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-684.65428056880842),true);
   TRY_TEST(IsEqual(py,-1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -508.67043163106791),true);
   TRY_TEST(IsEqual(py, -1001.1261389033072),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-809.35182374575743),true);
   TRY_TEST(IsEqual(py,-1116.5668976835791),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(110,&cp1);
   element->PointOnCurve(140,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-548.87503670886008),true);
   TRY_TEST(IsEqual(py,-1004.4287172526595),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-578.53372538212068),true);
   TRY_TEST(IsEqual(py,-1008.9111895010718),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(150,&cp1);
   element->PointOnCurve(151,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-588.35360,0.001),true);
   TRY_TEST(IsEqual(py,-1010.79974,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-589.33345,0.001),true);
   TRY_TEST(IsEqual(py,-1010.99939,0.001),true);

   //// line tangent to entry spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-489.03247,0.001),true);
   TRY_TEST(IsEqual(py,-1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, -1000.41664, 0.001), true);

   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-474.03507484100646),true);
   TRY_TEST(IsEqual(py,-1000.1429151347374),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-484.03375483745350),true);
   TRY_TEST(IsEqual(py,-1000.3037411037024),true);

   // line tangent to exit spiral
   Float64 length;
   hc->get_TotalLength(&length);
   POC.Release();
   element->PointOnCurve(length-50,&POC);
   dir.Release();
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-880.04038989655419),true);
   TRY_TEST(IsEqual(py,-1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -880.04038989655419), true);
   TRY_TEST(IsEqual(py, -1180.3350144338078), true);

   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -883.61562936445966),true);
   TRY_TEST(IsEqual(py, -1183.8304112645556),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-890.74331577219289),true);
   TRY_TEST(IsEqual(py,-1190.8443728455015),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-703.20889,0.0011),true);
   TRY_TEST(IsEqual(py,-1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pbt,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.50118,0.001),true);
   TRY_TEST(IsEqual(py,-1119.94828,0.001),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.5011,0.001),true);
   TRY_TEST(IsEqual(py,-1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi1,pft);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.07029,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,-900);
   cp2->Move(-700,-900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,-1100);
   cp2->Move(-700,-1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-787.9642,0.001),true);
   TRY_TEST(IsEqual(py,-1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,-1500);
   cp2->Move(-700,-1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1200.00),true);
   TRY_TEST(IsEqual(py,-1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(-800,-1000);
   cp2->Move(-1100,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(-600,-1000);
   cp2->Move(-900,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-617.6666,0.001),true);
   TRY_TEST(IsEqual(py,-1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(-200,-1000);
   cp2->Move(-500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -200.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);

   // again, but don't project curve
   cp1->Move(-200,-1000);
   cp2->Move(-500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,-1000);
   cp2->Move(-1000,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(-690,-1000);
   cp2->Move(-710,-1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}

void CTestCompoundCurve::Test11b()
{
   // same as Test10b except the direction of the curve is reverse
   CComPtr<ICompoundCurve> hc;
   TRY_TEST(hc.CoCreateInstance(CLSID_CompoundCurve),S_OK);

   CComQIPtr<IPathElement> element(hc);

   /////////////////////////////////////////////////////
   // Test a non-symmetrical spiral-curve-spiral to the right
   // Spiral lengths overlap
   // PBT = (-1000,-1300)
   // PI  = (-700,-1000)
   // PFT = (0,-1000)
   // R   = 500
   // Entry Spiral Length = 200
   // Exit Spiral Length = 100
   CComPtr<IPoint2d> pbt, pi, pft;
   pbt.CoCreateInstance(CLSID_Point2d);
   pi.CoCreateInstance(CLSID_Point2d);
   pft.CoCreateInstance(CLSID_Point2d);

   pbt->Move(-1000,-1300);
   pi->Move(-700,-1000);
   pft->Move(0,-1000);

   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);

   hc->put_Radius(500);
   hc->put_SpiralLength(spEntry,200);
   hc->put_SpiralLength(spExit,100);

   CurveDirectionType type;
   hc->get_Direction(&type);
   TRY_TEST(type, cdRight);

   // get some useful curve points
   CComPtr<IPoint2d> cc, spi1, spi2;
   hc->get_CC(&cc);
   hc->get_SPI(spEntry,&spi1);
   hc->get_SPI(spExit, &spi2);

   // create the line
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   // A couple of points to be used for results
   CComPtr<IPoint2d> p1, p2;
   CComPtr<IPoint2dCollection> points;
   IndexType nPoints;

   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(nullptr,VARIANT_FALSE,VARIANT_FALSE,&points), E_INVALIDARG);

   // make line intersect exit spiral
   line->ThroughPoints(cc,spi2);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   Float64 px,py;
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -505.64225645686224),true);
   TRY_TEST(IsEqual(py, -1000.9854331731150),true);

   // make line intersect entry spiral
   line->ThroughPoints(cc,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -818.84459859920526),true);
   TRY_TEST(IsEqual(py, -1124.3794191254133),true);

   // make line intersect circular curve
   line->ThroughPoints(cc,pi);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-684.65428056880842),true);
   TRY_TEST(IsEqual(py,-1040.6952164811710),true);

   // intersect both spirals at once
   line->ThroughPoints(spi1,spi2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-809.35182374575743),true);
   TRY_TEST(IsEqual(py,-1116.5668976835791),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, -508.67043163106791),true);
   TRY_TEST(IsEqual(py, -1001.1261389033072),true);

   // intersect circular curve in two places
   // first locate two points on the curve
   Float64 length;
   hc->get_TotalLength(&length);
   CComPtr<IPoint2d> cp1, cp2;
   element->PointOnCurve(length-140,&cp1);
   element->PointOnCurve(length-110,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-578.53372538212068),true);
   TRY_TEST(IsEqual(py,-1008.9111895010718),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-548.87503670886008),true);
   TRY_TEST(IsEqual(py,-1004.4287172526595),true);

   // intersect circular curve in two places 
   // (again, but make the intersection points really close)
   // first locate two points on the curve
   cp1.Release();
   cp2.Release();
   element->PointOnCurve(length-151,&cp1);
   element->PointOnCurve(length-150,&cp2);

   line->ThroughPoints(cp1,cp2);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-589.33345,0.001),true);
   TRY_TEST(IsEqual(py,-1010.99939,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-588.35360,0.001),true);
   TRY_TEST(IsEqual(py,-1010.79974,0.001),true);

   //// line tangent to exit spiral
   CComPtr<IPoint2d> POC;
   element->PointOnCurve(length-50,&POC);
   CComPtr<IDirection> dir;
   element->GetBearing(length-50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-489.03247,0.001),true);
   TRY_TEST(IsEqual(py,-1000.41664,0.001),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, -1000.41664, 0.001), true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -489.03247, 0.001), true);
   TRY_TEST(IsEqual(py, -1000.41664, 0.001), true);

   // intersect entry spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(length-45,&p1);
   element->PointOnCurve(length-35,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-484.03375483745350),true);
   TRY_TEST(IsEqual(py,-1000.3037411037024),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-474.03507484100646),true);
   TRY_TEST(IsEqual(py,-1000.1429151347374),true);

   // line tangent to exit spiral
   POC.Release();
   element->PointOnCurve(50,&POC);
   dir.Release();
   element->GetBearing(50,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-880.04038989655419),true);
   TRY_TEST(IsEqual(py,-1180.3350144338078),true);

   // reverse the direction of the tangent line
   dir->IncrementBy(CComVariant(M_PI));
   line.Release();
   MakeLine(POC, dir, &line);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line, VARIANT_TRUE, VARIANT_TRUE, &points), S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -880.04038989655419), true);
   TRY_TEST(IsEqual(py, -1180.3350144338078), true);

   // intersect exit spiral in 2 locations
   p1.Release();
   p2.Release();
   element->PointOnCurve(35,&p1);
   element->PointOnCurve(45,&p2);
   line->ThroughPoints(p1,p2);
   
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-890.74331577219289),true);
   TRY_TEST(IsEqual(py,-1190.8443728455015),true);

   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, -883.61562929997854),true);
   TRY_TEST(IsEqual(py, -1183.8304112013670),true);


   // line tangent to circular curve
   POC.Release();
   element->PointOnCurve(length/2,&POC);
   dir.Release();
   element->GetBearing(length/2,&dir);
   line.Release();
   MakeLine(POC,dir,&line);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-703.20889,0.0011),true);
   TRY_TEST(IsEqual(py,-1049.03367,0.001),true);

   // line intersect back tangent and exit spiral
   line->ThroughPoints(pft,spi1);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.50118,0.001),true);
   TRY_TEST(IsEqual(py,-1119.94828,0.001),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);

   // again, but don't project back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-813.5011,0.001),true);
   TRY_TEST(IsEqual(py,-1119.9482,0.001),true);

   // line intersect fwd tangent and entry spiral
   line->ThroughPoints(spi2,pbt);
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.07029,0.001),true);

   // again, but don't project ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-507.5005,0.001),true);
   TRY_TEST(IsEqual(py,-1001.0702,0.001),true);

   // no intersection with line parallel to entry tangent
   // outside of curve
   cp1->Move(0,-900);
   cp2->Move(-700,-900);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(0,-1100);
   cp2->Move(-700,-1100);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-787.9642,0.001),true);
   TRY_TEST(IsEqual(py,-1099.9999,0.001),true);

   // again, but on inside of curve (intersect with ahead tangent projected)
   cp1->Move(0,-1500);
   cp2->Move(-700,-1500);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1200.00),true);
   TRY_TEST(IsEqual(py,-1500.00),true);

   // again, but don't project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line parallel to exit tangent
   // outside of curve
   cp1->Move(-800,-1000);
   cp2->Move(-1100,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // again, but on inside of curve (intersect with curve)
   cp1->Move(-600,-1000);
   cp2->Move(-900,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-617.6666,0.001),true);
   TRY_TEST(IsEqual(py,-1017.6666,0.001),true);

   // again, but on inside of curve (intersect with projected tangent)
   cp1->Move(-200,-1000);
   cp2->Move(-500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, -200.00),true);
   TRY_TEST(IsEqual(py,-1000.00),true);

   // again, but don't project curve
   cp1->Move(-200,-1000);
   cp2->Move(-500,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // no intersection with line that cross both entry/entry tangent (inside of curve)
   cp1->Move(0,-1000);
   cp2->Move(-1000,-1300);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);

   // intersection with line that cross both entry/entry tangent (inside of curve) - project curve
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 2);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);
   
   points->get_Item(1, &p2);
   p2->get_X(&px);
   p2->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);

   // again, but project only back
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_TRUE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px, 0.00),true);
   TRY_TEST(IsEqual(py,-1000.),true);

   // again, but project only ahead
   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_FALSE,&points),S_OK);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 1);

   points->get_Item(0, &p1);
   p1->get_X(&px);
   p1->get_Y(&py);
   TRY_TEST(IsEqual(px,-1000.00),true);
   TRY_TEST(IsEqual(py,-1300.00),true);

   // no intersection with line that cross both entry/entry tangent (outside of curve)
   cp1->Move(-690,-1000);
   cp2->Move(-710,-1010);
   line->ThroughPoints(cp1,cp2);

   p1.Release();
   p2.Release();
   points.Release();
   TRY_TEST(element->Intersect(line,VARIANT_FALSE,VARIANT_FALSE,&points),S_FALSE);
   points->get_Count(&nPoints);
   TRY_TEST(nPoints, 0);
}
