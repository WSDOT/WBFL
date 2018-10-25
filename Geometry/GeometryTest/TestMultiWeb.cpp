///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// TestMultiWeb.cpp: implementation of the CTestMultiWeb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMultiWeb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestMultiWeb::CTestMultiWeb()
{

}

CTestMultiWeb::~CTestMultiWeb()
{

}

void CTestMultiWeb::Test()
{
   TestIMultiWeb();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestMultiWeb::TestIMultiWeb()
{
   CComPtr<IMultiWeb> beam;
   //TRY_TEST( beam.CoCreateInstance(CLSID_UBeam), S_OK );
   HRESULT hr =  beam.CoCreateInstance(CLSID_MultiWeb);

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   WebIndexType lval;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_D1(NULL), E_POINTER );
   TRY_TEST( beam->get_D1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D2(NULL), E_POINTER );
   TRY_TEST( beam->get_D2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_T1(NULL), E_POINTER );
   TRY_TEST( beam->get_T1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_T2(NULL), E_POINTER );
   TRY_TEST( beam->get_T2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W1(NULL), E_POINTER );
   TRY_TEST( beam->get_W1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W2(NULL), E_POINTER );
   TRY_TEST( beam->get_W2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_WebCount(NULL), E_POINTER );
   TRY_TEST( beam->get_WebCount(&lval), S_OK );
   TRY_TEST( lval == 0, true );

   TRY_TEST( beam->get_HookPoint(NULL), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_D1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D1(6), S_OK );
   beam->get_D1(&val);
   TRY_TEST( IsEqual(val,6.0), true );

   TRY_TEST( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D2(21), S_OK );
   beam->get_D2(&val);
   TRY_TEST( IsEqual(val,21.0), true );

   TRY_TEST( beam->put_T1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_T1(7.25), S_OK );
   beam->get_T1(&val);
   TRY_TEST( IsEqual(val,7.25), true );

   TRY_TEST( beam->put_T2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_T2(5.25), S_OK );
   beam->get_T2(&val);
   TRY_TEST( IsEqual(val,5.25), true );

   TRY_TEST( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W1(13.125), S_OK );
   beam->get_W1(&val);
   TRY_TEST( IsEqual(val,13.125), true );

   TRY_TEST( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W2(12), S_OK );
   beam->get_W2(&val);
   TRY_TEST( IsEqual(val,12.0), true );

//   TRY_TEST( beam->put_WebCount(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_WebCount(3), S_OK );
   beam->get_WebCount(&lval);
   TRY_TEST( lval,3 );

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
   TRY_TEST(beam->get_Height(NULL), E_POINTER );
   TRY_TEST(beam->get_Height(&val), S_OK );
   TRY_TEST(IsEqual(val,27.0), true );

   TRY_TEST(beam->get_TopFlangeWidth(NULL),E_POINTER);
   TRY_TEST(beam->get_TopFlangeWidth(&val),S_OK);
   TRY_TEST(IsEqual(val,72.0),true);

   TRY_TEST(beam->get_AvgWebWidth(NULL),E_POINTER);
   TRY_TEST(beam->get_AvgWebWidth(&val),S_OK);
   TRY_TEST(IsEqual(val,18.75),true);

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

void CTestMultiWeb::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_MultiWeb ), S_OK );
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
   TRY_TEST( shape->get_BoundingBox(NULL), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-36.), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, 36.), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val, 0.00), true );

   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,-27.), true );

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
   TRY_TEST( IsEqual(area,825.75), true );
   TRY_TEST( IsEqual(ixx, 50135.30160), true );
   TRY_TEST( IsEqual(iyy, 285211.20703), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,-9.17029972752044), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft, 36.),true);
   TRY_TEST(IsEqual(xright,36.),true);
   TRY_TEST(IsEqual(ytop,9.17029972752044),true);
   TRY_TEST(IsEqual(ybottom,17.8297002724796),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(NULL), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,276.142776249772), true );

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
   TRY_TEST( shape->FurthestDistance(NULL,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,NULL), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,47.000), true );

   // shape on left of line
   p1->Move(100,20);
   p2->Move(-100,20);
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
   TRY_TEST( cPoints, 16 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[16];
   ULONG fetched;
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.875), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-16.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-15.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, -3.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, -2.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,  2.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,  3.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,15.625), true );
   TRY_TEST( IsEqual(y,-6.000), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 16.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x, 21.875), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.875), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(NULL), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IMultiWeb> beamClone(clone);
   TRY_TEST( beamClone != 0, true );

   beamClone->get_W1(&val);
   TRY_TEST( IsEqual(val,13.125), true);

   beamClone->get_W2(&val);
   TRY_TEST( IsEqual(val,12.00), true);

   beamClone->get_D1(&val);
   TRY_TEST( IsEqual(val,6.00), true);

   beamClone->get_D2(&val);
   TRY_TEST( IsEqual(val,21.00), true);

   beamClone->get_T1(&val);
   TRY_TEST( IsEqual(val, 7.25), true);

   beamClone->get_T2(&val);
   TRY_TEST( IsEqual(val, 5.25), true);

   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(0.0, -5.0);

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
   p1->Move(-100,-5.0);
   p2->Move( 100,-5.0);

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
   TRY_TEST( cPoints, 16 );

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -5.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.875), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-16.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-15.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, -3.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, -2.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,  2.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,  3.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,15.625), true );
   TRY_TEST( IsEqual(y,-6.000), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 16.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x, 21.875), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.875), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y, -5.000), true );

   // clip in other direction
   p1->Move( 100,-5.0);
   p2->Move(-100,-5.0);

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
   TRY_TEST( cPoints, 5);

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -5.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y, -5.000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   //
   // ClipIn
   //
   clip.Release();

   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );
   clipRect->put_Left(-100);
   clipRect->put_Right(100);
   clipRect->put_Top(-4);
   clipRect->put_Bottom(-5);

   TRY_TEST( shape->ClipIn(NULL,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,NULL), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( CollectionIndexType i = 0; i < cPoints; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 5 );

   ATLTRACE("Trace of Points for MultiWeb - count = %d \n", cPoints);
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
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -4.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -5.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y, -5.000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y, -4.000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -4.000), true );
}

void CTestMultiWeb::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_MultiWeb ), S_OK);

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

   TRY_TEST( position->MoveEx(NULL,to), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,NULL), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to), S_OK );

   // Check the points
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,16);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[16];
   ULONG fetched;
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000+100), true );
   TRY_TEST( IsEqual(y,  0.000+100), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000+100), true );
   TRY_TEST( IsEqual(y, -6.000+100), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.875+100), true );
   TRY_TEST( IsEqual(y, -6.000+100), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875+100), true );
   TRY_TEST( IsEqual(y,-27.000+100), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-16.625+100), true );
   TRY_TEST( IsEqual(y,-27.000+100), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-15.625+100), true );
   TRY_TEST( IsEqual(y, -6.000+100), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, -3.625+100), true );
   TRY_TEST( IsEqual(y, -6.000+100), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, -2.625+100), true );
   TRY_TEST( IsEqual(y,-27.000+100), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,  2.625+100), true );
   TRY_TEST( IsEqual(y,-27.000+100), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,  3.625+100), true );
   TRY_TEST( IsEqual(y, -6.000+100), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,15.625+100), true );
   TRY_TEST( IsEqual(y,-6.000+100), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 16.625+100), true );
   TRY_TEST( IsEqual(y,-27.000+100), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x, 21.875+100), true );
   TRY_TEST( IsEqual(y,-27.000+100), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.875+100), true );
   TRY_TEST( IsEqual(y, -6.000+100), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000+100), true );
   TRY_TEST( IsEqual(y, -6.000+100), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000+100), true );
   TRY_TEST( IsEqual(y,  0.000+100), true );

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
   TRY_TEST( cPoints,16);

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.875), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-16.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-15.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, -3.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, -2.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,  2.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,  3.625), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,15.625), true );
   TRY_TEST( IsEqual(y,-6.000), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x, 16.625), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x, 21.875), true );
   TRY_TEST( IsEqual(y,-27.000), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.875), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y, -6.000), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   //
   // LocatorPoint property
   //
   hookPnt->Move(0,0);
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
   TRY_TEST(IsEqual(x,136.000), true );
   TRY_TEST(IsEqual(y,127.000), true );

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
   TRY_TEST(IsEqual(y,127.0), true );

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
   TRY_TEST(IsEqual(x,100.0-36), true );
   TRY_TEST(IsEqual(y,127.0), true );

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
   TRY_TEST(IsEqual(x,136.0), true );
   TRY_TEST(IsEqual(y,113.5), true );

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
   TRY_TEST(IsEqual(y,113.5), true );

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
   TRY_TEST(IsEqual(x,64.0), true );
   TRY_TEST(IsEqual(y,113.5), true );

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
   TRY_TEST(IsEqual(x,136.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

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
   TRY_TEST(IsEqual(y,100.0), true );

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
   TRY_TEST(IsEqual(x, 64.0), true );
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
   TRY_TEST(IsEqual(y,127.0), true );

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
   TRY_TEST( cPoints,16);

   coll->get__Enum(&Enum);
   Enum->Next((ULONG)cPoints,&points[0],&fetched);
   TRY_TEST( fetched, cPoints );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 36.000), true );
   TRY_TEST( IsEqual(y,  6.000), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 22.875), true );
   TRY_TEST( IsEqual(y,  6.000), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 21.875), true );
   TRY_TEST( IsEqual(y, 27.000), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x, 16.625), true );
   TRY_TEST( IsEqual(y, 27.000), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x, 15.625), true );
   TRY_TEST( IsEqual(y,  6.000), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,  3.625), true );
   TRY_TEST( IsEqual(y,  6.000), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,  2.625), true );
   TRY_TEST( IsEqual(y, 27.000), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x, -2.625), true );
   TRY_TEST( IsEqual(y, 27.000), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x, -3.625), true );
   TRY_TEST( IsEqual(y,  6.000), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,-15.625), true );
   TRY_TEST( IsEqual(y, 6.000), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,-16.625), true );
   TRY_TEST( IsEqual(y, 27.000), true );

   points[12]->get_X(&x);
   points[12]->get_Y(&y);
   TRY_TEST( IsEqual(x,-21.875), true );
   TRY_TEST( IsEqual(y, 27.000), true );

   points[13]->get_X(&x);
   points[13]->get_Y(&y);
   TRY_TEST( IsEqual(x,-22.875), true );
   TRY_TEST( IsEqual(y,  6.000), true );

   points[14]->get_X(&x);
   points[14]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y,  6.000), true );

   points[15]->get_X(&x);
   points[15]->get_Y(&y);
   TRY_TEST( IsEqual(x,-36.000), true );
   TRY_TEST( IsEqual(y,  0.000), true );

}

void CTestMultiWeb::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_MultiWeb ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IMultiWeb ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
