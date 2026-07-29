///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
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

// TestElasticProperties.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestElasticProperties.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestElasticProperties)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IElasticProperties> props;
         ASSERT_EQ( props.CoCreateInstance( CLSID_ElasticProperties ), S_OK );

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
         ASSERT_EQ( props->put_EA(area), S_OK );
         ASSERT_EQ( props->get_EA(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EA(&val), S_OK );
         ASSERT_EQ( IsEqual(val,area), true );

         ASSERT_EQ( props->put_EIxx(ixx), S_OK );
         ASSERT_EQ( props->get_EIxx(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EIxx(&val), S_OK );
         ASSERT_EQ( IsEqual(val,ixx), true );

         ASSERT_EQ( props->put_EIyy(iyy), S_OK );
         ASSERT_EQ( props->get_EIyy(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EIyy(&val), S_OK );
         ASSERT_EQ( IsEqual(val,iyy), true );

         ASSERT_EQ( props->put_EIxy(ixy), S_OK );
         ASSERT_EQ( props->get_EIxy(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EIxy(&val), S_OK );
         ASSERT_EQ( IsEqual(val,ixy), true );

         ASSERT_EQ( props->put_Centroid(nullptr), E_INVALIDARG );
         ASSERT_EQ( props->put_Centroid(cg), S_OK );
         ASSERT_EQ( props->get_Centroid(nullptr), E_POINTER );
         ASSERT_EQ( props->get_Centroid(&pntVal), S_OK );
         cg->Offset(10,10); // IShapeProperties does not have reference to the CG point
                            // Move the original cg point.
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,cgx), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,cgy), true );
         cg->Offset(-10,-10); // put the original cg point back to where it was.

         ASSERT_EQ( props->put_Xleft(-1), E_INVALIDARG);
         ASSERT_EQ( props->put_Xleft(left), S_OK );
         ASSERT_EQ( props->get_Xleft(nullptr), E_POINTER );
         ASSERT_EQ( props->get_Xleft(&val), S_OK );
         ASSERT_EQ( IsEqual(val,left), true );

         ASSERT_EQ( props->put_Xright(-1), E_INVALIDARG);
         ASSERT_EQ( props->put_Xright(right), S_OK );
         ASSERT_EQ( props->get_Xright(nullptr), E_POINTER );
         ASSERT_EQ( props->get_Xright(&val), S_OK );
         ASSERT_EQ( IsEqual(val,right), true );

         ASSERT_EQ( props->put_Ytop(-1), E_INVALIDARG);
         ASSERT_EQ( props->put_Ytop(top), S_OK );
         ASSERT_EQ( props->get_Ytop(nullptr), E_POINTER );
         ASSERT_EQ( props->get_Ytop(&val), S_OK );
         ASSERT_EQ( IsEqual(val,top), true );

         ASSERT_EQ( props->put_Ybottom(-1), E_INVALIDARG);
         ASSERT_EQ( props->put_Ybottom(bottom), S_OK );
         ASSERT_EQ( props->get_Ybottom(nullptr), E_POINTER );
         ASSERT_EQ( props->get_Ybottom(&val), S_OK );
         ASSERT_EQ( IsEqual(val,bottom), true );

         // Default coordinate system is centroidal
         ASSERT_EQ( props->get_CoordinateSystem(nullptr), E_POINTER );
         ASSERT_EQ( props->get_CoordinateSystem(&cstVal), S_OK );
         ASSERT_EQ( cstVal, csCentroidal );

         // Default orientation is 0.0
         ASSERT_EQ( props->get_Orientation(nullptr), E_POINTER );
         ASSERT_EQ( props->get_Orientation(&val), S_OK );
         ASSERT_EQ( IsZero(val), true );

         // Default origin is (0.0,0.0)
         ASSERT_EQ( props->get_Origin(nullptr), E_POINTER );
         pntVal.Release();
         ASSERT_EQ( props->get_Origin(&pntVal), S_OK );
         pntVal->get_X(&val);
         ASSERT_EQ( IsZero(val), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsZero(val), true );

         //
         // Principle Direction
         //
         ASSERT_EQ( props->get_PrincipleDirection(nullptr), E_POINTER );
         ASSERT_EQ( props->get_PrincipleDirection(&val), S_OK );
         ASSERT_EQ( IsEqual( val, 0.336452), true );

         //
         // Principle Values
         //
         ASSERT_EQ( props->get_EI11(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EI11(&val), S_OK );
         ASSERT_EQ( IsEqual(val,30.20176), true );

         ASSERT_EQ( props->get_EI22(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EI22(&val), S_OK );
         ASSERT_EQ( IsEqual(val,7.248239), true );

         ASSERT_EQ( props->get_EI12Min(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EI12Min(&val), S_OK );
         ASSERT_EQ( IsEqual(val,-11.47676), true );

         ASSERT_EQ( props->get_EI12Max(nullptr), E_POINTER );
         ASSERT_EQ( props->get_EI12Max(&val), S_OK );
         ASSERT_EQ( IsEqual(val,11.47676), true );

         //
         // Move the origin
         //
         pntVal.Release();
         pntVal.CoCreateInstance( CLSID_Point2d );
         pntVal->put_X(10);
         pntVal->put_Y(20);
         ASSERT_EQ( props->put_Origin(nullptr), E_INVALIDARG );
         ASSERT_EQ( props->put_Origin(pntVal), S_OK );

         props->get_CoordinateSystem(&cstVal);
         ASSERT_EQ( cstVal, csUser );

         ASSERT_EQ( props->get_Origin(nullptr), E_POINTER );
         pntVal.Release();
         ASSERT_EQ( props->get_Origin(&pntVal), S_OK );
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,10.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,20.0), true );

         pntVal.Release();
         props->get_Centroid( &pntVal );
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,cgx-10.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,cgy-20.0), true );

         props->get_EIxx(&val);
         ASSERT_EQ( IsEqual(val,ixx + area*(cgy-20)*(cgy-20)), true );

         props->get_EIyy(&val);
         ASSERT_EQ( IsEqual(val,iyy + area*(cgx-10)*(cgx-10)), true );

         props->get_EIxy(&val);
         ASSERT_EQ( IsEqual(val,ixy + area*(cgx-10)*(cgy-20)), true );

         // Put the origin back at (0,0)
         pntVal.Release();
         pntVal.CoCreateInstance( CLSID_Point2d );
         pntVal->put_X(0);
         pntVal->put_Y(0);
         props->put_Origin(pntVal);

         ASSERT_EQ( props->get_EA(&val), S_OK );
         ASSERT_EQ( IsEqual(val,area), true );

         ASSERT_EQ( props->get_EIxx(&val), S_OK );
         ASSERT_EQ( IsEqual(val,ixx + area*cgy*cgy), true );

         ASSERT_EQ( props->get_EIyy(&val), S_OK );
         ASSERT_EQ( IsEqual(val,iyy + area*cgx*cgx), true );

         ASSERT_EQ( props->get_EIxy(&val), S_OK );
         ASSERT_EQ( IsEqual(val,ixy + area*cgx*cgy), true );

         //
         // Test Orientation
         //

         ASSERT_EQ( props->put_Orientation( M_PI ), S_OK );
         ASSERT_EQ( props->get_Orientation(nullptr), E_POINTER );
         ASSERT_EQ( props->get_Orientation(&val), S_OK );
         ASSERT_EQ( IsEqual(val,M_PI), true );

         props->get_CoordinateSystem( &cstVal );
         ASSERT_EQ( cstVal, csUser );

         props->get_EIxx(&val);
         ASSERT_EQ( IsEqual(val,ixx+area*cgy*cgy), true );

         props->get_EIyy(&val);
         ASSERT_EQ( IsEqual(val,iyy+area*cgx*cgx), true );

         props->get_EIxy(&val);
         ASSERT_EQ( IsEqual(val,ixy+area*cgx*cgy), true );

         props->get_EA(&val);
         ASSERT_EQ( IsEqual(val,area), true );

         pntVal.Release();
         props->get_Centroid(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,-cgx), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,-cgy), true );

         //
         // Test CoordinateSystem property
         //

         // global
         ASSERT_EQ( props->put_CoordinateSystem(csGlobal), S_OK );
         props->get_CoordinateSystem( &cstVal );
         ASSERT_EQ( cstVal, csGlobal );

         props->get_EIxx(&val);
         ASSERT_EQ( IsEqual(val,ixx+area*cgy*cgy), true );

         props->get_EIyy(&val);
         ASSERT_EQ( IsEqual(val,iyy+area*cgx*cgx), true );

         props->get_EIxy(&val);
         ASSERT_EQ( IsEqual(val,ixy+area*cgx*cgy), true );

         props->get_EA(&val);
         ASSERT_EQ( IsEqual(val,area), true );

         props->get_Orientation(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );

         pntVal.Release();
         props->get_Centroid(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,cgx), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,cgy), true );

         pntVal.Release();
         props->get_Origin(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );

         // centroidal
         ASSERT_EQ( props->put_CoordinateSystem(csCentroidal), S_OK );
         props->get_CoordinateSystem( &cstVal );
         ASSERT_EQ( cstVal, csCentroidal );

         props->get_EIxx(&val);
         ASSERT_EQ( IsEqual(val,ixx), true );

         props->get_EIyy(&val);
         ASSERT_EQ( IsEqual(val,iyy), true );

         props->get_EIxy(&val);
         ASSERT_EQ( IsEqual(val,ixy), true );

         props->get_EA(&val);
         ASSERT_EQ( IsEqual(val,area), true );

         props->get_Orientation(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );

         pntVal.Release();
         props->get_Centroid(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,cgx), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,cgy), true );

         pntVal.Release();
         props->get_Origin(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,cgx), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,cgy), true );

         // principle
         ASSERT_EQ( props->put_CoordinateSystem(csPrinciple), S_OK );
         props->get_CoordinateSystem( &cstVal );
         ASSERT_EQ( cstVal, csPrinciple );

         props->get_EIxx(&val);
         ASSERT_EQ( IsEqual(val,30.20176), true );

         props->get_EIyy(&val);
         ASSERT_EQ( IsEqual(val,7.248239), true );

         props->get_EIxy(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );

         props->get_EA(&val);
         ASSERT_EQ( IsEqual(val,area), true );

         props->get_Orientation(&val);
         ASSERT_EQ( IsEqual(val, 0.336452), true );

         pntVal.Release();
         props->get_Centroid(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );

         pntVal.Release();
         props->get_Origin(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,cgx), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,cgy), true );

         // user
         ASSERT_EQ( props->put_CoordinateSystem(csUser), S_OK );
         props->get_CoordinateSystem( &cstVal );
         ASSERT_EQ( cstVal, csUser );

         props->get_EIxx(&val);
         ASSERT_EQ( IsEqual(val,30.20176), true );

         props->get_EIyy(&val);
         ASSERT_EQ( IsEqual(val,7.248239), true );

         props->get_EIxy(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );

         props->get_EA(&val);
         ASSERT_EQ( IsEqual(val,area), true );

         props->get_Orientation(&val);
         ASSERT_EQ( IsEqual(val, 0.336452), true );

         pntVal.Release();
         props->get_Centroid(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,0.0), true );

         pntVal.Release();
         props->get_Origin(&pntVal);
         pntVal->get_X(&val);
         ASSERT_EQ( IsEqual(val,cgx), true );
         pntVal->get_Y(&val);
         ASSERT_EQ( IsEqual(val,cgy), true );

         // Add two sets of elastic properties together
         CComPtr<IElasticProperties> prop1;
         ASSERT_EQ(prop1.CoCreateInstance(CLSID_ElasticProperties), S_OK);

         CComPtr<IElasticProperties> prop2;
         ASSERT_EQ(prop2.CoCreateInstance(CLSID_ElasticProperties), S_OK);

         // Initialize shape 1
         // Rectangle 5 wide x 10 high
         // Bottom Left at 5,15
         prop1->put_EA(50);
         prop1->put_EIxx(416.66667);
         prop1->put_EIyy(104.16667);
         prop1->put_EIxy(0);
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
         prop2->put_EA(10);
         prop2->put_EIxx(20.833333);
         prop2->put_EIyy(3.33333);
         prop2->put_EIxy(0);
         CComPtr<IPoint2d> cg2;
         cg2.CoCreateInstance(CLSID_Point2d);
         cg2->Move(21,7.5);
         prop2->put_Centroid(cg2);
         prop2->put_Xleft(1.0);
         prop2->put_Xright(1.0);
         prop2->put_Ytop(2.5);
         prop2->put_Ybottom(2.5);

         // Add the properties together
         ASSERT_EQ(prop1->AddProperties(nullptr),E_INVALIDARG);
         ASSERT_EQ(prop1->AddProperties(prop2),S_OK);

         // Transform to global coordinates for easier validation
         prop1->put_CoordinateSystem(csGlobal);

         prop1->get_EA(&area);
         ASSERT_EQ(IsEqual(area,60.),true);

         prop1->get_EIxx(&ixx);
         ASSERT_EQ(IsEqual(ixx,21000.),true);

         prop1->get_EIyy(&iyy);
         ASSERT_EQ(IsEqual(iyy,7330.),true);

         prop1->get_EIxy(&ixy);
         ASSERT_EQ(IsEqual(ixy,9075.),true);

         cg.Release();
         prop1->get_Centroid(&cg);
         Float64 cx,cy;
         cg->get_X(&cx);
         cg->get_Y(&cy);
         ASSERT_EQ(IsEqual(cx, 9.750000,0.01),  true);
         ASSERT_EQ(IsEqual(cy,17.916667,0.0001),true);

         Float64 l,r,t,b;
         prop1->get_Xleft(&l);
         prop1->get_Xright(&r);
         prop1->get_Ytop(&t);
         prop1->get_Ybottom(&b);
         ASSERT_EQ(IsEqual(l,4.75),true);
         ASSERT_EQ(IsEqual(r,12.25),true);
         ASSERT_EQ(IsEqual(t,7.083333333,0.0001),true);
         ASSERT_EQ(IsEqual(b,12.91666667,0.0001),true);

         // Add a shape with no area and make sure results stay the same
         CComPtr<IElasticProperties> prop3;
         prop3.CoCreateInstance(CLSID_ElasticProperties);

         // Add the properties together
         prop1->AddProperties(prop3);

         // Confirm nothing changed

         // Transform to global coordinates for easier validation
         prop1->put_CoordinateSystem(csGlobal);

         prop1->get_EA(&area);
         ASSERT_EQ(IsEqual(area,60.),true);

         prop1->get_EIxx(&ixx);
         ASSERT_EQ(IsEqual(ixx,21000.),true);

         prop1->get_EIyy(&iyy);
         ASSERT_EQ(IsEqual(iyy,7330.),true);

         prop1->get_EIxy(&ixy);
         ASSERT_EQ(IsEqual(ixy,9075.),true);

         cg.Release();
         prop1->get_Centroid(&cg);
         cg->get_X(&cx);
         cg->get_Y(&cy);
         ASSERT_EQ(IsEqual(cx, 9.750000,0.01),  true);
         ASSERT_EQ(IsEqual(cy,17.916667,0.0001),true);

         prop1->get_Xleft(&l);
         prop1->get_Xright(&r);
         prop1->get_Ytop(&t);
         prop1->get_Ybottom(&b);
         ASSERT_EQ(IsEqual(l,9.75),true);
         ASSERT_EQ(IsEqual(r,12.25),true);
         ASSERT_EQ(IsEqual(t,7.083333333,0.0001),true);
         ASSERT_EQ(IsEqual(b,17.91666667,0.0001),true);

         ///////////////////////////////////////
         // Test ISupportErrorInfo
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_ElasticProperties ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IElasticProperties ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         //////////////////////////////////////////////////////////////
         // Test IObjectSafety
         CComPtr<IObjectSafety> pObjSafety;
         ASSERT_EQ(pObjSafety.CoCreateInstance(CLSID_ElasticProperties), S_OK);
         DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
         DWORD dwSupportedOptions, dwEnabledOptions;
         pObjSafety->GetInterfaceSafetyOptions(IID_IElasticProperties,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
   }
};
} // namespace GeometryUnitTests