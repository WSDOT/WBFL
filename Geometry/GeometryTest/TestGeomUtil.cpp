///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestGeomUtil.cpp: implementation of the CTestGeomUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestGeomUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestGeomUtil::CTestGeomUtil()
{

}

CTestGeomUtil::~CTestGeomUtil()
{

}

void CTestGeomUtil::Test()
{
   CComPtr<IGeomUtil> util;
   TRY_TEST( util.CoCreateInstance( CLSID_GeomUtil ), S_OK );

   TRY_TEST( util->putref_Point2dFactory(NULL), E_INVALIDARG );
   TRY_TEST( util->get_Point2dFactory(NULL), E_POINTER );

   TRY_TEST( util->putref_Point3dFactory(NULL), E_INVALIDARG );
   TRY_TEST( util->get_Point3dFactory(NULL), E_POINTER );

   TRY_TEST( util->putref_Line2dFactory(NULL), E_INVALIDARG );
   TRY_TEST( util->get_Line2dFactory(NULL), E_POINTER );

   TRY_TEST( util->putref_LineSegment2dFactory(NULL), E_INVALIDARG );
   TRY_TEST( util->get_LineSegment2dFactory(NULL), E_POINTER );

   // Test Interface Pointers
   CComPtr<IGeomUtil2d> geom2d;
   TRY_TEST(util->get_Geom2d(NULL), E_POINTER );
   TRY_TEST(util->get_Geom2d(&geom2d), S_OK );
   TRY_TEST(geom2d != NULL,true );

   CComPtr<IGeomUtil3d> geom3d;
   TRY_TEST(util->get_Geom3d(NULL), E_POINTER );
   TRY_TEST(util->get_Geom3d(&geom3d), S_OK );
   TRY_TEST(geom3d != NULL,true );

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   util->QueryInterface(&punk1);
   geom2d->QueryInterface(&punk2);
   geom3d->QueryInterface(&punk3);
   TRY_TEST( punk1 == punk2, true );
   TRY_TEST( punk1 == punk3, true );
   TRY_TEST( punk2 == punk3, true );

   Test2d();
   Test3d();
   TestISupportErrorInfo();
}

void CTestGeomUtil::Test2d()
{
   CComPtr<IGeomUtil2d> util2d;
   TRY_TEST( util2d.CoCreateInstance( CLSID_GeomUtil ), S_OK );

   //
   // Angle
   //
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance( CLSID_Point2d );
   p1->Move(3,8);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance( CLSID_Point2d );
   p2->Move(0,0);

   CComPtr<IPoint2d> p3;
   p3.CoCreateInstance( CLSID_Point2d );
   p3->Move(5,7);

   Float64 angle;
   TRY_TEST(util2d->Angle(NULL,p2,p3,&angle),E_INVALIDARG);
   TRY_TEST(util2d->Angle(p1,NULL,p2,&angle),E_INVALIDARG);
   TRY_TEST(util2d->Angle(p1,p2,NULL,&angle),E_INVALIDARG);
   TRY_TEST(util2d->Angle(p1,p2,p3,NULL),E_POINTER);
   TRY_TEST(util2d->Angle(p1,p2,p3,&angle),S_OK);
   TRY_TEST(IsEqual(angle,6.02170649147),true);
   TRY_TEST(util2d->Angle(p3,p2,p1,&angle),S_OK);
   TRY_TEST(IsEqual(angle,0.2614788157),true);

   TRY_TEST( util2d->Angle(p1,p1,p3,&angle),GEOMETRY_E_SAMEPOINTS);
   TRY_TEST( util2d->Angle(p1,p3,p3,&angle),GEOMETRY_E_SAMEPOINTS);

   p1->Move(10,0);
   p3->Move(0,10);
   TRY_TEST(util2d->Angle(p1,p2,p3,&angle),S_OK);
   TRY_TEST(IsEqual(angle,PI_OVER_2),true);
   TRY_TEST(util2d->Angle(p3,p2,p1,&angle),S_OK);
   TRY_TEST(IsEqual(angle,3*PI_OVER_2),true);

   p1->Move(-3,-8);
   p3->Move(-5,-7);
   TRY_TEST(util2d->Angle(p1,p2,p3,&angle),S_OK);
   TRY_TEST(IsEqual(angle,6.02170649147),true);
   TRY_TEST(util2d->Angle(p3,p2,p1,&angle),S_OK);
   TRY_TEST(IsEqual(angle,0.2614788157),true);

   //
   // AreLinesColinear
   //
   CComPtr<IPoint2d> p4;
   p4.CoCreateInstance( CLSID_Point2d );
   
   p1->Move( 5, 5);
   p2->Move(15,15);
   p3->Move(25,25);
   p4->Move(35,35);

   CComPtr<ILine2d> l1;
   l1.CoCreateInstance( CLSID_Line2d );
   l1->ThroughPoints(p1,p2);

   CComPtr<ILine2d> l2;
   l2.CoCreateInstance( CLSID_Line2d );
   l2->ThroughPoints(p3,p4);

   VARIANT_BOOL bColinear;
   TRY_TEST( util2d->AreLinesColinear(NULL,l2,&bColinear), E_INVALIDARG );
   TRY_TEST( util2d->AreLinesColinear(l1,NULL,&bColinear), E_INVALIDARG );
   TRY_TEST( util2d->AreLinesColinear(l1,l2,NULL), E_POINTER );
   TRY_TEST( util2d->AreLinesColinear(l1,l2,&bColinear), S_OK );
   TRY_TEST( bColinear, VARIANT_TRUE );

   l2->ThroughPoints(p4,p3); // Reverse l2
   TRY_TEST( util2d->AreLinesColinear(l1,l2,&bColinear), S_OK );
   TRY_TEST( bColinear, VARIANT_TRUE );

   p4->Move(3,4);
   l2->ThroughPoints(p3,p4);
   TRY_TEST( util2d->AreLinesColinear(l1,l2,&bColinear), S_OK );
   TRY_TEST( bColinear, VARIANT_FALSE );

   //
   // AreLineSegmentsParallel
   //
   CComPtr<ILineSegment2d> seg1;
   seg1.CoCreateInstance( CLSID_LineSegment2d );
   p1->Move(-10,-10);
   p2->Move(-20,-20);
   seg1->putref_StartPoint(p1);
   seg1->putref_EndPoint(p2);

   CComPtr<ILineSegment2d> seg2;
   seg2.CoCreateInstance( CLSID_LineSegment2d );
   p3->Move(  0,-20);
   p4->Move(-20,-40);
   seg2->putref_StartPoint(p3);
   seg2->putref_EndPoint(p4);

   VARIANT_BOOL bParallel;
   TRY_TEST( util2d->AreLineSegmentsParallel(seg1,NULL,&bParallel), E_INVALIDARG );
   TRY_TEST( util2d->AreLineSegmentsParallel(NULL,seg2,&bParallel), E_INVALIDARG );
   TRY_TEST( util2d->AreLineSegmentsParallel(seg1,seg2,NULL), E_POINTER );
   TRY_TEST( util2d->AreLineSegmentsParallel(seg1,seg2,&bParallel), S_OK );
   TRY_TEST( bParallel, VARIANT_TRUE );

   p4->Offset(3,5);
   TRY_TEST( util2d->AreLineSegmentsParallel(seg1,seg2,&bParallel), S_OK );
   TRY_TEST( bParallel, VARIANT_FALSE );

   //
   // AreLinesParallel
   //
   p1->Move(-10,-10);
   p2->Move(-20,-20);
   l1->ThroughPoints(p1,p2);

   p3->Move(  0,-20);
   p4->Move(-20,-40);
   l2->ThroughPoints(p3,p4);
   TRY_TEST( util2d->AreLinesParallel(l1,NULL,&bParallel), E_INVALIDARG );
   TRY_TEST( util2d->AreLinesParallel(NULL,l2,&bParallel), E_INVALIDARG );
   TRY_TEST( util2d->AreLinesParallel(l1,l2,NULL), E_POINTER );
   TRY_TEST( util2d->AreLinesParallel(l1,l2,&bParallel), S_OK );
   TRY_TEST( bParallel, VARIANT_TRUE );

   p4->Offset(3,5);
   l2->ThroughPoints(p3,p4);
   TRY_TEST( util2d->AreLinesParallel(l1,l2,&bParallel), S_OK );
   TRY_TEST( bParallel, VARIANT_FALSE );

   //
   // CircleCircleIntersect
   //
   CComPtr<ICircle> circle1;
   circle1.CoCreateInstance( CLSID_Circle );
   CComQIPtr<IXYPosition> xy1(circle1);
   xy1->Offset(0,0);
   circle1->put_Radius(5);

   CComPtr<ICircle> circle2;
   circle2.CoCreateInstance( CLSID_Circle );
   CComQIPtr<IXYPosition> xy2(circle2);
   xy2->Offset(5,5);
   circle2->put_Radius(5);

   CComQIPtr<IPoint2d> intersect1;
   CComQIPtr<IPoint2d> intersect2;

   short nIntersect;
   TRY_TEST( util2d->CircleCircleIntersect(NULL,circle2,&intersect1,&intersect2,&nIntersect), E_INVALIDARG );
   TRY_TEST( util2d->CircleCircleIntersect(circle1,NULL,&intersect1,&intersect2,&nIntersect), E_INVALIDARG );
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,NULL,&intersect2,&nIntersect), E_POINTER );
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,NULL,&nIntersect), E_POINTER );
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,NULL), E_POINTER );
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );

   TRY_TEST( nIntersect, 2 );

   Float64 x,y;
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   CComPtr<IPoint2d> c1;
   circle1->get_Center(&c1);
   c1->Move(0,0);
   circle1->put_Radius(5.0);

   CComPtr<IPoint2d> c2;
   circle2->get_Center(&c2);
   c2->Move(0,0);
   circle2->put_Radius(5.0);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 3 );

   circle2->put_Radius(10.0);
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 0 );
   
   c2->Move(100,100);
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 0 );

   intersect1.Release();
   intersect2.Release();
   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(10,0);
   circle2->put_Radius(5.0);
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 1 );
   

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   intersect1.Release();
   intersect2.Release();
   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(5,5);
   circle2->put_Radius(5.0);
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );


   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(-5,5);
   circle2->put_Radius(5.0);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0) && IsEqual(y,5.0) || IsEqual(x,-5.0) && IsEqual(y,0.0), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0) && IsEqual(y,5.0) || IsEqual(x,-5.0) && IsEqual(y,0.0), true );

   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(-5,-5);
   circle2->put_Radius(5.0);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->CircleCircleIntersect(circle2,circle1,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0) && IsEqual(y,-5.0) || IsEqual(x,-5.0) && IsEqual(y,0.0), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0) && IsEqual(y,-5.0) || IsEqual(x,-5.0) && IsEqual(y,0.0), true );

   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(5,-5);
   circle2->put_Radius(5.0);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->CircleCircleIntersect(circle2,circle1,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0) && IsEqual(y,-5.0) || IsEqual(x,5.0) && IsEqual(y,0.0), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0) && IsEqual(y,-5.0) || IsEqual(x,5.0) && IsEqual(y,0.0), true );

   intersect1.Release();
   intersect2.Release();
   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(0,5);
   circle2->put_Radius(5.0);
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,4.330127) && IsEqual(y,2.5) || IsEqual(x,-4.330127) && IsEqual(y,2.5), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,4.330127) && IsEqual(y,2.5) || IsEqual(x,-4.330127) && IsEqual(y,2.5), true );

   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(0,-5);
   circle2->put_Radius(5.0);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );


   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,4.330127) && IsEqual(y,-2.5) || IsEqual(x,-4.330127) && IsEqual(y,-2.5), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,4.330127) && IsEqual(y,-2.5) || IsEqual(x,-4.330127) && IsEqual(y,-2.5), true );

   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(5,0);
   circle2->put_Radius(5.0);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,2.5) && IsEqual(y,4.330127) || IsEqual(x,2.5) && IsEqual(y,-4.330127), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,2.5) && IsEqual(y,4.330127) || IsEqual(x,2.5) && IsEqual(y,-4.330127), true );

   c1->Move(0,0);
   circle1->put_Radius(5.0);
   c2->Move(-5,0);
   circle2->put_Radius(5.0);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->CircleCircleIntersect(circle1,circle2,&intersect1,&intersect2,&nIntersect), S_OK );
   TRY_TEST( nIntersect, 2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,-2.5) && IsEqual(y,4.330127) || IsEqual(x,-2.5) && IsEqual(y,-4.330127), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,-2.5) && IsEqual(y,4.330127) || IsEqual(x,-2.5) && IsEqual(y,-4.330127), true );

   //
   // CreateNormalLineThroughPoint
   //
   p1->Move(40,34);
   p2->Move(0,4);
   l1->ThroughPoints(p1,p2);
   p3->Move(-3,8);
   CComPtr<ILine2d> l3;
   TRY_TEST( util2d->CreateNormalLineThroughPoint(NULL,p3,&l3), E_INVALIDARG );
   TRY_TEST( util2d->CreateNormalLineThroughPoint(l1,NULL,&l3), E_INVALIDARG );
   TRY_TEST( util2d->CreateNormalLineThroughPoint(l1,p3,NULL),  E_POINTER );
   TRY_TEST( util2d->CreateNormalLineThroughPoint(l1,p3,&l3),   S_OK );

   Float64 c;
   CComPtr<IVector2d> v;
   l3->GetImplicit(&c,&v);

   TRY_TEST( IsEqual(c,2.4), true );
   v->get_X(&x);
   v->get_Y(&y);
   TRY_TEST( IsEqual(x,0.8), true );
   TRY_TEST( IsEqual(y,0.6), true );

   p3->Move(0,4);
   l3.Release();
   TRY_TEST( util2d->CreateNormalLineThroughPoint(l1,p3,&l3),   S_OK );

   v.Release();
   l3->GetImplicit(&c,&v);

   TRY_TEST( IsEqual(c,2.4), true );
   v->get_X(&x);
   v->get_Y(&y);
   TRY_TEST( IsEqual(x,0.8), true );
   TRY_TEST( IsEqual(y,0.6), true );

   //
   // CreateParallelLine
   //
   p1->Move(0,0);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);
   l2.Release();
   TRY_TEST( util2d->CreateParallelLine(NULL,10.0,&l2), E_INVALIDARG );
   TRY_TEST( util2d->CreateParallelLine(l1,10.0,NULL),    E_POINTER );
   TRY_TEST( util2d->CreateParallelLine(l1,10.0,&l2), S_OK );
   util2d->AreLinesParallel(l1,l2,&bParallel);
   TRY_TEST( bParallel, VARIANT_TRUE );

   p1->Move(0,0);
   p2->Move(10,0);
   l1->ThroughPoints(p1,p2);
   l2.Release();
   TRY_TEST( util2d->CreateParallelLine(l1,10.0,&l2), S_OK );
   util2d->AreLinesParallel(l1,l2,&bParallel);
   TRY_TEST( bParallel, VARIANT_TRUE );

   p1->Move(0,0);
   p2->Move(0,10);
   l1->ThroughPoints(p1,p2);
   l2.Release();
   TRY_TEST( util2d->CreateParallelLine(l1,10.0,&l2), S_OK );
   util2d->AreLinesParallel(l1,l2,&bParallel);
   TRY_TEST( bParallel, VARIANT_TRUE );

   //
   // CreateParallelLineSegment
   //
   p1->Move(0,0);
   p2->Move(10,10);
   seg1->putref_StartPoint(p1);
   seg1->putref_EndPoint(p2);
   seg2.Release();
   TRY_TEST( util2d->CreateParallelLineSegment(NULL,10.0,&seg2), E_INVALIDARG );
   TRY_TEST( util2d->CreateParallelLineSegment(seg1,10.0,NULL),    E_POINTER );
   TRY_TEST( util2d->CreateParallelLineSegment(seg1,10.0,&seg2), S_OK );
   util2d->AreLineSegmentsParallel(seg1,seg2,&bParallel);
   TRY_TEST( bParallel, VARIANT_TRUE );

   p1->Move(0,0);
   p2->Move(10,0);
   seg2.Release();
   TRY_TEST( util2d->CreateParallelLineSegment(seg1,10.0,&seg2), S_OK );
   util2d->AreLineSegmentsParallel(seg1,seg2,&bParallel);
   TRY_TEST( bParallel, VARIANT_TRUE );

   p1->Move(0,0);
   p2->Move(0,10);
   seg2.Release();
   TRY_TEST( util2d->CreateParallelLineSegment(seg1,10.0,&seg2), S_OK );
   util2d->AreLineSegmentsParallel(seg1,seg2,&bParallel);
   TRY_TEST( bParallel, VARIANT_TRUE );

   //
   // CreateParallelLineThroughPoint
   //
   p1->Move(10,10);
   p2->Move(20,30);
   l1->ThroughPoints(p1,p2);
   p3->Move(-10,15);
   l2.Release();
   TRY_TEST( util2d->CreateParallelLineThroughPoint(NULL,p3,&l2), E_INVALIDARG );
   TRY_TEST( util2d->CreateParallelLineThroughPoint(l1,NULL,&l2), E_INVALIDARG );
   TRY_TEST( util2d->CreateParallelLineThroughPoint(l1,p3,NULL), E_POINTER );
   TRY_TEST( util2d->CreateParallelLineThroughPoint(l1,p3,&l2), S_OK );
   util2d->AreLinesParallel(l1,l2,&bParallel);
   TRY_TEST( bParallel, VARIANT_TRUE );

   //
   // Distance
   //
   p1->Move(-20,30);
   p2->Move(80,45);
   Float64 dist;
   TRY_TEST( util2d->Distance(NULL,p2,&dist), E_INVALIDARG );
   TRY_TEST( util2d->Distance(p1,NULL,&dist), E_INVALIDARG );
   TRY_TEST( util2d->Distance(p1,p2,NULL),    E_POINTER );
   TRY_TEST( util2d->Distance(p1,p2,&dist),    S_OK );
   TRY_TEST( IsEqual(dist,101.118742), true );

   p2->Move(-20,30);
   TRY_TEST( util2d->Distance(p1,p2,&dist),    S_OK );
   TRY_TEST( IsEqual(dist,0.0), true );

   //
   // DivideArc
   //
   p1->Move(10,0);
   p2->Move(0,0);
   p3->Move(-10,0);
   CComPtr<IPoint2dCollection> points;
   TRY_TEST( util2d->DivideArc(NULL,p2,p3,4,&points), E_INVALIDARG );
   TRY_TEST( util2d->DivideArc(p1,NULL,p3,4,&points), E_INVALIDARG );
   TRY_TEST( util2d->DivideArc(p1,p2,NULL,4,&points), E_INVALIDARG );
   TRY_TEST( util2d->DivideArc(p1,p2,p3,-1,&points),  E_INVALIDARG );
   TRY_TEST( util2d->DivideArc(p1,p2,p3,4,NULL),      E_POINTER );

   TRY_TEST( util2d->DivideArc(p1,p2,p3,0,&points),   E_INVALIDARG );
   TRY_TEST( util2d->DivideArc(p1,p2,p3,1,&points),   S_OK );
   CollectionIndexType count;
   points->get_Count(&count);
   TRY_TEST( count, 2 );

   points.Release();
   TRY_TEST( util2d->DivideArc(p1,p2,p3,4,&points),   S_OK );

   points->get_Count(&count);
   TRY_TEST( count, 5 );

   CComPtr<IEnumPoint2d> Enum;
   points->get__Enum(&Enum);
   CComPtr<IPoint2d> point[5];
   ULONG fetched;
   Enum->Next(5, &point[0], &fetched);
   TRY_TEST( fetched, 5 );
   point[0]->get_X(&x);
   point[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 10.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   point[1]->get_X(&x);
   point[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 7.071,0.001), true );
   TRY_TEST( IsEqual(y, 7.071,0.001), true );

   point[2]->get_X(&x);
   point[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,  0.0), true );
   TRY_TEST( IsEqual(y, 10.0), true );

   point[3]->get_X(&x);
   point[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-7.071,0.001), true );
   TRY_TEST( IsEqual(y, 7.071,0.001), true );

   point[4]->get_X(&x);
   point[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-10.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   //
   // DivideLineSegment
   //
   p1->Move(10,10);
   p2->Move(30,30);
   seg1->putref_StartPoint(p1);
   seg1->putref_EndPoint(p2);

   points.Release();
   TRY_TEST( util2d->DivideLineSegment(NULL,4,&points), E_INVALIDARG );
   TRY_TEST( util2d->DivideLineSegment(seg1,-1,&points), E_INVALIDARG );
   TRY_TEST( util2d->DivideLineSegment(seg1,4,NULL), E_POINTER );
   TRY_TEST( util2d->DivideLineSegment(seg1,0,&points), E_INVALIDARG );

   points.Release();
   TRY_TEST( util2d->DivideLineSegment(seg1,1,&points), S_OK );
   points->get_Count(&count);
   TRY_TEST( count, 2 );

   points.Release();
   TRY_TEST( util2d->DivideLineSegment(seg1,4,&points), S_OK );
   points->get_Count(&count);
   TRY_TEST( count, 5 );

   point[0].Release();
   point[1].Release();
   point[2].Release();
   point[3].Release();
   point[4].Release();

   Enum.Release();
   points->get__Enum(&Enum);
   Enum->Next(5, &point[0], &fetched);
   TRY_TEST( fetched, 5 );
   point[0]->get_X(&x);
   point[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,10.0), true );

   point[1]->get_X(&x);
   point[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,15.0), true );
   TRY_TEST( IsEqual(y,15.0), true );

   point[2]->get_X(&x);
   point[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,20.0), true );
   TRY_TEST( IsEqual(y,20.0), true );

   point[3]->get_X(&x);
   point[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,25.0), true );
   TRY_TEST( IsEqual(y,25.0), true );

   point[4]->get_X(&x);
   point[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,30.0), true );
   TRY_TEST( IsEqual(y,30.0), true );


   //
   // DoesLineContainPoint
   //
   p1->Move(-10,-10);
   p2->Move(-50, 20);
   l1->ThroughPoints(p1,p2);
   p3->Move(-30,5);
   p4->Move(0,0);
   VARIANT_BOOL bContains;
   TRY_TEST( util2d->DoesLineContainPoint(NULL,p3,1.0e-6,&bContains), E_INVALIDARG );
   TRY_TEST( util2d->DoesLineContainPoint(l1,NULL,1.0e-6,&bContains), E_INVALIDARG );
   TRY_TEST( util2d->DoesLineContainPoint(l1,p3,1.0e-6,NULL),         E_POINTER );

   TRY_TEST( util2d->DoesLineContainPoint(l1,p3,1.0e-6,&bContains), S_OK );
   TRY_TEST( bContains, VARIANT_TRUE );

   TRY_TEST( util2d->DoesLineContainPoint(l1,p4,1.0e-6,&bContains), S_OK );
   TRY_TEST( bContains, VARIANT_FALSE );

   //
   // DoesLineSegmentContainPoint
   //
   p1->Move(-10,-10);
   p2->Move(-50, 20);
   seg1->putref_StartPoint(p1);
   seg1->putref_EndPoint(p2);
   p3->Move(-30,5);
   p4->Move(0,0);
   TRY_TEST( util2d->DoesLineSegmentContainPoint(NULL,p3,1.0e-6,&bContains),   E_INVALIDARG );
   TRY_TEST( util2d->DoesLineSegmentContainPoint(seg1,NULL,1.0e-6,&bContains), E_INVALIDARG );
   TRY_TEST( util2d->DoesLineSegmentContainPoint(seg1,p3,1.0e-6,NULL),         E_POINTER );

   TRY_TEST( util2d->DoesLineSegmentContainPoint(seg1,p3,1.0e-6,&bContains), S_OK );
   TRY_TEST( bContains, VARIANT_TRUE );

   TRY_TEST( util2d->DoesLineSegmentContainPoint(seg1,p4,1.0e-6,&bContains), S_OK );
   TRY_TEST( bContains, VARIANT_FALSE );

   TRY_TEST( util2d->DoesLineSegmentContainPoint(seg1,p1,1.0e-6,&bContains), S_OK );
   TRY_TEST( bContains, VARIANT_TRUE );

   TRY_TEST( util2d->DoesLineSegmentContainPoint(seg1,p2,1.0e-6,&bContains), S_OK );
   TRY_TEST( bContains, VARIANT_TRUE );

   //
   // GenerateCircle
   //
   p1->Move(0,0);
   points.Release();
   TRY_TEST( util2d->GenerateCircle(-1,p1,10.0,M_PI/4,&points), E_INVALIDARG );
   TRY_TEST( util2d->GenerateCircle(4,NULL,10.0,M_PI/4,&points), E_INVALIDARG );
   TRY_TEST( util2d->GenerateCircle(4,NULL,-10.0,M_PI/4,&points), E_INVALIDARG );
   TRY_TEST( util2d->GenerateCircle(4,p1,10.0,M_PI/4,NULL), E_POINTER );

   TRY_TEST( util2d->GenerateCircle(0,p1,10.0,M_PI/4,&points), S_OK );
   points->get_Count(&count);
   TRY_TEST( count, 0 );

   points.Release();
   TRY_TEST( util2d->GenerateCircle(4,p1,10.0,M_PI/4,&points), S_OK );
   points->get_Count(&count);
   TRY_TEST( count, 4 );

   point[0].Release();
   point[1].Release();
   point[2].Release();
   point[3].Release();

   Enum.Release();
   points->get__Enum(&Enum);
   Enum->Next(4, &point[0], &fetched);
   TRY_TEST( fetched, 4 );
   point[0]->get_X(&x);
   point[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 7.071,0.001), true );
   TRY_TEST( IsEqual(y, 7.071,0.001), true );

   point[1]->get_X(&x);
   point[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-7.071,0.001), true );
   TRY_TEST( IsEqual(y, 7.071,0.001), true );

   point[2]->get_X(&x);
   point[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-7.071,0.001), true );
   TRY_TEST( IsEqual(y,-7.071,0.001), true );

   point[3]->get_X(&x);
   point[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 7.071,0.001), true );
   TRY_TEST( IsEqual(y,-7.071,0.001), true );

   //
   // IntersectLineWithLineSegment
   //
   p1->Move(0,0);
   p2->Move(10,10);
   p3->Move(10,0);
   p4->Move(0,10);
   l1->ThroughPoints(p1,p2);
   seg1->putref_StartPoint(p3);
   seg1->putref_EndPoint(p4);

   intersect1.Release();
   TRY_TEST( util2d->IntersectLineWithLineSegment(NULL,seg1,&intersect1), E_INVALIDARG );
   TRY_TEST( util2d->IntersectLineWithLineSegment(l1,NULL,&intersect1), E_INVALIDARG );
   TRY_TEST( util2d->IntersectLineWithLineSegment(l1,seg1,NULL), E_POINTER );
   TRY_TEST( util2d->IntersectLineWithLineSegment(l1,seg1,&intersect1), S_OK );

   TRY_TEST( intersect1 != 0, true );
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   p4->Move(100,100);
   intersect1.Release();
   TRY_TEST( util2d->IntersectLineWithLineSegment(l1,seg1,&intersect1), S_OK );
   TRY_TEST( intersect1 != 0, true );

   p3->Move(0,0);
   p4->Move(10,10);
   intersect1.Release();
   TRY_TEST( util2d->IntersectLineWithLineSegment(l1,seg1,&intersect1), S_OK );
   TRY_TEST( intersect1 == 0, true );

   p3->Move(10,15);
   p4->Move(10,15);
   intersect1.Release();
   TRY_TEST( util2d->IntersectLineWithLineSegment(l1,seg1,&intersect1), S_OK );
   TRY_TEST( intersect1 == 0, true );

   p3->Move(5,5);
   p4->Move(5,5);
   intersect1.Release();
   TRY_TEST( util2d->IntersectLineWithLineSegment(l1,seg1,&intersect1), S_OK );
   TRY_TEST( intersect1 != 0, true );
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   //
   // IsLineParallelToLineSegment
   //
   p1->Move(0,0);
   p2->Move(10,10);
   p3->Move(10,0);
   p4->Move(0,10);
   l1->ThroughPoints(p1,p2);
   seg1->putref_StartPoint(p3);
   seg1->putref_EndPoint(p4);

   TRY_TEST( util2d->IsLineParallelToLineSegment(NULL,seg1,&bParallel), E_INVALIDARG );
   TRY_TEST( util2d->IsLineParallelToLineSegment(l1,NULL,&bParallel),   E_INVALIDARG );
   TRY_TEST( util2d->IsLineParallelToLineSegment(l1,seg1,NULL),         E_POINTER );
   TRY_TEST( util2d->IsLineParallelToLineSegment(l1,seg1,&bParallel),   S_OK );
   TRY_TEST( bParallel, VARIANT_FALSE);

   p3->Move(0,10);
   p4->Move(10,20);
   TRY_TEST( util2d->IsLineParallelToLineSegment(l1,seg1,&bParallel),   S_OK );
   TRY_TEST( bParallel, VARIANT_TRUE);

   //
   // LineCircleIntersect
   //
   p1->Move(0,0);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);

   p3->Move(5,5);
   circle1->putref_Center(p3);
   circle1->put_Radius(5.0);
   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->LineCircleIntersect(NULL,circle1,&intersect1,&intersect2,&nIntersect), E_INVALIDARG);
   TRY_TEST( util2d->LineCircleIntersect(l1,NULL,&intersect1,&intersect2,&nIntersect),      E_INVALIDARG);
   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,NULL,&intersect2,&nIntersect),          E_POINTER);
   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,&intersect1,NULL,&nIntersect),          E_POINTER);
   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,&intersect1,&intersect2,NULL),          E_POINTER);

   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,&intersect1,&intersect2,&nIntersect), S_OK);
   TRY_TEST( nIntersect,2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,1.464466) && IsEqual(y,1.464466) || IsEqual(x,8.53553) && IsEqual(y,8.53553), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,1.464466) && IsEqual(y,1.464466) || IsEqual(x,8.53553) && IsEqual(y,8.53553), true );

   p1->Move(0,100);
   p2->Move(10,110);
   l1->ThroughPoints(p1,p2);
  
   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,&intersect1,&intersect2,&nIntersect), S_OK);
   TRY_TEST( nIntersect,0 );

   p1->Move(0,10);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,&intersect1,&intersect2,&nIntersect), S_OK);
   TRY_TEST( nIntersect,1 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0) && IsEqual(y,10.0), true );

   p1->Move(5,0);
   p2->Move(5,10);
   l1->ThroughPoints(p1,p2);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,&intersect1,&intersect2,&nIntersect), S_OK);
   TRY_TEST( nIntersect,2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0) && IsEqual(y,0.0) || IsEqual(x,5.0) && IsEqual(y,10.0), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0) && IsEqual(y,0.0) || IsEqual(x,5.0) && IsEqual(y,10.0), true );

   p1->Move(10,0);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);

   intersect1.Release();
   intersect2.Release();
   TRY_TEST( util2d->LineCircleIntersect(l1,circle1,&intersect1,&intersect2,&nIntersect), S_OK);
   TRY_TEST( nIntersect,1 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0) && IsEqual(y,5.0), true );

   p1->Move(-50,-210);
   p2->Move(90,90);
   l1->ThroughPoints(p1,p2);
   p3->Move(0,0);
   circle1->putref_Center(p3);
   circle1->put_Radius(100.0);

   intersect1.Release();
   intersect2.Release();
   util2d->LineCircleIntersect(l1,circle1,&intersect1,&intersect2,&nIntersect);
   TRY_TEST( nIntersect,2 );

   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,1.337507) && IsEqual(y,-99.991055) || IsEqual(x,77.4946) && IsEqual(y,63.20273), true );
   intersect2->get_X(&x);
   intersect2->get_Y(&y);
   TRY_TEST( IsEqual(x,1.337507) && IsEqual(y,-99.991055) || IsEqual(x,77.4946) && IsEqual(y,63.20273), true );


   //
   // LineLineIntersect
   //
   p1->Move(10,0);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);

   p3->Move(20,0);
   p4->Move(20,10);
   l2->ThroughPoints(p3,p4);

   intersect1.Release();
   TRY_TEST( util2d->LineLineIntersect(NULL,l2,&intersect1), E_INVALIDARG );
   TRY_TEST( util2d->LineLineIntersect(l1,NULL,&intersect1), E_INVALIDARG );
   TRY_TEST( util2d->LineLineIntersect(l1,l2,NULL),          E_POINTER );

   TRY_TEST( util2d->LineLineIntersect(l1,l2,&intersect1), S_OK );
   TRY_TEST( intersect1 == 0, true );

   p1->Move(0,0);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);

   p3->Move(10,0);
   p4->Move(0,10);
   l2->ThroughPoints(p3,p4);
   intersect1.Release();
   TRY_TEST( util2d->LineLineIntersect(l1,l2,&intersect1), S_OK );
   TRY_TEST( intersect1 != 0, true );
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   //
   // Magnitude
   //
   Float64 mag;
   p1->Move(10,10);
   TRY_TEST( util2d->Magnitude(NULL,&mag), E_INVALIDARG );
   TRY_TEST( util2d->Magnitude(p1,NULL), E_POINTER );
   TRY_TEST( util2d->Magnitude(p1,&mag), S_OK );
   TRY_TEST( IsEqual(mag,14.1421356), true );

   //
   // PointOnLineNearest
   //
   p1->Move(0,10);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);
   p3->Move(5,5);
   p4.Release();
   TRY_TEST( util2d->PointOnLineNearest(NULL,p3,&p4), E_INVALIDARG );
   TRY_TEST( util2d->PointOnLineNearest(l1,NULL,&p4), E_INVALIDARG );
   TRY_TEST( util2d->PointOnLineNearest(l1,p3,NULL),    E_POINTER );
   TRY_TEST( util2d->PointOnLineNearest(l1,p3,&p4), S_OK );

   p4->get_X(&x);
   p4->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,10.0), true );

   p3->Move(20,10);
   p4.Release();
   TRY_TEST( util2d->PointOnLineNearest(l1,p3,&p4), S_OK );

   p4->get_X(&x);
   p4->get_Y(&y);
   TRY_TEST( IsEqual(x,20.0), true );
   TRY_TEST( IsEqual(y,10.0), true );


   p1->Move(0,0);
   p2->Move(10,10);
   l1->ThroughPoints(p1,p2);
   p3->Move(0,10);
   p4.Release();
   TRY_TEST( util2d->PointOnLineNearest(l1,p3,&p4), S_OK );

   p4->get_X(&x);
   p4->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   p1->Move(0,0);
   p2->Move(-10,10);
   l1->ThroughPoints(p1,p2);
   p3->Move(0,10);
   p4.Release();
   TRY_TEST( util2d->PointOnLineNearest(l1,p3,&p4), S_OK );

   p4->get_X(&x);
   p4->get_Y(&y);
   TRY_TEST( IsEqual(x,-5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   p1->Move(0,0);
   p2->Move(-10,-10);
   l1->ThroughPoints(p1,p2);
   p3->Move(0,-10);
   p4.Release();
   TRY_TEST( util2d->PointOnLineNearest(l1,p3,&p4), S_OK );

   p4->get_X(&x);
   p4->get_Y(&y);
   TRY_TEST( IsEqual(x,-5.0), true );
   TRY_TEST( IsEqual(y,-5.0), true );

   p1->Move(0,0);
   p2->Move(10,-10);
   l1->ThroughPoints(p1,p2);
   p3->Move(0,-10);
   p4.Release();
   TRY_TEST( util2d->PointOnLineNearest(l1,p3,&p4), S_OK );

   p4->get_X(&x);
   p4->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,-5.0), true );

   //
   // SegSegIntersect
   //
   p1->Move(10,0);
   p2->Move(10,10);
   seg1->putref_StartPoint(p1);
   seg1->putref_EndPoint(p2);

   p3->Move(20,0);
   p4->Move(20,10);
   seg2->putref_StartPoint(p3);
   seg2->putref_EndPoint(p4);

   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(NULL,seg2,&intersect1), E_INVALIDARG );
   TRY_TEST( util2d->SegSegIntersect(seg1,NULL,&intersect1), E_INVALIDARG );
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,NULL),        E_POINTER );

   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_FALSE );
   TRY_TEST( intersect1 == 0, true );

   p1->Move(0,0);
   p2->Move(10,10);
   p3->Move(10,0);
   p4->Move(0,10);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_OK );
   TRY_TEST( intersect1 != 0, true );
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   p1->Move(0,0);
   p2->Move(0,0);
   p3->Move(10,0);
   p4->Move(0,10);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_FALSE );
   TRY_TEST( intersect1 == 0, true );

   p1->Move(5,5);
   p2->Move(5,5);
   p3->Move(10,0);
   p4->Move(0,10);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_OK );
   TRY_TEST( intersect1 != 0, true );
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   p1->Move(0,0);
   p2->Move(10,10);
   p3->Move(0,10);
   p4->Move(0,10);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_FALSE );
   TRY_TEST( intersect1 == 0, true );

   p1->Move(0,0);
   p2->Move(10,10);
   p3->Move(5,5);
   p4->Move(5,5);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_OK );
   TRY_TEST( intersect1 != 0, true );
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,5.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   p1->Move(5,5);
   p2->Move(5,5);
   p3->Move(10,10);
   p4->Move(10,10);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_FALSE );
   TRY_TEST( intersect1 == 0, true );

   p1->Move(10,10);
   p2->Move(10,10);
   p3->Move(10,10);
   p4->Move(10,10);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_OK );
   TRY_TEST( intersect1 != 0, true );
   intersect1->get_X(&x);
   intersect1->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,10.0), true );

   p1->Move(0,0);
   p2->Move(4,4);
   p3->Move(0,10);
   p4->Move(10,0);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_FALSE );
   TRY_TEST( intersect1 == 0, true );

   p1->Move(0,0);
   p2->Move(4,4);
   p3->Move(0,10);
   p4->Move(5,4);
   intersect1.Release();
   TRY_TEST( util2d->SegSegIntersect(seg1,seg2,&intersect1), S_FALSE );
   TRY_TEST( intersect1 == 0, true );

   //
   // ShortestDistanceToPoint
   //
   p1->Move(10,10);
   p2->Move(20,20);
   l1->ThroughPoints(p1,p2);

   p3->Move(10,20);
   TRY_TEST( util2d->ShortestDistanceToPoint(NULL,p3,&dist), E_INVALIDARG );
   TRY_TEST( util2d->ShortestDistanceToPoint(l1,NULL,&dist), E_INVALIDARG );
   TRY_TEST( util2d->ShortestDistanceToPoint(l1,p3,NULL),    E_POINTER );
   TRY_TEST( util2d->ShortestDistanceToPoint(l1,p3,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-7.071,0.001), true ); // Point on left side (-)

   p3->Move(20,10);
   TRY_TEST( util2d->ShortestDistanceToPoint(l1,p3,&dist), S_OK );
   TRY_TEST( IsEqual(dist,7.071,0.001), true ); // Point on right side (+)
}

void CTestGeomUtil::Test3d()
{
   CComPtr<IGeomUtil3d> util3d;
   TRY_TEST( util3d.CoCreateInstance( CLSID_GeomUtil ), S_OK );

   // Distance
   CComPtr<IPoint3d> p1;
   p1.CoCreateInstance( CLSID_Point3d );
   p1->Move(10,10,10);

   CComPtr<IPoint3d> p2;
   p2.CoCreateInstance( CLSID_Point3d );
   p2->Move(30,40,50);

   Float64 dist;
   TRY_TEST( util3d->Distance(NULL,p2,&dist),E_INVALIDARG);
   TRY_TEST( util3d->Distance(p1,NULL,&dist),E_INVALIDARG);
   TRY_TEST( util3d->Distance(p1,p2,NULL),E_POINTER);
   TRY_TEST( util3d->Distance(p1,p2,&dist), S_OK );
   TRY_TEST( IsEqual(dist,53.851648), true );

   p2->Move(10,10,10);
   TRY_TEST( util3d->Distance(p1,p2,&dist), S_OK );
   TRY_TEST( IsEqual(dist,0.0), true );

   // Magnitude
   Float64 mag;
   p1->Move(10,10,10);
   TRY_TEST( util3d->Magnitude(NULL,&mag), E_INVALIDARG );
   TRY_TEST( util3d->Magnitude(p1,NULL), E_POINTER );
   TRY_TEST( util3d->Magnitude(p1,&mag), S_OK );
   TRY_TEST( IsEqual(mag,17.320508), true );
}

void CTestGeomUtil::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_GeomUtil ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IGeomUtil ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IGeomUtil2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IGeomUtil3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
