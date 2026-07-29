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

// TestPlateGirder.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestPlateGirder.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestPlateGirder)
{
public:
   TEST_METHOD(TestIPlateGirder)
   {
         CComPtr<IPlateGirder> beam;
         ASSERT_EQ( beam.CoCreateInstance(CLSID_PlateGirder), S_OK );

         // Verify initialization. All dimensions should be zero.
         // Hook point (bottom center) should be zero.
         Float64 val;
         CComPtr<IPoint2d> pntVal;

         ASSERT_EQ( beam->get_BottomFlangeThickness(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_BottomFlangeThickness(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_BottomFlangeWidth(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_BottomFlangeWidth(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_TopFlangeThickness(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_TopFlangeThickness(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_TopFlangeWidth(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_TopFlangeWidth(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_WebHeight(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_WebHeight(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_WebWidth(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_WebWidth(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         ASSERT_EQ( beam->get_HookPoint(nullptr), E_POINTER );
         ASSERT_EQ( beam->get_HookPoint(&pntVal), S_OK );
         pntVal->get_X(&val);
         ASSERT_EQ( IsZero(val), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsZero(val), true );

         // Test properties
         ASSERT_EQ( beam->put_BottomFlangeThickness(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_BottomFlangeThickness(14), S_OK );
         beam->get_BottomFlangeThickness(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_BottomFlangeWidth(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_BottomFlangeWidth(14), S_OK );
         beam->get_BottomFlangeWidth(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_TopFlangeThickness(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_TopFlangeThickness(14), S_OK );
         beam->get_TopFlangeThickness(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_TopFlangeWidth(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_TopFlangeWidth(14), S_OK );
         beam->get_TopFlangeWidth(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_WebWidth(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_WebWidth(14), S_OK );
         beam->get_WebWidth(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         ASSERT_EQ( beam->put_WebWidth(-1), GEOMETRY_E_DIMENSION );
         ASSERT_EQ( beam->put_WebWidth(14), S_OK );
         beam->get_WebWidth(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         pntVal->Move(14,14);
         ASSERT_EQ( beam->putref_HookPoint(nullptr), E_INVALIDARG );
         ASSERT_EQ( beam->putref_HookPoint(pntVal), S_OK );
         pntVal.Release();
         beam->get_HookPoint(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,14.0), true );

         // Use some real dimensions
         beam->put_TopFlangeWidth(22);
         beam->put_TopFlangeThickness(1.25);
         beam->put_BottomFlangeWidth(22);
         beam->put_BottomFlangeThickness(2.25);
         beam->put_WebWidth(0.438);
         beam->put_WebHeight(122);

         ASSERT_EQ(beam->get_Height(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_Height(&val), S_OK );
         ASSERT_EQ(IsEqual(val,125.5), true );

         ASSERT_EQ(beam->get_QTopFlange(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_QTopFlange(&val), S_OK );
         ASSERT_EQ(IsEqual(val,1985.7,0.1),true);

         ASSERT_EQ(beam->get_QBottomFlange(nullptr), E_POINTER );
         ASSERT_EQ(beam->get_QBottomFlange(&val), S_OK );
         ASSERT_EQ(IsEqual(val,2551.3,0.1),true);

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
         ASSERT_EQ( shape.CoCreateInstance( CLSID_PlateGirder), S_OK );
         CComQIPtr<IPlateGirder> beam(shape);

         // Use some real dimensions
         beam->put_TopFlangeWidth(22);
         beam->put_TopFlangeThickness(1.25);
         beam->put_BottomFlangeWidth(22);
         beam->put_BottomFlangeThickness(2.25);
         beam->put_WebWidth(0.438);
         beam->put_WebHeight(122);

         //
         // Bounding Box
         //
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );

         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,-11.0), true );

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val, 11.0), true );

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val,125.5), true );

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
         ASSERT_EQ( IsEqual(area,130.436), true );
         ASSERT_EQ( IsEqual(ixx,347173.21061789), true );
         ASSERT_EQ( IsEqual(iyy,3106.5209479986), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,0.0), true );
         ASSERT_EQ( IsEqual(cgy,52.67,0.01), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         Float64 xleft,xright,ytop,ybottom;
         props->get_Xleft(&xleft);
         props->get_Xright(&xright);
         props->get_Ytop(&ytop);
         props->get_Ybottom(&ybottom);
         ASSERT_EQ(IsEqual(xleft,11.0),true);
         ASSERT_EQ(IsEqual(xright,11.0),true);
         ASSERT_EQ(IsEqual(ytop,125.5-cgy),true);
         ASSERT_EQ(IsEqual(ybottom,cgy),true);

         //
         // Perimeter
         //
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&val), S_OK );
         ASSERT_EQ( IsEqual(val,338.124), true );

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
         ASSERT_EQ( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
         ASSERT_EQ( shape->FurthestDistance(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,200.000), true );

         // shape on left
         p1->Move(0,-200);
         p2->Move(100,-200);
         line->ThroughPoints(p1,p2);
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,-200.0), true );

         // 
         // PolyPoints
         //
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );

         IndexType cPoints;
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 12 );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         std::array<CComPtr<IPoint2d>, 12> points;
         ULONG fetched;
         Enum->Next(12,&points[0],&fetched);
         ASSERT_EQ( fetched, 12 );

         Float64 x,y;

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-11.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-11.0), true );
         ASSERT_EQ( IsEqual(y, 2.25), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-0.219), true );
         ASSERT_EQ( IsEqual(y, 2.25), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-0.219), true );
         ASSERT_EQ( IsEqual(y, 124.25), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-11.0), true );
         ASSERT_EQ( IsEqual(y, 124.25), true );

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-11.0), true );
         ASSERT_EQ( IsEqual(y, 125.5), true );

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,11.0), true );
         ASSERT_EQ( IsEqual(y,125.5), true );

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,11.0), true );
         ASSERT_EQ( IsEqual(y,124.25), true );

         points[8]->get_X(&x);
         points[8]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.219), true );
         ASSERT_EQ( IsEqual(y,124.25), true );

         points[9]->get_X(&x);
         points[9]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.219), true );
         ASSERT_EQ( IsEqual(y,2.25), true );

         points[10]->get_X(&x);
         points[10]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,11.0), true );
         ASSERT_EQ( IsEqual(y,2.25), true );

         points[11]->get_X(&x);
         points[11]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,11.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ(shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ(shape->Clone(&clone), S_OK);

         CComQIPtr<IPlateGirder> beamClone(clone);
         ASSERT_EQ( beamClone != nullptr, true );

         beamClone->get_BottomFlangeThickness(&val);
         ASSERT_EQ( IsEqual(val,2.25), true);

         beamClone->get_BottomFlangeWidth(&val);
         ASSERT_EQ( IsEqual(val,22.0), true);

         beamClone->get_TopFlangeThickness(&val);
         ASSERT_EQ( IsEqual(val,1.25), true);

         beamClone->get_TopFlangeWidth(&val);
         ASSERT_EQ( IsEqual(val,22.0), true);

         beamClone->get_WebHeight(&val);
         ASSERT_EQ( IsEqual(val,122.0), true);

         beamClone->get_WebWidth(&val);
         ASSERT_EQ( IsEqual(val,0.438), true);

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(0.0, 50.);

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
         p1->Move( 50,50);
         p2->Move(-50,50);

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
         ASSERT_EQ( cPoints, 8 );

         coll->get__Enum(&Enum);
         Enum->Next(8,&points[0],&fetched);
         ASSERT_EQ( fetched, 8 );

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-0.219), true );
         ASSERT_EQ( IsEqual(y, 50.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-0.219), true );
         ASSERT_EQ( IsEqual(y, 124.25), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-11.0), true );
         ASSERT_EQ( IsEqual(y, 124.25), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-11.0), true );
         ASSERT_EQ( IsEqual(y,125.5), true );

         points[4]->get_X(&x);
         points[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,11.0), true );
         ASSERT_EQ( IsEqual(y,125.5), true );

         points[5]->get_X(&x);
         points[5]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,11.0), true );
         ASSERT_EQ( IsEqual(y,124.25), true );

         points[6]->get_X(&x);
         points[6]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.219), true );
         ASSERT_EQ( IsEqual(y,124.25),true );

         points[7]->get_X(&x);
         points[7]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.219), true );
         ASSERT_EQ( IsEqual(y,50.0), true );

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

         ASSERT_EQ( shape->ClipIn(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipIn(clipRect,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );

         // Verify clip by checking points
         coll.Release();
         Enum.Release();
         std::for_each(std::begin(points), std::end(points), [](auto& point) {point.Release(); });


         ASSERT_EQ(clip->get_PolyPoints(&coll), S_OK );
         coll->get_Count(&cPoints);
         ASSERT_EQ( cPoints, 4 );

         coll->get__Enum(&Enum);
         Enum->Next(5,&points[0],&fetched);
         ASSERT_EQ( fetched, 4 );

         int i = 0;
         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-0.219), true );
         ASSERT_EQ( IsEqual(y, 50.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x,-0.219), true );
         ASSERT_EQ( IsEqual(y, 55.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 0.219), true );
         ASSERT_EQ( IsEqual(y, 55.0), true );

         points[i++]->Location(&x, &y);
         ASSERT_EQ( IsEqual(x, 0.219), true );
         ASSERT_EQ( IsEqual(y, 50.0), true );
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ( position.CoCreateInstance( CLSID_PlateGirder), S_OK);

         CComQIPtr<IPlateGirder> beam(position);
         CComQIPtr<IShape> shape(position);

         CComPtr<IPoint2d> hookPnt;
         hookPnt.CoCreateInstance( CLSID_Point2d );
         hookPnt->Move(0,0);

         // Use some real dimensions
         beam->putref_HookPoint(hookPnt);
         beam->put_TopFlangeWidth(22);
         beam->put_TopFlangeThickness(1.25);
         beam->put_BottomFlangeWidth(22);
         beam->put_BottomFlangeThickness(2.25);
         beam->put_WebWidth(0.438);
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

         ASSERT_EQ( position->MoveEx(nullptr,to), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to), S_OK );

         CComPtr<IShapeProperties> props;
         shape->get_ShapeProperties(&props);
         CComPtr<IPoint2d> cg;
         props->get_Centroid(&cg);

         Float64 x,y;
         cg->get_X(&x);
         cg->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.),true);
         ASSERT_EQ(IsEqual(y,152.67,0.01),true);

         //
         // OffsetEx
         //

         // Move the shape back to where it was
         hookPnt->Move(0,0);

         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(100);
         size->put_Dy(100);

         ASSERT_EQ(position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ(position->OffsetEx(size), S_OK);

         props.Release();
         shape->get_ShapeProperties(&props);

         cg.Release();
         props->get_Centroid(&cg);

         cg->get_X(&x);
         cg->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.),true);
         ASSERT_EQ(IsEqual(y,152.67,0.01),true);

         //
         // LocatorPoint property
         //
         hookPnt->Move(0,0);
         ASSERT_EQ( position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER );

         // BottomLeft
         hookPnt->Move(0,0);
         to->Move(89,100);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 89.), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
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
         to->Move(111,100.000);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,111.), true );
         ASSERT_EQ(IsEqual(y,100.000), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterLeft
         hookPnt->Move(0,0);
         to->Move(89,162.75);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 89.), true );
         ASSERT_EQ(IsEqual(y,162.75), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterCenter
         hookPnt->Move(0,0);
         to->Move(100,162.75);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,162.75), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // CenterRight
         hookPnt->Move(0,0);
         to->Move(111,162.75);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,111.), true );
         ASSERT_EQ(IsEqual(y,162.75), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopLeft
         hookPnt->Move(0,0);
         to->Move(89,225.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x, 89.), true );
         ASSERT_EQ(IsEqual(y,225.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopCenter
         hookPnt->Move(0,0);
         to->Move(100,225.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.000), true );
         ASSERT_EQ(IsEqual(y,225.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

         // TopRight
         hookPnt->Move(0,0);
         to->Move(111,225.5);
         from.Release();
         ASSERT_EQ( position->put_LocatorPoint( lpTopRight, to ), S_OK );
         ASSERT_EQ( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ(IsEqual(x,111.), true );
         ASSERT_EQ(IsEqual(y,225.5), true );
         hookPnt->get_X(&x);
         hookPnt->get_Y(&y);
         ASSERT_EQ(IsEqual(x,100.0), true );
         ASSERT_EQ(IsEqual(y,100.0), true );

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

         props.Release();
         shape->get_ShapeProperties(&props);
         cg.Release();
         props->get_Centroid(&cg);
         cg->get_X(&x);
         cg->get_Y(&y);
         ASSERT_EQ(IsEqual(x,0.00),true);
         ASSERT_EQ(IsEqual(y,-52.67,0.01),true);
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_PlateGirder ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IPlateGirder ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests