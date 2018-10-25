///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestUBeam2.cpp: implementation of the CTestUBeam2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUBeam2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUBeam2::CTestUBeam2()
{

}

CTestUBeam2::~CTestUBeam2()
{

}

void CTestUBeam2::Test()
{
   TestIUBeam2();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestUBeam2::TestIUBeam2()
{
   CComPtr<IUBeam2> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_UBeam2), S_OK );

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_D1(NULL), E_POINTER );
   TRY_TEST( beam->get_D1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D2(NULL), E_POINTER );
   TRY_TEST( beam->get_D2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D3(NULL), E_POINTER );
   TRY_TEST( beam->get_D3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D4(NULL), E_POINTER );
   TRY_TEST( beam->get_D4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D5(NULL), E_POINTER );
   TRY_TEST( beam->get_D5(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D6(NULL), E_POINTER );
   TRY_TEST( beam->get_D6(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_T(NULL), E_POINTER );
   TRY_TEST( beam->get_T(&val), S_OK );
   TRY_TEST( IsZero(val), true );


   TRY_TEST( beam->get_W1(NULL), E_POINTER );
   TRY_TEST( beam->get_W1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W2(NULL), E_POINTER );
   TRY_TEST( beam->get_W2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W3(NULL), E_POINTER );
   TRY_TEST( beam->get_W3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W4(NULL), E_POINTER );
   TRY_TEST( beam->get_W4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W5(NULL), E_POINTER );
   TRY_TEST( beam->get_W5(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W6(NULL), E_POINTER );
   TRY_TEST( beam->get_W6(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W7(NULL), E_POINTER );
   TRY_TEST( beam->get_W7(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_C1(NULL), E_POINTER );
   TRY_TEST( beam->get_C1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_HookPoint(NULL), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_D1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D1(14), S_OK );
   beam->get_D1(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D2(14), S_OK );
   beam->get_D2(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_D3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D3(14), S_OK );
   beam->get_D3(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_D4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D4(14), S_OK );
   beam->get_D4(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_D5(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D5(14), S_OK );
   beam->get_D5(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_D6(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D6(14), S_OK );
   beam->get_D6(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W1(14), S_OK );
   beam->get_W1(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W2(14), S_OK );
   beam->get_W2(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_W3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W3(14), S_OK );
   beam->get_W3(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_W4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W4(14), S_OK );
   beam->get_W4(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_W5(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W5(14), S_OK );
   beam->get_W5(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_W6(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W6(14), S_OK );
   beam->get_W6(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_W7(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W7(14), S_OK );
   beam->get_W7(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_C1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_C1(14), S_OK );
   beam->get_C1(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   pntVal->Move(14,14);
   TRY_TEST( beam->putref_HookPoint(NULL), E_INVALIDARG );
   TRY_TEST( beam->putref_HookPoint(pntVal), S_OK );
   pntVal.Release();
   beam->get_HookPoint(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,14.0), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,14.0), true );

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

   TRY_TEST(beam->get_Height(NULL), E_POINTER );
   TRY_TEST(beam->get_Height(&val), S_OK );
   TRY_TEST(IsEqual(val,40.0), true );

   TRY_TEST(beam->get_Slope(0,NULL),E_POINTER);
   TRY_TEST(beam->get_Slope(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_Slope(2,&val),E_INVALIDARG);
   TRY_TEST(beam->get_Slope(0,&val),S_OK);
   TRY_TEST(IsEqual(val,-3.970149),true);
   TRY_TEST(beam->get_Slope(1,&val),S_OK);
   TRY_TEST(IsEqual(val,3.970149),true);
   
   TRY_TEST(beam->get_TopWidth(NULL),E_POINTER);
   TRY_TEST(beam->get_TopWidth(&val),S_OK);
   TRY_TEST(IsEqual(val,89.0),true);

   TRY_TEST(beam->get_TopFlangeWidth(NULL),E_POINTER);
   TRY_TEST(beam->get_TopFlangeWidth(&val),S_OK);
   TRY_TEST(IsEqual(val,15.75),true);

   TRY_TEST(beam->get_WebSpacing(NULL),E_POINTER);
   TRY_TEST(beam->get_WebSpacing(&val),S_OK);
   TRY_TEST(IsEqual(val,70.022086466165405),true);

   TRY_TEST(beam->get_WebLocation(0,NULL),E_POINTER);
   TRY_TEST(beam->get_WebLocation(-1,&val),E_INVALIDARG);
   TRY_TEST(beam->get_WebLocation(2,&val),E_INVALIDARG);
   TRY_TEST(beam->get_WebLocation(0,&val),S_OK);
   TRY_TEST(IsEqual(val,-35.011043233082702),true);
   TRY_TEST(beam->get_WebLocation(1,&val),S_OK);
   TRY_TEST(IsEqual(val,35.011043233082702),true);

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(beam->get_Shape(NULL), E_POINTER );
   TRY_TEST(beam->get_Shape(&shape), S_OK );
   TRY_TEST(shape != NULL,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(beam->get_XYPosition(NULL), E_POINTER );
   TRY_TEST(beam->get_XYPosition(&position), S_OK );
   TRY_TEST(position != NULL,true );

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   beam->QueryInterface(&punk1);
   shape->QueryInterface(&punk2);
   position->QueryInterface(&punk3);
   TRY_TEST( punk1 == punk2, true );
   TRY_TEST( punk1 == punk3, true );
   TRY_TEST( punk2 == punk3, true );
}

void CTestUBeam2::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_UBeam2 ), S_OK );
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
   TRY_TEST( shape->get_BoundingBox(NULL), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-44.5), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, 44.5), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val, 40.00), true );

   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val, 0.00), true );

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
   TRY_TEST( IsEqual(area,978.1015625), true );
   TRY_TEST( IsEqual(ixx, 183371.372367286), true );
   TRY_TEST( IsEqual(iyy, 672244.006479706), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,16.3516905452245), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,44.5),true);
   TRY_TEST(IsEqual(xright,44.5),true);
   TRY_TEST(IsEqual(ytop,23.6483094547755),true);
   TRY_TEST(IsEqual(ybottom,16.3516905452245),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(NULL), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,294.425976857583), true );

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
   TRY_TEST( shape->FurthestDistance(NULL,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,NULL), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,20.000), true );

   // shape on left
   p1->Move(0,-20);
   p2->Move(100,-20);
   line->ThroughPoints(p1,p2);
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-20.0), true );

   // 
   // PolyPoints
   //
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );

   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 17 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[17];
   ULONG fetched;
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-35.875), true );
   TRY_TEST( IsEqual(y, 33.25), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-44.125), true );
   TRY_TEST( IsEqual(y, 34.125), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-44.500), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-28.750), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.000), true );
   TRY_TEST( IsEqual(y, 18.375), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,-25.205357), true );
   TRY_TEST( IsEqual(y, 11.2500), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.205357), true );
   TRY_TEST( IsEqual(y,  8.2500), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.205357), true );
   TRY_TEST( IsEqual(y,  8.2500), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x, 25.205357), true );
   TRY_TEST( IsEqual(y, 11.2500), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.000), true );
   TRY_TEST( IsEqual(y, 18.375), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x, 28.750), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.500), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.125), true );
   TRY_TEST( IsEqual(y, 34.125), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x, 35.875), true );
   TRY_TEST( IsEqual(y, 33.250), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(NULL), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IUBeam2> beamClone(clone);
   TRY_TEST( beamClone != 0, true );

   beamClone->get_W1(&val);
   TRY_TEST( IsEqual(val,55.00), true);

   beamClone->get_W2(&val);
   TRY_TEST( IsEqual(val,89.0), true);

   beamClone->get_W3(&val);
   TRY_TEST( IsEqual(val,3.00), true);

   beamClone->get_W4(&val);
   TRY_TEST( IsEqual(val, 0.375), true);

   beamClone->get_W5(&val);
   TRY_TEST( IsEqual(val, 8.25), true);

   beamClone->get_W6(&val);
   TRY_TEST( IsEqual(val, 15.75), true);

   beamClone->get_W7(&val);
   TRY_TEST( IsEqual(val, 1.75), true);

   beamClone->get_D1(&val);
   TRY_TEST( IsEqual(val,40.0), true);

   beamClone->get_D2(&val);
   TRY_TEST( IsEqual(val,8.25), true);

   beamClone->get_D3(&val);
   TRY_TEST( IsEqual(val,3.00), true);

   beamClone->get_D4(&val);
   TRY_TEST( IsEqual(val,0.875), true);

   beamClone->get_D5(&val);
   TRY_TEST( IsEqual(val,5.875), true);

   beamClone->get_D6(&val);
   TRY_TEST( IsEqual(val,21.625), true);

   beamClone->get_C1(&val);
   TRY_TEST( IsEqual(val,0.0), true);

   beamClone->get_T(&val);
   TRY_TEST( IsEqual(val,4.972964), true);

   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(0.0, 0.5);

   TRY_TEST( shape->PointInShape(NULL,&bPointInShape), E_INVALIDARG );
   TRY_TEST( shape->PointInShape(pnt,NULL), E_POINTER );
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_TRUE );

   pnt->Move(500,500);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   pnt->Move(0,0); // Point on perimeter
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

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
   TRY_TEST(shape->ClipWithLine(NULL,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,NULL), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( CollectionIndexType i = 0; i < cPoints; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 6 );

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.000), true );
   TRY_TEST( IsEqual(y, 0.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, -27.625939849624064), true );
   TRY_TEST( IsEqual(y,   0.5000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.625939849624057), true );
   TRY_TEST( IsEqual(y,   0.5000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.000), true );
   TRY_TEST( IsEqual(y, 0.000), true );

   // clip in other direction
   p1->Move( 50, 25.0);
   p2->Move(-50, 25.0);

   clipLine->ThroughPoints(p1,p2);

   clip.Release();
   TRY_TEST(shape->ClipWithLine(NULL,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,NULL), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   
   coll.Release();
   Enum.Release();
   for ( CollectionIndexType i = 0; i < cPoints; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 12);

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, -33.796992481203013), true );
   TRY_TEST( IsEqual(y,  25.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-35.875), true );
   TRY_TEST( IsEqual(y, 33.250), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, -44.125), true );
   TRY_TEST( IsEqual(y,  34.125), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, -44.500), true );
   TRY_TEST( IsEqual(y,  40.000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-28.750), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.536127167630060), true );
   TRY_TEST( IsEqual(y, 25.0000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.536127167630060), true );
   TRY_TEST( IsEqual(y, 25.0000), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, 28.750), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.500), true );
   TRY_TEST( IsEqual(y, 40.0000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.125), true );
   TRY_TEST( IsEqual(y, 34.125), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x, 35.875), true );
   TRY_TEST( IsEqual(y, 33.250), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 33.796992481203013), true );
   TRY_TEST( IsEqual(y, 25.000), true );

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

   TRY_TEST( shape->ClipIn(NULL,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,NULL), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for (CollectionIndexType i = 0; i < cPoints; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   ATLTRACE("Trace of Points for UBeam2 - count = %d \n", cPoints);
   ATLTRACE("  pt         X         Y\n");
   ATLTRACE("---------------------------------\n");
   for (CollectionIndexType ip=0; ip<cPoints; ip++)
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
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.625940), true );
   TRY_TEST( IsEqual(y, 0.5), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.651128), true );
   TRY_TEST( IsEqual(y, 0.6), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.651128), true );
   TRY_TEST( IsEqual(y, 0.6), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.625940), true );
   TRY_TEST( IsEqual(y, 0.5), true );
}

void CTestUBeam2::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_UBeam2), S_OK);

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

   TRY_TEST( position->MoveEx(NULL,to), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,NULL), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to), S_OK );

   // Check the points
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,17);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[17];
   ULONG fetched;
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 72.500), true );
   TRY_TEST( IsEqual(y,100.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,64.125), true );
   TRY_TEST( IsEqual(y,133.25), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,55.875), true );
   TRY_TEST( IsEqual(y,134.125), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,55.5), true );
   TRY_TEST( IsEqual(y,140.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,71.25), true );
   TRY_TEST( IsEqual(y,140.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,73.0), true );
   TRY_TEST( IsEqual(y,118.375), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,74.79464), true );
   TRY_TEST( IsEqual(y,111.25), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,77.79464), true );
   TRY_TEST( IsEqual(y,108.25), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,122.205357), true );
   TRY_TEST( IsEqual(y,108.25), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,125.205357), true );
   TRY_TEST( IsEqual(y,111.25), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,127.0), true );
   TRY_TEST( IsEqual(y,118.375), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,128.75), true );
   TRY_TEST( IsEqual(y,140.0), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,144.5), true );
   TRY_TEST( IsEqual(y,140.0), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x,144.125), true );
   TRY_TEST( IsEqual(y,134.125), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x,135.875), true );
   TRY_TEST( IsEqual(y,133.25), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x,127.500), true );
   TRY_TEST( IsEqual(y,100.000), true );

   //
   // OffsetEx
   //

   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(-100);
   size->put_Dy(-100);

   TRY_TEST(position->OffsetEx(NULL), E_INVALIDARG );
   TRY_TEST(position->OffsetEx(size), S_OK);

   // Check the points
   coll.Release();
   Enum.Release();
   for ( CollectionIndexType i = 0; i < cPoints; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,17);

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-35.875), true );
   TRY_TEST( IsEqual(y, 33.25), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-44.125), true );
   TRY_TEST( IsEqual(y, 34.125), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-44.500), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-28.750), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.000), true );
   TRY_TEST( IsEqual(y, 18.375), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,-25.205357), true );
   TRY_TEST( IsEqual(y, 11.2500), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.205357), true );
   TRY_TEST( IsEqual(y,  8.2500), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.205357), true );
   TRY_TEST( IsEqual(y,  8.2500), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x, 25.205357), true );
   TRY_TEST( IsEqual(y, 11.2500), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.000), true );
   TRY_TEST( IsEqual(y, 18.375), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x, 28.750), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.500), true );
   TRY_TEST( IsEqual(y, 40.000), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.125), true );
   TRY_TEST( IsEqual(y, 34.125), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x, 35.875), true );
   TRY_TEST( IsEqual(y, 33.250), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   //
   // LocatorPoint property
   //
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,NULL), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,NULL), E_POINTER );

   // BottomLeft
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,144.5), true );
   TRY_TEST(IsEqual(y,100.00), true );

   // BottomCenter
   hookPnt->Move(0.0,0.0);
   to->Move(100.000,100.000);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomRight
   hookPnt->Move(0,0);
   to->Move(100.000,100.000);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,55.5), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterLeft
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,144.5), true );
   TRY_TEST(IsEqual(y,80.0), true );

   // CenterCenter
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,80.0), true );

   // CenterRight
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,55.5), true );
   TRY_TEST(IsEqual(y,80.0), true );

   // TopLeft
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,144.5), true );
   TRY_TEST(IsEqual(y,60.0), true );

   // TopCenter
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y, 60.0), true );

   // TopRight
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,55.5), true );
   TRY_TEST(IsEqual(y,60.0), true );

   // HookPoint
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpHookPoint, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpHookPoint, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0,0);
   CComPtr<IPoint2d> c;
   c.CoCreateInstance( CLSID_Point2d );
   c->put_X(0);
   c->put_Y(0);

   TRY_TEST( position->RotateEx(NULL,M_PI), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI), S_OK );

   // Check the points
   coll.Release();
   Enum.Release();
   for (CollectionIndexType i = 0; i < cPoints; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,17);

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 35.875), true );
   TRY_TEST( IsEqual(y,-33.25), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.125), true );
   TRY_TEST( IsEqual(y,-34.125), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x, 44.500), true );
   TRY_TEST( IsEqual(y,-40.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x, 28.750), true );
   TRY_TEST( IsEqual(y,-40.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, 27.000), true );
   TRY_TEST( IsEqual(y,-18.375), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, 25.205357), true );
   TRY_TEST( IsEqual(y,-11.2500), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.205357), true );
   TRY_TEST( IsEqual(y, -8.2500), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.205357), true );
   TRY_TEST( IsEqual(y, -8.2500), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,-25.205357), true );
   TRY_TEST( IsEqual(y,-11.2500), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.000), true );
   TRY_TEST( IsEqual(y,-18.375), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,-28.750), true );
   TRY_TEST( IsEqual(y,-40.000), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,-44.500), true );
   TRY_TEST( IsEqual(y,-40.000), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x,-44.125), true );
   TRY_TEST( IsEqual(y,-34.125), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x,-35.875), true );
   TRY_TEST( IsEqual(y,-33.250), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x,-27.500), true );
   TRY_TEST( IsEqual(y,  0.000), true );
}

void CTestUBeam2::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_UBeam2 ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IUBeam2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
