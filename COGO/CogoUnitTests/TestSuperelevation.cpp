///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestSuperelevation.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestSuperelevation.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestSuperelevation)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<ISuperelevation> pSuperelevation;
         ASSERT_EQ(pSuperelevation.CoCreateInstance(CLSID_Superelevation),S_OK);

         CComPtr<IStation> objStation;
         Float64 station;
         ZoneIndexType zoneIdx;
         ASSERT_EQ(pSuperelevation->get_BeginTransition(nullptr),E_POINTER);
         ASSERT_EQ(pSuperelevation->get_BeginTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pSuperelevation->put_BeginTransition(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pSuperelevation->get_BeginTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pSuperelevation->put_BeginTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

         objStation.Release();

         ASSERT_EQ(pSuperelevation->get_BeginFullSuper(nullptr),E_POINTER);
         ASSERT_EQ(pSuperelevation->get_BeginFullSuper(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pSuperelevation->put_BeginFullSuper(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pSuperelevation->get_BeginFullSuper(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pSuperelevation->put_BeginFullSuper(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

         objStation.Release();

         ASSERT_EQ(pSuperelevation->get_EndFullSuper(nullptr),E_POINTER);
         ASSERT_EQ(pSuperelevation->get_EndFullSuper(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pSuperelevation->put_EndFullSuper(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pSuperelevation->get_EndFullSuper(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pSuperelevation->put_EndFullSuper(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

         objStation.Release();

         ASSERT_EQ(pSuperelevation->get_EndTransition(nullptr),E_POINTER);
         ASSERT_EQ(pSuperelevation->get_EndTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pSuperelevation->put_EndTransition(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pSuperelevation->get_EndTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pSuperelevation->put_EndTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized


         Float64 rate;
         ASSERT_EQ(pSuperelevation->get_Rate(nullptr),E_POINTER);
         ASSERT_EQ(pSuperelevation->get_Rate(&rate),S_OK);
         ASSERT_EQ(IsEqual(rate,0.0),true);
         ASSERT_EQ(pSuperelevation->put_Rate(5.0),S_OK);
         ASSERT_EQ(pSuperelevation->get_Rate(&rate),S_OK);
         ASSERT_EQ(IsEqual(rate,5.0),true);

         IndexType pivotPnt;
         ASSERT_EQ(pSuperelevation->get_PivotPoint(nullptr),E_POINTER);
         ASSERT_EQ(pSuperelevation->get_PivotPoint(nullptr),E_POINTER);
         ASSERT_EQ(pSuperelevation->get_PivotPoint(&pivotPnt),S_OK);
         ASSERT_EQ(pivotPnt,0);

         ASSERT_EQ(pSuperelevation->put_PivotPoint(1),S_OK);
         ASSERT_EQ(pSuperelevation->get_PivotPoint(&pivotPnt),S_OK);
         ASSERT_EQ(pivotPnt,1);

         // Test ISupportErrorInfo
         CComQIPtr<ISupportErrorInfo> eInfo(pSuperelevation);
         ASSERT_EQ( eInfo != nullptr, true );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISuperelevation ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         // Test IObjectSafety
         ASSERT_EQ( TestIObjectSafety(CLSID_Superelevation,IID_ISuperelevation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests