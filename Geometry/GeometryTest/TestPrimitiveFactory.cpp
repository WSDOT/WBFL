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

// TestPrimitiveFactory.cpp: implementation of the TestPrimitiveFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrimitiveFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestPrimitiveFactory::CTestPrimitiveFactory()
{

}

CTestPrimitiveFactory::~CTestPrimitiveFactory()
{

}

void CTestPrimitiveFactory::Test()
{
   CComPtr<IPoint2dFactory> pf2d;
   TRY_TEST( pf2d.CoCreateInstance( CLSID_PrimitiveFactory ), S_OK );

   // Test Interfaces
   CComQIPtr<IPoint3dFactory> pf3d(pf2d);
   TRY_TEST( pf3d != 0, true );

   CComQIPtr<ILine2dFactory> lf(pf2d);
   TRY_TEST( lf != 0, true );

   CComQIPtr<ILineSegment2dFactory> lsf(pf2d);
   TRY_TEST( lsf != 0, true );

   CComPtr<IUnknown> punk1;
   pf3d.QueryInterface( &punk1 );

   CComPtr<IUnknown> punk2;
   lf.QueryInterface( &punk2 );

   CComPtr<IUnknown> punk3;
   lsf.QueryInterface( &punk3 );

   TRY_TEST( pf2d.IsEqualObject( punk1 ), true );
   TRY_TEST( pf2d.IsEqualObject( punk2 ), true );
   TRY_TEST( pf2d.IsEqualObject( punk3 ), true );

   TestIPoint2dFactory();
   TestIPoint3dFactory();
   TestILine2dFactory();
   TestILineSegment2dFactory();
   TestISupportErrorInfo();
}

void CTestPrimitiveFactory::TestIPoint2dFactory()
{
   CComPtr<IPoint2dFactory> factory;
   TRY_TEST( factory.CoCreateInstance( CLSID_PrimitiveFactory ), S_OK );

   CComPtr<IPoint2d> pnt;
   TRY_TEST( factory->CreatePoint(nullptr), E_POINTER );
   TRY_TEST( factory->CreatePoint(&pnt), S_OK );
   TRY_TEST( pnt != 0, true );
}

void CTestPrimitiveFactory::TestIPoint3dFactory()
{
   CComPtr<IPoint3dFactory> factory;
   TRY_TEST( factory.CoCreateInstance( CLSID_PrimitiveFactory ), S_OK );

   CComPtr<IPoint3d> pnt;
   TRY_TEST( factory->CreatePoint(nullptr), E_POINTER );
   TRY_TEST( factory->CreatePoint(&pnt), S_OK );
   TRY_TEST( pnt != 0, true );
}

void CTestPrimitiveFactory::TestILine2dFactory()
{
   CComPtr<ILine2dFactory> factory;
   TRY_TEST( factory.CoCreateInstance( CLSID_PrimitiveFactory ), S_OK );

   CComPtr<ILine2d> line;
   TRY_TEST( factory->CreateLine(nullptr), E_POINTER );
   TRY_TEST( factory->CreateLine(&line), S_OK );
   TRY_TEST( line != 0, true );
}

void CTestPrimitiveFactory::TestILineSegment2dFactory()
{
   CComPtr<ILineSegment2dFactory> factory;
   TRY_TEST( factory.CoCreateInstance( CLSID_PrimitiveFactory ), S_OK );

   CComPtr<ILineSegment2d> lineSeg;
   TRY_TEST( factory->CreateLineSegment(nullptr), E_POINTER );
   TRY_TEST( factory->CreateLineSegment(&lineSeg), S_OK );
   TRY_TEST( lineSeg != 0, true );
}


void CTestPrimitiveFactory::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_PrimitiveFactory ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ILine2dFactory ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ILineSegment2dFactory ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPoint2dFactory ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IPoint3dFactory ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
