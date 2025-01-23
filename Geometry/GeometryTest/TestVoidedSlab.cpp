///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TestVoidedSlab.cpp: implementation of the CTestVoidedSlab class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestVoidedSlab.h"
#include <array>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestVoidedSlab::CTestVoidedSlab()
{

}

CTestVoidedSlab::~CTestVoidedSlab()
{

}

void CTestVoidedSlab::Test()
{
   TestIVoidedSlab();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestVoidedSlab::TestIVoidedSlab()
{
   CComPtr<IVoidedSlab> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_VoidedSlab), S_OK );

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   IndexType lval;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_Height(nullptr), E_POINTER );
   TRY_TEST( beam->get_Height(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_Width(nullptr), E_POINTER );
   TRY_TEST( beam->get_Width(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_VoidSpacing(nullptr), E_POINTER );
   TRY_TEST( beam->get_VoidSpacing(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_VoidDiameter(nullptr), E_POINTER );
   TRY_TEST( beam->get_VoidDiameter(&val), S_OK );
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

   TRY_TEST( beam->put_VoidSpacing(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_VoidSpacing(12.5), S_OK );
   beam->get_VoidSpacing(&val);
   TRY_TEST( IsEqual(val,12.5), true );

   TRY_TEST( beam->put_VoidDiameter(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_VoidDiameter(0.833), S_OK );
   beam->get_VoidDiameter(&val);
   TRY_TEST( IsEqual(val,0.833), true );

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

void CTestVoidedSlab::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_VoidedSlab ), S_OK );
   CComQIPtr<IVoidedSlab> beam(shape);
   
   // Use some real dimensions (WSDOT 1'-6" Voided Slab)
   beam->put_Height(18);
   beam->put_Width(48);
   beam->put_VoidSpacing(12.5);
   beam->put_VoidDiameter(0.833);
   beam->put_VoidCount(3);

   //
   // Bounding Box
   //
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(nullptr), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-24.0), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, 24.0), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val, 18.0), true );

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
   TRY_TEST( IsEqual(area,862.365062561), true );
   TRY_TEST( IsEqual(ixx, 23327.929095931002), true );
   TRY_TEST( IsEqual(iyy, 165717.62311274296), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,9.0), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,24.0),true);
   TRY_TEST(IsEqual(xright,24.0),true);
   TRY_TEST(IsEqual(ytop,9.0),true);
   TRY_TEST(IsEqual(ybottom,9.0),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(nullptr), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,132.), true );

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

   IndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>, 5> points;
   ULONG fetched;
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   int i = 0;
   Float64 x,y;
   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y, 18.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y, 18.0), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(nullptr), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IVoidedSlab> beamClone(clone);
   TRY_TEST( beamClone != nullptr, true );

   beamClone->get_Height(&val);
   TRY_TEST( IsEqual(val,18.0), true);

   beamClone->get_Width(&val);
   TRY_TEST( IsEqual(val,48.0), true);

   beamClone->get_VoidDiameter(&val);
   TRY_TEST( IsEqual(val,0.833), true);

   beamClone->get_VoidSpacing(&val);
   TRY_TEST( IsEqual(val,12.5), true);

   IndexType lval;
   beamClone->get_VoidCount(&lval);
   TRY_TEST( lval, 3);

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
   TRY_TEST( clip != nullptr, true );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 5 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   i = 0;
   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.00), true );
   TRY_TEST( IsEqual(y,  0.00), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.00), true );
   TRY_TEST( IsEqual(y,  0.00), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.00), true );
   TRY_TEST( IsEqual(y,  0.50), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.00), true );
   TRY_TEST( IsEqual(y,  0.50), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.00), true );
   TRY_TEST( IsEqual(y,  0.00), true );

   // clip in other direction
   p1->Move( 50, 0.50);
   p2->Move(-50, 0.50);

   clipLine->ThroughPoints(p1,p2);

   clip.Release();
   TRY_TEST(shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,nullptr), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != nullptr, true );
   
   coll.Release();
   Enum.Release();
   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   i = 0;
   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.00), true );
   TRY_TEST( IsEqual(y,  0.50), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.00), true );
   TRY_TEST( IsEqual(y, 18.00), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.00), true );
   TRY_TEST( IsEqual(y, 18.00), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.00), true );
   TRY_TEST( IsEqual(y,  0.50), true );

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
   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   ATLTRACE("Trace of Points for VoidedSlab - count = %d \n", cPoints);
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
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   i = 0;
   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y,  1.5), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y, 16.5), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y, 16.5), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y,  1.5), true );
}

void CTestVoidedSlab::TestIXYPosition()
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
   IndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,4);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   std::array<CComPtr<IPoint2d>, 5> points;
   ULONG fetched;
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   Float64 x,y;
   int i = 0;
   points[i++]->Location(&x, &y);
   TRY_TEST(IsEqual(x, 124.0), true);
   TRY_TEST(IsEqual(y, 100.0), true);

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 76.0), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 76.0), true );
   TRY_TEST( IsEqual(y,118.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST(IsEqual(x, 124.0), true);
   TRY_TEST(IsEqual(y, 118.0), true);

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
   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });

   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,4);

   coll->get__Enum(&Enum);
   Enum->Next(6,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   i = 0;
   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x,-24.0), true );
   TRY_TEST( IsEqual(y, 18.0), true );

   points[i++]->Location(&x, &y);
   TRY_TEST( IsEqual(x, 24.0), true );
   TRY_TEST( IsEqual(y, 18.0), true );

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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   hookPnt->Move(0, 0);
   to->Move(100, 100);
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
   std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });

   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,4);

   coll->get__Enum(&Enum);
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   i = 0;
   points[i++]->Location(&x, &y);
   TRY_TEST(IsEqual(x,-24.0), true);
   TRY_TEST(IsEqual(y, 48.0), true);

   points[i++]->Location(&x, &y);
   TRY_TEST(IsEqual(x,-24.0), true);
   TRY_TEST(IsEqual(y, 0.0), true);

   points[i++]->Location(&x, &y);
   TRY_TEST(IsEqual(x,-42.0), true);
   TRY_TEST(IsEqual(y, 0.0), true);

   points[i++]->Location(&x, &y);
   TRY_TEST(IsEqual(x,-42.0), true);
   TRY_TEST(IsEqual(y, 48.0), true);
}

void CTestVoidedSlab::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_VoidedSlab ), S_OK );
   TRY_TEST( eInfo != nullptr, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IVoidedSlab ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
