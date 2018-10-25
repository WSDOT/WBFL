///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

// TestWidening.cpp: implementation of the CTestWidening class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestWidening.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestWidening::CTestWidening()
{

}

void CTestWidening::Test()
{
   CComPtr<IWidening> pWidening;
   TRY_TEST(pWidening.CoCreateInstance(CLSID_Widening),S_OK);

#pragma Reminder("UPDATE: methods that are not tested")
      //[helpstring("method Init")] HRESULT Init([in]IProfile* pProfile,[in] VARIANT varBeginStation,[in] VARIANT varBeginFullStation, [in] VARIANT varEndFullStation,[in] VARIANT varEndStation,[in] Float64 widening,[in]IndexType pnt1,[in]IndexType pnt2);
      //[propget, helpstring("property Profile")] HRESULT Profile([out, retval] IProfile* *pVal);
      //[propputref, helpstring("property Profile")] HRESULT Profile([in] IProfile* newVal);
      //[helpstring("method Clone")] HRESULT Clone([out,retval]IWidening** ppClone);

   CComPtr<IStation> objStation;
   Float64 station;
   ZoneIndexType zoneIdx;
   TRY_TEST(pWidening->get_BeginTransition(nullptr),E_POINTER);
   TRY_TEST(pWidening->get_BeginTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pWidening->put_BeginTransition(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pWidening->get_BeginTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pWidening->put_BeginTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

   objStation.Release();

   TRY_TEST(pWidening->get_BeginFullWidening(nullptr),E_POINTER);
   TRY_TEST(pWidening->get_BeginFullWidening(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pWidening->put_BeginFullWidening(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pWidening->get_BeginFullWidening(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pWidening->put_BeginFullWidening(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

   objStation.Release();

   TRY_TEST(pWidening->get_EndFullWidening(nullptr),E_POINTER);
   TRY_TEST(pWidening->get_EndFullWidening(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pWidening->put_EndFullWidening(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pWidening->get_EndFullWidening(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pWidening->put_EndFullWidening(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

   objStation.Release();

   TRY_TEST(pWidening->get_EndTransition(nullptr),E_POINTER);
   TRY_TEST(pWidening->get_EndTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,0.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   TRY_TEST(pWidening->put_EndTransition(CComVariant(100.0)),S_OK);
   objStation.Release();
   TRY_TEST(pWidening->get_EndTransition(&objStation),S_OK);
   objStation->get_Value(&station);
   TRY_TEST(IsEqual(station,100.0),true);
   objStation->get_StationZoneIndex(&zoneIdx);
   TRY_TEST(zoneIdx,INVALID_INDEX);

   objStation->put_StationZoneIndex(4);
   TRY_TEST(pWidening->put_EndTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized


   Float64 widening;
   TRY_TEST(pWidening->get_Widening(nullptr),E_POINTER);
   TRY_TEST(pWidening->get_Widening(&widening),S_OK);
   TRY_TEST(IsEqual(widening,0.0),true);
   TRY_TEST(pWidening->put_Widening(5.0),S_OK);
   TRY_TEST(pWidening->get_Widening(&widening),S_OK);
   TRY_TEST(IsEqual(widening,5.0),true);

   IndexType segmentIdx;
   TRY_TEST(pWidening->get_Segment(0,nullptr),E_POINTER);
   TRY_TEST(pWidening->get_Segment(1,nullptr),E_POINTER);
   TRY_TEST(pWidening->get_Segment(0,&segmentIdx),S_OK);
   TRY_TEST(segmentIdx,0);
   TRY_TEST(pWidening->get_Segment(1,&segmentIdx),S_OK);
   TRY_TEST(segmentIdx,INVALID_INDEX);
   TRY_TEST(pWidening->get_Segment(2,&segmentIdx),E_INVALIDARG);

   TRY_TEST(pWidening->put_Segment(0,5),S_OK);
   TRY_TEST(pWidening->get_Segment(0,&segmentIdx),S_OK);
   TRY_TEST(segmentIdx,5);

   CComPtr<IStructuredStorage2> ss;
   TRY_TEST(pWidening->get_StructuredStorage(nullptr),E_POINTER);
   TRY_TEST(pWidening->get_StructuredStorage(&ss),S_OK);
   TRY_TEST(ss != nullptr,true);


   // Test Events
   CComObject<CTestWidening>* pTestWidening;
   CComObject<CTestWidening>::CreateInstance(&pTestWidening);
   pTestWidening->AddRef();

   DWORD dwCookie;
   CComPtr<IUnknown> punk(pTestWidening);
   TRY_TEST(AtlAdvise(pWidening,punk,IID_IWideningEvents,&dwCookie),S_OK);


   pTestWidening->InitEventTest();
   TRY_TEST(pWidening->put_BeginTransition(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestWidening->PassedEventTest(), true );

   pTestWidening->InitEventTest();
   TRY_TEST(pWidening->put_BeginFullWidening(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestWidening->PassedEventTest(), true );

   pTestWidening->InitEventTest();
   TRY_TEST(pWidening->put_EndFullWidening(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestWidening->PassedEventTest(), true );

   pTestWidening->InitEventTest();
   TRY_TEST(pWidening->put_EndTransition(CComVariant(200.0)),S_OK);
   TRY_TEST(pTestWidening->PassedEventTest(), true );


   pTestWidening->InitEventTest();
   TRY_TEST(pWidening->put_Segment(1,5),S_OK);
   TRY_TEST(pTestWidening->PassedEventTest(), true );

   pTestWidening->InitEventTest();
   TRY_TEST(pWidening->put_Widening(10.0),S_OK);
   TRY_TEST(pTestWidening->PassedEventTest(), true );

   TRY_TEST(AtlUnadvise(pWidening,IID_IWideningEvents,dwCookie),S_OK);
   pTestWidening->Release();

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pWidening);
   TRY_TEST( eInfo != nullptr, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IWidening ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Widening,IID_IWidening,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(CLSID_Widening,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}

STDMETHODIMP CTestWidening::OnWideningChanged(IWidening* Widening)
{
   Pass();
   return S_OK;
}
