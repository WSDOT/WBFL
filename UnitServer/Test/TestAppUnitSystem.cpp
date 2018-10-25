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

// TestAppUnitSystem.cpp: implementation of the CTestAppUnitSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAppUnitSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAppUnitSystem::CTestAppUnitSystem()
{
   m_bTestState = false;
}

CTestAppUnitSystem::~CTestAppUnitSystem()
{

}

void CTestAppUnitSystem::Test()
{
   CComObject<CTestAppUnitSystem>* pMe;
   CComObject<CTestAppUnitSystem>::CreateInstance(&pMe);
   pMe->AddRef();
   CComPtr<IUnknown> punk(pMe);

   CComPtr<IAppUnitSystem> unitSystem;
   TRY_TEST( unitSystem.CoCreateInstance( CLSID_AppUnitSystem ), S_OK );

   DWORD dwCookie;
   TRY_TEST(AtlAdvise(unitSystem,punk,IID_IUnitSystemEvents,&dwCookie),S_OK);

   CComPtr<IDisplayUnitMgr2> dum;
   TRY_TEST( unitSystem->get_DisplayUnitMgr(nullptr), E_POINTER );
   TRY_TEST( unitSystem->get_DisplayUnitMgr(&dum), S_OK );
   TRY_TEST( dum != 0, true );

   CComPtr<IUnitServer> us;
   TRY_TEST( unitSystem->get_UnitServer(nullptr), E_POINTER );
   TRY_TEST( unitSystem->get_UnitServer(&us), S_OK );
   TRY_TEST( us != 0, true );

   ////////////////////////////////////////////////////
   // Test ConvertFromBaseUnits and ConvertToBaseUnits
   CComPtr<IUnitTypes> pUnitTypes;
   us->get_UnitTypes(&pUnitTypes);
   CComPtr<IUnitType> pUnitType;
   pUnitTypes->get_Item(CComVariant(CComBSTR("Length")),&pUnitType);
   CComPtr<IUnits> pUnits;
   pUnitType->get_Units(&pUnits);
   CComPtr<IUnit> pMeter;
   CComPtr<IUnit> pFeet;
   pUnits->get_Item(CComVariant(CComBSTR("m")),&pMeter);
   pUnits->get_Item(CComVariant(CComBSTR("ft")),&pFeet);

   Float64 result;
   TRY_TEST( unitSystem->ConvertFromBaseUnits(10.0,CComVariant(1L),&result), E_INVALIDARG);
   TRY_TEST( unitSystem->ConvertToBaseUnits(10.0,CComVariant(1L),&result), E_INVALIDARG);

   TRY_TEST( unitSystem->ConvertFromBaseUnits(10.0,CComVariant(CComBSTR("ft")),&result), S_OK );
   TRY_TEST( IsEqual(result,32.8084), true );

   TRY_TEST( unitSystem->ConvertToBaseUnits(10.0,CComVariant(CComBSTR("m")),&result), S_OK);
   TRY_TEST( IsEqual(result,10.0), true );

// This test no longer valid after IDispatch was removed
//   CComQIPtr<IDispatch> pDisp(pFeet);
//   TRY_TEST( unitSystem->ConvertFromBaseUnits(10.0,CComVariant(pDisp),&result),S_OK);
//   TRY_TEST( IsEqual(result,32.8084), true );

   CComQIPtr<IUnknown,&IID_IUnknown> pUnk(pMeter);
   TRY_TEST( unitSystem->ConvertToBaseUnits(10.0,CComVariant(pUnk),&result),S_OK);
   TRY_TEST( IsEqual(result,10.0), true );

   ////////////////////////////////////////////////////
   // Test Events
   pMe->InitEventTest();
   pUnitTypes.Release();
   us->get_UnitTypes(&pUnitTypes);
   pUnitTypes->Clear();
   TRY_TEST(pMe->PassedEventTest(), true );
   
   ///////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(unitSystem);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IAppUnitSystem ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   ///////////////////////////////////////////////////////////////
   // Disconnection from Connection point
   TRY_TEST(AtlUnadvise(unitSystem,IID_IUnitSystemEvents,dwCookie),S_OK);

   pMe->Release();
}

STDMETHODIMP CTestAppUnitSystem::OnUpdateDisplay()
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestAppUnitSystem::OnUnitServerChanged()
{
   Pass();
   return S_OK;
}
