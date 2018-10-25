///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TestShapeProperties.cpp: implementation of the CTestShapeProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestShapeProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestShapeProperties::CTestShapeProperties()
{

}

CTestShapeProperties::~CTestShapeProperties()
{

}

void CTestShapeProperties::Test()
{
   CComPtr<IShapeProperties> props;
   TRY_TEST( props.CoCreateInstance( CLSID_ShapeProperties ), S_OK );

   // Properties of a L6x4x7/8
   Float64 area = 7.98;
   Float64 ixx  = 27.7;
   Float64 iyy  = 9.75;
   Float64 ixy  = 7.153;
   Float64 cgx  = 1.12;
   Float64 cgy  = 2.12;
   CComPtr<IPoint2d> cg;
   cg.CoCreateInstance( CLSID_Point2d );
   cg->put_X(cgx);
   cg->put_Y(cgy);
   Float64 left = 0;
   Float64 bottom = 0;
   Float64 right = 4.0;
   Float64 top = 6.0;
   CoordinateSystemType cst = csCentroidal;

   Float64 val;
   CComPtr<IPoint2d> pntVal;
   CoordinateSystemType cstVal;
   
   //
   // Test properties
   //
   TRY_TEST( props->put_Area(area), S_OK );
   TRY_TEST( props->get_Area(NULL), E_POINTER );
   TRY_TEST( props->get_Area(&val), S_OK );
   TRY_TEST( IsEqual(val,area), true );

   TRY_TEST( props->put_Ixx(ixx), S_OK );
   TRY_TEST( props->get_Ixx(NULL), E_POINTER );
   TRY_TEST( props->get_Ixx(&val), S_OK );
   TRY_TEST( IsEqual(val,ixx), true );

   TRY_TEST( props->put_Iyy(iyy), S_OK );
   TRY_TEST( props->get_Iyy(NULL), E_POINTER );
   TRY_TEST( props->get_Iyy(&val), S_OK );
   TRY_TEST( IsEqual(val,iyy), true );

   TRY_TEST( props->put_Ixy(ixy), S_OK );
   TRY_TEST( props->get_Ixy(NULL), E_POINTER );
   TRY_TEST( props->get_Ixy(&val), S_OK );
   TRY_TEST( IsEqual(val,ixy), true );

   TRY_TEST( props->put_Centroid(NULL), E_INVALIDARG );
   TRY_TEST( props->put_Centroid(cg), S_OK );
   TRY_TEST( props->get_Centroid(NULL), E_POINTER );
   TRY_TEST( props->get_Centroid(&pntVal), S_OK );
   cg->Offset(10,10); // IShapeProperties does not have reference to the CG point
                      // Move the original cg point.
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,cgx), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,cgy), true );
   cg->Offset(-10,-10); // put the original cg point back to where it was.

   TRY_TEST( props->put_Xleft(-1),   E_INVALIDARG);
   TRY_TEST( props->put_Xleft(left), S_OK );
   TRY_TEST( props->get_Xleft(NULL), E_POINTER );
   TRY_TEST( props->get_Xleft(&val), S_OK );
   TRY_TEST( IsEqual(val,left), true );

   TRY_TEST( props->put_Xright(-1),   E_INVALIDARG);
   TRY_TEST( props->put_Xright(right), S_OK );
   TRY_TEST( props->get_Xright(NULL), E_POINTER );
   TRY_TEST( props->get_Xright(&val), S_OK );
   TRY_TEST( IsEqual(val,right), true );

   TRY_TEST( props->put_Ytop(-1),   E_INVALIDARG);
   TRY_TEST( props->put_Ytop(top), S_OK );
   TRY_TEST( props->get_Ytop(NULL), E_POINTER );
   TRY_TEST( props->get_Ytop(&val), S_OK );
   TRY_TEST( IsEqual(val,top), true );

   TRY_TEST( props->put_Ybottom(-1),   E_INVALIDARG);
   TRY_TEST( props->put_Ybottom(bottom), S_OK );
   TRY_TEST( props->get_Ybottom(NULL), E_POINTER );
   TRY_TEST( props->get_Ybottom(&val), S_OK );
   TRY_TEST( IsEqual(val,bottom), true );

   // Default coordinate system is centroidal
   TRY_TEST( props->get_CoordinateSystem(NULL), E_POINTER );
   TRY_TEST( props->get_CoordinateSystem(&cstVal), S_OK );
   TRY_TEST( cstVal, csCentroidal );

   // Default orientation is 0.0
   TRY_TEST( props->get_Orientation(NULL), E_POINTER );
   TRY_TEST( props->get_Orientation(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   // Default origin is (0.0,0.0)
   TRY_TEST( props->get_Origin(NULL), E_POINTER );
   pntVal.Release();
   TRY_TEST( props->get_Origin(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   //
   // Principle Direction
   //
   TRY_TEST( props->get_PrincipleDirection(NULL), E_POINTER );
   TRY_TEST( props->get_PrincipleDirection(&val), S_OK );
   TRY_TEST( IsEqual( val, 0.336452), true );

   //
   // Principle Values
   //
   TRY_TEST( props->get_I11(NULL), E_POINTER );
   TRY_TEST( props->get_I11(&val), S_OK );
   TRY_TEST( IsEqual(val,30.20176), true );

   TRY_TEST( props->get_I22(NULL), E_POINTER );
   TRY_TEST( props->get_I22(&val), S_OK );
   TRY_TEST( IsEqual(val,7.248239), true );

   TRY_TEST( props->get_I12Min(NULL), E_POINTER );
   TRY_TEST( props->get_I12Min(&val), S_OK );
   TRY_TEST( IsEqual(val,-11.47676), true );

   TRY_TEST( props->get_I12Max(NULL), E_POINTER );
   TRY_TEST( props->get_I12Max(&val), S_OK );
   TRY_TEST( IsEqual(val,11.47676), true );

   //
   // Move the origin
   //
   pntVal.Release();
   pntVal.CoCreateInstance( CLSID_Point2d );
   pntVal->put_X(10);
   pntVal->put_Y(20);
   TRY_TEST( props->put_Origin(NULL), E_INVALIDARG );
   TRY_TEST( props->put_Origin(pntVal), S_OK );

   props->get_CoordinateSystem(&cstVal);
   TRY_TEST( cstVal, csUser );
   
   TRY_TEST( props->get_Origin(NULL), E_POINTER );
   pntVal.Release();
   TRY_TEST( props->get_Origin(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,10.0), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,20.0), true );

   pntVal.Release();
   props->get_Centroid( &pntVal );
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,cgx-10.0), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,cgy-20.0), true );

   props->get_Ixx(&val);
   TRY_TEST( IsEqual(val,ixx + area*(cgy-20)*(cgy-20)), true );

   props->get_Iyy(&val);
   TRY_TEST( IsEqual(val,iyy + area*(cgx-10)*(cgx-10)), true );

   props->get_Ixy(&val);
   TRY_TEST( IsEqual(val,ixy + area*(cgx-10)*(cgy-20)), true );

   // Put the origin back at (0,0)
   pntVal.Release();
   pntVal.CoCreateInstance( CLSID_Point2d );
   pntVal->put_X(0);
   pntVal->put_Y(0);
   props->put_Origin(pntVal);

   TRY_TEST( props->get_Area(&val), S_OK );
   TRY_TEST( IsEqual(val,area), true );

   TRY_TEST( props->get_Ixx(&val), S_OK );
   TRY_TEST( IsEqual(val,ixx + area*cgy*cgy), true );

   TRY_TEST( props->get_Iyy(&val), S_OK );
   TRY_TEST( IsEqual(val,iyy + area*cgx*cgx), true );

   TRY_TEST( props->get_Ixy(&val), S_OK );
   TRY_TEST( IsEqual(val,ixy + area*cgx*cgy), true );

   //
   // Test Orientation
   //

   TRY_TEST( props->put_Orientation( M_PI ), S_OK );
   TRY_TEST( props->get_Orientation(NULL), E_POINTER );
   TRY_TEST( props->get_Orientation(&val), S_OK );
   TRY_TEST( IsEqual(val,M_PI), true );

   props->get_CoordinateSystem( &cstVal );
   TRY_TEST( cstVal, csUser );

   props->get_Ixx(&val);
   TRY_TEST( IsEqual(val,ixx+area*cgy*cgy), true );

   props->get_Iyy(&val);
   TRY_TEST( IsEqual(val,iyy+area*cgx*cgx), true );

   props->get_Ixy(&val);
   TRY_TEST( IsEqual(val,ixy+area*cgx*cgy), true );

   props->get_Area(&val);
   TRY_TEST( IsEqual(val,area), true );

   pntVal.Release();
   props->get_Centroid(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,-cgx), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,-cgy), true );

   //
   // Test CoordinateSystem property
   //

   // global
   TRY_TEST( props->put_CoordinateSystem(csGlobal), S_OK );
   props->get_CoordinateSystem( &cstVal );
   TRY_TEST( cstVal, csGlobal );

   props->get_Ixx(&val);
   TRY_TEST( IsEqual(val,ixx+area*cgy*cgy), true );

   props->get_Iyy(&val);
   TRY_TEST( IsEqual(val,iyy+area*cgx*cgx), true );

   props->get_Ixy(&val);
   TRY_TEST( IsEqual(val,ixy+area*cgx*cgy), true );

   props->get_Area(&val);
   TRY_TEST( IsEqual(val,area), true );

   props->get_Orientation(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   pntVal.Release();
   props->get_Centroid(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,cgx), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,cgy), true );

   pntVal.Release();
   props->get_Origin(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   // centroidal
   TRY_TEST( props->put_CoordinateSystem(csCentroidal), S_OK );
   props->get_CoordinateSystem( &cstVal );
   TRY_TEST( cstVal, csCentroidal );

   props->get_Ixx(&val);
   TRY_TEST( IsEqual(val,ixx), true );

   props->get_Iyy(&val);
   TRY_TEST( IsEqual(val,iyy), true );

   props->get_Ixy(&val);
   TRY_TEST( IsEqual(val,ixy), true );

   props->get_Area(&val);
   TRY_TEST( IsEqual(val,area), true );

   props->get_Orientation(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   pntVal.Release();
   props->get_Centroid(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,cgx), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,cgy), true );

   pntVal.Release();
   props->get_Origin(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,cgx), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,cgy), true );

   // principle
   TRY_TEST( props->put_CoordinateSystem(csPrinciple), S_OK );
   props->get_CoordinateSystem( &cstVal );
   TRY_TEST( cstVal, csPrinciple );

   props->get_Ixx(&val);
   TRY_TEST( IsEqual(val,30.20176), true );

   props->get_Iyy(&val);
   TRY_TEST( IsEqual(val,7.248239), true );

   props->get_Ixy(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   props->get_Area(&val);
   TRY_TEST( IsEqual(val,area), true );

   props->get_Orientation(&val);
   TRY_TEST( IsEqual(val, 0.336452), true );

   pntVal.Release();
   props->get_Centroid(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   pntVal.Release();
   props->get_Origin(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,cgx), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,cgy), true );

   // user
   TRY_TEST( props->put_CoordinateSystem(csUser), S_OK );
   props->get_CoordinateSystem( &cstVal );
   TRY_TEST( cstVal, csUser );

   props->get_Ixx(&val);
   TRY_TEST( IsEqual(val,30.20176), true );

   props->get_Iyy(&val);
   TRY_TEST( IsEqual(val,7.248239), true );

   props->get_Ixy(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   props->get_Area(&val);
   TRY_TEST( IsEqual(val,area), true );

   props->get_Orientation(&val);
   TRY_TEST( IsEqual(val, 0.336452), true );

   pntVal.Release();
   props->get_Centroid(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   pntVal.Release();
   props->get_Origin(&pntVal);
   pntVal->get_X(&val);
   TRY_TEST( IsEqual(val,cgx), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsEqual(val,cgy), true );

   TestISupportErrorInfo();
   TestIShapePropertiesEx();
}

void CTestShapeProperties::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_ShapeProperties ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShapeProperties ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}

void CTestShapeProperties::TestIShapePropertiesEx()
{
   CComPtr<IShapeProperties> prop1;
   TRY_TEST(prop1.CoCreateInstance(CLSID_ShapeProperties), S_OK);

   CComPtr<IShapeProperties> prop2;
   TRY_TEST(prop2.CoCreateInstance(CLSID_ShapeProperties), S_OK);

   // Test query interface
   CComQIPtr<IShapeProperties> qitest(prop1);
   TRY_TEST( qitest != NULL, true );

   // Initialize shape 1
   // Rectangle 5 wide x 10 high
   // Bottom Left at 5,15
   prop1->put_Area(50);
   prop1->put_Ixx(416.66667);
   prop1->put_Iyy(104.16667);
   prop1->put_Ixy(0);
   CComPtr<IPoint2d> cg1;
   cg1.CoCreateInstance(CLSID_Point2d);
   cg1->Move(7.5,20);
   prop1->put_Centroid(cg1);
   prop1->put_Xleft(2.5);
   prop1->put_Xright(2.5);
   prop1->put_Ytop(5.0);
   prop1->put_Ybottom(5.0);

   // Initialize shape 2
   // Rectangle 2 wide x 5 high
   // Bottom left at 20,5
   prop2->put_Area(10);
   prop2->put_Ixx(20.833333);
   prop2->put_Iyy(3.33333);
   prop2->put_Ixy(0);
   CComPtr<IPoint2d> cg2;
   cg2.CoCreateInstance(CLSID_Point2d);
   cg2->Move(21,7.5);
   prop2->put_Centroid(cg2);
   prop2->put_Xleft(1.0);
   prop2->put_Xright(1.0);
   prop2->put_Ytop(2.5);
   prop2->put_Ybottom(2.5);

   // Add the properties together
   TRY_TEST(prop1->AddProperties(NULL),E_INVALIDARG);
   TRY_TEST(prop1->AddProperties(prop2),S_OK);

   // Transform to global coordinates for easier validation
   prop1->put_CoordinateSystem(csGlobal);
   Float64 area, ixx, iyy, ixy;

   prop1->get_Area(&area);
   TRY_TEST(IsEqual(area,60.),true);

   prop1->get_Ixx(&ixx);
   TRY_TEST(IsEqual(ixx,21000.),true);

   prop1->get_Iyy(&iyy);
   TRY_TEST(IsEqual(iyy,7330.),true);

   prop1->get_Ixy(&ixy);
   TRY_TEST(IsEqual(ixy,9075.),true);

   CComPtr<IPoint2d> cg;
   prop1->get_Centroid(&cg);
   Float64 cx,cy;
   cg->get_X(&cx);
   cg->get_Y(&cy);
   TRY_TEST(IsEqual(cx, 9.750000,0.01),  true);
   TRY_TEST(IsEqual(cy,17.916667,0.0001),true);

   Float64 l,r,t,b;
   prop1->get_Xleft(&l);
   prop1->get_Xright(&r);
   prop1->get_Ytop(&t);
   prop1->get_Ybottom(&b);
   TRY_TEST(IsEqual(l,4.75),true);
   TRY_TEST(IsEqual(r,12.25),true);
   TRY_TEST(IsEqual(t,7.083333333,0.0001),true);
   TRY_TEST(IsEqual(b,12.91666667,0.0001),true);

   // Add a shape with no area and make sure results stay the same
   // The xleft, xright, ytop, and ybottom values will be effected.
   CComPtr<IShapeProperties> prop3;
   prop3.CoCreateInstance(CLSID_ShapeProperties);

   // Add the properties together
   prop1->AddProperties(prop3);

   // Confirm nothing changed

   // Transform to global coordinates for easier validation
   prop1->put_CoordinateSystem(csGlobal);

   prop1->get_Area(&area);
   TRY_TEST(IsEqual(area,60.),true);

   prop1->get_Ixx(&ixx);
   TRY_TEST(IsEqual(ixx,21000.),true);

   prop1->get_Iyy(&iyy);
   TRY_TEST(IsEqual(iyy,7330.),true);

   prop1->get_Ixy(&ixy);
   TRY_TEST(IsEqual(ixy,9075.),true);

   cg.Release();
   prop1->get_Centroid(&cg);
   cg->get_X(&cx);
   cg->get_Y(&cy);
   TRY_TEST(IsEqual(cx, 9.750000,0.01),  true);
   TRY_TEST(IsEqual(cy,17.916667,0.0001),true);

   prop1->get_Xleft(&l);
   prop1->get_Xright(&r);
   prop1->get_Ytop(&t);
   prop1->get_Ybottom(&b);
   TRY_TEST(IsEqual(l,9.75),true);
   TRY_TEST(IsEqual(r,12.25),true);
   TRY_TEST(IsEqual(t,7.083333333,0.0001),true);
   TRY_TEST(IsEqual(b,17.91666667,0.0001),true);
}
