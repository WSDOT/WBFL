///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 2000  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// TestPlane3d.cpp: implementation of the CTestPlane3d class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPlane3d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPlane3d::CTestPlane3d()
{

}

CTestPlane3d::~CTestPlane3d()
{

}

void CTestPlane3d::Test()
{
   CComPtr<IPlane3d> plane;
   TRY_TEST(plane.CoCreateInstance( CLSID_Plane3d ),S_OK);

   // XY Plane at Altitude = 10.0
   Float64 val;
   TRY_TEST(plane->ThroughAltitude(10),S_OK);
   TRY_TEST(plane->GetZ(5,5,NULL),E_POINTER);
   TRY_TEST(plane->GetZ(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,10.),true);

   TRY_TEST( plane->GetX(5,5,NULL),E_POINTER);
   TRY_TEST( plane->GetX(5,5,&val),GEOMETRY_E_NOSOLUTIONS);

   TRY_TEST( plane->GetY(5,5,NULL),E_POINTER);
   TRY_TEST( plane->GetY(5,5,&val),GEOMETRY_E_INFINITESOLUTIONS);

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

   TRY_TEST(plane->ThroughPoints(NULL,NULL,NULL),E_INVALIDARG);
   TRY_TEST(plane->ThroughPoints(p1,  NULL,NULL),E_INVALIDARG);
   TRY_TEST(plane->ThroughPoints(p1,  p2,  NULL),E_INVALIDARG);
   TRY_TEST(plane->ThroughPoints(p1,  p2,  p3),  S_OK);

   TRY_TEST(plane->GetX(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,5.0),true);

   TRY_TEST(plane->GetY(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,5.0),true);

   TRY_TEST(plane->GetZ(5,5,&val),GEOMETRY_E_NOSOLUTIONS); // Plane is parallel to Z axis

   // ThroughLineEx
   CComPtr<ILine2d> line;
   line.CoCreateInstance( CLSID_Line2d ); // Line on the X axis
   line->Rotate(0,0,PI_OVER_2); // Line is now in the pos Y direction
   p3->Move(10,0,10);
   TRY_TEST(plane->ThroughLineEx(NULL,NULL),E_INVALIDARG);
   TRY_TEST(plane->ThroughLineEx(line,NULL),E_INVALIDARG);
   TRY_TEST(plane->ThroughLineEx(line,p3),  S_OK);

   TRY_TEST(plane->GetX(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,5.0),true );

   TRY_TEST(plane->GetY(5,5,&val),GEOMETRY_E_INFINITESOLUTIONS); // Plane is parallel to Y axis

   TRY_TEST(plane->GetZ(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,5.0),true );

   p3->Move(0,10,0); // point is now on the line
   TRY_TEST(plane->ThroughLineEx(line,p3), GEOMETRY_E_POINTONLINE );

   // Arbitrary Plane
   p1->Move(10,0,0);
   p2->Move(0,10,0);
   p3->Move(0,0,10);
   plane->ThroughPoints(p1,p2,p3);

   TRY_TEST(plane->GetX(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(plane->GetY(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TRY_TEST(plane->GetZ(5,5,&val),S_OK);
   TRY_TEST(IsEqual(val,0.0),true);

   TestISupportErrorInfo();
}

void CTestPlane3d::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_Plane3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPlane3d ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
