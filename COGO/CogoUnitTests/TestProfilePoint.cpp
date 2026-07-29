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

// TestProfilePoint.cpp
//
// Ported from F:\ARP\WBFL\COGO\CogoTest\TestProfilePoint.cpp (legacy WBFLTest.h
// harness) to MSVC CppUnitTestFramework, talking to WBFLCogo.dll purely
// through its public COM interfaces (see CogoTestUtil.h).
#include "pch.h"

namespace CogoUnitTests
{

TEST_CLASS(TestProfilePoint)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IProfilePoint> pProfilePoint;
         ASSERT_EQ(pProfilePoint.CoCreateInstance(CLSID_ProfilePoint),S_OK);

         Float64 sta1,elev1;
         Float64 sta = 10.0;
         Float64 elev = 20.0;

         // Test Properties
         ASSERT_EQ( pProfilePoint->put_Station(CComVariant(sta)), S_OK );

         CComPtr<IStation> station;
         ASSERT_EQ( pProfilePoint->get_Station(&station), S_OK);
         station->get_Value(&sta1);
         ASSERT_EQ( IsEqual(sta,sta1),true );

         ASSERT_EQ( pProfilePoint->put_Elevation(elev), S_OK );
         ASSERT_EQ( pProfilePoint->get_Elevation(&elev1), S_OK);
         ASSERT_EQ( IsEqual(elev,elev1),true );

         ASSERT_EQ( pProfilePoint->get_Station(nullptr), E_POINTER );
         ASSERT_EQ( pProfilePoint->get_Elevation(nullptr), E_POINTER );

         // Test ISupportErrorInfo
         CComQIPtr<ISupportErrorInfo> eInfo(pProfilePoint);
         ASSERT_EQ( eInfo != nullptr, true );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_IProfilePoint ), S_OK );
         ASSERT_EQ( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         // Test IObjectSafety
         ASSERT_EQ( TestIObjectSafety(CLSID_ProfilePoint,IID_IProfilePoint,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   }
};
} // namespace CogoUnitTests