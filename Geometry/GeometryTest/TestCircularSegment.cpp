///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// TestCircularSegment.cpp: implementation of the CTestCircularSegment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCircularSegment.h"
#include <ObjSafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCircularSegment::CTestCircularSegment()
{

}

CTestCircularSegment::~CTestCircularSegment()
{

}

void CTestCircularSegment::Test()
{
   TestICircularSegment();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
   TestIObjectSafety();
   OtherTests();
}

void CTestCircularSegment::TestICircularSegment()
{
   // Verify initialization
   CComPtr<ICircularSegment> circseg;
   TRY_TEST( circseg.CoCreateInstance(CLSID_CircularSegment), S_OK );

   // Check radius, mid ordinate, and center point, hook point, and rotation
   // All should be zero
   Float64 radius;
   CComPtr<IPoint2d> center;
   CComPtr<IPoint2d> hook;
   Float64 mo;
   Float64 x,y;
   Float64 rotation;
   Float64 ia;

   TRY_TEST(circseg->get_Radius(nullptr), E_POINTER);
   TRY_TEST(circseg->get_Radius(&radius), S_OK);
   TRY_TEST(IsZero(radius),true);

   TRY_TEST(circseg->get_Center(nullptr),E_POINTER);
   TRY_TEST(circseg->get_Center(&center),S_OK);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsZero(x),true);
   TRY_TEST(IsZero(y),true);

   TRY_TEST(circseg->get_MidOrdinate(nullptr),E_POINTER);
   TRY_TEST(circseg->get_MidOrdinate(&mo),S_OK);
   TRY_TEST(IsZero(mo),true);

   TRY_TEST(circseg->get_HookPoint(nullptr),E_POINTER);
   TRY_TEST(circseg->get_HookPoint(&hook),S_OK);
   hook->get_X(&x);
   hook->get_Y(&y);
   TRY_TEST(IsZero(x),true);
   TRY_TEST(IsZero(y),true);

   TRY_TEST(circseg->get_Rotation(nullptr), E_POINTER);
   TRY_TEST(circseg->get_Rotation(&rotation), S_OK);
   TRY_TEST(IsZero(rotation),true);

   TRY_TEST(circseg->get_InteriorAngle(nullptr),E_POINTER);
   TRY_TEST(circseg->get_InteriorAngle(&ia),S_OK);
   TRY_TEST(IsZero(ia),true);

   // Testing setting/reading properties
   TRY_TEST(circseg->put_Radius(-10),GEOMETRY_E_RADIUS);
   TRY_TEST(circseg->put_Radius(20),S_OK);
   TRY_TEST(circseg->get_Radius(&radius),S_OK);
   TRY_TEST(IsEqual(radius,20.0),true);

   TRY_TEST(circseg->put_MidOrdinate(-10),GEOMETRY_E_MIDORDINATE);
   TRY_TEST(circseg->put_MidOrdinate(10),S_OK);
   TRY_TEST(circseg->get_MidOrdinate(&mo),S_OK);
   TRY_TEST(IsEqual(mo,10.0),true);

   // If the radius is too small, the mid ordinate is adjusted to fit
   TRY_TEST(circseg->put_Radius(4),S_OK);
   TRY_TEST(circseg->get_MidOrdinate(&mo),S_OK);
   TRY_TEST(IsEqual(mo,8.0),true);


   center.Release();
   center.CoCreateInstance(CLSID_Point2d);
   center->Move(10,10);
   TRY_TEST(circseg->put_Center(nullptr),E_INVALIDARG);
   TRY_TEST(circseg->put_Center(center),S_OK);
   CComPtr<IPoint2d> centerTest;
   TRY_TEST(circseg->get_Center(&centerTest),S_OK);
   centerTest->get_X(&x);
   centerTest->get_Y(&y);
   TRY_TEST(IsEqual(x,10.0),true);
   TRY_TEST(IsEqual(y,10.0),true);
   
   // Hook point is referencial
   hook.Release();
   hook.CoCreateInstance(CLSID_Point2d);
   hook->Move(10,10);
   TRY_TEST(circseg->putref_HookPoint(nullptr),E_INVALIDARG);
   TRY_TEST(circseg->putref_HookPoint(hook),S_OK);
   CComPtr<IPoint2d> hookTest;
   TRY_TEST(circseg->get_HookPoint(&hookTest),S_OK);
   TRY_TEST(hook.IsEqualObject(hookTest),true);

   TRY_TEST(circseg->put_InteriorAngle(-10),GEOMETRY_E_ANGLE);
   TRY_TEST(circseg->put_InteriorAngle(6*M_PI),GEOMETRY_E_ANGLE);
   TRY_TEST(circseg->put_InteriorAngle(M_PI),S_OK);
   TRY_TEST(circseg->get_InteriorAngle(&ia),S_OK);
   TRY_TEST(IsEqual(M_PI,ia),true);
   circseg->get_Radius(&radius);
   circseg->get_MidOrdinate(&mo);
   TRY_TEST(IsEqual(radius,mo),true);
   center.Release();
   hook.Release();
   circseg->get_Center(&center);
   circseg->get_HookPoint(&hook);
   Float64 cx,cy,hx,hy;
   center->get_X(&cx);
   center->get_Y(&cy);
   hook->get_X(&hx);
   hook->get_Y(&hy);
   TRY_TEST(IsEqual(cx,hx),true);
   TRY_TEST(IsEqual(cy,hy),true);

   // center should not move when rotation is set.
   // Move center to 50,50 so that it isnt' at 0,0
   center->Move(50,50);
   circseg->put_Center(center);
   mo = 2.0;
   circseg->put_MidOrdinate(mo);

   hook->get_X(&hx);
   hook->get_Y(&hy);
   TRY_TEST(IsEqual(hx,52.0),true);
   TRY_TEST(IsEqual(hy,50.0),true);
   
   TRY_TEST(circseg->put_Rotation(PI_OVER_2),S_OK);
   TRY_TEST(circseg->get_Rotation(&rotation),S_OK);
   TRY_TEST(IsEqual(rotation,PI_OVER_2),true);
   center->get_X(&cx);
   center->get_Y(&cy);
   TRY_TEST(IsEqual(cx,50.0),true);
   TRY_TEST(IsEqual(cy,50.0),true);
   // with 90deg rotation, hook point x and y should swap values
   hook->get_X(&hx);
   hook->get_Y(&hy);
   TRY_TEST(IsEqual(hx,50.0),true);
   TRY_TEST(IsEqual(hy,52.0),true);

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(circseg->get_Shape(nullptr), E_POINTER );
   TRY_TEST(circseg->get_Shape(&shape), S_OK );
   TRY_TEST(shape != nullptr,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(circseg->get_XYPosition(nullptr), E_POINTER );
   TRY_TEST(circseg->get_XYPosition(&position), S_OK );
   TRY_TEST(position != nullptr,true );

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   circseg->QueryInterface(&punk1);
   shape->QueryInterface(&punk2);
   position->QueryInterface(&punk3);
   TRY_TEST( punk1 == punk2, true );
   TRY_TEST( punk1 == punk3, true );
   TRY_TEST( punk2 == punk3, true );
}

void CTestCircularSegment::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST(shape.CoCreateInstance(CLSID_CircularSegment),S_OK);

   CComQIPtr<ICircularSegment> circseg(shape);

   // Test BoundingBox
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(60);
   circseg->put_Rotation(0);
   CComPtr<IRect2d> bb;
   TRY_TEST(shape->get_BoundingBox(nullptr),E_POINTER);
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   Float64 l,r,t,b;
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-10.),true);
   TRY_TEST(IsEqual(r, 50.),true);
   TRY_TEST(IsEqual(b,-50.),true);
   TRY_TEST(IsEqual(t, 50.),true);

   circseg->put_Rotation(PI_OVER_2);
   bb.Release();
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-50.),true);
   TRY_TEST(IsEqual(r, 50.),true);
   TRY_TEST(IsEqual(b,-10.),true);
   TRY_TEST(IsEqual(t, 50.),true);

   circseg->put_Rotation(M_PI);
   bb.Release();
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-50.),true);
   TRY_TEST(IsEqual(r, 10.),true);
   TRY_TEST(IsEqual(b,-50.),true);
   TRY_TEST(IsEqual(t, 50.),true);

   circseg->put_Rotation(3*PI_OVER_2);
   bb.Release();
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-50.),true);
   TRY_TEST(IsEqual(r, 50.),true);
   TRY_TEST(IsEqual(b,-50.),true);
   TRY_TEST(IsEqual(t, 10.),true);

   circseg->put_Radius(50);
   circseg->put_MidOrdinate(40);
   circseg->put_Rotation(0);
   bb.Release();
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   Float64 angle;
   circseg->get_InteriorAngle(&angle);
   Float64 lc = 2*50*sin(angle/2); // long chord
   TRY_TEST(IsEqual(l, 10.),true);
   TRY_TEST(IsEqual(r, 50.),true);
   TRY_TEST(IsEqual(b,-lc/2),true);
   TRY_TEST(IsEqual(t, lc/2),true);

   circseg->put_Rotation(PI_OVER_2);
   bb.Release();
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   circseg->get_InteriorAngle(&angle);
   TRY_TEST(IsEqual(l,-lc/2),true);
   TRY_TEST(IsEqual(r, lc/2),true);
   TRY_TEST(IsEqual(b, 10.),true);
   TRY_TEST(IsEqual(t, 50.),true);

   circseg->put_Rotation(M_PI);
   bb.Release();
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   TRY_TEST(IsEqual(l,-50.),true);
   TRY_TEST(IsEqual(r,-10.),true);
   TRY_TEST(IsEqual(b,-lc/2),true);
   TRY_TEST(IsEqual(t, lc/2),true);

   circseg->put_Rotation(3*PI_OVER_2);
   bb.Release();
   TRY_TEST(shape->get_BoundingBox(&bb),S_OK);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);
   circseg->get_InteriorAngle(&angle);
   TRY_TEST(IsEqual(l,-lc/2),true);
   TRY_TEST(IsEqual(r, lc/2),true);
   TRY_TEST(IsEqual(b,-50.),true);
   TRY_TEST(IsEqual(t,-10.),true);

   /////////////////////////////////
   // Test Clone
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(60);
   circseg->put_Rotation(3*PI_OVER_2);

   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(nullptr),E_POINTER);
   TRY_TEST(shape->Clone(&clone),S_OK);
   Float64 radius,mo,rotation;
   CComQIPtr<ICircularSegment> cloneCircSeg(clone);
   cloneCircSeg->get_Radius(&radius);
   cloneCircSeg->get_MidOrdinate(&mo);
   cloneCircSeg->get_Rotation(&rotation);
   TRY_TEST(IsEqual(radius,50.),true);
   TRY_TEST(IsEqual(mo,60.),true);
   TRY_TEST(IsEqual(rotation,3*PI_OVER_2),true);

   //////////////////////////////
   // Test Perimeter
   // Use a half circle. Perimeter = 2*PI*r/2 + 2*r
   Float64 perimeter;
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(50);
   TRY_TEST(shape->get_Perimeter(nullptr),E_POINTER);
   TRY_TEST(shape->get_Perimeter(&perimeter),S_OK);
   TRY_TEST(IsEqual(perimeter,M_PI*50+100.),true);

   // perimeter should be invariant to rotation and translation
   circseg->put_Rotation(0.75*M_PI);
   CComPtr<IPoint2d> center;
   circseg->get_Center(&center);
   center->Move(50,40);
   circseg->put_Center(center);
   TRY_TEST(shape->get_Perimeter(&perimeter),S_OK);
   TRY_TEST(IsEqual(perimeter,M_PI*50+100.),true);

   ////////////////////////////
   // Test PointInShape
   circseg->put_Rotation(0.0);
   center->Move(10,10);
   circseg->put_Center(center);
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);
   pnt->Move(70,10);
   VARIANT_BOOL bInShape;
   TRY_TEST(shape->PointInShape(nullptr,&bInShape),E_INVALIDARG);
   TRY_TEST(shape->PointInShape(pnt,nullptr),E_POINTER);
   TRY_TEST(shape->PointInShape(pnt,&bInShape),S_OK);
   TRY_TEST(bInShape,VARIANT_FALSE);

   pnt->Move(10,-70);
   TRY_TEST(shape->PointInShape(pnt,&bInShape),S_OK);
   TRY_TEST(bInShape,VARIANT_FALSE);

   pnt->Move(10,70);
   TRY_TEST(shape->PointInShape(pnt,&bInShape),S_OK);
   TRY_TEST(bInShape,VARIANT_FALSE);

   pnt->Move(-70,10);
   TRY_TEST(shape->PointInShape(pnt,&bInShape),S_OK);
   TRY_TEST(bInShape,VARIANT_FALSE);

   pnt->Move(20,20);
   TRY_TEST(shape->PointInShape(pnt,&bInShape),S_OK);
   TRY_TEST(bInShape,VARIANT_TRUE);

   pnt->Move(0,20);
   TRY_TEST(shape->PointInShape(pnt,&bInShape),S_OK);
   TRY_TEST(bInShape,VARIANT_FALSE);

   ////////////////////////////
   // Test FurthestDistance
   CComPtr<IPoint2d> p1;
   CComPtr<IPoint2d> p2;
   p1.CoCreateInstance(CLSID_Point2d);
   p2.CoCreateInstance(CLSID_Point2d);
   p1->Move(-100,-70);
   p2->Move( 100,-70);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(p1,p2);

   Float64 dist;
   circseg->put_Rotation(M_PI/4);
   center->Move(10,10);
   circseg->put_Center(center);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(50);

   TRY_TEST(shape->FurthestDistance(nullptr,&dist),E_INVALIDARG);
   TRY_TEST(shape->FurthestDistance(line,nullptr),E_POINTER);
   TRY_TEST(shape->FurthestDistance(line,&dist),S_OK);
   TRY_TEST(IsEqual(dist,-44.64466),true);

   line->ThroughPoints(p2,p1);
   TRY_TEST(shape->FurthestDistance(line,&dist),S_OK);
   TRY_TEST(IsEqual(dist,130.0),true);

//   circseg->put_Rotation(3*M_PI/4);
   
   p1->Move(-100,90);
   p2->Move( 100,90);
   line->ThroughPoints(p1,p2);

   TRY_TEST(shape->FurthestDistance(line,&dist),S_OK);
   TRY_TEST(IsEqual(dist,115.355339),true);

   line->ThroughPoints(p2,p1);
   TRY_TEST(shape->FurthestDistance(line,&dist),S_OK);
   TRY_TEST(IsEqual(dist,-30.0),true);

   // line through shape
   p1->Move(-100,5);
   p2->Move( 100,5);
   line->ThroughPoints(p1,p2);
   TRY_TEST(shape->FurthestDistance(line,&dist),S_OK);
   TRY_TEST(IsEqual(dist,30.35533906),true);

   line->ThroughPoints(p2,p1);
   TRY_TEST(shape->FurthestDistance(line,&dist),S_OK);
   TRY_TEST(IsEqual(dist,55.0),true);

   ////////////////////////////
   // Test PolyPoints
   //
   // PolyPoints are tested by CircularSegment.xls. This
   // spreadsheet plots the polypoints so I can visually verify
   // the shape
   // The following are points reported from the spreadsheet and
   // verified visually. They are coded here for regression testing purposes
   // If the implementation changes, these points should not change
   Float64 px[] = {
      51.7356,
      53.7115,  
      55.4346,  
      56.8948,  
      58.0837,  
      58.9944,  
      59.6217,  
      59.9619,  
      60.013,   
      59.7748,  
      59.2487,  
      58.4376,  
      57.3463,  
      55.981,   
      54.3498,  
      52.462,   
      50.3285,  
      47.9617,  
      45.3753,  
      42.5842,  
      39.6046,  
      36.4537,  
      33.1498,  
      29.712,   
      26.1601,  
      22.5147,  
      18.7969,  
      15.0283,  
      11.2305,  
      7.42564,  
      3.63566,  
      -0.117501,
      -3.81213, 
      -7.42685, 
      -10.9408, 
      -14.3335,
      -17.5855
   };

   Float64 py[] = {
      -17.5855,
      -14.3335,
      -10.9408,
      -7.42685,
      -3.81213,
      -0.117501,
      3.63566,
      7.42564,
      11.2305,
      15.0283,
      18.7969,
      22.5147,
      26.1601,
      29.712,
      33.1498,
      36.4537,
      39.6046,
      42.5842,
      45.3753,
      47.9617,
      50.3285,
      52.462,
      54.3498,
      55.981,
      57.3463,
      58.4376,
      59.2487,
      59.7748,
      60.013,
      59.9619,
      59.6217,
      58.9944,
      58.0837,
      56.8948,
      55.4346,
      53.7115,
      51.7356
   };

   circseg->put_Rotation(M_PI/4);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(40);
   center->Move(10,10);
   circseg->put_Center(center);

   CComPtr<IPoint2dCollection> points;
   TRY_TEST(shape->get_PolyPoints(nullptr),E_POINTER);
   TRY_TEST(shape->get_PolyPoints(&points),S_OK);

   IndexType nPoints = sizeof(px)/sizeof(Float64);
   IndexType cPoints;
   points->get_Count(&cPoints);
   TRY_TEST(cPoints,nPoints); // nPoints polypoints
   for ( IndexType i = 0; i < cPoints && i < nPoints; i++ )
   {
      CComPtr<IPoint2d> p;
      points->get_Item(i,&p);
      Float64 x,y;
      p->get_X(&x);
      p->get_Y(&y);

      TRY_TEST(IsEqual(x,px[i],0.0001),true);
      TRY_TEST(IsEqual(y,py[i],0.0001),true);
   }


   ////////////////////////////
   // Test ShapeProperties

   // keep it simple, start with half a circle
   circseg->put_Rotation(0.0);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(50);
   center->Move(0,0);
   circseg->put_Center(center);

   CComPtr<IShapeProperties> props;
   TRY_TEST(shape->get_ShapeProperties(nullptr),E_POINTER);
   TRY_TEST(shape->get_ShapeProperties(&props),S_OK);

   Float64 area, ixx, iyy, ixy;
   CComPtr<IPoint2d> cg;
   Float64 cgx, cgy;

   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   props->get_Centroid(&cg);
   TRY_TEST( IsEqual(area,M_PI*radius*radius/2,0.1), true );
   TRY_TEST( IsEqual(ixx,M_PI*radius*radius*radius*radius/8,0.1), true );
   TRY_TEST( IsEqual(iyy,pow(radius,4)*(9*M_PI*M_PI-64)/(72*M_PI),0.1), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,4*radius/(3*M_PI),0.1), true );
   TRY_TEST( IsEqual(cgy,0.0), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   bb.Release();
   shape->get_BoundingBox(&bb);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);

   props->get_Xleft(&xleft);
   TRY_TEST(IsEqual(xleft,cgx-l),true);
   props->get_Xright(&xright);
   TRY_TEST(IsEqual(xright,r-cgx),true);
   props->get_Ytop(&ytop);
   TRY_TEST(IsEqual(ytop,t-cgy),true);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(ybottom,cgy-b),true);

   TRY_TEST(IsEqual(xleft+xright,50.0),true);
   TRY_TEST(IsEqual(ytop+ybottom,100.0),true);

   // rotate 90 deg and check results
   center->Move(0,0);
   circseg->put_Center(center);
   circseg->put_Rotation(PI_OVER_2);

   props.Release();
   TRY_TEST(shape->get_ShapeProperties(&props),S_OK);

   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   cg.Release();
   props->get_Centroid(&cg);
   TRY_TEST( IsEqual(area,M_PI*radius*radius/2), true );
   TRY_TEST( IsEqual(ixx,pow(radius,4)*(9*M_PI*M_PI-64)/(72*M_PI)), true );
   TRY_TEST( IsEqual(iyy,M_PI*radius*radius*radius*radius/8), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,4*radius/(3*M_PI)), true );
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   bb.Release();
   shape->get_BoundingBox(&bb);
   bb->get_Left(&l);
   bb->get_Right(&r);
   bb->get_Top(&t);
   bb->get_Bottom(&b);

   props->get_Xleft(&xleft);
   TRY_TEST(IsEqual(xleft,cgx-l),true);
   props->get_Xright(&xright);
   TRY_TEST(IsEqual(xright,r-cgx),true);
   props->get_Ytop(&ytop);
   TRY_TEST(IsEqual(ytop,t-cgy),true);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(ybottom,cgy-b),true);

   TRY_TEST(IsEqual(xleft+xright,100.0),true);
   TRY_TEST(IsEqual(ytop+ybottom,50.0),true);

   // put shape at some weird place and compare properties with
   // its polygonal representation.
   center->put_X(50);
   center->put_Y(-90);
   
   center->put_X(0);
   center->put_Y(0);

   circseg->put_Center(center);
   circseg->put_Radius(60);
   circseg->put_MidOrdinate(40);
   circseg->put_Rotation( 0.6969696969 );
   props.Release();
   shape->get_ShapeProperties(&props);

   points.Release();
   shape->get_PolyPoints(&points);
   
   points->get_Count(&cPoints);
   ATLTRACE("Trace of Points for CircularSegment - count = %d \n", cPoints);
   ATLTRACE("  pt         X         Y\n");
   ATLTRACE("---------------------------------\n");
   for (IndexType ip = 0; ip < cPoints; ip++)
   {
      CComPtr<IPoint2d> pnt;
      points->get_Item(ip, &pnt);
      Float64 x, y;
      pnt->get_X(&x);
      pnt->get_Y(&y);
      ATLTRACE(" %4d  %10f %10f \n", ip, x, y);
   }
   ATLTRACE("---------------------------\n");

   CComPtr<IPolyShape> polyShape;
   polyShape.CoCreateInstance(CLSID_PolyShape);
   polyShape->SetPoints(points);
   CComPtr<IShapeProperties> props2;
   CComQIPtr<IShape> shape2(polyShape);
   shape2->get_ShapeProperties(&props2);
   Float64 val1,val2;
   props->get_Area(&val1);
   props2->get_Area(&val2);
   TRY_TEST(IsEqual(val1,val2,0.01),true);

   props->get_Ixx(&val1);
   props2->get_Ixx(&val2);
   TRY_TEST(IsEqual(val1/val2,1.0,0.01),true);

   props->get_Iyy(&val1);
   props2->get_Iyy(&val2);
   TRY_TEST(IsEqual(val1/val2,1.0,0.01),true);

   props->get_Ixy(&val1);
   props2->get_Ixy(&val2);
   TRY_TEST(IsEqual(val1/val2,1.0,0.01),true);

   CComPtr<IPoint2d> cg1;
   CComPtr<IPoint2d> cg2;
   props->get_Centroid(&cg1);
   props2->get_Centroid(&cg2);

   cg1->get_X(&val1);
   cg2->get_X(&val2);
   TRY_TEST(IsEqual(val1,val2,0.01),true);

   cg1->get_Y(&val1);
   cg2->get_Y(&val2);
   TRY_TEST(IsEqual(val1,val2,0.01),true);

   ////////////////////////////
   // Test ClipWithLine
   circseg->put_Rotation(0.0);
   radius = 50;
   circseg->put_Radius(radius);
   circseg->put_MidOrdinate(radius);
   center->Move(10,10);
   circseg->put_Center(center);

   // clipping line well below shape (shape on right of line)
   p1->Move( 100,-70);
   p2->Move(-100,-70);
   line->ThroughPoints(p1,p2);
   CComPtr<IShape> clipShape;
   TRY_TEST(shape->ClipWithLine(nullptr,&clipShape),E_INVALIDARG);
   TRY_TEST(shape->ClipWithLine(line,nullptr),E_POINTER);
   TRY_TEST(shape->ClipWithLine(line,&clipShape),S_OK);
   props.Release();
   CComQIPtr<ICircularSegment> qiShape(clipShape);
   TRY_TEST(qiShape != nullptr, true);
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area);
   TRY_TEST(IsEqual(area,M_PI*radius*radius/2),true);

   // reverse clipping line (shape on left of line)
   // entire shape clipped away
   line->ThroughPoints(p2,p1);
   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   TRY_TEST(clipShape,nullptr);

   // clip shape in such a way that we are left with a quarter circle
   center->Move(100,100);
   circseg->put_Center(center);
   circseg->put_Rotation(PI_OVER_2);
   radius = 50;
   circseg->put_Radius(radius);
   circseg->put_MidOrdinate(radius);

   p1->Move(100,-500);
   p2->Move(100, 500);
   line->ThroughPoints(p1,p2);

   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&val1);
   val2 = M_PI*radius*radius/4;
   TRY_TEST(IsEqual(val1,val2,0.01),true);

   // Test relative correctness of centroid.
   // Should be left and above center of circle
   // and x and y should be equal.
   cg.Release();
   props->get_Centroid(&cg);
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST(cgx > 100,true);
   TRY_TEST(cgy > 100,true);
   TRY_TEST( IsEqual(cgx,cgy),true);

   // clip in such a way the the result is still a circular segment
   center->Move(0,0);
   circseg->put_Center(center);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(60);
   circseg->put_Rotation(0);
   p1->Move(40,-100);
   p2->Move(40, 100);
   line->ThroughPoints(p1,p2);
   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   CComQIPtr<ICircularSegment> qi3(clipShape);
   TRY_TEST(qi3 != nullptr,true);
   // center and radius should be the same
   qi3->get_Radius(&radius);
   TRY_TEST(IsEqual(radius,50.),true);
   center.Release();
   qi3->get_Center(&center);
   center->get_X(&cgx);
   center->get_Y(&cgy);
   TRY_TEST(IsEqual(cgx,0.0),true);
   TRY_TEST(IsEqual(cgy,0.0),true);
   // mid-ordinate should be the radius less the original mid-ordinate
   qi3->get_MidOrdinate(&val1);
   TRY_TEST(IsEqual(val1,10.),true);


   // reverse the direction of the clipping line
   // result should be a polygon.
   // area clip = area shape - area clip from above
   //
   // get area of source shape and the clip shape from above
   Float64 area1, area2, area3;
   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Area(&area1);
   
   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area2);

   line->ThroughPoints(p2,p1);
   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   CComQIPtr<IPolyShape> qiPolyShape(clipShape);
   TRY_TEST(qiPolyShape != nullptr, true );

   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area3);
   val1 = area1 - area2;
   TRY_TEST( IsEqual(area3,val1,0.3),true);

   // run a clipping line through the straight edge of the shape
   // Clip with line going both direction. Sum of clipped shape areas
   // must be equal to the area of the original shape
   center->Move(0,0);
   circseg->put_Center(center);
   circseg->put_Radius(100);
   circseg->put_MidOrdinate(70);
   circseg->put_Rotation(0);
   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Area(&area1);

   p1->Move(90,90);
   p2->Move(20,-60);
   line->ThroughPoints(p1,p2);

   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area2);

   line->ThroughPoints(p2,p1);

   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area3);

   val1 = area2 + area3;
   TRY_TEST(IsEqual(area1,val1),true);

   // same as above, but this time shape is a full circle (interior angle = 360)
   center->Move(0,0);
   circseg->put_Center(center);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(100);
   circseg->put_Rotation(0);
   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Area(&area1);

   p1->Move(-50,-50);
   p2->Move(50,50);
   line->ThroughPoints(p1,p2);

   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area2);
   TRY_TEST(IsEqual(area2*2,area1,0.001),true); // clip shape half circle

   Float64 cgx1,cgy1;
   cg.Release();
   props->get_Centroid(&cg);
   cg->get_X(&cgx1);
   cg->get_Y(&cgy1);

   line->ThroughPoints(p2,p1);

   clipShape.Release();
   shape->ClipWithLine(line,&clipShape);
   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area3);
   TRY_TEST(IsEqual(area3*2,area1,0.001),true); // clip shape half circle

   Float64 cgx2,cgy2;
   cg.Release();
   props->get_Centroid(&cg);
   cg->get_X(&cgx2);
   cg->get_Y(&cgy2);

   val1 = area2 + area3;
   TRY_TEST(IsEqual(area1,val1,0.001),true);

   TRY_TEST(IsEqual(cgx1,-cgx2,0.001),true);
   TRY_TEST(IsEqual(cgy1,-cgy2,0.001),true);

   ////////////////////////////
   // Test ClipIn
   radius = 50;
   circseg->put_Radius(radius);
   circseg->put_MidOrdinate(radius);
   center->Move(0,0);
   circseg->put_Center(center);
   circseg->put_Rotation(0);

   // Use a rectangle that is bigger than the entire shape
   // Results should be a clone of the original shape
   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance(CLSID_Rect2d);
   clipRect->put_Left(-10);
   clipRect->put_Right(100);
   clipRect->put_Top(100);
   clipRect->put_Bottom(-100);

   clipShape.Release();
   TRY_TEST(shape->ClipIn(nullptr,&clipShape),E_INVALIDARG);
   TRY_TEST(shape->ClipIn(clipRect,nullptr),E_POINTER);
   TRY_TEST(shape->ClipIn(clipRect,&clipShape),S_OK);
   
   CComQIPtr<ICircularSegment> qiShape2(clipShape);
   TRY_TEST(qiShape2 != nullptr, true);

   props.Release();
   shape->get_ShapeProperties(&props);

   props2.Release();
   clipShape->get_ShapeProperties(&props2);

   props->get_Area(&val1);
   props2->get_Area(&val2);
   TRY_TEST(IsEqual(val1,val2),true);

   // Clip all out
   clipRect->put_Left(-1000);
   clipRect->put_Right(-900);
   clipRect->put_Top(-900);
   clipRect->put_Bottom(-1000);
   clipShape.Release();
   TRY_TEST(shape->ClipIn(clipRect,&clipShape),S_OK);
   TRY_TEST(clipShape == nullptr,true);

   // Clip a square in the center
   clipRect->put_Left(1);
   clipRect->put_Right(6);
   clipRect->put_Top(5);
   clipRect->put_Bottom(0);
   clipShape.Release();
   TRY_TEST(shape->ClipIn(clipRect,&clipShape),S_OK);
   props.Release();
   clipShape->get_ShapeProperties(&props);
   props->get_Area(&area);
   TRY_TEST(IsEqual(area,25.),true);
   cg.Release();
   props->get_Centroid(&cg);
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST(IsEqual(cgx,3.5),true);
   TRY_TEST(IsEqual(cgy,2.5),true);
}

void CTestCircularSegment::TestIXYPosition()
{
   // Test Offset
   CComPtr<IXYPosition> position;
   position.CoCreateInstance(CLSID_CircularSegment);
   CComQIPtr<ICircularSegment> circseg(position);

   CComPtr<IPoint2d> center;
   center.CoCreateInstance(CLSID_Point2d);
   Float64 cx,cy;
   cx = 10;
   cy = 10;
   center->Move(cx,cy);
   circseg->put_Center(center);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(40);
   circseg->put_Rotation(M_PI/4);

   CComPtr<IPoint2d> hook;
   circseg->get_HookPoint(&hook);
   Float64 hx,hy;
   hook->get_X(&hx);
   hook->get_Y(&hy);

   // area is invariant
   Float64 area1, area2;
   CComQIPtr<IShape> shape(circseg);
   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);
   props->get_Area(&area1);

   Float64 dx,dy;
   dx = -50;
   dy = 99;
   TRY_TEST(position->Offset(dx,dy),S_OK);
   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Area(&area2);
   TRY_TEST(IsEqual(area1,area2),true);

   center.Release();
   circseg->get_Center(&center);
   Float64 x,y;
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,cx+dx),true);
   TRY_TEST(IsEqual(y,cy+dy),true);

   hook.Release();
   circseg->get_HookPoint(&hook);
   hook->get_X(&x);
   hook->get_Y(&y);
   TRY_TEST(IsEqual(x,hx+dx),true);
   TRY_TEST(IsEqual(y,hy+dy),true);

   // Test OffsetEx
   center->Move(cx,cy);
   circseg->put_Center(center);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(40);
   circseg->put_Rotation(M_PI/4);

   CComPtr<ISize2d> size;
   size.CoCreateInstance(CLSID_Size2d);
   size->put_Dx(dx);
   size->put_Dy(dy);
   TRY_TEST(position->OffsetEx(nullptr),E_INVALIDARG);
   TRY_TEST(position->OffsetEx(size),S_OK);

   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Area(&area2);
   TRY_TEST(IsEqual(area1,area2),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,cx+dx),true);
   TRY_TEST(IsEqual(y,cy+dy),true);

   hook.Release();
   circseg->get_HookPoint(&hook);
   hook->get_X(&x);
   hook->get_Y(&y);
   TRY_TEST(IsEqual(x,hx+dx),true);
   TRY_TEST(IsEqual(y,hy+dy),true);

   // Test LocatorPoint
   center->Move(0,0);
   circseg->put_Center(center);
   Float64 radius = 50;
   circseg->put_Radius(radius);
   circseg->put_MidOrdinate(40);
   circseg->put_Rotation(0);

   CComPtr<IPoint2d> lpin;
   lpin.CoCreateInstance(CLSID_Point2d);

   CComPtr<IPoint2d> lpout;
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

   CComPtr<ILineSegment2d> chord;
   circseg->get_Chord(&chord);
   Float64 lc; // long chord
   chord->get_Length(&lc);

   // Top Left
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpTopLeft,lpin),S_OK);
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x,40.0),true);
   TRY_TEST(IsEqual(y,-lc),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y,-lc/2),true);

   // Top Center
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpTopCenter,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x,20.0),true);
   TRY_TEST(IsEqual(y,-lc),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-30.0),true);
   TRY_TEST(IsEqual(y,-lc/2),true);

   // Top Right
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpTopRight,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x, 0.0),true);
   TRY_TEST(IsEqual(y,-lc),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-50.0),true);
   TRY_TEST(IsEqual(y,-lc/2),true);

   // Center Left
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpCenterLeft,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x, 40.0),true);
   TRY_TEST(IsEqual(y,-lc/2),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   // Center Center
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpCenterCenter,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x, 20.0),true);
   TRY_TEST(IsEqual(y,-lc/2),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-30.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   // Center Right
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpCenterRight,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x,  0.0),true);
   TRY_TEST(IsEqual(y,-lc/2),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-50.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   // Bottom Left
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpBottomLeft,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x, 40.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y, lc/2),true);

   // Bottom Center
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpBottomCenter,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x, 20.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-30.0),true);
   TRY_TEST(IsEqual(y, lc/2),true);

   // Bottom Right
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpBottomRight,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x,  0.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-50.0),true);
   TRY_TEST(IsEqual(y, lc/2),true);

   // Hook Point
   lpin->Move(0,0);
   TRY_TEST(position->put_LocatorPoint(lpHookPoint,lpin),S_OK);
   lpout.Release();
   TRY_TEST(position->get_LocatorPoint(lpBottomRight,&lpout),S_OK);
   lpout->get_X(&x);
   lpout->get_Y(&y);
   TRY_TEST(IsEqual(x, 40.0),true);
   TRY_TEST(IsEqual(y,-lc/2),true);

   center.Release();
   circseg->get_Center(&center);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,-10.0),true);
   TRY_TEST(IsEqual(y,  0.0),true);

   // Test Rotate and RotateEx
   TRY_TEST(position->RotateEx(nullptr,0.0),E_INVALIDARG);
   center->Move(10,10);
   circseg->put_Center(center);
   circseg->put_Radius(50);
   circseg->put_MidOrdinate(40);
   circseg->put_Rotation(0);
   TRY_TEST(position->RotateEx(center,M_PI),S_OK);
   Float64 rotation;
   circseg->get_Rotation(&rotation);
   TRY_TEST(IsEqual(rotation,M_PI),true);
}

void CTestCircularSegment::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_CircularSegment ), S_OK );
   TRY_TEST( eInfo != nullptr, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICircularSegment ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}

void CTestCircularSegment::TestIObjectSafety()
{
   CComPtr<IObjectSafety> safety;
   TRY_TEST( safety.CoCreateInstance( CLSID_CircularSegment ), S_OK );
   TRY_TEST( safety != nullptr, true );

   DWORD dwSupported;
   DWORD dwEnabled;
   
   TRY_TEST( safety->SetInterfaceSafetyOptions( IID_IUnknown, INTERFACESAFE_FOR_UNTRUSTED_CALLER, INTERFACESAFE_FOR_UNTRUSTED_CALLER), S_OK);

   TRY_TEST( safety->GetInterfaceSafetyOptions( IID_ICircularSegment, &dwSupported, &dwEnabled ), S_OK );
   TRY_TEST( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   TRY_TEST( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );

   TRY_TEST( safety->GetInterfaceSafetyOptions( IID_IShape, &dwSupported, &dwEnabled ), S_OK );
   TRY_TEST( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   TRY_TEST( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   
   TRY_TEST( safety->GetInterfaceSafetyOptions( IID_IXYPosition, &dwSupported, &dwEnabled ), S_OK );
   TRY_TEST( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   TRY_TEST( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
}

void CTestCircularSegment::OtherTests()
{
   // Test a shape with a zero mid-ordinate
   CComPtr<ICircularSegment> sc;
   sc.CoCreateInstance(CLSID_CircularSegment);

   sc->put_Radius(100);
   sc->put_MidOrdinate(0);
   sc->put_Rotation(M_PI/4);
   
   CComPtr<IPoint2d> center;
   center.CoCreateInstance(CLSID_Point2d);
   center->Move(100,100);
   sc->put_Center(center);

   CComQIPtr<IShape> shape(sc);
   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);

   Float64 val;
   CComPtr<IPoint2d> cg;

   shape->get_Perimeter(&val);
   TRY_TEST(IsZero(val),true);

   props->get_Area(&val);
   TRY_TEST(IsZero(val),true);

   props->get_Ixx(&val);
   TRY_TEST(IsZero(val),true);

   props->get_Iyy(&val);
   TRY_TEST(IsZero(val),true);

   props->get_Ixy(&val);
   TRY_TEST(IsZero(val),true);

   props->get_Centroid(&cg);
   cg->get_X(&val);
   TRY_TEST(IsEqual(val,170.71,0.01),true);

   cg->get_Y(&val);
   TRY_TEST(IsEqual(val,170.71,0.01),true);
}