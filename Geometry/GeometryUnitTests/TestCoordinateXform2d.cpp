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

// TestCoordinateXform2d.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestCoordinateXform2d.cpp
// (legacy WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestCoordinateXform2d)
{
public:
   TEST_METHOD(BasicOperations)
   {
         const Float64 tolerance = 1.0e-04;

         CComPtr<ICoordinateXform2d> pXform;
         ASSERT_EQ( pXform.CoCreateInstance( CLSID_CoordinateXform2d ), S_OK );

         CComPtr<IPoint2d> origin;
         origin.CoCreateInstance( CLSID_Point2d );
         origin->put_X(5);
         origin->put_Y(5);

         ASSERT_EQ( pXform->put_NewOrigin(nullptr), E_INVALIDARG );
         ASSERT_EQ( pXform->put_NewOrigin(origin), S_OK );

         CComPtr<IPoint2d> o;
         ASSERT_EQ( pXform->get_NewOrigin(nullptr), E_POINTER );
         ASSERT_EQ( pXform->get_NewOrigin(&o), S_OK );
         Float64 x,y;
         o->get_X(&x);
         o->get_Y(&y);
         ASSERT_EQ(IsEqual(x,5.0),true);
         ASSERT_EQ(IsEqual(y,5.0),true);

         ASSERT_EQ( pXform->put_RotationAngle(M_PI/4), S_OK );
         Float64 angle;
         ASSERT_EQ( pXform->get_RotationAngle(nullptr), E_POINTER );
         ASSERT_EQ( pXform->get_RotationAngle(&angle), S_OK );
         ASSERT_EQ( IsEqual(angle,M_PI/4), true );

         origin->put_X(7);
         origin->put_Y(-4);
         pXform->put_NewOrigin(origin);
         pXform->put_RotationAngle(27*M_PI/180);

         CComPtr<IPoint2d> pnt;
         ASSERT_EQ( pXform->Xform(nullptr, xfrmOldToNew), E_INVALIDARG );
         ASSERT_EQ( pXform->Xform(&pnt.p, xfrmOldToNew), E_INVALIDARG );

         pnt.CoCreateInstance( CLSID_Point2d );
         pnt->Move( -9,7 );

         CComPtr<IPoint2d> result;
         ASSERT_EQ( pXform->XformEx( nullptr, xfrmOldToNew, &result ), E_INVALIDARG );
         ASSERT_EQ( pXform->XformEx( pnt, xfrmOldToNew, nullptr ), E_POINTER );
         ASSERT_EQ( pXform->XformEx( pnt, xfrmOldToNew, &result ), S_OK );
         result->get_X(&x);
         result->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-9.2622, tolerance), true );
         ASSERT_EQ( IsEqual(y,17.0649, tolerance), true );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-9., tolerance), true );
         ASSERT_EQ( IsEqual(y, 7., tolerance), true );

         ASSERT_EQ( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-9.26221, tolerance), true );
         ASSERT_EQ( IsEqual(y,17.06492, tolerance), true );


         pnt->Move( -9.2622, 17.0649 );
         ASSERT_EQ( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-9., tolerance), true );
         ASSERT_EQ( IsEqual(y, 7., tolerance), true );

         pnt->Move( -5,-4 );
         ASSERT_EQ( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-10.6921, tolerance), true );
         ASSERT_EQ( IsEqual(y, 5.4479, tolerance), true );

         pnt->Move( -10.6921, 5.4479 );
         ASSERT_EQ( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-5., tolerance), true );
         ASSERT_EQ( IsEqual(y,-4., tolerance), true );

         pnt->Move( 2.7, -3.6 );
         ASSERT_EQ( pXform->Xform( &pnt.p, xfrmNewToOld ), S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x,11.0401, tolerance), true );
         ASSERT_EQ( IsEqual(y,-5.9818, tolerance), true );

         pnt->Move( 11.0401, -5.9818 );
         ASSERT_EQ( pXform->Xform( &pnt.p, xfrmOldToNew ), S_OK );
         pnt->get_X(&x);
         pnt->get_Y(&y);
         ASSERT_EQ( IsEqual(x, 2.7,0.1), true );
         ASSERT_EQ( IsEqual(y,-3.6,0.1), true );
   }

   TEST_METHOD(TestISupportErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_CoordinateXform2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ICoordinateXform2d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests