///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// TestDisplayUnit2.cpp: implementation of the CTestDisplayUnit2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDisplayUnit2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDisplayUnit::CTestDisplayUnit()
{

}

CTestDisplayUnit::~CTestDisplayUnit()
{

}

void CTestDisplayUnit::Test()
{
   // Test creation
   // This object is not directly creatable.
   CComPtr<IDisplayUnit> pDispUnit;

   // object should not be registered
   TRY_TEST( pDispUnit.CoCreateInstance( CComBSTR("WBFLUnitServer.DisplayUnit") ), CO_E_CLASSSTRING );

   // this line should not compile
//   pDispUnit.CoCreateInstance( CLSID_DisplayUnit );

   // Before we can do any test, we need to setup the display units manager
   CComPtr<IUnitSystem> pUS;
   pUS.CoCreateInstance( CLSID_UnitSystem );

   CComPtr<IDisplayUnitMgr> pDUM;
   pUS->get_DisplayUnitMgr(&pDUM);

   CComPtr<IDisplayUnitGroup> pGroup;
   pDUM->Add(CComBSTR("Distance"),CComBSTR("Length"),&pGroup);

   CComPtr<IDisplayUnitFormatter> formatter;
   formatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   formatter->FormatSpecifiers(6,3,tjRight,nftFixed,0.0001);

   pGroup->Add(CComBSTR("m"),unitsSI,formatter,VARIANT_TRUE,&pDispUnit);

   TRY_TEST( pDispUnit != 0, true );

   //******************************************
   //* Test Formatter property
   //******************************************
   CComPtr<IDisplayUnitFormatter> pTestFormatter;
   TRY_TEST( pDispUnit->get_Formatter(NULL), E_POINTER );
   TRY_TEST( pDispUnit->get_Formatter(&pTestFormatter), S_OK );
   TRY_TEST( pTestFormatter.IsEqualObject(formatter), true );
   TRY_TEST( pDispUnit->putref_Formatter(NULL), E_INVALIDARG );
   TRY_TEST( pDispUnit->putref_Formatter(pTestFormatter), S_OK );

   //******************************************
   //* Test UnitTag
   //******************************************
   CComBSTR bstrTest;
   TRY_TEST( pDispUnit->get_UnitTag(NULL), E_POINTER );
   TRY_TEST( pDispUnit->get_UnitTag(&bstrTest), S_OK );
   TRY_TEST( wcscmp( bstrTest, CComBSTR("m")), 0);

   //******************************************
   //* Test UnitSystem
   //******************************************
   UnitSystemType unitSystem;
   TRY_TEST( pDispUnit->get_UnitSystem(NULL), E_POINTER );
   TRY_TEST( pDispUnit->get_UnitSystem(&unitSystem), S_OK );
   TRY_TEST( unitSystem, unitsSI );

   //******************************************
   //* Test IsDefault
   //******************************************
   VARIANT_BOOL bIsDefault;
   TRY_TEST( pDispUnit->IsDefault(NULL), E_POINTER );
   TRY_TEST( pDispUnit->IsDefault(&bIsDefault), S_OK );
   TRY_TEST( bIsDefault, VARIANT_TRUE );

   //******************************************
   //* Test Format
   //******************************************
   TRY_TEST( pDispUnit->Format(12.3456,VARIANT_TRUE,NULL), E_POINTER );
   TRY_TEST( pDispUnit->Format(12.3456,VARIANT_TRUE,&bstrTest), S_OK );
   TRY_TEST( wcscmp( bstrTest, CComBSTR("12.346 m")), 0);
   TRY_TEST( pDispUnit->Format(12.3456,VARIANT_FALSE,&bstrTest), S_OK );
   TRY_TEST( wcscmp( bstrTest, CComBSTR("12.346")), 0);
   formatter->FormatSpecifiers(8,5,tjRight,nftFixed,0.0001);
   TRY_TEST( pDispUnit->Format(12.3456,VARIANT_TRUE,&bstrTest), S_OK );
   TRY_TEST( wcscmp( bstrTest, CComBSTR("12.34560 m")), 0);

   // ****************************************************
   // * Test ISupportErrorInfo
   // ****************************************************
   CComQIPtr<ISupportErrorInfo>  pSEI(pDispUnit);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IDisplayUnit ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
