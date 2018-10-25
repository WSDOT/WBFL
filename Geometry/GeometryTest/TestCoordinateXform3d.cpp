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

// TestCoordinateXform3d.cpp: implementation of the CTestCoordinateXform3d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCoordinateXform3d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCoordinateXform3d::CTestCoordinateXform3d()
{

}

CTestCoordinateXform3d::~CTestCoordinateXform3d()
{

}

void CTestCoordinateXform3d::Test()
{
   const Float64 tolerance = 1e-04;

   CComPtr<ICoordinateXform3d> pXform;
   TRY_TEST( pXform.CoCreateInstance( CLSID_CoordinateXform3d ), S_OK );

   CComPtr<IPoint3d> origin;
   origin.CoCreateInstance( CLSID_Point3d );
   origin->put_X(5);
   origin->put_Y(5);
   origin->put_Z(5);

   TRY_TEST( pXform->putref_NewOrigin(nullptr), E_INVALIDARG );
   TRY_TEST( pXform->putref_NewOrigin(origin), S_OK );

   CComPtr<IPoint3d> o;
   TRY_TEST( pXform->get_NewOrigin(nullptr), E_POINTER );
   TRY_TEST( pXform->get_NewOrigin(&o), S_OK );
   Float64 x,y,z;
   o->get_X(&x);
   o->get_Y(&y);
   o->get_Z(&z);
   TRY_TEST(IsEqual(x,5.0, tolerance),true);
   TRY_TEST(IsEqual(y,5.0, tolerance),true);
   TRY_TEST(IsEqual(z,5.0, tolerance),true);

   CComPtr<IVector3d> rv; // rotation vector
   rv.CoCreateInstance( CLSID_Vector3d );
   rv->put_X(5);
   rv->put_Y(5);
   rv->put_Z(5);

   TRY_TEST( pXform->putref_RotationVector(nullptr), E_INVALIDARG );
   TRY_TEST( pXform->putref_RotationVector(rv), S_OK );

   CComPtr<IVector3d> vec;
   TRY_TEST( pXform->get_RotationVector(nullptr), E_POINTER );
   TRY_TEST( pXform->get_RotationVector(&vec), S_OK );
   vec->get_X(&x);
   vec->get_Y(&y);
   vec->get_Z(&z);
   TRY_TEST(IsEqual(x,5.0, tolerance),true);
   TRY_TEST(IsEqual(y,5.0, tolerance),true);
   TRY_TEST(IsEqual(z,5.0, tolerance),true);

   TRY_TEST( pXform->put_RotationAngle(M_PI/4), S_OK );
   Float64 angle;
   TRY_TEST( pXform->get_RotationAngle(nullptr), E_POINTER );
   TRY_TEST( pXform->get_RotationAngle(&angle), S_OK );
   TRY_TEST( IsEqual(angle,M_PI/4, tolerance), true );

   // Setup for some real transformations (XY Plane)
   origin->put_X(7);
   origin->put_Y(-4);
   origin->put_Z(0);

   rv->put_X(0);
   rv->put_Y(0);
   rv->put_Z(0);

   pXform->put_RotationAngle(27*M_PI/180);

   CComPtr<IPoint3d> pnt;
   TRY_TEST( pXform->Xform(nullptr, xfrmOldToNew), E_INVALIDARG );
   TRY_TEST( pXform->Xform(&pnt.p, xfrmOldToNew), E_INVALIDARG );

   pnt.CoCreateInstance( CLSID_Point3d );
   pnt->Move( -9,7,0 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), GEOMETRY_E_ZEROMAGNITUDE ); // Rotation Vector is zero
   rv->put_X(0);
   rv->put_Y(0);
   rv->put_Z(1);

   CComPtr<IPoint3d> result;
   TRY_TEST( pXform->XformEx( nullptr, xfrmOldToNew, &result ), E_INVALIDARG );
   TRY_TEST( pXform->XformEx( pnt, xfrmOldToNew, nullptr ), E_POINTER );
   TRY_TEST( pXform->XformEx( pnt, xfrmOldToNew, &result ), S_OK );
   result->get_X(&x);
   result->get_Y(&y);
   result->get_Z(&z);
   TRY_TEST( IsEqual(x,-9.2622, tolerance), true );
   TRY_TEST( IsEqual(y,17.0649, tolerance), true );
   TRY_TEST( IsEqual(z, 0., tolerance), true );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,-9., tolerance), true );
   TRY_TEST( IsEqual(y, 7., tolerance), true );
   TRY_TEST( IsEqual(z, 0., tolerance), true );

   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );

   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,-9.2622, tolerance), true );
   TRY_TEST( IsEqual(y,17.0649, tolerance), true );
   TRY_TEST( IsEqual(z, 0.0000, tolerance), true );

   pnt->Move( -9.2622, 17.0649, 0.0000 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,-9., tolerance), true );
   TRY_TEST( IsEqual(y, 7., tolerance), true );
   TRY_TEST( IsEqual(z, 0.0000, tolerance), true );

   pnt->Move( -5,-4,0 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,-10.6921, tolerance), true );
   TRY_TEST( IsEqual(y, 5.4479, tolerance), true );
   TRY_TEST( IsEqual(z, 0.0000, tolerance), true );

   pnt->Move( -10.6921, 5.4479, 0.000 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,-5., tolerance), true );
   TRY_TEST( IsEqual(y,-4., tolerance), true );
   TRY_TEST( IsEqual(z, 0., tolerance), true );

   pnt->Move( 2.7, -3.6, 0.0 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,11.0401, tolerance), true );
   TRY_TEST( IsEqual(y,-5.9818, tolerance), true );
   TRY_TEST( IsEqual(z, 0., tolerance), true );

   pnt->Move( 11.0401, -5.9818, 0.0000 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x, 2.7,0.1), true );
   TRY_TEST( IsEqual(y,-3.6,0.1), true );
   TRY_TEST( IsEqual(z, 0.), true );

   // Test XZ Plane
   origin->put_X(7);
   origin->put_Y(0);
   origin->put_Z(-4);

   rv->put_X(0);
   rv->put_Y(-1);
   rv->put_Z(0);

   pnt->Move( -9,0,7 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );

   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,-9.2622, tolerance), true );
   TRY_TEST( IsEqual(y, 0.0000, tolerance), true );
   TRY_TEST( IsEqual(z,17.0649, tolerance), true );

   pnt->Move( -9.2622, 0.0000, 17.0649 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x,-9., tolerance), true );
   TRY_TEST( IsEqual(y, 0., tolerance), true );
   TRY_TEST( IsEqual(z, 7., tolerance), true );

   // Test YZ Plane
   origin->put_X(0);
   origin->put_Y(7);
   origin->put_Z(-4);

   rv->put_X(1);
   rv->put_Y(0);
   rv->put_Z(0);

   pnt->Move( 0,-9,7 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );

   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x, 0.0000, tolerance), true );
   TRY_TEST( IsEqual(y,-9.2622, tolerance), true );
   TRY_TEST( IsEqual(z,17.0649, tolerance), true );

   pnt->Move( 0.0000, -9.2622, 17.0649 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x, 0., tolerance), true );
   TRY_TEST( IsEqual(y,-9., tolerance), true );
   TRY_TEST( IsEqual(z, 7., tolerance), true );

   // 3D Transformation
   origin->put_X(2.45);
   origin->put_Y(4.00);
   origin->put_Z(4.25);
   rv->put_X(0);
   rv->put_Y(-1);
   rv->put_Z(-1);
   pXform->put_RotationAngle(62.5*M_PI/180);

   pnt->Move(3.9,2.1,7.0);
   pXform->Xform( &pnt.p, xfrmOldToNew );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x, 3.5861, tolerance), true );
   TRY_TEST( IsEqual(y, 0.2609, tolerance), true );
   TRY_TEST( IsEqual(z, 0.5891, tolerance), true );

   pnt->Move(3.5861,0.2609,0.5891);
   pXform->Xform( &pnt.p, xfrmNewToOld );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x, 3.9, 0.1), true );
   TRY_TEST( IsEqual(y, 2.1, 0.1), true );
   TRY_TEST( IsEqual(z, 7.0, 0.1), true );

   pnt->Move(1,1,1);
   pXform->Xform( &pnt.p, xfrmNewToOld );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x, 2.9117, tolerance), true );
   TRY_TEST( IsEqual(y, 4.3728, tolerance), true );
   TRY_TEST( IsEqual(z, 5.8772, tolerance), true );

   pnt->Move(2.9117,4.3728,5.8772);
   pXform->Xform( &pnt.p, xfrmOldToNew );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   pnt->get_Z(&z);
   TRY_TEST( IsEqual(x, 1.0, 0.1), true );
   TRY_TEST( IsEqual(y, 1.0, 0.1), true );
   TRY_TEST( IsEqual(z, 1.0, 0.1), true );

   TestISupportErrorInfo();
}

void CTestCoordinateXform3d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_CoordinateXform3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICoordinateXform3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

}
