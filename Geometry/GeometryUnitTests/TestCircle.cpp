///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestCircle.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestCircle.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestCircle)
{
public:
   TEST_METHOD(TestICircle)
   {
         CComPtr<ICircle> circle;
         ASSERT_EQ( circle.CoCreateInstance( CLSID_Circle ), S_OK );

         // Verify initialization. Radius and center should be zero.
         Float64 r,x,y;
         CComPtr<IPoint2d> center;

         ASSERT_EQ( circle->get_Radius(nullptr), E_POINTER );
         ASSERT_EQ( circle->get_Radius(&r), S_OK );
         ASSERT_EQ( circle->get_Center(nullptr), E_POINTER );
         ASSERT_EQ( circle->get_Center(&center), S_OK );

         center->get_X(&x);
         center->get_Y(&y);

         ASSERT_EQ( IsZero(r), true );
         ASSERT_EQ( IsZero(x), true );
         ASSERT_EQ( IsZero(y), true );

         // Radius
         ASSERT_EQ( circle->put_Radius(-100), GEOMETRY_E_RADIUS );
         ASSERT_EQ( circle->put_Radius(100), S_OK );
         ASSERT_EQ( circle->get_Radius(&r), S_OK );
         ASSERT_EQ( IsEqual(r,100.0), true );

         // Center
         center.Release();
         center.CoCreateInstance( CLSID_Point2d );
         center->Move(15,20);
         ASSERT_EQ( circle->putref_Center(nullptr), E_INVALIDARG );
         ASSERT_EQ( circle->putref_Center(center), S_OK );

         CComPtr<IPoint2d> pnt;
         ASSERT_EQ( circle->get_Center(&pnt), S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,15.0), true );
         ASSERT_EQ( IsEqual(y,20.0), true );

         pnt->Move(3,5);
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ( IsEqual(x,3.0), true );
         ASSERT_EQ( IsEqual(y,5.0), true );

         // ThroughTwoPoints
         CComPtr<IPoint2d> p1, p2;
         p1.CoCreateInstance(CLSID_Point2d);
         p2.CoCreateInstance(CLSID_Point2d);
         p1->Move(15,10);
         p2->Move(15,10);
         ASSERT_EQ(circle->ThroughTwoPoints(nullptr,p2),E_INVALIDARG);
         ASSERT_EQ(circle->ThroughTwoPoints(p1,nullptr),E_INVALIDARG);
         ASSERT_EQ(circle->ThroughTwoPoints(p1,p2),GEOMETRY_E_COINCIDENTPOINTS);
         p1->Move(10,10);
         ASSERT_EQ(circle->ThroughTwoPoints(p1,p2),S_OK);
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ( IsEqual(x,12.5), true );
         ASSERT_EQ( IsEqual(y,10.0), true );
         circle->get_Radius(&r);
         ASSERT_EQ( IsEqual(r,2.5), true );

         // ThroughThreePoints
         CComPtr<IPoint2d> p3;
         p3.CoCreateInstance(CLSID_Point2d);
         p1->Move(15,10);
         p2->Move(15,10);
         p3->Move(15,10);
         ASSERT_EQ(circle->ThroughThreePoints(nullptr,p2,p3),E_INVALIDARG);
         ASSERT_EQ(circle->ThroughThreePoints(p1,nullptr,p3),E_INVALIDARG);
         ASSERT_EQ(circle->ThroughThreePoints(p1,p2,nullptr),E_INVALIDARG);
         ASSERT_EQ(circle->ThroughThreePoints(p1,p2,p3),GEOMETRY_E_COLINEAR);
         p1->Move(15,10);
         p2->Move(15,20);
         p3->Move(15,30);
         ASSERT_EQ(circle->ThroughThreePoints(p1,p2,p3),GEOMETRY_E_COLINEAR);
         p1->Move(10,10);
         p2->Move(20,10);
         p3->Move(15,15);
         ASSERT_EQ(circle->ThroughThreePoints(p1,p2,p3),S_OK);
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ( IsEqual(x,15.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );
         circle->get_Radius(&r);
         ASSERT_EQ( IsEqual(r,5.0), true );

         // ContainsPoint
         center->Move(10,10);
         circle->put_Radius(10);
         p1->Move(0,0);
         VARIANT_BOOL bResult;
         ASSERT_EQ(circle->ContainsPoint(nullptr,&bResult),E_INVALIDARG);
         ASSERT_EQ(circle->ContainsPoint(p1,nullptr),E_POINTER);
         ASSERT_EQ(circle->ContainsPoint(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_FALSE);
         p1->Move(20,10);
         ASSERT_EQ(circle->ContainsPoint(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_TRUE);
         p1->Move(30,5);
         ASSERT_EQ(circle->ContainsPoint(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_FALSE);
         p1->Move(9,9);
         ASSERT_EQ(circle->ContainsPoint(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_TRUE);
         ASSERT_EQ(circle->ContainsPoint(center,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_TRUE);

         // PointOnCircle
         center->Move(10,10);
         circle->put_Radius(10);
         p1->Move(0,0);
         ASSERT_EQ(circle->PointOnCircle(nullptr,&bResult),E_INVALIDARG);
         ASSERT_EQ(circle->PointOnCircle(p1,nullptr),E_POINTER);
         ASSERT_EQ(circle->PointOnCircle(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_FALSE);
         p1->Move(20,10);
         ASSERT_EQ(circle->PointOnCircle(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_TRUE);
         p1->Move(30,5);
         ASSERT_EQ(circle->PointOnCircle(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_FALSE);
         p1->Move(9,9);
         ASSERT_EQ(circle->PointOnCircle(p1,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_FALSE);
         ASSERT_EQ(circle->PointOnCircle(center,&bResult),S_OK);
         ASSERT_EQ(bResult,VARIANT_FALSE);

         // Test Interface Pointers
         CComPtr<IShape> shape;
         ASSERT_EQ(circle->get_Shape(nullptr), E_POINTER );
         ASSERT_EQ(circle->get_Shape(&shape), S_OK );
         ASSERT_EQ(shape != nullptr,true );

         CComPtr<IXYPosition> position;
         ASSERT_EQ(circle->get_XYPosition(nullptr), E_POINTER );
         ASSERT_EQ(circle->get_XYPosition(&position), S_OK );
         ASSERT_EQ(position != nullptr,true );

         CComPtr<IUnknown> punk1;
         CComPtr<IUnknown> punk2;
         CComPtr<IUnknown> punk3;
         circle->QueryInterface(&punk1);
         shape->QueryInterface(&punk2);
         position->QueryInterface(&punk3);
         ASSERT_EQ( punk1 == punk2, true );
         ASSERT_EQ( punk1 == punk3, true );
         ASSERT_EQ( punk2 == punk3, true );
   }

   TEST_METHOD(TestIShape)
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
         ASSERT_EQ( shape->get_ShapeProperties(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_ShapeProperties(&props), S_OK );
         Float64 area, ixx, iyy, ixy, cgx, cgy;
         CComPtr<IPoint2d> cg;

         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         cg.Release();
         props->get_Centroid(&cg);
         ASSERT_EQ( IsEqual(area,M_PI*radius*radius), true );
         ASSERT_EQ( IsEqual(ixx,M_PI*radius*radius*radius*radius/4), true );
         ASSERT_EQ( IsEqual(iyy,M_PI*radius*radius*radius*radius/4), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,3.0), true );
         ASSERT_EQ( IsEqual(cgy,5.0), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         Float64 xleft,xright,ytop,ybottom;
         props->get_Xleft(&xleft);
         props->get_Xright(&xright);
         props->get_Ytop(&ytop);
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(xleft,radius),true);
         ASSERT_EQ(IsEqual(xright,radius),true);
         ASSERT_EQ(IsEqual(ytop,radius),true);
         ASSERT_EQ(IsEqual(ybottom,radius),true);

         //
         // BoundingBox
         //
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );
         Float64 val;
         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,3-radius), true );
         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val,3+radius), true );
         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val,5+radius), true );
         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val,5-radius), true );

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val,TWO_PI*radius), true );

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
         ASSERT_EQ( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
         ASSERT_EQ( shape->FurthestDistance(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,110.0), true );

         // shape on left
         center->Move(50, 100);
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,-90.0), true );

         //
         // PointInShape
         //
         center->Move(3,5);
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(-10,-10);
         ASSERT_EQ( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
         ASSERT_EQ( shape->PointInShape( pnt, nullptr ), E_POINTER);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(3,5);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_TRUE );

         pnt->Move(3,15);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_TRUE );

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ( shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ( shape->Clone(&clone), S_OK );

         CComQIPtr<ICircle> circle_clone(clone);
         ASSERT_EQ( circle_clone != nullptr, true );
         pnt.Release();
         circle_clone->get_Center(&pnt);
         pnt->get_X(&cgx);
         pnt->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,3.0), true );
         ASSERT_EQ( IsEqual(cgy,5.0), true );
         circle_clone->get_Radius(&val);
         ASSERT_EQ( IsEqual(val,radius), true );

         //
         // PolyPoints
         //
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,37);

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
         ASSERT_EQ( IsEqual(area,M_PI*radius*radius), true );
         ASSERT_EQ( IsEqual(ixx,M_PI*radius*radius*radius*radius/4,0.1), true );
         ASSERT_EQ( IsEqual(iyy,M_PI*radius*radius*radius*radius/4,0.1), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,3.0), true );
         ASSERT_EQ( IsEqual(cgy,5.0), true );
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

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
         ASSERT_EQ( shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipWithLine(line,nullptr),  E_POINTER );
         ASSERT_EQ( shape->ClipWithLine(line,&clip), S_OK );
         ASSERT_EQ( clip != nullptr, true );
         props.Release();
         clip->get_ShapeProperties(&props);
         props->get_Area(&area);
         Float64 testArea = 0.5*M_PI*radius*radius;
         ASSERT_EQ( IsEqual(area,testArea), true );

         // Clip against line such that the entire circle remains
         p1->Move(0,50);
         p2->Move(20,70);
         line->ThroughPoints(p1,p2);
         clip.Release();
         ASSERT_EQ( shape->ClipWithLine(line,&clip), S_OK );
         ASSERT_EQ( clip != nullptr, true );
         props.Release();
         clip->get_ShapeProperties(&props);
         props->get_Area(&area);
         ASSERT_EQ( IsEqual(area,M_PI*radius*radius), true );
         CComQIPtr<ICircle> clipCircle(clip);
         ASSERT_EQ( clipCircle != nullptr, true );

         // Clip against line such that the entire circle is removed
         p1->Move(0,-50);
         p2->Move(20,-70);
         line->ThroughPoints(p1,p2);
         clip.Release();
         ASSERT_EQ( shape->ClipWithLine(line,&clip), S_OK );
         ASSERT_EQ( clip == 0, true );

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
         ASSERT_EQ( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipIn(clipRect,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );

         // Check the area of the clipped shape. It should be 100
         props.Release();
         clip->get_ShapeProperties(&props);
         props->get_Area(&area);
         ASSERT_EQ( IsEqual(area,100.0,0.001), true );

         // Clip with a rectange that is larger than the circle.
         // A clone of the circle should be returned
         clipRect->put_Left(-500);
         clipRect->put_Right(500);
         clipRect->put_Bottom(-500);
         clipRect->put_Top(500);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );
         circle_clone.Release();
         clip->QueryInterface( &circle_clone );
         ASSERT_EQ( circle_clone != nullptr, true );

         // Clip away the top half of the circle
         // Verify by checking the area (should be half the area of the circle)
         clipRect->put_Left(-500);
         clipRect->put_Right(500);
         clipRect->put_Bottom(-500);
         clipRect->put_Top(0);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );
         ASSERT_EQ( clip != nullptr, true );
         props.Release();
         clip->get_ShapeProperties(&props);
         props->get_Area(&area);
         ASSERT_EQ( IsEqual(area,0.5*M_PI*radius*radius,0.01), true );

         // Entire clipping rectangle is above the circle
         clipRect->put_Left(-500);
         clipRect->put_Right(500);
         clipRect->put_Top(3*radius);
         clipRect->put_Bottom(2*radius);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK);
         ASSERT_EQ( clip == 0, true );

         // Entire clipping rectangle is below the circle
         clipRect->put_Left(-500);
         clipRect->put_Right(500);
         clipRect->put_Top(-2*radius);
         clipRect->put_Bottom(-3*radius);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK);
         ASSERT_EQ( clip == 0, true );

         // Entire clipping rectangle is left of the circle
         clipRect->put_Left(-500);
         clipRect->put_Right(-400);
         clipRect->put_Top(2*radius);
         clipRect->put_Bottom(-2*radius);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK);
         ASSERT_EQ( clip == 0, true );

         // Entire clipping rectangle is right of the circle
         clipRect->put_Left(400);
         clipRect->put_Right(500);
         clipRect->put_Top(2*radius);
         clipRect->put_Bottom(-2*radius);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK);
         ASSERT_EQ( clip == 0, true );
   }

   TEST_METHOD(TestIXYPosition)
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

         ASSERT_EQ( position->MoveEx(nullptr,to), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to), S_OK );
         Float64 x,y;
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,103.0), true );
         ASSERT_EQ(IsEqual(y,105.0), true );

         //
         // OffsetEx
         //
         center->Move(3,5);
         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(100);
         size->put_Dy(100);
         ASSERT_EQ( position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ( position->OffsetEx(size), S_OK );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,103.0), true );
         ASSERT_EQ(IsEqual(y,105.0), true );

         //
         // LocatorPoint property
         //
         center->Move(3,5);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         to->Move(90,90);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomLeft, &from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,90.0), true );
         ASSERT_EQ( IsEqual(y,90.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // BottomCenter
         to->Move(100,90);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,90.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // BottomRight
         to->Move(110,90);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.0), true );
         ASSERT_EQ( IsEqual(y,90.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterLeft
         to->Move(90,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,90.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterCenter
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterRight
         to->Move(110,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopLeft
         to->Move(90,110);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,90.0), true );
         ASSERT_EQ( IsEqual(y,110.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopCenter
         to->Move(100,110);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,110.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopRight
         to->Move(110,110);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.0), true );
         ASSERT_EQ( IsEqual(y,110.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // HookPoint
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpHookPoint, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpHookPoint, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         //
         // RotateEx (Provides coverage of Rotate)
         //
         center->Move(10,0);
         CComPtr<IPoint2d> c;
         c.CoCreateInstance( CLSID_Point2d );
         c->put_X(0);
         c->put_Y(0);

         ASSERT_EQ( position->RotateEx(nullptr,M_PI/2), E_INVALIDARG );
         ASSERT_EQ( position->RotateEx(c,M_PI/2), S_OK );
         center->get_X(&x);
         center->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0), true );
         ASSERT_EQ(IsEqual(y,10.0), true );
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Circle ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ICircle ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }

   TEST_METHOD(TestIObjectSafety)
   {
         CComPtr<IObjectSafety> safety;
         ASSERT_EQ( safety.CoCreateInstance( CLSID_Circle ), S_OK );
         ASSERT_EQ( safety != nullptr, true );

         DWORD dwSupported;
         DWORD dwEnabled;

         ASSERT_EQ( safety->SetInterfaceSafetyOptions( IID_IUnknown, INTERFACESAFE_FOR_UNTRUSTED_CALLER, INTERFACESAFE_FOR_UNTRUSTED_CALLER), S_OK);

         ASSERT_EQ( safety->GetInterfaceSafetyOptions( IID_ICircle, &dwSupported, &dwEnabled ), S_OK );
         ASSERT_EQ( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
         ASSERT_EQ( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );

         ASSERT_EQ( safety->GetInterfaceSafetyOptions( IID_IShape, &dwSupported, &dwEnabled ), S_OK );
         ASSERT_EQ( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
         ASSERT_EQ( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );

         ASSERT_EQ( safety->GetInterfaceSafetyOptions( IID_IXYPosition, &dwSupported, &dwEnabled ), S_OK );
         ASSERT_EQ( dwSupported, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
         ASSERT_EQ( dwEnabled, INTERFACESAFE_FOR_UNTRUSTED_CALLER );
   }
};
} // namespace GeometryUnitTests