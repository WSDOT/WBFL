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

// TestLineSegment3d.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestLineSegment3d.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestLineSegment3d)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<ILineSegment3d> pSeg;
         ASSERT_EQ(pSeg.CoCreateInstance( CLSID_LineSegment3d ),S_OK);

         //
         // Test StartPoint property
         //
         CComPtr<IPoint3d> p1;
         p1.CoCreateInstance( CLSID_Point3d );
         p1->put_X(10);
         p1->put_Y(10);
         p1->put_Z(10);

         ASSERT_EQ(pSeg->put_StartPoint(nullptr),E_INVALIDARG);
         ASSERT_EQ(pSeg->put_StartPoint(p1),S_OK);

         CComPtr<IPoint3d> pStart;
         ASSERT_EQ(pSeg->get_StartPoint(nullptr),E_POINTER);
         ASSERT_EQ(pSeg->get_StartPoint(&pStart),S_OK);
         Float64 x,y,z;
         pStart->get_X(&x);
         pStart->get_Y(&y);
         pStart->get_Z(&z);
         ASSERT_EQ(IsEqual(x,10.0),true);
         ASSERT_EQ(IsEqual(y,10.0),true);
         ASSERT_EQ(IsEqual(z,10.0),true);

         // Get the start point when the receiving point object already
         // references an existing point.
         p1.Release();
         ASSERT_EQ(pSeg->get_StartPoint(&p1),S_OK);
         p1->get_X(&x);
         p1->get_Y(&y);
         p1->get_Z(&z);
         ASSERT_EQ(IsEqual(x,10.0),true);
         ASSERT_EQ(IsEqual(y,10.0),true);
         ASSERT_EQ(IsEqual(z,10.0),true);

         //
         // Test EndPoint property
         CComPtr<IPoint3d> p2;
         p2.CoCreateInstance( CLSID_Point3d );
         p2->put_X(20);
         p2->put_Y(20);
         p2->put_Z(20);
         ASSERT_EQ(pSeg->put_EndPoint(nullptr),E_INVALIDARG);
         ASSERT_EQ(pSeg->put_EndPoint(p2),S_OK);

         CComPtr<IPoint3d> pEnd;
         ASSERT_EQ(pSeg->get_EndPoint(nullptr),E_POINTER);
         ASSERT_EQ(pSeg->get_EndPoint(&pEnd),S_OK);
         pEnd->get_X(&x);
         pEnd->get_Y(&y);
         pEnd->get_Z(&z);
         ASSERT_EQ(IsEqual(x,20.0),true);
         ASSERT_EQ(IsEqual(y,20.0),true);
         ASSERT_EQ(IsEqual(z,20.0),true);

         // Get the start point when the receiving point object already
         // references an existing point.
         p2.Release();
         ASSERT_EQ(pSeg->get_EndPoint(&p2),S_OK);
         p2->get_X(&x);
         p2->get_Y(&y);
         p2->get_Z(&z);
         ASSERT_EQ(IsEqual(x,20.0),true);
         ASSERT_EQ(IsEqual(y,20.0),true);
         ASSERT_EQ(IsEqual(z,20.0),true);

         //
         // Test Length property
         //
         p1->put_X(10);
         p1->put_Y(10);
         p1->put_Z(10);
         p2->put_X(20);
         p2->put_Y(20);
         p2->put_Z(20);
         pSeg->put_StartPoint(p1);
         pSeg->put_EndPoint(p2);
         Float64 length;
         ASSERT_EQ(pSeg->get_Length(nullptr),E_POINTER);
         ASSERT_EQ(pSeg->get_Length(&length),S_OK);
         ASSERT_EQ(IsEqual(length,17.320508),true);

         //
         // Test Offset method
         //
         p1->put_X(10);
         p1->put_Y(10);
         p2->put_X(20);
         p2->put_Y(20);
         pSeg->put_StartPoint(p1);
         pSeg->put_EndPoint(p2);
         ASSERT_EQ(pSeg->Offset(-10,-10,0),S_OK);
         pStart.Release();
         pSeg->get_StartPoint(&pStart);
         pEnd.Release();
         pSeg->get_EndPoint(&pEnd);
         pStart->get_X(&x);
         pStart->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
         pEnd->get_X(&x);
         pEnd->get_Y(&y);
         ASSERT_EQ( IsEqual(x,10.0), true );
         ASSERT_EQ( IsEqual(y,10.0), true );

         //
         // Test OffsetEx method
         //
         p1->put_X(-10);
         p1->put_Y(-10);
         p2->put_X(-20);
         p2->put_Y(-20);
         pSeg->put_StartPoint(p1);
         pSeg->put_EndPoint(p2);
         CComPtr<ISize3d> size;
         size.CoCreateInstance( CLSID_Size3d );
         size->put_Dx(10);
         size->put_Dy(10);
         size->put_Dz( 0);
         ASSERT_EQ(pSeg->OffsetEx(nullptr),E_INVALIDARG);
         ASSERT_EQ(pSeg->OffsetEx(size),S_OK);
         pStart.Release();
         pSeg->get_StartPoint(&pStart);
         pEnd.Release();
         pSeg->get_EndPoint(&pEnd);
         pStart->get_X(&x);
         pStart->get_Y(&y);
         ASSERT_EQ( IsEqual(x,0.0), true );
         ASSERT_EQ( IsEqual(y,0.0), true );
         pEnd->get_X(&x);
         pEnd->get_Y(&y);
         ASSERT_EQ( IsEqual(x,-10.0), true );
         ASSERT_EQ( IsEqual(y,-10.0), true );

         ////
         //// Test Rotate method
         ////
         //pStart->put_X(10);
         //pStart->put_Y(10);
         //pEnd->put_X(20);
         //pEnd->put_Y(20);
         //pSeg->putref_StartPoint(pStart);
         //pSeg->putref_EndPoint(pEnd);

         //ASSERT_EQ(pSeg->Rotate(0,0,M_PI),S_OK);
         //pStart.Release();
         //pEnd.Release();
         //pSeg->get_StartPoint(&pStart);
         //pSeg->get_EndPoint(&pEnd);
         //pStart->get_X(&x);
         //pStart->get_Y(&y);
         //ASSERT_EQ(IsEqual(x,-10.0),true);
         //ASSERT_EQ(IsEqual(y,-10.0),true);
         //pEnd->get_X(&x);
         //pEnd->get_Y(&y);
         //ASSERT_EQ(IsEqual(x,-20.0),true);
         //ASSERT_EQ(IsEqual(y,-20.0),true);

         ////
         //// Test RotateEx method
         ////
         //pStart->put_X(10);
         //pStart->put_Y(10);
         //pEnd->put_X(20);
         //pEnd->put_Y(20);
         //pSeg->putref_StartPoint(pStart);
         //pSeg->putref_EndPoint(pEnd);

         //CComPtr<IPoint2d> center;
         //center.CoCreateInstance( CLSID_Point3d );
         //center->put_X(0.00);
         //center->put_Y(0.00);
         //ASSERT_EQ(pSeg->RotateEx(nullptr,M_PI/2),E_INVALIDARG);
         //ASSERT_EQ(pSeg->RotateEx(center,M_PI/2),S_OK);
         //pStart.Release();
         //pEnd.Release();
         //pSeg->get_StartPoint(&pStart);
         //pSeg->get_EndPoint(&pEnd);
         //pStart->get_X(&x);
         //pStart->get_Y(&y);
         //ASSERT_EQ(IsEqual(x,-10.0),true);
         //ASSERT_EQ(IsEqual(y, 10.0),true);
         //pEnd->get_X(&x);
         //pEnd->get_Y(&y);
         //ASSERT_EQ(IsEqual(x,-20.0),true);
         //ASSERT_EQ(IsEqual(y, 20.0),true);
   }

   TEST_METHOD(SupportsErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_LineSegment3d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ILineSegment3d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }
};
} // namespace GeometryUnitTests