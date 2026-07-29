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

// TestPlane3d.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestPlane3d.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestPlane3d)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IPlane3d> plane;
         ASSERT_EQ(plane.CoCreateInstance( CLSID_Plane3d ),S_OK);

         // XY Plane at Altitude = 10.0
         Float64 val;
         ASSERT_EQ(plane->ThroughAltitude(10),S_OK);
         ASSERT_EQ(plane->GetZ(5,5,nullptr),E_POINTER);
         ASSERT_EQ(plane->GetZ(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,10.),true);

         ASSERT_EQ( plane->GetX(5,5,nullptr),E_POINTER);
         ASSERT_EQ( plane->GetX(5,5,&val),GEOMETRY_E_NOSOLUTIONS);

         ASSERT_EQ( plane->GetY(5,5,nullptr),E_POINTER);
         ASSERT_EQ( plane->GetY(5,5,&val), GEOMETRY_E_NOSOLUTIONS);

         // Plane through three points
         CComPtr<IPoint3d> p1;
         p1.CoCreateInstance( CLSID_Point3d );
         p1->Move(0,0,0);

         CComPtr<IPoint3d> p2;
         p2.CoCreateInstance( CLSID_Point3d );
         p2->Move(0,0,10);

         CComPtr<IPoint3d> p3;
         p3.CoCreateInstance( CLSID_Point3d );
         p3->Move(10,10,0);

         ASSERT_EQ(plane->ThroughPoints(nullptr,nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(plane->ThroughPoints(p1,  nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(plane->ThroughPoints(p1,  p2,  nullptr),E_INVALIDARG);
         ASSERT_EQ(plane->ThroughPoints(p1,  p2,  p3),  S_OK);

         ASSERT_EQ(plane->GetX(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,5.0),true);

         ASSERT_EQ(plane->GetY(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,5.0),true);

         ASSERT_EQ(plane->GetZ(5,5,&val),GEOMETRY_E_NOSOLUTIONS); // Plane is parallel to Z axis

         // ThroughLineEx
         CComPtr<ILine2d> line;
         line.CoCreateInstance( CLSID_Line2d ); // Line on the X axis
         line->Rotate(0,0,PI_OVER_2); // Line is now in the pos Y direction
         p3->Move(10,0,10);
         ASSERT_EQ(plane->ThroughLineEx(nullptr,nullptr),E_INVALIDARG);
         ASSERT_EQ(plane->ThroughLineEx(line,nullptr),E_INVALIDARG);
         ASSERT_EQ(plane->ThroughLineEx(line,p3),  S_OK);

         ASSERT_EQ(plane->GetX(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,5.0),true );

         ASSERT_EQ(plane->GetY(5,5,&val), GEOMETRY_E_NOSOLUTIONS); // Plane is parallel to Y axis

         ASSERT_EQ(plane->GetZ(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,5.0),true );

         p3->Move(0,10,0); // point is now on the line
         ASSERT_EQ(plane->ThroughLineEx(line,p3), GEOMETRY_E_COLINEAR);

         // Arbitrary Plane
         p1->Move(10,0,0);
         p2->Move(0,10,0);
         p3->Move(0,0,10);
         plane->ThroughPoints(p1,p2,p3);

         ASSERT_EQ(plane->GetX(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);

         ASSERT_EQ(plane->GetY(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);

         ASSERT_EQ(plane->GetZ(5,5,&val),S_OK);
         ASSERT_EQ(IsEqual(val,0.0),true);
   }

   TEST_METHOD(SupportsErrorInfo)
   {
         CComPtr<ISupportErrorInfo> eInfo;
         ASSERT_EQ( eInfo.CoCreateInstance( CLSID_Plane3d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IPlane3d ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   }

   TEST_METHOD(PlaneLineIntersect)
   {
         CComPtr<IPlane3d> plane;
         ASSERT_EQ(plane.CoCreateInstance( CLSID_Plane3d ),S_OK);

         // Plane through three points
         CComPtr<IPoint3d> p1;
         p1.CoCreateInstance( CLSID_Point3d );
         p1->Move(1,0,0);

         CComPtr<IPoint3d> p2;
         p2.CoCreateInstance( CLSID_Point3d );
         p2->Move(0,1,0);

         CComPtr<IPoint3d> p3;
         p3.CoCreateInstance( CLSID_Point3d );
         p3->Move(0,0,1);

         plane->ThroughPoints(p1,  p2,  p3);

         CComPtr<ILineSegment3d> line;
         line.CoCreateInstance(CLSID_LineSegment3d);

         CComPtr<IPoint3d> pA;
         pA.CoCreateInstance(CLSID_Point3d);
         pA->Move(0,0,0);

         CComPtr<IPoint3d> pB;
         pB.CoCreateInstance(CLSID_Point3d);
         pB->Move(10,10,10);

         line->ThroughPoints(pA,pB);

         CComPtr<IPoint3d> pntIntersect;
         plane->LineSegmentIntersect(line,&pntIntersect);

         Float64 x,y,z;
         pntIntersect->Location(&x,&y,&z);
         ASSERT_EQ(IsEqual(x,0.333333),true);
         ASSERT_EQ(IsEqual(y,0.333333),true);
         ASSERT_EQ(IsEqual(z,0.333333),true);

         pB->Move(10,10,0);
         line->put_EndPoint(pB);
         pntIntersect.Release();
         plane->LineSegmentIntersect(line,&pntIntersect);
         pntIntersect->Location(&x,&y,&z);
         ASSERT_EQ(IsEqual(x,0.5),true);
         ASSERT_EQ(IsEqual(y,0.5),true);
         ASSERT_EQ(IsEqual(z,0.0),true);

         pB->Move( 0,10,10);
         line->put_EndPoint(pB);
         pntIntersect.Release();
         plane->LineSegmentIntersect(line,&pntIntersect);
         pntIntersect->Location(&x,&y,&z);
         ASSERT_EQ(IsEqual(x,0.0),true);
         ASSERT_EQ(IsEqual(y,0.5),true);
         ASSERT_EQ(IsEqual(z,0.5),true);

         pB->Move(10, 0,10);
         line->put_EndPoint(pB);
         pntIntersect.Release();
         plane->LineSegmentIntersect(line,&pntIntersect);
         pntIntersect->Location(&x,&y,&z);
         ASSERT_EQ(IsEqual(x,0.5),true);
         ASSERT_EQ(IsEqual(y,0.0),true);
         ASSERT_EQ(IsEqual(z,0.5),true);

         // Parallel to YZ at X = 1
         p1->Move(1,0,0);
         p2->Move(1,1,0);
         p3->Move(1,0,1);
         plane->ThroughPoints(p1,p2,p3);

         pB->Move(10,0,0);
         line->put_EndPoint(pB);
         pntIntersect.Release();
         plane->LineSegmentIntersect(line,&pntIntersect);
         pntIntersect->Location(&x,&y,&z);
         ASSERT_EQ(IsEqual(x,1.0),true);
         ASSERT_EQ(IsEqual(y,0.0),true);
         ASSERT_EQ(IsEqual(z,0.0),true);

         // parallel to the plane
         pB->Move(0,10,10);
         line->put_EndPoint(pB);
         pntIntersect.Release();
         ASSERT_EQ(plane->LineSegmentIntersect(line,&pntIntersect),GEOMETRY_E_NOSOLUTIONS);

         // in the plane
         pA->Move(1,0,0);
         pB->Move(1,10,10);
         line->put_StartPoint(pA);
         line->put_EndPoint(pB);
         pntIntersect.Release();
         ASSERT_EQ(plane->LineSegmentIntersect(line,&pntIntersect),GEOMETRY_E_NOSOLUTIONS);
   }
};
} // namespace GeometryUnitTests