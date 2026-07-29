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

// TestTrafficBarrier.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestTrafficBarrier.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestTrafficBarrier)
{
public:
   TEST_METHOD(TestITrafficBarrier)
   {
         CComPtr<ITrafficBarrier> barrier;
         ASSERT_EQ( barrier.CoCreateInstance( CLSID_TrafficBarrier ), S_OK );

         // Verify default values
         Float64 val;
         CComPtr<IPoint2d> pntVal;
         TrafficBarrierOrientation tboVal;

         ASSERT_EQ( barrier->get_HookPoint(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_HookPoint(&pntVal), S_OK );
         pntVal->get_X(&val);
         ASSERT_EQ( IsZero(val), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_Orientation(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_Orientation(&tboVal), S_OK );
         ASSERT_EQ( tboVal, tboLeft );

         ASSERT_EQ( barrier->get_X1(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_X1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_X2(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_X2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_X3(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_X3(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_X4(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_X4(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_X5(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_X5(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_Y1(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_Y1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_Y2(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_Y2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_Y3(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_Y3(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( barrier->get_Y4(nullptr), E_POINTER );
         ASSERT_EQ( barrier->get_Y4(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         // Test put property
         ASSERT_EQ( barrier->put_X1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_X1(12.0), S_OK );
         barrier->get_X1(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_X2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_X2(12.0), S_OK );
         barrier->get_X2(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_X3(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_X3(12.0), S_OK );
         barrier->get_X3(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_X4(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_X4(12.0), S_OK );
         barrier->get_X4(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_X5(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_X5(12.0), S_OK );
         barrier->get_X5(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_Y1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_Y1(12.0), S_OK );
         barrier->get_Y1(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_Y2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_Y2(12.0), S_OK );
         barrier->get_Y2(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_Y3(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_Y3(12.0), S_OK );
         barrier->get_Y3(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_Y4(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( barrier->put_Y4(12.0), S_OK );
         barrier->get_Y4(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

         ASSERT_EQ( barrier->put_Orientation(tboRight), S_OK );
         barrier->get_Orientation(&tboVal);
         ASSERT_EQ( tboVal, tboRight );

         ASSERT_EQ( barrier->putref_HookPoint(nullptr), E_INVALIDARG );
         ASSERT_EQ( barrier->putref_HookPoint(pntVal), S_OK );

         // Test Interface Pointers
         CComPtr<IShape> shape;
         ASSERT_EQ(barrier->get_Shape(nullptr), E_POINTER );
         ASSERT_EQ(barrier->get_Shape(&shape), S_OK );
         ASSERT_EQ(shape != nullptr,true );

         CComPtr<IXYPosition> position;
         ASSERT_EQ(barrier->get_XYPosition(nullptr), E_POINTER );
         ASSERT_EQ(barrier->get_XYPosition(&position), S_OK );
         ASSERT_EQ(position != nullptr,true );

         CComPtr<IUnknown> punk1;
         CComPtr<IUnknown> punk2;
         CComPtr<IUnknown> punk3;
         barrier->QueryInterface(&punk1);
         shape->QueryInterface(&punk2);
         position->QueryInterface(&punk3);
         ASSERT_EQ( punk1 == punk2, true );
         ASSERT_EQ( punk1 == punk3, true );
         ASSERT_EQ( punk2 == punk3, true );
   }

   TEST_METHOD(TestIShape)
   {
         CComPtr<IShape> shape;
         ASSERT_EQ( shape.CoCreateInstance( CLSID_TrafficBarrier ), S_OK );
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
         ASSERT_EQ( IsEqual(area,417.625), true );
         ASSERT_EQ( IsEqual(ixx,44747.861222833), true );
         ASSERT_EQ( IsEqual(iyy,6262.5842348081), true );
         ASSERT_EQ( IsEqual(ixy,-5237.9423208781), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,-0.23279581961489), true );
         ASSERT_EQ( IsEqual(cgy,13.909333532874), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         //
         // Bounding Box
         //
         Float64 xleft,xright,ytop,ybottom;
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );

         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,-8.25), true );
         props->get_Xleft(&xleft);
         ASSERT_EQ(IsEqual(xleft,cgx-val),true);

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val,10.5), true );
         props->get_Xright(&xright);
         ASSERT_EQ(IsEqual(xright,val-cgx),true);

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val,32.00), true );
         props->get_Ytop(&ytop);
         ASSERT_EQ(IsEqual(ytop,val-cgy),true);

         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val,-7.50), true );
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(ybottom,cgy-val),true);

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val,106.44267779471), true ); // Get value from PGSuper

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
         ASSERT_EQ( IsEqual(dist,57.500), true );

         // shape on left
         p1->Move(0,-50);
         p2->Move(100,-50);
         line->ThroughPoints(p1,p2);
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,-42.50), true );

         // 
         // PolyPoints
         //
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );

         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 8 );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 8> points;
         ULONG fetched;
         Enum->Next(8,&points[0],&fetched);
         ASSERT_EQ( fetched, 8 );

         Float64 x,y;

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.5), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.5), true );
         ASSERT_EQ( IsEqual(y,3.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,5.625), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,3.25), true );
         ASSERT_EQ( IsEqual(y,32.0), true );

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-8.25), true );
         ASSERT_EQ( IsEqual(y,32.0), true );

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-3.5), true );
         ASSERT_EQ( IsEqual(y,-7.5), true );

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,-7.5), true );

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ(shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ(shape->Clone(&clone), S_OK);

         CComQIPtr<ITrafficBarrier> barrierClone(clone);
         ASSERT_EQ( barrierClone != nullptr, true );

         barrierClone->get_X1(&val);
         ASSERT_EQ( IsEqual(val,3.5), true);

         barrierClone->get_X2(&val);
         ASSERT_EQ( IsEqual(val,10.5), true);

         barrierClone->get_X3(&val);
         ASSERT_EQ( IsEqual(val,11.5), true);

         barrierClone->get_X4(&val);
         ASSERT_EQ( IsEqual(val,2.375), true);

         barrierClone->get_X5(&val);
         ASSERT_EQ( IsEqual(val,4.875), true);

         barrierClone->get_Y1(&val);
         ASSERT_EQ( IsEqual(val,3.0), true);

         barrierClone->get_Y2(&val);
         ASSERT_EQ( IsEqual(val,7.0), true);

         barrierClone->get_Y3(&val);
         ASSERT_EQ( IsEqual(val,32.0), true);

         barrierClone->get_Y4(&val);
         ASSERT_EQ( IsEqual(val,7.5), true);

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(-1.0, 1.0);

         ASSERT_EQ( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
         ASSERT_EQ( shape->PointInShape(pnt,nullptr), E_POINTER );
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_TRUE );

         pnt->Move(500,500);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(0,0); // Point on perimeter
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

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
         ASSERT_EQ(shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ(shape->ClipWithLine(clipLine,nullptr), E_POINTER );
         ASSERT_EQ(shape->ClipWithLine(clipLine,&clip), S_OK );
         ASSERT_EQ( clip != nullptr, true );

         // Verify clip by checking points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         ASSERT_EQ(clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 7 );

         coll->get__Enum(&Enum);
         Enum->Next(7,&points[0],&fetched);
         ASSERT_EQ( fetched, 7 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.5), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.5), true );
         ASSERT_EQ( IsEqual(y,3.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-4.762658), true );
         ASSERT_EQ( IsEqual(y,3.0), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-3.5), true );
         ASSERT_EQ( IsEqual(y,-7.5), true );

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,-7.5), true );

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

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

         ASSERT_EQ( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipIn(clipRect,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );

         // Verify clip by checking points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         ASSERT_EQ(clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 4 );

         coll->get__Enum(&Enum);
         Enum->Next(5,&points[0],&fetched);
         ASSERT_EQ( fetched, 4 );

         int i = 0;
         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,10.5), true );
         ASSERT_EQ( IsEqual(y,3.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 9.803571), true );
         ASSERT_EQ( IsEqual(y, 4.0000), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-4.88291), true );
         ASSERT_EQ( IsEqual(y, 4.000), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-4.762658), true );
         ASSERT_EQ( IsEqual(y, 3.000), true );
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ( position.CoCreateInstance( CLSID_TrafficBarrier), S_OK);

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

         ASSERT_EQ( position->MoveEx(nullptr,to), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to), S_OK );

         // Check the points
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,8);

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 8> points;
         ULONG fetched;
         Enum->Next(8,&points[0],&fetched);
         ASSERT_EQ( fetched, 8 );

         Float64 x,y;

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.5), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.5), true );
         ASSERT_EQ( IsEqual(y,103.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.625), true );
         ASSERT_EQ( IsEqual(y,110.0), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,103.25), true );
         ASSERT_EQ( IsEqual(y,132.0), true );

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,91.75), true );
         ASSERT_EQ( IsEqual(y,132.0), true );

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,96.5), true );
         ASSERT_EQ( IsEqual(y,92.5), true );

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,92.5), true );

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
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         shape->get_PolyPoints(&coll);
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,8);

         coll->get__Enum(&Enum);
         Enum->Next(8,&points[0],&fetched);
         ASSERT_EQ( fetched, 8 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.5), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.5), true );
         ASSERT_EQ( IsEqual(y,103.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.625), true );
         ASSERT_EQ( IsEqual(y,110.0), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,103.25), true );
         ASSERT_EQ( IsEqual(y,132.0), true );

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,91.75), true );
         ASSERT_EQ( IsEqual(y,132.0), true );

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,96.5), true );
         ASSERT_EQ( IsEqual(y,92.5), true );

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,92.5), true );

         //
         // MoveLocatorPointEx (Provides full coverage of MoveLocatorPoint)
         //
         hookPnt->Move(0,0);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         hookPnt->Move(0,0);
         to->Move(91.75,92.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,91.75), true );
         ASSERT_EQ( IsEqual(y,92.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // BottomCenter
         hookPnt->Move(0,0);
         to->Move(101.125,92.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,101.125), true );
         ASSERT_EQ( IsEqual(y,92.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // BottomRight
         hookPnt->Move(0,0);
         to->Move(110.5,92.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.5), true );
         ASSERT_EQ( IsEqual(y,92.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterLeft
         hookPnt->Move(0,0);
         to->Move(91.75,112.25);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,91.75), true );
         ASSERT_EQ( IsEqual(y,112.25), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterCenter
         hookPnt->Move(0,0);
         to->Move(101.125,112.25);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint(lpCenterCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint(lpCenterCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,101.125), true );
         ASSERT_EQ( IsEqual(y,112.25), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterRight
         hookPnt->Move(0,0);
         to->Move(110.5,112.25);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.5), true );
         ASSERT_EQ( IsEqual(y,112.25), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopLeft
         hookPnt->Move(0,0);
         to->Move(91.75,132);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,91.75), true );
         ASSERT_EQ( IsEqual(y,132.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopCenter
         hookPnt->Move(0,0);
         to->Move(101.125,132.0);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,101.125), true );
         ASSERT_EQ( IsEqual(y,132.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopRight
         hookPnt->Move(0,0);
         to->Move(110.5,132.0);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,110.5), true );
         ASSERT_EQ( IsEqual(y,132.0), true );
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
         hookPnt->Move(0,0);
         CComPtr<IPoint2d> c;
         c.CoCreateInstance( CLSID_Point2d );
         c->put_X(0);
         c->put_Y(0);

         ASSERT_EQ( position->RotateEx(nullptr,M_PI), E_INVALIDARG );
         ASSERT_EQ( position->RotateEx(c,M_PI), S_OK );

         // Check the points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         shape->get_PolyPoints(&coll);
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,8);

         coll->get__Enum(&Enum);
         Enum->Next(8,&points[0],&fetched);
         ASSERT_EQ( fetched, 8 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-10.5), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-10.5), true );
         ASSERT_EQ( IsEqual(y,-3.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-5.625), true );
         ASSERT_EQ( IsEqual(y,-10.0), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-3.25), true );
         ASSERT_EQ( IsEqual(y,-32.0), true );

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,8.25), true );
         ASSERT_EQ( IsEqual(y,-32.0), true );

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,3.5), true );
         ASSERT_EQ( IsEqual(y,7.5), true );

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,7.5), true );
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_TrafficBarrier ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ITrafficBarrier ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests