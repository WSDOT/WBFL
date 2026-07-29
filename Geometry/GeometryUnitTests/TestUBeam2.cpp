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

// TestUBeam2.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestUBeam2.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestUBeam2)
{
public:
   TEST_METHOD(TestIUBeam2)
   {
         CComPtr<IUBeam2> beam;
         ASSERT_EQ( beam.CoCreateInstance(CLSID_UBeam2), S_OK );

         // Verify initialization. All dimensions should be zero.
         // Hook point (bottom center) should be zero.
         Float64 val;
         CComPtr<IPoint2d> pntVal;

         ASSERT_EQ( beam->get_D1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D3(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D3(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D4(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D4(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D5(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D5(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_D6(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_D6(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_T(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_T(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );


         ASSERT_EQ( beam->get_W1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W2(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W2(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W3(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W3(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W4(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W4(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W5(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W5(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W6(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W6(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_W7(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W7(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_C1(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_C1(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_HookPoint(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_HookPoint(&pntVal), S_OK );
         pntVal->get_X(&val);
         ASSERT_EQ( IsZero(val), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsZero(val), true );

         // Test properties
         ASSERT_EQ( beam->put_D1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D1(14), S_OK );
         beam->get_D1(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D2(14), S_OK );
         beam->get_D2(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_D3(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D3(14), S_OK );
         beam->get_D3(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_D4(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D4(14), S_OK );
         beam->get_D4(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_D5(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D5(14), S_OK );
         beam->get_D5(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_D6(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_D6(14), S_OK );
         beam->get_D6(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W1(14), S_OK );
         beam->get_W1(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W2(14), S_OK );
         beam->get_W2(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_W3(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W3(14), S_OK );
         beam->get_W3(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_W4(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W4(14), S_OK );
         beam->get_W4(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_W5(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W5(14), S_OK );
         beam->get_W5(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_W6(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W6(14), S_OK );
         beam->get_W6(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_W7(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_W7(14), S_OK );
         beam->get_W7(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_C1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_C1(14), S_OK );
         beam->get_C1(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

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

         // Use some real dimensions (TXDOT U40 girder)
         beam->put_W1(55);
         beam->put_W2(89);
         beam->put_W3(3);
         beam->put_W4(0.375);
         beam->put_W5(8.25);
         beam->put_W6(15.75);
         beam->put_W7(1.75);
         beam->put_D1(40);
         beam->put_D2(8.25);
         beam->put_D3(3);
         beam->put_D4(0.875);
         beam->put_D5(5.875);
         beam->put_D6(21.625);
         beam->put_C1(0.0);

         ASSERT_EQ(beam->get_Height(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_Height(&val), S_OK );
         ASSERT_EQ(IsEqual(val,40.0), true );

         ASSERT_EQ(beam->get_Slope(0,nullptr),E_POINTER);
         ASSERT_EQ(beam->get_Slope(-1,&val),E_INVALIDARG);
         ASSERT_EQ(beam->get_Slope(2,&val),E_INVALIDARG);
         ASSERT_EQ(beam->get_Slope(0,&val),S_OK);
         ASSERT_EQ(IsEqual(val,-3.970149),true);
         ASSERT_EQ(beam->get_Slope(1,&val),S_OK);
         ASSERT_EQ(IsEqual(val,3.970149),true);

         ASSERT_EQ(beam->get_TopWidth(nullptr),E_POINTER);
         ASSERT_EQ(beam->get_TopWidth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,89.0),true);

         ASSERT_EQ(beam->get_TopFlangeWidth(nullptr),E_POINTER);
         ASSERT_EQ(beam->get_TopFlangeWidth(&val),S_OK);
         ASSERT_EQ(IsEqual(val,15.75),true);

         ASSERT_EQ(beam->get_WebSpacing(nullptr),E_POINTER);
         ASSERT_EQ(beam->get_WebSpacing(&val),S_OK);
         ASSERT_EQ(IsEqual(val,70.022086466165405),true);

         ASSERT_EQ(beam->get_WebLocation(0,nullptr),E_POINTER);
         ASSERT_EQ(beam->get_WebLocation(-1,&val),E_INVALIDARG);
         ASSERT_EQ(beam->get_WebLocation(2,&val),E_INVALIDARG);
         ASSERT_EQ(beam->get_WebLocation(0,&val),S_OK);
         ASSERT_EQ(IsEqual(val,-35.011043233082702),true);
         ASSERT_EQ(beam->get_WebLocation(1,&val),S_OK);
         ASSERT_EQ(IsEqual(val,35.011043233082702),true);

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
         ASSERT_EQ( shape.CoCreateInstance( CLSID_UBeam2 ), S_OK );
         CComQIPtr<IUBeam2> beam(shape);

         // Use some real dimensions (TXDOT U40 girder)
         beam->put_W1(55);
         beam->put_W2(89);
         beam->put_W3(3);
         beam->put_W4(0.375);
         beam->put_W5(8.25);
         beam->put_W6(15.75);
         beam->put_W7(1.75);
         beam->put_D1(40);
         beam->put_D2(8.25);
         beam->put_D3(3);
         beam->put_D4(0.875);
         beam->put_D5(5.875);
         beam->put_D6(21.625);

         //
         // Bounding Box
         //
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );

         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,-44.5), true );

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val, 44.5), true );

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val, 40.00), true );

         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val, 0.00), true );

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
         ASSERT_EQ( IsEqual(area,978.1015625), true );
         ASSERT_EQ( IsEqual(ixx, 183371.372367286), true );
         ASSERT_EQ( IsEqual(iyy, 672244.006479706), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,0.0), true );
         ASSERT_EQ( IsEqual(cgy,16.3516905452245), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         Float64 xleft,xright,ytop,ybottom;
         props->get_Xleft(&xleft);
         props->get_Xright(&xright);
         props->get_Ytop(&ytop);
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(xleft,44.5),true);
         ASSERT_EQ(IsEqual(xright,44.5),true);
         ASSERT_EQ(IsEqual(ytop,23.6483094547755),true);
         ASSERT_EQ(IsEqual(ybottom,16.3516905452245),true);

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val,294.425976857583), true );

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
         p1->Move(0,20);
         p2->Move(100,20);
         line->ThroughPoints(p1,p2);
         Float64 dist;
         ASSERT_EQ( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
         ASSERT_EQ( shape->FurthestDistance(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,20.000), true );

         // shape on left
         p1->Move(0,-20);
         p2->Move(100,-20);
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
         std::array<CComPtr<IPoint2d>,19> points;
         ULONG fetched;
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         Float64 x,y;
         int i = 0;
         TEST_POINT(points, 0.000000, 0.000000);
         TEST_POINT(points, -27.500000, 0.000000);
         TEST_POINT(points, -35.875000, 33.250000);
         TEST_POINT(points, -44.125000, 34.125000);
         TEST_POINT(points, -44.500000, 40.000000);
         TEST_POINT(points, -28.750000, 40.000000);
         TEST_POINT(points, -27.000000, 18.375000);
         TEST_POINT(points, -25.205357, 11.250000);
         TEST_POINT(points, -22.205357, 8.250000);
         TEST_POINT(points, 0.000000, 8.250000);
         TEST_POINT(points, 22.205357, 8.250000);
         TEST_POINT(points, 25.205357, 11.250000);
         TEST_POINT(points, 27.000000, 18.375000);
         TEST_POINT(points, 28.750000, 40.000000);
         TEST_POINT(points, 44.500000, 40.000000);
         TEST_POINT(points, 44.125000, 34.125000);
         TEST_POINT(points, 35.875000, 33.250000);
         TEST_POINT(points, 27.500000, 0.000000);
         TEST_POINT(points, 0.000000, 0.000000);

         ASSERT_EQ(i, cPoints);

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ(shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ(shape->Clone(&clone), S_OK);

         CComQIPtr<IUBeam2> beamClone(clone);
         ASSERT_EQ( beamClone != nullptr, true );

         beamClone->get_W1(&val);
         ASSERT_EQ( IsEqual(val,55.00), true);

         beamClone->get_W2(&val);
         ASSERT_EQ( IsEqual(val,89.0), true);

         beamClone->get_W3(&val);
         ASSERT_EQ( IsEqual(val,3.00), true);

         beamClone->get_W4(&val);
         ASSERT_EQ( IsEqual(val, 0.375), true);

         beamClone->get_W5(&val);
         ASSERT_EQ( IsEqual(val, 8.25), true);

         beamClone->get_W6(&val);
         ASSERT_EQ( IsEqual(val, 15.75), true);

         beamClone->get_W7(&val);
         ASSERT_EQ( IsEqual(val, 1.75), true);

         beamClone->get_D1(&val);
         ASSERT_EQ( IsEqual(val,40.0), true);

         beamClone->get_D2(&val);
         ASSERT_EQ( IsEqual(val,8.25), true);

         beamClone->get_D3(&val);
         ASSERT_EQ( IsEqual(val,3.00), true);

         beamClone->get_D4(&val);
         ASSERT_EQ( IsEqual(val,0.875), true);

         beamClone->get_D5(&val);
         ASSERT_EQ( IsEqual(val,5.875), true);

         beamClone->get_D6(&val);
         ASSERT_EQ( IsEqual(val,21.625), true);

         beamClone->get_C1(&val);
         ASSERT_EQ( IsEqual(val,0.0), true);

         beamClone->get_T(&val);
         ASSERT_EQ( IsEqual(val,4.972964), true);

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(0.0, 0.5);

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
         p1->Move(-50,0.50);
         p2->Move( 50,0.50);

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
         ASSERT_EQ( cPoints, 6 );

         coll->get__Enum(&Enum);
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         i = 0;
         TEST_POINT(points, 0.000000, 0.000000);
         TEST_POINT(points, -27.500000, 0.000000);
         TEST_POINT(points, -27.625940, 0.500000);
         TEST_POINT(points, 27.625940, 0.500000);
         TEST_POINT(points, 27.500000, 0.000000);
         TEST_POINT(points, 0.000000, 0.000000);

         ASSERT_EQ(i, cPoints);

         // clip in other direction
         p1->Move( 50, 25.0);
         p2->Move(-50, 25.0);

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
         ASSERT_EQ( cPoints, 12);

         coll->get__Enum(&Enum);
         Enum->Next((ULONG)cPoints,&points[0],&fetched);
         ASSERT_EQ( fetched, cPoints );

         i = 0;
         TEST_POINT(points, -33.796992, 25.000000);
         TEST_POINT(points, -35.875000, 33.250000);
         TEST_POINT(points, -44.125000, 34.125000);
         TEST_POINT(points, -44.500000, 40.000000);
         TEST_POINT(points, -28.750000, 40.000000);
         TEST_POINT(points, -27.536127, 25.000000);
         TEST_POINT(points, 27.536127, 25.000000);
         TEST_POINT(points, 28.750000, 40.000000);
         TEST_POINT(points, 44.500000, 40.000000);
         TEST_POINT(points, 44.125000, 34.125000);
         TEST_POINT(points, 35.875000, 33.250000);
         TEST_POINT(points, 33.796992, 25.000000);

         ASSERT_EQ(i, cPoints);

         //
         // ClipIn
         //
         clip.Release();

         CComPtr<IRect2d> clipRect;
         clipRect.CoCreateInstance( CLSID_Rect2d );
         clipRect->put_Left(-100);
         clipRect->put_Right(100);
         clipRect->put_Top(0.6);
         clipRect->put_Bottom(0.5);

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

         ATLTRACE("Trace of Points for UBeam2 - count = %d \n", cPoints);
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
         TEST_POINT(points, -27.625940, 0.500000);
         TEST_POINT(points, -27.651128, 0.600000);
         TEST_POINT(points, 27.651128, 0.600000);
         TEST_POINT(points, 27.625940, 0.500000);

         ASSERT_EQ(i, cPoints);
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ( position.CoCreateInstance( CLSID_UBeam2), S_OK);

         CComQIPtr<IUBeam2> beam(position);
         CComQIPtr<IShape> shape(position);

         CComPtr<IPoint2d> hookPnt;
         beam->get_HookPoint(&hookPnt);

         // Use some real dimensions (TXDOT U40 girder)
         beam->put_W1(55);
         beam->put_W2(89);
         beam->put_W3(3);
         beam->put_W4(0.375);
         beam->put_W5(8.25);
         beam->put_W6(15.75);
         beam->put_W7(1.75);
         beam->put_D1(40);
         beam->put_D2(8.25);
         beam->put_D3(3);
         beam->put_D4(0.875);
         beam->put_D5(5.875);
         beam->put_D6(21.625);

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
         TEST_POINT(points, 100.000000, 100.000000);
         TEST_POINT(points, 72.500000, 100.000000);
         TEST_POINT(points, 64.125000, 133.250000);
         TEST_POINT(points, 55.875000, 134.125000);
         TEST_POINT(points, 55.500000, 140.000000);
         TEST_POINT(points, 71.250000, 140.000000);
         TEST_POINT(points, 73.000000, 118.375000);
         TEST_POINT(points, 74.794643, 111.250000);
         TEST_POINT(points, 77.794643, 108.250000);
         TEST_POINT(points, 100.000000, 108.250000);
         TEST_POINT(points, 122.205357, 108.250000);
         TEST_POINT(points, 125.205357, 111.250000);
         TEST_POINT(points, 127.000000, 118.375000);
         TEST_POINT(points, 128.750000, 140.000000);
         TEST_POINT(points, 144.500000, 140.000000);
         TEST_POINT(points, 144.125000, 134.125000);
         TEST_POINT(points, 135.875000, 133.250000);
         TEST_POINT(points, 127.500000, 100.000000);
         TEST_POINT(points, 100.000000, 100.000000);

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
         TEST_POINT(points, 0.000000, 0.000000);
         TEST_POINT(points, -27.500000, 0.000000);
         TEST_POINT(points, -35.875000, 33.250000);
         TEST_POINT(points, -44.125000, 34.125000);
         TEST_POINT(points, -44.500000, 40.000000);
         TEST_POINT(points, -28.750000, 40.000000);
         TEST_POINT(points, -27.000000, 18.375000);
         TEST_POINT(points, -25.205357, 11.250000);
         TEST_POINT(points, -22.205357, 8.250000);
         TEST_POINT(points, 0.000000, 8.250000);
         TEST_POINT(points, 22.205357, 8.250000);
         TEST_POINT(points, 25.205357, 11.250000);
         TEST_POINT(points, 27.000000, 18.375000);
         TEST_POINT(points, 28.750000, 40.000000);
         TEST_POINT(points, 44.500000, 40.000000);
         TEST_POINT(points, 44.125000, 34.125000);
         TEST_POINT(points, 35.875000, 33.250000);
         TEST_POINT(points, 27.500000, 0.000000);
         TEST_POINT(points, 0.000000, 0.000000);

         ASSERT_EQ(i, cPoints);

         //
         // LocatorPoint property
         //
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
         ASSERT_EQ(IsEqual(x,144.5), true );
         ASSERT_EQ(IsEqual(y,100.00), true );

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
         ASSERT_EQ(IsEqual(y,100.0), true );

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
         ASSERT_EQ(IsEqual(x,55.5), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

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
         ASSERT_EQ(IsEqual(x,144.5), true );
         ASSERT_EQ(IsEqual(y,80.0), true );

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
         ASSERT_EQ(IsEqual(y,80.0), true );

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
         ASSERT_EQ(IsEqual(x,55.5), true );
         ASSERT_EQ(IsEqual(y,80.0), true );

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
         ASSERT_EQ(IsEqual(x,144.5), true );
         ASSERT_EQ(IsEqual(y,60.0), true );

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
         ASSERT_EQ(IsEqual(y, 60.0), true );

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
         ASSERT_EQ(IsEqual(x,55.5), true );
         ASSERT_EQ(IsEqual(y,60.0), true );

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
         TEST_POINT(points, 0.000000, 0.000000);
         TEST_POINT(points, 27.500000, -0.000000);
         TEST_POINT(points, 35.875000, -33.250000);
         TEST_POINT(points, 44.125000, -34.125000);
         TEST_POINT(points, 44.500000, -40.000000);
         TEST_POINT(points, 28.750000, -40.000000);
         TEST_POINT(points, 27.000000, -18.375000);
         TEST_POINT(points, 25.205357, -11.250000);
         TEST_POINT(points, 22.205357, -8.250000);
         TEST_POINT(points, -0.000000, -8.250000);
         TEST_POINT(points, -22.205357, -8.250000);
         TEST_POINT(points, -25.205357, -11.250000);
         TEST_POINT(points, -27.000000, -18.375000);
         TEST_POINT(points, -28.750000, -40.000000);
         TEST_POINT(points, -44.500000, -40.000000);
         TEST_POINT(points, -44.125000, -34.125000);
         TEST_POINT(points, -35.875000, -33.250000);
         TEST_POINT(points, -27.500000, 0.000000);
         TEST_POINT(points, 0.000000, 0.000000);

         ASSERT_EQ(i, cPoints); 
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_UBeam2 ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IUBeam2 ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests