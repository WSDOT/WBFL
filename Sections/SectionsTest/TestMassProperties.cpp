///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// TestMassProperties.cpp: implementation of the CTestMassProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMassProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestMassProperties::CTestMassProperties()
{

}

CTestMassProperties::~CTestMassProperties()
{

}

void CTestMassProperties::Test()
{
   CComPtr<IMassProperties> props;
   TRY_TEST(props.CoCreateInstance(CLSID_MassProperties),S_OK);

   // Default value should be zero
   Float64 mass;
   TRY_TEST(props->get_MassPerLength(&mass),S_OK);
   TRY_TEST(IsZero(mass),true);

   // Test for errors
   TRY_TEST(props->get_MassPerLength(nullptr),E_POINTER);

   // This is a legal value.
   TRY_TEST(props->put_MassPerLength(-1),S_OK);

   //  Put a number in and see if you get it back out
   props->put_MassPerLength(50);
   props->get_MassPerLength(&mass);
   TRY_TEST(IsEqual(50.0,mass),true);

   // Add mass properties
   CComPtr<IMassProperties> props2;
   props2.CoCreateInstance(CLSID_MassProperties);
   props->put_MassPerLength(100);
   props2->put_MassPerLength(5.5);
   TRY_TEST(props->AddProperties(nullptr),E_INVALIDARG);
   TRY_TEST(props->AddProperties(props2),S_OK);
   props->get_MassPerLength(&mass);
   TRY_TEST(IsEqual(mass,105.5),true);
   props2->get_MassPerLength(&mass);
   TRY_TEST(IsEqual(mass,5.5),true);

   // make sure it works the other direction
   props->put_MassPerLength(100);
   props2->put_MassPerLength(5.5);
   TRY_TEST(props2->AddProperties(props),S_OK);
   props2->get_MassPerLength(&mass);
   TRY_TEST(IsEqual(mass,105.5),true);
   props->get_MassPerLength(&mass);
   TRY_TEST(IsEqual(mass,100.0),true);

   //////////////////////////////////////////////////////////////
   // Test ISupportErrorInfo
   CComQIPtr<ISupportErrorInfo>  pSEI(props);
   TRY_TEST( pSEI != 0, true );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IMassProperties ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );
   TRY_TEST( pSEI->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //////////////////////////////////////////////////////////////
   // Test IObjectSafety
   CComQIPtr<IObjectSafety> pObjSafety(props);
   TRY_TEST(pObjSafety != 0,true);
   DWORD dwDesiredOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
   DWORD dwSupportedOptions, dwEnabledOptions;
   pObjSafety->GetInterfaceSafetyOptions(IID_IMassProperties,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
   pObjSafety->GetInterfaceSafetyOptions(IID_IStructuredStorage2,&dwSupportedOptions,&dwEnabledOptions);
   TRY_TEST( dwSupportedOptions, dwDesiredOptions );
}
