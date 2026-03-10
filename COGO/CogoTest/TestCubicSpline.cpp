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

// TestCubicSpline.cpp: implementation of the TestCubicSpline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCubicSpline.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCubicSpline::CTestCubicSpline()
{

}

CTestCubicSpline::~CTestCubicSpline()
{

}

void CTestCubicSpline::Test()
{

   ////////////////////////////////////////////
   ////////////////////////////////////////////
   // Tests Needed
   // PointOnCurve with a point before and after the start/end of spline
   // DistanceFromStart with a point that projects onto the back/ahead tangents
   // Spline with no points (should be an angle point!)
   ////////////////////////////////////////////
   ////////////////////////////////////////////
   Float64 x,y;

   
   CComPtr<ICubicSpline> spline;
   TRY_TEST(spline.CoCreateInstance(CLSID_CubicSpline),S_OK);

   // test spline by evaluating it against a known solution
   // see http://math.fullerton.edu/mathews/n2003/splines/CubicSplinesMod/Links/CubicSplinesMod_lnk_4.html
   spline->Clear();
   spline->AddPoint(0,1);
   spline->AddPoint(1,0);
   spline->AddPoint(2,0);
   spline->AddPoint(3,1);
   spline->AddPoint(4,2);
   spline->AddPoint(5,2);
   spline->AddPoint(6,1);
   spline->put_StartDirection(CComVariant( atan2(-0.2,1) ));
   spline->put_EndDirection(CComVariant( atan2(-2.5,1) ));

   CComQIPtr<IPathElement> element(spline);

   CComPtr<IPoint2d> p;
   TRY_TEST(element->PointOnCurve(-1,nullptr), E_POINTER );

   // before the start of the spline... the input is the distance along the spline. before the spline we assume
   // a straight line tangent to the spline. the distance is measured along the line which is the hypotenuse
   // of a triangle, not the x-direction. this is why the correct answer is a little short of 1.2
   element->PointOnCurve(-1, &p); p->get_Y(&y); p.Release(); TRY_TEST(IsEqual(y, 1.1961161351381839), true);
   element->PointOnCurve( 0, &p); p->get_Y(&y); p.Release(); TRY_TEST(IsEqual(y, 1.0), true);
   //spline->Evaluate(1,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,0.0), true);
   //spline->Evaluate(2,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,0.0), true);
   //spline->Evaluate(3,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,1.0), true);
   //spline->Evaluate(4,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,2.0), true);
   //spline->Evaluate(5,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,2.0), true);
   //spline->Evaluate(6,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,1.0), true);
   //spline->Evaluate(7,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,-1.5), true);

   // test spline slope (derivative = bearing)
   Float64 dy;
   CComPtr<IDirection> d;
   TRY_TEST(element->GetBearing(-1,nullptr), E_POINTER );

   element->GetBearing(-1, &d); d->get_Value(&dy); d.Release(); TRY_TEST(IsEqual(tan(dy), -0.2), true);
   element->GetBearing( 0, &d); d->get_Value(&dy); d.Release(); TRY_TEST(IsEqual(tan(dy), -0.2), true);
   //spline->Slope(1,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.86628205128205149), true);
   //spline->Slope(2,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 0.66512820512820525), true);
   //spline->Slope(3,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 1.2057692307692305), true);
   //spline->Slope(4,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 0.51179487179487160), true);
   //spline->Slope(5,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.25294871794871754), true);
   //spline->Slope(6,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-2.5), true);
   //spline->Slope(7,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-2.5), true);
   element->GetBearing(50, &d); d->get_Value(&dy); d.Release(); TRY_TEST(IsEqual(tan(dy), -2.5), true);

   // spline length
   Float64 L;
   element->GetLength(&L);
   TRY_TEST( IsEqual(L,7.878,0.001), true);

   // test bearing at start and end... should match the start/end direction values
   CComPtr<IDirection> direction;
   TRY_TEST(element->GetBearing(0,nullptr),E_POINTER);
   TRY_TEST(element->GetBearing(0,&direction),S_OK);

   Float64 value;
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-0.2,tan(value),0.001), true );

   // before start
   direction.Release();
   TRY_TEST(element->GetBearing(-10,&direction),S_OK);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-0.2,tan(value),0.001), true );

   // check the normal
   direction.Release();
   TRY_TEST(element->GetNormal(0,nullptr),E_POINTER);
   TRY_TEST(element->GetNormal(0,&direction),S_OK);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/0.2,tan(value),0.001), true );

   direction.Release();
   TRY_TEST(element->GetNormal(-10,&direction),S_OK);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/0.2,tan(value),0.001), true );

   // bearing and normal check at end
   direction.Release();
   element->GetBearing(L,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-2.5,tan(value),0.001), true );
   
   direction.Release();
   element->GetBearing(L+10,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-2.5,tan(value),0.001), true );

   direction.Release();
   element->GetNormal(L,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/2.5,tan(value),0.001), true );

   direction.Release();
   element->GetNormal(L+10,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/2.5,tan(value),0.001), true );

   // project a point onto the spline
   p.Release();
   p.CoCreateInstance(CLSID_Point2d);
   p->Move(4,0);

   CComPtr<IPoint2d> pntOnSpline;
   Float64 distFromStart;
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(element->ProjectPoint(nullptr,&pntOnSpline, &distFromStart, &vbOnProjection),E_INVALIDARG);
   TRY_TEST(element->ProjectPoint(p,   nullptr, &distFromStart, &vbOnProjection),E_POINTER);
   TRY_TEST(element->ProjectPoint(p,&pntOnSpline, &distFromStart, &vbOnProjection),   S_OK);
   pntOnSpline->get_X(&x);
   pntOnSpline->get_Y(&y);

   TRY_TEST(IsEqual(x,2.9212265014648437),true);
   TRY_TEST(IsEqual(y,0.90555618284927675),true);
   TRY_TEST( IsEqual(distFromStart,3.8186,0.001), true );

   // project a point before start of spline
   p->Move(-10,0);
   pntOnSpline.Release();
   TRY_TEST(element->ProjectPoint(p,&pntOnSpline, &distFromStart, &vbOnProjection),S_OK);
   pntOnSpline->get_X(&x);
   pntOnSpline->get_Y(&y);

   TRY_TEST(IsEqual(x,-9.4230,0.001),true);
   TRY_TEST(IsEqual(y,2.8846,0.001),true);
   TRY_TEST( IsEqual(distFromStart,-9.6096,0.001), true );

   // project a point after start of spline
   p->Move(10,0);
   pntOnSpline.Release();
   TRY_TEST(element->ProjectPoint(p,&pntOnSpline, &distFromStart, &vbOnProjection),S_OK);
   pntOnSpline->get_X(&x);
   pntOnSpline->get_Y(&y);

   TRY_TEST(IsEqual(x,6.89655,0.001),true);
   TRY_TEST(IsEqual(y,-1.24137,0.001),true);
   TRY_TEST( IsEqual(distFromStart,10.292,0.001), true );

   // create a line and test intersections
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   CComPtr<IPoint2d> pntStart, pntEnd;
   pntStart.CoCreateInstance(CLSID_Point2d);
   pntEnd.CoCreateInstance(CLSID_Point2d);
   pntStart->Move(-10,1.0);
   pntEnd->Move( 10,1.0);
   line->ThroughPoints(pntStart,pntEnd);

   CComPtr<IPoint2dCollection> points;
   TRY_TEST(element->Intersect(nullptr,VARIANT_TRUE,VARIANT_TRUE,&points),E_INVALIDARG);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,nullptr),E_POINTER);
   TRY_TEST(element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   IndexType nPoints;
   points->get_Count(&nPoints);
   TRY_TEST( nPoints, 3 );

   p.Release();
   points->get_Item(0,&p);
   p->get_X(&x);
   p->get_Y(&y);  
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,1.0), true );

   p.Release();
   points->get_Item(1,&p);
   p->get_X(&x);
   p->get_Y(&y);
   TRY_TEST( IsEqual(x,3.0), true );
   TRY_TEST( IsEqual(y,1.0), true );

   p.Release();
   points->get_Item(2,&p);
   p->get_X(&x);
   p->get_Y(&y);
   TRY_TEST( IsEqual(x,6.0), true );
   TRY_TEST( IsEqual(y,1.0), true );

   // move the line and test intersections again
   pntStart->Move(-10,0.5);
   pntEnd->Move(10,0.5);
   line->ThroughPoints(pntStart,pntEnd);

   points.Release();
   element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points);
   points->get_Count(&nPoints);
   TRY_TEST( nPoints, 3 );

   p.Release();
   points->get_Item(0,&p);
   p->get_X(&x);
   p->get_Y(&y);  
   TRY_TEST( IsEqual(x,0.5665,0.001), true );
   TRY_TEST( IsEqual(y,0.5), true );

   p.Release();
   points->get_Item(1,&p);
   p->get_X(&x);
   p->get_Y(&y);
   TRY_TEST( IsEqual(x,2.5644,0.001), true );
   TRY_TEST( IsEqual(y,0.5), true );

   p.Release();
   points->get_Item(2,&p);
   p->get_X(&x);
   p->get_Y(&y);
   TRY_TEST( IsEqual(x,6.1999,0.001), true );
   TRY_TEST( IsEqual(y,0.5), true );

   // move the line and test intersections again
   pntStart->Move(0,1);
   pntEnd->Move(4,2);
   line->ThroughPoints(pntStart,pntEnd);

   points.Release();
   element->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points);
   points->get_Count(&nPoints);
   TRY_TEST( nPoints, 3 );

   p.Release();
   points->get_Item(0,&p);
   p->get_X(&x);
   p->get_Y(&y);  
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,1.0), true );

   p.Release();
   points->get_Item(1,&p);
   p->get_X(&x);
   p->get_Y(&y);
   TRY_TEST( IsEqual(x,4.0), true );
   TRY_TEST( IsEqual(y,2.0), true );

   p.Release();
   points->get_Item(2,&p);
   p->get_X(&x);
   p->get_Y(&y);
   TRY_TEST( IsEqual(x,4.3910,0.001), true );
   TRY_TEST( IsEqual(y,2.0977,0.001), true );

   //////////////////////////////////////
   // slope should remain unchanged if the spline is offset/moved
   spline->Clear();
   Float64 offset = 10;
   spline->AddPoint(0+offset,1+offset);
   spline->AddPoint(1+offset,0+offset);
   spline->AddPoint(2+offset,0+offset);
   spline->AddPoint(3+offset,1+offset);
   spline->AddPoint(4+offset,2+offset);
   spline->AddPoint(5+offset,2+offset);
   spline->AddPoint(6+offset,1+offset);
   spline->put_StartDirection(CComVariant( atan2(-0.2,1) ));
   spline->put_EndDirection(CComVariant( atan2(-2.5,1) ));

   // now test the spline as a cogo object

   // quarter circle
   Float64 angle;
   spline->Clear();
   Float64 R = 10;
   Float64 cx = 0;
   Float64 cy = 0;
   nPoints = 5;
   for ( IndexType i = 0; i < nPoints; i++ )
   {
      angle = (M_PI/2)*i/(nPoints-1);
      x = cx + R*cos(angle);
      y = cy + R*sin(angle);
      spline->AddPoint(x,y);
   }
   spline->put_StartDirection(CComVariant(PI_OVER_2));
   spline->put_EndDirection(CComVariant(M_PI));
   element->GetLength(&L);
   Float64 l = (2*M_PI*R)/4;
   TRY_TEST(IsEqual(L,l,0.1),true);

   // straight line
   spline->Clear();

   spline->AddPoint(0,0);
   spline->AddPoint(10,0);
   spline->put_StartDirection(CComVariant(0));
   spline->put_EndDirection(CComVariant(0));

   p.Release();
   element->PointOnCurve(2.,&p);
   p->get_X(&x);   TRY_TEST( IsEqual(x,2.0), true );
   p->get_Y(&y);   TRY_TEST( IsEqual(y,0.0), true );


   // curve line
   spline->Clear();

   spline->AddPoint(0,0);
   spline->AddPoint(10,10);
   spline->put_StartDirection(CComVariant(0));
   spline->put_EndDirection(CComVariant(M_PI/4));

   p.Release();
   element->PointOnCurve(0., &p);
   p->get_X(&x);   TRY_TEST(IsEqual(x, 0.0), true);
   p->get_Y(&y);   TRY_TEST(IsEqual(y, 0.0), true);

   p.Release();
   element->PointOnCurve(2., &p);
   p->get_X(&x);   TRY_TEST(IsEqual(x, 1.98136), true);
   p->get_Y(&y);   TRY_TEST(IsEqual(y, 0.23124), true);

   element->GetLength(&L);
   p.Release();
   element->PointOnCurve(L, &p);
   p->get_X(&x);   TRY_TEST(IsEqual(x, 10.0), true);
   p->get_Y(&y);   TRY_TEST(IsEqual(y, 10.0), true);

   // another curve line - this data comes from a real model that didn't work correctly
   // until we fixed the spline object
   spline->Clear();
   spline->AddPoint(25.950838, 47.9880235);
   spline->AddPoint(148.83656, 196.75139);
   spline->put_StartDirection(CComVariant(0.97387));
   spline->put_EndDirection(CComVariant(0.750248));

   p.Release();
   element->PointOnCurve(0, &p);
   p->get_X(&x);   TRY_TEST(IsEqual(x, 25.950838), true);
   p->get_Y(&y);   TRY_TEST(IsEqual(y, 47.9880235), true);

   element->GetLength(&L);
   p.Release();
   element->PointOnCurve(L, &p);
   p->get_X(&x);   TRY_TEST(IsEqual(x, 148.83656), true);
   p->get_Y(&y);   TRY_TEST(IsEqual(y, 196.75139), true);

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(spline);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICubicSpline ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CubicSpline,IID_ICubicSpline,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
