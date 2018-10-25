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

// TestNUBeam.cpp: implementation of the CTestNUBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestNUBeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestNUBeam::CTestNUBeam()
{

}

CTestNUBeam::~CTestNUBeam()
{

}

void CTestNUBeam::Test()
{
   TestINUBeam();
   TestIShape();
   TestIShape2();
   TestIShape3();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestNUBeam::TestINUBeam()
{
   CComPtr<INUBeam> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_NUBeam), S_OK );

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_D1(NULL), E_POINTER );
   TRY_TEST( beam->get_D1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D2(NULL), E_POINTER );
   TRY_TEST( beam->get_D2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D3(NULL), E_POINTER );
   TRY_TEST( beam->get_D3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D4(NULL), E_POINTER );
   TRY_TEST( beam->get_D4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_D5(NULL), E_POINTER );
   TRY_TEST( beam->get_D5(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_T(NULL), E_POINTER );
   TRY_TEST( beam->get_T(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W1(NULL), E_POINTER );
   TRY_TEST( beam->get_W1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W2(NULL), E_POINTER );
   TRY_TEST( beam->get_W2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_R1(NULL), E_POINTER );
   TRY_TEST( beam->get_R1(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_R2(NULL), E_POINTER );
   TRY_TEST( beam->get_R2(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_R3(NULL), E_POINTER );
   TRY_TEST( beam->get_R3(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_R4(NULL), E_POINTER );
   TRY_TEST( beam->get_R4(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_HookPoint(NULL), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_D1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D1(65), S_OK );
   beam->get_D1(&val);
   TRY_TEST( IsEqual(val,65.0), true );

   TRY_TEST( beam->put_D2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D2(45), S_OK );
   beam->get_D2(&val);
   TRY_TEST( IsEqual(val,45.0), true );

   TRY_TEST( beam->put_D3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D3(2015), S_OK );
   beam->get_D3(&val);
   TRY_TEST( IsEqual(val,2015.0), true );

   TRY_TEST( beam->put_D4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D4(140), S_OK );
   beam->get_D4(&val);
   TRY_TEST( IsEqual(val,140.0), true );

   TRY_TEST( beam->put_D5(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_D5(135), S_OK );
   beam->get_D5(&val);
   TRY_TEST( IsEqual(val,135.0), true );

   TRY_TEST( beam->put_T(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_T(150), S_OK );
   beam->get_T(&val);
   TRY_TEST( IsEqual(val,150.0), true );

   TRY_TEST( beam->put_W1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W1(1225), S_OK );
   beam->get_W1(&val);
   TRY_TEST( IsEqual(val,1225.0), true );

   TRY_TEST( beam->put_W2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W2(975), S_OK );
   beam->get_W2(&val);
   TRY_TEST( IsEqual(val,975.0), true );

   TRY_TEST( beam->put_R1(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_R1(200), S_OK );
   beam->get_R1(&val);
   TRY_TEST( IsEqual(val,200.0), true );

   TRY_TEST( beam->put_R2(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_R2(200), S_OK );
   beam->get_R2(&val);
   TRY_TEST( IsEqual(val,200.0), true );

   TRY_TEST( beam->put_R3(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_R3(50), S_OK );
   beam->get_R3(&val);
   TRY_TEST( IsEqual(val,50.0), true );

   TRY_TEST( beam->put_R4(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_R4(50), S_OK );
   beam->get_R4(&val);
   TRY_TEST( IsEqual(val,50.0), true );

   pntVal->Move(14,14);
   TRY_TEST( beam->putref_HookPoint(NULL), E_INVALIDARG );
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
   TRY_TEST(beam->get_Height(NULL), E_POINTER );
   TRY_TEST(beam->get_Height(&val), S_OK );
   TRY_TEST(IsEqual(val,2400.), true );

   TRY_TEST(beam->get_TopFlangeWidth(NULL), E_POINTER );
   TRY_TEST(beam->get_TopFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,1225.), true );

   TRY_TEST(beam->get_BottomFlangeWidth(NULL), E_POINTER );
   TRY_TEST(beam->get_BottomFlangeWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,975.), true );

   TRY_TEST(beam->get_AvgWebWidth(NULL), E_POINTER );
   TRY_TEST(beam->get_AvgWebWidth(&val), S_OK );
   TRY_TEST(IsEqual(val,150.), true );


   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(beam->get_Shape(NULL), E_POINTER );
   TRY_TEST(beam->get_Shape(&shape), S_OK );
   TRY_TEST(shape != NULL,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(beam->get_XYPosition(NULL), E_POINTER );
   TRY_TEST(beam->get_XYPosition(&position), S_OK );
   TRY_TEST(position != NULL,true );

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

void CTestNUBeam::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_NUBeam), S_OK);

   CComQIPtr<INUBeam> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // Use some real dimensions (NU2400 - 150mm web)
   beam->put_W1(1225);
   beam->put_W2(975);
   beam->put_D1(65);
   beam->put_D2(45);
   beam->put_D3(2015);
   beam->put_D4(140);
   beam->put_D5(135);
   beam->put_T(150);
   beam->put_R1(200);
   beam->put_R2(200);
   beam->put_R3(50);
   beam->put_R4(50);

   //
   // MoveEx (tests Offset as well)
   //
   CComPtr<IPoint2d> from;
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(0,0);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(100,100);

   TRY_TEST( position->MoveEx(NULL,to), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,NULL), E_INVALIDARG );
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

   TRY_TEST(position->OffsetEx(NULL), E_INVALIDARG );
   TRY_TEST(position->OffsetEx(size), S_OK);

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0,0);
   CComPtr<IPoint2d> c;
   c.CoCreateInstance( CLSID_Point2d );
   c->put_X(0);
   c->put_Y(0);

   TRY_TEST( position->RotateEx(NULL,M_PI), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI), S_OK );
}

void CTestNUBeam::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_NUBeam ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_INUBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
