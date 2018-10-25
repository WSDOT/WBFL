///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// TestCircle.cpp: implementation of the CTestCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCircle.h"
#include <ObjSafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCircle::CTestCircle()
{

}

CTestCircle::~CTestCircle()
{

}

void CTestCircle::Test()
{
   TestICircle();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
   TestIObjectSafety();
}

void CTestCircle::TestICircle()
{
   CComPtr<ICircle> circle;
   TRY_TEST( circle.CoCreateInstance( CLSID_Circle ), S_OK );

   // Verify initialization. Radius and center should be zero.
   Float64 r,x,y;
   CComPtr<IPoint2d> center;

   TRY_TEST( circle->get_Radius(NULL), E_POINTER );
   TRY_TEST( circle->get_Radius(&r), S_OK );
   TRY_TEST( circle->get_Center(NULL), E_POINTER );
   TRY_TEST( circle->get_Center(&center), S_OK );

   center->get_X(&x);
   center->get_Y(&y);

   TRY_TEST( IsZero(r), true );
   TRY_TEST( IsZero(x), true );
   TRY_TEST( IsZero(y), true );

   // Radius
   TRY_TEST( circle->put_Radius(-100), GEOMETRY_E_RADIUS );
   TRY_TEST( circle->put_Radius(100), S_OK );
   TRY_TEST( circle->get_Radius(&r), S_OK );
   TRY_TEST( IsEqual(r,100.0), true );

   // Center
   center.Release();
   center.CoCreateInstance( CLSID_Point2d );
   center->Move(15,20);
   TRY_TEST( circle->putref_Center(NULL), E_INVALIDARG );
   TRY_TEST( circle->putref_Center(center), S_OK );
   
   CComPtr<IPoint2d> pnt;
   TRY_TEST( circle->get_Center(&pnt), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,15.0), true );
   TRY_TEST( IsEqual(y,20.0), true );

   pnt->Move(3,5);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST( IsEqual(x,3.0), true );
   TRY_TEST( IsEqual(y,5.0), true );

   // ThroughTwoPoints
   CComPtr<IPoint2d> p1, p2;
   p1.CoCreateInstance(CLSID_Point2d);
   p2.CoCreateInstance(CLSID_Point2d);
   p1->Move(15,10);
   p2->Move(15,10);
   TRY_TEST(circle->ThroughTwoPoints(NULL,p2),E_INVALIDARG);
   TRY_TEST(circle->ThroughTwoPoints(p1,NULL),E_INVALIDARG);
   TRY_TEST(circle->ThroughTwoPoints(p1,p2),GEOMETRY_E_COINCIDENTPOINTS);
   p1->Move(10,10);
   TRY_TEST(circle->ThroughTwoPoints(p1,p2),S_OK);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST( IsEqual(x,12.5), true );
   TRY_TEST( IsEqual(y,10.0), true );
   circle->get_Radius(&r);
   TRY_TEST( IsEqual(r,2.5), true );

   // ThroughThreePoints
   CComPtr<IPoint2d> p3;
   p3.CoCreateInstance(CLSID_Point2d);
   p1->Move(15,10);
   p2->Move(15,10);
   p3->Move(15,10);
   TRY_TEST(circle->ThroughThreePoints(NULL,p2,p3),E_INVALIDARG);
   TRY_TEST(circle->ThroughThreePoints(p1,NULL,p3),E_INVALIDARG);
   TRY_TEST(circle->ThroughThreePoints(p1,p2,NULL),E_INVALIDARG);
   TRY_TEST(circle->ThroughThreePoints(p1,p2,p3),GEOMETRY_E_COLINEAR);
   p1->Move(15,10);
   p2->Move(15,20);
   p3->Move(15,30);
   TRY_TEST(circle->ThroughThreePoints(p1,p2,p3),GEOMETRY_E_COLINEAR);
   p1->Move(10,10);
   p2->Move(20,10);
   p3->Move(15,15);
   TRY_TEST(circle->ThroughThreePoints(p1,p2,p3),S_OK);
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST( IsEqual(x,15.0), true );
   TRY_TEST( IsEqual(y,10.0), true );
   circle->get_Radius(&r);
   TRY_TEST( IsEqual(r,5.0), true );

   // ContainsPoint
   center->Move(10,10);
   circle->put_Radius(10);
   p1->Move(0,0);
   VARIANT_BOOL bResult;
   TRY_TEST(circle->ContainsPoint(NULL,&bResult),E_INVALIDARG);
   TRY_TEST(circle->ContainsPoint(p1,NULL),E_POINTER);
   TRY_TEST(circle->ContainsPoint(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_FALSE);
   p1->Move(20,10);
   TRY_TEST(circle->ContainsPoint(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_TRUE);
   p1->Move(30,5);
   TRY_TEST(circle->ContainsPoint(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_FALSE);
   p1->Move(9,9);
   TRY_TEST(circle->ContainsPoint(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_TRUE);
   TRY_TEST(circle->ContainsPoint(center,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_TRUE);

   // PointOnCircle
   center->Move(10,10);
   circle->put_Radius(10);
   p1->Move(0,0);
   TRY_TEST(circle->PointOnCircle(NULL,&bResult),E_INVALIDARG);
   TRY_TEST(circle->PointOnCircle(p1,NULL),E_POINTER);
   TRY_TEST(circle->PointOnCircle(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_FALSE);
   p1->Move(20,10);
   TRY_TEST(circle->PointOnCircle(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_TRUE);
   p1->Move(30,5);
   TRY_TEST(circle->PointOnCircle(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_FALSE);
   p1->Move(9,9);
   TRY_TEST(circle->PointOnCircle(p1,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_FALSE);
   TRY_TEST(circle->PointOnCircle(center,&bResult),S_OK);
   TRY_TEST(bResult,VARIANT_FALSE);

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(circle->get_Shape(NULL), E_POINTER );
   TRY_TEST(circle->get_Shape(&shape), S_OK );
   TRY_TEST(shape != NULL,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(circle->get_XYPosition(NULL), E_POINTER );
   TRY_TEST(circle->get_XYPosition(&position), S_OK );
   TRY_TEST(position != NULL,true );

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   circle->QueryInterface(&punk1);
   shape->QueryInterface(&punk2);
   position->QueryInterface(&punk3);
   TRY_TEST( punk1 == punk2, true );
   TRY_TEST( punk1 == punk3, true );
   TRY_TEST( punk2 == punk3, true );

}

void CTestCircle::TestIShape()
{
   CComPtr<IShape> shape;
   shape.CoCreateInstance( CLSID_Circle );

   CComQIPtr<ICircle> circle(shape);
   CComPtr<IPoint2d> center;
   center.CoCreateInstance( CLSID_Point2d );
   center->put_X(3);
   center->put_Y(5);
   circle->putref_Center(center);

   Float64 radius = 10;
   circle->put_Radius(radius);

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
   TRY_TEST( IsEqual(area,M_PI*radius*radius), true );
   TRY_TEST( IsEqual(ixx,M_PI*radius*radius*radius*radius/4), true );
   TRY_TEST( IsEqual(iyy,M_PI*radius*radius*radius*radius/4), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,3.0), true );
   TRY_TEST( IsEqual(cgy,5.0), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,radius),true);
   TRY_TEST(IsEqual(xright,radius),true);
   TRY_TEST(IsEqual(ytop,radius),true);
   TRY_TEST(IsEqual(ybottom,radius),true);

   //
   // BoundingBox
   //
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(NULL), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   Float64 val;
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,3-radius), true );
   box->get_Right(&val);
   TRY_TEST( IsEqual(val,3+radius), true );
   box->get_Top(&val);
   TRY_TEST( IsEqual(val,5+radius), true );
   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,5-radius), true );

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(NULL), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,TWO_PI*radius), true );

   //
   // FurthestDistance
   //
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance( CLSID_Point2d );
   p1->Move(0,0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance( CLSID_Point2d );
   p2->Move(100,0);

   CComPtr<ILine2d> line;
   line.CoCreateInstance( CLSID_Line2d );
   line->ThroughPoints(p1,p2);

   // Shape on right
   center->Move(50,-100);
   circle->put_Radius(10);

   Float64 dist;
   TRY_TEST( shape->FurthestDistance(NULL,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,NULL), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,110.0), true );

   // shape on left
   center->Move(50, 100);
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-90.0), true );

   //
   // PointInShape
   //
   center->Move(3,5);
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(-10,-10);
   TRY_TEST( shape->PointInShape(NULL,&bPointInShape), E_INVALIDARG );
   TRY_TEST( shape->PointInShape( pnt, NULL ), E_POINTER);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   pnt->Move(3,5);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_TRUE );

   pnt->Move(3,15);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_TRUE );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST( shape->Clone(NULL), E_POINTER );
   TRY_TEST( shape->Clone(&clone), S_OK );

   CComQIPtr<ICircle> circle_clone(clone);
   TRY_TEST( circle_clone != 0, true );
   pnt.Release();
   circle_clone->get_Center(&pnt);
   pnt->get_X(&cgx);
   pnt->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,3.0), true );
   TRY_TEST( IsEqual(cgy,5.0), true );
   circle_clone->get_Radius(&val);
   TRY_TEST( IsEqual(val,radius), true );

   //
   // PolyPoints
   //
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,37);
   
   // Create a PolyShape and check its section properties
   CComPtr<IPolyShape> polyShape;
   polyShape.CoCreateInstance( CLSID_PolyShape );
   polyShape->AddPoints( coll );

   CComQIPtr<IShape> polyShape_IShape(polyShape);

   props.Release();
   polyShape_IShape->get_ShapeProperties(&props);

   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   cg.Release();
   props->get_Centroid(&cg);
   TRY_TEST( IsEqual(area,M_PI*radius*radius), true );
   TRY_TEST( IsEqual(ixx,M_PI*radius*radius*radius*radius/4,0.1), true );
   TRY_TEST( IsEqual(iyy,M_PI*radius*radius*radius*radius/4,0.1), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,3.0), true );
   TRY_TEST( IsEqual(cgy,5.0), true );
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   //
   // ClipWithLine
   //

   center.Release();
   circle->get_Center(&center);
   center->Move(0,0);

   p1->Move(0,0);
   p2->Move(20,20);
   line->ThroughPoints( p1, p2 );

   // Clip with a simple line through the center of the circle
   // Verify by checking area.
   CComPtr<IShape> clip;
   TRY_TEST( shape->ClipWithLine(NULL,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipWithLine(line,NULL),  E_POINTER );
   TRY_TEST( shape->ClipWithLine(line,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   props.Release();
   clip->get_ShapeProperties(&props);
   props->get_Area(&area);
   Float64 testArea = 0.5*M_PI*radius*radius;
   TRY_TEST( IsEqual(area,testArea), true );

   // Clip against line such that the entire circle remains
   p1->Move(0,50);
   p2->Move(20,70);
   line->ThroughPoints(p1,p2);
   clip.Release();
   TRY_TEST( shape->ClipWithLine(line,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   props.Release();
   clip->get_ShapeProperties(&props);
   props->get_Area(&area);
   TRY_TEST( IsEqual(area,M_PI*radius*radius), true );
   CComQIPtr<ICircle> clipCircle(clip);
   TRY_TEST( clipCircle != 0, true );

   // Clip against line such that the entire circle is removed
   p1->Move(0,-50);
   p2->Move(20,-70);
   line->ThroughPoints(p1,p2);
   clip.Release();
   TRY_TEST( shape->ClipWithLine(line,&clip), S_OK );
   TRY_TEST( clip == 0, true );

   //
   // ClipIn
   //

   // Clip out a square the is entirely contained within the circle
   center.Release();
   circle->get_Center(&center);
   center->Move(0,0);
   circle->put_Radius(10.0);

   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );
   clipRect->put_Left(-5);
   clipRect->put_Right(5);
   clipRect->put_Bottom(-5);
   clipRect->put_Top(5);

   clip.Release();
   TRY_TEST( shape->ClipIn(NULL,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,NULL), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );

   // Check the area of the clipped shape. It should be 100
   props.Release();
   clip->get_ShapeProperties(&props);
   props->get_Area(&area);
   TRY_TEST( IsEqual(area,100.0,0.001), true );

   // Clip with a rectange that is larger than the circle.
   // A clone of the circle should be returned
   clipRect->put_Left(-500);
   clipRect->put_Right(500);
   clipRect->put_Bottom(-500);
   clipRect->put_Top(500);

   clip.Release();
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   circle_clone.Release();
   clip->QueryInterface( &circle_clone );
   TRY_TEST( circle_clone != 0, true );

   // Clip away the top half of the circle
   // Verify by checking the area (should be half the area of the circle)
   clipRect->put_Left(-500);
   clipRect->put_Right(500);
   clipRect->put_Bottom(-500);
   clipRect->put_Top(0);

   clip.Release();
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   props.Release();
   clip->get_ShapeProperties(&props);
   props->get_Area(&area);
   TRY_TEST( IsEqual(area,0.5*M_PI*radius*radius,0.01), true );

   // Entire clipping rectangle is above the circle
   clipRect->put_Left(-500);
   clipRect->put_Right(500);
   clipRect->put_Top(3*radius);
   clipRect->put_Bottom(2*radius);
   
   clip.Release();
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK);
   TRY_TEST( clip == 0, true );

   // Entire clipping rectangle is below the circle
   clipRect->put_Left(-500);
   clipRect->put_Right(500);
   clipRect->put_Top(-2*radius);
   clipRect->put_Bottom(-3*radius);
   
   clip.Release();
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK);
   TRY_TEST( clip == 0, true );

   // Entire clipping rectangle is left of the circle
   clipRect->put_Left(-500);
   clipRect->put_Right(-400);
   clipRect->put_Top(2*radius);
   clipRect->put_Bottom(-2*radius);
   
   clip.Release();
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK);
   TRY_TEST( clip == 0, true );

   // Entire clipping rectangle is right of the circle
   clipRect->put_Left(400);
   clipRect->put_Right(500);
   clipRect->put_Top(2*radius);
   clipRect->put_Bottom(-2*radius);
   
   clip.Release();
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK);
   TRY_TEST( clip == 0, true );
}

void CTestCircle::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   position.CoCreateInstance( CLSID_Circle );

   CComQIPtr<ICircle> circle(position);
   CComPtr<IPoint2d> center;
   center.CoCreateInstance( CLSID_Point2d );
   center->put_X(3);
   center->put_Y(5);
   circle->putref_Center(center);

   Float64 radius = 10;
   circle->put_Radius(radius);

   //
   // MoveEx (Provides full coverage of Offset)
   //
   CComPtr<IPoint2d> from;
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(10,10);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(110,110);

   TRY_TEST( position->MoveEx(NULL,to), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,NULL), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to), S_OK );
   Float64 x,y;
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,103.0), true );
   TRY_TEST(IsEqual(y,105.0), true );

   //
   // OffsetEx
   //
   center->Move(3,5);
   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(100);
   size->put_Dy(100);
   TRY_TEST( position->OffsetEx(NULL), E_INVALIDARG );
   TRY_TEST( position->OffsetEx(size), S_OK );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,103.0), true );
   TRY_TEST(IsEqual(y,105.0), true );

   //
   // LocatorPoint property
   //
   center->Move(3,5);
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,NULL), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,NULL), E_POINTER );

   // BottomLeft
   to->Move(90,90);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomLeft, &from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,90.0), true );
   TRY_TEST( IsEqual(y,90.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomCenter
   to->Move(100,90);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,90.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomRight
   to->Move(110,90);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,110.0), true );
   TRY_TEST( IsEqual(y,90.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterLeft
   to->Move(90,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,90.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterCenter
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterRight
   to->Move(110,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,110.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopLeft
   to->Move(90,110);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,90.0), true );
   TRY_TEST( IsEqual(y,110.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopCenter
   to->Move(100,110);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,110.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopRight
   to->Move(110,110);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,110.0), true );
   TRY_TEST( IsEqual(y,110.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // HookPoint
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpHookPoint, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpHookPoint, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   //
   // RotateEx (Provides coverage of Rotate)
   //
   center->Move(10,0);
   CComPtr<IPoint2d> c;
   c.CoCreateInstance( CLSID_Point2d );
   c->put_X(0);
   c->put_Y(0);

   TRY_TEST( position->RotateEx(NULL,M_PI/2), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI/2), S_OK );
   center->get_X(&x);
   center->get_Y(&y);
   TRY_TEST(IsEqual(x, 0.0), true );
   TRY_TEST(IsEqual(y,10.0), true );
}

void CTestCircle::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_Circle ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICircle ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}

void CTestCircle::TestIObjectSafety()
{
   CComPtr<IObjectSafety> safety;
   TRY_TEST( safety.CoCreateInstance( CLSID_Circle ), S_OK );
   TRY_TEST( safety != 0, true );

   DWORD dwSupported;
   DWORD dwEnabled;
   
   TRY_TEST( safety->SetInterfaceSafetyOptions( IID_IUnknown, INTERFACESAFE_FOR_UNTRUSTED_CALLER, INTERFACESAFE_FOR_UNTRUSTED_CALLER), S_OK);

   TRY_TEST( safety->GetInterfaceSafetyOptions( IID_ICircle, &dwSupported, &dwEnabled ), S_OK );
   TRY_TEST( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   TRY_TEST( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );

   TRY_TEST( safety->GetInterfaceSafetyOptions( IID_IStructuredStorage2, &dwSupported, &dwEnabled ), S_OK );
   TRY_TEST( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   TRY_TEST( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );

   TRY_TEST( safety->GetInterfaceSafetyOptions( IID_IShape, &dwSupported, &dwEnabled ), S_OK );
   TRY_TEST( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   TRY_TEST( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   
   TRY_TEST( safety->GetInterfaceSafetyOptions( IID_IXYPosition, &dwSupported, &dwEnabled ), S_OK );
   TRY_TEST( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   TRY_TEST( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
}
