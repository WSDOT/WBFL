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

// TestCoordinateXform2d.cpp: implementation of the CTestCoordinateXform2d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCoordinateXform2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCoordinateXform2d::CTestCoordinateXform2d()
{

}

CTestCoordinateXform2d::~CTestCoordinateXform2d()
{

}

void CTestCoordinateXform2d::Test()
{
   const Float64 tolerance = 1.0e-04;

   CComPtr<ICoordinateXform2d> pXform;
   TRY_TEST( pXform.CoCreateInstance( CLSID_CoordinateXform2d ), S_OK );

   CComPtr<IPoint2d> origin;
   origin.CoCreateInstance( CLSID_Point2d );
   origin->put_X(5);
   origin->put_Y(5);

   TRY_TEST( pXform->put_NewOrigin(nullptr), E_INVALIDARG );
   TRY_TEST( pXform->put_NewOrigin(origin), S_OK );

   CComPtr<IPoint2d> o;
   TRY_TEST( pXform->get_NewOrigin(nullptr), E_POINTER );
   TRY_TEST( pXform->get_NewOrigin(&o), S_OK );
   Float64 x,y;
   o->get_X(&x);
   o->get_Y(&y);
   TRY_TEST(IsEqual(x,5.0),true);
   TRY_TEST(IsEqual(y,5.0),true);

   TRY_TEST( pXform->put_RotationAngle(M_PI/4), S_OK );
   Float64 angle;
   TRY_TEST( pXform->get_RotationAngle(nullptr), E_POINTER );
   TRY_TEST( pXform->get_RotationAngle(&angle), S_OK );
   TRY_TEST( IsEqual(angle,M_PI/4), true );

   origin->put_X(7);
   origin->put_Y(-4);
   pXform->put_NewOrigin(origin);
   pXform->put_RotationAngle(27*M_PI/180);

   CComPtr<IPoint2d> pnt;
   TRY_TEST( pXform->Xform(nullptr, xfrmOldToNew), E_INVALIDARG );
   TRY_TEST( pXform->Xform(&pnt.p, xfrmOldToNew), E_INVALIDARG );

   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move( -9,7 );

   CComPtr<IPoint2d> result;
   TRY_TEST( pXform->XformEx( nullptr, xfrmOldToNew, &result ), E_INVALIDARG );
   TRY_TEST( pXform->XformEx( pnt, xfrmOldToNew, nullptr ), E_POINTER );
   TRY_TEST( pXform->XformEx( pnt, xfrmOldToNew, &result ), S_OK );
   result->get_X(&x);
   result->get_Y(&y);
   TRY_TEST( IsEqual(x,-9.2622, tolerance), true );
   TRY_TEST( IsEqual(y,17.0649, tolerance), true );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,-9., tolerance), true );
   TRY_TEST( IsEqual(y, 7., tolerance), true );

   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,-9.26221, tolerance), true );
   TRY_TEST( IsEqual(y,17.06492, tolerance), true );


   pnt->Move( -9.2622, 17.0649 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,-9., tolerance), true );
   TRY_TEST( IsEqual(y, 7., tolerance), true );

   pnt->Move( -5,-4 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,-10.6921, tolerance), true );
   TRY_TEST( IsEqual(y, 5.4479, tolerance), true );

   pnt->Move( -10.6921, 5.4479 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,-5., tolerance), true );
   TRY_TEST( IsEqual(y,-4., tolerance), true );

   pnt->Move( 2.7, -3.6 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x,11.0401, tolerance), true );
   TRY_TEST( IsEqual(y,-5.9818, tolerance), true );

   pnt->Move( 11.0401, -5.9818 );
   TRY_TEST( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST( IsEqual(x, 2.7,0.1), true );
   TRY_TEST( IsEqual(y,-3.6,0.1), true );

   TestISupportErrorInfo();
}

void CTestCoordinateXform2d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_CoordinateXform2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICoordinateXform2d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
