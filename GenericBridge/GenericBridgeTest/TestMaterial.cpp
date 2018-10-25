///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright © 1999-2015  Washington State Department of Transportation
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

// TestMaterial.cpp: implementation of the CTestMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestMaterial::CTestMaterial()
{

}

CTestMaterial::~CTestMaterial()
{

}

void CTestMaterial::Test()
{
   HRESULT hr;
   CComPtr<IMaterial> material;
   hr = material.CoCreateInstance(CLSID_Material);
   TRY_TEST(hr,S_OK);

   ///////////////////////////////////////
   // Test simple set/get
   Float64 value;
   TRY_TEST(material->put_E(0,-12.2),E_INVALIDARG);
   TRY_TEST(material->put_E(0,100),S_OK);
   TRY_TEST(material->get_E(0,NULL),E_POINTER);;
   TRY_TEST(material->get_E(0,&value),S_OK);;
   TRY_TEST(IsEqual(value,100.0),true);

   TRY_TEST(material->put_Density(0,-12.2),S_OK);
   TRY_TEST(material->put_Density(1,0),S_OK);
   TRY_TEST(material->put_Density(2,100),S_OK);
   TRY_TEST(material->get_Density(0,NULL),E_POINTER);;
   TRY_TEST(material->get_Density(2,&value),S_OK);;
   TRY_TEST(IsEqual(value,100.0),true);

   ///////////////////////////////////////
   // Test Error Info
   CComQIPtr<ISupportErrorInfo> eInfo(material);
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IMaterial ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   // Test IObjectSafety
   TRY_TEST( TestIObjectSafety(material,IID_IMaterial,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   TRY_TEST( TestIObjectSafety(material,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
