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

// TestPrecastBeam2.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestPrecastBeam2.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestPrecastBeam2)
{
public:
   TEST_METHOD(TestIPrecastBeam)
   {
         CComPtr<IPrecastBeam2> beam;
         ASSERT_EQ( beam.CoCreateInstance(CLSID_PrecastBeam2), S_OK );

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

         ASSERT_EQ( beam->get_H(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_H(&val), S_OK );
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

         ASSERT_EQ( beam->get_W3(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_W3(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ(beam->get_W4(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_W4(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_W5(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_W5(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

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

         ASSERT_EQ( beam->put_H(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_H(14), S_OK );
         beam->get_H(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_T1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_T1(14), S_OK );
         beam->get_T1(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_T2(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_T2(14), S_OK );
         beam->get_T2(&val);
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

         ASSERT_EQ(beam->put_W5(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_W5(14), S_OK);
         beam->get_W5(&val);
         ASSERT_EQ(IsEqual(val, 14.0), true);

         ASSERT_EQ( beam->put_C1(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_C1(1), S_OK );
         beam->get_C1(&val);
         ASSERT_EQ( IsEqual(val,1.0), true );

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

         // Use some real dimensions (WSDOT Modified WF100G girder)
         beam->put_W1(6);
         beam->put_W2(18.4375);
         beam->put_W3(3);
         beam->put_W4(3);
         beam->put_W5(13.125);
         beam->put_D1(3);
         beam->put_D2(3);
         beam->put_D3(3);
         beam->put_D4(3);
         beam->put_D5(4.5);
         beam->put_D6(5.125);
         beam->put_H(100);
         beam->put_T1(6.125);
         beam->put_T2(6.125);
         beam->put_C1(1.0);

         ASSERT_EQ(beam->get_Height(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_Height(&val), S_OK );
         ASSERT_EQ(IsEqual(val,100.0), true );

         ASSERT_EQ(beam->get_TopFlangeWidth(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_TopFlangeWidth(&val), S_OK );
         ASSERT_EQ(IsEqual(val,61.0), true );

         ASSERT_EQ(beam->get_BottomFlangeWidth(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_BottomFlangeWidth(&val), S_OK );
         ASSERT_EQ(IsEqual(val,38.375), true );

         ASSERT_EQ(beam->get_AvgWebWidth(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_AvgWebWidth(&val), S_OK );
         ASSERT_EQ(IsEqual(val,6.125), true );


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
         ASSERT_EQ( shape.CoCreateInstance( CLSID_PrecastBeam2 ), S_OK );
         CComQIPtr<IPrecastBeam2> beam(shape);

         // Use some real dimensions (WSDOT Modified WF100G girder)
         beam->put_W1(6);
         beam->put_W2(18.4375);
         beam->put_W3(3);
         beam->put_W4(3);
         beam->put_W5(13.125);
         beam->put_D1(3);
         beam->put_D2(3);
         beam->put_D3(3);
         beam->put_D4(3);
         beam->put_D5(4.5);
         beam->put_D6(5.125);
         beam->put_H(100);
         beam->put_T1(6.125);
         beam->put_T2(6.125);
         beam->put_C1(1.0);

         //
         // Bounding Box
         //
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );

         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,-30.5), true );

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val, 30.5), true );

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val,100.0), true );

         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val,0.00), true );

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
         ASSERT_EQ( IsEqual(area,1118.78125), true );
         ASSERT_EQ( IsEqual(ixx, 1612833.8649339355), true );
         ASSERT_EQ( IsEqual(iyy, 99849.307047526003), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,0.0), true );
         ASSERT_EQ( IsEqual(cgy, 49.889825586808556), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         Float64 xleft,xright,ytop,ybottom;
         props->get_Xleft(&xleft);
         props->get_Xright(&xright);
         props->get_Ytop(&ytop);
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(xleft,30.5),true);
         ASSERT_EQ(IsEqual(xright,30.5),true);
         ASSERT_EQ(IsEqual(ytop,100.0-cgy),true);
         ASSERT_EQ(IsEqual(ybottom,cgy),true);

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val, 365.28393667457732), true );

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
         ASSERT_EQ( cPoints, 23 );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 23> points;
         ULONG fetched;
         Enum->Next(23,&points[0],&fetched);
         ASSERT_EQ( fetched, 23 );

         Float64 x,y;

         int i = 0;
         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,100.), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-30.5), true );
         ASSERT_EQ( IsEqual(y, 100.), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-30.5), true );
         ASSERT_EQ( IsEqual(y, 97.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-24.5), true );
         ASSERT_EQ( IsEqual(y, 97.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-6.0625), true );
         ASSERT_EQ( IsEqual(y, 94.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-3.0625), true );
         ASSERT_EQ( IsEqual(y, 91.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-3.0625), true );
         ASSERT_EQ( IsEqual(y, 12.625), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-6.0625), true );
         ASSERT_EQ( IsEqual(y, 9.625), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-19.1875), true );
         ASSERT_EQ( IsEqual(y, 5.125), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-19.1875), true );
         ASSERT_EQ( IsEqual(y,1.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-18.1875), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 18.1875), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 19.1875), true );
         ASSERT_EQ( IsEqual(y,1.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 19.1875), true );
         ASSERT_EQ( IsEqual(y,5.125), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 6.0625), true );
         ASSERT_EQ( IsEqual(y,9.625), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 3.0625), true );
         ASSERT_EQ( IsEqual(y,12.625), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 3.0625), true );
         ASSERT_EQ( IsEqual(y,91.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 6.0625), true );
         ASSERT_EQ( IsEqual(y,94.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 24.5), true);
         ASSERT_EQ(IsEqual(y, 97.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 30.5), true);
         ASSERT_EQ(IsEqual(y, 97.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 30.5), true);
         ASSERT_EQ(IsEqual(y, 100.), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 0.0), true);
         ASSERT_EQ(IsEqual(y, 100.), true);

         ASSERT_EQ(i, cPoints);

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ(shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ(shape->Clone(&clone), S_OK);

         CComQIPtr<IPrecastBeam2> beamClone(clone);
         ASSERT_EQ( beamClone != nullptr, true );

         beamClone->get_W1(&val);
         ASSERT_EQ(IsEqual(val, 6.0), true);

         beamClone->get_W2(&val);
         ASSERT_EQ(IsEqual(val, 18.4375), true);

         beamClone->get_W3(&val);
         ASSERT_EQ( IsEqual(val,3.0), true);

         beamClone->get_W4(&val);
         ASSERT_EQ( IsEqual(val,3.0), true);

         beamClone->get_W5(&val);
         ASSERT_EQ( IsEqual(val,13.125), true);

         beamClone->get_D1(&val);
         ASSERT_EQ( IsEqual(val,3.0), true);

         beamClone->get_D2(&val);
         ASSERT_EQ( IsEqual(val, 3.0), true);

         beamClone->get_D3(&val);
         ASSERT_EQ( IsEqual(val, 3.0), true);

         beamClone->get_D4(&val);
         ASSERT_EQ( IsEqual(val, 3.0), true);

         beamClone->get_D5(&val);
         ASSERT_EQ( IsEqual(val,4.5), true);

         beamClone->get_D6(&val);
         ASSERT_EQ( IsEqual(val, 5.125), true);

         beamClone->get_H(&val);
         ASSERT_EQ( IsEqual(val,100.), true);

         beamClone->get_T1(&val);
         ASSERT_EQ( IsEqual(val,6.125), true);

         beamClone->get_T2(&val);
         ASSERT_EQ( IsEqual(val,6.125), true);

         beamClone->get_C1(&val);
         ASSERT_EQ( IsEqual(val,1.0), true);

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
         ASSERT_EQ( cPoints, 5 );

         coll->get__Enum(&Enum);
         Enum->Next(5,&points[0],&fetched);
         ASSERT_EQ( fetched, 5 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-18.6875), true );
         ASSERT_EQ( IsEqual(y, 0.500), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-18.1875), true );
         ASSERT_EQ( IsEqual(y, 0.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y, 0.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 18.1875), true );
         ASSERT_EQ( IsEqual(y, 0.0), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 18.6875), true );
         ASSERT_EQ( IsEqual(y,0.5), true );

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
         ASSERT_EQ( cPoints, 5 );

         coll->get__Enum(&Enum);
         Enum->Next(5,&points[0],&fetched);
         ASSERT_EQ( fetched, 5 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-18.7875), true );
         ASSERT_EQ( IsEqual(y, 0.6), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-18.6875), true );
         ASSERT_EQ( IsEqual(y, 0.5), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 18.6875), true );
         ASSERT_EQ( IsEqual(y, 0.5), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 18.7875), true );
         ASSERT_EQ( IsEqual(y, 0.6), true );
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ( position.CoCreateInstance( CLSID_PrecastBeam2), S_OK);

         CComQIPtr<IPrecastBeam2> beam(position);
         CComQIPtr<IShape> shape(position);

         CComPtr<IPoint2d> hookPnt;
         hookPnt.CoCreateInstance( CLSID_Point2d );
         hookPnt->Move(0,0);

         // Use some real dimensions (WSDOT W74MG girder)
         beam->putref_HookPoint(hookPnt);
         // Use some real dimensions (WSDOT Modified WF100G girder)
         beam->put_W1(6);
         beam->put_W2(18.4375);
         beam->put_W3(3);
         beam->put_W4(3);
         beam->put_W5(13.125);
         beam->put_D1(3);
         beam->put_D2(3);
         beam->put_D3(3);
         beam->put_D4(3);
         beam->put_D5(4.5);
         beam->put_D6(5.125);
         beam->put_H(100);
         beam->put_T1(6.125);
         beam->put_T2(6.125);
         beam->put_C1(1.0);

         //
         // MoveEx (tests Offset as well)
         //
         CComPtr<IPoint2d> from;
         from.CoCreateInstance( CLSID_Point2d );
         from->Move(0,0);

         Float64 offset = 100;
         CComPtr<IPoint2d> to;
         to.CoCreateInstance( CLSID_Point2d );
         to->Move(offset, offset);

         ASSERT_EQ( position->MoveEx(nullptr,to), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to), S_OK );

         // Check the points
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );
         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,23);

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 23> points;
         ULONG fetched;
         Enum->Next(23,&points[0],&fetched);
         ASSERT_EQ( fetched, 23 );

         Float64 x,y;

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -24.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 94.0 + offset), true);

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 91.0 + offset), true);

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 12.625 + offset), true);

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 9.625 + offset), true);

         points[8]->get_X(&x);
         points[8]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 5.125 + offset), true);

         points[9]->get_X(&x);
         points[9]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 1.0 + offset), true);

         points[10]->get_X(&x);
         points[10]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -18.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 0.0 + offset), true);

         points[11]->get_X(&x);
         points[11]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0 + offset), true);
         ASSERT_EQ(IsEqual(y, 0.0 + offset), true);

         points[12]->get_X(&x);
         points[12]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 18.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 0.0 + offset), true);

         points[13]->get_X(&x);
         points[13]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 1.0 + offset), true);

         points[14]->get_X(&x);
         points[14]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 5.125 + offset), true);

         points[15]->get_X(&x);
         points[15]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 9.625 + offset), true);

         points[16]->get_X(&x);
         points[16]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 12.625 + offset), true);

         points[17]->get_X(&x);
         points[17]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 91.0 + offset), true);

         points[18]->get_X(&x);
         points[18]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 94.0 + offset), true);

         points[19]->get_X(&x);
         points[19]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 24.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[20]->get_X(&x);
         points[20]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[21]->get_X(&x);
         points[21]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         points[22]->get_X(&x);
         points[22]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         //
         // OffsetEx
         //

         // Move the triangle back to where it was
         hookPnt->Move(0,0);

         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(offset);
         size->put_Dy(offset);

         ASSERT_EQ(position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ(position->OffsetEx(size), S_OK);

         // Check the points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         shape->get_PolyPoints(&coll);
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints,23);

         coll->get__Enum(&Enum);
         Enum->Next(23,&points[0],&fetched);
         ASSERT_EQ( fetched, 23 );


         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -24.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 94.0 + offset), true);

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 91.0 + offset), true);

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 12.625 + offset), true);

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 9.625 + offset), true);

         points[8]->get_X(&x);
         points[8]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 5.125 + offset), true);

         points[9]->get_X(&x);
         points[9]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 1.0 + offset), true);

         points[10]->get_X(&x);
         points[10]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, -18.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 0.0 + offset), true);

         points[11]->get_X(&x);
         points[11]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0 + offset), true);
         ASSERT_EQ(IsEqual(y, 0.0 + offset), true);

         points[12]->get_X(&x);
         points[12]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 18.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 0.0 + offset), true);

         points[13]->get_X(&x);
         points[13]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 1.0 + offset), true);

         points[14]->get_X(&x);
         points[14]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 19.1875 + offset), true);
         ASSERT_EQ(IsEqual(y, 5.125 + offset), true);

         points[15]->get_X(&x);
         points[15]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 9.625 + offset), true);

         points[16]->get_X(&x);
         points[16]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 12.625 + offset), true);

         points[17]->get_X(&x);
         points[17]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 3.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 91.0 + offset), true);

         points[18]->get_X(&x);
         points[18]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 6.0625 + offset), true);
         ASSERT_EQ(IsEqual(y, 94.0 + offset), true);

         points[19]->get_X(&x);
         points[19]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 24.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[20]->get_X(&x);
         points[20]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 97.0 + offset), true);

         points[21]->get_X(&x);
         points[21]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 30.5 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         points[22]->get_X(&x);
         points[22]->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 0.0 + offset), true);
         ASSERT_EQ(IsEqual(y, 100. + offset), true);

         //
         // LocatorPoint property
         //
         hookPnt->Move(0,0);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         hookPnt->Move(0,0);
         to->Move(99.454,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 99.454), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,129.954), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // BottomCenter
         hookPnt->Move(0,0);
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
         to->Move(100.546,100.000);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.546), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,70.046), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterLeft
         hookPnt->Move(0,0);
         to->Move(99.454,100.9335);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 99.454), true );
         ASSERT_EQ(IsEqual(y,100.9335), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,129.954), true );
         ASSERT_EQ(IsEqual(y,50.9335), true );

         // CenterCenter
         hookPnt->Move(0,0);
         to->Move(100,100.9335);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,100.9335), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,50.9335), true );

         // CenterRight
         hookPnt->Move(0,0);
         to->Move(100.546,100.9335);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.546), true );
         ASSERT_EQ(IsEqual(y,100.9335), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,70.046), true );
         ASSERT_EQ(IsEqual(y,50.9335), true );

         // TopLeft
         hookPnt->Move(0,0);
         to->Move(99.454,101.867);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 99.454), true );
         ASSERT_EQ(IsEqual(y,101.867), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,129.954), true );
         ASSERT_EQ(IsEqual(y,1.867), true );

         // TopCenter
         hookPnt->Move(0,0);
         to->Move(100,101.867);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,101.867), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,1.867), true );

         // TopRight
         hookPnt->Move(0,0);
         to->Move(100.546,101.867);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.546), true );
         ASSERT_EQ(IsEqual(y,101.867), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,70.046), true );
         ASSERT_EQ(IsEqual(y,1.867), true );

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
         ASSERT_EQ( cPoints,23);

         coll->get__Enum(&Enum);
         Enum->Next(23,&points[0],&fetched);
         ASSERT_EQ( fetched, 23 );

         int i = 0;
         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 0.0), true);
         ASSERT_EQ(IsEqual(y, -100.), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 30.5), true);
         ASSERT_EQ(IsEqual(y, -100.), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 30.5), true);
         ASSERT_EQ(IsEqual(y, -97.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 24.5), true);
         ASSERT_EQ(IsEqual(y, -97.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 6.0625), true);
         ASSERT_EQ(IsEqual(y, -94.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 3.0625), true);
         ASSERT_EQ(IsEqual(y, -91.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 3.0625), true);
         ASSERT_EQ(IsEqual(y, -12.625), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 6.0625), true);
         ASSERT_EQ(IsEqual(y, -9.625), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 19.1875), true);
         ASSERT_EQ(IsEqual(y, -5.125), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 19.1875), true);
         ASSERT_EQ(IsEqual(y, -1.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 18.1875), true);
         ASSERT_EQ(IsEqual(y, 0.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 0.0), true);
         ASSERT_EQ(IsEqual(y, 0.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -18.1875), true);
         ASSERT_EQ(IsEqual(y, 0.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -19.1875), true);
         ASSERT_EQ(IsEqual(y, -1.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -19.1875), true);
         ASSERT_EQ(IsEqual(y, -5.125), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -6.0625), true);
         ASSERT_EQ(IsEqual(y, -9.625), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -3.0625), true);
         ASSERT_EQ(IsEqual(y, -12.625), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -3.0625), true);
         ASSERT_EQ(IsEqual(y, -91.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -6.0625), true);
         ASSERT_EQ(IsEqual(y, -94.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -24.5), true);
         ASSERT_EQ(IsEqual(y, -97.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -30.5), true);
         ASSERT_EQ(IsEqual(y, -97.0), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, -30.5), true);
         ASSERT_EQ(IsEqual(y, -100.), true);

         points[i++]->Location(&x, &y);
         ASSERT_EQ(IsEqual(x, 0.0), true);
         ASSERT_EQ(IsEqual(y, -100.), true);

         ASSERT_EQ(i, cPoints);
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_PrecastBeam2 ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IPrecastBeam2 ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests