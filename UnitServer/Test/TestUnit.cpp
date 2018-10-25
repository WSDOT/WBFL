///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestUnit.cpp: implementation of the CTestUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUnit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUnit::CTestUnit()
{

}

CTestUnit::~CTestUnit()
{

}

void CTestUnit::Test()
{
   CComPtr<IUnitServer> unitServer;
   unitServer.CoCreateInstance( CLSID_UnitServer );

   CComPtr<IUnitTypes> unitTypes;
   unitServer->get_UnitTypes(&unitTypes);

   CComPtr<IUnitType> unitType;
   unitTypes->Add(CComBSTR("MyUnitType"),1,0,0,0,0,&unitType);

   CComPtr<IUnits> units;
   unitType->get_Units(&units);

   CComPtr<IUnit> unit;
   units->Add(CComBSTR("MyUnit"),1.0,2.0,3.0,unitsSI,&unit);

   TRY_TEST( unit != NULL, true );
   
   Float64 val;
   TRY_TEST( unit->get_PreTerm(NULL), E_POINTER );
   TRY_TEST( unit->get_PreTerm(&val), S_OK );
   TRY_TEST( IsEqual(val,1.0), true );

   TRY_TEST( unit->get_ConvFactor(NULL), E_POINTER );
   TRY_TEST( unit->get_ConvFactor(&val), S_OK );
   TRY_TEST( IsEqual(val,2.0), true );

   TRY_TEST( unit->get_PostTerm(NULL), E_POINTER );
   TRY_TEST( unit->get_PostTerm(&val), S_OK );
   TRY_TEST( IsEqual(val,3.0), true );

   CComBSTR bstrTag;
   TRY_TEST( unit->get_Tag(NULL), E_POINTER );
   TRY_TEST( unit->get_Tag(&bstrTag), S_OK );
   TRY_TEST( wcscmp(bstrTag,CComBSTR("MyUnit")), 0 );

   UnitSystemType ust;
   TRY_TEST( unit->get_UnitSystem(NULL), E_POINTER );
   TRY_TEST( unit->get_UnitSystem(&ust), S_OK );
   TRY_TEST( ust, unitsSI );

   CComPtr<IUnitType> pParent;
   TRY_TEST( unit->get_UnitType(NULL), E_POINTER );
   TRY_TEST( unit->get_UnitType(&pParent), S_OK );
   TRY_TEST( pParent.IsEqualObject( unitType ), true );

   CComPtr<IUnitServer> pParentSvr;
   TRY_TEST( unit->get_UnitServer(NULL), E_POINTER );
   TRY_TEST( unit->get_UnitServer(&pParentSvr), S_OK );
   TRY_TEST( pParentSvr.IsEqualObject( unitServer ), true );

   // Now release the unit server and see if the unit is still valid
   pParent.Release();
   unitType.Release();
   pParentSvr.Release();
   unitServer.Release();
   TRY_TEST( unit->get_UnitServer(&pParentSvr), S_OK );

   ///////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(unit);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnit ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
