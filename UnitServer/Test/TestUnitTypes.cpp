///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
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

// TestUnitTypes.cpp: implementation of the CTestUnitTypes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUnitTypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUnitTypes::CTestUnitTypes()
{

}

CTestUnitTypes::~CTestUnitTypes()
{

}

void CTestUnitTypes::Test()
{
   CComPtr<IUnitServer> unitServer;
   unitServer.CoCreateInstance( CLSID_UnitServer );

   CComPtr<IUnitTypes> unitTypes;
   unitServer->get_UnitTypes(&unitTypes);

   /////////////////////////////////////////////////////
   // Test Count
   CollectionIndexType count;
   TRY_TEST(unitTypes->get_Count(nullptr),E_POINTER);
   TRY_TEST(unitTypes->get_Count(&count),S_OK);
   TRY_TEST(count,16); // Default configuration

   /////////////////////////////////////////////////////
   // Test Add
   //
   CComPtr<IUnitType> unitType;
   TRY_TEST( unitTypes->Add(nullptr,0,1,-1,0,0,&unitType), E_INVALIDARG );
   TRY_TEST( unitTypes->Add(CComBSTR("Mass"),0,1,-1,0,0,&unitType), UNITS_E_UNITTYPEALREADYDEFINED );
   TRY_TEST( unitTypes->Add(CComBSTR("Acceleration"),0,1,-2,0,0,nullptr), S_OK );
   TRY_TEST( unitTypes->Add(CComBSTR("Velocity"),0,1,-1,0,0,&unitType), S_OK );
   TRY_TEST( unitType != 0, true );

   // check the properties of the new unit type
   CComBSTR bstrType;
   Float64 val;
   unitType->get_Label(&bstrType);
   TRY_TEST( wcscmp(bstrType,CComBSTR("Velocity"))==0,true);
   unitType->get_Angle(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Length(&val);
   TRY_TEST( IsEqual(val,1.0), true );
   unitType->get_Mass(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Temperature(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Time(&val);
   TRY_TEST( IsEqual(val,-1.0), true );

   /////////////////////////////////////////////////////
   // Test Remove
   TRY_TEST( unitTypes->Remove(CComVariant()), E_INVALIDARG );
   TRY_TEST( unitTypes->Remove(CComVariant("Junk")),UNITS_E_BADUNITTYPE);
   TRY_TEST( unitTypes->Remove(CComVariant(-1L)),E_INVALIDARG);
   TRY_TEST( unitTypes->Remove(CComVariant(100L)),E_INVALIDARG);
   TRY_TEST( unitTypes->Remove(CComVariant("Moment")), S_OK );
   TRY_TEST( unitTypes->Remove(CComVariant(14L)), S_OK);
   TRY_TEST( unitTypes->Remove(CComVariant(unitType)),S_OK);

   //////////////////////////////////////////////////////
   // Test get_Item
   unitType.Release();
   TRY_TEST( unitTypes->get_Item(CComVariant(-1L),&unitType), E_INVALIDARG);
   TRY_TEST( unitTypes->get_Item(CComVariant(1000L),&unitType), E_INVALIDARG);
   TRY_TEST( unitTypes->get_Item(CComVariant(),&unitType), E_INVALIDARG );
   TRY_TEST( unitTypes->get_Item(CComVariant("Junk"),&unitType), E_INVALIDARG );
   TRY_TEST( unitTypes->get_Item(CComVariant(0L),nullptr), E_POINTER);
   TRY_TEST( unitTypes->get_Item(CComVariant(0L),&unitType), S_OK );

   unitType->get_Label(&bstrType);
   TRY_TEST( wcscmp(bstrType,CComBSTR("Mass"))==0,true);
   unitType->get_Angle(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Length(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Mass(&val);
   TRY_TEST( IsEqual(val,1.0), true );
   unitType->get_Temperature(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Time(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   unitType.Release();
   TRY_TEST( unitTypes->get_Item(CComVariant(1L),&unitType), S_OK );

   unitType->get_Label(&bstrType);
   TRY_TEST( wcscmp(bstrType,CComBSTR("Length"))==0,true);
   unitType->get_Angle(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Length(&val);
   TRY_TEST( IsEqual(val,1.0), true );
   unitType->get_Mass(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Temperature(&val);
   TRY_TEST( IsEqual(val,0.0), true );
   unitType->get_Time(&val);
   TRY_TEST( IsEqual(val,0.0), true );

   ///////////////////////////////////////////////////////
   // Test EnumUnitTypes
   CComPtr<IEnumUnitTypes> Enum;
   TRY_TEST( unitTypes->get__EnumUnitTypes(nullptr), E_POINTER );
   TRY_TEST( unitTypes->get__EnumUnitTypes(&Enum), S_OK );
   TRY_TEST( Enum != 0 , true );

   ///////////////////////////////////////////////////////
   // Test Clear
   TRY_TEST( unitTypes->Clear(), S_OK );
   unitTypes->get_Count(&count);
   TRY_TEST( count, 0 );

   ///////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(unitTypes);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnitTypes ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
