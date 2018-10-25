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

// TestUnitServer.cpp: implementation of the CTestUnitServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestUnitServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestUnitServer::CTestUnitServer()
{

}

CTestUnitServer::~CTestUnitServer()
{

}

void CTestUnitServer::Test()
{
   CComObject<CTestUnitServer>* pMe;
   CComObject<CTestUnitServer>::CreateInstance(&pMe);
   CComPtr<IUnknown> punk(pMe);

   CComPtr<IUnitServer> unitServer;
   TRY_TEST( unitServer.CoCreateInstance( CLSID_UnitServer ), S_OK );

   DWORD dwCookie;
   TRY_TEST(AtlAdvise(unitServer,punk,IID_IUnitServerEventSink,&dwCookie),S_OK);

   TRY_TEST(unitServer->SetBaseUnits(nullptr,CComBSTR("m"),CComBSTR("sec"),CComBSTR("C"),CComBSTR("rad")),E_INVALIDARG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),nullptr,CComBSTR("sec"),CComBSTR("C"),CComBSTR("rad")),E_INVALIDARG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),nullptr,CComBSTR("C"),CComBSTR("rad")),E_INVALIDARG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),CComBSTR("sec"),nullptr,CComBSTR("rad")),E_INVALIDARG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),CComBSTR("sec"),CComBSTR("C"),nullptr),E_INVALIDARG);

   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("Junk"),CComBSTR("m"),CComBSTR("sec"),CComBSTR("C"),CComBSTR("rad")),UNITS_E_BADUNITTAG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("Junk"),CComBSTR("sec"),CComBSTR("C"),CComBSTR("rad")),UNITS_E_BADUNITTAG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),CComBSTR("Junk"),CComBSTR("C"),CComBSTR("rad")),UNITS_E_BADUNITTAG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),CComBSTR("sec"),CComBSTR("Junk"),CComBSTR("rad")),UNITS_E_BADUNITTAG);
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),CComBSTR("sec"),CComBSTR("C"),CComBSTR("Junk")),UNITS_E_BADUNITTAG);
   
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),CComBSTR("sec"),CComBSTR("C"),CComBSTR("rad")),S_OK);

   // Base units can only be set once. This second call should error out
   TRY_TEST(unitServer->SetBaseUnits(CComBSTR("kg"),CComBSTR("m"),CComBSTR("sec"),CComBSTR("C"),CComBSTR("rad")),UNITS_E_BASEUNITSSET);

   // Get properties
   CComBSTR bstr;
   TRY_TEST(unitServer->get_Mass(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_Mass(&bstr),S_OK);
   TRY_TEST(wcscmp(bstr,CComBSTR("kg")),0);

   TRY_TEST(unitServer->get_Length(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_Length(&bstr),S_OK);
   TRY_TEST(wcscmp(bstr,CComBSTR("m")),0);

   TRY_TEST(unitServer->get_Time(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_Time(&bstr),S_OK);
   TRY_TEST(wcscmp(bstr,CComBSTR("sec")),0);

   TRY_TEST(unitServer->get_Temperature(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_Temperature(&bstr),S_OK);
   TRY_TEST(wcscmp(bstr,CComBSTR("C")),0);

   TRY_TEST(unitServer->get_Angle(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_Angle(&bstr),S_OK);
   TRY_TEST(wcscmp(bstr,CComBSTR("rad")),0);

   CComPtr<IUnitTypes> pUnitTypes;
   TRY_TEST(unitServer->get_UnitTypes(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_UnitTypes(&pUnitTypes),S_OK);
   TRY_TEST(pUnitTypes != nullptr, true );

   CComPtr<IUnitConvert> pConv;
   TRY_TEST(unitServer->get_UnitConvert(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_UnitConvert(&pConv),S_OK);
   TRY_TEST(pConv != 0, true );
   TRY_TEST(pConv.IsEqualObject(unitServer),true);

   CComPtr<IUnitConvert2> pConv2;
   TRY_TEST(unitServer->get_UnitConvert2(nullptr),E_POINTER);
   TRY_TEST(unitServer->get_UnitConvert2(&pConv2),S_OK);
   TRY_TEST(pConv2 != 0, true );
   TRY_TEST(pConv2.IsEqualObject(unitServer),true);

   TRY_TEST(pConv2.IsEqualObject(pConv),true);
   TRY_TEST(pConv.IsEqualObject(pConv2),true);

   // Te following tests provides coverage for IUnitConvert and IUnitConvert2
   // Test Convert
   Float64 val;
   TRY_TEST(pConv->Convert(1.0,nullptr,CComBSTR("ft"),&val),E_INVALIDARG);
   TRY_TEST(pConv->Convert(1.0,CComBSTR("m"),nullptr,&val),E_INVALIDARG);
   TRY_TEST(pConv->Convert(1.0,CComBSTR("Junk"),CComBSTR("ft"),&val),UNITS_E_BADUNITTAG);
   TRY_TEST(pConv->Convert(1.0,CComBSTR("m"),CComBSTR("Junk"),&val),UNITS_E_BADUNITTAG);
   TRY_TEST(pConv->Convert(1.0,CComBSTR("kg"),CComBSTR("ft"),&val),UNITS_E_UNITTYPEMISMATCH);
   TRY_TEST(pConv->Convert(1.0,CComBSTR("m"),CComBSTR("ft"),nullptr),E_POINTER);
   TRY_TEST(pConv->Convert(1.0,CComBSTR("m"),CComBSTR("ft"),&val),S_OK);
   TRY_TEST(IsEqual(val,3.2808,0.0001),true);

   TRY_TEST(pConv->Convert(1.0,CComBSTR("m^2"),CComBSTR("ft^2"),&val),S_OK);
   TRY_TEST(IsEqual(val,10.76391042,0.0001),true);

   TRY_TEST(pConv->Convert(15.0,CComBSTR("F"),CComBSTR("C"),&val),S_OK);
   TRY_TEST(IsEqual(val,-9.44444444,0.0001),true);

   // Test ConvertFromBaseUnits
   TRY_TEST(pConv->ConvertFromBaseUnits(1.0,nullptr,&val),E_INVALIDARG);
   TRY_TEST(pConv->ConvertFromBaseUnits(1.0,CComBSTR("Junk"),&val),UNITS_E_BADUNITTAG);
   TRY_TEST(pConv->ConvertFromBaseUnits(1.0,CComBSTR("ft"),nullptr),E_POINTER);
   TRY_TEST(pConv->ConvertFromBaseUnits(1.0,CComBSTR("ft"),&val),S_OK);
   TRY_TEST(IsEqual(val,3.2808,0.0001),true);

   TRY_TEST(pConv->ConvertFromBaseUnits(1.0,CComBSTR("ft^2"),&val),S_OK);
   TRY_TEST(IsEqual(val,10.76391042,0.0001),true);

   // Test ConvertToBaseUnits
   TRY_TEST(pConv->ConvertToBaseUnits(1.0,nullptr,&val),E_INVALIDARG);
   TRY_TEST(pConv->ConvertToBaseUnits(1.0,CComBSTR("Junk"),&val),UNITS_E_BADUNITTAG);
   TRY_TEST(pConv->ConvertToBaseUnits(1.0,CComBSTR("ft"),nullptr),E_POINTER);
   TRY_TEST(pConv->ConvertToBaseUnits(1.0,CComBSTR("ft"),&val),S_OK);
   TRY_TEST(IsEqual(val,0.3048),true);

   pConv->ConvertToBaseUnits(20.0,CComBSTR("F"),&val);
   pConv->ConvertFromBaseUnits(val,CComBSTR("C"),&val);
   TRY_TEST(IsEqual(val,-6.66666666),true);

   pConv->ConvertToBaseUnits(1.0,CComBSTR("m^2"),&val);
   pConv->ConvertFromBaseUnits(val,CComBSTR("ft^2"),&val);
   TRY_TEST(IsEqual(val,10.76391042,0.0001),true);

   // Test conversion of Temp^2
   CComPtr<IUnitTypes> unitTypes;
   unitServer->get_UnitTypes(&unitTypes);
   CComPtr<IUnitType> utTemp2;
   unitTypes->Add(CComBSTR("Temp2"),0,0,0,2,0,&utTemp2);

   CComPtr<IUnits> pUnits;
   utTemp2->get_Units(&pUnits);

   CComPtr<IUnit> uF2;
   CComPtr<IUnit> uC2;

   pUnits->Add(CComBSTR("F2"),0.0,(5./9.)*(5./9.),0.0,unitsAll,&uF2);
   pUnits->Add(CComBSTR("C2"),0.0,1.0,0.0,unitsAll,&uC2);

   Float64 result;
   pConv2->Convert(15.0,uF2,uC2,&result);
   TRY_TEST( IsEqual(result,4.629629629), true );

   pConv2->ConvertToBaseUnits(15,uF2,&result);
   pConv2->ConvertFromBaseUnits(result,uC2,&result);
   TRY_TEST( IsEqual(result,4.629629629), true );

   // Test conversion of something really weird (15 ft^2*F^3 -> ??? m^2*C^3)
   CComPtr<IUnitType> utWeird;
   unitTypes->Add(CComBSTR("Weird"),0,2,0,3,0,&utWeird);

   pUnits.Release();
   utWeird->get_Units(&pUnits);

   CComPtr<IUnit> uWeirdFrom;
   CComPtr<IUnit> uWeirdTo;

   pUnits->Add(CComBSTR("WeirdFrom"),0.0,(5./9.)*(5./9.)*(5./9.)*0.3048*0.3048,0.0,unitsAll,&uWeirdFrom);
   pUnits->Add(CComBSTR("WeirdTo"),0.0,1.0,0.0,unitsAll,&uWeirdTo);

   pConv2->Convert(15.0,uWeirdFrom,uWeirdTo,&result);
   TRY_TEST( IsEqual(result,0.238948148148), true );

   pConv2->ConvertToBaseUnits(15,uWeirdFrom,&result);
   pConv2->ConvertFromBaseUnits(result,uWeirdTo,&result);
   TRY_TEST( IsEqual(result,0.238948148148), true );

   pConv.Release();
   pConv2.Release();
   pUnitTypes.Release();

   // ****************************************************
   // * Test ISupportErrorInfo
   // ****************************************************
   CComQIPtr<ISupportErrorInfo>  pSEI(unitServer);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnitServer ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnitConvert ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IUnitConvert2 ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
   pSEI.Release();

   ///////////////////////////////////////////////////////////////
   // Test the events
   CComPtr<IUnitType> utVelocity;

   pMe->InitEventTest();
   unitTypes->Add(CComBSTR("Velocity"),0,1,-2,0,0,&utVelocity);
   TRY_TEST(pMe->PassedEventTest(),true);

   CComPtr<IUnits> units;
   utVelocity->get_Units(&units);

   CComPtr<IUnit> uMPS; // meters per second
   pMe->InitEventTest();
   units->Add(CComBSTR("mps"),0.0,1.0,0.0,unitsSI,&uMPS);
   TRY_TEST(pMe->PassedEventTest(),true);

   CComPtr<IUnit> uFPS; // feet per second
   units->Add(CComBSTR("fps"),0.0,0.3048,0.0,unitsUS,&uFPS);

   pMe->InitEventTest();
   units->Remove(CComVariant("mps"));
   TRY_TEST(pMe->PassedEventTest(),true);

   pMe->InitEventTest();
   units->Clear();
   TRY_TEST(pMe->PassedEventTest(),true);

   pMe->InitEventTest();
   unitTypes->Remove(CComVariant(utVelocity));
   TRY_TEST(pMe->PassedEventTest(),true);

   pMe->InitEventTest();
   unitTypes->Clear();
   TRY_TEST(pMe->PassedEventTest(),true);

   unitTypes.Release();
   units.Release();
   uMPS.Release();
   uFPS.Release();
   utVelocity.Release();

   ///////////////////////////////////////////////////////////////
   // Disconnection from Connection point
   TRY_TEST(AtlUnadvise(unitServer,IID_IUnitServerEventSink,dwCookie),S_OK);


   // Non-default internal base units
   // Internal base units that produce kips, inches, and ksi.
   CComPtr<IUnitServer> unitServer2;
   unitServer2.CoCreateInstance( CLSID_UnitServer );
   unitServer2->SetBaseUnits(CComBSTR("12kslug"),CComBSTR("in"),CComBSTR("sec"),CComBSTR("F"),CComBSTR("deg"));

   pConv.Release();
   unitServer2->get_UnitConvert(&pConv);
   pConv->ConvertToBaseUnits(4.0,CComBSTR("ksi"),&val);
   TRY_TEST( IsEqual(val,4.0), true ); // ksi
   pConv->ConvertToBaseUnits(27.5790291727,CComBSTR("MPa"),&val);
   TRY_TEST( IsEqual(val,4.0), true );
}


STDMETHODIMP CTestUnitServer::OnUnitAdded(/*[in]*/IUnitType* unitType,/*[in]*/IUnit* unit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestUnitServer::OnUnitRemoved(/*[in]*/IUnitType* unitType,/*[in]*/BSTR unit)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestUnitServer::OnUnitsCleared(/*[in]*/IUnitType* unitType)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestUnitServer::OnUnitTypeAdded(/*[in]*/IUnitType* unitType)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestUnitServer::OnUnitTypeRemoved(/*[in]*/BSTR unitType)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestUnitServer::OnUnitTypesCleared()
{
   Pass();
   return S_OK;
}
