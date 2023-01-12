///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TestNUDeckedIBeam.cpp: implementation of the CTestNUDeckedIBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestNUDeckedIBeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestNUDeckedIBeam::CTestNUDeckedIBeam()
{

}

CTestNUDeckedIBeam::~CTestNUDeckedIBeam()
{

}

void CTestNUDeckedIBeam::Test()
{
   TestINUDeckedIBeam();
   TestIShape();
   TestIShape2();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestNUDeckedIBeam::TestINUDeckedIBeam()
{
   CComPtr<INUDeckedIBeam> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_NUDeckedIBeam), S_OK );

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

   TRY_TEST(beam->get_D5(nullptr), E_POINTER);
   TRY_TEST(beam->get_D5(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D6(nullptr), E_POINTER);
   TRY_TEST(beam->get_D6(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_T(nullptr), E_POINTER);
   TRY_TEST(beam->get_T(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_H(nullptr), E_POINTER);
   TRY_TEST(beam->get_H(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST( beam->get_W1(nullptr), E_POINTER );
   TRY_TEST( beam->get_W1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W2(nullptr), E_POINTER );
   TRY_TEST( beam->get_W2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST(beam->get_W3(nullptr), E_POINTER);
   TRY_TEST(beam->get_W3(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W4(nullptr), E_POINTER);
   TRY_TEST(beam->get_W4(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST( beam->get_R1(nullptr), E_POINTER );
   TRY_TEST( beam->get_R1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_R2(nullptr), E_POINTER );
   TRY_TEST( beam->get_R2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST(beam->get_C1(nullptr), E_POINTER);
   TRY_TEST(beam->get_C1(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST( beam->get_HookPoint(nullptr), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_D1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D1(2), S_OK );
   beam->get_D1(&val);
   TRY_TEST( IsEqual(val,2.0), true );

   TRY_TEST( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D2(6), S_OK );
   beam->get_D2(&val);
   TRY_TEST( IsEqual(val,6.0), true );

   TRY_TEST( beam->put_D3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D3(9), S_OK );
   beam->get_D3(&val);
   TRY_TEST( IsEqual(val,9.0), true );

   TRY_TEST( beam->put_D4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D4(3), S_OK );
   beam->get_D4(&val);
   TRY_TEST( IsEqual(val,3.0), true );

   TRY_TEST( beam->put_D5(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D5(13), S_OK );
   beam->get_D5(&val);
   TRY_TEST( IsEqual(val,13.0), true );

   TRY_TEST(beam->put_D6(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D6(5), S_OK);
   beam->get_D6(&val);
   TRY_TEST(IsEqual(val, 5.0), true);

   TRY_TEST(beam->put_H(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_H(108), S_OK);
   beam->get_H(&val);
   TRY_TEST(IsEqual(val, 108.0), true);

   TRY_TEST(beam->put_T(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_T(4), S_OK);
   beam->get_T(&val);
   TRY_TEST(IsEqual(val, 4.0), true);

   TRY_TEST( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W1(26), S_OK );
   beam->get_W1(&val);
   TRY_TEST( IsEqual(val,26.0), true );

   TRY_TEST( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W2(49), S_OK );
   beam->get_W2(&val);
   TRY_TEST( IsEqual(val,49.0), true );

   TRY_TEST(beam->put_W3(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W3(1), S_OK);
   beam->get_W3(&val);
   TRY_TEST(IsEqual(val, 1.0), true);

   TRY_TEST(beam->put_W4(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W4(38), S_OK);
   beam->get_W4(&val);
   TRY_TEST(IsEqual(val, 38.0), true);

   TRY_TEST( beam->put_R1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_R1(10), S_OK );
   beam->get_R1(&val);
   TRY_TEST( IsEqual(val,10.0), true );

   TRY_TEST( beam->put_R2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_R2(22.5), S_OK );
   beam->get_R2(&val);
   TRY_TEST( IsEqual(val,22.5), true );

   TRY_TEST(beam->put_C1(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_C1(1), S_OK);
   beam->get_C1(&val);
   TRY_TEST(IsEqual(val, 1.0), true);

   pntVal->Move(14,14);
   TRY_TEST( beam->putref_HookPoint(nullptr), E_INVALIDARG );
   TRY_TEST( beam->putref_HookPoint(pntVal), S_OK );
   pntVal.Release();
   beam->get_HookPoint(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,14.0), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,14.0), true );

   // Move the beam back
   pntVal->Move(0,0);
   beam->putref_HookPoint(pntVal);

   // Test propertyes
   TRY_TEST(beam->get_Height(nullptr), E_POINTER );
   TRY_TEST(beam->get_Height(&val), S_OK );
   TRY_TEST(IsEqual(val,108.), true );

   TRY_TEST(beam->get_TopFlangeWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_TopFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,126.), true );

   TRY_TEST(beam->get_BottomFlangeWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_BottomFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,38.), true );

   TRY_TEST(beam->get_AvgWebWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_AvgWebWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,4.), true );


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

void CTestNUDeckedIBeam::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_NUDeckedIBeam), S_OK);

   CComQIPtr<INUDeckedIBeam> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Use some real dimensions
   beam->put_W1(26);
   beam->put_W2(49);
   beam->put_W3(1);
   beam->put_W4(38);
   beam->put_D1(2);
   beam->put_D2(6);
   beam->put_D3(9);
   beam->put_D4(3);
   beam->put_D5(13);
   beam->put_D6(5);
   beam->put_H(108);
   beam->put_T(4);
   beam->put_R1(10);
   beam->put_R2(22.5);

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
}

void CTestNUDeckedIBeam::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_NUDeckedIBeam ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_INUDeckedIBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}


#define TEST_POINT(_point_,_x_,_y_) _point_[i]->get_X(&x); _point_[i++]->get_Y(&y); TRY_TEST(IsEqual(x,_x_,0.0001),true); TRY_TEST(IsEqual(y,_y_,0.0001),true);

void CTestNUDeckedIBeam::TestIShape()
{
	CComPtr<IShape> shape;
	TRY_TEST(shape.CoCreateInstance(CLSID_NUDeckedIBeam), S_OK);
	CComQIPtr<INUDeckedIBeam> beam(shape);

	// Use some real dimensions
	beam->put_W1(26);
	beam->put_W2(49);
	beam->put_W3(1);
	beam->put_W4(38);
	beam->put_D1(2);
	beam->put_D2(6);
	beam->put_D3(9);
	beam->put_D4(3);
	beam->put_D5(13);
	beam->put_D6(5);
	beam->put_H(108);
	beam->put_T(4);
	beam->put_R1(10);
	beam->put_R2(22.5);
	beam->put_C1(1.0);
	
	//
	// Bounding Box
	//
	Float64 val;
	CComPtr<IRect2d> box;
	TRY_TEST(shape->get_BoundingBox(nullptr), E_POINTER);
	TRY_TEST(shape->get_BoundingBox(&box), S_OK);

	box->get_Left(&val);
	TRY_TEST(IsEqual(val, -63.0), true);

	box->get_Right(&val);
	TRY_TEST(IsEqual(val, 63.0), true);

	box->get_Top(&val);
	TRY_TEST(IsEqual(val, 108.0), true);

	box->get_Bottom(&val);
	TRY_TEST(IsEqual(val, 0.00), true);

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
	TRY_TEST(IsEqual(area, 1286.6976042586434), true);
	TRY_TEST(IsEqual(ixx, 2471035.0754711358), true);
	TRY_TEST(IsEqual(iyy, 419404.68570325995), true);
	TRY_TEST(IsEqual(ixy, 0.0, 0.0005), true);
	cg->get_X(&cgx);
	cg->get_Y(&cgy);
	TRY_TEST(IsEqual(cgx, 0.0), true);
	TRY_TEST(IsEqual(cgy, 59.057149336875156), true);
	CoordinateSystemType cst;
	props->get_CoordinateSystem(&cst);
	TRY_TEST(cst, csCentroidal);

	Float64 xleft, xright, ytop, ybottom;
	props->get_Xleft(&xleft);
	props->get_Xright(&xright);
	props->get_Ytop(&ytop);
	props->get_Ybottom(&ybottom);
	TRY_TEST(IsEqual(xleft, 63.0), true);
	TRY_TEST(IsEqual(xright, 63.0), true);
	TRY_TEST(IsEqual(ytop, 108.0 - cgy), true);
	TRY_TEST(IsEqual(ybottom, cgy), true);

	//
	// Perimeter
	//
	TRY_TEST(shape->get_Perimeter(nullptr), E_POINTER);
	TRY_TEST(shape->get_Perimeter(&val), S_OK);
	TRY_TEST(IsEqual(val, 502.08150632310787), true);

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
}

void CTestNUDeckedIBeam::TestIShape2()
{
	CComPtr<IShape> shape;
	TRY_TEST(shape.CoCreateInstance(CLSID_NUDeckedIBeam), S_OK);
	CComQIPtr<INUDeckedIBeam> beam(shape);

	// Use some real dimensions
	beam->put_W1(26);
	beam->put_W2(49);
	beam->put_W3(1);
	beam->put_W4(38);
	beam->put_D1(2);
	beam->put_D2(6);
	beam->put_D3(9);
	beam->put_D4(3);
	beam->put_D5(13);
	beam->put_D6(5);
	beam->put_H(108);
	beam->put_T(4);
	beam->put_R1(10);
	beam->put_R2(22.5);
	beam->put_C1(1.0);

	// 
	// PolyPoints
	//
	CComPtr<IPoint2dCollection> coll;
	TRY_TEST(shape->get_PolyPoints(nullptr), E_POINTER);
	TRY_TEST(shape->get_PolyPoints(&coll), S_OK);

	const CollectionIndexType nPoints = 96; // number of expected points
	CollectionIndexType cPoints;
	coll->get_Count(&cPoints);
	TRY_TEST(cPoints, nPoints);

	CComPtr<IEnumPoint2d> Enum;
	coll->get__Enum(&Enum);
	CComPtr<IPoint2d> points[nPoints];
	ULONG fetched;
	Enum->Next(nPoints, &points[0], &fetched);
	TRY_TEST(fetched, nPoints);

	Float64 x, y;
	int i = 0;

   // dump for plotting
	//for (int j = 0; j < nPoints; j++)
	//{
	//	CComPtr<IPoint2d> pnt;
	//	points[j]->Location(&x, &y);
	//	std::cout << x << ", " << y << std::endl;
	//}


   TEST_POINT(points, -18.0, 0.0);
   TEST_POINT(points, -19.0, 1.0);
   TEST_POINT(points, -19.0, 5.0);
   TEST_POINT(points, -14.9196, 6.9202);
   TEST_POINT(points, -13.7843, 7.49421);
   TEST_POINT(points, -12.6832, 8.13146);
   TEST_POINT(points, -11.62, 8.82992);
   TEST_POINT(points, -10.5979, 9.58735);
   TEST_POINT(points, -9.62023, 10.4013);
   TEST_POINT(points, -8.69016, 11.2693);
   TEST_POINT(points, -7.81062, 12.1884);
   TEST_POINT(points, -6.98443, 13.1558);
   TEST_POINT(points, -6.21424, 14.1683);
   TEST_POINT(points, -5.5025, 15.2227);
   TEST_POINT(points, -4.8515, 16.3157);
   TEST_POINT(points, -4.2633, 17.4437);
   TEST_POINT(points, -3.7398, 18.6031);
   TEST_POINT(points, -3.28267, 19.7903);
   TEST_POINT(points, -2.89336, 21.0014);
   TEST_POINT(points, -2.57313, 22.2326);
   TEST_POINT(points, -2.32299, 23.4799);
   TEST_POINT(points, -2.14374, 24.7394);
   TEST_POINT(points, -2.03596, 26.007);
   TEST_POINT(points, -2.0, 27.2786);
   TEST_POINT(points, -2.0, 89.0995);
   TEST_POINT(points, -2.03044, 89.8791);
   TEST_POINT(points, -2.12156, 90.654);
   TEST_POINT(points, -2.27281, 91.4194);
   TEST_POINT(points, -2.48327, 92.1706);
   TEST_POINT(points, -2.75167, 92.9032);
   TEST_POINT(points, -3.07636, 93.6127);
   TEST_POINT(points, -3.45536, 94.2946);
   TEST_POINT(points, -3.88638, 94.9449);
   TEST_POINT(points, -4.36679, 95.5597);
   TEST_POINT(points, -4.89367, 96.1351);
   TEST_POINT(points, -5.4638, 96.6677);
   TEST_POINT(points, -6.07371, 97.1543);
   TEST_POINT(points, -6.71971, 97.5918);
   TEST_POINT(points, -7.39784, 97.9776);
   TEST_POINT(points, -8.10399, 98.3093);
   TEST_POINT(points, -8.83385, 98.585);
   TEST_POINT(points, -9.58298, 98.803);
   TEST_POINT(points, -10.3468, 98.9619);
   TEST_POINT(points, -11.1207, 99.0608);
   TEST_POINT(points, -11.9, 99.099);
   TEST_POINT(points, -13.0, 105.0);
   TEST_POINT(points, -62.0, 106.0);
   TEST_POINT(points, -63.0, 108.0);
   TEST_POINT(points, 63.0, 108.0);
   TEST_POINT(points, 62.0, 106.0);
   TEST_POINT(points, 13.0, 105.0);
   TEST_POINT(points, 11.9, 99.099);
   TEST_POINT(points, 11.1207, 99.0608);
   TEST_POINT(points, 10.3468, 98.9619);
   TEST_POINT(points, 9.58298, 98.803);
   TEST_POINT(points, 8.83385, 98.585);
   TEST_POINT(points, 8.10399, 98.3093);
   TEST_POINT(points, 7.39784, 97.9776);
   TEST_POINT(points, 6.71971, 97.5918);
   TEST_POINT(points, 6.07371, 97.1543);
   TEST_POINT(points, 5.4638, 96.6677);
   TEST_POINT(points, 4.89367, 96.1351);
   TEST_POINT(points, 4.36679, 95.5597);
   TEST_POINT(points, 3.88638, 94.9449);
   TEST_POINT(points, 3.45536, 94.2946);
   TEST_POINT(points, 3.07636, 93.6127);
   TEST_POINT(points, 2.75167, 92.9032);
   TEST_POINT(points, 2.48327, 92.1706);
   TEST_POINT(points, 2.27281, 91.4194);
   TEST_POINT(points, 2.12156, 90.654);
   TEST_POINT(points, 2.03044, 89.8791);
   TEST_POINT(points, 2.0, 89.0995);
   TEST_POINT(points, 2.0, 27.2786);
   TEST_POINT(points, 2.03596, 26.007);
   TEST_POINT(points, 2.14374, 24.7394);
   TEST_POINT(points, 2.32299, 23.4799);
   TEST_POINT(points, 2.57313, 22.2326);
   TEST_POINT(points, 2.89336, 21.0014);
   TEST_POINT(points, 3.28267, 19.7903);
   TEST_POINT(points, 3.7398, 18.6031);
   TEST_POINT(points, 4.2633, 17.4437);
   TEST_POINT(points, 4.8515, 16.3157);
   TEST_POINT(points, 5.5025, 15.2227);
   TEST_POINT(points, 6.21424, 14.1683);
   TEST_POINT(points, 6.98443, 13.1558);
   TEST_POINT(points, 7.81062, 12.1884);
   TEST_POINT(points, 8.69016, 11.2693);
   TEST_POINT(points, 9.62023, 10.4013);
   TEST_POINT(points, 10.5979, 9.58735);
   TEST_POINT(points, 11.62, 8.82992);
   TEST_POINT(points, 12.6832, 8.13146);
   TEST_POINT(points, 13.7843, 7.49421);
   TEST_POINT(points, 14.9196, 6.9202);
   TEST_POINT(points, 19.0, 5.0);
   TEST_POINT(points, 19.0, 1.0);
   TEST_POINT(points, 18.0, 0.0);
	TRY_TEST(i, nPoints);

	//
	// Clone
	//
	CComPtr<IShape> clone;
	TRY_TEST(shape->Clone(nullptr), E_POINTER);
	TRY_TEST(shape->Clone(&clone), S_OK);

	CComQIPtr<INUDeckedIBeam> beamClone(clone);
	TRY_TEST(beamClone != 0, true);

	Float64 val;

	beamClone->get_W1(&val);
	TRY_TEST(IsEqual(val, 26.0), true);

	beamClone->get_W2(&val);
	TRY_TEST(IsEqual(val, 49.0), true);

	beamClone->get_W3(&val);
	TRY_TEST(IsEqual(val, 1.0), true);

	beamClone->get_W4(&val);
	TRY_TEST(IsEqual(val, 38.0), true);

	beamClone->get_D1(&val);
	TRY_TEST(IsEqual(val, 2.0), true);

	beamClone->get_D2(&val);
	TRY_TEST(IsEqual(val, 6.0), true);

	beamClone->get_D3(&val);
	TRY_TEST(IsEqual(val, 9.0), true);

	beamClone->get_D4(&val);
	TRY_TEST(IsEqual(val, 3.0), true);

	beamClone->get_D5(&val);
	TRY_TEST(IsEqual(val, 13.0), true);

	beamClone->get_D6(&val);
	TRY_TEST(IsEqual(val, 5.0), true);

	beamClone->get_H(&val);
	TRY_TEST(IsEqual(val, 108.0), true);

	beamClone->get_T(&val);
	TRY_TEST(IsEqual(val, 4.0), true);

	beamClone->get_R1(&val);
	TRY_TEST(IsEqual(val, 10.0), true);

	beamClone->get_R2(&val);
	TRY_TEST(IsEqual(val, 22.5), true);

	beamClone->get_C1(&val);
	TRY_TEST(IsEqual(val, 1.0), true);

	//
	// PointInShape
	//
	VARIANT_BOOL bPointInShape;
	CComPtr<IPoint2d> pnt;
	pnt.CoCreateInstance(CLSID_Point2d);
	pnt->Move(0.0, 0.5);

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
