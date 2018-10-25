///////////////////////////////////////////////////////////////////////
// Unit Test - Test driver for WBFLUnits library
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TestDisplayUnitMgr.cpp: implementation of the CTestDisplayUnitMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDisplayUnitMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestDisplayUnitMgr::CTestDisplayUnitMgr()
{
   m_bTestState = false;
}

CTestDisplayUnitMgr::~CTestDisplayUnitMgr()
{

}

void CTestDisplayUnitMgr::Test()
{
   CComObject<CTestDisplayUnitMgr>* pMe;
   CComObject<CTestDisplayUnitMgr>::CreateInstance(&pMe);
   pMe->AddRef();
   CComPtr<IUnknown> punk(pMe);

   // Test creation
   // This object is not directly creatable.
   CComPtr<IDisplayUnitMgr> pDisplayUnitMgr;

   // object should not be registered
   TRY_TEST( pDisplayUnitMgr.CoCreateInstance( CComBSTR("WBFLUnitServer.DisplayUnitMgr") ), CO_E_CLASSSTRING );

   // this line should not compile
//   pDisplayUnitMgr.CoCreateInstance( CLSID_DisplayUnitMgr );

   CComPtr<IUnitSystem> pUnitSystem;
   pUnitSystem.CoCreateInstance( CLSID_UnitSystem );
   pUnitSystem->get_DisplayUnitMgr(&pDisplayUnitMgr);
   ATLASSERT(pDisplayUnitMgr != 0);

   DWORD dwCookie;
   TRY_TEST(AtlAdvise(pDisplayUnitMgr,punk,IID_IDisplayUnitMgrEvents,&dwCookie),S_OK);

   //
   // Add
   //
   CComPtr<IDisplayUnitGroup> pGroup;
   CComBSTR bstrTest;

   TRY_TEST(pDisplayUnitMgr->Add(CComBSTR("LongLength"),CComBSTR("Length"),NULL),E_POINTER);
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
   TRY_TEST(pDisplayUnitMgr->get_Count(NULL), E_POINTER);
   TRY_TEST(pDisplayUnitMgr->get_Count(&count),S_OK);
   TRY_TEST(count,3);

   // Test Item
   pGroup.Release();
   TRY_TEST(pDisplayUnitMgr->get_Item(NULL,&pGroup),E_INVALIDARG);
   TRY_TEST(pDisplayUnitMgr->get_Item(CComBSTR("LittleForce"),NULL),E_POINTER);
   TRY_TEST(pDisplayUnitMgr->get_Item(CComBSTR("Junk"),&pGroup),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(pDisplayUnitMgr->get_Item(CComBSTR("LittleForce"),&pGroup),S_OK);
   pGroup->get_Name(&bstrTest);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("LittleForce") ), 0);

   // Test Format
   TRY_TEST(pDisplayUnitMgr->Format(10.0,NULL,VARIANT_TRUE,&bstrTest),E_INVALIDARG);
   TRY_TEST(pDisplayUnitMgr->Format(10.0,CComBSTR("Junk"),VARIANT_TRUE,&bstrTest),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(pDisplayUnitMgr->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,NULL),E_POINTER);

   TRY_TEST(pDisplayUnitMgr->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("10.000 m") ), 0);

   TRY_TEST(pDisplayUnitMgr->Format(1.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR(" 1.000 m") ), 0);

   // Test scientific notation
   pLengthFormatter->FormatSpecifiers(5,3,tjRight,nftScientific,0.0001);
   TRY_TEST(pDisplayUnitMgr->Format(11000.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("1.100e+004 m") ), 0);

   // Test engineering notation
   pLengthFormatter->FormatSpecifiers(6,3,tjRight,nftEngineering,0.0001);
   TRY_TEST(pDisplayUnitMgr->Format(11000.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("11.000e+003 m") ), 0);

   CComPtr<IUnitModeController> pUMC;
   pUnitSystem->get_UnitModeController(&pUMC);

   pUMC->put_UnitMode(umUS);

   TRY_TEST(pDisplayUnitMgr->Format(10.0,CComBSTR("LongLength"),VARIANT_TRUE,&bstrTest),S_OK);
   TRY_TEST(wcscmp( bstrTest, CComBSTR("32.81 ft") ), 0);

   // Test for the case when a default display unit hasn't been designated
   pUMC->put_UnitMode(umSI);
   TRY_TEST(pDisplayUnitMgr->Format(10.0,CComBSTR("BigForce"),VARIANT_TRUE,&bstrTest),UNITS_E_DEFAULTNOTFOUND);
   pUMC->put_UnitMode(umUS);
   TRY_TEST(pDisplayUnitMgr->Format(10.0,CComBSTR("BigForce"),VARIANT_TRUE,&bstrTest),UNITS_E_DEFAULTNOTFOUND);

   // Test Tag property
   CComBSTR tag;
   TRY_TEST(pDisplayUnitMgr->get_Tag(NULL,&tag),E_INVALIDARG);
   TRY_TEST(pDisplayUnitMgr->get_Tag(CComBSTR("Junk"),&tag),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(pDisplayUnitMgr->get_Tag(CComBSTR("LongLength"),NULL),E_POINTER);
   pUMC->put_UnitMode(umSI);
   TRY_TEST(pDisplayUnitMgr->get_Tag(CComBSTR("LongLength"),&tag),S_OK);
   TRY_TEST( wcscmp(tag,CComBSTR("m")), 0 );
   pUMC->put_UnitMode(umUS);
   TRY_TEST(pDisplayUnitMgr->get_Tag(CComBSTR("LongLength"),&tag),S_OK);
   TRY_TEST( wcscmp(tag,CComBSTR("ft")), 0 );

   // Test ConvertToDisplayUnits and ConvertFromDisplayUnits
   Float64 result;
   pUMC->put_UnitMode(umSI);
   TRY_TEST(pDisplayUnitMgr->ConvertToDisplayUnits(10.0,CComBSTR("Junk"),&result),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(pDisplayUnitMgr->ConvertToDisplayUnits(10.0,NULL,&result),E_INVALIDARG);
   TRY_TEST(pDisplayUnitMgr->ConvertToDisplayUnits(10.0,CComBSTR("LongLength"),NULL),E_POINTER);
   TRY_TEST(pDisplayUnitMgr->ConvertToDisplayUnits(10.0,CComBSTR("LongLength"),&result),S_OK);
   pUMC->put_UnitMode(umUS);
   TRY_TEST(pDisplayUnitMgr->ConvertFromDisplayUnits(10.0,CComBSTR("Junk"),&result),UNITS_E_BADDISPLAYUNITGROUP);
   TRY_TEST(pDisplayUnitMgr->ConvertFromDisplayUnits(10.0,NULL,&result),E_INVALIDARG);
   TRY_TEST(pDisplayUnitMgr->ConvertFromDisplayUnits(10.0,CComBSTR("LongLength"),NULL),E_POINTER);
   TRY_TEST(pDisplayUnitMgr->ConvertFromDisplayUnits(result,CComBSTR("LongLength"),&result),S_OK);
   TRY_TEST( IsEqual(result,3.048),true);

   // Test Remove
   TRY_TEST( pDisplayUnitMgr->Remove(NULL), E_INVALIDARG );
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
   TRY_TEST(pDisplayUnitMgr->get__EnumDisplayUnitGroups(NULL),E_POINTER);
   TRY_TEST(pDisplayUnitMgr->get__EnumDisplayUnitGroups(&pEnum),S_OK);

   //////////////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(pDisplayUnitMgr);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IDisplayUnitMgr ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   ///////////////////////////////////////////////////////////////
   // Disconnection from Connection point
   TRY_TEST(AtlUnadvise(pDisplayUnitMgr,IID_IDisplayUnitMgrEvents,dwCookie),S_OK);

   pMe->Release();

   MoreTests();
}

void CTestDisplayUnitMgr::MoreTests()
{
   CComPtr<IDisplayUnitMgr> pDisplayUnitMgr;
   CComPtr<IUnitSystem> pUnitSystem;
   pUnitSystem.CoCreateInstance( CLSID_UnitSystem );
   pUnitSystem->get_DisplayUnitMgr(&pDisplayUnitMgr);

   CComPtr<IDisplayUnitGroup> group;
   pDisplayUnitMgr->Add(CComBSTR("Distance"),CComBSTR("Length"),&group);

   CComPtr<IDisplayUnitFormatter> formatter;
   formatter.CoCreateInstance( CLSID_DisplayUnitFormatter );
   formatter->FormatSpecifiers(6,3,tjRight,nftFixed,0.0001);

   CComPtr<IDisplayUnit> du;
   group->Add(CComBSTR("m"),unitsSI,formatter,VARIANT_TRUE,&du);

   formatter.Release();
   group.Release();
   pDisplayUnitMgr.Release();
   pUnitSystem.Release();

   // The display unit should still work
   CComBSTR bstrVal;
   du->Format(10,VARIANT_TRUE,&bstrVal);

   TRY_TEST( wcscmp(bstrVal,CComBSTR("10.000 m")), 0 );
}

STDMETHODIMP CTestDisplayUnitMgr::OnFormatChanged(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr::OnDisplayUnitCreated(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/IDisplayUnit* displayUnit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr::OnDisplayUnitRemoved(/*[in]*/ IDisplayUnitGroup* group,/*[in]*/BSTR displayUnit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr::OnDisplayUnitGroupCleared(/*[in]*/ IDisplayUnitGroup* group)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr::OnDisplayUnitGroupCreated(/*[in]*/ IDisplayUnitGroup* group)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr::OnDisplayUnitGroupRemoved(/*[in]*/ BSTR group)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestDisplayUnitMgr::OnDisplayUnitGroupsCleared()
{
   Pass();
   return S_OK;
}

