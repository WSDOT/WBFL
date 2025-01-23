///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo> eInfo(pSuperelevation);
   TRY_TEST( eInfo != nullptr, true );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISuperelevation ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(CLSID_Superelevation,IID_ISuperelevation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
