///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestGenericShape.cpp: implementation of the CTestGenericShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestGenericShape.h"
#include <array>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestGenericShape::CTestGenericShape()
{

}

CTestGenericShape::~CTestGenericShape()
{

}

void CTestGenericShape::Test()
{
   TestIGenericShape();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestGenericShape::TestIGenericShape()
{
   CComPtr<IGenericShape> generic_shape;
   TRY_TEST( generic_shape.CoCreateInstance( CLSID_GenericShape ), S_OK );

   // Verify initialization. Properties should be zero. HookPoint at (0,0);
   Float64 area, ixx, iyy, ixy;
   Float64 x,y;
   CComPtr<IPoint2d> hookPnt;

   TRY_TEST( generic_shape->get_Area(nullptr), E_POINTER );
   TRY_TEST( generic_shape->get_Area(&area), S_OK );
   TRY_TEST( generic_shape->get_Ixx(nullptr), E_POINTER );
   TRY_TEST( generic_shape->get_Ixx(&ixx), S_OK );
   TRY_TEST( generic_shape->get_Iyy(nullptr), E_POINTER );
   TRY_TEST( generic_shape->get_Iyy(&iyy), S_OK );
   TRY_TEST( generic_shape->get_Ixy(nullptr), E_POINTER );
   TRY_TEST( generic_shape->get_Ixy(&ixy), S_OK );
   TRY_TEST( generic_shape->get_Centroid(nullptr), E_POINTER );
   TRY_TEST( generic_shape->get_Centroid(&hookPnt), S_OK );
   hookPnt->Location(&x,&y);

   TRY_TEST( IsZero(area),      true );
   TRY_TEST( IsZero(ixx),       true );
   TRY_TEST( IsZero(iyy),       true );
   TRY_TEST( IsZero(ixy),       true );
   TRY_TEST( IsZero(x),         true );
   TRY_TEST( IsZero(y),         true );

   TRY_TEST( generic_shape->put_Area(5), S_OK );
   TRY_TEST( generic_shape->put_Perimeter(10), S_OK);
   TRY_TEST( generic_shape->put_Ixx(1), S_OK );
   TRY_TEST( generic_shape->put_Iyy(2), S_OK );
   TRY_TEST( generic_shape->put_Ixy(0), S_OK );
   hookPnt->put_X(10);
   hookPnt->put_Y(20);

   TRY_TEST( generic_shape->get_Area(&area), S_OK );
   TRY_TEST( generic_shape->get_Ixx(&ixx), S_OK );
   TRY_TEST( generic_shape->get_Iyy(&iyy), S_OK );
   TRY_TEST( generic_shape->get_Ixy(&ixy), S_OK );

   TRY_TEST( IsEqual(area,5.0), true );
   TRY_TEST( IsEqual(ixx,1.0), true );
   TRY_TEST( IsEqual(iyy,2.0), true );
   TRY_TEST( IsEqual(ixy,0.0), true );

   CComPtr<IPoint2d> test_hookPnt;
   TRY_TEST( generic_shape->get_Centroid(&test_hookPnt), S_OK );
   test_hookPnt->get_X(&x);
   test_hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,20.0), true );

   CComPtr<IPoint2d> new_hookPnt;
   new_hookPnt.CoCreateInstance( CLSID_Point2d );
   new_hookPnt->Move(-50,-60);
   TRY_TEST( generic_shape->putref_Centroid(nullptr), E_INVALIDARG );
   TRY_TEST( generic_shape->putref_Centroid(new_hookPnt), S_OK);
   test_hookPnt.Release();
   TRY_TEST( generic_shape->get_Centroid(&test_hookPnt), S_OK );
   test_hookPnt->get_X(&x);
   test_hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,-50.0), true );
   TRY_TEST( IsEqual(y,-60.0), true );

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(generic_shape->get_Shape(nullptr), E_POINTER );
   TRY_TEST(generic_shape->get_Shape(&shape), S_OK );
   TRY_TEST(shape != nullptr,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(generic_shape->get_XYPosition(nullptr), E_POINTER );
   TRY_TEST(generic_shape->get_XYPosition(&position), S_OK );
   TRY_TEST(position != nullptr,true );

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   generic_shape->QueryInterface(&punk1);
   shape->QueryInterface(&punk2);
   position->QueryInterface(&punk3);
   TRY_TEST( punk1 == punk2, true );
   TRY_TEST( punk1 == punk3, true );
   TRY_TEST( punk2 == punk3, true );
}

void CTestGenericShape::TestIShape()
{
   Float64 x,y;

   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_GenericShape ), S_OK );

   CComQIPtr<IGenericShape> generic_shape(shape);
   TRY_TEST( generic_shape != nullptr, true );

   CComPtr<IPoint2d> hookPnt;
   generic_shape->get_Centroid(&hookPnt);
   hookPnt->put_X(10);
   hookPnt->put_Y(20);

   TRY_TEST( generic_shape->put_Area(5), S_OK );
   TRY_TEST( generic_shape->put_Perimeter(10), S_OK);
   TRY_TEST( generic_shape->put_Ixx(1), S_OK );
   TRY_TEST( generic_shape->put_Iyy(2), S_OK );
   TRY_TEST( generic_shape->put_Ixy(0), S_OK );

   //
   // ShapeProperties
   //
   CComPtr<IShapeProperties> props;
   TRY_TEST( shape->get_ShapeProperties(nullptr), E_POINTER );
   TRY_TEST( shape->get_ShapeProperties(&props), S_OK );

   Float64 area, ixx, iyy, ixy, cgx, cgy;
   CComPtr<IPoint2d> cg;

   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   cg.Release();
   props->get_Centroid(&cg);
   TRY_TEST( IsEqual(area,5.0), true );
   TRY_TEST( IsEqual(ixx,1.0), true );
   TRY_TEST( IsEqual(iyy,2.0), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,10.0), true );
   TRY_TEST( IsEqual(cgy,20.0), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,0.0),true);
   TRY_TEST(IsEqual(xright,0.0),true);
   TRY_TEST(IsEqual(ytop,0.0),true);
   TRY_TEST(IsEqual(ybottom,0.0),true);

   //
   // BoundingBox
   //
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(nullptr), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   Float64 val;
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,10.0), true );
   box->get_Right(&val);
   TRY_TEST( IsEqual(val,10.0), true );
   box->get_Top(&val);
   TRY_TEST( IsEqual(val,20.0), true );
   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,20.0), true );

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(nullptr), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,10.0), true );

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
   TRY_TEST( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,nullptr), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,30.000), true );

   // shape on left
   p1->Move(0,-50);
   p2->Move(100,-50);
   line->ThroughPoints(p1,p2);
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-70.0), true );

   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(-10,-10);
   TRY_TEST( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
   TRY_TEST( shape->PointInShape( pnt, nullptr ), E_POINTER);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   pnt->Move(10,20);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_TRUE );

   pnt->Move(15,20);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST( shape->Clone(nullptr), E_POINTER );
   TRY_TEST( shape->Clone(&clone), S_OK );

   CComQIPtr<IGenericShape> generic_shape_clone(clone);
   TRY_TEST( generic_shape_clone != nullptr, true );
   pnt.Release();
   generic_shape_clone->get_Centroid(&pnt);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,20.0), true );

   TRY_TEST( generic_shape_clone->get_Area(&area), S_OK );
   TRY_TEST( generic_shape_clone->get_Ixx(&ixx), S_OK );
   TRY_TEST( generic_shape_clone->get_Iyy(&iyy), S_OK );
   TRY_TEST( generic_shape_clone->get_Ixy(&ixy), S_OK );

   TRY_TEST( IsEqual(area,5.0), true );
   TRY_TEST( IsEqual(ixx,1.0), true );
   TRY_TEST( IsEqual(iyy,2.0), true );
   TRY_TEST( IsEqual(ixy,0.0), true );

   //
   // PolyPoints
   //
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(nullptr), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   IndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,1 );
   
   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>, 5> points;
   ULONG fetched;
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 1 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,20.0), true );

   // Rotate the shape and test again
   CComQIPtr<IXYPosition> position(shape);
   hookPnt.Release();
   generic_shape->get_Centroid(&hookPnt);
   position->RotateEx(hookPnt,PI_OVER_2);
   coll.Release();
   Enum.Release();

   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,1 );
   
   coll->get__Enum(&Enum);
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 1 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,20.0), true );

   //
   // ClipWithLine
   //

   // start with new shape
   shape.Release();
   generic_shape.Release();
   position.Release();

   shape.CoCreateInstance( CLSID_GenericShape );
   shape.QueryInterface( &generic_shape );

   hookPnt.Release();
   generic_shape->get_Centroid(&hookPnt);
   generic_shape->put_Area(5);
   generic_shape->put_Perimeter(10);
   generic_shape->put_Ixx(1);
   generic_shape->put_Iyy(2);
   generic_shape->put_Ixy(0);
   hookPnt->put_X(10);
   hookPnt->put_Y(20);
   
   // Setup the clipping line

   // line to left of shape... clipping result is null
   p1->Move(0,0);
   p2->Move(20,20);

   CComPtr<ILine2d> clipLine;
   clipLine.CoCreateInstance( CLSID_Line2d );
   clipLine->ThroughPoints(p1,p2);

   CComPtr<IShape> clip;
   TRY_TEST( shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipWithLine(clipLine,nullptr), E_POINTER );
   TRY_TEST( shape->ClipWithLine(clipLine,&clip), S_OK );

   TRY_TEST( clip, nullptr );

   // line to right of shape
   p1->Move(0,20);
   p2->Move(20,40);
   clipLine->ThroughPoints(p1,p2);
   TRY_TEST( shape->ClipWithLine(clipLine,&clip), S_OK );

   coll.Release();
   Enum.Release();
   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


   TRY_TEST( clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,1 );
   
   coll->get__Enum(&Enum);
   Enum->Next(4,&points[0],&fetched);
   TRY_TEST( fetched, 1 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,20.0), true );

   //
   // ClipIn
   //

   // start with new shape
   clip.Release();
   shape.Release();
   generic_shape.Release();
   position.Release();

   shape.CoCreateInstance( CLSID_GenericShape );
   shape.QueryInterface( &generic_shape );

   hookPnt.Release();
   generic_shape->get_Centroid(&hookPnt);
   generic_shape->put_Area(5);
   generic_shape->put_Perimeter(10);
   generic_shape->put_Ixx(1);
   generic_shape->put_Iyy(2);
   generic_shape->put_Ixy(0);
   hookPnt->put_X(10);
   hookPnt->put_Y(20);

   // Setup the clipping rect
   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );

   // not in rect
   clipRect->put_Left(100);
   clipRect->put_Right(200);
   clipRect->put_Top(25);
   clipRect->put_Bottom(15);

   TRY_TEST( shape->ClipIn(nullptr,&clip),     E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,nullptr),  E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   TRY_TEST( clip,nullptr);

   // in rect
   clipRect->put_Left(-100);
   clipRect->put_Right(100);
   clipRect->put_Top(25);
   clipRect->put_Bottom(15);
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );

   coll.Release();
   Enum.Release();
   points[0].Release();
   points[1].Release();
   points[2].Release();
   points[3].Release();
   points[4].Release();

   TRY_TEST( clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,1 );
   
   coll->get__Enum(&Enum);
   Enum->Next(4,&points[0],&fetched);
   TRY_TEST( fetched, 1 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,10.0), true );
   TRY_TEST( IsEqual(y,20.0), true );
}

void CTestGenericShape::TestIXYPosition()
{
   Float64 x,y;

   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_GenericShape ), S_OK );

   CComQIPtr<IGenericShape> generic_shape(position);
   TRY_TEST( generic_shape != nullptr, true );

   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   generic_shape->get_Centroid(&hookPnt);
   generic_shape->put_Area(5);
   generic_shape->put_Perimeter(10);
   generic_shape->put_Ixx(1);
   generic_shape->put_Iyy(2);
   generic_shape->put_Ixy(0);
   hookPnt->put_X(10);
   hookPnt->put_Y(20);

   //
   // OffsetEx and Offset
   //
   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(10);
   size->put_Dy(20);
   TRY_TEST( position->OffsetEx(nullptr), E_INVALIDARG );
   TRY_TEST( position->OffsetEx(size), S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,20.), true );
   TRY_TEST( IsEqual(y,40.), true );

   TRY_TEST( position->Offset(10,20), S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,30.), true );
   TRY_TEST( IsEqual(y,60.), true );

   //
   // MoveEx
   //
   CComPtr<IPoint2d> from;
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(10,10);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(110,110);

   TRY_TEST( position->MoveEx(nullptr,to),    E_INVALIDARG );
   TRY_TEST( position->MoveEx(from, nullptr), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to),    S_OK );

   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);

   TRY_TEST( IsEqual(x,130.), true );
   TRY_TEST( IsEqual(y,160.), true );

   //
   // LocatorPoint property
   //
   hookPnt->Move(0,0);

   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

   // BottomLeft
   to->Move(95,85);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,95.0), true );
   TRY_TEST( IsEqual(y,85.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,95.), true );
   TRY_TEST( IsEqual(y,85.), true );

   // BottomCenter
   to->Move(100,85);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y, 85.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y, 85.), true );

   // BottomRight
   to->Move(105,85);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpBottomRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpBottomRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,105.0), true );
   TRY_TEST( IsEqual(y, 85.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,105.), true );
   TRY_TEST( IsEqual(y, 85.), true );

   // CenterLeft
   to->Move(95,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x, 95.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x, 95.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterCenter
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // CenterRight
   to->Move(105,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpCenterRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpCenterRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,105.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,105.), true );
   TRY_TEST( IsEqual(y,100.), true );

   // TopLeft
   to->Move(95,115);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopLeft,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopLeft,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x, 95.0), true );
   TRY_TEST( IsEqual(y,115.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x, 95.), true );
   TRY_TEST( IsEqual(y,115.), true );

   // TopCenter
   to->Move(100,115);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopCenter,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopCenter,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,115.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,115.), true );

   // TopRight
   to->Move(105,115);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpTopRight,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpTopRight,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,105.0), true );
   TRY_TEST( IsEqual(y,115.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,105.), true );
   TRY_TEST( IsEqual(y,115.), true );

   // HookPoint
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint(lpHookPoint,to), S_OK );
   TRY_TEST( position->get_LocatorPoint(lpHookPoint,&from), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST( IsEqual(x,100.), true );
   TRY_TEST( IsEqual(y,100.), true );

   //
   // Rotate and RotateEx
   //
   hookPnt->Move(10,20);
   CComPtr<IPoint2d> rotPoint;
   rotPoint.CoCreateInstance( CLSID_Point2d );

   // Rotate about the origin of the coordinate system and check the coordintes of the rectangle
   rotPoint->Move(0,0);

   TRY_TEST( position->RotateEx(nullptr,PI_OVER_2), E_INVALIDARG );
   TRY_TEST( position->RotateEx(rotPoint,PI_OVER_2), S_OK );

   CComPtr<IPoint2dCollection> coll;
   shape->get_PolyPoints(&coll);
   IndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,1 );
   
   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>, 5> points;
   ULONG fetched;
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 1 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-20.0), true );
   TRY_TEST( IsEqual(y, 10.0), true );

   // Test section properties of the rectangle rotated 45 deg.
   hookPnt->Move(0,0);
   rotPoint->Move(0,0);
   position->RotateEx(rotPoint,M_PI/4);

   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);
   Float64 area, ixx, iyy, ixy;
   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   
   TRY_TEST( IsEqual(area,5.), true );
   TRY_TEST( IsEqual(ixx,1.5), true );
   TRY_TEST( IsEqual(iyy,1.5), true );
   TRY_TEST( IsEqual(ixy,-0.5), true );
}

void CTestGenericShape::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_GenericShape ), S_OK );
   TRY_TEST( eInfo != nullptr, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IGenericShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
