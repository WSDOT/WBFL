///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// TestBoxBeam.cpp: implementation of the CTestBoxBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestBoxBeam.h"
#include <array>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestBoxBeam::CTestBoxBeam()
{

}

CTestBoxBeam::~CTestBoxBeam()
{

}

void CTestBoxBeam::Test()
{
   TestIBoxBeam();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestBoxBeam::TestIBoxBeam()
{
   CComPtr<IBoxBeam> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_BoxBeam), S_OK );

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_H1(nullptr), E_POINTER );
   TRY_TEST( beam->get_H1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_H2(nullptr), E_POINTER );
   TRY_TEST( beam->get_H2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_H3(nullptr), E_POINTER );
   TRY_TEST( beam->get_H3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_H4(nullptr), E_POINTER );
   TRY_TEST( beam->get_H4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_H5(nullptr), E_POINTER );
   TRY_TEST( beam->get_H5(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_H6(nullptr), E_POINTER );
   TRY_TEST( beam->get_H6(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_H7(nullptr), E_POINTER );
   TRY_TEST( beam->get_H7(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W1(nullptr), E_POINTER );
   TRY_TEST( beam->get_W1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W2(nullptr), E_POINTER );
   TRY_TEST( beam->get_W2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W3(nullptr), E_POINTER );
   TRY_TEST( beam->get_W3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W4(nullptr), E_POINTER );
   TRY_TEST( beam->get_W4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_F1(nullptr), E_POINTER );
   TRY_TEST( beam->get_F1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_F2(nullptr), E_POINTER );
   TRY_TEST( beam->get_F2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_C1(nullptr), E_POINTER );
   TRY_TEST( beam->get_C1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_HookPoint(nullptr), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_H1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_H2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_H3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_H4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_H5(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_H6(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_H7(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_F1(-1),  GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_F2(-1),  GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_C1(-1),  GEOMETRY_E_DIMENSION );

   // Try some real dimensions (TXDOT Box Beam Type 4B40)
   TRY_TEST( beam->put_H1( 5.5), S_OK);
   TRY_TEST( beam->put_H2(29.5), S_OK);
   TRY_TEST( beam->put_H3( 5.0), S_OK);
   TRY_TEST( beam->put_H4( 4.0), S_OK);
   TRY_TEST( beam->put_H5( 3.0), S_OK);
   TRY_TEST( beam->put_H6( 5.0), S_OK);
   TRY_TEST( beam->put_H7(17.0), S_OK);
   TRY_TEST( beam->put_W1( 3.0), S_OK);
   TRY_TEST( beam->put_W2( 5.0), S_OK);
   TRY_TEST( beam->put_W3(27.75), S_OK);
   TRY_TEST( beam->put_W4( 5.0), S_OK);
   TRY_TEST( beam->put_F1(  5.0), S_OK);
   TRY_TEST( beam->put_F2(  5.0), S_OK);
   TRY_TEST( beam->put_C1(  0.0), S_OK);

   TRY_TEST( beam->get_H1(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.5), true );

   TRY_TEST( beam->get_H2(&val), S_OK);
   TRY_TEST( IsEqual(val,29.5), true );

   TRY_TEST( beam->get_H3(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );

   TRY_TEST( beam->get_H4(&val), S_OK);
   TRY_TEST( IsEqual(val, 4.0), true );

   TRY_TEST( beam->get_H5(&val), S_OK);
   TRY_TEST( IsEqual(val, 3.0), true );   
   
   TRY_TEST( beam->get_H6(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );

   TRY_TEST( beam->get_H7(&val), S_OK);
   TRY_TEST( IsEqual(val,17.0), true );

   TRY_TEST( beam->get_W1(&val), S_OK);
   TRY_TEST( IsEqual(val, 3.0), true );
   
   TRY_TEST( beam->get_W2(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );
   
   TRY_TEST( beam->get_W3(&val), S_OK);
   TRY_TEST( IsEqual(val,27.75), true );
   
   TRY_TEST( beam->get_W4(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );
   
   TRY_TEST( beam->get_F1(&val), S_OK);
   TRY_TEST( IsEqual(val,5.0), true );
   
   TRY_TEST( beam->get_F2(&val), S_OK);
   TRY_TEST( IsEqual(val,5.0), true );
   
   TRY_TEST( beam->get_C1(&val), S_OK);
   TRY_TEST( IsEqual(val,0.0), true );

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(beam->get_Shape(nullptr), E_POINTER );
   TRY_TEST(beam->get_Shape(&shape), S_OK );
   TRY_TEST(shape != nullptr,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(beam->get_XYPosition(nullptr), E_POINTER );
   TRY_TEST(beam->get_XYPosition(&position), S_OK );
   TRY_TEST(position != nullptr,true );

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

void CTestBoxBeam::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_BoxBeam ), S_OK );
   CComQIPtr<IBoxBeam> beam(shape);

   // Try some real dimensions (TXDOT Box Beam Type 4B40)
   beam->put_H1( 5.5);
   beam->put_H2(29.5);
   beam->put_H3( 5.0);
   beam->put_H4( 4.0);
   beam->put_H5( 3.0);
   beam->put_H6( 5.0);
   beam->put_H7(17.0);
   beam->put_W1( 3.0);
   beam->put_W2( 5.0);
   beam->put_W3(27.75);
   beam->put_W4( 5.0);
   beam->put_F1(  5.0);
   beam->put_F2(  5.0);
   beam->put_C1(  0.0);

   //
   // Bounding Box
   //
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(nullptr), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-23.875), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, 23.875), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val, 40.0), true );

   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,  0.0), true );

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
   TRY_TEST( IsEqual(area,969.375), true );
   TRY_TEST( IsEqual(ixx, 185480.77672323846), true );
   TRY_TEST( IsEqual(iyy, 236459.59049479163), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,18.731990113905013), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,23.875),true);
   TRY_TEST(IsEqual(xright,23.875),true);
   TRY_TEST(IsEqual(ytop,21.268009886094987),true);
   TRY_TEST(IsEqual(ybottom,18.731990113905013),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(nullptr), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,178.12741699796953), true );

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
   TRY_TEST( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,nullptr), E_POINTER );
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
   TRY_TEST( shape->get_PolyPoints(nullptr), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );

   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 14 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>,14> points;
   ULONG fetched;
   Enum->Next(14,&points[0],&fetched);
   TRY_TEST( fetched, 14 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,  0.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y,17.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,18.875), true );
   TRY_TEST( IsEqual(y,22.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,18.875), true );
   TRY_TEST( IsEqual(y,33.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,21.875), true );
   TRY_TEST( IsEqual(y,36.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,21.875), true );
   TRY_TEST( IsEqual(y,40.0), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y, 40.0), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y, 36.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y, 33.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y, 22.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y, 17.0), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.0), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(nullptr), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IBoxBeam> beamClone(clone);
   TRY_TEST( beamClone != 0, true );

   TRY_TEST( beamClone->get_H1(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.5), true );

   TRY_TEST( beamClone->get_H2(&val), S_OK);
   TRY_TEST( IsEqual(val,29.5), true );

   TRY_TEST( beamClone->get_H3(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );

   TRY_TEST( beamClone->get_H4(&val), S_OK);
   TRY_TEST( IsEqual(val, 4.0), true );

   TRY_TEST( beamClone->get_H5(&val), S_OK);
   TRY_TEST( IsEqual(val, 3.0), true );   
   
   TRY_TEST( beamClone->get_H6(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );

   TRY_TEST( beamClone->get_H7(&val), S_OK);
   TRY_TEST( IsEqual(val,17.0), true );

   TRY_TEST( beamClone->get_W1(&val), S_OK);
   TRY_TEST( IsEqual(val, 3.0), true );
   
   TRY_TEST( beamClone->get_W2(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );
   
   TRY_TEST( beamClone->get_W3(&val), S_OK);
   TRY_TEST( IsEqual(val,27.75), true );
   
   TRY_TEST( beamClone->get_W4(&val), S_OK);
   TRY_TEST( IsEqual(val, 5.0), true );
   
   TRY_TEST( beamClone->get_F1(&val), S_OK);
   TRY_TEST( IsEqual(val,5.0), true );
   
   TRY_TEST( beamClone->get_F2(&val), S_OK);
   TRY_TEST( IsEqual(val,5.0), true );
   
   TRY_TEST( beamClone->get_C1(&val), S_OK);
   TRY_TEST( IsEqual(val,0.0), true );

   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(0.0, 1.0);

   TRY_TEST( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
   TRY_TEST( shape->PointInShape(pnt,nullptr), E_POINTER );
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
   TRY_TEST(shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,nullptr), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 14; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 6 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 6 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,  0.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y, 0.5), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y,  0.5), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,  0.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   // clip in other direction
   p1->Move( 50, 0.50);
   p2->Move(-50, 0.50);

   clipLine->ThroughPoints(p1,p2);

   clip.Release();
   TRY_TEST(shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,nullptr), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 14; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 12 );

   coll->get__Enum(&Enum);
   Enum->Next(14,&points[0],&fetched);
   TRY_TEST( fetched, 12 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y, 0.5), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y,17.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,18.875), true );
   TRY_TEST( IsEqual(y,22.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,18.875), true );
   TRY_TEST( IsEqual(y,33.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,21.875), true );
   TRY_TEST( IsEqual(y,36.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,21.875), true );
   TRY_TEST( IsEqual(y,40.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y, 40.0), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y, 36.000), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y, 33.0), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y, 22.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y, 17.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y,  0.5), true );

   //
   // ClipIn
   //
   clip.Release();

   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );
   clipRect->put_Left(-100);
   clipRect->put_Right(100);
   clipRect->put_Top(16.5);
   clipRect->put_Bottom(1.5);

   TRY_TEST( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,nullptr), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 14; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   ATLTRACE("Trace of Points for BoxBeam - count = %d \n", cPoints);
   ATLTRACE("  pt         X         Y\n");
   ATLTRACE("---------------------------------\n");
   for (CollectionIndexType ip = 0; ip<cPoints; ip++)
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
   Enum->Next(4,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 23.875), true );
   TRY_TEST( IsEqual(y,  1.5), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 23.875), true );
   TRY_TEST( IsEqual(y, 16.5), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y, 16.5), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y,  1.5), true );
}

void CTestBoxBeam::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_BoxBeam), S_OK);

   CComQIPtr<IBoxBeam> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Try some real dimensions (TXDOT Box Beam Type 4B40)
   beam->putref_HookPoint(hookPnt);
   beam->put_H1( 5.5);
   beam->put_H2(29.5);
   beam->put_H3( 5.0);
   beam->put_H4( 4.0);
   beam->put_H5( 3.0);
   beam->put_H6( 5.0);
   beam->put_H7(17.0);
   beam->put_W1( 3.0);
   beam->put_W2( 5.0);
   beam->put_W3(27.75);
   beam->put_W4( 5.0);
   beam->put_F1(  5.0);
   beam->put_F2(  5.0);
   beam->put_C1(  0.0);


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
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(0,0);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(100,100);

   TRY_TEST( position->MoveEx(nullptr,to), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,nullptr), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to), S_OK );

   // Check the points
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(nullptr), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,14);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>,15> points;
   ULONG fetched;
   Enum->Next(14,&points[0],&fetched);
   TRY_TEST( fetched, 14 );

   Float64 x,y;


   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 100.0), true );
   TRY_TEST( IsEqual(y, 100.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,123.875), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,123.875), true );
   TRY_TEST( IsEqual(y,117.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,118.875), true );
   TRY_TEST( IsEqual(y,122.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,118.875), true );
   TRY_TEST( IsEqual(y,133.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,121.875), true );
   TRY_TEST( IsEqual(y,136.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,121.875), true );
   TRY_TEST( IsEqual(y,140.0), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, 78.125), true );
   TRY_TEST( IsEqual(y, 140.0), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x, 78.125), true );
   TRY_TEST( IsEqual(y,136.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,81.125), true );
   TRY_TEST( IsEqual(y,133.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,81.125), true );
   TRY_TEST( IsEqual(y,122.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,76.125), true );
   TRY_TEST( IsEqual(y,117.0), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,76.125), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   props.Release();
   shape->get_ShapeProperties(&props);
   Float64 val;
   props->get_Ixx(&val);
   TRY_TEST(IsEqual(Ixx,val),true);
   props->get_Iyy(&val);
   TRY_TEST(IsEqual(Iyy,val),true);

   //
   // OffsetEx
   //

   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(-100);
   size->put_Dy(-100);

   TRY_TEST(position->OffsetEx(nullptr), E_INVALIDARG );
   TRY_TEST(position->OffsetEx(size), S_OK);

   // Check the points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 14; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,14);

   coll->get__Enum(&Enum);
   Enum->Next(14,&points[0],&fetched);
   TRY_TEST( fetched, 14 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,  0.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,23.875), true );
   TRY_TEST( IsEqual(y,17.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,18.875), true );
   TRY_TEST( IsEqual(y,22.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,18.875), true );
   TRY_TEST( IsEqual(y,33.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,21.875), true );
   TRY_TEST( IsEqual(y,36.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,21.875), true );
   TRY_TEST( IsEqual(y,40.0), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y, 40.0), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y, 36.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y, 33.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y, 22.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y, 17.0), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.0), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Ixx(&val);
   TRY_TEST(IsEqual(Ixx,val),true);
   props->get_Iyy(&val);
   TRY_TEST(IsEqual(Iyy,val),true);

   //
   // LocatorPoint property
   //
   hookPnt->Move(0,0);
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

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
   TRY_TEST(IsEqual(x,123.875), true );
   TRY_TEST(IsEqual(y,100.0), true );

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
   TRY_TEST(IsEqual(x, 76.125), true );
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
   TRY_TEST(IsEqual(x,123.875), true );
   TRY_TEST(IsEqual(y, 80.0), true );

   // CenterCenter
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y, 80.0), true );

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
   TRY_TEST(IsEqual(x, 76.125), true );
   TRY_TEST(IsEqual(y, 80.0), true );

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
   TRY_TEST(IsEqual(x,123.875), true );
   TRY_TEST(IsEqual(y, 60.0), true );

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
   TRY_TEST(IsEqual(x, 76.125), true );
   TRY_TEST(IsEqual(y, 60.0), true );

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

   TRY_TEST( position->RotateEx(nullptr,M_PI), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI), S_OK );

   // Check the points
   coll.Release();
   Enum.Release();
   for (int i = 0; i < 14; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,14);

   coll->get__Enum(&Enum);
   Enum->Next(15,&points[0],&fetched);
   TRY_TEST( fetched, 14 );


   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,  0.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-23.875), true );
   TRY_TEST( IsEqual(y,-17.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y,-22.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-18.875), true );
   TRY_TEST( IsEqual(y,-33.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y,-36.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y,-40.0), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, 21.875), true );
   TRY_TEST( IsEqual(y,-40.0), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x, 21.875), true );
   TRY_TEST( IsEqual(y,-36.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x, 18.875), true );
   TRY_TEST( IsEqual(y,-33.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x, 18.875), true );
   TRY_TEST( IsEqual(y,-22.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 23.875), true );
   TRY_TEST( IsEqual(y,-17.0), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x, 23.875), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.0), true );
   TRY_TEST( IsEqual(y, 0.0), true );
}

void CTestBoxBeam::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_BoxBeam ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IBoxBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
