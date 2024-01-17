///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// TestUnitType.cpp: implementation of the CTestUnitType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUnitType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUnitType::CTestUnitType()
{

}

CTestUnitType::~CTestUnitType()
{

}

void CTestUnitType::Test()
{
   CComPtr<IUnitServer> unitServer;
   unitServer.CoCreateInstance( CLSID_UnitServer );

   CComPtr<IUnitTypes> unitTypes;
   unitServer->get_UnitTypes(&unitTypes);

   // Create a unit type to manipulate during testing
   CComPtr<IUnitType> unitType;
   unitTypes->Add(CComBSTR("MyUnitType"),20,20,20,20,20,&unitType);

   Float64 val;
   TRY_TEST( unitType->get_Angle(nullptr),E_POINTER);
   TRY_TEST( unitType->get_Angle(&val), S_OK );
   TRY_TEST( IsEqual(val,20.0), true );

   TRY_TEST( unitType->get_Length(nullptr),E_POINTER);
   TRY_TEST( unitType->get_Length(&val), S_OK );
   TRY_TEST( IsEqual(val,20.0), true );

   TRY_TEST( unitType->get_Mass(nullptr),E_POINTER);
   TRY_TEST( unitType->get_Mass(&val), S_OK );
   TRY_TEST( IsEqual(val,20.0), true );

   TRY_TEST( unitType->get_Temperature(nullptr),E_POINTER);
   TRY_TEST( unitType->get_Temperature(&val), S_OK );
   TRY_TEST( IsEqual(val,20.0), true );

   TRY_TEST( unitType->get_Time(nullptr),E_POINTER);
   TRY_TEST( unitType->get_Time(&val), S_OK );
   TRY_TEST( IsEqual(val,20.0), true );

   CComPtr<IUnits> units;
   TRY_TEST( unitType->get_Units(nullptr), E_POINTER );
   TRY_TEST( unitType->get_Units(&units), S_OK );

   CComPtr<IUnitServer> testUnitServer;
   TRY_TEST( unitType->get_UnitServer(nullptr), E_POINTER );
   TRY_TEST( unitType->get_UnitServer(&testUnitServer), S_OK );
   TRY_TEST( testUnitServer.IsEqualObject(unitServer), true );

   CComBSTR bstrLabel;
   TRY_TEST( unitType->get_Label(nullptr), E_POINTER );
   TRY_TEST( unitType->get_Label(&bstrLabel), S_OK );
   TRY_TEST( wcscmp(bstrLabel,CComBSTR("MyUnitType")),0);

   ///////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(unitType);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnitType ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
