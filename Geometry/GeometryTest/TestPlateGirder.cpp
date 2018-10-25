///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TestPlateGirder.cpp: implementation of the CTestPlateGirder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPlateGirder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPlateGirder::CTestPlateGirder()
{

}

CTestPlateGirder::~CTestPlateGirder()
{

}

void CTestPlateGirder::Test()
{
   TestIPlateGirder();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestPlateGirder::TestIPlateGirder()
{
   CComPtr<IPlateGirder> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_PlateGirder), S_OK );

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_BottomFlangeThick(NULL), E_POINTER );
   TRY_TEST( beam->get_BottomFlangeThick(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_BottomFlangeWidth(NULL), E_POINTER );
   TRY_TEST( beam->get_BottomFlangeWidth(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_TopFlangeThick(NULL), E_POINTER );
   TRY_TEST( beam->get_TopFlangeThick(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_TopFlangeWidth(NULL), E_POINTER );
   TRY_TEST( beam->get_TopFlangeWidth(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_WebHeight(NULL), E_POINTER );
   TRY_TEST( beam->get_WebHeight(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_WebThick(NULL), E_POINTER );
   TRY_TEST( beam->get_WebThick(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_HookPoint(NULL), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_BottomFlangeThick(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_BottomFlangeThick(14), S_OK );
   beam->get_BottomFlangeThick(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_BottomFlangeWidth(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_BottomFlangeWidth(14), S_OK );
   beam->get_BottomFlangeWidth(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_TopFlangeThick(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_TopFlangeThick(14), S_OK );
   beam->get_TopFlangeThick(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_TopFlangeWidth(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_TopFlangeWidth(14), S_OK );
   beam->get_TopFlangeWidth(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_WebThick(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_WebThick(14), S_OK );
   beam->get_WebThick(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   TRY_TEST( beam->put_WebThick(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_WebThick(14), S_OK );
   beam->get_WebThick(&val);
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

   // Use some real dimensions
   beam->put_TopFlangeWidth(22);
   beam->put_TopFlangeThick(1.25);
   beam->put_BottomFlangeWidth(22);
   beam->put_BottomFlangeThick(2.25);
   beam->put_WebThick(0.438);
   beam->put_WebHeight(122);

   TRY_TEST(beam->get_Height(NULL), E_POINTER );
   TRY_TEST(beam->get_Height(&val), S_OK );
   TRY_TEST(IsEqual(val,125.5), true );

   TRY_TEST(beam->get_QTopFlange(NULL), E_POINTER );
   TRY_TEST(beam->get_QTopFlange(&val), S_OK );
   TRY_TEST(IsEqual(val,1985.7,0.1),true);

   TRY_TEST(beam->get_QBottomFlange(NULL), E_POINTER );
   TRY_TEST(beam->get_QBottomFlange(&val), S_OK );
   TRY_TEST(IsEqual(val,2551.3,0.1),true);

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

void CTestPlateGirder::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_PlateGirder), S_OK );
   CComQIPtr<IPlateGirder> beam(shape);
   
   // Use some real dimensions
   beam->put_TopFlangeWidth(22);
   beam->put_TopFlangeThick(1.25);
   beam->put_BottomFlangeWidth(22);
   beam->put_BottomFlangeThick(2.25);
   beam->put_WebThick(0.438);
   beam->put_WebHeight(122);

   //
   // Bounding Box
   //
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(NULL), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-11.0), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, 11.0), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val,125.5), true );

   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,0.00), true );

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
   TRY_TEST( IsEqual(area,130.436), true );
   TRY_TEST( IsEqual(ixx,347173.21061789), true );
   TRY_TEST( IsEqual(iyy,3106.5209479986), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,52.67,0.01), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,11.0),true);
   TRY_TEST(IsEqual(xright,11.0),true);
   TRY_TEST(IsEqual(ytop,125.5-cgy),true);
   TRY_TEST(IsEqual(ybottom,cgy),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(NULL), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,338.124), true );

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
   p1->Move(0,200);
   p2->Move(100,200);
   line->ThroughPoints(p1,p2);
   Float64 dist;
   TRY_TEST( shape->FurthestDistance(NULL,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,NULL), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,200.000), true );

   // shape on left
   p1->Move(0,-200);
   p2->Move(100,-200);
   line->ThroughPoints(p1,p2);
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-200.0), true );

   // 
   // PolyPoints
   //
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );

   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 12 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[12];
   ULONG fetched;
   Enum->Next(12,&points[0],&fetched);
   TRY_TEST( fetched, 12 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-11.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-11.0), true );
   TRY_TEST( IsEqual(y, 2.25), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.219), true );
   TRY_TEST( IsEqual(y, 2.25), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.219), true );
   TRY_TEST( IsEqual(y, 124.25), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-11.0), true );
   TRY_TEST( IsEqual(y, 124.25), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,-11.0), true );
   TRY_TEST( IsEqual(y, 125.5), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,11.0), true );
   TRY_TEST( IsEqual(y,125.5), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,11.0), true );
   TRY_TEST( IsEqual(y,124.25), true );

   points[8]->get_X(&x);
   points[8]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.219), true );
   TRY_TEST( IsEqual(y,124.25), true );

   points[9]->get_X(&x);
   points[9]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.219), true );
   TRY_TEST( IsEqual(y,2.25), true );

   points[10]->get_X(&x);
   points[10]->get_Y(&y);
   TRY_TEST( IsEqual(x,11.0), true );
   TRY_TEST( IsEqual(y,2.25), true );

   points[11]->get_X(&x);
   points[11]->get_Y(&y);
   TRY_TEST( IsEqual(x,11.0), true );
   TRY_TEST( IsEqual(y,0.0), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(NULL), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IPlateGirder> beamClone(clone);
   TRY_TEST( beamClone != 0, true );

   beamClone->get_BottomFlangeThick(&val);
   TRY_TEST( IsEqual(val,2.25), true);

   beamClone->get_BottomFlangeWidth(&val);
   TRY_TEST( IsEqual(val,22.0), true);

   beamClone->get_TopFlangeThick(&val);
   TRY_TEST( IsEqual(val,1.25), true);

   beamClone->get_TopFlangeWidth(&val);
   TRY_TEST( IsEqual(val,22.0), true);

   beamClone->get_WebHeight(&val);
   TRY_TEST( IsEqual(val,122.0), true);

   beamClone->get_WebThick(&val);
   TRY_TEST( IsEqual(val,0.438), true);

   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(0.0, 50.);

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
   p1->Move( 50,50);
   p2->Move(-50,50);

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
   for ( int i = 0; i < 12; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 8 );

   coll->get__Enum(&Enum);
   Enum->Next(8,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.219), true );
   TRY_TEST( IsEqual(y, 50.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.219), true );
   TRY_TEST( IsEqual(y, 124.25), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-11.0), true );
   TRY_TEST( IsEqual(y, 124.25), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-11.0), true );
   TRY_TEST( IsEqual(y,125.5), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,11.0), true );
   TRY_TEST( IsEqual(y,125.5), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x,11.0), true );
   TRY_TEST( IsEqual(y,124.25), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.219), true );
   TRY_TEST( IsEqual(y,124.25),true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x,0.219), true );
   TRY_TEST( IsEqual(y,50.0), true );

   //
   // ClipIn
   //
   clip.Release();

   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );
   clipRect->put_Left(-100);
   clipRect->put_Right(100);
   clipRect->put_Top(55);
   clipRect->put_Bottom(50);

   TRY_TEST( shape->ClipIn(NULL,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,NULL), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 12; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   coll->get__Enum(&Enum);
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.219), true );
   TRY_TEST( IsEqual(y, 50.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-0.219), true );
   TRY_TEST( IsEqual(y, 55.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.219), true );
   TRY_TEST( IsEqual(y, 55.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 0.219), true );
   TRY_TEST( IsEqual(y, 50.0), true );
}

void CTestPlateGirder::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_PlateGirder), S_OK);

   CComQIPtr<IPlateGirder> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Use some real dimensions
   beam->putref_HookPoint(hookPnt);
   beam->put_TopFlangeWidth(22);
   beam->put_TopFlangeThick(1.25);
   beam->put_BottomFlangeWidth(22);
   beam->put_BottomFlangeThick(2.25);
   beam->put_WebThick(0.438);
   beam->put_WebHeight(122);

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

   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);
   CComPtr<IPoint2d> cg;
   props->get_Centroid(&cg);

   Float64 x,y;
   cg->get_X(&x);
   cg->get_Y(&y);
   TRY_TEST(IsEqual(x,100.),true);
   TRY_TEST(IsEqual(y,152.67,0.01),true);

   //
   // OffsetEx
   //

   // Move the shape back to where it was
   hookPnt->Move(0,0);

   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(100);
   size->put_Dy(100);

   TRY_TEST(position->OffsetEx(NULL), E_INVALIDARG );
   TRY_TEST(position->OffsetEx(size), S_OK);

   props.Release();
   shape->get_ShapeProperties(&props);

   cg.Release();
   props->get_Centroid(&cg);

   cg->get_X(&x);
   cg->get_Y(&y);
   TRY_TEST(IsEqual(x,100.),true);
   TRY_TEST(IsEqual(y,152.67,0.01),true);

   //
   // LocatorPoint property
   //
   hookPnt->Move(0,0);
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,NULL), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,NULL), E_POINTER );

   // BottomLeft
   hookPnt->Move(0,0);
   to->Move(89,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 89.), true );
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
   to->Move(111,100.000);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,111.), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterLeft
   hookPnt->Move(0,0);
   to->Move(89,162.75);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 89.), true );
   TRY_TEST(IsEqual(y,162.75), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterCenter
   hookPnt->Move(0,0);
   to->Move(100,162.75);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,162.75), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // CenterRight
   hookPnt->Move(0,0);
   to->Move(111,162.75);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,111.), true );
   TRY_TEST(IsEqual(y,162.75), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopLeft
   hookPnt->Move(0,0);
   to->Move(89,225.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x, 89.), true );
   TRY_TEST(IsEqual(y,225.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopCenter
   hookPnt->Move(0,0);
   to->Move(100,225.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,225.5), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // TopRight
   hookPnt->Move(0,0);
   to->Move(111,225.5);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,111.), true );
   TRY_TEST(IsEqual(y,225.5), true );
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

   TRY_TEST( position->RotateEx(NULL,M_PI), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI), S_OK );

   props.Release();
   shape->get_ShapeProperties(&props);
   cg.Release();
   props->get_Centroid(&cg);
   cg->get_X(&x);
   cg->get_Y(&y);
   TRY_TEST(IsEqual(x,0.00),true);
   TRY_TEST(IsEqual(y,-52.67,0.01),true);
}

void CTestPlateGirder::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_PlateGirder ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPlateGirder ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
