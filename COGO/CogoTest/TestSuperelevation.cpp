///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

// TestSuperelevation.cpp: implementation of the CTestSuperelevation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestSuperelevation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestSuperelevation::CTestSuperelevation()
{

}

void CTestSuperelevation::Test()
{
   CComPtr<ISuperelevation> pSuperelevation;
   TRY_TEST(pSuperelevation.CoCreateInstance(CLSID_Superelevation),S_OK);

#pragma Reminder("UPDATE: methods that are not tested")
      //[helpstring("method Init")] HRESULT Init([in]IProfile* pProfile,[in] VARIANT varBeginStation,[in] VARIANT varBeginFullStation, [in] VARIANT varEndFullStation,[in] VARIANT varEndStation,[in] Float64 Superelevation,[in]IndexType pnt1,[in]IndexType pnt2);
      //[propget, helpstring("property Profile")] HRESULT Profile([out, retval] IProfile* *pVal);
      //[propputref, helpstring("property Profile")] HRESULT Profile([in] IProfile* newVal);
      //[helpstring("method Clone")] HRESULT Clone([out,retval]ISuperelevation** ppClone);

   CComPtr<IStation> objStation;
   Float64 station;
   ZoneIndexType zoneIdx;
   TRY_TEST(pSuperelevation->get_BeginTransition(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_BeginTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pSuperelevation->put_BeginTransition(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pSuperelevation->get_BeginTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pSuperelevation->put_BeginTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

   objStation.Release();

   TRY_TEST(pSuperelevation->get_BeginFullSuper(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_BeginFullSuper(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pSuperelevation->put_BeginFullSuper(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pSuperelevation->get_BeginFullSuper(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pSuperelevation->put_BeginFullSuper(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

   objStation.Release();

   TRY_TEST(pSuperelevation->get_EndFullSuper(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_EndFullSuper(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pSuperelevation->put_EndFullSuper(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pSuperelevation->get_EndFullSuper(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pSuperelevation->put_EndFullSuper(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

   objStation.Release();

   TRY_TEST(pSuperelevation->get_EndTransition(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_EndTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pSuperelevation->put_EndTransition(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pSuperelevation->get_EndTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pSuperelevation->put_EndTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized


   Float64 rate;
   TRY_TEST(pSuperelevation->get_Rate(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_Rate(&rate),S_OK);
   TRY_TEST(IsEqual(rate,0.0),true);
   TRY_TEST(pSuperelevation->put_Rate(5.0),S_OK);
   TRY_TEST(pSuperelevation->get_Rate(&rate),S_OK);
   TRY_TEST(IsEqual(rate,5.0),true);

   IndexType pivotPnt;
   TRY_TEST(pSuperelevation->get_PivotPoint(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_PivotPoint(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_PivotPoint(&pivotPnt),S_OK);
   TRY_TEST(pivotPnt,0);

   TRY_TEST(pSuperelevation->put_PivotPoint(1),S_OK);
   TRY_TEST(pSuperelevation->get_PivotPoint(&pivotPnt),S_OK);
   TRY_TEST(pivotPnt,1);

   CComPtr<IStructuredStorage2> ss;
   TRY_TEST(pSuperelevation->get_StructuredStorage(nullptr),E_POINTER);
   TRY_TEST(pSuperelevation->get_StructuredStorage(&ss),S_OK);
   TRY_TEST(ss != nullptr,true);


   // Test Events
   CComObject<CTestSuperelevation>* pTestSuperelevation;
   CComObject<CTestSuperelevation>::CreateInstance(&pTestSuperelevation);
   pTestSuperelevation->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestSuperelevation);
   TRY_TEST(AtlAdvise(pSuperelevation,punk,IID_ISuperelevationEvents,&dwCookie),S_OK);


   pTestSuperelevation->InitEventTest();
   TRY_TEST(pSuperelevation->put_BeginTransition(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestSuperelevation->PassedEventTest(), true );

   pTestSuperelevation->InitEventTest();
   TRY_TEST(pSuperelevation->put_BeginFullSuper(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestSuperelevation->PassedEventTest(), true );

   pTestSuperelevation->InitEventTest();
   TRY_TEST(pSuperelevation->put_EndFullSuper(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestSuperelevation->PassedEventTest(), true );

   pTestSuperelevation->InitEventTest();
   TRY_TEST(pSuperelevation->put_EndTransition(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestSuperelevation->PassedEventTest(), true );


   pTestSuperelevation->InitEventTest();
   TRY_TEST(pSuperelevation->put_PivotPoint(0),S_OK);
   TRY_TEST(pTestSuperelevation->PassedEventTest(), true );

   pTestSuperelevation->InitEventTest();
   TRY_TEST(pSuperelevation->put_Rate(0.06),S_OK);
   TRY_TEST(pTestSuperelevation->PassedEventTest(), true );

   TRY_TEST(AtlUnadvise(pSuperelevation,IID_ISuperelevationEvents,dwCookie),S_OK);
   pTestSuperelevation->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pSuperelevation);
   TRY_TEST( eInfo != nullptr, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISuperelevation ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Superelevation,IID_ISuperelevation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Superelevation,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestSuperelevation::OnSuperelevationChanged(ISuperelevation* Superelevation)
{
   Pass();
   return S_OK;
}
