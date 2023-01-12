///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// TestUnitSystem.cpp: implementation of the CTestUnitSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUnitSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUnitSystem::CTestUnitSystem()
{
   m_bTestState = false;
}

CTestUnitSystem::~CTestUnitSystem()
{

}

void CTestUnitSystem::Test()
{
   CComObject<CTestUnitSystem>* pMe;
   CComObject<CTestUnitSystem>::CreateInstance(&pMe);
   pMe->AddRef();
   CComPtr<IUnknown> punk(pMe);

   CComPtr<IUnitSystem> unitSystem;
   TRY_TEST( unitSystem.CoCreateInstance( CLSID_UnitSystem ), S_OK );

   DWORD dwCookie;
   TRY_TEST(AtlAdvise(unitSystem,punk,IID_IUnitSystemEvents,&dwCookie),S_OK);

   CComPtr<IDisplayUnitMgr> dum;
   TRY_TEST( unitSystem->get_DisplayUnitMgr(nullptr), E_POINTER );
   TRY_TEST( unitSystem->get_DisplayUnitMgr(&dum), S_OK );
   TRY_TEST( dum != 0, true );

   CComPtr<IUnitModeController> umc;
   TRY_TEST( unitSystem->get_UnitModeController(nullptr), E_POINTER );
   TRY_TEST( unitSystem->get_UnitModeController(&umc), S_OK );
   TRY_TEST( umc != 0, true );

   CComPtr<IUnitServer> us;
   TRY_TEST( unitSystem->get_UnitServer(nullptr), E_POINTER );
   TRY_TEST( unitSystem->get_UnitServer(&us), S_OK );
   TRY_TEST( us != 0, true );

   ////////////////////////////////////////////////////
   // Test Events
   pMe->InitEventTest();
   UnitModeType um;
   umc->get_UnitMode(&um);
   umc->put_UnitMode(um == umUS ? umSI : umUS);
   TRY_TEST(pMe->PassedEventTest(), true );

   pMe->InitEventTest();
   CComPtr<IUnitTypes> pUnitTypes;
   us->get_UnitTypes(&pUnitTypes);
   pUnitTypes->Clear();
   TRY_TEST(pMe->PassedEventTest(), true );
   pUnitTypes.Release();


   ///////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(unitSystem);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnitSystem ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   pSEI.Release();

   ///////////////////////////////////////////////////////////////
   // Disconnection from Connection point
   TRY_TEST(AtlUnadvise(unitSystem,IID_IUnitSystemEvents,dwCookie),S_OK);

   pMe->Release();

   umc.Release();
   dum.Release();
   us.Release();
   unitSystem.Release();
}

STDMETHODIMP CTestUnitSystem::OnUpdateDisplay()
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestUnitSystem::OnUnitServerChanged()
{
   Pass();
   return S_OK;
}
