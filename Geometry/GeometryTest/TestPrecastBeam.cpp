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

// TestPrecastBeam.cpp: implementation of the CTestPrecastBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrecastBeam.h"
#include <array>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPrecastBeam::CTestPrecastBeam()
{

}

CTestPrecastBeam::~CTestPrecastBeam()
{

}

void CTestPrecastBeam::Test()
{
   TestIPrecastBeam();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestPrecastBeam::TestIPrecastBeam()
{
   CComPtr<IPrecastBeam> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_PrecastBeam), S_OK );

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_D1(nullptr), E_POINTER );
   TRY_TEST( beam->get_D1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D2(nullptr), E_POINTER );
   TRY_TEST( beam->get_D2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D3(nullptr), E_POINTER );
   TRY_TEST( beam->get_D3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D4(nullptr), E_POINTER );
   TRY_TEST( beam->get_D4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D5(nullptr), E_POINTER );
   TRY_TEST( beam->get_D5(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D6(nullptr), E_POINTER );
   TRY_TEST( beam->get_D6(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D7(nullptr), E_POINTER );
   TRY_TEST( beam->get_D7(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_T1(nullptr), E_POINTER );
   TRY_TEST( beam->get_T1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_T2(nullptr), E_POINTER );
   TRY_TEST( beam->get_T2(&val), S_OK );
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

   TRY_TEST( beam->put_D7(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D7(14), S_OK );
   beam->get_D7(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_T1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_T1(14), S_OK );
   beam->get_T1(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_T2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_T2(14), S_OK );
   beam->get_T2(&val);
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

   TRY_TEST( beam->put_C1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_C1(1), S_OK );
   beam->get_C1(&val);
   TRY_TEST( IsEqual(val,1.0), true );

   pntVal->Move(14,14);
   TRY_TEST( beam->putref_HookPoint(nullptr), E_INVALIDARG );
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

   // Use some real dimensions (WSDOT W74MG girder)
   beam->put_W1(0.419);
   beam->put_W2(0.051);
   beam->put_W3(0.241);
   beam->put_W4(0.0);
   beam->put_D1(0.073);
   beam->put_D2(0.067);
   beam->put_D3(0.051);
   beam->put_D4(0.152);
   beam->put_D5(0.076);
   beam->put_D6(0.0);
   beam->put_D7(1.448);
   beam->put_T1(0.152);
   beam->put_T2(0.152);
   beam->put_C1(0.0);

   TRY_TEST(beam->get_Height(nullptr), E_POINTER );
   TRY_TEST(beam->get_Height(&val), S_OK );
   TRY_TEST(IsEqual(val,1.867), true );

   TRY_TEST(beam->get_TopFlangeWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_TopFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,1.092), true );

   TRY_TEST(beam->get_BottomFlangeWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_BottomFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,0.634), true );

   TRY_TEST(beam->get_AvgWebWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_AvgWebWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,0.152), true );


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

void CTestPrecastBeam::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_PrecastBeam ), S_OK );
   CComQIPtr<IPrecastBeam> beam(shape);
   
   // Use some real dimensions (WSDOT W74MG girder)
   beam->put_W1(0.419);
   beam->put_W2(0.051);
   beam->put_W3(0.241);
   beam->put_W4(0.0);
   beam->put_D1(0.073);
   beam->put_D2(0.067);
   beam->put_D3(0.051);
   beam->put_D4(0.152);
   beam->put_D5(0.076);
   beam->put_D6(0.0);
   beam->put_D7(1.448);
   beam->put_T1(0.152);
   beam->put_T2(0.152);
// C1 purposely not defined - should be zero

   //
   // Bounding Box
   //
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(nullptr), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-0.546), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, 0.546), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val,1.867), true );

   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,0.00), true );

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
   TRY_TEST( IsEqual(area,0.481492), true );
   TRY_TEST( IsEqual(ixx,0.22760306149685), true );
   TRY_TEST( IsEqual(iyy,0.014501658964667), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,0.96689527690318), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,0.546),true);
   TRY_TEST(IsEqual(xright,0.546),true);
   TRY_TEST(IsEqual(ytop,1.867-cgy),true);
   TRY_TEST(IsEqual(ybottom,cgy),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(nullptr), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,6.5702946161260), true );

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
   TRY_TEST( cPoints, 19 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>, 19> points;
   ULONG fetched;
   Enum->Next(19,&points[0],&fetched);
   TRY_TEST( fetched, 19 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,1.867), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.546), true );
   TRY_TEST( IsEqual(y, 1.867), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.546), true );
   TRY_TEST( IsEqual(y, 1.794), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.127), true );
   TRY_TEST( IsEqual(y, 1.727), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y, 1.676), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y, 0.228), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y, 0.228), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.317), true );
   TRY_TEST( IsEqual(y, 0.152), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.317), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.317), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.317), true );
   TRY_TEST( IsEqual(y,0.152), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.076), true );
   TRY_TEST( IsEqual(y,0.228), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.076), true );
   TRY_TEST( IsEqual(y,0.228), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.076), true );
   TRY_TEST( IsEqual(y,1.676), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.127), true );
   TRY_TEST( IsEqual(y,1.727), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.546), true );
   TRY_TEST( IsEqual(y,1.794), true );

   points[17]->get_X(&x);
   points[17]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.546), true );
   TRY_TEST( IsEqual(y,1.867), true );

   points[18]->get_X(&x);
   points[18]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,1.867), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(nullptr), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IPrecastBeam> beamClone(clone);
   TRY_TEST( beamClone != 0, true );

   beamClone->get_W1(&val);
   TRY_TEST( IsEqual(val,0.419), true);

   beamClone->get_W2(&val);
   TRY_TEST( IsEqual(val,0.051), true);

   beamClone->get_W3(&val);
   TRY_TEST( IsEqual(val,0.241), true);

   beamClone->get_W4(&val);
   TRY_TEST( IsEqual(val,0.0), true);

   beamClone->get_D1(&val);
   TRY_TEST( IsEqual(val,0.073), true);

   beamClone->get_D2(&val);
   TRY_TEST( IsEqual(val,0.067), true);

   beamClone->get_D3(&val);
   TRY_TEST( IsEqual(val,0.051), true);

   beamClone->get_D4(&val);
   TRY_TEST( IsEqual(val,0.152), true);

   beamClone->get_D5(&val);
   TRY_TEST( IsEqual(val,0.076), true);

   beamClone->get_D6(&val);
   TRY_TEST( IsEqual(val,0.0), true);

   beamClone->get_D7(&val);
   TRY_TEST( IsEqual(val,1.448), true);

   beamClone->get_T1(&val);
   TRY_TEST( IsEqual(val,0.152), true);

   beamClone->get_T2(&val);
   TRY_TEST( IsEqual(val,0.152), true);

   beamClone->get_C1(&val);
   TRY_TEST( IsEqual(val,0.0), true);
   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(0.0, 0.5);

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
   for ( int i = 0; i < 19; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 9 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 9 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y, 0.500), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y, 0.228), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.317), true );
   TRY_TEST( IsEqual(y, 0.152), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.317), true );
   TRY_TEST( IsEqual(y, 0.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.317), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.317), true );
   TRY_TEST( IsEqual(y,0.152), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.076), true );
   TRY_TEST( IsEqual(y,0.228), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.076), true );
   TRY_TEST( IsEqual(y, 0.500), true );

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

   TRY_TEST( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,nullptr), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 19; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 5 );

   coll->get__Enum(&Enum);
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y, 0.6), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y, 0.5), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.076), true );
   TRY_TEST( IsEqual(y, 0.5), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.076), true );
   TRY_TEST( IsEqual(y, 0.6), true );
}

void CTestPrecastBeam::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_PrecastBeam), S_OK);

   CComQIPtr<IPrecastBeam> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Use some real dimensions (WSDOT W74MG girder)
   beam->putref_HookPoint(hookPnt);
   beam->put_W1(0.419);
   beam->put_W2(0.051);
   beam->put_W3(0.241);
   beam->put_W4(0.0);
   beam->put_D1(0.073);
   beam->put_D2(0.067);
   beam->put_D3(0.051);
   beam->put_D4(0.152);
   beam->put_D5(0.076);
   beam->put_D6(0.0);
   beam->put_D7(1.448);
   beam->put_T1(0.152);
   beam->put_T2(0.152);

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
   TRY_TEST( cPoints,19);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>, 19> points;
   ULONG fetched;
   Enum->Next(19,&points[0],&fetched);
   TRY_TEST( fetched, 19 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,101.867), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.454), true );
   TRY_TEST( IsEqual(y, 101.867), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.454), true );
   TRY_TEST( IsEqual(y, 101.794), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.873), true );
   TRY_TEST( IsEqual(y, 101.727), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.924), true );
   TRY_TEST( IsEqual(y, 101.676), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.924), true );
   TRY_TEST( IsEqual(y, 100.228), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.924), true );
   TRY_TEST( IsEqual(y, 100.228), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.683), true );
   TRY_TEST( IsEqual(y, 100.152), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.683), true );
   TRY_TEST( IsEqual(y, 100.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.317), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.317), true );
   TRY_TEST( IsEqual(y,100.152), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.076), true );
   TRY_TEST( IsEqual(y,100.228), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.076), true );
   TRY_TEST( IsEqual(y,100.228), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.076), true );
   TRY_TEST( IsEqual(y,101.676), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.127), true );
   TRY_TEST( IsEqual(y,101.727), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.546), true );
   TRY_TEST( IsEqual(y,101.794), true );

   points[17]->get_X(&x);
   points[17]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.546), true );
   TRY_TEST( IsEqual(y,101.867), true );

   points[18]->get_X(&x);
   points[18]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,101.867), true );

   //
   // OffsetEx
   //

   // Move the triangle back to where it was
   hookPnt->Move(0,0);

   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(100);
   size->put_Dy(100);

   TRY_TEST(position->OffsetEx(nullptr), E_INVALIDARG );
   TRY_TEST(position->OffsetEx(size), S_OK);

   // Check the points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 19; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,19);

   coll->get__Enum(&Enum);
   Enum->Next(19,&points[0],&fetched);
   TRY_TEST( fetched, 19 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,101.867), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.454), true );
   TRY_TEST( IsEqual(y, 101.867), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.454), true );
   TRY_TEST( IsEqual(y, 101.794), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.873), true );
   TRY_TEST( IsEqual(y, 101.727), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.924), true );
   TRY_TEST( IsEqual(y, 101.676), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.924), true );
   TRY_TEST( IsEqual(y, 100.228), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.924), true );
   TRY_TEST( IsEqual(y, 100.228), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.683), true );
   TRY_TEST( IsEqual(y, 100.152), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,  99.683), true );
   TRY_TEST( IsEqual(y, 100.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.317), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.317), true );
   TRY_TEST( IsEqual(y,100.152), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.076), true );
   TRY_TEST( IsEqual(y,100.228), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.076), true );
   TRY_TEST( IsEqual(y,100.228), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.076), true );
   TRY_TEST( IsEqual(y,101.676), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.127), true );
   TRY_TEST( IsEqual(y,101.727), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.546), true );
   TRY_TEST( IsEqual(y,101.794), true );

   points[17]->get_X(&x);
   points[17]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.546), true );
   TRY_TEST( IsEqual(y,101.867), true );

   points[18]->get_X(&x);
   points[18]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y,101.867), true );

   //
   // LocatorPoint property
   //
   hookPnt->Move(0,0);
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

   // BottomLeft
   hookPnt->Move(0,0);
   to->Move(99.454,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 99.454), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomCenter
   hookPnt->Move(0,0);
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
   to->Move(100.546,100.000);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.546), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterLeft
   hookPnt->Move(0,0);
   to->Move(99.454,100.9335);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 99.454), true );
   TRY_TEST(IsEqual(y,100.9335), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterCenter
   hookPnt->Move(0,0);
   to->Move(100,100.9335);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.9335), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterRight
   hookPnt->Move(0,0);
   to->Move(100.546,100.9335);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.546), true );
   TRY_TEST(IsEqual(y,100.9335), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopLeft
   hookPnt->Move(0,0);
   to->Move(99.454,101.867);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 99.454), true );
   TRY_TEST(IsEqual(y,101.867), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopCenter
   hookPnt->Move(0,0);
   to->Move(100,101.867);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,101.867), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopRight
   hookPnt->Move(0,0);
   to->Move(100.546,101.867);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.546), true );
   TRY_TEST(IsEqual(y,101.867), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

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
   for (int i = 0; i < 19; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,19);

   coll->get__Enum(&Enum);
   Enum->Next(19,&points[0],&fetched);
   TRY_TEST( fetched, 19 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.000), true );
   TRY_TEST( IsEqual(y,-1.867), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.546), true );
   TRY_TEST( IsEqual(y,-1.867), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.546), true );
   TRY_TEST( IsEqual(y,-1.794), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.127), true );
   TRY_TEST( IsEqual(y,-1.727), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.076), true );
   TRY_TEST( IsEqual(y,-1.676), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.076), true );
   TRY_TEST( IsEqual(y,-0.228), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.076), true );
   TRY_TEST( IsEqual(y,-0.228), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.317), true );
   TRY_TEST( IsEqual(y,-0.152), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.317), true );
   TRY_TEST( IsEqual(y, 0.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.317), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.317), true );
   TRY_TEST( IsEqual(y,-0.152), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y,-0.228), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y,-0.228), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.076), true );
   TRY_TEST( IsEqual(y,-1.676), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.127), true );
   TRY_TEST( IsEqual(y,-1.727), true );

   points[16]->get_X(&x);
   points[16]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.546), true );
   TRY_TEST( IsEqual(y,-1.794), true );

   points[17]->get_X(&x);
   points[17]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.546), true );
   TRY_TEST( IsEqual(y,-1.867), true );

   points[18]->get_X(&x);
   points[18]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.0), true );
   TRY_TEST( IsEqual(y,-1.867), true );
}

void CTestPrecastBeam::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_PrecastBeam ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPrecastBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
