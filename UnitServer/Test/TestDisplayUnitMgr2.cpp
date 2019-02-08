///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2019  Washington State Department of Transportation
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

// TestDisplayUnitMgr2.cpp: implementation of the CTestDisplayUnitMgr2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDisplayUnitMgr2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestDisplayUnitMgr2::CTestDisplayUnitMgr2()
{
   m_bTestState = false;
}

CTestDisplayUnitMgr2::~CTestDisplayUnitMgr2()
{

}

void CTestDisplayUnitMgr2::Test()
{
   CComObject<CTestDisplayUnitMgr2>* pMe;
   CComObject<CTestDisplayUnitMgr2>::CreateInstance(&pMe);
   pMe->AddRef();
   CComPtr<IUnknown> punk(pMe);

   // Test creation
   // This object is not directly creatable.
   CComPtr<IDisplayUnitMgr2> pDisplayUnitMgr;

   // object should not be registered
   TRY_TEST( pDisplayUnitMgr.CoCreateInstance( CComBSTR("WBFLUnitServer.DisplayUnitMgr2") ), CO_E_CLASSSTRING );

   // this line should not compile
//   pDisplayUnitMgr.CoCreateInstance( CLSID_DisplayUnitMgr );

   CComPtr<IAppUnitSystem> pUnitSystem;
   pUnitSystem.CoCreateInstance( CLSID_AppUnitSystem );
   pUnitSystem->get_DisplayUnitMgr(&pDisplayUnitMgr);
   ATLASSERT(pDisplayUnitMgr != 0);

   DWORD dwCookie;
   TRY_TEST(AtlAdvise(pDisplayUnitMgr,punk,IID_IDisplayUnitMgrEvents,&dwCookie),S_OK);

   //
   // Add
   //
   CComPtr<IDisplayUnitGroup> pGroup;
   CComBSTR bstrTest;

   TRY_TEST(pDisplayUnitMgr->Add(CComBSTR("LongLength"),CComBSTR("Length"),nullptr),E_POINTER);
   TRY_TEST(pDisplayUnitMgr->Add(CComBSTR("LongLength"),CComBSTR("Baseball"),&pGroup),UNITS_E_BADUNITTYPE);

   pMe->InitEventTest();
   TRY_TEST(pDisplayUnitMgr->Add(CComBSTR("LongLength"),CComBSTR("Length"),&pGroup),S_OK);
   TRY_TEST(pMe->PassedEventTest(),true);

   pGroup->get_Name(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("LongLength") ), 0);

   pGroup->get_UnitType(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("Length") ), 0);

   // Add a couple of display units (m=SI default, mm, ft=US default)
   CComPtr<IDisplayUnitFormatter> pLengthFormatter;
   pLengthFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   pLengthFormatter->FormatSpecifiers(6,3,tjRight,nftFixed,0.0001);
   CComPtr<IDisplayUnit> pDispUnit;

   pMe->InitEventTest();
   pGroup->Add(CComBSTR("m"),unitsSI,pLengthFormatter,VARIANT_TRUE,&pDispUnit);
   TRY_TEST(pMe->PassedEventTest(), true );

   CComPtr<IDisplayUnitFormatter> pFormatter;
   pDispUnit.Release();
   pFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   pFormatter->FormatSpecifiers(4,0,tjRight,nftFixed,0.0001);
   pGroup->Add(CComBSTR("mm"),unitsSI,pFormatter,VARIANT_FALSE,&pDispUnit);

   pFormatter.Release();
   pDispUnit.Release();
   pFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   pFormatter->FormatSpecifiers(5,2,tjRight,nftFixed,0.0001);
   pGroup->Add(CComBSTR("ft"),unitsUS,pFormatter,VARIANT_TRUE,&pDispUnit);

   // Try to create the same group twice.
   // Event should not fire
   pGroup.Release();
   pMe->InitEventTest();
   TRY_TEST(pDisplayUnitMgr->Add(CComBSTR("LongLength"),CComBSTR("Length"),&pGroup),UNITS_E_GROUPALREADYDEFINED);
   TRY_TEST(pMe->PassedEventTest(),false);

   // Add another display unit group
   pGroup.Release();
   TRY_TEST(pDisplayUnitMgr->Add(CComBSTR("BigForce"),CComBSTR("Force"),&pGroup),S_OK);
   pGroup->get_Name(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("BigForce") ), 0);

   pGroup->get_UnitType(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("Force") ), 0);

   // Add a non-default display unit
   pFormatter.Release();
   pDispUnit.Release();
   pFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   pFormatter->FormatSpecifiers(12,6,tjRight,nftFixed,0.0001);
   pGroup->Add(CComBSTR("kN"),unitsSI,pFormatter,VARIANT_FALSE,&pDispUnit);

   ///////////////////////////////////////////////////
   // Test events

   // Change the formatter to see if an event fires
   pMe->InitEventTest();
   pFormatter.Release();
   pFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   pFormatter->FormatSpecifiers(6,3,tjRight,nftFixed,0.0001);
   pMe->InitEventTest();
   pDispUnit->putref_Formatter(pFormatter);
   TRY_TEST(pMe->PassedEventTest(),true);

   // Remove the last display unit to see if an event fires
   pMe->InitEventTest();
   pGroup->Remove(CComBSTR("kN"));
   TRY_TEST(pMe->PassedEventTest(),true);

   // Test for the case when you add a second default display unit for the same
   // system of units

   // Add another display unit group
   pGroup.Release();
   TRY_TEST(pDisplayUnitMgr->Add(CComBSTR("LittleForce"),CComBSTR("Force"),&pGroup),S_OK);
   pGroup->get_Name(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("LittleForce") ), 0);

   pGroup->get_UnitType(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("Force") ), 0);

   // Add a few display units
   pFormatter.Release();
   pDispUnit.Release();
   pFormatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   pFormatter->FormatSpecifiers(12,6,tjRight,nftFixed,0.0001);
   pGroup->Add(CComBSTR("kN"),unitsSI,pFormatter,VARIANT_FALSE,&pDispUnit);

   // Clear the group to see if an event fires
   pMe->InitEventTest();
   pGroup->Clear();
   TRY_TEST(pMe->PassedEventTest(), true);

   // Test Count
   CollectionIndexType count;
   TRY_TEST(pDisplayUnitMgr->get_Count(nullptr), E_POINTER);
   TRY_TEST(pDisplayUnitMgr->get_Count(&count),S_OK);
   TRY_TEST(count,3);

   // Test Item
   pGroup.Release();
   TRY_TEST(pDisplayUnitMgr->get_Item(nullptr,&pGroup),E_INVALIDARG);
   TRY_TEST(pDisplayUnitMgr->get_Item(CComBSTR("LittleForce"),nullptr),E_POINTER);
   TRY_TEST(pDisplayUnitMgr->get_Item(CComBSTR("Junk"),&pGroup),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(pDisplayUnitMgr->get_Item(CComBSTR("LittleForce"),&pGroup),S_OK);
   pGroup->get_Name(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("LittleForce") ), 0);

   // Test Remove
   TRY_TEST( pDisplayUnitMgr->Remove(nullptr), E_INVALIDARG );
   TRY_TEST( pDisplayUnitMgr->Remove(CComBSTR("Junk")), UNITS_E_BADDISPLAYUNITGROUP );

   pMe->InitEventTest();
   TRY_TEST(pDisplayUnitMgr->Remove(CComBSTR("BigForce")), S_OK );
   TRY_TEST(pMe->PassedEventTest(),true);

   pDisplayUnitMgr->get_Count(&count);
   TRY_TEST(count,2);

   // Test Clear
   pMe->InitEventTest();
   TRY_TEST(pDisplayUnitMgr->Clear(), S_OK);
   TRY_TEST(pMe->PassedEventTest(), true );

   pDisplayUnitMgr->get_Count(&count);
   TRY_TEST(count,0);

   //******************************************
   //* Test _EnumDisplayUnitGroups
   //******************************************
   CComPtr<IEnumDisplayUnitGroups> pEnum;
   TRY_TEST(pDisplayUnitMgr->get__EnumDisplayUnitGroups(nullptr),E_POINTER);
   TRY_TEST(pDisplayUnitMgr->get__EnumDisplayUnitGroups(&pEnum),S_OK);

   //////////////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(pDisplayUnitMgr);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IDisplayUnitMgr2 ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   ///////////////////////////////////////////////////////////////
   // Disconnection from Connection point
   TRY_TEST(AtlUnadvise(pDisplayUnitMgr,IID_IDisplayUnitMgrEvents,dwCookie),S_OK);

   pMe->Release();
}

STDMETHODIMP CTestDisplayUnitMgr2::OnFormatChanged(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr2::OnDisplayUnitCreated(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr2::OnDisplayUnitRemoved(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/BSTR displayUnit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr2::OnDisplayUnitGroupCleared(/*[in]*/ IDisplayUnitGroup* group)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr2::OnDisplayUnitGroupCreated(/*[in]*/ IDisplayUnitGroup* group)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr2::OnDisplayUnitGroupRemoved(/*[in]*/ BSTR group)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr2::OnDisplayUnitGroupsCleared()
{
   Pass();
   return S_OK;
}

