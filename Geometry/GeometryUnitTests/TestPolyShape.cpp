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

// TestPolyShape.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestPolyShape.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h). The legacy Test() was a pure dispatcher to the
// methods below, which are now independent TEST_METHODs; the dispatcher
// itself is dropped.
#include "pch.h"

namespace GeometryUnitTests
{

// Ported unchanged from F:\ARP\WBFL\Geometry\GeometryTest\TestPolyShape.cpp
// (were private static helper methods of CTestPolyShape; ported as free
// functions since TEST_METHODs don't share a meaningful base class here).
// TestIShapeOpen/TestIShapeClosed are called from TestIShape below; TestPoints
// is called from TestIXYPosition below - same call structure as the original.
void TestIShapeOpen()
{
         // Test with an open polygon
         CComPtr<IShape> shape;
         ASSERT_EQ( shape.CoCreateInstance( CLSID_PolyShape ), S_OK );

         CComQIPtr<IPolyShape> polyShape(shape);

         // Properties of a degenerate shape
         CComPtr<IShapeProperties> props;
         ASSERT_EQ(shape->get_ShapeProperties( nullptr ), E_POINTER );
         ASSERT_EQ(shape->get_ShapeProperties(&props), S_OK );
         Float64 area, ixx, iyy, ixy, cgx, cgy;
         CComPtr<IPoint2d> cg;
         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         props->get_Centroid(&cg);
         ASSERT_EQ( IsZero(area), true );
         ASSERT_EQ( IsZero(ixx), true );
         ASSERT_EQ( IsZero(iyy), true );
         ASSERT_EQ( IsZero(ixy), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsZero(cgx), true );
         ASSERT_EQ( IsZero(cgy), true );

         // Use are real shape. 5x10 rectangle.
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(5,0);
         polyShape->AddPoint(5,10);
         polyShape->AddPoint(0,10);
         props.Release();
         ASSERT_EQ(shape->get_ShapeProperties(&props), S_OK );
         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         cg.Release();
         props->get_Centroid(&cg);
         ASSERT_EQ( IsEqual(area,50.0), true );
         ASSERT_EQ( IsEqual(ixx,416.66666666666666), true );
         ASSERT_EQ( IsEqual(iyy,104.16666666666666), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,2.5), true );
         ASSERT_EQ( IsEqual(cgy,5.0), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         //
         // BoundingBox
         //
         Float64 val;
         CComPtr<IRect2d> box;
         ASSERT_EQ( shape->get_BoundingBox(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_BoundingBox(&box), S_OK );
         box->get_Left(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );
         props->get_Xleft(&val);
         ASSERT_EQ( IsEqual(val,2.5), true );

         box->get_Right(&val);
         ASSERT_EQ( IsEqual(val,5.0), true );
         props->get_Xright(&val);
         ASSERT_EQ( IsEqual(val,2.5), true );

         box->get_Top(&val);
         ASSERT_EQ( IsEqual(val,10.0), true );
         props->get_Ytop(&val);
         ASSERT_EQ( IsEqual(val,5.0), true );

         box->get_Bottom(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );
         props->get_Ybottom(&val);
         ASSERT_EQ( IsEqual(val,5.0), true );

         //
         // PolyPoints
         //
         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( shape->get_PolyPoints(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_PolyPoints(&coll), S_OK );

         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);

         CComPtr<IPoint2d> pnts[7];
         ULONG fetched;
         Enum->Next(4,&pnts[0],&fetched);
         ASSERT_EQ(fetched,4);

         Float64 x,y;
         pnts[0]->get_X(&x);
         pnts[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         pnts[1]->get_X(&x);
         pnts[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,5.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         pnts[2]->get_X(&x);
         pnts[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 5.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         pnts[3]->get_X(&x);
         pnts[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         //
         // Perimeter
         //
         Float64 perimeter;
         ASSERT_EQ( shape->get_Perimeter(nullptr), E_POINTER );
         ASSERT_EQ( shape->get_Perimeter(&perimeter), S_OK );
         ASSERT_EQ( IsEqual(perimeter,30.0), true );

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
         ASSERT_EQ( shape->FurthestDistance(nullptr,&dist), E_INVALIDARG );
         ASSERT_EQ( shape->FurthestDistance(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,20.0), true );

         // shape on left
         p1->Move(0,-20);
         p2->Move(100,-20);
         line->ThroughPoints(p1,p2);
         ASSERT_EQ( shape->FurthestDistance(line,&dist), S_OK );
         ASSERT_EQ( IsEqual(dist,-20.0), true );

         //
         // Clone
         //
         CComPtr<IShape> clone;
         ASSERT_EQ( shape->Clone(nullptr), E_POINTER );
         ASSERT_EQ( shape->Clone(&clone), S_OK );
         CComQIPtr<IPolyShape> ps(clone);
         ASSERT_EQ(ps != nullptr, true );
         props.Release();
         ASSERT_EQ(clone->get_ShapeProperties(&props), S_OK );
         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         cg.Release();
         props->get_Centroid(&cg);
         ASSERT_EQ( IsEqual(area,50.0), true );
         ASSERT_EQ( IsEqual(ixx,416.66666666666666), true );
         ASSERT_EQ( IsEqual(iyy,104.16666666666666), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,2.5), true );
         ASSERT_EQ( IsEqual(cgy,5.0), true );
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );
         clone.Release();

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(3,3);
         ASSERT_EQ( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
         ASSERT_EQ( shape->PointInShape(pnt,nullptr), E_POINTER );
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_TRUE );

         pnt->Move(100,100);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(2.5,0);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(5,5);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         //
         // ClipWithLine
         //
         p1->Move(0,0);
         p2->Move(100,100);
         line->ThroughPoints(p1,p2);
         CComPtr<IShape> clip;
         ASSERT_EQ( shape->ClipWithLine(nullptr,&clip), E_INVALIDARG );
         ASSERT_EQ( shape->ClipWithLine(line,nullptr), E_POINTER );
         ASSERT_EQ( shape->ClipWithLine(line,&clip), S_OK );

         coll.Release();
         clip->get_PolyPoints(&coll);
         IndexType nPoints;
         coll->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 4 );

         Enum.Release();
         coll->get__Enum(&Enum);
         pnts[0].Release();
         pnts[1].Release();
         pnts[2].Release();
         pnts[3].Release();
         Enum->Next((ULONG)nPoints,&pnts[0],&fetched);
         ASSERT_EQ(fetched,nPoints);

         pnts[0]->get_X(&x);
         pnts[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         pnts[1]->get_X(&x);
         pnts[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,5.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         pnts[2]->get_X(&x);
         pnts[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,5.0), true );
         ASSERT_EQ( IsEqual(y,5.0), true );

         pnts[3]->get_X(&x);
         pnts[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         // Clip away the entire shape
         p1->Move(0,1000);
         p2->Move(1000,1000);
         line->ThroughPoints(p2,p1);
         clip.Release();
         shape->ClipWithLine(line,&clip);
         ASSERT_EQ( clip == 0, true );

         // Clip such that the resulting polygon is simply a line
         // Since the resulting shape is not a polygon, the clip shape is nullptr
         p1->Move(0,0);
         p2->Move(10,0);
         line->ThroughPoints(p1,p2);
         clip.Release();
         shape->ClipWithLine(line,&clip);
         ASSERT_EQ( clip == 0, true );

         // clip with the same line in opposite directions...
         // the area of each resulting clip shape should total
         // the area of the whole shape
         props.Release();
         shape->get_ShapeProperties(&props);
         props->get_Area(&area);

         p1->Move(-5,7);
         p2->Move(15,7);
         line->ThroughPoints(p1,p2);
         clip.Release();
         shape->ClipWithLine(line,&clip);
         props.Release();

         Float64 area1;
         clip->get_ShapeProperties(&props);
         props->get_Area(&area1);

         line->Reverse();
         clip.Release();
         shape->ClipWithLine(line,&clip);
         props.Release();

         Float64 area2;
         clip->get_ShapeProperties(&props);
         props->get_Area(&area2);

         ASSERT_EQ( IsEqual(area,area1+area2), true);


         //
         // ClipIn
         //
         CComPtr<IRect2d> clipRect;
         clipRect.CoCreateInstance( CLSID_Rect2d );
         clipRect->put_Left(2.5);
         clipRect->put_Right(10);
         clipRect->put_Top(20);
         clipRect->put_Bottom(5);

         clip.Release();
         ASSERT_EQ( shape->ClipIn(nullptr,&clip),     E_INVALIDARG );
         ASSERT_EQ( shape->ClipIn(clipRect,nullptr),  E_POINTER );
         ASSERT_EQ( shape->ClipIn(clipRect,&clip), S_OK );

         coll.Release();
         clip->get_PolyPoints(&coll);
         coll->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 5 );

         Enum.Release();
         coll->get__Enum(&Enum);
         pnts[0].Release();
         pnts[1].Release();
         pnts[2].Release();
         pnts[3].Release();
         pnts[4].Release();
         Enum->Next((ULONG)nPoints,&pnts[0],&fetched);
         ASSERT_EQ(fetched,nPoints);

         pnts[0]->get_X(&x);
         pnts[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,5.0), true );
         ASSERT_EQ( IsEqual(y,5.0), true );

         pnts[1]->get_X(&x);
         pnts[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 5.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         pnts[2]->get_X(&x);
         pnts[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 2.5), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         pnts[3]->get_X(&x);
         pnts[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,2.5), true );
         ASSERT_EQ( IsEqual(y,5.0), true );

         pnts[4]->get_X(&x);
         pnts[4]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,5.0), true );
         ASSERT_EQ( IsEqual(y,5.0), true );

         clip.Release();
}

void TestIShapeClosed()
{
         // Test with a closed polygon
         CComPtr<IShape> shape;
         ASSERT_EQ( shape.CoCreateInstance( CLSID_PolyShape ), S_OK );

         CComQIPtr<IPolyShape> polyShape(shape);

         // Use are real shape. 5x10 rectangle.
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(5,0);
         polyShape->AddPoint(5,10);
         polyShape->AddPoint(0,10);
         polyShape->AddPoint(0,0);

         CComPtr<IShapeProperties> props;
         Float64 area, ixx, iyy, ixy, cgx, cgy;
         CComPtr<IPoint2d> cg;
         shape->get_ShapeProperties(&props);
         props->get_Area(&area);
         props->get_Ixx(&ixx);
         props->get_Iyy(&iyy);
         props->get_Ixy(&ixy);
         props->get_Centroid(&cg);
         ASSERT_EQ( IsEqual(area,50.0), true );
         ASSERT_EQ( IsEqual(ixx,416.66666666666666), true );
         ASSERT_EQ( IsEqual(iyy,104.16666666666666), true );
         ASSERT_EQ( IsEqual(ixy,0.0), true );
         cg->get_X(&cgx);
         cg->get_Y(&cgy);
         ASSERT_EQ( IsEqual(cgx,2.5), true );
         ASSERT_EQ( IsEqual(cgy,5.0), true );
         CoordinateSystemType cst;
         props->get_CoordinateSystem(&cst);
         ASSERT_EQ( cst, csCentroidal );

         //
         // PointInShape
         //
         VARIANT_BOOL bPointInShape;
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move(3,3);
         ASSERT_EQ( shape->PointInShape(nullptr,&bPointInShape), E_INVALIDARG );
         ASSERT_EQ( shape->PointInShape(pnt,nullptr), E_POINTER );
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_TRUE );

         pnt->Move(100,100);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(2.5,0);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         pnt->Move(5,5);
         ASSERT_EQ( shape->PointInShape(pnt,&bPointInShape), S_OK );
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );
}

void TestPoints(IPolyShape* polyShape)
{
         CComPtr<IPoint2dCollection> coll;
         polyShape->get_Points(&coll);
         std::array<CComPtr<IPoint2d>, 4> points;
         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         ULONG fetched;
         Enum->Next(4,&points[0],&fetched);
         ASSERT_EQ(fetched,4);

         Float64 x,y;
         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y,110.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,110.0), true );
}
TEST_CLASS(TestPolyShape)
{
public:
   TEST_METHOD(TestIPolyShape)
   {
         CComPtr<IPolyShape> polyShape;
         ASSERT_EQ( polyShape.CoCreateInstance( CLSID_PolyShape ), S_OK );

         IndexType nPoints;
         ASSERT_EQ( polyShape->get_Count(nullptr), E_POINTER );
         ASSERT_EQ( polyShape->get_Count(&nPoints), S_OK );
         ASSERT_EQ( nPoints, 0 );

         ASSERT_EQ( polyShape->AddPoint(0,0), S_OK );
         polyShape->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 1 );

         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->put_X(10);
         pnt->put_Y(0);
         ASSERT_EQ( polyShape->AddPointEx( nullptr), E_INVALIDARG );
         ASSERT_EQ( polyShape->AddPointEx( pnt ), S_OK );
         polyShape->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 2 );

         polyShape->AddPoint(10,10);
         polyShape->AddPoint( 0,10);
         polyShape->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 4 );

         CComPtr<IPoint2dCollection> coll;
         ASSERT_EQ( polyShape->get_Points(nullptr), E_POINTER );
         ASSERT_EQ( polyShape->get_Points(&coll), S_OK );
         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);

         std::array<CComPtr<IPoint2d>, 4> pnts;
         ULONG fetched;
         Enum->Next(4,&pnts[0],&fetched);
         ASSERT_EQ(fetched,4);

         Float64 x,y;
         pnts[0]->get_X(&x);
         pnts[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         pnts[1]->get_X(&x);
         pnts[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );

         pnts[2]->get_X(&x);
         pnts[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         pnts[3]->get_X(&x);
         pnts[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         ASSERT_EQ( polyShape->Clear(), S_OK );
         coll->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 4 );

         coll.Release();
         coll.CoCreateInstance( CLSID_Point2dCollection );
         coll->Add(pnts[0]);
         coll->Add(pnts[1]);
         coll->Add(pnts[2]);
         coll->Add(pnts[3]);
         coll->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 4 );
         polyShape->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 0 );
         ASSERT_EQ( polyShape->AddPoints(nullptr), E_INVALIDARG );
         ASSERT_EQ( polyShape->AddPoints(coll), S_OK );
         polyShape->get_Count(&nPoints);
         ASSERT_EQ( nPoints, 4 );

         pnt.Release();
         ASSERT_EQ( polyShape->get_Point(-1,&pnt),  E_INVALIDARG ); // Neg index
         ASSERT_EQ( polyShape->get_Point(100,&pnt), E_INVALIDARG ); // Index too large
         ASSERT_EQ( polyShape->get_Point(3,nullptr),   E_POINTER );
         ASSERT_EQ( polyShape->get_Point(2,&pnt),   S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         ASSERT_EQ( polyShape->RemovePoint(-1), E_INVALIDARG );
         ASSERT_EQ( polyShape->RemovePoint(10), E_INVALIDARG );
         ASSERT_EQ( polyShape->RemovePoint( 2), S_OK );
         pnt.Release();
         ASSERT_EQ( polyShape->get_Point(2,&pnt),   S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 0.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         CComPtr<IShape> shape;
         ASSERT_EQ(polyShape->get_Shape(nullptr), E_POINTER );
         ASSERT_EQ(polyShape->get_Shape(&shape), S_OK );
         ASSERT_EQ(shape != nullptr,true );

         CComPtr<IXYPosition> position;
         ASSERT_EQ(polyShape->get_XYPosition(nullptr), E_POINTER );
         ASSERT_EQ(polyShape->get_XYPosition(&position), S_OK );
         ASSERT_EQ(position != nullptr,true );

         CComPtr<IUnknown> punk1;
         CComPtr<IUnknown> punk2;
         CComPtr<IUnknown> punk3;
         polyShape->QueryInterface(&punk1);
         shape->QueryInterface(&punk2);
         position->QueryInterface(&punk3);
         ASSERT_EQ( punk1 == punk2, true );
         ASSERT_EQ( punk1 == punk3, true );
         ASSERT_EQ( punk2 == punk3, true );
   }

   TEST_METHOD(TestIShape)
   {
         TestIShapeOpen();
         TestIShapeClosed();

         // Misc Tests
         CComPtr<IShape> shape;
         shape.CoCreateInstance( CLSID_PolyShape );

         Float64 val;

         // BoundingBox w/ nPoints = 0
         CComPtr<IRect2d> box;
         shape->get_BoundingBox(&box);
         box->get_Left(&val);
         ASSERT_EQ( IsZero(val), true );
         box->get_Right(&val);
         ASSERT_EQ( IsZero(val), true );
         box->get_Top(&val);
         ASSERT_EQ( IsZero(val), true );
         box->get_Bottom(&val);
         ASSERT_EQ( IsZero(val), true );

         // PointInShape w/ nPoints < 3
         CComPtr<IPoint2d> pnt;
         pnt.CoCreateInstance( CLSID_Point2d );
         VARIANT_BOOL bPointInShape;
         shape->PointInShape(pnt,&bPointInShape);
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         // ClipWithLine w/ nPoints < 3
         CComPtr<ILine2d> line;
         line.CoCreateInstance( CLSID_Line2d );
         CComPtr<IShape> clip;
         shape->ClipWithLine(line,&clip);
         ASSERT_EQ( clip == 0, true );

         // PointInShape w/ Width = 0
         CComQIPtr<IPolyShape> polyShape(shape);
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(0,10);
         polyShape->AddPoint(0,10);
         shape->PointInShape(pnt,&bPointInShape);
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         // PointInShape w/ Height = 0
         polyShape->Clear();
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(10,0);
         polyShape->AddPoint(10,0);
         polyShape->AddPoint(0,0);
         shape->PointInShape(pnt,&bPointInShape);
         ASSERT_EQ( bPointInShape, VARIANT_FALSE );

         //
         // Test a diamond shape
         //
         CComPtr<IPolyShape> diamond;
         diamond.CoCreateInstance( CLSID_PolyShape );
         diamond->AddPoint(12.533141373155,0);
         diamond->AddPoint(0,12.533141373155);
         diamond->AddPoint(-12.533141373155,0);
         diamond->AddPoint(0,-12.533141373155);

         shape.Release();
         diamond->QueryInterface(&shape);
         CComPtr<IShapeProperties> props;
         shape->get_ShapeProperties(&props);
         Float64 area;
         props->get_Area(&area);
         ASSERT_EQ( IsEqual(area,100*M_PI), true );
   }

   TEST_METHOD(TestIXYPosition)
   {
         CComPtr<IXYPosition> position;
         ASSERT_EQ( position.CoCreateInstance( CLSID_PolyShape ), S_OK );

         CComQIPtr<IPolyShape> polyShape(position);

         // 5x10 rectangle.
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(5,0);
         polyShape->AddPoint(5,10);
         polyShape->AddPoint(0,10);

         //
         // MoveEx (also provides full code coverage for Offset)
         //
         CComPtr<IPoint2d> from;
         from.CoCreateInstance( CLSID_Point2d );
         from->put_X(10);
         from->put_Y(10);

         CComPtr<IPoint2d> to;
         to.CoCreateInstance( CLSID_Point2d );
         to->put_X(110);
         to->put_Y(110);

         ASSERT_EQ( position->MoveEx(nullptr,to), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,nullptr), E_INVALIDARG );
         ASSERT_EQ( position->MoveEx(from,to), S_OK );

         TestPoints(polyShape);

         //
         // OffsetEx
         //
         polyShape->Clear();
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(5,0);
         polyShape->AddPoint(5,10);
         polyShape->AddPoint(0,10);

         CComPtr<ISize2d> size;
         size.CoCreateInstance( CLSID_Size2d );
         size->put_Dx(100);
         size->put_Dy(100);

         ASSERT_EQ( position->OffsetEx(nullptr), E_INVALIDARG );
         ASSERT_EQ( position->OffsetEx(size), S_OK );

         TestPoints(polyShape);

         //
         // MoveLocatorPoint and MoveMoveLocatorPointEx
         //
         polyShape->Clear();
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(5,0);
         polyShape->AddPoint(5,10);
         polyShape->AddPoint(0,10);

         ASSERT_EQ(position->put_LocatorPoint(lpBottomLeft,nullptr), E_INVALIDARG );
         ASSERT_EQ(position->get_LocatorPoint(lpBottomLeft,nullptr), E_POINTER);

         // Bottom Left
         Float64 x,y;
         to->Move(100,100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpBottomLeft,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpBottomLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         TestPoints(polyShape);

         // Bottom Center
         to->Move(102.5,100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpBottomCenter,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpBottomCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,102.5), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         TestPoints(polyShape);

         // Bottom Right
         to->Move(105,100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpBottomRight,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpBottomRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         TestPoints(polyShape);

         // Left Center
         to->Move(100,105);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpCenterLeft,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpCenterLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,105.0), true );
         TestPoints(polyShape);

         // Center
         to->Move(102.5,105);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpCenterCenter,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpCenterCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,102.5), true );
         ASSERT_EQ( IsEqual(y,105.0), true );
         TestPoints(polyShape);

         // Right Center
         to->Move(105,105);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpCenterRight,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpCenterRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y,105.0), true );
         TestPoints(polyShape);

         // Top Left
         to->Move(100,110);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpTopLeft,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpTopLeft,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,110.0), true );
         TestPoints(polyShape);

         // Top Center
         to->Move(102.5,110);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpTopCenter,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpTopCenter,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,102.5), true );
         ASSERT_EQ( IsEqual(y,110.0), true );
         TestPoints(polyShape);

         // Top Right
         to->Move(105,110);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpTopRight,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpTopRight,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,105.0), true );
         ASSERT_EQ( IsEqual(y,110.0), true );
         TestPoints(polyShape);

         // Hook Point (first point)
         to->Move(100,100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpHookPoint,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpHookPoint,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,100.0), true );
         ASSERT_EQ( IsEqual(y,100.0), true );
         TestPoints(polyShape);

         // Hook Point for polyshape with zero points
         polyShape->Clear();
         to->Move(100,100);
         from.Release();
         ASSERT_EQ(position->put_LocatorPoint(lpHookPoint,to), S_OK );
         ASSERT_EQ(position->get_LocatorPoint(lpHookPoint,&from), S_OK );
         from->get_X(&x);
         from->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(x,0.0), true );

         //
         // Rotate and RotateEx
         //
         polyShape->Clear();
         polyShape->AddPoint(0,0);
         polyShape->AddPoint(5,0);
         polyShape->AddPoint(5,10);
         polyShape->AddPoint(0,10);

         to->Move(5,10); // Use "to" as the center of rotation
         ASSERT_EQ( position->RotateEx(nullptr,M_PI/2), E_INVALIDARG );
         ASSERT_EQ( position->RotateEx(to,M_PI/2), S_OK );

         CComPtr<IPoint2dCollection> coll;
         polyShape->get_Points(&coll);
         std::array<CComPtr<IPoint2d>, 4> points;
         CComPtr<IEnumPoint2d> Enum;
         coll->get__Enum(&Enum);
         ULONG fetched;
         Enum->Next(4,&points[0],&fetched);
         ASSERT_EQ(fetched,4);

         points[0]->get_X(&x);
         points[0]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,15.0), true );
         ASSERT_EQ( IsEqual(y, 5.0), true );

         points[1]->get_X(&x);
         points[1]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,15.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         points[2]->get_X(&x);
         points[2]->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 5.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         points[3]->get_X(&x);
         points[3]->get_Y(&y);
         ASSERT_EQ( IsEqual(x,5.0), true );
         ASSERT_EQ( IsEqual(y,5.0), true );
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_PolyShape ), S_OK );
         ASSERT_EQ( eInfo != nullptr, true );

         // Interfaces that should be supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IPolyShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

         // Interface that is not supported
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }

   TEST_METHOD(TestContains)
   {
         CComPtr<IPolyShape> polyShape;
         polyShape.CoCreateInstance( CLSID_PolyShape );

      //    (3,15)+------+ (7,15)
      //          |      |
      //(0,10)    |      |
      //   +------+      +------+ (10,10)
      //   |                    |
      //   |                    |
      //   |             +      |
      //   |          (7,5)     |
      //   |                    |
      //   +--------------------+
      //(0,0)                     (10,0)

         polyShape->AddPoint( 0, 0);
         polyShape->AddPoint(10, 0);
         polyShape->AddPoint(10,10);
         polyShape->AddPoint( 7,10);
         polyShape->AddPoint( 7,15);
         polyShape->AddPoint( 3,15);
         polyShape->AddPoint( 3,10);
         polyShape->AddPoint( 0,10);

         CComPtr<IPoint2d> p;
         p.CoCreateInstance(CLSID_Point2d);
         p->Move(7,5);

         VARIANT_BOOL bContains;
         CComQIPtr<IShape> shape(polyShape);
         shape->PointInShape(p,&bContains);
         ASSERT_EQ( bContains, VARIANT_TRUE );
   }
};
} // namespace GeometryUnitTests