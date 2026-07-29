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

// TestBulbTee.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestBulbTee.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestBulbTee)
{
public:
   TEST_METHOD(TestIBulbTee)
   {
         CComPtr<IBulbTee> beam;
         ASSERT_EQ(beam.CoCreateInstance(CLSID_BulbTee), S_OK);

         // Verify initialization. All dimensions should be zero.
         // Hook point (bottom center) should be zero.
         Float64 val;
         CComPtr<IPoint2d> pntVal;

         ASSERT_EQ(beam->get_D1(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_D1(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_D2(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_D2(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_D3(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_D3(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_D4(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_D4(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_D5(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_D5(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_D6(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_D6(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_D7(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_D7(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_W1(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_W1(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_W2(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_W2(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_W3(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_W3(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_W4(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_W4(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_W5(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_W5(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_T1(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_T1(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_T2(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_T2(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_C1(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_C1(&val), S_OK);
         ASSERT_EQ(IsZero(val), true);

         ASSERT_EQ(beam->get_HookPoint(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_HookPoint(&pntVal), S_OK);
         pntVal->get_X(&val);
         ASSERT_EQ(IsZero(val), true);
         pntVal->get_Y(&val);
         ASSERT_EQ(IsZero(val), true);

         // Test properties
         ASSERT_EQ(beam->put_D1(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_D2(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_D3(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_D4(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_D5(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_D6(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_D7(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_W1(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_W2(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_W3(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_W4(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_W5(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_T1(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_T2(-1), GEOMETRY_E_DIMENSION);
         ASSERT_EQ(beam->put_C1(-1), GEOMETRY_E_DIMENSION);

         // Try some real dimensions (WSDOT WF69G)
         ASSERT_EQ(beam->put_D1(6), S_OK);
         ASSERT_EQ(beam->put_D2(3), S_OK);
         ASSERT_EQ(beam->put_D3(3), S_OK);
         ASSERT_EQ(beam->put_D4(5.125), S_OK);
         ASSERT_EQ(beam->put_D5(4.5), S_OK);
         ASSERT_EQ(beam->put_D6(3), S_OK);
         ASSERT_EQ(beam->put_D7(44.375), S_OK);
         ASSERT_EQ(beam->put_W1(18.4375), S_OK);
         ASSERT_EQ(beam->put_W2(3), S_OK);
         ASSERT_EQ(beam->put_W3(13.125), S_OK);
         ASSERT_EQ(beam->put_W4(3), S_OK);
         ASSERT_EQ(beam->put_W5(60), S_OK);
         ASSERT_EQ(beam->put_T1(6.125), S_OK);
         ASSERT_EQ(beam->put_T2(6.125), S_OK);
         ASSERT_EQ(beam->put_C1(1), S_OK);

         ASSERT_EQ(beam->get_D1(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 6.0), true);

         ASSERT_EQ(beam->get_D2(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 3.0), true);

         ASSERT_EQ(beam->get_D3(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 3.0), true);

         ASSERT_EQ(beam->get_D4(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 5.125), true);

         ASSERT_EQ(beam->get_D6(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 3.0), true);

         ASSERT_EQ(beam->get_D7(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 44.375), true);

         ASSERT_EQ(beam->get_W1(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 18.4375), true);

         ASSERT_EQ(beam->get_W2(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 3.0), true);

         ASSERT_EQ(beam->get_W3(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 13.125), true);

         ASSERT_EQ(beam->get_W4(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 3.0), true);

         ASSERT_EQ(beam->get_W5(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 60.0), true);

         ASSERT_EQ(beam->get_T1(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 6.125), true);

         ASSERT_EQ(beam->get_T2(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 6.125), true);

         ASSERT_EQ(beam->get_C1(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 1.0), true);

         // Test Interface Pointers
         CComPtr<IShape> shape;
         ASSERT_EQ(beam->get_Shape(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_Shape(&shape), S_OK);
         ASSERT_EQ(shape != nullptr, true);

         CComPtr<IXYPosition> position;
         ASSERT_EQ(beam->get_XYPosition(nullptr), E_POINTER);
         ASSERT_EQ(beam->get_XYPosition(&position), S_OK);
         ASSERT_EQ(position != nullptr, true);

         CComPtr<IUnknown> punk1;
         CComPtr<IUnknown> punk2;
         CComPtr<IUnknown> punk3;
         beam->QueryInterface(&punk1);
         shape->QueryInterface(&punk2);
         position->QueryInterface(&punk3);
         ASSERT_EQ(punk1 == punk2, true);
         ASSERT_EQ(punk1 == punk3, true);
         ASSERT_EQ(punk2 == punk3, true);
   }

   TEST_METHOD(TestIShape)
   {
         CComPtr<IShape> shape;
         ASSERT_EQ(shape.CoCreateInstance(CLSID_BulbTee), S_OK);
         CComQIPtr<IBulbTee> beam(shape);

         // Try some real dimensions (WSDOT WF69G)
         ASSERT_EQ(beam->put_D1(6), S_OK);
         ASSERT_EQ(beam->put_D2(3), S_OK);
         ASSERT_EQ(beam->put_D3(3), S_OK);
         ASSERT_EQ(beam->put_D4(5.125), S_OK);
         ASSERT_EQ(beam->put_D5(4.5), S_OK);
         ASSERT_EQ(beam->put_D6(3), S_OK);
         ASSERT_EQ(beam->put_D7(44.375), S_OK);
         ASSERT_EQ(beam->put_W1(18.4375), S_OK);
         ASSERT_EQ(beam->put_W2(3), S_OK);
         ASSERT_EQ(beam->put_W3(13.125), S_OK);
         ASSERT_EQ(beam->put_W4(3), S_OK);
         ASSERT_EQ(beam->put_W5(60), S_OK);
         ASSERT_EQ(beam->put_T1(6.125), S_OK);
         ASSERT_EQ(beam->put_T2(6.125), S_OK);
         ASSERT_EQ(beam->put_C1(1), S_OK);

         //
         // Bounding Box
         //
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ(shape->get_BoundingBox(nullptr), E_POINTER);
         ASSERT_EQ(shape->get_BoundingBox(&box), S_OK);

         box->get_Left(&val);
         ASSERT_EQ(IsEqual(val, -30.0), true);

         box->get_Right(&val);
         ASSERT_EQ(IsEqual(val, 30.0), true);

         box->get_Top(&val);
         ASSERT_EQ(IsEqual(val, 69.0), true);

         box->get_Bottom(&val);
         ASSERT_EQ(IsEqual(val, 0.0), true);

         //
         // ShapeProperties
         //
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
         ASSERT_EQ(IsEqual(area, 1087.53125), true);
         ASSERT_EQ(IsEqual(ixx, 769358.20231312467), true);
         ASSERT_EQ(IsEqual(iyy, 150453.00463867188), true);
         ASSERT_EQ(IsEqual(ixy, 0.0), true);
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ(IsEqual(cgx, 0.0), true);
         ASSERT_EQ(IsEqual(cgy, 38.703877642404912), true);
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ(cst, csCentroidal);

         Float64 xleft, xright, ytop, ybottom;
         props->get_Xleft(&xleft);
         props->get_Xright(&xright);
         props->get_Ytop(&ytop);
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(xleft, 30.0), true);
         ASSERT_EQ(IsEqual(xright, 30.0), true);
         ASSERT_EQ(IsEqual(ytop, 69 - 38.703877642404912), true);
         ASSERT_EQ(IsEqual(ybottom, 38.703877642404912), true);

         //
         // Perimeter
         //
         ASSERT_EQ(shape->get_Perimeter(nullptr), E_POINTER);
         ASSERT_EQ(shape->get_Perimeter(&val), S_OK);
         ASSERT_EQ(IsEqual(val, 301.28393667457738), true);

         //
         // FurthestDistance
         //
         CComPtr<IPoint2d> p1;
         p1.CoCreateInstance(CLSID_Point2d);

         CComPtr<IPoint2d> p2;
         p2.CoCreateInstance(CLSID_Point2d);

         CComPtr<ILine2d> line;
         line.CoCreateInstance(CLSID_Line2d);

         // Shape on right
         p1->Move(0, 20);
         p2->Move(100, 20);
         line->ThroughPoints(p1, p2);
         Float64 dist;
         ASSERT_EQ(shape->FurthestDistance(nullptr, &dist), E_INVALIDARG);
         ASSERT_EQ(shape->FurthestDistance(line, nullptr), E_POINTER);
         ASSERT_EQ(shape->FurthestDistance(line, &dist), S_OK);
         ASSERT_EQ(IsEqual(dist, 20.000), true);

         // shape on left
         p1->Move(0, -20);
         p2->Move(100, -20);
         line->ThroughPoints(p1, p2);
         ASSERT_EQ(shape->FurthestDistance(line, &dist), S_OK);
         ASSERT_EQ(IsEqual(dist, -20.0), true);


         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance(CLSID_Point2d);
         pnt->Move(0.0, 1.0);

         ASSERT_EQ(shape->PointInShape(nullptr, &bPointInShape), E_INVALIDARG);
         ASSERT_EQ(shape->PointInShape(pnt, nullptr), E_POINTER);
         ASSERT_EQ(shape->PointInShape(pnt, &bPointInShape), S_OK);
         ASSERT_EQ(bPointInShape, VARIANT_TRUE);

         pnt->Move(500, 500);
         ASSERT_EQ(shape->PointInShape(pnt, &bPointInShape), S_OK);
         ASSERT_EQ(bPointInShape, VARIANT_FALSE);

         pnt->Move(0, 0); // Point on perimeter
         ASSERT_EQ(shape->PointInShape(pnt, &bPointInShape), S_OK);
         ASSERT_EQ(bPointInShape, VARIANT_FALSE);
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ(position.CoCreateInstance(CLSID_BulbTee), S_OK);

         CComQIPtr<IBulbTee> beam(position);
         CComQIPtr<IShape> shape(position);

         CComPtr<IPoint2d> hookPnt;
         hookPnt.CoCreateInstance(CLSID_Point2d);
         hookPnt->Move(0, 0);

         // Try some real dimensions (WSDOT WF69G)
         ASSERT_EQ(beam->putref_HookPoint(hookPnt), S_OK);
         ASSERT_EQ(beam->put_D1(6), S_OK);
         ASSERT_EQ(beam->put_D2(3), S_OK);
         ASSERT_EQ(beam->put_D3(3), S_OK);
         ASSERT_EQ(beam->put_D4(5.125), S_OK);
         ASSERT_EQ(beam->put_D5(4.5), S_OK);
         ASSERT_EQ(beam->put_D6(3), S_OK);
         ASSERT_EQ(beam->put_D7(44.375), S_OK);
         ASSERT_EQ(beam->put_W1(18.4375), S_OK);
         ASSERT_EQ(beam->put_W2(3), S_OK);
         ASSERT_EQ(beam->put_W3(13.125), S_OK);
         ASSERT_EQ(beam->put_W4(3), S_OK);
         ASSERT_EQ(beam->put_W5(60), S_OK);
         ASSERT_EQ(beam->put_T1(6.125), S_OK);
         ASSERT_EQ(beam->put_T2(6.125), S_OK);
         ASSERT_EQ(beam->put_C1(1), S_OK);

         // Get moment of inertia about CG before move
         // These properties should be invariant
         CComPtr<IShapeProperties> props;
         shape->get_ShapeProperties(&props);
         props->put_CoordinateSystem(csCentroidal);
         Float64 Ixx, Iyy;
         props->get_Ixx(&Ixx);
         props->get_Iyy(&Iyy);

         //
         // MoveEx (tests Offset as well)
         //
         CComPtr<IPoint2d> from;
         from.CoCreateInstance(CLSID_Point2d);
         from->Move(0, 0);

         CComPtr<IPoint2d> to;
         to.CoCreateInstance(CLSID_Point2d);
         to->Move(100, 100);

         ASSERT_EQ(position->MoveEx(nullptr, to), E_INVALIDARG);
         ASSERT_EQ(position->MoveEx(from, nullptr), E_INVALIDARG);
         ASSERT_EQ(position->MoveEx(from, to), S_OK);

         props.Release();
         shape->get_ShapeProperties(&props);
         Float64 val;
         props->get_Ixx(&val);
         ASSERT_EQ(IsEqual(Ixx, val), true);
         props->get_Iyy(&val);
         ASSERT_EQ(IsEqual(Iyy, val), true);

         //
         // OffsetEx
         //

         CComPtr<ISize2d> size;
         size.CoCreateInstance(CLSID_Size2d);
         size->put_Dx(-100);
         size->put_Dy(-100);

         ASSERT_EQ(position->OffsetEx(nullptr), E_INVALIDARG);
         ASSERT_EQ(position->OffsetEx(size), S_OK);

         props.Release();
         shape->get_ShapeProperties(&props);
         props->get_Ixx(&val);
         ASSERT_EQ(IsEqual(Ixx, val), true);
         props->get_Iyy(&val);
         ASSERT_EQ(IsEqual(Iyy, val), true);

         ///
         // LocatorPoint property
         //
         hookPnt->Move(0, 0);
         ASSERT_EQ(position->put_LocatorPoint(lpBottomLeft, nullptr), E_INVALIDARG);
         ASSERT_EQ(position->get_LocatorPoint(lpBottomLeft, nullptr), E_POINTER);

         Float64 x, y;

         // BottomLeft
         hookPnt->Move(0, 0);
         to->Move(100, 100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpBottomLeft, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpBottomLeft, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.000), true);
         ASSERT_EQ(IsEqual(y, 100.000), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 130.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);

         // BottomCenter
         hookPnt->Move(0.0, 0.0);
         to->Move(100.000, 100.000);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpBottomCenter, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpBottomCenter, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.000), true);
         ASSERT_EQ(IsEqual(y, 100.000), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);

         // BottomRight
         hookPnt->Move(0, 0);
         to->Move(100.000, 100.000);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpBottomRight, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpBottomRight, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.000), true);
         ASSERT_EQ(IsEqual(y, 100.000), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 70.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);

         // CenterLeft
         hookPnt->Move(0, 0);
         to->Move(100, 100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpCenterLeft, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpCenterLeft, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 130.0), true);
         ASSERT_EQ(IsEqual(y, 65.5), true);

         // CenterCenter
         hookPnt->Move(0, 0);
         to->Move(100, 100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpCenterCenter, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpCenterCenter, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 65.5), true);

         // CenterRight
         hookPnt->Move(0, 0);
         to->Move(100.0, 100.0);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpCenterRight, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpCenterRight, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 70.0), true);
         ASSERT_EQ(IsEqual(y, 65.5), true);

         // TopLeft
         hookPnt->Move(0, 0);
         to->Move(100.0, 100.0);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpTopLeft, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpTopLeft, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 130.0), true);
         ASSERT_EQ(IsEqual(y, 31.0), true);

         // TopCenter
         hookPnt->Move(0, 0);
         to->Move(100.0, 100.0);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpTopCenter, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpTopCenter, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 31.0), true);

         // TopRight
         hookPnt->Move(0, 0);
         to->Move(100.0, 100.0);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpTopRight, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpTopRight, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 70.0), true);
         ASSERT_EQ(IsEqual(y, 31.0), true);

         // HookPoint
         hookPnt->Move(0, 0);
         to->Move(100, 100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpHookPoint, to), S_OK);
         ASSERT_EQ(position->get_LocatorPoint(lpHookPoint, &from), S_OK);
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 100.0), true);
         ASSERT_EQ(IsEqual(y, 100.0), true);
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ(eInfo.CoCreateInstance(CLSID_BulbTee), S_OK);
         ASSERT_EQ(eInfo != nullptr, true);

         // Interfaces that should be supported
         ASSERT_EQ(eInfo->InterfaceSupportsErrorInfo(IID_IBulbTee), S_OK);
         ASSERT_EQ(eInfo->InterfaceSupportsErrorInfo(IID_IShape), S_OK);
         ASSERT_EQ(eInfo->InterfaceSupportsErrorInfo(IID_IXYPosition), S_OK);

         // Interface that is not supported
         ASSERT_EQ(eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo), S_FALSE);
   }
};
} // namespace GeometryUnitTests