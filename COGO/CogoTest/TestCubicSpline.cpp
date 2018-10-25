///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
   // PointOnSpline with a point before and after the start/end of spline
   // DistanceFromStart with a point that projects onto the back/ahead tangents
   // Spline with no points (should be an angle point!)
   ////////////////////////////////////////////
   ////////////////////////////////////////////
   Float64 x,y;

   
   CComPtr<ICubicSpline> spline;
   TRY_TEST(spline.CoCreateInstance(CLSID_CubicSpline),S_OK);

   // there must be at least 2 points
   spline->AddPoint(1,1);
   TRY_TEST( spline->Evaluate(6,VARIANT_TRUE,VARIANT_TRUE,&y), COGO_E_CUBICSPLINEPOINTS );

   // spline points must be in increasing X order when an X-axis is placed between
   // the fist and last points
   spline->AddPoint(5,5);
   spline->AddPoint(3,1);
   TRY_TEST( spline->Evaluate(6,VARIANT_TRUE,VARIANT_TRUE,&y), COGO_E_CUBICSPLINEPOINTS );

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

   TRY_TEST(spline->Evaluate(-1,VARIANT_TRUE,VARIANT_TRUE,NULL), E_POINTER );

   spline->Evaluate(-1,VARIANT_TRUE,VARIANT_TRUE,&y); TRY_TEST( IsEqual(y,1.2), true);
   spline->Evaluate(0,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,1.0), true);
   spline->Evaluate(1,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,0.0), true);
   spline->Evaluate(2,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,0.0), true);
   spline->Evaluate(3,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,1.0), true);
   spline->Evaluate(4,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,2.0), true);
   spline->Evaluate(5,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,2.0), true);
   spline->Evaluate(6,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,1.0), true);
   spline->Evaluate(7,VARIANT_TRUE,VARIANT_TRUE,&y);  TRY_TEST( IsEqual(y,-1.5), true);

   // test spline slope (derivative = bearing)
   Float64 dy;
   TRY_TEST(spline->Slope(-1,VARIANT_TRUE,VARIANT_TRUE,NULL), E_POINTER );

   spline->Slope(-1,VARIANT_TRUE,VARIANT_TRUE,&dy); TRY_TEST( IsEqual(dy,-0.2), true);
   spline->Slope(0,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.2), true);
   spline->Slope(1,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.86628205128205149), true);
   spline->Slope(2,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 0.66512820512820525), true);
   spline->Slope(3,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 1.2057692307692305), true);
   spline->Slope(4,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 0.51179487179487160), true);
   spline->Slope(5,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.25294871794871754), true);
   spline->Slope(6,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-2.5), true);
   spline->Slope(7,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-2.5), true);

   // spline length
   Float64 L;
   spline->get_Length(&L);
   TRY_TEST( IsEqual(L,7.878,0.001), true);

   // test point on spline... get the point at a given distance
   // then evaluate the spline at x. y should be the same at all points
   for ( long j = 0; j < 12; j++ )
   {
      Float64 s = j*L/11;
      CComPtr<IPoint2d> pnt;
      spline->PointOnSpline(s,&pnt);

      pnt->get_X(&x);
      pnt->get_Y(&y);
      spline->Evaluate(x,VARIANT_FALSE,VARIANT_FALSE,&dy);
      TRY_TEST(IsEqual(y,dy),true);
   }

   // points are off of spline (and end points not projected)
   TRY_TEST( spline->Evaluate(-10,VARIANT_FALSE,VARIANT_FALSE,&y), E_INVALIDARG );
   TRY_TEST( spline->Evaluate( 10,VARIANT_FALSE,VARIANT_FALSE,&y), E_INVALIDARG );

   // points are off of spline (and end points not projected)
   TRY_TEST( spline->Slope(-10,VARIANT_FALSE,VARIANT_FALSE,&y), E_INVALIDARG );
   TRY_TEST( spline->Slope( 10,VARIANT_FALSE,VARIANT_FALSE,&y), E_INVALIDARG );

   // test bearing at start and end... should match the start/end direction values
   CComPtr<IDirection> direction;
   TRY_TEST(spline->Bearing(0,NULL),E_POINTER);
   TRY_TEST(spline->Bearing(0,&direction),S_OK);

   Float64 value;
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-0.2,tan(value),0.001), true );

   // before start
   direction.Release();
   TRY_TEST(spline->Bearing(-10,&direction),S_OK);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-0.2,tan(value),0.001), true );

   // check the normal
   direction.Release();
   TRY_TEST(spline->Normal(0,NULL),E_POINTER);
   TRY_TEST(spline->Normal(0,&direction),S_OK);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/0.2,tan(value),0.001), true );

   direction.Release();
   TRY_TEST(spline->Normal(-10,&direction),S_OK);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/0.2,tan(value),0.001), true );

   // bearing and normal check at end
   direction.Release();
   spline->Bearing(L,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-2.5,tan(value),0.001), true );
   
   direction.Release();
   spline->Bearing(L+10,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(-2.5,tan(value),0.001), true );

   direction.Release();
   spline->Normal(L,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/2.5,tan(value),0.001), true );

   direction.Release();
   spline->Normal(L+10,&direction);
   direction->get_Value(&value);
   TRY_TEST( IsEqual(1/2.5,tan(value),0.001), true );

   // project a point onto the spline
   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);
   p->Move(4,0);

   CComPtr<IPoint2d> pntOnSpline;
   TRY_TEST(spline->ProjectPoint(NULL,&pntOnSpline),E_INVALIDARG);
   TRY_TEST(spline->ProjectPoint(p,   NULL        ),E_POINTER);
   TRY_TEST(spline->ProjectPoint(p,&pntOnSpline),   S_OK);
   pntOnSpline->get_X(&x);
   pntOnSpline->get_Y(&y);

   TRY_TEST(IsEqual(x,2.9212265014648437),true);
   TRY_TEST(IsEqual(y,0.90555618284927675),true);

   // get distance from start of spline to the point p, projected onto the spline
   Float64 dist_from_start;
   TRY_TEST(spline->DistanceFromStart(NULL,&dist_from_start),E_INVALIDARG);
   TRY_TEST(spline->DistanceFromStart(p,   NULL),            E_POINTER);
   TRY_TEST(spline->DistanceFromStart(p,&dist_from_start),S_OK);
   TRY_TEST( IsEqual(dist_from_start,3.8186,0.001), true );

   // get distance from start of spline to the actual projected point (should be the same as before)
   spline->DistanceFromStart(pntOnSpline,&dist_from_start);
   TRY_TEST( IsEqual(dist_from_start,3.8186,0.001), true );

   // project a point before start of spline
   p->Move(-10,0);
   pntOnSpline.Release();
   TRY_TEST(spline->ProjectPoint(p,&pntOnSpline),S_OK);
   pntOnSpline->get_X(&x);
   pntOnSpline->get_Y(&y);

   TRY_TEST(IsEqual(x,-9.4230,0.001),true);
   TRY_TEST(IsEqual(y,2.8846,0.001),true);
   spline->DistanceFromStart(p,&dist_from_start);
   TRY_TEST( IsEqual(dist_from_start,-9.6096,0.001), true );
   spline->DistanceFromStart(pntOnSpline,&dist_from_start);
   TRY_TEST( IsEqual(dist_from_start,-9.6096,0.001), true );

   // project a point after start of spline
   p->Move(10,0);
   pntOnSpline.Release();
   TRY_TEST(spline->ProjectPoint(p,&pntOnSpline),S_OK);
   pntOnSpline->get_X(&x);
   pntOnSpline->get_Y(&y);

   TRY_TEST(IsEqual(x,6.89655,0.001),true);
   TRY_TEST(IsEqual(y,-1.24137,0.001),true);
   spline->DistanceFromStart(p,&dist_from_start);
   TRY_TEST( IsEqual(dist_from_start,10.292,0.001), true );
   spline->DistanceFromStart(pntOnSpline,&dist_from_start);
   TRY_TEST( IsEqual(dist_from_start,10.292,0.001), true );

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
   TRY_TEST(spline->Intersect(NULL,VARIANT_TRUE,VARIANT_TRUE,&points),E_INVALIDARG);
   TRY_TEST(spline->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,NULL),E_POINTER);
   TRY_TEST(spline->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points),S_OK);
   CollectionIndexType nPoints;
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
   spline->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points);
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
   spline->Intersect(line,VARIANT_TRUE,VARIANT_TRUE,&points);
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
   spline->Slope(-1+offset,VARIANT_TRUE,VARIANT_TRUE,&dy); TRY_TEST( IsEqual(dy,-0.2), true);
   spline->Slope(0+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.2), true);
   spline->Slope(1+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.86628205128205149), true);
   spline->Slope(2+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 0.66512820512820525), true);
   spline->Slope(3+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 1.2057692307692305), true);
   spline->Slope(4+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy, 0.51179487179487160), true);
   spline->Slope(5+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-0.25294871794871754), true);
   spline->Slope(6+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-2.5), true);
   spline->Slope(7+offset,VARIANT_TRUE,VARIANT_TRUE,&dy);  TRY_TEST( IsEqual(dy,-2.5), true);

   // now test the spline as a cogo object

   // quarter circle
   Float64 angle;
   spline->Clear();
   Float64 R = 10;
   Float64 cx = 0;
   Float64 cy = 0;
   nPoints = 5;
   for ( CollectionIndexType i = 0; i < nPoints; i++ )
   {
      angle = (M_PI/2)*i/(nPoints-1);
      x = cx + R*cos(angle);
      y = cy + R*sin(angle);
      spline->AddPoint(x,y);
   }
   spline->put_StartDirection(CComVariant(PI_OVER_2));
   spline->put_EndDirection(CComVariant(M_PI));
   spline->get_Length(&L);
   Float64 l = (2*M_PI*R)/4;
   TRY_TEST(IsEqual(L,l,0.1),true);

   for ( CollectionIndexType i = 0; i < 2*nPoints; i++ )
   {
      angle = (M_PI/2)*i/(2*nPoints-1);
      x = cx + R*cos(angle);
      y = cy + R*sin(angle);
      
      spline->Evaluate(x,VARIANT_FALSE,VARIANT_FALSE,&dy);
      TRY_TEST(IsEqual(y,dy,0.1),true);
   }

   // straignt line
   spline->Clear();

   spline->AddPoint(0,0);
   spline->AddPoint(10,0);
   spline->put_StartDirection(CComVariant(0));
   spline->put_EndDirection(CComVariant(0));

   p.Release();
   spline->PointOnSpline(2.,&p);
   p->get_X(&x);   TRY_TEST( IsEqual(x,2.0), true );
   p->get_Y(&y);   TRY_TEST( IsEqual(y,0.0), true );


   // curve line
   spline->Clear();

   spline->AddPoint(0,0);
   spline->AddPoint(10,10);
   spline->put_StartDirection(CComVariant(0));
   spline->put_EndDirection(CComVariant(M_PI/4));

   p.Release();
   spline->PointOnSpline(2.,&p);
   p->get_X(&x);   TRY_TEST( IsEqual(x,1.9813,0.001), true );
   p->get_Y(&y);   TRY_TEST( IsEqual(y,0.2312,0.001), true );



   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(spline);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICubicSpline ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_CubicSpline,IID_ICubicSpline,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_CubicSpline,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
