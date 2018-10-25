///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// TestDisplayUnitGroup.cpp: implementation of the CTestDisplayUnitGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDisplayUnitGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDisplayUnitGroup::CTestDisplayUnitGroup()
{

}

CTestDisplayUnitGroup::~CTestDisplayUnitGroup()
{

}

void CTestDisplayUnitGroup::Test()
{
   // Test creation
   // This object is not directly creatable.
   CComPtr<IDisplayUnitGroup> pGroup;

   // object should not be registered
   TRY_TEST( pGroup.CoCreateInstance( CComBSTR("WBFLUnitServer.DisplayUnitGroup") ), CO_E_CLASSSTRING );

   // this line should not compile
//   pGroup.CoCreateInstance( CLSID_DisplayUnitGroup );

   // Create the unit system object, get a reference to the display unit manager, and
   // create a display unit group, the we will start testing the group.

   CComPtr<IUnitSystem> pUS;
   pUS.CoCreateInstance( CLSID_UnitSystem );

   CComPtr<IDisplayUnitMgr> pDUM;
   pUS->get_DisplayUnitMgr(&pDUM);

   pDUM->Add(CComBSTR("Distance"),CComBSTR("Length"),&pGroup);

   // ****************************************************
   // * Test Name
   // ****************************************************
   CComBSTR bstrTest;
   TRY_TEST( pGroup->get_Name(NULL), E_POINTER );
   TRY_TEST( pGroup->get_Name(&bstrTest), S_OK );
   TRY_TEST( wcscmp( bstrTest, CComBSTR("Distance")), 0);

   // ****************************************************
   // * Test UnitType
   // ****************************************************
   TRY_TEST( pGroup->get_UnitType(NULL), E_POINTER );
   TRY_TEST( pGroup->get_UnitType(&bstrTest), S_OK );
   TRY_TEST( wcscmp( bstrTest,CComBSTR("Length")), 0 );

   // ****************************************************
   // * Test Add
   // ****************************************************

   // These tests verify the basic implementation of the interface and not the
   // complex interactions. Tests will consist of the successful creation of a 
   // single display unit object, and all failure conditions due to bad input.
   //
   // Testing the creation of several display units, along with different scenarios
   // for default units and unit systems will be explored later.
   
   // First, need to create a display unit formatter
   CComPtr<IDisplayUnitFormatter> pFormatter;
   pFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   
   CComPtr<IDisplayUnit> pDispUnit;

   // bad input
   TRY_TEST( pGroup->Add(NULL,unitsSI,pFormatter,VARIANT_TRUE,&pDispUnit), E_INVALIDARG );
   TRY_TEST( pGroup->Add(CComBSTR("Junk"),unitsSI,pFormatter,VARIANT_TRUE,&pDispUnit), UNITS_E_BADUNITTAG );
   TRY_TEST( pGroup->Add(CComBSTR("m"),unitsSI,NULL,VARIANT_TRUE,&pDispUnit), E_INVALIDARG );
   TRY_TEST( pGroup->Add(CComBSTR("m"),unitsSI,pFormatter,VARIANT_TRUE,NULL), E_POINTER );

   // success
   TRY_TEST( pGroup->Add(CComBSTR("m"),unitsSI,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );

   // add another
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("ft"),unitsUS,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );

   // add another
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("mm"),unitsSI,pFormatter,VARIANT_FALSE,&pDispUnit), S_OK );

   // ****************************************************
   // * Test Count and Clear
   // ****************************************************
   CollectionIndexType count;
   TRY_TEST( pGroup->get_Count(NULL), E_POINTER );
   TRY_TEST( pGroup->get_Count(&count), S_OK );
   TRY_TEST( count, 3 );
   TRY_TEST( pGroup->Clear(), S_OK );
   TRY_TEST( pGroup->get_Count(&count), S_OK );
   TRY_TEST( count, 0 );

   // ****************************************************
   // * Test Remove
   // ****************************************************

   // Test with bad pointer
   TRY_TEST( pGroup->Remove(NULL), E_INVALIDARG );

   // Test on an empty group
   TRY_TEST( pGroup->Remove(CComBSTR("mm")),UNITS_E_BADUNITTAG);

   // Create a display unit
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("mm"),unitsSI,pFormatter,VARIANT_FALSE,&pDispUnit), S_OK );

   // Remove with a bad name
   TRY_TEST( pGroup->Remove(CComBSTR("Junk")), UNITS_E_BADUNITTAG );

   // Successful removal
   TRY_TEST( pGroup->get_Count(&count), S_OK );
   TRY_TEST( count, 1 );
   TRY_TEST( pGroup->Remove(CComBSTR("mm")), S_OK );
   TRY_TEST( pGroup->get_Count(&count), S_OK );
   TRY_TEST( count, 0 );

   // ****************************************************
   // * Test Item
   // ****************************************************
   
   // Add a few so we have something to get
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("mm"),unitsSI,pFormatter,VARIANT_FALSE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("ft"),unitsUS,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("m"),unitsSI,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("in"),unitsUS,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );

   // Bad input
   pDispUnit.Release();
   TRY_TEST( pGroup->get_Item(NULL,&pDispUnit), E_INVALIDARG );
   TRY_TEST( pGroup->get_Item(CComBSTR("mm"),NULL), E_POINTER );
   TRY_TEST( pGroup->get_Item(CComBSTR("Junk"),&pDispUnit), UNITS_E_BADUNITTAG );

   // Success
   pDispUnit.Release();
   TRY_TEST( pGroup->get_Item(CComBSTR("ft"),&pDispUnit), S_OK );

   // verify the attributes of the display unit
   pDispUnit->get_UnitTag(&bstrTest);
   TRY_TEST( wcscmp( bstrTest,CComBSTR("ft")), 0 );

   VARIANT_BOOL bIsDefault;
   pDispUnit->IsDefault(&bIsDefault);
   TRY_TEST(bIsDefault,VARIANT_TRUE);

   // ****************************************************
   // * Test Default
   // ****************************************************

   // You can designate as many display units "default" as you like. However, only
   // the first one will be the actually default, until it is removed from the collection
   pDispUnit.Release();
   TRY_TEST( pGroup->get_Default(umSI,NULL), E_POINTER);
   TRY_TEST( pGroup->get_Default(umSI,&pDispUnit), S_OK);
   pDispUnit->get_UnitTag(&bstrTest);
   TRY_TEST( wcscmp( bstrTest,CComBSTR("m")), 0 );

   pDispUnit.Release();
   TRY_TEST( pGroup->get_Default(umUS,&pDispUnit), S_OK);
   pDispUnit->get_UnitTag(&bstrTest);
   TRY_TEST( wcscmp( bstrTest,CComBSTR("ft")), 0 );

   // Clear the display units and create some more with different default attributes
   pGroup->Clear();
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("mm"),unitsAll,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("ft"),unitsUS,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("m"),unitsSI,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("in"),unitsUS,pFormatter,VARIANT_TRUE,&pDispUnit), S_OK );

   // test default unit
   pDispUnit.Release();
   TRY_TEST( pGroup->get_Default(umSI,&pDispUnit), S_OK);
   pDispUnit->get_UnitTag(&bstrTest);
   TRY_TEST( wcscmp( bstrTest,CComBSTR("mm")), 0 );

   pDispUnit.Release();
   TRY_TEST( pGroup->get_Default(umUS,&pDispUnit), S_OK);
   pDispUnit->get_UnitTag(&bstrTest);
   TRY_TEST( wcscmp( bstrTest,CComBSTR("mm")), 0 );


   // Clear the display units and create some without a single one being the default
   pGroup->Clear();
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("mm"),unitsAll,pFormatter,VARIANT_FALSE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("ft"),unitsUS,pFormatter,VARIANT_FALSE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("m"),unitsSI,pFormatter,VARIANT_FALSE,&pDispUnit), S_OK );
   pDispUnit.Release();
   TRY_TEST( pGroup->Add(CComBSTR("in"),unitsUS,pFormatter,VARIANT_FALSE,&pDispUnit), S_OK );

   // test default unit
   pDispUnit.Release();
   TRY_TEST( pGroup->get_Default(umSI,&pDispUnit), UNITS_E_DEFAULTNOTFOUND);

   //******************************************
   //* Test _EnumDisplayUnits
   //******************************************
   CComPtr<IEnumDisplayUnits> pEnum;
   TRY_TEST(pGroup->get__EnumDisplayUnits(NULL),E_POINTER);
   TRY_TEST(pGroup->get__EnumDisplayUnits(&pEnum),S_OK);

   // ****************************************************
   // * Test ISupportErrorInfo
   // ****************************************************
   CComQIPtr<ISupportErrorInfo>  pSEI(pGroup);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IDisplayUnitGroup ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
