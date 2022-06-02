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
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPCIDeckedIBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}


#define TEST_POINT(_point_,_x_,_y_) _point_[i]->get_X(&x); _point_[i++]->get_Y(&y); TRY_TEST(IsEqual(x,_x_,0.0001),true); TRY_TEST(IsEqual(y,_y_,0.0001),true);

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

	const CollectionIndexType nPoints = 148; // number of expected points
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
	//for (int j = 0; j < cPoints; j++)
	//{
	//	CComPtr<IPoint2d> pnt;
	//	points[j]->Location(&x, &y);
	//	std::cout << x << ", " << y << std::endl;
	//}

   TEST_POINT(points, -18.1875, 0.0);
   TEST_POINT(points, -19.1875, 1.0);
   TEST_POINT(points, -19.1875, 2.34915);
   TEST_POINT(points, -19.1838, 2.47127);
   TEST_POINT(points, -19.1726, 2.59294);
   TEST_POINT(points, -19.154, 2.7137);
   TEST_POINT(points, -19.1281, 2.8331);
   TEST_POINT(points, -19.0949, 2.9507);
   TEST_POINT(points, -19.0546, 3.06605);
   TEST_POINT(points, -19.0073, 3.17872);
   TEST_POINT(points, -18.9533, 3.2883);
   TEST_POINT(points, -18.8926, 3.39437);
   TEST_POINT(points, -18.8256, 3.49654);
   TEST_POINT(points, -18.7525, 3.59443);
   TEST_POINT(points, -18.6736, 3.68767);
   TEST_POINT(points, -18.589, 3.77592);
   TEST_POINT(points, -18.4993, 3.85884);
   TEST_POINT(points, -18.4047, 3.93612);
   TEST_POINT(points, -18.3055, 4.00748);
   TEST_POINT(points, -18.2021, 4.07266);
   TEST_POINT(points, -18.095, 4.1314);
   TEST_POINT(points, -17.9845, 4.18349);
   TEST_POINT(points, -17.871, 4.22873);
   TEST_POINT(points, -9.89908, 7.12761);
   TEST_POINT(points, -9.21809, 7.39907);
   TEST_POINT(points, -8.55495, 7.7116);
   TEST_POINT(points, -7.91213, 8.06405);
   TEST_POINT(points, -7.29203, 8.45509);
   TEST_POINT(points, -6.69697, 8.88327);
   TEST_POINT(points, -6.12916, 9.34699);
   TEST_POINT(points, -5.59073, 9.84451);
   TEST_POINT(points, -5.08368, 10.374);
   TEST_POINT(points, -4.60991, 10.9334);
   TEST_POINT(points, -4.17119, 11.5208);
   TEST_POINT(points, -3.76915, 12.1338);
   TEST_POINT(points, -3.40529, 12.7702);
   TEST_POINT(points, -3.08098, 13.4277);
   TEST_POINT(points, -2.79742, 14.1037);
   TEST_POINT(points, -2.55566, 14.7958);
   TEST_POINT(points, -2.35662, 15.5014);
   TEST_POINT(points, -2.20104, 16.2178);
   TEST_POINT(points, -2.08949, 16.9423);
   TEST_POINT(points, -2.02239, 17.6724);
   TEST_POINT(points, -2.0, 18.4051);
   TEST_POINT(points, -2.0, 36.1525);
   TEST_POINT(points, -2.02714, 36.851);
   TEST_POINT(points, -2.10841, 37.5452);
   TEST_POINT(points, -2.24331, 38.2311);
   TEST_POINT(points, -2.43103, 38.9044);
   TEST_POINT(points, -2.67044, 39.5611);
   TEST_POINT(points, -2.9601, 40.1973);
   TEST_POINT(points, -3.29824, 40.809);
   TEST_POINT(points, -3.68285, 41.3927);
   TEST_POINT(points, -4.11159, 41.9448);
   TEST_POINT(points, -4.58188, 42.4619);
   TEST_POINT(points, -5.09089, 42.9409);
   TEST_POINT(points, -5.63554, 43.3791);
   TEST_POINT(points, -6.21255, 43.7736);
   TEST_POINT(points, -6.81844, 44.1221);
   TEST_POINT(points, -7.44954, 44.4226);
   TEST_POINT(points, -8.10207, 44.6732);
   TEST_POINT(points, -8.77207, 44.8724);
   TEST_POINT(points, -9.45552, 45.019);
   TEST_POINT(points, -10.1483, 45.1121);
   TEST_POINT(points, -10.8462, 45.1512);
   TEST_POINT(points, -13.0, 51.0);
   TEST_POINT(points, -49.0, 52.0);
   TEST_POINT(points, -51.0, 46.0);
   TEST_POINT(points, -58.5, 46.0);
   TEST_POINT(points, -58.5, 47.0);
   TEST_POINT(points, -53.0, 47.5);
   TEST_POINT(points, -53.0, 52.5);
   TEST_POINT(points, -54.0, 53.0);
   TEST_POINT(points, -54.0, 54.0);
   TEST_POINT(points, 54.0, 54.0);
   TEST_POINT(points, 54.0, 53.0);
   TEST_POINT(points, 53.0, 52.5);
   TEST_POINT(points, 53.0, 47.5);
   TEST_POINT(points, 58.5, 47.0);
   TEST_POINT(points, 58.5, 46.0);
   TEST_POINT(points, 51.0, 46.0);
   TEST_POINT(points, 49.0, 52.0);
   TEST_POINT(points, 13.0, 51.0);
   TEST_POINT(points, 10.8462, 45.1512);
   TEST_POINT(points, 10.1483, 45.1121);
   TEST_POINT(points, 9.45552, 45.019);
   TEST_POINT(points, 8.77207, 44.8724);
   TEST_POINT(points, 8.10207, 44.6732);
   TEST_POINT(points, 7.44954, 44.4226);
   TEST_POINT(points, 6.81844, 44.1221);
   TEST_POINT(points, 6.21255, 43.7736);
   TEST_POINT(points, 5.63554, 43.3791);
   TEST_POINT(points, 5.09089, 42.9409);
   TEST_POINT(points, 4.58188, 42.4619);
   TEST_POINT(points, 4.11159, 41.9448);
   TEST_POINT(points, 3.68285, 41.3927);
   TEST_POINT(points, 3.29824, 40.809);
   TEST_POINT(points, 2.9601, 40.1973);
   TEST_POINT(points, 2.67044, 39.5611);
   TEST_POINT(points, 2.43103, 38.9044);
   TEST_POINT(points, 2.24331, 38.2311);
   TEST_POINT(points, 2.10841, 37.5452);
   TEST_POINT(points, 2.02714, 36.851);
   TEST_POINT(points, 2.0, 36.1525);
   TEST_POINT(points, 2.0, 18.4051);
   TEST_POINT(points, 2.02239, 17.6724);
   TEST_POINT(points, 2.08949, 16.9423);
   TEST_POINT(points, 2.20104, 16.2178);
   TEST_POINT(points, 2.35662, 15.5014);
   TEST_POINT(points, 2.55566, 14.7958);
   TEST_POINT(points, 2.79742, 14.1037);
   TEST_POINT(points, 3.08098, 13.4277);
   TEST_POINT(points, 3.40529, 12.7702);
   TEST_POINT(points, 3.76915, 12.1338);
   TEST_POINT(points, 4.17119, 11.5208);
   TEST_POINT(points, 4.60991, 10.9334);
   TEST_POINT(points, 5.08368, 10.374);
   TEST_POINT(points, 5.59073, 9.84451);
   TEST_POINT(points, 6.12916, 9.34699);
   TEST_POINT(points, 6.69697, 8.88327);
   TEST_POINT(points, 7.29203, 8.45509);
   TEST_POINT(points, 7.91213, 8.06405);
   TEST_POINT(points, 8.55495, 7.7116);
   TEST_POINT(points, 9.21809, 7.39907);
   TEST_POINT(points, 9.89908, 7.12761);
   TEST_POINT(points, 17.871, 4.22873);
   TEST_POINT(points, 17.9845, 4.18349);
   TEST_POINT(points, 18.095, 4.1314);
   TEST_POINT(points, 18.2021, 4.07266);
   TEST_POINT(points, 18.3055, 4.00748);
   TEST_POINT(points, 18.4047, 3.93612);
   TEST_POINT(points, 18.4993, 3.85884);
   TEST_POINT(points, 18.589, 3.77592);
   TEST_POINT(points, 18.6736, 3.68767);
   TEST_POINT(points, 18.7525, 3.59443);
   TEST_POINT(points, 18.8256, 3.49654);
   TEST_POINT(points, 18.8926, 3.39437);
   TEST_POINT(points, 18.9533, 3.2883);
   TEST_POINT(points, 19.0073, 3.17872);
   TEST_POINT(points, 19.0546, 3.06605);
   TEST_POINT(points, 19.0949, 2.9507);
   TEST_POINT(points, 19.1281, 2.8331);
   TEST_POINT(points, 19.154, 2.7137);
   TEST_POINT(points, 19.1726, 2.59294);
   TEST_POINT(points, 19.1838, 2.47127);
   TEST_POINT(points, 19.1875, 2.34915);
   TEST_POINT(points, 19.1875, 1.0);
   TEST_POINT(points, 18.1875, 0.0);

   TRY_TEST(i, nPoints);

	//
	// Clone
	//
	CComPtr<IShape> clone;
	TRY_TEST(shape->Clone(nullptr), E_POINTER);
	TRY_TEST(shape->Clone(&clone), S_OK);

	CComQIPtr<IPCIDeckedIBeam> beamClone(clone);
	TRY_TEST(beamClone != 0, true);

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
