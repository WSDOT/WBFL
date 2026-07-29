///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
// Copyright � 1999-2026  Washington State Department of Transportation
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

// TestMassProperties.cpp
//
// Ported from F:\ARP\WBFL\Geometry\GeometryTest\TestMassProperties.cpp (legacy
// WBFLTest.h harness) to MSVC CppUnitTestFramework, talking to
// WBFLGeometry.dll purely through its public COM interfaces (see
// GeometryTestUtil.h).
#include "pch.h"

namespace GeometryUnitTests
{

TEST_CLASS(TestMassProperties)
{
public:
   TEST_METHOD(BasicOperations)
   {
         CComPtr<IMassProperties> props;
         ASSERT_EQ(props.CoCreateInstance(CLSID_MassProperties),S_OK);

         // Default value should be zero
         Float64 mass;
         ASSERT_EQ(props->get_MassPerLength(&mass),S_OK);
         ASSERT_EQ(IsZero(mass),true);

         // Test for errors
         ASSERT_EQ(props->get_MassPerLength(nullptr),E_POINTER);

         // This is a legal value.
         ASSERT_EQ(props->put_MassPerLength(-1),S_OK);

         //  Put a number in and see if you get it back out
         props->put_MassPerLength(50);
         props->get_MassPerLength(&mass);
         ASSERT_EQ(IsEqual(50.0,mass),true);

         // Add mass properties
         CComPtr<IMassProperties> props2;
         props2.CoCreateInstance(CLSID_MassProperties);
         props->put_MassPerLength(100);
         props2->put_MassPerLength(5.5);
         ASSERT_EQ(props->AddProperties(nullptr),E_INVALIDARG);
         ASSERT_EQ(props->AddProperties(props2),S_OK);
         props->get_MassPerLength(&mass);
         ASSERT_EQ(IsEqual(mass,105.5),true);
         props2->get_MassPerLength(&mass);
         ASSERT_EQ(IsEqual(mass,5.5),true);

         // make sure it works the other direction
         props->put_MassPerLength(100);
         props2->put_MassPerLength(5.5);
         ASSERT_EQ(props2->AddProperties(props),S_OK);
         props2->get_MassPerLength(&mass);
         ASSERT_EQ(IsEqual(mass,105.5),true);
         props->get_MassPerLength(&mass);
         ASSERT_EQ(IsEqual(mass,100.0),true);

         //////////////////////////////////////////////////////////////
         // Test ISupportErrorInfo
         CComQIPtr<ISupportErrorInfo>  pSEI(props);
         ASSERT_EQ( pSEI != nullptr, true );
         ASSERT_EQ( pSEI->InterfaceSupportsErrorInfo( IID_IMassProperties ), S_OK );
         ASSERT_EQ( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

         //////////////////////////////////////////////////////////////
         // Test IObjectSafety
         CComQIPtr<IObjectSafety> pObjSafety(props);
         ASSERT_EQ(pObjSafety != nullptr,true);
         DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
         DWORD dwSupportedOptions, dwEnabledOptions;
         pObjSafety->GetInterfaceSafetyOptions(IID_IMassProperties,&dwSupportedOptions,&dwEnabledOptions);
         ASSERT_EQ( dwSupportedOptions, dwDesiredOptions );
   }
};
} // namespace GeometryUnitTests