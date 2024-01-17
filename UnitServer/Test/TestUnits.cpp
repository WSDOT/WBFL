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

// TestUnits.cpp: implementation of the CTestUnits class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUnits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUnits::CTestUnits()
{

}

CTestUnits::~CTestUnits()
{

}

void CTestUnits::Test()
{
   // We have to do some work to drill down into the unit server to get a
   // units collection. To make things easy, we will just get the units 
   // collection for the first unit type.
   CComPtr<IUnitServer> unitServer;
   unitServer.CoCreateInstance( CLSID_UnitServer );

   CComPtr<IUnitTypes> unitTypes;
   unitServer->get_UnitTypes(&unitTypes);

   CComPtr<IUnitType> unitType;
   unitTypes->get_Item(CComVariant(1),&unitType);

   CComPtr<IUnits> units;
   unitType->get_Units(&units);

   TRY_TEST( units != 0, true );

   ///////////////////////////////////////////////////////
   // Let's clear out the units collection so we can manipulate
   // it with our own data
   TRY_TEST( units->Clear(), S_OK );

   ///////////////////////////////////////////////////////
   // Test Count
   IndexType count;
   TRY_TEST( units->get_Count(nullptr), E_POINTER );
   TRY_TEST( units->get_Count(&count), S_OK );
   TRY_TEST( count, 0 );

   ///////////////////////////////////////////////////////
   // Test Add
   CComPtr<IUnit> pUnit;
   TRY_TEST(units->Add(nullptr,0,1,0,unitsSI,&pUnit),E_INVALIDARG);
   TRY_TEST(units->Add(CComBSTR("a"),0,1,0,unitsSI,nullptr),S_OK);
   TRY_TEST(units->Add(CComBSTR("a"),1,1,1,unitsSI,nullptr),UNITS_E_UNITALREADYDEFINED); 

   pUnit.Release();
   TRY_TEST(units->Add(CComBSTR("b"),0,1,0,unitsSI,&pUnit),S_OK);

   pUnit.Release();
   TRY_TEST(units->Add(CComBSTR("c"),0,1,0,unitsSI,&pUnit),S_OK);

   TRY_TEST( units->get_Count(&count), S_OK );
   TRY_TEST( count, 3 );

   ///////////////////////////////////////////////////////
   // Test Item
   pUnit.Release();
   TRY_TEST( units->get_Item(CComVariant(),&pUnit), E_INVALIDARG );
   TRY_TEST( units->get_Item(CComVariant(-1L),&pUnit), E_INVALIDARG );
   TRY_TEST( units->get_Item(CComVariant(100L),&pUnit), E_INVALIDARG );
   TRY_TEST( units->get_Item(CComVariant(CComBSTR("Junk")),&pUnit), E_INVALIDARG );
   TRY_TEST( units->get_Item(CComVariant(0L),&pUnit), S_OK );
   CComBSTR bstrTag;
   pUnit->get_Tag(&bstrTag);
   TRY_TEST( wcscmp(bstrTag,CComBSTR("a")) == 0, true );

   pUnit.Release();
   TRY_TEST( units->get_Item(CComVariant(CComBSTR("b")),&pUnit), S_OK );
   pUnit->get_Tag(&bstrTag);
   TRY_TEST( wcscmp(bstrTag,CComBSTR("b")) == 0, true );

   pUnit.Release();
   TRY_TEST( units->get_Item(CComVariant((short)2),&pUnit), S_OK );
   pUnit->get_Tag(&bstrTag);
   TRY_TEST( wcscmp(bstrTag,CComBSTR("c")) == 0, true );

   ///////////////////////////////////////////////////////
   // Test _EnumUnits
   CComPtr<IEnumUnits> Enum;
   TRY_TEST( units->get__EnumUnits(nullptr), E_POINTER );
   TRY_TEST( units->get__EnumUnits(&Enum), S_OK );

   CComPtr<IUnit> pUnits[4];
   ULONG fetched;
   Enum->Next(3,&pUnits[0],&fetched);
   TRY_TEST( fetched, 3 );

   pUnits[0]->get_Tag(&bstrTag);
   TRY_TEST( wcscmp(bstrTag,CComBSTR("a")) == 0, true );

   pUnits[1]->get_Tag(&bstrTag);
   TRY_TEST( wcscmp(bstrTag,CComBSTR("b")) == 0, true );

   pUnits[2]->get_Tag(&bstrTag);
   TRY_TEST( wcscmp(bstrTag,CComBSTR("c")) == 0, true );

   ///////////////////////////////////////////////////////
   // Test Remove
   TRY_TEST( units->Remove(CComVariant()), E_INVALIDARG );
   TRY_TEST( units->Remove(CComVariant(-1L)), E_INVALIDARG );
   TRY_TEST( units->Remove(CComVariant(100L)), E_INVALIDARG );
   TRY_TEST( units->Remove(CComVariant(CComBSTR("Junk"))), E_INVALIDARG );
   TRY_TEST( units->Remove(CComVariant(0)), S_OK );
   units->get_Count(&count);
   TRY_TEST( count, 2 );
   TRY_TEST( units->Remove(CComVariant(CComBSTR("b"))), S_OK );
   units->get_Count(&count);
   TRY_TEST( count, 1 );

   pUnit.Release();
   units->get_Item(CComVariant(0L),&pUnit);
   pUnit->get_Tag(&bstrTag);
   TRY_TEST( wcscmp(bstrTag,CComBSTR("c")) == 0, true );

   ///////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(units);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnits ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}
