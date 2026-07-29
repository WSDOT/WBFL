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

// TestWidening.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestWidening.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestWidening)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IWidening> pWidening;
         ASSERT_EQ(pWidening.CoCreateInstance(CLSID_Widening),S_OK);

      #pragma Reminder("UPDATE: methods that are not tested")
            //[helpstring("method Init")] HRESULT Init([in]IProfile* pProfile,[in] VARIANT varBeginStation,[in] VARIANT varBeginFullStation, [in] VARIANT varEndFullStation,[in] VARIANT varEndStation,[in] Float64 widening,[in]IndexType pnt1,[in]IndexType pnt2);
            //[propget, helpstring("property Profile")] HRESULT Profile([out, retval] IProfile* *pVal);
            //[propput, helpstring("property Profile")] HRESULT Profile([in] IProfile* newVal);
            //[helpstring("method Clone")] HRESULT Clone([out,retval]IWidening** ppClone);

         CComPtr<IStation> objStation;
         Float64 station;
         ZoneIndexType zoneIdx;
         ASSERT_EQ(pWidening->get_BeginTransition(nullptr),E_POINTER);
         ASSERT_EQ(pWidening->get_BeginTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pWidening->put_BeginTransition(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pWidening->get_BeginTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pWidening->put_BeginTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

         objStation.Release();

         ASSERT_EQ(pWidening->get_BeginFullWidening(nullptr),E_POINTER);
         ASSERT_EQ(pWidening->get_BeginFullWidening(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pWidening->put_BeginFullWidening(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pWidening->get_BeginFullWidening(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pWidening->put_BeginFullWidening(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

         objStation.Release();

         ASSERT_EQ(pWidening->get_EndFullWidening(nullptr),E_POINTER);
         ASSERT_EQ(pWidening->get_EndFullWidening(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pWidening->put_EndFullWidening(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pWidening->get_EndFullWidening(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pWidening->put_EndFullWidening(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized

         objStation.Release();

         ASSERT_EQ(pWidening->get_EndTransition(nullptr),E_POINTER);
         ASSERT_EQ(pWidening->get_EndTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,0.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         ASSERT_EQ(pWidening->put_EndTransition(CComVariant(100.0)),S_OK);
         objStation.Release();
         ASSERT_EQ(pWidening->get_EndTransition(&objStation),S_OK);
         objStation->get_Value(&station);
         ASSERT_EQ(IsEqual(station,100.0),true);
         objStation->get_StationZoneIndex(&zoneIdx);
         ASSERT_EQ(zoneIdx,INVALID_INDEX);

         objStation->put_StationZoneIndex(4);
         ASSERT_EQ(pWidening->put_EndTransition(CComVariant(objStation)),E_INVALIDARG); // not associated with profile so station must be normalized


         Float64 widening;
         ASSERT_EQ(pWidening->get_Widening(nullptr),E_POINTER);
         ASSERT_EQ(pWidening->get_Widening(&widening),S_OK);
         ASSERT_EQ(IsEqual(widening,0.0),true);
         ASSERT_EQ(pWidening->put_Widening(5.0),S_OK);
         ASSERT_EQ(pWidening->get_Widening(&widening),S_OK);
         ASSERT_EQ(IsEqual(widening,5.0),true);

         IndexType segmentIdx;
         ASSERT_EQ(pWidening->get_Segment(0,nullptr),E_POINTER);
         ASSERT_EQ(pWidening->get_Segment(1,nullptr),E_POINTER);
         ASSERT_EQ(pWidening->get_Segment(0,&segmentIdx),S_OK);
         ASSERT_EQ(segmentIdx,0);
         ASSERT_EQ(pWidening->get_Segment(1,&segmentIdx),S_OK);
         ASSERT_EQ(segmentIdx,INVALID_INDEX);
         ASSERT_EQ(pWidening->get_Segment(2,&segmentIdx),E_INVALIDARG);

         ASSERT_EQ(pWidening->put_Segment(0,5),S_OK);
         ASSERT_EQ(pWidening->get_Segment(0,&segmentIdx),S_OK);
         ASSERT_EQ(segmentIdx,5);

         // Test ISupportErrorInfo
         CComQIPtr<ISupportErrorInfo> eInfo(pWidening);
         ASSERT_EQ( eInfo != nullptr, true );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IWidening ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         // Test IObjectSafety
         ASSERT_EQ( TestIObjectSafety(CLSID_Widening,IID_IWidening,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests