///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestStationEquationCollection.cpp: implementation of the CTestStationEquationCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestStationEquationCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestStationEquationCollection::CTestStationEquationCollection()
{

}

void CTestStationEquationCollection::Test()
{
   CComPtr<IAlignment> alignment;
   TRY_TEST(alignment.CoCreateInstance(CLSID_Alignment),S_OK);

   CComPtr<IStationEquationCollection> equations;
   TRY_TEST(alignment->get_StationEquations(NULL),E_POINTER);
   TRY_TEST(alignment->get_StationEquations(&equations),S_OK);

   IndexType count;
   TRY_TEST(equations->get_Count(NULL),E_POINTER);
   TRY_TEST(equations->get_Count(&count),S_OK);
   TRY_TEST(count,0);

   CComPtr<IStationEquation> equation;
   TRY_TEST(equations->Add(3400.00,3200.00,&equation),S_OK);
   TRY_TEST(equations->get_Count(&count),S_OK);
   TRY_TEST(count,1);
   Float64 back,ahead;
   equation->GetEquation(&back,&ahead);
   TRY_TEST(IsEqual(back,3400.0),true);
   TRY_TEST(IsEqual(ahead,3200.0),true);

   equation.Release();
   TRY_TEST(equations->Add(200.00,50.0,&equation),COGO_E_STATIONEQUATIONBACK);
   TRY_TEST(equations->Add(4200.0,500.0,&equation),S_OK);
   TRY_TEST(equations->get_Count(&count),S_OK);
   TRY_TEST(count,2);
   equation->GetEquation(&back,&ahead);
   TRY_TEST(IsEqual(back,4200.0),true);
   TRY_TEST(IsEqual(ahead,500.0),true);

   equation.Release();
   TRY_TEST(equations->Add(600.0,1500.0,&equation),S_OK);
   TRY_TEST(equations->get_Count(&count),S_OK);
   TRY_TEST(count,3);
   equation->GetEquation(&back,&ahead);
   TRY_TEST(IsEqual(back,600.0),true);
   TRY_TEST(IsEqual(ahead,1500.0),true);

   // Test with some real values
   TRY_TEST(equations->Clear(),S_OK);
   equation.Release();
   TRY_TEST(equations->Add(1500,1350,&equation),S_OK);
   equation.Release();
   TRY_TEST(equations->Add(2000,2150,&equation),S_OK);
   equation.Release();
   TRY_TEST(equations->Add(3200,4000,&equation),S_OK);
   equation.Release();
   TRY_TEST(equations->Add(4800,0,&equation),S_OK);

   CComPtr<IStation> station;
   station.CoCreateInstance(CLSID_Station);

   // before first equation
   station->SetStation(0,11700);
   Float64 normalizedStation;
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),COGO_E_STATIONRANGEERROR);
   station->SetStation(0,1200);
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),S_OK);
   TRY_TEST(IsEqual(normalizedStation,1200.0),true);

   // after last equation
   station->SetStation(25,11700); // bad zone index
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),E_INVALIDARG);
   station->SetStation(4,-600);
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),COGO_E_STATIONRANGEERROR);
   station->SetStation(4,1200);
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),S_OK);
   TRY_TEST(IsEqual(normalizedStation,5200.0),true);

   station->SetStation(1,11700);
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),COGO_E_STATIONRANGEERROR);
   station->SetStation(1,1250);
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),COGO_E_STATIONRANGEERROR);
   station->SetStation(1,1700);
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),S_OK);
   TRY_TEST(IsEqual(normalizedStation,1850.0),true);

   CComPtr<IStation> objStation;
   TRY_TEST(equations->ConvertToNormalizedStationEx(CComVariant(station),NULL),E_POINTER);
   TRY_TEST(equations->ConvertToNormalizedStationEx(CComVariant(station),&objStation),S_OK);
   ZoneIndexType idx;
   Float64 value;
   objStation->GetStation(&idx,&value);
   TRY_TEST(idx,INVALID_INDEX);
   TRY_TEST(IsEqual(value,1850.0),true);

   // station is already normalized
   station->SetStation(INVALID_INDEX,1700);
   TRY_TEST(equations->ConvertToNormalizedStation(CComVariant(station),&normalizedStation),S_OK);
   TRY_TEST(IsEqual(normalizedStation,1700.0),true);

   station.Release();
   TRY_TEST(equations->ConvertFromNormalizedStation(1200.0,NULL),E_POINTER);
   TRY_TEST(equations->ConvertFromNormalizedStation(1200.0,&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,0);
   TRY_TEST(IsEqual(value,1200.0),true);

   station.Release();
   TRY_TEST(equations->ConvertFromNormalizedStation(1800.0,&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,1);
   TRY_TEST(IsEqual(value,1650.0),true);

   station.Release();
   TRY_TEST(equations->ConvertFromNormalizedStation(2300.0,&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,2);
   TRY_TEST(IsEqual(value,2300.0),true);

   station.Release();
   TRY_TEST(equations->ConvertFromNormalizedStation(3300.0,&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,3);
   TRY_TEST(IsEqual(value,4100.0),true);

   station.Release();
   TRY_TEST(equations->ConvertFromNormalizedStation(4500.0,&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,4);
   TRY_TEST(IsEqual(value,500.0),true);

   // at equation idx = 1
   station.Release();
   TRY_TEST(equations->ConvertFromNormalizedStation(2150,&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,1);
   TRY_TEST(IsEqual(value,2000.),true);

   // at equation idx = 2
   station.Release();
   TRY_TEST(equations->ConvertFromNormalizedStation(3200,&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,2);
   TRY_TEST(IsEqual(value,3200.0),true);

   station.Release();
   objStation->SetStation(1,1360); // bad zone
   TRY_TEST(equations->ConvertFromNormalizedStationEx(CComVariant(objStation),&station),E_INVALIDARG);
   objStation->SetStation(INVALID_INDEX,1360);
   TRY_TEST(equations->ConvertFromNormalizedStationEx(CComVariant(objStation),&station),S_OK);
   TRY_TEST(station->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,0);
   TRY_TEST(IsEqual(value,1360.0),true);

   // Test Distance
   Float64 dist;
   equations->Distance(CComVariant(2000),CComVariant(3000),&dist);
   TRY_TEST(IsEqual(dist,1000.0),true);
   equations->Distance(CComVariant(3000),CComVariant(2000),&dist);
   TRY_TEST(IsEqual(dist,-1000.0),true);
   objStation->SetStation(1,1400);
   station->SetStation(2,3000);
   equations->Distance(CComVariant(objStation),CComVariant(station),&dist);
   TRY_TEST(IsEqual(dist,1450.0),true);

   // Test increment
   objStation->SetStation(3,4100);
   equations->IncrementBy(objStation,-500);
   TRY_TEST(objStation->GetStation(&idx,&value),S_OK);
   TRY_TEST(idx,2);
   TRY_TEST(IsEqual(value,2800.0),true);


   // Test Events
   CComObject<CTestStationEquationCollection>* pTestStationEquationCollection;
   CComObject<CTestStationEquationCollection>::CreateInstance(&pTestStationEquationCollection);
   pTestStationEquationCollection->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestStationEquationCollection);
   TRY_TEST(AtlAdvise(equations,punk,IID_IStationEquationCollectionEvents,&dwCookie),S_OK);

   pTestStationEquationCollection->InitEventTest();
   equations->Clear();
   TRY_TEST(pTestStationEquationCollection->PassedEventTest(), true );

   pTestStationEquationCollection->InitEventTest();
   equation.Release();
   equations->Add(1500,1350,&equation);
   TRY_TEST(pTestStationEquationCollection->PassedEventTest(), true );

   pTestStationEquationCollection->InitEventTest();
   equation.Release();
   equations->Add(2000,2150,&equation);
   TRY_TEST(pTestStationEquationCollection->PassedEventTest(), true );

   pTestStationEquationCollection->InitEventTest();
   equations->Remove(0);
   TRY_TEST(pTestStationEquationCollection->PassedEventTest(), true );

   TRY_TEST(AtlUnadvise(equations,IID_IStationEquationCollectionEvents,dwCookie),S_OK);
   pTestStationEquationCollection->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(equations);
   TRY_TEST( eInfo != NULL, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStationEquationCollection ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_StationEquationCollection,IID_IStationEquationCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_StationEquationCollection,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestStationEquationCollection::OnEquationAdded(CollectionIndexType idx,IStationEquation* pp)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestStationEquationCollection::OnEquationRemoved(CollectionIndexType idx)
{
   Pass();
   return S_OK;
}

STDMETHODIMP CTestStationEquationCollection::OnEquationsCleared()
{
   Pass();
   return S_OK;
}
