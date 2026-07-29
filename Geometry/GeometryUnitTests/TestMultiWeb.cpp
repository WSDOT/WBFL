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

// TestMultiWeb.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestMultiWeb.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestMultiWeb)
{
public:
   TEST_METHOD(TestIMultiWeb)
   {
         CComPtr<IMultiWeb> beam;
         //ASSERT_EQ( beam.CoCreateInstance(CLSID_UBeam), S_OK );
         HRESULT hr =  beam.CoCreateInstance(CLSID_MultiWeb);

         // Verify initialization. All dimensions should be zero.
         // Hook point (bottom center) should be zero.
         Float64 val;
         WebIndexType lval;
         CComPtr<IPoint2d> pntVal;

         ASSERT_EQ( beam->get_D1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_T1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_T1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_T2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_T2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_WebCount(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_WebCount(&lval), S_OK );
         ASSERT_EQ( lval == 0, true );

         ASSERT_EQ( beam->get_HookPoint(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_HookPoint(&pntVal), S_OK );
         pntVal->get_X(&val);
         ASSERT_EQ( IsZero(val), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsZero(val), true );

         // Test properties
         ASSERT_EQ( beam->put_D1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D1(6), S_OK );
         beam->get_D1(&val);
         ASSERT_EQ( IsEqual(val,6.0), true );

         ASSERT_EQ( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D2(21), S_OK );
         beam->get_D2(&val);
         ASSERT_EQ( IsEqual(val,21.0), true );

         ASSERT_EQ( beam->put_T1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_T1(7.25), S_OK );
         beam->get_T1(&val);
         ASSERT_EQ( IsEqual(val,7.25), true );

         ASSERT_EQ( beam->put_T2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_T2(5.25), S_OK );
         beam->get_T2(&val);
         ASSERT_EQ( IsEqual(val,5.25), true );

         ASSERT_EQ( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W1(13.125), S_OK );
         beam->get_W1(&val);
         ASSERT_EQ( IsEqual(val,13.125), true );

         ASSERT_EQ( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W2(12), S_OK );
         beam->get_W2(&val);
         ASSERT_EQ( IsEqual(val,12.0), true );

      //   ASSERT_EQ( beam->put_WebCount(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_WebCount(3), S_OK );
         beam->get_WebCount(&lval);
         ASSERT_EQ( lval,3 );

         pntVal->Move(14,14);
         ASSERT_EQ( beam->putref_HookPoint(nullptr), E_INVALIDARG );
         ASSERT_EQ( beam->putref_HookPoint(pntVal), S_OK );
         pntVal.Release();
         beam->get_HookPoint(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         //
         // Height,TopFlangeWidth,BottomFlangeWidth,AvgWebWidth
         //
         ASSERT_EQ(beam->get_Height(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_Height(&val), S_OK );
         ASSERT_EQ(IsEqual(val,27.0), true );

         ASSERT_EQ(beam->get_TopFlangeWidth(nullptr),E_POINTER);
         ASSERT_EQ(beam->get_TopFlangeWidth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,72.0),true);

         ASSERT_EQ(beam->get_AvgWebWidth(nullptr),E_POINTER);
         ASSERT_EQ(beam->get_AvgWebWidth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,18.75),true);

         // Test Interface Pointers
         CComPtr<IShape> shape;
         ASSERT_EQ(beam->get_Shape(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_Shape(&shape), S_OK );
         ASSERT_EQ(shape != nullptr,true );

         CComPtr<IXYPosition> position;
         ASSERT_EQ(beam->get_XYPosition(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_XYPosition(&position), S_OK );
         ASSERT_EQ(position != nullptr,true );

         CComPtr<IUnknown> punk1;
         CComPtr<IUnknown> punk2;
         CComPtr<IUnknown> punk3;
         beam->QueryInterface(&punk1);
         shape->QueryInterface(&punk2);
         position->QueryInterface(&punk3);
         ASSERT_EQ( punk1 == punk2, true );
         ASSERT_EQ( punk1 == punk3, true );
         ASSERT_EQ( punk2 == punk3, true );
   }

   TEST_METHOD(TestIShape)
   {
         CComPtr<IShape> shape;
         ASSERT_EQ( shape.CoCreateInstance( CLSID_MultiWeb ), S_OK );
         CComQIPtr<IMultiWeb> beam(shape);

         // Use some real dimensions (2'-3" by 6' with 3 webs)
         beam->put_D1( 6.00);
         beam->put_D2(21.00);
         beam->put_W1(13.125);
         beam->put_W2(12.0);
         beam->put_T1(7.25);
         beam->put_T2(5.25);
         beam->put_WebCount(3);

         //
         // Bounding Box
         //
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );

         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,-36.), true );

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val, 36.), true );

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val, 0.00), true );

         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val,-27.), true );

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
         ASSERT_EQ( IsEqual(area,825.75), true );
         ASSERT_EQ( IsEqual(ixx, 50135.30160), true );
         ASSERT_EQ( IsEqual(iyy, 285211.20703), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,0.0), true );
         ASSERT_EQ( IsEqual(cgy, -9.1702997275204368), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         Float64 xleft,xright,ytop,ybottom;
         props->get_Xleft(&xleft);
         props->get_Xright(&xright);
         props->get_Ytop(&ytop);
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(xleft, 36.),true);
         ASSERT_EQ(IsEqual(xright,36.),true);
         ASSERT_EQ(IsEqual(ytop,9.17029972752044),true);
         ASSERT_EQ(IsEqual(ybottom,17.8297002724796),true);

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val,276.142776249772), true );

         //
         // FurthestDistance
         //
         CComPtr<IPoint2d> p1;
         p1.CoCreateInstance( CLSID_Point2d );

         CComPtr<IPoint2d> p2;
         p2.CoCreateInstance( CLSID_Point2d );

         CComPtr<ILine2d> line;
         line.CoCreateInstance( CLSID_Line2d );

         // Shape on right of line
         p1->Move(-100,20);
         p2->Move(100,20);
         line->ThroughPoints(p1,p2);
         Float64 dist;
         ASSERT_EQ( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
         ASSERT_EQ( shape->FurthestDistance(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,47.000), true );

         // shape on left of line
         p1->Move(100,20);
         p2->Move(-100,20);
         line->ThroughPoints(p1,p2);
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,-20.0), true );

         // 
         // PolyPoints
         //
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );

         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 19 );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 19> points;
         ULONG fetched;
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         Float64 x,y;
         int i = 0;
         TEST_POINT(points, 0., 0.);
         TEST_POINT(points, -36., 0.);
         TEST_POINT(points, -36., -6.);
         TEST_POINT(points, -22.875, -6.);
         TEST_POINT(points, -21.875, -27.);
         TEST_POINT(points, -16.625, -27.);
         TEST_POINT(points, -15.625, -6.);
         TEST_POINT(points, -3.625, -6.);
         TEST_POINT(points, -2.625, -27.);
         TEST_POINT(points, 0., -27.);
         TEST_POINT(points, 2.625, -27.);
         TEST_POINT(points, 3.625, -6.);
         TEST_POINT(points, 15.625, -6.);
         TEST_POINT(points, 16.625, -27.);
         TEST_POINT(points, 21.875, -27.);
         TEST_POINT(points, 22.875, -6.);
         TEST_POINT(points, 36., -6.);
         TEST_POINT(points, 36., 0.);
         TEST_POINT(points, 0., 0.);

         ASSERT_EQ(i, cPoints);

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ(shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ(shape->Clone(&clone), S_OK);

         CComQIPtr<IMultiWeb> beamClone(clone);
         ASSERT_EQ( beamClone != nullptr, true );

         beamClone->get_W1(&val);
         ASSERT_EQ( IsEqual(val,13.125), true);

         beamClone->get_W2(&val);
         ASSERT_EQ( IsEqual(val,12.00), true);

         beamClone->get_D1(&val);
         ASSERT_EQ( IsEqual(val,6.00), true);

         beamClone->get_D2(&val);
         ASSERT_EQ( IsEqual(val,21.00), true);

         beamClone->get_T1(&val);
         ASSERT_EQ( IsEqual(val, 7.25), true);

         beamClone->get_T2(&val);
         ASSERT_EQ( IsEqual(val, 5.25), true);

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(0.0, -5.0);

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
         p1->Move(-100,-10.0);
         p2->Move( 100,-10.0);

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
         ASSERT_EQ( cPoints, 13 );

         coll->get__Enum(&Enum);
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         i = 0;
         TEST_POINT(points, -22.68452, -10.);
         TEST_POINT(points, -21.875, -27.);
         TEST_POINT(points, -16.625, -27.);
         TEST_POINT(points, -15.81548, -10.);
         TEST_POINT(points, -3.43452, -10.);
         TEST_POINT(points, -2.625, -27.);
         TEST_POINT(points, 0., -27.);
         TEST_POINT(points, 2.625, -27.);
         TEST_POINT(points, 3.43452, -10.);
         TEST_POINT(points, 15.81548, -10.);
         TEST_POINT(points, 16.625, -27.);
         TEST_POINT(points, 21.875, -27.);
         TEST_POINT(points, 22.68452, -10.);


         ASSERT_EQ(i, cPoints);

         // clip in other direction
         p1->Move( 100,-10.0);
         p2->Move(-100,-10.0);

         clipLine->ThroughPoints(p1,p2);

         clip.Release();
         ASSERT_EQ(shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ(shape->ClipWithLine(clipLine,nullptr), E_POINTER );
         ASSERT_EQ(shape->ClipWithLine(clipLine,&clip), S_OK );
         ASSERT_EQ( clip != nullptr, true );

         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         ASSERT_EQ(clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 18);

         coll->get__Enum(&Enum);
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         i = 0;
         TEST_POINT(points, 0., 0.);
         TEST_POINT(points, -36., 0.);
         TEST_POINT(points, -36., -6.);
         TEST_POINT(points, -22.875, -6.);
         TEST_POINT(points, -22.68452, -10.);
         TEST_POINT(points, -15.815476, -10.);
         TEST_POINT(points, -15.625, -6.);
         TEST_POINT(points, -3.625, -6.);
         TEST_POINT(points, -3.43452, -10.);
         TEST_POINT(points, 3.43452, -10.);
         TEST_POINT(points, 3.625, -6.);
         TEST_POINT(points, 15.625, -6.);
         TEST_POINT(points, 15.815476, -10.);
         TEST_POINT(points, 22.68452, -10.);
         TEST_POINT(points, 22.875, -6.);
         TEST_POINT(points, 36., -6.);
         TEST_POINT(points, 36., 0.);
         TEST_POINT(points, 0., 0.);

         ASSERT_EQ(i, cPoints);

         //
         // ClipIn
         //
         clip.Release();

         CComPtr<IRect2d> clipRect;
         clipRect.CoCreateInstance( CLSID_Rect2d );
         clipRect->put_Left(-100);
         clipRect->put_Right(100);
         clipRect->put_Top(0);
         clipRect->put_Bottom(-7);

         ASSERT_EQ( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipIn(clipRect,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );

         // Verify clip by checking points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         ASSERT_EQ(clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 18 );

         ATLTRACE("Trace of Points for MultiWeb - count = %d \n", cPoints);
         ATLTRACE("  pt         X         Y\n");
         ATLTRACE("---------------------------------\n");
         for (IndexType ip = 0; ip<cPoints; ip++)
         {
            CComPtr<IPoint2d> pnt;
            coll->get_Item(ip, &pnt);
            Float64 x, y;
            pnt->get_X(&x);
            pnt->get_Y(&y);
            ATLTRACE(" %4d  %10f %10f \n", ip, x, y);
         }
         ATLTRACE("---------------------------\n");


         coll->get__Enum(&Enum);
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         i = 0;
         TEST_POINT(points, 0., 0.);
         TEST_POINT(points, -36., 0.);
         TEST_POINT(points, -36., -6.);
         TEST_POINT(points, -22.875, -6.);
         TEST_POINT(points, -22.82738, -7.);
         TEST_POINT(points, -15.67262, -7.);
         TEST_POINT(points, -15.625, -6.);
         TEST_POINT(points, -3.625, -6.);
         TEST_POINT(points, -3.57738, -7.);
         TEST_POINT(points, 3.57738, -7.);
         TEST_POINT(points, 3.625, -6.);
         TEST_POINT(points, 15.625, -6.);
         TEST_POINT(points, 15.67262, -7.);
         TEST_POINT(points, 22.82738, -7.);
         TEST_POINT(points, 22.875, -6.);
         TEST_POINT(points, 36., -6.);
         TEST_POINT(points, 36., 0.);
         TEST_POINT(points, 0., 0.);


         ASSERT_EQ(i, cPoints);
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ( position.CoCreateInstance( CLSID_MultiWeb ), S_OK);

         CComQIPtr<IMultiWeb> beam(position);
         CComQIPtr<IShape> shape(position);

         CComPtr<IPoint2d> hookPnt;
         hookPnt.CoCreateInstance( CLSID_Point2d );
         hookPnt->Move(0,0);

         // Use some real dimensions (2'-3" by 6' with 3 webs)
         beam->putref_HookPoint(hookPnt);
         beam->put_D1( 6.00);
         beam->put_D2(21.00);
         beam->put_W1(13.125);
         beam->put_W2(12.0);
         beam->put_T1(7.25);
         beam->put_T2(5.25);
         beam->put_WebCount(3);

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
         ASSERT_EQ( cPoints,19);

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 19> points;
         ULONG fetched;
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         Float64 x,y;
         int i = 0;
         TEST_POINT(points, 100., 100.);
         TEST_POINT(points, 64., 100.);
         TEST_POINT(points, 64., 94.);
         TEST_POINT(points, 77.125, 94.);
         TEST_POINT(points, 78.125, 73.);
         TEST_POINT(points, 83.375, 73.);
         TEST_POINT(points, 84.375, 94.);
         TEST_POINT(points, 96.375, 94.);
         TEST_POINT(points, 97.375, 73.);
         TEST_POINT(points, 100., 73.);
         TEST_POINT(points, 102.625, 73.);
         TEST_POINT(points, 103.625, 94.);
         TEST_POINT(points, 115.625, 94.);
         TEST_POINT(points, 116.625, 73.);
         TEST_POINT(points, 121.875, 73.);
         TEST_POINT(points, 122.875, 94.);
         TEST_POINT(points, 136., 94.);
         TEST_POINT(points, 136., 100.);
         TEST_POINT(points, 100., 100.);

         ASSERT_EQ(i, cPoints);

         //
         // OffsetEx
         //

         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(-100);
         size->put_Dy(-100);

         ASSERT_EQ(position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ(position->OffsetEx(size), S_OK);

         // Check the points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         shape->get_PolyPoints(&coll);
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,19);

         coll->get__Enum(&Enum);
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         i = 0;
         TEST_POINT(points, 0., 0.);
         TEST_POINT(points, -36., 0.);
         TEST_POINT(points, -36., -6.);
         TEST_POINT(points, -22.875, -6.);
         TEST_POINT(points, -21.875, -27.);
         TEST_POINT(points, -16.625, -27.);
         TEST_POINT(points, -15.625, -6.);
         TEST_POINT(points, -3.625, -6.);
         TEST_POINT(points, -2.625, -27.);
         TEST_POINT(points, 0., -27.);
         TEST_POINT(points, 2.625, -27.);
         TEST_POINT(points, 3.625, -6.);
         TEST_POINT(points, 15.625, -6.);
         TEST_POINT(points, 16.625, -27.);
         TEST_POINT(points, 21.875, -27.);
         TEST_POINT(points, 22.875, -6.);
         TEST_POINT(points, 36., -6.);
         TEST_POINT(points, 36., 0.);
         TEST_POINT(points, 0., 0.);

         ASSERT_EQ(i, cPoints);

         //
         // LocatorPoint property
         //
         hookPnt->Move(0,0);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         hookPnt->Move(0,0);
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,136.000), true );
         ASSERT_EQ(IsEqual(y,127.00), true );

         // BottomCenter
         hookPnt->Move(0.0,0.0);
         to->Move(100.000,100.000);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,127.0), true );

         // BottomRight
         hookPnt->Move(0,0);
         to->Move(100.000,100.000);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,64.0), true );
         ASSERT_EQ(IsEqual(y,127.0), true );

         // CenterLeft
         hookPnt->Move(0,0);
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,136.0), true );
         ASSERT_EQ(IsEqual(y,113.5), true );

         // CenterCenter
         hookPnt->Move(0,0);
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,113.5), true );

         // CenterRight
         hookPnt->Move(0,0);
         to->Move(100.0,100.0);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,64.0), true );
         ASSERT_EQ(IsEqual(y,113.5), true );

         // TopLeft
         hookPnt->Move(0,0);
         to->Move(100.0,100.0);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,136.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopCenter
         hookPnt->Move(0,0);
         to->Move(100.0,100.0);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopRight
         hookPnt->Move(0,0);
         to->Move(100.0,100.0);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 64.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // HookPoint
         hookPnt->Move(0,0);
         to->Move(100,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpHookPoint, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpHookPoint, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );
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
         ASSERT_EQ( cPoints,19);

         coll->get__Enum(&Enum);
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         i = 0;
         TEST_POINT(points, 0., 0.);
         TEST_POINT(points, 36., 0.);
         TEST_POINT(points, 36., 6.);
         TEST_POINT(points, 22.875, 6.);
         TEST_POINT(points, 21.875, 27.);
         TEST_POINT(points, 16.625, 27.);
         TEST_POINT(points, 15.625, 6.);
         TEST_POINT(points, 3.625, 6.);
         TEST_POINT(points, 2.625, 27.);
         TEST_POINT(points, 0., 27.);
         TEST_POINT(points, -2.625, 27.);
         TEST_POINT(points, -3.625, 6.);
         TEST_POINT(points, -15.625, 6.);
         TEST_POINT(points, -16.625, 27.);
         TEST_POINT(points, -21.875, 27.);
         TEST_POINT(points, -22.875, 6.);
         TEST_POINT(points, -36., 6.);
         TEST_POINT(points, -36., 0.);
         TEST_POINT(points, 0., 0.);

         ASSERT_EQ(i, cPoints); 
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_MultiWeb ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IMultiWeb ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests