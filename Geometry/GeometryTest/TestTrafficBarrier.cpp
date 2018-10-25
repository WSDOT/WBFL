///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 2000  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// TestTrafficBarrier.cpp: implementation of the CTestTrafficBarrier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestTrafficBarrier.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestTrafficBarrier::CTestTrafficBarrier()
{

}

CTestTrafficBarrier::~CTestTrafficBarrier()
{

}

void CTestTrafficBarrier::Test()
{
   TestITrafficBarrier();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestTrafficBarrier::TestITrafficBarrier()
{
   CComPtr<ITrafficBarrier> barrier;
   TRY_TEST( barrier.CoCreateInstance( CLSID_TrafficBarrier ), S_OK );

   // Verify default values
   Float64 val;
   CComPtr<IPoint2d> pntVal;
   TrafficBarrierOrientation tboVal;

   TRY_TEST( barrier->get_HookPoint(NULL), E_POINTER );
   TRY_TEST( barrier->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_Orientation(NULL), E_POINTER );
   TRY_TEST( barrier->get_Orientation(&tboVal), S_OK );
   TRY_TEST( tboVal, tboLeft );

   TRY_TEST( barrier->get_X1(NULL), E_POINTER );
   TRY_TEST( barrier->get_X1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_X2(NULL), E_POINTER );
   TRY_TEST( barrier->get_X2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_X3(NULL), E_POINTER );
   TRY_TEST( barrier->get_X3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_X4(NULL), E_POINTER );
   TRY_TEST( barrier->get_X4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_X5(NULL), E_POINTER );
   TRY_TEST( barrier->get_X5(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_Y1(NULL), E_POINTER );
   TRY_TEST( barrier->get_Y1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_Y2(NULL), E_POINTER );
   TRY_TEST( barrier->get_Y2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_Y3(NULL), E_POINTER );
   TRY_TEST( barrier->get_Y3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( barrier->get_Y4(NULL), E_POINTER );
   TRY_TEST( barrier->get_Y4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   // Test put property
   TRY_TEST( barrier->put_X1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_X1(12.0), S_OK );
   barrier->get_X1(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_X2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_X2(12.0), S_OK );
   barrier->get_X2(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_X3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_X3(12.0), S_OK );
   barrier->get_X3(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_X4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_X4(12.0), S_OK );
   barrier->get_X4(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_X5(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_X5(12.0), S_OK );
   barrier->get_X5(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_Y1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_Y1(12.0), S_OK );
   barrier->get_Y1(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_Y2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_Y2(12.0), S_OK );
   barrier->get_Y2(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_Y3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_Y3(12.0), S_OK );
   barrier->get_Y3(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_Y4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( barrier->put_Y4(12.0), S_OK );
   barrier->get_Y4(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( barrier->put_Orientation(tboRight), S_OK );
   barrier->get_Orientation(&tboVal);
   TRY_TEST( tboVal, tboRight );

   TRY_TEST( barrier->putref_HookPoint(NULL), E_INVALIDARG );
   TRY_TEST( barrier->putref_HookPoint(pntVal), S_OK );

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(barrier->get_Shape(NULL), E_POINTER );
   TRY_TEST(barrier->get_Shape(&shape), S_OK );
   TRY_TEST(shape != NULL,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(barrier->get_XYPosition(NULL), E_POINTER );
   TRY_TEST(barrier->get_XYPosition(&position), S_OK );
   TRY_TEST(position != NULL,true );

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   barrier->QueryInterface(&punk1);
   shape->QueryInterface(&punk2);
   position->QueryInterface(&punk3);
   TRY_TEST( punk1 == punk2, true );
   TRY_TEST( punk1 == punk3, true );
   TRY_TEST( punk2 == punk3, true );
}

void CTestTrafficBarrier::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_TrafficBarrier ), S_OK );
   CComQIPtr<ITrafficBarrier> barrier(shape);
   
   // Use some real dimensions
   barrier->put_X1(3.5);
   barrier->put_X2(10.5);
   barrier->put_X3(11.5);
   barrier->put_X4(2.375);
   barrier->put_X5(4.875);
   barrier->put_Y1(3.0);
   barrier->put_Y2(7.0);
   barrier->put_Y3(32.0);
   barrier->put_Y4(7.5);

   //
   // ShapeProperties
   //
   CComPtr<IShapeProperties> props;
   TRY_TEST( shape->get_ShapeProperties(NULL), E_POINTER );
   TRY_TEST( shape->get_ShapeProperties(&props), S_OK );
   Float64 area, ixx, iyy, ixy, cgx, cgy;
   CComPtr<IPoint2d> cg;

   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   cg.Release();
   props->get_Centroid(&cg);
   TRY_TEST( IsEqual(area,417.625), true );
   TRY_TEST( IsEqual(ixx,44747.861222833), true );
   TRY_TEST( IsEqual(iyy,6262.5842348081), true );
   TRY_TEST( IsEqual(ixy,-5237.9423208781), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,-0.23279581961489), true );
   TRY_TEST( IsEqual(cgy,13.909333532874), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   //
   // Bounding Box
   //
   Float64 xleft,xright,ytop,ybottom;
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(NULL), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-8.25), true );
   props->get_Xleft(&xleft);
   TRY_TEST(IsEqual(xleft,cgx-val),true);
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val,10.5), true );
   props->get_Xright(&xright);
   TRY_TEST(IsEqual(xright,val-cgx),true);

   box->get_Top(&val);
   TRY_TEST( IsEqual(val,32.00), true );
   props->get_Ytop(&ytop);
   TRY_TEST(IsEqual(ytop,val-cgy),true);

   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,-7.50), true );
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(ybottom,cgy-val),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(NULL), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,106.44267779471), true ); // Get value from PGSuper

   //
   // FurthestDistance
   //
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance( CLSID_Point2d );

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance( CLSID_Point2d );

   CComPtr<ILine2d> line;
   line.CoCreateInstance( CLSID_Line2d );

   // Shape on right
   p1->Move(0,50);
   p2->Move(100,50);
   line->ThroughPoints(p1,p2);
   Float64 dist;
   TRY_TEST( shape->FurthestDistance(NULL,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,NULL), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,57.500), true );

   // shape on left
   p1->Move(0,-50);
   p2->Move(100,-50);
   line->ThroughPoints(p1,p2);
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-42.50), true );

   // 
   // PolyPoints
   //
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );

   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 8 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[8];
   ULONG fetched;
   Enum->Next(8,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.5), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.5), true );
   TRY_TEST( IsEqual(y,3.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,5.625), true );
   TRY_TEST( IsEqual(y,10.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,3.25), true );
   TRY_TEST( IsEqual(y,32.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-8.25), true );
   TRY_TEST( IsEqual(y,32.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,-3.5), true );
   TRY_TEST( IsEqual(y,-7.5), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,-7.5), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(NULL), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<ITrafficBarrier> barrierClone(clone);
   TRY_TEST( barrierClone != 0, true );

   barrierClone->get_X1(&val);
   TRY_TEST( IsEqual(val,3.5), true);

   barrierClone->get_X2(&val);
   TRY_TEST( IsEqual(val,10.5), true);

   barrierClone->get_X3(&val);
   TRY_TEST( IsEqual(val,11.5), true);

   barrierClone->get_X4(&val);
   TRY_TEST( IsEqual(val,2.375), true);

   barrierClone->get_X5(&val);
   TRY_TEST( IsEqual(val,4.875), true);

   barrierClone->get_Y1(&val);
   TRY_TEST( IsEqual(val,3.0), true);

   barrierClone->get_Y2(&val);
   TRY_TEST( IsEqual(val,7.0), true);

   barrierClone->get_Y3(&val);
   TRY_TEST( IsEqual(val,32.0), true);

   barrierClone->get_Y4(&val);
   TRY_TEST( IsEqual(val,7.5), true);

   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(-1.0, 1.0);

   TRY_TEST( shape->PointInShape(NULL,&bPointInShape), E_INVALIDARG );
   TRY_TEST( shape->PointInShape(pnt,NULL), E_POINTER );
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_TRUE );

   pnt->Move(500,500);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   pnt->Move(0,0); // Point on perimeter
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   //
   // ClipWithLine
   //

   // setup clipping line
   p1->Move(-50,3);
   p2->Move( 50,3);

   CComPtr<ILine2d> clipLine;
   clipLine.CoCreateInstance( CLSID_Line2d );
   clipLine->ThroughPoints(p1,p2);

   CComPtr<IShape> clip;
   TRY_TEST(shape->ClipWithLine(NULL,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,NULL), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 7 );

   coll->get__Enum(&Enum);
   Enum->Next(7,&points[0],&fetched);
   TRY_TEST( fetched, 7 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.5), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.5), true );
   TRY_TEST( IsEqual(y,3.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-4.762658), true );
   TRY_TEST( IsEqual(y,3.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-3.5), true );
   TRY_TEST( IsEqual(y,-7.5), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,-7.5), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   //
   // ClipIn
   //
   clip.Release();

   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );
   clipRect->put_Left(-100);
   clipRect->put_Right(100);
   clipRect->put_Top(4);
   clipRect->put_Bottom(3);

   TRY_TEST( shape->ClipIn(NULL,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,NULL), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   coll->get__Enum(&Enum);
   Enum->Next(4,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.5), true );
   TRY_TEST( IsEqual(y,3.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 9.803571), true );
   TRY_TEST( IsEqual(y, 4.0000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-4.88291), true );
   TRY_TEST( IsEqual(y, 4.000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-4.762658), true );
   TRY_TEST( IsEqual(y, 3.000), true );
}

void CTestTrafficBarrier::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_TrafficBarrier), S_OK);

   CComQIPtr<ITrafficBarrier> barrier(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Use some real dimensions
   barrier->put_X1(3.5);
   barrier->put_X2(10.5);
   barrier->put_X3(11.5);
   barrier->put_X4(2.375);
   barrier->put_X5(4.875);
   barrier->put_Y1(3.0);
   barrier->put_Y2(7.0);
   barrier->put_Y3(32.0);
   barrier->put_Y4(7.5);
   barrier->putref_HookPoint(hookPnt);

   //
   // MoveEx (tests Offset as well)
   //
   CComPtr<IPoint2d> from;
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(0,0);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(100,100);

   TRY_TEST( position->MoveEx(NULL,to), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,NULL), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to), S_OK );

   // Check the points
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,8);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[8];
   ULONG fetched;
   Enum->Next(8,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,110.5), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,110.5), true );
   TRY_TEST( IsEqual(y,103.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,105.625), true );
   TRY_TEST( IsEqual(y,110.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,103.25), true );
   TRY_TEST( IsEqual(y,132.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,91.75), true );
   TRY_TEST( IsEqual(y,132.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,96.5), true );
   TRY_TEST( IsEqual(y,92.5), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,92.5), true );

   //
   // OffsetEx
   //

   // Move the triangle back to where it was
   hookPnt->Move(0,0);

   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(100);
   size->put_Dy(100);

   TRY_TEST(position->OffsetEx(NULL), E_INVALIDARG );
   TRY_TEST(position->OffsetEx(size), S_OK);

   // Check the points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 8; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,8);

   coll->get__Enum(&Enum);
   Enum->Next(8,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,110.5), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,110.5), true );
   TRY_TEST( IsEqual(y,103.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,105.625), true );
   TRY_TEST( IsEqual(y,110.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,103.25), true );
   TRY_TEST( IsEqual(y,132.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,91.75), true );
   TRY_TEST( IsEqual(y,132.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,96.5), true );
   TRY_TEST( IsEqual(y,92.5), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,92.5), true );

   //
   // MoveLocatorPointEx (Provides full coverage of MoveLocatorPoint)
   //
   hookPnt->Move(0,0);
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,NULL), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,NULL), E_POINTER );

   // BottomLeft
   hookPnt->Move(0,0);
   to->Move(91.75,92.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,91.75), true );
   TRY_TEST( IsEqual(y,92.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomCenter
   hookPnt->Move(0,0);
   to->Move(101.125,92.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,101.125), true );
   TRY_TEST( IsEqual(y,92.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomRight
   hookPnt->Move(0,0);
   to->Move(110.5,92.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,110.5), true );
   TRY_TEST( IsEqual(y,92.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterLeft
   hookPnt->Move(0,0);
   to->Move(91.75,112.25);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,91.75), true );
   TRY_TEST( IsEqual(y,112.25), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterCenter
   hookPnt->Move(0,0);
   to->Move(101.125,112.25);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,101.125), true );
   TRY_TEST( IsEqual(y,112.25), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterRight
   hookPnt->Move(0,0);
   to->Move(110.5,112.25);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,110.5), true );
   TRY_TEST( IsEqual(y,112.25), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopLeft
   hookPnt->Move(0,0);
   to->Move(91.75,132);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,91.75), true );
   TRY_TEST( IsEqual(y,132.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopCenter
   hookPnt->Move(0,0);
   to->Move(101.125,132.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,101.125), true );
   TRY_TEST( IsEqual(y,132.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopRight
   hookPnt->Move(0,0);
   to->Move(110.5,132.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,110.5), true );
   TRY_TEST( IsEqual(y,132.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // HookPoint
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpHookPoint, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpHookPoint, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0,0);
   CComPtr<IPoint2d> c;
   c.CoCreateInstance( CLSID_Point2d );
   c->put_X(0);
   c->put_Y(0);

   TRY_TEST( position->RotateEx(NULL,M_PI), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI), S_OK );

   // Check the points
   coll.Release();
   Enum.Release();
   for (int i = 0; i < 8; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,8);

   coll->get__Enum(&Enum);
   Enum->Next(8,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-10.5), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-10.5), true );
   TRY_TEST( IsEqual(y,-3.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-5.625), true );
   TRY_TEST( IsEqual(y,-10.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-3.25), true );
   TRY_TEST( IsEqual(y,-32.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,8.25), true );
   TRY_TEST( IsEqual(y,-32.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,3.5), true );
   TRY_TEST( IsEqual(y,7.5), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,7.5), true );
}

void CTestTrafficBarrier::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_TrafficBarrier ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ITrafficBarrier ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
