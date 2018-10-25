///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2018  Washington State Department of Transportation
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

// TestDocUnitSystem.cpp: implementation of the CTestDocUnitSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDocUnitSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDocUnitSystem::CTestDocUnitSystem()
{
   m_bTestState = false;
}

CTestDocUnitSystem::~CTestDocUnitSystem()
{

}

void CTestDocUnitSystem::ConfigureDisplayUnits(IDisplayUnitMgr2* pDUM)
{
   CComPtr<IDisplayUnit> du;

   CComPtr<IDisplayUnitFormatter> formatter;
   formatter.CoCreateInstance(CLSID_DisplayUnitFormatter);
   formatter->FormatSpecifiers(6,3,tjRight,nftFixed,0.0001);

   CComPtr<IDisplayUnitGroup> grpLongLength;
   pDUM->Add(CComBSTR("LongLength"),CComBSTR("Length"),&grpLongLength);

   grpLongLength->Add(CComBSTR("ft"),unitsUS,formatter,VARIANT_TRUE,&du);
   du.Release();
   grpLongLength->Add(CComBSTR("m"), unitsSI,formatter,VARIANT_TRUE,&du);

   CComPtr<IDisplayUnitGroup> grpBigForce;
   pDUM->Add(CComBSTR("BigForce"),CComBSTR("Force"),&grpBigForce);
}

void CTestDocUnitSystem::Test()
{
   CComObject<CTestDocUnitSystem>* pMe;
   CComObject<CTestDocUnitSystem>::CreateInstance(&pMe);
   pMe->AddRef();
   CComPtr<IUnknown> punk(pMe);

   CComPtr<IDocUnitSystem> unitSystem;
   TRY_TEST( unitSystem.CoCreateInstance( CLSID_DocUnitSystem ), S_OK );

   DWORD dwCookie;
   TRY_TEST(AtlAdvise(unitSystem,punk,IID_IDocUnitSystemEvents,&dwCookie),S_OK);

   CComPtr<IUnitModeController> umc;
   TRY_TEST( unitSystem->get_UnitModeController(nullptr), E_POINTER );
   TRY_TEST( unitSystem->get_UnitModeController(&umc), S_OK );
   TRY_TEST( umc != 0, true );

   // The following tests occur without the DocUnitSystem being
   // associated with an AppUnitSystem. The purpose of these
   // tests is to determine of the DocUnitSystem correctly returns an
   // error.

   // Get the AppUnitSystem
   // Call should not succeeded. Point is nullptr because DocUnitSystem
   // hasn't been associated with an AppUnitSystem yet
   CComPtr<IAppUnitSystem> appUnitSys;
   TRY_TEST(unitSystem->get_AppUnitSystem(&appUnitSys),S_OK);
   TRY_TEST(appUnitSys == nullptr,true);

   // Test Format
   CComBSTR bstrTest;
   TRY_TEST(unitSystem->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),UNITS_E_APPUNITSYSNOTSET);

   // Test Tag property
   CComBSTR tag;
   unitSystem->put_UnitMode(umSI);
   TRY_TEST(unitSystem->get_Tag(CComBSTR("LongLength"),&tag),UNITS_E_APPUNITSYSNOTSET);

   // Test ConvertToDisplayUnits and ConvertFromDisplayUnits
   Float64 result;
   TRY_TEST(unitSystem->ConvertToDisplayUnits(10.0,CComBSTR("LongLength"),&result),UNITS_E_APPUNITSYSNOTSET);
   TRY_TEST(unitSystem->ConvertFromDisplayUnits(result,CComBSTR("LongLength"),&result),UNITS_E_APPUNITSYSNOTSET);

   ////////////////////////////////////////////////////
   // Create AppUnitSystem and associated with DocUnitSystem
   CComPtr<IAppUnitSystem> appUnitSystem;
   appUnitSystem.CoCreateInstance(CLSID_AppUnitSystem);
   TRY_TEST(unitSystem->putref_AppUnitSystem(nullptr), E_INVALIDARG);
   TRY_TEST(unitSystem->putref_AppUnitSystem(appUnitSystem), S_OK);
   CComPtr<IAppUnitSystem> testAppUnitSystem;
   TRY_TEST(unitSystem->get_AppUnitSystem(nullptr), E_POINTER);
   TRY_TEST(unitSystem->get_AppUnitSystem(&testAppUnitSystem),S_OK);
   TRY_TEST(appUnitSystem.IsEqualObject(testAppUnitSystem),true);
   testAppUnitSystem.Release();

   //////////////////////////////////////////////////
   // Configure the display units
   CComPtr<IDisplayUnitMgr2> dum;
   appUnitSystem->get_DisplayUnitMgr(&dum);
   ConfigureDisplayUnits(dum);

   // Get the display unit formatter so we can manipulate it
   CComPtr<IDisplayUnitFormatter> pLengthFormatter;
   CComPtr<IDisplayUnitGroup> duGroup;
   CComPtr<IDisplayUnit> du;
   dum->get_Item(CComBSTR("LongLength"),&duGroup);
   duGroup->get_Default(umUS,&du); // default is same for US and SI
   du->get_Formatter(&pLengthFormatter);

   // done with display unit mgr;
   dum.Release();

   ////////////////////////////////////////////////////
   // Test Format
   TRY_TEST(unitSystem->Format(10.0,nullptr,VARIANT_TRUE,&bstrTest),E_INVALIDARG);
   TRY_TEST(unitSystem->Format(10.0,CComBSTR("Junk"),VARIANT_TRUE,&bstrTest),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(unitSystem->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,nullptr),E_POINTER);

   TRY_TEST(unitSystem->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("10.000 m") ), 0);

   TRY_TEST(unitSystem->Format(1.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR(" 1.000 m") ), 0);

   // Test scientific notation
   pLengthFormatter->FormatSpecifiers(5,3,tjRight,nftScientific,0.0001);
   TRY_TEST(unitSystem->Format(11000.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("1.100e+04 m") ), 0);

   // Test engineering notation
   pLengthFormatter->FormatSpecifiers(6,3,tjRight,nftEngineering,0.0001);
   TRY_TEST(unitSystem->Format(11000.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("11.000e+003 m") ), 0);

   unitSystem->put_UnitMode(umUS);

   pLengthFormatter->FormatSpecifiers(5,2,tjRight,nftFixed,0.0001);
   TRY_TEST(unitSystem->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("32.81 ft") ), 0);

   // Test for the case when a default display unit hasn't been designated
   unitSystem->put_UnitMode(umSI);
   TRY_TEST(unitSystem->Format(10.0,CComBSTR("BigForce"),VARIANT_TRUE,&bstrTest),UNITS_E_DEFAULTNOTFOUND);
   unitSystem->put_UnitMode(umUS);
   TRY_TEST(unitSystem->Format(10.0,CComBSTR("BigForce"),VARIANT_TRUE,&bstrTest),UNITS_E_DEFAULTNOTFOUND);

   //////////////////////////////////////////////
   // Test Tag property
   TRY_TEST(unitSystem->get_Tag(nullptr,&tag),E_INVALIDARG);
   TRY_TEST(unitSystem->get_Tag(CComBSTR("Junk"),&tag),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(unitSystem->get_Tag(CComBSTR("LongLength"),nullptr),E_POINTER);
   unitSystem->put_UnitMode(umSI);
   TRY_TEST(unitSystem->get_Tag(CComBSTR("LongLength"),&tag),S_OK);
   TRY_TEST( wcscmp(tag,CComBSTR("m")), 0 );
   unitSystem->put_UnitMode(umUS);
   TRY_TEST(unitSystem->get_Tag(CComBSTR("LongLength"),&tag),S_OK);
   TRY_TEST( wcscmp(tag,CComBSTR("ft")), 0 );

   ///////////////////////////////////////////////////////////
   // Test ConvertToDisplayUnits and ConvertFromDisplayUnits
   unitSystem->put_UnitMode(umSI);
   TRY_TEST(unitSystem->ConvertToDisplayUnits(10.0,CComBSTR("Junk"),&result),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(unitSystem->ConvertToDisplayUnits(10.0,nullptr,&result),E_INVALIDARG);
   TRY_TEST(unitSystem->ConvertToDisplayUnits(10.0,CComBSTR("LongLength"),nullptr),E_POINTER);
   TRY_TEST(unitSystem->ConvertToDisplayUnits(10.0,CComBSTR("LongLength"),&result),S_OK);
   unitSystem->put_UnitMode(umUS);
   TRY_TEST(unitSystem->ConvertFromDisplayUnits(10.0,CComBSTR("Junk"),&result),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(unitSystem->ConvertFromDisplayUnits(10.0,nullptr,&result),E_INVALIDARG);
   TRY_TEST(unitSystem->ConvertFromDisplayUnits(10.0,CComBSTR("LongLength"),nullptr),E_POINTER);
   TRY_TEST(unitSystem->ConvertFromDisplayUnits(result,CComBSTR("LongLength"),&result),S_OK);
   TRY_TEST( IsEqual(result,3.048),true);

   ////////////////////////////////////////////////////
   // Test Events

   // Change unit mode, should fire event regardless if it
   // is changed on the unit system or the unit mode controller
   pMe->InitEventTest();
   UnitModeType um;
   unitSystem->get_UnitMode(&um);
   unitSystem->put_UnitMode(um == umSI ? umUS : umSI);
   TRY_TEST(pMe->PassedEventTest(), true );
   
   pMe->InitEventTest();
   umc->get_UnitMode(&um);
   umc->put_UnitMode(um == umSI ? umUS : umSI);
   TRY_TEST(pMe->PassedEventTest(), true );

   ///////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(unitSystem);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IDocUnitSystem ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   ///////////////////////////////////////////////////////////////
   // Disconnection from Connection point
   TRY_TEST(AtlUnadvise(unitSystem,IID_IDocUnitSystemEvents,dwCookie),S_OK);

   pMe->Release();

   MoreTests();
}

void CTestDocUnitSystem::MoreTests()
{
   // Test to simulate a MDI app.
   // One AppUnitSystem and 2 DocUnitSystems each with a unit modes that change

   CComPtr<IAppUnitSystem> appUnitSys;
   appUnitSys.CoCreateInstance(CLSID_AppUnitSystem);

   // configure display units
   CComPtr<IDisplayUnitMgr2> dum;
   appUnitSys->get_DisplayUnitMgr(&dum);
   ConfigureDisplayUnits(dum);
   dum.Release();

   CComPtr<IDocUnitSystem> docUnitSys1;
   docUnitSys1.CoCreateInstance(CLSID_DocUnitSystem);
   docUnitSys1->putref_AppUnitSystem(appUnitSys);
   docUnitSys1->put_UnitMode(umSI);

   CComPtr<IDocUnitSystem> docUnitSys2;
   docUnitSys2.CoCreateInstance(CLSID_DocUnitSystem);
   docUnitSys2->putref_AppUnitSystem(appUnitSys);
   docUnitSys2->put_UnitMode(umUS);

   // Format some text strings
   CComBSTR bstrTest;
   TRY_TEST(docUnitSys1->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("10.000 m") ), 0);

   TRY_TEST(docUnitSys2->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("32.808 ft") ), 0);

   // Change unit mode for doc1
   docUnitSys1->put_UnitMode(umUS);
   TRY_TEST(docUnitSys1->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("32.808 ft") ), 0);
   
   TRY_TEST(docUnitSys2->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("32.808 ft") ), 0);

   // Change unit mode for doc2
   docUnitSys2->put_UnitMode(umSI);
   TRY_TEST(docUnitSys1->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("32.808 ft") ), 0);

   TRY_TEST(docUnitSys2->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("10.000 m") ), 0);
}

STDMETHODIMP CTestDocUnitSystem::OnUpdateDisplay()
{
   Pass();
   return S_OK;
}
