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

// TestPCIDeckedIBeam.cpp: implementation of the CTestPCIDeckedIBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPCIDeckedIBeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPCIDeckedIBeam::CTestPCIDeckedIBeam()
{

}

CTestPCIDeckedIBeam::~CTestPCIDeckedIBeam()
{

}

void CTestPCIDeckedIBeam::Test()
{
   TestIPCIDeckedIBeam();
   TestIShape();
   TestIShape2();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestPCIDeckedIBeam::TestIPCIDeckedIBeam()
{
   CComPtr<IPCIDeckedIBeam> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_PCIDeckedIBeam), S_OK );

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

   TRY_TEST(beam->get_D7(nullptr), E_POINTER);
   TRY_TEST(beam->get_D7(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D8(nullptr), E_POINTER);
   TRY_TEST(beam->get_D8(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_D9(nullptr), E_POINTER);
   TRY_TEST(beam->get_D9(&val), S_OK);
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

   TRY_TEST(beam->get_W5(nullptr), E_POINTER);
   TRY_TEST(beam->get_W5(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_W6(nullptr), E_POINTER);
   TRY_TEST(beam->get_W6(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST( beam->get_R1(nullptr), E_POINTER );
   TRY_TEST( beam->get_R1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST(beam->get_R2(nullptr), E_POINTER);
   TRY_TEST(beam->get_R2(&val), S_OK);
   TRY_TEST(IsZero(val), true);

   TRY_TEST(beam->get_R3(nullptr), E_POINTER);
   TRY_TEST(beam->get_R3(&val), S_OK);
   TRY_TEST(IsZero(val), true);

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
   TRY_TEST( beam->put_D1(8), S_OK );
   beam->get_D1(&val);
   TRY_TEST( IsEqual(val,8.0), true );

   TRY_TEST( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D2(1), S_OK );
   beam->get_D2(&val);
   TRY_TEST( IsEqual(val,1.0), true );

   TRY_TEST( beam->put_D3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D3(0.5), S_OK );
   beam->get_D3(&val);
   TRY_TEST( IsEqual(val,0.5), true );

   TRY_TEST( beam->put_D4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D4(0.5), S_OK );
   beam->get_D4(&val);
   TRY_TEST( IsEqual(val,0.5), true );

   TRY_TEST( beam->put_D5(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D5(1), S_OK );
   beam->get_D5(&val);
   TRY_TEST( IsEqual(val,1.0), true );

   TRY_TEST(beam->put_D6(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D6(9), S_OK);
   beam->get_D6(&val);
   TRY_TEST(IsEqual(val, 9.0), true);

   TRY_TEST(beam->put_D7(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D7(3), S_OK);
   beam->get_D7(&val);
   TRY_TEST(IsEqual(val, 3.0), true);

   TRY_TEST(beam->put_D8(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D8(10), S_OK);
   beam->get_D8(&val);
   TRY_TEST(IsEqual(val, 10.0), true);

   TRY_TEST(beam->put_D9(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_D9(3.75), S_OK);
   beam->get_D9(&val);
   TRY_TEST(IsEqual(val, 3.75), true);

   TRY_TEST(beam->put_H(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_H(54), S_OK);
   beam->get_H(&val);
   TRY_TEST(IsEqual(val, 54.0), true);

   TRY_TEST(beam->put_T(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_T(4), S_OK);
   beam->get_T(&val);
   TRY_TEST(IsEqual(val, 4.0), true);

   TRY_TEST( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W1(26), S_OK );
   beam->get_W1(&val);
   TRY_TEST( IsEqual(val,26.0), true );

   TRY_TEST( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W2(45.5), S_OK );
   beam->get_W2(&val);
   TRY_TEST( IsEqual(val,45.5), true );

   TRY_TEST(beam->put_W3(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W3(7.5), S_OK);
   beam->get_W3(&val);
   TRY_TEST(IsEqual(val, 7.5), true);

   TRY_TEST(beam->put_W4(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W4(1), S_OK);
   beam->get_W4(&val);
   TRY_TEST(IsEqual(val, 1.0), true);

   TRY_TEST(beam->put_W5(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W5(5.5), S_OK);
   beam->get_W5(&val);
   TRY_TEST(IsEqual(val, 5.5), true);

   TRY_TEST(beam->put_W6(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_W6(38.375), S_OK);
   beam->get_W6(&val);
   TRY_TEST(IsEqual(val, 38.375), true);

   TRY_TEST( beam->put_R1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_R1(9), S_OK );
   beam->get_R1(&val);
   TRY_TEST( IsEqual(val,9.0), true );

   TRY_TEST(beam->put_R2(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_R2(12), S_OK);
   beam->get_R2(&val);
   TRY_TEST(IsEqual(val, 12.0), true);

   TRY_TEST(beam->put_R3(-1), GEOMETRY_E_DIMENSION);
   TRY_TEST(beam->put_R3(2), S_OK);
   beam->get_R3(&val);
   TRY_TEST(IsEqual(val, 2.0), true);

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
   TRY_TEST(IsEqual(val,54.), true );

   TRY_TEST(beam->get_TopFlangeWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_TopFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,106.), true );

   TRY_TEST(beam->get_BottomFlangeWidth(nullptr), E_POINTER );
   TRY_TEST(beam->get_BottomFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,38.375), true );

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

void CTestPCIDeckedIBeam::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_PCIDeckedIBeam), S_OK);

   CComQIPtr<IPCIDeckedIBeam> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Use some real dimensions
   beam->put_W1(26);
   beam->put_W2(45.5);
   beam->put_W3(7.5);
   beam->put_W4(1);
   beam->put_W5(5.5);
   beam->put_W6(38.375);
   beam->put_D1(8);
   beam->put_D2(1);
   beam->put_D3(0.5);
   beam->put_D4(0.5);
   beam->put_D5(1);
   beam->put_D6(9);
   beam->put_D7(3);
   beam->put_D8(10);
   beam->put_D9(3.75);
   beam->put_H(54);
   beam->put_T(4);
   beam->put_R1(9);
   beam->put_R2(12);
   beam->put_R3(2);
   beam->put_C1(1.0);

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

void CTestPCIDeckedIBeam::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_PCIDeckedIBeam ), S_OK );
   TRY_TEST( eInfo != nullptr, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPCIDeckedIBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}

void CTestPCIDeckedIBeam::TestIShape()
{
	CComPtr<IShape> shape;
	TRY_TEST(shape.CoCreateInstance(CLSID_PCIDeckedIBeam), S_OK);
	CComQIPtr<IPCIDeckedIBeam> beam(shape);

	// Use some real dimensions
   beam->put_W1(26);
   beam->put_W2(45.5);
   beam->put_W3(7.5);
   beam->put_W4(1);
   beam->put_W5(5.5);
   beam->put_W6(38.375);
   beam->put_D1(8);
   beam->put_D2(1);
   beam->put_D3(0.5);
   beam->put_D4(0.5);
   beam->put_D5(1);
   beam->put_D6(9);
   beam->put_D7(3);
   beam->put_D8(10);
   beam->put_D9(3.75);
   beam->put_H(54);
   beam->put_T(4);
   beam->put_R1(9);
   beam->put_R2(12);
   beam->put_R3(2);
   beam->put_C1(1.0);
	
	//
	// Bounding Box
	//
	Float64 val;
	CComPtr<IRect2d> box;
	TRY_TEST(shape->get_BoundingBox(nullptr), E_POINTER);
	TRY_TEST(shape->get_BoundingBox(&box), S_OK);

	box->get_Left(&val);
	TRY_TEST(IsEqual(val, -58.5), true);

	box->get_Right(&val);
	TRY_TEST(IsEqual(val, 58.5), true);

	box->get_Top(&val);
	TRY_TEST(IsEqual(val, 54.0), true);

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
	TRY_TEST(IsEqual(area, 941.66528114402706), true);
	TRY_TEST(IsEqual(ixx, 420903.30302683858), true);
	TRY_TEST(IsEqual(iyy, 403184.22410364990), true);
	TRY_TEST(IsEqual(ixy, 0.0, 0.0005), true);
	cg->get_X(&cgx);
	cg->get_Y(&cgy);
	TRY_TEST(IsEqual(cgx, 0.0), true);
	TRY_TEST(IsEqual(cgy, 32.324778419863591), true);
	CoordinateSystemType cst;
	props->get_CoordinateSystem(&cst);
	TRY_TEST(cst, csCentroidal);

	Float64 xleft, xright, ytop, ybottom;
	props->get_Xleft(&xleft);
	props->get_Xright(&xright);
	props->get_Ytop(&ytop);
	props->get_Ybottom(&ybottom);
	TRY_TEST(IsEqual(xleft, 58.5), true);
	TRY_TEST(IsEqual(xright, 58.5), true);
	TRY_TEST(IsEqual(ytop, 54.0 - cgy), true);
	TRY_TEST(IsEqual(ybottom, cgy), true);

	//
	// Perimeter
	//
	TRY_TEST(shape->get_Perimeter(nullptr), E_POINTER);
	TRY_TEST(shape->get_Perimeter(&val), S_OK);
	TRY_TEST(IsEqual(val, 403.95659655723534), true);

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

void CTestPCIDeckedIBeam::TestIShape2()
{
	CComPtr<IShape> shape;
	TRY_TEST(shape.CoCreateInstance(CLSID_PCIDeckedIBeam), S_OK);
	CComQIPtr<IPCIDeckedIBeam> beam(shape);

	// Use some real dimensions
	beam->put_W1(26);
	beam->put_W2(45.5);
	beam->put_W3(7.5);
	beam->put_W4(1);
   beam->put_W5(5.5);
   beam->put_W6(38.375);
   beam->put_D1(8);
	beam->put_D2(1);
	beam->put_D3(0.5);
	beam->put_D4(0.5);
	beam->put_D5(1);
	beam->put_D6(9);
   beam->put_D7(3);
   beam->put_D8(10);
   beam->put_D9(3.75);
	beam->put_H(54);
	beam->put_T(4);
	beam->put_R1(9);
	beam->put_R2(12);
   beam->put_R3(2);
	beam->put_C1(1.0);

	// 
	// PolyPoints
	//
	CComPtr<IPoint2dCollection> coll;
	TRY_TEST(shape->get_PolyPoints(nullptr), E_POINTER);
	TRY_TEST(shape->get_PolyPoints(&coll), S_OK);

	const IndexType nPoints = 151; // number of expected points
	IndexType cPoints;
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
   TEST_POINT(points, 0.000000, 0.000000);
   TEST_POINT(points, -18.187500, 0.000000);
   TEST_POINT(points, -19.187500, 1.000000);
   TEST_POINT(points, -19.187500, 2.349145);
   TEST_POINT(points, -19.183768, 2.471272);
   TEST_POINT(points, -19.172585, 2.592943);
   TEST_POINT(points, -19.153994, 2.713703);
   TEST_POINT(points, -19.128063, 2.833104);
   TEST_POINT(points, -19.094890, 2.950698);
   TEST_POINT(points, -19.054597, 3.066047);
   TEST_POINT(points, -19.007337, 3.178720);
   TEST_POINT(points, -18.953284, 3.288297);
   TEST_POINT(points, -18.892642, 3.394369);
   TEST_POINT(points, -18.825635, 3.496540);
   TEST_POINT(points, -18.752514, 3.594429);
   TEST_POINT(points, -18.673553, 3.687670);
   TEST_POINT(points, -18.589045, 3.775915);
   TEST_POINT(points, -18.499306, 3.858835);
   TEST_POINT(points, -18.404672, 3.936121);
   TEST_POINT(points, -18.305495, 4.007484);
   TEST_POINT(points, -18.202145, 4.072658);
   TEST_POINT(points, -18.095008, 4.131399);
   TEST_POINT(points, -17.984484, 4.183489);
   TEST_POINT(points, -17.870986, 4.228732);
   TEST_POINT(points, -9.899083, 7.127606);
   TEST_POINT(points, -9.218094, 7.399066);
   TEST_POINT(points, -8.554951, 7.711604);
   TEST_POINT(points, -7.912131, 8.064051);
   TEST_POINT(points, -7.292032, 8.455094);
   TEST_POINT(points, -6.696968, 8.883272);
   TEST_POINT(points, -6.129161, 9.346988);
   TEST_POINT(points, -5.590729, 9.844510);
   TEST_POINT(points, -5.083683, 10.373982);
   TEST_POINT(points, -4.609914, 10.933429);
   TEST_POINT(points, -4.171190, 11.520761);
   TEST_POINT(points, -3.769150, 12.133787);
   TEST_POINT(points, -3.405293, 12.770219);
   TEST_POINT(points, -3.080978, 13.427681);
   TEST_POINT(points, -2.797415, 14.103721);
   TEST_POINT(points, -2.555663, 14.795814);
   TEST_POINT(points, -2.356622, 15.501378);
   TEST_POINT(points, -2.201038, 16.217779);
   TEST_POINT(points, -2.089489, 16.942344);
   TEST_POINT(points, -2.022393, 17.672368);
   TEST_POINT(points, -2.000000, 18.405127);
   TEST_POINT(points, -2.000000, 36.152531);
   TEST_POINT(points, -2.027144, 36.850995);
   TEST_POINT(points, -2.108411, 37.545246);
   TEST_POINT(points, -2.243313, 38.231096);
   TEST_POINT(points, -2.431034, 38.904408);
   TEST_POINT(points, -2.670443, 39.561121);
   TEST_POINT(points, -2.960095, 40.197273);
   TEST_POINT(points, -3.298244, 40.809028);
   TEST_POINT(points, -3.682850, 41.392695);
   TEST_POINT(points, -4.111592, 41.944753);
   TEST_POINT(points, -4.581885, 42.461873);
   TEST_POINT(points, -5.090891, 42.940935);
   TEST_POINT(points, -5.635541, 43.379051);
   TEST_POINT(points, -6.212549, 43.773576);
   TEST_POINT(points, -6.818435, 44.122131);
   TEST_POINT(points, -7.449544, 44.422614);
   TEST_POINT(points, -8.102069, 44.673212);
   TEST_POINT(points, -8.772074, 44.872414);
   TEST_POINT(points, -9.455518, 45.019017);
   TEST_POINT(points, -10.148279, 45.112139);
   TEST_POINT(points, -10.846176, 45.151217);
   TEST_POINT(points, -13.000000, 51.000000);
   TEST_POINT(points, -49.000000, 52.000000);
   TEST_POINT(points, -51.000000, 46.000000);
   TEST_POINT(points, -58.500000, 46.000000);
   TEST_POINT(points, -58.500000, 47.000000);
   TEST_POINT(points, -53.000000, 47.500000);
   TEST_POINT(points, -53.000000, 52.500000);
   TEST_POINT(points, -54.000000, 53.000000);
   TEST_POINT(points, -54.000000, 54.000000);
   TEST_POINT(points, 0.000000, 54.000000);
   TEST_POINT(points, 54.000000, 54.000000);
   TEST_POINT(points, 54.000000, 53.000000);
   TEST_POINT(points, 53.000000, 52.500000);
   TEST_POINT(points, 53.000000, 47.500000);
   TEST_POINT(points, 58.500000, 47.000000);
   TEST_POINT(points, 58.500000, 46.000000);
   TEST_POINT(points, 51.000000, 46.000000);
   TEST_POINT(points, 49.000000, 52.000000);
   TEST_POINT(points, 13.000000, 51.000000);
   TEST_POINT(points, 10.846176, 45.151217);
   TEST_POINT(points, 10.148279, 45.112139);
   TEST_POINT(points, 9.455518, 45.019017);
   TEST_POINT(points, 8.772074, 44.872414);
   TEST_POINT(points, 8.102069, 44.673212);
   TEST_POINT(points, 7.449544, 44.422614);
   TEST_POINT(points, 6.818435, 44.122131);
   TEST_POINT(points, 6.212549, 43.773576);
   TEST_POINT(points, 5.635541, 43.379051);
   TEST_POINT(points, 5.090891, 42.940935);
   TEST_POINT(points, 4.581885, 42.461873);
   TEST_POINT(points, 4.111592, 41.944753);
   TEST_POINT(points, 3.682850, 41.392695);
   TEST_POINT(points, 3.298244, 40.809028);
   TEST_POINT(points, 2.960095, 40.197273);
   TEST_POINT(points, 2.670443, 39.561121);
   TEST_POINT(points, 2.431034, 38.904408);
   TEST_POINT(points, 2.243313, 38.231096);
   TEST_POINT(points, 2.108411, 37.545246);
   TEST_POINT(points, 2.027144, 36.850995);
   TEST_POINT(points, 2.000000, 36.152531);
   TEST_POINT(points, 2.000000, 18.405127);
   TEST_POINT(points, 2.022393, 17.672368);
   TEST_POINT(points, 2.089489, 16.942344);
   TEST_POINT(points, 2.201038, 16.217779);
   TEST_POINT(points, 2.356622, 15.501378);
   TEST_POINT(points, 2.555663, 14.795814);
   TEST_POINT(points, 2.797415, 14.103721);
   TEST_POINT(points, 3.080978, 13.427681);
   TEST_POINT(points, 3.405293, 12.770219);
   TEST_POINT(points, 3.769150, 12.133787);
   TEST_POINT(points, 4.171190, 11.520761);
   TEST_POINT(points, 4.609914, 10.933429);
   TEST_POINT(points, 5.083683, 10.373982);
   TEST_POINT(points, 5.590729, 9.844510);
   TEST_POINT(points, 6.129161, 9.346988);
   TEST_POINT(points, 6.696968, 8.883272);
   TEST_POINT(points, 7.292032, 8.455094);
   TEST_POINT(points, 7.912131, 8.064051);
   TEST_POINT(points, 8.554951, 7.711604);
   TEST_POINT(points, 9.218094, 7.399066);
   TEST_POINT(points, 9.899083, 7.127606);
   TEST_POINT(points, 17.870986, 4.228732);
   TEST_POINT(points, 17.984484, 4.183489);
   TEST_POINT(points, 18.095008, 4.131399);
   TEST_POINT(points, 18.202145, 4.072658);
   TEST_POINT(points, 18.305495, 4.007484);
   TEST_POINT(points, 18.404672, 3.936121);
   TEST_POINT(points, 18.499306, 3.858835);
   TEST_POINT(points, 18.589045, 3.775915);
   TEST_POINT(points, 18.673553, 3.687670);
   TEST_POINT(points, 18.752514, 3.594429);
   TEST_POINT(points, 18.825635, 3.496540);
   TEST_POINT(points, 18.892642, 3.394369);
   TEST_POINT(points, 18.953284, 3.288297);
   TEST_POINT(points, 19.007337, 3.178720);
   TEST_POINT(points, 19.054597, 3.066047);
   TEST_POINT(points, 19.094890, 2.950698);
   TEST_POINT(points, 19.128063, 2.833104);
   TEST_POINT(points, 19.153994, 2.713703);
   TEST_POINT(points, 19.172585, 2.592943);
   TEST_POINT(points, 19.183768, 2.471272);
   TEST_POINT(points, 19.187500, 2.349145);
   TEST_POINT(points, 19.187500, 1.000000);
   TEST_POINT(points, 18.187500, 0.000000);
   TEST_POINT(points, 0.000000, 0.000000);

   TRY_TEST(i, nPoints);

	//
	// Clone
	//
	CComPtr<IShape> clone;
	TRY_TEST(shape->Clone(nullptr), E_POINTER);
	TRY_TEST(shape->Clone(&clone), S_OK);

	CComQIPtr<IPCIDeckedIBeam> beamClone(clone);
	TRY_TEST(beamClone != nullptr, true);

	Float64 val;

	beamClone->get_W1(&val);
	TRY_TEST(IsEqual(val, 26.0), true);

	beamClone->get_W2(&val);
	TRY_TEST(IsEqual(val, 45.5), true);

	beamClone->get_W3(&val);
	TRY_TEST(IsEqual(val, 7.5), true);

	beamClone->get_W4(&val);
	TRY_TEST(IsEqual(val, 1.0), true);

   beamClone->get_W5(&val);
   TRY_TEST(IsEqual(val, 5.5), true);

   beamClone->get_W6(&val);
   TRY_TEST(IsEqual(val, 38.375), true);

	beamClone->get_D1(&val);
	TRY_TEST(IsEqual(val, 8.0), true);

	beamClone->get_D2(&val);
	TRY_TEST(IsEqual(val, 1.0), true);

	beamClone->get_D3(&val);
	TRY_TEST(IsEqual(val, 0.5), true);

	beamClone->get_D4(&val);
	TRY_TEST(IsEqual(val, 0.5), true);

	beamClone->get_D5(&val);
	TRY_TEST(IsEqual(val, 1.0), true);

	beamClone->get_D6(&val);
	TRY_TEST(IsEqual(val, 9.0), true);

   beamClone->get_D7(&val);
   TRY_TEST(IsEqual(val, 3.0), true);

   beamClone->get_D8(&val);
   TRY_TEST(IsEqual(val, 10.0), true);

   beamClone->get_D9(&val);
   TRY_TEST(IsEqual(val, 3.75), true);

	beamClone->get_H(&val);
	TRY_TEST(IsEqual(val, 54.0), true);

	beamClone->get_T(&val);
	TRY_TEST(IsEqual(val, 4.0), true);

	beamClone->get_R1(&val);
	TRY_TEST(IsEqual(val, 9.0), true);

   beamClone->get_R2(&val);
   TRY_TEST(IsEqual(val, 12.0), true);

   beamClone->get_R3(&val);
   TRY_TEST(IsEqual(val, 2.0), true);

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
