///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestBulbTee2.cpp: implementation of the CTestBulbTee2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBulbTee2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestBulbTee2::CTestBulbTee2()
{

}

CTestBulbTee2::~CTestBulbTee2()
{

}

void CTestBulbTee2::Test()
{
   TestIBulbTee();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestBulbTee2::TestIBulbTee()
{
   CComPtr<IBulbTee2> beam;
   TRY_TEST(beam.CoCreateInstance(CLSID_BulbTee2), S_OK);

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST(beam->get_D1(nullptr), E_POINTER);
   TRY_TEST(beam->get_D1(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D2(nullptr), E_POINTER);
   TRY_TEST(beam->get_D2(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D3(nullptr), E_POINTER);
   TRY_TEST(beam->get_D3(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D4(nullptr), E_POINTER);
   TRY_TEST(beam->get_D4(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D5(nullptr), E_POINTER);
   TRY_TEST(beam->get_D5(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D6(nullptr), E_POINTER);
   TRY_TEST(beam->get_D6(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D7(nullptr), E_POINTER);
   TRY_TEST(beam->get_D7(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W1(nullptr), E_POINTER);
   TRY_TEST(beam->get_W1(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W2(nullptr), E_POINTER);
   TRY_TEST(beam->get_W2(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W3(nullptr), E_POINTER);
   TRY_TEST(beam->get_W3(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W4(nullptr), E_POINTER);
   TRY_TEST(beam->get_W4(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W5(nullptr), E_POINTER);
   TRY_TEST(beam->get_W5(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W6(nullptr), E_POINTER);
   TRY_TEST(beam->get_W6(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_T1(nullptr), E_POINTER);
   TRY_TEST(beam->get_T1(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_T2(nullptr), E_POINTER);
   TRY_TEST(beam->get_T2(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_C1(nullptr), E_POINTER);
   TRY_TEST(beam->get_C1(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_C2(nullptr), E_POINTER);
   TRY_TEST(beam->get_C2(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_n1(nullptr), E_POINTER);
   TRY_TEST(beam->get_n1(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_n2(nullptr), E_POINTER);
   TRY_TEST(beam->get_n2(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_HookPoint(nullptr), E_POINTER);
   TRY_TEST(beam->get_HookPoint(&pntVal), S_OK);
   pntVal->get_X(&val);
   TRY_TEST(IsZero(val), true);
   pntVal->get_Y(&val);
   TRY_TEST(IsZero(val), true);

   // Test properties
   TRY_TEST(beam->put_D1(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D2(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D3(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D4(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D5(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D6(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D7(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W1(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W2(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W3(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W4(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W5(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W6(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_T1(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_T2(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_C1(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_C2(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_n1(-1), S_OK);
   TRY_TEST(beam->put_n2(-1), S_OK);

   // Try some real dimensions (WSDOT WF69G)
   TRY_TEST(beam->put_D1(6), S_OK);
   TRY_TEST(beam->put_D2(3), S_OK);
   TRY_TEST(beam->put_D3(3), S_OK);
   TRY_TEST(beam->put_D4(5.125), S_OK);
   TRY_TEST(beam->put_D5(4.5), S_OK);
   TRY_TEST(beam->put_D6(3), S_OK);
   TRY_TEST(beam->put_D7(44.375), S_OK);
   TRY_TEST(beam->put_W1(18.4375), S_OK);
   TRY_TEST(beam->put_W2(3), S_OK);
   TRY_TEST(beam->put_W3(13.125), S_OK);
   TRY_TEST(beam->put_W4(3), S_OK);
   TRY_TEST(beam->put_W5(30), S_OK);
   TRY_TEST(beam->put_W6(30), S_OK);
   TRY_TEST(beam->put_T1(6.125), S_OK);
   TRY_TEST(beam->put_T2(6.125), S_OK);
   TRY_TEST(beam->put_C1(1), S_OK);
   TRY_TEST(beam->put_C2(15), S_OK);
   TRY_TEST(beam->put_n1(0.02), S_OK);
   TRY_TEST(beam->put_n2(-0.02), S_OK);

   TRY_TEST(beam->get_D1(&val), S_OK);
   TRY_TEST(IsEqual(val, 6.0), true);

   TRY_TEST(beam->get_D2(&val), S_OK);
   TRY_TEST(IsEqual(val, 3.0), true);

   TRY_TEST(beam->get_D3(&val), S_OK);
   TRY_TEST(IsEqual(val, 3.0), true);

   TRY_TEST(beam->get_D4(&val), S_OK);
   TRY_TEST(IsEqual(val, 5.125), true);

   TRY_TEST(beam->get_D6(&val), S_OK);
   TRY_TEST(IsEqual(val, 3.0), true);

   TRY_TEST(beam->get_D7(&val), S_OK);
   TRY_TEST(IsEqual(val, 44.375), true);

   TRY_TEST(beam->get_W1(&val), S_OK);
   TRY_TEST(IsEqual(val, 18.4375), true);

   TRY_TEST(beam->get_W2(&val), S_OK);
   TRY_TEST(IsEqual(val, 3.0), true);

   TRY_TEST(beam->get_W3(&val), S_OK);
   TRY_TEST(IsEqual(val, 13.125), true);

   TRY_TEST(beam->get_W4(&val), S_OK);
   TRY_TEST(IsEqual(val, 3.0), true);

   TRY_TEST(beam->get_W5(&val), S_OK);
   TRY_TEST(IsEqual(val, 30.0), true);

   TRY_TEST(beam->get_W6(&val), S_OK);
   TRY_TEST(IsEqual(val, 30.0), true);

   TRY_TEST(beam->get_T1(&val), S_OK);
   TRY_TEST(IsEqual(val, 6.125), true);

   TRY_TEST(beam->get_T2(&val), S_OK);
   TRY_TEST(IsEqual(val, 6.125), true);

   TRY_TEST(beam->get_C1(&val), S_OK);
   TRY_TEST(IsEqual(val, 1.0), true);

   TRY_TEST(beam->get_C2(&val), S_OK);
   TRY_TEST(IsEqual(val, 15.0), true);

   TRY_TEST(beam->get_n1(&val), S_OK);
   TRY_TEST(IsEqual(val, 0.02), true);

   TRY_TEST(beam->get_n2(&val), S_OK);
   TRY_TEST(IsEqual(val, -0.02), true);

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(beam->get_Shape(nullptr), E_POINTER);
   TRY_TEST(beam->get_Shape(&shape), S_OK);
   TRY_TEST(shape != nullptr, true);

   CComPtr<IXYPosition> position;
   TRY_TEST(beam->get_XYPosition(nullptr), E_POINTER);
   TRY_TEST(beam->get_XYPosition(&position), S_OK);
   TRY_TEST(position != nullptr, true);

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   beam->QueryInterface(&punk1);
   shape->QueryInterface(&punk2);
   position->QueryInterface(&punk3);
   TRY_TEST(punk1 == punk2, true);
   TRY_TEST(punk1 == punk3, true);
   TRY_TEST(punk2 == punk3, true);
}

void CTestBulbTee2::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST(shape.CoCreateInstance(CLSID_BulbTee2), S_OK);
   CComQIPtr<IBulbTee2> beam(shape);

   // Try some real dimensions (WSDOT WF69G)
   TRY_TEST(beam->put_D1(6), S_OK);
   TRY_TEST(beam->put_D2(3), S_OK);
   TRY_TEST(beam->put_D3(3), S_OK);
   TRY_TEST(beam->put_D4(5.125), S_OK);
   TRY_TEST(beam->put_D5(4.5), S_OK);
   TRY_TEST(beam->put_D6(3), S_OK);
   TRY_TEST(beam->put_D7(44.375), S_OK);
   TRY_TEST(beam->put_W1(18.4375), S_OK);
   TRY_TEST(beam->put_W2(3), S_OK);
   TRY_TEST(beam->put_W3(13.125), S_OK);
   TRY_TEST(beam->put_W4(3), S_OK);
   TRY_TEST(beam->put_W5(30), S_OK);
   TRY_TEST(beam->put_W6(30), S_OK);
   TRY_TEST(beam->put_T1(6.125), S_OK);
   TRY_TEST(beam->put_T2(6.125), S_OK);
   TRY_TEST(beam->put_C1(1), S_OK);
   TRY_TEST(beam->put_C2(15), S_OK);
   TRY_TEST(beam->put_n1(0.02), S_OK);
   TRY_TEST(beam->put_n2(-0.02), S_OK);

   //
   // Bounding Box
   //
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST(shape->get_BoundingBox(nullptr), E_POINTER);
   TRY_TEST(shape->get_BoundingBox(&box), S_OK);

   box->get_Left(&val);
   TRY_TEST(IsEqual(val, -30.0), true);

   box->get_Right(&val);
   TRY_TEST(IsEqual(val, 30.0), true);

   box->get_Top(&val);
   TRY_TEST(IsEqual(val, 69.9), true);

   box->get_Bottom(&val);
   TRY_TEST(IsEqual(val, 0.0), true);

   //
   // ShapeProperties
   //
   CComPtr<IShapeProperties> props;
   TRY_TEST(shape->get_ShapeProperties(nullptr), E_POINTER);
   TRY_TEST(shape->get_ShapeProperties(&props), S_OK);
   Float64 area, ixx, iyy, ixy, cgx, cgy;
   CComPtr<IPoint2d> cg;

   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   cg.Release();
   props->get_Centroid(&cg);
   TRY_TEST(IsEqual(area, 1119.03125), true);
   TRY_TEST(IsEqual(ixx, 798071.07781859976), true);
   TRY_TEST(IsEqual(iyy, 158329.51421028795), true);
   TRY_TEST(IsEqual(ixy, -7399.6791562527796), true);
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST(IsEqual(cgx, -0.22117344801586084), true);
   TRY_TEST(IsEqual(cgy, 39.565942803019738), true);
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST(cst, csCentroidal);

   Float64 xleft, xright, ytop, ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft, 29.778826551984139), true);
   TRY_TEST(IsEqual(xright, 30.221173448015861), true);
   TRY_TEST(IsEqual(ytop, 69.9 - 39.565942803019738), true);
   TRY_TEST(IsEqual(ybottom, 39.565942803019738), true);

   //
   // Perimeter
   //
   TRY_TEST(shape->get_Perimeter(nullptr), E_POINTER);
   TRY_TEST(shape->get_Perimeter(&val), S_OK);
   TRY_TEST(IsEqual(val, 301.89593547481729), true);

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
   TRY_TEST(shape->FurthestDistance(nullptr, &dist), E_INVALIDARG);
   TRY_TEST(shape->FurthestDistance(line, nullptr), E_POINTER);
   TRY_TEST(shape->FurthestDistance(line, &dist), S_OK);
   TRY_TEST(IsEqual(dist, 20.000), true);

   // shape on left
   p1->Move(0, -20);
   p2->Move(100, -20);
   line->ThroughPoints(p1, p2);
   TRY_TEST(shape->FurthestDistance(line, &dist), S_OK);
   TRY_TEST(IsEqual(dist, -20.0), true);


   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance(CLSID_Point2d);
   pnt->Move(0.0, 1.0);

   TRY_TEST(shape->PointInShape(nullptr, &bPointInShape), E_INVALIDARG);
   TRY_TEST(shape->PointInShape(pnt, nullptr), E_POINTER);
   TRY_TEST(shape->PointInShape(pnt, &bPointInShape), S_OK);
   TRY_TEST(bPointInShape, VARIANT_TRUE);

   pnt->Move(500, 500);
   TRY_TEST(shape->PointInShape(pnt, &bPointInShape), S_OK);
   TRY_TEST(bPointInShape, VARIANT_FALSE);

   pnt->Move(0, 0); // Point on perimeter
   TRY_TEST(shape->PointInShape(pnt, &bPointInShape), S_OK);
   TRY_TEST(bPointInShape, VARIANT_FALSE);
}

void CTestBulbTee2::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST(position.CoCreateInstance(CLSID_BulbTee2), S_OK);

   CComQIPtr<IBulbTee2> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance(CLSID_Point2d);
   hookPnt->Move(0, 0);

   // Try some real dimensions (WSDOT WF69G)
   TRY_TEST(beam->putref_HookPoint(hookPnt), S_OK);
   TRY_TEST(beam->put_D1(6), S_OK);
   TRY_TEST(beam->put_D2(3), S_OK);
   TRY_TEST(beam->put_D3(3), S_OK);
   TRY_TEST(beam->put_D4(5.125), S_OK);
   TRY_TEST(beam->put_D5(4.5), S_OK);
   TRY_TEST(beam->put_D6(3), S_OK);
   TRY_TEST(beam->put_D7(44.375), S_OK);
   TRY_TEST(beam->put_W1(18.4375), S_OK);
   TRY_TEST(beam->put_W2(3), S_OK);
   TRY_TEST(beam->put_W3(13.125), S_OK);
   TRY_TEST(beam->put_W4(3), S_OK);
   TRY_TEST(beam->put_W5(30), S_OK);
   TRY_TEST(beam->put_W6(30), S_OK);
   TRY_TEST(beam->put_T1(6.125), S_OK);
   TRY_TEST(beam->put_T2(6.125), S_OK);
   TRY_TEST(beam->put_C1(1), S_OK);
   TRY_TEST(beam->put_C2(15), S_OK);
   TRY_TEST(beam->put_n1(0.02), S_OK);
   TRY_TEST(beam->put_n2(-0.02), S_OK);

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

   TRY_TEST(position->MoveEx(nullptr, to), E_INVALIDARG);
   TRY_TEST(position->MoveEx(from, nullptr), E_INVALIDARG);
   TRY_TEST(position->MoveEx(from, to), S_OK);

   props.Release();
   shape->get_ShapeProperties(&props);
   Float64 val;
   props->get_Ixx(&val);
   TRY_TEST(IsEqual(Ixx, val), true);
   props->get_Iyy(&val);
   TRY_TEST(IsEqual(Iyy, val), true);

   //
   // OffsetEx
   //

   CComPtr<ISize2d> size;
   size.CoCreateInstance(CLSID_Size2d);
   size->put_Dx(-100);
   size->put_Dy(-100);

   TRY_TEST(position->OffsetEx(nullptr), E_INVALIDARG);
   TRY_TEST(position->OffsetEx(size), S_OK);

   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Ixx(&val);
   TRY_TEST(IsEqual(Ixx, val), true);
   props->get_Iyy(&val);
   TRY_TEST(IsEqual(Iyy, val), true);

   ///
   // LocatorPoint property
   //
   hookPnt->Move(0, 0);
   TRY_TEST(position->put_LocatorPoint(lpBottomLeft, nullptr), E_INVALIDARG);
   TRY_TEST(position->get_LocatorPoint(lpBottomLeft, nullptr), E_POINTER);

   Float64 x, y;

   // BottomLeft
   hookPnt->Move(0, 0);
   to->Move(100, 100);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpBottomLeft, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpBottomLeft, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.000), true);
   TRY_TEST(IsEqual(y, 100.000), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 130.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);

   // BottomCenter
   hookPnt->Move(0.0, 0.0);
   to->Move(100.000, 100.000);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpBottomCenter, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpBottomCenter, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.000), true);
   TRY_TEST(IsEqual(y, 100.000), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);

   // BottomRight
   hookPnt->Move(0, 0);
   to->Move(100.000, 100.000);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpBottomRight, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpBottomRight, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.000), true);
   TRY_TEST(IsEqual(y, 100.000), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 70.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);

   // CenterLeft
   hookPnt->Move(0, 0);
   to->Move(100, 100);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpCenterLeft, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpCenterLeft, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 130.0), true);
   TRY_TEST(IsEqual(y, 65.05), true);

   // CenterCenter
   hookPnt->Move(0, 0);
   to->Move(100, 100);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpCenterCenter, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpCenterCenter, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 65.05), true);

   // CenterRight
   hookPnt->Move(0, 0);
   to->Move(100.0, 100.0);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpCenterRight, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpCenterRight, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 70.0), true);
   TRY_TEST(IsEqual(y, 65.05), true);

   // TopLeft
   hookPnt->Move(0, 0);
   to->Move(100.0, 100.0);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpTopLeft, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpTopLeft, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 130.0), true);
   TRY_TEST(IsEqual(y, 30.1), true);

   // TopCenter
   hookPnt->Move(0, 0);
   to->Move(100.0, 100.0);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpTopCenter, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpTopCenter, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 30.1), true);

   // TopRight
   hookPnt->Move(0, 0);
   to->Move(100.0, 100.0);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpTopRight, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpTopRight, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 70.0), true);
   TRY_TEST(IsEqual(y, 30.1), true);

   // HookPoint
   hookPnt->Move(0, 0);
   to->Move(100, 100);
   from.Release();
   TRY_TEST(position->put_LocatorPoint(lpHookPoint, to), S_OK);
   TRY_TEST(position->get_LocatorPoint(lpHookPoint, &from), S_OK);
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 100.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);
}

void CTestBulbTee2::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST(eInfo.CoCreateInstance(CLSID_BulbTee2), S_OK);
   TRY_TEST(eInfo != 0, true);

   // Interfaces that should be supported
   TRY_TEST(eInfo->InterfaceSupportsErrorInfo(IID_IBulbTee2), S_OK);
   TRY_TEST(eInfo->InterfaceSupportsErrorInfo(IID_IShape), S_OK);
   TRY_TEST(eInfo->InterfaceSupportsErrorInfo(IID_IXYPosition), S_OK);
   TRY_TEST(eInfo->InterfaceSupportsErrorInfo(IID_IStructuredStorage2), S_OK);

   // Interface that is not supported
   TRY_TEST(eInfo->InterfaceSupportsErrorInfo(IID_ISupportErrorInfo), S_FALSE);
}
