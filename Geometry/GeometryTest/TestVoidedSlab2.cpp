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

// TestVoidedSlab2.cpp: implementation of the CTestVoidedSlab2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestVoidedSlab2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestVoidedSlab2::CTestVoidedSlab2()
{

}

CTestVoidedSlab2::~CTestVoidedSlab2()
{

}

void CTestVoidedSlab2::Test()
{
   TestIVoidedSlab();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestVoidedSlab2::TestIVoidedSlab()
{
   CComPtr<IVoidedSlab2> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_VoidedSlab2), S_OK );

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CollectionIndexType lval;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_Height(nullptr), E_POINTER );
   TRY_TEST( beam->get_Height(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_Width(nullptr), E_POINTER );
   TRY_TEST( beam->get_Width(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_ExteriorVoidSpacing(nullptr), E_POINTER );
   TRY_TEST( beam->get_ExteriorVoidSpacing(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_InteriorVoidSpacing(nullptr), E_POINTER );
   TRY_TEST( beam->get_InteriorVoidSpacing(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_ExteriorVoidDiameter(nullptr), E_POINTER );
   TRY_TEST( beam->get_ExteriorVoidDiameter(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_InteriorVoidDiameter(nullptr), E_POINTER );
   TRY_TEST( beam->get_InteriorVoidDiameter(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_ExteriorVoidElevation(nullptr), E_POINTER );
   TRY_TEST( beam->get_ExteriorVoidElevation(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_InteriorVoidElevation(nullptr), E_POINTER );
   TRY_TEST( beam->get_InteriorVoidElevation(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_VoidCount(nullptr), E_POINTER );
   TRY_TEST( beam->get_VoidCount(&lval), S_OK );
   TRY_TEST( lval == 0, true );

   TRY_TEST( beam->get_HookPoint(nullptr), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_Height(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_Height(18), S_OK );
   beam->get_Height(&val);
   TRY_TEST( IsEqual(val,18.0), true );

   TRY_TEST( beam->put_Width(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_Width(48), S_OK );
   beam->get_Width(&val);
   TRY_TEST( IsEqual(val,48.0), true );

   TRY_TEST( beam->put_ExteriorVoidSpacing(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_ExteriorVoidSpacing(12.5), S_OK );
   beam->get_ExteriorVoidSpacing(&val);
   TRY_TEST( IsEqual(val,12.5), true );

   TRY_TEST( beam->put_InteriorVoidSpacing(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_InteriorVoidSpacing(12.5), S_OK );
   beam->get_InteriorVoidSpacing(&val);
   TRY_TEST( IsEqual(val,12.5), true );

   TRY_TEST( beam->put_ExteriorVoidDiameter(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_ExteriorVoidDiameter(0.833), S_OK );
   beam->get_ExteriorVoidDiameter(&val);
   TRY_TEST( IsEqual(val,0.833), true );

   TRY_TEST( beam->put_InteriorVoidDiameter(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_InteriorVoidDiameter(0.833), S_OK );
   beam->get_InteriorVoidDiameter(&val);
   TRY_TEST( IsEqual(val,0.833), true );

   TRY_TEST( beam->put_ExteriorVoidElevation(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_ExteriorVoidElevation(1.000), S_OK );
   beam->get_ExteriorVoidElevation(&val);
   TRY_TEST( IsEqual(val,1.000), true );

   TRY_TEST( beam->put_InteriorVoidElevation(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_InteriorVoidElevation(1.000), S_OK );
   beam->get_InteriorVoidElevation(&val);
   TRY_TEST( IsEqual(val,1.000), true );

//   TRY_TEST( beam->put_VoidCount(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_VoidCount(3), S_OK );
   beam->get_VoidCount(&lval);
   TRY_TEST( lval, 3 );

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

void CTestVoidedSlab2::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_VoidedSlab2 ), S_OK );
   CComQIPtr<IVoidedSlab2> beam(shape);
   
   beam->put_Height(36);
   beam->put_Width(260);
   beam->put_ExteriorVoidDiameter(20);
   beam->put_InteriorVoidDiameter(30);
   beam->put_ExteriorVoidElevation(12);
   beam->put_InteriorVoidElevation(18);
   beam->put_InteriorVoidSpacing(45);
   beam->put_ExteriorVoidSpacing(45);
   beam->put_VoidCount(5);

   //
   // Bounding Box
   //
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(nullptr), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-130.0), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, 130.0), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val, 36.0), true );

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
   TRY_TEST( IsEqual(area,6611.1064281089311), true );
   TRY_TEST( IsEqual(ixx, 851120.47291073855), true );
   TRY_TEST( IsEqual(iyy, 44640853.286266908), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,18.570239070464662), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,130.0),true);
   TRY_TEST(IsEqual(xright,130.0),true);
   TRY_TEST(IsEqual(ytop,17.429760929535338),true);
   TRY_TEST(IsEqual(ybottom,18.570239070464662),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(nullptr), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,592.), true );

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
   TRY_TEST( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,nullptr), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,50.000), true );

   // shape on left
   p1->Move(0,-50);
   p2->Move(100,-50);
   line->ThroughPoints(p1,p2);
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-50.0), true );

   // 
   // PolyPoints
   //
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(nullptr), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );

   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 10 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[10];
   ULONG fetched;
   Enum->Next(10,&points[0],&fetched);
   TRY_TEST( fetched, 10 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.0), true );
   TRY_TEST( IsEqual(y, 36.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.0), true );
   TRY_TEST( IsEqual(y, 36.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.0), true );
   TRY_TEST( IsEqual(y, 36.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.0), true );
   TRY_TEST( IsEqual(y,  36.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.0), true );
   TRY_TEST( IsEqual(y,  36.0), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.0), true );
   TRY_TEST( IsEqual(y,  36.0), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.0), true );
   TRY_TEST( IsEqual(y,   0.0), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.0), true );
   TRY_TEST( IsEqual(y,   0.0), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(nullptr), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IVoidedSlab2> beamClone(clone);
   TRY_TEST( beamClone != 0, true );

   beamClone->get_Height(&val);
   TRY_TEST( IsEqual(val,36.0), true);

   beamClone->get_Width(&val);
   TRY_TEST( IsEqual(val,260.0), true);

   beamClone->get_ExteriorVoidDiameter(&val);
   TRY_TEST( IsEqual(val,20.0), true);

   beamClone->get_InteriorVoidDiameter(&val);
   TRY_TEST( IsEqual(val,30.0), true);

   beamClone->get_ExteriorVoidSpacing(&val);
   TRY_TEST( IsEqual(val,45.0), true);

   beamClone->get_InteriorVoidSpacing(&val);
   TRY_TEST( IsEqual(val,45.0), true);

   beamClone->get_ExteriorVoidElevation(&val);
   TRY_TEST( IsEqual(val,12.0), true);

   beamClone->get_InteriorVoidElevation(&val);
   TRY_TEST( IsEqual(val,18.0), true);

   CollectionIndexType lval;
   beamClone->get_VoidCount(&lval);
   TRY_TEST( lval, 5);

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
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 5 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.00), true );
   TRY_TEST( IsEqual(y,  0.00), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.00), true );
   TRY_TEST( IsEqual(y,  0.50), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.00), true );
   TRY_TEST( IsEqual(y,   0.50), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.00), true );
   TRY_TEST( IsEqual(y,   0.00), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.00), true );
   TRY_TEST( IsEqual(y,  0.00), true );

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
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.00), true );
   TRY_TEST( IsEqual(y,  0.50), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,130.00), true );
   TRY_TEST( IsEqual(y, 36.00), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.00), true );
   TRY_TEST( IsEqual(y,  36.00), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-130.00), true );
   TRY_TEST( IsEqual(y,   0.50), true );

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
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 5 );

   ATLTRACE("Trace of Points for VoidedSlab2 - count = %d \n", cPoints);
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
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,100.0), true );
   TRY_TEST( IsEqual(y, 16.5), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-100.0), true );
   TRY_TEST( IsEqual(y,  16.5), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-100.0), true );
   TRY_TEST( IsEqual(y,   1.5), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 100.0), true );
   TRY_TEST( IsEqual(y,   1.5), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x, 100.0), true );
   TRY_TEST( IsEqual(y,  16.5), true );
}

void CTestVoidedSlab2::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_VoidedSlab), S_OK);

   CComQIPtr<IVoidedSlab> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Use some real dimensions (WSDOT 1'-6" Voided Slab)
   beam->putref_HookPoint(hookPnt);
   beam->put_Height(18);
   beam->put_Width(48);
   beam->put_VoidSpacing(12.5);
   beam->put_VoidDiameter(0.833);
   beam->put_VoidCount(3);

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
   TRY_TEST( cPoints,5);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[5];
   ULONG fetched;
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 76.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 124.0), true );
   TRY_TEST( IsEqual(y, 100.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 124.0), true );
   TRY_TEST( IsEqual(y, 118.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 76.0), true );
   TRY_TEST( IsEqual(y,118.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x, 76.0), true );
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
   for ( int i = 0; i < 5; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,5);

   coll->get__Enum(&Enum);
   Enum->Next(6,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y, 18.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y, 18.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

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
   TRY_TEST(IsEqual(x,124.0), true );
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
   TRY_TEST(IsEqual(x, 76.0), true );
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
   TRY_TEST(IsEqual(x,124.0), true );
   TRY_TEST(IsEqual(y, 91.0), true );

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
   TRY_TEST(IsEqual(y, 91.0), true );

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
   TRY_TEST(IsEqual(x, 76.0), true );
   TRY_TEST(IsEqual(y, 91.0), true );

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
   TRY_TEST(IsEqual(x,124.0), true );
   TRY_TEST(IsEqual(y, 82.0), true );

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
   TRY_TEST(IsEqual(y, 82.0), true );

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
   TRY_TEST(IsEqual(x, 76.0), true );
   TRY_TEST(IsEqual(y, 82.0), true );

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
   c->put_X(-24);
   c->put_Y(0);

   TRY_TEST( position->RotateEx(nullptr,M_PI/2), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI/2), S_OK );

   // Check the points
   coll.Release();
   Enum.Release();
   for (int i = 0; i < 5; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,5);

   coll->get__Enum(&Enum);
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y, 48.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-42.0), true );
   TRY_TEST( IsEqual(y, 48.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-42.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );
}

void CTestVoidedSlab2::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_VoidedSlab ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IVoidedSlab ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
