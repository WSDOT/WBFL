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

// TestTriangle.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestTriangle.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestTriangle)
{
public:
   TEST_METHOD(TestITriangle)
   {
         CComPtr<ITriangle> tri;
         ASSERT_EQ( tri.CoCreateInstance( CLSID_Triangle ), S_OK );

         // Verify initialization. Height, Width, and Offset should be zero.
         Float64 h, w, offset;
         CComPtr<IPoint2d> hookPnt;
         Float64 x,y;

         ASSERT_EQ( tri->get_Height(nullptr), E_POINTER );
         ASSERT_EQ( tri->get_Height(&h), S_OK );
         ASSERT_EQ( tri->get_Width(nullptr), E_POINTER );
         ASSERT_EQ( tri->get_Width(&w), S_OK );
         ASSERT_EQ( tri->get_Offset(nullptr), E_POINTER );
         ASSERT_EQ( tri->get_Offset(&offset), S_OK );
         ASSERT_EQ( tri->get_HookPoint(nullptr), E_POINTER );
         ASSERT_EQ( tri->get_HookPoint(&hookPnt), S_OK );

         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);

         ASSERT_EQ( IsZero(h), true );
         ASSERT_EQ( IsZero(w), true );
         ASSERT_EQ( IsZero(offset), true );
         ASSERT_EQ( IsZero(x), true );
         ASSERT_EQ( IsZero(y), true );

         // Test properties
         ASSERT_EQ( tri->put_Height(-5), S_OK );
         ASSERT_EQ( tri->put_Width(-5), S_OK );
         ASSERT_EQ( tri->put_Offset(5), S_OK );
         ASSERT_EQ( tri->putref_HookPoint(nullptr), E_INVALIDARG );
         hookPnt.Release();
         hookPnt.CoCreateInstance( CLSID_Point2d );
         hookPnt->Move(10,10);
         ASSERT_EQ( tri->putref_HookPoint(hookPnt), S_OK );

         ASSERT_EQ( tri->get_Height(&h), S_OK );
         ASSERT_EQ( tri->get_Width(&w), S_OK );
         ASSERT_EQ( tri->get_Offset(&offset), S_OK );
         ASSERT_EQ( IsEqual(h,-5.0), true );
         ASSERT_EQ( IsEqual(w,-5.0), true );
         ASSERT_EQ( IsEqual(offset,5.0), true );


         // Test Interface Pointers
         CComPtr<IShape> shape;
         ASSERT_EQ(tri->get_Shape(nullptr), E_POINTER );
         ASSERT_EQ(tri->get_Shape(&shape), S_OK );
         ASSERT_EQ(shape != nullptr,true );

         CComPtr<IXYPosition> position;
         ASSERT_EQ(tri->get_XYPosition(nullptr), E_POINTER );
         ASSERT_EQ(tri->get_XYPosition(&position), S_OK );
         ASSERT_EQ(position != nullptr,true );

         CComPtr<IUnknown> punk1;
         CComPtr<IUnknown> punk2;
         CComPtr<IUnknown> punk3;
         tri->QueryInterface(&punk1);
         shape->QueryInterface(&punk2);
         position->QueryInterface(&punk3);
         ASSERT_EQ( punk1 == punk2, true );
         ASSERT_EQ( punk1 == punk3, true );
         ASSERT_EQ( punk2 == punk3, true );
   }

   TEST_METHOD(TestIShape)
   {
         Float64 h,w,offset,x,y;

         CComPtr<IShape> shape;
         shape.CoCreateInstance( CLSID_Triangle );

         CComQIPtr<ITriangle> tri(shape);
         CComPtr<IPoint2d> hookPnt;
         hookPnt.CoCreateInstance( CLSID_Point2d );
         hookPnt->Move(0,0);

         tri->putref_HookPoint(hookPnt);
         tri->put_Height(5);
         tri->put_Width(5);
         tri->put_Offset(0);

         CComPtr<IShapeProperties> props;
         ASSERT_EQ(shape->get_ShapeProperties(nullptr), E_POINTER);
         ASSERT_EQ(shape->get_ShapeProperties(&props), S_OK);
         Float64 area, ixx, iyy, ixy, cgx, cgy;
         CComPtr<IPoint2d> cg;

         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         cg.Release();
         props->get_Centroid(&cg);
         ASSERT_EQ(IsEqual(area, 12.5), true);
         ASSERT_EQ(IsEqual(ixx, 17.3611111111111), true);
         ASSERT_EQ(IsEqual(iyy, 17.3611111111111), true);
         ASSERT_EQ(IsEqual(ixy, -8.6805555555555), true);
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ(IsEqual(cgx, 1.666666666666666666), true);
         ASSERT_EQ(IsEqual(cgy, 1.666666666666666666), true);
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ(cst, csCentroidal);

         tri->putref_HookPoint(hookPnt);
         tri->put_Height(-5);
         tri->put_Width(-5);
         tri->put_Offset(0);

      //                Y
      //                |
      //        W = -5  | (0,0)
      //   ----.--------+------------ X
      // (-5,0) \       |
      //         \      |
      //          \     |  H = -5
      //           \    |
      //            \   |  Offset = 0
      //             \  |
      //              \ |
      //               \. (0,-5)
      //                |

         //
         // ShapeProperties
         //
         props.Release();
         ASSERT_EQ( shape->get_ShapeProperties(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_ShapeProperties(&props), S_OK );
         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         cg.Release();
         props->get_Centroid(&cg);
         ASSERT_EQ( IsEqual(area,12.5), true );
         ASSERT_EQ( IsEqual(ixx,17.3611111111111), true );
         ASSERT_EQ( IsEqual(iyy,17.3611111111111), true );
         ASSERT_EQ( IsEqual(ixy,-8.6805555555555), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,-1.666666666666666666), true );
         ASSERT_EQ( IsEqual(cgy,-1.666666666666666666), true );
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         //
         // BoundingBox
         //
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );

         Float64 val;
         Float64 xleft,xright,ytop,ybottom;

         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,-5.0), true );
         props->get_Xleft(&xleft);
         ASSERT_EQ(IsEqual(xleft,cgx-val),true);

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );
         props->get_Xright(&xright);
         ASSERT_EQ(IsEqual(xright,val-cgx),true);

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );
         props->get_Ytop(&ytop);
         ASSERT_EQ(IsEqual(ytop,val-cgy),true);

         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val,-5.0), true );
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(ybottom,cgy-val),true);

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val,17.0710678119), true );

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
         ASSERT_EQ( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
         ASSERT_EQ( shape->FurthestDistance(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,55.000), true );

         // shape on left
         p1->Move(0,-50);
         p2->Move(100,-50);
         line->ThroughPoints(p1,p2);
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,-45.0), true );

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(-10,-10);
         ASSERT_EQ( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
         ASSERT_EQ( shape->PointInShape( pnt, nullptr ), E_POINTER);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(-1,-1);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_TRUE );

         pnt->Move(0,0);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ( shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ( shape->Clone(&clone), S_OK );

         CComQIPtr<ITriangle> triangle_clone(clone);
         ASSERT_EQ( triangle_clone != nullptr, true );
         pnt.Release();
         triangle_clone->get_HookPoint(&pnt);
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
         ASSERT_EQ( triangle_clone->get_Height(&h), S_OK );
         ASSERT_EQ( triangle_clone->get_Width(&w), S_OK );
         ASSERT_EQ( triangle_clone->get_Offset(&offset), S_OK );
         ASSERT_EQ( IsEqual(h,-5.0), true );
         ASSERT_EQ( IsEqual(w,-5.0), true );
         ASSERT_EQ( IsEqual(offset,0.0), true );

         //
         // PolyPoints
         //
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,3);

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 5> points;
         ULONG fetched;
         Enum->Next(3,&points[0],&fetched);
         ASSERT_EQ( fetched, 3 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-5.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,-5.0), true );

         //
         // ClipWithLine
         //

         // Setup line (45 deg line, through 0,0)
         p1->Move(0,0);
         p2->Move(10,10);

         CComPtr<ILine2d> clipLine;
         clipLine.CoCreateInstance( CLSID_Line2d );
         clipLine->ThroughPoints(p1,p2);

         CComPtr<IShape> clip;
         ASSERT_EQ( shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipWithLine(clipLine,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipWithLine(clipLine,&clip), S_OK );

         coll.Release();
         Enum.Release();
         points[0].Release();
         points[1].Release();
         points[2].Release();
         points[3].Release();

         ASSERT_EQ( clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,4 );

         coll->get__Enum(&Enum);
         Enum->Next(4,&points[0],&fetched);
         ASSERT_EQ( fetched, 4 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-2.5), true );
         ASSERT_EQ( IsEqual(y,-2.5), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,-5.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         //
         // ClipIn
         //

         // Create clipping rect (make a trapizoid with height 3)
         CComPtr<IRect2d> clipRect;
         clipRect.CoCreateInstance( CLSID_Rect2d );
         clipRect->put_Left(-100);
         clipRect->put_Right(100);
         clipRect->put_Top(100);
         clipRect->put_Bottom(-3);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipIn(clipRect,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );
         coll.Release();
         Enum.Release();
         points[0].Release();
         points[1].Release();
         points[2].Release();
         points[3].Release();
         points[4].Release();

         ASSERT_EQ( clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,5 );

         coll->get__Enum(&Enum);
         Enum->Next(5,&points[0],&fetched);
         ASSERT_EQ( fetched, 5 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-5.0), true );
         ASSERT_EQ( IsEqual(y, 0.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-2.0), true );
         ASSERT_EQ( IsEqual(y,-3.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 0.0), true );
         ASSERT_EQ( IsEqual(y,-3.0), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
   }

   TEST_METHOD(TestIXYPosition)
   {
         Float64 x,y;

         CComPtr<IXYPosition> position;
         position.CoCreateInstance( CLSID_Triangle );

         CComQIPtr<ITriangle> tri(position);
         CComQIPtr<IShape> shape(position);

         CComPtr<IPoint2d> hookPnt;
         hookPnt.CoCreateInstance( CLSID_Point2d );
         hookPnt->Move(0,0);

         tri->putref_HookPoint(hookPnt);
         tri->put_Height(-5);
         tri->put_Width(-5);
         tri->put_Offset(0);

         //
         // MoveEx (tests Offset as well)
         //
         CComPtr<IPoint2d> from;
         from.CoCreateInstance( CLSID_Point2d );
         from->Move(0,0);

         CComPtr<IPoint2d> to;
         to.CoCreateInstance( CLSID_Point2d );
         to->Move(100,100);

         ASSERT_EQ( position->MoveEx(nullptr,to), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to), S_OK );

         // Check the points
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,3);

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 5> points;
         ULONG fetched;
         Enum->Next(3,&points[0],&fetched);
         ASSERT_EQ( fetched, 3 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,95.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,95.0), true );

         //
         // OffsetEx
         //

         // Move the triangle back to where it was
         hookPnt->Move(0,0);

         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(100);
         size->put_Dy(100);

         ASSERT_EQ(position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ(position->OffsetEx(size), S_OK);

         // Check the points
         coll.Release();
         Enum.Release();
         points[0].Release();
         points[1].Release();
         points[2].Release();

         shape->get_PolyPoints(&coll);
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,3);

         coll->get__Enum(&Enum);
         Enum->Next(3,&points[0],&fetched);
         ASSERT_EQ( fetched, 3 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,95.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,95.0), true );

         //
         // LocatorPoint property
         //
         hookPnt->Move(0,0);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         hookPnt->Move(0,0);
         to->Move(95,95);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,95.0), true );
         ASSERT_EQ( IsEqual(y,95.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // BottomCenter
         hookPnt->Move(0,0);
         to->Move(97.5,95);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,97.5), true );
         ASSERT_EQ( IsEqual(y,95.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // BottomRight
         hookPnt->Move(0,0);
         to->Move(100,95);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y, 95.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterLeft
         hookPnt->Move(0,0);
         to->Move(95,97.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,95.0), true );
         ASSERT_EQ( IsEqual(y,97.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterCenter
         hookPnt->Move(0,0);
         to->Move(97.5,97.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,97.5), true );
         ASSERT_EQ( IsEqual(y,97.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterRight
         hookPnt->Move(0,0);
         to->Move(100,97.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y, 97.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopLeft
         hookPnt->Move(0,0);
         to->Move(95,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 95.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopCenter
         hookPnt->Move(0,0);
         to->Move(97.5,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 97.5), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopRight
         hookPnt->Move(0,0);
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // HookPoint
         hookPnt->Move(0,0);
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpHookPoint, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpHookPoint, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         //
         // RotateEx (Provides coverage of Rotate)
         //
         hookPnt->Move(10,10);
         CComPtr<IPoint2d> c;
         c.CoCreateInstance( CLSID_Point2d );
         c->put_X(0);
         c->put_Y(0);

         ASSERT_EQ( position->RotateEx(nullptr,M_PI/2), E_INVALIDARG );
         ASSERT_EQ( position->RotateEx(c,M_PI/2), S_OK );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,-10.0), true );
         ASSERT_EQ(IsEqual(y, 10.0), true );

         // Check the points
         coll.Release();
         Enum.Release();
         points[0].Release();
         points[1].Release();
         points[2].Release();

         shape->get_PolyPoints(&coll);
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,3);

         coll->get__Enum(&Enum);
         Enum->Next(3,&points[0],&fetched);
         ASSERT_EQ( fetched, 3 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-10.0), true );
         ASSERT_EQ( IsEqual(y, 10.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-10.0), true );
         ASSERT_EQ( IsEqual(y,  5.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-5.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Triangle ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ITriangle ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests